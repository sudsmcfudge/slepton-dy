#!/usr/bin/env python

from numpy import *

#all cross sections in terms of pb

def lumiplot(fn, sigma_calchep, sigma_slepLslepL, BR, sLSP, sProduction):
    a = loadtxt(fn)

    slep = a[:,0]
    chi  = a[:,1]
    n_pcut  = array(a[:,2],int)
    n_matching = array(a[:,3],int)
    n_total = array(a[:,4],int)
    sigma_mad = a[:,5]

    #scale = []


    scale = []
    i = 0
    for t,b in zip(sigma_calchep, sigma_slepLslepL):
        scale0 = t/b
        x = slep[i]
        while(x == slep[i]):
            scale.append(scale0)
            i = i+1
            if (i == len(slep)):
                break

            

    
    #for t,b in zip(sigma_calchep, sigma_slepLslepL):
    #    scale.append(t/b)

    #scale = array(scale)

    sigma = scale * sigma_mad * BR
    
    fn_out = sLSP + '_' + sProduction + '.dat'

    f = open(fn_out, 'w')

    for i in range(len(slep)):
        s = str([slep[i], chi[i], n_pcut[i], n_matching[i], n_total[i], sigma[i]])
        s = s.replace(',' , '')
        s = s.replace('[' , '')
        s = s.replace(']', '')
        f.write(s+'\n')
    f.close()


fn = "sorted_binoLSP_ATLAS_table.dat"

calchep_slepRslepR = loadtxt('/home/eckel/Dropbox/mySlepton/calchepData/slepRslepR_7TeV.dat',skiprows=3)
sigma_slepRslepR = calchep_slepRslepR[:,1]

calchep_snusnu = loadtxt('/home/eckel/Dropbox/mySlepton/calchepData/snusnu_7TeV.dat',skiprows=3)
sigma_snusnu = calchep_snusnu[:,1]

calchep_slepsnu = loadtxt('/home/eckel/Dropbox/mySlepton/calchepData/slepLsnu_7TeV.dat',skiprows=3)
sigma_slepsnu = calchep_slepsnu[:,1]
sigma_slepsnu = 2*sigma_slepsnu # combinatoric factor

calchep_slepLslepL = loadtxt('/home/eckel/Dropbox/mySlepton/calchepData/slepLslepL_7TeV.dat',skiprows=3)
sigma_slepLslepL = calchep_slepLslepL[:,1]

sigmalist = [sigma_slepLslepL, sigma_slepsnu, sigma_snusnu, sigma_slepRslepR];
productionlist = ['slepLslepL', 'slepsnu', 'snusnu', 'slepRslepR'];


#Bino
BRlist = [1, 0, 0, 1]

for i in range(4):
    sigma_calchep = sigmalist[i];
    BR = BRlist[i];
    ss = productionlist[i];
    lumiplot(fn, sigma_calchep, sigma_slepLslepL, BR, 'Bino_LSP', ss);

#Wino
slepLBR = 3.33609348E-01;
snuBR   = 6.66943178E-01;

BRlist = [slepLBR*slepLBR, slepLBR*snuBR, snuBR*snuBR, 1];

for i in range(4):
    sigma_calchep = sigmalist[i];
    BR = BRlist[i];
    ss = productionlist[i];
    lumiplot(fn, sigma_calchep, sigma_slepLslepL, BR, 'Wino_LSP', ss);

#Higgsino
slepLBR = 5.33983615E-01 + 2.97214985E-01;
snuBR   = 6.91125420E-01;

BRlist = [slepLBR*slepLBR, slepLBR*snuBR, snuBR*snuBR, 1];

for i in range(4):
    sigma_calchep = sigmalist[i];
    BR = BRlist[i];
    ss = productionlist[i];
    lumiplot(fn, sigma_calchep, sigma_slepLslepL, BR, 'Higgsino_LSP', ss);
