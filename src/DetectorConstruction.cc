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
    
    // Return the physical volume of the world
    return physWorld;

}