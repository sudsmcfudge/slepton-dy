CPP = g++

EXLIB = -L/home/eckel/local/MadGraph5/ExRootAnalysis/lib/ -lExRootAnalysis
EXINC = -I/home/eckel/local/MadGraph5/ExRootAnalysis

ROOTCFG = -I`root-config --incdir --libs`

default:
	echo "PICK SOMETHING"

confidence: 
	$(CPP) $(ROOTCFG) -o conf.exe myconfidence.cxx
