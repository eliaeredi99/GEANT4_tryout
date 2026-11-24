#include "physics.hh"

Custom_PhysicsList::Custom_PhysicsList(){
    // Add the default physics processes to the physics list
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
};

Custom_PhysicsList::~Custom_PhysicsList(){};