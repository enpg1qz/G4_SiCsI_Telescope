
#include "MyEventAction.hh"
#include "MyRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"


#include <tuple>        // std::tuple, std::get, std::tie, std::ignore
#include <vector>
#include <fstream>
using namespace std;
//extern ofstream shuchu;

extern G4int NofEvent;
extern vector<tuple<G4double,G4double>> rundata;



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyEventAction::MyEventAction(MyRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),eventE(0),eventdE(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyEventAction::~MyEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyEventAction::BeginOfEventAction(const G4Event*)
{
  eventE =0;
  eventdE =0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyEventAction::EndOfEventAction(const G4Event*)
{
  NofEvent += 1;
  tuple<G4double,G4double> edata(eventE,eventdE);
  rundata.push_back(edata);
  //shuchu<<endl<<"shangmiande NofEvent:"<<NofEvent<<endl;
}

void MyEventAction::AddeventE(G4double x)
{
  eventE +=x;
}
void MyEventAction::AddeventdE(G4double x)
{
  eventdE +=x;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
