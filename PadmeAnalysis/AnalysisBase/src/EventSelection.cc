#include "TTargetRecoBeam.hh"
#include "TRecoEvent.hh"
#include "TSACRecoEvent.hh"
#include "TECalRecoEvent.hh"
#include "TPVetoRecoEvent.hh"
#include "THEPVetoRecoEvent.hh"
#include "TEVetoRecoEvent.hh"
#include "TTargetRecoEvent.hh"
#include "TRecoVObject.hh"
#include "TRecoVHit.hh"
#include "TRecoVClusCollection.hh"
#include "TRecoVCluster.hh"
#include "HistoSvc.hh"
#include "TMath.h"
#include "TLorentzVector.h"
#include <iostream>
#include "EventSelection.hh"

EventSelection::EventSelection()
{
  fRecoEvent   = NULL;

  fhitEventTarget= NULL;
  fhitEventECal= NULL;
  fhitEventPVeto= NULL;
  fhitEventEVeto= NULL;
  fhitEventHEPVeto= NULL;
  fhitEventSAC= NULL;

  fClCollTarget= NULL;
  fClCollECal= NULL;
  fClCollPVeto= NULL;
  fClCollEVeto= NULL;
  fClCollHEPVeto= NULL;
  fClCollSAC= NULL;
  
  /*fhitEvent    = NULL;
  fClColl      = NULL;*/
  fProcessingMode = 0;
  fVerbose        = 0;
}
EventSelection::EventSelection(Int_t processingMode, Int_t verbosityFlag)
{
  /*fRecoEvent   = NULL;
  fhitEventTarget= NULL;
  fhitEventECal= NULL;
  fhitEventPVeto= NULL;
  fhitEventEVeto= NULL;
  fhitEventHEPVeto= NULL;
  fhitEventSAC= NULL;
  fClCollTarget= NULL;
  fClCollECal= NULL;
  fClCollPVeto= NULL;
  fClCollEVeto= NULL;
  fClCollHEPVeto= NULL;
  fClCollSAC= NULL;*/

  fProcessingMode = processingMode;
  fVerbose        = verbosityFlag;
}
EventSelection::~EventSelection()
{
}


Bool_t EventSelection::InitSelection(TRecoEvent* evHeader, TRecoVObject* targetev, TTargetRecoBeam* targetcl, TRecoVObject* ecalev, TRecoVClusCollection* ecalcl, TRecoVObject* pvetoev, TRecoVClusCollection* pvetocl, TRecoVObject* evetoev, TRecoVClusCollection* evetocl, TRecoVObject* hepvetoev, TRecoVClusCollection* hepvetocl,TRecoVObject* sacev, TRecoVClusCollection* saccl)
{
  Bool_t retCode = 0;
  fRecoEvent = evHeader;

  fhitEventTarget = targetev;
  fClCollTarget = targetcl;

  fhitEventECal = ecalev;
  fClCollECal   = ecalcl;
  
  fhitEventPVeto = pvetoev;
  fClCollPVeto = pvetocl;

  fhitEventEVeto = evetoev;
  fClCollEVeto = evetocl;

  fhitEventHEPVeto = hepvetoev;
  fClCollHEPVeto = hepvetocl;

  fhitEventSAC = sacev;
  fClCollSAC = saccl;
  
  return retCode;
}


