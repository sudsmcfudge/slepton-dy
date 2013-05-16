CPP = g++

EXLIB = -L/home/eckel/local/MadGraph5/ExRootAnalysis/lib/ -lExRootAnalysis
EXINC = -I/home/eckel/local/MadGraph5/ExRootAnalysis

ROOTCFG = -I`root-config --incdir --libs`

default:
	echo "PICK SOMETHING"

tree:	
	$(CPP) $(EXINC) $(ROOTCFG) $(EXLIB) -o tree.exe maketree.cxx

cuts: 
	$(CPP) $(ROOTCFG) -o cuts.exe runcuts.cxx

mt2_cuts:
	$(CPP) $(ROOTCFG) -o mt2_cuts.exe runcuts_mt2.cxx

high: 
	$(CPP) $(ROOTCFG) -o high_mass_cuts.exe high_mass_cuts.cxx

mt2:
	$(CPP) $(EXINC) $(ROOTCFG) $(EXLIB) -o mt2_tree.exe maketree_mt2.cxx
