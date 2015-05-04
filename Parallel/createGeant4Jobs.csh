#!/bin/tcsh

rm voodoo
rm voodoo1
rm voodoo2
rm voodoo3
rm voodoo4

setenv suddirineoslistguns "pi- mu- e-"
#energies in GeV
setenv suddirineoslistenergies "50 100 150 200" 

foreach subdirineosguns  ($suddirineoslistguns)

echo "===================================================================================="

foreach subdirineosenergies  ($suddirineoslistenergies)

echo "------------------------"
echo "${subdirineosguns} ${subdirineosenergies} GeV"

foreach num (`seq 1 100`)

set num1=`expr ${num} \* 1257 + 158725983 `

cat setupGeant4.sh > voodoo

setenv file geantoutput_${subdirineosguns}_${subdirineosenergies}GeV_${num}.root  
setenv workpath "/afs/cern.ch/work/a/apsallid/CMS/Geant4/ResolutionGeant4_SamplingCalo/Parallel/$subdirineosguns/$subdirineosenergies"

if ( $num == 1) then
rm -rf $workpath/jobs $workpath/logfiles $workpath/results
mkdir -p $workpath/jobs $workpath/logfiles $workpath/results
chmod 755 $workpath/jobs $workpath/logfiles $workpath/results
endif

sed -e "s/OUTPUT/$file/g" voodoo > voodoo1
sed -e "s/TYPEGUN/$subdirineosguns/g" voodoo1 > voodoo2
sed -e "s/TYPEENE/$subdirineosenergies/g" voodoo2 > voodoo3
sed -e "s/THESEEDNUM/${num1}/g" voodoo3 > voodoo4

mv voodoo4 $workpath/jobs/geant_${num}.job
chmod 755 $workpath/jobs/geant_${num}.job

echo geant_${num}.job

rm voodoo 
rm voodoo1
rm voodoo2
rm voodoo3

end

end

end
~

