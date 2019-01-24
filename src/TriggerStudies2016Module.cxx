#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/common/include/LumiSelection.h"

#include "UHH2/TriggersExamination/include/TriggerStudiesSelections.h"
#include "UHH2/TriggersExamination/include/TriggerStudiesHists.h"
#include "UHH2/TriggersExamination/include/TriggerStudiesDijetReducedHists.h"
#include "UHH2/TriggersExamination/include/TriggerStudiesMultipleMatchingHist.h"
#include "UHH2/TriggersExamination/include/TriggerStudiesHLTmatchL1Hists.h"
#include "UHH2/TriggersExamination/include/Lumi2016Hists.h"

using namespace std;
using namespace uhh2;

namespace uhh2examples {

/** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
 * 
 * This is the central class which calls other AnalysisModules, Hists or Selection classes.
 * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
 */
class TriggerStudies2016Module: public AnalysisModule {
public:
    
    explicit TriggerStudies2016Module(Context & ctx);
    virtual bool process(Event & event) override;

private:
    
  //    std::unique_ptr<CommonModules> common;


  // correctors
  std::unique_ptr<JetCorrector> jet_corrector, jet_corrector_BCD, jet_corrector_EFearly, jet_corrector_FlateG, jet_corrector_H;
  std::unique_ptr<GenericJetResolutionSmearer> jetER_smearer; 

  // cleaners
  std::unique_ptr<JetLeptonCleaner> jetleptoncleaner, JLC_BCD, JLC_EFearly, JLC_FlateG, JLC_H;
  std::unique_ptr<JetCleaner>       jetcleaner;
  std::unique_ptr<MuonCleaner>      muoSR_cleaner;   
  std::unique_ptr<ElectronCleaner>  eleSR_cleaner;    

    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
  std::unique_ptr<Selection> njet_sel, dijet_sel;

  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::unique_ptr<uhh2::AndSelection> metfilters_sel;

  //  std::unique_ptr<uhh2::Selection> trigger_sel;
  std::unique_ptr<uhh2::Selection> trigger40_sel;
  std::unique_ptr<uhh2::Selection> trigger60_sel;
  std::unique_ptr<uhh2::Selection> trigger80_sel;
  std::unique_ptr<uhh2::Selection> trigger140_sel;
  std::unique_ptr<uhh2::Selection> trigger200_sel;
  std::unique_ptr<uhh2::Selection> trigger260_sel;
  std::unique_ptr<uhh2::Selection> trigger320_sel;
  std::unique_ptr<uhh2::Selection> trigger400_sel;
  std::unique_ptr<uhh2::Selection> trigger500_sel;

  std::unique_ptr<uhh2::Selection> trigger60_HFJEC_sel;
  std::unique_ptr<uhh2::Selection> trigger80_HFJEC_sel;
  std::unique_ptr<uhh2::Selection> trigger100_HFJEC_sel;
  std::unique_ptr<uhh2::Selection> trigger160_HFJEC_sel;
  std::unique_ptr<uhh2::Selection> trigger220_HFJEC_sel;
  std::unique_ptr<uhh2::Selection> trigger300_HFJEC_sel;


  std::unique_ptr<uhh2::Selection> L1GT_BX_minus_1_sel;
  std::unique_ptr<uhh2::Selection> L1GT_BX_plus_1_sel;
  std::unique_ptr<uhh2::Selection> L1GT_BX_0_sel;

  //  std::unique_ptr<uhh2::AnalysisModule> UnprefireableFilter;
  //  std::unique_ptr<uhh2::Selection> UnprefireableFilter;
  std::unique_ptr<uhh2examples::EventFilter> UnprefireableFilter;

    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
  std::unique_ptr<Hists> h_nocuts,  h_njet, h_dijet, h_dijet_L2Res, h_unprefire, h_unprefire_L2Res, h_2Detaphi, h_2Detaphi_L2Res, h_trigger, h_trigger_L2Res, h_trigger_MultMatch;
  std::unique_ptr<Hists> h_lumi;

  //bin in pt (=number of triggers) and eta
  const int n_eta     = 37;
  const TString eta_range[37] = {"-5191","-3839","-3489","-3139","-2964","-2853", "-265", "-25", "-2322", "-2172", "-193", "-1653", "-1479", "-1305", "-1044", "-0783", "-0522", "-0261","00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193", "2172", "2322", "25", "2650", "2853", "2964", "3139", "3489", "3839", "5191"};
  const double eta_bins[37]     = {-5.191, -3.839, -3.489, -3.139, -2.964, -2.853, -2.65, -2.5, -2.322, -2.172, -1.93, -1.653, -1.479, -1.305, -1.044, -0.783, -0.522, -0.261, 0, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191};


  const int n_pt_HF   = 9;
  const int n_pt      = 11;
  /* 2016 DiJet HLT bins*/
  const TString pt_range[11]= {"51", "74", "96", "165", "232", "300", "366", "456", "569", "1000", "2000"};
  const double pt_bins[11]={51, 74, 96, 165, 232, 300, 366, 456, 569, 1000, 2000};
  
  const TString pt_range_HF[9]= {"72", "95", "118", "188", "257", "354", "450", "1000", "2000"};
  const double pt_bin_HF[9]={72, 95, 118, 188, 257, 354, 450, 1000, 2000}; 

  /* 2017 DiJet HLT bins*/
  /*  const TString pt_range[11]= {"53", "73", "97", "179", "307", "370", "434", "520", "649", "1000", "2000"};
  const double pt_bins[11]={53, 73, 97, 179, 307, 370, 434, 520, 649, 1000, 2000};
  const TString pt_range_HF[9]= {"73", "93", "113", "176", "239", "318", "450", "1000", "2000"};
  const double pt_bin_HF[9]={73, 93, 113, 176, 239, 318, 450, 1000, 2000}; */

  //  std::unique_ptr<Hists> h_trg[37][11];
  std::unique_ptr<Hists> h_trg_L2Res[37][11];
  std::unique_ptr<Hists> h_trg_MultMatch[37][11];


  std::unique_ptr<Hists> h_trg_L2Res_allPt[37];
  std::unique_ptr<Hists> h_trg_MultMatch_allPt[37];

  std::string trigger40 = "NULL"; std::string trigger60 = "NULL"; std::string trigger80 = "NULL"; 
  std::string trigger140 = "NULL"; std::string trigger200 = "NULL";  std::string trigger260 = "NULL"; 
  std::string trigger320 = "NULL";  std::string trigger400 = "NULL";  std::string trigger500 = "NULL";
  std::string trigger60_HFJEC = "NULL"; std::string trigger80_HFJEC = "NULL"; std::string trigger100_HFJEC = "NULL"; 
  std::string trigger160_HFJEC = "NULL"; std::string trigger220_HFJEC = "NULL"; std::string trigger300_HFJEC = "NULL";

