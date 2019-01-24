// histograms for monitoring of variables for 3 cases:
// 1) probe jet matched to L1Jet seed with BX=0
// 2)probe jet matched to L1Jet seed with BX=-1
// 3)probe jet matched to L1Jet seed with BX=-1 and BX=0
#include "UHH2/TriggersExamination/include/TriggerStudiesMultipleMatchingHist.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

TriggerStudiesMultipleMatchingHist::TriggerStudiesMultipleMatchingHist(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
//L1J seed

  book<TH1F>("L1J_dRjetProbeL1bxMinus1_bx0", "L1J_dRjetProbeL1bxMinus1_bx0;  dR(L1Jet bx=-1, jetProbe) [matched to BX=0]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjetProbeL1bxMinus1_bxMinus1", "L1J_dRjetProbeL1bxMinus1_bxMinus1;  dR(L1Jet bx=-1, jetProbe) [matched to BX=-1]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjetProbeL1bxMinus1_bx0bxMinus1", "L1J_dRjetProbeL1bxMinus1_bx0bxMinus1;  dR(L1Jet bx=-1, jetProbe) [matched to BX=0 and BX=-1]; Counts", 100, 0, 10.);

  book<TH1F>("L1J_dRjetProbeL1bx0_bx0", "L1J_dRjetProbeL1bx0_bx0;  dR(L1Jet bx=0, jetProbe) [matched to BX=0]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjetProbeL1bx0_bxMinus1", "L1J_dRjetProbeL1bx0_bxMinus1;  dR(L1Jet bx=0, jetProbe) [matched to BX=-1]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjetProbeL1bx0_bx0bxMinus1", "L1J_dRjetProbeL1bx0_bx0bxMinus1;  dR(L1Jet bx=0, jetProbe) [matched to BX=0 and BX=-1]; Counts", 100, 0, 10.);

  book<TH1F>("L1J_PtProbeoverL1bxMinus1_bx0", "L1J_PtProbeoverL1bxMinus1_bx0;  L1Jet bx=-1 pt / jetProbe pt [matched to BX=0]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_PtProbeoverL1bxMinus1_bxMinus1", "L1J_PtProbeoverL1bxMinus1_bxMinus1;  L1Jet bx=-1 pt / jetProbe pt [matched to BX=-1]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_PtProbeoverL1bxMinus1_bx0bxMinus1", "L1J_PtProbeoverL1bxMinus1_bx0bxMinus1;  L1Jet bx=-1 pt / jetProbe pt [matched to BX=0 and BX=-1]; Counts", 100, 0, 10.);

  book<TH1F>("L1J_PtProbeoverL1bx0_bx0", "L1J_PtProbeoverL1bx0_bx0;  L1Jet bx=0 pt / jetProbe pt [matched to BX=0]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_PtProbeoverL1bx0_bxMinus1", "L1J_PtProbeoverL1bx0_bxMinus1; L1Jet bx=0 pt / jetProbe pt [matched to BX=-1]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_PtProbeoverL1bx0_bx0bxMinus1", "L1J_PtProbeoverL1bx0_bx0bxMinus1;  L1Jet bx=0 pt / jetProbe pt [matched to BX=0 and BX=-1]; Counts", 100, 0, 10.);

  book<TH1F>("L1J_mpfAsymmetry_bx0", "L1J_mpfAsymmetry_bx0; B [matched to BX=0]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_mpfAsymmetry_bxMinus1", "L1J_mpfAsymmetry_bxMinus1; B [matched to BX=-1]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_mpfAsymmetry_bx0bxMinus1", "L1J_mpfAsymmetry_bx0bxMinus1; B [matched to BX=0 and BX=-1]; Counts", 100, -2, 2.);//closest seed to jetProbe

  book<TH1F>("L1J_pBalAsymmetry_bx0", "L1J_pBalAsymmetry_bx0; B [matched to BX=0]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_pBalAsymmetry_bxMinus1", "L1J_pBalAsymmetry_bxMinus1; B [matched to BX=-1]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_pBalAsymmetry_bx0bxMinus1", "L1J_pBalAsymmetry_bx0bxMinus1; B [matched to BX=0 and BX=-1]; Counts", 100, -2, 2.);//closest seed to jetProbe



}