Bool_t EventSelection::InitHistosSelection()
{
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  std::string hname;
  
  int binX=11;   
  int minX=-0.5;
  int maxX=10.5;

  hname="NGammaGammaForEvent_TimeRequest"; 
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="NGammaGammaForEvent_TimeRequest_DeltaPhi10Degree"; 
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="NGammaGammaForEvent_TimeRequest_DeltaPhi10Degree_EnergyInterval_InvariantMassInterval"; 
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="NGammaGammaForEvent_TimeRequest_CoG2cm"; 
  hSvc->BookHisto(hname, binX, minX, maxX);
  
  binX=500;   
  minX=0;
  maxX=2000;
  int binY=40;
  int minY=0;
  int maxY=40;

  hname="AnnihilationGammaEcalGammaSac"; 
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_twoPhotonInTime3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi20Degree2Method";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi10Degree2Method";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi10Degree2Method_ThrEnergy";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi5Degree2Method";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi20Degree2Method_DeltaTheta";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi10Degree2Method_DeltaTheta";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi5Degree2Method_DeltaTheta";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns1cm_InDeltaPhi";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns1cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns2cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns2cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns2cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns3cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns3cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns3cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton3ns5cm"; 
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_twoPhotonInTime1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi20Degree2Method";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi10Degree2Method";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi5Degree2Method";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi20Degree2Method_DeltaTheta";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi10Degree2Method_DeltaTheta";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi5Degree2Method_DeltaTheta";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns1cm_InDeltaPhi";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns1cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns2cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns2cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns2cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns3cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns3cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns3cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_gravTwoPhoton1.5ns5cm"; 
  hSvc->BookHisto(hname, binX, minX, maxX);
  
  binX=601;   
  minX=-300.5;
  maxX=300.5;
  hname="ECal_xCoG_3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_yCoG_3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_y:xCog_3ns";
  hSvc->BookHisto2(hname, binX, minX, maxX, binX, minX, maxX);
  hname="ECal_xCoG_in3ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_yCoG_in3ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_ImpactParameter_3ns";
  hSvc->BookHisto(hname, binX, -0.5, maxX);
  hname="ECal_xCoG_1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_yCoG_1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_y:xCog_1.5ns";
  hSvc->BookHisto2(hname, binX, minX, maxX, binX, minX, maxX);
  hname="ECal_xCoG_in1.5ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_yCoG_in1.5ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_ImpactParameter_1.5ns";
  hSvc->BookHisto(hname, binX, -0.5, maxX);
  
  binX=101;   
  minX=-0.5;
  maxX=70.5;
  binY=70;   
  minY=-0.5;
  maxY=30.5;
  hname="InvariantMass_GInFiducialRegion_3ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMassCog_GInFiducialRegion_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="InvariantMass_GInFiducialRegion_1.5ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMassCog_GInFiducialRegion_1.5ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_InvariantMass_InDeltaPhi_3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi_3ns_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi20Degree2Method_3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi10Degree2Method_3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi5Degree2Method_3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi20Degree2Method_DeltaTheta_3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi10Degree2Method_DeltaTheta_3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi5Degree2Method_DeltaTheta_3ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi_3ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi_3ns1cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi_1.5ns_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi_1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi_1.5ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi_1.5ns1cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_3ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_CoGVsInvariantMassLorentz_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECal_InvariantMassLorentz_3ns1cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_3ns2cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_3ns2cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_3ns2cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_3ns3cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_3ns3cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  
  hname="ECal_InvariantMassLorentz_1.5ns1cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_CoGVsInvariantMassLorentz_1.5ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECal_InvariantMassLorentz_1.5ns1cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi20Degree2Method_1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi10Degree2Method_1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi5Degree2Method_1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi20Degree2Method_DeltaTheta_1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi10Degree2Method_DeltaTheta_1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECAL_InvariantMass_InDeltaPhi5Degree2Method_DeltaTheta_1.5ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_1.5ns2cm";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_1.5ns2cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_1.5ns2cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_1.5ns3cm_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="ECal_InvariantMassLorentz_1.5ns3cm_InDeltaPhi_withAngleCut";
  hSvc->BookHisto(hname, binX, minX, maxX);
  
  
  binX=501;   
  minX=-0.5;
  maxX=2000.5;
  binY=700;   
  minY=-0.5;
  maxY=0.2;
  
  hname="ECal_angleBetweenTwoPhotonIn3ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname ="ECal_angleBetweenTwoPhotonVSEnergyIn3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECal_angleBetweenTwoPhotonIn3ns2cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname ="ECal_angleBetweenTwoPhotonVSEnergyIn3ns2cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECal_angleBetweenTwoPhotonIn1.5ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname ="ECal_angleBetweenTwoPhotonVSEnergyIn1.5ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECal_angleBetweenTwoPhotonIn1.5ns2cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname ="ECal_angleBetweenTwoPhotonVSEnergyIn1.5ns2cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  
  binY=400;   
  minY=-300.5;
  maxY=300.5;
  
  hname="ECAL_XGamma1_3ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_XGamma2_3ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_YGamma1_3ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_YGamma2_3ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_XGamma1_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_XGamma2_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_YGamma1_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_YGamma2_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto(hname, binY, minY, maxY);
  
  hname="ECAL_XGamma1_1.5ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_XGamma2_1.5ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_YGamma1_1.5ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_YGamma2_1.5ns1cm";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_XGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_XGamma2_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_YGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_YGamma2_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto(hname, binY, minY, maxY);
  
  binX=501;   
  minX=-0.5;
  maxX=500.5;
  binY=200;   
  minY=-0.5;
  maxY=0.1;  
  hname="ECAL_EGamma2VSEGamma1_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binX, minX, maxX);
  hname="ECAL_Theta1VSEGamma1_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Theta2VSEGamma2_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Theta2VSTheta1_3ns1cm";
  hSvc->BookHisto2(hname, binY, minY, maxY, binY, minY, maxY);
  binY=500;   
  minY=-6.16;
  maxY=6.16; 
  hname="ECAL_Phi1VSEGamma1_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Phi2VSEGamma2_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Phi2VSPhi1_3ns1cm";
  hSvc->BookHisto2(hname, binY, minY, maxY, binY, minY, maxY);
  
  hname="ECAL_DeltaThetaDistributions_TwoPhoton3ns_InDeltaPhi20Degree2Method";
  hSvc->BookHisto(hname, binY, minY, maxY);
  hname="ECAL_DeltaPhiDistributions_TwoPhoton3ns_InDeltaTheta";
  hSvc->BookHisto(hname, binY, minY, maxY);
  
  hname="ECAL_EGamma2VSEGamma1_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binX, minX, maxX);
  binY=200;   
  minY=-0.5;
  maxY=0.1;
  hname="ECAL_Theta1VSEGamma1_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Theta2VSEGamma2_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Theta2VSTheta1_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binY, minY, maxY, binY, minY, maxY);
  binY=500;   
  minY=-6.16;
  maxY=6.16;
  hname="ECAL_Phi1VSEGamma1_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Phi2VSEGamma2_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Phi2VSPhi1_3ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binY, minY, maxY, binY, minY, maxY);
  
  binX=501;   
  minX=-0.5;
  maxX=500.5;
  binY=200;   
  minY=-0.5;
  maxY=0.1; 
  hname="ECAL_EGamma2VSEGamma1_1.5ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binX, minX, maxX);
  hname="ECAL_Theta1VSEGamma1_1.5ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Theta2VSEGamma2_1.5ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Theta2VSTheta1_1.5ns1cm";
  hSvc->BookHisto2(hname, binY, minY, maxY, binY, minY, maxY);
  binY=500;   
  minY=-6.16;
  maxY=6.16;
  hname="ECAL_Phi1VSEGamma1_1.5ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Phi2VSEGamma2_1.5ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Phi2VSPhi1_1.5ns1cm";
  hSvc->BookHisto2(hname, binY, minY, maxY, binY, minY, maxY);
  
  binY=200;   
  minY=-0.5;
  maxY=0.1;
  hname="ECAL_EGamma2VSEGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binX, minX, maxX);
  hname="ECAL_Theta1VSEGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Theta2VSEGamma2_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Theta2VSTheta1_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binY, minY, maxY, binY, minY, maxY);
  binY=500;   
  minY=-6.16;
  maxY=6.16;
  hname="ECAL_Phi1VSEGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Phi2VSEGamma2_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Phi2VSPhi1_1.5ns1cm_InInvariantMassRange";
  hSvc->BookHisto2(hname, binY, minY, maxY, binY, minY, maxY);
  
  binX=71;   
  minX=-0.5;
  maxX=30.5;
  binY=500;   
  minY=-6.16;
  maxY=6.16;
  hname="ECAL_Phi1VsInvariantMass_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Phi2VsInvariantMass_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  binY=200;   
  minY=-0.5;
  maxY=0.1; 
  hname="ECAL_Theta1VsInvariantMass_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  hname="ECAL_Theta2VsInvariantMass_3ns1cm";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
  
  
  binX=1001;   
  minX=-500.5;
  maxX=500.5;

  hname="DTimeECalSac";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="DTimeECalPVeto";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="DTimePVetoSac";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="DTimeCorrectPVetoSAC";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="DTimePVetoSACCh21";
  hSvc->BookHisto(hname, binX, minX, maxX);
  
  binX=101;   
  minX=-0.5;
  maxX=100.5;
  binY=700;   
  minY=-0.5;
  maxY=1400.5;
  hname="PVetoChIdClEnSAC";
  hSvc->BookHisto2(hname, binX, minX, maxX, binY, minY, maxY);
   
  
  binX=700;   
  minX=-0.5;
  maxX=1400.5;  
  hname="EnTotEvBremsstrhlungSACPVeto";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="SAC_ClEnergy_evNoBremsstrahlung";
  hSvc->BookHisto(hname, binX, minX, maxX);
  hname="SAC_evSel_SinglePhotonAnnihilationEnergy_TimeCoincidenceRequest2ns";
  hSvc->BookHisto(hname, binX, minX, maxX);
  
  
  return true;
}

