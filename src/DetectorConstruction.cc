#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction(){} // Define the constructor 'DetectorConstruction' for the DetectorConstruction class
DetectorConstruction::~DetectorConstruction(){} // Define the destructor '~DetectorConstruction' for the DetectorConstruction class

G4VPhysicalVolume *DetectorConstruction::Construct() // Define the 'Construct' method for the DetectorConstruction class
{
    // Get an instance of the NIST material manager
    G4NistManager *nist = G4NistManager::Instance();

    // Find or build the material for the world volume (air)
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // Create the world volume using half-lengths, I suppose 1.3 meter height to easily fit the isocenter 
    G4Box *solidWorld = new G4Box("solidWorld", 0.25 * m, 0.25 * m, 0.65 * m);

    // Create the logical volume combining the solid dimensions and material
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // Place the logical volume in the physical world
    // (rotation, position, logical volume, name, mother volume (no, this is the mother volume),
    // need boolean operator?, copy number, check overlaps (always true, slows down simulation but necessary))
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    // Return the physical volume of the world
    return physWorld;

}