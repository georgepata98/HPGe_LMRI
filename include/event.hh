#ifndef EVENT_HH
#define EVENT_HH

#include "G4SystemOfUnits.hh"
#include "G4UserEventAction.hh"
#include "G4AnalysisManager.hh"
#include "G4GenericAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4THitsMap.hh"

#include "run.hh"

#include <iostream>
#include <fstream>

class MyEventAction : public G4UserEventAction
{
public: 
    MyEventAction(MyRunAction* runAction);
    ~MyEventAction() override;

    virtual void BeginOfEventAction(const G4Event *event) override;
    virtual void EndOfEventAction(const G4Event *event) override;

private:
    G4THitsMap<G4double>* GetHitsCollection(G4int hcID, const G4Event *event) const;  // HitsMap create de MultiFunctionalDetector
    G4double GetSum(G4THitsMap<G4double>* hitsMap) const;

    MyRunAction* fRunAction = nullptr;

    // HitsCollectionID pentru fiecare pereche MultiFunctionalDetector/PrimitiveScorer

    //G4int fAbsoEdepHCID1 = -1;
    //G4int fAbsoEdepHCID2 = -1;
    G4int fAbsoEdepHCID = -1;
    
    std::ofstream* fOutputFile;

    G4int aux = 0;
};

#endif