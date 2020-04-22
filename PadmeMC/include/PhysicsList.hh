//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// --------------------------------------------------------------
// Based on GEANT 4 - PhysicsList class from Hadr01 example
// --------------------------------------------------------------
//
// Antonino Sergi (Antonino.Sergi@cern.ch)
//
//
//  03-09-2012 Sergey Podolsky (siarhei.padolski@cern.ch)      
//
// --------------------------------------------------------------

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

//Optical Processes
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
class G4OpWLS;
class G4VPhysicsConstructor;
class PhysicsListMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsList: public G4VModularPhysicsList {
public:

  static PhysicsList *GetInstance();

  void ConstructParticle();
  void ConstructProcess();
  void SetMessengerParam();
  void SetCuts();
  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);
  void SetCutForProton(G4double);

  void AddPhysicsList(const G4String& name);
  void OpticalPhysics();
  void List() {}
  void AddParameterisation();

  void     SetBrPie2(G4double); ///< Set the branching ratio of the pi+- --> e+- nu decay
  G4double GetBrPie2() { return fBrPie2; }
  void     SetMuonDecay(G4int); ///< Set muon decay mode
  G4String GetPhysicsListName() {return fPhysicsListName;}

private:

  void SetBuilderList1(G4bool flagHP = false);
  void SetBuilderList2();

  PhysicsList();
  virtual ~PhysicsList();
  static PhysicsList* fgInstance;


  G4double fCutForGamma;
  G4double fCutForElectron;
  G4double fCutForPositron;
  G4double fCutForProton;


  // Optical
  G4Cerenkov*          fCerenkovProcess;
  G4Scintillation*     fScintillationProcess;
  G4OpAbsorption*      fAbsorptionProcess;
  G4OpRayleigh*        fRayleighScatteringProcess;
  G4OpBoundaryProcess* fBoundaryProcess;
  G4OpWLS*             fWLSProcess;

  G4VPhysicsConstructor* fEmPhysicsList;
  G4VPhysicsConstructor* fParticleList;

  std::vector<G4VPhysicsConstructor*> fHadronPhys;

  PhysicsListMessenger* fMessenger;

  G4double fBrPie2; ///< Branching ratio of the pi+- --> e+- nu decay
  G4double fMDS; /// < Needed for hnl mode from D mesons
  G4String fPhysicsListName;
};

#endif
