#include "run.hh"

MyRunAction::MyRunAction()
{
    G4RunManager::GetRunManager()->SetPrintProgress(0);
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    
    // Inregistrarea variabilelor G4Accumulable de tip G4double

    //accumulableManager->RegisterAccumulable(totalEdep1);
    //accumulableManager->RegisterAccumulable(totalEdep2);
    accumulableManager->RegisterAccumulable(totalEdep);

    // Histograma

    auto analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->SetVerboseLevel(1);

    /*if((e1 - e0) >= 1000) { nbins = 1000; }
    if((e1 - e0) >= 500 && (e1 - e0) < 1000) { nbins = 750; }
    if((e1 - e0) < 500) { nbins = 500; }*/
    nbins = e1 - e0;  // 1 keV/bin
    
    analysisManager->CreateH1("Edep", "Edep in Ge crystal", nbins, e0, e1);
}

MyRunAction::~MyRunAction()
{
    if(fOutputFile.is_open()) { fOutputFile.close(); }
}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();

    accumulableManager->Reset();

    G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    G4int runID = run->GetRunID();

    fOutputFile.open(("checkpoint_Run" + std::to_string(runID) + ".txt").c_str());  // nume fisier de date (corespunzator unui Run) care e incarcat dupa fiecare event de interes

    auto analysisManager = G4AnalysisManager::Instance();

    G4String fileName = ("histogram_Run" + std::to_string(runID) + ".root").c_str();
    analysisManager->OpenFile(fileName);
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();

    accumulableManager->Merge();

    if(fOutputFile.is_open()) { fOutputFile.close(); }

    G4int runID = run->GetRunID();
    G4int nOfEvents = run->GetNumberOfEvent();
    //G4double meanEdep = (totalEdep1.GetValue() + totalEdep2.GetValue()) / nOfEvents;
    G4double meanEdep = totalEdep.GetValue() / nOfEvents;

    G4cout << "\n_______ End of Run" << runID << " _______" << G4endl << "Total number of Events:\n    " << nOfEvents << G4endl << "Average energy deposited in Ge crystal:\n    " << meanEdep/keV << " [keV]" << G4endl << G4endl;

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}

std::ofstream* MyRunAction::GetOutputFile()
{
    return &fOutputFile;
}