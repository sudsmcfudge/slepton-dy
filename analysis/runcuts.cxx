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

  if (argc != 2){
    cout << argv[0] << " <input file>" << endl;
    exit(0);
  }

  TString fn = argv[1];
  TFile fp(fn);
  cout << fn << endl;
  //  TFile fp("cmp_run_ww1/eckel_analysis_tree.root");
  TTree *backTree = (TTree *) fp.Get("MyTree");

  //  Double_t pi = TMath::Pi();

  Int_t nBins = 1000;
  Int_t n;

  // Matching Andreev paper

  // N = L * sig

  // sigWW = 70pb * (10.8%)**2
  // sigLL = 0.023204pb * 3 (degenerate sleptons)

  


  // set cuts                                                                
  //  minPT = 50.0;
  //maxPT = 1e5;
  //  minMET = 100.0;
  //maxMET = 1e5;
  //minMll = 0.0;
  //maxMll = 1e5;
  //  mZ = 91.2;
  //  dMll = 10.0;
  //  minDeltaR = 0.3;
  //maxDeltaR = 1e5;
  //minOpAngle = 0.0;
  //  maxOpAngle = 13.0*pi/18.0; //130 deg
  //  minMETPhi = 15.0*pi/18.0; //150 deg
  //maxMETPhi = pi;

  // isolated leptons
  // deltaR < 0.3

  //  ss = TString::Format("%f", minPT);

  //  ss = (TString) minPT;

  //  cout << minPT << endl;
  //  cout << ss << endl;
  
  //  TCut c1 = "Electron.PT > " + ss;
  //  c1.Print();
  //  TCut c2 = "Electron_size == 2";
  //  TCut c3 = "MissingET.MET > 100.0";
  //  TCut c4 = "

  vector<TCut> cuts;

  // Cut #3
  
  TCut c_pt = "PT1 > 50.0 && PT2 > 50.0";
  //TCut c_pt = "PT1 > 50.0";
  TCut c_op = "opAngle < 14.0/18.0*pi";
  TCut c_mll = "Mll > 91.2 + 10.0 || Mll < 91.2 - 10.0";
  TCut c_jet = "max_jetpt < 60.0";
  TCut c_met = "MET > 140.0";
  TCut c_phi = "dmetPhi > 15.0/18.0*pi";
  TCut c_deltaR = "deltaR > 0.4";

  TCut current_cut = "";

  vector<TH1F*> histos;

  //  TH1F *hist = new TH1F("no cuts", "no cuts", nBins, 0, 1000);

  TH1F *htemp,*hnew;

  n = backTree->Draw("MET>>hist(1000,0,500)", current_cut);
  //  cout << n << endl; //" " << n*scale_w << " " << endl;
  htemp = (TH1F*)gDirectory->Get("hist");
  TH1F *hist = (TH1F*)htemp->Clone("no cuts");
  //  cout << hist->GetNbinsX() << " " << hist->GetXaxis()->GetXmin() << " " <<  hist->GetXaxis()->GetXmax() << endl;
  histos.push_back(hist);
  
  cuts.push_back(c_pt);
  cuts.push_back(c_op);
  cuts.push_back(c_deltaR);
  cuts.push_back(c_mll);
  cuts.push_back(c_met);
  cuts.push_back(c_phi);
  cuts.push_back(c_jet);  

  for (i=0; i<((int)cuts.size()); i++){
    current_cut = "";
    //    current_cut += c_jet;
    for (j=0; j<=i; j++){
      current_cut += cuts[j];
    }
    //    current_cut += cuts[i];

    //TH1F *hist = new TH1F("","", nBins, 0, 1000);

    //    current_cut.Print();

    n = backTree->Draw("max_jetpt>>hist(1000,0,500)",current_cut,"");
    cout << n << endl; // " " << n*scale_w << " " << endl;
    htemp = (TH1F*)gDirectory->Get("hist");
    TH1F *hist = (TH1F*)htemp->Clone(cuts[i]);
    //    cout << hist->GetNbinsX() << " " << hist->GetXaxis()->GetXmin() << " " <<  hist->GetXaxis()->GetXmax() << endl;
    //    hist = (TH1F*)gDirectory->Get("hist");
    histos.push_back(hist);
  }

  
  
  TCanvas *c1 = new TCanvas("mycanvas","WW cuts", 1680, 1050);
  c1->Divide(4,2);

  //  backTree->SetDirectory(0);

  for (i=0; i<((int)histos.size()); i++){
    c1->cd(i+1);
    hnew = histos[i];
    if (i>0){
      hnew->SetTitle(cuts[i-1]);
    }
    //      hnew->GetXaxis()->SetRangeUser(0,100);
    hnew->SetDirectory(0);
    //hnew->Draw("");
    histos[i]->SetDirectory(0);
    histos[i]->Draw();
  }
  
  //  cout << endl;

  //  for (i=0; i<120; i++){
  //    cout <<  histos[histos.size()-1]->GetBinContent(i) << endl;
  //  }

  //  TH1F *h = new TH1F("h","",100,0,1000);
  //  TH1F *h_signal = new TH1F("h_signal","",100,0,nBins);
  //  TH1F *h_back = new TH1F("h_back","",100,0,nBins);

  //  cout << signalTree->Draw("MET>>h_signal", c_pt+c_op+c_mll+c_jet+c_met+c_phi) << endl;
  //  backTree->Draw("MET>>h_back", current_cut);
  //  h_back->SetDirectory(0);
  //  h_back->Draw();


  //  cout << N_W << " " << N_slep << endl;
  

  //h_signal->Scale(N_slep/N);
  //h_signal->SetLineColor(4);
  //h_signal->SetFillColor(4);
  //h_back->Scale(scale_w);
  //  h_back->SetLineColor(2);
  //  h_back->SetFillColor(2);
  //h_signal->Draw("same");

  c1->Print(fn + "_out.eps");

  fp.Close();


  return 0;
  

}
