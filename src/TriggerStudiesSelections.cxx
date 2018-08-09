#include "UHH2/TriggersExamination/include/TriggerStudiesSelections.h"
#include "UHH2/core/include/Event.h"
#include "Riostream.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2.h"

#include <stdexcept>

using namespace uhh2examples;
using namespace uhh2;
using namespace std;

DijetSelection::DijetSelection(float dphi_min_, float third_frac_max_): dphi_min(dphi_min_), third_frac_max(third_frac_max_){}
    
bool DijetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    if(event.jets->size() < 2) return false;
    const auto & jet0 = event.jets->at(0);
    const auto & jet1 = event.jets->at(1);
    const float s_eta_barr = 1.3;
    if ((fabs(jet0.eta())>s_eta_barr)&&(fabs(jet1.eta())>s_eta_barr)) return false;

    auto dphi = deltaPhi(jet0, jet1);
    if(dphi < dphi_min) return false;
    if(event.jets->size() == 2) return true;
    const auto & jet3 = event.jets->at(2);
    auto third_jet_frac = jet3.pt() / (0.5 * (jet0.pt() + jet1.pt()));
    return third_jet_frac < third_frac_max;
}


EventFilter::EventFilter(uhh2::Context & ctx)
{
  auto dataset_type = ctx.get("dataset_type");
  bool is_mc = dataset_type == "MC";
  if(is_mc){
    cout << "Warning: EventFilter will not have an effect on this MC sample (dataset_type = '" + dataset_type + "')" << endl;
    return;
  }

  TString FilteredEvents     = ctx.get("filtered_events");
  if(FilteredEvents == ""){
    throw runtime_error("FilteredEvents: filtered_events is needed!");
  }
  TFile file_FilteredEvents(FilteredEvents);
  TTree * filtered_tree = dynamic_cast<TTree*>(file_FilteredEvents.Get("tree"));
  // fetch branches we need
  TBranch * brun = filtered_tree->GetBranch("run");
  TBranch * blumiblock = filtered_tree->GetBranch("lumi");
  TBranch * beventid = filtered_tree->GetBranch("event");
  run_lumi_ev rle;
  brun->SetAddress(&rle.run);
  blumiblock->SetAddress(&rle.lumiblock);
  beventid->SetAddress(&rle.event);

 auto ientries = filtered_tree->GetEntries();
 for(auto ientry = 0l; ientry < ientries; ientry++){
   for(auto b : {brun, blumiblock, beventid}){
      b->GetEntry(ientry);
    }
    rlsev.push_back(rle);
  }
 TString Cut_Dir = "/nfs/dust/cms/user/karavdia/CMSSW_9_4_3/src/UHH2/TriggersExamination/data/";
 TFile* cut_map = new TFile(Cut_Dir+"hotjets-17runBCDEF.root","READ");
 h_map = (TH2D*) cut_map->Get("h2hotfilter");
 h_map->SetDirectory(0);
 cut_map->Close();

}

bool EventFilter::passes(const uhh2::Event &event){
  // int ev_run = event.run;
  // int ev_lumi = event.luminosityBlock;
  // long long ev_evid = event.event;
  // std::cout<<"run:lumi:event = "<<ev_run<<" "<<ev_lumi<<" "<<ev_evid<<std::endl;

  for(size_t i=0; i< rlsev.size(); i++){
    if(rlsev[i].run==event.run && rlsev[i].lumiblock==event.luminosityBlock && rlsev[i].event == event.event){
      std::cout<<"run:lumi:event = "<<event.run<<" "<<event.luminosityBlock<<" "<<event.event<<std::endl;
      return true;
    }
  }
  return false;
}

bool EventFilter::EtaPhiCleaning(uhh2::Event& evt)
{
  //  assert(evt);

  int n_bins_x = h_map->GetNbinsX();
  int n_bins_y = h_map->GetNbinsY();


  double xMin = h_map->GetXaxis()->GetXmin();
  double xWidth = h_map->GetXaxis()->GetBinWidth(1);

 
  double yMin = h_map->GetYaxis()->GetXmin();
  double yWidth = h_map->GetYaxis()->GetBinWidth(1);
  double cutValue=0;

  const int njets = evt.jets->size();
 
  for(int i=0; i < njets; i++){
    int idx_x = 0;
    int idx_y = 0;
    Jet jet = evt.jets->at(i);// loop over all jets in evt
 
    while(jet.eta() > xMin+xWidth + idx_x * xWidth) idx_x++;
    while(jet.phi() > yMin+yWidth + idx_y * yWidth) idx_y++;

    cutValue = h_map->GetBinContent(idx_x+1, idx_y+1);

    if(cutValue > 0) break;
        
     
  }

  if(cutValue > 0) return false;
 
  return true;
}