  bool apply_unprefireable_filter = false;
  bool isMC, split_JEC_DATA, split_JEC_MC, ClosureTest;
  TString dataset_version, JEC_Version;
  string jetLabel;

  //Runnumbers for applying different corrections
  constexpr static int s_runnr_BCD     = 276811; //up to this one, including this one
  constexpr static int s_runnr_EFearly = 278802; //up to this one, EXCLUDING this one
  constexpr static int s_runnr_Fearly  = 278802; //up to this one, EXCLUDING this one
  constexpr static int s_runnr_FlateG = 280385; //up to this one, including this one
  //  bool debug = true;
  bool debug = false;
  bool fill_all_hists = false;
};


TriggerStudies2016Module::TriggerStudies2016Module(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
  cout << "Hello World from TriggerStudies2016Module!" << endl;
  isMC = (ctx.get("dataset_type") == "MC");
  fill_all_hists = (ctx.get("fill_all_hists") == "True");
    
    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
        cout << " " << kv.first << " = " << kv.second << endl;
    }

    //1. setup JEC and MET filters, call correct_met

    
    // // 1. setup other modules. CommonModules and the JetCleaner:
    // common.reset(new CommonModules());
    // // TODO: configure common here, e.g. by 
    // // calling common->set_*_id or common->disable_*
    // common->switch_metcorrection(true);
    // common->switch_metCHS(true);

    // //    common->switch_metcorrection(false);
    // common->set_jet_id(PtEtaCut(15.0, 5.2)); //cleaning low pt jets
    // common->init(ctx);
    
    // 2. set up selections
    njet_sel.reset(new NJetSelection(2)); // see common/include/NSelections.h
    dijet_sel.reset(new DijetSelection(2.7, 0.3)); // see TriggerStudiesSelections

