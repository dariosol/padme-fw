// --------------------------------------------------------------
// History:
//
// Created by Emanuele Leonardi (emanuele.leonardi@roma1.infn.it) 2016-07-22
//
// --------------------------------------------------------------

#ifndef HEPVetoDigi_h
#define HEPVetoDigi_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HEPVetoDigi : public G4VDigi
{
  public:

      HEPVetoDigi();
     ~HEPVetoDigi();
      HEPVetoDigi(const HEPVetoDigi&);
      const HEPVetoDigi& operator=(const HEPVetoDigi&);
      G4int operator==(const HEPVetoDigi&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
    
  void SetChannelId(G4int c) { fChannelId = c; }
  G4int GetChannelId() { return fChannelId; }

  void SetTime(G4double t) { fTime = t; };
  G4double GetTime() { return fTime; };

  void SetTimeSpread(G4double t) { fTimeSpread = t; };
  G4double GetTimeSpread() { return fTimeSpread; };

  void SetEnergy(G4double e) { fEnergy = e; }
  G4double GetEnergy() { return fEnergy; }

  void SetPosition(G4ThreeVector p) { fPosition = p; }
  G4ThreeVector GetPosition() { return fPosition; }
  G4double GetPosX() { return fPosition.x(); };
  G4double GetPosY() { return fPosition.y(); };
  G4double GetPosZ() { return fPosition.z(); };

  void SetLocalPosition(G4ThreeVector p) { fLocalPosition = p; }
  G4ThreeVector GetLocalPosition() { return fLocalPosition; }
  G4double GetLocalPosX() { return fLocalPosition.x(); };
  G4double GetLocalPosY() { return fLocalPosition.y(); };
  G4double GetLocalPosZ() { return fLocalPosition.z(); };
  
  G4int GetNHits(){return fNHits;};
  void SetNHits(int nh){fNHits = nh;};

private:
    
  G4int         fChannelId;
  G4double      fTime;
  G4double      fTimeSpread;
  G4double      fEnergy;
  G4ThreeVector fPosition;
  G4ThreeVector fLocalPosition;
  G4int         fNHits;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4TDigiCollection<HEPVetoDigi> HEPVetoDigiCollection;

extern G4Allocator<HEPVetoDigi> HEPVetoDigiAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* HEPVetoDigi::operator new(size_t)
{
  void* aDigi;
  aDigi = (void*) HEPVetoDigiAllocator.MallocSingle();
  return aDigi;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void HEPVetoDigi::operator delete(void* aDigi)
{
  HEPVetoDigiAllocator.FreeSingle((HEPVetoDigi*) aDigi);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
