#include "MyDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
//#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "StringSplit.hh"
#include "ReadLine.hh"
#include<fstream>
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorConstruction::MyDetectorConstruction()
: G4VUserDetectorConstruction(),
  fVolumeE(0),fVolumedE(0),Sidz(1.540*mm)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorConstruction::~MyDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{

  Sidz=1.540*mm;
  G4double CsIdz = 50*mm;
  G4double gapdz = 5*mm;
  G4double dxdy = 50*mm;

  fstream theFile;  //   ifstream theFile;
  string filename="./data/para.dat";
  theFile.open(filename,ios::in);
  vector<string> result;
  ///读第一行
  ReadLine(theFile,result);
  ReadLine(theFile,result);
  {
    Sidz=stod(result[0])*mm;
    CsIdz = stod(result[1])*mm;
    gapdz = stod(result[2])*mm;
    dxdy = stod(result[3])*mm;

  }
  theFile.close();

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;
/*
  G4double Sidz=1.540*mm;
  G4double CsIdz = 50*mm;
  G4double dxdy = 50*mm;
  G4double gapdz = 5*mm;
*/
  G4ThreeVector posSi = G4ThreeVector(0*cm, 0*cm, 5*cm);
  G4ThreeVector posCsI = posSi+G4ThreeVector(0*cm, 0*cm, gapdz+0.5*(Sidz+CsIdz));

  //
  // World
  //
  G4double world_sizeXY = 30*cm;
  G4double world_sizeZ  = 30*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* world_mat = nist->FindOrBuildMaterial("G4_Air");



  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
  //
  // Si
  //
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_Si");


  // Conical section shape
  //G4double shape1_dZ =  1.540*mm;
  //G4double shape1_dXY =  50.*mm;

  G4Box* solidShape1 =
    new G4Box("Shape1",                       //its name
    0.5*dxdy, 0.5*dxdy, 0.5*Sidz);     //its size

  G4LogicalVolume* logicShape1 =
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posSi,                    //at position
                    logicShape1,             //its logical volume
                    "Si",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4VisAttributes* VisAtt1 = new G4VisAttributes(G4Colour(1.0,0.0,0.0,1));

  logicShape1 -> SetVisAttributes(VisAtt1);
  //
  // Set Shape1 as scoring volume
  //
  fVolumedE = logicShape1;

  //////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  //
  // CsI
  //
  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");


    // Conical section shape
    //G4double shape2_dZ =  50.*mm;
    //G4double shape2_dXY =  50.*mm;

    G4Box* solidShape2 =
      new G4Box("Shape2",                       //its name
      0.5*dxdy, 0.5*dxdy, 0.5*CsIdz);     //its size

    G4LogicalVolume* logicShape2 =
      new G4LogicalVolume(solidShape2,         //its solid
                          shape2_mat,          //its material
                          "Shape2");           //its name

    new G4PVPlacement(0,                       //no rotation
                      posCsI,                    //at position
                      logicShape2,             //its logical volume
                      "CsI",                //its name
                      logicWorld,                //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking

  G4VisAttributes* VisAtt2 = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.8));

  logicShape2 -> SetVisAttributes(VisAtt2);

  fVolumeE = logicShape2;


  //
  //always return the physical World
  //
  return physWorld;
}