void TriggerStudiesMultipleMatchingHist::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;
  //  sort_by_pt(*event.jets);
  std::vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  if(Njets<2) return;

 //###############################  Declare Probe and Barrel Jet  ###########################################
  //    sort_by_pt<Jet>(*event.jets);
    Jet jet1 = event.jets->at(0);// leading jet
    Jet jet2 = event.jets->at(1);// sub-leading jet
    const float s_eta_barr = 1.3;
    Jet jet_probe = jet1; Jet jet_barrel = jet2;
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

    //  if(Njets>=3){}
  

  double dR_l1jBX0_jetProbe_min = 100.;
  int l1jBX0_jetProbe_close = -1;
  double dR_l1jBXm1_jetProbe_min = 100.;
  int l1jBXm1_jetProbe_close = -1;
  // double dR_l1jBXp1_jetProbe_min = 100.;         
  // int l1jBXp1_jetProbe_close = -1;

  // find min dR for BX=0, BX=-1, BX=+1
  int l1j_count = 0;
  for(auto& L1J : *event.L1J_seeds){
    int bx_l1j = L1J.bx();
    if(bx_l1j == -1){
      if(dR_l1jBXm1_jetProbe_min>uhh2::deltaR(L1J,jet_probe)){
	dR_l1jBXm1_jetProbe_min = uhh2::deltaR(L1J,jet_probe);
	l1jBXm1_jetProbe_close = l1j_count;
      }
    }
    // if(bx_l1j == +1){
    //   if(dR_l1jBXp1_jetProbe_min>uhh2::deltaR(L1J,jet_probe)){
    // 	dR_l1jBXp1_jetProbe_min = uhh2::deltaR(L1J,jet_probe);
    // 	l1jBXp1_jetProbe_close = l1j_count;
    //   }
    // }
    if(bx_l1j == 0){
      if(dR_l1jBX0_jetProbe_min>uhh2::deltaR(L1J,jet_probe)){
	dR_l1jBX0_jetProbe_min = uhh2::deltaR(L1J,jet_probe);
	l1jBX0_jetProbe_close = l1j_count;
      }
    }
    l1j_count++;
  }


  //1) probe jet matched to L1Jet with BX=0
  if(dR_l1jBX0_jetProbe_min<0.4 && dR_l1jBXm1_jetProbe_min>0.4){
    hist("L1J_pBalAsymmetry_bx0")->Fill(A_asymmetry, weight);
    hist("L1J_mpfAsymmetry_bx0")->Fill(B_asymmetry, weight);
    hist("L1J_dRjetProbeL1bx0_bx0")->Fill(dR_l1jBX0_jetProbe_min, weight);
    hist("L1J_dRjetProbeL1bxMinus1_bx0")->Fill(dR_l1jBXm1_jetProbe_min, weight);
    auto& L1J = event.L1J_seeds->at(l1jBX0_jetProbe_close);
    hist("L1J_PtProbeoverL1bx0_bx0")->Fill(L1J.pt()/jet_probe.pt(), weight);
    if(l1jBXm1_jetProbe_close>-1){
      auto& L1Jm1 = event.L1J_seeds->at(l1jBXm1_jetProbe_close);
      hist("L1J_PtProbeoverL1bxMinus1_bx0")->Fill(L1Jm1.pt()/jet_probe.pt(), weight);
    }
  }
  //2) probe jet matched to L1Jet with BX=-1
  if(dR_l1jBXm1_jetProbe_min<0.4 && dR_l1jBX0_jetProbe_min>0.4){
    hist("L1J_pBalAsymmetry_bxMinus1")->Fill(A_asymmetry, weight);
    hist("L1J_mpfAsymmetry_bxMinus1")->Fill(B_asymmetry, weight);
    hist("L1J_dRjetProbeL1bxMinus1_bxMinus1")->Fill(dR_l1jBXm1_jetProbe_min, weight);
    hist("L1J_dRjetProbeL1bx0_bxMinus1")->Fill(dR_l1jBX0_jetProbe_min, weight);
    auto& L1J = event.L1J_seeds->at(l1jBXm1_jetProbe_close);
    hist("L1J_PtProbeoverL1bxMinus1_bxMinus1")->Fill(L1J.pt()/jet_probe.pt(), weight);
    if(l1jBX0_jetProbe_close>-1){
      auto& L1J0 = event.L1J_seeds->at(l1jBX0_jetProbe_close);
      hist("L1J_PtProbeoverL1bx0_bxMinus1")->Fill(L1J0.pt()/jet_probe.pt(), weight);
    }
  }

  //3) probe jet matched to L1Jet with BX=0 and L1Jet with BX=-1
  if(dR_l1jBX0_jetProbe_min<0.4 && dR_l1jBXm1_jetProbe_min<0.4){
    hist("L1J_pBalAsymmetry_bx0bxMinus1")->Fill(A_asymmetry, weight);
    hist("L1J_mpfAsymmetry_bx0bxMinus1")->Fill(B_asymmetry, weight);
    hist("L1J_dRjetProbeL1bxMinus1_bx0bxMinus1")->Fill(dR_l1jBXm1_jetProbe_min, weight);
    hist("L1J_dRjetProbeL1bx0_bx0bxMinus1")->Fill(dR_l1jBX0_jetProbe_min, weight);
    auto& L1J = event.L1J_seeds->at(l1jBXm1_jetProbe_close);
    hist("L1J_PtProbeoverL1bxMinus1_bx0bxMinus1")->Fill(L1J.pt()/jet_probe.pt(), weight);
    auto& L1J0 = event.L1J_seeds->at(l1jBX0_jetProbe_close);
    hist("L1J_PtProbeoverL1bx0_bx0bxMinus1")->Fill(L1J0.pt()/jet_probe.pt(), weight);
  }
}

TriggerStudiesMultipleMatchingHist::~TriggerStudiesMultipleMatchingHist(){}
