#include "PrimaryGeneratorAction.hh"

Custom_PrimaryGeneratorAction::Custom_PrimaryGeneratorAction(){
    fParticleGun = new G4ParticleGun(1);
};
Custom_PrimaryGeneratorAction::~Custom_PrimaryGeneratorAction(){
    delete fParticleGun;
};

void Custom_PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent){
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String  particleName = "e-";
    G4ParticleDefinition *particle = particleTable->FindParticle("e-");

    G4ThreeVector pos(0., 0., -0.5*m);
    G4ThreeVector mom(0., 0., 1.);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(6 *MeV);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
};