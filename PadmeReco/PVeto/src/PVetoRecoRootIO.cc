#include "PVetoRecoRootIO.hh"
#include "RecoVRootIO.hh"

#include "TPVetoRecoEvent.hh"
#include "PVetoReconstruction.hh"
#include "TPVetoClusCollection.hh"
//#include "TRecoVHit.hh"

#include "TString.h"
#include "TVector3.h"
#include "TProcessID.h"
#include <stdio.h>
#include "Riostream.h"


PVetoRecoRootIO::PVetoRecoRootIO() 
  : RecoVRootIO(TString("PVeto"))
{
  fEvent = new TPVetoRecoEvent();
  fClusColl = new TPVetoClusCollection();
  //  fClusColl = new TRecoVClusCollection(TRecoVCluster::Class());

  TTree::SetBranchStyle(fBranchStyle);

  fEnabled = true;
  //  fHitsEnabled = true;
  std::cout << "PVetoRecoRootIO: Initialized" << std::endl;

}
PVetoRecoRootIO::~PVetoRecoRootIO()
{;}

