#include "Detector.hh"

Custom_SensitiveDetector::Custom_SensitiveDetector(G4String name) : G4VSensitiveDetector(name){}
Custom_SensitiveDetector::~Custom_SensitiveDetector(){}

G4bool Custom_SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    G4Track *track = aStep->GetTrack();
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    G4cout << "Photon position: " << posPhoton << G4endl;
    return true;
}