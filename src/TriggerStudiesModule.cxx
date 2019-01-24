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

using namespace std;
using namespace uhh2;

namespace uhh2examples {

/** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
 * 
 * This is the central class which calls other AnalysisModules, Hists or Selection classes.
 * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
 */
class TriggerStudiesModule: public AnalysisModule {
public:
    
    explicit TriggerStudiesModule(Context & ctx);
    virtual bool process(Event & event) override;

private:
    
    std::unique_ptr<CommonModules> common;
    
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
  std::unique_ptr<Hists> h_nocuts,  h_njet, h_dijet, h_dijet_L2Res, h_unprefire, h_unprefire_L2Res, h_2Detaphi, h_2Detaphi_L2Res, h_trigger, h_trigger_L2Res;
  std::unique_ptr<Hists> h_trigger_BX0, h_trigger_L2Res_BX0, h_trigger_BXm1, h_trigger_L2Res_BXm1, h_trigger_BXp1, h_trigger_L2Res_BXp1;
  std::unique_ptr<Hists> h_trg40, h_trg60, h_trg80, h_trg140, h_trg200,h_trg260,h_trg320,h_trg400,h_trg500;
  std::unique_ptr<Hists> h_trgHF60, h_trgHF80,h_trgHF100, h_trgHF160,h_trgHF220, h_trgHF300;   
  std::unique_ptr<Hists> h_trg40_L2Res, h_trg60_L2Res, h_trg80_L2Res, h_trg140_L2Res, h_trg200_L2Res,h_trg260_L2Res,h_trg320_L2Res,h_trg400_L2Res,h_trg500_L2Res;
  std::unique_ptr<Hists> h_trgHF60_L2Res, h_trgHF80_L2Res,h_trgHF100_L2Res, h_trgHF160_L2Res,h_trgHF220_L2Res, h_trgHF300_L2Res;   


  //hist for probe in the barrel, probe in EC and probe in HF
  //BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2
  std::unique_ptr<Hists> h_trigger_BB, h_trigger_L2Res_BB, h_trigger_EC1, h_trigger_L2Res_EC1, h_trigger_EC2, h_trigger_L2Res_EC2, h_trigger_HF, h_trigger_L2Res_HF;
  std::unique_ptr<Hists> h_trigger_BX0_BB, h_trigger_L2Res_BX0_BB, h_trigger_BXm1_BB, h_trigger_L2Res_BXm1_BB, h_trigger_BXp1_BB, h_trigger_L2Res_BXp1_BB;
  std::unique_ptr<Hists> h_trigger_BX0_EC1, h_trigger_L2Res_BX0_EC1, h_trigger_BXm1_EC1, h_trigger_L2Res_BXm1_EC1, h_trigger_BXp1_EC1, h_trigger_L2Res_BXp1_EC1;
  std::unique_ptr<Hists> h_trigger_BX0_EC2, h_trigger_L2Res_BX0_EC2, h_trigger_BXm1_EC2, h_trigger_L2Res_BXm1_EC2, h_trigger_BXp1_EC2, h_trigger_L2Res_BXp1_EC2;
  std::unique_ptr<Hists> h_trigger_BX0_HF, h_trigger_L2Res_BX0_HF, h_trigger_BXm1_HF, h_trigger_L2Res_BXm1_HF, h_trigger_BXp1_HF, h_trigger_L2Res_BXp1_HF;

  // std::unique_ptr<Hists> h_trg40_BB, h_trg60_BB, h_trg80_BB, h_trg140_BB, h_trg200_BB,h_trg260_BB,h_trg320_BB,h_trg400_BB,h_trg500_BB;
  // std::unique_ptr<Hists> h_trgHF60_BB, h_trgHF80_BB,h_trgHF100_BB, h_trgHF160_BB,h_trgHF220_BB, h_trgHF300_BB;   

  std::unique_ptr<Hists> h_trg40_L2Res_BB, h_trg60_L2Res_BB, h_trg80_L2Res_BB, h_trg140_L2Res_BB, h_trg200_L2Res_BB,h_trg260_L2Res_BB,h_trg320_L2Res_BB,h_trg400_L2Res_BB,h_trg500_L2Res_BB;
  std::unique_ptr<Hists> h_trgHF60_L2Res_BB, h_trgHF80_L2Res_BB,h_trgHF100_L2Res_BB, h_trgHF160_L2Res_BB,h_trgHF220_L2Res_BB, h_trgHF300_L2Res_BB;   

  std::unique_ptr<Hists> h_trg40_L2Res_EC1, h_trg60_L2Res_EC1, h_trg80_L2Res_EC1, h_trg140_L2Res_EC1, h_trg200_L2Res_EC1,h_trg260_L2Res_EC1,h_trg320_L2Res_EC1,h_trg400_L2Res_EC1,h_trg500_L2Res_EC1;
  std::unique_ptr<Hists> h_trgHF60_L2Res_EC1, h_trgHF80_L2Res_EC1,h_trgHF100_L2Res_EC1, h_trgHF160_L2Res_EC1,h_trgHF220_L2Res_EC1, h_trgHF300_L2Res_EC1;   

  std::unique_ptr<Hists> h_trg40_L2Res_EC2, h_trg60_L2Res_EC2, h_trg80_L2Res_EC2, h_trg140_L2Res_EC2, h_trg200_L2Res_EC2,h_trg260_L2Res_EC2,h_trg320_L2Res_EC2,h_trg400_L2Res_EC2,h_trg500_L2Res_EC2;
  std::unique_ptr<Hists> h_trgHF60_L2Res_EC2, h_trgHF80_L2Res_EC2,h_trgHF100_L2Res_EC2, h_trgHF160_L2Res_EC2,h_trgHF220_L2Res_EC2, h_trgHF300_L2Res_EC2;   

