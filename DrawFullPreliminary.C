// draws STAR preliminary plots for SPIN 2014
// -- draws 35mr and 100mr on same plot

void DrawFullPreliminary(const char * kin="pt")
{
  const Double_t SYSTEMATIC_12 = 0.000282; // FOR RUN 12 !!!!!!!!!!!!!!!!!!!!!
  const Double_t SYSTEMATIC_13 = 0.000617; // FOR RUN 13 !!!!!!!!!!!!!!!!!!!!!


  if(!(!strcmp(kin,"en")||!strcmp(kin,"pt")))
  {
    fprintf(stderr,"ERROR: kin must be \"en\" or \"pt\"");
    return;
  };

  // open files
  char fileS_n[128]; // 35mr
  char fileL_n[128]; // 100mr 
  sprintf(fileS_n,"output_for_spin/output_%s_35mr/spin_pi0.root",kin);
  sprintf(fileL_n,"output_for_spin/output_%s_100mr/spin_pi0.root",kin);
  TFile * fileS = new TFile(fileS_n,"READ");
  TFile * fileL = new TFile(fileL_n,"READ");
  TFile * prelim12 = new TFile("12/prelim.root","READ");
  TFile * prelim13 = new TFile("13/prelim.root","READ");


  // get graphs and set title strings
  TGraphErrors * grS;
  TGraphErrors * grL;
  char title_str[128];
  char axis_str[128];
  Double_t offset;
  if(!strcmp(kin,"pt")) 
  {
    grS = (TGraphErrors*) fileS->Get("A_LL/pt_dep_a3_g0_e0");
    grL = (TGraphErrors*) fileL->Get("A_LL/pt_dep_a3_g0_e0");
    strcpy(title_str,"#pi^{0} Double Helicity Asymmetry A_{LL} vs. p_{T}");
    strcpy(axis_str,"p_{T} [GeV/c]");
    offset = 0.025;
  }
  else if(!strcmp(kin,"en"))
  {
    grS = (TGraphErrors*) fileS->Get("A_LL/en_dep_a3_g0_p0");
    grL = (TGraphErrors*) fileL->Get("A_LL/en_dep_a3_g0_p0");
    strcpy(title_str,"#pi^{0} Double Helicity Asymmetry A_{LL} vs. E_{#gamma#gamma}");
    strcpy(axis_str,"E_{#gamma#gamma} [GeV]");
    offset = 0.25;
  };


  // get MAX_BINS (maximum no. kinematic bins)
  Int_t MAX_BINS_tmp = grL->GetN();
  const Int_t MAX_BINS = MAX_BINS_tmp;

  // offset the 100mr graph
  TGraphErrors * grLoffset = new TGraphErrors();
  Double_t x,y,x_e,y_e;
  for(Int_t n=0; n<MAX_BINS; n++)
  {
    grL->GetPoint(n,x,y);
    x_e = grL->GetErrorX(n);
    y_e = grL->GetErrorY(n);
    grLoffset->SetPoint(n,x+offset,y);
    grLoffset->SetPointError(n,x_e,y_e);
  };


  // get graph of number of pi0s vs. kinematic (pt or E) from prelim.root files
  TGraph * numgrS_12;
  TGraph * numgrL_12;
  TGraph * numgrS_13;
  TGraph * numgrL_13;
  numgrS_12 = (TGraph*) prelim12->Get("numgrS");
  numgrL_12 = (TGraph*) prelim12->Get("numgrL");
  numgrS_13 = (TGraph*) prelim13->Get("numgrS");
  numgrL_13 = (TGraph*) prelim13->Get("numgrL");


  // systematic uncertainties
  TGraphErrors * grSsys = new TGraphErrors();
  TGraphErrors * grLsys = new TGraphErrors();
  Double_t xp_12,yp_12,xp_13,yp_13;
  for(Int_t n=0; n<MAX_BINS; n++)
  {
    grS->GetPoint(n,x,y);
    numgrS_12->GetPoint(n,xp_12,yp_12);
    numgrS_13->GetPoint(n,xp_13,yp_13);
    x_e = grS->GetErrorX(n);
    y_e = (SYSTEMATIC_12*xp_12 + SYSTEMATIC_13*xp_13) / (xp_12 + xp_13);
    grSsys->SetPoint(n,x,y);
    grSsys->SetPointError(n,x_e,y_e);

    grLoffset->GetPoint(n,x,y); // use offset here
    numgrL_12->GetPoint(n,xp_12,yp_12);
    numgrL_13->GetPoint(n,xp_13,yp_13);
    x_e = grL->GetErrorX(n);
    y_e = (SYSTEMATIC_12*xp_12 + SYSTEMATIC_13*xp_13) / (xp_12 + xp_13);
    grLsys->SetPoint(n,x,y);
    grLsys->SetPointError(n,x_e,y_e);
  };

  grSsys->SetFillColor(kRed);
  grLsys->SetFillColor(kBlue);
  grSsys->SetFillStyle(3001);
  grLsys->SetFillStyle(3001);
    



  // zero line
  TLine * zero_line = new TLine(grL->GetXaxis()->GetXmin(),0,grL->GetXaxis()->GetXmax(),0);
  zero_line->SetLineColor(kCyan+3);
  zero_line->SetLineWidth(3);
  zero_line->SetLineStyle(2);


  // plot style
  grS->SetMarkerColor(kRed);
  grS->SetLineColor(kRed);
  grS->SetMarkerSize(2);
  grS->SetMarkerStyle(kFullCircle);
  grS->SetLineWidth(3);
  grL->SetMarkerColor(kBlue);
  grL->SetLineColor(kBlue);
  grL->SetMarkerSize(2);
  grL->SetMarkerStyle(kFullSquare);
  grL->SetLineWidth(3);
  grLoffset->SetMarkerColor(kBlue);
  grLoffset->SetLineColor(kBlue);
  grLoffset->SetMarkerSize(2);
  grLoffset->SetMarkerStyle(kFullSquare);
  grLoffset->SetLineWidth(3);


  // create multigraph
  TMultiGraph * mg = new TMultiGraph();
  mg->Add(grS);
  //mg->Add(grL);
  mg->Add(grLoffset);


  // plot tiles & axes titles
  grS->SetTitle(title_str);
  grS->GetXaxis()->SetTitle(axis_str);
  grS->GetYaxis()->SetTitle("A_{LL}");
  grS->GetXaxis()->SetLabelSize(0.05);
  grS->GetYaxis()->SetLabelSize(0.05);
  grS->GetXaxis()->SetTitleOffset(1.0);
  grS->GetYaxis()->SetTitleOffset(1.0);
  grS->GetXaxis()->SetTitleSize(0.05);
  grS->GetYaxis()->SetTitleSize(0.05);
  grL->SetTitle(title_str);
  grL->GetXaxis()->SetTitle(axis_str);
  grL->GetYaxis()->SetTitle("A_{LL}");
  grL->GetXaxis()->SetLabelSize(0.05);
  grL->GetYaxis()->SetLabelSize(0.05);
  grL->GetXaxis()->SetTitleOffset(1.0);
  grL->GetYaxis()->SetTitleOffset(1.0);
  grL->GetXaxis()->SetTitleSize(0.05);
  grL->GetYaxis()->SetTitleSize(0.05);


  // fit
  printf("\n\n35mr FIT RESULTS");
  grS->Fit("pol0","N","",grS->GetXaxis()->GetXmin(),grS->GetXaxis()->GetXmax());
  printf("\n\n100mr FIT RESULTS");
  grL->Fit("pol0","N","",grL->GetXaxis()->GetXmin(),grL->GetXaxis()->GetXmax());



  // draw
  TCanvas * prelim_plot = new TCanvas("prelim_plot","prelim_plot",1000,500);
  mg->Draw("ape");
  grLsys->Draw("2");
  grSsys->Draw("2");
  mg->Draw("pe");
  zero_line->Draw();


  // set multigraph parameters & update tcanvas
  mg->SetTitle(title_str);
  mg->GetXaxis()->SetTitle(axis_str);
  mg->GetYaxis()->SetTitle("A_{LL}");
  mg->GetXaxis()->SetLabelSize(0.05);
  mg->GetYaxis()->SetLabelSize(0.05);
  mg->GetXaxis()->SetTitleOffset(1.0);
  mg->GetYaxis()->SetTitleOffset(1.0);
  mg->GetXaxis()->SetTitleSize(0.05);
  mg->GetYaxis()->SetTitleSize(0.05);
  mg->GetXaxis()->SetLimits(grS->GetXaxis()->GetXmin(),grS->GetXaxis()->GetXmax());
  prelim_plot->Update();


  TFile * outfile = new TFile("prelim.root","RECREATE");
  prelim_plot->Write("prelim_plot");
};

