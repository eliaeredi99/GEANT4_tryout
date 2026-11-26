#include "ActionInitialization.hh"
#include "run.hh"

Custom_ActionInitialization::Custom_ActionInitialization(){};
Custom_ActionInitialization::~Custom_ActionInitialization(){};

void Custom_ActionInitialization::Build() const{
    Custom_PrimaryGeneratorAction *generator = new Custom_PrimaryGeneratorAction();
    SetUserAction(generator);

    Custom_RunAction *runAction = new Custom_RunAction();
    SetUserAction(runAction);
};