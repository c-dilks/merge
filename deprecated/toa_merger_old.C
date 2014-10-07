// merges phiset/all.root from 2012 and 2013 data sets

void toa_merger(const char * file12 = "12/phiset/all.root",
                const char * file13 = "13/phiset/all.root")
{
  // open run12 and run13 files
  gROOT->Reset();
  TFile * tfile12 = new TFile(file12,"READ");
  TFile * tfile13 = new TFile(file13,"READ");

  
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


  // read phi distribution object arrays
  TObjArray * infile_sph_arr12[4][eta_bins][pt_bins][en_bins];
  TObjArray * infile_pi0_arr12[4][eta_bins][pt_bins][en_bins];
  TObjArray * infile_thr_arr12[4][eta_bins][pt_bins][en_bins];
  TObjArray * infile_sph_arr13[4][eta_bins][pt_bins][en_bins];
  TObjArray * infile_pi0_arr13[4][eta_bins][pt_bins][en_bins];
  TObjArray * infile_thr_arr13[4][eta_bins][pt_bins][en_bins];
  char infile_sph_arr12_n[4][eta_bins][pt_bins][en_bins][64];
  char infile_pi0_arr12_n[4][eta_bins][pt_bins][en_bins][64];
  char infile_thr_arr12_n[4][eta_bins][pt_bins][en_bins][64];
  char infile_sph_arr13_n[4][eta_bins][pt_bins][en_bins][64];
  char infile_pi0_arr13_n[4][eta_bins][pt_bins][en_bins][64];
  char infile_thr_arr13_n[4][eta_bins][pt_bins][en_bins][64];
  for(Int_t s=0; s<4; s++)
  {
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        for(Int_t e=0; e<en_bins; e++)
        {
          sprintf(infile_sph_arr12_n[s][g][p][e],"sph/phi_dist_sph_s%d_g%d_p%d_e%d",s,g,p,e);
          sprintf(infile_pi0_arr12_n[s][g][p][e],"pi0/phi_dist_pi0_s%d_g%d_p%d_e%d",s,g,p,e);
          sprintf(infile_thr_arr12_n[s][g][p][e],"thr/phi_dist_thr_s%d_g%d_p%d_e%d",s,g,p,e);
          sprintf(infile_sph_arr13_n[s][g][p][e],"sph/phi_dist_sph_s%d_g%d_p%d_e%d",s,g,p,e);
          sprintf(infile_pi0_arr13_n[s][g][p][e],"pi0/phi_dist_pi0_s%d_g%d_p%d_e%d",s,g,p,e);
          sprintf(infile_thr_arr13_n[s][g][p][e],"thr/phi_dist_thr_s%d_g%d_p%d_e%d",s,g,p,e);

          infile_sph_arr12[s][g][p][e] = (TObjArray*) tfile12->Get(infile_sph_arr12_n[s][g][p][e]);
          infile_pi0_arr12[s][g][p][e] = (TObjArray*) tfile12->Get(infile_pi0_arr12_n[s][g][p][e]);
          infile_thr_arr12[s][g][p][e] = (TObjArray*) tfile12->Get(infile_thr_arr12_n[s][g][p][e]);
          infile_sph_arr13[s][g][p][e] = (TObjArray*) tfile13->Get(infile_sph_arr13_n[s][g][p][e]);
          infile_pi0_arr13[s][g][p][e] = (TObjArray*) tfile13->Get(infile_pi0_arr13_n[s][g][p][e]);
          infile_thr_arr13[s][g][p][e] = (TObjArray*) tfile13->Get(infile_thr_arr13_n[s][g][p][e]);
        };
      };
    };
  };


  // merge object arrays and write to output file
  char outfile_n[128];
  strcpy(outfile_n,"phiset/all.root");
  TFile * outfile = new TFile(outfile_n,"RECREATE");
  outfile->mkdir("sph");
  outfile->mkdir("pi0");
  outfile->mkdir("thr");
  TObjArray * outfile_sph_arr[4][eta_bins][pt_bins][en_bins];
  TObjArray * outfile_pi0_arr[4][eta_bins][pt_bins][en_bins];
  TObjArray * outfile_thr_arr[4][eta_bins][pt_bins][en_bins];
  char outfile_sph_arr_n[4][eta_bins][pt_bins][en_bins][64];
  char outfile_pi0_arr_n[4][eta_bins][pt_bins][en_bins][64];
  char outfile_thr_arr_n[4][eta_bins][pt_bins][en_bins][64];
  for(Int_t s=0; s<4; s++)
  {
    for(Int_t g=0; g<eta_bins; g++)
    {
      for(Int_t p=0; p<pt_bins; p++)
      {
        for(Int_t e=0; e<en_bins; e++)
        {
          sprintf(outfile_sph_arr_n[s][g][p][e],"phi_dist_sph_s%d_g%d_p%d_e%d",s,g,p,e);
          sprintf(outfile_pi0_arr_n[s][g][p][e],"phi_dist_pi0_s%d_g%d_p%d_e%d",s,g,p,e);
          sprintf(outfile_thr_arr_n[s][g][p][e],"phi_dist_thr_s%d_g%d_p%d_e%d",s,g,p,e);

          outfile_sph_arr[s][g][p][e] = new TObjArray();
          outfile_pi0_arr[s][g][p][e] = new TObjArray();
          outfile_thr_arr[s][g][p][e] = new TObjArray();

          for(Int_t it=0; it<infile_sph_arr12[s][g][p][e]->GetEntries(); it++)
            outfile_sph_arr[s][g][p][e]->AddLast((TH1D*)(infile_sph_arr12[s][g][p][e]->At(it)));
          for(Int_t it=0; it<infile_sph_arr13[s][g][p][e]->GetEntries(); it++)
            outfile_sph_arr[s][g][p][e]->AddLast((TH1D*)(infile_sph_arr13[s][g][p][e]->At(it)));

          for(Int_t it=0; it<infile_pi0_arr12[s][g][p][e]->GetEntries(); it++)
            outfile_pi0_arr[s][g][p][e]->AddLast((TH1D*)(infile_pi0_arr12[s][g][p][e]->At(it)));
          for(Int_t it=0; it<infile_pi0_arr13[s][g][p][e]->GetEntries(); it++)
            outfile_pi0_arr[s][g][p][e]->AddLast((TH1D*)(infile_pi0_arr13[s][g][p][e]->At(it)));

          for(Int_t it=0; it<infile_thr_arr12[s][g][p][e]->GetEntries(); it++)
            outfile_thr_arr[s][g][p][e]->AddLast((TH1D*)(infile_thr_arr12[s][g][p][e]->At(it)));
          for(Int_t it=0; it<infile_thr_arr13[s][g][p][e]->GetEntries(); it++)
            outfile_thr_arr[s][g][p][e]->AddLast((TH1D*)(infile_thr_arr13[s][g][p][e]->At(it)));

          outfile->cd("/sph");
          outfile_sph_arr[s][g][p][e]->Write(outfile_sph_arr_n[s][g][p][e],TObject::kSingleKey);
          outfile->cd("/pi0");
          outfile_pi0_arr[s][g][p][e]->Write(outfile_pi0_arr_n[s][g][p][e],TObject::kSingleKey);
          outfile->cd("/thr");
          outfile_thr_arr[s][g][p][e]->Write(outfile_thr_arr_n[s][g][p][e],TObject::kSingleKey);
        };
      };
    };
  };
  printf("%s and %s have been merged to %s\n",file12,file13,outfile_n);
};
