// SACDetector.cc
// --------------------------------------------------------------
// History:
//
// Created by Emanuele Leonardi (emanuele.leonardi@roma1.infn.it) 2105-12-11
// --------------------------------------------------------------

#include "SACDetector.hh"

#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"

#include "SACMessenger.hh"
#include "SACGeometry.hh"
#include "SACSD.hh"

SACDetector::SACDetector(G4LogicalVolume* motherVolume)
  :fMotherVolume(motherVolume)
{

  // Connect to SACMessenger to enable datacard configuration
  fSACMessenger = new SACMessenger(this);

}

SACDetector::~SACDetector()
{
  delete fSACMessenger;
}

void SACDetector::CreateGeometry()
{

  SACGeometry* geo = SACGeometry::GetInstance();

  // Create main SAC box
  printf("SAC will be placed at %f %f %f\n",geo->GetSACPosX(),geo->GetSACPosY(),geo->GetSACPosZ());
  G4ThreeVector sacPos = G4ThreeVector(geo->GetSACPosX(),geo->GetSACPosY(),geo->GetSACPosZ()); 
  G4double sacSizeX = geo->GetSACSizeX();
  G4double sacSizeY = geo->GetSACSizeY();
  G4double sacSizeZ = geo->GetSACSizeZ();
  printf("SAC size is %f %f %f\n",sacSizeX,sacSizeY,sacSizeZ);
  G4Box* solidSAC = new G4Box("SAC",0.5*sacSizeX,0.5*sacSizeY,sacSizeZ);
  fSACVolume = new G4LogicalVolume(solidSAC,G4Material::GetMaterial("Vacuum"),"SAC",0,0,0);
  fSACVolume->SetVisAttributes(G4VisAttributes::Invisible);
  G4RotationMatrix* Rot = new G4RotationMatrix;
  Rot -> rotateY(0.1*rad);
  Rot -> rotateX(0.1*rad);
  new G4PVPlacement(Rot,sacPos,fSACVolume,"SAC",fMotherVolume,false,0,false);

  // Show size of gap between crystals
  printf("Gap between SAC crystals is %f\n",geo->GetCrystalGap());

  // Show thickness of coating around crystals
  printf("Coating around SAC crystals is %f\n",geo->GetCrystalCoating());

  // Create standard PbF2 crystal
  G4double crySizeX = geo->GetCrystalSizeX();
  G4double crySizeY = geo->GetCrystalSizeY();
  G4double crySizeZ = geo->GetCrystalSizeZ();
  printf("SAC Crystal size is %f %f %f\n",crySizeX,crySizeY,crySizeZ);
  G4Box* solidCry  = new G4Box("SACCry",0.5*crySizeX,0.5*crySizeY,0.5*crySizeZ);
  fCrystalVolume  = new G4LogicalVolume(solidCry,G4Material::GetMaterial("PbF2"),"SACCry",0,0,0);
  fCrystalVolume->SetVisAttributes(G4VisAttributes(G4Colour::Magenta()));

  // Make crystal a sensitive detector
  G4SDManager* sdMan = G4SDManager::GetSDMpointer();
  G4String sacSDName = geo->GetSACSensitiveDetectorName();
  printf("Registering SAC SD %s\n",sacSDName.data());
  SACSD* sacSD = new SACSD(sacSDName);
  sdMan->AddNewDetector(sacSD);

  //20-05-2020 ADD to track cerenkov photons
  // sacSD->GetOptTrack()->UseOpticalTracking(); 

  fCrystalVolume->SetSensitiveDetector(sacSD);

  // Create SAC cell (PbF2 crystal+coating)
  G4double cellSizeX = geo->GetCellSizeX();
  G4double cellSizeY = geo->GetCellSizeY();
  G4double cellSizeZ = geo->GetCellSizeZ();
  printf("SAC cell size is %f %f %f\n",cellSizeX,cellSizeY,cellSizeZ);
  G4Box* solidCell  = new G4Box("SACCell",0.5*cellSizeX,0.5*cellSizeY,0.5*cellSizeZ);
  fCellVolume  = new G4LogicalVolume(solidCell,G4Material::GetMaterial("EJ510Paint"),"SACCell",0, 0, 0);
  fCellVolume->SetVisAttributes(G4VisAttributes(G4Colour::Magenta()));

  // Position SAC crystal inside cell
  new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),fCrystalVolume,"SACCry",fCellVolume,false,0,false);

  // Get number of rows and columns of crystals and position all crystals
  G4int nRow    = geo->GetSACNRows();
  G4int nCol    = geo->GetSACNCols();
  G4int nLayers = geo->GetSACNLayers();

  G4double Zoffset = 0.;
  
  //I should repeat the structure for different layers
  for (G4int layer=0; layer<nLayers;layer++){
    for (G4int row=0;row<nRow;row++){
      for (G4int col=0;col<nCol;col++){
	if (geo->ExistsCrystalAt(row,col)) {
	  G4ThreeVector positionCry = G4ThreeVector(geo->GetCrystalPosX(row,col),geo->GetCrystalPosY(row,col),geo->GetCrystalPosZ(row,col)+Zoffset);
	  //  printf("cristal position %f %f %f\n",geo->GetCrystalPosX(row,col),geo->GetCrystalPosY(row,col),geo->GetCrystalPosZ(row,col)+Zoffset);
	  G4int idxCell = row*SACGEOMETRY_N_COLS_MAX+col+layer*nRow*nCol;
	  //	  printf("*******idxCell %d\n",idxCell);
	 G4PVPlacement* daughter= new G4PVPlacement(0,positionCry,fCellVolume,"SACCell",fSACVolume,false,idxCell,false);
	 G4LogicalVolume* daughter_log = daughter->GetLogicalVolume();
	// if(daughter->CheckOverlaps(1000,false)){
	//   printf("WARNING - overlaps found in %s\n",daughter_log->GetName().data());
	//   return;
	// }
	}
      }
    }
    Zoffset+=  geo->GetCellSizeZ();
  }
}
