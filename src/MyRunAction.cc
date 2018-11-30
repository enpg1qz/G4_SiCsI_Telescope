#include "MyRunAction.hh"
//#include "MyPrimaryGeneratorAction.hh"
#include "MyDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4ParameterManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <string>
#include "StringSplit.hh"
#include "ReadLine.hh"

#include "math.h"
#include <ctime>
#include <tuple>        // std::tuple, std::get, std::tie, std::ignore
#include <vector>
#include<fstream>
using namespace std;
//extern ofstream shuchu;
/*
extern G4double dEdx[2500];

extern G4double energy;

extern G4double shecheng[250];
extern G4int zongshu;
*/
extern G4int pZ;
extern G4int pA;
extern G4double pCharge;
extern G4double pexcitEnergy;
extern G4double pEnergyMax;
extern G4double pEnergyMin;

extern G4int NofEvent;
extern G4String myparticlename;
extern vector<tuple<G4double,G4double> > rundata;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyRunAction::MyRunAction()
: G4UserRunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyRunAction::~MyRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyRunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed

  fstream theFile;  //   ifstream theFile;
  string filename="./data/para.dat";
  theFile.open(filename,ios::in);
  vector<string> result;
  ///读第一行
  ReadLine(theFile,result);
  {
    pZ=stoi(result[0]);
    pA=stoi(result[1]);
    pCharge=stod(result[2])*eplus;
    pexcitEnergy=stod(result[3])*keV;
    pEnergyMin=stod(result[4])*MeV;
    pEnergyMax=stod(result[5])*MeV;
  }
  theFile.close();

  G4RunManager::GetRunManager()->SetRandomNumberStore(false);


  //shuchu.open("shuju4-26-0.txt",ios_base::app);

  rundata.clear();
  NofEvent = 0;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyRunAction::EndOfRunAction(const G4Run*)
{
  G4double Sidz;
  {
    const MyDetectorConstruction* detectorConstruction
      = static_cast<const MyDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    Sidz = detectorConstruction->get_Sidz();
  }
  time_t now = time(0);
  tm *ltm = localtime(&now);

  ofstream rundatafile;
  G4String fileName = "./data/"+myparticlename+"-"+to_string((int)round(Sidz/mm*1000))+"-E-dE-"+to_string(NofEvent)+"-"+to_string(1 + ltm->tm_mon)+"_"+to_string(ltm->tm_mday)+".txt";
  //G4String fileName = myparticlename+"-dE-E.txt";
  rundatafile.open(fileName,ios_base::app);
  ///rundatafile<<"### NofEvent:"<<NofEvent<<"  "<<"particlename:"<<myparticlename<<"  "<<"datasize: "<<rundata.size()<<endl;
  ///rundatafile<<"### pZ:"<<pZ<<"  "<<"pA:"<<pA<<"  "<<"pCharge: "<<pCharge<<endl;
  vector<tuple<G4double,G4double> >::iterator it;
  for (it = rundata.begin(); it != rundata.end(); it++){
    rundatafile << std::get<0>(*it) <<' '<< std::get<1>(*it);
    if (it == rundata.begin()){
      rundatafile<<"  ### NofEvent:"<<NofEvent<<"  "<<"particlename:"<<myparticlename<<"  "<<"datasize: "<<rundata.size()<<" ";
      rundatafile<<"  ### pZ:"<<pZ<<"  "<<"pA:"<<pA<<"  "<<"pCharge: "<<pCharge<<"Sidz: "<<Sidz/mm;
    }
    rundatafile << endl;
  }
  rundatafile.close();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
