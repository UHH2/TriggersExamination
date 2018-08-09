#include "UHH2/TriggersExamination/include/TriggerStudiesDijetHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

TriggerStudiesDijetHists::TriggerStudiesDijetHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
  // jets
  book<TH1F>("eta_jetTag", "#eta^{jet tag}; #eta^{jetTag}; ", 100, -5.2, 5.2);
  book<TH1F>("eta_jetProbe", "#eta^{jet probe}; #eta^{jetProbe}; ", 100, -5.2, 5.2);
  book<TH1F>("eta_jet3", "#eta^{jet 3}; #eta^{jet 3}; ", 100, -5.2, 5.2);

  book<TH1F>("pt_jetTag", "pt^{jet tag};pt^{jetTag}, GeV", 100, 0, 1000);
  book<TH1F>("pt_jetProbe", "pt^{jet probe};pt^{jetProbe}, GeV", 100, 0, 1000);
  book<TH1F>("pt_jet3", "pt^{jet 3};pt^{jet 3}, GeV", 100, 0, 1000);

  book<TH1F>("pt_jet_ave", "pt^{jet ave}, GeV", 100, 0, 1000);


  book<TH1F>("pBalAsymmetry", "pBalAsymmetry; A; Counts", 100, -2, 2.);
  book<TH1F>("mpfAsymmetry", "mpfAsymmetry; B; Counts", 100, -2, 2.);
  book<TH1F>("pBalResponse", "pBalResponse; ptBal response; Counts", 100, 0,5.0);
  book<TH1F>("mpfResponse", "mpfResponse; MPF response; Counts", 100, 0,5.0);

  //L1EG seed
  book<TH1F>("L1EG_dRjetTag_bxMinus1", "L1EG_dRjetTag_bxMinus1; dR(L1EG, jetTag) [BX=-1]; Counts", 100, 0, 10.);//dR between L1EG and jetTag for L1EG in BX=-1
  book<TH1F>("L1EG_dRjetTag_bxPlus1", "L1EG_dRjetTag_bxPlus1;  dR(L1EG, jetTag) [BX=+1]; Counts", 100, 0, 10.);//dR between L1EG and jetTag for L1EG in BX=+1
  book<TH1F>("L1EG_dRjetTag_bx0", "L1EG_dRjetTag_bx0;  dR(L1EG, jetTag) [BX=0]; Counts", 100, 0, 10.);//dR between L1EG and jetTag for L1EG in BX=0
  book<TH1F>("L1EG_dRjetProbe_bxMinus1", "L1EG_dRjetProbe_bxMinus1;  dR(L1EG, jetProbe) [BX=-1]; Counts", 100, 0, 10.);
  book<TH1F>("L1EG_dRjetProbe_bxPlus1", "L1EG_dRjetProbe_bxPlus1;  dR(L1EG, jetProbe) [BX=+1]; Counts", 100, 0, 10.);
  book<TH1F>("L1EG_dRjetProbe_bx0", "L1EG_dRjetProbe_bx0;  dR(L1EG, jetProbe) [BX=0]; Counts", 100, 0, 10.);

  book<TH1I>("L1EG_drJetTagMin_BX", "L1EG_drJetTagMin_BX; L1EG BX [#Delta^{min}R(tag jet, L1EG)]; Counts", 7,-3,3);//closest seed to jetTag
  book<TH1I>("L1EG_drJetProbeMin_BX", "L1EG_drJetProbeMin_BX; L1EG BX [#Delta^{min}R(probe jet, L1EG)]; Counts", 7,-3,3);//closest seed to jetProbe
  

  book<TH1F>("L1EG_drJetTagMin_Pt_bxMinus1", "L1EG_drJetTagMin_Pt_bxMinus1; L1EG pt [#Delta^{min}R(tag jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetTag
  book<TH1F>("L1EG_drJetTagMin_Pt_bxPlus1", "L1EG_drJetTagMin_Pt_bxPlus1; L1EG pt [#Delta^{min}R(tag jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetTag
  book<TH1F>("L1EG_drJetTagMin_Pt_bx0", "L1EG_drJetTagMin_Pt_bx0; L1EG pt [#Delta^{min}R(tag jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetTag

  book<TH1F>("L1EG_drJetProbeMin_Pt_bxMinus1", "L1EG_drJetProbeMin_Pt_bxMinus1; L1EG pt [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_Pt_bxPlus1", "L1EG_drJetProbeMin_Pt_bxPlus1; L1EG pt [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_Pt_bx0", "L1EG_drJetProbeMin_Pt_bx0; L1EG pt [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetProbe

  book<TH1F>("L1EG_drJetTagMin_Ptave_bxMinus1", "L1EG_drJetTagMin_Ptave_bxMinus1; pt_{ave} [#Delta^{min}R(tag jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetTag
  book<TH1F>("L1EG_drJetTagMin_Ptave_bxPlus1", "L1EG_drJetTagMin_Ptave_bxPlus1; pt_{ave} [#Delta^{min}R(tag jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetTag
  book<TH1F>("L1EG_drJetTagMin_Ptave_bx0", "L1EG_drJetTagMin_Ptave_bx0; pt_{ave} [#Delta^{min}R(tag jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetTag

  book<TH1F>("L1EG_drJetProbeMin_Ptave_bxMinus1", "L1EG_drJetProbeMin_Ptave_bxMinus1; pt_{ave} [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_Ptave_bxPlus1", "L1EG_drJetProbeMin_Ptave_bxPlus1; pt_{ave} [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_Ptave_bx0", "L1EG_drJetProbeMin_Ptave_bx0; pt_{ave} [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0, 1000);//closest seed to jetProbe

  book<TH1F>("L1EG_drJetTagMin_dR_bxMinus1", "L1EG_drJetTagMin_dR_bxMinus1; #Delta R(tag jet, L1EG) [#Delta^{min}R(tag jet, L1EG)]; Counts", 200, 0, 1.);//closest seed to jetTag
  book<TH1F>("L1EG_drJetTagMin_dR_bxPlus1", "L1EG_drJetTagMin_dR_bxPlus1; #Delta R(tag jet, L1EG) [#Delta^{min}R(tag jet, L1EG)]; Counts", 200, 0, 1.);//closest seed to jetTag
  book<TH1F>("L1EG_drJetTagMin_dR_bx0", "L1EG_drJetTagMin_dR_bx0; #Delta R(tag jet, L1EG) [#Delta^{min}R(tag jet, L1EG)]; Counts", 200, 0, 1.);//closest seed to jetTag

  book<TH1F>("L1EG_drJetProbeMin_dR_bxMinus1", "L1EG_drJetProbeMin_dR_bxMinus1; #Delta R(probe jet, L1EG) [#Delta^{min}R(probe jet, L1EG)]; Counts", 200, 0, 1.);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_dR_bxPlus1", "L1EG_drJetProbeMin_dR_bxPlus1; #Delta R(probe jet, L1EG) [#Delta^{min}R(probe jet, L1EG)]; Counts", 200, 0, 1.);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_dR_bx0", "L1EG_drJetProbeMin_dR_bx0; #Delta R(probe jet, L1EG) [#Delta^{min}R(probe jet, L1EG)]; Counts", 200, 0, 1.);//closest seed to jetProbe

  book<TH1F>("L1EG_drJetProbeMin_pBalAsymmetry", "L1EG_drJetProbeMin_pBalAsymmetry; A [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_pBalAsymmetry_bxMinus1", "L1EG_drJetProbeMin_pBalAsymmetry_bxMinus1; A [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_pBalAsymmetry_bxPlus1", "L1EG_drJetProbeMin_pBalAsymmetry_bxPlus1; A [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_pBalAsymmetry_bx0", "L1EG_drJetProbeMin_pBalAsymmetry_bx0; A [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_mpfAsymmetry", "L1EG_drJetProbeMin_mpfAsymmetry; B [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_mpfAsymmetry_bxMinus1", "L1EG_drJetProbeMin_mpfAsymmetry_bxMinus1; B [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_mpfAsymmetry_bxPlus1", "L1EG_drJetProbeMin_mpfAsymmetry_bxPlus1; B [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_mpfAsymmetry_bx0", "L1EG_drJetProbeMin_mpfAsymmetry_bx0; B [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, -2, 2.);//closest seed to jetProbe

  book<TH1F>("L1EG_drJetProbeMin_pBalResponse", "L1EG_drJetProbeMin_pBalResponse; ptBal response [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_pBalResponse_bxMinus1", "L1EG_drJetProbeMin_pBalResponse_bxMinus1; ptBal response [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_pBalResponse_bxPlus1", "L1EG_drJetProbeMin_pBalResponse_bxPlus1; ptBal response [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_pBalResponse_bx0", "L1EG_drJetProbeMin_pBalResponse_bx0; ptBal response [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_mpfResponse", "L1EG_drJetProbeMin_mpfResponse; MPF response [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_mpfResponse_bxMinus1", "L1EG_drJetProbeMin_mpfResponse_bxMinus1; MPF response [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_mpfResponse_bxPlus1", "L1EG_drJetProbeMin_mpfResponse_bxPlus1; MPF response [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_mpfResponse_bx0", "L1EG_drJetProbeMin_mpfResponse_bx0; MPF response [#Delta^{min}R(probe jet, L1EG)]; Counts", 100, 0,5.0);//closest seed to jetProbe

  book<TH1F>("L1EG_drJetProbeMin_neuEMfracProbe", "L1EG_drJetProbeMin_neuEMfracProbe; probe jet neutral EM fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_neuEMfracProbe_bxMinus1", "L1EG_drJetProbeMin_neuEMfracProbe_bxMinus1; probe jet neutral EM fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_neuEMfracProbe_bxPlus1", "L1EG_drJetProbeMin_neuEMfracProbe_bxPlus1; probe jet neutral EM fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_neuEMfracProbe_bx0", "L1EG_drJetProbeMin_neuEMfracProbe_bx0; probe jet neutral EM fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_chEMfracProbe", "L1EG_drJetProbeMin_chEMfracProbe; probe jet  charged EM fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_chEMfracProbe_bxMinus1", "L1EG_drJetProbeMin_chEMfracProbe_bxMinus1; probe jet charged EM fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_chEMfracProbe_bxPlus1", "L1EG_drJetProbeMin_chEMfracProbe_bxPlus1; probe jet  charged EM fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_chEMfracProbe_bx0", "L1EG_drJetProbeMin_chEMfracProbe_bx0; probe jet EM  charged fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe

  book<TH1F>("L1EG_drJetProbeMin_neuHADfracProbe", "L1EG_drJetProbeMin_neuHADfracProbe; probe jet neutral HAD fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_neuHADfracProbe_bxMinus1", "L1EG_drJetProbeMin_neuHADfracProbe_bxMinus1; probe jet neutral HAD fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_neuHADfracProbe_bxPlus1", "L1EG_drJetProbeMin_neuHADfracProbe_bxPlus1; probe jet neutral HAD fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_neuHADfracProbe_bx0", "L1EG_drJetProbeMin_neuHADfracProbe_bx0; probe jet neutral HAD fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_chHADfracProbe", "L1EG_drJetProbeMin_chHADfracProbe; probe jet  charged HAD fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_chHADfracProbe_bxMinus1", "L1EG_drJetProbeMin_chHADfracProbe_bxMinus1; probe jet charged HAD fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_chHADfracProbe_bxPlus1", "L1EG_drJetProbeMin_chHADfracProbe_bxPlus1; probe jet  charged HAD fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1EG_drJetProbeMin_chHADfracProbe_bx0", "L1EG_drJetProbeMin_chHADfracProbe_bx0; probe jet HAD  charged fraction [#Delta^{min}R(probe jet, L1EG)]; Counts", 88,0,1.1);//closest seed to jetProbe

//L1J seed

  book<TH1F>("L1J_dRjetTag_bxMinus1", "L1J_dRjetTag_bxMinus1; dR(L1Jet, jetTag) [BX=-1]; Counts", 100, 0, 10.);//dR between L1Jet and jetTag for L1Jet in BX=-1
  book<TH1F>("L1J_dRjetTag_bxPlus1", "L1J_dRjetTag_bxPlus1;  dR(L1Jet, jetTag) [BX=+1]; Counts", 100, 0, 10.);//dR between L1Jet and jetTag for L1Jet in BX=+1
  book<TH1F>("L1J_dRjetTag_bx0", "L1J_dRjetTag_bx0;  dR(L1Jet, jetTag) [BX=0]; Counts", 100, 0, 10.);//dR between L1Jet and jetTag for L1Jet in BX=0
  book<TH1F>("L1J_dRjetProbe_bxMinus1", "L1J_dRjetProbe_bxMinus1;  dR(L1Jet, jetProbe) [BX=-1]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjetProbe_bxPlus1", "L1J_dRjetProbe_bxPlus1;  dR(L1Jet, jetProbe) [BX=+1]; Counts", 100, 0, 10.);
  book<TH1F>("L1J_dRjetProbe_bx0", "L1J_dRjetProbe_bx0;  dR(L1Jet, jetProbe) [BX=0]; Counts", 100, 0, 10.);

  book<TH1I>("L1J_drJetTagMin_BX", "L1J_drJetTagMin_BX; L1Jet BX [#Delta^{min}R(tag jet, L1Jet)]; Counts", 7,-3,3);//closest seed to jetTag
  book<TH1I>("L1J_drJetProbeMin_BX", "L1J_drJetProbeMin_BX; L1Jet BX [#Delta^{min}R(probe jet, L1Jet)]; Counts", 7,-3,3);//closest seed to jetProbe

  book<TH1F>("L1J_drJetTagMin_Pt_bxMinus1", "L1J_drJetTagMin_Pt_bxMinus1; L1Jet pt [ #Delta^{min}R(tag jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetTag
  book<TH1F>("L1J_drJetTagMin_Pt_bxPlus1", "L1J_drJetTagMin_Pt_bxPlus1; L1Jet pt [#Delta^{min}R(tag jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetTag
  book<TH1F>("L1J_drJetTagMin_Pt_bx0", "L1J_drJetTagMin_Pt_bx0; L1Jet pt [#Delta^{min}R(tag jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetTag

  book<TH1F>("L1J_drJetProbeMin_Pt_bxMinus1", "L1J_drJetProbeMin_Pt_bxMinus1; L1Jet pt [ #Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_Pt_bxPlus1", "L1J_drJetProbeMin_Pt_bxPlus1; L1Jet pt [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_Pt_bx0", "L1J_drJetProbeMin_Pt_bx0; L1Jet pt [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_Pt", "L1J_drJetProbeMin_Pt; L1Jet pt [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe

  book<TH1F>("L1J_drJetTagMin_Ptave_bxMinus1", "L1J_drJetTagMin_Ptave_bxMinus1; pt_{ave} [ #Delta^{min}R(tag jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetTag
  book<TH1F>("L1J_drJetTagMin_Ptave_bxPlus1", "L1J_drJetTagMin_Ptave_bxPlus1; pt_{ave} [#Delta^{min}R(tag jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetTag
  book<TH1F>("L1J_drJetTagMin_Ptave_bx0", "L1J_drJetTagMin_Ptave_bx0; pt_{ave} [#Delta^{min}R(tag jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetTag

  book<TH1F>("L1J_drJetProbeMin_Ptave_bxMinus1", "L1J_drJetProbeMin_Ptave_bxMinus1; pt_{ave} [ #Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_Ptave_bxPlus1", "L1J_drJetProbeMin_Ptave_bxPlus1; pt_{ave} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_Ptave_bx0", "L1J_drJetProbeMin_Ptave_bx0; pt_{ave} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_Ptave", "L1J_drJetProbeMin_Ptave; pt_{ave} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe


  book<TH1F>("L1J_drJetProbeMin_EtaProbe_bxMinus1", "L1J_drJetProbeMin_EtaProbe_bxMinus1; #eta_{probe} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -5.2, 5.2);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_EtaProbe_bxPlus1", "L1J_drJetProbeMin_EtaProbe_bxPlus1; #eta_{probe} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -5.2, 5.2);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_EtaProbe_bx0", "L1J_drJetProbeMin_EtaProbe_bx0; #eta_{probe} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -5.2, 5.2);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_EtaProbe", "L1J_drJetProbeMin_EtaProbe; #eta_{probe} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -5.2, 5.2);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_PtProbe_bxMinus1", "L1J_drJetProbeMin_PtProbe_bxMinus1; Pt_{probe} [ #Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_PtProbe_bxPlus1", "L1J_drJetProbeMin_PtProbe_bxPlus1; Pt_{probe} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_PtProbe_bx0", "L1J_drJetProbeMin_PtProbe_bx0; Pt_{probe} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_PtProbe", "L1J_drJetProbeMin_PtProbe; Pt_{probe} [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0, 1000);//closest seed to jetProbe

  book<TH1F>("L1J_drJetTagMin_dR_bxMinus1", "L1J_drJetTagMin_dR_bxMinus1; #Delta R(tag jet, L1Jet) [ #Delta^{min}R(tag jet, L1Jet)]; Counts", 200, 0, 1.);//closest seed to jetTag
  book<TH1F>("L1J_drJetTagMin_dR_bxPlus1", "L1J_drJetTagMin_dR_bxPlus1; #Delta R(tag jet, L1Jet) [#Delta^{min}R(tag jet, L1Jet)]; Counts", 200, 0, 1.);//closest seed to jetTag
  book<TH1F>("L1J_drJetTagMin_dR_bx0", "L1J_drJetTagMin_dR_bx0; #Delta R(tag jet, L1Jet) [#Delta^{min}R(tag jet, L1Jet)]; Counts", 200, 0, 1.);//closest seed to jetTag
  book<TH1F>("L1J_drJetTagMin_dR", "L1J_drJetTagMin_dR; #Delta R(tag jet, L1Jet) [#Delta^{min}R(tag jet, L1Jet)]; Counts", 200, 0, 1.);//closest seed to jetTag

  book<TH1F>("L1J_drJetProbeMin_dR_bxMinus1", "L1J_drJetProbeMin_dR_bxMinus1; #Delta R(probe jet, L1Jet) [ #Delta^{min}R(probe jet, L1Jet)]; Counts", 200, 0, 1.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_dR_bxPlus1", "L1J_drJetProbeMin_dR_bxPlus1; #Delta R(probe jet, L1Jet) [#Delta^{min}R(probe jet, L1Jet)]; Counts", 200, 0, 1.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_dR_bx0", "L1J_drJetProbeMin_dR_bx0; #Delta R(probe jet, L1Jet) [#Delta^{min}R(probe jet, L1Jet)]; Counts", 200, 0, 1.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_dR", "L1J_drJetProbeMin_dR; #Delta R(probe jet, L1Jet) [#Delta^{min}R(probe jet, L1Jet)]; Counts", 200, 0, 1.);//closest seed to jetProbe

  book<TH1F>("L1J_drJetProbeMin_pBalAsymmetry", "L1J_drJetProbeMin_pBalAsymmetry; A [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_pBalAsymmetry_bxMinus1", "L1J_drJetProbeMin_pBalAsymmetry_bxMinus1; A [ #Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_pBalAsymmetry_bxPlus1", "L1J_drJetProbeMin_pBalAsymmetry_bxPlus1; A [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_pBalAsymmetry_bx0", "L1J_drJetProbeMin_pBalAsymmetry_bx0; A [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_mpfAsymmetry", "L1J_drJetProbeMin_mpfAsymmetry; B [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_mpfAsymmetry_bxMinus1", "L1J_drJetProbeMin_mpfAsymmetry_bxMinus1; B [ #Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_mpfAsymmetry_bxPlus1", "L1J_drJetProbeMin_mpfAsymmetry_bxPlus1; B [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_mpfAsymmetry_bx0", "L1J_drJetProbeMin_mpfAsymmetry_bx0; B [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, -2, 2.);//closest seed to jetProbe

  book<TH1F>("L1J_drJetProbeMin_pBalResponse", "L1J_drJetProbeMin_pBalResponse; ptBal response [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_pBalResponse_bxMinus1", "L1J_drJetProbeMin_pBalResponse_bxMinus1; ptBal response [ #Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_pBalResponse_bxPlus1", "L1J_drJetProbeMin_pBalResponse_bxPlus1; ptBal response [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_pBalResponse_bx0", "L1J_drJetProbeMin_pBalResponse_bx0; ptBal response [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_mpfResponse", "L1J_drJetProbeMin_mpfResponse; MPF response [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_mpfResponse_bxMinus1", "L1J_drJetProbeMin_mpfResponse_bxMinus1; MPF response [ #Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_mpfResponse_bxPlus1", "L1J_drJetProbeMin_mpfResponse_bxPlus1; MPF response [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_mpfResponse_bx0", "L1J_drJetProbeMin_mpfResponse_bx0; MPF response [#Delta^{min}R(probe jet, L1Jet)]; Counts", 100, 0,5.0);//closest seed to jetProbe
  //  book<TH2F>("L1J_drJetProbeMin__eta_phi","L1J_drJetProbeMin__eta_phi; probe jet #eta; probe jet #phi", 100, -5.2, 5.2, 100, -3.14, 3.41);

 book<TH1F>("L1J_drJetProbeMin_neuEMfracProbe", "L1J_drJetProbeMin_neuEMfracProbe; probe jet neutral EM fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_neuEMfracProbe_bxMinus1", "L1J_drJetProbeMin_neuEMfracProbe_bxMinus1; probe jet neutral EM fraction [ #Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_neuEMfracProbe_bxPlus1", "L1J_drJetProbeMin_neuEMfracProbe_bxPlus1; probe jet neutral EM fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_neuEMfracProbe_bx0", "L1J_drJetProbeMin_neuEMfracProbe_bx0; probe jet neutral EM fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_chEMfracProbe", "L1J_drJetProbeMin_chEMfracProbe; probe jet  charged EM fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_chEMfracProbe_bxMinus1", "L1J_drJetProbeMin_chEMfracProbe_bxMinus1; probe jet charged EM fraction [ #Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_chEMfracProbe_bxPlus1", "L1J_drJetProbeMin_chEMfracProbe_bxPlus1; probe jet  charged EM fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_chEMfracProbe_bx0", "L1J_drJetProbeMin_chEMfracProbe_bx0; probe jet EM  charged fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe

  book<TH1F>("L1J_drJetProbeMin_neuHADfracProbe", "L1J_drJetProbeMin_neuHADfracProbe; probe jet neutral HAD fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_neuHADfracProbe_bxMinus1", "L1J_drJetProbeMin_neuHADfracProbe_bxMinus1; probe jet neutral HAD fraction [ #Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_neuHADfracProbe_bxPlus1", "L1J_drJetProbeMin_neuHADfracProbe_bxPlus1; probe jet neutral HAD fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_neuHADfracProbe_bx0", "L1J_drJetProbeMin_neuHADfracProbe_bx0; probe jet neutral HAD fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_chHADfracProbe", "L1J_drJetProbeMin_chHADfracProbe; probe jet  charged HAD fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_chHADfracProbe_bxMinus1", "L1J_drJetProbeMin_chHADfracProbe_bxMinus1; probe jet charged HAD fraction [ #Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_chHADfracProbe_bxPlus1", "L1J_drJetProbeMin_chHADfracProbe_bxPlus1; probe jet  charged HAD fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe
  book<TH1F>("L1J_drJetProbeMin_chHADfracProbe_bx0", "L1J_drJetProbeMin_chHADfracProbe_bx0; probe jet HAD  charged fraction [#Delta^{min}R(probe jet, L1J)]; Counts", 88,0,1.1);//closest seed to jetProbe

  book<TH2F>("L1J_drJetProbeMin_ProbeEtaProbePhi", "L1J_drJetProbeMin_ProbeEtaProbePhi; probe jet #eta [#Delta^{min}R(probe jet, L1J)]; probe jet #phi [#Delta^{min}R(probe jet, L1J)]; Counts", 20,-5.2,5.2, 20,-3.14,3.14);//closest seed to jetProbe
  book<TH2F>("L1J_drJetProbeMin_ProbeEtaProbePhi_bx0", "L1J_drJetProbeMin_ProbeEtaProbePhi_bx0; probe jet #eta [#Delta^{min}R(probe jet, L1J)]; probe jet #phi [#Delta^{min}R(probe jet, L1J)]; Counts", 20,-5.2,5.2, 20,-3.14,3.14);//closest seed to jetProbe
  book<TH2F>("L1J_drJetProbeMin_ProbeEtaProbePhi_bxPlus1", "L1J_drJetProbeMin_ProbeEtaProbePhi_bxPlus1; probe jet #eta [#Delta^{min}R(probe jet, L1J)]; probe jet #phi [#Delta^{min}R(probe jet, L1J)]; Counts", 20,-5.2,5.2, 20,-3.14,3.14);//closest seed to jetProbe
  book<TH2F>("L1J_drJetProbeMin_ProbeEtaProbePhi_bxMinus1", "L1J_drJetProbeMin_ProbeEtaProbePhi_bxMinus1; probe jet #eta [ #Delta^{min}R(probe jet, L1J)]; probe jet #phi [#Delta^{min}R(probe jet, L1J)]; Counts", 20,-5.2,5.2, 20,-3.14,3.14);//closest seed to jetProbe

  book<TH2F>("L1J_drJetProbeMin_dR0dRm1", "L1J_drJetProbeMin_dR0dRm; #Delta R(probe jet, L1Jet BX=0) [#Delta^{min}R(probe jet, L1Jet)];#Delta R(probe jet, L1Jet BX=-1) [#Delta^{min}R(probe jet, L1Jet)]", 30, -0.1, 0.5, 30, -0.1, 0.5);
  book<TH2F>("L1J_drJetProbeMin_dR0dRp1", "L1J_drJetProbeMin_dR0dRp; #Delta R(probe jet, L1Jet BX=0) [#Delta^{min}R(probe jet, L1Jet)];#Delta R(probe jet, L1Jet BX=+1) [#Delta^{min}R(probe jet, L1Jet)]", 30, -0.1, 0.5, 30, -0.1, 0.5);
  book<TH2F>("L1J_drJetProbeMin_dPt0dPtm1", "L1J_drJetProbeMin_dPt0dPtm; (L1Jet pt BX=0)/(probe jet pt) [#Delta^{min}R(probe jet, L1Jet)]; (L1Jet pt BX=-1)/(probe jet pt) [#Delta^{min}R(probe jet, L1Jet)]", 30, -0.1, 1.2, 30, -0.1, 1.2);
  book<TH2F>("L1J_drJetProbeMin_dPt0dPtp1", "L1J_drJetProbeMin_dPt0dPtp; (L1Jet pt BX=0)/(probe jet pt) [#Delta^{min}R(probe jet, L1Jet)]; (L1Jet pt BX=+1)/(probe jet pt) [#Delta^{min}R(probe jet, L1Jet)]", 30, -0.1, 1.2, 30, -0.1, 1.2);
  book<TH2F>("L1J_drJetProbeMin_dPt0dPtm1SUM", "L1J_drJetProbeMin_dPt0dPtmSUM; (L1Jet pt BX=0)/(#sum_{-1,0,+1} L1Jet pt BX=x) [#Delta^{min}R(probe jet, L1Jet)]; (L1Jet pt BX=-1)/(#sum_{-1,0,+1} L1Jet pt BX=x) [#Delta^{min}R(probe jet, L1Jet)]", 30, -0.1, 1.2, 30, -0.1, 1.2);
}


void TriggerStudiesDijetHists::fill(const Event & event){
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
  

    hist("eta_jetTag")->Fill(jet_barrel.eta(), weight);
    hist("pt_jetTag")->Fill(jet_barrel.pt(), weight);
    hist("eta_jetProbe")->Fill(jet_probe.eta(), weight);
    hist("pt_jetProbe")->Fill(jet_probe.pt(), weight);
    hist("pt_jet_ave")->Fill(0.5*(jets->at(1).pt()+jets->at(0).pt()), weight);

  if(Njets>=3){
    //    float alpha = jet3_pt/pt_ave;
    hist("eta_jet3")->Fill(jets->at(2).eta(), weight);
    hist("pt_jet3")->Fill(jets->at(2).pt(), weight);
  }
  
  hist("pBalAsymmetry")->Fill(A_asymmetry,weight);
  hist("mpfAsymmetry")->Fill(B_asymmetry,weight);
  hist("pBalResponse")->Fill(rel_r,weight);
  hist("mpfResponse")->Fill(mpf_r,weight);


  //  cout<<"L1EG_seeds->size() = "<<event.L1EG_seeds->size()<<endl;
  double dR_l1eg_jetTag_min = 0.4;
  int l1eg_jetTag_close = -1;
  double dR_l1eg_jetProbe_min = 0.4;
  int l1eg_jetProbe_close = -1;
  int l1eg_count = 0;
  for(auto& L1EG : *event.L1EG_seeds){
    int bx_l1eg = L1EG.bx();
    if(bx_l1eg == -1){
      hist("L1EG_dRjetTag_bxMinus1")->Fill(uhh2::deltaR(L1EG,jet_barrel), weight);
      hist("L1EG_dRjetProbe_bxMinus1")->Fill(uhh2::deltaR(L1EG,jet_probe), weight);
   
    }
    if(bx_l1eg == +1){
      hist("L1EG_dRjetTag_bxPlus1")->Fill(uhh2::deltaR(L1EG,jet_barrel), weight);
      hist("L1EG_dRjetProbe_bxPlus1")->Fill(uhh2::deltaR(L1EG,jet_probe), weight);
 
    }
    if(bx_l1eg == 0){
      hist("L1EG_dRjetTag_bx0")->Fill(uhh2::deltaR(L1EG,jet_barrel), weight);
      hist("L1EG_dRjetProbe_bx0")->Fill(uhh2::deltaR(L1EG,jet_probe), weight);
    
    }

    double dR_l1eg_jetTag_ = uhh2::deltaR(L1EG,jet_barrel);
    if(dR_l1eg_jetTag_< dR_l1eg_jetTag_min){
      dR_l1eg_jetTag_min = dR_l1eg_jetTag_;
      l1eg_jetTag_close = l1eg_count;
    }
    double dR_l1eg_jetProbe_ = uhh2::deltaR(L1EG,jet_probe);
    if(dR_l1eg_jetProbe_< dR_l1eg_jetProbe_min){
      dR_l1eg_jetProbe_min = dR_l1eg_jetProbe_;
      l1eg_jetProbe_close = l1eg_count;
    }
    l1eg_count++;  
  }



  if(l1eg_jetTag_close>-1){//fill hist for L1EG seed closest to jetTag
    auto& L1EG = event.L1EG_seeds->at(l1eg_jetTag_close);
    int bx = L1EG.bx();
    hist("L1EG_drJetTagMin_BX")->Fill(bx, weight);
    if(bx == -1){ 
      hist("L1EG_drJetTagMin_Pt_bxMinus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJetTagMin_dR_bxMinus1")->Fill(uhh2::deltaR(L1EG,jet_barrel), weight);
      hist("L1EG_drJetTagMin_Ptave_bxMinus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    }
    if(bx == +1){
      hist("L1EG_drJetTagMin_Pt_bxPlus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJetTagMin_dR_bxPlus1")->Fill(uhh2::deltaR(L1EG,jet_barrel), weight);
      hist("L1EG_drJetTagMin_Ptave_bxPlus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    }
    if(bx == 0){
      hist("L1EG_drJetTagMin_Pt_bx0")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJetTagMin_dR_bx0")->Fill(uhh2::deltaR(L1EG,jet_barrel), weight);
      if(Njets>=2) hist("L1EG_drJetTagMin_Ptave_bx0")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    }
  }
  if(l1eg_jetProbe_close>-1){//fill hist for L1EG seed closest to jetProbe
    auto& L1EG = event.L1EG_seeds->at(l1eg_jetProbe_close);
    hist("L1EG_drJetProbeMin_pBalAsymmetry")->Fill(A_asymmetry, weight);
    hist("L1EG_drJetProbeMin_mpfAsymmetry")->Fill(B_asymmetry, weight);
    hist("L1EG_drJetProbeMin_pBalResponse")->Fill(rel_r, weight);
    hist("L1EG_drJetProbeMin_mpfResponse")->Fill(mpf_r, weight);
    int bx = L1EG.bx();
    hist("L1EG_drJetProbeMin_BX")->Fill(bx, weight);

//   event.set(tt_probejet_neutEmEF,jet_probe->neutralEmEnergyFraction());
//     event.set(tt_probejet_neutHadEF,jet_probe->neutralHadronEnergyFraction());
//     event.set(tt_probejet_chEmEF,jet_probe->chargedEmEnergyFraction());
//     event.set(tt_probejet_chHadEF,jet_probe->chargedHadronEnergyFraction());
//     event.set(tt_probejet_photonEF,jet_probe->photonEnergyFraction());
// event.set(tt_probejet_muonEF,jet_probe->muonEnergyFraction());

    hist("L1EG_drJetProbeMin_neuEMfracProbe")->Fill(jet_probe.neutralEmEnergyFraction(), weight);
    hist("L1EG_drJetProbeMin_chEMfracProbe")->Fill(jet_probe.chargedEmEnergyFraction(), weight);
    hist("L1EG_drJetProbeMin_neuHADfracProbe")->Fill(jet_probe.neutralHadronEnergyFraction(), weight);
    hist("L1EG_drJetProbeMin_chHADfracProbe")->Fill(jet_probe.chargedHadronEnergyFraction(), weight);
    if(bx == -1){
      hist("L1EG_drJetProbeMin_Pt_bxMinus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJetProbeMin_dR_bxMinus1")->Fill(uhh2::deltaR(L1EG,jet_probe), weight);
      hist("L1EG_drJetProbeMin_Ptave_bxMinus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
      hist("L1EG_drJetProbeMin_pBalAsymmetry_bxMinus1")->Fill(A_asymmetry, weight);
      hist("L1EG_drJetProbeMin_mpfAsymmetry_bxMinus1")->Fill(B_asymmetry, weight);
      hist("L1EG_drJetProbeMin_pBalResponse_bxMinus1")->Fill(rel_r, weight);
      hist("L1EG_drJetProbeMin_mpfResponse_bxMinus1")->Fill(mpf_r, weight);
      hist("L1EG_drJetProbeMin_neuEMfracProbe_bxMinus1")->Fill(jet_probe.neutralEmEnergyFraction(), weight);
      hist("L1EG_drJetProbeMin_chEMfracProbe_bxMinus1")->Fill(jet_probe.chargedEmEnergyFraction(), weight);
      hist("L1EG_drJetProbeMin_neuHADfracProbe_bxMinus1")->Fill(jet_probe.neutralHadronEnergyFraction(), weight);
      hist("L1EG_drJetProbeMin_chHADfracProbe_bxMinus1")->Fill(jet_probe.chargedHadronEnergyFraction(), weight);

    }
    if(bx == +1){
      hist("L1EG_drJetProbeMin_Pt_bxPlus1")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJetProbeMin_dR_bxPlus1")->Fill(uhh2::deltaR(L1EG,jet_probe), weight);
      hist("L1EG_drJetProbeMin_Ptave_bxPlus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
      hist("L1EG_drJetProbeMin_pBalAsymmetry_bxPlus1")->Fill(A_asymmetry, weight);
      hist("L1EG_drJetProbeMin_mpfAsymmetry_bxPlus1")->Fill(B_asymmetry, weight);
      hist("L1EG_drJetProbeMin_pBalResponse_bxPlus1")->Fill(rel_r, weight);
      hist("L1EG_drJetProbeMin_mpfResponse_bxPlus1")->Fill(mpf_r, weight);
      hist("L1EG_drJetProbeMin_neuEMfracProbe_bxPlus1")->Fill(jet_probe.neutralEmEnergyFraction(), weight);
      hist("L1EG_drJetProbeMin_chEMfracProbe_bxPlus1")->Fill(jet_probe.chargedEmEnergyFraction(), weight);
      hist("L1EG_drJetProbeMin_neuHADfracProbe_bxPlus1")->Fill(jet_probe.neutralHadronEnergyFraction(), weight);
      hist("L1EG_drJetProbeMin_chHADfracProbe_bxPlus1")->Fill(jet_probe.chargedHadronEnergyFraction(), weight);

    }
    if(bx == 0){
      hist("L1EG_drJetProbeMin_Pt_bx0")->Fill(L1EG.pt(), weight);
      hist("L1EG_drJetProbeMin_dR_bx0")->Fill(uhh2::deltaR(L1EG,jet_probe), weight);
      hist("L1EG_drJetProbeMin_Ptave_bx0")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
      hist("L1EG_drJetProbeMin_pBalAsymmetry_bx0")->Fill(A_asymmetry, weight);
      hist("L1EG_drJetProbeMin_mpfAsymmetry_bx0")->Fill(B_asymmetry, weight);
      hist("L1EG_drJetProbeMin_pBalResponse_bx0")->Fill(rel_r, weight);
      hist("L1EG_drJetProbeMin_mpfResponse_bx0")->Fill(mpf_r, weight);
      hist("L1EG_drJetProbeMin_neuEMfracProbe_bx0")->Fill(jet_probe.neutralEmEnergyFraction(), weight);
      hist("L1EG_drJetProbeMin_chEMfracProbe_bx0")->Fill(jet_probe.chargedEmEnergyFraction(), weight);
      hist("L1EG_drJetProbeMin_neuHADfracProbe_bx0")->Fill(jet_probe.neutralHadronEnergyFraction(), weight);
      hist("L1EG_drJetProbeMin_chHADfracProbe_bx0")->Fill(jet_probe.chargedHadronEnergyFraction(), weight);

    }
  }

 //  cout<<"L1J_seeds->size() = "<<event.L1J_seeds->size()<<endl;
  double dR_l1j_jetTag_min = 0.4;
  int l1j_jetTag_close = -1;
  double dR_l1j_jetProbe_min = 0.4;
  int l1j_jetProbe_close = -1;
  double dR_l1jBX0_jetProbe_min = 0.4;
  int l1jBX0_jetProbe_close = -1;
  double dR_l1jBXm1_jetProbe_min = 0.4;
  int l1jBXm1_jetProbe_close = -1;
  double dR_l1jBXp1_jetProbe_min = 0.4;         
  int l1jBXp1_jetProbe_close = -1;

  int l1j_count = 0;
  for(auto& L1J : *event.L1J_seeds){
    int bx_l1j = L1J.bx();
    if(bx_l1j == -1){
      hist("L1J_dRjetTag_bxMinus1")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
      hist("L1J_dRjetProbe_bxMinus1")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
     
    }
    if(bx_l1j == +1){
      hist("L1J_dRjetTag_bxPlus1")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
      hist("L1J_dRjetProbe_bxPlus1")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
   

    }
    if(bx_l1j == 0){
      hist("L1J_dRjetTag_bx0")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
      hist("L1J_dRjetProbe_bx0")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
    }

    if(Njets>=1){
      double dR_l1j_jetTag_ = uhh2::deltaR(L1J,jet_barrel);
      if(dR_l1j_jetTag_< dR_l1j_jetTag_min){
	dR_l1j_jetTag_min = dR_l1j_jetTag_;
	l1j_jetTag_close = l1j_count;
      }
    }
    if(Njets>=2){
      double dR_l1j_jetProbe_ = uhh2::deltaR(L1J,jet_probe);
      if(dR_l1j_jetProbe_< dR_l1j_jetProbe_min){
	dR_l1j_jetProbe_min = dR_l1j_jetProbe_;
	l1j_jetProbe_close = l1j_count;
      }
      //dR for different BX                                                                                                                                           
      int l1jet_bx = event.L1J_seeds->at(l1j_count).bx();
      if(l1jet_bx<0){                                                                                                                                                
	if(dR_l1j_jetProbe_< dR_l1jBXm1_jetProbe_min){                                                                                                         
	  dR_l1jBXm1_jetProbe_min = dR_l1j_jetProbe_;                                                                                                          
	  l1jBXm1_jetProbe_close = l1j_count;                                                                                                                     
	}                                                                                                                                                            
      }                                                                                                                                                              
      if(l1jet_bx>0){                                                                                                              
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
    }
    l1j_count++;
  }
  if(l1j_jetTag_close>-1){//fill hist for L1J seed closest to jetTag
    auto& L1J = event.L1J_seeds->at(l1j_jetTag_close);
    int bx = L1J.bx();
    hist("L1J_drJetTagMin_BX")->Fill(bx, weight);
    hist("L1J_drJetTagMin_dR")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
    if(bx == -1){ 
      hist("L1J_drJetTagMin_Pt_bxMinus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJetTagMin_dR_bxMinus1")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
      hist("L1J_drJetTagMin_Ptave_bxMinus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    }
    if(bx == +1){
      hist("L1J_drJetTagMin_Pt_bxPlus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJetTagMin_dR_bxPlus1")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
      hist("L1J_drJetTagMin_Ptave_bxPlus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    }
    if(bx == 0){
      hist("L1J_drJetTagMin_Pt_bx0")->Fill(L1J.pt(), weight);
      hist("L1J_drJetTagMin_dR_bx0")->Fill(uhh2::deltaR(L1J,jet_barrel), weight);
      hist("L1J_drJetTagMin_Ptave_bx0")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    }
  }
  if(l1j_jetProbe_close>-1){//fill hist for L1J seed closest to jetProbe
    auto& L1J = event.L1J_seeds->at(l1j_jetProbe_close);
    hist("L1J_drJetProbeMin_pBalAsymmetry")->Fill(A_asymmetry, weight);
    hist("L1J_drJetProbeMin_mpfAsymmetry")->Fill(B_asymmetry, weight);
    hist("L1J_drJetProbeMin_pBalResponse")->Fill(rel_r, weight);
    hist("L1J_drJetProbeMin_mpfResponse")->Fill(mpf_r, weight);
    int bx = L1J.bx();
    hist("L1J_drJetProbeMin_BX")->Fill(bx, weight);
    //    std::cout<<"L1J_drJetProbeMin_bx filled with bx = "<<bx<<std::endl;
    hist("L1J_drJetProbeMin_neuEMfracProbe")->Fill(jet_probe.neutralEmEnergyFraction(), weight);
    hist("L1J_drJetProbeMin_chEMfracProbe")->Fill(jet_probe.chargedEmEnergyFraction(), weight);
    hist("L1J_drJetProbeMin_neuHADfracProbe")->Fill(jet_probe.neutralHadronEnergyFraction(), weight);
    hist("L1J_drJetProbeMin_chHADfracProbe")->Fill(jet_probe.chargedHadronEnergyFraction(), weight);
    hist("L1J_drJetProbeMin_dR")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
    ((TH2F*)hist("L1J_drJetProbeMin_ProbeEtaProbePhi"))->Fill(jet_probe.eta(),jet_probe.phi(),weight);
    hist("L1J_drJetProbeMin_Ptave")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
    hist("L1J_drJetProbeMin_EtaProbe")->Fill(jet_probe.eta(), weight);
    hist("L1J_drJetProbeMin_Pt")->Fill(L1J.pt(), weight);
    hist("L1J_drJetProbeMin_PtProbe")->Fill(jet_probe.pt(), weight);
    //    cout<<"l1jBX0_jetProbe_close = "<<l1jBX0_jetProbe_close<<" l1jBXm1_jetProbe_close = "<<l1jBXm1_jetProbe_close<<endl;

    L1Jet L1J_bx0, L1J_bxp1, L1J_bxm1;
    double sum_pt = 0;
    if(l1jBX0_jetProbe_close>=0){
      L1J_bx0 = event.L1J_seeds->at(l1jBX0_jetProbe_close);
      sum_pt += L1J_bx0.pt();
    }
    if(l1jBXp1_jetProbe_close>=0){
      L1J_bxp1 = event.L1J_seeds->at(l1jBXp1_jetProbe_close);
      sum_pt += L1J_bxp1.pt();
    }
    if(l1jBXm1_jetProbe_close>=0){
      L1J_bxm1 = event.L1J_seeds->at(l1jBXm1_jetProbe_close);
      sum_pt += L1J_bxm1.pt();
    }

    if(l1jBX0_jetProbe_close>=0 && l1jBXm1_jetProbe_close>=0){
      //      auto& L1J_bx0 = event.L1J_seeds->at(l1jBX0_jetProbe_close);
      //      auto& L1J_bxm1 = event.L1J_seeds->at(l1jBXm1_jetProbe_close);
      // auto& L1J_bxp1 = event.L1J_seeds->at(l1jBXp1_jetProbe_close);
      ((TH2F*)hist("L1J_drJetProbeMin_dR0dRm1"))->Fill(uhh2::deltaR(L1J_bx0,jet_probe),uhh2::deltaR(L1J_bxm1,jet_probe), weight);
      ((TH2F*)hist("L1J_drJetProbeMin_dPt0dPtm1"))->Fill(L1J_bx0.pt()/jet_probe.pt(),L1J_bxm1.pt()/jet_probe.pt(), weight);
      ((TH2F*)hist("L1J_drJetProbeMin_dPt0dPtm1SUM"))->Fill(L1J_bx0.pt()/sum_pt,L1J_bxm1.pt()/sum_pt, weight);
    }
    else{
      if(l1jBX0_jetProbe_close<0 && l1jBXm1_jetProbe_close>=0){
        //auto& L1J_bxm1 = event.L1J_seeds->at(l1jBXm1_jetProbe_close);
        ((TH2F*)hist("L1J_drJetProbeMin_dR0dRm1"))->Fill(-0.1,uhh2::deltaR(L1J_bxm1,jet_probe), weight);
	((TH2F*)hist("L1J_drJetProbeMin_dPt0dPtm1"))->Fill(-0.1,L1J_bxm1.pt()/jet_probe.pt(), weight);
	((TH2F*)hist("L1J_drJetProbeMin_dPt0dPtm1SUM"))->Fill(-0.1,L1J_bxm1.pt()/sum_pt, weight);
      }                                                                        
      else{                                              
	if(l1jBX0_jetProbe_close>=0){
	  //auto& L1J_bx0 = event.L1J_seeds->at(l1jBX0_jetProbe_close);       
	  ((TH2F*)hist("L1J_drJetProbeMin_dR0dRm1"))->Fill(uhh2::deltaR(L1J_bx0,jet_probe),-0.1, weight);
	  ((TH2F*)hist("L1J_drJetProbeMin_dPt0dPtm1"))->Fill(L1J_bx0.pt()/jet_probe.pt(),-0.1, weight);
	  ((TH2F*)hist("L1J_drJetProbeMin_dPt0dPtm1SUM"))->Fill(L1J_bx0.pt()/sum_pt,-0.1, weight);
	}
      }                                                                                                                               
    }// L1Jet BX=-1, BX=0


    if(l1jBX0_jetProbe_close>=0 && l1jBXp1_jetProbe_close>=0){
      //      auto& L1J_bx0 = event.L1J_seeds->at(l1jBX0_jetProbe_close);
      //      auto& L1J_bxp1 = event.L1J_seeds->at(l1jBXp1_jetProbe_close);
      // auto& L1J_bxp1 = event.L1J_seeds->at(l1jBXp1_jetProbe_close);
      ((TH2F*)hist("L1J_drJetProbeMin_dR0dRp1"))->Fill(uhh2::deltaR(L1J_bx0,jet_probe),uhh2::deltaR(L1J_bxp1,jet_probe), weight);
      ((TH2F*)hist("L1J_drJetProbeMin_dPt0dPtp1"))->Fill(L1J_bx0.pt()/jet_probe.pt(),L1J_bxp1.pt()/jet_probe.pt(), weight);
    }
    else{
      if(l1jBX0_jetProbe_close<0 && l1jBXp1_jetProbe_close>=0){
	//        auto& L1J_bxp1 = event.L1J_seeds->at(l1jBXp1_jetProbe_close);
        ((TH2F*)hist("L1J_drJetProbeMin_dR0dRp1"))->Fill(-0.1,uhh2::deltaR(L1J_bxp1,jet_probe), weight);
	((TH2F*)hist("L1J_drJetProbeMin_dPt0dPtp1"))->Fill(-0.1,L1J_bxp1.pt()/jet_probe.pt(), weight);
      }                                                                        
      else{                                              
	if(l1jBX0_jetProbe_close>=0){
	  //	  auto& L1J_bx0 = event.L1J_seeds->at(l1jBX0_jetProbe_close);       
	  ((TH2F*)hist("L1J_drJetProbeMin_dR0dRp1"))->Fill(uhh2::deltaR(L1J_bx0,jet_probe),-0.1, weight);
	  ((TH2F*)hist("L1J_drJetProbeMin_dPt0dPtp1"))->Fill(L1J_bx0.pt()/jet_probe.pt(),-0.1, weight);
	}
      }                                                                                                                               
    }// L1Jet BX=-1, BX=0



              

    if(bx == -1){
      hist("L1J_drJetProbeMin_PtProbe_bxMinus1")->Fill(jet_probe.pt(), weight);
      hist("L1J_drJetProbeMin_Pt_bxMinus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJetProbeMin_dR_bxMinus1")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
      hist("L1J_drJetProbeMin_Ptave_bxMinus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
      hist("L1J_drJetProbeMin_EtaProbe_bxMinus1")->Fill(jet_probe.eta(), weight);
      hist("L1J_drJetProbeMin_pBalAsymmetry_bxMinus1")->Fill(A_asymmetry, weight);
      hist("L1J_drJetProbeMin_mpfAsymmetry_bxMinus1")->Fill(B_asymmetry, weight);
      hist("L1J_drJetProbeMin_pBalResponse_bxMinus1")->Fill(rel_r, weight);
      hist("L1J_drJetProbeMin_mpfResponse_bxMinus1")->Fill(mpf_r, weight);
      hist("L1J_drJetProbeMin_neuEMfracProbe_bxMinus1")->Fill(jet_probe.neutralEmEnergyFraction(), weight);
      hist("L1J_drJetProbeMin_chEMfracProbe_bxMinus1")->Fill(jet_probe.chargedEmEnergyFraction(), weight);
      hist("L1J_drJetProbeMin_neuHADfracProbe_bxMinus1")->Fill(jet_probe.neutralHadronEnergyFraction(), weight);
      hist("L1J_drJetProbeMin_chHADfracProbe_bxMinus1")->Fill(jet_probe.chargedHadronEnergyFraction(), weight);
      ((TH2F*)hist("L1J_drJetProbeMin_ProbeEtaProbePhi_bxMinus1"))->Fill(jet_probe.eta(),jet_probe.phi(),weight);
    }
    if(bx == +1){
      hist("L1J_drJetProbeMin_PtProbe_bxPlus1")->Fill(jet_probe.pt(), weight);
      hist("L1J_drJetProbeMin_Pt_bxPlus1")->Fill(L1J.pt(), weight);
      hist("L1J_drJetProbeMin_dR_bxPlus1")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
      hist("L1J_drJetProbeMin_Ptave_bxPlus1")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
      hist("L1J_drJetProbeMin_EtaProbe_bxPlus1")->Fill(jet_probe.eta(), weight);
      hist("L1J_drJetProbeMin_pBalAsymmetry_bxPlus1")->Fill(A_asymmetry, weight);
      hist("L1J_drJetProbeMin_mpfAsymmetry_bxPlus1")->Fill(B_asymmetry, weight);
      hist("L1J_drJetProbeMin_pBalResponse_bxPlus1")->Fill(rel_r, weight);
      hist("L1J_drJetProbeMin_mpfResponse_bxPlus1")->Fill(mpf_r, weight);
      hist("L1J_drJetProbeMin_neuEMfracProbe_bxPlus1")->Fill(jet_probe.neutralEmEnergyFraction(), weight);
      hist("L1J_drJetProbeMin_chEMfracProbe_bxPlus1")->Fill(jet_probe.chargedEmEnergyFraction(), weight);
      hist("L1J_drJetProbeMin_neuHADfracProbe_bxPlus1")->Fill(jet_probe.neutralHadronEnergyFraction(), weight);
      hist("L1J_drJetProbeMin_chHADfracProbe_bxPlus1")->Fill(jet_probe.chargedHadronEnergyFraction(), weight);
      ((TH2F*)hist("L1J_drJetProbeMin_ProbeEtaProbePhi_bxPlus1"))->Fill(jet_probe.eta(),jet_probe.phi(),weight);
    }
    if(bx == 0){
      hist("L1J_drJetProbeMin_PtProbe_bx0")->Fill(jet_probe.pt(), weight);
      hist("L1J_drJetProbeMin_Pt_bx0")->Fill(L1J.pt(), weight);
      hist("L1J_drJetProbeMin_dR_bx0")->Fill(uhh2::deltaR(L1J,jet_probe), weight);
      hist("L1J_drJetProbeMin_Ptave_bx0")->Fill(0.5*(jet_probe.pt()+jet_barrel.pt()), weight);
      hist("L1J_drJetProbeMin_EtaProbe_bx0")->Fill(jet_probe.eta(), weight);
      hist("L1J_drJetProbeMin_pBalAsymmetry_bx0")->Fill(A_asymmetry, weight);
      hist("L1J_drJetProbeMin_mpfAsymmetry_bx0")->Fill(B_asymmetry, weight);
      hist("L1J_drJetProbeMin_pBalResponse_bx0")->Fill(rel_r, weight);
      hist("L1J_drJetProbeMin_mpfResponse_bx0")->Fill(mpf_r, weight);
      hist("L1J_drJetProbeMin_neuEMfracProbe_bx0")->Fill(jet_probe.neutralEmEnergyFraction(), weight);
      hist("L1J_drJetProbeMin_chEMfracProbe_bx0")->Fill(jet_probe.chargedEmEnergyFraction(), weight);
      hist("L1J_drJetProbeMin_neuHADfracProbe_bx0")->Fill(jet_probe.neutralHadronEnergyFraction(), weight);
      hist("L1J_drJetProbeMin_chHADfracProbe_bx0")->Fill(jet_probe.chargedHadronEnergyFraction(), weight);
      ((TH2F*)hist("L1J_drJetProbeMin_ProbeEtaProbePhi_bx0"))->Fill(jet_probe.eta(),jet_probe.phi(),weight);
    }
  }

 
}

TriggerStudiesDijetHists::~TriggerStudiesDijetHists(){}
