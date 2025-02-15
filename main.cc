#include <iostream>
#include <ctime>
#include <climits>

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4ScoringManager.hh"

#include "Randomize.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    unsigned long long int totalEvents = 100000;
    G4bool visualization = false;  // se seteaza 'false' in simulari

    G4int visEvents = 20;  // nr. de evenimente care sa se vizualizeze cu GUI
    G4int eventsPerRun = 2000000000;
    G4int nOfRuns = totalEvents / eventsPerRun;
    G4int eventsInFinalRun = totalEvents - eventsPerRun * nOfRuns;



    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    G4ScoringManager::GetScoringManager();

    G4UIExecutive *ui = nullptr;
    if(argc == 1) { ui = new G4UIExecutive(argc, argv); }

    G4RunManager *runManager = new G4RunManager();
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    runManager->Initialize();

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();


    if(ui)
    {
        if(visualization)
        {
            UImanager->ApplyCommand("/control/execute macros/gps.mac");
            UImanager->ApplyCommand("/control/execute macros/ui.mac");
            runManager->BeamOn(visEvents);

            ui->SessionStart();  // activare GUI
        }
        if(!visualization) 
        {
            UImanager->ApplyCommand("/control/execute macros/gps.mac");
        }
        delete ui;
    }
    else
    {
        G4String command = "/control/execute macros/";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }


    if(!visualization)
    {
        for(G4int i=0; i<nOfRuns; ++i)
        {
            G4Random::setTheSeed(time(0) + i);
            runManager->BeamOn(eventsPerRun);

            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        }
        if(eventsInFinalRun > 0)
        {
            G4Random::setTheSeed(time(0) + nOfRuns);
            runManager->BeamOn(eventsInFinalRun);
        }
    }


    delete visManager;
    delete runManager;
    return 0;
}