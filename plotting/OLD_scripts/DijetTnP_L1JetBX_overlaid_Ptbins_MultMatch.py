#Plot dijet Tag&Probe (L2Res) distributions in -1,0,+1 BX overlaid
#data: 17.06.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy


#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd_patJetsAK4PFCHS_addMultMatch/uhh2.AnalysisModuleRunner.DATA.Run2017B.root')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd_patJetsAK4PFCHS_addMultMatch/uhh2.AnalysisModuleRunner.DATA.Run2017C.root')

fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd_patJetsAK4PFCHS_addMultMatch/uhh2.AnalysisModuleRunner.DATA.Run2017F.root')


distrs=['L1J_dRjetProbeL1bxMinus1','L1J_dRjetProbeL1bx0','L1J_PtProbeoverL1bx0','L1J_PtProbeoverL1bxMinus1',
        'L1J_pBalAsymmetry','L1J_mpfAsymmetry'
        ] #distirbution to plot

dirs={'L1Jet in BX 0':'_bx0','L1Jet in BX -1':'_bxMinus1','L1Jet in BX 0 and -1':'_bx0bxMinus1'} #directories with different L1GT BX

regions={'BB':'_BB','EC1':'_EC1','EC2':'_EC2','HF':'_HF','':''} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined

# #Dijet
# ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140',
# 'pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320',
# 'pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500',                                                          
#}

#SingleJet
# #central
# ptbins={'pt#in[72,95]':'Trigger40','pt#in[95,160]':'Trigger60','pt#in[160,226]':'Trigger80','pt#in[226,283]':'Trigger140',
# 'pt#in[283,344]':'Trigger200','pt#in[344,443]':'Trigger260','pt#in[443,577]':'Trigger320',
# 'pt#in[577,606]':'Trigger400','pt#in[606,#infty]':'Trigger500',                                                          
# }
# regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
#                     'EC2':'2.5<|probe jet #eta|<2.8','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}    

#forward
ptbins={'pt#in[72,95]':'Trigger40HF','pt#in[95,160]':'Trigger60HF','pt#in[160,226]':'Trigger80HF','pt#in[226,283]':'Trigger140HF',
'pt#in[283,344]':'Trigger200HF','pt#in[344,443]':'Trigger260HF','pt#in[443,577]':'Trigger320HF',
'pt#in[577,606]':'Trigger400HF','pt#in[606,#infty]':'Trigger500HF',                                                          
}
regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
                    'EC2':'2.8<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}       



#ptbins={'pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 'pt#in[239,318]':'Trigger220HF',
#'pt#in[318,#infty]':'Trigger300HF', 
#}                                                                                                                                                                    
#ptbins_xaxis={'Trigger40':62,'Trigger60':85,'Trigger80':138,'Trigger140':243,'Trigger200':339,'Trigger260':402,'Trigger320':477,'Trigger400':585,'Trigger500':825,
#'Trigger60HF':83,'Trigger80HF':103,'Trigger100HF':145,'Trigger160HF':208, 'Trigger220HF':279, 'Trigger300HF':659,
#}                                                                                                                                                                     
                                                                                                          
# if len(ptbins)<7:                                                                                                                                                     
#     regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
#                     'EC2':'2.8<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}                                                                                                                                                     
# else:                 
#     regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
#                     'EC2':'2.5<|probe jet #eta|<2.8','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}    

#regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5','EC2':'2.5<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}
MarkerColor={'L1Jet in BX 0':kBlack,'L1Jet in BX -1':kRed,'L1Jet in BX 0 and -1':kGreen}

# ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140','pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320','pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500',
# 'pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 'pt#in[239,318]':'Trigger220HF', 'pt#in[318,#infty]':'Trigger300HF',
# }
#ptbins={'pt#in[51,73]':'Trigger40'}

hists = {}
canvas_dist = {}
gROOT.SetBatch(True)
for ptbin in ptbins:
    for dist_ in distrs:
        for key_region in regions:
            canvas_dist[dist_+key_region+ptbin] = TCanvas(dist_+key_region+ptbin,dist_+key_region+ptbin,100,100,800,600)
            legend = TLegend(.60,.75,.99,.99) 
            gStyle.SetOptStat(0)
            gStyle.SetOptTitle(0)
            gStyle.SetLabelSize(0.08,"XY")
            gStyle.SetTitleSize(0.08,"XY")
            gStyle.SetTitleOffset(1.11,"Y")
            gStyle.SetLabelOffset(0.01,"Y")
            legend.SetHeader(regions_legend[key_region]+', '+ptbin,"C")
            for key_dir_ in dirs:
                # print key_dir_
                print ptbins[ptbin]+'_MultMatch'+regions[key_region]+'/'+dist_+dirs[key_dir_]
                hists[key_dir_+dist_+key_region+ptbin] = fin.Get(ptbins[ptbin]+'_MultMatch'+regions[key_region]+'/'+dist_+dirs[key_dir_])
#                hists[key_dir_+dist_+key_region+ptbin].Print()
                hists[key_dir_+dist_+key_region+ptbin].SetMarkerColor(MarkerColor[key_dir_])
                hists[key_dir_+dist_+key_region+ptbin].SetMarkerStyle(23)
                hists[key_dir_+dist_+key_region+ptbin].SetMarkerSize(1.5)
                legend.AddEntry(hists[key_dir_+dist_+key_region+ptbin],key_dir_,"lp")
                hists[key_dir_+dist_+key_region+ptbin].Draw('EP same')

#set up maximum of hists to BX=0
#            hists['L1Jet in BX -1'+dist_+key_region+ptbin].Print()
#            hists['L1Jet in BX -1'+dist_+key_region+ptbin].GetYaxis().SetRangeUser(1e-1,100.0*hists['L1Jet in BX 0'+dist_+key_region+ptbin].GetMaximum()) #L1Jet
            hists['L1Jet in BX -1'+dist_+key_region+ptbin].GetYaxis().SetRangeUser(1e-1,100.0*hists['L1Jet in BX 0'+dist_+key_region+ptbin].GetMaximum()) #L1Jet
            canvas_dist[dist_+key_region+ptbin].SetLogy()
            legend.Draw()
            canvas_dist[dist_+key_region+ptbin].SaveAs(dist_+regions[key_region]+'_'+ptbins[ptbin]+'.pdf')



