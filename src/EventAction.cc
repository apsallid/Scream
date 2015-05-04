//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file analysis/shared/src/EventAction.cc
/// \brief Implementation of the EventAction class
//
//
// $Id: EventAction.cc 68015 2013-03-13 13:27:27Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"
//#include "OutfileManager.hh"
#include "RunAction.hh"
#include "HistoManager.hh"
//#include <fstream>
#include "G4Event.hh"
#include "TRandom3.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



EventAction::EventAction(RunAction* run, HistoManager* histo)//, OutfileManager* out)
:G4UserEventAction(),
 fRunAct(run),fHistoManager(histo),//,fOutfileManager(out),
 fEnergyAbs(0.),//, fEnergyGap1(0.), //fEnergyGap(0.),

  

// fTrackLAbs(0.), fTrackLGap(0.),
 fPrintModulo(0)                             
{
 fPrintModulo = 100; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void EventAction::BeginOfEventAction(const G4Event* evt)
{  
  G4int evtNb = evt->GetEventID();
  if (evtNb%fPrintModulo == 0) 
   G4cout << "\n---> Begin of event   : " << evtNb << G4endl;
 counter=evtNb+1;
 // initialisation per event
 enecha1 = 0.; enecha2 = 0.; enecha3 = 0.; enecha4 = 0.; enecha5 = 0.; enecha6 = 0.;eneinallcha = 0.;
 //if (evtNb==1){

  for(G4int k=0;k<6; k++){
  for(G4int j=0;j<10;j++){
  for(G4int i=0;i<10;i++){

 fEnergyAbs =0.; fEnergyGap[k][i][j]=0.; AdcVals[k][i][j]=0;//.; fEnergyGap1 =0.;
 //fTrackLAbs = fTrackLGap = 0.;
}
}
}

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//std::ofstream outfile("/home/Kalamaris/geant4/Test-build");

void EventAction::EndOfEventAction(const G4Event* evt)
{
  //accumulates statistic
  G4int evtNb = evt->GetEventID();
  G4int  Mapping[96]={89,91,93,95,49,51,53,55,
                      70,72,74,76,78,80,81,83,85,87,
                      77,84,79,82,42,44,46,48,66,68,
                      67,94,69,92,71,90,73,88,75,86,
                      41,56,43,54,45,52,47,50,65,96,
                      18,15,64,33,62,35,60,37,58,39,
                      28,5,26,07,24,9,22,11,20,13,
                      14,16,34,36,38,40,32,1,30,3,
                      25,27,29,31,2,4,6,8,10,12,
                      57,59,61,63,17,19,21,23};
  

  fRunAct->fillPerEvent(fEnergyAbs, fEnergyGap[0][0][0]);//, fEnergyGap1);


  G4int padcounter=0;

  std::ofstream outfile("Run.data",std::ios::out);
  
  //Loop over 6 chamber and the 10x10 pads
  for(G4int k=0;k<6; k++){
    for(G4int j=0;j<10;j++){
      for(G4int i=0;i<10;i++){

	if( k == 0 ) {enecha1 = enecha1 + fEnergyGap[k][i][j];} // Chamber1 
	if( k == 1 ) {enecha2 = enecha2 + fEnergyGap[k][i][j];} // Chamber2
	if( k == 2 ) {enecha3 = enecha3 + fEnergyGap[k][i][j];} // Chamber3
	if( k == 3 ) {enecha4 = enecha4 + fEnergyGap[k][i][j];} // Chamber4
	if( k == 4 ) {enecha5 = enecha5 + fEnergyGap[k][i][j];} // Chamber5
	if( k == 5 ) {enecha6 = enecha6 + fEnergyGap[k][i][j];} // Chamber6

	outfile.open("Run.data", std::ofstream::out | std::ofstream::app);
	if((j==0) && (i==0) && (k==0))
	  {outfile<<"START_RUN"<<G4endl;
	    outfile<<evtNb<<G4endl;
	    outfile<<evtNb<<G4endl;
	    outfile<<"START_EVENT"<<G4endl;
	    outfile<<evtNb+1<<G4endl;
	    outfile<<evtNb+1<<G4endl;
	  }

	if ((i==0) && (j==0))  outfile<<96<<G4endl;

	AdcVals[k][i][j]=G4int((fEnergyGap[k][i][j]/0.0012)*150.+200.);


	if (AdcVals[k][i][j]>1023) {ovf=true;AdcVals[k][i][j]=1023;ovfcounter++;}
	else {ovf=false;}
  
	if (  ! (((i==0) && (j==0)) || ((i==0) && (j==9)) || ((i==9) && (j==0)) || ((i==9) && (j==9)) )   )
	  { //if (AdcVals[k][i][j]>200) AdcVals[k][i][j]=200;
	    //   G4cout<<"EnergyGap ["<<k<<","<<i<<","<<j<<"]="<<fEnergyGap[k][i][j]<<G4endl;
	    //G4cout<<"Adc Value ["<<k<<","<<i<<","<<j<<"]="<<AdcVals[k][i][j]<<G4endl;
	    //G4cout<<"ASCII FORMAT OUTPUT "<<(10000000*1 + 1000000*G4int(ovf) + 10000*padcounter + AdcVals[k][i][j])<<G4endl;
 
 
	    //if (AdcVals[k][i][j]<0) AdcVals[k][i][j]=AdcVals[k][i][j]+2147483848;
	    //outfile.width(8);
	    outfile/*<<"Adc Value ["<<k<<","<<i<<","<<j<<"]="*/<<(10000000*1 + 1000000*G4int(ovf) + 10000*(Mapping[padcounter]-1) + AdcVals[k][i][j])<<G4endl;



 
	    padcounter++;   
 
	    if (padcounter>95) padcounter=0;
 
	    //---------------------------------------------------------vals1----------------------------------------
	    //AdcVals1[i][j]=G4int((fEnergyGap1[i][j]/0.0012)*150.+200.);




	  }
  
	outfile.close();

	//fill histograms
	// fHistoManager->FillHisto(1, fEnergyAbs);
	// fHistoManager->FillHisto(2, fEnergyGap);

      } // end of loop over pad i
    } // end of loop over pad j
  }  // end of loop over chambers k
  //fEnergyGap[k][i][j]
  fHistoManager->FillHisto(1, fEnergyGap[0][0][4]);//First Detector pad (1,5) 
  fHistoManager->FillHisto(2, fEnergyGap[0][1][4]);//First Detector pad (2,5)
  fHistoManager->FillHisto(3, fEnergyGap[0][2][4]);//First Detector pad (3,5)
  fHistoManager->FillHisto(4, fEnergyGap[0][3][4]);//First Detector pad (4,5)
  fHistoManager->FillHisto(5, fEnergyGap[0][4][4]);//First Detector pad (5,5)
  fHistoManager->FillHisto(6, enecha1);//Energy in chamber1
  fHistoManager->FillHisto(7, enecha2);//Energy in chamber2
  fHistoManager->FillHisto(8, enecha3);//Energy in chamber3
  fHistoManager->FillHisto(9, enecha4);//Energy in chamber4
  fHistoManager->FillHisto(10, enecha5);//Energy in chamber5
  fHistoManager->FillHisto(11, enecha6);//Energy in chamber6
  eneinallcha = enecha1 + enecha2 + enecha3 + enecha4 + enecha5 + enecha6;//Energy in all chamber
  fHistoManager->FillHisto(12, eneinallcha);//Energy in all chamber

  //Smearing
  TRandom3 lrndm;
  //If the seed is zero the seed is set to a random value
  lrndm.SetSeed(0);
  //Smear factors for each chamber
  G4double smearfactor[chambers];
  for (int sm = 0; sm < 6; ++sm){
    smearfactor[sm]=0.;
    smearfactor[sm] = lrndm.Gaus( 1., 0.13 ); // This should be fixed to the right sigma for each chamber
  }
  //Smeared distributions
  fHistoManager->FillHisto(13, fEnergyGap[0][0][4] * smearfactor[0]);//First Detector pad (1,5) 
  fHistoManager->FillHisto(14, fEnergyGap[0][1][4] * smearfactor[0]);//First Detector pad (2,5)
  fHistoManager->FillHisto(15, fEnergyGap[0][2][4] * smearfactor[0]);//First Detector pad (3,5)
  fHistoManager->FillHisto(16, fEnergyGap[0][3][4] * smearfactor[0]);//First Detector pad (4,5)
  fHistoManager->FillHisto(17, fEnergyGap[0][4][4] * smearfactor[0]);//First Detector pad (5,5)
  fHistoManager->FillHisto(18, (enecha1 * smearfactor[0]) );//Energy in chamber1
  fHistoManager->FillHisto(19, (enecha2 * smearfactor[1]) );//Energy in chamber2
  fHistoManager->FillHisto(20, (enecha3 * smearfactor[2]) );//Energy in chamber3
  fHistoManager->FillHisto(21, (enecha4 * smearfactor[3]) );//Energy in chamber4
  fHistoManager->FillHisto(22, (enecha5 * smearfactor[4]) );//Energy in chamber5
  fHistoManager->FillHisto(23, (enecha6 * smearfactor[5]) );//Energy in chamber6
  eneinallcha = (enecha1 * smearfactor[0]) + (enecha2 * smearfactor[1]) + (enecha3 * smearfactor[2]) + (enecha4 * smearfactor[3]) + (enecha5 * smearfactor[4]) + (enecha6 * smearfactor[5]);//Energy in all chamber
  fHistoManager->FillHisto(24, eneinallcha);//Energy in all chamber
  fHistoManager->FillHisto(25, smearfactor[0]);//Testing the smear factor only for the 1st chamber. This should be gaussian.


  //G4cout<< "First Detector pad (1,5) " << fEnergyGap[0][0][4] <<G4endl;
  //G4cout<< "First Detector pad (2,5) " << fEnergyGap[0][1][4] <<G4endl;

  //G4cout<<"Padcounter  "<<padcounter<<G4endl;
  //G4cout<<"End of event # "<<counter<<G4endl;
}

  /* for(G4int j=0;j<10;j++){
  for(G4int i=0;i<10;i++){

  if (AdcVals[i][j]=1023) {ovfcounter++;}

}


}
}
  G4cout<<"Overflow # per event "<<ovfcounter<<G4endl;
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
