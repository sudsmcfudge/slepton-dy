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

  TTree *backTree = (TTree *) fp.Get("MyTree");

  Int_t n;

  // ATLAS paper cuts

  TCut c_mll = "Mll > 91.2 + 10.0 || Mll < 91.2 - 10.0";
  TCut c_jet = "max_jetpt < 30.0";
  TCut c_metrel = "met_rel > 40";
  TCut c_mt2 = "mt2 > 90";

  TCut current_cut = "";

  n = backTree->Draw("mt2",c_jet+c_mll+c_metrel+c_mt2); 

  cout << n << endl;

  fp.Close();


  return 0;
  

}
