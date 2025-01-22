#include "PhotoSD.hh"

MySensitiveDetector::MySensitiveDetector(const G4String& name, const G4String& hitsCollectionName) : G4VSensitiveDetector(name)
{
    collectionName.insert(hitsCollectionName);
}

MySensitiveDetector::~MySensitiveDetector()
{}


void MySensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
    // Create hits collection
    fHitsCollection = new PhotoHitsCollection(SensitiveDetectorName, collectionName[0]);

    // Add this collection in hce
    auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection(hcID, fHitsCollection);
}


G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory*)
{
    G4Track *track = aStep->GetTrack();
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
//    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    auto fPDG = track->GetDefinition()->GetPDGEncoding();
    auto fEnergy = preStepPoint->GetKineticEnergy();
    //auto fTime = preStepPoint->GetGlobalTime();
    auto wavelength = 0.0012398/fEnergy;

    if (abs(fPDG)==22 && wavelength>300) {
        PhotoHit* newHit = new PhotoHit();
        newHit->SetWavelength(wavelength);
        //newHit->SetTime(fTime);
        fHitsCollection->insert(newHit);
    }

    return true;
}


void MySensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
//    auto nofHits = fHitsCollection->entries();
//    G4cout << "-------->Hits Collection: in this event they are " << nofHits << G4endl;
//    for ( std::size_t i=0; i<nofHits; ++i ) (*fHitsCollection)[i]->Print();
}

