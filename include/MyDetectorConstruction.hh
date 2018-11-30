#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetVolumeE() const { return fVolumeE; }
    G4LogicalVolume* GetVolumedE() const { return fVolumedE; }
    G4double get_Sidz() const { return Sidz; }

  protected:
    G4LogicalVolume*  fVolumeE;
    G4LogicalVolume*  fVolumedE;
    G4double Sidz;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