  std::unique_ptr<Hists> h_trg40_L2Res_HF, h_trg60_L2Res_HF, h_trg80_L2Res_HF, h_trg140_L2Res_HF, h_trg200_L2Res_HF,h_trg260_L2Res_HF,h_trg320_L2Res_HF,h_trg400_L2Res_HF,h_trg500_L2Res_HF;
  std::unique_ptr<Hists> h_trgHF60_L2Res_HF, h_trgHF80_L2Res_HF,h_trgHF100_L2Res_HF, h_trgHF160_L2Res_HF,h_trgHF220_L2Res_HF, h_trgHF300_L2Res_HF;   


  std::unique_ptr<Hists> h_trg40_MultMatch, h_trg60_MultMatch, h_trg80_MultMatch, h_trg140_MultMatch, h_trg200_MultMatch,h_trg260_MultMatch,h_trg320_MultMatch,h_trg400_MultMatch,h_trg500_MultMatch;
  std::unique_ptr<Hists> h_trgHF60_MultMatch, h_trgHF80_MultMatch,h_trgHF100_MultMatch, h_trgHF160_MultMatch,h_trgHF220_MultMatch, h_trgHF300_MultMatch;   
  std::unique_ptr<Hists> h_trg40_MultMatch_BB, h_trg60_MultMatch_BB, h_trg80_MultMatch_BB, h_trg140_MultMatch_BB, h_trg200_MultMatch_BB,h_trg260_MultMatch_BB,h_trg320_MultMatch_BB,h_trg400_MultMatch_BB,h_trg500_MultMatch_BB;
  std::unique_ptr<Hists> h_trgHF60_MultMatch_BB, h_trgHF80_MultMatch_BB,h_trgHF100_MultMatch_BB, h_trgHF160_MultMatch_BB,h_trgHF220_MultMatch_BB, h_trgHF300_MultMatch_BB;   

  std::unique_ptr<Hists> h_trg40_MultMatch_EC1, h_trg60_MultMatch_EC1, h_trg80_MultMatch_EC1, h_trg140_MultMatch_EC1, h_trg200_MultMatch_EC1,h_trg260_MultMatch_EC1,h_trg320_MultMatch_EC1,h_trg400_MultMatch_EC1,h_trg500_MultMatch_EC1;
  std::unique_ptr<Hists> h_trgHF60_MultMatch_EC1, h_trgHF80_MultMatch_EC1,h_trgHF100_MultMatch_EC1, h_trgHF160_MultMatch_EC1,h_trgHF220_MultMatch_EC1, h_trgHF300_MultMatch_EC1;   

  std::unique_ptr<Hists> h_trg40_MultMatch_EC2, h_trg60_MultMatch_EC2, h_trg80_MultMatch_EC2, h_trg140_MultMatch_EC2, h_trg200_MultMatch_EC2,h_trg260_MultMatch_EC2,h_trg320_MultMatch_EC2,h_trg400_MultMatch_EC2,h_trg500_MultMatch_EC2;
  std::unique_ptr<Hists> h_trgHF60_MultMatch_EC2, h_trgHF80_MultMatch_EC2,h_trgHF100_MultMatch_EC2, h_trgHF160_MultMatch_EC2,h_trgHF220_MultMatch_EC2, h_trgHF300_MultMatch_EC2;   

  std::unique_ptr<Hists> h_trg40_MultMatch_HF, h_trg60_MultMatch_HF, h_trg80_MultMatch_HF, h_trg140_MultMatch_HF, h_trg200_MultMatch_HF,h_trg260_MultMatch_HF,h_trg320_MultMatch_HF,h_trg400_MultMatch_HF,h_trg500_MultMatch_HF;
  std::unique_ptr<Hists> h_trgHF60_MultMatch_HF, h_trgHF80_MultMatch_HF,h_trgHF100_MultMatch_HF, h_trgHF160_MultMatch_HF,h_trgHF220_MultMatch_HF, h_trgHF300_MultMatch_HF;   


  // //  std::unique_ptr<Hists> h_trigger_HLT;
  // std::unique_ptr<TriggerStudiesHLTmatchL1Hists> h_trigger_HLT;
  // std::unique_ptr<TriggerStudiesHLTmatchL1Hists> h_trigger_HLT_BB;
  // std::unique_ptr<TriggerStudiesHLTmatchL1Hists> h_trigger_HLT_EC1;
  // std::unique_ptr<TriggerStudiesHLTmatchL1Hists> h_trigger_HLT_EC2;
  // std::unique_ptr<TriggerStudiesHLTmatchL1Hists> h_trigger_HLT_HF;

  std::string trigger40 = "NULL"; std::string trigger60 = "NULL"; std::string trigger80 = "NULL"; 
  std::string trigger140 = "NULL"; std::string trigger200 = "NULL";  std::string trigger260 = "NULL"; 
  std::string trigger320 = "NULL";  std::string trigger400 = "NULL";  std::string trigger500 = "NULL";
  std::string trigger60_HFJEC = "NULL"; std::string trigger80_HFJEC = "NULL"; std::string trigger100_HFJEC = "NULL"; 
  std::string trigger160_HFJEC = "NULL"; std::string trigger220_HFJEC = "NULL"; std::string trigger300_HFJEC = "NULL";

