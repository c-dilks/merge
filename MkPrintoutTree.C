// builds a tree based on "printout.dat" files produced from DrawThree.C
//
// it needs the following files:
//
//  - 12/printout_sph.dat
//  - 12/printout_pi0.dat
//  - 12/printout_sph.dat
//
//  - 13/printout_sph.dat
//  - 13/printout_pi0.dat
//  - 13/printout_sph.dat
//
//  - printout_sph.dat
//  - printout_pi0.dat
//  - printout_sph.dat

void MkPrintoutTree()
{
  TFile * outfile = new TFile("printout_tree.root","RECREATE");
  TTree * tr_sph = new TTree("tr_sph","tr_sph");
  TTree * tr_pi0 = new TTree("tr_pi0","tr_pi0");
  TTree * tr_thr = new TTree("tr_thr","tr_thr");
  gROOT->ProcessLine(".! paste 12/printout_sph.dat 13/printout_sph.dat printout_sph.dat > printout_merged_sph.dat");
  gROOT->ProcessLine(".! paste 12/printout_pi0.dat 13/printout_pi0.dat printout_pi0.dat > printout_merged_pi0.dat");
  gROOT->ProcessLine(".! paste 12/printout_thr.dat 13/printout_thr.dat printout_thr.dat > printout_merged_thr.dat");

  // branch notation
  // - each branch starts with "12", "13", or "mm", denoting run12, run13, and merged set
  // - kin and kin_err are the kinematic data points + error (either pT or E12)
  // - A_LL, A_Lb, A_Ly + errors are the asymmetry measurments and errors
  //   -- *_LL is double spin asymmetry
  //   -- *_Lb is blue single spin asymmetry
  //   -- *_Ly is yellow single spin asymmetry
  // - chi2_zero_* and ndf_zero_* are chisquare and NDF for asymmetry fit to zero
  //   -- prob_zero_* is the p-value (probability sample chisquare will be greater than this chisquare for given NDF) 
  // - chi2_cons_* and ndf_cons_* are chisquare and NDF for asymmetry fit to constant
  //   -- prob_cons_* is the p-value
  //   -- cons_* and cons_err_* are this fitted constant + error
  char tr_str[4096];
  char tr_str_12[1024];
  char tr_str_13[1024];
  char tr_str_mm[1024];
  strcpy(tr_str_12,"12_kin/F:12_kin_err/F:12_A_LL/F:12_A_LL_err/F:12_A_Lb/F:12_A_Lb_err/F:12_A_Ly/F:12_A_Ly_err/F:12_chi2_zero_LL/F:12_ndf_zero_LL/F:12_prob_zero_LL/F:12_chi2_zero_Lb/F:12_ndf_zero_Lb/F:12_prob_zero_Lb/F:12_chi2_zero_Ly/F:12_ndf_zero_Ly/F:12_prob_zero_Ly/F:12_chi2_cons_LL/F:12_ndf_cons_LL/F:12_prob_cons_LL/F:12_cons_LL/F:12_cons_err_LL/F:12_chi2_cons_Lb/F:12_ndf_cons_Lb/F:12_prob_cons_Lb/F:12_cons_Lb/F:12_cons_err_Lb/F:12_chi2_cons_Ly/F:12_ndf_cons_Ly/F:12_prob_cons_Ly/F:12_cons_Ly/F:12_cons_err_Ly/F");
  strcpy(tr_str_13,"13_kin/F:13_kin_err/F:13_A_LL/F:13_A_LL_err/F:13_A_Lb/F:13_A_Lb_err/F:13_A_Ly/F:13_A_Ly_err/F:13_chi2_zero_LL/F:13_ndf_zero_LL/F:13_prob_zero_LL/F:13_chi2_zero_Lb/F:13_ndf_zero_Lb/F:13_prob_zero_Lb/F:13_chi2_zero_Ly/F:13_ndf_zero_Ly/F:13_prob_zero_Ly/F:13_chi2_cons_LL/F:13_ndf_cons_LL/F:13_prob_cons_LL/F:13_cons_LL/F:13_cons_err_LL/F:13_chi2_cons_Lb/F:13_ndf_cons_Lb/F:13_prob_cons_Lb/F:13_cons_Lb/F:13_cons_err_Lb/F:13_chi2_cons_Ly/F:13_ndf_cons_Ly/F:13_prob_cons_Ly/F:13_cons_Ly/F:13_cons_err_Ly/F");
  strcpy(tr_str_mm,"mm_kin/F:mm_kin_err/F:mm_A_LL/F:mm_A_LL_err/F:mm_A_Lb/F:mm_A_Lb_err/F:mm_A_Ly/F:mm_A_Ly_err/F:mm_chi2_zero_LL/F:mm_ndf_zero_LL/F:mm_prob_zero_LL/F:mm_chi2_zero_Lb/F:mm_ndf_zero_Lb/F:mm_prob_zero_Lb/F:mm_chi2_zero_Ly/F:mm_ndf_zero_Ly/F:mm_prob_zero_Ly/F:mm_chi2_cons_LL/F:mm_ndf_cons_LL/F:mm_prob_cons_LL/F:mm_cons_LL/F:mm_cons_err_LL/F:mm_chi2_cons_Lb/F:mm_ndf_cons_Lb/F:mm_prob_cons_Lb/F:mm_cons_Lb/F:mm_cons_err_Lb/F:mm_chi2_cons_Ly/F:mm_ndf_cons_Ly/F:mm_prob_cons_Ly/F:mm_cons_Ly/F:mm_cons_err_Ly/F");
  sprintf(tr_str,"%s:%s:%s",tr_str_12,tr_str_13,tr_str_mm);
  tr_sph->ReadFile("printout_merged_sph.dat",tr_str);
  tr_pi0->ReadFile("printout_merged_pi0.dat",tr_str);
  tr_thr->ReadFile("printout_merged_thr.dat",tr_str);
  tr_sph->Write();
  tr_pi0->Write();
  tr_thr->Write();
};