Bool_t EventSelection::ProcessSelection()
{
  //Double_t AbsFactorScale=1.132;//EcalCalib_3
  //Double_t AbsFactorScale=1.277; //EcalCalib_2
  Double_t AbsFactorScale=1.;
  Bool_t retCode = 0;
  TRecoVCluster* ecalclu=NULL;
  TRecoVCluster* ecalclu2=NULL;
  TRecoVCluster* SACclu=NULL;
  TRecoVHit* sacHit;
  TRecoVHit* hit;
  TRecoVHit* hit2;
  TRecoVHit* targetHit;
  TRecoVCluster* SACclu2=NULL;
  TRecoVCluster* PVetoclu=NULL;
  TRecoVHit* pVetoHit;
  std::string hname;
  int loop=0;
  
  HistoSvc* hSvc =  HistoSvc::GetInstance();
 
  Int_t NClSAC = fClCollSAC->GetNElements();
  Int_t NClECal = fClCollECal->GetNElements();
  Int_t NClPVeto = fClCollPVeto->GetNElements();
  Int_t NHitsSac = fhitEventSAC->GetNHits();
  Int_t NHitsPVeto = fhitEventPVeto->GetNHits();
  
  for(int jpveto=0; jpveto<NHitsPVeto; jpveto++){
    pVetoHit=fhitEventPVeto->Hit(jpveto);
    Double_t pvetoTimeCorr=applyTimePVetoLinCorr((pVetoHit->GetChannelId()), pVetoHit->GetTime());
    for(int jsac=0; jsac<NHitsSac; jsac++){
      sacHit=fhitEventSAC->Hit(jsac);
      if(sacHit->GetChannelId()!=21) continue;
      hname="DTimePVetoSACCh21";
      hSvc->FillHisto(hname, (pvetoTimeCorr-sacHit->GetTime()), 1.);
      
    }
  }
  
  TVector3 pos1;
  TVector3 pos2;
  double dPhi = -999.;
  for (Int_t jecal=0; jecal<NClECal; ++jecal){
    ecalclu          = fClCollECal->Element(jecal);
    Double_t ClTECal = ecalclu->GetTime();
    Double_t EnClECal= ecalclu->GetEnergy()*AbsFactorScale;
    Int_t NGGInTheSameEventTime3ns=0;
    Int_t NGGInTheSameEventDeltaPhi10_3ns=0;
    Int_t NGGInTheSameEventDeltaPhi10_EnergyInterval_InvariantMassInterval_3ns=0;
    Int_t NGGInTheSameEventCoG2cm3ns=0;
    for(Int_t jecal2=jecal+1; jecal2<NClECal; jecal2++){
      ecalclu2 = fClCollECal->Element(jecal2);
      if(fabs(ecalclu->GetTime()-ecalclu2->GetTime())<3.){
        NGGInTheSameEventTime3ns++;
        hname="ECAL_twoPhotonInTime3ns";
        hSvc->FillHisto(hname,(ecalclu->GetEnergy()+ecalclu2->GetEnergy())*AbsFactorScale , 1.);
        pos1 = ecalclu->GetPosition();
        pos2 = ecalclu2->GetPosition();
        Double_t XWeighted=0.;
        Double_t YWeighted=0.;
        Double_t g1x=ecalclu->GetPosition().X();
        Double_t g1y=ecalclu->GetPosition().Y();
        Double_t g2x=ecalclu2->GetPosition().X();
        Double_t g2y=ecalclu2->GetPosition().Y();
        Double_t g1E=ecalclu->GetEnergy()*AbsFactorScale;
        Double_t g2E=ecalclu2->GetEnergy()*AbsFactorScale;
        XWeighted= (g1x*g1E+g2x*g2E)/(g1E+g2E);
        YWeighted= (g1y*g1E+g2y*g2E)/(g1E+g2E);
        
        hname="ECal_xCoG_3ns";
        hSvc->FillHisto(hname,XWeighted , 1.);
        hname="ECal_yCoG_3ns";
        hSvc->FillHisto(hname,YWeighted , 1.);
        hname="ECal_y:xCog_3ns";
        hSvc->FillHisto2(hname, XWeighted, YWeighted, 1.);
        
        
        Double_t CoG= sqrt(XWeighted*XWeighted+YWeighted*YWeighted);
        Double_t R_1 = sqrt(g1x*g1x+ g1y*g1y+3470*3470);
        Double_t Px_1 = g1E*g1x/ R_1;
        Double_t Py_1 = g1E*g1y/ R_1;
        Double_t Pz_1 = g1E*3470/ R_1;
        Double_t R_2 = sqrt(g2x*g2x+ g2y*g2y+3470*3470);
        Double_t Px_2 = g2E*g2x/ R_2;
        Double_t Py_2 = g2E*g2y/ R_2;
        Double_t Pz_2 = g2E*3470/ R_2;
         
        TLorentzVector P4g1F,P4g2F,SumP;
        P4g1F.SetPxPyPzE(Px_1,Py_1,Pz_1, g1E);
        P4g2F.SetPxPyPzE(Px_2,Py_2,Pz_2,g2E);
        SumP=P4g1F+P4g2F;
        Double_t InvariantMass = SumP.M();
        Double_t angleBetweenTwoPhoton = P4g1F.Angle(P4g2F.Vect());
         
        Double_t ImpactParameter = fabs(ecalclu->GetPosition().Y()-ecalclu->GetPosition().X()*((ecalclu2->GetPosition().Y()-ecalclu->GetPosition().Y())/(ecalclu2->GetPosition().X()-ecalclu->GetPosition().X())))/sqrt(1+((ecalclu2->GetPosition().Y()-ecalclu->GetPosition().Y())/(ecalclu2->GetPosition().X()-ecalclu->GetPosition().X()))*((ecalclu2->GetPosition().Y()-ecalclu->GetPosition().Y())/(ecalclu2->GetPosition().X()-ecalclu->GetPosition().X())));
        hname="ECAL_ImpactParameter_3ns";
        hSvc->FillHisto(hname, ImpactParameter, 1.);
        
        Double_t thetag1 = P4g1F.Theta();
        Double_t thetag2 = P4g2F.Theta(); 
        Double_t phig1 = P4g1F.Phi();
        Double_t phig2 = P4g2F.Phi();
        
        Bool_t InInvariantMassRange = false;
        if(InvariantMass>12. && InvariantMass< 30) InInvariantMassRange=true;
        
        Bool_t InFiducialRegion=false;
        if((fabs((g1x))>90. || fabs(g1y)>90.) && (fabs((g2x))>90. || fabs(g2y)>90. )) InFiducialRegion=true;
        
        Bool_t InEnergy=false;
        if(g1E>70 && g2E>70) InEnergy=true;
        
        Bool_t TotEnergyCut=false;
        if(g1E+g2E>300 && g1E+g2E<700 ) TotEnergyCut=true;
        
        Bool_t InDeltaPhi = false;
        Double_t distance = sqrt((g1x-g2x)*(g1x-g2x)+(g1y-g2y)*(g1y-g2y));
        if(/*distance >R_1 &&*/ (phig2*phig1<0 && (fabs(phig1-phig2)-3.14)<0.1) || (phig2*phig1>0 && (fabs(phig1+phig2)-3.14)< 0.1)) InDeltaPhi= true;
        //std::cout<< "DPhi " << fabs(phig1-phig2) << " bool "<< InDeltaPhi << std::endl;
        
        bool isPhySym = phiSymmetricalInECal(pos1, pos2, dPhi);
        Bool_t dPhiIn20Degree=false; //0.35 rad
        Bool_t dPhiIn10Degree=false; //0.17 rad
        Bool_t dPhiIn5Degree=false;  //0.087 rad
        if(fabs(dPhi-3.14)<0.35) dPhiIn20Degree=true;
        if(fabs(dPhi-3.14)<0.17) dPhiIn10Degree=true;
        if(fabs(dPhi-3.14)<0.087) dPhiIn5Degree=true;
        
        if (TotEnergyCut && InInvariantMassRange && dPhiIn10Degree){
        NGGInTheSameEventDeltaPhi10_EnergyInterval_InvariantMassInterval_3ns ++;
        }
        
        
        if(dPhiIn20Degree){
          HistoInDeltaPhi20DegreeSecondMethod3ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
           HistoInDeltaPhi20DegreeSecondMethod3nsDeltaTheta(g1E, g2E, InvariantMass);
           HistoDeltaTheta_InDeltaPhi20Interval(angleBetweenTwoPhoton);
           
         }
        }
        if(dPhiIn10Degree){
          NGGInTheSameEventDeltaPhi10_3ns++;
          HistoInDeltaPhi10DegreeSecondMethod3ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
           HistoInDeltaPhi10DegreeSecondMethod3nsDeltaTheta(g1E, g2E, InvariantMass);
           
          }
          if(InEnergy){
           HistoInDeltaPhi10DegreeSecondMethod3nsThrEnergy(g1E, g2E, InvariantMass);
          }
        }
        
        if(dPhiIn5Degree){
          HistoInDeltaPhi5DegreeSecondMethod3ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
           HistoInDeltaPhi5DegreeSecondMethod3nsDeltaTheta(g1E, g2E, InvariantMass);
           
         }
        }
        
        if(InDeltaPhi){                                             //there is an error maybe in this calculation
          HistoInDeltaPhi3ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
            HistoInDeltaPhi3nsDeltaTheta(g1E, g2E, InvariantMass);
          }
        }
        if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
         HistoDeltaPhi_InDeltaThetaInterval(dPhi);
        }
        if(fabs(XWeighted)<10. && fabs(YWeighted)<10.){
         HistoIn1cmCoG3ns(g1E,  g2E,  InvariantMass, XWeighted, YWeighted, angleBetweenTwoPhoton, phig1, phig2, thetag1, thetag2, g1x, g2x, g1y, g2y, CoG);
         if(dPhiIn10Degree){
          HistoIn1cmCoG3nsDeltaPhi(g1E, g2E, InvariantMass);
         }
         if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
           HistoIn1cmCoG3nsDeltaTheta(g1E, g2E, InvariantMass, InDeltaPhi);
           
         }
         if(InFiducialRegion){
            HistoIn1cmCoG3nsInFiducialRegion(g1E, g2E, InvariantMass, CoG);
         }
          
          
         if(InInvariantMassRange){
            HistoIn1cmCoG3nsInvariantMassRange( g1x, g2x, g1y, g2y, g1E, g2E, thetag1, thetag2, phig1, phig2);           
         }
        }
        
        
        if(fabs(XWeighted)<20. && fabs(YWeighted)<20.){
          HistoIn2cmCoG3ns(g1E, g2E, InvariantMass, angleBetweenTwoPhoton);
          NGGInTheSameEventCoG2cm3ns++;
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
            HistoIn2cmCoG3nsDeltaTheta(g1E, g2E, InvariantMass);
            if(dPhiIn10Degree){
            HistoIn2cmCoG3nsDeltaThetaDeltaPhi(g1E, g2E, InvariantMass);
            }
          }
        }
        
        if(fabs(XWeighted)<30. && fabs(YWeighted)<30.){
          HistoIn3cmCoG3ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
            HistoIn3cmCoG3nsDeltaTheta(g1E, g2E, InvariantMass);
            if(dPhiIn10Degree){
              HistoIn3cmCoG3nsDeltaThetaDeltaPhi(g1E, g2E, InvariantMass);
            }
          }
        }
        
        if(fabs(XWeighted)<50. && fabs(YWeighted)<50.){
         HistoIn5cmCoG3ns(g1E, g2E, InvariantMass);
        }
      }
   
      if(fabs(ecalclu->GetTime()-ecalclu2->GetTime())<1.5){
        hname="ECAL_twoPhotonInTime1.5ns";
        hSvc->FillHisto(hname,(ecalclu->GetEnergy()+ecalclu2->GetEnergy())*AbsFactorScale , 1.);
        Double_t XWeighted=0.;
        Double_t YWeighted=0.;
        pos1 = ecalclu->GetPosition();
        pos2 = ecalclu2->GetPosition();
        Double_t g1x=ecalclu->GetPosition().X();
        Double_t g1y=ecalclu->GetPosition().Y();
        Double_t g2x=ecalclu2->GetPosition().X();
        Double_t g2y=ecalclu2->GetPosition().Y();
        Double_t g1E=ecalclu->GetEnergy()*AbsFactorScale;
        Double_t g2E=ecalclu2->GetEnergy()*AbsFactorScale;
        XWeighted= (g1x*g1E+g2x*g2E)/(g1E+g2E);
        YWeighted= (g1y*g1E+g2y*g2E)/(g1E+g2E);
        
        hname="ECal_xCoG_1.5ns";
        hSvc->FillHisto(hname,XWeighted , 1.);
        hname="ECal_yCoG_1.5ns";
        hSvc->FillHisto(hname,YWeighted , 1.);
        hname="ECal_y:xCog_1.5ns";
        hSvc->FillHisto2(hname, XWeighted, YWeighted, 1.);
        
        Double_t CoG= sqrt(XWeighted*XWeighted+YWeighted*YWeighted);
        Double_t R_1 = sqrt(g1x*g1x+ g1y*g1y+3470*3470);
        Double_t Px_1 = g1E*g1x/ R_1;
        Double_t Py_1 = g1E*g1y/ R_1;
        Double_t Pz_1 = g1E*3470/ R_1;
        Double_t R_2 = sqrt(g2x*g2x+ g2y*g2y+3470*3470);
        Double_t Px_2 = g2E*g2x/ R_2;
        Double_t Py_2 = g2E*g2y/ R_2;
        Double_t Pz_2 = g2E*3470/ R_2;
         
        TLorentzVector P4g1F,P4g2F,SumP;
        P4g1F.SetPxPyPzE(Px_1,Py_1,Pz_1, g1E);
        P4g2F.SetPxPyPzE(Px_2,Py_2,Pz_2,g2E);
        SumP=P4g1F+P4g2F;
        Double_t InvariantMass = SumP.M();
        Double_t angleBetweenTwoPhoton = P4g1F.Angle(P4g2F.Vect());
         
        Double_t ImpactParameter = fabs(ecalclu->GetPosition().Y()-ecalclu->GetPosition().X()*((ecalclu2->GetPosition().Y()-ecalclu->GetPosition().Y())/(ecalclu2->GetPosition().X()-ecalclu->GetPosition().X())))/sqrt(1+((ecalclu2->GetPosition().Y()-ecalclu->GetPosition().Y())/(ecalclu2->GetPosition().X()-ecalclu->GetPosition().X()))*((ecalclu2->GetPosition().Y()-ecalclu->GetPosition().Y())/(ecalclu2->GetPosition().X()-ecalclu->GetPosition().X())));
        hname="ECAL_ImpactParameter_1.5ns";
         hSvc->FillHisto(hname, ImpactParameter, 1.);
         
        Double_t thetag1 = P4g1F.Theta();
        Double_t thetag2 = P4g2F.Theta(); 
        Double_t phig1 = P4g1F.Phi();
        Double_t phig2 = P4g2F.Phi();
         
        Bool_t InFiducialRegion=false;
        if((fabs((g1x))>90. || fabs(g1y)>90.) && (fabs((g2x))>90. || fabs(g2y)>90. )) InFiducialRegion=true;
        
        Bool_t InInvariantMassRange = false;
        if(InvariantMass>12. && InvariantMass< 20) InInvariantMassRange=true;
        
        Bool_t InDeltaPhi = false; 
        Double_t distance = sqrt((g1x-g2x)*(g1x-g2x)+(g1y-g2y)*(g1y-g2y));
        if(/*distance >R_1 &&*/ (phig2*phig1<0 && (fabs(phig1-phig2)-3.14)<0.1) || (phig2*phig1>0 && (fabs(phig1+phig2)-3.14)< 0.1)) InDeltaPhi= true;
        
        bool isPhySym = phiSymmetricalInECal(pos1, pos2, dPhi);
        Bool_t dPhiIn20Degree=false; //0.35 rad
        Bool_t dPhiIn10Degree=false; //0.17 rad
        Bool_t dPhiIn5Degree=false;  //0.087 rad
        if(fabs(dPhi-3.14)<0.35) dPhiIn20Degree=true;
        if(fabs(dPhi-3.14)<0.17) dPhiIn10Degree=true;
        if(fabs(dPhi-3.14)<0.087) dPhiIn5Degree=true;
        
        if(dPhiIn20Degree){
          HistoInDeltaPhi20DegreeSecondMethod1_5ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
           HistoInDeltaPhi20DegreeSecondMethod1_5nsDeltaTheta(g1E, g2E, InvariantMass);
           
         }
        }
        if(dPhiIn10Degree){
          HistoInDeltaPhi10DegreeSecondMethod1_5ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
           HistoInDeltaPhi10DegreeSecondMethod1_5nsDeltaTheta(g1E, g2E, InvariantMass);
           
         }
        }
        if(dPhiIn5Degree){
          HistoInDeltaPhi5DegreeSecondMethod1_5ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
           HistoInDeltaPhi5DegreeSecondMethod1_5nsDeltaTheta(g1E, g2E, InvariantMass);
           
         }
        }
        
        if(InDeltaPhi){                                                        //maybe there is an error in this calculation
          HistoInDeltaPhi1_5ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
            HistoInDeltaPhi1_5nsDeltaTheta(g1E, g2E, InvariantMass);
          }
        }
         
        if(fabs(XWeighted)<10. && fabs(YWeighted)<10.){
         HistoIn1cmCoG1_5ns(g1E,  g2E,  InvariantMass, XWeighted, YWeighted, angleBetweenTwoPhoton, phig1, phig2, thetag1, thetag2, g1x, g2x, g1y, g2y,CoG);
         if(dPhiIn10Degree){
          HistoIn1cmCoG1_5nsDeltaPhi(g1E, g2E, InvariantMass);
         }
         if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
           HistoIn1cmCoG1_5nsDeltaTheta(g1E, g2E, InvariantMass, dPhiIn10Degree);
           
         }
         if(InFiducialRegion){
            HistoIn1cmCoG1_5nsInFiducialRegion(g1E, g2E, InvariantMass, CoG);
         }
          
          
         if(InInvariantMassRange){
            HistoIn1cmCoG1_5nsInvariantMassRange( g1x, g2x, g1y, g2y, g1E, g2E, thetag1, thetag2, phig1, phig2);           
         }
        }
        
        
        if(fabs(XWeighted)<20. && fabs(YWeighted)<20.){
          HistoIn2cmCoG1_5ns(g1E, g2E, InvariantMass, angleBetweenTwoPhoton);
          
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
            HistoIn2cmCoG1_5nsDeltaTheta(g1E, g2E, InvariantMass);
            if(dPhiIn10Degree){
            HistoIn2cmCoG1_5nsDeltaThetaDeltaPhi(g1E, g2E, InvariantMass);
            }
          }
        }
        
        if(fabs(XWeighted)<30. && fabs(YWeighted)<30.){
          HistoIn3cmCoG1_5ns(g1E, g2E, InvariantMass);
          if(angleBetweenTwoPhoton>0.08 && angleBetweenTwoPhoton<0.12){
            HistoIn3cmCoG1_5nsDeltaTheta(g1E, g2E, InvariantMass);
            if(dPhiIn10Degree){
              HistoIn3cmCoG1_5nsDeltaThetaDeltaPhi(g1E, g2E, InvariantMass);
            }
          }
        }
        
        if(fabs(XWeighted)<50. && fabs(YWeighted)<50.){
         HistoIn5cmCoG1_5ns(g1E, g2E, InvariantMass);
        }
   }
    
 }
  hname="NGammaGammaForEvent_TimeRequest"; 
  hSvc->FillHisto(hname,NGGInTheSameEventTime3ns , 1.);
  hname="NGammaGammaForEvent_TimeRequest_DeltaPhi10Degree"; 
  hSvc->FillHisto(hname,NGGInTheSameEventDeltaPhi10_3ns , 1.);
  hname="NGammaGammaForEvent_TimeRequest_DeltaPhi10Degree_EnergyInterval_InvariantMassInterval"; 
  hSvc->FillHisto(hname,NGGInTheSameEventDeltaPhi10_EnergyInterval_InvariantMassInterval_3ns , 1.);
  hname="NGammaGammaForEvent_TimeRequest_CoG2cm";
  hSvc->FillHisto(hname,NGGInTheSameEventCoG2cm3ns , 1.);

  }
   return retCode;
}