  bool apply_unprefireable_filter = false;
};


TriggerStudiesModule::TriggerStudiesModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from TriggerStudiesModule!" << endl;
    const bool isMC = (ctx.get("dataset_type") == "MC");
   
    
    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
        cout << " " << kv.first << " = " << kv.second << endl;
    }
    
    // 1. setup other modules. CommonModules and the JetCleaner:
    common.reset(new CommonModules());
    // TODO: configure common here, e.g. by 
    // calling common->set_*_id or common->disable_*
    common->switch_metcorrection(true);
    common->switch_metCHS(true);

    //    common->switch_metcorrection(false);
    common->set_jet_id(PtEtaCut(15.0, 5.2)); //cleaning low pt jets
    common->init(ctx);
    
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

    h_trigger.reset(new TriggerStudiesHists(ctx, "Trigger"));
    h_trigger_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res"));
    // h_trigger_HLT.reset(new TriggerStudiesHLTmatchL1Hists(ctx, "Trigger_HLT"));
    // h_trigger_HLT_BB.reset(new TriggerStudiesHLTmatchL1Hists(ctx, "Trigger_HLT_BB"));
    // h_trigger_HLT_EC1.reset(new TriggerStudiesHLTmatchL1Hists(ctx, "Trigger_HLT_EC1"));
    // h_trigger_HLT_EC2.reset(new TriggerStudiesHLTmatchL1Hists(ctx, "Trigger_HLT_EC2"));
    // h_trigger_HLT_HF.reset(new TriggerStudiesHLTmatchL1Hists(ctx, "Trigger_HLT_HF"));
    h_trigger_BB.reset(new TriggerStudiesHists(ctx, "Trigger_BB"));
    h_trigger_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_BB"));
    h_trigger_EC1.reset(new TriggerStudiesHists(ctx, "Trigger_EC1"));
    h_trigger_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_EC1"));
    h_trigger_EC2.reset(new TriggerStudiesHists(ctx, "Trigger_EC2"));
    h_trigger_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_EC2"));
    h_trigger_HF.reset(new TriggerStudiesHists(ctx, "Trigger_HF"));
    h_trigger_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_HF"));


    h_trigger_BX0.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBX0"));
    h_trigger_L2Res_BX0.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBX0"));
    h_trigger_BXm1.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXm1"));
    h_trigger_L2Res_BXm1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXm1"));
    h_trigger_BXp1.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXp1"));
    h_trigger_L2Res_BXp1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXp1"));

    h_trigger_BX0_BB.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBX0_BB"));
    h_trigger_L2Res_BX0_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBX0_BB"));
    h_trigger_BXm1_BB.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXm1_BB"));
    h_trigger_L2Res_BXm1_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXm1_BB"));
    h_trigger_BXp1_BB.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXp1_BB"));
    h_trigger_L2Res_BXp1_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXp1_BB"));

    h_trigger_BX0_EC1.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBX0_EC1"));
    h_trigger_L2Res_BX0_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBX0_EC1"));
    h_trigger_BXm1_EC1.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXm1_EC1"));
    h_trigger_L2Res_BXm1_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXm1_EC1"));
    h_trigger_BXp1_EC1.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXp1_EC1"));
    h_trigger_L2Res_BXp1_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXp1_EC1"));

    h_trigger_BX0_EC2.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBX0_EC2"));
    h_trigger_L2Res_BX0_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBX0_EC2"));
    h_trigger_BXm1_EC2.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXm1_EC2"));
    h_trigger_L2Res_BXm1_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXm1_EC2"));
    h_trigger_BXp1_EC2.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXp1_EC2"));
    h_trigger_L2Res_BXp1_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXp1_EC2"));

    h_trigger_BX0_HF.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBX0_HF"));
    h_trigger_L2Res_BX0_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBX0_HF"));
    h_trigger_BXm1_HF.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXm1_HF"));
    h_trigger_L2Res_BXm1_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXm1_HF"));
    h_trigger_BXp1_HF.reset(new TriggerStudiesHists(ctx, "Trigger_L1GTBXp1_HF"));
    h_trigger_L2Res_BXp1_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger_L2Res_L1GTBXp1_HF"));

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


    h_trg40.reset(new TriggerStudiesHists(ctx, "Trigger40"));
    h_trg60.reset(new TriggerStudiesHists(ctx, "Trigger60"));
    h_trg80.reset(new TriggerStudiesHists(ctx, "Trigger80"));
    h_trg140.reset(new TriggerStudiesHists(ctx, "Trigger140"));
    h_trg200.reset(new TriggerStudiesHists(ctx, "Trigger200"));
    h_trg260.reset(new TriggerStudiesHists(ctx, "Trigger260"));
    h_trg320.reset(new TriggerStudiesHists(ctx, "Trigger320"));
    h_trg400.reset(new TriggerStudiesHists(ctx, "Trigger400"));
    h_trg500.reset(new TriggerStudiesHists(ctx, "Trigger500"));
    h_trgHF60.reset(new TriggerStudiesHists(ctx, "Trigger60HF"));
    h_trgHF80.reset(new TriggerStudiesHists(ctx, "Trigger80HF"));
    h_trgHF100.reset(new TriggerStudiesHists(ctx, "Trigger100HF"));
    h_trgHF160.reset(new TriggerStudiesHists(ctx, "Trigger160HF"));
    h_trgHF220.reset(new TriggerStudiesHists(ctx, "Trigger220HF"));
    h_trgHF300.reset(new TriggerStudiesHists(ctx, "Trigger300HF"));

    h_trg40_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger40_L2Res"));
    h_trg60_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60_L2Res"));
    h_trg80_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80_L2Res"));
    h_trg140_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger140_L2Res"));
    h_trg200_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger200_L2Res"));
    h_trg260_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger260_L2Res"));
    h_trg320_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger320_L2Res"));
    h_trg400_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger400_L2Res"));
    h_trg500_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger500_L2Res"));
    h_trgHF60_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60HF_L2Res"));
    h_trgHF80_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80HF_L2Res"));
    h_trgHF100_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger100HF_L2Res"));
    h_trgHF160_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger160HF_L2Res"));
    h_trgHF220_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger220HF_L2Res"));
    h_trgHF300_L2Res.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger300HF_L2Res"));


    h_trg40_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger40_L2Res_BB"));
    h_trg60_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60_L2Res_BB"));
    h_trg80_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80_L2Res_BB"));
    h_trg140_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger140_L2Res_BB"));
    h_trg200_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger200_L2Res_BB"));
    h_trg260_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger260_L2Res_BB"));
    h_trg320_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger320_L2Res_BB"));
    h_trg400_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger400_L2Res_BB"));
    h_trg500_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger500_L2Res_BB"));
    h_trgHF60_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60HF_L2Res_BB"));
    h_trgHF80_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80HF_L2Res_BB"));
    h_trgHF100_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger100HF_L2Res_BB"));
    h_trgHF160_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger160HF_L2Res_BB"));
    h_trgHF220_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger220HF_L2Res_BB"));
    h_trgHF300_L2Res_BB.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger300HF_L2Res_BB"));

    h_trg40_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger40_L2Res_EC1"));
    h_trg60_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60_L2Res_EC1"));
    h_trg80_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80_L2Res_EC1"));
    h_trg140_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger140_L2Res_EC1"));
    h_trg200_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger200_L2Res_EC1"));
    h_trg260_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger260_L2Res_EC1"));
    h_trg320_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger320_L2Res_EC1"));
    h_trg400_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger400_L2Res_EC1"));
    h_trg500_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger500_L2Res_EC1"));
    h_trgHF60_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60HF_L2Res_EC1"));
    h_trgHF80_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80HF_L2Res_EC1"));
    h_trgHF100_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger100HF_L2Res_EC1"));
    h_trgHF160_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger160HF_L2Res_EC1"));
    h_trgHF220_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger220HF_L2Res_EC1"));
    h_trgHF300_L2Res_EC1.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger300HF_L2Res_EC1"));


    h_trg40_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger40_L2Res_EC2"));
    h_trg60_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60_L2Res_EC2"));
    h_trg80_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80_L2Res_EC2"));
    h_trg140_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger140_L2Res_EC2"));
    h_trg200_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger200_L2Res_EC2"));
    h_trg260_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger260_L2Res_EC2"));
    h_trg320_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger320_L2Res_EC2"));
    h_trg400_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger400_L2Res_EC2"));
    h_trg500_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger500_L2Res_EC2"));
    h_trgHF60_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60HF_L2Res_EC2"));
    h_trgHF80_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80HF_L2Res_EC2"));
    h_trgHF100_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger100HF_L2Res_EC2"));
    h_trgHF160_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger160HF_L2Res_EC2"));
    h_trgHF220_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger220HF_L2Res_EC2"));
    h_trgHF300_L2Res_EC2.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger300HF_L2Res_EC2"));


    h_trg40_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger40_L2Res_HF"));
    h_trg60_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60_L2Res_HF"));
    h_trg80_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80_L2Res_HF"));
    h_trg140_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger140_L2Res_HF"));
    h_trg200_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger200_L2Res_HF"));
    h_trg260_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger260_L2Res_HF"));
    h_trg320_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger320_L2Res_HF"));
    h_trg400_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger400_L2Res_HF"));
    h_trg500_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger500_L2Res_HF"));
    h_trgHF60_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger60HF_L2Res_HF"));
    h_trgHF80_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger80HF_L2Res_HF"));
    h_trgHF100_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger100HF_L2Res_HF"));
    h_trgHF160_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger160HF_L2Res_HF"));
    h_trgHF220_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger220HF_L2Res_HF"));
    h_trgHF300_L2Res_HF.reset(new TriggerStudiesDijetReducedHists(ctx, "Trigger300HF_L2Res_HF"));


    //MultipleMatching
    h_trg40_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger40_MultMatch"));
    h_trg60_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60_MultMatch"));
    h_trg80_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80_MultMatch"));
    h_trg140_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger140_MultMatch"));
    h_trg200_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger200_MultMatch"));
    h_trg260_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger260_MultMatch"));
    h_trg320_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger320_MultMatch"));
    h_trg400_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger400_MultMatch"));
    h_trg500_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger500_MultMatch"));
    h_trgHF60_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60HF_MultMatch"));
    h_trgHF80_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80HF_MultMatch"));
    h_trgHF100_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger100HF_MultMatch"));
    h_trgHF160_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger160HF_MultMatch"));
    h_trgHF220_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger220HF_MultMatch"));
    h_trgHF300_MultMatch.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger300HF_MultMatch"));


    h_trg40_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger40_MultMatch_BB"));
    h_trg60_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60_MultMatch_BB"));
    h_trg80_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80_MultMatch_BB"));
    h_trg140_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger140_MultMatch_BB"));
    h_trg200_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger200_MultMatch_BB"));
    h_trg260_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger260_MultMatch_BB"));
    h_trg320_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger320_MultMatch_BB"));
    h_trg400_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger400_MultMatch_BB"));
    h_trg500_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger500_MultMatch_BB"));
    h_trgHF60_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60HF_MultMatch_BB"));
    h_trgHF80_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80HF_MultMatch_BB"));
    h_trgHF100_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger100HF_MultMatch_BB"));
    h_trgHF160_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger160HF_MultMatch_BB"));
    h_trgHF220_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger220HF_MultMatch_BB"));
    h_trgHF300_MultMatch_BB.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger300HF_MultMatch_BB"));

    h_trg40_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger40_MultMatch_EC1"));
    h_trg60_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60_MultMatch_EC1"));
    h_trg80_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80_MultMatch_EC1"));
    h_trg140_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger140_MultMatch_EC1"));
    h_trg200_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger200_MultMatch_EC1"));
    h_trg260_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger260_MultMatch_EC1"));
    h_trg320_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger320_MultMatch_EC1"));
    h_trg400_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger400_MultMatch_EC1"));
    h_trg500_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger500_MultMatch_EC1"));
    h_trgHF60_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60HF_MultMatch_EC1"));
    h_trgHF80_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80HF_MultMatch_EC1"));
    h_trgHF100_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger100HF_MultMatch_EC1"));
    h_trgHF160_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger160HF_MultMatch_EC1"));
    h_trgHF220_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger220HF_MultMatch_EC1"));
    h_trgHF300_MultMatch_EC1.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger300HF_MultMatch_EC1"));


    h_trg40_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger40_MultMatch_EC2"));
    h_trg60_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60_MultMatch_EC2"));
    h_trg80_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80_MultMatch_EC2"));
    h_trg140_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger140_MultMatch_EC2"));
    h_trg200_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger200_MultMatch_EC2"));
    h_trg260_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger260_MultMatch_EC2"));
    h_trg320_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger320_MultMatch_EC2"));
    h_trg400_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger400_MultMatch_EC2"));
    h_trg500_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger500_MultMatch_EC2"));
    h_trgHF60_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60HF_MultMatch_EC2"));
    h_trgHF80_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80HF_MultMatch_EC2"));
    h_trgHF100_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger100HF_MultMatch_EC2"));
    h_trgHF160_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger160HF_MultMatch_EC2"));
    h_trgHF220_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger220HF_MultMatch_EC2"));
    h_trgHF300_MultMatch_EC2.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger300HF_MultMatch_EC2"));


    h_trg40_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger40_MultMatch_HF"));
    h_trg60_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60_MultMatch_HF"));
    h_trg80_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80_MultMatch_HF"));
    h_trg140_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger140_MultMatch_HF"));
    h_trg200_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger200_MultMatch_HF"));
    h_trg260_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger260_MultMatch_HF"));
    h_trg320_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger320_MultMatch_HF"));
    h_trg400_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger400_MultMatch_HF"));
    h_trg500_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger500_MultMatch_HF"));
    h_trgHF60_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger60HF_MultMatch_HF"));
    h_trgHF80_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger80HF_MultMatch_HF"));
    h_trgHF100_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger100HF_MultMatch_HF"));
    h_trgHF160_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger160HF_MultMatch_HF"));
    h_trgHF220_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger220HF_MultMatch_HF"));
    h_trgHF300_MultMatch_HF.reset(new TriggerStudiesMultipleMatchingHist(ctx, "Trigger300HF_MultiMatch_HF"));


    // const std::string& trigger40 = ctx.get("trigger40", "NULL");
    // const std::string& trigger60 = ctx.get("trigger60", "NULL");
    // const std::string& trigger80 = ctx.get("trigger80", "NULL");
    // const std::string& trigger140 = ctx.get("trigger140", "NULL");
    // const std::string& trigger200 = ctx.get("trigger200", "NULL");
    // const std::string& trigger260 = ctx.get("trigger260", "NULL");
    // const std::string& trigger320 = ctx.get("trigger320", "NULL");
    // const std::string& trigger400 = ctx.get("trigger400", "NULL");
    // const std::string& trigger500 = ctx.get("trigger500", "NULL");
    // const std::string& trigger60_HFJEC = ctx.get("trigger60_HFJEC", "NULL");
    // const std::string& trigger80_HFJEC = ctx.get("trigger80_HFJEC", "NULL");
    // const std::string& trigger100_HFJEC = ctx.get("trigger100_HFJEC", "NULL");
    // const std::string& trigger160_HFJEC = ctx.get("trigger160_HFJEC", "NULL");
    // const std::string& trigger220_HFJEC = ctx.get("trigger220_HFJEC", "NULL");
    // const std::string& trigger300_HFJEC = ctx.get("trigger300_HFJEC", "NULL");
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

     


}


