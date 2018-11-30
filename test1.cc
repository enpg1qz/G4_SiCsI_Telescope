
#include "MyDetectorConstruction.hh"
#include "MyActionInitialization.hh"
//#include "QBBC.hh"
//#include "B3PhysicsList.hh"
#include "QGSP_BIC.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"
#include "G4SystemOfUnits.hh"

#include <tuple>        // std::tuple, std::get, std::tie, std::ignore
#include <vector>
#include <fstream>
using namespace std;



G4int NofEvent = 0;
G4int pZ ;
G4int pA ;
G4double pCharge  ; //*eplus
G4double pexcitEnergy ;  //*keV
G4double pEnergyMax; //*MeV
G4double pEnergyMin; //*MeV

vector<tuple<G4double,G4double>> rundata;
G4String myparticlename;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //


  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = time( NULL );
  G4Random::setTheSeed( seed );

  // Construct the default run manager
  //
///#ifdef G4MULTITHREADED
///  G4MTRunManager* runManager = new G4MTRunManager;
///#else
  G4RunManager* runManager = new G4RunManager;
///#endif

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new MyDetectorConstruction());

  // Physics list
  G4VModularPhysicsList* physicsList = new QGSP_BIC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
//////////////////////////////////
//////  runManager->SetUserInitialization(new B3PhysicsList());
///////////////////////////////////

  // User action initialization
  runManager->SetUserInitialization(new MyActionInitialization());

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
