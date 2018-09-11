#Plot dijet Tag&Probe (L2Res) distributions in -1,0,+1 BX overlaid
#data: 17.06.2018


from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy
import math

gROOT.SetBatch(True)


#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd_patJetsAK4PFCHS_addMultMatch/uhh2.AnalysisModuleRunner.DATA.Run2017B.root')
#fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd_patJetsAK4PFCHS_addMultMatch/uhh2.AnalysisModuleRunner.DATA.Run2017C.root')
fin = TFile('/nfs/dust/cms/user/karavdia/PreFireStudy/JetHT2017F_UnprefireableFilterOFF_SingleJetTriggers_addFwd_patJetsAK4PFCHS_addMultMatch/uhh2.AnalysisModuleRunner.DATA.Run2017F.root')

distrs=['L1J_pBalAsymmetry'
        ] #distirbution to extract residuals from by (1+<A>)/(1-<A>)

Ptave='L1J_drJetProbeMin_Ptave'

yaxisnames={'L1J_drJetProbeMin_pBalAsymmetry':'pt-Bal','L1J_drJetProbeMin_mpfAsymmetry':'MPF','L1J_pBalAsymmetry':'pt-balance','L1J_mpfAsymmetry':'MPF'}

dirs={'L1Jet in BX 0':'_bx0','L1Jet in BX -1':'_bxMinus1','L1Jet in BX 0 and -1':'_bx0bxMinus1'} #directories with different L1GT BX
MarkerColor={'L1Jet in BX 0':kBlack,'L1Jet in BX -1':kRed,'L1Jet in BX 0 and -1':kGreen}
#regions={'BB':'_BB','EC1':'_EC1','EC2':'_EC2','HF':'_HF','':''} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
#regions={'EC2':'_EC2'} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined
regions={'HF':'_HF'} #BB: 0<eta<1.3, EC1: 1.3<eta<2.5, EC2: 2.5<eta<3.0, HF: 3.0<eta<5.2, all combined

#SingleJet
#central
# ptbins={'pt#in[72,95]':'Trigger40','pt#in[95,160]':'Trigger60','pt#in[160,226]':'Trigger80','pt#in[226,283]':'Trigger140',
# 'pt#in[283,344]':'Trigger200','pt#in[344,443]':'Trigger260','pt#in[443,577]':'Trigger320',
# 'pt#in[577,606]':'Trigger400','pt#in[606,#infty]':'Trigger500',                                                          
# }
# # #forward
ptbins={'pt#in[72,95]':'Trigger40HF','pt#in[95,160]':'Trigger60HF','pt#in[160,226]':'Trigger80HF','pt#in[226,283]':'Trigger140HF',
'pt#in[283,344]':'Trigger200HF','pt#in[344,443]':'Trigger260HF','pt#in[443,577]':'Trigger320HF',
'pt#in[577,606]':'Trigger400HF','pt#in[606,#infty]':'Trigger500HF',                                                          
}
     


# ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140','pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320','pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500',}

#ptbins={'pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 'pt#in[239,318]':'Trigger220HF', 'pt#in[318,#infty]':'Trigger300HF',}

# ptbins_xaxis={'Trigger40':62,'Trigger60':85,'Trigger80':138,'Trigger140':243,'Trigger200':339,'Trigger260':402,'Trigger320':477,'Trigger400':585,'Trigger500':825,
# 'Trigger60HF':83,'Trigger80HF':103,'Trigger100HF':145,'Trigger160HF':208, 'Trigger220HF':279, 'Trigger300HF':659,
# }

# ptbins_xaxis={'Trigger40':62,'Trigger60':85,'Trigger80':138,'Trigger140':243,'Trigger200':339,'Trigger260':402,'Trigger320':477,'Trigger400':585,'Trigger500':825,
# 'Trigger40HF':62,'Trigger60HF':85,'Trigger80HF':138,'Trigger140HF':243,'Trigger200HF':339,'Trigger260HF':402,'Trigger320HF':477,'Trigger400HF':585,'Trigger500HF':825,
# #'Trigger60HF':83,'Trigger80HF':103,'Trigger100HF':145,'Trigger160HF':208, 'Trigger220HF':279, 'Trigger300HF':659,
# }


