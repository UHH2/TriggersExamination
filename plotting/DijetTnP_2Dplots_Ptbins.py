#Plot 2D distibution from dijet Tag&Probe (L2Res) prefire study data:
#28.07.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy


import numpy as np
#fin = TFile('/nfs/dust/cms/user/karavdia/CMSSW_9_4_3/src/UHH2/TriggersExamination/plotting/uhh2.AnalysisModuleRunner.DATA.Run2016H_9.root', 'open')
fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2016_UnprefireableFilterON_DijetTriggers_addL1JetEtaPhi_patJetsAK4PFCHS_addMultMatch_L1L2L3_LumiPlots500pb_allEtaBins_allPtBins/uhh2.AnalysisModuleRunner.DATA.Run2016H.root', 'open')


#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd_patJetsAK4PFCHS_addMultMatch/uhh2.AnalysisModuleRunner.DATA.Run2017F.root')


distrs=['L1J_drJetProbeMin_dR0dRm1','L1J_drJetProbeMin_dPt0dPtm1','L1J_drJetProbeMin_dPt0dPtp1', 'L1J_drJetProbeMin_dR0dRp1', 'L1J_drJetProbeMin_dPt0dPtm1SUM',
        'L1J_drJetProbeMin_L1EtaL1Phi',
        'L1J_drJetProbeMin_diffL1EtaL1Phi', 'L1J_drJetProbeMin_diffL1EtaL1Phi_bx0','L1J_drJetProbeMin_diffL1EtaL1Phi_bxMinus1',
        'L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt','L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt_bx0','L1J_drJetProbeMin_diffL1EtaL1PtoverProbePt_bxMinus1',
        ] #distirbution to plot

dirs={'L1Jet in ALL':''} #directories with different L1GT BX

MarkerColor={'L1Jet in BX 0':kBlack,'L1Jet in BX -1':kRed,'L1Jet in BX +1':kBlue}


n_eta=37                                                                                                                                                              
eta_range = ["-5191","-3839","-3489","-3139","-2964","-2853", "-265", "-25", "-2322", "-2172", "-193", "-1653", "-1479",                                              
             "-1305", "-1044", "-0783","-0522", "-0261","00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193",                                          
             "2172", "2322", "25", "2650", "2853", "2964", "3139", "3489", "3839", "5191"]                                                                            
eta_bins= [-5.191, -3.839, -3.489, -3.139, -2.964, -2.853, -2.65, -2.5, -2.322, -2.172, -1.93, -1.653, -1.479, -1.305, -1.044, -0.783, -0.522,               
 -0.261, 0.000, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191]                            
#DiJet HLT, 2016
n_pt = 11
pt_range_cntr=["51", "74", "96", "165", "232", "300", "366", "456", "569", "1000", "2000"]
pt_bins_cntr=[51, 74, 96, 165, 232, 300, 366, 456, 569, 1000, 2000]                                                                                    
pt_range_HF=["72", "95", "118", "188", "257", "354", "450", "1000", "2000"]
pt_bins_HF=[72, 95, 118, 188, 257, 354, 450, 1000, 2000]      


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

        print "len(pt_bins)", len(pt_bins) 

        for j in range(len(pt_bins)-1):
            name = name_Eta                                                                                                                              
            PtBinName="_pT_"+pt_range[j]+"_"+pt_range[j+1]
            PtBinLeg="pt#in["+pt_range[j]+", "+pt_range[j+1]+"]"
            name +=PtBinName
            print "name = ",name
            for key_dir_ in dirs:
                print "dist_:",dist_
                canvas_dist[dist_+name+key_dir_] = TCanvas(dist_+name+key_dir_,dist_+name+key_dir_,100,100,800,600)
                legend = TLegend(.30,.85,.85,.99) 
                legend.SetTextSize(0.04)
                legend.SetHeader(etaBinLeg+', '+PtBinLeg,"C")                                     
                hists[key_dir_+dist_+name] = fin.Get(name+'/'+dist_+dirs[key_dir_])
                hists[key_dir_+dist_+name].Draw('colz')
                Tl = TLatex()
                Tl.SetTextAlign(12)
                Tl.SetTextSize(0.045)
                text = TString("matched to both ")
                fraction = 0
                if(hists[key_dir_+dist_+name].Integral(0,30,0,30)>0):
                    fraction = 100.0*(hists[key_dir_+dist_+name].Integral(2,30,2,30)/hists[key_dir_+dist_+name].Integral(0,30,0,30))
                    r_fraction = '{0:.1f}'.format(fraction)
                    print "fraction:", r_fraction
                    text += r_fraction
                else:                
                    text += "0"
                text +=" %"
                if(dist_ == 'L1J_drJetProbeMin_dR0dRm1' or dist_ == 'L1J_drJetProbeMin_dR0dRp1'):
                    Tl.DrawLatex(-0.05,-0.05,text.Data())
                legend.Draw()
                canvas_dist[dist_+name+key_dir_].SaveAs(dist_+'_'+etaBinName+PtBinName+dirs[key_dir_]+'.pdf')
 


