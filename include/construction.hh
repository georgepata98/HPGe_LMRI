#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4RotationMatrix.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4VPrimitiveScorer.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"

#include <iostream>
#include <cmath>

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction() override;

public:
    G4VPhysicalVolume* Construct() override;
    virtual void ConstructSDandField() override;

private:
    G4VPhysicalVolume* DefineVolumes();
    
    G4double endCapWindowThickness, endCapWindowDiameter, detectorDiameter, detectorLength, holeDiameter, holeDepth, mountCupWallThickness, endCapToCrystalGap, endCapWallThickness, insulatorThickness, endCapWallLength, outsideContactLayerThickness, detectorEndRadius;
};

#endif