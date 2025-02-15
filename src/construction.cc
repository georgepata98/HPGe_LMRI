#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    return DefineVolumes();
}

G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes()
{
    // _____ Compozitie detector HPGe LMRI Serial Number 47-TP22323A _____

    G4NistManager *nist = G4NistManager::Instance();

    G4Material *air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *Ge = nist->FindOrBuildMaterial("G4_Ge");
    G4Material *Al = nist->FindOrBuildMaterial("G4_Al");
    G4Material *B = nist->FindOrBuildMaterial("G4_B");
    G4Material *Li = nist->FindOrBuildMaterial("G4_Li");
    G4Material *H = nist->FindOrBuildMaterial("G4_H");
    G4Material *C = nist->FindOrBuildMaterial("G4_C");
    G4Material *O = nist->FindOrBuildMaterial("G4_O");
    G4Material *mylar = new G4Material("mylar", 1.4*g/cm3, 3);  // datele despre Mylar sunt dupa NIST
    mylar->AddMaterial(H, 4.2*perCent);
    mylar->AddMaterial(C, 62.5*perCent);
    mylar->AddMaterial(O, 33.3*perCent);
    G4Material *vacuum = new G4Material("vacuum", 1, 1.008*g/mole, 1e-25*g/cm3, kStateGas, 2.73*kelvin, 3e-18*pascal);


    G4Box *solidWorld = new G4Box("solidWorld", 20*cm, 20*cm, 20*cm);  // hx, hy, hz
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0);

    // _____ Constructia detectorului - capacul detectorului ajunge in z=0 _____

    detectorDiameter = 58.8*mm;  // se refera la cristalul de Ge
    detectorLength = 46*mm;  // se refera la cristalul de Ge
    holeDiameter = 9.3*mm;
    holeDepth = 32.7*mm;
    mountCupWallThickness = 0.76*mm;
    endCapToCrystalGap = 3.3*mm;
    endCapWallThickness = 1.3*mm;
    //insulatorThickness = 0.03*mm;
    insulatorThickness = 1.4*mm;  // Pentru a tine cont de stratul de Li de deasupra cristalului de care am uitat (ar fi fost inca un F pe foaie)
    endCapWindowThickness = 1.27*mm;
    outsideContactLayerThickness = 1.4*mm;
    detectorEndRadius = 8*mm;
    endCapWindowDiameter = detectorDiameter + 2*mountCupWallThickness + 2*(endCapToCrystalGap - insulatorThickness) + 2*endCapWallThickness;
    endCapWallLength = detectorLength + endCapToCrystalGap;

    
    // _____ Literele reprezinta notatiile din figura tehnica a diferitor suprafete _____
    
    // D ----------
    G4Tubs *solidEndCapWindow = new G4Tubs("solidEndCapWindow", 0*mm, endCapWindowDiameter/2, endCapWindowThickness/2, 0*deg, 360*deg);
    G4LogicalVolume *logicEndCapWindow = new G4LogicalVolume(solidEndCapWindow, Al, "logicEndCapWindow");
    G4VPhysicalVolume *physEndCapWindow = new G4PVPlacement(0, G4ThreeVector(0, 0, -endCapWindowThickness/2), logicEndCapWindow, "physEndCapWindow", logicWorld, false, 0, true);

    // I ----------
    G4Tubs *solidEndCapWall = new G4Tubs("solidEndCapWall", endCapWindowDiameter/2 - endCapWallThickness, endCapWindowDiameter/2, endCapWallLength/2, 0*deg, 360*deg);
    G4LogicalVolume *logicEndCapWall = new G4LogicalVolume(solidEndCapWall, Al, "logicEndCapWall");
    G4VPhysicalVolume *physEndCapWall = new G4PVPlacement(0, G4ThreeVector(0, 0, -endCapWindowThickness - endCapWallLength/2), logicEndCapWall, "physEndCapWall", logicWorld, false, 0, true);

    // VID (mother volume) ----------
    G4Tubs *solidVoid = new G4Tubs("solidVoid", 0*mm, endCapWindowDiameter/2 - endCapWallThickness, endCapWallLength/2, 0*deg, 360*deg);  // este un mother volume !!!
    G4LogicalVolume *logicVoid = new G4LogicalVolume(solidVoid, vacuum, "logicVoid");
    G4VPhysicalVolume *physVoid = new G4PVPlacement(0, G4ThreeVector(0, 0, -endCapWallLength/2), logicVoid, "physVoid", logicWorld, false, 0, true);

    // E ----------
    G4Tubs *solidInsulator = new G4Tubs("solidInsulator", 0*mm, detectorDiameter/2 + mountCupWallThickness, insulatorThickness/2, 0*deg, 360*deg);
    //G4LogicalVolume *logicInsulator = new G4LogicalVolume(solidInsulator, mylar, "logicInsulator");
    G4LogicalVolume *logicInsulator = new G4LogicalVolume(solidInsulator, Li, "logicInsulator");
    G4VPhysicalVolume *physInsulator = new G4PVPlacement(0, G4ThreeVector(0, 0, endCapWallLength/2 - endCapToCrystalGap + insulatorThickness/2), logicInsulator, "physInsulator", logicVoid, false, 0, true);

    // H ----------
    G4Tubs *solidMountCupWall = new G4Tubs("solidMountCupWall", detectorDiameter/2, detectorDiameter/2 + mountCupWallThickness, detectorLength/2, 0*deg, 360*deg);
    G4LogicalVolume *logicMountCupWall = new G4LogicalVolume(solidMountCupWall, Al, "logicMountCupWall");
    G4VPhysicalVolume *physMountCupWall = new G4PVPlacement(0, G4ThreeVector(0, 0, endCapWallLength/2 - endCapToCrystalGap - detectorLength/2), logicMountCupWall, "physMountCupWall", logicVoid, false, 0, true);

    // F ----------
    G4Cons *solidOutsideContactLayer1 = new G4Cons("solidOutsideContactLayer1", detectorDiameter/2 - outsideContactLayerThickness*sqrt(2), detectorDiameter/2, detectorDiameter/2 - detectorEndRadius - outsideContactLayerThickness*sqrt(2), detectorDiameter/2 - detectorEndRadius, detectorEndRadius/2, 0*deg, 360*deg);
    G4LogicalVolume *logicOutsideContactLayer1 = new G4LogicalVolume(solidOutsideContactLayer1, Li, "logicOutsideContactLayer1");
    G4VPhysicalVolume *physOutsideContactLayer1 = new G4PVPlacement(0, G4ThreeVector(0, 0, endCapWallLength/2 - endCapToCrystalGap - detectorEndRadius/2), logicOutsideContactLayer1, "physOutsideContactLayer1", logicVoid, false, 0, true);

    G4Tubs *solidOutsideContactLayer2 = new G4Tubs("solidOutsideContactLayer2", detectorDiameter/2 - outsideContactLayerThickness, detectorDiameter/2, detectorLength/2 - detectorEndRadius/2, 0*deg, 360*deg);
    G4LogicalVolume *logicOutsideContactLayer2 = new G4LogicalVolume(solidOutsideContactLayer2, Li, "logicOutsideContactLayer2");
    G4VPhysicalVolume *physOutsideContactLayer2 = new G4PVPlacement(0, G4ThreeVector(0, 0, endCapWallLength/2 - endCapToCrystalGap - detectorEndRadius - detectorLength/2 + detectorEndRadius/2), logicOutsideContactLayer2, "physOutsideContactLayer2", logicVoid, false, 0, true);

    // VID gaura ----------
    G4Sphere *solidVoidHole1 = new G4Sphere("solidVoidHole1", 0*mm, holeDiameter/2, 0*deg, 180*deg, 0*deg, 180*deg);
    G4LogicalVolume *logicVoidHole1 = new G4LogicalVolume(solidVoidHole1, vacuum, "logicVoidHole1");
    G4RotationMatrix *rotX = new G4RotationMatrix();
    rotX->rotateX(-90*deg);
    G4VPhysicalVolume *physVoidHole1 = new G4PVPlacement(rotX, G4ThreeVector(0, 0, -endCapWallLength/2 + holeDepth - holeDiameter/2), logicVoidHole1, "physVoidHole1", logicVoid, false, 0, true);

    G4Tubs *solidVoidHole2 = new G4Tubs("solidVoidHole2", 0*mm, holeDiameter/2, holeDepth/2 - holeDiameter/4, 0*deg, 360*deg);
    G4LogicalVolume *logicVoidHole2 = new G4LogicalVolume(solidVoidHole2, vacuum, "logicVoidHole2");
    G4VPhysicalVolume *physVoidHole2 = new G4PVPlacement(0, G4ThreeVector(0, 0, -endCapWallLength/2 + holeDepth/2 - holeDiameter/4), logicVoidHole2, "physVoidHole2", logicVoid, false, 0, true);

    // Cristal Ge ----------
    G4Cons *solidCrystal1 = new G4Cons("solidCrystal1", 0*mm, detectorDiameter/2 - outsideContactLayerThickness*sqrt(2), 0*mm, detectorDiameter/2 - detectorEndRadius - outsideContactLayerThickness*sqrt(2), detectorEndRadius/2, 0*deg, 360*deg);
    //G4LogicalVolume *logicCrystal1 = new G4LogicalVolume(solidCrystal1, Ge, "logicCrystal1");
    //G4VPhysicalVolume *physCrystal1 = new G4PVPlacement(0, G4ThreeVector(0, 0, endCapWallLength/2 - endCapToCrystalGap - detectorEndRadius/2), logicCrystal1, "physCrystal1", logicVoid, false, 0, true);

    G4UnionSolid *solidUnionVoidHole = new G4UnionSolid("solidUnionVoidHole", solidVoidHole2, solidVoidHole1, rotX, G4ThreeVector(0, 0, holeDepth/2 - holeDiameter/4));  // rotatia si translatia corespund celui de-al doilea volum, solidVoidHole1, relativ la solidVoidHole2 care are originea in (0,0,0)
    G4Tubs *solidUncutCrystal = new G4Tubs("solidUncutCrystal", 0*mm, detectorDiameter/2 - outsideContactLayerThickness, detectorLength/2 - detectorEndRadius/2, 0*deg, 360*deg);

    G4SubtractionSolid *solidCrystal2 = new G4SubtractionSolid("solidCrystal2", solidUncutCrystal, solidUnionVoidHole, nullptr, G4ThreeVector(0, 0, -detectorLength/2 + detectorEndRadius/2 + holeDepth/2 - holeDiameter/4));
    //G4LogicalVolume *logicCrystal2 = new G4LogicalVolume(solidCrystal2, Ge, "logicCrystal2");
    //G4VPhysicalVolume *physCrystal2 = new G4PVPlacement(0, G4ThreeVector(0, 0, -endCapWallLength/2 + detectorLength/2 - detectorEndRadius/2), logicCrystal2, "physCrystal2", logicVoid, false, 0, true);

    G4UnionSolid *solidCrystal = new G4UnionSolid("solidCrystal", solidCrystal2, solidCrystal1, nullptr, G4ThreeVector(0, 0, detectorLength/2 - detectorEndRadius/2 + detectorEndRadius/2));  // cristalul final de Ge
    G4LogicalVolume *logicCrystal = new G4LogicalVolume(solidCrystal, Ge, "logicCrystal");
    G4VPhysicalVolume *physCrystal = new G4PVPlacement(0, G4ThreeVector(0, 0, -endCapWallLength/2 + detectorLength/2 - detectorEndRadius/2), logicCrystal, "physCrystal", logicVoid, false, 0, true);


    // _____ Vizualizare _____

    G4VisAttributes *blue = new G4VisAttributes(G4Colour::Blue());
    blue->SetVisibility(true);
    blue->SetForceSolid(true);

    logicEndCapWindow->SetVisAttributes(G4Colour::Brown());
    logicEndCapWall->SetVisAttributes(G4Colour::Brown());
    logicInsulator->SetVisAttributes(G4Colour::Red());
    logicMountCupWall->SetVisAttributes(G4Colour::Red());
    logicOutsideContactLayer1->SetVisAttributes(G4Colour::Yellow());
    logicOutsideContactLayer2->SetVisAttributes(G4Colour::Yellow());
    //logicCrystal1->SetVisAttributes(blue);
    //logicCrystal2->SetVisAttributes(blue);
    logicCrystal->SetVisAttributes(blue);
    

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
    /*G4MultiFunctionalDetector *crystal1, *crystal2;
    G4VPrimitiveScorer *primitive1, *primitive2;

    crystal1 = new G4MultiFunctionalDetector("crystal1");  // cristalul de Ge cu forma conica
    crystal2 = new G4MultiFunctionalDetector("crystal2");  // cristalul de Ge cu forma cilindrica
    primitive1 = new G4PSEnergyDeposit("Edep1");
    primitive2 = new G4PSEnergyDeposit("Edep2");

    crystal1->RegisterPrimitive(primitive1);
    crystal2->RegisterPrimitive(primitive2);

    SetSensitiveDetector("logicCrystal1", crystal1);
    SetSensitiveDetector("logicCrystal2", crystal2);

    G4SDManager::GetSDMpointer()->AddNewDetector(crystal1);
    G4SDManager::GetSDMpointer()->AddNewDetector(crystal2);*/

    G4MultiFunctionalDetector *crystal;
    G4VPrimitiveScorer *primitive;

    crystal = new G4MultiFunctionalDetector("crystal");
    primitive = new G4PSEnergyDeposit("Edep");

    crystal->RegisterPrimitive(primitive);

    SetSensitiveDetector("logicCrystal", crystal);

    G4SDManager::GetSDMpointer()->AddNewDetector(crystal);
}