Double_t EventSelection::applyTimePVetoLinCorr(Double_t  xChId, Double_t xTime)
{
  return xTime - (32.9 + 9.*(xChId - 13.)/65.);
}

Bool_t EventSelection::phiSymmetricalInECal(TVector3 P1, TVector3 P2,  double& distPhi)
{
 distPhi = -999.;
 //distR   = -999.;
 //b       = -999.;
 P1.SetZ(0.);
 P2.SetZ(0.);
 TVector3 Pb = P2-P1;
 double impactPar = (P1.Cross(Pb)).Perp()/Pb.Perp();
 //std::cout<<" P1.X, Y "<<P1.X()<<" "<<P1.Y()<<std::endl;
 //std::cout<<" P2.X, Y "<<P2.X()<<" "<<P2.Y()<<std::endl;
 double impPar = (P1.X()*Pb.Y()-P2.X()*Pb.Y())/Pb.Perp();


 double scalarP = P1.Dot(P2);
 double cosphi = scalarP/P1.Perp()/P2.Perp();
 double dPhi = acos(cosphi);

 distPhi = dPhi;
 //distR   = Pb.Perp();
 //b = impPar;
 //std::cout<<"dPhi = "<<distPhi<<" b = "<<b<<" impPar "<<impPar<<std::endl;

 //if (cosphi<-0.985 && fabs(b)<10.) return true;
 if (cosphi<-0.985) return true; //phi > 170.06 degree
 return false;

}






