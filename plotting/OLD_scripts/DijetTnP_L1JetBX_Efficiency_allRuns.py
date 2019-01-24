#Plot dijet Tag&Probe (L2Res) efficiency distributions in -1,0,+1 BX overlaid for all runs on the same plot
#data: 17.06.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy

# path = '/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2016_UnprefireableFilterON_DijetTriggers_addL1JetEtaPhi_patJetsAK4PFCHS_addMultMatch_L1L2L3/'
# files ={'Run2016B':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2016B.root', 'open'),
#         'Run2016C':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2016C.root', 'open'),
#         'Run2016D':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2016D.root', 'open'),
#         'Run2016E':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2016E.root', 'open'),
#         'Run2016F':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2016F.root', 'open'),
#         'Run2016G':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2016G.root', 'open'),
#         'Run2016H':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2016H.root', 'open'),
#         }

path = '/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017_UnprefireableFilterON_SingleJetTriggers_addFwd_patJetsAK4PFCHS_addMultMatch/'
files ={'Run2017B':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2017B.root', 'open'),
        'Run2017C':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2017C.root', 'open'),
        'Run2017D':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2017D.root', 'open'),
        'Run2017E':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2017E.root', 'open'),
        'Run2017F':TFile(path+'/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open'),
}


# distrs=['L1J_drJetProbeMin_mpfResponse','L1J_drJetProbeMin_pBalResponse','L1J_drJetProbeMin_pBalAsymmetry','L1J_drJetProbeMin_mpfAsymmetry',
#         'L1J_drJetProbeMin_dR', 
#         'L1J_drJetProbeMin_Pt',
#         'L1J_drJetProbeMin_Ptave',
#         'L1J_drJetProbeMin_neuEMfracProbe', 'L1J_drJetProbeMin_chEMfracProbe', 'L1J_drJetProbeMin_neuHADfracProbe','L1J_drJetProbeMin_chHADfracProbe',
#         'L1J_drJetTagMin_dR','L1J_drJetProbeMin_dR', 'L1J_drJetProbeMin_EtaProbe',
#         'L1J_drJetProbeMin_PtProbe',
#         ] #distirbution to plot

distrs=['L1J_drJetProbeMin_EtaProbe','L1J_drJetProbeMin_PtProbe','L1J_drJetProbeMin_NPV',
        ] #distirbution to plot


#     'L1J_drJetProbeMin_BX','L1EG_drJetProbeMin_BX',
#distrs=['L1J_drJetProbeMin_Pt','L1J_drJetProbeMin_Ptave']
dirs={'L1Jet in BX 0':'_bx0','L1Jet in BX +1':'_bxPlus1','L1Jet in BX -1':'_bxMinus1'} #directories with different L1GT BX
#dirs={'L1EG in BX 0':'_bx0','L1EG in BX +1':'_bxPlus1','L1EG in BX -1':'_bxMinus1'} #directories with different L1GT BX
#regions={'BB':'_BB','EC1':'_EC1','EC2':'_EC2','HF':'_HF','':''} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
regions={'':''}
regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5','EC2':'2.5<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}
MarkerColor={'L1Jet in BX 0':kBlack,'L1Jet in BX -1':kRed,'L1Jet in BX +1':kBlue, 
             'Run2016B':kRed-9,'Run2016C':kRed-7, 'Run2016D':kRed,'Run2016E':kBlue,'Run2016F':kBlue+2,'Run2016G':kGreen+1,'Run2016H':kGreen+4,
             'Run2017B':kRed-9,'Run2017C':kRed-7, 'Run2017D':kRed,'Run2017E':kBlue,'Run2017F':kBlue+2
}

#MarkerColor={'L1EG in BX 0':kBlack,'L1EG in BX -1':kRed,'L1EG in BX +1':kBlue}

hists = {}
canvas_dist = {}
gROOT.SetBatch(True)
for dist_ in distrs:
    for key_region in regions:
        print 'Trigger_L2Res'+regions[key_region]+'/'+dist_
        for key_dir_ in dirs:
            canvas_dist[dist_+key_region+key_dir_] = TCanvas(dist_+key_region+key_dir_,dist_+key_region+key_dir_,800,600)
            legend = TLegend(.70,.70,.99,.99) 
            gStyle.SetOptStat(0)
            gStyle.SetOptTitle(0)
#        legend.SetHeader(regions_legend[key_region],"C")
#        legend.SetHeader('',"C")

            for fin_key in sorted(files):
                fin = files[fin_key]
                hists[dist_+key_region+fin_key] = fin.Get('Trigger_L2Res'+regions[key_region]+'/'+dist_)
                print 'Trigger_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_]
                hists[key_dir_+dist_+key_region+fin_key] = fin.Get('Trigger_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_])
                hists[key_dir_+dist_+key_region+fin_key].SetMarkerColor(MarkerColor[fin_key])
                hists[key_dir_+dist_+key_region+fin_key].SetMarkerStyle(21)
                hists[key_dir_+dist_+key_region+fin_key].SetMarkerSize(1.2)
                legend.AddEntry(hists[key_dir_+dist_+key_region+fin_key],fin_key,"lp")
                hists[key_dir_+dist_+key_region+fin_key].Print()
                hists[dist_+key_region+fin_key].Print()
                hists[key_dir_+dist_+key_region+fin_key].Divide(hists[dist_+key_region+fin_key])
                hists[key_dir_+dist_+key_region+fin_key].GetYaxis().SetRangeUser(0.0,1.4) #L1Jet
                hists[key_dir_+dist_+key_region+fin_key].GetYaxis().SetTitle(key_dir_+' efficiency') #L1Je
                hists[key_dir_+dist_+key_region+fin_key].Draw('EP same')
            legend.Draw()
            canvas_dist[dist_+key_region+key_dir_].SaveAs('Eff_'+dist_+regions[key_region]+dirs[key_dir_]+'_allRuns.pdf')
#            canvas_dist[dist_+key_region].SaveAs('Eff_'+dist_+regions[key_region]+'_allRuns.root')
