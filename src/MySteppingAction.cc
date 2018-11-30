
#include "MySteppingAction.hh"
#include "MyEventAction.hh"
#include "MyDetectorConstruction.hh"

#include "G4Step.hh"
//#include "G4StepPoint.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include <math.h>
#include <tuple>        // std::tuple, std::get, std::tie, std::ignore
#include <vector>

#include <fstream>
using namespace std;
//extern ofstream shuchu;
/*
extern G4double dEdx[2500];
extern G4double shecheng[250];
extern G4int zongshu;
*/


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MySteppingAction::MySteppingAction(MyEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fVolumeE(0),fVolumedE(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MySteppingAction::~MySteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MySteppingAction::UserSteppingAction(const G4Step* aStep)
{
////////////////////////////////////
/*
  if (!fScoringVolume) {
    const MyDetectorConstruction* detectorConstruction
      = static_cast<const MyDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
  }


  // get volume of the current step
  G4LogicalVolume* volume
    = aStep->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
*/
//////////////////////////////////////////

/////  G4int trackid = (aStep->GetTrack()->GetTrackID()) ;
/////  if (trackid !=1) return;

  // check if we are in scoring volume
  ///////////////////////////if (volume == fScoringVolume) {

/*
    G4String particlename = (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName());
    shuchu<<particlename<<endl;
    shuchu <<'{'<< (aStep->GetPreStepPoint()->GetPosition().x()) <<','
      <<(aStep->GetPreStepPoint()->GetPosition().y())<<','
      <<(aStep->GetPreStepPoint()->GetPosition().z())<<'}'<<"mm"<<"   "
	  <<"GetTotalEnergy:"<<aStep->GetPreStepPoint()->GetTotalEnergy()<<"    "<<"GetKineticEnergy:"<<aStep->GetPreStepPoint()->GetKineticEnergy()<<"    ";
      shuchu <<'{'<< (aStep->GetPostStepPoint()->GetPosition().x()) <<','
        <<(aStep->GetPostStepPoint()->GetPosition().y())<<','
        <<(aStep->GetPostStepPoint()->GetPosition().z())<<'}'<<"mm"<<"   "
	  <<"GetTotalEnergy:"<<aStep->GetPostStepPoint()->GetTotalEnergy()<<"    "<<"GetKineticEnergy:"<<aStep->GetPostStepPoint()->GetKineticEnergy()<<"    ";
    shuchu <<(aStep->GetTrack()->GetDynamicParticle()->GetTotalEnergy()/MeV)<<"MeV"<<"    ";
    shuchu <<(aStep->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/MeV)<<"MeV"<<"    ";
    shuchu<<"GetTotalEnergyDeposit:"<<aStep->GetTotalEnergyDeposit()/MeV<<"    ";
      G4double len = (aStep->GetStepLength())/mm;
    shuchu <<"GetDeltaEnergy:"<<aStep->GetDeltaEnergy()/MeV<<"MeV"<<"    ";
    shuchu <<(aStep->GetDeltaEnergy()/MeV)/len<<"MeV/mm"<<endl;
*/
/////////////////////////////////////////////////////////////////////////////////
/*
  G4double prez = aStep->GetPreStepPoint()->GetPosition().z()/mm;
  G4double postz = aStep->GetPostStepPoint()->GetPosition().z()/mm;
/////  G4double pree = aStep->GetPreStepPoint()->GetKineticEnergy()/MeV;
/////  G4double poste = aStep->GetPostStepPoint()->GetKineticEnergy()/MeV;
  G4double len = (aStep->GetStepLength())/mm;
/////  G4double de_dx = (poste-pree)/len; // MeV/mm
  G4double deposit_de =aStep->GetTotalEnergyDeposit()/MeV;
  G4double deposit_de_dx = deposit_de/len;  */
//  for(G4int i=(G4int)(std::ceil(prez*10));i<postz*10;++i){
//    if(i>=0&&i<2500){dEdx[i]+=deposit_de_dx;  /*dEdx[i]-=de_dx;*/  /*shuchu<<i<<"  ";*/}
//  }
  /*
  G4int trackid = (aStep->GetTrack()->GetTrackID()) ;
  if (trackid !=1) return;

  G4double poste = aStep->GetPostStepPoint()->GetKineticEnergy()/MeV;
  if (poste==0){
    /////G4double postz = aStep->GetPostStepPoint()->GetPosition().z()/mm;
    G4int i = (G4int)(std::floor(postz));
    if(i>=0&&i<250) {shecheng[i]++;zongshu++;};
  }
  */
/////////////////////////////////////////////////////////////////////////////////
  if (!fVolumeE) {
    const MyDetectorConstruction* detectorConstruction
      = static_cast<const MyDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fVolumeE = detectorConstruction->GetVolumeE();
  }
  if (!fVolumedE) {
    const MyDetectorConstruction* detectorConstruction
      = static_cast<const MyDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fVolumedE = detectorConstruction->GetVolumedE();
  }


  // get volume of the current step
  G4LogicalVolume* volume
    = aStep->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  if (volume == fVolumedE || volume == fVolumeE ){
    //G4String particlename = (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName());
    // collect energy deposited in this step
    G4double edepStep = aStep->GetTotalEnergyDeposit();
    if (volume == fVolumedE) fEventAction->AddeventdE(edepStep);
    if (volume == fVolumeE) fEventAction->AddeventE(edepStep);
  }




  ///////////////////////}


    return;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
