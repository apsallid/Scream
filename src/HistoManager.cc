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
/// \file analysis/AnaEx01/src/HistoManager.cc
/// \brief Implementation of the HistoManager class
//
//
// $Id: HistoManager.cc 74272 2013-10-02 14:48:50Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//#include "OutfileManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
{
  fFileName[0] = "Scream";
  fFactoryOn = false;
  
  // histograms
  for (G4int k=0; k<MaxHisto; k++) {
    fHistId[k] = 0;
    fHistPt[k] = 0;    
 /*}
  // ntuple
  for (G4int k=0; k<MaxNtCol; k++) {
    fNtColId[k] = 0;
  }*/  
}
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(2);
  G4String extension = analysisManager->GetFileType();
  fFileName[1] = fFileName[0] + "." + extension;
      
  // Create directories 
  analysisManager->SetHistoDirectoryName("histo");
  //analysisManager->SetNtupleDirectoryName("ntuple");
    
  // Open an output file
  //
  G4bool fileOpen = analysisManager->OpenFile(fFileName[0]);
  if (!fileOpen) {
    G4cout << "\n---> HistoManager::book(): cannot open " << fFileName[1] 
           << G4endl;
    return;
  }
  
  // create selected histograms
  //
  analysisManager->SetFirstHistoId(1);
  //analysisManager->SetFirstNtupleId(1);

  // fHistId[1] = analysisManager->CreateH1("1","Edep in absorber (MeV)",
  //                                             1000, 0., 50*GeV);
  // fHistPt[1] = analysisManager->GetH1(fHistId[1]);
                                           
  // fHistId[2] = analysisManager->CreateH1("2","Edep in Detector1 (MeV)",
  //                                             1000, 0., 150*keV);
  // fHistPt[2] = analysisManager->GetH1(fHistId[2]);
  
 // fHistId[3] = analysisManager->CreateH1("3","Edep in Detector1 (MeV)",
  //                                            1000, 0., 150*keV);
 // fHistPt[3] = analysisManager->GetH1(fHistId[3]);
                                           
  fHistId[1] = analysisManager->CreateH1("1","Edep in Detector1 pad (1,5) ",
                                              1000, 0., 500*keV);
  fHistPt[1] = analysisManager->GetH1(fHistId[1]);

  fHistId[2] = analysisManager->CreateH1("2","Edep in Detector1 pad (2,5)",
                                              1000, 0., 500*keV);
  fHistPt[2] = analysisManager->GetH1(fHistId[2]);

  fHistId[3] = analysisManager->CreateH1("3","Edep in Detector1 pad (3,5) ",
                                              1000, 0., 500*keV);
  fHistPt[3] = analysisManager->GetH1(fHistId[3]);

  fHistId[4] = analysisManager->CreateH1("4","Edep in Detector1 pad (4,5) ",
                                              1000, 0., 500*keV);
  fHistPt[4] = analysisManager->GetH1(fHistId[4]);

  fHistId[5] = analysisManager->CreateH1("5","Edep in Detector1 pad (5,5) ",
                                              1000, 0., 500*keV);
  fHistPt[5] = analysisManager->GetH1(fHistId[5]);

  fHistId[6] = analysisManager->CreateH1("6","Edep in chamber1",
                                              100000, 0., 50*MeV);
  fHistPt[6] = analysisManager->GetH1(fHistId[6]);

  fHistId[7] = analysisManager->CreateH1("7","Edep in chamber2",
                                              100000, 0., 50*MeV);
  fHistPt[7] = analysisManager->GetH1(fHistId[7]);

  fHistId[8] = analysisManager->CreateH1("8","Edep in chamber3",
                                              100000, 0., 50*MeV);
  fHistPt[8] = analysisManager->GetH1(fHistId[8]);

  fHistId[9] = analysisManager->CreateH1("9","Edep in chamber4",
                                              100000, 0., 50*MeV);
  fHistPt[9] = analysisManager->GetH1(fHistId[9]);

  fHistId[10] = analysisManager->CreateH1("10","Edep in chamber5",
                                              100000, 0., 50*MeV);
  fHistPt[10] = analysisManager->GetH1(fHistId[10]);

  fHistId[11] = analysisManager->CreateH1("11","Edep in chamber6",
                                              100000, 0., 50*MeV);
  fHistPt[11] = analysisManager->GetH1(fHistId[11]);

  fHistId[12] = analysisManager->CreateH1("12","Edep in all chambers",
                                              100000, 0., 50*MeV);
  fHistPt[12] = analysisManager->GetH1(fHistId[12]);

  fHistId[13] = analysisManager->CreateH1("13","Smeared Edep in Detector1 pad (1,5) ",
                                              1000, 0., 500*keV);
  fHistPt[13] = analysisManager->GetH1(fHistId[13]);

  fHistId[14] = analysisManager->CreateH1("14","Smeared Edep in Detector1 pad (2,5)",
                                              1000, 0., 500*keV);
  fHistPt[14] = analysisManager->GetH1(fHistId[14]);

  fHistId[15] = analysisManager->CreateH1("15","Smeared Edep in Detector1 pad (3,5) ",
                                              1000, 0., 500*keV);
  fHistPt[15] = analysisManager->GetH1(fHistId[15]);

  fHistId[16] = analysisManager->CreateH1("16","Smeared Edep in Detector1 pad (4,5) ",
                                              1000, 0., 500*keV);
  fHistPt[16] = analysisManager->GetH1(fHistId[16]);

  fHistId[17] = analysisManager->CreateH1("17","Smeared Edep in Detector1 pad (5,5) ",
                                              1000, 0., 500*keV);
  fHistPt[17] = analysisManager->GetH1(fHistId[17]);

  fHistId[18] = analysisManager->CreateH1("18","Smeared Edep in chamber1",
                                              100000, 0., 50*MeV);
  fHistPt[18] = analysisManager->GetH1(fHistId[18]);

  fHistId[19] = analysisManager->CreateH1("19","Smeared Edep in chamber2",
                                              100000, 0., 50*MeV);
  fHistPt[19] = analysisManager->GetH1(fHistId[19]);

  fHistId[20] = analysisManager->CreateH1("20","Smeared Edep in chamber3",
                                              100000, 0., 50*MeV);
  fHistPt[20] = analysisManager->GetH1(fHistId[20]);

  fHistId[21] = analysisManager->CreateH1("21","Smeared Edep in chamber4",
                                              100000, 0., 50*MeV);
  fHistPt[21] = analysisManager->GetH1(fHistId[21]);

  fHistId[22] = analysisManager->CreateH1("22","Smeared Edep in chamber5",
                                              100000, 0., 50*MeV);
  fHistPt[22] = analysisManager->GetH1(fHistId[22]);

  fHistId[23] = analysisManager->CreateH1("23","Smeared Edep in chamber6",
                                              100000, 0., 50*MeV);
  fHistPt[23] = analysisManager->GetH1(fHistId[23]);

  fHistId[24] = analysisManager->CreateH1("24","Smeared Edep in all chambers",
                                              100000, 0., 50*MeV);
  fHistPt[24] = analysisManager->GetH1(fHistId[24]);

  fHistId[25] = analysisManager->CreateH1("25","The smear factor. It should be gaussian.",
                                              1000, -10., 10.);
  fHistPt[25] = analysisManager->GetH1(fHistId[25]);

  // Create 1st ntuple (id = 1)
  //    
 /* analysisManager->CreateNtuple("101", "Edep");
  fNtColId[0] = analysisManager->CreateNtupleDColumn("Eabs");
  fNtColId[1] = analysisManager->CreateNtupleDColumn("Egap");
  analysisManager->FinishNtuple();

  // Create 2nd ntuple (id = 2)
  //    
  analysisManager->CreateNtuple("102", "TrackL");
  fNtColId[2] = analysisManager->CreateNtupleDColumn("Labs");
  fNtColId[3] = analysisManager->CreateNtupleDColumn("Lgap");
  analysisManager->FinishNtuple();
  
  */fFactoryOn = true; /*      
  G4cout << "\n----> Histogram Tree is opened in " << fFileName[1] << G4endl;*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::save()
{
  if (fFactoryOn) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
    analysisManager->Write();
    analysisManager->CloseFile();  
   // G4cout << "\n----> Histogram Tree is saved in " << fFileName[1] << G4endl;
      
    delete G4AnalysisManager::Instance();
    fFactoryOn = false;
  }                    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillHisto(G4int ih, G4double xbin)//, G4double weight)
{
  if (ih > MaxHisto) {
    G4cout << "---> warning from HistoManager::FillHisto() : histo " << ih
           << "does note xist; xbin= " << xbin /*<< " w= " << weight */<< G4endl;
    return;
  }

  if (fHistPt[ih]) fHistPt[ih]->fill(xbin);//, weight);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*void HistoManager::Normalize(G4int ih, G4double fac)
{
  if (ih >= MaxHisto) {
    G4cout << "---> warning from HistoManager::Normalize() : histo " << ih
           << "  fac= " << fac << G4endl;
    return;
  }

  if (fHistPt[ih]) fHistPt[ih]->scale(fac);
}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*void HistoManager::FillNtuple(G4double energyAbs, G4double energyGap,
                              G4double trackLAbs, G4double trackLGap)
{                
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // Fill 1st ntuple ( id = 1)
  analysisManager->FillNtupleDColumn(1,fNtColId[0], energyAbs);
  analysisManager->FillNtupleDColumn(1,fNtColId[1], energyGap);
  analysisManager->AddNtupleRow(1);  
  // Fill 2nd ntuple ( id = 2)
  analysisManager->FillNtupleDColumn(2,fNtColId[2], trackLAbs);
  analysisManager->FillNtupleDColumn(2,fNtColId[3], trackLGap);
  analysisManager->AddNtupleRow(2);  
}  */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*void HistoManager::PrintStatistic()
{
  if(fFactoryOn) {
    G4cout << "\n ----> print histograms statistic \n" << G4endl;
    
    G4cout 
       << " EAbs : mean = " << G4BestUnit(fHistPt[1]->mean(), "Energy") 
               << " rms = " << G4BestUnit(fHistPt[1]->rms(),  "Energy") 
               << G4endl;
    G4cout                
       << " EGap : mean = " << G4BestUnit(fHistPt[2]->mean(), "Energy") 
               << " rms = " << G4BestUnit(fHistPt[2]->rms(),  "Energy") 
               << G4endl;
    G4cout 
       << " LAbs : mean = " << G4BestUnit(fHistPt[3]->mean(), "Length") 
               << " rms = " << G4BestUnit(fHistPt[3]->rms(),  "Length") 
               << G4endl;
    G4cout 
       << " LGap : mean = " << G4BestUnit(fHistPt[4]->mean(), "Length") 
               << " rms = " << G4BestUnit(fHistPt[4]->rms(),  "Length") 
               << G4endl;
  }
}*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


