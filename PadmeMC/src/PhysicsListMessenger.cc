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
//
// $Id: PhysicsListMessenger.cc,v 1.5.2.1 2010/03/18 10:33:19 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//
//
/////////////////////////////////////////////////////////////////////////
//
// PhysicsListMessenger
//
// Created: 31.01.2006 V.Ivanchenko
//
// Modified:
// 04.06.2006 Adoptation of hadr01 (V.Ivanchenko)
//
// 03-09-2012 Sergey Podolsky (siarhei.padolski@cern.ch)      
//
////////////////////////////////////////////////////////////////////////

#include "PhysicsListMessenger.hh"
#include "PhysicsList.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4RunManager.hh"

PhysicsListMessenger* PhysicsListMessenger::fInstance = nullptr;

PhysicsListMessenger::PhysicsListMessenger() :
  G4UImessenger(), 
  fGammaCutCmd(0), fElectCutCmd(0), fPosCutCmd(0), fCutCmd(0), fAllCutCmd(0),
  fPListCmd(0), fListCmd(0), fFastCmd(0), fDecayPiplusDecayCmd(0), fMuonDecayCmd(0) {

  fGammaCutCmd = new G4UIcmdWithADoubleAndUnit("/Simulation/CutGamma",this);  
  fGammaCutCmd->SetGuidance("Set gamma cut.");
  fGammaCutCmd->SetParameterName("Gcut",false);
  fGammaCutCmd->SetUnitCategory("Length");
  fGammaCutCmd->SetRange("Gcut>=0.0");
  fGammaCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fElectCutCmd = new G4UIcmdWithADoubleAndUnit("/Simulation/CutEl",this);  
  fElectCutCmd->SetGuidance("Set electron cut.");
  fElectCutCmd->SetParameterName("Ecut",false);
  fElectCutCmd->SetUnitCategory("Length");
  fElectCutCmd->SetRange("Ecut>=0.0");
  fElectCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fPosCutCmd = new G4UIcmdWithADoubleAndUnit("/Simulation/CutPos",this);
  fPosCutCmd->SetGuidance("Set positron cut.");
  fPosCutCmd->SetParameterName("Pcut",false);
  fPosCutCmd->SetUnitCategory("Length");
  fPosCutCmd->SetRange("Pcut>=0.0");
  fPosCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fCutCmd = new G4UIcmdWithADoubleAndUnit("/Simulation/CutProt",this);
  fCutCmd->SetGuidance("Set proton cut.");
  fCutCmd->SetParameterName("ProtCut",false);
  fCutCmd->SetUnitCategory("Length");
  fCutCmd->SetRange("ProtCut>=0.0");
  fCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fAllCutCmd = new G4UIcmdWithADoubleAndUnit("/Simulation/CutsAll",this);
  fAllCutCmd->SetGuidance("Set cut for all.");
  fAllCutCmd->SetParameterName("cut",false);
  fAllCutCmd->SetUnitCategory("Length");
  fAllCutCmd->SetRange("cut>=0.0");
  fAllCutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fPListCmd = new G4UIcmdWithAString("/Simulation/Physics",this);
  fPListCmd->SetGuidance("Add modular physics list.");
  fPListCmd->SetParameterName("PList",false);
  fPListCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fListCmd = new G4UIcmdWithoutParameter("/Simulation/ListPhysics",this);
  fListCmd->SetGuidance("Available Physics Lists");
  fListCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fFastCmd = new G4UIcmdWithoutParameter("/Simulation/TurnOnFastLkr",this);
  fFastCmd->SetGuidance("Switch on fast LKr Simulation");
  fFastCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  fDecayPiplusDecayCmd = new G4UIcmdWithADouble("/decay/BrPie2",this);
  fDecayPiplusDecayCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fMuonDecayCmd = new G4UIcmdWithAnInteger("/decay/muonDecay",this);
  fMuonDecayCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  fBrPie2 = -1;
  fMuonDecayMode = -1.;
  fCutGamma = -1.;
  fCutElectron = -1.;
  fCutPositron = -1.;
  fCutProton = -1.;
  fPhysicsListName = -1.;
  fAddParameterisation =false;
  
}

PhysicsListMessenger::~PhysicsListMessenger() {
  delete fGammaCutCmd;
  delete fElectCutCmd;
  delete fPosCutCmd;
  delete fCutCmd;
  delete fAllCutCmd;
  delete fPListCmd;
  delete fListCmd;
  delete fFastCmd;
  delete fDecayPiplusDecayCmd;
}
PhysicsListMessenger* PhysicsListMessenger::GetInstance() {
  if (!fInstance) {
    fInstance = new PhysicsListMessenger();
  }
  return fInstance;
}

void PhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String val) {

  G4cout << command->GetCommandPath() << " " << val << G4endl;

  if (command == fGammaCutCmd) {
    fCutGamma = fGammaCutCmd->GetNewDoubleValue(val);
  }
  else if (command == fElectCutCmd) {
    fCutElectron = fElectCutCmd->GetNewDoubleValue(val);
  }
  else if (command == fPosCutCmd) {
    fCutPositron = fPosCutCmd->GetNewDoubleValue(val);
  } else if( command == fCutCmd ) {
    fCutProton = fCutCmd->GetNewDoubleValue(val);
  }
  else if (command == fAllCutCmd) {
    G4double cut = fAllCutCmd->GetNewDoubleValue(val);
    fCutGamma = cut;
    fCutElectron = cut;
    fCutPositron = cut;
    fCutProton = cut;
  }
  else if (command == fPListCmd) {
    G4String name = val;
    if(name == "PHYSLIST") {
      char* path = getenv(name);
      if (path) name = G4String(path);
      else {
	G4cerr << "### PhysicsListMessenger WARNING: "
	       << " environment variable PHYSLIST is not defined"
	       << G4endl;
	return; 
      }
    }
    fPhysicsListName = name;
  }
  else if (command == fListCmd) {
    fListPhysList = true;
  }
  else if (command == fFastCmd) {
    fAddParameterisation = true;
  }
  else if (command == fDecayPiplusDecayCmd) {
    fBrPie2 = fDecayPiplusDecayCmd->GetNewDoubleValue(val);
  }
  else if (command == fMuonDecayCmd) {
    fMuonDecayMode = fMuonDecayCmd->GetNewIntValue(val);
  }
}