void EventSelection::HistoInDeltaPhi3ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi_3ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}

void EventSelection::HistoInDeltaPhi3nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi_3ns_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}

void EventSelection::HistoIn1cmCoG3ns(Double_t g1E, Double_t g2E, Double_t InvariantMass,Double_t XWeighted,Double_t YWeighted,Double_t angleBetweenTwoPhoton,Double_t phig1,Double_t phig2,Double_t thetag1,Double_t thetag2,Double_t g1x,Double_t g2x,Double_t g1y,Double_t g2y , Double_t CoG ){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns1cm";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_xCoG_in3ns1cm";
  hSvc->FillHisto(hname,XWeighted , 1.);
  hname="ECal_yCoG_in3ns1cm";
  hSvc->FillHisto(hname,YWeighted , 1.);
  hname="ECal_InvariantMassLorentz_3ns1cm";
  hSvc->FillHisto(hname, InvariantMass, 1.);
  hname="ECal_CoGVsInvariantMassLorentz_3ns1cm";
  hSvc->FillHisto2(hname, InvariantMass, CoG,  1.);
  hname="ECal_angleBetweenTwoPhotonIn3ns1cm";
  hSvc->FillHisto(hname, angleBetweenTwoPhoton, 1.);
  hname ="ECal_angleBetweenTwoPhotonVSEnergyIn3ns1cm";
  hSvc->FillHisto2(hname, g1E+g2E,  angleBetweenTwoPhoton, 1.);
  hname="ECAL_Phi1VsInvariantMass_3ns1cm";
  hSvc->FillHisto2(hname, InvariantMass,  phig1, 1.);
  hname="ECAL_Phi2VsInvariantMass_3ns1cm";
  hSvc->FillHisto2(hname, InvariantMass,  phig2, 1.);
  hname="ECAL_Theta1VsInvariantMass_3ns1cm";
  hSvc->FillHisto2(hname, InvariantMass,  thetag1, 1.);
  hname="ECAL_Theta2VsInvariantMass_3ns1cm";
  hSvc->FillHisto2(hname, InvariantMass,  thetag1, 1.);
   
  hname="ECAL_XGamma1_3ns1cm";
  hSvc->FillHisto(hname, g1x, 1.);
  hname="ECAL_XGamma2_3ns1cm";
  hSvc->FillHisto(hname, g2x, 1.);
  hname="ECAL_YGamma1_3ns1cm";
  hSvc->FillHisto(hname, g1y, 1.);
  hname="ECAL_YGamma2_3ns1cm";
  hSvc->FillHisto(hname, g2y, 1.);
   
  hname="ECAL_EGamma2VSEGamma1_3ns1cm";
  hSvc->FillHisto2(hname, g1E , g2E , 1.);
  hname="ECAL_Theta1VSEGamma1_3ns1cm";
  hSvc->FillHisto2(hname, g1E , thetag1 , 1.);
  hname="ECAL_Theta2VSEGamma2_3ns1cm";
  hSvc->FillHisto2(hname, g2E , thetag2 , 1.);
  hname="ECAL_Theta2VSTheta1_3ns1cm";
  hSvc->FillHisto2(hname,  thetag1 , thetag2, 1.);
  hname="ECAL_Phi1VSEGamma1_3ns1cm";
  hSvc->FillHisto2(hname, g1E , phig1 , 1.);
  hname="ECAL_Phi2VSEGamma2_3ns1cm";
  hSvc->FillHisto2(hname, g2E , phig2 , 1.);
  hname="ECAL_Phi2VSPhi1_3ns1cm";
  hSvc->FillHisto2(hname,  phig1 , phig2, 1.);
   
}


