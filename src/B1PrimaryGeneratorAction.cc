#include "B1PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleDefinition.hh"
#include "G4RunManager.hh"

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  gun(0)
{
  gun = new G4GeneralParticleSource();
}

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
 delete gun;
}	

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 gun -> GeneratePrimaryVertex(anEvent);
}