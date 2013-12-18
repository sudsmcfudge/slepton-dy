#include <iostream>
#include <TTree.h>
#include <TCanvas.h>
#include <vector>
#include <TMath.h>
#include <TCut.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>

using namespace std;

int main(int argc, char *argv[])
{
  int i,j;

  if (argc != 2) {
    cout << argv[0] << " <input file>" << endl;
    exit(0);
  }

  TString fn = argv[1];
  TFile fp(fn);
  cout << fn << endl;
  
  TTree *backTree = (TTree *) fp.Get("MyTree");

  Int_t n1,n2;

  /*
  myTree->Branch("max_jetpt", &jetpt, "jetpt/D");
  myTree->Branch("njets", &njets, "njets/I");
  myTree->Branch("PT1", &pt1, "pt1/D");
  myTree->Branch("PT2", &pt2, "pt2/D");
  myTree->Branch("MET", &met, "met/D");
  myTree->Branch("MET_phi", &metPhi, "metPhi/D");
  myTree->Branch("opAngle", &opAngle, "opAngle/D");
  myTree->Branch("Mll", &m, "m/D");
  myTree->Branch("deltaR", &deltaR, "deltaR/D");
  myTree->Branch("phil", &phil, "phil/D");
  myTree->Branch("dmetPhi",&dmetPhi,"dmetPhi/D");

  myTree->Branch("mt2",&mt2,"mt2/D");
  myTree->Branch("met_rel",&met_rel,"met_rel/D");
  

  // investigate eta distributions
  myTree->Branch("avgEta", &avgEta, "avgEta/D");
  myTree->Branch("leadingEta", &leadingEta, "leadingEta/D");
  */


  // Leftover Selection Cuts
  
  // Jets
  TCut c_jet = "max_jetpt <= 20.0";

  // Electron && Muon
  TCut c_pt = "PT1 > 10.0 && PT2 > 10.0";
  TCut c_mll = "Mll > 20.0";

  // Electron
#ifndef USEMUON

  TCut c_deltaR = "deltaR >= 0.1";

#endif

  // Muon
#ifdef USEMUON

  TCut c_deltaR = "deltaR >= 0.05";

#endif


  // ATLAS paper cuts

  TCut c_Zveto = "Mll > 91.2 + 10.0 || Mll < 91.2 - 10.0";
  TCut c_metrel = "met_rel > 40";
  TCut c_mt2_90 = "mt2 > 90";
  TCut c_mt2_110 = "mt2 > 110";

  TCut generic_cuts = c_jet+c_pt+c_mll+c_deltaR+c_Zveto+c_metrel;

  //  n = backTree->Draw("mt2",c_jet+c_mll+c_metrel+c_mt2); 
  n1 = backTree->Draw("mt2",generic_cuts+c_mt2_90); 
  n2 = backTree->Draw("mt2",generic_cuts+c_mt2_110); 

  if (n1 > n2){
    cout << n1 << endl;
  }
  else {
    cout << n2 << endl;
  }

  fp.Close();


  return 0;
  

}
