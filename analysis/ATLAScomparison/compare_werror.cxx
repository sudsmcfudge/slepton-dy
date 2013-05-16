
{
  //diboson
  //549996
  //426493
  //366476

  Int_t n_diboson,n_ttbar,n_slep1,n_slep2,n_ww;
  Int_t ncut_diboson,ncut_ttbar,ncut_slep1,ncut_slep2;
  Double_t lum,diboson_xs,diboson_scale,ttbar_xs,ttbar_scale;
  Double_t slep1_xs,slep1_scale,slep2_xs,slep2_scale;
  Double_t ww_xs,ww_scale;

  Double_t a,b,c,aaa;
  double w, sig, wsum;

  int i;

  Double_t ttbar_err, ww_err,err,sum;

  TFitResultPtr r;

  //  TString fn1 = "../tt_7TeVx100.root";
  //  TString fn2 = "../diboson_7TeVx10.root";
  TString fn1 = "../tt_comparison/fiducialx100.root";
  TString fn2 = "../diboson_fiducial_x10.root";
  TString fn3 = "../signal_mslep130_mchi20.root";
  TString fn4 = "../signal_mslep190_mchi100.root";
  //  TString fn5 = "ww_mt2_CMS.root";
  //  TString fn5 = "../ww_comparison/fiducial_xqcut25.root";
  //  TString fn5 = "../diboson_eeevj.root";

  TFile fp1(fn1);
  TFile fp2(fn2);
  TFile fp3(fn3);
  TFile fp4(fn4);
  //  TFile fp5(fn5);
  
  TTree *ttbarTree = (TTree *) fp1.Get("MyTree");
  TTree *dibosonTree   = (TTree *) fp2.Get("MyTree");
  TTree *slep1Tree   = (TTree *) fp3.Get("MyTree");
  TTree *slep2Tree   = (TTree *) fp4.Get("MyTree");

  // mt2 distribution is wrong for 3e state, different equation
  //  TTree *diboson_3eTree   = (TTree *) fp5.Get("MyTree"); 

  //  TCut c_pt = "PT1 > 50.0 && PT2 > 50.0";

  //  TCut c_pt = "PT1 > 30.0 && PT2 > 30.0";
  //  TCut c_op = "opAngle < 14.0/18.0*pi";
  TCut c_mll = "Mll > 91.2 + 10.0 || Mll < 91.2 - 10.0";
  TCut c_jet = "max_jetpt < 30.0";

  TCut c_metrel = "met_rel > 40";
  TCut c_mt2 = "mt2 > 90";

  //  TCut c_met = "MET > 140.0";
  //  TCut c_phi = "dmetPhi > 15.0/18.0*pi";
  //  TCut c_deltaR = "deltaR > 0.4";

  gStyle->SetOptFit(1);
  gStyle->SetOptStat(1000000001);
  gStyle->SetStatH(0.15);
  gStyle->SetStatW(0.1);

  TCanvas *c1 = new TCanvas();
  c1->Divide(1,2);
  c1->cd(1);
  //  TH1F *h1 = new TH1F("diboson","",25,0,250);
  //  TH1F *h2 = new TH1F("ttbar","",25,0,250);

  ncut_diboson = dibosonTree->Draw("mt2>>diboson_hist_mt2(25,0,250)",c_jet+c_mll+c_metrel,"wts");
  ncut_ttbar = ttbarTree->Draw("mt2>>ttbar_hist_mt2(25,0,250)",c_jet+c_mll+c_metrel, "wts");
  ncut_slep1 = slep1Tree->Draw("mt2>>slep1_hist_mt2(25,0,250)",c_jet+c_mll+c_metrel, "wts");
  ncut_slep2 = slep2Tree->Draw("mt2>>slep2_hist_mt2(25,0,250)",c_jet+c_mll+c_metrel, "wts");

  // ratios from ATLAS paper "after cuts"
  //  double ee_to_ossf_diboson = 2.29;
  //  double ee_to_ossf_ttbar   = 2.62;

  //  double ee_to_osall_diboson = 3.22;
  //  double ee_to_osall_ttbar   = 4.56;
  

  // from pt ratio plots "before cuts"
  double ee_to_ossf_diboson = 2.55287;
  double ee_to_ossf_diboson_err = 0.0877609;

  double ee_to_ossf_ttbar   = 2.35311;
  double ee_to_ossf_ttbar_err = 0.0578718;

  double ee_to_osall_diboson = 4.2136;
  double ee_to_osall_diboson_err = 0.12846;

  double ee_to_osall_ttbar   = 4.7088;
  double ee_to_osall_ttbar_err   = 0.10605;

  // stat only
  
  //  double ee_to_ossf_diboson_err = ee_to_ossf_diboson	\
  //    * sqrt(3.05/12.6/12.6 + 1.3/5.5/5.5);
  //  double ee_to_ossf_ttbar_err = ee_to_ossf_ttbar	\
  //    * sqrt(1.8*1.8/6.8/6.8 + 1.2*1.2/2.6/2.6);
  //  double ee_to_osall_ttbar_err = ee_to_osall_ttbar	\
  //  * sqrt(4.8*4.8/96.2/96.2 + 2.3*2.3/21.1/21.1);
  
  // stat + sys in quadrature
  /*
  double ee_to_ossf_diboson_err = ee_to_ossf_diboson \
    * sqrt(8.27/12.6/12.6+4.35/5.5/5.5);
  double ee_to_ossf_ttbar_err = ee_to_ossf_ttbar \
    * sqrt(2.92*2.92/6.8/6.8+1.77*1.77/2.6/2.6);
  double ee_to_osall_ttbar_err = ee_to_osall_ttbar \
    * sqrt(893.29/96.2/96.2+22.93/21.1/21.1);
  */

  diboson_hist_mt2->Sumw2();  
  ttbar_hist_mt2->Sumw2();
  slep1_hist_mt2->Sumw2();
  slep2_hist_mt2->Sumw2();

  lum = 4.7;

  slep1_xs = 21.9;
  n_slep1 = 31334;
  slep1_scale = lum * slep1_xs / n_slep1;

  slep2_xs = 5.4;
  n_slep2 = 30153;
  slep2_scale = lum * slep2_xs / n_slep2;
  
  //  diboson_xs = 390.0;
  //  n_diboson = 394890;
  diboson_xs = 264.07;
  n_diboson = 426493;
  diboson_scale = lum * diboson_xs / n_diboson;

  //  diboson_3e_xs = 23.9898;
  //  n_diboson_3e = 810444;
  //  diboson_3e_scale = lum * diboson_3e_xs / n_diboson_3e;

  //  diboson_scale /= 1.5; // scaling from ww_paper

  //  ww_xs = 323.0;
  //  n_ww = 397519;
  //  ww_scale = lum * ww_xs / n_ww;
  
  //  ww_xs = 323.0;
  //  n_ww = 397712;
  ww_xs = 216.98;
  n_ww = 398336;
  ww_scale = lum * ww_xs / n_ww;

  TH1F *scale_hist_mt2 = new TH1F("scale", "", 25, 0,250);
  for (i=1; i<=25; i++){
    scale_hist_mt2->SetBinContent(i, ee_to_ossf_diboson);
    scale_hist_mt2->SetBinError(i, ee_to_ossf_diboson_err);
  }

  diboson_hist_mt2->Multiply(scale_hist_mt2);
  diboson_hist_mt2->Scale(diboson_scale);

  //  diboson_hist_mt2->Sumw2();
  //  diboson_hist_mt2->Scale(diboson_scale*2); // factor of 2 since OS-SF
  //  diboson_hist_mt2->Scale(diboson_scale*ee_to_ossf_diboson);
  //  TArrayD *ar_ww = diboson_hist_mt2->GetSumw2();
  //  diboson_hist_mt2->SetFillColor(5);

  c1_1->SetLogy();

  //  ttbar_xs = 1080.0;
  //  n_ttbar = 1852138;
  ttbar_xs = 826.99;
  n_ttbar = 2228059;

  ttbar_scale = lum * ttbar_xs / n_ttbar;


  for (i=1; i<=25; i++){
    scale_hist_mt2->SetBinContent(i, ee_to_ossf_ttbar);
    scale_hist_mt2->SetBinError(i, ee_to_ossf_ttbar_err);
  }

  ttbar_hist_mt2->Multiply(scale_hist_mt2);
  ttbar_hist_mt2->Scale(ttbar_scale);


  //  ttbar_scale /= 0.8;

  //  ttbar_scale *= 1/0.4553/.7/.7;

  //  ttbar_hist_mt2->Sumw2();
  //  ttbar_hist_mt2->Scale(ttbar_scale*2); // factor of 2 since OS-SF
  //  ttbar_hist_mt2->Scale(ttbar_scale*ee_to_ossf_ttbar);
  //  ttbar_hist_mt2->SetFillColor(2);
  //  TArrayD *ar_tt = ttbar_hist_mt2->GetSumw2();

  //  MAY NEED TO CHANGE THE ERROR CALCULATED HERE!!!
  //
  // diboson_hist_mt2->SetFillColor(5);
  diboson_hist_mt2->SetFillColor(4);
  aaa = diboson_hist_mt2->GetBinContent(25) + diboson_hist_mt2->GetBinContent(26);
  diboson_hist_mt2->SetBinContent(25, aaa);
  //  diboson_hist_mt2->Draw();


  // change these scalings too
 // factor of 2 since OS-SF (add later)
  slep1_hist_mt2->Scale(slep1_scale);
  slep1_hist_mt2->SetLineColor(2);
  slep1_hist_mt2->SetLineStyle(2);
  //  slep1_hist_mt2->Draw("same");

  slep2_hist_mt2->Scale(slep2_scale);
  slep2_hist_mt2->SetLineColor(4);
  slep2_hist_mt2->SetLineStyle(2);
  //  slep2_hist_mt2->Draw("same");

  // comparisons
  char *blah;
  float xx,yy,xx2,yy2,spread,mean;

  // total mt2 hist
  char *fn_total_mt2 = "fig/fig_01d_total.csv";
  FILE *fp_total_mt2 = fopen(fn_total_mt2, "r");

  fscanf(fp_total_mt2, "%s\n", &blah);
  //  cout << blah << endl;

  // upper error "hist"
  char *fn_error_mt2 = "fig/fig_01d_error.csv";
  FILE *fp_error_mt2 = fopen(fn_error_mt2, "r");

  fscanf(fp_error_mt2, "%s\n", &blah);
  //  cout << blah << endl;
  
  TH1F *h_mt2_total = new TH1F("total_mt2", "MT2", 25,0,250);

  for (i=1; i<=25; i++){
    fscanf(fp_total_mt2, "%f,%f\n", &xx,&yy);
    fscanf(fp_error_mt2, "%f,%f\n", &xx2,&yy2);

    //    cout << i << " " << xx << " " << yy << endl;

    h_mt2_total->SetBinContent(i,yy);
    h_mt2_total->SetBinError(i,yy2-yy);
  }

  // empty bin
  h_mt2_total->SetBinContent(24,0);
  h_mt2_total->SetBinError(24,0);

  fclose(fp_total_mt2);
  fclose(fp_error_mt2);
  
  char *fn_c1 = "fig/fig_01d_diboson.csv";
  TH1F *h_mt2_1 = new TH1F("diboson","MT2",25,0,250);
  FILE *fpc1 = fopen(fn_c1,"r");

  fscanf(fpc1,"%s\n",&blah);

  for (i=1; i<=25; i++){
    fscanf(fpc1, "%f,%f\n", &xx,&yy);
    h_mt2_1->SetBinContent(i,yy);
    //    h_mt2_1->SetBinError(i,h_mt2_total->GetBinError(i));
    //    cout << xx << " " << yy << endl;
  }

  h_mt2_1->SetBinContent(24,0);

  fclose(fpc1);

  char *fn_c2 = "fig/fig_01d_singletop.csv";
  TH1F *h_mt2_2 = new TH1F("singletop","",25,0,250);
  FILE *fpc2 = fopen(fn_c2,"r");

  fscanf(fpc2,"%s\n",&blah);

  for (i=1; i<=10; i++){
    fscanf(fpc2, "%f,%f\n", &xx,&yy);
    h_mt2_2->SetBinContent(i,yy);
    //    cout << xx << " " << yy << endl;
  }
  for (i=11; i<=25; i++){
    a = h_mt2_1->GetBinContent(i);
    h_mt2_2->SetBinContent(i,a);
  }

  fclose(fpc2);

  char *fn_c3 = "fig/fig_01d_ttbar.csv";
  TH1F *h_mt2_3 = new TH1F("tt","",25,0,250);
  FILE *fpc3 = fopen(fn_c3,"r");

  fscanf(fpc3,"%s\n",&blah);

  for (i=1; i<=12; i++){
    fscanf(fpc3, "%f,%f\n", &xx,&yy);
    h_mt2_3->SetBinContent(i,yy);
    //    cout << xx << " " << yy << endl;
  }
  for (i=13; i<=25; i++){
    a = h_mt2_2->GetBinContent(i);
    h_mt2_3->SetBinContent(i,a);
  }

  fclose(fpc3);

  h_mt2_1->Sumw2();
  h_mt2_2->Sumw2();
  h_mt2_3->Sumw2();


  TH1F *h_ATLAS_diboson_mt2 = h_mt2_1;
  h_ATLAS_diboson_mt2->SetFillColor(5);
  diboson_hist_mt2->Draw();
  h_ATLAS_diboson_mt2->Draw("same");

  TAxis *axis = h_ATLAS_diboson_mt2->GetYaxis();
  axis->SetRangeUser(0.001,100);

  c1->cd(2);

  TH1F *h_compare_diboson_mt2 = new TH1F("h_mad_diboson_mt2 / h_ATLAS","",25,0,250);

  h_compare_diboson_mt2->Sumw2();
  h_compare_diboson_mt2->Divide(diboson_hist_mt2,h_ATLAS_diboson_mt2,1,1);

  h_compare_diboson_mt2->SetFillColor(5);
  h_compare_diboson_mt2->Draw();

  r = h_compare_diboson_mt2->Fit("pol0","SQ","",0,250);
  par0 = r->Parameter(0);
  err0 = r->ParError(0);

  cout << "diboson_mt2:\t" << par0 << " +/- " << err0 << endl;

  axis = h_compare_diboson_mt2->GetYaxis();
  axis->SetRangeUser(0,2);

  TString fn = "diboson_hist_mt2.eps";
  c1->SaveAs(fn);

  TCanvas *c2 = new TCanvas();
  c2->Divide(1,2);
  c2->cd(1);

  aaa = ttbar_hist_mt2->GetBinContent(25) + ttbar_hist_mt2->GetBinContent(26);
  ttbar_hist_mt2->SetBinContent(25,aaa);

  c1_n2_1->SetLogy();

  ttbar_hist_mt2->Draw();
  ttbar_hist_mt2->SetFillColor(4);

  TH1F *h_ATLAS_ttbar_mt2 = new TH1F("ttbar","MT2",25,0,250);
  h_ATLAS_ttbar_mt2->Sumw2();

  h_ATLAS_ttbar_mt2->Add(h_mt2_3,h_mt2_2,1,-1);
  h_ATLAS_ttbar_mt2->SetFillColor(2);  
  //  h_ATLAS_ttbar_mt2->SetXTitle("MT2");
  h_ATLAS_ttbar_mt2->Draw("same");

  axis = ttbar_hist_mt2->GetYaxis();
  axis->SetRangeUser(0.001,100);


  //  for (i=1; i<=25; i++){
  //    h_ATLAS_ttbar_mt2->SetBinError(i,h_mt2_total->GetBinError(i));
  //  }

  //  ttbar_hist_mt2->Draw("same");

  c2->cd(2);

  TH1F *h_compare_ttbar_mt2 = new TH1F("h_mad_ttbar_mt2 / h_ATLAS","",25,0,250);

  h_compare_ttbar_mt2->Sumw2();
  h_compare_ttbar_mt2->Divide(ttbar_hist_mt2,h_ATLAS_ttbar_mt2,1,1);

  h_compare_ttbar_mt2->SetFillColor(2);
  h_compare_ttbar_mt2->Draw();

  axis = h_compare_ttbar_mt2->GetYaxis();
  axis->SetRangeUser(0,1.5);

  r = h_compare_ttbar_mt2->Fit("pol0","SQ","",0,250);
  par0 = r->Parameter(0);
  err0 = r->ParError(0);

  cout << "ttbar_mt2:\t" << par0 << " +/- " << err0 << endl;

  TString fn = "ttbar_hist_mt2.eps";
  c2->SaveAs(fn);


  // metrel

  // total metrel hist
  char *fn_total_metrel = "fig/fig_01a_total.csv";
  FILE *fp_total_metrel = fopen(fn_total_metrel, "r");

  fscanf(fp_total_metrel, "%s\n", &blah);

  // upper error "hist"
  char *fn_error_metrel = "fig/fig_01a_error.csv";
  FILE *fp_error_metrel = fopen(fn_error_metrel, "r");

  fscanf(fp_error_metrel, "%s\n", &blah);
  
  TH1F *h_metrel_total = new TH1F("total_metrel", "METREL", 31,40,350);

  for (i=1; i<=31; i++){
    fscanf(fp_total_metrel, "%f,%f\n", &xx,&yy);
    fscanf(fp_error_metrel, "%f,%f\n", &xx2,&yy2);

    h_metrel_total->SetBinContent(i,yy);
    h_metrel_total->SetBinError(i,yy2-yy);
  }

  // empty bins (some bins have error?)
  h_metrel_total->SetBinContent(24,0);
  h_metrel_total->SetBinContent(26,0);
  h_metrel_total->SetBinError(26,0);
  h_metrel_total->SetBinContent(29,0);

  fclose(fp_total_metrel);
  fclose(fp_error_metrel);

  TCanvas *c3 = new TCanvas();

  c3->Divide(1,2);
  c3->cd(1);

  TH1F *scale_hist_metrel = new TH1F("scale_metrel","",31,40,350);

  dibosonTree->Draw("met_rel>>diboson_hist_metrel(31,40,350)",c_jet+c_mll,"wts");
  ttbarTree->Draw("met_rel>>ttbar_hist_metrel(31,40,350)",c_jet+c_mll, "wts");
  slep1Tree->Draw("met_rel>>slep1_hist_metrel(31,40,350)",c_jet+c_mll, "wts");
  slep2Tree->Draw("met_rel>>slep2_hist_metrel(31,40,350)",c_jet+c_mll, "wts");

  c1_n3_1->SetLogy();

  diboson_hist_metrel->Sumw2();
  ttbar_hist_metrel->Sumw2();
  slep1_hist_metrel->Sumw2();
  slep2_hist_metrel->Sumw2();

  for (i=1; i<=31; i++){
    scale_hist_metrel->SetBinContent(i, ee_to_osall_diboson);
    scale_hist_metrel->SetBinError(i, ee_to_osall_diboson_err);
  }

  diboson_hist_metrel->Multiply(scale_hist_metrel);
  diboson_hist_metrel->Scale(diboson_scale);

  for (i=1; i<=31; i++){
    scale_hist_metrel->SetBinContent(i, ee_to_osall_ttbar);
    scale_hist_metrel->SetBinError(i, ee_to_osall_ttbar_err);
  }

  ttbar_hist_metrel->Multiply(scale_hist_metrel);
  ttbar_hist_metrel->Scale(ttbar_scale);

  //  diboson_hist_metrel->Scale(diboson_scale*2);
  //diboson_hist_metrel->Scale(diboson_scale*ee_to_osall_diboson);
  //diboson_hist_metrel->SetFillColor(5);

  //  ttbar_hist_metrel->Scale(ttbar_scale*2);
  //ttbar_hist_metrel->Scale(ttbar_scale*ee_to_osall_ttbar);
  //ttbar_hist_metrel->SetFillColor(2);

  /*
  TH1F *hh3 = new TH1F("MET_rel",c_mll+c_jet,31,40,350);

  hh3->SetXTitle("MET_rel");

  hh3.Add(diboson_hist_metrel,ttbar_hist_metrel);

  hh3->SetFillColor(2);
  hh3->Draw();
  */

  /*
  slep1_hist_metrel->Scale(slep_scale1*2);
  slep1_hist_metrel->SetLineColor(2);
  slep1_hist_metrel->SetLineStyle(2);
  slep1_hist_metrel->Draw("same");

  slep2_hist_metrel->Scale(slep_scale2*2);
  slep2_hist_metrel->SetLineColor(4);
  slep2_hist_metrel->SetLineStyle(2);
  slep2_hist_metrel->Draw("same");
  */   

  char *fn_metrel1 = "fig/fig_01a_diboson.csv";
  TH1F *h_metrel_1 = new TH1F("diboson1","metrel",31,40,350);
  FILE *fp_metrel1 = fopen(fn_metrel1,"r");

  fscanf(fp_metrel1,"%s\n",&blah);

  for (i=1; i<=31; i++){
    fscanf(fp_metrel1, "%f,%f\n", &xx,&yy);
    h_metrel_1->SetBinContent(i,yy);
    //    h_metrel_1->SetBinError(i, h_metrel_total->GetBinError(i));
    //    cout << xx << " " << yy << endl;
  }

  h_metrel_1->SetBinContent(24,0);
  h_metrel_1->SetBinContent(26,0);
  h_metrel_1->SetBinContent(29,0);

  fclose(fp_metrel1);

  char *fn_metrel2 = "fig/fig_01a_singletop.csv";
  TH1F *h_metrel_2 = new TH1F("singletop1","metrel",31,40,350);
  FILE *fp_metrel2 = fopen(fn_metrel2,"r");

  fscanf(fp_metrel2,"%s\n",&blah);

  for (i=1; i<=16; i++){
    fscanf(fp_metrel2, "%f,%f\n", &xx,&yy);
    h_metrel_2->SetBinContent(i,yy);
    //    cout << xx << " " << yy << endl;
  }

  for (i=17; i<=31; i++){
    a = h_metrel_1->GetBinContent(i);
    h_metrel_2->SetBinContent(i,a);
  }

  fclose(fp_metrel2);
  
  char *fn_metrel3 = "fig/fig_01a_ttbar.csv";
  TH1F *h_metrel_3 = new TH1F("ttbar1","metrel",31,40,350);
  FILE *fp_metrel3 = fopen(fn_metrel3,"r");

  fscanf(fp_metrel3,"%s\n",&blah);

  for (i=1; i<=17; i++){
    fscanf(fp_metrel3, "%f,%f\n", &xx,&yy);
    h_metrel_3->SetBinContent(i,yy);
    //    cout << xx << " " << yy << endl;
  }

  for (i=18; i<=31; i++){
    a = h_metrel_1->GetBinContent(i);
    h_metrel_3->SetBinContent(i,a);
  }

  fclose(fp_metrel3);

  h_metrel_1->Sumw2();
  h_metrel_2->Sumw2();
  h_metrel_3->Sumw2();

  TH1F *h_ATLAS_diboson_metrel = h_metrel_1;
  TH1F *h_ATLAS_ttbar_metrel = new TH1F("ttbar2","metrel",31,40,350);

  h_ATLAS_ttbar_metrel->Sumw2();

  h_ATLAS_ttbar_metrel->Add(h_metrel_3,h_metrel_2,1,-1);

  //  for (i=1; i<=31; i++){
  //    h_ATLAS_ttbar_metrel->SetBinError(i, h_metrel_total->GetBinError(i));
  //  }

  diboson_hist_metrel->SetFillColor(4);
  diboson_hist_metrel->Draw();

  h_ATLAS_diboson_metrel->SetFillColor(5);
  h_ATLAS_diboson_metrel->Draw("same");
  
  c3->cd(2);  

  TH1F *h_compare_diboson_metrel = new TH1F("h_mad_diboson / h_ATLAS","",31,40,350);

  h_compare_diboson_metrel->Sumw2();

  h_compare_diboson_metrel->Divide(diboson_hist_metrel,h_ATLAS_diboson_metrel,1,1);

  h_compare_diboson_metrel->SetFillColor(5);
  h_compare_diboson_metrel->Draw();

  axis = h_compare_diboson_metrel->GetYaxis();
  axis->SetRangeUser(0,1.5);

  r = h_compare_diboson_metrel->Fit("pol0","SQ","",40,350);
  par0 = r->Parameter(0);
  err0 = r->ParError(0);

  cout << "diboson_metrel:\t" << par0 << " +/- " << err0 << endl;


  TString fn = "diboson_hist_metrel.eps";
  c3->SaveAs(fn);

  //  cout << "METREL diboson scaling: " << sum/wsum << " +/- " << sqrt(1/wsum) << endl;

    
  TCanvas *c4 = new TCanvas();

  c4->Divide(1,2);
  c4->cd(1);

  c1_n4_1->SetLogy();

  ttbar_hist_metrel->Draw();

  h_ATLAS_ttbar_metrel->SetFillColor(2);
  h_ATLAS_ttbar_metrel->Draw("same");
  
  ttbar_hist_metrel->SetFillColor(4);
  ttbar_hist_metrel->Draw("same");

  axis = ttbar_hist_metrel->GetYaxis();
  axis->SetRangeUser(0.001,200);

  c4->cd(2);  

  TH1F *h_compare_ttbar_metrel = new TH1F("h_mad_ttbar / h_ATLAS","",31,40,350);

  h_compare_ttbar_metrel->Sumw2();

  h_compare_ttbar_metrel->Divide(ttbar_hist_metrel,h_ATLAS_ttbar_metrel,1,1);

  h_compare_ttbar_metrel->SetFillColor(5);
  h_compare_ttbar_metrel->Draw();

  axis = h_compare_ttbar_metrel->GetYaxis();
  axis->SetRangeUser(0,1);

  r = h_compare_ttbar_metrel->Fit("pol0","SQ","",40,350);
  par0 = r->Parameter(0);
  err0 = r->ParError(0);

  cout << "ttbar_metrel:\t" << par0 << " +/- " << err0 << endl;

  TString fn = "ttbar_hist_metrel.eps";
  c4->SaveAs(fn);


  //  cout << "METREL ttbar scaling: " << sum/wsum << " +/- " << sqrt(1/wsum) << endl;

  TCanvas *c5 = new TCanvas();

  c5->Divide(1,2);
  c5->cd(1);

  c1_n5_1->SetLogy();

  dibosonTree->Draw("PT1>>diboson_hist_pt(35,0,350)",c_metrel,"wts");
  ttbarTree->Draw("PT1>>ttbar_hist_pt(35,0,350)",c_metrel, "wts");
  slep1Tree->Draw("PT1>>slep1_hist_pt(35,0,350)",c_metrel, "wts");
  slep2Tree->Draw("PT1>>slep2_hist_pt(35,0,350)",c_metrel, "wts");

  diboson_hist_pt->Sumw2();
  ttbar_hist_pt->Sumw2();
  slep1_hist_pt->Sumw2();
  slep2_hist_pt->Sumw2();

  diboson_hist_pt->Scale(diboson_scale);
  diboson_hist_pt->SetFillColor(5);

  ttbar_hist_pt->Scale(ttbar_scale);
  ttbar_hist_pt->SetFillColor(2);

  /*

  TH1F *hhh3 = new TH1F("PT1",c_mll+c_jet+c_metrel,35,0,350);

  hhh3->SetXTitle("P_T (leading electron)");

  hhh3.Add(diboson_hist_pt,ttbar_hist_pt);

  hhh3->SetFillColor(2);
  hhh3->Draw();

  diboson_hist_pt->Draw("same");

  slep1_hist_pt->Scale(slep_scale1);
  slep1_hist_pt->SetLineColor(2);
  slep1_hist_pt->SetLineStyle(2);
  slep1_hist_pt->Draw("same");

  slep2_hist_pt->Scale(slep_scale2);
  slep2_hist_pt->SetLineColor(4);
  slep2_hist_pt->SetLineStyle(2);
  slep2_hist_pt->Draw("same");

*/  

  // PT

  // total pt hist
  char *fn_total_pt = "fig/figaux_03a_total.csv";
  FILE *fp_total_pt = fopen(fn_total_pt, "r");

  fscanf(fp_total_pt, "%s\n", &blah);

  // upper error "hist"
  char *fn_error_pt = "fig/figaux_03a_error.csv";
  FILE *fp_error_pt = fopen(fn_error_pt, "r");

  fscanf(fp_error_pt, "%s\n", &blah);
  
  TH1F *h_pt_total = new TH1F("total_pt", "PT", 35,0,350);

  for (i=2; i<=35; i++){
    fscanf(fp_total_pt, "%f,%f\n", &xx,&yy);
    fscanf(fp_error_pt, "%f,%f\n", &xx2,&yy2);

    h_pt_total->SetBinContent(i,yy);
    h_pt_total->SetBinError(i,yy2-yy);
  }

  // empty bins (some bins have error?)
  h_pt_total->SetBinContent(1,0);
  h_pt_total->SetBinError(1,0);

  fclose(fp_total_pt);
  fclose(fp_error_pt);


  char *fn_d1 = "fig/figaux_03a_diboson.csv";
  TH1F *h_pt_1 = new TH1F("diboson2","PT",35,0,350);
  FILE *fpd1 = fopen(fn_d1,"r");

  fscanf(fpd1,"%s\n",&blah);

  for (i=1; i<=35; i++){
    fscanf(fpd1, "%f,%f\n", &xx,&yy);
    h_pt_1->SetBinContent(i,yy);
    //    h_pt_1->SetBinError(i,h_pt_total->GetBinError(i));
    //    cout << xx << " " << yy << endl;
  }

  h_pt_1->SetBinContent(1,0);

  fclose(fpd1);

  char *fn_d2 = "fig/figaux_03a_singletop.csv";
  TH1F *h_pt_2 = new TH1F("singletop2","PT",35,0,350);
  FILE *fpd2 = fopen(fn_d2,"r");

  fscanf(fpd2,"%s\n",&blah);

  for (i=1; i<=35; i++){
    fscanf(fpd2, "%f,%f\n", &xx,&yy);
    h_pt_2->SetBinContent(i,yy);
    //    cout << xx << " " << yy << endl;
  }

  h_pt_2->SetBinContent(1,0);

  h_pt_2->SetBinContent(29,h_pt_1->GetBinContent(29));
  h_pt_2->SetBinContent(33,h_pt_1->GetBinContent(33));
  h_pt_2->SetBinContent(35,h_pt_1->GetBinContent(35));

  fclose(fpd2);

  char *fn_d3 = "fig/figaux_03a_ttbar.csv";
  TH1F *h_pt_3 = new TH1F("ttbar3","PT",35,0,350);
  FILE *fpd3 = fopen(fn_d3,"r");

  fscanf(fpd3,"%s\n",&blah);

  for (i=1; i<=35; i++){
    fscanf(fpd3, "%f,%f\n", &xx,&yy);
    h_pt_3->SetBinContent(i,yy);
    //    cout << xx << " " << yy << endl;
  }

  h_pt_3->SetBinContent(1,0);

  h_pt_3->SetBinContent(31,h_pt_2->GetBinContent(31));
  h_pt_3->SetBinContent(32,h_pt_2->GetBinContent(32));
  h_pt_3->SetBinContent(34,h_pt_2->GetBinContent(34));
  h_pt_3->SetBinContent(35,h_pt_2->GetBinContent(35));

  fclose(fpd3);

  h_pt_1->Sumw2();
  h_pt_2->Sumw2();
  h_pt_3->Sumw2();

  TH1F *h_ATLAS_diboson_pt = h_pt_1;

  TH1F *h_ATLAS_ttbar_pt = new TH1F("ttbarpt", "PT", 35,0,350);
  h_ATLAS_ttbar_pt->Add(h_pt_3,h_pt_2,1,-1);

  //  for (i=1; i<=35; i++){
  //    h_ATLAS_ttbar_pt->SetBinError(i,h_pt_total->GetBinError(i));
  //  }

  diboson_hist_pt->Draw();

  h_ATLAS_diboson_pt->SetFillColor(5);
  diboson_hist_pt->SetFillColor(4);
  h_ATLAS_diboson_pt->Draw("same");
  //  diboson_hist_pt->Draw("same");

  c5->cd(2);

  TH1F *h_compare_diboson_pt = new TH1F("h_mad_diboson_pt / h_ATLAS","",35,0,350);

  h_compare_diboson_pt->Sumw2();

  h_compare_diboson_pt->Divide(diboson_hist_pt,h_ATLAS_diboson_pt,1,1);

  h_compare_diboson_pt->SetFillColor(5);
  h_compare_diboson_pt->Draw();

  axis = h_compare_diboson_pt->GetYaxis();
  axis->SetRangeUser(0,3);

  r = h_compare_diboson_pt->Fit("pol0","SQ","",0,350);
  par0 = r->Parameter(0);
  err0 = r->ParError(0);

  cout << "diboson_pt:\t" << par0 << " +/- " << err0 << endl;

  TString fn = "diboson_hist_pt.eps";
  c5->SaveAs(fn);

  TCanvas *c6 = new TCanvas();
  c6->Divide(1,2);
  c6->cd(1);

  c1_n6_1->SetLogy();

  h_ATLAS_ttbar_pt->SetFillColor(2);  
  //  h_ATLAS_ttbar_pt->SetXTitle("PT");

  axis = h_ATLAS_ttbar_pt->GetYaxis();
  axis->SetRangeUser(0.001,1000);

  ttbar_hist_pt->SetFillColor(4);
  ttbar_hist_pt->Draw();
  h_ATLAS_ttbar_pt->Draw("same");

  c6->cd(2);

  TH1F *h_compare_ttbar_pt = new TH1F("h_mad_ttbar_pt / h_ATLAS","",35,0,350);

  h_compare_ttbar_pt->Sumw2();

  h_compare_ttbar_pt->Divide(ttbar_hist_pt,h_ATLAS_ttbar_pt,1,1);

  h_compare_ttbar_pt->SetFillColor(2);
  h_compare_ttbar_pt->Draw();

  axis = h_compare_ttbar_pt->GetYaxis();
  axis->SetRangeUser(0,1);
  
  r = h_compare_ttbar_pt->Fit("pol0","SQ","",0,350);
  par0 = r->Parameter(0);
  err0 = r->ParError(0);

  cout << "ttbar_pt:\t" << par0 << " +/- " << err0 << endl;

  TString fn = "ttbar_hist_pt.eps";
  c6->SaveAs(fn);


  char *fn_e1 = "fig/figaux_03b_diboson.csv";
  TH1F *h_pt_mu1 = new TH1F("diboson3","PT",35,0,350);
  FILE *fpe1 = fopen(fn_e1,"r");

  fscanf(fpe1,"%s\n",&blah);

  for (i=2; i<=35; i++){
    fscanf(fpe1, "%f,%f\n", &xx,&yy);
    h_pt_mu1->SetBinContent(i,yy);
    //    cout << xx << " " << yy << endl;
  }

  h_pt_mu1->SetBinContent(1,0);

  fclose(fpe1);

  char *fn_e2 = "fig/figaux_03b_singletop.csv";
  TH1F *h_pt_mu2 = new TH1F("singletop3","PT",35,0,350);
  FILE *fpe2 = fopen(fn_e2,"r");

  fscanf(fpe2,"%s\n",&blah);

  for (i=2; i<=35; i++){
    fscanf(fpe2, "%f,%f\n", &xx,&yy);
    h_pt_mu2->SetBinContent(i,yy);
    //    cout << xx << " " << yy << endl;
  }

  h_pt_mu2->SetBinContent(1,0);

  h_pt_mu2->SetBinContent(29,h_pt_mu1->GetBinContent(29));
  h_pt_mu2->SetBinContent(30,h_pt_mu1->GetBinContent(33));

  fclose(fpe2);

  char *fn_e3 = "fig/figaux_03b_ttbar.csv";
  TH1F *h_pt_mu3 = new TH1F("ttbar4","PT",35,0,350);
  FILE *fpe3 = fopen(fn_e3,"r");

  fscanf(fpe3,"%s\n",&blah);

  for (i=2; i<=35; i++){
    fscanf(fpe3, "%f,%f\n", &xx,&yy);
    h_pt_mu3->SetBinContent(i,yy);
    //    cout << xx << " " << yy << endl;
  }

  h_pt_mu3->SetBinContent(1,0);

  h_pt_mu3->SetBinContent(30,h_pt_mu2->GetBinContent(31));
  h_pt_mu3->SetBinContent(34,h_pt_mu2->GetBinContent(35));

  fclose(fpe3);

  h_pt_mu1->Sumw2();
  h_pt_mu2->Sumw2();
  h_pt_mu3->Sumw2();

  TH1F *h_ATLAS_diboson_pt_mu = h_pt_mu1;

  TH1F *h_ATLAS_ttbar_pt_mu = new TH1F("ttbarpt_mu", "PT", 35,0,350);
  h_ATLAS_ttbar_pt_mu->Sumw2();

  h_ATLAS_ttbar_pt_mu->Add(h_pt_mu3,h_pt_mu2,1,-1);



  char *fn_f1 = "fig/figaux_03c_diboson.csv";
  TH1F *h_pt_emu1 = new TH1F("diboson4","PT",35,0,350);
  FILE *fpf1 = fopen(fn_f1,"r");

  fscanf(fpf1,"%s\n",&blah);

  for (i=2; i<=35; i++){
    fscanf(fpf1, "%f,%f\n", &xx,&yy);
    h_pt_emu1->SetBinContent(i,yy);
  }

  h_pt_emu1->SetBinContent(1,0);
  h_pt_emu1->SetBinContent(33,0);

  fclose(fpf1);

  char *fn_f2 = "fig/figaux_03c_singletop.csv";
  TH1F *h_pt_emu2 = new TH1F("singletop4","PT",35,0,350);
  FILE *fpf2 = fopen(fn_f2,"r");

  fscanf(fpf2,"%s\n",&blah);

  for (i=2; i<=35; i++){
    fscanf(fpf2, "%f,%f\n", &xx,&yy);
    h_pt_emu2->SetBinContent(i,yy);
  }

  h_pt_emu2->SetBinContent(1,0);
  h_pt_emu2->SetBinContent(35,h_pt_emu1->GetBinContent(35));

  fclose(fpf2);

  char *fn_f3 = "fig/figaux_03c_ttbar.csv";
  TH1F *h_pt_emu3 = new TH1F("ttbar5","PT",35,0,350);
  FILE *fpf3 = fopen(fn_f3,"r");

  fscanf(fpf3,"%s\n",&blah);

  for (i=2; i<=35; i++){
    fscanf(fpf3, "%f,%f\n", &xx,&yy);
    h_pt_emu3->SetBinContent(i,yy);
  }

  h_pt_emu3->SetBinContent(1,0);

  fclose(fpf3);

  h_pt_emu1->Sumw2();
  h_pt_emu2->Sumw2();
  h_pt_emu3->Sumw2();

  TH1F *h_ATLAS_diboson_pt_emu = h_pt_emu1;

  TH1F *h_ATLAS_ttbar_pt_emu = new TH1F("ttbarpt_emu", "PT", 35,0,350);
  h_ATLAS_ttbar_pt_emu->Sumw2();

  h_ATLAS_ttbar_pt_emu->Add(h_pt_emu3,h_pt_emu2,1,-1);


  TH1F *h_mumu_by_ee_diboson = new TH1F("mumu_ee_diboson","",35,0,350);
  TH1F *h_mumu_by_ee_ttbar = new TH1F("mumu_ee_ttbar","",35,0,350);

  h_mumu_by_ee_diboson->Sumw2();
  h_mumu_by_ee_ttbar->Sumw2();

  /*
  TCanvas *c9 = new TCanvas();
  h_mumu_by_ee_diboson->Divide(h_ATLAS_diboson_pt_mu,h_ATLAS_diboson_pt,1,1);
  cout << "mumu_by_ee_diboson" << endl;
  h_mumu_by_ee_diboson->Fit(pol0,"","",0,350);
  cout << endl;

  TCanvas *c10 = new TCanvas();
  h_mumu_by_ee_ttbar->Divide(h_ATLAS_ttbar_pt_mu,h_ATLAS_ttbar_pt,1,1);
  cout << "mumu_by_ee_ttbar" << endl;
  h_mumu_by_ee_ttbar->Fit(pol0,"","",0,350);
  cout << endl;

  TH1F *h_emu_by_ee_diboson = new TH1F("emu_ee_diboson","",35,0,350);
  TH1F *h_emu_by_ee_ttbar = new TH1F("emu_ee_ttbar","",35,0,350);

  h_emu_by_ee_diboson->Sumw2();
  h_emu_by_ee_ttbar->Sumw2();

  TCanvas *c11 = new TCanvas();
  h_emu_by_ee_diboson->Divide(h_ATLAS_diboson_pt_emu,h_ATLAS_diboson_pt,1,1);
  cout << "emu_by_ee_diboson" << endl;
  h_emu_by_ee_diboson->Fit(pol0,"","",0,350);
  cout << endl;

  TCanvas *c12 = new TCanvas();
  h_emu_by_ee_ttbar->Divide(h_ATLAS_ttbar_pt_emu,h_ATLAS_ttbar_pt,1,1);
  cout << "emu_by_ee_ttbar" << endl;
  h_emu_by_ee_ttbar->Fit(pol0,"","",0,350);
  cout << endl;
  */  

  char *fn_red = "fig/fig_01d_redsignal_L.csv";
  FILE *fp_red = fopen(fn_red,"r");
  char *fn_red2 = "fig/fig_01d_redsignal_H.csv";
  FILE *fp_red2 = fopen(fn_red2,"r");

  TH1F *h_mt2_red = new TH1F("red","MT2",25,0,250);

  fscanf(fp_red,"%s\n",&blah);
  fscanf(fp_red2,"%s\n",&blah);

  for (i=1; i<=15; i++){
    fscanf(fp_red, "%f,%f\n", &xx,&yy);
    fscanf(fp_red2, "%f,%f\n", &xx2,&yy2);

    mean = (yy + yy2)/2.0;
    spread = (yy2 - yy)/2.0;

    //    cout << mean << "," << spread << endl;

    h_mt2_red->SetBinContent(i,mean);
    h_mt2_red->SetBinError(i,spread);
  }

  fclose(fp_red);
  fclose(fp_red2);
  
  //  h_mt2_red->Sumw2();

  char *fn_blue = "fig/fig_01d_bluesignal_L.csv";
  FILE *fp_blue = fopen(fn_blue,"r");
  char *fn_blue2 = "fig/fig_01d_bluesignal_H.csv";
  FILE *fp_blue2 = fopen(fn_blue2,"r");

  TH1F *h_mt2_blue = new TH1F("blue","MT2",25,0,250);

  fscanf(fp_blue,"%s\n",&blah);
  fscanf(fp_blue2,"%s\n",&blah);

  for (i=1; i<=15; i++){
    fscanf(fp_blue, "%f,%f\n", &xx,&yy);
    fscanf(fp_blue2, "%f,%f\n", &xx2,&yy2);

    mean = (yy + yy2)/2.0;
    spread = (yy2 - yy)/2.0;

    //    cout << mean << "," << spread << endl;

    h_mt2_blue->SetBinContent(i,mean);
    h_mt2_blue->SetBinError(i,spread);
  }

  fclose(fp_blue);
  fclose(fp_blue2);
  
  //  h_mt2_blue->Sumw2();

  TCanvas *c7 = new TCanvas();

  c7->Divide(1,2);
  c7->cd(1);

  slep1_hist_mt2->Draw();
  h_mt2_red->Draw("same");

  c1_n7_1->SetLogy();

  c7->cd(2);

  TH1F *h_compare_red_mt2 = new TH1F("h_mad_red_mt2 / h_ATLAS","",25,0,250);

  h_compare_red_mt2->Sumw2();
  h_compare_red_mt2->Divide(slep1_hist_mt2,h_mt2_red,1,1);

  h_compare_red_mt2->SetFillColor(2);
  h_compare_red_mt2->Draw();

  r = h_compare_red_mt2->Fit("pol0","SQ","",0,250);
  par0 = r->Parameter(0);
  err0 = r->ParError(0);

  cout << "red_mt2:\t" << par0 << " +/- " << err0 << endl;

  TString fn = "slep1_hist_mt2.eps";
  c7->SaveAs(fn);

  TCanvas *c8 = new TCanvas();

  c8->Divide(1,2);
  c8->cd(1);

  slep2_hist_mt2->Draw();
  h_mt2_blue->Draw("same");

  c1_n8_1->SetLogy();

  c8->cd(2);

  TH1F *h_compare_blue_mt2 = new TH1F("h_mad_blue_mt2 / h_ATLAS","",25,0,250);

  h_compare_blue_mt2->Sumw2();
  h_compare_blue_mt2->Divide(slep2_hist_mt2,h_mt2_blue,1,1);

  h_compare_blue_mt2->SetFillColor(2);
  h_compare_blue_mt2->Draw();

  r = h_compare_blue_mt2->Fit("pol0","SQ","",10,250); //omit first bin
  par0 = r->Parameter(0);
  err0 = r->ParError(0);

  cout << "blue_mt2:\t" << par0 << " +/- " << err0 << endl;

  TString fn = "slep2_hist_mt2.eps";
  c8->SaveAs(fn);


  //  c1->Close();
  //  c2->Close();
  //  c3->Close();
  //  c4->Close();
  //  c5->Close();
  //  c6->Close();

  // rescale by fitted K-factor
  for (i=1; i<=25; i++){
    scale_hist_mt2->SetBinContent(i, 0.700);
    scale_hist_mt2->SetBinError(i, 0.015);
  }
  diboson_hist_mt2->Divide(scale_hist_mt2);

  for (i=1; i<=25; i++){
    scale_hist_mt2->SetBinContent(i, 0.192);
    scale_hist_mt2->SetBinError(i, 0.018);
  }
  ttbar_hist_mt2->Divide(scale_hist_mt2);

  for (i=1; i<=25; i++){
    scale_hist_mt2->SetBinContent(i, 0.6333);
    scale_hist_mt2->SetBinError(i, 0.0051);
  }
  slep1_hist_mt2->Divide(scale_hist_mt2);
  slep2_hist_mt2->Divide(scale_hist_mt2);

  sum = diboson_hist_mt2->IntegralAndError(10,25,err);
  cout << "diboson: " << sum << " +/- " << err << endl;
  sum = ttbar_hist_mt2->IntegralAndError(10,25,err);
  cout << "ttbar: " << sum << " +/- " << err << endl;
  sum = slep1_hist_mt2->IntegralAndError(10,25,err);
  cout << "slep1: " << sum << " +/- " << err << endl;
  sum = slep2_hist_mt2->IntegralAndError(10,25,err);
  cout << "slep2: " << sum << " +/- " << err << endl;


  //  cout << "diboson: " << ncut_diboson*diboson_scale/0.780006*2.55287 << endl;
  //  cout << "ttbar:   " << ncut_ttbar*ttbar_scale/.2*2.35311 << endl;
  //  cout << "slep1:   " << ncut_slep1*slep1_scale/.63 << endl;
  //  cout << "slep2:   " << ncut_slep2*slep2_scale/.63 << endl;
  
}