void EventSelection::HistoIn1cmCoG3nsDeltaPhi(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns1cm_InDeltaPhi";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi_3ns1cm";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn1cmCoG3nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass, Bool_t InDeltaPhi){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECal_InvariantMassLorentz_3ns1cm_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
  if(InDeltaPhi){
    hname="ECAL_gravTwoPhoton3ns1cm_InDeltaPhi_withAngleCut";
    hSvc->FillHisto(hname,g1E+g2E , 1.);
    hname="ECAL_InvariantMass_InDeltaPhi_3ns1cm_withAngleCut";
    hSvc->FillHisto(hname, InvariantMass, 1.);
  }
   
}


void EventSelection::HistoIn1cmCoG3nsInFiducialRegion(Double_t g1E, Double_t g2E, Double_t InvariantMass, Double_t CoG){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_InvariantMassCog_GInFiducialRegion_3ns1cm";
  hSvc->FillHisto2(hname, InvariantMass, CoG , 1.);
  hname="InvariantMass_GInFiducialRegion_3ns1cm";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn1cmCoG3nsInvariantMassRange(Double_t g1E, Double_t g2E,Double_t g1x, Double_t g2x, Double_t g1y, Double_t g2y, Double_t thetag1, Double_t thetag2, Double_t phig1, Double_t phig2){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_XGamma1_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto(hname, g1x, 1.);
  hname="ECAL_XGamma2_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto(hname, g2x, 1.);
  hname="ECAL_YGamma1_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto(hname, g1y, 1.);
  hname="ECAL_YGamma2_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto(hname, g2y, 1.);
  hname="ECAL_EGamma2VSEGamma1_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g1E , g2E , 1.);
  hname="ECAL_Theta1VSEGamma1_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g1E , thetag1 , 1.);
  hname="ECAL_Theta2VSEGamma2_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g2E , thetag2 , 1.);
  hname="ECAL_Theta2VSTheta1_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname,  thetag1 , thetag2, 1.);
  hname="ECAL_Phi1VSEGamma1_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g1E , phig1 , 1.);
  hname="ECAL_Phi2VSEGamma2_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g2E , phig2 , 1.);
  hname="ECAL_Phi2VSPhi1_3ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname,  phig1 , phig2, 1.);
   
}


void EventSelection::HistoIn2cmCoG3ns(Double_t g1E, Double_t g2E, Double_t InvariantMass, Double_t angleBetweenTwoPhoton){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns2cm";
  hSvc->FillHisto(hname,g1E+g2E , 1.);      
  hname="ECal_InvariantMassLorentz_3ns2cm";
  hSvc->FillHisto(hname, InvariantMass, 1.);
  hname="ECal_angleBetweenTwoPhotonIn3ns2cm";
  hSvc->FillHisto(hname, angleBetweenTwoPhoton, 1.);
  hname ="ECal_angleBetweenTwoPhotonVSEnergyIn3ns2cm";
  hSvc->FillHisto2(hname, g1E+g2E,  angleBetweenTwoPhoton, 1.);
   
}


void EventSelection::HistoIn2cmCoG3nsDeltaThetaDeltaPhi(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns2cm_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_InvariantMassLorentz_3ns2cm_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn2cmCoG3nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns2cm_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_InvariantMassLorentz_3ns2cm_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn3cmCoG3ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns3cm";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
   
}


void EventSelection::HistoIn3cmCoG3nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns3cm_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_InvariantMassLorentz_3ns3cm_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}

