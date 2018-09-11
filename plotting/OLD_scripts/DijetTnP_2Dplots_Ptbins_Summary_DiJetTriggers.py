#Plot 2D distibution from dijet Tag&Probe (L2Res) prefire study data:
#28.07.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy


import numpy as np


#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_DijetTriggers//uhh2.AnalysisModuleRunner.DATA.Run2017F.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_DijetTriggers//uhh2.AnalysisModuleRunner.DATA.Run2017D.root', 'open')
fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy_JetHT2017F_UnprefireableFilterOFF_DijetTriggers//uhh2.AnalysisModuleRunner.DATA.Run2017E.root', 'open')

distrs=['L1J_drJetProbeMin_dR0dRm1','L1J_drJetProbeMin_dPt0dPtm1','L1J_drJetProbeMin_dPt0dPtp1', 'L1J_drJetProbeMin_dR0dRp1', 'L1J_drJetProbeMin_dPt0dPtm1SUM'] #distirbution to plot

#distrs=['L1J_drJetProbeMin_dR0dRm1'] #distirbution to plot


#dirs={'L1Jet in BX 0':'_bx0','L1Jet in BX +1':'_bxPlus1','L1Jet in BX -1':'_bxMinus1'} #directories with different L1GT BX
dirs={'L1Jet in ALL':''} #directories with different L1GT BX
#dirs={'L1EG in BX 0':'_bx0','L1EG in BX +1':'_bxPlus1','L1EG in BX -1':'_bxMinus1'} #directories with different L1GT BX
#regions={'BB':'_BB','EC1':'_EC1','EC2':'_EC2','HF':'_HF','':''} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
regions={'BB':'_BB','EC1':'_EC1','EC2':'_EC2','HF':'_HF'} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
#regions={'EC2':'_EC2'} 
#regions={'HF':'_HF'} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
#regions={'BB':'_BB'} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined

#Dijet
ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140',
'pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320',
'pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500',
'pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 
'pt#in[239,318]':'Trigger220HF','pt#in[318,#infty]':'Trigger300HF'                                                    
}

# ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140',
# 'pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320',
# 'pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500',                                                          
# }
#ptbins={'pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 'pt#in[239,318]':'Trigger220HF','pt#in[318,#infty]':'Trigger300HF'}                                                                                                                                     

# ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140',
# 'pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320',
# 'pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500','pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 'pt#in[239,318]':'Trigger220HF','pt#in[318,#infty]':'Trigger300HF'                                                          
# }

eta_bins = np.array([0.0,1.3,2.5,2.8,3.0,5.2],dtype='float64')
etabins_yaxis={'BB':1.0,'EC1':2.0,'EC2':2.7,'HF':4.0} #central
pt_bins=np.array([72,95,160,226,283,344,443,577,606,1000],dtype='float64')
ptbins_xaxis={'Trigger40':80,'Trigger60':100,'Trigger80':170,'Trigger140':250,'Trigger200':300,'Trigger260':350,'Trigger320':500,'Trigger400':585,'Trigger500':660,
              'Trigger60HF':80,'Trigger80HF':100,'Trigger100HF':160,'Trigger160HF':230,'Trigger220HF':300,'Trigger300HF':350}


hists = {}
canvas_dist = {}
summary_hist = {}
gROOT.SetBatch(True)
for dist_ in distrs:
    summary_hist[dist_] = TH2D('h'+dist_,dist_,len(pt_bins)-1,pt_bins,len(eta_bins)-1,eta_bins)
    for ptbin in ptbins:
        # print ptbins[ptbin]
        for key_region in regions:
            for key_dir_ in dirs:
                hists[key_dir_+dist_+key_region+ptbin] = fin.Get(ptbins[ptbin]+'_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_])
                N_ev = hists[key_dir_+dist_+key_region+ptbin].GetEntries()
                fraction = 0
                if(N_ev>100):
                    if(hists[key_dir_+dist_+key_region+ptbin].Integral(0,30,0,30)>0):
                        if(dist_=='L1J_drJetProbeMin_dPt0dPtm1' or dist_=='L1J_drJetProbeMin_dPt0dPtp1'):
                            fraction = 100.0*(hists[key_dir_+dist_+key_region+ptbin].Integral(2,30,5,30)/hists[key_dir_+dist_+key_region+ptbin].Integral(0,30,0,30))
                        else:
                            fraction = 100.0*(hists[key_dir_+dist_+key_region+ptbin].Integral(2,30,2,30)/hists[key_dir_+dist_+key_region+ptbin].Integral(0,30,0,30))
                       #     print "hists[key_dir_+dist_+key_region+ptbin].Integral(2,30,5,30), hists[key_dir_+dist_+key_region+ptbin].Integral(2,30,2,30)", hists[key_dir_+dist_+key_region+ptbin].Integral(2,30,5,30), hists[key_dir_+dist_+key_region+ptbin].Integral(2,30,2,30)
                        r_fraction = '{0:.1f}'.format(fraction)
                        if(key_region == 'EC2'):
                            if(ptbins[ptbin]=='Trigger300HF' or ptbins[ptbin]=='Trigger220HF' or ptbins[ptbin]=='Trigger160HF' or  ptbins[ptbin]=='Trigger100HF' or 
                               ptbins[ptbin]=='Trigger80HF' or ptbins[ptbin]=='Trigger60HF'):
                                summary_hist[dist_].Fill(ptbins_xaxis[ptbins[ptbin]],2.9,fraction)
                            else:
                                summary_hist[dist_].Fill(ptbins_xaxis[ptbins[ptbin]],2.7,fraction)
                        else:
                            summary_hist[dist_].Fill(ptbins_xaxis[ptbins[ptbin]],etabins_yaxis[key_region],fraction)
    canvas_dist[dist_] = TCanvas(dist_,dist_,100,100,800,600)
    gStyle.SetOptStat(0)
    gStyle.SetOptTitle(0)
    gStyle.SetLabelSize(0.045,"XY")
    gStyle.SetTitleSize(0.045,"XY")
    gStyle.SetTitleOffset(0.80,"Y")
    gStyle.SetTitleOffset(1.05,"X")
    gStyle.SetLabelOffset(0.02,"Y")
    gStyle.SetPalette(55)
    summary_hist[dist_].Print()
    summary_hist[dist_].Draw('colz')
    summary_hist[dist_].GetZaxis().SetRangeUser(0,100)
    summary_hist[dist_].GetZaxis().SetTitle('fraction macthed to L1Jet in BX=-1 and BX=0')
    summary_hist[dist_].GetXaxis().SetTitle('probe jet p_{T}, GeV')
    summary_hist[dist_].GetYaxis().SetTitle('probe jet #eta')
    gPad.SetLeftMargin(0.075)
    gPad.SetRightMargin(0.15)
    canvas_dist[dist_].SaveAs('Summary_'+dist_+'.pdf')
#                print "Input:", etabins_yaxis[regions[key_region]]
 


