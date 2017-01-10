// ECalGeometry.hh
// --------------------------------------------------------------
// History:
//
// Created by Emanuele Leonardi (emanuele.leonardi@roma1.infn.it) 2105-12-14
// --------------------------------------------------------------

#ifndef ECalGeometry_H
#define ECalGeometry_H 1

#include <vector>

#include "globals.hh"
#include "G4SystemOfUnits.hh"

class G4LogicalVolume;

#define ECALGEOMETRY_N_ROWS_MAX 100
#define ECALGEOMETRY_N_COLS_MAX 100

class ECalGeometry
{

public:

  ~ECalGeometry();
  static ECalGeometry* GetInstance();
  std::vector<G4String> GetHashTable();

private:

  static ECalGeometry* fInstance;

protected:

  ECalGeometry();

public:

  // Position of center of ECal box
  G4double GetECalPosX() { return 0.*cm; }
  G4double GetECalPosY() { return 0.*cm; }
  //G4double GetECalPosZ() { return fECalFrontFacePosZ+(fCrystalSizeZ+fCrystalGap)*0.5; }
  G4double GetECalPosZ() { return fECalFrontFacePosZ+GetECalSizeZ()*0.5; }

  // Size of ECal box
  //G4double GetECalSizeX() { return (fCrystalSizeX+2.*fCrystalCoating+fCrystalGap)*fECalNCols; }
  //G4double GetECalSizeY() { return (fCrystalSizeY+2.*fCrystalCoating+fCrystalGap)*fECalNRows; }
  //G4double GetECalSizeZ() { return  fCrystalSizeZ+2.*fCrystalCoating+fCrystalGap; }
  G4double GetECalSizeX() { return (GetCellSizeX()+fCrystalGap)*fECalNCols; }
  G4double GetECalSizeY() { return (GetCellSizeY()+fCrystalGap)*fECalNRows; }
  G4double GetECalSizeZ() { return  GetCellSizeZ()+fCrystalGap; }

  // Number of rows and columns of crystals in ECAL
  G4int GetECalNRows()        { return fECalNRows; }
  G4int GetECalNCols()        { return fECalNCols; }
  void  SetECalNRows(G4int r) { fECalNRows = r; }
  void  SetECalNCols(G4int c) { fECalNCols = c; }

  // Check if crystal exists at given row/column
  G4int ExistsCrystalAt(G4int,G4int);

  // Position of center of crystal at given row/column
  G4double GetCrystalPosX(G4int,G4int);
  G4double GetCrystalPosY(G4int,G4int);
  G4double GetCrystalPosZ(G4int,G4int);

  // Size of BGO crystal
  G4double GetCrystalSizeX() { return fCrystalSizeX; }
  G4double GetCrystalSizeY() { return fCrystalSizeY; }
  G4double GetCrystalSizeZ() { return fCrystalSizeZ; }

  // Set size of BGO crystal
  void SetCrystalSizeX(G4double s) { fCrystalSizeX = s; }
  void SetCrystalSizeY(G4double s) { fCrystalSizeY = s; }
  void SetCrystalSizeZ(G4double s) { fCrystalSizeZ = s; }

  // Size of ECal cell (BGO crystal+coating)
  G4double GetCellSizeX() { return fCrystalSizeX+2.*fCrystalCoating; }
  G4double GetCellSizeY() { return fCrystalSizeY+2.*fCrystalCoating; }
  G4double GetCellSizeZ() { return fCrystalSizeZ+2.*fCrystalCoating; }

  // Size of gap between crystals
  G4double GetCrystalGap() { return fCrystalGap; }
  void SetCrystalGap(G4double g) { fCrystalGap = g; }

  // Thickness of paint coating around each crystal
  G4double GetCrystalCoating() { return fCrystalCoating; }
  void SetCrystalCoating(G4double c) { fCrystalCoating = c; }

  // Set position along Z of ECal front face
  G4double GetECalFrontFacePosZ() { return fECalFrontFacePosZ; }
  void SetECalFrontFacePosZ(G4double z) { fECalFrontFacePosZ = z; }

  // Set inner and outer radii of ECal
  //void SetECalInnerRadius(G4double r) { fECalInnerRadius = r; }
  //void SetECalOuterRadius(G4double r) { fECalOuterRadius = r; }

  // Get name of ECal sensitive detector
  G4String GetECalSensitiveDetectorName() { return fECalSensitiveDetectorName; }

private:

  G4double fCrystalSizeX;
  G4double fCrystalSizeY;
  G4double fCrystalSizeZ;

  G4int fECalNRows;
  G4int fECalNCols;

  G4double fCrystalGap; // Air gap size between adjacent crystals+coating

  G4double fCrystalCoating; // Thickness of coating around crystals

  G4double fECalFrontFacePosZ; // Position along Z axis of ECal front face

  //G4double fECalInnerRadius; // Radius of hole at ECal center
  //G4double fECalOuterRadius; // External radius of ECal

  G4int fECalCrystalMap[ECALGEOMETRY_N_ROWS_MAX][ECALGEOMETRY_N_COLS_MAX]; // Map of existing crystals

  G4String fECalSensitiveDetectorName;

};

#endif