    // 3. Set up Hists classes:
    h_nocuts.reset(new TriggerStudiesHists(ctx, "NoCuts"));
    h_njet.reset(new TriggerStudiesHists(ctx, "Njet"));
    h_dijet.reset(new TriggerStudiesHists(ctx, "Dijet"));
    h_dijet_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Dijet_L2Res"));
    h_unprefire.reset(new TriggerStudiesHists(ctx, "Unprefire"));
    h_unprefire_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Unprefire_L2Res"));
    h_2Detaphi.reset(new TriggerStudiesHists(ctx, "2Detaphi"));
    h_2Detaphi_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "2Detaphi_L2Res"));
    h_lumi.reset(new Lumi2016Hists(ctx, "LumiHists"));


    h_trigger.reset(new TriggerStudiesHists(ctx, "Trigger"));
    h_trigger_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res"));
    h_trigger_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger_MultMatch"));

    //4a. Set up lumi JSON filter
    lumi_sel.reset(new LumiSelection(ctx));

    // 4b. Set up unprefireable events filter
    UnprefireableFilter.reset(new EventFilter(ctx));
    //4c. Set up MET filters
    metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters"));
    metfilters_sel->add<TriggerSelection>("1-good-vtx", "Flag_goodVertices");
    metfilters_sel->add<TriggerSelection>("globalTightHalo2016Filter", "Flag_globalTightHalo2016Filter");
    metfilters_sel->add<TriggerSelection>("HBHENoiseFilter", "Flag_HBHENoiseFilter");
    metfilters_sel->add<TriggerSelection>("HBHENoiseIsoFilter", "Flag_HBHENoiseIsoFilter");
    metfilters_sel->add<TriggerSelection>("EcalDeadCellTriggerPrimitiveFilter", "Flag_EcalDeadCellTriggerPrimitiveFilter");
    if(!isMC)  metfilters_sel->add<TriggerSelection>("eeBadScFilter", "Flag_eeBadScFilter");
    metfilters_sel->add<TriggerSelection>("chargedHadronTrackResolutionFilter", "Flag_chargedHadronTrackResolutionFilter"); 
    metfilters_sel->add<TriggerSelection>("muonBadTrackFilter", "Flag_muonBadTrackFilter");

    //5. Set up trigger selection
    
    L1GT_BX_minus_1_sel.reset(new TriggerSelection("muGT_BX_minus_1__prefire"));//L1GT fired in BX-1
    L1GT_BX_plus_1_sel.reset(new TriggerSelection("muGT_BX_plus_1"));//L1GT fired in BX+1
    L1GT_BX_0_sel.reset(new TriggerSelection("muGT_BX_plus_0"));//L1GT fired in BX=0

    //6. Set eta-pt binned hists
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
      TString name;
      name = "Trigger_L2Res_"; name+="eta_"+eta_range[i]+"_"+eta_range[i+1];
      h_trg_L2Res_allPt[i].reset(new TriggerStudiesDijetReducedHists(ctx, name.Data()));
      name = "Trigger_MultMatch_"; name+="eta_"+eta_range[i]+"_"+eta_range[i+1];
      h_trg_MultMatch_allPt[i].reset(new TriggerStudiesMultipleMatchingHist(ctx, name.Data()));
      if(fill_all_hists){
	for(int j=0;j<(eta_cut_bool ? n_pt_HF-1 : n_pt-1 ) ; j++){
	  pt_range_j  = (eta_cut_bool ? pt_range_HF[j] : pt_range[j]);
	  pt_range_j1 = (eta_cut_bool ? pt_range_HF[j+1] : pt_range[j+1]);
	  name = "Trigger_L2Res_"; name+="eta_"+eta_range[i]+"_"+eta_range[i+1]+"_pT_"+pt_range_j+"_"+pt_range_j1;
	  h_trg_L2Res[i][j].reset(new TriggerStudiesDijetReducedHists(ctx, name.Data()));
	  name = "Trigger_MultMatch_"; name+="eta_"+eta_range[i]+"_"+eta_range[i+1]+"_pT_"+pt_range_j+"_"+pt_range_j1;
	  h_trg_MultMatch[i][j].reset(new TriggerStudiesMultipleMatchingHist(ctx, name.Data()));
	}
      }
    }

    auto apply_unprefireable_filter_str = ctx.get("apply_unprefireable_filter");
    if(apply_unprefireable_filter_str == "True") apply_unprefireable_filter = true;
     trigger40 = ctx.get("trigger40", "NULL");
     trigger60 = ctx.get("trigger60", "NULL");
     trigger80 = ctx.get("trigger80", "NULL");
     trigger140 = ctx.get("trigger140", "NULL");
     trigger200 = ctx.get("trigger200", "NULL");
     trigger260 = ctx.get("trigger260", "NULL");
     trigger320 = ctx.get("trigger320", "NULL");
     trigger400 = ctx.get("trigger400", "NULL");
     trigger500 = ctx.get("trigger500", "NULL");
     trigger60_HFJEC = ctx.get("trigger60_HFJEC", "NULL");
     trigger80_HFJEC = ctx.get("trigger80_HFJEC", "NULL");
     trigger100_HFJEC = ctx.get("trigger100_HFJEC", "NULL");
     trigger160_HFJEC = ctx.get("trigger160_HFJEC", "NULL");
     trigger220_HFJEC = ctx.get("trigger220_HFJEC", "NULL");
     trigger300_HFJEC = ctx.get("trigger300_HFJEC", "NULL");
    if(trigger40 != "NULL") 
      trigger40_sel.reset(new TriggerSelection(trigger40));
    else trigger40_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger60 != "NULL") 
      trigger60_sel.reset(new TriggerSelection(trigger60));
    else trigger60_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger80 != "NULL") 
      trigger80_sel.reset(new TriggerSelection(trigger80));
    else trigger80_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger140 != "NULL") 
      trigger140_sel.reset(new TriggerSelection(trigger140));
    else trigger140_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger200 != "NULL") 
      trigger200_sel.reset(new TriggerSelection(trigger200));
    else trigger200_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger260 != "NULL") 
      trigger260_sel.reset(new TriggerSelection(trigger260));
    else trigger260_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger320 != "NULL") 
      trigger320_sel.reset(new TriggerSelection(trigger320));
    else trigger320_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger400 != "NULL") 
      trigger400_sel.reset(new TriggerSelection(trigger400));
    else trigger400_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger500 != "NULL") 
      trigger500_sel.reset(new TriggerSelection(trigger500));
    else trigger500_sel.reset(new uhh2::AndSelection(ctx));

    if(trigger60_HFJEC != "NULL") 
      trigger60_HFJEC_sel.reset(new TriggerSelection(trigger60_HFJEC));
    else trigger60_HFJEC_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger80_HFJEC != "NULL") 
      trigger80_HFJEC_sel.reset(new TriggerSelection(trigger80_HFJEC));
    else trigger80_HFJEC_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger100_HFJEC != "NULL") 
      trigger100_HFJEC_sel.reset(new TriggerSelection(trigger100_HFJEC));
    else trigger100_HFJEC_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger160_HFJEC != "NULL") 
      trigger160_HFJEC_sel.reset(new TriggerSelection(trigger160_HFJEC));
    else trigger160_HFJEC_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger220_HFJEC != "NULL") 
      trigger220_HFJEC_sel.reset(new TriggerSelection(trigger220_HFJEC));
    else trigger220_HFJEC_sel.reset(new uhh2::AndSelection(ctx));
    if(trigger300_HFJEC != "NULL") 
      trigger300_HFJEC_sel.reset(new TriggerSelection(trigger300_HFJEC));
    else trigger300_HFJEC_sel.reset(new uhh2::AndSelection(ctx));

    split_JEC_MC   = false; //Different MC corrections only existed for Spring16_25ns_V8* 
    split_JEC_DATA = true;
    //    ClosureTest = true;//Apply L2L3Res
    ClosureTest = false;//Do NOT apply L2L3Res
    jetLabel = ctx.get("JetLabel");
    dataset_version = ctx.get("dataset_version");
    JEC_Version = ctx.get("JEC_Version");

    //std::vector<std::string> JEC_corr_noRes, JEC_corr_noRes_BCD, JEC_corr_noRes_E, JEC_corr_noRes_Fearly, JEC_corr_noRes_FlateGH; 
    std::vector<std::string> JEC_corr,       JEC_corr_BCD,       JEC_corr_EFearly,       JEC_corr_FlateG,       JEC_corr_H,      JEC_corr_MC_FlateGH;
    std::vector<std::string> JEC_corr_L1RC,  JEC_corr_BCD_L1RC,  JEC_corr_EFearly_L1RC,  JEC_corr_FlateG_L1RC,  JEC_corr_H_L1RC, JEC_corr_MC_FlateGH_L1RC;
    if(isMC){
      //for MC
      if(jetLabel == "AK4CHS"){
	if(!ClosureTest){
	  //residuals
	  //JEC-Version MC: Legacy 2017 

	 if(JEC_Version == "Summer16_07Aug2017_V14"){
	    JEC_corr              = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;           //noRes only for DATA ;), only one version for MC for deriving Summer16_07Aug2016
	    JEC_corr_L1RC         = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;           
	    //dummies, in this version, MC is not split
	    JEC_corr_BCD          = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;          
	    JEC_corr_BCD_L1RC     = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;
	    JEC_corr_EFearly      = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;
	    JEC_corr_EFearly_L1RC = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;
	    JEC_corr_FlateG       = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;
	    JEC_corr_FlateG_L1RC  = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;
	    JEC_corr_H            = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;
	    JEC_corr_H_L1RC       = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;
	    cout << "This is MC, JECs used are: ";
	    for(unsigned int i=0; i<JEC_corr.size(); i++) cout << JEC_corr[i] << ", ";
	    cout << endl;
	  }
	  else throw runtime_error("In TestModule.cxx: Invalid JEC_Version for deriving residuals on AK4CHS, MC specified ("+JEC_Version+") ");
	}
	//closure
	else{

	 if(JEC_Version == "Summer16_07Aug2017_V14"){
	    JEC_corr              = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;               //ReReco Data + Summer16 MC V14
	    JEC_corr_L1RC         = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;
	    //dummies, in this version, MC is not split
	    JEC_corr_BCD          = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;
	    JEC_corr_BCD_L1RC     = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;
	    JEC_corr_EFearly      = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;
	    JEC_corr_EFearly_L1RC = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;
	    JEC_corr_FlateG       = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;
	    JEC_corr_FlateG_L1RC  = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;
	    JEC_corr_H            = JERFiles::Summer16_07Aug2017_V14_L123_AK4PFchs_MC;
	    JEC_corr_H_L1RC       = JERFiles::Summer16_07Aug2017_V14_L1RC_AK4PFchs_MC;
	    cout << "This is MC, JECs used are: ";
	    for(unsigned int i=0; i<JEC_corr.size(); i++) cout << JEC_corr[i] << ", ";
	    cout << endl;
	  }
	  else throw runtime_error("In TestModule.cxx: Invalid JEC_Version for closure test on AK4CHS, MC specified.");
	}
      }//AK4CHS
    
    }
    else { 
      //for DATA
      if(jetLabel == "AK4CHS"){
	if(!ClosureTest){
	  //residuals
	if(JEC_Version == "Summer16_07Aug2017_V14"){
	    JEC_corr              = JERFiles::Summer16_07Aug2017_V14_GH_L123_noRes_AK4PFchs_DATA;  //ReReco Data + Moriond17 MC V14
	    JEC_corr_L1RC         = JERFiles::Summer16_07Aug2017_V14_GH_L1RC_AK4PFchs_DATA;
	    JEC_corr_BCD          = JERFiles::Summer16_07Aug2017_V14_BCD_L123_noRes_AK4PFchs_DATA;
	    JEC_corr_BCD_L1RC     = JERFiles::Summer16_07Aug2017_V14_BCD_L1RC_AK4PFchs_DATA;
	    JEC_corr_EFearly      = JERFiles::Summer16_07Aug2017_V14_EF_L123_noRes_AK4PFchs_DATA;
	    JEC_corr_EFearly_L1RC = JERFiles::Summer16_07Aug2017_V14_EF_L1RC_AK4PFchs_DATA;
	    JEC_corr_FlateG       = JERFiles::Summer16_07Aug2017_V14_GH_L123_noRes_AK4PFchs_DATA;
	    JEC_corr_FlateG_L1RC  = JERFiles::Summer16_07Aug2017_V14_GH_L1RC_AK4PFchs_DATA;
	    JEC_corr_H            = JERFiles::Summer16_07Aug2017_V14_GH_L123_noRes_AK4PFchs_DATA;
	    JEC_corr_H_L1RC       = JERFiles::Summer16_07Aug2017_V14_GH_L1RC_AK4PFchs_DATA;
	  }
	  else throw runtime_error("In TestModule.cxx: Invalid JEC_Version for deriving residuals on AK4CHS, DATA specified.");
	}//Derive corrections

	else{ //closure test
	if(JEC_Version == "Summer16_07Aug2017_V14"){
	    //closure
	    JEC_corr              = JERFiles::Summer16_07Aug2017_V14_GH_L123_AK4PFchs_DATA;              //ReReco Data + Summer16 V14
	    JEC_corr_L1RC         = JERFiles::Summer16_07Aug2017_V14_GH_L1RC_AK4PFchs_DATA;
	    JEC_corr_BCD          = JERFiles::Summer16_07Aug2017_V14_BCD_L123_AK4PFchs_DATA;
	    JEC_corr_BCD_L1RC     = JERFiles::Summer16_07Aug2017_V14_BCD_L1RC_AK4PFchs_DATA;
	    JEC_corr_EFearly      = JERFiles::Summer16_07Aug2017_V14_EF_L123_AK4PFchs_DATA;
	    JEC_corr_EFearly_L1RC = JERFiles::Summer16_07Aug2017_V14_EF_L1RC_AK4PFchs_DATA;
	    JEC_corr_FlateG       = JERFiles::Summer16_07Aug2017_V14_GH_L123_AK4PFchs_DATA;
	    JEC_corr_FlateG_L1RC  = JERFiles::Summer16_07Aug2017_V14_GH_L1RC_AK4PFchs_DATA;
	    JEC_corr_H            = JERFiles::Summer16_07Aug2017_V14_GH_L123_AK4PFchs_DATA;
	    JEC_corr_H_L1RC       = JERFiles::Summer16_07Aug2017_V14_GH_L1RC_AK4PFchs_DATA;
	    cout << "JEC for DATA: Summer16_07Aug2017_V14_BCD/EFearly/FlateG/H_L123_AK4PFchs_DATA;" << endl;
	  }
	  else throw runtime_error("In TestModule.cxx: Invalid JEC_Version for closure test on AK4CHS, DATA specified.");
	}//Closure test
      }
    }
    //DATA



    if(jetLabel == "AK4CHS"){ 
      //DATA
      if(!isMC){
	if(split_JEC_DATA){ //these only exist for DATA 
	  jet_corrector_BCD.reset(new JetCorrector(ctx, JEC_corr_BCD, JEC_corr_BCD_L1RC));
	  jet_corrector_EFearly.reset(new JetCorrector(ctx, JEC_corr_EFearly,  JEC_corr_EFearly_L1RC));
	  jet_corrector_FlateG.reset(new JetCorrector(ctx, JEC_corr_FlateG,  JEC_corr_FlateG_L1RC));
	  jet_corrector_H.reset(new JetCorrector(ctx, JEC_corr_H, JEC_corr_H_L1RC));
	  JLC_BCD.reset(new JetLeptonCleaner(ctx, JEC_corr_BCD));
	  JLC_EFearly.reset(new JetLeptonCleaner(ctx, JEC_corr_EFearly));
	  JLC_FlateG.reset(new JetLeptonCleaner(ctx, JEC_corr_FlateG));
	  JLC_H.reset(new JetLeptonCleaner(ctx, JEC_corr_H));
	}
	else{
	  jet_corrector.reset(new JetCorrector(ctx, JEC_corr, JEC_corr_L1RC));	
	  jetleptoncleaner.reset(new JetLeptonCleaner(ctx, JEC_corr));
	}
      }

      //MC
      //For MC: only one version of JECs exists
      else if(isMC){
	if(split_JEC_MC){
	  jet_corrector_BCD.reset(new JetCorrector(ctx, JEC_corr_BCD, JEC_corr_BCD_L1RC));
	  jet_corrector_EFearly.reset(new JetCorrector(ctx, JEC_corr_EFearly, JEC_corr_EFearly_L1RC));
	  jet_corrector_FlateG.reset(new JetCorrector(ctx, JEC_corr_FlateG, JEC_corr_FlateG_L1RC));
	  jet_corrector_H.reset(new JetCorrector(ctx, JEC_corr_H, JEC_corr_H_L1RC));
	  JLC_BCD.reset(new JetLeptonCleaner(ctx, JEC_corr_BCD));
	  JLC_EFearly.reset(new JetLeptonCleaner(ctx, JEC_corr_EFearly));
	  JLC_FlateG.reset(new JetLeptonCleaner(ctx, JEC_corr_FlateG));
	  JLC_H.reset(new JetLeptonCleaner(ctx, JEC_corr_H));
	}
	else{
	  jet_corrector.reset(new JetCorrector(ctx, JEC_corr, JEC_corr_L1RC));
	  jetleptoncleaner.reset(new JetLeptonCleaner(ctx, JEC_corr));
	}
      }
    }
  
  
    
    //JER Smearing for corresponding JEC-Version
  
    if(isMC){
      //if(JEC_Version == "Summer16_07Aug2017_V14") jetER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", true, JERSmearing::SF_13TeV_Summer16_25nsV1)); //03 May 2018: Updated SF
      if(JEC_Version == "Summer16_07Aug2017_V14") jetER_smearer.reset(new GenericJetResolutionSmearer(ctx)); //03 May 2018: Updated SF
      else throw runtime_error("In TestModule.cxx: When setting up JER smearer, invalid 'JEC_Version' was specified.");
    }
  



}


