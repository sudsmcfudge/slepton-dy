{
  Int_t n_diboson,n_ttbar,ncut_diboson,ncut_ttbar;
  Double_t lum,diboson_xs,diboson_scale,ttbar_xs,ttbar_scale;

  Double_t a,b,c;
  double w, sig, wsum;

  Double_t ttbar_err, ww_err;
  
  TString fn1 = "ttbar_elec_full.root";
  TString fn2 = "ttbar_muon_full.root";
  TString fn3 = "diboson_elec_full.root";
  TString fn4 = "diboson_muon_full.root";
  TString fn7 = "snowmass_ww_elec.root";
  TString fn8 = "snowmass_ww_muon.root";
  TString fn9 = "snowmass_tt_elec.root";
  TString fn10 = "snowmass_tt_muon.root";


  TFile fp1(fn1);
  TFile fp2(fn2);
  TFile fp3(fn3);
  TFile fp4(fn4);
  TFile fp7(fn7);
  TFile fp8(fn8);
  TFile fp9(fn9);
  TFile fp10(fn10);

  
  TTree *ttbar_elec_Tree = (TTree *) fp1.Get("MyTree");
  TTree *ttbar_muon_Tree   = (TTree *) fp2.Get("MyTree");
  TTree *diboson_elec_Tree   = (TTree *) fp3.Get("MyTree");
  TTree *diboson_muon_Tree   = (TTree *) fp4.Get("MyTree");
  
  TTree *snow_ww_elec_Tree = (TTree *) fp7.Get("MyTree");
  TTree *snow_ww_muon_Tree   = (TTree *) fp8.Get("MyTree");
  TTree *snow_tt_elec_Tree = (TTree *) fp9.Get("MyTree");
  TTree *snow_tt_muon_Tree   = (TTree *) fp10.Get("MyTree");


  //  TCut c_pt = "PT1 > 50.0 && PT2 > 50.0";

  //  TCut c_pt = "PT1 > 30.0 && PT2 > 30.0";
  //  TCut c_op = "opAngle < 14.0/18.0*pi";
  //  TCut c_mll = "Mll > 91.2 + 10.0 || Mll < 91.2 - 10.0";
  //  TCut c_jet = "max_jetpt < 30.0";

  TCut c_pt = "PT1 > 10.0 && PT2 > 10.0";
  TCut c_mll = "Mll > 20";
  TCut c_jet = "max_jetpt < 100";

  //  TCut c_metrel = "met_rel > 40";
  //  TCut c_met_rel = "mt2 > 90";

  //  TCut c_met = "MET > 140.0";
  //  TCut c_phi = "dmetPhi > 15.0/18.0*pi";
  //  TCut c_deltaR = "deltaR > 0.4";

  TCut cuts_total = c_mll + c_pt + c_jet;

  TCanvas *c1 = new TCanvas();
  
  ttbar_elec_Tree->Draw("mt2>>h_ttee(25,0,250)",cuts_total,"wts");
  ttbar_muon_Tree->Draw("mt2>>h_ttmm(25,0,250)",cuts_total,"wts");
  diboson_elec_Tree->Draw("mt2>>h_wwee(25,0,250)",cuts_total,"wts");
  diboson_muon_Tree->Draw("mt2>>h_wwmm(25,0,250)",cuts_total,"wts");

  snow_tt_elec_Tree->Draw("mt2>>h_snowttee(25,0,250)",cuts_total,"wts");
  snow_tt_muon_Tree->Draw("mt2>>h_snowttmm(25,0,250)",cuts_total,"wts");
  snow_ww_elec_Tree->Draw("mt2>>h_snowwwee(25,0,250)",cuts_total,"wts");
  snow_ww_muon_Tree->Draw("mt2>>h_snowwwmm(25,0,250)",cuts_total,"wts");

  htemp = (TH1F*)gDirectory->Get("h_ttee");
  TH1F *ttbar_ee = (TH1F*)htemp->Clone("mad_tt_ee / snow_tt_ee");

  htemp = (TH1F*)gDirectory->Get("h_ttmm");
  TH1F *ttbar_mm = (TH1F*)htemp->Clone("mad_tt_mm / snow_tt_mm");

  htemp = (TH1F*)gDirectory->Get("h_wwee");
  TH1F *diboson_ee = (TH1F*)htemp->Clone("mad_ww_ee / snow_ww_ee");

  htemp = (TH1F*)gDirectory->Get("h_wwmm");
  TH1F *diboson_mm = (TH1F*)htemp->Clone("mad_ww_mm / snow_ww_mm");

  htemp = (TH1F*)gDirectory->Get("h_snowttee");
  TH1F *snow_ttbar_ee = (TH1F*)htemp->Clone("mad_tt_ee / snow_tt_ee");

  htemp = (TH1F*)gDirectory->Get("h_snowttmm");
  TH1F *snow_ttbar_mm = (TH1F*)htemp->Clone("mad_tt_mm / snow_tt_mm");

  htemp = (TH1F*)gDirectory->Get("h_snowwwee");
  TH1F *snow_diboson_ee = (TH1F*)htemp->Clone("mad_ww_ee / snow_ww_ee");

  htemp = (TH1F*)gDirectory->Get("h_snowwwmm");
  TH1F *snow_diboson_mm = (TH1F*)htemp->Clone("mad_ww_mm / snow_ww_mm");

  ttbar_ee->Sumw2();
  ttbar_mm->Sumw2();
  diboson_ee->Sumw2();
  diboson_mm->Sumw2();
  snow_ttbar_ee->Sumw2();
  snow_ttbar_mm->Sumw2();
  snow_diboson_ee->Sumw2();
  snow_diboson_mm->Sumw2();

  scale_tt = 1/ttbar_ee->Integral();
  ttbar_ee->Scale(scale_tt);
  scale_tt = 1/ttbar_mm->Integral();
  ttbar_mm->Scale(scale_tt);
  scale_ww = 1/diboson_ee->Integral();
  diboson_ee->Scale(scale_ww);
  scale_ww = 1/diboson_mm->Integral();
  diboson_mm->Scale(scale_ww);

  scale_tt = 1/snow_ttbar_ee->Integral();
  snow_ttbar_ee->Scale(scale_tt);
  scale_tt = 1/snow_ttbar_mm->Integral();
  snow_ttbar_mm->Scale(scale_tt);
  scale_ww = 1/snow_diboson_ee->Integral();
  snow_diboson_ee->Scale(scale_ww);
  scale_ww = 1/snow_diboson_mm->Integral();
  snow_diboson_mm->Scale(scale_ww);

  ttbar_ee->Divide(snow_ttbar_ee);
  ttbar_ee->Draw();

  TCanvas *c2 = new TCanvas();
  ttbar_mm->Divide(snow_ttbar_mm);
  ttbar_mm->Draw();
  
  TCanvas *c3 = new TCanvas();
  diboson_ee->Divide(snow_diboson_ee);
  diboson_ee->Draw();

  TCanvas *c4 = new TCanvas();
  diboson_mm->Divide(snow_diboson_mm);
  diboson_mm->Draw();


  //  c1->SaveAs("met_rel_comparison_aftercuts.eps");  

  //  TCanvas *c2 = new TCanvas();

  //  lum = 100.0; // fb^-1
  lum = 0.1; // fb^-1

  //  slep_xs1 = 21.9;
  //  n_slep1 = 31334;
  //  slep_scale1 = lum * slep_xs1 / n_slep1;

  //  slep_xs2 = 5.4;
  //  n_slep2 = 30153;
  //  slep_scale2 = lum * slep_xs2 / n_slep2;
  
  ttbar_elec_xs = 2858.9; // fb
  ttbar_muon_xs = 2863.4; // fb
  n_ttbar_elec = 2249097;
  n_ttbar_muon = 2249604;

  ttbar_elec_scale = lum * ttbar_elec_xs / n_ttbar_elec;
  ttbar_muon_scale = lum * ttbar_muon_xs / n_ttbar_muon;

  diboson_elec_xs = 636.0; // fb
  diboson_muon_xs = 639.2; // fb
  n_diboson_elec = 398685;
  n_diboson_muon = 398169;

  diboson_elec_scale = lum * diboson_elec_xs / n_diboson_elec;
  diboson_muon_scale = lum * diboson_muon_xs / n_diboson_muon;

  // 400 50
  //  bench_elec_xs = 0.8538; // fb
  //  bench_muon_xs = 0.8491; // fb
  //  n_bench_ee = 4908; //400 50
  //  n_bench_mm = 4886; //400 50

  // 300 50
  //  bench_elec_xs = 2.768; // fb
  //  bench_muon_xs = 2.78; // fb
  //  n_bench_ee = 5202;
  //  n_bench_mm = 5196;

  //  n_ww = 397712;
  //  ww_xs = 216.98;
  //  n_ww = 398336;
  //  ww_scale = lum * ww_xs / n_ww;

  //  h_ttee->Scale(ttbar_elec_scale);
  //  h_ttmm->Scale(ttbar_muon_scale);
  //  h_wwee->Scale(diboson_elec_scale);
  //  h_wwmm->Scale(diboson_muon_scale);

  h_ttee->SetFillColor(kRed);
  h_ttmm->SetFillColor(kRed);

  h_wwee->SetFillColor(kYellow);
  h_wwmm->SetFillColor(kYellow);

  //  TH1F *ratio = new TH1F("new","",50,0,250);
  //  ratio->Divide(h_ttee,h_wwee);

  THStack hs_back("background","");

  hs_back.Add(h_wwee);
  hs_back.Add(h_wwmm);
  hs_back.Add(h_ttee);
  hs_back.Add(h_ttmm);

  //  hs_back.Draw();

  //  c2->SetLogy();
  //  c2->SaveAs("met_rel.eps");
 
}
