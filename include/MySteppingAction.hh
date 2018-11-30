
#ifndef MySteppingAction_h
#define MySteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class MyEventAction;

class G4LogicalVolume;

/// Stepping action class
///

class MySteppingAction : public G4UserSteppingAction
{
  public:
    MySteppingAction(MyEventAction* eventAction);
    virtual ~MySteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    MyEventAction*  fEventAction;
    G4LogicalVolume* fVolumeE;
    G4LogicalVolume* fVolumedE;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
