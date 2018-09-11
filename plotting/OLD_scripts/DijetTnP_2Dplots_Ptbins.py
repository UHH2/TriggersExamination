#Plot 2D distibution from dijet Tag&Probe (L2Res) prefire study data:
#28.07.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy


import numpy as np

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_triggerThresholds_wL1Prescales_wHLTandL1matching_2DetaphiCleaning_wL1min_rebin_ptbins_addR0dRm1_adddPt0dPtm1/uhh2.AnalysisModuleRunner.DATA.Run2017D.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_DijetTriggers//uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_DijetTriggers//uhh2.AnalysisModuleRunner.DATA.Run2017D.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers/uhh2.AnalysisModuleRunner.DATA.Run2017E.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers/uhh2.AnalysisModuleRunner.DATA.Run2017D.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers/uhh2.AnalysisModuleRunner.DATA.Run2017C.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers/uhh2.AnalysisModuleRunner.DATA.Run2017B.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd/uhh2.AnalysisModuleRunner.DATA.Run2017B.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd/uhh2.AnalysisModuleRunner.DATA.Run2017C.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd/uhh2.AnalysisModuleRunner.DATA.Run2017D.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd/uhh2.AnalysisModuleRunner.DATA.Run2017E.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd_patJetsAK4PFCHS/uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')

fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd_patJetsAK4PFCHS_addMultMatch/uhh2.AnalysisModuleRunner.DATA.Run2017F.root')


distrs=['L1J_drJetProbeMin_dR0dRm1','L1J_drJetProbeMin_dPt0dPtm1','L1J_drJetProbeMin_dPt0dPtp1', 'L1J_drJetProbeMin_dR0dRp1', 'L1J_drJetProbeMin_dPt0dPtm1SUM',
        'L1J_drJetProbeMin_L1EtaL1Phi',
        'L1J_drJetProbeMin_diffL1EtaL1Phi', 'L1J_drJetProbeMin_diffL1EtaL1Phi_bx0','L1J_drJetProbeMin_diffL1EtaL1Phi_bxPlus1','L1J_drJetProbeMin_diffL1EtaL1Phi_bxMinus1',
        'L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt','L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt_bx0','L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt_bxPlus1','L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt_bxMinus1',
        'L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt','L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt_bx0','L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt_bxMinus1'
        ] #distirbution to plot

dirs={'L1Jet in ALL':''} #directories with different L1GT BX
#dirs={'L1Jet in BX 0':'_bx0','L1Jet in BX +1':'_bxPlus1','L1Jet in BX -1':'_bxMinus1'} #directories with different L1GT BX

#dirs={'L1EG in BX 0':'_bx0','L1EG in BX +1':'_bxPlus1','L1EG in BX -1':'_bxMinus1'} #directories with different L1GT BX
regions={'BB':'_BB','EC1':'_EC1','EC2':'_EC2','HF':'_HF','':''} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
#regions={'BB':'_BB','EC1':'_EC1','EC2':'_EC2','HF':'_HF'} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
#regions={'EC2':'_EC2'} 
#regions={'HF':'_HF'} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
#regions={'BB':'_BB'} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined

#Dijet
# ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140',
# 'pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320',
# 'pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500',                                                          
# }
#ptbins={'pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 'pt#in[239,318]':'Trigger220HF','pt#in[318,#infty]':'Trigger300HF'}                                                                                                                                     

# ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140',
# 'pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320',
# 'pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500','pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 'pt#in[239,318]':'Trigger220HF','pt#in[318,#infty]':'Trigger300HF'                                                          
# }
# if len(ptbins)<7:                                                                                                                                                     
#     regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
#                     'EC2':'2.8<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}                                                                                                                                                     
# else:                 
#     regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
#                     'EC2':'2.5<|probe jet #eta|<2.8','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}    


#SingleJet
ptbins={'pt#in[72,95]':'Trigger40','pt#in[95,160]':'Trigger60','pt#in[160,226]':'Trigger80','pt#in[226,283]':'Trigger140',
'pt#in[283,344]':'Trigger200','pt#in[344,443]':'Trigger260','pt#in[443,577]':'Trigger320',
'pt#in[577,606]':'Trigger400','pt#in[606,#infty]':'Trigger500',                                                          
}
# # #central
regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
                'EC2':'2.5<|probe jet #eta|<2.8','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}    

# ptbins={'pt#in[72,95]':'Trigger40HF','pt#in[95,160]':'Trigger60HF','pt#in[160,226]':'Trigger80HF','pt#in[226,283]':'Trigger140HF',
# 'pt#in[283,344]':'Trigger200HF','pt#in[344,443]':'Trigger260HF','pt#in[443,577]':'Trigger320HF',
# 'pt#in[577,606]':'Trigger400HF','pt#in[606,#infty]':'Trigger500HF',                                                          
# }
# #forward                                                       
# regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
#                 'EC2':'2.8<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}                                                       



