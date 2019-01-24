#Plot 2D distibution from dijet Tag&Probe (L2Res) prefire study data:
#28.07.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy


import numpy as np

fin = TFile('/nfs/dust/cms/user/karavdia/CMSSW_9_4_3/src/UHH2/TriggersExamination/plotting/uhh2.AnalysisModuleRunner.DATA.Run2016H_9.root', 'open') 

distrs=['L1J_drJetProbeMin_dR0dRm1','L1J_drJetProbeMin_dPt0dPtm1','L1J_drJetProbeMin_dPt0dPtp1', 'L1J_drJetProbeMin_dR0dRp1', 'L1J_drJetProbeMin_dPt0dPtm1SUM'] #distirbution to plot

#distrs=['L1J_drJetProbeMin_dR0dRm1'] #distirbution to plot

dirs={'L1Jet in ALL':''} #directories with different L1GT BX
n_eta=37                                                                                                                                                              
eta_range = ["-5191","-3839","-3489","-3139","-2964","-2853", "-265", "-25", "-2322", "-2172", "-193", "-1653", "-1479",                                              
             "-1305", "-1044", "-0783","-0522", "-0261","00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193",                                          
             "2172", "2322", "25", "2650", "2853", "2964", "3139", "3489", "3839", "5191"]                                                                            
eta_bins= [-5.191, -3.839, -3.489, -3.139, -2.964, -2.853, -2.65, -2.5, -2.322, -2.172, -1.93, -1.653, -1.479, -1.305, -1.044, -0.783, -0.522,                        
 -0.261, 0.000, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191]                             
eta_range_HF = ["-5191","-3839","-3489","-3139","-2964","-2853", "-265", "2650", "2853", "2964", "3139", "3489", "3839", "5191"]                                      
eta_bins_HF= np.array([-5.191, -3.839, -3.489, -3.139, -2.964, -2.853, -2.65, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191],dtype='float64')
eta_range_cntr = ["-2853", "-265", "-25", "-2322", "-2172", "-193", "-1653", "-1479",
             "-1305", "-1044", "-0783","-0522", "-0261","00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193",                                          
             "2172", "2322", "25", "2650", "2853"]                                                                            
eta_bins_cntr= np.array([-2.853, -2.65, -2.5, -2.322, -2.172, -1.93, -1.653, -1.479, -1.305, -1.044, -0.783, -0.522,
 -0.261, 0.000, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853],dtype='float64')
#DiJet HLT, 2016                                                                                                                                                      
n_pt = 11                                                                                                                                                             
pt_range_cntr=["51", "74", "96", "165", "232", "300", "366", "456", "569", "1000", "2000"]                                                                            
pt_bins_cntr=np.array([51, 74, 96, 165, 232, 300, 366, 456, 569, 1000, 2000],dtype='float64')
pt_range_HF=["72", "95", "118", "188", "257", "354", "450", "1000", "2000"]                                                                                           
pt_bins_HF=np.array([72, 95, 118, 188, 257, 354, 450, 1000, 2000],dtype='float64')                                                                                    
hists = {}
canvas_dist = {}
summary_hist = {}
gROOT.SetBatch(True)
gStyle.SetOptStat(0)                                                                                                                                                  
gStyle.SetOptTitle(0)                                                                                                                                                 
gStyle.SetLabelSize(0.045,"XYZ")                                                                                                                                      
gStyle.SetTitleSize(0.045,"XYZ")                                                                                                                                      
gStyle.SetTitleOffset(1.05,"Y")                                                                                                                                       
gStyle.SetTitleOffset(1.05,"X")                                                                                                                                       
gStyle.SetLabelOffset(0.02,"Y")                                                                                                                                       
gStyle.SetPalette(55)                                                                                                                                                 
gROOT.ForceStyle()     

for dist_ in distrs:
    summary_hist[dist_+'_HF'] = TH2D('hHF'+dist_,dist_,len(pt_bins_HF)-1,pt_bins_HF,len(eta_bins_HF)-1,eta_bins_HF)
    summary_hist[dist_+'_cntr'] = TH2D('hCNTR'+dist_,dist_,len(pt_bins_cntr)-1,pt_bins_cntr,len(eta_bins_cntr)-1,eta_bins_cntr)

#    summary_hist[dist_] = TH2D('h'+dist_,dist_,len(pt_bins)-1,pt_bins,len(eta_bins)-1,eta_bins)

#    for ptbin in ptbins:
        # print ptbins[ptbin]
 #       for key_region in regions:
    for i in range(n_eta-1):                                                                                                                                         
        name_Eta = "Trigger_L2Res_" # name+="eta_"+eta_range[i]+"_"+eta_range[i+1]                                                                                    
        etaBinName = "eta_"+eta_range[i]+"_"+eta_range[i+1]                                                                                                           
        etaBinLeg = str(eta_bins[i])+' < probe jet #eta < '+str(eta_bins[i+1])                                                                                        
        name_Eta +=etaBinName                                                                                                                                         
        eta_cut_bool = False                                                                                                                                          
        if(abs(eta_bins[i])<abs(eta_bins[i+1])):                                                                                                                      
            eta_cut_bool = abs(eta_bins[i])>2.8                                                                                                                       
        else:                                                                                                                                                         
            eta_cut_bool = abs(eta_bins[i+1])>2.8                                                                                                                     
        if not eta_cut_bool:                                                                                                                                          
            pt_range=pt_range_cntr                                                                                                                                    
            pt_bins=pt_bins_cntr                                                                                                                                      
        else:                                                                                                                                                         
            pt_range=pt_range_HF                                                                                                                                      
            pt_bins=pt_bins_HF                                                                                                                                       
 #       print "len(pt_bins)", len(pt_bins)                                                                                                                           
        for j in range(len(pt_bins)-1):                                                                                                                             
            name = name_Eta                                                                                                                                          
            PtBinName="_pT_"+pt_range[j]+"_"+pt_range[j+1]                                                                                                            
            PtBinLeg="pt#in["+pt_range[j]+", "+pt_range[j+1]+"]"                                                                                                      
            name +=PtBinName                                                                                                                                          
