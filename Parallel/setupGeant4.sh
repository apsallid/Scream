#!/bin/bash

echo "The script starts now."

echo "System: "
uname -a

source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh

source /afs/cern.ch/work/a/apsallid/CMS/Geant4/setupGeant410p03.sh

export PWD=`pwd`

cp /afs/cern.ch/work/a/apsallid/CMS/Geant4/Scream/runparallel.mac .

sed -e "s/PARTICLEGUN/TYPEGUN/g" runparallel.mac > voodoo
sed -e "s/ENERGYOFGUN/TYPEENE/g" voodoo > voodoo1
sed -e "s/SEEDNUM/THESEEDNUM/g" voodoo1 > voodoo2


mv voodoo2 run.mac 

Scream run.mac

mv Scream.root OUTPUT  

cp OUTPUT /afs/cern.ch/work/a/apsallid/CMS/Geant4/ResolutionGeant4_SamplingCalo/Parallel/TYPEGUN/TYPEENE/results 

#/afs/cern.ch/project/eos/installation/cms/bin/eos.select cp $PWD/OUTPUT $EOSMAINPATH/TYPE/PandoraOutput/OUTPUT 


 
