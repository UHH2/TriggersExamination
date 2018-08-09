#include "UHH2/TriggersExamination/include/TriggerStudiesHLTmatchL1Hists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

// TriggerStudiesHLTmatchL1Hists
TriggerStudiesHLTmatchL1Hists::TriggerStudiesHLTmatchL1Hists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here

//L1J seed
//  uhh2::GenericEvent::Handle<std::vector<FlavorParticle>> handle_triggers[15];
  handle_triggers[0]= ctx.declare_event_input< vector< FlavorParticle > >(  "triggerObjects_hltDiPFJetAve40" );
  handle_triggers[1]= ctx.declare_event_input< vector< FlavorParticle > >(  "triggerObjects_hltDiPFJetAve60" );
  handle_triggers[2]= ctx.declare_event_input< vector< FlavorParticle > >(  "triggerObjects_hltDiPFJetAve80" );
  handle_triggers[3] = ctx.declare_event_input< vector< FlavorParticle > >("triggerObjects_hltDiPFJetAve140" );
  handle_triggers[4] = ctx.declare_event_input< vector< FlavorParticle > >("triggerObjects_hltDiPFJetAve200" );
  handle_triggers[5] = ctx.declare_event_input< vector< FlavorParticle > >("triggerObjects_hltDiPFJetAve260" );
  handle_triggers[6] = ctx.declare_event_input< vector< FlavorParticle > >("triggerObjects_hltDiPFJetAve320" );
  handle_triggers[7] = ctx.declare_event_input< vector< FlavorParticle > >("triggerObjects_hltDiPFJetAve400" );
  handle_triggers[8] = ctx.declare_event_input< vector< FlavorParticle > >("triggerObjects_hltDiPFJetAve500" );
  handle_triggers[9]= ctx.declare_event_input< vector< FlavorParticle > >(  "triggerObjects_hltDiPFJetAve60ForHFJEC" );
  handle_triggers[10]= ctx.declare_event_input< vector< FlavorParticle > >(  "triggerObjects_hltDiPFJetAve80ForHFJEC" );
  handle_triggers[11]= ctx.declare_event_input< vector< FlavorParticle > >(  "triggerObjects_hltDiPFJetAve100ForHFJEC" );
  handle_triggers[12] = ctx.declare_event_input< vector< FlavorParticle > >("triggerObjects_hltDiPFJetAve160ForHFJEC" );
  handle_triggers[13] = ctx.declare_event_input< vector< FlavorParticle > >("triggerObjects_hltDiPFJetAve220ForHFJEC" );
  handle_triggers[14] = ctx.declare_event_input< vector< FlavorParticle > >("triggerObjects_hltDiPFJetAve300ForHFJEC");

  book<TH1F>("L1J_dRjetHLTtag_bxMinus1", "L1J_dRjetHLTtag_bxMinus1; dR(L1Jet, jetHLTtag); Counts", 100, 0, 10.);//dR between L1Jet and jetHLTtag for L1Jet in BX=-1
  book<TH1F>("L1J_dRjetHLTtag_bxPlus1", "L1J_dRjetHLTtag_bxPlus1;  dR(L1Jet, jetHLTtag); Counts", 100, 0, 10.);//dR between L1Jet and jetHLTtag for L1Jet in BX=+1
  book<TH1F>("L1J_dRjetHLTtag_bx0", "L1J_dRjetHLTtag_bx0;  dR(L1Jet, jetHLTtag); Counts", 100, 0, 10.);//dR between L1Jet and jetHLTtag for L1Jet in BX=0
  book<TH1F>("L1J_dRjetHLTprobe_bxMinus1", "L1J_dRjetHLTprobe_bxMinus1;  dR(L1Jet, jetHLTprobe); Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjetHLTprobe_bxPlus1", "L1J_dRjetHLTprobe_bxPlus1;  dR(L1Jet, jetHLTprobe); Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjetHLTprobe_bx0", "L1J_dRjetHLTprobe_bx0;  dR(L1Jet, jetHLTprobe); Counts", 100, 0, 10.);

  book<TH1I>("L1J_drJetHLTtagMin_BX", "L1J_drJetHLTtagMin_BX; L1Jet BX [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 7,-3,3);//closest seed to jetHLTtag
  book<TH1I>("L1J_drJetHLTprobeMin_BX", "L1J_drJetHLTprobeMin_BX; L1Jet BX [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 7,-3,3);//closest seed to jetHLTprobe

  book<TH1F>("L1J_drJetHLTtagMin_Pt_bxMinus1", "L1J_drJetHLTtagMin_Pt_bxMinus1; L1Jet pt [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTtag
  book<TH1F>("L1J_drJetHLTtagMin_Pt_bxPlus1", "L1J_drJetHLTtagMin_Pt_bxPlus1; L1Jet pt [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTtag
  book<TH1F>("L1J_drJetHLTtagMin_Pt_bx0", "L1J_drJetHLTtagMin_Pt_bx0; L1Jet pt [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTtag

  book<TH1F>("L1J_drJetHLTprobeMin_Pt_bxMinus1", "L1J_drJetHLTprobeMin_Pt_bxMinus1; L1Jet pt [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_Pt_bxPlus1", "L1J_drJetHLTprobeMin_Pt_bxPlus1; L1Jet pt [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_Pt_bx0", "L1J_drJetHLTprobeMin_Pt_bx0; L1Jet pt [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTprobe

  book<TH1F>("L1J_drJetHLTtagMin_Ptave_bxMinus1", "L1J_drJetHLTtagMin_Ptave_bxMinus1; pt_{ave} [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTtag
  book<TH1F>("L1J_drJetHLTtagMin_Ptave_bxPlus1", "L1J_drJetHLTtagMin_Ptave_bxPlus1; pt_{ave} [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTtag
  book<TH1F>("L1J_drJetHLTtagMin_Ptave_bx0", "L1J_drJetHLTtagMin_Ptave_bx0; pt_{ave} [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTtag

  book<TH1F>("L1J_drJetHLTprobeMin_Ptave_bxMinus1", "L1J_drJetHLTprobeMin_Ptave_bxMinus1; pt_{ave} [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_Ptave_bxPlus1", "L1J_drJetHLTprobeMin_Ptave_bxPlus1; pt_{ave} [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_Ptave_bx0", "L1J_drJetHLTprobeMin_Ptave_bx0; pt_{ave} [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_EtaProbe", "L1J_drJetHLTprobeMin_EtaProbe; #eta^{HLT}_{probe} [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 40, -5.2, 5.2);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_EtaProbe_bxMinus1", "L1J_drJetHLTprobeMin_EtaProbe_bxMinus1; #eta^{HLT}_{probe} [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 40, -5.2, 5.2);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_EtaProbe_bxPlus1", "L1J_drJetHLTprobeMin_EtaProbe_bxPlus1; #eta^{HLT}_{probe} [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 40, -5.2, 5.2);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_EtaProbe_bx0", "L1J_drJetHLTprobeMin_EtaProbe_bx0; #eta^{HLT}_{probe} [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 40, -5.2, 5.2);//closest seed to jetHLTprobe

  book<TH1F>("L1J_drJetHLTtagMin_dR_bxMinus1", "L1J_drJetHLTtagMin_dR_bxMinus1; #Delta R(tag HLT jet, L1Jet) [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jetHLTtag
  book<TH1F>("L1J_drJetHLTtagMin_dR_bxPlus1", "L1J_drJetHLTtagMin_dR_bxPlus1; #Delta R(tag HLT jet, L1Jet) [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jetHLTtag
  book<TH1F>("L1J_drJetHLTtagMin_dR_bx0", "L1J_drJetHLTtagMin_dR_bx0; #Delta R(tag HLT jet, L1Jet) [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jetHLTtag
  book<TH1F>("L1J_drJetHLTtagMin_dR", "L1J_drJetHLTtagMin_dR; #Delta R(tag HLT jet, L1Jet) [#Delta^{min}R(tag HLT jet, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jetHLTtag

  book<TH1F>("L1J_drJetHLTprobeMin_dR_bxMinus1", "L1J_drJetHLTprobeMin_dR_bxMinus1; #Delta R(probe HLT jet, L1Jet) [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_dR_bxPlus1", "L1J_drJetHLTprobeMin_dR_bxPlus1; #Delta R(probe HLT jet, L1Jet) [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_dR_bx0", "L1J_drJetHLTprobeMin_dR_bx0; #Delta R(probe HLT jet, L1Jet) [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_dR", "L1J_drJetHLTprobeMin_dR; #Delta R(probe HLT jet, L1Jet) [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0, 1.);//closest seed to jetHLTprobe

  book<TH1F>("L1J_drJetHLTprobeMin_pBalAsymmetry", "L1J_drJetHLTprobeMin_pBalAsymmetry; A [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_pBalAsymmetry_bxMinus1", "L1J_drJetHLTprobeMin_pBalAsymmetry_bxMinus1; A [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_pBalAsymmetry_bxPlus1", "L1J_drJetHLTprobeMin_pBalAsymmetry_bxPlus1; A [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_pBalAsymmetry_bx0", "L1J_drJetHLTprobeMin_pBalAsymmetry_bx0; A [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_mpfAsymmetry", "L1J_drJetHLTprobeMin_mpfAsymmetry; B [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_mpfAsymmetry_bxMinus1", "L1J_drJetHLTprobeMin_mpfAsymmetry_bxMinus1; B [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_mpfAsymmetry_bxPlus1", "L1J_drJetHLTprobeMin_mpfAsymmetry_bxPlus1; B [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_mpfAsymmetry_bx0", "L1J_drJetHLTprobeMin_mpfAsymmetry_bx0; B [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetHLTprobe

  book<TH1F>("L1J_drJetHLTprobeMin_pBalResponse", "L1J_drJetHLTprobeMin_pBalResponse; ptBal response [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0,5.0);//cloL1J_drJetHLTprobeMinsest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_pBalResponse_bxMinus1", "L1J_drJetHLTprobeMin_pBalResponse_bxMinus1; ptBal response [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_pBalResponse_bxPlus1", "L1J_drJetHLTprobeMin_pBalResponse_bxPlus1; ptBal response [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_pBalResponse_bx0", "L1J_drJetHLTprobeMin_pBalResponse_bx0; ptBal response [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_mpfResponse", "L1J_drJetHLTprobeMin_mpfResponse; MPF response [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_mpfResponse_bxMinus1", "L1J_drJetHLTprobeMin_mpfResponse_bxMinus1; MPF response [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_mpfResponse_bxPlus1", "L1J_drJetHLTprobeMin_mpfResponse_bxPlus1; MPF response [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetHLTprobe
  book<TH1F>("L1J_drJetHLTprobeMin_mpfResponse_bx0", "L1J_drJetHLTprobeMin_mpfResponse_bx0; MPF response [#Delta^{min}R(probe HLT jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetHLTprobe

  book<TH2F>("L1J_drJetHLTprobeMin_ProbeEtaProbePhi", "L1J_drJetHLTprobeMin_ProbeEtaProbePhi; probe HLT jet #eta [#Delta^{min}R(probe HLT jet, L1J)]; probe HLT jet #phi [#Delta^{min}R(probe HLT jet, L1J)]; Counts", 20,-5.2,5.2, 20,-3.14,3.14);//closest seed to jetHLTprobe
  book<TH2F>("L1J_drJetHLTprobeMin_ProbeEtaProbePhi_bx0", "L1J_drJetHLTprobeMin_ProbeEtaProbePhi_bx0; probe HLT jet #eta [#Delta^{min}R(probe HLT jet, L1J)]; probe HLT jet #phi [#Delta^{min}R(probe HLT jet, L1J)]; Counts", 20,-5.2,5.2, 20,-3.14,3.14);//closest seed to jetHLTprobe
  book<TH2F>("L1J_drJetHLTprobeMin_ProbeEtaProbePhi_bxPlus1", "L1J_drJetHLTprobeMin_ProbeEtaProbePhi_bxPlus1; probe HLT jet #eta [#Delta^{min}R(probe HLT jet, L1J)]; probe HLT jet #phi [#Delta^{min}R(probe HLT jet, L1J)]; Counts", 20,-5.2,5.2, 20,-3.14,3.14);//closest seed to jetHLTprobe
  book<TH2F>("L1J_drJetHLTprobeMin_ProbeEtaProbePhi_bxMinus1", "L1J_drJetHLTprobeMin_ProbeEtaProbePhi_bxMinus1; probe HLT jet #eta [#Delta^{min}R(probe HLT jet, L1J)]; probe HLT jet #phi [#Delta^{min}R(probe HLT jet, L1J)]; Counts", 20,-5.2,5.2, 20,-3.14,3.14);//closest seed to jetHLTprobe

  book<TH2F>("L1J_drJetHLTprobeMin_dR0dRm1", "L1J_drJetHLTprobeMin_dR0dRm; #Delta R(probe HLT jet, L1Jet BX=0) [#Delta^{min}R(probe HLT jet, L1Jet)];#Delta R(probe HLT jet, L1Jet BX=-1) [#Delta^{min}R(probe HLT jet, L1Jet)]", 30, -0.1, 0.5, 30, -0.1, 0.5);//
  book<TH2F>("L1J_drJetHLTprobeMin_dR0dRp1", "L1J_drJetHLTprobeMin_dR0dRp; #Delta R(probe HLT jet, L1Jet BX=0) [#Delta^{min}R(probe HLT jet, L1Jet)];#Delta R(probe HLT jet, L1Jet BX=+1) [#Delta^{min}R(probe HLT jet, L1Jet)]", 30, -0.1, 0.5, 30, -0.1, 0.5);//
}

void TriggerStudiesHLTmatchL1Hists::set_tr_list(std::vector<bool> pass_list){
  for(unsigned int i=0; i<pass_list.size();i++)
    pass_trigger_list.push_back(pass_list[i]);
}      

//void TriggerStudiesHLTmatchL1Hists::fill(const Event & event, std::vector<bool> & pass_trigger_list){
void TriggerStudiesHLTmatchL1Hists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;
  //  sort_by_pt(*event.jets);
  //  std::vector<Jet>* jets = event.jets;
  int tr_ind=-1;
  for(int i=0;i<15;i++){
    if(pass_trigger_list[i]) tr_ind=i; 
  }
  std::vector<FlavorParticle> jets = event.get(handle_triggers[tr_ind]);//TEST
  int Njets = jets.size();
  if(Njets<2) return;

 //###############################  Declare Probe and Barrel Jet  ###########################################
  //    sort_by_pt<Jet>(*jets);
    FlavorParticle jet1 = jets.at(0);// leading jet
    FlavorParticle jet2 = jets.at(1);// sub-leading jet
    const float s_eta_barr = 1.3;
    FlavorParticle jet_probe = jet1; FlavorParticle jet_barrel = jet2;
    if ((fabs(jet1.eta())<s_eta_barr)&&(fabs(jet2.eta())<s_eta_barr)) {
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
    else if ((fabs(jet1.eta())<s_eta_barr)||(fabs(jet2.eta())<s_eta_barr)){
      if(fabs(jet1.eta())<s_eta_barr){
	jet_probe = jet2;
	jet_barrel = jet1;
      }
      else{
	jet_probe = jet1;
	jet_barrel = jet2;
      }
    }
    else if((fabs(jet1.eta())>s_eta_barr)&&(fabs(jet2.eta())>s_eta_barr)) return;//for L2Residuals one jet must be in the barrel part

    double probejet_pt = jet_probe.pt(); 
    double barreljet_pt = jet_barrel.pt();
    double barreljet_phi = jet_barrel.phi();
    float A_asymmetry = (probejet_pt - barreljet_pt)/(probejet_pt + barreljet_pt);
    float rel_r = (1+A_asymmetry)/(1-A_asymmetry);
    TVector2 pt, met;
    met.Set(event.met->pt() * cos(event.met->phi()),event.met->pt() * sin(event.met->phi()));
    pt.Set(barreljet_pt * cos(barreljet_phi),barreljet_pt* sin(barreljet_phi));
    float mpf_r = 1 + (met.Px()*pt.Px() + met.Py()*pt.Py())/(pt.Px()*pt.Px() + pt.Py()*pt.Py());
    float B_asymmetry = (met.Px()*pt.Px() + met.Py()*pt.Py())/((probejet_pt + barreljet_pt) * sqrt(pt.Px()*pt.Px() + pt.Py()*pt.Py())); //vec_MET*vec_ptbarr/(2ptave*ptbarr)
  

  //   hist("eta_jetHLTtag")->Fill(jet_barrel.eta(), weight);
  //   hist("pt_jetTag")->Fill(jet_barrel.pt(), weight);
  //   hist("eta_jetHLTprobe")->Fill(jet_probe.eta(), weight);
  //   hist("pt_jetHLTprobe")->Fill(jet_probe.pt(), weight);
  //   hist("pt_jet_ave")->Fill(0.5*(jets.at(1).pt()+jets.at(0).pt()), weight);

  // if(Njets>=3){
  //   //    float alpha = jet3_pt/pt_ave;
  //   hist("eta_jet3")->Fill(jets.at(2).eta(), weight);
  //   hist("pt_jet3")->Fill(jets.at(2).pt(), weight);
  // }
  
  // hist("pBalAsymmetry")->Fill(A_asymmetry,weight);
  // hist("mpfAsymmetry")->Fill(B_asymmetry,weight);
  // hist("pBalResponse")->Fill(rel_r,weight);
  // hist("mpfResponse")->Fill(mpf_r,weight);


  double dR_l1j_jetTag_min = 0.4;
  int l1j_jetTag_close = -1;
  double dR_l1j_jetHLTprobe_min = 0.4;
  int l1j_jetHLTprobe_close = -1;
  double dR_l1jBX0_jetHLTprobe_min = 0.4;
  int l1jBX0_jetHLTprobe_close = -1;
  double dR_l1jBXm1_jetHLTprobe_min = 0.4;
  int l1jBXm1_jetHLTprobe_close = -1;
  double dR_l1jBXp1_jetHLTprobe_min = 0.4;
  int l1jBXp1_jetHLTprobe_close = -1;


  int l1j_count = 0;
  for(auto& L1J : *event.L1J_seeds){
    int bx_l1j = L1J.bx();
  //   if(bx_l1j == -1){
  //     hist("L1J_dRjetTag_bxMinus1")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
  //     hist("L1J_dRjetHLTprobe_bxMinus1")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
     
  //   }
  //   if(bx_l1j == +1){
  //     hist("L1J_dRjetTag_bxPlus1")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
  //     hist("L1J_dRjetHLTprobe_bxPlus1")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
   

  //   }
  //   if(bx_l1j == 0){
  //     hist("L1J_dRjetTag_bx0")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
  //     hist("L1J_dRjetHLTprobe_bx0")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
  //   }

    if(Njets>=1){
      double dR_l1j_jetTag_ = uhh2::deltaR(L1J,jet_barrel);
      if(dR_l1j_jetTag_< dR_l1j_jetTag_min){
	dR_l1j_jetTag_min = dR_l1j_jetTag_;
	l1j_jetTag_close = l1j_count;
      }
    }
    if(Njets>=2){
      double dR_l1j_jetHLTprobe_ = uhh2::deltaR(L1J,jet_probe);
      if(dR_l1j_jetHLTprobe_< dR_l1j_jetHLTprobe_min){
	dR_l1j_jetHLTprobe_min = dR_l1j_jetHLTprobe_;
	l1j_jetHLTprobe_close = l1j_count;
      }
      //dR for different BX
      int l1jet_bx = event.L1J_seeds->at(l1j_count).bx();
	if(l1jet_bx<0){
	  if(dR_l1j_jetHLTprobe_< dR_l1jBXm1_jetHLTprobe_min){
	    dR_l1jBXm1_jetHLTprobe_min = dR_l1j_jetHLTprobe_;                                                                                                         
	    l1jBXm1_jetHLTprobe_close = l1j_count;  
	  }
	}
      if(l1jet_bx>0){
	if(dR_l1j_jetHLTprobe_< dR_l1jBXp1_jetHLTprobe_min){
	  dR_l1jBXp1_jetHLTprobe_min = dR_l1j_jetHLTprobe_;                                                                                                          
	  l1jBXp1_jetHLTprobe_close = l1j_count;  
	}
      }
      if(l1jet_bx==0){
	if(dR_l1j_jetHLTprobe_< dR_l1jBX0_jetHLTprobe_min){
	  dR_l1jBX0_jetHLTprobe_min = dR_l1j_jetHLTprobe_;                                                                                                          
	  l1jBX0_jetHLTprobe_close = l1j_count;  
	}
      }
    }
    l1j_count++;
  }
  if(l1j_jetTag_close>-1){//fill hist for L1J seed closest to jetTag
    auto& L1J = event.L1J_seeds->at(l1j_jetTag_close);
    int bx = L1J.bx();
    hist("L1J_drJetHLTtagMin_BX")->Fill(bx, weight);
    hist("L1J_drJetHLTtagMin_dR")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
    if(bx == -1){ 
      hist("L1J_drJetHLTtagMin_Pt_bxMinus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJetHLTtagMin_dR_bxMinus1")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
      hist("L1J_drJetHLTtagMin_Ptave_bxMinus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    }
    if(bx == +1){
      hist("L1J_drJetHLTtagMin_Pt_bxPlus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJetHLTtagMin_dR_bxPlus1")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
      hist("L1J_drJetHLTtagMin_Ptave_bxPlus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    }
    if(bx == 0){
      hist("L1J_drJetHLTtagMin_Pt_bx0")->Fill(L1J.pt(), weight);
      hist("L1J_drJetHLTtagMin_dR_bx0")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
      hist("L1J_drJetHLTtagMin_Ptave_bx0")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    }
  }
  if(l1j_jetHLTprobe_close>-1){//fill hist for L1J seed closest to jetHLTprobe
    auto& L1J = event.L1J_seeds->at(l1j_jetHLTprobe_close);
    hist("L1J_drJetHLTprobeMin_pBalAsymmetry")->Fill(A_asymmetry, weight);
    hist("L1J_drJetHLTprobeMin_mpfAsymmetry")->Fill(B_asymmetry, weight);
    hist("L1J_drJetHLTprobeMin_pBalResponse")->Fill(rel_r, weight);
    hist("L1J_drJetHLTprobeMin_mpfResponse")->Fill(mpf_r, weight);
    hist("L1J_drJetHLTprobeMin_EtaProbe")->Fill(jet_probe.eta(), weight);
    int bx = L1J.bx();
    hist("L1J_drJetHLTprobeMin_BX")->Fill(bx, weight);
    hist("L1J_drJetHLTprobeMin_dR")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
    ((TH2F*)hist("L1J_drJetHLTprobeMin_ProbeEtaProbePhi"))->Fill(jet_probe.eta(),jet_probe.phi(),weight);
    if(l1jBX0_jetHLTprobe_close>-1 && l1jBXm1_jetHLTprobe_close>-1){    
      auto& L1J_bx0 = event.L1J_seeds->at(l1jBX0_jetHLTprobe_close);
      auto& L1J_bxm1 = event.L1J_seeds->at(l1jBXm1_jetHLTprobe_close);
      // auto& L1J_bxp1 = event.L1J_seeds->at(l1jBXp1_jetHLTprobe_close);
      ((TH2F*)hist("L1J_drJetHLTprobeMin_dR0dRm1"))->Fill(uhh2::deltaR(L1J_bx0,jet_probe),uhh2::deltaR(L1J_bxm1,jet_probe), weight);
    }
    else{
      if(l1jBX0_jetHLTprobe_close<0 && l1jBXm1_jetHLTprobe_close>-1){
	auto& L1J_bxm1 = event.L1J_seeds->at(l1jBXm1_jetHLTprobe_close);
	((TH2F*)hist("L1J_drJetHLTprobeMin_dR0dRm1"))->Fill(0.0,uhh2::deltaR(L1J_bxm1,jet_probe), weight);
      }
      else{
	if(l1jBX0_jetHLTprobe_close>-1){
	  auto& L1J_bx0 = event.L1J_seeds->at(l1jBX0_jetHLTprobe_close);
	  ((TH2F*)hist("L1J_drJetHLTprobeMin_dR0dRm1"))->Fill(uhh2::deltaR(L1J_bx0,jet_probe),0.0, weight);
	}
      }
    }

    if(l1jBX0_jetHLTprobe_close>-1 && l1jBXp1_jetHLTprobe_close>-1){    
      auto& L1J_bx0 = event.L1J_seeds->at(l1jBX0_jetHLTprobe_close);
      auto& L1J_bxp1 = event.L1J_seeds->at(l1jBXp1_jetHLTprobe_close);
      // auto& L1J_bxp1 = event.L1J_seeds->at(l1jBXp1_jetHLTprobe_close);
      ((TH2F*)hist("L1J_drJetHLTprobeMin_dR0dRp1"))->Fill(uhh2::deltaR(L1J_bx0,jet_probe),uhh2::deltaR(L1J_bxp1,jet_probe), weight);
    }
    else{
      if(l1jBX0_jetHLTprobe_close<0 && l1jBXp1_jetHLTprobe_close>-1){
	auto& L1J_bxp1 = event.L1J_seeds->at(l1jBXp1_jetHLTprobe_close);
	((TH2F*)hist("L1J_drJetHLTprobeMin_dR0dRp1"))->Fill(-0.1,uhh2::deltaR(L1J_bxp1,jet_probe), weight);
      }
      else{
	if(l1jBX0_jetHLTprobe_close>-1){
	  auto& L1J_bx0 = event.L1J_seeds->at(l1jBX0_jetHLTprobe_close);
	  ((TH2F*)hist("L1J_drJetHLTprobeMin_dR0dRp1"))->Fill(uhh2::deltaR(L1J_bx0,jet_probe),-0.1, weight);
	}
      }
    }

    if(bx == -1){
      hist("L1J_drJetHLTprobeMin_Pt_bxMinus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJetHLTprobeMin_dR_bxMinus1")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
      hist("L1J_drJetHLTprobeMin_Ptave_bxMinus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
      hist("L1J_drJetHLTprobeMin_EtaProbe_bxMinus1")->Fill(jet_probe.eta(), weight);
      hist("L1J_drJetHLTprobeMin_pBalAsymmetry_bxMinus1")->Fill(A_asymmetry, weight);
      hist("L1J_drJetHLTprobeMin_mpfAsymmetry_bxMinus1")->Fill(B_asymmetry, weight);
      hist("L1J_drJetHLTprobeMin_pBalResponse_bxMinus1")->Fill(rel_r, weight);
      hist("L1J_drJetHLTprobeMin_mpfResponse_bxMinus1")->Fill(mpf_r, weight);
      ((TH2F*)hist("L1J_drJetHLTprobeMin_ProbeEtaProbePhi_bxMinus1"))->Fill(jet_probe.eta(),jet_probe.phi(),weight);
    }
    if(bx == +1){
      hist("L1J_drJetHLTprobeMin_Pt_bxPlus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJetHLTprobeMin_dR_bxPlus1")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
      hist("L1J_drJetHLTprobeMin_Ptave_bxPlus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
      hist("L1J_drJetHLTprobeMin_EtaProbe_bxPlus1")->Fill(jet_probe.eta(), weight);
      hist("L1J_drJetHLTprobeMin_pBalAsymmetry_bxPlus1")->Fill(A_asymmetry, weight);
      hist("L1J_drJetHLTprobeMin_mpfAsymmetry_bxPlus1")->Fill(B_asymmetry, weight);
      hist("L1J_drJetHLTprobeMin_pBalResponse_bxPlus1")->Fill(rel_r, weight);
      hist("L1J_drJetHLTprobeMin_mpfResponse_bxPlus1")->Fill(mpf_r, weight);
      ((TH2F*)hist("L1J_drJetHLTprobeMin_ProbeEtaProbePhi_bxPlus1"))->Fill(jet_probe.eta(),jet_probe.phi(),weight);
    }
    if(bx == 0){
      hist("L1J_drJetHLTprobeMin_Pt_bx0")->Fill(L1J.pt(), weight);
      hist("L1J_drJetHLTprobeMin_dR_bx0")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
      hist("L1J_drJetHLTprobeMin_Ptave_bx0")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
      hist("L1J_drJetHLTprobeMin_EtaProbe_bx0")->Fill(jet_probe.eta(), weight);
      hist("L1J_drJetHLTprobeMin_pBalAsymmetry_bx0")->Fill(A_asymmetry, weight);
      hist("L1J_drJetHLTprobeMin_mpfAsymmetry_bx0")->Fill(B_asymmetry, weight);
      hist("L1J_drJetHLTprobeMin_pBalResponse_bx0")->Fill(rel_r, weight);
      hist("L1J_drJetHLTprobeMin_mpfResponse_bx0")->Fill(mpf_r, weight);
      ((TH2F*)hist("L1J_drJetHLTprobeMin_ProbeEtaProbePhi_bx0"))->Fill(jet_probe.eta(),jet_probe.phi(),weight);
    }
  }

 
}

TriggerStudiesHLTmatchL1Hists::~TriggerStudiesHLTmatchL1Hists(){}
