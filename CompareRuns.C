// compares statistics and asymmetries for runs 12 and 13

void CompareRuns(const char * kin_var="p_{#perp}", const char * filename="printout_tree.root")
{
  gStyle->SetOptFit(1);
  // open trees
  TFile * infile = new TFile(filename,"READ");
  TTree * sph = (TTree*) infile->Get("tr_sph");
  TTree * pi0 = (TTree*) infile->Get("tr_pi0");
  TTree * thr = (TTree*) infile->Get("tr_thr");

  Double_t kin_max = sph->GetMaximum("mm_kin");
  kin_max += 2;
  Int_t nbins = 30; // number of kinematic bins

  Int_t sf=1; // scale factor for drawing images


  // asymmetries for both runs and merged set
  // -- pngs drawn from DrawThree.png already show these; this script just accumulates
  //    all of the data into one TCanvas for simultaneous viewing
  // --> jtype
  //     - 0 = single photon
  //     - 1 = pions
  //     - 2 = three or more photons
  // --> run year
  //     - 0 = run12
  //     - 1 = run13
  //     - 2 = merged data set
  TGraphErrors * asym_gr[3][3][4]; // [run year] [jtype] [asym]
  TH1D * asym_hist[3][3][4];
  TH1D * asym_histerr[3][3][4];
  char asym_hist_n[3][3][4][64];
  char asym_histerr_n[3][3][4][64];
  for(Int_t r=0; r<3; r++)
  {
    for(Int_t j=0; j<3; j++)
    {
      for(Int_t a=1; a<4; a++)
      {
        sprintf(asym_hist_n[r][j][a],"asym_hist_r%d_j%d_a%d",r,j,a);
        sprintf(asym_histerr_n[r][j][a],"asym_histerr_r%d_j%d_a%d",r,j,a);
        asym_gr[r][j][a] = new TGraphErrors();
        asym_hist[r][j][a] = new TH1D(asym_hist_n[r][j][a],asym_hist_n[r][j][a],nbins,0,kin_max);
        asym_histerr[r][j][a] = new TH1D(asym_histerr_n[r][j][a],asym_histerr_n[r][j][a],nbins,0,kin_max);
      };
    };
  };

  sph->Project(asym_hist_n[0][0][1],"12_kin","12_A_Ly");
  sph->Project(asym_hist_n[0][0][2],"12_kin","12_A_Lb");
  sph->Project(asym_hist_n[0][0][3],"12_kin","12_A_LL");
  sph->Project(asym_hist_n[1][0][1],"13_kin","13_A_Ly");
  sph->Project(asym_hist_n[1][0][2],"13_kin","13_A_Lb");
  sph->Project(asym_hist_n[1][0][3],"13_kin","13_A_LL");
  sph->Project(asym_hist_n[2][0][1],"mm_kin","mm_A_Ly");
  sph->Project(asym_hist_n[2][0][2],"mm_kin","mm_A_Lb");
  sph->Project(asym_hist_n[2][0][3],"mm_kin","mm_A_LL");
  sph->Project(asym_histerr_n[0][0][1],"12_kin","12_A_Ly_err");
  sph->Project(asym_histerr_n[0][0][2],"12_kin","12_A_Lb_err");
  sph->Project(asym_histerr_n[0][0][3],"12_kin","12_A_LL_err");
  sph->Project(asym_histerr_n[1][0][1],"13_kin","13_A_Ly_err");
  sph->Project(asym_histerr_n[1][0][2],"13_kin","13_A_Lb_err");
  sph->Project(asym_histerr_n[1][0][3],"13_kin","13_A_LL_err");
  sph->Project(asym_histerr_n[2][0][1],"mm_kin","mm_A_Ly_err");
  sph->Project(asym_histerr_n[2][0][2],"mm_kin","mm_A_Lb_err");
  sph->Project(asym_histerr_n[2][0][3],"mm_kin","mm_A_LL_err");

  pi0->Project(asym_hist_n[0][1][1],"12_kin","12_A_Ly");
  pi0->Project(asym_hist_n[0][1][2],"12_kin","12_A_Lb");
  pi0->Project(asym_hist_n[0][1][3],"12_kin","12_A_LL");
  pi0->Project(asym_hist_n[1][1][1],"13_kin","13_A_Ly");
  pi0->Project(asym_hist_n[1][1][2],"13_kin","13_A_Lb");
  pi0->Project(asym_hist_n[1][1][3],"13_kin","13_A_LL");
  pi0->Project(asym_hist_n[2][1][1],"mm_kin","mm_A_Ly");
  pi0->Project(asym_hist_n[2][1][2],"mm_kin","mm_A_Lb");
  pi0->Project(asym_hist_n[2][1][3],"mm_kin","mm_A_LL");
  pi0->Project(asym_histerr_n[0][1][1],"12_kin","12_A_Ly_err");
  pi0->Project(asym_histerr_n[0][1][2],"12_kin","12_A_Lb_err");
  pi0->Project(asym_histerr_n[0][1][3],"12_kin","12_A_LL_err");
  pi0->Project(asym_histerr_n[1][1][1],"13_kin","13_A_Ly_err");
  pi0->Project(asym_histerr_n[1][1][2],"13_kin","13_A_Lb_err");
  pi0->Project(asym_histerr_n[1][1][3],"13_kin","13_A_LL_err");
  pi0->Project(asym_histerr_n[2][1][1],"mm_kin","mm_A_Ly_err");
  pi0->Project(asym_histerr_n[2][1][2],"mm_kin","mm_A_Lb_err");
  pi0->Project(asym_histerr_n[2][1][3],"mm_kin","mm_A_LL_err");

  thr->Project(asym_hist_n[0][2][1],"12_kin","12_A_Ly");
  thr->Project(asym_hist_n[0][2][2],"12_kin","12_A_Lb");
  thr->Project(asym_hist_n[0][2][3],"12_kin","12_A_LL");
  thr->Project(asym_hist_n[1][2][1],"13_kin","13_A_Ly");
  thr->Project(asym_hist_n[1][2][2],"13_kin","13_A_Lb");
  thr->Project(asym_hist_n[1][2][3],"13_kin","13_A_LL");
  thr->Project(asym_hist_n[2][2][1],"mm_kin","mm_A_Ly");
  thr->Project(asym_hist_n[2][2][2],"mm_kin","mm_A_Lb");
  thr->Project(asym_hist_n[2][2][3],"mm_kin","mm_A_LL");
  thr->Project(asym_histerr_n[0][2][1],"12_kin","12_A_Ly_err");
  thr->Project(asym_histerr_n[0][2][2],"12_kin","12_A_Lb_err");
  thr->Project(asym_histerr_n[0][2][3],"12_kin","12_A_LL_err");
  thr->Project(asym_histerr_n[1][2][1],"13_kin","13_A_Ly_err");
  thr->Project(asym_histerr_n[1][2][2],"13_kin","13_A_Lb_err");
  thr->Project(asym_histerr_n[1][2][3],"13_kin","13_A_LL_err");
  thr->Project(asym_histerr_n[2][2][1],"mm_kin","mm_A_Ly_err");
  thr->Project(asym_histerr_n[2][2][2],"mm_kin","mm_A_Lb_err");
  thr->Project(asym_histerr_n[2][2][3],"mm_kin","mm_A_LL_err");

  Double_t content,center,contenterr;
  Double_t count;
  for(Int_t r=0; r<3; r++)
  {
    for(Int_t j=0; j<3; j++)
    {
      for(Int_t a=1; a<4; a++)
      {
        count = 0;
        for(Int_t b=1; b<=nbins; b++)
        {
          content = asym_hist[r][j][a]->GetBinContent(b);
          contenterr = asym_histerr[r][j][a]->GetBinContent(b);
          center = asym_hist[r][j][a]->GetBinCenter(b);
          if(content!=0)
          {
            asym_gr[r][j][a]->SetPoint(count,center,content);
            asym_gr[r][j][a]->SetPointError(count,0,contenterr);
            count++;
          };
        };
      };
    };
  };
  
  char asym_gr_t[3][3][4][128];
  sprintf(asym_gr_t[0][0][1],"Run12 :: single #gamma :: A_{L}^{Y} vs. %s",kin_var);
  sprintf(asym_gr_t[0][0][2],"Run12 :: single #gamma :: A_{L}^{B} vs. %s",kin_var);
  sprintf(asym_gr_t[0][0][3],"Run12 :: single #gamma :: A_{LL} vs. %s",kin_var);
  sprintf(asym_gr_t[0][1][1],"Run12 :: #pi^{0} :: A_{L}^{Y} vs. %s",kin_var);
  sprintf(asym_gr_t[0][1][2],"Run12 :: #pi^{0} :: A_{L}^{B} vs. %s",kin_var);
  sprintf(asym_gr_t[0][1][3],"Run12 :: #pi^{0} :: A_{LL} vs. %s",kin_var);
  sprintf(asym_gr_t[0][2][1],"Run12 :: N_{#gamma}>2 :: A_{L}^{Y} vs. %s",kin_var);
  sprintf(asym_gr_t[0][2][2],"Run12 :: N_{#gamma}>2 :: A_{L}^{B} vs. %s",kin_var);
  sprintf(asym_gr_t[0][2][3],"Run12 :: N_{#gamma}>2 :: A_{LL} vs. %s",kin_var);

  sprintf(asym_gr_t[1][0][1],"Run13 :: single #gamma :: A_{L}^{Y} vs. %s",kin_var);
  sprintf(asym_gr_t[1][0][2],"Run13 :: single #gamma :: A_{L}^{B} vs. %s",kin_var);
  sprintf(asym_gr_t[1][0][3],"Run13 :: single #gamma :: A_{LL} vs. %s",kin_var);
  sprintf(asym_gr_t[1][1][1],"Run13 :: #pi^{0} :: A_{L}^{Y} vs. %s",kin_var);
  sprintf(asym_gr_t[1][1][2],"Run13 :: #pi^{0} :: A_{L}^{B} vs. %s",kin_var);
  sprintf(asym_gr_t[1][1][3],"Run13 :: #pi^{0} :: A_{LL} vs. %s",kin_var);
  sprintf(asym_gr_t[1][2][1],"Run13 :: N_{#gamma}>2 :: A_{L}^{Y} vs. %s",kin_var);
  sprintf(asym_gr_t[1][2][2],"Run13 :: N_{#gamma}>2 :: A_{L}^{B} vs. %s",kin_var);
  sprintf(asym_gr_t[1][2][3],"Run13 :: N_{#gamma}>2 :: A_{LL} vs. %s",kin_var);

  sprintf(asym_gr_t[2][0][1],"merged :: single #gamma :: A_{L}^{Y} vs. %s",kin_var);
  sprintf(asym_gr_t[2][0][2],"merged :: single #gamma :: A_{L}^{B} vs. %s",kin_var);
  sprintf(asym_gr_t[2][0][3],"merged :: single #gamma :: A_{LL} vs. %s",kin_var);
  sprintf(asym_gr_t[2][1][1],"merged :: #pi^{0} :: A_{L}^{Y} vs. %s",kin_var);
  sprintf(asym_gr_t[2][1][2],"merged :: #pi^{0} :: A_{L}^{B} vs. %s",kin_var);
  sprintf(asym_gr_t[2][1][3],"merged :: #pi^{0} :: A_{LL} vs. %s",kin_var);
  sprintf(asym_gr_t[2][2][1],"merged :: N_{#gamma}>2 :: A_{L}^{Y} vs. %s",kin_var);
  sprintf(asym_gr_t[2][2][2],"merged :: N_{#gamma}>2 :: A_{L}^{B} vs. %s",kin_var);
  sprintf(asym_gr_t[2][2][3],"merged :: N_{#gamma}>2 :: A_{LL} vs. %s",kin_var);

  for(Int_t r=0; r<3; r++)
  {
    for(Int_t j=0; j<3; j++)
    {
      for(Int_t a=1; a<4; a++)
      {
        asym_gr[r][j][a]->SetTitle(asym_gr_t[r][j][a]);
        asym_gr[r][j][a]->SetMarkerStyle(33);
        asym_gr[r][j][a]->SetMarkerSize(2);
      };
      asym_gr[r][j][1]->SetMarkerColor(kOrange-3);
      asym_gr[r][j][2]->SetMarkerColor(kBlue);
      asym_gr[r][j][3]->SetMarkerColor(kMagenta);
      asym_gr[r][j][1]->SetLineColor(kOrange-3);
      asym_gr[r][j][2]->SetLineColor(kBlue);
      asym_gr[r][j][3]->SetLineColor(kMagenta);
    };
  };

  for(Int_t r=0; r<3; r++)
  {
    for(Int_t j=0; j<3; j++)
    {
      for(Int_t a=1; a<4; a++)
      {
        // yes, these fits were done in DrawThree.C
        // I'm doing them again here since I'm too lazy to pull them
        // from the printout.dat files
        asym_gr[r][j][a]->Fit("pol0","","",0,kin_max);
      };
    };
  };
  
  TCanvas * canv_A_Ly = new TCanvas("canv_A_Ly","canv_A_Ly",sf*1000,sf*1000);
  canv_A_Ly->Divide(3,3);
  for(Int_t i=1; i<=9; i++) canv_A_Ly->GetPad(i)->SetGrid(1,1);
  canv_A_Ly->cd(1); asym_gr[0][0][1]->Draw("APE1");
  canv_A_Ly->cd(2); asym_gr[1][0][1]->Draw("APE1");
  canv_A_Ly->cd(3); asym_gr[2][0][1]->Draw("APE1");
  canv_A_Ly->cd(4); asym_gr[0][1][1]->Draw("APE1");
  canv_A_Ly->cd(5); asym_gr[1][1][1]->Draw("APE1");
  canv_A_Ly->cd(6); asym_gr[2][1][1]->Draw("APE1");
  canv_A_Ly->cd(7); asym_gr[0][2][1]->Draw("APE1");
  canv_A_Ly->cd(8); asym_gr[1][2][1]->Draw("APE1");
  canv_A_Ly->cd(9); asym_gr[2][2][1]->Draw("APE1");


  TCanvas * canv_A_Lb = new TCanvas("canv_A_Lb","canv_A_Lb",sf*1000,sf*1000);
  canv_A_Lb->Divide(3,3);
  for(Int_t i=1; i<=9; i++) canv_A_Lb->GetPad(i)->SetGrid(1,1);
  canv_A_Lb->cd(1); asym_gr[0][0][2]->Draw("APE1");
  canv_A_Lb->cd(2); asym_gr[1][0][2]->Draw("APE1");
  canv_A_Lb->cd(3); asym_gr[2][0][2]->Draw("APE1");
  canv_A_Lb->cd(4); asym_gr[0][1][2]->Draw("APE1");
  canv_A_Lb->cd(5); asym_gr[1][1][2]->Draw("APE1");
  canv_A_Lb->cd(6); asym_gr[2][1][2]->Draw("APE1");
  canv_A_Lb->cd(7); asym_gr[0][2][2]->Draw("APE1");
  canv_A_Lb->cd(8); asym_gr[1][2][2]->Draw("APE1");
  canv_A_Lb->cd(9); asym_gr[2][2][2]->Draw("APE1");


  TCanvas * canv_A_LL = new TCanvas("canv_A_LL","canv_A_LL",sf*1000,sf*1000);
  canv_A_LL->Divide(3,3);
  for(Int_t i=1; i<=9; i++) canv_A_LL->GetPad(i)->SetGrid(1,1);
  canv_A_LL->cd(1); asym_gr[0][0][3]->Draw("APE1");
  canv_A_LL->cd(2); asym_gr[1][0][3]->Draw("APE1");
  canv_A_LL->cd(3); asym_gr[2][0][3]->Draw("APE1");
  canv_A_LL->cd(4); asym_gr[0][1][3]->Draw("APE1");
  canv_A_LL->cd(5); asym_gr[1][1][3]->Draw("APE1");
  canv_A_LL->cd(6); asym_gr[2][1][3]->Draw("APE1");
  canv_A_LL->cd(7); asym_gr[0][2][3]->Draw("APE1");
  canv_A_LL->cd(8); asym_gr[1][2][3]->Draw("APE1");
  canv_A_LL->cd(9); asym_gr[2][2][3]->Draw("APE1");




  // asym_diff = difference in run12 and run 13 asymmetry vs. kin_var
  // asym_errdiv = ratio of error bars from run12 to run13 vs. kin_var
  // asym_quaderr = asymmetry error bars added in quadrature
  // -- project kin_var weighted by asymmetry difference or error bar ratio to *_hist
  // -- make TGraphErrors *_gr from hist with errors obtained from histerr
  // --> jtype
  //     - 0 = single photon
  //     - 1 = pions
  //     - 2 = three or more photons
  TGraphErrors * asym_diff_gr[3][4]; // [jtype] [asym]
  TGraphErrors * asym_errdiv_gr[3][4]; // [jtype] [asym]
  TH1D * asym_diff_hist[3][4]; 
  TH1D * asym_errdiv_hist[3][4]; 
  TH1D * asym_quaderr[3][4];
  char asym_diff_hist_n[3][4][64];
  char asym_errdiv_hist_n[3][4][64];
  char asym_quaderr_n[3][4][64];
  for(Int_t j=0; j<3; j++)
  {
    for(Int_t a=1; a<4; a++)
    {
      sprintf(asym_diff_hist_n[j][a],"asym_diff_hist_j%d_a%d",j,a);
      sprintf(asym_errdiv_hist_n[j][a],"asym_errdiv_hist_j%d_a%d",j,a);
      sprintf(asym_quaderr_n[j][a],"asym_quaderr_j%d_a%d",j,a);
      asym_diff_gr[j][a] = new TGraphErrors();
      asym_errdiv_gr[j][a] = new TGraphErrors();
      asym_diff_hist[j][a] = new TH1D(asym_diff_hist_n[j][a],asym_diff_hist_n[j][a],nbins,0,kin_max);
      asym_errdiv_hist[j][a] = new TH1D(asym_errdiv_hist_n[j][a],asym_errdiv_hist_n[j][a],nbins,0,kin_max);
      asym_quaderr[j][a] = new TH1D(asym_quaderr_n[j][a],asym_quaderr_n[j][a],nbins,0,kin_max);
    };
  };

  sph->Project(asym_diff_hist_n[0][1],"mm_kin","12_A_Ly-13_A_Ly");
  sph->Project(asym_diff_hist_n[0][2],"mm_kin","12_A_Lb-13_A_Lb");
  sph->Project(asym_diff_hist_n[0][3],"mm_kin","12_A_LL-13_A_LL");
  sph->Project(asym_errdiv_hist_n[0][1],"mm_kin","12_A_Ly_err/13_A_Ly_err");
  sph->Project(asym_errdiv_hist_n[0][2],"mm_kin","12_A_Lb_err/13_A_Lb_err");
  sph->Project(asym_errdiv_hist_n[0][3],"mm_kin","12_A_LL_err/13_A_LL_err");
  sph->Project(asym_quaderr_n[0][1],"mm_kin","sqrt(pow(12_A_Ly_err,2)+pow(13_A_Ly_err,2))");
  sph->Project(asym_quaderr_n[0][2],"mm_kin","sqrt(pow(12_A_Lb_err,2)+pow(13_A_Lb_err,2))");
  sph->Project(asym_quaderr_n[0][3],"mm_kin","sqrt(pow(12_A_LL_err,2)+pow(13_A_LL_err,2))");

  pi0->Project(asym_diff_hist_n[1][1],"mm_kin","12_A_Ly-13_A_Ly");
  pi0->Project(asym_diff_hist_n[1][2],"mm_kin","12_A_Lb-13_A_Lb");
  pi0->Project(asym_diff_hist_n[1][3],"mm_kin","12_A_LL-13_A_LL");
  pi0->Project(asym_errdiv_hist_n[1][1],"mm_kin","12_A_Ly_err/13_A_Ly_err");
  pi0->Project(asym_errdiv_hist_n[1][2],"mm_kin","12_A_Lb_err/13_A_Lb_err");
  pi0->Project(asym_errdiv_hist_n[1][3],"mm_kin","12_A_LL_err/13_A_LL_err");
  pi0->Project(asym_quaderr_n[1][1],"mm_kin","sqrt(pow(12_A_Ly_err,2)+pow(13_A_Ly_err,2))");
  pi0->Project(asym_quaderr_n[1][2],"mm_kin","sqrt(pow(12_A_Lb_err,2)+pow(13_A_Lb_err,2))");
  pi0->Project(asym_quaderr_n[1][3],"mm_kin","sqrt(pow(12_A_LL_err,2)+pow(13_A_LL_err,2))");
  
  thr->Project(asym_diff_hist_n[2][1],"mm_kin","12_A_Ly-13_A_Ly");
  thr->Project(asym_diff_hist_n[2][2],"mm_kin","12_A_Lb-13_A_Lb");
  thr->Project(asym_diff_hist_n[2][3],"mm_kin","12_A_LL-13_A_LL");
  thr->Project(asym_errdiv_hist_n[2][1],"mm_kin","12_A_Ly_err/13_A_Ly_err");
  thr->Project(asym_errdiv_hist_n[2][2],"mm_kin","12_A_Lb_err/13_A_Lb_err");
  thr->Project(asym_errdiv_hist_n[2][3],"mm_kin","12_A_LL_err/13_A_LL_err");
  thr->Project(asym_quaderr_n[2][1],"mm_kin","sqrt(pow(12_A_Ly_err,2)+pow(13_A_Ly_err,2))");
  thr->Project(asym_quaderr_n[2][2],"mm_kin","sqrt(pow(12_A_Lb_err,2)+pow(13_A_Lb_err,2))");
  thr->Project(asym_quaderr_n[2][3],"mm_kin","sqrt(pow(12_A_LL_err,2)+pow(13_A_LL_err,2))");

  for(Int_t j=0; j<3; j++)
  {
    for(Int_t a=1; a<4; a++)
    {
      count=0;
      for(Int_t b=1; b<=nbins; b++)
      {
        content = asym_diff_hist[j][a]->GetBinContent(b);
        contenterr = asym_quaderr[j][a]->GetBinContent(b);
        center = asym_diff_hist[j][a]->GetBinCenter(b);
        if(content!=0)
        {
          asym_diff_gr[j][a]->SetPoint(count,center,content);
          asym_diff_gr[j][a]->SetPointError(count,0,contenterr);
          count++;
        };
      };
    };
  };

  for(Int_t j=0; j<3; j++)
  {
    for(Int_t a=1; a<4; a++)
    {
      count=0;
      for(Int_t b=1; b<=nbins; b++)
      {
        content = asym_errdiv_hist[j][a]->GetBinContent(b);
        contenterr = asym_quaderr[j][a]->GetBinContent(b);
        center = asym_errdiv_hist[j][a]->GetBinCenter(b);
        if(content!=0)
        {
          asym_errdiv_gr[j][a]->SetPoint(count,center,content);
          //asym_errdiv_gr[j][a]->SetPointError(count,0,contenterr);
          count++;
        };
      };
    };
  };


  char asym_diff_gr_t[3][4][128];
  sprintf(asym_diff_gr_t[0][1],"single #gamma :: A_{L}^{Y}(12) - A_{L}^{Y}(13) vs. %s",kin_var);
  sprintf(asym_diff_gr_t[0][2],"single #gamma :: A_{L}^{B}(12) - A_{L}^{B}(13) vs. %s",kin_var);
  sprintf(asym_diff_gr_t[0][3],"single #gamma :: A_{LL}(12) - A_{LL}(13) vs. %s",kin_var);

  sprintf(asym_diff_gr_t[1][1],"#pi^{0} :: A_{L}^{Y}(12) - A_{L}^{Y}(13) vs. %s",kin_var);
  sprintf(asym_diff_gr_t[1][2],"#pi^{0} :: A_{L}^{B}(12) - A_{L}^{B}(13) vs. %s",kin_var);
  sprintf(asym_diff_gr_t[1][3],"#pi^{0} :: A_{LL}(12) - A_{LL}(13) vs. %s",kin_var);

  sprintf(asym_diff_gr_t[2][1],"N_{#gamma}>2 :: A_{L}^{Y}(12) - A_{L}^{Y}(13) vs. %s",kin_var);
  sprintf(asym_diff_gr_t[2][2],"N_{#gamma}>2 :: A_{L}^{B}(12) - A_{L}^{B}(13) vs. %s",kin_var);
  sprintf(asym_diff_gr_t[2][3],"N_{#gamma}>2 :: A_{LL}(12) - A_{LL}(13) vs. %s",kin_var);


  char asym_errdiv_gr_t[3][4][128];
  sprintf(asym_errdiv_gr_t[0][1],"single #gamma :: #sigma A_{L}^{Y}(12) / #sigma A_{L}^{Y}(13) vs. %s",kin_var);
  sprintf(asym_errdiv_gr_t[0][2],"single #gamma :: #sigma A_{L}^{B}(12) / #sigma A_{L}^{B}(13) vs. %s",kin_var);
  sprintf(asym_errdiv_gr_t[0][3],"single #gamma :: #sigma A_{LL}(12) / #sigma A_{LL}(13) vs. %s",kin_var);

  sprintf(asym_errdiv_gr_t[1][1],"#pi^{0} :: #sigma A_{L}^{Y}(12) / #sigma A_{L}^{Y}(13) vs. %s",kin_var);
  sprintf(asym_errdiv_gr_t[1][2],"#pi^{0} :: #sigma A_{L}^{B}(12) / #sigma A_{L}^{B}(13) vs. %s",kin_var);
  sprintf(asym_errdiv_gr_t[1][3],"#pi^{0} :: #sigma A_{LL}(12) / #sigma A_{LL}(13) vs. %s",kin_var);

  sprintf(asym_errdiv_gr_t[2][1],"N_{#gamma}>2 :: #sigma A_{L}^{Y}(12) / #sigma A_{L}^{Y}(13) vs. %s",kin_var);
  sprintf(asym_errdiv_gr_t[2][2],"N_{#gamma}>2 :: #sigma A_{L}^{B}(12) / #sigma A_{L}^{B}(13) vs. %s",kin_var);
  sprintf(asym_errdiv_gr_t[2][3],"N_{#gamma}>2 :: #sigma A_{LL}(12) / #sigma A_{LL}(13) vs. %s",kin_var);


  for(Int_t j=0; j<3; j++)
  {
    asym_diff_gr[j][1]->SetMarkerColor(kOrange-3);
    asym_diff_gr[j][2]->SetMarkerColor(kBlue);
    asym_diff_gr[j][3]->SetMarkerColor(kMagenta);
    asym_diff_gr[j][1]->SetLineColor(kOrange-3);
    asym_diff_gr[j][2]->SetLineColor(kBlue);
    asym_diff_gr[j][3]->SetLineColor(kMagenta);
    for(Int_t a=1; a<4; a++)
    {
      asym_diff_gr[j][a]->SetMarkerStyle(33);
      asym_diff_gr[j][a]->SetMarkerSize(2);
      asym_diff_gr[j][a]->SetTitle(asym_diff_gr_t[j][a]);
      asym_diff_gr[j][a]->Fit("pol0","","",0,kin_max);
    };
  };
  gStyle->SetOptFit(1);

  for(Int_t j=0; j<3; j++)
  {
    asym_errdiv_gr[j][1]->SetMarkerColor(kOrange-3);
    asym_errdiv_gr[j][2]->SetMarkerColor(kBlue);
    asym_errdiv_gr[j][3]->SetMarkerColor(kMagenta);
    asym_errdiv_gr[j][1]->SetLineColor(kOrange-3);
    asym_errdiv_gr[j][2]->SetLineColor(kBlue);
    asym_errdiv_gr[j][3]->SetLineColor(kMagenta);
    for(Int_t a=1; a<4; a++)
    {
      asym_errdiv_gr[j][a]->SetMarkerStyle(kFullStar);
      asym_errdiv_gr[j][a]->SetMarkerSize(2);
      asym_errdiv_gr[j][a]->SetTitle(asym_errdiv_gr_t[j][a]);
      //asym_errdiv_gr[j][a]->Fit("pol0","","",0,kin_max);
    };
  };


  TCanvas * canv_asym_diff = new TCanvas("canv_asym_diff","canv_asym_diff",sf*1200,sf*800);
  canv_asym_diff->Divide(3,3);
  for(Int_t i=1; i<=9; i++) canv_asym_diff->GetPad(i)->SetGrid(1,1);
  canv_asym_diff->cd(1); asym_diff_gr[0][1]->Draw("APE1");
  canv_asym_diff->cd(2); asym_diff_gr[0][2]->Draw("APE1");
  canv_asym_diff->cd(3); asym_diff_gr[0][3]->Draw("APE1");

  canv_asym_diff->cd(4); asym_diff_gr[1][1]->Draw("APE1");
  canv_asym_diff->cd(5); asym_diff_gr[1][2]->Draw("APE1");
  canv_asym_diff->cd(6); asym_diff_gr[1][3]->Draw("APE1");

  canv_asym_diff->cd(7); asym_diff_gr[2][1]->Draw("APE1");
  canv_asym_diff->cd(8); asym_diff_gr[2][2]->Draw("APE1");
  canv_asym_diff->cd(9); asym_diff_gr[2][3]->Draw("APE1");


  TCanvas * canv_asym_errdiv = new TCanvas("canv_asym_errdiv","canv_asym_errdiv",sf*1000,sf*1000);
  canv_asym_errdiv->Divide(3,3);
  for(Int_t i=1; i<=9; i++) canv_asym_errdiv->GetPad(i)->SetGrid(1,1);
  canv_asym_errdiv->cd(1); asym_errdiv_gr[0][1]->Draw("APE1");
  canv_asym_errdiv->cd(2); asym_errdiv_gr[0][2]->Draw("APE1");
  canv_asym_errdiv->cd(3); asym_errdiv_gr[0][3]->Draw("APE1");

  canv_asym_errdiv->cd(4); asym_errdiv_gr[1][1]->Draw("APE1");
  canv_asym_errdiv->cd(5); asym_errdiv_gr[1][2]->Draw("APE1");
  canv_asym_errdiv->cd(6); asym_errdiv_gr[1][3]->Draw("APE1");

  canv_asym_errdiv->cd(7); asym_errdiv_gr[2][1]->Draw("APE1");
  canv_asym_errdiv->cd(8); asym_errdiv_gr[2][2]->Draw("APE1");
  canv_asym_errdiv->cd(9); asym_errdiv_gr[2][3]->Draw("APE1");

  TFile * outfile = new TFile("compare.root","RECREATE");
  canv_A_Ly->Write();
  canv_A_Lb->Write();
  canv_A_LL->Write();
  canv_asym_diff->Write();
  canv_asym_errdiv->Write();
}
