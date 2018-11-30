#include "MyPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4PhysicalConstants.hh"

//extern G4double energy; //dai danwei
extern G4String myparticlename;
extern G4int pZ;
extern G4int pA;
extern G4double pCharge;
extern G4double pexcitEnergy;
extern G4double pEnergyMax;
extern G4double pEnergyMin;



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
                    = particleTable->FindParticle("chargedgeantino");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  fParticleGun->SetParticleEnergy(250*MeV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  /*
  G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
  if (particle == G4ChargedGeantino::ChargedGeantino()) {
    ///////
    //C12
    G4int Z = 1, A = 1;
    G4double ionCharge   = 1.*eplus;
    G4double excitEnergy = 0.*keV;
    ///////
    G4ParticleDefinition* ion
       = G4IonTable::GetIonTable()->GetIon(pZ,pA,pexcitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(pCharge);
  }
  */

  G4ParticleDefinition* ion
     = G4IonTable::GetIonTable()->GetIon(pZ,pA,pexcitEnergy);
  fParticleGun->SetParticleDefinition(ion);
  fParticleGun->SetParticleCharge(pCharge);

  G4double x0 = 0.*mm; //1.*mm * (G4UniformRand()-0.5);
  G4double y0 = 0.*mm; //1.*mm * (G4UniformRand()-0.5);
  G4double z0 = 0.*mm;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  fParticleGun->SetParticleEnergy((pEnergyMin+G4UniformRand()*(pEnergyMax-pEnergyMin))*MeV);

  //cosAlpha uniform in [cos(0), cos(myAlphaMax)]
  G4double myAlphaMax = 0.3*rad;
  G4double cosAlpha = 1. - G4UniformRand()*(1.- std::cos(myAlphaMax));
  G4double sinAlpha = std::sqrt(1. - cosAlpha*cosAlpha);
  G4double psi      = 2*pi*G4UniformRand();  //psi uniform in [0, 2*pi]
  G4ThreeVector dir(sinAlpha*std::cos(psi),sinAlpha*std::sin(psi),cosAlpha);
  fParticleGun->SetParticleMomentumDirection(dir);

  myparticlename = fParticleGun->GetParticleDefinition()->GetParticleName();

  //create vertex
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
