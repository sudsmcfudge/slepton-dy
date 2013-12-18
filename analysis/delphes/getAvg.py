import sys, numpy

a = numpy.loadtxt(sys.stdin)
print numpy.average(a)
