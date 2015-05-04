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
/// \file analysis/shared/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//
// $Id: DetectorConstruction.cc 77256 2013-11-22 10:10:23Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include "G4SDManager.hh"
//#include "G4VSensitiveDetector.hh"
//#include "SDGap.hh"
#include "G4PVReplica.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),



 fAbsorberMaterial(0),fGapMaterial(0),fDefaultMaterial(0),
 fSolidWorld(0),fLogicWorld(0),fPhysiWorld(0),
 fSolidCalor(0),fLogicCalor(0),fPhysiCalor(0),
 //fSolidLayer(0),fLogicLayer(0),fPhysiLayer(0),
 fSolidAbsorber(0),fLogicAbsorber(0),fPhysiAbsorber(0),
 //fSolidGap(0), 
fLogicGap(0), fLogicGap1(0), fLogicGap2(0),

 
//fPhysiGap[5][5]=0,

//fPhysiGap(0),
 //fSolidPads(0), fLogicPads(0), fPhysiPads(0), 
 

 fDetectorMessenger(0)

//}
//}
{
  // default parameter values of the calorimeter
  fAbsorberThickness = 27.*cm;
  fGapThickness      = 5.*mm;
  fEnvThickness      = 5.*cm;
  fCalorSizeYZ       = 10.*cm;
  
  
  // materials
  DefineMaterials();
  SetAbsorberMaterial("G4_Fe");
  SetGapMaterial("G4_Ar");
  
  // create commands for interactive definition of the calorimeter
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructCalorimeter();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
// use G4-NIST materials data base
//
G4NistManager* man = G4NistManager::Instance();
fDefaultMaterial = man->FindOrBuildMaterial("G4_AIR");
man->FindOrBuildMaterial("G4_Fe");
man->FindOrBuildMaterial("G4_Ar");

// print table
//
G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructCalorimeter()
{
G4double posx,posy,posz;
  // Clean old geometry, if any
  //
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // complete the Calor parameters definition
  ComputeCalorParameters();
   
  //     
  // World
  //
  fSolidWorld = new G4Box("World",                                //its name
                   fWorldSizeX/2,fWorldSizeYZ/2,fWorldSizeYZ/2);  //its size
                         
  fLogicWorld = new G4LogicalVolume(fSolidWorld,            //its solid
                                   fDefaultMaterial,        //its material
                                   "World");                //its name
                                   
  fPhysiWorld = new G4PVPlacement(0,                        //no rotation
                                 G4ThreeVector(),           //at (0,0,0)
                                 fLogicWorld,             //its logical volume
                                 "World",                   //its name
                                 0,                         //its mother  volume
                                 false,                  //no boolean operation
                                 0);                        //copy number
  
  //                               
  // Calorimeter
  //  
  fSolidCalor=0; fLogicCalor=0; fPhysiCalor=0;
 // fSolidLayer=0; fLogicLayer=0; fPhysiLayer=0;
  
  if (fCalorThickness > 0.)  
    { fSolidCalor = new G4Box("Calorimeter",                //its name
                    4*fCalorThickness/2,4*fCalorSizeYZ,4*fCalorSizeYZ);//size
                                 
      fLogicCalor = new G4LogicalVolume(fSolidCalor,        //its solid
                                        fDefaultMaterial,   //its material
                                        "Calorimeter");     //its name
                                           
      fPhysiCalor = new G4PVPlacement(0,                    //no rotation
                                     G4ThreeVector(),       //at (0,0,0)
                                     fLogicCalor,           //its logical volume
                                     "Calorimeter",         //its name
                                     fLogicWorld,           //its mother  volume
                                     false,              //no boolean operation
                                     0);                    //copy number
  
   }
  //                               
  // Absorber
  //
  fSolidAbsorber=0; fLogicAbsorber=0; fPhysiAbsorber=0;  
  
  if (fAbsorberThickness > 0.) 
    { fSolidAbsorber = new G4Box("Absorber",                //its name
                          fAbsorberThickness/2,fCalorSizeYZ/2,fCalorSizeYZ/2); 
                          
      fLogicAbsorber = new G4LogicalVolume(fSolidAbsorber,    //its solid
                                            fAbsorberMaterial, //its material
                                            fAbsorberMaterial->GetName());//name
                                                
      fPhysiAbsorber = new G4PVPlacement(0,                   //no rotation
                          G4ThreeVector(-3*fEnvThickness,0.,0.),  //its position
                                        fLogicAbsorber,     //its logical volume
                                        fAbsorberMaterial->GetName(), //its name
                                        fLogicCalor,          //its mother
                                        false,               //no boulean operat
                                        0);                   //copy number
                                        
    }
  
  //                                 
  // Gap
  //
  //fSolidGap=0;
 fLogicGap=0; //fPhysiGap[10][10]=0; 





  
  if (fGapThickness > 0.)
    {
                
             for(G4int j=0;j<10;j++){
             for(G4int i=0;i<10;i++)
  {
       

       fSolidGap[i][j] = new G4Box("Gap",
                               fGapThickness/2,fCalorSizeYZ/20,fCalorSizeYZ/20);
                               
       fLogicGap = new G4LogicalVolume(fSolidGap[i][j],
                                           fGapMaterial,
                                           fGapMaterial->GetName());
   
     
  //              for(G4int i=0;i<6;i++)
  
        posx=fGapThickness;//+i*(fGapThickness+fEnvThickness);

 posy=-45+j*10;
 posz=-45+i*10;

      fPhysiGap[i][j]= new G4PVPlacement(0,                  //no rotation
                                     G4ThreeVector(0.,posy,posz),       //at (0,0,0)
                                     fLogicGap,           //its logical volume
                                     "Gap",               //its name
                                     fLogicCalor,           //its mother  volume
                                     false,               //no boolean operation
                                     i);                    //copy number 



    
  PrintCalorParameters();     
  
  //                                        
  // Visualization attributes
  //
  fLogicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  fLogicCalor->SetVisAttributes(G4VisAttributes::Invisible);
   
  G4VisAttributes* magenta=new G4VisAttributes(true,G4Colour(1.,0.,1.));
  G4VisAttributes* yellow=new G4VisAttributes(true,G4Colour(1.,1.,0.));
  fLogicGap->SetVisAttributes(magenta);
 
  fLogicAbsorber->SetVisAttributes(yellow);



  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(false);
  fLogicCalor->SetVisAttributes(simpleBoxVisAtt);
}
}
//---------------------------------------------Gap1--------------------------------------------------------
             for(G4int j=0;j<10;j++){
             for(G4int i=0;i<10;i++)
  {
       

       fSolidGap1[i][j] = new G4Box("Gap",
                               fGapThickness/2,fCalorSizeYZ/20,fCalorSizeYZ/20);
                               
       fLogicGap1 = new G4LogicalVolume(fSolidGap1[i][j],
                                           fGapMaterial,
                                           fGapMaterial->GetName());
   
     
  //              for(G4int i=0;i<6;i++)
  
        posx=fGapThickness;//+i*(fGapThickness+fEnvThickness);

 posy=-45+j*10;
 posz=-45+i*10;

      fPhysiGap1[i][j]= new G4PVPlacement(0,                  //no rotation
                                     G4ThreeVector(posx+(fGapThickness+fEnvThickness),posy,posz),       //at (0,0,0)
                                     fLogicGap1,           //its logical volume
                                     "Gap",               //its name
                                     fLogicCalor,           //its mother  volume
                                     false,               //no boolean operation
                                     i);                    //copy number 



    
  PrintCalorParameters();     
  
  //                                        
  // Visualization attributes
  //
  fLogicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  fLogicCalor->SetVisAttributes(G4VisAttributes::Invisible);
   
  G4VisAttributes* magenta=new G4VisAttributes(true,G4Colour(1.,0.,1.));
  G4VisAttributes* yellow=new G4VisAttributes(true,G4Colour(1.,1.,0.));
  fLogicGap1->SetVisAttributes(magenta);
 
  fLogicAbsorber->SetVisAttributes(yellow);



  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(false);
  fLogicCalor->SetVisAttributes(simpleBoxVisAtt);
}
}

//--------------------------------------------Gap2--------------------------------------------------------   
     for(G4int j=0;j<10;j++){
     for(G4int i=0;i<10;i++)
  {
       

       fSolidGap2[i][j] = new G4Box("Gap",
                               fGapThickness/2,fCalorSizeYZ/20,fCalorSizeYZ/20);
                               
       fLogicGap2 = new G4LogicalVolume(fSolidGap2[i][j],
                                           fGapMaterial,
                                           fGapMaterial->GetName());
   
     
  //              for(G4int i=0;i<6;i++)
  
        posx=fGapThickness;//+i*(fGapThickness+fEnvThickness);

 posy=-45+j*10;
 posz=-45+i*10;

      fPhysiGap2[i][j]= new G4PVPlacement(0,                  //no rotation
                                     G4ThreeVector(posx+2*(fGapThickness+fEnvThickness),posy,posz),       //at (0,0,0)
                                     fLogicGap2,           //its logical volume
                                     "Gap",               //its name
                                     fLogicCalor,           //its mother  volume
                                     false,               //no boolean operation
                                     i);                    //copy number 



    
  PrintCalorParameters();     
  
  //                                        
  // Visualization attributes
  //
  fLogicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  fLogicCalor->SetVisAttributes(G4VisAttributes::Invisible);
   
  G4VisAttributes* magenta=new G4VisAttributes(true,G4Colour(1.,0.,1.));
  G4VisAttributes* yellow=new G4VisAttributes(true,G4Colour(1.,1.,0.));
  fLogicGap2->SetVisAttributes(magenta);
 
  fLogicAbsorber->SetVisAttributes(yellow);



  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(false);
  fLogicCalor->SetVisAttributes(simpleBoxVisAtt);
}
}

//------------------------------------------------Gap3------------------------------------------------------
         
            for(G4int j=0;j<10;j++){
             for(G4int i=0;i<10;i++)
  {
       

       fSolidGap3[i][j] = new G4Box("Gap",
                               fGapThickness/2,fCalorSizeYZ/20,fCalorSizeYZ/20);
                               
       fLogicGap3 = new G4LogicalVolume(fSolidGap3[i][j],
                                           fGapMaterial,
                                           fGapMaterial->GetName());
   
     
  //              for(G4int i=0;i<6;i++)
  
        posx=fGapThickness;//+i*(fGapThickness+fEnvThickness);

 posy=-45+j*10;
 posz=-45+i*10;

      fPhysiGap3[i][j]= new G4PVPlacement(0,                  //no rotation
                                     G4ThreeVector(posx+3*(fGapThickness+fEnvThickness),posy,posz),       //at (0,0,0)
                                     fLogicGap3,           //its logical volume
                                     "Gap",               //its name
                                     fLogicCalor,           //its mother  volume
                                     false,               //no boolean operation
                                     i);                    //copy number 



    
  PrintCalorParameters();     
  
  //                                        
  // Visualization attributes
  //
  fLogicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  fLogicCalor->SetVisAttributes(G4VisAttributes::Invisible);
   
  G4VisAttributes* magenta=new G4VisAttributes(true,G4Colour(1.,0.,1.));
  G4VisAttributes* yellow=new G4VisAttributes(true,G4Colour(1.,1.,0.));
  fLogicGap3->SetVisAttributes(magenta);
 
  fLogicAbsorber->SetVisAttributes(yellow);



  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(false);
  fLogicCalor->SetVisAttributes(simpleBoxVisAtt);
}
}


//-----------------------------------------------Gap4--------------------------------------------------------

                   for(G4int j=0;j<10;j++){
             for(G4int i=0;i<10;i++)
  {
       

       fSolidGap4[i][j] = new G4Box("Gap",
                               fGapThickness/2,fCalorSizeYZ/20,fCalorSizeYZ/20);
                               
       fLogicGap4 = new G4LogicalVolume(fSolidGap4[i][j],
                                           fGapMaterial,
                                           fGapMaterial->GetName());
   
     
  //              for(G4int i=0;i<6;i++)
  
        posx=fGapThickness;//+i*(fGapThickness+fEnvThickness);

 posy=-45+j*10;
 posz=-45+i*10;

      fPhysiGap4[i][j]= new G4PVPlacement(0,                  //no rotation
                                     G4ThreeVector(posx+4*(fGapThickness+fEnvThickness),posy,posz),       //at (0,0,0)
                                     fLogicGap4,           //its logical volume
                                     "Gap",               //its name
                                     fLogicCalor,           //its mother  volume
                                     false,               //no boolean operation
                                     i);                    //copy number 



    
  PrintCalorParameters();     
  
  //                                        
  // Visualization attributes
  //
  fLogicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  fLogicCalor->SetVisAttributes(G4VisAttributes::Invisible);
   
  G4VisAttributes* magenta=new G4VisAttributes(true,G4Colour(1.,0.,1.));
  G4VisAttributes* yellow=new G4VisAttributes(true,G4Colour(1.,1.,0.));
  fLogicGap4->SetVisAttributes(magenta);
 
  fLogicAbsorber->SetVisAttributes(yellow);



  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(false);
  fLogicCalor->SetVisAttributes(simpleBoxVisAtt);
}
}

//--------------------------------------------------Gap5-----------------------------------------------------
             for(G4int j=0;j<10;j++){
             for(G4int i=0;i<10;i++)
  {
       

       fSolidGap5[i][j] = new G4Box("Gap",
                               fGapThickness/2,fCalorSizeYZ/20,fCalorSizeYZ/20);
                               
       fLogicGap5 = new G4LogicalVolume(fSolidGap5[i][j],
                                           fGapMaterial,
                                           fGapMaterial->GetName());
   
     
  //              for(G4int i=0;i<6;i++)
  
        posx=fGapThickness;//+i*(fGapThickness+fEnvThickness);

 posy=-45+j*10;
 posz=-45+i*10;

      fPhysiGap5[i][j]= new G4PVPlacement(0,                  //no rotation
                                     G4ThreeVector(posx+5*(fGapThickness+fEnvThickness),posy,posz),       //at (0,0,0)
                                     fLogicGap5,           //its logical volume
                                     "Gap",               //its name
                                     fLogicCalor,           //its mother  volume
                                     false,               //no boolean operation
                                     i);                    //copy number 



    
  PrintCalorParameters();     
  
  //                                        
  // Visualization attributes
  //
  fLogicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  fLogicCalor->SetVisAttributes(G4VisAttributes::Invisible);
   
  G4VisAttributes* magenta=new G4VisAttributes(true,G4Colour(1.,0.,1.));
  G4VisAttributes* yellow=new G4VisAttributes(true,G4Colour(1.,1.,0.));
  fLogicGap5->SetVisAttributes(magenta);
 
  fLogicAbsorber->SetVisAttributes(yellow);



  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(false);
  fLogicCalor->SetVisAttributes(simpleBoxVisAtt);
}
}
      



}


  //
  //always return the physical World
  //
  return fPhysiWorld;

  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintCalorParameters()
{
 /* G4cout << "\n------------------------------------------------------------"
         << "\n---> The calorimeter is " << fEnvThickness << " layers of: [ "
         << fAbsorberThickness/mm << "mm of " << fAbsorberMaterial->GetName() 
         << " + "
         << fGapThickness/mm << "mm of " << fGapMaterial->GetName() << " ] " 
         << "\n------------------------------------------------------------\n";
*/}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorberMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial =
  G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);      
  if (pttoMaterial)
  {
      fAbsorberMaterial = pttoMaterial;
      if ( fLogicAbsorber )
      {
          fLogicAbsorber->SetMaterial(fAbsorberMaterial);
          G4RunManager::GetRunManager()->PhysicsHasBeenModified();
      }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetGapMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =  
  G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  if (pttoMaterial)
  {
      fGapMaterial = pttoMaterial;
      if ( fLogicGap )
      {
          fLogicGap->SetMaterial(fGapMaterial);
          G4RunManager::GetRunManager()->PhysicsHasBeenModified();

        //  fLogicPads->SetMaterial(fGapMaterial);
        //  G4RunManager::GetRunManager()->PhysicsHasBeenModified();


      }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorberThickness(G4double val)
{
  // change Absorber thickness and recompute the calorimeter parameters
  fAbsorberThickness = val;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetGapThickness(G4double val)
{
  // change Gap thickness and recompute the calorimeter parameters
  fGapThickness = val;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetCalorSizeYZ(G4double val)
{
  // change the transverse size and recompute the calorimeter parameters
  fCalorSizeYZ = val;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetEnvThickness(G4int val)
{
  fEnvThickness = val;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}











//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