bool TriggerStudies2016Module::process(Event & event) {
   
    
  //    cout << "TriggerStudies2016Module: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;
  // 0. Apply lumi JSOn selection
  if(!lumi_sel->passes(event)) return false;

    // // 1. run all modules other modules.
    // common->process(event);
    
    // 2. test selections and fill histograms
    h_nocuts->fill(event);

    //2a. Require at least 2 jets with pt>15 GeV
    bool njet_selection = njet_sel->passes(event);
    if (!njet_selection)  return false;
    h_njet->fill(event);
    sort_by_pt(*event.jets);

    //2b. Require jet to be back-to-back and alpha be smaller than 0.3
    bool dijet_selection = dijet_sel->passes(event);
    if(!dijet_selection) return false;
    h_dijet->fill(event);
    h_dijet_L2Res->fill(event);

    //2c. Require to pass MET filter
    if(!metfilters_sel->passes(event)) return false; 

    // //2d. LEPTON selection
    // muoSR_cleaner->process(event);
    // sort_by_pt<Muon>(*event.muons); 
    // //    if(debug)  std::cout<<"#muons = "<<event.muons->size()<<std::endl;
    
    // eleSR_cleaner->process(event);
    // sort_by_pt<Electron>(*event.electrons);
    // //    if(debug) std::cout<<"#electrons = "<<event.electrons->size()<<std::endl;
    
    // if (event.electrons->size()>0 || event.muons->size()>0) return false; //TEST lepton cleaning


    //3. Apply JEC, JER and correct MET
    //####################  Select and Apply proper JEC-Versions for every Run ##################
    bool apply_BCD = false;
    bool apply_EFearly = false;
    bool apply_FlateG = false;
    bool apply_H = false;
    bool apply_global = false;

    //    cout<<"event.run = "<<event.run<<" split_JEC_DATA = "<<split_JEC_DATA<<" split_JEC_MC = "<<split_JEC_MC<<" isMC = "<<isMC<<endl;

    if(ClosureTest){
      //closure test
      if(!isMC){
	//DATA
	if(split_JEC_DATA){ 
	  //split JEC
	  if(event.run <= s_runnr_BCD)         apply_BCD = true;
	  else if(event.run < s_runnr_EFearly) apply_EFearly = true; //< is correct, not <=
	  else if(event.run <= s_runnr_FlateG) apply_FlateG = true; 
	  else if(event.run > s_runnr_FlateG) apply_H = true;
	  else throw runtime_error("TestModule.cxx: run number not covered by if-statements in process-routine.");
	  //	  cout<<" Hm ... event.run = "<<event.run<<" split_JEC_DATA = "<<split_JEC_DATA<<" split_JEC_MC = "<<split_JEC_MC<<endl;
	}
	else{
	  //not split JEC
	  apply_global = true;
	}
      }
      else{
	//MC
	if(split_JEC_MC){
	  //split JEC
	  if(dataset_version.Contains("RunBCD"))          apply_BCD = true;
	  else if(dataset_version.Contains("RunEFearly")) apply_EFearly = true;
	  else if(dataset_version.Contains("RunFlateG"))  apply_FlateG = true;
	  else if(dataset_version.Contains("RunH"))       apply_H = true;
	  else throw runtime_error("TestModule.cxx: run number not covered by if-statements in process-routine.");
	}
	else{
	  //not split JEC
	  apply_global = true;
	}
      }
    }
    else{
      //residuals
      if(!isMC){
	//DATA
	if(split_JEC_DATA){ 
	  //split JEC
	  if(event.run <= s_runnr_BCD)         apply_BCD = true;
	  else if(event.run < s_runnr_EFearly) apply_EFearly = true; //< is correct, not <= 
	  else if(event.run <= s_runnr_FlateG) apply_FlateG = true; 
	  else if(event.run > s_runnr_FlateG)  apply_H = true;
	  else throw runtime_error("TestModule.cxx: run number not covered by if-statements in process-routine.");
	}
	else{
	  //not split JEC
	  apply_global = true;
	}
      }
      
      else if(isMC){
	//MC
	if(split_JEC_MC){
	  //split JEC
	  if(dataset_version.Contains("RunBCD"))          apply_BCD = true;
	  else if(dataset_version.Contains("RunEFearly")) apply_EFearly = true;
	  else if(dataset_version.Contains("RunFlateG"))  apply_FlateG = true;
	  else if(dataset_version.Contains("RunH"))       apply_H = true;
	  else throw runtime_error("TestModule.cxx: run number not covered by if-statements in process-routine.");
	}      
	else{
	  //not split JEC
	  apply_global = true;
	}
      }
    }

    // if(debug)
    //   cout<<"all flags for apply_RunX are set"<<endl;
  
    if(apply_BCD+apply_EFearly+apply_FlateG+apply_H+apply_global != 1) throw runtime_error("In TestModule.cxx: Sum of apply_* when applying JECs is not == 1. Fix this.");


  //Second: Apply proper JECs
    if(apply_BCD){
      JLC_BCD->process(event);
      jet_corrector_BCD->process(event);
    }
    if(apply_EFearly){
      JLC_EFearly->process(event);
      jet_corrector_EFearly->process(event);
    }
   if(apply_FlateG){
      JLC_FlateG->process(event);
      jet_corrector_FlateG->process(event);
    }
    if(apply_H){
      JLC_H->process(event);
      jet_corrector_H->process(event);
    }
    if(apply_global){
      if(debug)
       	cout<<"Going to apply global correction"<<endl;
      //      jetleptoncleaner->process(event); //no leptons in the event!
      jet_corrector->process(event);
    }
    // if(debug)
    // 	cout<<"JEC correction is applied!"<<endl;

//#############################################################################################################
//################################  Apply JER and MET  ########################################################
// if(debug){     
//   cout<<"After JEC, before JER"<<endl;
//       cout << " Evt# "<<event.event<<" Run: "<<event.run<<" " << endl;
//       cout<< "MET: "<< event.met->pt() <<" jets.size() = "<<event.jets->size()<<" Njets = "<<jet_n<<endl;
//       for(unsigned int i=0;i<event.jets->size();i++){
// 	Jet* jet = &event.jets->at(i);
// 	std::cout<<"jet #"<<i<<" with eta = "<<jet->eta()<<" and corrected pt = "<<jet->pt()<<std::endl<<endl;
//      }
//    }


//     // //Apply JER to all jet collections  (Comment out for Test on Legacy Data 24.Jan2018)
//  sort_by_pt<Jet>(*event.jets);
//  if(jetER_smearer.get()) jetER_smearer->process(event); //TEST JER SFs effect
//  sort_by_pt<Jet>(*event.jets);

// if(debug){   
//   cout<<"After JER, before MET"<<endl;
//  cout << " Evt# "<<event.event<<" Run: "<<event.run<<" " << endl;
//  cout<< "MET: "<< event.met->pt() <<endl;
//       for(unsigned int i=0;i<event.jets->size();i++){
// 	Jet* jet = &event.jets->at(i);
// 	std::cout<<"jet #"<<i<<" with eta = "<<jet->eta()<<" and corrected pt = "<<jet->pt()<<std::endl<<endl;
//      }
//    }


    //correct MET only AFTER smearing the jets
    if(apply_BCD){
      jet_corrector_BCD->correct_met(event,true);
    }
    if(apply_EFearly){
      jet_corrector_EFearly->correct_met(event,true);
    }
   if(apply_FlateG){
      jet_corrector_FlateG->correct_met(event,true);
    }
    if(apply_H){
      jet_corrector_H->correct_met(event,true);
    }
    if(apply_global){
      jet_corrector->correct_met(event,true);
    }

    //    h_afterMET->fill(event); 
    // if(debug){ 
    //   cout << "After MET"<<endl;
    //   cout<< "MET: "<< event.met->pt() <<endl;
    //   cout << " Evt# "<<event.event<<" Run: "<<event.run<<" " << endl;
    //   for(unsigned int i=0;i<event.jets->size();i++){
    // 	Jet* jet = &event.jets->at(i);
    // 	std::cout<<"jet #"<<i<<" with eta = "<<jet->eta()<<" and corrected pt = "<<jet->pt()<<std::endl<<endl;
    //  }
   
//############################################################################################################    

   
 //###############################  Declare Probe and Barrel Jet  ###########################################
    Jet jet1 = event.jets->at(0);// leading jet
    Jet jet2 = event.jets->at(1);// sub-leading jet
    double pt_ave = 0.5*(jet1.pt()+jet2.pt());
    const float s_eta_barr = 1.3;
    Jet jet_probe = jet1; Jet jet_barrel = jet2;
    if ((fabs(jet1.eta())<=s_eta_barr)&&(fabs(jet2.eta())<=s_eta_barr)) {
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
    else if ((fabs(jet1.eta())<=s_eta_barr)||(fabs(jet2.eta())<=s_eta_barr)){
      if(fabs(jet1.eta())<=s_eta_barr){
	jet_probe = jet2;
	jet_barrel = jet1;
      }
      else{
	jet_probe = jet1;
	jet_barrel = jet2;
      }
    }
    //    double probejet_eta = fabs(jet_probe.eta()); 
    double probejet_eta = jet_probe.eta(); 

    //3. Check in which BX L1GT was fired
    bool L1GT_BX_minus1 = L1GT_BX_minus_1_sel->passes(event);
    bool L1GT_BX_plus1 =  L1GT_BX_plus_1_sel->passes(event);
    bool L1GT_BX_0 =  L1GT_BX_0_sel->passes(event);
    //    cout<<" L1GT_BX_minus1, L1GT_BX_plus1, L1GT_BX_0 = "<<L1GT_BX_minus1<<" "<<L1GT_BX_plus1<<" "<<L1GT_BX_0<<endl;

    //4. Apply unprefiable events filter
    if(apply_unprefireable_filter){
      //      cout<<"apply_unprefireable_filter!"<<endl;
      bool unprefire_sel = UnprefireableFilter->passes(event);
      if(!unprefire_sel)  return false; //TEST
      h_unprefire->fill(event);
      h_unprefire_L2Res->fill(event);
    }

    //5. Apply cleaning with eta-phi map
    bool etaphi2D_sel = UnprefireableFilter->EtaPhiCleaning(event);
    if(!etaphi2D_sel)  return false; //TEST
    h_2Detaphi->fill(event);
    h_2Detaphi_L2Res->fill(event);


    //6. apply trigger selection

    bool pass_trigger40=false; bool pass_trigger60=false; bool pass_trigger80=false;
    bool pass_trigger140=false; bool pass_trigger200=false; bool pass_trigger260=false;
    bool pass_trigger320=false; bool pass_trigger400=false; bool pass_trigger500=false;
    bool pass_trigger60_HFJEC=false; bool pass_trigger80_HFJEC=false;
    bool pass_trigger100_HFJEC=false; bool pass_trigger160_HFJEC=false;
    bool pass_trigger220_HFJEC=false; bool pass_trigger300_HFJEC=false;
   
    
    const double eta_cut = 2.853;
    bool eta_cut_bool = abs(probejet_eta) <  eta_cut;     
    bool eta_cut_bool_HF = abs(probejet_eta) >=  eta_cut;
    std::vector<bool> pass_trigger_list;
    pass_trigger40 = (trigger40_sel->passes(event) && pt_ave>pt_bins[0]   && pt_ave<pt_bins[1] && (eta_cut_bool));
    pass_trigger60 = (trigger60_sel->passes(event) && pt_ave>pt_bins[1]   && pt_ave<pt_bins[2] &&  (eta_cut_bool));
    pass_trigger80 = (trigger80_sel->passes(event) && pt_ave>pt_bins[2]   && pt_ave<pt_bins[3]&& (eta_cut_bool)); 
    pass_trigger140 = (trigger140_sel->passes(event) && pt_ave>pt_bins[3] && pt_ave<pt_bins[4]&& (eta_cut_bool)); 
    pass_trigger200 = (trigger200_sel->passes(event) && pt_ave>pt_bins[4] && pt_ave<pt_bins[5]&& (eta_cut_bool)); 
    pass_trigger260 = (trigger260_sel->passes(event) && pt_ave>pt_bins[5] && pt_ave<pt_bins[6]&& (eta_cut_bool));
    pass_trigger320 = (trigger320_sel->passes(event) && pt_ave>pt_bins[6] && pt_ave<pt_bins[7]&& (eta_cut_bool));
    pass_trigger400 = (trigger400_sel->passes(event) && pt_ave>pt_bins[7] && pt_ave<pt_bins[8]&& (eta_cut_bool));
    pass_trigger500 = (trigger500_sel->passes(event) && pt_ave>pt_bins[8] && (eta_cut_bool));
      
    //FWD Trigger
    pass_trigger60_HFJEC = (trigger60_HFJEC_sel->passes(event) && pt_ave>pt_bin_HF[0]   && pt_ave<pt_bin_HF[1] && eta_cut_bool_HF);
    pass_trigger80_HFJEC = (trigger80_HFJEC_sel->passes(event) && pt_ave>pt_bin_HF[1]   && pt_ave<pt_bin_HF[2] && eta_cut_bool_HF);
    pass_trigger100_HFJEC = (trigger100_HFJEC_sel->passes(event) && pt_ave>pt_bin_HF[2] && pt_ave<pt_bin_HF[3] && eta_cut_bool_HF);
    pass_trigger160_HFJEC = (trigger160_HFJEC_sel->passes(event) && pt_ave>pt_bin_HF[3] && pt_ave<pt_bin_HF[4] && eta_cut_bool_HF);
    pass_trigger220_HFJEC = (trigger220_HFJEC_sel->passes(event) && pt_ave>pt_bin_HF[4] && pt_ave<pt_bin_HF[5] && eta_cut_bool_HF);
    pass_trigger300_HFJEC = (trigger300_HFJEC_sel->passes(event) && pt_ave>pt_bin_HF[5] && eta_cut_bool_HF); 


    pass_trigger_list.push_back(pass_trigger40);
    pass_trigger_list.push_back(pass_trigger60);
    pass_trigger_list.push_back(pass_trigger80);
    pass_trigger_list.push_back(pass_trigger140);
    pass_trigger_list.push_back(pass_trigger200); 
    pass_trigger_list.push_back(pass_trigger260);
    pass_trigger_list.push_back(pass_trigger320);
    pass_trigger_list.push_back(pass_trigger400);
    pass_trigger_list.push_back(pass_trigger500);
      
    //FWD Trigger
    pass_trigger_list.push_back(pass_trigger60_HFJEC);
    pass_trigger_list.push_back(pass_trigger80_HFJEC);
    pass_trigger_list.push_back(pass_trigger100_HFJEC);
    pass_trigger_list.push_back(pass_trigger160_HFJEC);
    pass_trigger_list.push_back(pass_trigger220_HFJEC);
    pass_trigger_list.push_back(pass_trigger300_HFJEC);


    bool trigger_selection = pass_trigger40 || pass_trigger60 || pass_trigger80 || pass_trigger140 || pass_trigger200 || pass_trigger260 || pass_trigger320 || pass_trigger400 || pass_trigger500 || pass_trigger60_HFJEC || pass_trigger80_HFJEC || pass_trigger100_HFJEC || pass_trigger160_HFJEC || pass_trigger220_HFJEC || pass_trigger300_HFJEC;
    if(!trigger_selection) return false;
    // cout<<"pass_trigger40 = "<<pass_trigger40<<" pass_trigger60 = "<<pass_trigger60<<" pass_trigger80 = " <<pass_trigger80
    // 	<<" pass_trigger140 = "<<pass_trigger140<<" pass_trigger200 = "<<pass_trigger200<<" pass_trigger260 = "<<pass_trigger260
    // 	<<" pass_trigger320 = "<<pass_trigger320<<" pass_trigger400 = "<<pass_trigger400<<" pass_trigger500 = "<<pass_trigger500<<endl;
    // cout<<" pass_trigger60_HFJEC = "<<pass_trigger60_HFJEC<<" pass_trigger80_HFJEC = "<<pass_trigger80_HFJEC<<" pass_trigger100_HFJEC = "<<pass_trigger100_HFJEC
    // 	<<" pass_trigger160_HFJEC = "<<pass_trigger160_HFJEC<<" pass_trigger220_HFJEC = "<<pass_trigger220_HFJEC<<" pass_trigger300_HFJEC = "<<pass_trigger300_HFJEC<<endl;

    //6. Scale each event accounding to prescale //ToDo: take into account L1 prescales too!
    int prescale_trigger40=1; int prescale_trigger60=1; int prescale_trigger80=1;
    int prescale_trigger140=1; int prescale_trigger200=1; int prescale_trigger260=1;
    int prescale_trigger320=1; int prescale_trigger400=1; int prescale_trigger500=1;
    int prescale_trigger60_HFJEC=1; int prescale_trigger80_HFJEC=1;
    int prescale_trigger100_HFJEC=1; int prescale_trigger160_HFJEC=1;
    int prescale_trigger220_HFJEC=1; int prescale_trigger300_HFJEC=1;

    int prescale_triggerL1_40=1; int prescale_triggerL1_60=1; int prescale_triggerL1_80=1;
    int prescale_triggerL1_140=1; int prescale_triggerL1_200=1; int prescale_triggerL1_260=1;
    int prescale_triggerL1_320=1; int prescale_triggerL1_400=1; int prescale_triggerL1_500=1;
    int prescale_triggerL1_60_HFJEC=1; int prescale_triggerL1_80_HFJEC=1;
    int prescale_triggerL1_100_HFJEC=1; int prescale_triggerL1_160_HFJEC=1;
    int prescale_triggerL1_220_HFJEC=1; int prescale_triggerL1_300_HFJEC=1;
   
    if(pass_trigger40){
      uhh2::Event::TriggerIndex triggerIndex40 = event.get_trigger_index(trigger40);
      prescale_trigger40=event.trigger_prescale(triggerIndex40);
      int L1min = event.trigger_prescaleL1min(triggerIndex40);
      int L1max = event.trigger_prescaleL1max(triggerIndex40);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_40=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }
    if(pass_trigger60){
      uhh2::Event::TriggerIndex triggerIndex60 = event.get_trigger_index(trigger60);
      prescale_trigger60=event.trigger_prescale(triggerIndex60);
      int L1min = event.trigger_prescaleL1min(triggerIndex60);
      int L1max = event.trigger_prescaleL1max(triggerIndex60);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_60=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }
    if(pass_trigger80){
      uhh2::Event::TriggerIndex triggerIndex80 = event.get_trigger_index(trigger80);
      prescale_trigger80=event.trigger_prescale(triggerIndex80);
      int L1min = event.trigger_prescaleL1min(triggerIndex80);
      int L1max = event.trigger_prescaleL1max(triggerIndex80);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_80=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }
    if(pass_trigger140){
      uhh2::Event::TriggerIndex triggerIndex140 = event.get_trigger_index(trigger140);
      prescale_trigger140=event.trigger_prescale(triggerIndex140);
      int L1min = event.trigger_prescaleL1min(triggerIndex140);
      int L1max = event.trigger_prescaleL1max(triggerIndex140);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_140=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }
    if(pass_trigger200){
      uhh2::Event::TriggerIndex triggerIndex200 = event.get_trigger_index(trigger200);
      prescale_trigger200=event.trigger_prescale(triggerIndex200);
      int L1min = event.trigger_prescaleL1min(triggerIndex200);
      int L1max = event.trigger_prescaleL1max(triggerIndex200);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_200=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }
    if(pass_trigger260){
      uhh2::Event::TriggerIndex triggerIndex260 = event.get_trigger_index(trigger260);
      prescale_trigger260=event.trigger_prescale(triggerIndex260);
      int L1min = event.trigger_prescaleL1min(triggerIndex260);
      int L1max = event.trigger_prescaleL1max(triggerIndex260);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_260=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }
    if(pass_trigger320){
      uhh2::Event::TriggerIndex triggerIndex320 = event.get_trigger_index(trigger320);
      prescale_trigger320=event.trigger_prescale(triggerIndex320);
      int L1min = event.trigger_prescaleL1min(triggerIndex320);
      int L1max = event.trigger_prescaleL1max(triggerIndex320);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_320=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }
    if(pass_trigger400){
      uhh2::Event::TriggerIndex triggerIndex400 = event.get_trigger_index(trigger400);
      prescale_trigger400=event.trigger_prescale(triggerIndex400);
      int L1min = event.trigger_prescaleL1min(triggerIndex400);
      int L1max = event.trigger_prescaleL1max(triggerIndex400);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_400=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }
    if(pass_trigger500){
      uhh2::Event::TriggerIndex triggerIndex500 = event.get_trigger_index(trigger500);
      prescale_trigger500=event.trigger_prescale(triggerIndex500);
      int L1min = event.trigger_prescaleL1min(triggerIndex500);
      int L1max = event.trigger_prescaleL1max(triggerIndex500);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_500=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }

    if(pass_trigger60_HFJEC) {
      uhh2::Event::TriggerIndex triggerIndex60_HFJEC = event.get_trigger_index(trigger60_HFJEC);
      prescale_trigger60_HFJEC=event.trigger_prescale(triggerIndex60_HFJEC);
      int L1min = event.trigger_prescaleL1min(triggerIndex60_HFJEC);
      int L1max = event.trigger_prescaleL1max(triggerIndex60_HFJEC);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_60_HFJEC=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }  
    if(pass_trigger80_HFJEC) {
      uhh2::Event::TriggerIndex triggerIndex80_HFJEC = event.get_trigger_index(trigger80_HFJEC);
      prescale_trigger80_HFJEC=event.trigger_prescale(triggerIndex80_HFJEC);
      int L1min = event.trigger_prescaleL1min(triggerIndex80_HFJEC);
      int L1max = event.trigger_prescaleL1max(triggerIndex80_HFJEC);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_80_HFJEC=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }  
    if(pass_trigger100_HFJEC) {
      uhh2::Event::TriggerIndex triggerIndex100_HFJEC = event.get_trigger_index(trigger100_HFJEC);
      prescale_trigger100_HFJEC=event.trigger_prescale(triggerIndex100_HFJEC);
      int L1min = event.trigger_prescaleL1min(triggerIndex100_HFJEC);
      int L1max = event.trigger_prescaleL1max(triggerIndex100_HFJEC);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_100_HFJEC=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }  
    if(pass_trigger160_HFJEC) {
      uhh2::Event::TriggerIndex triggerIndex160_HFJEC = event.get_trigger_index(trigger160_HFJEC);
      prescale_trigger160_HFJEC=event.trigger_prescale(triggerIndex160_HFJEC);
      int L1min = event.trigger_prescaleL1min(triggerIndex160_HFJEC);
      int L1max = event.trigger_prescaleL1max(triggerIndex160_HFJEC);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_160_HFJEC=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }  
    if(pass_trigger220_HFJEC) {
      uhh2::Event::TriggerIndex triggerIndex220_HFJEC = event.get_trigger_index(trigger220_HFJEC);
      prescale_trigger220_HFJEC=event.trigger_prescale(triggerIndex220_HFJEC);
      int L1min = event.trigger_prescaleL1min(triggerIndex220_HFJEC);
      int L1max = event.trigger_prescaleL1max(triggerIndex220_HFJEC);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_220_HFJEC=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }  
    if(pass_trigger300_HFJEC) {
      uhh2::Event::TriggerIndex triggerIndex300_HFJEC = event.get_trigger_index(trigger300_HFJEC);
      prescale_trigger300_HFJEC=event.trigger_prescale(triggerIndex300_HFJEC);
      int L1min = event.trigger_prescaleL1min(triggerIndex300_HFJEC);
      int L1max = event.trigger_prescaleL1max(triggerIndex300_HFJEC);
      if(L1min==1  || L1min == L1max) prescale_triggerL1_300_HFJEC=L1min;
      else cout<<"L1min = "<<L1min<<" L1max = "<<L1max;
    }  
  

    int prescale_total = prescale_trigger40*prescale_trigger60*prescale_trigger80*prescale_trigger140*prescale_trigger200*prescale_trigger260;
    prescale_total *= prescale_trigger320*prescale_trigger400*prescale_trigger500;
    //   cout<<"prescale_central = "<<prescale_total<<endl;
    prescale_total *= prescale_trigger60_HFJEC*prescale_trigger80_HFJEC*prescale_trigger100_HFJEC*prescale_trigger160_HFJEC*prescale_trigger220_HFJEC*prescale_trigger300_HFJEC;

    int prescale_total_L1 = prescale_triggerL1_40*prescale_triggerL1_60*prescale_triggerL1_80*prescale_triggerL1_140*prescale_triggerL1_200*prescale_triggerL1_260;
    prescale_total_L1 *= prescale_triggerL1_320*prescale_triggerL1_400*prescale_triggerL1_500;
    //    cout<<"prescale_central_L1 = "<<prescale_total_L1<<endl;
    prescale_total_L1 *= prescale_triggerL1_60_HFJEC*prescale_triggerL1_80_HFJEC*prescale_triggerL1_100_HFJEC*prescale_triggerL1_160_HFJEC*prescale_triggerL1_220_HFJEC*prescale_triggerL1_300_HFJEC;
    //    cout<<"prescale_central*HFJEC L1 = "<<prescale_total_L1<<endl;

    //ToDo: APPLY prescales
    // event.weight *= prescale_total;
    // event.weight *= prescale_total_L1;

    //7. Fill hists (integrated over eta and pt)
    h_lumi->fill(event);
    h_trigger->fill(event);
    h_trigger_L2Res->fill(event);
    h_trigger_MultMatch->fill(event);

    // 8. Fill hists in eta-pt bins
    double pt_bin_i;
    double pt_bin_i1;
    for(int j=0; j<n_eta-1; j++){
      if(probejet_eta > eta_bins[j+1] || probejet_eta < eta_bins[j]) continue;
      if(fabs(eta_bins[j])<fabs(eta_bins[j+1])){
	eta_cut_bool = fabs(eta_bins[j])>2.8;
      }
      else {
	eta_cut_bool = fabs(eta_bins[j+1])>2.8;
      }
	h_trg_L2Res_allPt[j]->fill(event);
	h_trg_MultMatch_allPt[j]->fill(event);
	if(fill_all_hists){
	  for(int i=0; i< (eta_cut_bool ? n_pt_HF-1 : n_pt-1) ; i++){
	    pt_bin_i  = (eta_cut_bool ? pt_bin_HF[i] : pt_bins[i]);
	    pt_bin_i1 = (eta_cut_bool ? pt_bin_HF[i+1] : pt_bins[i+1]);
	    if(pt_ave>pt_bin_i1 || pt_ave<pt_bin_i) continue;
	    //	h_trg[j][i]->fill(event);
	    h_trg_L2Res[j][i]->fill(event);
	    h_trg_MultMatch[j][i]->fill(event);
	  }
	}
    }
    return true;  
}


// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the TriggerStudies2016Module is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(TriggerStudies2016Module)

}
