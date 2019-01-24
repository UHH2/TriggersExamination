#include "UHH2/TriggersExamination/include/TriggerStudiesHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

TriggerStudiesHists::TriggerStudiesHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
  // jets
  book<TH1F>("N_jets", "N_{jets};N_{jets}", 20, 0, 20);  
  book<TH1F>("eta_jet1", "#eta^{jet 1}; #eta^{jet 1}; ", 50, -5.2, 5.2);
  book<TH1F>("eta_jet2", "#eta^{jet 2}; #eta^{jet 2}; ", 50, -5.2, 5.2);
  book<TH1F>("eta_jet3", "#eta^{jet 3}; #eta^{jet 3}; ", 50, -5.2, 5.2);
  book<TH1F>("eta_jet4", "#eta^{jet 4}; #eta^{jet 4}", 50, -5.2, 5.2);

  book<TH1F>("pt_jet1", "pt^{jet 1};pt^{jet 1}, GeV", 100, 0, 1000);
  book<TH1F>("pt_jet2", "pt^{jet 2};pt^{jet 2}, GeV", 100, 0, 1000);
  book<TH1F>("pt_jet3", "pt^{jet 3};pt^{jet 3}, GeV", 100, 0, 1000);
  book<TH1F>("pt_jet4", "pt^{jet 4};pt^{jet 4}, GeV", 100, 0, 1000);
  book<TH1F>("pt_jet_ave", "pt^{jet ave}, GeV", 100, 0, 1000);

  // primary vertices
  book<TH1F>("N_pv", "N^{PV};N^{PV}", 50, 0, 50);

  //L1EG seed
  book<TH1I>("L1EG_BX", "L1EG_BX; L1EG BX; Counts", 5, -2, 2);
  book<TH1F>("L1EG_Pt_bxMinus1", "L1EG_Pt_bxMinus1; L1EG pt [BX=-1]; Counts", 100, 0, 1000);//L1EG pt for L1EG in BX=-1
  book<TH1F>("L1EG_Pt_bxPlus1", "L1EG_Pt_bxPlus1; L1EG pt [BX=+1]; Counts", 100, 0, 1000);//L1EG pt for L1EG in BX=+1
  book<TH1F>("L1EG_Pt_bx0", "L1EG_Pt_bx0; L1EG pt [BX=0]; Counts", 100, 0, 1000);//L1EG pt for L1EG in BX=0
  book<TH1F>("L1EG_eta_bxMinus1", "L1EG_eta_bxMinus1; L1EG #eta [BX=-1]; Counts", 50, -5.2, 5.2);
  book<TH1F>("L1EG_eta_bxPlus1", "L1EG_eta_bxPlus1; L1EG #eta [BX=+1]; Counts", 50, -5.2, 5.2);
  book<TH1F>("L1EG_eta_bx0", "L1EG_eta_bx0; L1EG #eta [BX=0]; Counts", 50, -5.2, 5.2);
  book<TH1F>("L1EG_phi_bxMinus1", "L1EG_phi_bxMinus1; L1EG #phi [BX=-1]; Counts", 60, -3.15, 3.15);
  book<TH1F>("L1EG_phi_bxPlus1", "L1EG_phi_bxPlus1; L1EG #phi [BX=+1]; Counts", 60, -3.15, 3.15);
  book<TH1F>("L1EG_phi_bx0", "L1EG_phi_bx0; L1EG #phi [BX=0]; Counts", 60, -3.15, 3.15);

  book<TH1F>("L1EG_dRjet1_bxMinus1", "L1EG_dRjet1_bxMinus1; dR(L1EG, jet1) [BX=-1]; Counts", 100, 0, 10.);//dR between L1EG and jet1 for L1EG in BX=-1
  book<TH1F>("L1EG_dRjet1_bxPlus1", "L1EG_dRjet1_bxPlus1;  dR(L1EG, jet1) [BX=+1]; Counts", 100, 0, 10.);//dR between L1EG and jet1 for L1EG in BX=+1
  book<TH1F>("L1EG_dRjet1_bx0", "L1EG_dRjet1_bx0;  dR(L1EG, jet1) [BX=0]; Counts", 100, 0, 10.);//dR between L1EG and jet1 for L1EG in BX=0
  book<TH1F>("L1EG_dRjet2_bxMinus1", "L1EG_dRjet2_bxMinus1;  dR(L1EG, jet2) [BX=-1]; Counts", 100, 0, 10.);
  book<TH1F>("L1EG_dRjet2_bxPlus1", "L1EG_dRjet2_bxPlus1;  dR(L1EG, jet2) [BX=+1]; Counts", 100, 0, 10.);
  book<TH1F>("L1EG_dRjet2_bx0", "L1EG_dRjet2_bx0;  dR(L1EG, jet2) [BX=0]; Counts", 100, 0, 10.);

  book<TH1F>("L1EG_drJet1Min_Pt_bxMinus1", "L1EG_drJet1Min_Pt_bxMinus1; L1EG pt [BX=-1, #Delta^{min}R(jet1, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet1
  book<TH1F>("L1EG_drJet1Min_Pt_bxPlus1", "L1EG_drJet1Min_Pt_bxPlus1; L1EG pt [BX=+1, #Delta^{min}R(jet1, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet1
  book<TH1F>("L1EG_drJet1Min_Pt_bx0", "L1EG_drJet1Min_Pt_bx0; L1EG pt [BX=0, #Delta^{min}R(jet1, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet1

  book<TH1F>("L1EG_drJet2Min_Pt_bxMinus1", "L1EG_drJet2Min_Pt_bxMinus1; L1EG pt [BX=-1, #Delta^{min}R(jet2, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet2
  book<TH1F>("L1EG_drJet2Min_Pt_bxPlus1", "L1EG_drJet2Min_Pt_bxPlus1; L1EG pt [BX=+1, #Delta^{min}R(jet2, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet2
  book<TH1F>("L1EG_drJet2Min_Pt_bx0", "L1EG_drJet2Min_Pt_bx0; L1EG pt [BX=0, #Delta^{min}R(jet2, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet2

  book<TH1F>("L1EG_drJet1Min_Ptave_bxMinus1", "L1EG_drJet1Min_Ptave_bxMinus1; pt_{ave} [BX=-1, #Delta^{min}R(jet1, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet1
  book<TH1F>("L1EG_drJet1Min_Ptave_bxPlus1", "L1EG_drJet1Min_Ptave_bxPlus1; pt_{ave} [BX=+1, #Delta^{min}R(jet1, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet1
  book<TH1F>("L1EG_drJet1Min_Ptave_bx0", "L1EG_drJet1Min_Ptave_bx0; pt_{ave} [BX=0, #Delta^{min}R(jet1, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet1

  book<TH1F>("L1EG_drJet2Min_Ptave_bxMinus1", "L1EG_drJet2Min_Ptave_bxMinus1; pt_{ave} [BX=-1, #Delta^{min}R(jet2, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet2
  book<TH1F>("L1EG_drJet2Min_Ptave_bxPlus1", "L1EG_drJet2Min_Ptave_bxPlus1; pt_{ave} [BX=+1, #Delta^{min}R(jet2, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet2
  book<TH1F>("L1EG_drJet2Min_Ptave_bx0", "L1EG_drJet2Min_Ptave_bx0; pt_{ave} [BX=0, #Delta^{min}R(jet2, L1EG)]; Counts", 100, 0, 1000);//closest seed to jet2

  book<TH1F>("L1EG_drJet1Min_dR_bxMinus1", "L1EG_drJet1Min_dR_bxMinus1; #Delta R(jet1, L1EG)] [BX=-1, #Delta^{min}R(jet1, L1EG)]; Counts", 100, 0, 1.);//closest seed to jet1
  book<TH1F>("L1EG_drJet1Min_dR_bxPlus1", "L1EG_drJet1Min_dR_bxPlus1; #Delta R(jet1, L1EG)] [BX=+1, #Delta^{min}R(jet1, L1EG)]; Counts", 100, 0, 1.);//closest seed to jet1
  book<TH1F>("L1EG_drJet1Min_dR_bx0", "L1EG_drJet1Min_dR_bx0; #Delta R(jet1, L1EG)] [BX=0, #Delta^{min}R(jet1, L1EG)]; Counts", 100, 0, 1.);//closest seed to jet1

  book<TH1F>("L1EG_drJet2Min_dR_bxMinus1", "L1EG_drJet2Min_dR_bxMinus1; #Delta R(jet2, L1EG)] [BX=-1, #Delta^{min}R(jet2, L1EG)]; Counts", 100, 0, 1.);//closest seed to jet2
  book<TH1F>("L1EG_drJet2Min_dR_bxPlus1", "L1EG_drJet2Min_dR_bxPlus1; #Delta R(jet2, L1EG)] [BX=+1, #Delta^{min}R(jet2, L1EG)]; Counts", 100, 0, 1.);//closest seed to jet2
  book<TH1F>("L1EG_drJet2Min_dR_bx0", "L1EG_drJet2Min_dR_bx0; #Delta R(jet2, L1EG)] [BX=0, #Delta^{min}R(jet2, L1EG)]; Counts", 100, 0, 1.);//closest seed to jet2


//L1J seed
 book<TH1I>("L1J_BX", "L1J_BX; L1Jet BX; Counts", 5, -2, 2);
  book<TH1F>("L1J_Pt_bxMinus1", "L1J_Pt_bxMinus1; L1Jet pt [BX=-1]; Counts", 100, 0, 1000);//L1Jet pt for L1Jet in BX=-1
  book<TH1F>("L1J_Pt_bxPlus1", "L1J_Pt_bxPlus1; L1Jet pt [BX=+1]; Counts", 100, 0, 1000);//L1Jet pt for L1Jet in BX=+1
  book<TH1F>("L1J_Pt_bx0", "L1J_Pt_bx0; L1Jet pt [BX=0]; Counts", 100, 0, 1000);//L1Jet pt for L1Jet in BX=0
  book<TH1F>("L1J_eta_bxMinus1", "L1J_eta_bxMinus1; L1Jet #eta [BX=-1]; Counts", 50, -5.2, 5.2);
  book<TH1F>("L1J_eta_bxPlus1", "L1J_eta_bxPlus1; L1Jet #eta [BX=+1]; Counts", 50, -5.2, 5.2);
  book<TH1F>("L1J_eta_bx0", "L1J_eta_bx0; L1Jet #eta [BX=0]; Counts", 50, -5.2, 5.2);
  book<TH1F>("L1J_phi_bxMinus1", "L1J_phi_bxMinus1; L1Jet #phi [BX=-1]; Counts", 60, -3.15, 3.15);
  book<TH1F>("L1J_phi_bxPlus1", "L1J_phi_bxPlus1; L1Jet #phi [BX=+1]; Counts", 60, -3.15, 3.15);
  book<TH1F>("L1J_phi_bx0", "L1J_phi_bx0; L1Jet #phi [BX=0]; Counts", 60, -3.15, 3.15);

  book<TH1F>("L1J_dRjet1_bxMinus1", "L1J_dRjet1_bxMinus1; dR(L1J, jet1) [BX=-1]; Counts", 100, 0, 10.);//dR between L1Jet and jet1 for L1Jet in BX=-1
  book<TH1F>("L1J_dRjet1_bxPlus1", "L1J_dRjet1_bxPlus1;  dR(L1J, jet1) [BX=+1]; Counts", 100, 0, 10.);//dR between L1Jet and jet1 for L1Jet in BX=+1
  book<TH1F>("L1J_dRjet1_bx0", "L1J_dRjet1_bx0;  dR(L1J, jet1) [BX=0]; Counts", 100, 0, 10.);//dR between L1Jet and jet1 for L1Jet in BX=0
  book<TH1F>("L1J_dRjet2_bxMinus1", "L1J_dRjet2_bxMinus1;  dR(L1J, jet2) [BX=-1]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjet2_bxPlus1", "L1J_dRjet2_bxPlus1;  dR(L1J, jet2) [BX=+1]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjet2_bx0", "L1J_dRjet2_bx0;  dR(L1J, jet2) [BX=0]; Counts", 100, 0, 10.);

  book<TH1F>("L1J_drJet1Min_Pt_bxMinus1", "L1J_drJet1Min_Pt_bxMinus1; L1Jet pt [BX=-1, #Delta^{min}R(jet1, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet1
  book<TH1F>("L1J_drJet1Min_Pt_bxPlus1", "L1J_drJet1Min_Pt_bxPlus1; L1Jet pt [BX=+1, #Delta^{min}R(jet1, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet1
  book<TH1F>("L1J_drJet1Min_Pt_bx0", "L1J_drJet1Min_Pt_bx0; L1Jet pt [BX=0, #Delta^{min}R(jet1, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet1

  book<TH1F>("L1J_drJet2Min_Pt_bxMinus1", "L1J_drJet2Min_Pt_bxMinus1; L1Jet pt [BX=-1, #Delta^{min}R(jet2, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet2
  book<TH1F>("L1J_drJet2Min_Pt_bxPlus1", "L1J_drJet2Min_Pt_bxPlus1; L1Jet pt [BX=+1, #Delta^{min}R(jet2, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet2
  book<TH1F>("L1J_drJet2Min_Pt_bx0", "L1J_drJet2Min_Pt_bx0; L1Jet pt [BX=0, #Delta^{min}R(jet2, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet2

  book<TH1F>("L1J_drJet1Min_Ptave_bxMinus1", "L1J_drJet1Min_Ptave_bxMinus1; pt_{ave} [BX=-1, #Delta^{min}R(jet1, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet1
  book<TH1F>("L1J_drJet1Min_Ptave_bxPlus1", "L1J_drJet1Min_Ptave_bxPlus1; pt_{ave} [BX=+1, #Delta^{min}R(jet1, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet1
  book<TH1F>("L1J_drJet1Min_Ptave_bx0", "L1J_drJet1Min_Ptave_bx0; pt_{ave} [BX=0, #Delta^{min}R(jet1, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet1

  book<TH1F>("L1J_drJet2Min_Ptave_bxMinus1", "L1J_drJet2Min_Ptave_bxMinus1; pt_{ave} [BX=-1, #Delta^{min}R(jet2, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet2
  book<TH1F>("L1J_drJet2Min_Ptave_bxPlus1", "L1J_drJet2Min_Ptave_bxPlus1; pt_{ave} [BX=+1, #Delta^{min}R(jet2, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet2
  book<TH1F>("L1J_drJet2Min_Ptave_bx0", "L1J_drJet2Min_Ptave_bx0; pt_{ave} [BX=0, #Delta^{min}R(jet2, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jet2

  book<TH1F>("L1J_drJet1Min_dR_bxMinus1", "L1J_drJet1Min_dR_bxMinus1; #Delta R(jet1, L1Jet)] [BX=-1, #Delta^{min}R(jet1, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jet1
  book<TH1F>("L1J_drJet1Min_dR_bxPlus1", "L1J_drJet1Min_dR_bxPlus1; #Delta R(jet1, L1Jet)] [BX=+1, #Delta^{min}R(jet1, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jet1
  book<TH1F>("L1J_drJet1Min_dR_bx0", "L1J_drJet1Min_dR_bx0; #Delta R(jet1, L1Jet)] [BX=0, #Delta^{min}R(jet1, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jet1

  book<TH1F>("L1J_drJet2Min_dR_bxMinus1", "L1J_drJet2Min_dR_bxMinus1; #Delta R(jet2, L1Jet)] [BX=-1, #Delta^{min}R(jet2, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jet2
  book<TH1F>("L1J_drJet2Min_dR_bxPlus1", "L1J_drJet2Min_dR_bxPlus1; #Delta R(jet2, L1Jet)] [BX=+1, #Delta^{min}R(jet2, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jet2
  book<TH1F>("L1J_drJet2Min_dR_bx0", "L1J_drJet2Min_dR_bx0; #Delta R(jet2, L1Jet)] [BX=0, #Delta^{min}R(jet2, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jet2


}


void TriggerStudiesHists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;
  
  std::vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  hist("N_jets")->Fill(Njets, weight);
  
  if(Njets>=1){
    hist("eta_jet1")->Fill(jets->at(0).eta(), weight);
    hist("pt_jet1")->Fill(jets->at(0).pt(), weight);
  }
  if(Njets>=2){
    hist("eta_jet2")->Fill(jets->at(1).eta(), weight);
    hist("pt_jet2")->Fill(jets->at(1).pt(), weight);
    hist("pt_jet_ave")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
  }
  if(Njets>=3){
    hist("eta_jet3")->Fill(jets->at(2).eta(), weight);
    hist("pt_jet3")->Fill(jets->at(2).pt(), weight);
  }
  if(Njets>=4){
    hist("eta_jet4")->Fill(jets->at(3).eta(), weight);
    hist("pt_jet4")->Fill(jets->at(3).pt(), weight);
  }

  int Npvs = event.pvs->size();
  hist("N_pv")->Fill(Npvs, weight);


  //  cout<<"L1EG_seeds->size() = "<<event.L1EG_seeds->size()<<endl;
  double dR_l1eg_jet1_min = 0.4;
  int l1eg_jet1_close = -1;
  double dR_l1eg_jet2_min = 0.4;
  int l1eg_jet2_close = -1;
  int l1eg_count = 0;
  for(auto& L1EG : *event.L1EG_seeds){
    int bx_l1eg = L1EG.bx();
    hist("L1EG_BX")->Fill(bx_l1eg, weight);
    if(bx_l1eg == -1){
      hist("L1EG_Pt_bxMinus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_eta_bxMinus1")->Fill(L1EG.eta(), weight);
      hist("L1EG_phi_bxMinus1")->Fill(L1EG.phi(), weight);
      if(Njets>=1) hist("L1EG_dRjet1_bxMinus1")->Fill(uhh2::deltaR(L1EG,jets->at(0)), weight);
      if(Njets>=2) hist("L1EG_dRjet2_bxMinus1")->Fill(uhh2::deltaR(L1EG,jets->at(1)), weight);
    }
    if(bx_l1eg == +1){
      hist("L1EG_Pt_bxPlus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_eta_bxPlus1")->Fill(L1EG.eta(), weight);
      hist("L1EG_phi_bxPlus1")->Fill(L1EG.phi(), weight);
      if(Njets>=1) hist("L1EG_dRjet1_bxPlus1")->Fill(uhh2::deltaR(L1EG,jets->at(0)), weight);
      if(Njets>=2) hist("L1EG_dRjet2_bxPlus1")->Fill(uhh2::deltaR(L1EG,jets->at(1)), weight);
    }
    if(bx_l1eg == 0){
      hist("L1EG_Pt_bx0")->Fill(L1EG.pt(), weight);
      hist("L1EG_eta_bx0")->Fill(L1EG.eta(), weight);
      hist("L1EG_phi_bx0")->Fill(L1EG.phi(), weight);
      if(Njets>=1) hist("L1EG_dRjet1_bx0")->Fill(uhh2::deltaR(L1EG,jets->at(0)), weight);
      if(Njets>=2) hist("L1EG_dRjet2_bx0")->Fill(uhh2::deltaR(L1EG,jets->at(1)), weight);
    }

    if(Njets>=1){
      double dR_l1eg_jet1_ = uhh2::deltaR(L1EG,jets->at(0));
      if(dR_l1eg_jet1_< dR_l1eg_jet1_min){
	dR_l1eg_jet1_min = dR_l1eg_jet1_;
	l1eg_jet1_close = l1eg_count;
      }
    }
    if(Njets>=2){
      double dR_l1eg_jet2_ = uhh2::deltaR(L1EG,jets->at(1));
      if(dR_l1eg_jet2_< dR_l1eg_jet2_min){
	dR_l1eg_jet2_min = dR_l1eg_jet2_;
	l1eg_jet2_close = l1eg_count;
      }
    }
    l1eg_count++;
  }
  if(l1eg_jet1_close>-1){//fill hist for L1EG seed closest to jet1
    auto& L1EG = event.L1EG_seeds->at(l1eg_jet1_close);
    int bx = L1EG.bx();
    if(bx == -1){ 
      hist("L1EG_drJet1Min_Pt_bxMinus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJet1Min_dR_bxMinus1")->Fill(uhh2::deltaR(L1EG,jets->at(0)), weight);
      if(Njets>=2) hist("L1EG_drJet1Min_Ptave_bxMinus1")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
    if(bx == +1){
      hist("L1EG_drJet1Min_Pt_bxPlus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJet1Min_dR_bxPlus1")->Fill(uhh2::deltaR(L1EG,jets->at(0)), weight);
      if(Njets>=2) hist("L1EG_drJet1Min_Ptave_bxPlus1")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
    if(bx == 0){
      hist("L1EG_drJet1Min_Pt_bx0")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJet1Min_dR_bx0")->Fill(uhh2::deltaR(L1EG,jets->at(0)), weight);
      if(Njets>=2) hist("L1EG_drJet1Min_Ptave_bx0")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
  }
  if(l1eg_jet2_close>-1){//fill hist for L1EG seed closest to jet2
    auto& L1EG = event.L1EG_seeds->at(l1eg_jet2_close);
    int bx = L1EG.bx();
    if(bx == -1){
      hist("L1EG_drJet2Min_Pt_bxMinus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJet2Min_dR_bxMinus1")->Fill(uhh2::deltaR(L1EG,jets->at(1)), weight);
      if(Njets>=2) hist("L1EG_drJet2Min_Ptave_bxMinus1")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
    if(bx == +1){
      hist("L1EG_drJet2Min_Pt_bxPlus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJet2Min_dR_bxPlus1")->Fill(uhh2::deltaR(L1EG,jets->at(1)), weight);
      if(Njets>=2) hist("L1EG_drJet2Min_Ptave_bxPlus1")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
    if(bx == 0){
      hist("L1EG_drJet2Min_Pt_bx0")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJet2Min_dR_bx0")->Fill(uhh2::deltaR(L1EG,jets->at(1)), weight);
      if(Njets>=2) hist("L1EG_drJet2Min_Ptave_bx0")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
  }

 //  cout<<"L1J_seeds->size() = "<<event.L1J_seeds->size()<<endl;
  double dR_l1j_jet1_min = 0.4;
  int l1j_jet1_close = -1;
  double dR_l1j_jet2_min = 0.4;
  int l1j_jet2_close = -1;
  int l1j_count = 0;
  for(auto& L1J : *event.L1J_seeds){
    int bx_l1j = L1J.bx();
    hist("L1J_BX")->Fill(bx_l1j, weight);
    if(bx_l1j == -1){
      hist("L1J_Pt_bxMinus1")->Fill(L1J.pt(), weight);
      hist("L1J_eta_bxMinus1")->Fill(L1J.eta(), weight);
      hist("L1J_phi_bxMinus1")->Fill(L1J.phi(), weight);
      if(Njets>=1) hist("L1J_dRjet1_bxMinus1")->Fill(uhh2::deltaR(L1J,jets->at(0)), weight);
      if(Njets>=2) hist("L1J_dRjet2_bxMinus1")->Fill(uhh2::deltaR(L1J,jets->at(1)), weight);
    }
    if(bx_l1j == +1){
      hist("L1J_Pt_bxPlus1")->Fill(L1J.pt(), weight);
      hist("L1J_eta_bxPlus1")->Fill(L1J.eta(), weight);
      hist("L1J_phi_bxPlus1")->Fill(L1J.phi(), weight);
      if(Njets>=1) hist("L1J_dRjet1_bxPlus1")->Fill(uhh2::deltaR(L1J,jets->at(0)), weight);
      if(Njets>=2) hist("L1J_dRjet2_bxPlus1")->Fill(uhh2::deltaR(L1J,jets->at(1)), weight);
    }
    if(bx_l1j == 0){
      hist("L1J_Pt_bx0")->Fill(L1J.pt(), weight);
      hist("L1J_eta_bx0")->Fill(L1J.eta(), weight);
      hist("L1J_phi_bx0")->Fill(L1J.phi(), weight);
      if(Njets>=1) hist("L1J_dRjet1_bx0")->Fill(uhh2::deltaR(L1J,jets->at(0)), weight);
      if(Njets>=2) hist("L1J_dRjet2_bx0")->Fill(uhh2::deltaR(L1J,jets->at(1)), weight);
    }

    if(Njets>=1){
      double dR_l1j_jet1_ = uhh2::deltaR(L1J,jets->at(0));
      if(dR_l1j_jet1_< dR_l1j_jet1_min){
	dR_l1j_jet1_min = dR_l1j_jet1_;
	l1j_jet1_close = l1j_count;
      }
    }
    if(Njets>=2){
      double dR_l1j_jet2_ = uhh2::deltaR(L1J,jets->at(1));
      if(dR_l1j_jet2_< dR_l1j_jet2_min){
	dR_l1j_jet2_min = dR_l1j_jet2_;
	l1j_jet2_close = l1j_count;
      }
    }
    l1j_count++;
  }
  if(l1j_jet1_close>-1){//fill hist for L1J seed closest to jet1
    auto& L1J = event.L1J_seeds->at(l1j_jet1_close);
    int bx = L1J.bx();
    if(bx == -1){ 
      hist("L1J_drJet1Min_Pt_bxMinus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJet1Min_dR_bxMinus1")->Fill(uhh2::deltaR(L1J,jets->at(0)), weight);
      if(Njets>=2) hist("L1J_drJet1Min_Ptave_bxMinus1")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
    if(bx == +1){
      hist("L1J_drJet1Min_Pt_bxPlus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJet1Min_dR_bxPlus1")->Fill(uhh2::deltaR(L1J,jets->at(0)), weight);
      if(Njets>=2) hist("L1J_drJet1Min_Ptave_bxPlus1")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
    if(bx == 0){
      hist("L1J_drJet1Min_Pt_bx0")->Fill(L1J.pt(), weight);
      hist("L1J_drJet1Min_dR_bx0")->Fill(uhh2::deltaR(L1J,jets->at(0)), weight);
      if(Njets>=2) hist("L1J_drJet1Min_Ptave_bx0")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
  }
  if(l1j_jet2_close>-1){//fill hist for L1J seed closest to jet2
    auto& L1J = event.L1J_seeds->at(l1j_jet2_close);
    int bx = L1J.bx();
    if(bx == -1){
      hist("L1J_drJet2Min_Pt_bxMinus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJet2Min_dR_bxMinus1")->Fill(uhh2::deltaR(L1J,jets->at(1)), weight);
      if(Njets>=2) hist("L1J_drJet2Min_Ptave_bxMinus1")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
    if(bx == +1){
      hist("L1J_drJet2Min_Pt_bxPlus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJet2Min_dR_bxPlus1")->Fill(uhh2::deltaR(L1J,jets->at(1)), weight);
      if(Njets>=2) hist("L1J_drJet2Min_Ptave_bxPlus1")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
    if(bx == 0){
      hist("L1J_drJet2Min_Pt_bx0")->Fill(L1J.pt(), weight);
      hist("L1J_drJet2Min_dR_bx0")->Fill(uhh2::deltaR(L1J,jets->at(1)), weight);
      if(Njets>=2) hist("L1J_drJet2Min_Ptave_bx0")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);
    }
  }

 
}

TriggerStudiesHists::~TriggerStudiesHists(){}
