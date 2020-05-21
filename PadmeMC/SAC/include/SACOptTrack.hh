// --------------------------------------------------------------------
// History:
//
// Created by Domenico Di Filippo (difilippo@na.infn.it) 2010-03-15
//  2010-04-19 Domenico Di Filippo: new independent variables definition
//  2011-01-24 Domenico Di Filippo: (difilippo@na.infn.it)
//    - Switch to std::vector
//
// --------------------------------------------------------------------

#ifndef SACOptTrack_H
#define SACOptTrack_H

#include "globals.hh"
#include "G4MaterialPropertyVector.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"
#include "SACSampleMatrix.hh"
#include "G4AffineTransform.hh"

#include <vector>

class SACOptTrack{

public:
    SACOptTrack();
    ~SACOptTrack();

    // Set temporany vector to be filled
    void SetEnergyVector(std::vector<G4double>* e) {fPhotonsEnergy=e;}
    void SetTimeVector(std::vector<G4double>* t) {fPhotonsDelay=t;}
    G4bool ProcessOpticalPhoton(G4Step *);

    void SetEfficiencyFactor(G4double e) {fEfficiency=e;};
    void ReloadMatrix() {fMatrixReady=false;}

    // Set/Get tracking type
    void UseOpticalTracking() {fDoOpticalTracking = true; fUseMatrix=false;}
    void UseMatrix() {fDoOpticalTracking = false; fUseMatrix = true;}
    void UseEfficiency() {fDoOpticalTracking = false; fUseMatrix = false;}
    bool GetOpticalTracking() {return fDoOpticalTracking;}
    G4bool IsUsingMatrix() {return fUseMatrix;}

private:

    void Process(const G4ThreeVector&,
                 const G4ThreeVector&,
                 const double&,
		 const double&);

    bool fUseMatrix, fDoOpticalTracking, fMatrixReady;
    G4double fEfficiency;
    SACSampleMatrix fEfficiencyMatrix, fTimeMatrix, fSigmaTimeMatrix;

    G4ThreeVector fXVer,fYVer,fZVer, fCenter;

    G4ParticleDefinition *fOpticalPhoton;
    std::vector<G4double> *fPhotonsEnergy, *fPhotonsDelay;

};

#endif

