#ifndef physics_hh
#define physics_hh

#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4VModularPhysicsList.hh"

class Custom_PhysicsList : public G4VModularPhysicsList {
    public:
        Custom_PhysicsList();
        ~Custom_PhysicsList();
};



#endif