void EventSelection::HistoIn3cmCoG3nsDeltaThetaDeltaPhi(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns3cm_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_InvariantMassLorentz_3ns3cm_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn5cmCoG3ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns5cm";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
   
}

void EventSelection::HistoInDeltaPhi20DegreeSecondMethod3ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi20Degree2Method";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi20Degree2Method_3ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi10DegreeSecondMethod3ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi10Degree2Method";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi10Degree2Method_3ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi5DegreeSecondMethod3ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi5Degree2Method";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi5Degree2Method_3ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi20DegreeSecondMethod3nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi20Degree2Method_DeltaTheta";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi20Degree2Method_DeltaTheta_3ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi10DegreeSecondMethod3nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi10Degree2Method_DeltaTheta";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi10Degree2Method_DeltaTheta_3ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi5DegreeSecondMethod3nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi5Degree2Method_DeltaTheta";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi5Degree2Method_DeltaTheta_3ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi10DegreeSecondMethod3nsThrEnergy(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton3ns_InDeltaPhi10Degree2Method_ThrEnergy";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
 // hname="ECAL_InvariantMass_InDeltaPhi10Degree2Method_3ns_ThrEnergy70MeV";
 // hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoDeltaTheta_InDeltaPhi20Interval(Double_t angleBetweenTwoPhoton){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_DeltaThetaDistributions_TwoPhoton3ns_InDeltaPhi20Degree2Method";
  hSvc->FillHisto(hname, angleBetweenTwoPhoton , 1.);
}

void EventSelection::HistoDeltaPhi_InDeltaThetaInterval(Double_t dphi){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_DeltaPhiDistributions_TwoPhoton3ns_InDeltaTheta";
  hSvc->FillHisto(hname,dphi , 1.);
}




















void EventSelection::HistoInDeltaPhi1_5ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi_1.5ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}

void EventSelection::HistoInDeltaPhi1_5nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi_1.5ns_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}

void EventSelection::HistoIn1cmCoG1_5ns(Double_t g1E, Double_t g2E, Double_t InvariantMass,Double_t XWeighted,Double_t YWeighted,Double_t angleBetweenTwoPhoton,Double_t phig1,Double_t phig2,Double_t thetag1,Double_t thetag2,Double_t g1x,Double_t g2x,Double_t g1y,Double_t g2y , Double_t CoG){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns1cm";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_xCoG_in1.5ns1cm";
  hSvc->FillHisto(hname,XWeighted , 1.);
  hname="ECal_yCoG_in1.5ns1cm";
  hSvc->FillHisto(hname,YWeighted , 1.);
  hname="ECal_InvariantMassLorentz_1.5ns1cm";
  hSvc->FillHisto(hname, InvariantMass, 1.);
  hname="ECal_CoGVsInvariantMassLorentz_1.5ns1cm";
  hSvc->FillHisto2(hname, InvariantMass, CoG,  1.);
  hname="ECal_angleBetweenTwoPhotonIn1.5ns1cm";
  hSvc->FillHisto(hname, angleBetweenTwoPhoton, 1.);
  hname ="ECal_angleBetweenTwoPhotonVSEnergyIn1.5ns1cm";
  hSvc->FillHisto2(hname, g1E+g2E,  angleBetweenTwoPhoton, 1.);
  //hname="ECAL_Phi1VsInvariantMass_1.5ns1cm";
  //hSvc->FillHisto2(hname, InvariantMass,  phig1, 1.);
  //hname="ECAL_Phi2VsInvariantMass_1.5ns1cm";
  //hSvc->FillHisto2(hname, InvariantMass,  phig2, 1.);
  //hname="ECAL_Theta1VsInvariantMass_1.5ns1cm";
  //hSvc->FillHisto2(hname, InvariantMass,  thetag1, 1.);
  //hname="ECAL_Theta2VsInvariantMass_1.5ns1cm";
  //hSvc->FillHisto2(hname, InvariantMass,  thetag1, 1.);
   
  hname="ECAL_XGamma1_1.5ns1cm";
  hSvc->FillHisto(hname, g1x, 1.);
  hname="ECAL_XGamma2_1.5ns1cm";
  hSvc->FillHisto(hname, g2x, 1.);
  hname="ECAL_YGamma1_1.5ns1cm";
  hSvc->FillHisto(hname, g1y, 1.);
  hname="ECAL_YGamma2_1.5ns1cm";
  hSvc->FillHisto(hname, g2y, 1.);
   
  hname="ECAL_EGamma2VSEGamma1_1.5ns1cm";
  hSvc->FillHisto2(hname, g1E , g2E , 1.);
  hname="ECAL_Theta1VSEGamma1_1.5ns1cm";
  hSvc->FillHisto2(hname, g1E , thetag1 , 1.);
  hname="ECAL_Theta2VSEGamma2_1.5ns1cm";
  hSvc->FillHisto2(hname, g2E , thetag2 , 1.);
  hname="ECAL_Theta2VSTheta1_1.5ns1cm";
  hSvc->FillHisto2(hname,  thetag1 , thetag2, 1.);
  hname="ECAL_Phi1VSEGamma1_1.5ns1cm";
  hSvc->FillHisto2(hname, g1E , phig1 , 1.);
  hname="ECAL_Phi2VSEGamma2_1.5ns1cm";
  hSvc->FillHisto2(hname, g2E , phig2 , 1.);
  hname="ECAL_Phi2VSPhi1_1.5ns1cm";
  hSvc->FillHisto2(hname,  phig1 , phig2, 1.);
   
}


