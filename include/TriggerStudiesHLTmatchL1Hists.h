#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/FlavorParticle.h"
namespace uhh2examples {

/**  \brief Example class for booking and filling histograms
 * 
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class TriggerStudiesHLTmatchL1Hists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    TriggerStudiesHLTmatchL1Hists(uhh2::Context & ctx, const std::string & dirname);

    //    void fill(const uhh2::Event & ev, std::vector<bool> & tr_list);
    virtual void fill(const uhh2::Event & ev) override;
    virtual ~TriggerStudiesHLTmatchL1Hists();
    uhh2::GenericEvent::Handle<std::vector<FlavorParticle>> handle_triggers[15]; 
    std::vector<bool> pass_trigger_list;
    void set_tr_list(std::vector<bool> pass_list);
};

}
