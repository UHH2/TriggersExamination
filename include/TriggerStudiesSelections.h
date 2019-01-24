#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/core/include/AnalysisModule.h"

#include "TTree.h"

namespace uhh2examples {
    
/* Select events with at least two jets in which the leading two jets have deltaphi > 2.7 and the third jet pt is
 * below 20% of the average of the leading two jets, where the minimum deltaphi and
 * maximum third jet pt fraction can be changed in the constructor.
 * The jets are assumed to be sorted in pt.
 */
class DijetSelection: public uhh2::Selection {
public:
    DijetSelection(float dphi_min = 2.7f, float third_frac_max = 0.2f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float dphi_min, third_frac_max;
};

struct run_lumi_ev {
  int run;
  int lumiblock;
  long long event;
};

class EventFilter: public uhh2::Selection {
 public:
  explicit EventFilter(uhh2::Context & ctx);

  virtual bool passes(const uhh2::Event &event);
  bool EtaPhiCleaning(uhh2::Event& evt);

 private:
  //TTree *filtered_tree; 
  //list of good events
  std::vector<run_lumi_ev> rlsev;
  TH2D* h_map;

};
}
