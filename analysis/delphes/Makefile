CPP = g++

EXLIB = -L/home/eckel/local/MadGraph5/ExRootAnalysis/lib/ -lExRootAnalysis
EXINC = -I/home/eckel/local/MadGraph5/ExRootAnalysis

DLIB = -L/home/eckel/local/Delphes-3.0.10/ -lDelphes
DINC = -I/home/eckel/local/Delphes-3.0.10/

ROOTCFG = -I`root-config --incdir --libs`

default:
	echo "PICK SOMETHING"

elec_cuts:
	$(CPP) $(ROOTCFG) -o elec_cuts.exe runcuts_ee.cxx

muon_cuts:
	$(CPP) $(ROOTCFG) -D USEMUON -o muon_cuts.exe runcuts_ee.cxx

elec_tree:
	$(CPP) $(EXINC) $(DINC) $(ROOTCFG) $(EXLIB) $(DLIB) -o elec_tree.exe maketree_ee.cxx

muon_tree:
	$(CPP) $(EXINC) $(DINC) $(ROOTCFG) $(EXLIB) $(DLIB) -D USEMUON -o muon_tree.exe maketree_ee.cxx

elec_tree2:
	$(CPP) $(EXINC) $(DINC) $(ROOTCFG) $(EXLIB) $(DLIB) -o elec_tree.exe maketree2.cxx

muon_tree2:
	$(CPP) $(EXINC) $(DINC) $(ROOTCFG) $(EXLIB) $(DLIB) -D USEMUON -o muon_tree.exe maketree2.cxx
