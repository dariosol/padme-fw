// BeamGenerator.cc
// --------------------------------------------------------------
// History:
//
// 2016-02-11 Created by Emanuele Leonardi (emanuele.leonardi@roma1.infn.it)
//
// --------------------------------------------------------------

#include "BeamGenerator.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomDirection.hh"
#include "G4Poisson.hh"
#include "Randomize.hh"
//#include "TRandom3.h"

#include "BeamMessenger.hh"
#include "HistoManager.hh"
#include "DetectorConstruction.hh"

BeamGenerator::BeamGenerator(DetectorConstruction* myDC)
 :fDetector(myDC)
{

  fEvent = 0;

  // Initialize calibration run to some sensible values
  //fCalibrationRun  = false;
  //fCalibRunEnergy  = 50.*MeV;
  //fCalibRunCenterX = 14.*cm;
  //fCalibRunCenterY = 14.*cm;
  //fCalibRunRadius  =  1.*cm;

  // Default Z position of beam is 1 um before the target.
  // Can be changed with /beam/position_z datacard
  BeamParameters* bpar = BeamParameters::GetInstance();
  bpar->SetBeamCenterPosZ(fDetector->GetTargetFrontFaceZ()-1.*um);

  // Connect to BeamMessenger
  fBeamMessenger = new BeamMessenger(this);
  fHistoManager = HistoManager::GetInstance();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BeamGenerator::~BeamGenerator()
{
  delete fBeamMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BeamGenerator::GenerateBeam(G4Event* anEvent)
{ 

  fEvent = anEvent;

  BeamParameters* bpar = BeamParameters::GetInstance();

  static int nev;
  nev++;
  if(nev%10000 == 0) std::cout << "Generating event number " << nev << std::endl;

  // Special calibration run
  if ( bpar->CalibrationRun() ) {
    // Origin of calibration beam is on back face of Target
    //bpar->SetBeamOriginPosZ(fDetector->GetTargetFrontFaceZ()+fDetector->GetTargetThickness());
    bpar->SetBeamCenterPosZ(fDetector->GetTargetFrontFaceZ()+fDetector->GetTargetThickness());
    GenerateCalibrationGamma();
    return;
  }

  // Main positron beam origin is set to 1 um before the front face of the Target
  //bpar->SetBeamOriginPosZ(fDetector->GetTargetFrontFaceZ()-1.*um);
  /*
  G4int nTotPositrons = bpar->GetNPositronsPerBunch();
  if (bpar->NPositronsPerBunchApplySpread()) {
    nTotPositrons = G4Poisson(nTotPositrons);
    }*/
   G4int nTotPositrons=1;
  G4int nPositrons = nTotPositrons;
  if (nPositrons<0) {
    G4cout << "BeamGenerator - WARNING - Negative number of primary positrons in event. Please check your settings" << G4endl;
    nPositrons = 0;
  }

  
  //******************************************************
  //General BG generator particles on the target per event 
  //******************************************************
  fHistoManager->FillHisto(6,nPositrons);
  for(int ip = 0; ip < nPositrons; ip++) { 

    // Generate primary e+
    GeneratePrimaryPositron();
    //G4cout << "Positron " << fPositron.t << " " << fPositron.pos << " " << fPositron.P << " " << fPositron.dir << G4endl;

    bool myparticle=bpar->GetParticle();

    // Create e+ primary particle with generated four-momentum
    G4PrimaryParticle* positron;
    if(myparticle==0)  positron = new G4PrimaryParticle(G4ParticleTable::GetParticleTable()->FindParticle("gamma"),
									  fPositron.p.x(),fPositron.p.y(),fPositron.p.z(),fPositron.E);
     if(myparticle==1) positron = new G4PrimaryParticle(G4ParticleTable::GetParticleTable()->FindParticle("neutron"),
									  fPositron.p.x(),fPositron.p.y(),fPositron.p.z(),fPositron.E);
   
     // Create primary vertex at generated position/time
    G4PrimaryVertex* vtx = new G4PrimaryVertex(G4ThreeVector(fPositron.pos.x(),fPositron.pos.y(),fPositron.pos.z()),fPositron.t);
    vtx->SetPrimary(positron);

    fHistoManager->FillHisto2(36,fPositron.pos.x(),fPositron.pos.y(),1.);
    fHistoManager->FillHisto(2,fPositron.E);
    fHistoManager->FillHisto(3,fPositron.t);
    fHistoManager->FillHisto(4,fPositron.t);
    fEvent->AddPrimaryVertex(vtx);
  }

}

void BeamGenerator::GeneratePrimaryPositron()
{

  BeamParameters* bpar = BeamParameters::GetInstance();

  // Generate a primary e+ with right time/energy/position/direction

  // Get mass of positron
  bool myparticle=bpar->GetParticle();
  
  if(myparticle==0)fPositron.m = G4ParticleTable::GetParticleTable()->FindParticle("gamma")->GetPDGMass(); // Mass
  if(myparticle==1)fPositron.m = G4ParticleTable::GetParticleTable()->FindParticle("neutron")->GetPDGMass(); // Mass
  
  G4cout << "BeamGenerator - Particle mass " << fPositron.m << G4endl;

  // Assign a time using bunch time structure (if required)
  G4double parTime = 0.;
  if ( bpar->BeamApplyBunchStructure() ) {
    G4double bunchLen = bpar->GetBunchTimeLength();
    G4double ubunchLen = bpar->GetMicroBunchTimeLength();
    G4double ubunchDly = bpar->GetMicroBunchTimeDelay();
    G4double nubunch = bunchLen/(ubunchDly+ubunchLen);
    G4int ubunchNow = int(G4UniformRand()*nubunch);
    parTime = ubunchNow*(ubunchDly+ubunchLen)+G4UniformRand()*ubunchLen;
  }
  fPositron.t = parTime;
  //  G4cout << "BeamGenerator - Positron time " << fPositron.t << G4endl;

  // Set positron momentum
  fPositron.P = bpar->GetBeamMomentum();
  if ( bpar->BeamMomentumApplySpread() ) fPositron.P = G4RandGauss::shoot(fPositron.P,bpar->GetBeamMomentumSpread());
  //  G4cout << "BeamGenerator - Positron momentum " << fPositron.P << G4endl;

  // Define position and direction for center of beam
  //G4ThreeVector beam_pos = G4ThreeVector(bpar->GetBeamCenterPosX(),bpar->GetBeamCenterPosY(),bpar->GetBeamOriginPosZ());
  G4ThreeVector beam_pos = G4ThreeVector(bpar->GetBeamCenterPosX(),bpar->GetBeamCenterPosY(),bpar->GetBeamCenterPosZ());
  G4ThreeVector beam_dir = bpar->GetBeamDirection();
  beam_dir = beam_dir.unit();

  // Generate starting position of the positrons taking into account beam position and direction
  G4ThreeVector part_pos;
  if ( bpar->BeamCenterPosApplySpread() ) {
    // Generate initial particle position assuming beam generates at origin and is directed along Z
    G4double xPos = G4RandGauss::shoot(0.,bpar->GetBeamCenterPosXSpread());
    G4double yPos = G4RandGauss::shoot(0.,bpar->GetBeamCenterPosYSpread());
    G4double zPos = 0.;
    part_pos = G4ThreeVector(xPos,yPos,zPos);
    // Rotate initial position to the correct beam direction
    part_pos.rotateUz(beam_dir);
    // Finally displace to the real beam origin
    part_pos += beam_pos;    
  } else {
    // All particles originate at center of beam (no spread)
    part_pos = beam_pos;
  }
  fPositron.pos = part_pos;
  //G4cout << "BeamGenerator - Beam postion " << beam_pos << " Positron position " << fPositron.pos << G4endl;
  
  // Add emittance around direction of beam axis
  G4ThreeVector part_dir;
  if ( bpar->BeamApplyEmittance() ) {

    // Extract theta and phi according to emittance
    // Here we could introduce a correlation with the particle position wrt the beam axis

    // Phi is uniform around the beam direction
    G4double phi   = twopi*G4UniformRand();

    // Theta is gaussian with sigma from a phi-based combination of emittance along X and Y
    G4double sigma_theta = bpar->GetBeamEmittanceX()*cos(phi)+bpar->GetBeamEmittanceX()*sin(phi);
    G4double theta = G4RandGauss::shoot(0,sigma_theta);

    // Compute particle direction assuming beam is directed along Z (default direction)
    G4double pX = sin(theta)*cos(phi);
    G4double pY = sin(theta)*sin(phi);
    G4double pZ = cos(theta);
    part_dir = G4ThreeVector(pX,pY,pZ);

    // Now rotate to the real beam direction
    part_dir.rotateUz(beam_dir);

  } else {

    // Beam direction is along the beam axis
    part_dir = beam_dir;

  }
  fPositron.dir = part_dir.unit();
  G4cout << "BeamGenerator - Beam direction " << beam_dir
  << " Particle direction " << fPositron.dir << G4endl;


  // Set positron total energy
  fPositron.E = sqrt(fPositron.P*fPositron.P+fPositron.m*fPositron.m);
  G4cout << "BeamGenerator - Particle energy " << fPositron.E << " " << fPositron.E-fPositron.P << G4endl;

  // Set positron momentum vector
  fPositron.p = G4ThreeVector(fPositron.P*fPositron.dir.x(),
			      fPositron.P*fPositron.dir.y(),
			      fPositron.P*fPositron.dir.z());
  G4cout << "BeamGenerator - Particle momentum vector " << fPositron.p << G4endl;

}

void BeamGenerator::GenerateCalibrationGamma()
{

  BeamParameters* bpar = BeamParameters::GetInstance();

  // Create primary vertex at center of back face of target with t=0.
  G4double vT = 0.*ns;
  G4double vX = 0.*cm;
  G4double vY = 0.*cm;
  G4double vZ = bpar->GetBeamCenterPosZ();
  G4PrimaryVertex* vtx = new G4PrimaryVertex(G4ThreeVector(vX,vY,vZ),vT);
  //  printf("BeamGenerator::GenerateCalibrationGamma - Vertex at %f %f %f t=%f\n",vX,vY,vZ,vT);

  // Choose a point within circle on the surface of ECal
  G4double pX = bpar->GetCalibRunCenterX();
  G4double pY = bpar->GetCalibRunCenterY();
  G4double pZ = fDetector->GetECalFrontFaceZ();
  if (bpar->GetCalibRunRadius() != 0.) {
    // Flat distribution over circle
    G4double rd = bpar->GetCalibRunRadius()*sqrt(G4UniformRand());
    G4double th = 2.*pi*G4UniformRand();
    pX += rd*cos(th);
    pY += rd*sin(th);
  }
  //  printf("BeamGenerator::GenerateCalibrationGamma - Point to %f %f %f\n",pX,pY,pZ);

  // Compute unit vector from vertex to generated point
  G4ThreeVector vp = G4ThreeVector(pX-vX,pY-vY,pZ-vZ).unit();
  //  printf("BeamGenerator::GenerateCalibrationGamma - Vector %f %f %f\n",vp.x(),vp.y(),vp.z());

  // Create gamma pointing from vertex to generated point
  // Will be improved to use different particles (e.g. e+)
  G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  G4double part_E = bpar->GetCalibRunEnergy();
  G4PrimaryParticle* particle = new G4PrimaryParticle(part,part_E*vp.x(),part_E*vp.y(),part_E*vp.z(),part_E);
  vtx->SetPrimary(particle);

  // Add primary vertex to event
  fEvent->AddPrimaryVertex(vtx);

}
