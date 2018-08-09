#Plot dijet Tag&Probe (L2Res) distributions in -1,0,+1 BX overlaid
#data: 17.06.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_CONDOR/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterON_CONDOR_2/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterON_triggerThresholds_CONDOR/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_triggerThresholds_CONDOR/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterON_triggerThresholds_wL1Prescales_wHLTandL1matching_2DetaphiCleaning_wL1min/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_triggerThresholds_wL1Prescales_wHLTandL1matching_2DetaphiCleaning_wL1min/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

distrs=['L1J_drJetProbeMin_mpfResponse','L1J_drJetProbeMin_pBalResponse','L1J_drJetProbeMin_pBalAsymmetry','L1J_drJetProbeMin_mpfAsymmetry',
        'pBalAsymmetry','pBalResponse','mpfAsymmetry','mpfResponse',
        'L1J_drJetProbeMin_BX','L1EG_drJetProbeMin_BX',
        'L1EG_drJetProbeMin_dR_bx0','L1J_drJetProbeMin_dR_bx0',
        'L1EG_drJetProbeMin_dR_bxMinus1','L1J_drJetProbeMin_dR_bxMinus1',
        'L1EG_drJetProbeMin_dR_bxPlus1','L1J_drJetProbeMin_dR_bxPlus1',
        ] #distirbution to plot
 
#distrs=['L1J_drJetProbeMin_Pt_bxMinus1','L1J_drJetProbeMin_Pt_bx0','L1J_drJetProbeMin_Ptave_bxMinus1','L1J_drJetProbeMin_Ptave_bx0']
#distrs=['L1J_drJetProbeMin_mpfResponse','L1EG_drJetProbeMin_mpfResponse'] #distirbution to plot
#distrs=['L1J_drJetProbeMin_BX'] #distirbution to plot
dirs={'FinOR in BX 0':'Trigger_L2Res_L1GTBX0','FinOR in BX +1':'Trigger_L2Res_L1GTBXp1','FinOR in BX -1':'Trigger_L2Res_L1GTBXm1'} #directories with different L1GT BX
#dirs={'FinOR in BX 0':'Trigger_L2Res_L1GTBX0'} #directories with different L1GT BX
regions={'BB':'_BB','EC1':'_EC1','EC2':'_EC2','HF':'_HF','':''} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5','EC2':'2.5<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}
#dirs={'L1GT in BX +1':'Trigger_L2Res_L1GTBXp1/'} #directories with different L1GT BX
MarkerColor={'FinOR in BX 0':kBlack,'FinOR in BX -1':kRed,'FinOR in BX +1':kBlue}
MarkerSize={'FinOR in BX 0':1.5,'FinOR in BX -1':1.7,'FinOR in BX +1':1.9}


hists = {}
canvas_dist = {}
for dist_ in distrs:
    for key_region in regions:
        canvas_dist[dist_+key_region] = TCanvas(dist_+key_region,dist_+key_region,800,600)
        legend = TLegend(.70,.75,.99,.99) 
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)
        legend.SetHeader(regions_legend[key_region],"C")
        for key_dir_ in dirs:
            # print key_dir_
            hists[key_dir_+dist_+key_region] = fin.Get(dirs[key_dir_]+regions[key_region]+'/'+dist_)
            hists[key_dir_+dist_+key_region].SetMarkerColor(MarkerColor[key_dir_])
            hists[key_dir_+dist_+key_region].SetMarkerStyle(20)
            hists[key_dir_+dist_+key_region].SetMarkerSize(MarkerSize[key_dir_])
            legend.AddEntry(hists[key_dir_+dist_+key_region],key_dir_,"lp")
            # hists[key_dir_+dist_+key_region].Print()
            hists[key_dir_+dist_+key_region].Draw('EP same')

#set up maximum of hists to BX=0
#        print hists['FinOR in BX 0'+dist_+key_region].GetMaximum()
        hists['FinOR in BX +1'+dist_+key_region].GetYaxis().SetRangeUser(1e-1,1.3*hists['FinOR in BX 0'+dist_+key_region].GetMaximum())
        #if dist_ == 'L1J_drJetProbeMin_mpfResponse' or dist_ == 'L1EG_drJetProbeMin_mpfResponse' or dist_ == 'L1J_drJetProbeMin_BX' or dist_ == 'L1EG_drJetProbeMin_BX':
        canvas_dist[dist_+key_region].SetLogy()
        legend.Draw()
        canvas_dist[dist_+key_region].SaveAs(dist_+regions[key_region]+'.pdf')
