#Plot dijet Tag&Probe (L2Res) distributions in -1,0,+1 BX overlaid
#data: 17.06.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy

#fin = TFile('/nfs/dust/cms/user/karavdia/CMSSW_9_4_3/src/UHH2/TriggersExamination/plotting/uhh2.AnalysisModuleRunner.DATA.Run2016C.root', 'open')
#fin = TFile('/nfs/dust/cms/user/karavdia/CMSSW_9_4_3/src/UHH2/TriggersExamination/plotting/uhh2.AnalysisModuleRunner.DATA.Run2016H_9.root', 'open')
fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2016_UnprefireableFilterON_DijetTriggers_addL1JetEtaPhi_patJetsAK4PFCHS_addMultMatch_L1L2L3_LumiPlots500pb_allEtaBins/uhh2.AnalysisModuleRunner.DATA.Run2016H.root', 'open')
distrs=['L1J_drJetProbeMin_pBalAsymmetry','L1J_drJetProbeMin_mpfAsymmetry',
        'L1J_drJetProbeMin_dR', 
        'L1J_drJetProbeMin_Pt',
        'L1J_drJetProbeMin_neuEMfracProbe', 'L1J_drJetProbeMin_neuHADfracProbe',
       # 'L1J_drJetProbeMin_dR', 
        'L1J_drJetProbeMin_NPV',
        'L1J_drJetProbeMin_chMultiProbe','L1J_drJetProbeMin_neuMultiProbe'
        ] #distirbution to plot

#distrs=['L1EG_drJetProbeMin_dR','L1EG_drJetProbeMin_mpfResponse','L1EG_drJetProbeMin_pBalResponse','L1EG_drJetProbeMin_pBalAsymmetry','L1EG_drJetProbeMin_mpfAsymmetry'] #distirbution to plot


#     'L1J_drJetProbeMin_BX','L1EG_drJetProbeMin_BX',
#distrs=['L1J_drJetProbeMin_Pt','L1J_drJetProbeMin_Ptave']
dirs={'L1Jet in BX 0':'_bx0','L1Jet in BX -1':'_bxMinus1'} #directories with different L1Jet BX

regions={'':''} 
regions_legend={'':'0.0<|probe jet #eta|<5.2'}
n_eta=37
eta_range = ["-5191","-3839","-3489","-3139","-2964","-2853", "-265", "-25", "-2322", "-2172", "-193", "-1653", "-1479", 
             "-1305", "-1044", "-0783","-0522", "-0261","00", "0261", "0522", "0783", "1044", "1305", "1479", "1653", "193", 
             "2172", "2322", "25", "2650", "2853", "2964", "3139", "3489", "3839", "5191"] 
eta_bins= [-5.191, -3.839, -3.489, -3.139, -2.964, -2.853, -2.65, -2.5, -2.322, -2.172, -1.93, -1.653, -1.479, -1.305, -1.044, -0.783, -0.522,
 -0.261, 0.000, 0.261, 0.522, 0.783, 1.044, 1.305, 1.479, 1.653, 1.93, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.489, 3.839, 5.191]                         
    
MarkerColor={'L1Jet in BX 0':kBlack,'L1Jet in BX -1':kRed,'L1Jet in BX +1':kBlue}

hists = {}
canvas_dist = {}
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

#    for key_region in regions:
    for i in range(n_eta-1):
        name = "Trigger_L2Res_" # name+="eta_"+eta_range[i]+"_"+eta_range[i+1]  
        etaBinName = "eta_"+eta_range[i]+"_"+eta_range[i+1]
        etaBinLeg = str(eta_bins[i])+' < probe jet #eta < '+str(eta_bins[i+1])
        name +=etaBinName
        canvas_dist[dist_+name] = TCanvas(dist_+name,dist_+name,800,600)
        legend = TLegend(.63,.75,.99,.99)
        legend.SetTextSize(0.04) 

        legend.SetHeader(etaBinLeg,"C")
#        print 'Trigger_L2Res'+regions[key_region]+'/'+dist_
#        hists[dist_+key_region] = fin.Get('Trigger_L2Res'+regions[key_region]+'/'+dist_)
        print name + '/'+dist_
        hists[dist_+name] = fin.Get(name+'/'+dist_)
#        hists[dist_+key_region].Rebin(4)
#        hists[key_dir_+dist_+key_region].Draw('EP same')

        for key_dir_ in dirs:
            # print key_dir_
#            print 'Trigger_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_]
            print name+'/'+dist_+dirs[key_dir_]
#            hists[key_dir_+dist_+key_region] = fin.Get('Trigger_L2Res'+regions[key_region]+'/'+dist_+dirs[key_dir_])
            hists[key_dir_+dist_+name] = fin.Get(name+'/'+dist_+dirs[key_dir_])
            hists[key_dir_+dist_+name].SetMarkerColor(MarkerColor[key_dir_])
            hists[key_dir_+dist_+name].SetMarkerStyle(21)
            hists[key_dir_+dist_+name].SetMarkerSize(1.5)
            legend.AddEntry(hists[key_dir_+dist_+name],key_dir_,"lp")
            hists[key_dir_+dist_+name].Print()
            hists[dist_+name].Print()
#            hists[key_dir_+dist_+name].Rebin(4)
            hists[key_dir_+dist_+name].Divide(hists[dist_+name])
            hists[key_dir_+dist_+name].Draw('EP same')


        hists['L1Jet in BX -1'+dist_+name].GetYaxis().SetRangeUser(0.0,1.4) #L1Jet
#        hists['L1Jet in BX -1'+dist_+name].GetYaxis().SetRangeUser(0.0,1000) #L1Jet
        hists['L1Jet in BX -1'+dist_+name].GetYaxis().SetTitle("BX=x efficiency") #L1Jet
#        canvas_dist[dist_+name].SetLogy()
        legend.Draw()
#        print "canvas key:", dist_+name
        canvas_dist[dist_+name].SaveAs('Eff_'+dist_+"_"+etaBinName+'.pdf')
#        canvas_dist[dist_+name].SaveAs('Eff_'+dist_+regions[name]+'.root')
