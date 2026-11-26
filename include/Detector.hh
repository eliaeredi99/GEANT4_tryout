#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

class Custom_SensitiveDetector : public G4VSensitiveDetector{
    public:
        Custom_SensitiveDetector(G4String);
        ~Custom_SensitiveDetector();
    
    private:
        virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};




#endif