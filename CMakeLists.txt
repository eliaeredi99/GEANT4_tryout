# Questo è un progetto che ho fatto come esercitazione
# L'idea è di creare una sorgente di 10 fotoni sparati in direzione di un cubo di diamante
# Non ho idea di cosa devo fare, ci sta che scriva cose sbagliate e che prenda un piega diversa da quanto presupposto
# Sotto la struttura del progetto per capire meglio la scelta dei comandi

#	g4_try_1/
#	├── CMakeLists.txt
#	├── try_1.cc              (il main)
#	├── include/
#	│   ├── DetectorConstruction.hh
#	│   ├── ActionInitialization.hh
#	│   └── PrimaryGeneratorAction.hh
#	├── src/
#	│   ├── DetectorConstruction.cc
#	│   ├── ActionInitialization.cc
#	│   └── PrimaryGeneratorAction.cc
#	├── macros/
#	│   └── run.mac
#	└── build/


# Definiamo i requisiti minimi (a caso: l'esempio di versione di CMake dato da Claude) e nome progetto
cmake_minimum_required(VERSION 3.22)
project(g4_try_1)

# Trova geant 4 e attiva interfacce grafiche, poi include le librerie presenti nel percorso Geant4_USE_FILE (è una variabile)
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# Raccoglie automaticamente tutti file sorgente e header del progetto (riconosciuti con l'estensione .cc o .hh)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Crea l'eseguibile try_1 utilizzando il sorgente try_1.cc e le componenti aggiuntive sources e headers, Definisce e collega l'eseguibile alla posizione degli headers e librerie
add_executable(try_1 try_1.cc ${sources} ${headers})
target_include_directories(try_1 PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(try_1 ${Geant4_LIBRARIES})

# Infine colleghiamo il progetto all'eseguibile
add_custom_target(g4_try_1 DEPENDS try_1)