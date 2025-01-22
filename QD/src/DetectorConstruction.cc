#include "DetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    // DIMENSIONS
    auto sphi = 0.*deg;
    auto dphi = 360.*deg;
    auto worldR = 1.*m;


    // MATERIALS
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *water = nist->FindOrBuildMaterial("G4_WATER");
//    G4Material *vacuum = nist->FindOrBuildMaterial("G4_Galactic");

    G4Material *Al = nist->FindOrBuildMaterial("G4_Al");
    G4Material *glass = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

    G4Material *CdS = new G4Material("CdS", 4.82*g/cm3, 2);
    CdS->AddElement(nist->FindOrBuildElement("Cd"), 50.0*perCent);
    CdS->AddElement(nist->FindOrBuildElement("S"), 50.0*perCent);

    G4Material *scint = new G4Material("Scint", 1.000*g/cm3, 2);
    scint->AddMaterial(water, 99.99653*perCent);
    scint->AddMaterial(CdS, 0.00347*perCent);

    //G4Material *fLXe = new G4Material("fLXe", 3.020*g/cm3, 1);
    //fLXe -> AddElement(nist->FindOrBuildElement("Xe"), 100.0*perCent);


    // FROM OMRI START
    G4double energy[32] = 
    {2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV, 2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV, 2.341*eV, 2.386*eV,
     2.433*eV, 2.481*eV, 2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV, 2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
     3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV, 3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV, 3.760*eV, 3.877*eV, 
     4.002*eV, 4.136*eV}; // energy of photons

    G4double rindexScint[32] = 
    {1.3435, 1.3440, 1.3445, 1.3450, 1.3455, 1.3460, 1.3465, 1.3470, 1.3475, 1.3480,
     1.3485, 1.3492, 1.3500, 1.3505, 1.3510, 1.3518, 1.3522, 1.3530, 1.3535, 1.3540,
     1.3545, 1.3550, 1.3555, 1.3560, 1.3568, 1.3572, 1.3580, 1.3585, 1.3590, 1.3595,
     1.3600, 1.3608}; // refractive index of scint

    G4double energyScint[32] = 
    {1.771*eV, 1.914*eV, 2.057*eV, 2.200*eV, 2.343*eV, 2.486*eV, 2.629*eV, 2.771*eV, 2.914*eV, 3.057*eV,
     3.200*eV, 3.343*eV, 3.486*eV, 3.629*eV, 3.771*eV, 3.914*eV, 4.057*eV, 4.200*eV, 4.343*eV, 4.486*eV,
     4.629*eV, 4.771*eV, 4.914*eV, 5.057*eV, 5.200*eV, 5.343*eV, 5.486*eV, 5.629*eV, 5.771*eV, 5.914*eV,
     6.057*eV, 6.200*eV};

    //for Scintillation 15/3/22
    G4double absorption[32] =
    { 3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m, 15.152*m, 17.241*m, 18.868*m, 20.000*m,
     26.316*m, 35.714*m, 45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m, 52.632*m, 47.619*m,
     45.455*m, 41.667*m, 37.037*m, 33.333*m, 30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m, 
     17.500*m, 14.500*m};
    
    G4double scintFast[32] =
    {1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
     1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
     1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
     1.00, 1.00};
    
    G4double scintSlow[32] =
    {0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00,
     8.00, 7.00, 6.00, 4.00, 3.00, 2.00, 1.00, 0.01, 1.00, 2.00,
     3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00, 7.00, 6.00,
     5.00, 4.00};
    
    G4MaterialPropertiesTable *mptScint = new G4MaterialPropertiesTable();
    //dependant on energy
    mptScint->AddProperty("RINDEX", energyScint, rindexScint, 32);
    mptScint->AddProperty("ABSLENGTH", energyScint, absorption, 32);
    mptScint->AddProperty("SCINTILLATIONCOMPONENT1", energyScint, scintFast, 32);
    mptScint->AddProperty("SCINTILLATIONCOMPONENT2", energyScint, scintSlow, 32);
    //independant on energy
    mptScint->AddConstProperty("SCINTILLATIONYIELD", 1357./MeV); //  1357./MeV originally ???
    mptScint->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptScint->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.*ns);       //fast time constant of scintillator
    mptScint->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 10.*ns);      //slow time constant of scintillator
    mptScint->AddConstProperty("SCINTILLATIONYIELD1", 0.8, 0.5);
    mptScint->AddConstProperty("SCINTILLATIONYIELD2", 0.8, 0.5);
    // Check that group velocity is calculated from RINDEX
    if(mptScint->GetProperty("RINDEX")->GetVectorLength() != mptScint->GetProperty("GROUPVEL")->GetVectorLength())
    {
        G4ExceptionDescription ed;
        ed << "Error calculating group velocities. Incorrect number of entries in group velocity material property vector.";
        G4Exception("OpNovice::OpNoviceDetectorConstruction", "OpNovice001",  FatalException, ed);
    }

    scint->SetMaterialPropertiesTable(mptScint);
    
    // Set the Birks Constant for the scintillator (assumption)
    scint->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

    // Air
    G4double rindexAir[2] = {1.00, 1.00};
    G4MaterialPropertiesTable *mptAir = new G4MaterialPropertiesTable(); //Air (worldMat) properties table
    mptAir->AddProperty("RINDEX", energy, rindexAir, 2);
    air->SetMaterialPropertiesTable(mptAir);

    //Glass
    G4double rindexGlass[2] = {1.47, 1.47};
    G4double glass_AbsLength[2] = {4.2 * m, 4.2 * m};
     G4MaterialPropertiesTable *mptGlass = new G4MaterialPropertiesTable();       //Glass properties table
    mptGlass->AddProperty("ABSLENGTH", energy, glass_AbsLength, 2);
    mptGlass->AddProperty("RINDEX", energy, rindexGlass, 2);
    glass->SetMaterialPropertiesTable(mptGlass);


 

    // THE WORLD
    auto worldS = new G4Box("worldS", worldR, worldR, worldR); // name, x/2, y/2, z/2
    auto worldL = new G4LogicalVolume(worldS, air, "worldL"); // solid, material, name
    auto worldP = new G4PVPlacement(0,                // no rotation
                                    G4ThreeVector(),  // at (0, 0, 0)
                                    worldL,           // its logical volume
                                    "worldP",         // its name
                                    0,                // its mother volume
                                    false,            // no boolean operation
                                    0,                // copy number
                                    true);            // check for overlaps
    worldL->SetVisAttributes(G4VisAttributes::GetInvisible());


    // STAND
    auto standS = new G4Box("standS", 0.06*m, 0.06*m, 0.07325*m);
    standL = new G4LogicalVolume(standS, Al, "standL");
    new G4PVPlacement(0,
                      G4ThreeVector(-0.30*m, 0.*m, -0.205*m),
                      standL,
                      "standP",
                      worldL,
                      false,
                      0,
                      true);
    G4VisAttributes *standVisAtt = new G4VisAttributes(G4Colour(0.9, 0.9, 0.9, 1));
    standVisAtt->G4VisAttributes::SetForceSolid(true);
    standL->SetVisAttributes(standVisAtt);

    // BOTTLE
    auto bottle1S = new G4Tubs("bottle1S", 0, 0.040*m, 0.095*m, sphi, dphi);
    auto bottle2S = new G4Tubs("bottle2S", 0, 0.037*m, 0.087*m, sphi, dphi);
    auto bottleS = new G4SubtractionSolid ("bottleS", bottle1S, bottle2S);
    bottleL = new G4LogicalVolume(bottleS, glass, "bottleL");
    new G4PVPlacement(0,
                      G4ThreeVector(-0.30*m, 0.*m, -0.036*m),
                      bottleL,
                      "bottleP",
                      worldL,
                      false,
                      0,
                      true);
    G4VisAttributes *bottleVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.5));
    bottleVisAtt->G4VisAttributes::SetForceSolid(true);
    bottleL->SetVisAttributes(bottleVisAtt);

    // QD
    //auto qdS = new G4Tubs("qdS", 0.*m, 0.037*m, 0.032*m, 0., 2.0*CLHEP::pi);
    auto qdS = new G4Tubs("qdS", 0.*m, 0.037*m, 0.067*m, 0., 2.0*CLHEP::pi);
    qdL = new G4LogicalVolume(qdS, scint, "qdL");
    new G4PVPlacement(0,
                      G4ThreeVector(0*m, 0*m, -0.0545*m),
                      qdL,
                      "qdP",
                      bottleL,
                      false,
                      0,
                      true);
    G4VisAttributes *qdVisAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 0.5, 1));
    qdVisAtt->G4VisAttributes::SetForceSolid(true);
    qdL->SetVisAttributes(qdVisAtt);

    // PMT
    auto pmtS = new G4Sphere("pmtS", 0.07*m, 0.076*m, 0.*CLHEP::pi, 1.*CLHEP::pi, 0.*CLHEP::pi, 1.*CLHEP::pi);
    pmtL = new G4LogicalVolume(pmtS, glass, "pmtL");
    G4RotationMatrix *rotationMatrix = new G4RotationMatrix();
    rotationMatrix->rotateZ(-0.5*CLHEP::pi);
    new G4PVPlacement(rotationMatrix,
                      G4ThreeVector(-0.15*m, 0.*m, -0.09*m),
                      pmtL,
                      "pmtP",
                      worldL,
                      false,
                      0,
                      true);
    G4VisAttributes *pmtVisAtt = new G4VisAttributes(G4Colour(0.7, 0.2, 0.7, 0.7));
    pmtVisAtt->G4VisAttributes::SetForceSolid(true);
    pmtL->SetVisAttributes(pmtVisAtt);


    return worldP;
}


void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *PhotoSD = new MySensitiveDetector("PhotoSD", "PhotoHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(PhotoSD);
    SetSensitiveDetector("pmtL", PhotoSD);
}

