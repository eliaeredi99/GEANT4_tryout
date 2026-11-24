#ifndef ActionInitialization_hh
#define ActionInitialization_hh

#include "G4VUserActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

class Custom_ActionInitialization : public G4VUserActionInitialization{
    public:
        Custom_ActionInitialization();
        ~Custom_ActionInitialization();

        virtual void Build() const;
};


#endif