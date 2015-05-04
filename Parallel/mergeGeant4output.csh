#!/bin/tcsh

setenv suddirineoslistguns "pi- mu- e-"
#energies in GeV
setenv suddirineoslistenergies "50 100 150 200"

foreach subdirineosguns  ($suddirineoslistguns)

echo "===================================================================================="

foreach subdirineosenergies  ($suddirineoslistenergies)

echo "------------------------"
echo "${subdirineosguns} ${subdirineosenergies} GeV"

setenv workpath "/afs/cern.ch/work/a/apsallid/CMS/Geant4/ResolutionGeant4_SamplingCalo/Parallel/$subdirineosguns/$subdirineosenergies/results"

setenv output testcalo_${subdirineosguns}_${subdirineosenergies}.root

hadd $output ${workpath}/*.root

end 

end

