// merges run12 & run13 phiset/all.root files to ./phiset/all.root

void toa_merger(const char * file12 = "12/phiset/all.root",
                const char * file13 = "13/phiset/all.root")
{
  // open phiset/all.root files for each run
  TFile * tf12 = new TFile(file12,"READ");
  TFile * tf13 = new TFile(file13,"READ");
  // define output file
  TFile * tfmerge = new TFile("phiset/all.root","RECREATE");


  // get bins from environment
  Int_t phi_bins0, eta_bins0, pt_bins0, en_bins0;
  if(gSystem->Getenv("PHI_BINS")==NULL){fprintf(stderr,"ERROR: source env vars\n"); return;};
  sscanf(gSystem->Getenv("PHI_BINS"),"%d",&phi_bins0);
  sscanf(gSystem->Getenv("ETA_BINS"),"%d",&eta_bins0);
  sscanf(gSystem->Getenv("PT_BINS"),"%d",&pt_bins0);
  sscanf(gSystem->Getenv("EN_BINS"),"%d",&en_bins0);
  const Int_t phi_bins = phi_bins0;
  const Int_t eta_bins = eta_bins0;
  const Int_t pt_bins = pt_bins0;
  const Int_t en_bins = en_bins0;
  Float_t phi_div[phi_bins+1];
  Float_t eta_div[eta_bins+1];
  Float_t pt_div[pt_bins+1];
  Float_t en_div[en_bins+1];
  char phi_div_env[phi_bins+1][20];
  char eta_div_env[eta_bins+1][20];
  char pt_div_env[pt_bins+1][20];
  char en_div_env[en_bins+1][20];
  for(Int_t i=0; i<=phi_bins; i++)
  {
    sprintf(phi_div_env[i],"PHI_DIV_%d",i);
    sscanf(gSystem->Getenv(phi_div_env[i]),"%f",&(phi_div[i]));
    printf("%s %f\n",phi_div_env[i],phi_div[i]);
  };
  for(Int_t i=0; i<=eta_bins; i++)
  {
    sprintf(eta_div_env[i],"ETA_DIV_%d",i);
    sscanf(gSystem->Getenv(eta_div_env[i]),"%f",&(eta_div[i]));
    printf("%s %f\n",eta_div_env[i],eta_div[i]);
  };
  for(Int_t i=0; i<=pt_bins; i++)
  {
    sprintf(pt_div_env[i],"PT_DIV_%d",i);
    sscanf(gSystem->Getenv(pt_div_env[i]),"%f",&(pt_div[i]));
    printf("%s %f\n",pt_div_env[i],pt_div[i]);
  };
  for(Int_t i=0; i<=en_bins; i++)
  {
    sprintf(en_div_env[i],"EN_DIV_%d",i);
    sscanf(gSystem->Getenv(en_div_env[i]),"%f",&(en_div[i]));
    printf("%s %f\n",en_div_env[i],en_div[i]);
  };
  Float_t phi_low; sscanf(gSystem->Getenv("PHI_LOW"),"%f",&phi_low);
  Float_t phi_high; sscanf(gSystem->Getenv("PHI_HIGH"),"%f",&phi_high);
  Float_t eta_low; sscanf(gSystem->Getenv("ETA_LOW"),"%f",&eta_low);
  Float_t eta_high; sscanf(gSystem->Getenv("ETA_HIGH"),"%f",&eta_high);
  Float_t pt_low; sscanf(gSystem->Getenv("PT_LOW"),"%f",&pt_low);
  Float_t pt_high; sscanf(gSystem->Getenv("PT_HIGH"),"%f",&pt_high);
  Float_t en_low; sscanf(gSystem->Getenv("EN_LOW"),"%f",&en_low);
  Float_t en_high; sscanf(gSystem->Getenv("EN_HIGH"),"%f",&en_high);
  char jtype[3][8];
  strcpy(jtype[0],"sph");
  strcpy(jtype[1],"pi0");
  strcpy(jtype[2],"thr");


  // define objects to be opened & their names
  TObjArray * phi_arr_12[3][4][eta_bins][pt_bins][en_bins]; // [jtype] [spin] [eta] [pt] [en]
  TObjArray * phi_arr_13[3][4][eta_bins][pt_bins][en_bins]; // [jtype] [spin] [eta] [pt] [en]
  TObjArray * pt_wdist_arr_12[3][eta_bins][en_bins]; // [jtype] [eta] [en]
  TObjArray * pt_wdist_arr_13[3][eta_bins][en_bins]; // [jtype] [eta] [en]
  TObjArray * en_wdist_arr_12[3][eta_bins][pt_bins]; // [jtype] [eta] [pt]
  TObjArray * en_wdist_arr_13[3][eta_bins][pt_bins]; // [jtype] [eta] [pt]
  TObjArray * mm_wdist_arr_12[3][eta_bins][pt_bins][en_bins]; // [jtype] [eta] [pt] [en]
  TObjArray * mm_wdist_arr_13[3][eta_bins][pt_bins][en_bins]; // [jtype] [eta] [pt] [en]
  TH1D * pt_wdist_tot_12[3][eta_bins][en_bins]; // [jtype] [eta] [en]
  TH1D * pt_wdist_tot_13[3][eta_bins][en_bins]; // [jtype] [eta] [en]
  TH1D * en_wdist_tot_12[3][eta_bins][pt_bins]; // [jtype] [eta] [pt]
  TH1D * en_wdist_tot_13[3][eta_bins][pt_bins]; // [jtype] [eta] [pt]
  TH1D * mm_wdist_tot_12[3][eta_bins][pt_bins][en_bins]; // [jtype] [eta] [pt] [en]
  TH1D * mm_wdist_tot_13[3][eta_bins][pt_bins][en_bins]; // [jtype] [eta] [pt] [en]
  char phi_arr_n[3][4][eta_bins][pt_bins][en_bins][64];
  char phi_arr_wn[3][4][eta_bins][pt_bins][en_bins][64]; // (without directory.. used to write merged array)
  char pt_wdist_arr_n[3][eta_bins][en_bins][64];
  char en_wdist_arr_n[3][eta_bins][pt_bins][64];
  char mm_wdist_arr_n[3][eta_bins][pt_bins][en_bins][64];
  char pt_wdist_tot_n[3][eta_bins][en_bins][64];
  char en_wdist_tot_n[3][eta_bins][pt_bins][64];
  char mm_wdist_tot_n[3][eta_bins][pt_bins][en_bins][64];

  
  // get objects from tfiles
  printf("opening arrays from run 12 & run 13 files...\n");
  for(Int_t j=0; j<3; j++)
  {
    // phi distribution object arrays 
    for(Int_t s=0; s<4; s++)
    {
      for(Int_t g=0; g<eta_bins; g++)
      {
        for(Int_t p=0; p<pt_bins; p++)
        {
          for(Int_t e=0; e<en_bins; e++)
          {
            sprintf(phi_arr_n[j][s][g][p][e],"/%s/phi_dist_%s_s%d_g%d_p%d_e%d",jtype[j],jtype[j],s,g,p,e);
            sprintf(phi_arr_wn[j][s][g][p][e],"phi_dist_%s_s%d_g%d_p%d_e%d",jtype[j],s,g,p,e);
            phi_arr_12[j][s][g][p][e] = (TObjArray*) tf12->Get(phi_arr_n[j][s][g][p][e]);
            phi_arr_13[j][s][g][p][e] = (TObjArray*) tf13->Get(phi_arr_n[j][s][g][p][e]);
          };
        };
      };
    };
    // pt wdists & tot hists
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t e=0; e<en_bins; e++)
      {
        sprintf(pt_wdist_arr_n[j][g][e],"pt_wdist_%s_g%d_e%d",jtype[j],g,e);
        pt_wdist_arr_12[j][g][e] = (TObjArray*) tf12->Get(pt_wdist_arr_n[j][g][e]);
        pt_wdist_arr_13[j][g][e] = (TObjArray*) tf13->Get(pt_wdist_arr_n[j][g][e]);
        sprintf(pt_wdist_tot_n[j][g][e],"pt_wdist_tot_%s_g%d_e%d",jtype[j],g,e);
        pt_wdist_tot_12[j][g][e] = (TH1D*) tf12->Get(pt_wdist_tot_n[j][g][e]);
        pt_wdist_tot_13[j][g][e] = (TH1D*) tf13->Get(pt_wdist_tot_n[j][g][e]);
      };
    };
    // en wdists & tot hists
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        sprintf(en_wdist_arr_n[j][g][p],"en_wdist_%s_g%d_p%d",jtype[j],g,p);
        en_wdist_arr_12[j][g][p] = (TObjArray*) tf12->Get(en_wdist_arr_n[j][g][p]);
        en_wdist_arr_13[j][g][p] = (TObjArray*) tf13->Get(en_wdist_arr_n[j][g][p]);
        sprintf(en_wdist_tot_n[j][g][p],"en_wdist_tot_%s_g%d_p%d",jtype[j],g,p);
        en_wdist_tot_12[j][g][p] = (TH1D*) tf12->Get(en_wdist_tot_n[j][g][p]);
        en_wdist_tot_13[j][g][p] = (TH1D*) tf13->Get(en_wdist_tot_n[j][g][p]);
      };
    };
    // mm wdists & tot hists
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        for(Int_t e=0; e<en_bins; e++)
        {
          sprintf(mm_wdist_arr_n[j][g][p][e],"mm_wdist_%s_g%d_p%d_e%d",jtype[j],g,p,e);
          mm_wdist_arr_12[j][g][p][e] = (TObjArray*) tf12->Get(mm_wdist_arr_n[j][g][p][e]);
          mm_wdist_arr_13[j][g][p][e] = (TObjArray*) tf13->Get(mm_wdist_arr_n[j][g][p][e]);
          sprintf(mm_wdist_tot_n[j][g][p][e],"mm_wdist_tot_%s_g%d_p%d_e%d",jtype[j],g,p,e);
          mm_wdist_tot_12[j][g][p][e] = (TH1D*) tf12->Get(mm_wdist_tot_n[j][g][p][e]);
          mm_wdist_tot_13[j][g][p][e] = (TH1D*) tf13->Get(mm_wdist_tot_n[j][g][p][e]);
        };
      };
    };
  };


  // initialize merge arrays
  TObjArray * phi_arr_merge[3][4][eta_bins][pt_bins][en_bins]; // [jtype] [spin] [eta] [pt] [en]
  TObjArray * pt_wdist_arr_merge[3][eta_bins][en_bins]; // [jtype] [eta] [en]
  TObjArray * en_wdist_arr_merge[3][eta_bins][pt_bins]; // [jtype] [eta] [pt]
  TObjArray * mm_wdist_arr_merge[3][eta_bins][pt_bins][en_bins]; // [jtype] [eta] [pt] [en]

  
  // merge run 12 & 13 in to new arrays
  printf("merging arrays...\n");
  for(Int_t j=0; j<3; j++)
  {
    // phi distribution object arrays 
    for(Int_t s=0; s<4; s++)
    {
      for(Int_t g=0; g<eta_bins; g++)
      {
        for(Int_t p=0; p<pt_bins; p++)
        {
          for(Int_t e=0; e<en_bins; e++)
          {
            phi_arr_merge[j][s][g][p][e] = new TObjArray();
            for(Int_t o=0; o<phi_arr_12[j][s][g][p][e]->GetEntries(); o++)
              phi_arr_merge[j][s][g][p][e]->AddLast(phi_arr_12[j][s][g][p][e]->At(o));
            for(Int_t o=0; o<phi_arr_13[j][s][g][p][e]->GetEntries(); o++)
              phi_arr_merge[j][s][g][p][e]->AddLast(phi_arr_13[j][s][g][p][e]->At(o));
          };
        };
      };
    };
    // pt wdist arrays
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t e=0; e<en_bins; e++)
      {
        pt_wdist_arr_merge[j][g][e] = new TObjArray();
        for(Int_t o=0; o<pt_wdist_arr_12[j][g][e]->GetEntries(); o++)
          pt_wdist_arr_merge[j][g][e]->AddLast(pt_wdist_arr_12[j][g][e]->At(o));
        for(Int_t o=0; o<pt_wdist_arr_13[j][g][e]->GetEntries(); o++)
          pt_wdist_arr_merge[j][g][e]->AddLast(pt_wdist_arr_13[j][g][e]->At(o));
      };
    };
    // en wdist arrays 
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        en_wdist_arr_merge[j][g][p] = new TObjArray();
        for(Int_t o=0; o<en_wdist_arr_12[j][g][p]->GetEntries(); o++)
          en_wdist_arr_merge[j][g][p]->AddLast(en_wdist_arr_12[j][g][p]->At(o));
        for(Int_t o=0; o<en_wdist_arr_13[j][g][p]->GetEntries(); o++)
          en_wdist_arr_merge[j][g][p]->AddLast(en_wdist_arr_13[j][g][p]->At(o));
      };
    };
    // mm wdist arrays
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        for(Int_t e=0; e<en_bins; e++)
        {
          mm_wdist_arr_merge[j][g][p][e] = new TObjArray();
          for(Int_t o=0; o<mm_wdist_arr_12[j][g][p][e]->GetEntries(); o++)
            mm_wdist_arr_merge[j][g][p][e]->AddLast(mm_wdist_arr_12[j][g][p][e]->At(o));
          for(Int_t o=0; o<mm_wdist_arr_13[j][g][p][e]->GetEntries(); o++)
            mm_wdist_arr_merge[j][g][p][e]->AddLast(mm_wdist_arr_13[j][g][p][e]->At(o));
        };
      };
    };
  };


  // add tot wdists for runs 12 & 13
  // -- this uses the TH1 method (run 12 hist) = (run 12 hist) + (run 13 hist)
  //    so that the run 12 hists *become* the merged distributions and in turn
  //    are written to the merged phiset/all.root file
  printf("adding run 12 & run 13 tot wdists...\n");
  for(Int_t j=0; j<3; j++)
  {
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t e=0; e<en_bins; e++)
      {
        pt_wdist_tot_12[j][g][e]->Add(pt_wdist_tot_13[j][g][e],1);
      };
      for(Int_t p=0; p<pt_bins; p++)
      {
        en_wdist_tot_12[j][g][p]->Add(en_wdist_tot_13[j][g][p],1);
      };
      for(Int_t p=0; p<pt_bins; p++)
      {
        for(Int_t e=0; e<en_bins; e++)
        {
          mm_wdist_tot_12[j][g][p][e]->Add(mm_wdist_tot_13[j][g][p][e],1);
        };
      };
    };
  };
  

  // write output in merged file
  //
  // write phi dist arrays
  printf("writing output to phiset/all.root...\n");
  for(Int_t j=0; j<3; j++)
  {
    tfmerge->cd();
    tfmerge->mkdir(jtype[j]);
    tfmerge->cd(jtype[j]);
    for(Int_t s=0; s<4; s++)
    {
      for(Int_t g=0; g<eta_bins; g++)
      {
        for(Int_t p=0; p<pt_bins; p++)
        {
          for(Int_t e=0; e<en_bins; e++)
          {
            phi_arr_merge[j][s][g][p][e]->Write(phi_arr_wn[j][s][g][p][e],TObject::kSingleKey);
            //printf("%d\n",phi_arr_merge[j][s][g][p][e]->GetEntries());
          };
        };
      };
    };
  };
  // write wdist arrays
  tfmerge->cd();
  for(Int_t j=0; j<3; j++)
  {
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t e=0; e<en_bins; e++)
      {
        pt_wdist_arr_merge[j][g][e]->Write(pt_wdist_arr_n[j][g][e],TObject::kSingleKey);
        //printf("%d\n",pt_wdist_arr_merge[j][g][e]->GetEntries());
      };
    };
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        en_wdist_arr_merge[j][g][p]->Write(en_wdist_arr_n[j][g][p],TObject::kSingleKey);
        //printf("%d\n",en_wdist_arr_merge[j][g][p]->GetEntries());
      };
    };
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        for(Int_t e=0; e<en_bins; e++)
        {
          mm_wdist_arr_merge[j][g][p][e]->Write(mm_wdist_arr_n[j][g][p][e],TObject::kSingleKey);
          //printf("%d\n",mm_wdist_arr_merge[j][g][p][e]->GetEntries());
        };
      };
    };
  };
  // write tot wdists (recall that (run12 hist) = (run12 hist) + (run13 hist), 
  //                   so we just have to write run12 hists to tfile here...)
  for(Int_t j=0; j<3; j++)
  {
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t e=0; e<en_bins; e++)
      {
        pt_wdist_tot_12[j][g][e]->Write(pt_wdist_tot_n[j][g][e]);
      };
    };
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        en_wdist_tot_12[j][g][p]->Write(en_wdist_tot_n[j][g][p]);
      };
    };
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        for(Int_t e=0; e<en_bins; e++)
        {
          mm_wdist_tot_12[j][g][p][e]->Write(mm_wdist_tot_n[j][g][p][e]);
        };
      };
    };
  };
};
