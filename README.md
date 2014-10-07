Short Version
-------------
- run12 & run13 analysis --> produce `spin.root` files
- `generate_env_file`
- `. env_bins.sh`
- `root -b -q toa_merger.C`
- `asym_call_jets`
- `root -b -q MkPrintoutTree.C`
- `root CompareRuns.C`


Longitudinal Run12 and Run13 Merger
-----------------------------------

0. run full analysis on run12 and run13 data (at least produce
   `phiset/all.root`); make sure you use the same binning for each
   - `12/` and `13/` are symlinks to the spin analysis directories
     for run 12 and 13, respectively
   - run12 & run13 binning are kept the same by symlinks from
     `spin12/Bin_Splitter.C` and `spin13/Bin_Splitter.C` to 
     `./Bin_Splitter.C`

1. run `generate_env_file` and source `env_bins.sh`
   - compares environment used in run 12 and 13 and produces
     env_bins.sh if they are the same; if not, it will complain

2. run `toa_merger.C` to merge `1{2,3}/phiset/all.root`
   - produces merged file `phiset/all.root`

3. run `asym_call` or `asym_call_jets` to run the asymmetry analysis
   on the new `phiset/all.root` file; outputs are spin.root, three.png

--- DEPRECATED CODE BELOW ---


4. run `MkPrintoutTree.C`
   the `printout.dat` files produced for run12 and run13 can be compared 
   with that produced from the merged data set; execute `MkPrintoutTree.C`
   to build three trees (single photon, pions, >2 photons) with the following
   branches:
   - each branch starts with `12`, `13`, or `mm`, denoting run12, run13, and merged set
   - `kin` and `kin_err` are the kinematic data points + error (either pT or E12)
   - `A_LL`, `A_Lb`, `A_Ly` + errors are the asymmetry measurments and errors
     -- `*_LL` is double spin asymmetry
     -- `*_Lb` is blue single spin asymmetry
     -- `*_Ly` is yellow single spin asymmetry
   - `chi2_zero_*` and `ndf_zero_*` are chisquare and NDF for asymmetry fit to zero
     -- `prob_zero_*` is the p-value (probability sample chisquare will be greater than this chisquare for given NDF) 
   - `chi2_cons_*` and `ndf_cons_*` are chisquare and NDF for asymmetry fit to constant
     -- `prob_cons_*` is the p-value
     -- `cons_*` and `cons_err_*` are this fitted constant + error

5. run `CompareRuns.C` to produce TCanvases with the following:
   - AL blue 
   - AL yellow
   - ALL 
   - difference between nominal asymmetries for run12 - run13
   - ratio of error bars between run12 / run13
