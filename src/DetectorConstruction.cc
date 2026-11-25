#include "DetectorConstruction.hh"
#include "Detector.hh"

// Initialize the constructor and destructor for the DetectorConstruction class
// inherited from the G4VUserDetectorConstruction class in DetectorConstruction.hh.
// Empty curly brackets indicate that the constructor and destructor do not perform any specific actions upon object creation or destruction
DetectorConstruction::DetectorConstruction(){} // Define the constructor 'DetectorConstruction' for the DetectorConstruction class
DetectorConstruction::~DetectorConstruction(){} // Define the destructor '~DetectorConstruction' for the DetectorConstruction class

G4VPhysicalVolume *DetectorConstruction::Construct() // Define the 'Construct' method for the DetectorConstruction class
{
    // Get an instance of the NIST material manager
    G4NistManager *nist = G4NistManager::Instance();

    // Introducing the diamond material, needs the ('name', density, number of elements), its components needs to present the number of 
    G4Material *Diamond = new G4Material("Diamond", 3.520 *g/cm3, 1);
    Diamond->AddElement(nist->FindOrBuildElement("C"), 1);

    G4Material *H2O = new G4Material("H2O", 1.000 *g/cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    G4Material *Tungsten = new G4Material("Tungsten", 19.3 *g/cm3, 1);
    Tungsten->AddElement(nist->FindOrBuildElement("W"), 1);
    
    G4Material *Copper = new G4Material("Cu", 8.96 *g/cm3, 1);
    Copper->AddElement(nist->FindOrBuildElement("Cu"), 1);

    // Find or build the material for the world volume (air)
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // SOLID WORLD: define shape and size of the world volume. I used G4Box to create a box-shaped world volume. 
    // Create the world volume using half-lengths, I suppose 1.3 meter height to easily fit the isocenter 
    G4Box *solidWorld = new G4Box("solidWorld", 0.25 * m, 0.25 * m, 0.65 * m);

    // LOGIC WORLD: create a logical volume by combining solid shape, material, Fields and other properties. It can be placed multiple times.
    // Create the logical volume combining the solid dimensions and material
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // PHYSICAL WORLD: Place the logical volume in the physical world defininf rotation and mother volume.
    // It requires several parameters (rotation, position, logical volume, name, mother volume ('0', this is the mother volume),
    // need boolean operator?, copy number, check overlaps (always true, slows down simulation but necessary))
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    // Water Phantom definition, physPhantom needs the definition of the logic form of the mother volume (logicWorld)
    G4Box *solidPhantom = new G4Box("water_phantom", 0.25/2 *m, 0.25/2 *m, 0.15/2 *m);
    G4LogicalVolume *logicPhantom = new G4LogicalVolume(solidPhantom, H2O, "logicPhantom");
    G4VPhysicalVolume *physPhantom = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.475 *m), logicPhantom, "physPhantom", logicWorld, false, 0, true);

    // Detector definition, physDetector needs the definition of the logic form of the mother volume (logicPhantom, GEANT4 can't handle volume overlaps. One volume needs to be completely contained to use the mother volume solution)
    G4Box *solidDetector = new G4Box("diamond_detector", 0.0025/2 *m, 0.0025/2 *m, 0.0005/2 *m);
    //G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector, Diamond, "logicDetector");
    //G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.025 *m), logicDetector, "physDetector", logicPhantom, false, 0, true); This was to define an object made of diamond, now we want sensitive volume!
    logicDetector = new G4LogicalVolume(solidDetector, Diamond, "logicDetector");
    for(G4int i=0; i<100; i++){
        for(G4int j=0; j<100; j++){
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(((i+0.5)/100-0.5)*0.0025 *m, ((j+0.5)/100-0.5)*0.0025 *m, 0.025*m), logicDetector, "physDetector", logicPhantom, false, j+i*100, true);
        }
    };


    // Collimator definition via boolean subtraction: Tungsten plate subtracted of a volume representing the hole:
    // IT IS IMPORTATN THAT THE VOLUME SUBTRACTED EXCEEDS THE BOUNDARIES OF THE FIRST OBJECT, AS A-B YIELDS EVERY POINT OF A NOT INCLUDED IN B AND GEANT4 CANNOT RESOLVES OVERLAPPING BOUNDARIES
    G4Box *solidPlate = new G4Box("collimator", 0.25/2 *m, 0.25/2 *m, 0.10/2 *m);
    G4Box *solidHole = new G4Box("hole", 0.03/2 *m, 0.03/2 *m, 0.20/2 *m);
    G4SubtractionSolid *solidCollimator = new G4SubtractionSolid("Collimator", solidPlate, solidHole);
    G4LogicalVolume *logicCollimator = new G4LogicalVolume(solidCollimator, Tungsten, "logicCollimator");
    G4VPhysicalVolume *physCollimator = new G4PVPlacement(0, G4ThreeVector(0., 0., -0.03 *m), logicCollimator, "physCollimator", logicWorld, false, 0, true);

    // Target definition, it is composed of two different cilinder of tungsten and copper that i unite in a common mother volume of air.
    // The G4Tubs class requires ("name", r_int, r_ext, half thickness, sector start angle, sector total angle)
    G4Tubs *solidTargetContainer = new G4Tubs("target_container", 0., 0.026/2 *m, ((0.001/2 + 0.002/2) + 0.001) *m, 0 *deg, 360 *deg);
    G4LogicalVolume *logicTargetContainer = new G4LogicalVolume(solidTargetContainer, H2O, "logicTargetContainer");
    G4VPhysicalVolume *physTargetContainer = new G4PVPlacement(0, G4ThreeVector(0., 0., -0.50 *m), logicTargetContainer, "physTargetContainer", logicWorld, false, 0, true); 

    G4Tubs *solidTargetW = new G4Tubs("Target_W", 0., 0.025/2 *m, 0.001/2 *m, 0 *deg, 360 *deg);
    G4LogicalVolume *logicTargetW = new G4LogicalVolume(solidTargetW, Tungsten, "logicTargetW");
    G4VPhysicalVolume *physTargetW = new G4PVPlacement(0, G4ThreeVector(0., 0., -0.0015 *m), logicTargetW, "physTargetW", logicTargetContainer, false, 0, true); 

    G4Tubs *solidTargetCu = new G4Tubs("Target_Cu", 0., 0.025/2 *m, 0.002/2 *m, 0 *deg, 360 *deg);
    G4LogicalVolume *logicTargetCu = new G4LogicalVolume(solidTargetCu, Copper, "logicTargetCu");
    G4VPhysicalVolume *physTargetCu = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.00055 *m), logicTargetCu, "physTargetCu", logicTargetContainer, false, 0, true); 


    // // GENERATATED BY CLAUDE TO COLOUR THE VOLUMES AND HELP ME UNDERSTAND EVENTUAL ERRORS IN THE TARGET DEFINITION 
    // // Container d'aria del target: wireframe grigio, per vederne i confini
    // auto *visContainer = new G4VisAttributes(G4Colour(0.7, 0.7, 0.7, 0.5));
    // visContainer->SetForceSolid(true);
    // logicTargetContainer->SetVisAttributes(visContainer);

    // // Tungsteno: blu, solido
    // auto *visW = new G4VisAttributes(G4Colour(0.1, 0.2, 0.9));
    // visW->SetForceSolid(true);
    // logicTargetW->SetVisAttributes(visW);

    // // Rame: arancione, solido
    // auto *visCu = new G4VisAttributes(G4Colour(0.9, 0.5, 0.1));
    // visCu->SetForceSolid(true);
    // logicTargetCu->SetVisAttributes(visCu);

    // // Collimatore: grigio scuro, semitrasparente
    // auto *visColl = new G4VisAttributes(G4Colour(0.3, 0.3, 0.3, 0.5));
    // visColl->SetForceSolid(true);
    // logicCollimator->SetVisAttributes(visColl);

    // // Fantoccio: azzurro trasparente
    // auto *visPhantom = new G4VisAttributes(G4Colour(0.0, 0.7, 1.0, 0.3));
    // visPhantom->SetForceSolid(true);
    // logicPhantom->SetVisAttributes(visPhantom);

    // // Detector: rosso pieno
    // auto *visDet = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    // visDet->SetForceSolid(true);
    // logicDetector->SetVisAttributes(visDet);



    // Return the physical volume of the world
    return physWorld;
}


void DetectorConstruction::ConstructSDandField(){
    Custom_SensitiveDetector *sensDet = new Custom_SensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
}