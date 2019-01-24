#include <memory>
#include <stdlib.h>

#include "UHH2/core/include/Utils.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/EventHelper.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/core/include/AnalysisModule.h"

#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/LumiSelection.h> //includes also LuminosityHists.h
#include <UHH2/common/include/TriggerSelection.h>
#include "UHH2/common/include/CleaningModules.h"
#include <UHH2/common/include/NSelections.h> 
#include <UHH2/common/include/MuonIds.h> 
#include <UHH2/common/include/ElectronIds.h>
#include "UHH2/common/include/PrintingModules.h"

#include "UHH2/TriggersExamination/include/Lumi2016Hists.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"


using namespace uhh2;
using namespace std;
    
bool operator<(const run_lumi & rl1, const run_lumi & rl2){
    if(rl1.run == rl2.run){
        return rl1.lumiblock < rl2.lumiblock;
    }
    else{
        return rl1.run < rl2.run;
    }
}


Lumi2016Hists::Lumi2016Hists(uhh2::Context & ctx,
                                const std::string & dirname,
				const std::string & triggername,
				bool do_inst_lumi_hist) :
    Hists(ctx, dirname),
    triggername_(triggername),
    do_inst_lumi_hist_(do_inst_lumi_hist)
{
    lumi_per_bin = string2double(ctx.get("lumihists_lumi_per_bin", "50.0"));
    if(lumi_per_bin <= 0.0) {
        throw runtime_error("lumihists_lumi_per_bin is <= 0.0; this is not allowed");
    }
    
    trigger_fwd     = (ctx.get("Trigger_FWD") == "true");

    string lumifile = ctx.get("lumi_file");
    std::unique_ptr<TFile> file(TFile::Open(lumifile.c_str(), "read"));
    TTree * tree = dynamic_cast<TTree*>(file->Get("AnalysisTree"));
    if(!tree){
        throw runtime_error("LuminosityHists: Did not find TTree 'AnalysisTree' in file ;" + lumifile + "'");
    }
    // only fetch branches we really need:
    TBranch * brun = tree->GetBranch("run");
    TBranch * blumiblock = tree->GetBranch("luminosityBlock");
    TBranch * bilumi = tree->GetBranch("intgRecLumi");
    run_lumi rl;
    double ilumi;
    brun->SetAddress(&rl.run);
    blumiblock->SetAddress(&rl.lumiblock);
    bilumi->SetAddress(&ilumi);
    
    // use the file to build a map from run/lumi --> integrated lumi in pb.
    // Inserting into a map sorts by run and lumi.

    double total_lumi = 0.0; // in   1/pb
    double maxinstlumi = 0.0;
    auto ientries = tree->GetEntries();
    
    for(auto ientry = 0l; ientry < ientries; ientry++){
        for(auto b : {brun, blumiblock, bilumi}){
            b->GetEntry(ientry);
        }
        double ilumi_pb = ilumi * 1e-6; // convert units in file (microbarn) to pb.
	if(ilumi_pb > maxinstlumi) maxinstlumi = ilumi_pb;
        total_lumi += ilumi_pb;
        auto it_inserted = rl2lumi.insert(make_pair(rl, ilumi_pb));
        if(!it_inserted.second){
            throw runtime_error("Duplicate run/lumi entry in lumi file '" + lumifile + "'");
        }

    }
    //cout << "LuminosityHists: read total lumi " << total_lumi << " from lumi file " << lumifile << endl;
    
    // Save the bin borders to find out the number of bins to use and for later assigning each event to a bin.
    int nbins_estimated = int(total_lumi / lumi_per_bin + 1);
    if(nbins_estimated >= 20000){
        throw runtime_error("LuminosityHists misconfiguration: would take more than 20000 bins. Please increase lumi_per_bin");
    }
    upper_binborders.reserve(nbins_estimated);

    double ilumi_current_bin = 0.0;
    for(const auto & rl : rl2lumi){
       ilumi_current_bin += rl.second;
       if(ilumi_current_bin >= lumi_per_bin){
          upper_binborders.push_back(rl.first);
            ilumi_current_bin = ilumi_current_bin - lumi_per_bin;
        }
    }
    int nbins = upper_binborders.size() + 1; // add one for the partial bin
    hlumi = book<TH1D>("luminosity", "Events over time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin);

    EtaProbeLumi = book<TH2D>("EtaProbevsLumi", "Probe jet eta vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin, (sizeof(eta_bins) / sizeof(eta_bins[0]) - 1), eta_bins);

    EtaProbeLumi_bx0bxMinus1 = book<TH2D>("EtaProbevsLumi_bx0bxMinus1", "Probe jet eta vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin, (sizeof(eta_bins) / sizeof(eta_bins[0]) - 1), eta_bins);
    EtaProbeLumi_bxMinus1 = book<TH2D>("EtaProbevsLumi_bxMinus1", "Probe jet eta vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin, (sizeof(eta_bins) / sizeof(eta_bins[0]) - 1), eta_bins);
    EtaProbeLumi_bxMinus1_all = book<TH2D>("EtaProbevsLumi_bxMinus1_all", "Probe jet eta vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin, (sizeof(eta_bins) / sizeof(eta_bins[0]) - 1), eta_bins);
    EtaProbeLumi_bx0 = book<TH2D>("EtaProbevsLumi_bx0", "Probe jet eta vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin, (sizeof(eta_bins) / sizeof(eta_bins[0]) - 1), eta_bins);
    dRProbeLumi_bx0 = book<TH2D>("dRProbevsLumi_bx0", "#DeltaR(Probe jet, L1J BX=0) vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin,20,0.0,1.0);
    dRProbeLumi_bxMinus1 = book<TH2D>("dRProbevsLumi_bxMinus1", "#DeltaR(Probe jet, L1J BX=-1) vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin,20,0.0,1.0);
    dRProbeLumi_bxMinus1_all = book<TH2D>("dRProbevsLumi_bxMinus1_all", "#DeltaR(Probe jet, L1J BX=-1) vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin,20,0.0,1.0);

    dPtProbeLumi_bx0 = book<TH2D>("dPtProbevsLumi_bx0", "L1J BX=0 pt/Probe jet pt vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin,100,0.0,10.0);
    dPtProbeLumi_bxMinus1 = book<TH2D>("dPtProbevsLumi_bxMinus1", "L1J BX=-1 pt/Probe jet vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin,100,0.0,10.0);
    dPtProbeLumi_bxMinus1_all = book<TH2D>("dPtProbevsLumi_bxMinus1_all", "L1J BX=-1 pt/Probe jet vs time divided in equal lumi-size bins", nbins, 0, ( int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin,100,0.0,10.0);


    /*  TString name1 = "hist_data_A_";
  TString name2 = "hist_data_B_";
  TString name3 = "hist_data_Npv_";

  bool eta_cut_bool;
  TString pt_range_j;
  TString pt_range_j1;

  for(int i=0;i<n_eta-1;i++){
      if(fabs(eta_bins[i])<fabs(eta_bins[i+1])){
	eta_cut_bool = fabs(eta_bins[i])>2.8;
      }
      else {
	eta_cut_bool = fabs(eta_bins[i+1])>2.8;
      }

    for(int j=0;j<(eta_cut_bool ? n_pt_HF-1 : n_pt-1 ) ; j++){
      pt_range_j  = (eta_cut_bool ? pt_range_HF[j] : pt_range[j]);
      pt_range_j1 = (eta_cut_bool ? pt_range_HF[j+1] : pt_range[j+1]);
      //      cout<<"eta_"+eta_range[i]+"_"+eta_range[i+1]+"_pT_"+pt_range_j+"_"+pt_range_j1<<endl;

     TString name = name1; name+="eta_"+eta_range[i]+"_"+eta_range[i+1]+"_pT_"+pt_range_j+"_"+pt_range_j1;
     hAsymLumi[i][j] = book<TH2D>(name, "Asymmetry per Lumi", nbins,0,(int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin,100,-1.2,1.2);
     name = name2; name+="eta_"+eta_range[i]+"_"+eta_range[i+1]+"_pT_"+pt_range_j+"_"+pt_range_j1;
     hBsymLumi[i][j] = book<TH2D>(name, "Bsymmetry per Lumi", nbins,0,(int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin,100,-1.2,1.2);
     name = name3; name+="eta_"+eta_range[i]+"_"+eta_range[i+1]+"_pT_"+pt_range_j+"_"+pt_range_j1;
     hNpvLumi[i][j] = book<TH2D>(name, "Npv per Lumi", nbins,0,(int(total_lumi / lumi_per_bin) + 1)*lumi_per_bin,100,0,100);

  }
  }
    */
}
    
void Lumi2016Hists::fill(const uhh2::Event & ev){
    if(!ev.isRealData) return;
    

    bool trigger_accepted = true;
    if (trigger_accepted) {
        run_lumi rl{ev.run, ev.luminosityBlock};
        auto it = upper_bound(upper_binborders.begin(), upper_binborders.end(), rl);
        int ibin = distance(upper_binborders.begin(), it); // can be upper_bounds.size() at most, which is nbins and thus Ok.
	hlumi->Fill(ibin*lumi_per_bin, ev.weight); // weight is usually 1.0 anyway, but who knows ...
	cout<<"ev.run "<<ev.run<<" ev.luminosityBlock "<<ev.luminosityBlock<<endl;
 //Calculate pt_ave
   sort_by_pt<Jet>(*ev.jets);
    Jet* jet1 = &ev.jets->at(0);// leading jet
    Jet* jet2 = &ev.jets->at(1);// sub-leading jet
    float jet1_pt = jet1->pt(); float jet2_pt = jet2->pt();

//###############################  Declare Probe and Barrel Jet  ###########################################

    Jet* jet_probe = jet1; Jet* jet_barrel = jet2;
    if ((fabs(jet1->eta())<1.3)&&(fabs(jet2->eta())<1.3)) {
      int ran = rand();
      int numb = ran % 2 + 1;
      if(numb==1){
	jet_probe = jet2;
	jet_barrel = jet1;
      }
      if(numb==2){
	jet_probe = jet1;
	jet_barrel = jet2;
      }
    } 
    else if ((fabs(jet1->eta())<1.3)||(fabs(jet2->eta())<1.3)){
      if(fabs(jet1->eta())<1.3){
	jet_probe = jet2;
	jet_barrel = jet1;
      }
      else{
	jet_probe = jet1;
	jet_barrel = jet2;
      }
    }
//##########################################################################################################
 
    float  probejet_pt = jet_probe->pt(); 
    float  barreljet_pt = jet_barrel->pt(); 
    float probejet_eta = jet_probe->eta(); 
    float  probejet_phi = jet_probe->phi(); 
     float barreljet_eta = jet_barrel->eta(); 
    float  barreljet_phi = jet_barrel->phi(); 
    float pt_ave = (jet1_pt + jet2_pt)/2.;
    float jet3_pt = 0; float jet3_ptRaw = 0; 
    if(ev.jets->size()>2){
      Jet* jet3 = &ev.jets->at(2);
      jet3_pt = jet3->pt();
     }
   float alpha = jet3_pt/pt_ave;
    
    float asymmetry = (probejet_pt - barreljet_pt)/(probejet_pt + barreljet_pt);
    TVector2 pt, met;
    met.Set(ev.met->pt() * cos(ev.met->phi()),ev.met->pt() * sin(ev.met->phi()));
    pt.Set(barreljet_pt * cos(barreljet_phi),barreljet_pt* sin(barreljet_phi));
    float mpf_r = 1 + (met.Px()*pt.Px() + met.Py()*pt.Py())/(pt.Px()*pt.Px() + pt.Py()*pt.Py());
    float B = (met.Px()*pt.Px() + met.Py()*pt.Py())/((probejet_pt + barreljet_pt) * sqrt(pt.Px()*pt.Px() + pt.Py()*pt.Py())); //vec_MET*vec_ptbarr/(2ptave*ptbarr)

    bool eta_cut_bool;
    double pt_bin_i;
    double pt_bin_i1;

    if(alpha>0.3) return;
    /*  for(int j=0; j<n_eta-1; j++){
      if(probejet_eta > eta_bins[j+1] || probejet_eta < eta_bins[j]) continue;
      
      if(fabs(eta_bins[j])<fabs(eta_bins[j+1])){
	eta_cut_bool = fabs(eta_bins[j])>2.8;
      }
      else {
	eta_cut_bool = fabs(eta_bins[j+1])>2.8;
      }
    
      for(int i=0; i< (eta_cut_bool ? n_pt_HF-1 : n_pt-1) ; i++){
	pt_bin_i  = (eta_cut_bool ? pt_bin_HF[i] : pt_bins[i]);
	pt_bin_i1 = (eta_cut_bool ? pt_bin_HF[i+1] : pt_bins[i+1]);
	if(pt_ave>pt_bin_i1 || pt_ave<pt_bin_i) continue;
	hAsymLumi[j][i]->Fill(ibin*lumi_per_bin,asymmetry,ev.weight);
	hBsymLumi[j][i]->Fill(ibin*lumi_per_bin, B, ev.weight);
	hNpvLumi[j][i]->Fill(ibin*lumi_per_bin, ev.pvs->size(), ev.weight);
      }
    }
*/
    cout<<"ibin*lumi_per_bin = "<<ibin*lumi_per_bin<<endl;
    EtaProbeLumi->Fill(ibin*lumi_per_bin, probejet_eta, ev.weight);
    //run matching between probe jet and L1Jet seeds
    double dR_l1j_jetProbe_min = 0.9;
    int l1j_jetProbe_close = -1;
    double dR_l1jBX0_jetProbe_min = 0.9;
    int l1jBX0_jetProbe_close = -1;
    double dR_l1jBXm1_jetProbe_min = 0.9;
    int l1jBXm1_jetProbe_close = -1;
    double dR_l1jBXp1_jetProbe_min = 0.9;         
    int l1jBXp1_jetProbe_close = -1;

    int l1j_count = 0;
    for(auto& L1J : *ev.L1J_seeds){
      int bx_l1j = L1J.bx();
      double dR_l1j_jetProbe_ = uhh2::deltaR(L1J,*jet_probe);
      //      std::cout<<"BX = "<<bx_l1j<<" dR_l1j_jetProbe_ = "<<dR_l1j_jetProbe_<<std::endl; 
      if(dR_l1j_jetProbe_< dR_l1j_jetProbe_min){
	dR_l1j_jetProbe_min = dR_l1j_jetProbe_;
	l1j_jetProbe_close = l1j_count;
      }
      //dR for different BX                                                                                                                                           
      int l1jet_bx = bx_l1j;
      if(l1jet_bx==-1){                                                                                                                                               
	if(dR_l1j_jetProbe_< dR_l1jBXm1_jetProbe_min){                                                                                                         
	  dR_l1jBXm1_jetProbe_min = dR_l1j_jetProbe_;                                                                                                          
	  l1jBXm1_jetProbe_close = l1j_count;                                                                                                                     
	}                                                                                                                                                            
      }                                                                                                                                              
      if(l1jet_bx==+1){                                                                                                              
        if(dR_l1j_jetProbe_< dR_l1jBXp1_jetProbe_min){
          dR_l1jBXp1_jetProbe_min = dR_l1j_jetProbe_;
          l1jBXp1_jetProbe_close = l1j_count;
        }
      }                                                                                                                                                        
      if(l1jet_bx==0){
        if(dR_l1j_jetProbe_< dR_l1jBX0_jetProbe_min){
          dR_l1jBX0_jetProbe_min = dR_l1j_jetProbe_;
          l1jBX0_jetProbe_close = l1j_count;
        }
      }
    l1j_count++;
    }

    if(l1j_jetProbe_close>-1){//fill hist for L1J seed closest to jetProbe
      //      cout<<"dR_l1jBX0_jetProbe_min = "<<dR_l1jBX0_jetProbe_min<<" dR_l1jBXm1_jetProbe_min = "<<dR_l1jBXm1_jetProbe_min<<endl;
      //      std::cout<<"BX = "<<bx_l1j<<" dR_l1j_jetProbe_ = "<<dR_l1j_jetProbe_<<std::endl; 
      //      auto& L1J = ev.L1J_seeds->at(l1j_jetProbe_close);
      //      int bx = L1J.bx();
      //1) probe jet matched to L1Jet with BX=0
      if(dR_l1jBX0_jetProbe_min<0.8 && dR_l1jBXm1_jetProbe_min>0.8){
	EtaProbeLumi_bx0->Fill(ibin*lumi_per_bin, probejet_eta, ev.weight);
	dRProbeLumi_bx0->Fill(ibin*lumi_per_bin, dR_l1jBX0_jetProbe_min, ev.weight);
	dPtProbeLumi_bx0->Fill(ibin*lumi_per_bin, (ev.L1J_seeds->at(l1jBX0_jetProbe_close)).pt()/jet_probe->pt(), ev.weight);
      }
      //2) probe jet matched to L1Jet with BX=-1
      if(dR_l1jBXm1_jetProbe_min<0.8 && dR_l1jBX0_jetProbe_min>0.8){
	EtaProbeLumi_bxMinus1->Fill(ibin*lumi_per_bin, probejet_eta, ev.weight);
	dRProbeLumi_bxMinus1->Fill(ibin*lumi_per_bin, dR_l1jBXm1_jetProbe_min, ev.weight);
	dPtProbeLumi_bxMinus1->Fill(ibin*lumi_per_bin, (ev.L1J_seeds->at(l1jBXm1_jetProbe_close)).pt()/jet_probe->pt(), ev.weight);
      }
      //3) probe jet matched to L1Jet with BX=0 and L1Jet with BX=-1
      if(dR_l1jBX0_jetProbe_min<0.8 && dR_l1jBXm1_jetProbe_min<0.8){
	EtaProbeLumi_bx0bxMinus1->Fill(ibin*lumi_per_bin, probejet_eta, ev.weight);
	dRProbeLumi_bx0->Fill(ibin*lumi_per_bin, dR_l1jBX0_jetProbe_min, ev.weight);
	dRProbeLumi_bxMinus1->Fill(ibin*lumi_per_bin, dR_l1jBXm1_jetProbe_min, ev.weight);
	dPtProbeLumi_bx0->Fill(ibin*lumi_per_bin, (ev.L1J_seeds->at(l1jBX0_jetProbe_close)).pt()/jet_probe->pt(), ev.weight);
	dPtProbeLumi_bxMinus1->Fill(ibin*lumi_per_bin, (ev.L1J_seeds->at(l1jBXm1_jetProbe_close)).pt()/jet_probe->pt(), ev.weight);
      }
      //4 probe jet matched to L1Jet with BX=-1, BX=0 might be close too, but might be far away
      if(dR_l1jBXm1_jetProbe_min<0.8){
	EtaProbeLumi_bxMinus1_all->Fill(ibin*lumi_per_bin, probejet_eta, ev.weight);
	dRProbeLumi_bxMinus1_all->Fill(ibin*lumi_per_bin, dR_l1jBXm1_jetProbe_min, ev.weight);
	dPtProbeLumi_bxMinus1_all->Fill(ibin*lumi_per_bin, (ev.L1J_seeds->at(l1jBXm1_jetProbe_close)).pt()/jet_probe->pt(), ev.weight);
      }

    }
    }

}
