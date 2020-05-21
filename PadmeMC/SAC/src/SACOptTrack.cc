// --------------------------------------------------------------------
// History:
//
// Created by Domenico Di Filippo (difilippo@na.infn.it) 2010-03-15
// 2010-04-19 - Domenico Di Filippo (difilippo@na.infn.it)
//   - New independent variables definition
// 2011-01-24 - Domenico Di Filippo (difilippo@na.infn.it)
//   - Switch to std::vector
//
// --------------------------------------------------------------------

#include "SACOptTrack.hh"
#include "SACGeometry.hh"

#include "G4ParticleTable.hh"
#include "G4AffineTransform.hh"
#include "G4NavigationHistory.hh"
#include "Randomize.hh"

using namespace std;

const G4ThreeVector Z = G4ThreeVector(0, 0, 1);

SACOptTrack::SACOptTrack(){

      fOpticalPhoton =
         G4ParticleTable::GetParticleTable()->FindParticle("opticalphoton");

      fEfficiencyMatrix.SetOutOfRangeValue(0);
      fTimeMatrix.SetOutOfRangeValue(0);

      fPhotonsEnergy = 0;
      fPhotonsDelay = 0;

      fUseMatrix = false;
      fEfficiency = 1.0;
      fDoOpticalTracking = false;
      fMatrixReady = false;

}

SACOptTrack::~SACOptTrack() {}

G4bool SACOptTrack::ProcessOpticalPhoton(G4Step *aStep){

   // Don't kill anything if fDoOpticalTracking was set
   if (fDoOpticalTracking) return false;
   G4bool toret = false;

   SACGeometry *geoParams = SACGeometryParameters::GetInstance();

   // Load matrices if not already done
   //20-05-2020 Commented: we don't have them yet
   /*
   if (!fMatrixReady) if (fUseMatrix){
      fTimeMatrix.Load(geoParams->GetSACTimeMatrix());
      fEfficiencyMatrix.Load(geoParams->GetSACEfficiencyMatrix());
      if (fEfficiencyMatrix.GetDimensionsNumber()==0)
         fUseMatrix = false;
      fMatrixReady = true;
   }
   */
   // Get block orientation
   const double GlobalTime = aStep->GetTrack()->GetGlobalTime();
   const G4AffineTransform Transform = aStep->
      GetPreStepPoint()->GetTouchableHandle()->GetHistory()->
      GetPtrTopTransform()->Inverse();

   fXVer = Transform.TransformAxis(G4ThreeVector(-1,0,0)).unit();
   fYVer = Transform.TransformAxis(G4ThreeVector(0,-1,0)).unit();
   fZVer = Transform.TransformAxis(G4ThreeVector(0,0,1)).unit();
   fCenter = Transform.TransformPoint(G4ThreeVector(0,0,3.6175378796927*mm)); // WHY I NEED THAT Z ???

   // Process all secondary opticalphotons
   G4TrackVector *v = aStep->GetfSecondary();
   G4TrackVector::iterator i=v->begin();
   while (i != v->end())
      if ((*i)->GetDefinition() == fOpticalPhoton &&
          (*i)->GetVolume()->GetName()=="SACCry"){
         toret = true;
         Process((*i)->GetPosition(),
	         (*i)->GetMomentumDirection(),
	         (*i)->GetTotalEnergy(),
		 GlobalTime);
         delete *i;
         // cppcheck-suppress eraseDereference symbolName=i
         v->erase(i);
      } else ++i;

   if(aStep->GetTrack()->GetDefinition() == fOpticalPhoton &&
      aStep->GetTrack()->GetVolume()->GetName()=="SACry"){
      toret = true;
      Process(aStep->GetPreStepPoint()->GetPosition(),
	      aStep->GetPreStepPoint()->GetMomentumDirection(),
	      aStep->GetPostStepPoint()->GetTotalEnergy(),
	      GlobalTime);
      aStep->GetTrack()->SetTrackStatus(fStopAndKill);
   }

   return toret;

}

void SACOptTrack::Process(const G4ThreeVector &PosGb,
const G4ThreeVector &MomGb, const double &Energy, const double &GlobalTime){

   if (fPhotonsEnergy == 0 && fPhotonsDelay == 0) return;

   G4double Effic = fEfficiency;

   if (fUseMatrix) {

      // exit if matrices are not ready
      if (fTimeMatrix.GetDimensionsNumber() < 6) return;
      if (fEfficiencyMatrix.GetDimensionsNumber() < 6 ) return;

      // Calculate optical photon coordinates
      G4ThreeVector Pos = PosGb - fCenter;
      const G4double RadialDistance = std::sqrt (
       (Pos * fXVer) * (Pos * fXVer) +
       (Pos * fYVer) * (Pos * fYVer) );
      const G4double GuideDistance = Pos * fZVer;
      const G4double PhiPosition = std::atan2(Pos * fYVer, Pos * fXVer);
//    dr = sqrt (
//       (MomGb * fXVer) * (MomGb * fXVer) +
//       (MomGb * fYVer) * (MomGb * fYVer) );
      const G4double ZMomentum = MomGb * fZVer;
      const G4double PhiDirection = std::atan2(MomGb * fYVer, MomGb * fXVer);


      // Find matrix bin
      //fTimeMatrix.GetDimension(0)->Query(ZMomentum);
      //fTimeMatrix.GetDimension(1)->Query(GuideDistance);
      //fTimeMatrix.GetDimension(2)->Query(Energy);
      //fTimeMatrix.GetDimension(3)->Query(RadialDistance);
      //fTimeMatrix.GetDimension(4)->Query(PhiDirection);
      //fTimeMatrix.GetDimension(5)->Query(PhiPosition);
      //
      //fEfficiencyMatrix.GetDimension(0)->Query(ZMomentum);
      //fEfficiencyMatrix.GetDimension(1)->Query(GuideDistance);
      //fEfficiencyMatrix.GetDimension(2)->Query(Energy);
      //fEfficiencyMatrix.GetDimension(3)->Query(RadialDistance);
      //fEfficiencyMatrix.GetDimension(4)->Query(PhiDirection);
      //fEfficiencyMatrix.GetDimension(5)->Query(PhiPosition);
      //
      //// Get efficiency in the bin
      //Effic *= fEfficiencyMatrix.GetValue();

   }

   //if (Effic <= 0) return;
   //if (Effic >= 1.0 || G4UniformRand() < Effic){

      // Update vectors
      fPhotonsEnergy->push_back(Energy);
      fPhotonsDelay->push_back(/*fTimeMatrix.GetValue() +*/ GlobalTime);

   }

}