# ptbins_xaxis={'Trigger40':62,'Trigger60':85,'Trigger80':138,'Trigger140':243,'Trigger200':339,'Trigger260':402,'Trigger320':477,'Trigger400':585,'Trigger500':825,
# 'Trigger60HF':83,'Trigger80HF':103,'Trigger100HF':145,'Trigger160HF':208, 'Trigger220HF':279, 'Trigger300HF':659,
# }                                                                                                                                                                     


                                                                                                                                                                     


#regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5','EC2':'2.5<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}
MarkerColor={'L1Jet in BX 0':kBlack,'L1Jet in BX -1':kRed,'L1Jet in BX +1':kBlue}

# eta_bins = np.array([0.0,1.3,2.5,2.8,5.2],dtype='float64')
# etabins_yaxis={'BB':1.0,'EC1':2.0,'EC2':2.7,'HF':4.0} #central
# pt_bins=np.array([72,95,160,226,283,344,443,577,606,700],dtype='float64')
# ptbins_xaxis={'Trigger40':80,'Trigger60':100,'Trigger80':170,'Trigger140':250,'Trigger200':300,'Trigger260':350,'Trigger320':500,'Trigger400':585,'Trigger500':660}

# ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140','pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320','pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500',
# 'pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 'pt#in[239,318]':'Trigger220HF', 'pt#in[318,#infty]':'Trigger300HF',
# }
#ptbins={'pt#in[51,73]':'Trigger40'}

hists = {}
canvas_dist = {}
summary_hist = {}
gROOT.SetBatch(True)
for dist_ in distrs:
    for ptbin in ptbins:
        for key_region in regions:
            for key_dir_ in dirs:
                canvas_dist[dist_+key_region+ptbin+key_dir_] = TCanvas(dist_+key_region+ptbin+key_dir_,dist_+key_region+ptbin+key_dir_,100,100,800,600)
         #       print pt_bins
 #               summary_hist[dist_] = TH2D('h'+dist_,dist_,len(pt_bins)-1,pt_bins,len(eta_bins)-1,eta_bins)
#                summary_hist[dist_] = TH2D('h'+dist_,dist_,10,0,10,4,0,5.2)
                legend = TLegend(.30,.85,.85,.99) 
                gStyle.SetOptStat(0)
                gStyle.SetOptTitle(0)
                gStyle.SetLabelSize(0.08,"XY")
                gStyle.SetTitleSize(0.08,"XY")
                gStyle.SetTitleOffset(1.11,"Y")
                gStyle.SetLabelOffset(0.01,"Y")
                legend.SetHeader(regions_legend[key_region]+', '+ptbin,"C")
                legend.SetTextSize(0.05)
#                print ptbins[ptbin]+'_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_]
                hists[key_dir_+dist_+key_region+ptbin] = fin.Get(ptbins[ptbin]+'_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_])
#                hists[key_dir_+dist_+key_region+ptbin].SetMarkerColor(MarkerColor[key_dir_])
#                hists[key_dir_+dist_+key_region+ptbin].SetMarkerStyle(21)
#                hists[key_dir_+dist_+key_region+ptbin].SetMarkerSize(1.5)
      #          legend.AddEntry(hists[key_dir_+dist_+key_region+ptbin],key_dir_,"lp")
                hists[key_dir_+dist_+key_region+ptbin].Draw('colz')
                Tl = TLatex()
                Tl.SetTextAlign(12)
                Tl.SetTextSize(0.045)
                text = TString("matched to both ")
                fraction = 0
                if(hists[key_dir_+dist_+key_region+ptbin].Integral(0,30,0,30)>0):
                    fraction = 100.0*(hists[key_dir_+dist_+key_region+ptbin].Integral(2,30,2,30)/hists[key_dir_+dist_+key_region+ptbin].Integral(0,30,0,30))
                    r_fraction = '{0:.1f}'.format(fraction)
                    print "fraction:", r_fraction
                    text += r_fraction
                else:                
                    text += "0"
                text +=" %"
                if(dist_ == 'L1J_drJetProbeMin_dR0dRm1' or dist_ == 'L1J_drJetProbeMin_dR0dRp1'):
                    Tl.DrawLatex(-0.05,-0.05,text.Data())
                #     hists['L1Jet in BX -1'+dist_+key_region+ptbin].GetYaxis().SetRangeUser(1e-1,100.0*hists['L1Jet in BX -1'+dist_+key_region+ptbin].GetMaximum()) #L1Jet
                #     canvas_dist[dist_+key_region+ptbin].SetLogy()
                legend.Draw()
#                print str(dirs[key_dir_])#, ptbins_xaxis[dirs[key_dir_]]
                canvas_dist[dist_+key_region+ptbin+key_dir_].SaveAs(dist_+regions[key_region]+'_'+ptbins[ptbin]+''+dirs[key_dir_]+'.pdf')
              #   summary_hist[dist_].Fill(ptbins_xaxis[ptbins[ptbin]],etabins_yaxis[key_region],fraction)
    # canvas_dist[dist_] = TCanvas(dist_,dist_,100,100,800,600)
    # summary_hist[dist_].Draw('colz')
    # canvas_dist[dist_].SaveAs('Summary_'+dist_+'.pdf')
#                print "Input:", etabins_yaxis[regions[key_region]]
 


