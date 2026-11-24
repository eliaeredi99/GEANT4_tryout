#include "DetectorConstruction.hh"

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

    G4Material *H2O = new G4Material("H20", 1.000 *g/m3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    G4Element *Tungsten = nist->FindOrBuildElement("W");

    // Find or build the material for the world volume (air)
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // SOLID WORLD: define shape and size of the world volume. I used G4Box to create a box-shaped world volume. 
    // Create the world volume using half-lengths, I suppose 1.3 meter height to easily fit the isocenter 
    G4Box *solidWorld = new G4Box("solidWorld", 0.25 * m, 0.25 * m, 0.65 * m);

    // LOGIC WORLD: create a logical volume by combining solid shape, material, Fields and other properties. It can be placed multiple times.
    // Create the logical volume combining the solid dimensions and material
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // PHYSICAL WORLD: Place the logical volume in the physical world defininf rotation and mother volume.
    // It requires several parameters (rotation, position, logical volume, name, mother volume (no, this is the mother volume),
    // need boolean operator?, copy number, check overlaps (always true, slows down simulation but necessary))
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    // Water Phantom definition, physPhantom needs the definition of the logic form of the mother volume (logicWorld)
    G4Box *solidPhantom = new G4Box("water_phantom", 0.25/2 *m, 0.25/2 *m, 0.15/2 *m);
    G4LogicalVolume *logicPhantom = new G4LogicalVolume(solidPhantom, H2O, "logicPhantom");
    G4VPhysicalVolume *physPhantom = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.475 *m), logicPhantom, "physPhantom", logicWorld, false, 0, true);

    // Detector definition, physDetector needs the definition of the logic form of the mother volume (logicPhantom, GEANT4 can't handle volume overlaps. One volume needs to be completely contained to use the mother volume solution)
    G4Box *solidDetector = new G4Box("diamond_detector", 0.0025/2 *m, 0.0025/2 *m, 0.0005/2 *m);
    G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector, Diamond, "logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.025 *m), logicDetector, "physDetector", logicPhantom, false, 0, true);



    // Return the physical volume of the world
    return physWorld;

}