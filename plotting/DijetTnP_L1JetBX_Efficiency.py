#Plot dijet Tag&Probe (L2Res) distributions in -1,0,+1 BX overlaid
#data: 17.06.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy

#fin = TFile('/nfs/dust/cms/user/karavdia/CMSSW_9_4_3/src/UHH2/TriggerStudies/plotting/uhh2.AnalysisModuleRunner.DATA.Run2017F_ALL.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_CONDOR/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterON_CONDOR_2/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterON_triggerThresholds_CONDOR/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterON_triggerThresholds_CONDOR_2/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterON_triggerThresholds_wL1Prescales/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_triggerThresholds_wL1Prescales_wHLTandL1matching/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_triggerThresholds_wL1Prescales_wHLTandL1matching_2DetaphiCleaning/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_triggerThresholds_wL1Prescales_wHLTandL1matching_2DetaphiCleaning_wL1min/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterON_triggerThresholds_wL1Prescales_wHLTandL1matching_2DetaphiCleaning_wL1min_rebin/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_triggerThresholds_wL1Prescales_wHLTandL1matching_2DetaphiCleaning_wL1min_rebin/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_DijetTriggers/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

distrs=['L1J_drJetProbeMin_mpfResponse','L1J_drJetProbeMin_pBalResponse','L1J_drJetProbeMin_pBalAsymmetry','L1J_drJetProbeMin_mpfAsymmetry',
        'L1J_drJetProbeMin_dR', 
        'L1J_drJetProbeMin_Pt',
        'L1J_drJetProbeMin_Ptave',
        'L1J_drJetProbeMin_neuEMfracProbe', 'L1J_drJetProbeMin_chEMfracProbe', 'L1J_drJetProbeMin_neuHADfracProbe','L1J_drJetProbeMin_chHADfracProbe',
        'L1J_drJetTagMin_dR','L1J_drJetProbeMin_dR', 'L1J_drJetProbeMin_EtaProbe',
        'L1J_drJetProbeMin_PtProbe',
        ] #distirbution to plot

#distrs=['L1EG_drJetProbeMin_dR','L1EG_drJetProbeMin_mpfResponse','L1EG_drJetProbeMin_pBalResponse','L1EG_drJetProbeMin_pBalAsymmetry','L1EG_drJetProbeMin_mpfAsymmetry'] #distirbution to plot


#     'L1J_drJetProbeMin_BX','L1EG_drJetProbeMin_BX',
#distrs=['L1J_drJetProbeMin_Pt','L1J_drJetProbeMin_Ptave']
dirs={'L1Jet in BX 0':'_bx0','L1Jet in BX +1':'_bxPlus1','L1Jet in BX -1':'_bxMinus1'} #directories with different L1GT BX
#dirs={'L1EG in BX 0':'_bx0','L1EG in BX +1':'_bxPlus1','L1EG in BX -1':'_bxMinus1'} #directories with different L1GT BX
regions={'BB':'_BB','EC1':'_EC1','EC2':'_EC2','HF':'_HF','':''} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5','EC2':'2.5<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}
MarkerColor={'L1Jet in BX 0':kBlack,'L1Jet in BX -1':kRed,'L1Jet in BX +1':kBlue}
#MarkerColor={'L1EG in BX 0':kBlack,'L1EG in BX -1':kRed,'L1EG in BX +1':kBlue}

hists = {}
canvas_dist = {}
for dist_ in distrs:
    for key_region in regions:
        canvas_dist[dist_+key_region] = TCanvas(dist_+key_region,dist_+key_region,800,600)
        legend = TLegend(.70,.75,.99,.99) 
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)
        legend.SetHeader(regions_legend[key_region],"C")
        print 'Trigger_L2Res'+regions[key_region]+'/'+dist_
        hists[dist_+key_region] = fin.Get('Trigger_L2Res'+regions[key_region]+'/'+dist_)
        hists[dist_+key_region].Rebin(4)
#        hists[key_dir_+dist_+key_region].Draw('EP same')

        for key_dir_ in dirs:
            # print key_dir_
            print 'Trigger_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_]
            hists[key_dir_+dist_+key_region] = fin.Get('Trigger_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_])
            hists[key_dir_+dist_+key_region].SetMarkerColor(MarkerColor[key_dir_])
            hists[key_dir_+dist_+key_region].SetMarkerStyle(21)
            hists[key_dir_+dist_+key_region].SetMarkerSize(1.5)
            legend.AddEntry(hists[key_dir_+dist_+key_region],key_dir_,"lp")
            # hists[key_dir_+dist_+key_region].Print()
            hists[key_dir_+dist_+key_region].Rebin(4)
            hists[key_dir_+dist_+key_region].Divide(hists[dist_+key_region])
            hists[key_dir_+dist_+key_region].Draw('EP same')


        hists['L1Jet in BX -1'+dist_+key_region].GetYaxis().SetRangeUser(0.0,1.2) #L1Jet
        hists['L1Jet in BX -1'+dist_+key_region].GetYaxis().SetTitle("BX=x efficiency") #L1Jet
#        canvas_dist[dist_+key_region].SetLogy()
        legend.Draw()
        canvas_dist[dist_+key_region].SaveAs('Eff_'+dist_+regions[key_region]+'.pdf')
