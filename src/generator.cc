#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
:G4VUserPrimaryGeneratorAction()
{
    fGPS = new G4GeneralParticleSource();
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fGPS;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    fGPS->GeneratePrimaryVertex(anEvent);
}