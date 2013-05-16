#include <iostream>
#include <TROOT.h>
#include <TTree.h>
#include <TChain.h>
//#include <TCanvas.h>
//#include  "TMath.h"
#include  <TString.h>
//#include "TSystem.h"
#include <TClonesArray.h>

#include <vector>

#include <TLorentzVector.h>

#include "ExRootAnalysis/ExRootClasses.h"

#include "ExRootAnalysis/ExRootTreeReader.h"
#include "ExRootAnalysis/ExRootTreeWriter.h"
#include "ExRootAnalysis/ExRootTreeBranch.h"
#include "ExRootAnalysis/ExRootResult.h"
#include "ExRootAnalysis/ExRootUtilities.h"

using namespace std;

void swapelectrons(TRootElectron *e1, TRootElectron *e2)
{
  TRootElectron etemp = *e1;
  *e1 = *e2;
  *e2 = etemp;
  return;
}

int main(int argc, char **argv)
{
  void makeTree(vector<TString>);

  int i;
  vector<TString> fn;

  if (argc < 3){
    cout << argv[0] << " <input files> <...> <output file>" << endl;
    exit(0);
  }

  for (i=1; i<argc; i++){
    fn.push_back(argv[i]);
  }

  makeTree(fn);

  return 0;
}


void makeTree(vector<TString> fn)
{
  //  gSystem->Load("/home/eckel/local/MadGraph5/ExRootAnalysis/lib/libExRootAnalysis");
  //  gSystem->Load("libPhysics");

  //  Load("/home/eckel/local/MadGraph5/ExRootAnalysis/lib/libExRootAnalysis");
  //  Load("libPhysics");

  void swapelectrons(TRootElectron *, TRootElectron *);
  
  Double_t pi = TMath::Pi();

  //  TString fn = "/home/eckel/local/MadGraph5/WWbackground/Events/run_ww1_pgs_events.root";

  int i,j,nmet, n_matching;

  int nfiles = fn.size() - 1;

  // Create chain of root trees
  TChain chain("LHCO");

  for (i=0; i<nfiles; i++){
    chain.Add(fn[i]);
  }

  //  chain.Add(fn);

  TString fout = fn[nfiles];

  TFile *fp = new TFile(fout,"recreate");

  //  cout << fout << endl;

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t nEvents = treeReader->GetEntries();
  
  // Get pointers to branches used in this analysis
  TClonesArray *branchElec = treeReader->UseBranch("Electron");
  TClonesArray *branchMET = treeReader->UseBranch("MissingET");
  TClonesArray *branchJets = treeReader->UseBranch("Jet");

  TRootElectron *elec1;
  TRootElectron *elec2;
  TRootElectron *elec_temp;
  TRootJet *jet1;
  TLorentzVector vec1, vec2;
  TRootMissingET *met_c;


  TTree *myTree = new TTree("MyTree", "my test tree");
  //  TwoElectronEvent *e = new TwoElectronEvent();
  
  Long64_t nelec;
  Int_t njets;
  Double_t pt1, pt2, met, metPhi, jetpt, phil, dmetPhi;
  Double_t avgEta, leadingEta;
  Double_t opAngle,m,deltaPhi,deltaEta,deltaR,mt2,met_rel;
  Double_t delecPhi, djetPhi, dist;

  Double_t mm = 10000.0;

  //myTree->Branch("Electron1", &elec1);
  //myTree->Branch("Electron2", &elec2);
  //myTree->Branch("MET_Branch", &branchMET);
  //myTree->Branch("Jet_Branch", &branchJets);
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
  //  myTree->Branch("avgEta", &avgEta, "avgEta/D");

  //  Int_t nevent = LHCO->GetEntries();
  cout << nEvents << endl;

  n_matching = 0;

  for (Long64_t iev=0; iev<nEvents; iev++){

    // Load selected branches with data from specified event
    treeReader->ReadEntry(iev);
    nelec = branchElec->GetEntries();
    njets = branchJets->GetEntries();
    nmet = branchMET->GetEntries();
    //    cout << nmet << endl;


    if (nmet > 0) n_matching++;

    if (nelec > 1 && nmet > 0){

      // sort by PT
      elec1 = (TRootElectron *) branchElec->At(0);
      elec2 = (TRootElectron *) branchElec->At(1);
      
      if (elec1->PT < elec2->PT){
	swapelectrons(elec1, elec2);
      }

      for (i=2; i<nelec; i++){
	elec_temp = (TRootElectron *) branchElec->At(i);
	
	if (elec_temp->PT > elec2->PT){
	  swapelectrons(elec_temp, elec2);
	  if (elec2->PT > elec1->PT){
	    swapelectrons(elec1,elec2);
	  }
	}
      }

      // Eta calculations
      leadingEta = elec1->Eta;
      avgEta = (elec1->Eta + elec2->Eta)/2.0;

      met_c = (TRootMissingET *) branchMET->At(0);

      vec1.SetPtEtaPhiM(elec1->PT, elec1->Eta, elec1->Phi, 0.0);
      vec2.SetPtEtaPhiM(elec2->PT, elec2->Eta, elec2->Phi, 0.0);

      // MT2 stuff
      mt2 = 2*( vec1.Et()*vec2.Et() + vec1.Px()*vec2.Px() 
		                    + vec1.Py()*vec2.Py() );
      mt2 = TMath::Sqrt(mt2);

      jetpt = -10.0;
      
      for (i=0; i<njets; i++){
	jet1 = (TRootJet *) branchJets->At(i);
	if (jet1->PT > jetpt){
	  jetpt = jet1->PT;
	}
      }
      
      m = (vec1 + vec2).M();
      phil = (vec1+vec2).Phi();
      
      if (phil < 0){
	phil = 2*pi + phil;
      }

      pt1 = elec1->PT;
      pt2 = elec2->PT;
      
      met = met_c->MET;
      metPhi = met_c->Phi;
      
      dmetPhi = TMath::Abs(phil - metPhi);
      
      if (dmetPhi > pi){
	dmetPhi = 2*pi - dmetPhi;
      }
      
      deltaPhi = elec1->Phi - elec2->Phi;
      deltaEta = elec1->Eta - elec2->Eta;
       
      if (TMath::Abs(deltaPhi) > pi){
	opAngle = 2*pi - TMath::Abs(deltaPhi);
      }
      else{
	opAngle = TMath::Abs(deltaPhi);
      }
 
      deltaR   = TMath::Sqrt(opAngle*opAngle + deltaEta*deltaEta);

      // E_T^miss,rel calculation
      
      dist = 100000.;

      // find closest (in terms of deltaphi) object electron/jet to p_T^miss

      // find closest electrons
      for (i=0; i<nelec; i++){
	elec_temp = (TRootElectron *) branchElec->At(i);
	
	delecPhi = TMath::Abs(elec_temp->Phi - metPhi);
      
	if (delecPhi > pi){
	  delecPhi = 2*pi - delecPhi;
	}
      
	if (delecPhi < dist){
	  dist = delecPhi;
	}
      }
      
      // find closest jet
      for (i=0; i<njets; i++){
	jet1 = (TRootJet *) branchJets->At(i);
	
	djetPhi = TMath::Abs(jet1->Phi - metPhi);
      
	if (djetPhi > pi){
	  djetPhi = 2*pi - djetPhi;
	}
      
	if (djetPhi < dist){
	  dist = djetPhi;
	}
      }

      if (dist >= pi/2){
	met_rel = met;
      }
      else {
	met_rel = met * TMath::Sin(dist);
      }
     
      myTree->Fill();

    }



    
  }
  
  cout << n_matching << endl;

  Long64_t nevents_2elec = myTree->GetEntries();
  cout << nevents_2elec << endl;


  myTree->Write();
  

  //  return myTree;

  //  myTree->SetDirectory(0);
  //  myTree->Draw("MET","");

  fp->Close();
}


