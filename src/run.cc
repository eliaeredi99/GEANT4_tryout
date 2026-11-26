#include "run.hh"

Custom_RunAction::Custom_RunAction(){}
Custom_RunAction::~Custom_RunAction(){}

void Custom_RunAction::BeginOfRunAction(const G4Run *){
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->OpenFile("output.root");

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent"); //IColumn for int values
    man->CreateNtupleDColumn("fX"); //DColumn for double values
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);
    
}
void Custom_RunAction::EndOfRunAction(const G4Run *){
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}