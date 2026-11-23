#include <iostream>


#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"

#include "DetectorConstruction.hh"

int main(int argc, char** argv) {

    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->Initialize();

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    ui->SessionStart();
    return 0;
}