#            print "name = ",name                         
            for key_dir_ in dirs:
#                hists[key_dir_+dist_+name] = fin.Get(ptbins[ptbin]+'_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_])
                hists[key_dir_+dist_+name] = fin.Get(name+'/'+dist_+dirs[key_dir_])
                N_ev = hists[key_dir_+dist_+name].GetEntries()
                fraction = 0
                if(N_ev>100):
                    if(hists[key_dir_+dist_+name].Integral(0,30,0,30)>0):
                        if(dist_=='L1J_drJetProbeMin_dPt0dPtm1' or dist_=='L1J_drJetProbeMin_dPt0dPtp1'):
                            fraction = 100.0*(hists[key_dir_+dist_+name].Integral(2,30,5,30)/hists[key_dir_+dist_+name].Integral(0,30,0,30))
                        else:
                            fraction = 100.0*(hists[key_dir_+dist_+name].Integral(2,30,2,30)/hists[key_dir_+dist_+name].Integral(0,30,0,30))
                        r_fraction = '{0:.1f}'.format(fraction)
                        if not eta_cut_bool:
                            summary_hist[dist_+'_cntr'].Fill(pt_bins[j],eta_bins[i],fraction)
                        else:
                            summary_hist[dist_+'_HF'].Fill(pt_bins[j],eta_bins[i],fraction)

                        # if(key_region == 'EC2'):
                        #     if(ptbins[ptbin]=='Trigger500HF' or ptbins[ptbin]=='Trigger260HF' or ptbins[ptbin]=='Trigger200HF' or  ptbins[ptbin]=='Trigger140HF' or 
                        #        ptbins[ptbin]=='Trigger400HF' or ptbins[ptbin]=='Trigger320HF' or ptbins[ptbin]=='Trigger40HF' or ptbins[ptbin]=='Trigger80HF'):
                        #         summary_hist[dist_].Fill(ptbins_xaxis[ptbins[ptbin]],2.9,fraction)
                        #     else:
                        #         summary_hist[dist_].Fill(ptbins_xaxis[ptbins[ptbin]],2.7,fraction)
                        # else:
                        #     summary_hist[dist_].Fill(ptbins_xaxis[ptbins[ptbin]],etabins_yaxis[key_region],fraction)
    canvas_dist[dist_+'_cntr'] = TCanvas(dist_,dist_,100,100,800,600)
    gStyle.SetOptStat(0)
    gStyle.SetOptTitle(0)
    gStyle.SetLabelSize(0.045,"XY")
    gStyle.SetTitleSize(0.045,"XY")
    gStyle.SetTitleOffset(0.80,"Y")
    gStyle.SetTitleOffset(1.05,"X")
    gStyle.SetLabelOffset(0.02,"Y")
    gStyle.SetPalette(55)
    gROOT.ForceStyle()
    summary_hist[dist_+'_cntr'].Print()
    summary_hist[dist_+'_cntr'].Draw('colz')
    summary_hist[dist_+'_cntr'].GetZaxis().SetRangeUser(0,100)
    summary_hist[dist_+'_cntr'].GetZaxis().SetTitle('fraction macthed to L1Jet in BX=-1 and BX=0')
    summary_hist[dist_+'_cntr'].GetXaxis().SetTitle('probe jet p_{T}, GeV')
    summary_hist[dist_+'_cntr'].GetYaxis().SetTitle('probe jet #eta')
    gPad.SetLeftMargin(0.075)
    gPad.SetRightMargin(0.15)
    canvas_dist[dist_+'_cntr'].SaveAs('Summary_'+dist_+'_cntr'+'.pdf')
    canvas_dist[dist_+'_HF'] = TCanvas(dist_,dist_,100,100,800,600)
    gStyle.SetOptStat(0)
    gStyle.SetOptTitle(0)
    gStyle.SetLabelSize(0.045,"XY")
    gStyle.SetTitleSize(0.045,"XY")
    gStyle.SetTitleOffset(0.80,"Y")
    gStyle.SetTitleOffset(1.05,"X")
    gStyle.SetLabelOffset(0.02,"Y")
    gStyle.SetPalette(55)
    gROOT.ForceStyle()
    summary_hist[dist_+'_HF'].Print()
    summary_hist[dist_+'_HF'].Draw('colz')
    summary_hist[dist_+'_HF'].GetZaxis().SetRangeUser(0,100)
    summary_hist[dist_+'_HF'].GetZaxis().SetTitle('fraction macthed to L1Jet in BX=-1 and BX=0')
    summary_hist[dist_+'_HF'].GetXaxis().SetTitle('probe jet p_{T}, GeV')
    summary_hist[dist_+'_HF'].GetYaxis().SetTitle('probe jet #eta')
    gPad.SetLeftMargin(0.075)
    gPad.SetRightMargin(0.15)
    canvas_dist[dist_+'_HF'].SaveAs('Summary_'+dist_+'_HF'+'.pdf')

#                print "Input:", etabins_yaxis[regions[key_region]]
 


