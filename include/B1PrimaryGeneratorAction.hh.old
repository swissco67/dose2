#ifndef B1PrimaryGeneratorAction_hh
#define B1PrimaryGeneratorAction_hh 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

using namespace std; 


class G4Event;
class G4GeneralParticleSource;
class B1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
B1PrimaryGeneratorAction();
~B1PrimaryGeneratorAction();

void GeneratePrimaries(G4Event* anEvent);

private:  
G4GeneralParticleSource* gun;
};
#endif