# if len(ptbins)<7:
#     regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5','EC2':'2.8<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}
# else:
#     regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5','EC2':'2.5<|probe jet #eta|<2.8','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}


# ptbins={'pt#in[51,73]':'Trigger40','pt#in[73,97]':'Trigger60','pt#in[97,179]':'Trigger80','pt#in[179,307]':'Trigger140','pt#in[307,370]':'Trigger200','pt#in[370,434]':'Trigger260','pt#in[434,520]':'Trigger320','pt#in[520,649]':'Trigger400','pt#in[649,#infty]':'Trigger500',
# 'pt#in[73,93]':'Trigger60HF','pt#in[93,113]':'Trigger80HF','pt#in[113,176]':'Trigger100HF','pt#in[176,239]':'Trigger160HF', 'pt#in[239,318]':'Trigger220HF', 'pt#in[318,#infty]':'Trigger300HF',
# }



#ptbins={'pt#in[51,73]':'Trigger40'}

hists = {}
hists_ptave = {}
canvas_dist = {}
graphs = {}
mg_graphs = {}

if(ptbins['pt#in[72,95]']=='Trigger40'):
    key_label = 'Central'
    regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
                    'EC2':'2.5<|probe jet #eta|<2.8','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}    
elif(ptbins['pt#in[72,95]']=='Trigger40HF'):
    key_label = 'Forward'
    regions_legend={'BB':'0.0<|probe jet #eta|<1.3','EC1':'1.3<|probe jet #eta|<2.5',
                    'EC2':'2.8<|probe jet #eta|<3.0','HF':'3.0<|probe jet #eta|<5.2','':'0.0<|probe jet #eta|<5.2'}  
for dist_ in distrs:
    for key_region in regions:
        canvas_dist[dist_+key_region] = TCanvas(dist_+key_region,dist_+key_region,100,100,800,600)
        legend = TLegend(.60,.75,.99,.99) 
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)
        gStyle.SetLabelSize(0.05,"XY")
        gStyle.SetTitleSize(0.05,"XY")
        gStyle.SetTitleOffset(1.05,"Y")
        gStyle.SetTitleOffset(1.05,"X")
        gStyle.SetLabelOffset(0.01,"Y")
        legend.SetHeader(regions_legend[key_region],"C")
        print 'key_region = ',key_region
        mg_graphs[dist_+key_region] = TMultiGraph()
        for key_dir_ in dirs:
            graphs[dist_+key_region+key_dir_] = TGraphErrors(len(ptbins))
            i=0
            for ptbin in ptbins:
                # print key_dir_
 #               print ptbins[ptbin]+'_MultMatch'+regions[key_region]+'/'+dist_+dirs[key_dir_]
                hists[key_dir_+dist_+key_region+ptbin] = fin.Get(ptbins[ptbin]+'_MultMatch'+regions[key_region]+'/'+dist_+dirs[key_dir_])
#                hists_ptave[key_dir_+dist_+key_region+ptbin] = fin.Get(ptbins[ptbin]+'_MultMatch'+regions[key_region]+'/'+Ptave+dirs[key_dir_])
                hists_ptave[key_dir_+dist_+key_region+ptbin] = fin.Get(ptbins[ptbin]+'_L2Res'+regions[key_region]+'/'+Ptave)

#                print "Mean = ",hists[key_dir_+dist_+key_region+ptbin].GetMean() 
#                print "pt = ",ptbins_xaxis[ptbins[ptbin]]
#                print "StdDev = ",hists[key_dir_+dist_+key_region+ptbin].GetStdDev() 
                #                hists[key_dir_+dist_+key_region+ptbin].Print()
