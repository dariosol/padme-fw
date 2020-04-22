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
// $Id: PhysicsListMessenger.hh,v 1.3.6.1 2010/03/18 10:33:19 gcosmo Exp $
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
//
// 03-09-2012 Sergey Podolsky (siarhei.padolski@cern.ch)
//
////////////////////////////////////////////////////////////////////////

#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PhysicsList;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;

class PhysicsListMessenger: public G4UImessenger {


private:
  PhysicsListMessenger();
  virtual ~PhysicsListMessenger();

public:
  static PhysicsListMessenger* GetInstance();
  void SetNewValue(G4UIcommand*, G4String);

  void SetCutForGamma(G4double value ) { fCutGamma = value;}
  G4double GetCutForGamma(){return fCutGamma;}
  void SetCutForElectron(G4double value){ fCutElectron =value;}
  G4double GetCutForElectron(){return fCutElectron;}
  void SetCutForPositron(G4double value){fCutPositron = value;}
  G4double GetCutForPositron(){return fCutPositron;}
  void SetCutForProton(G4double value){fCutProton = value;}
  G4double GetCutForProton(){return fCutProton;}

  void SetPhysicsList(G4String name){fPhysicsListName = name;}
  G4String GetPhysicsList(){return fPhysicsListName;}

  void SetAddParameterisation(G4bool value){fAddParameterisation = value;}
  G4bool GetAddParameterisation(){return fAddParameterisation;}

  void     SetBrPie2(G4double value ){fBrPie2 = value;}
  G4double GetBrPie2() const { return fBrPie2; }
  void     SetMuonDecay(G4int value ){fMuonDecayMode = value;} ///< Set muon decay mode 
  G4double     GetMuonDecay(){return fMuonDecayMode;} ///< Set muon decay mode 
  void SetListPhysList(G4bool value) {fListPhysList = value;}
  G4bool GetListPhysList(){return fListPhysList;}

private:
  static PhysicsListMessenger* fInstance;

  G4UIcmdWithADoubleAndUnit* fGammaCutCmd;
  G4UIcmdWithADoubleAndUnit* fElectCutCmd;
  G4UIcmdWithADoubleAndUnit* fPosCutCmd;
  G4UIcmdWithADoubleAndUnit* fCutCmd;
  G4UIcmdWithADoubleAndUnit* fAllCutCmd;
  G4UIcmdWithAString*        fPListCmd;
  G4UIcmdWithoutParameter*   fListCmd;  
  G4UIcmdWithoutParameter*   fFastCmd; 



  G4UIcmdWithADouble*        fDecayPiplusDecayCmd;
  G4UIcmdWithAnInteger*      fMuonDecayCmd;


  G4double fBrPie2;
  G4int    fMuonDecayMode;
  G4double fCutGamma;
  G4double fCutElectron;
  G4double fCutPositron;
  G4double fCutProton;
  G4String fPhysicsListName;
  G4bool   fAddParameterisation;
  G4bool   fListPhysList;
};

#endif
