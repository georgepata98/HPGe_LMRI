#include "event.hh"

MyEventAction::MyEventAction(MyRunAction *runAction)
:fRunAction(runAction)
{
    G4RunManager::GetRunManager()->SetPrintProgress(0);

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(0);

    // Apelarea lui fOutputFile creat in run.hh

    fOutputFile = runAction->GetOutputFile();
}

MyEventAction::~MyEventAction()
{}

G4THitsMap<G4double>* MyEventAction::GetHitsCollection(G4int hcID, const G4Event *event) const
{
    auto hitsCollection = static_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(hcID));

    if(!hitsCollection)
    {
        G4ExceptionDescription msg;
        msg << "Cannot access hitsCollection ID " << hcID;
        G4Exception("EventAction::GetHitsCollection()", "MyCode0003", FatalException, msg);
    }

    return hitsCollection;
}

G4double MyEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
    G4double sumValue = 0;

    for(auto it:*hitsMap->GetMap())
    { sumValue += *(it.second); }  // cantitatea inregistrata (i.e. energia depozitata) este mereu a doua valoare, prima fiind copy number

    return sumValue;
}

void MyEventAction::BeginOfEventAction(const G4Event *event)
{}

void MyEventAction::EndOfEventAction(const G4Event *event)
{
    auto analysisManager = G4AnalysisManager::Instance();

    //if(fAbsoEdepHCID1 == -1)
    //{
    //    fAbsoEdepHCID1 = G4SDManager::GetSDMpointer()->GetCollectionID("crystal1/Edep1");  // Numele string a perechii MultiFunctionalDetector/PrimitiveScorer
    //}

    //if(fAbsoEdepHCID2 == -1)
    //{
    //    fAbsoEdepHCID2 = G4SDManager::GetSDMpointer()->GetCollectionID("crystal2/Edep2");  // Numele string a perechii MultiFunctionalDetector/PrimitiveScorer
    //}

    if(fAbsoEdepHCID == -1)
    {
        fAbsoEdepHCID = G4SDManager::GetSDMpointer()->GetCollectionID("crystal/Edep");  // Numele string a perechii MultiFunctionalDetector/PrimitiveScorer
    }

    //G4double edep1 = GetSum(GetHitsCollection(fAbsoEdepHCID1, event));
    //G4double edep2 = GetSum(GetHitsCollection(fAbsoEdepHCID2, event));
    G4double edep = GetSum(GetHitsCollection(fAbsoEdepHCID, event));

    if(aux == 0)
    {
        *fOutputFile << "I. Event ID  |  II. Energy deposited in the event [keV]" << G4endl;
        aux = 1;
    }

    //if(edep1 > 0 || edep2 > 0)
    //{
    //    fRunAction->AddEdep1(edep1);
    //    fRunAction->AddEdep2(edep2);

    //    *fOutputFile << event->GetEventID() << "  " << edep1/keV + edep2/keV << G4endl;

    //    analysisManager->FillH1(0, edep1/keV + edep2/keV);
    //}

    if(edep > 0)
    {
        fRunAction->AddEdep(edep);

        *fOutputFile << event->GetEventID() << "  " << edep/keV << G4endl;

        analysisManager->FillH1(0, edep/keV);
    }
}