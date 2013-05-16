signal_results_table.dat

masses in GeV, cross section in pb

m_slep m_chi n_after_cuts n_matched_before_cuts n_generated $sigma_pb


Steps:
generate events using production script
regenerate as necessary to produce nonzero N after cuts
run_analysis to produce number of counts after cuts
move to exclusion:
sort binoLSP_ATLAS_table
run gentable.py
run script.sh
cp *_cls.dat to Dropbox/mySlepton/
