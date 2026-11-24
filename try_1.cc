// iostream is a standard library in C++ that provides input and output stream functionality.
#include <iostream>

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"   // GEANT4 commands manager
#include "G4VisExecutive.hh"// Visualization manager
#include "G4UIExecutive.hh" // User interface manager
#include "FTFP_BERT.hh"     // Physics list for the simulation

// Written by me
#include "DetectorConstruction.hh"
#include "physics.hh"

// The main function is the entry point of the program. It is where the execution of the program begins.
// The main function takes two parameters: argc (argument count) and argv (argument vector).
int main(int argc, char** argv) {

    // runMananger is a pointer to the G4RunManager class, which is responsible for managing the simulation run.
    G4RunManager *runManager = new G4RunManager();

    // Set the initialization of the physical world, which is defined in the DetectorConstruction class.
    // The DetectorConstruction method is declared in the DetectorConstruction.hh file and defined in the DetectorConstruction.cc file.
    runManager->SetUserInitialization(new DetectorConstruction());
    // Set the initialization of the physics list, which is defined in the Custom_PhysicsList class.
    runManager->SetUserInitialization(new Custom_PhysicsList());
    // GEANT4 check if everything necessary is initialized and run the simulation.
    runManager->Initialize();

    // Set the initialization of the User Interface (UI) and Visualization (Vis) managers.
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/drawVolume");
    // Set the viewpoint vector for the visualization. Not particularly useful but fun.
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 0 0 0");
    ui->SessionStart();
    
    return 0;
}