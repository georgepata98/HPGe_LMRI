#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"

#include <iostream>
#include <fstream>

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    ~MyRunAction() override;

    virtual void BeginOfRunAction(const G4Run *run) override;
    virtual void EndOfRunAction(const G4Run *run) override;

    // Functiile AddEdepk depind de variabilele edepk si se comporta dupa formula totalEdepk, k=1,2

    //void AddEdep1(G4double edep1) { totalEdep1 += edep1; }
    //void AddEdep2(G4double edep2) { totalEdep2 += edep2; }
    void AddEdep(G4double edep) { totalEdep += edep; }

    std::ofstream* GetOutputFile();

private:
    // Cate un vector G4double pentru cristalul conic, respectiv cilindric

    //G4Accumulable<G4double> totalEdep1 = 0;
    //G4Accumulable<G4double> totalEdep2 = 0;
    G4Accumulable<G4double> totalEdep = 0;

    std::ofstream fOutputFile;

    // Numar bini si capetele histogramei, e1 = floor(1.1 * E_gamma)

    G4int nbins, e0 = 0, e1 = 25;
};

#endif