void EventSelection::HistoIn1cmCoG1_5nsDeltaPhi(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns1cm_InDeltaPhi";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi_1.5ns1cm";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn1cmCoG1_5nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass, Bool_t InDeltaPhi){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECal_InvariantMassLorentz_1.5ns1cm_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
  if(InDeltaPhi){
    hname="ECAL_gravTwoPhoton1.5ns1cm_InDeltaPhi_withAngleCut";
    hSvc->FillHisto(hname,g1E+g2E , 1.);
    hname="ECAL_InvariantMass_InDeltaPhi_1.5ns1cm_withAngleCut";
    hSvc->FillHisto(hname, InvariantMass, 1.);
  }
   
}


void EventSelection::HistoIn1cmCoG1_5nsInFiducialRegion(Double_t g1E, Double_t g2E, Double_t InvariantMass, Double_t CoG){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_InvariantMassCog_GInFiducialRegion_1.5ns1cm";
  hSvc->FillHisto2(hname, InvariantMass, CoG , 1.);
  hname="InvariantMass_GInFiducialRegion_1.5ns1cm";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn1cmCoG1_5nsInvariantMassRange(Double_t g1E, Double_t g2E,Double_t g1x, Double_t g2x, Double_t g1y, Double_t g2y, Double_t thetag1, Double_t thetag2, Double_t phig1, Double_t phig2){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_XGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto(hname, g1x, 1.);
  hname="ECAL_XGamma2_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto(hname, g2x, 1.);
  hname="ECAL_YGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto(hname, g1y, 1.);
  hname="ECAL_YGamma2_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto(hname, g2y, 1.);
  hname="ECAL_EGamma2VSEGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g1E , g2E , 1.);
  hname="ECAL_Theta1VSEGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g1E , thetag1 , 1.);
  hname="ECAL_Theta2VSEGamma2_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g2E , thetag2 , 1.);
  hname="ECAL_Theta2VSTheta1_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname,  thetag1 , thetag2, 1.);
  hname="ECAL_Phi1VSEGamma1_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g1E , phig1 , 1.);
  hname="ECAL_Phi2VSEGamma2_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname, g2E , phig2 , 1.);
  hname="ECAL_Phi2VSPhi1_1.5ns1cm_InInvariantMassRange";
  hSvc->FillHisto2(hname,  phig1 , phig2, 1.);
   
}


void EventSelection::HistoIn2cmCoG1_5ns(Double_t g1E, Double_t g2E, Double_t InvariantMass, Double_t angleBetweenTwoPhoton){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns2cm";
  hSvc->FillHisto(hname,g1E+g2E , 1.);      
  hname="ECal_InvariantMassLorentz_1.5ns2cm";
  hSvc->FillHisto(hname, InvariantMass, 1.);
  hname="ECal_angleBetweenTwoPhotonIn1.5ns2cm";
  hSvc->FillHisto(hname, angleBetweenTwoPhoton, 1.);
  hname ="ECal_angleBetweenTwoPhotonVSEnergyIn1.5ns2cm";
  hSvc->FillHisto2(hname, g1E+g2E,  angleBetweenTwoPhoton, 1.);
   
}


void EventSelection::HistoIn2cmCoG1_5nsDeltaThetaDeltaPhi(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns2cm_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_InvariantMassLorentz_1.5ns2cm_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn2cmCoG1_5nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns2cm_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_InvariantMassLorentz_1.5ns2cm_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn3cmCoG1_5ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns3cm";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
   
}


void EventSelection::HistoIn3cmCoG1_5nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns3cm_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_InvariantMassLorentz_1.5ns3cm_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}

void EventSelection::HistoIn3cmCoG1_5nsDeltaThetaDeltaPhi(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns3cm_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECal_InvariantMassLorentz_1.5ns3cm_InDeltaPhi_withAngleCut";
  hSvc->FillHisto(hname, InvariantMass, 1.);
   
}


void EventSelection::HistoIn5cmCoG1_5ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns5cm";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
   
}


void EventSelection::HistoInDeltaPhi20DegreeSecondMethod1_5ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi20Degree2Method";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi20Degree2Method_1.5ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi10DegreeSecondMethod1_5ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi10Degree2Method";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi10Degree2Method_1.5ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi5DegreeSecondMethod1_5ns(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi5Degree2Method";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi5Degree2Method_1.5ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi20DegreeSecondMethod1_5nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi20Degree2Method_DeltaTheta";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi20Degree2Method_DeltaTheta_1.5ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi10DegreeSecondMethod1_5nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi10Degree2Method_DeltaTheta";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi10Degree2Method_DeltaTheta_1.5ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

void EventSelection::HistoInDeltaPhi5DegreeSecondMethod1_5nsDeltaTheta(Double_t g1E, Double_t g2E, Double_t InvariantMass){
  std::string hname;
  HistoSvc* hSvc =  HistoSvc::GetInstance();
  hname="ECAL_gravTwoPhoton1.5ns_InDeltaPhi5Degree2Method_DeltaTheta";
  hSvc->FillHisto(hname,g1E+g2E , 1.);
  hname="ECAL_InvariantMass_InDeltaPhi5Degree2Method_DeltaTheta_1.5ns";
  hSvc->FillHisto(hname, InvariantMass, 1.);
}

