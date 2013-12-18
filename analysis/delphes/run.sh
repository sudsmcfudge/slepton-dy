#!/bin/bash

./elec_tree.exe snowmassFiles/BB-4p-0-300-v1510_14TEV_NoPileUp_*.root snowmass_ww_elec.root 
./muon_tree.exe snowmassFiles/BB-4p-0-300-v1510_14TEV_NoPileUp_*.root snowmass_ww_muon.root 
./elec_tree.exe snowmassFiles/tt-4p-0-600-v1510_14TEV_NoPileUp_*.root snowmass_tt_elec.root 
./muon_tree.exe snowmassFiles/tt-4p-0-600-v1510_14TEV_NoPileUp_*.root snowmass_tt_muon.root 
./elec_tree.exe ~/local/MadGraph5/diboson_eevvj/Events/run_14TeV_jetcuts_*/tag_1_delphes.root diboson_elec_full.root 
./muon_tree.exe ~/local/MadGraph5/diboson_mmvvj/Events/run_14TeV_jetcuts_*/tag_1_delphes.root diboson_muon_full.root 
./elec_tree.exe ~/local/MadGraph5/tt_bbeevvjj/Events/run_14TeV_jetcuts_*/tag_1_delphes.root ttbar_elec_full.root 
./muon_tree.exe ~/local/MadGraph5/tt_bbmmvvjj/Events/run_14TeV_jetcuts_*/tag_1_delphes.root ttbar_muon_full.root 
