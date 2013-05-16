#include <iostream>
#include <fstream>
#include "TLimit.h"
#include "TConfidenceLevel.h"
#include "TLimitDataSource.h"
#include "TH1F.h"
//#include <assert>

using namespace std;

int main(int argc, char *argv[])
{
  double mslep, mchi, sigma_pb;
  int n_cuts, n_matched, n_gen, i, nlen;

  double background_err;

  ifstream myfile;

  int N = 200;

  double mslep_array[N];
  double mchi_array[N];
  int n_cuts_array[N];
  int n_matched_array[N];
  double sigma_array[N]; // in fb

  double signal[N], data, background,lum;
  double cls,e_cls;
  double cl[N];
  double exp_cl[N];

  //  assert(argc == 2);

  myfile.open(argv[1]);

  i = 0;

  while (myfile >> mslep){
    myfile >> mchi;
    myfile >> n_cuts;
    myfile >> n_matched;
    myfile >> n_gen;
    myfile >> sigma_pb;

    mslep_array[i] = mslep;
    mchi_array[i] = mchi;
    n_cuts_array[i] = n_cuts;
    n_matched_array[i] = n_matched;
    sigma_array[i] = sigma_pb*1000.0;
    i++;
  }

  myfile.close();

  nlen = i;

  lum = 4.7; // in fb^-1

  background = 9.2;
  background_err = 1.8;
  data = 7.0;

  TH1F* sh = new TH1F("signal", "", 1, 0,1);
  TH1F* bh = new TH1F("background", "", 1, 0,1);
  TH1F* dh = new TH1F("data", "", 1, 0,1);

  bh->SetBinContent(1,background);
  bh->SetBinError(1,background_err);

  dh->SetBinContent(1,data);



  for (i=0; i<nlen; i++){
    
    //    cout << lum * sigma_array[i] / n_matched_array[i]<< endl;

    signal[i] = ((double) n_cuts_array[i]) * lum / \
      (n_matched_array[i] / sigma_array[i]);
    
    sh->SetBinContent(1,signal[i]);
    //    sh->SetBinError(1,1);

    TLimitDataSource *mydatasource = new TLimitDataSource(sh, bh, dh);
    TConfidenceLevel *myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
    //    TConfidenceLevel *myconfidence = TLimit::ComputeLimit(mydatasource, 50000, kTRUE);
  
    cls = myconfidence->CLs();
    e_cls = myconfidence->GetExpectedCLs_b();

    cl[i] = 1.0 - cls;
    exp_cl[i] = 1.0 - e_cls;    

    cout << mslep_array[i] << " " << mchi_array[i] << " " << cl[i] << " " << exp_cl[i] << endl;

    delete mydatasource;
    delete myconfidence;
  }


  
}
