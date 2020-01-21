#include "B1DetectorConstruction.hh"
#include "B1ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"
#include "G4GDMLParser.hh"
#include "PhysicsList.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  G4cout << G4endl;
//  G4cout << "argc=" << argc << G4endl;
  G4cout << "Usage: b1dose intput_gdml_file Sensitive_Volume <macro optional>"
         << G4endl;
  G4cout << G4endl;

  if (argc<3)
  {
     G4cout << "Error! Mandatory input file is not specified!" << G4endl;
     G4cout << G4endl;
     return -1;
  }

  G4GDMLParser parser;
  parser.Read(argv[1]);

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 3 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(4);
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  //
  // Detector construction
  B1DetectorConstruction* detector = new B1DetectorConstruction(argv[2], parser);  
  runManager->SetUserInitialization(detector);

  // Physics list
  G4VUserPhysicsList* physics = new PhysicsList();
  runManager -> SetUserInitialization(physics); 
    
  // User action initialization
  runManager->SetUserInitialization(new B1ActionInitialization());
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive("Quiet");
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[3];
    G4cout << "batch mode ApplyCommand: " << command+fileName << G4endl;
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    G4cout << "interactive mode" << G4endl;
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
