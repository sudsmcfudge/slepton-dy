//#include <iostream>
//#include <TH1F.h>
//#include <TLimit.h>

//using namespace std;

//int main(int argc, char *argv[])
{
  double mslep, mchi, sigma_pb;
  int n_cuts, n_matched, n_gen, i, nlen;

  ifstream myfile;

  N = 100;

  double mslep_array[N];
  double mchi_array[N];
  int n_cuts_array[N];
  int n_matched_array[N];
  double sigma_array[N]; // in fb

  double signal[N], data, background,lum;
  double cls,e_cls;
  double cl[N];
  double exp_cl[N];

  myfile.open("binoLSP_ATLAS_table.dat");

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

    //cout << signal[i] << " " << cl[i] << " " << exp_cl[i] << endl;

    delete mydatasource;
    delete myconfidence;
  }


  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t bwstops[NRGBs] = { 1.00, 0.84, 0.61, 0.34, 0.00 };
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  //  TColor::CreateGradientColorTable(NRGBs, stops, stops, stops, stops, NCont);
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

  /*
  int nbinsx=12;
  int nbinsy=6;

  double ymin=15;
  double ymax=75;
  double xmin=75;
  double xmax=195;
  */

  int nbinsx=22;
  int nbinsy=11;

  double ymin=15;
  double ymax=125;
  double xmin=-5;
  double xmax=215;


  int bin;

  TCanvas *c1 = new TCanvas();

  TH2D *contour = new TH2D("contour","Luminosity [fb^{-1}]",nbinsx,xmin,xmax,nbinsy,ymin,ymax);

  /*  
  for (i=0; i<nlen; i++){
    if (cl[i] < 1 && cl[i] > 0.95){
      bin=contour->Fill(mslep_array[i],mchi_array[i],1.0 - cl[i]);
      cout << mslep_array[i] << " " << 1.0 - cl[i] << endl;
    }
  }
  */
  
  for (i=0; i<nlen; i++){
    //    if (exp_cl[i] < 1 && exp_cl[i] > 0.3){
    bin=contour->Fill(mslep_array[i],mchi_array[i],1.0 - exp_cl[i]);
    cout << mslep_array[i] << " " << mchi_array[i] << " " << cl[i] << " " << exp_cl[i] << endl;
    //    }
  }
  

  contour->SetStats(false);
  c1->SetLogz();

  contour->SetMinimum(0.0);
  contour->SetMaximum(0.05);
  contour->Draw("COLZ");


  /*

  c1->SetLogz();
  c1->SetBottomMargin(0.15);
  c1->SetRightMargin(0.15);

  c1->SetFillColor(kWhite);
  gStyle->SetTitleX(0.7);
  gStyle->SetCanvasColor(kWhite);
  contour->SetFillColor(kWhite);


  contour->SetMinimum(0.08);
  contour->SetMaximum(8.0e3);
  contour->Draw("COLZ");
  contour->GetXaxis()->SetNdivisions(8, 2, 4);
  contour->GetYaxis()->SetNdivisions(8, 2, 4);
  contour->GetXaxis()->SetTitle("Wino Mass [GeV]");
  contour->GetYaxis()->SetTitle("Slepton Mass [GeV]");
  contour->GetXaxis()->SetTitleOffset(1.25);
  */
  
}