bool TriggerStudiesModule::process(Event & event) {
   
    
  //    cout << "TriggerStudiesModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;
  // 0. Apply lumi JSOn selection
  if(!lumi_sel->passes(event)) return false;

    // 1. run all modules other modules.
    common->process(event);
    
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
    double probejet_eta = fabs(jet_probe.eta()); 

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
   
    /*
    //2016 
 // constexpr static float d_Pt_AveMC_cut   =  51;
    constexpr static float d_Pt_Ave40_cut   =  51;
    constexpr static float d_Pt_Ave60_cut   =  74;
    constexpr static float d_Pt_Ave80_cut   =  96;
    constexpr static float d_Pt_Ave140_cut  = 165;
    constexpr static float d_Pt_Ave200_cut  = 232;
    constexpr static float d_Pt_Ave260_cut  = 300;
    constexpr static float d_Pt_Ave320_cut  = 366;
    constexpr static float d_Pt_Ave400_cut  = 456;
    constexpr static float d_Pt_Ave500_cut  = 569;
    constexpr static float d_Pt_Ave60HF_cut   = 72 ;
    constexpr static float d_Pt_Ave80HF_cut   = 95 ;
    constexpr static float d_Pt_Ave100HF_cut  = 118;
    constexpr static float d_Pt_Ave160HF_cut  = 188;
    constexpr static float d_Pt_Ave220HF_cut  = 257;
    constexpr static float d_Pt_Ave300HF_cut = 354;
    */

     // 2017 94X 17Nov2017
    // constexpr static float d_Pt_AveMC_cut   =  51;
    constexpr static float d_Pt_Ave40_cut   =  53;
    constexpr static float d_Pt_Ave60_cut   =  73;
    constexpr static float d_Pt_Ave80_cut   =  97;
    constexpr static float d_Pt_Ave140_cut  = 179;
    constexpr static float d_Pt_Ave200_cut  = 307;
    constexpr static float d_Pt_Ave260_cut  = 370;
    constexpr static float d_Pt_Ave320_cut  = 434;
    constexpr static float d_Pt_Ave400_cut  = 520;
    constexpr static float d_Pt_Ave500_cut  = 649;
    constexpr static float d_Pt_Ave60HF_cut   = 73 ;
    constexpr static float d_Pt_Ave80HF_cut   = 93 ;
    constexpr static float d_Pt_Ave100HF_cut  = 113;
    constexpr static float d_Pt_Ave160HF_cut  = 176;
    constexpr static float d_Pt_Ave220HF_cut  = 239;
    constexpr static float d_Pt_Ave300HF_cut = 318;
    
    double trg_thresh[9] = {
      d_Pt_Ave40_cut,
      d_Pt_Ave60_cut,
      d_Pt_Ave80_cut,
      d_Pt_Ave140_cut,
      d_Pt_Ave200_cut,
      d_Pt_Ave260_cut,
      d_Pt_Ave320_cut,
      d_Pt_Ave400_cut,
      d_Pt_Ave500_cut
    };

    double trgHF_thresh[6] = {d_Pt_Ave60HF_cut,d_Pt_Ave80HF_cut,d_Pt_Ave100HF_cut,d_Pt_Ave160HF_cut,d_Pt_Ave220HF_cut,d_Pt_Ave300HF_cut};

    const double eta_cut = 2.853;
    bool eta_cut_bool = abs(probejet_eta) <  eta_cut;     
    bool eta_cut_bool_HF = abs(probejet_eta) >=  eta_cut;
    std::vector<bool> pass_trigger_list;
    pass_trigger40 = (trigger40_sel->passes(event) && pt_ave>trg_thresh[0]   && pt_ave<trg_thresh[1] && (eta_cut_bool));
    pass_trigger60 = (trigger60_sel->passes(event) && pt_ave>trg_thresh[1]   && pt_ave<trg_thresh[2] &&  (eta_cut_bool));
    pass_trigger80 = (trigger80_sel->passes(event) && pt_ave>trg_thresh[2]   && pt_ave<trg_thresh[3]&& (eta_cut_bool)); 
    pass_trigger140 = (trigger140_sel->passes(event) && pt_ave>trg_thresh[3] && pt_ave<trg_thresh[4]&& (eta_cut_bool)); 
    pass_trigger200 = (trigger200_sel->passes(event) && pt_ave>trg_thresh[4] && pt_ave<trg_thresh[5]&& (eta_cut_bool)); 
    pass_trigger260 = (trigger260_sel->passes(event) && pt_ave>trg_thresh[5] && pt_ave<trg_thresh[6]&& (eta_cut_bool));
    pass_trigger320 = (trigger320_sel->passes(event) && pt_ave>trg_thresh[6] && pt_ave<trg_thresh[7]&& (eta_cut_bool));
    pass_trigger400 = (trigger400_sel->passes(event) && pt_ave>trg_thresh[7] && pt_ave<trg_thresh[8]&& (eta_cut_bool));
    pass_trigger500 = (trigger500_sel->passes(event) && pt_ave>trg_thresh[8] && (eta_cut_bool));
      
    //FWD Trigger
    pass_trigger60_HFJEC = (trigger60_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[0]   && pt_ave<trgHF_thresh[1] && eta_cut_bool_HF);
    pass_trigger80_HFJEC = (trigger80_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[1]   && pt_ave<trgHF_thresh[2] && eta_cut_bool_HF);
    pass_trigger100_HFJEC = (trigger100_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[2] && pt_ave<trgHF_thresh[3] && eta_cut_bool_HF);
    pass_trigger160_HFJEC = (trigger160_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[3] && pt_ave<trgHF_thresh[4] && eta_cut_bool_HF);
    pass_trigger220_HFJEC = (trigger220_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[4] && pt_ave<trgHF_thresh[5] && eta_cut_bool_HF);
    pass_trigger300_HFJEC = (trigger300_HFJEC_sel->passes(event) && pt_ave>trgHF_thresh[5] && eta_cut_bool_HF); 


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


    // pass_trigger40 = (trigger40_sel->passes(event));
    // pass_trigger60 = (trigger60_sel->passes(event));
    // pass_trigger80 = (trigger80_sel->passes(event)); 
    // pass_trigger140 = (trigger140_sel->passes(event));
    // pass_trigger200 = (trigger200_sel->passes(event));
    // pass_trigger260 = (trigger260_sel->passes(event)); 
    // pass_trigger320 = (trigger320_sel->passes(event));
    // pass_trigger400 = (trigger400_sel->passes(event));
    // pass_trigger500 = (trigger500_sel->passes(event));
    // pass_trigger60_HFJEC = (trigger60_HFJEC_sel->passes(event));
    // pass_trigger80_HFJEC = (trigger80_HFJEC_sel->passes(event));
    // pass_trigger100_HFJEC = (trigger100_HFJEC_sel->passes(event));
    // pass_trigger160_HFJEC = (trigger160_HFJEC_sel->passes(event));
    // pass_trigger220_HFJEC = (trigger220_HFJEC_sel->passes(event));
    // pass_trigger300_HFJEC = (trigger300_HFJEC_sel->passes(event));

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

    // event.weight *= prescale_total;
    // event.weight *= prescale_total_L1;

    //7. Fill hists
    h_trigger->fill(event);
    h_trigger_L2Res->fill(event);
    //    ((std::unique_ptr<TriggerStudiesHLTmatchL1Hists>) h_trigger_HLT)->set_tr_list(pass_trigger_list);
    //    ((TriggerStudiesHLTmatchL1Hists*) h_trigger_HLT)->set_tr_list(pass_trigger_list);
    // h_trigger_HLT->set_tr_list(pass_trigger_list);
    // h_trigger_HLT->fill(event); 
    if(L1GT_BX_0){
      h_trigger_BX0->fill(event);
      h_trigger_L2Res_BX0->fill(event);
    }
    if(L1GT_BX_minus1){
      h_trigger_BXm1->fill(event);
      h_trigger_L2Res_BXm1->fill(event);
    }
    if(L1GT_BX_plus1){
      h_trigger_BXp1->fill(event);
      h_trigger_L2Res_BXp1->fill(event);
    }

    //8.Fill hist for probe in the barrel, probe in EC and probe in HF
    //BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2
   
    if(probejet_eta<=s_eta_barr){
	h_trigger_BB->fill(event);
	h_trigger_L2Res_BB->fill(event);
	// h_trigger_HLT_BB->set_tr_list(pass_trigger_list);
	// h_trigger_HLT_BB->fill(event); 

      if(L1GT_BX_0){
	h_trigger_BX0_BB->fill(event);
	h_trigger_L2Res_BX0_BB->fill(event);
      }
      if(L1GT_BX_minus1){
	h_trigger_BXm1_BB->fill(event);
	h_trigger_L2Res_BXm1_BB->fill(event);
      }
      if(L1GT_BX_plus1){
	h_trigger_BXp1_BB->fill(event);
	h_trigger_L2Res_BXp1_BB->fill(event);
      }
    }

    if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trigger_EC1->fill(event);
	h_trigger_L2Res_EC1->fill(event);
	// h_trigger_HLT_EC1->set_tr_list(pass_trigger_list);
	// h_trigger_HLT_EC1->fill(event); 

      if(L1GT_BX_0){
	h_trigger_BX0_EC1->fill(event);
	h_trigger_L2Res_BX0_EC1->fill(event);
      }
      if(L1GT_BX_minus1){
	h_trigger_BXm1_EC1->fill(event);
	h_trigger_L2Res_BXm1_EC1->fill(event);
      }
      if(L1GT_BX_plus1){
	h_trigger_BXp1_EC1->fill(event);
	h_trigger_L2Res_BXp1_EC1->fill(event);
      }
    }
    if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trigger_EC2->fill(event);
	h_trigger_L2Res_EC2->fill(event);
	// h_trigger_HLT_EC2->set_tr_list(pass_trigger_list);
	// h_trigger_HLT_EC2->fill(event); 

      if(L1GT_BX_0){
	h_trigger_BX0_EC2->fill(event);
	h_trigger_L2Res_BX0_EC2->fill(event);
      }
      if(L1GT_BX_minus1){
	h_trigger_BXm1_EC2->fill(event);
	h_trigger_L2Res_BXm1_EC2->fill(event);
      }
      if(L1GT_BX_plus1){
	h_trigger_BXp1_EC2->fill(event);
	h_trigger_L2Res_BXp1_EC2->fill(event);
      }
    }
    if(probejet_eta>=3.0){
	h_trigger_HF->fill(event);
	h_trigger_L2Res_HF->fill(event);
	// h_trigger_HLT_HF->set_tr_list(pass_trigger_list);
	// h_trigger_HLT_HF->fill(event); 

      if(L1GT_BX_0){
	h_trigger_BX0_HF->fill(event);
	h_trigger_L2Res_BX0_HF->fill(event);
      }
      if(L1GT_BX_minus1){
	h_trigger_BXm1_HF->fill(event);
	h_trigger_L2Res_BXm1_HF->fill(event);
      }
      if(L1GT_BX_plus1){
	h_trigger_BXp1_HF->fill(event);
	h_trigger_L2Res_BXp1_HF->fill(event);
      }
    }



    //7. Fill hists for each trigger path
    if(pass_trigger40) {
      h_trg40->fill(event); h_trg40_L2Res->fill(event); h_trg40_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trg40_L2Res_BB->fill(event);
	h_trg40_MultMatch_BB->fill(event);
      } 
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trg40_L2Res_EC1->fill(event); 
	h_trg40_MultMatch_EC1->fill(event); 
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trg40_L2Res_EC2->fill(event); 
	h_trg40_MultMatch_EC2->fill(event); 
      }
      if(probejet_eta>=3.0){
	h_trg40_L2Res_HF->fill(event); 
	h_trg40_MultMatch_HF->fill(event); 
      }
    }
    if(pass_trigger60) {
      h_trg60->fill(event); h_trg60_L2Res->fill(event); h_trg60_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trg60_L2Res_BB->fill(event);
	h_trg60_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trg60_L2Res_EC1->fill(event);
	h_trg60_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trg60_L2Res_EC2->fill(event);
	h_trg60_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trg60_L2Res_HF->fill(event);
	h_trg60_MultMatch_HF->fill(event);
      }

    } 
    if(pass_trigger80) {
      h_trg80->fill(event); h_trg80_L2Res->fill(event); h_trg80_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trg80_L2Res_BB->fill(event);
	h_trg80_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trg80_L2Res_EC1->fill(event);
	h_trg80_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trg80_L2Res_EC2->fill(event);
	h_trg80_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trg80_L2Res_HF->fill(event);
	h_trg80_MultMatch_HF->fill(event);
      }
}
    if(pass_trigger140) {
      h_trg140->fill(event); h_trg140_L2Res->fill(event); h_trg140_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trg140_L2Res_BB->fill(event);
	h_trg140_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trg140_L2Res_EC1->fill(event);
	h_trg140_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trg140_L2Res_EC2->fill(event);
	h_trg140_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trg140_L2Res_HF->fill(event);
	h_trg140_MultMatch_HF->fill(event);
      }

}
    if(pass_trigger200) {
      h_trg200->fill(event); h_trg200_L2Res->fill(event); h_trg200_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trg200_L2Res_BB->fill(event);
	h_trg200_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trg200_L2Res_EC1->fill(event);
	h_trg200_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trg200_L2Res_EC2->fill(event);
	h_trg200_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trg200_L2Res_HF->fill(event);
	h_trg200_MultMatch_HF->fill(event);
      }

}
    if(pass_trigger260) {
      h_trg260->fill(event); h_trg260_L2Res->fill(event); h_trg260_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trg260_L2Res_BB->fill(event);
	h_trg260_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trg260_L2Res_EC1->fill(event);
	h_trg260_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trg260_L2Res_EC2->fill(event);
	h_trg260_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trg260_L2Res_HF->fill(event);
	h_trg260_MultMatch_HF->fill(event);
      }

}
    if(pass_trigger320) {
      h_trg320->fill(event); h_trg320_L2Res->fill(event); h_trg320_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trg320_L2Res_BB->fill(event);
	h_trg320_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trg320_L2Res_EC1->fill(event);
	h_trg320_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trg320_L2Res_EC2->fill(event);
	h_trg320_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trg320_L2Res_HF->fill(event);
	h_trg320_MultMatch_HF->fill(event);
      }

} 
    if(pass_trigger400) {
      h_trg400->fill(event); h_trg400_L2Res->fill(event); h_trg400_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trg400_L2Res_BB->fill(event);
	h_trg400_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trg400_L2Res_EC1->fill(event);
	h_trg400_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trg400_L2Res_EC2->fill(event);
	h_trg400_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trg400_L2Res_HF->fill(event);
	h_trg400_MultMatch_HF->fill(event);
      }

}
    if(pass_trigger500) {
      h_trg500->fill(event); h_trg500_L2Res->fill(event); h_trg500_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trg500_L2Res_BB->fill(event);
	h_trg500_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trg500_L2Res_EC1->fill(event);
	h_trg500_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trg500_L2Res_EC2->fill(event);
	h_trg500_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trg500_L2Res_HF->fill(event);
	h_trg500_MultMatch_HF->fill(event);
      }

    }
    if(pass_trigger60_HFJEC) {
      h_trgHF60->fill(event); h_trgHF60_L2Res->fill(event); h_trgHF60_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trgHF60_L2Res_BB->fill(event);
	h_trgHF60_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trgHF60_L2Res_EC1->fill(event);
	h_trgHF60_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trgHF60_L2Res_EC2->fill(event);
	h_trgHF60_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trgHF60_L2Res_HF->fill(event);
	h_trgHF60_MultMatch_HF->fill(event);
      }
}  
    if(pass_trigger80_HFJEC) {
      h_trgHF80->fill(event); h_trgHF80_L2Res->fill(event); h_trgHF80_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trgHF80_L2Res_BB->fill(event);
	h_trgHF80_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trgHF80_L2Res_EC1->fill(event);
	h_trgHF80_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trgHF80_L2Res_EC2->fill(event);
	h_trgHF80_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trgHF80_L2Res_HF->fill(event);
	h_trgHF80_MultMatch_HF->fill(event);
      }
}
    if(pass_trigger100_HFJEC) {
      h_trgHF100->fill(event); h_trgHF100_L2Res->fill(event); h_trgHF100_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trgHF100_L2Res_BB->fill(event);
	h_trgHF100_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
      h_trgHF100_L2Res_EC1->fill(event);
      h_trgHF100_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trgHF100_L2Res_EC2->fill(event);
	h_trgHF100_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trgHF100_L2Res_HF->fill(event);
	h_trgHF100_MultMatch_HF->fill(event);
      }
}
    if(pass_trigger160_HFJEC) {
      h_trgHF160->fill(event); h_trgHF160_L2Res->fill(event); h_trgHF160_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trgHF160_L2Res_BB->fill(event);
	h_trgHF160_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trgHF160_L2Res_EC1->fill(event);
	h_trgHF160_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trgHF160_L2Res_EC2->fill(event);
	h_trgHF160_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trgHF160_L2Res_HF->fill(event);
	h_trgHF160_MultMatch_HF->fill(event);
      }

}
    if(pass_trigger220_HFJEC) {
      h_trgHF220->fill(event); h_trgHF220_L2Res->fill(event); h_trgHF220_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trgHF220_L2Res_BB->fill(event);
	h_trgHF220_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trgHF220_L2Res_EC1->fill(event);
	h_trgHF220_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trgHF220_L2Res_EC2->fill(event);
	h_trgHF220_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trgHF220_L2Res_HF->fill(event);
	h_trgHF220_MultMatch_HF->fill(event);
      }

}
    if(pass_trigger300_HFJEC) {
      h_trgHF300->fill(event); h_trgHF300_L2Res->fill(event); h_trgHF300_MultMatch->fill(event);
      if(probejet_eta<=s_eta_barr){
	h_trgHF300_L2Res_BB->fill(event);
	h_trgHF300_MultMatch_BB->fill(event);
      }
      if(probejet_eta>s_eta_barr && probejet_eta<2.5){
	h_trgHF300_L2Res_EC1->fill(event);
	h_trgHF300_MultMatch_EC1->fill(event);
      }
      if(probejet_eta>=2.5 && probejet_eta<3.0){
	h_trgHF300_L2Res_EC2->fill(event);
	h_trgHF300_MultMatch_EC2->fill(event);
      }
      if(probejet_eta>=3.0){
	h_trgHF300_L2Res_HF->fill(event);
	h_trgHF300_MultMatch_HF->fill(event);
      }

}
 
    return true;  
}

// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the TriggerStudiesModule is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(TriggerStudiesModule)

}
