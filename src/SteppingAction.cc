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
/// \file analysis/shared/src/SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
// $Id: SteppingAction.cc 68015 2013-03-13 13:27:27Z gcosmo $
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"
//#include "OutfileManager.hh"
#include "G4Step.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* det,
                                         EventAction* evt)
: G4UserSteppingAction(), 
  fDetector(det), fEventAction(evt)                                         
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // get volume of the current step
  G4VPhysicalVolume* volume 
  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // collect energy and track length step by step
  G4double edep = aStep->GetTotalEnergyDeposit();
 // G4double Earray[10][10]; 
  /*G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();*/
      
  if (volume == fDetector->GetAbsorber()) fEventAction->AddAbs(edep);
  for(G4int k=0;k<6; k++){
  for(G4int j=0;j<10;j++){
  for(G4int i=0;i<10;i++){

  

  if ((volume == fDetector->GetGap(i,j)) && (k==0)) fEventAction->AddGap(edep,k,i,j);

  if ((volume == fDetector->GetGap1(i,j)) && (k==1)) fEventAction->AddGap(edep,k,i,j);

  if ((volume == fDetector->GetGap2(i,j)) && (k==2)) fEventAction->AddGap(edep,k,i,j);
 
  if ((volume == fDetector->GetGap3(i,j)) && (k==3)) fEventAction->AddGap(edep,k,i,j);

  if ((volume == fDetector->GetGap4(i,j)) && (k==4)) fEventAction->AddGap(edep,k,i,j);

  if ((volume == fDetector->GetGap5(i,j)) && (k==5)) fEventAction->AddGap(edep,k,i,j);
 
//if (volume == fDetector->GetGap1()) fEventAction->AddGap1(edep);

  //else
}//for i
}//for j
}//for k
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
