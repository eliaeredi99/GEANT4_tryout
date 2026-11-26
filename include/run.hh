#ifndef run_hh
#define run_hh

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"

class Custom_RunAction : public G4UserRunAction{
    public:
        Custom_RunAction();
        ~Custom_RunAction();

        virtual void BeginOfRunAction(const G4Run *);
        virtual void EndOfRunAction(const G4Run *);
};



#endif