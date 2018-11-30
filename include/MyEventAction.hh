
#ifndef MyEventAction_h
#define MyEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class MyRunAction;

/// Event action class
///

class MyEventAction : public G4UserEventAction
{
  public:
    MyEventAction(MyRunAction* runAction);
    virtual ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddeventdE(G4double x);
    void AddeventE(G4double x);


  private:
    MyRunAction* fRunAction;
    G4double eventE,eventdE;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
