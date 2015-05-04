#!/bin/tcsh

setenv suddirineoslistguns "pi- mu- e-"
#energies in GeV
setenv suddirineoslistenergies "50 100 150 200"

foreach subdirineosguns  ($suddirineoslistguns)

echo "===================================================================================="

foreach subdirineosenergies  ($suddirineoslistenergies)

echo "------------------------"
echo "${subdirineosguns} ${subdirineosenergies} GeV"

setenv workpath "/afs/cern.ch/work/a/apsallid/CMS/Geant4/ResolutionGeant4_SamplingCalo/Parallel/$subdirineosguns/$subdirineosenergies/jobs"

setenv runumberslist ` ls -ltr ${workpath} | grep .job |  awk '{print $9}' `

foreach run  ($runumberslist)

#echo ${run}
chmod 755 ${workpath}/${run}

echo "Sending ${run}"
bsub -q 2nd -o /tmp/junk ${workpath}/${run}

end

end 

end

