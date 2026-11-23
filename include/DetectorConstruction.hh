// ifndef stand for "if not defined", used to check if the header file has already been included in the script.cc.
// If it has not been included, the code between #ifndef and #endif will be executed.
// This prevents multiple inclusions of the same header file, which can lead to compilation errors.

#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh

// Inlcude the libraries used in the DetectorConstruction.cc file, still protected by the #ifndef
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VUserDetectorConstruction.hh"

// class G4VPhysicalVolume;

// ': public' stands for inheritance in C++.
// It means that the DetectorConstruction class is inheriting from the G4VUserDetectorConstruction class.
class DetectorConstruction : public G4VUserDetectorConstruction {

    // Public access specifier, meaning that if you use this class you can access the Constructor and Destructor methods
    // and the Construct() method.
    public:
        // In C++ there's no garbage collector, so we have to manually manage memory allocation and deallocation through constructors and destructors.
        DetectorConstruction();   // constructor for the DetectorConstruction class, same as __init__ in Python
        ~DetectorConstruction();  // destructor for the DetectorConstruction class, same as __del__ in Python
        
        // Virtual function that constructs the detector geometry and returns a pointer to the physical volume.
        // The 'virtual' keyword indicates that this function can be overridden in derived classes.
        // It is actually a pure virtual function in the base class G4VUserDetectorConstruction
        // which means that it is not necessary to write 'virtual' in the derived class, but it is a good practice to do so.
        virtual G4VPhysicalVolume *Construct();
};

# endif  //Close the #ifndef statement