#                graphs[dist_+key_region+key_dir_].SetPoint(i,ptbins_xaxis[ptbins[ptbin]],(1+hists[key_dir_+dist_+key_region+ptbin].GetMean())/(1-hists[key_dir_+dist_+key_region+ptbin].GetMean()))
                # print ptbins[ptbin]+'_MultMatch'+regions[key_region]+'/'+Ptave
                # print "ptAve mena = ", hists_ptave[key_dir_+dist_+key_region+ptbin].GetMean()
                # print "pt bins = ", ptbins_xaxis[ptbins[ptbin]]
#                graphs[dist_+key_region+key_dir_].SetPoint(i,hists_ptave[key_dir_+dist_+key_region+ptbin].GetMean(),(1+hists[key_dir_+dist_+key_region+ptbin].GetMean())/(1-hists[key_dir_+dist_+key_region+ptbin].GetMean()))
                
                N_ev = hists[key_dir_+dist_+key_region+ptbin].GetEntries()
                print "N events: ",  N_ev
                if(N_ev>50):
                    asymm = hists[key_dir_+dist_+key_region+ptbin].GetMean()
                    error_asymm = 3*hists[key_dir_+dist_+key_region+ptbin].GetMeanError()
                #                error_asymm = hists[key_dir_+dist_+key_region+ptbin].GetStdDev()
                    response = (1+asymm)/(1-asymm)
                    error_response = math.sqrt(2)*error_asymm*math.sqrt(abs(response*asymm/(1-asymm*asymm)))
                else:
                    response = 0
                    error_response = 0
                if(error_response>0):
                    graphs[dist_+key_region+key_dir_].SetPoint(i,hists_ptave[key_dir_+dist_+key_region+ptbin].GetMean(),response)
                    graphs[dist_+key_region+key_dir_].SetPointError(i,hists_ptave[key_dir_+dist_+key_region+ptbin].GetMeanError(),error_response)
                    print "response, err", response, error_response
                    i=i+1
                
            graphs[dist_+key_region+key_dir_].SetMarkerColor(MarkerColor[key_dir_])
            graphs[dist_+key_region+key_dir_].SetMarkerStyle(21)
            graphs[dist_+key_region+key_dir_].SetMarkerSize(1.5)
            graphs[dist_+key_region+key_dir_].GetXaxis().SetRangeUser(30,5000)
            legend.AddEntry(graphs[dist_+key_region+key_dir_],key_dir_,"lp")            
            mg_graphs[dist_+key_region].Add(graphs[dist_+key_region+key_dir_])
        mg_graphs[dist_+key_region].Draw('aep')
#        mg_graphs[dist_+key_region].GetYaxis().SetRangeUser(0.50,2.00)
        mg_graphs[dist_+key_region].GetYaxis().SetRangeUser(0.70,2.20)
#        mg_graphs[dist_+key_region].GetYaxis().SetRangeUser(0.70,1.20)
        mg_graphs[dist_+key_region].GetXaxis().SetRangeUser(30,7000)
        mg_graphs[dist_+key_region].GetXaxis().SetTitle('p^{ave}_{T}, GeV')
        mg_graphs[dist_+key_region].GetYaxis().SetTitle(yaxisnames[dist_]+' response')
#set up maximum of hists to BX=0
#                hists['L1Jet in BX -1'+dist_+key_region+ptbin].GetYaxis().SetRangeUser(1e-1,3.0*hists['L1Jet in BX 0'+dist_+key_region+ptbin].GetMaximum()) #L1Jet
        canvas_dist[dist_+key_region].SetLogx()
        legend.Draw()
#        canvas_dist[dist_+key_region].SaveAs('Response_'+dist_+regions[key_region]+'_'+str(len(ptbins))+'.pdf')
        canvas_dist[dist_+key_region].SaveAs('Response_'+dist_+regions[key_region]+'_'+key_label+'.pdf')
