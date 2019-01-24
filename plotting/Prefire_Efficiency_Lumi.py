#Plot dijet Tag&Probe (L2Res) efficiency distributions in -1,0,+1 BX overlaid for all runs on the same plot
#data: 17.06.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy

#combined file
#fin = TFile('uhh2.AnalysisModuleRunner.DATA.Run2016C.root', 'open')
fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2016_UnprefireableFilterON_DijetTriggers_addL1JetEtaPhi_patJetsAK4PFCHS_addMultMatch_L1L2L3_LumiPlots500pbdRdPt_allEtaBins/uhh2.AnalysisModuleRunner.DATA.Run2016.root', 'open')

distrs=['EtaProbevsLumi',
        'dRProbevsLumi',
        'dPtProbevsLumi'
        ] #distirbution to plot


#     'L1J_drJetProbeMin_BX','L1EG_drJetProbeMin_BX',
#dirs={'L1Jet in BX 0':'_bx0','L1Jet in BX +1':'_bxPlus1','L1Jet in BX -1':'_bxMinus1'} #directories with different L1GT BX
dirs={'L1Jet in BX 0':'_bx0','L1Jet in BX -1':'_bxMinus1','L1Jet in BX -1 (all)':'_bxMinus1_all','L1Jet in BX -1 and BX 0':'_bx0bxMinus1'} #directories with different L1GT BX
regions={'':''}
regions_legend={'':'0.0<|probe jet #eta|<5.2'}
# MarkerColor={'L1Jet in BX 0':kBlack,'L1Jet in BX -1':kRed,'L1Jet in BX +1':kBlue, 
#              'Run2016B':kRed-9,'Run2016C':kRed-7, 'Run2016D':kRed,'Run2016E':kBlue,'Run2016F':kBlue+2,'Run2016G':kGreen+1,'Run2016H':kGreen+4,
#              'Run2017B':kRed-9,'Run2017C':kRed-7, 'Run2017D':kRed,'Run2017E':kBlue,'Run2017F':kBlue+2
# }

#MarkerColor={'L1EG in BX 0':kBlack,'L1EG in BX -1':kRed,'L1EG in BX +1':kBlue}

hists = {}
canvas_dist = {}
gROOT.SetBatch(True)
lumiBCD = 12900
lumiEF = lumiBCD+6800
lumiGH = lumiEF+16800
line_BCD = TLine(lumiBCD,-5.2,lumiBCD,5.2)
line_EF = TLine(lumiEF,-5.2,lumiEF,5.2)
line_GH = TLine(lumiGH,-5.2,lumiGH,5.2)
line_BCD.SetLineStyle(2)
line_EF.SetLineStyle(2)
line_GH.SetLineStyle(2)
line_BCD.SetLineWidth(3)
line_EF.SetLineWidth(3)
line_GH.SetLineWidth(3)

# lumiB=4810
# lumiC=lumiB+2340
# lumiD=lumiC+3130
# lumiE=lumiD+3010
# lumiF=lumiE+2060
# lumiG=lumiF+5700
# lumiH=lumiG+6340
# print "total lumi =",lumiH
# line_B=TLine(lumiB,-5.2,lumiB,5.2)
# line_C=TLine(lumiC,-5.2,lumiC,5.2)
# line_D=TLine(lumiD,-5.2,lumiD,5.2)
# line_E=TLine(lumiE,-5.2,lumiE,5.2)
# line_F=TLine(lumiF,-5.2,lumiF,5.2)
# line_G=TLine(lumiG,-5.2,lumiG,5.2)
# line_H=TLine(lumiH,-5.2,lumiH,5.2)
# line_B.SetLineStyle(2)
# line_B.SetLineWidth(3)
# line_C.SetLineStyle(2)
# line_C.SetLineWidth(3)
# line_D.SetLineStyle(2)
# line_D.SetLineWidth(3)
# line_E.SetLineStyle(2)
# line_E.SetLineWidth(3)
# line_F.SetLineStyle(2)
# line_F.SetLineWidth(3)
# line_G.SetLineStyle(2)
# line_G.SetLineWidth(3)
# line_H.SetLineStyle(2)
# line_H.SetLineWidth(3)
gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
gStyle.SetLabelSize(0.045,"XYZ")
gStyle.SetTitleSize(0.045,"XYZ")
gStyle.SetTitleOffset(0.80,"Y")
gStyle.SetTitleOffset(1.05,"X")
gStyle.SetLabelOffset(0.02,"Y")
gStyle.SetPalette(55)
gROOT.ForceStyle()
for dist_ in distrs:
    for key_region in regions:
        print 'Trigger_L2Res'+regions[key_region]+'/'+dist_
        for key_dir_ in dirs:
            canvas_dist[dist_+key_region+key_dir_] = TCanvas(dist_+key_region+key_dir_,dist_+key_region+key_dir_,800,600)
           # legend = TLegend(.75,.85,.89,.99) 
          
#        legend.SetHeader(regions_legend[key_region],"C")
#        legend.SetHeader('',"C")
            
            hists[dist_+key_region] = fin.Get('LumiHists'+regions[key_region]+'/'+dist_)
            print 'LumiHists'+regions[key_region]+'/'+dist_+dirs[key_dir_]
            hists[key_dir_+dist_+key_region] = fin.Get('LumiHists'+regions[key_region]+'/'+dist_+dirs[key_dir_])
            # hists[key_dir_+dist_+key_region].SetMarkerColor(MarkerColor[key_dir_])
            # hists[key_dir_+dist_+key_region].SetMarkerStyle(21)
            # hists[key_dir_+dist_+key_region].SetMarkerSize(1.2)
            #legend.AddEntry(hists[key_dir_+dist_+key_region],key_dir_,"lp")
            #legend.SetHeader(key_dir_)
            hists[key_dir_+dist_+key_region].Print()
            hists[dist_+key_region].Print()
            hists[key_dir_+dist_+key_region].Divide(hists[dist_+key_region])
            hists[key_dir_+dist_+key_region].GetZaxis().SetRangeUser(0.0,1.0) #L1Jet
            hists[key_dir_+dist_+key_region].GetZaxis().SetTitle(key_dir_+' efficiency') #L1Je
            hists[key_dir_+dist_+key_region].GetXaxis().SetTitle('Time integrated luminosity, pb^{-1}') #L1Je
            hists[key_dir_+dist_+key_region].GetYaxis().SetTitle('Probe jet #eta') #L1Je
            hists[key_dir_+dist_+key_region].Draw('colz')
            line_BCD.Draw()
            line_EF.Draw()
#            line_GH.Draw()

            # line_B.Draw()
            # line_C.Draw()
            # line_D.Draw()
            # line_E.Draw()
            # line_F.Draw()
            # line_G.Draw()
            # line_H.Draw()

           # legend.Draw()
            gPad.SetLeftMargin(0.075)
            gPad.SetRightMargin(0.15)
            canvas_dist[dist_+key_region+key_dir_].SaveAs('Eff_'+dist_+regions[key_region]+dirs[key_dir_]+'_allRuns.pdf')

