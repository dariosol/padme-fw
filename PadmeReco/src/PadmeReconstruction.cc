#include "PadmeReconstruction.hh"

#include "TPadmeRun.hh"
#include "TRawEvent.hh"
#include "TMCEvent.hh"

#include "TTargetMCEvent.hh"
#include "TEVetoMCEvent.hh"
#include "TPVetoMCEvent.hh"
#include "THEPVetoMCEvent.hh"
#include "TECalMCEvent.hh"
#include "TSACMCEvent.hh"
#include "TTPixMCEvent.hh"

#include "TTargetRecoEvent.hh"
#include "TEVetoRecoEvent.hh"
#include "TPVetoRecoEvent.hh"
#include "THEPVetoRecoEvent.hh"
#include "TECalRecoEvent.hh"
#include "TSACRecoEvent.hh"
//#include "TTPixRecoEvent.hh"

#include "TargetReconstruction.hh"
#include "EVetoReconstruction.hh"
#include "PVetoReconstruction.hh"
#include "HEPVetoReconstruction.hh"
#include "ECalReconstruction.hh"
#include "SACReconstruction.hh"
#include "TPixReconstruction.hh"

#include "ECalParameters.hh"

#include "RecoRootIOManager.hh"

PadmeReconstruction::PadmeReconstruction(TObjArray* InputFileNameList, TString ConfFileName, TFile* OutputFile, Int_t NEvt, UInt_t Seed) :
  PadmeVReconstruction(OutputFile,"Padme",ConfFileName),fInputFileNameList(InputFileNameList), fHistoFile(OutputFile)
{

  // Input event structures will be allocated if corresponding branch exists
  fMCEvent        = 0;
  fTargetMCEvent  = 0;
  fEVetoMCEvent   = 0;
  fPVetoMCEvent   = 0;
  fHEPVetoMCEvent = 0;
  fECalMCEvent    = 0;
  fSACMCEvent     = 0;
  fTPixMCEvent    = 0;

  fRawEvent       = 0;
  
  fRecoEvent        = 0;
  fTargetRecoEvent  = 0;
  fEVetoRecoEvent   = 0;
  fPVetoRecoEvent   = 0;
  fHEPVetoRecoEvent = 0;
  fECalRecoEvent    = 0;
  fSACRecoEvent     = 0;
  fTPixRecoEvent    = 0;
  

  InitLibraries();
  Init(NEvt,Seed);

}

PadmeReconstruction::~PadmeReconstruction()
{
  for (UInt_t iLib = 0; iLib < fRecoLibrary.size(); iLib++) {
    delete fRecoLibrary[iLib];
  }
}

void PadmeReconstruction::InitLibraries()
{
  TString dummyConfFile = "pippo.conf";
  fRecoLibrary.push_back(new EVetoReconstruction  (fHistoFile,"config/EVeto.cfg"));
  fRecoLibrary.push_back(new PVetoReconstruction  (fHistoFile,"config/PVeto.cfg"));
  fRecoLibrary.push_back(new HEPVetoReconstruction(fHistoFile,"config/HEPVeto.cfg"));
  fRecoLibrary.push_back(new ECalReconstruction   (fHistoFile,"config/ECal.cfg"));
  fRecoLibrary.push_back(new SACReconstruction    (fHistoFile,"config/SAC.cfg"));
  fRecoLibrary.push_back(new TPixReconstruction   (fHistoFile,"config/TPix.cfg"));
  fRecoLibrary.push_back(new TargetReconstruction (fHistoFile,"config/Target.cfg"));
}

void PadmeReconstruction::InitDetectorsInfo()
{

  std::cout << "PadmeReconstruction: Initializing" << std::endl;

  fMainReco = this; //init PadmeReconstruction main reco as itself
  if (FindReco("Target"))  ((TargetReconstruction*)  FindReco("Target")) ->Init(this);
  if (FindReco("EVeto"))   ((EVetoReconstruction*)   FindReco("EVeto"))  ->Init(this);
  if (FindReco("PVeto"))   ((PVetoReconstruction*)   FindReco("PVeto"))  ->Init(this);
  if (FindReco("HEPVeto")) ((HEPVetoReconstruction*) FindReco("HEPVeto"))->Init(this);
  if (FindReco("ECal"))    ((ECalReconstruction*)    FindReco("ECal"))   ->Init(this);
  if (FindReco("SAC"))     ((SACReconstruction*)     FindReco("SAC"))    ->Init(this);
  if (FindReco("TPix"))    ((TPixReconstruction*)    FindReco("TPix"))   ->Init(this);
}

void PadmeReconstruction::Init(Int_t NEvt, UInt_t Seed)
{

  //gRandom->SetSeed(Seed);
  fNEvt = NEvt;

  TTree::SetMaxTreeSize(190000000000);

  // Show run information
  TString runTree = "Runs";
  TChain* runChain = BuildChain(runTree);
  if (runChain) {
    Int_t runNEntries = runChain->GetEntries();
    TObjArray* runBranches = runChain->GetListOfBranches();
    std::cout << "Found Tree '" << runTree << "' with " << runBranches->GetEntries() << " branches and " << runNEntries << " entries" << std::endl;
    TPadmeRun* run = new TPadmeRun();
    for(Int_t iBranch = 0; iBranch < runBranches->GetEntries(); iBranch++){
      TString branchName = ((TBranch*)(*runBranches)[iBranch])->GetName();
      TClass* branchObjectClass = TClass::GetClass(((TBranch*)(*runBranches)[iBranch])->GetClassName());
      std::cout << "Found Branch " << branchName.Data() << " containing " << branchObjectClass->GetName() << std::endl;
      if(branchName=="Run") {
	runChain->SetBranchAddress(branchName.Data(),&run);
	runChain->GetEntry(0); // Currently only one run per file
	std::cout << "=== MC Run information - Start ===" << std::endl;
	std::cout << "Run number/type " << run->GetRunNumber() << " " << run->GetRunType() << std::endl;
	std::cout << "Run start/stop time " << run->GetTimeStart() << " " << run->GetTimeStop() << std::endl;
	std::cout << "Run number of events " << run->GetNEvents() << std::endl;
	TDetectorInfo* detInfo = run->GetDetectorInfo();
	ShowSubDetectorInfo(detInfo,"Target");
	ShowSubDetectorInfo(detInfo,"EVeto");
	ShowSubDetectorInfo(detInfo,"PVeto");
	ShowSubDetectorInfo(detInfo,"HEPVeto");
	ShowSubDetectorInfo(detInfo,"ECal");
	ShowSubDetectorInfo(detInfo,"SAC");
	ShowSubDetectorInfo(detInfo,"TPix");
	std::cout << "=== MC Run information - End ===" << std::endl << std::endl;

	// Pass detector info to corresponding Parameters class for decoding
	TSubDetectorInfo* subDetInfo = detInfo->FindSubDetectorInfo("ECal");
	if (subDetInfo) ECalParameters::GetInstance()->SetMCDetInfo(subDetInfo);
    
      }
    }
  }
  else std::cout << " Tree " << runTree << " not found "<<std::endl;

  Int_t nEntries;

  nEntries = 0;
  TString mcTreeName = "MC";
  fMCChain = NULL;
  std::cout<<" Looking for tree named "<<mcTreeName<<std::endl;
  fMCChain = BuildChain(mcTreeName);
  if(fMCChain) {
    
    nEntries = fMCChain->GetEntries();
    std::cout<<" Tree named "<<mcTreeName<<" found with "<<nEntries<<" events"<<std::endl;
    TObjArray* branches = fMCChain->GetListOfBranches();
    for(Int_t iBranch = 0; iBranch < branches->GetEntries(); iBranch++){

      TString branchName = ((TBranch*)(*branches)[iBranch])->GetName();
      TClass* branchObjectClass = TClass::GetClass(((TBranch*)(*branches)[iBranch])->GetClassName());
      std::cout << "Found Branch " << branchName.Data() << " containing " << branchObjectClass->GetName() << std::endl;

      if (branchName=="Event") {
	fMCEvent = new TMCEvent();
	fMCChain->SetBranchAddress(branchName.Data(),&fMCEvent);
      } else if (branchName=="Target") {
	fTargetMCEvent = new TTargetMCEvent();
	fMCChain->SetBranchAddress(branchName.Data(),&fTargetMCEvent);
      } else if (branchName=="EVeto") {
	fEVetoMCEvent = new TEVetoMCEvent();
	fMCChain->SetBranchAddress(branchName.Data(),&fEVetoMCEvent);
      } else if (branchName=="PVeto") {
	fPVetoMCEvent = new TPVetoMCEvent();
	fMCChain->SetBranchAddress(branchName.Data(),&fPVetoMCEvent);
      } else if (branchName=="HEPVeto") {
	fHEPVetoMCEvent = new THEPVetoMCEvent();
	fMCChain->SetBranchAddress(branchName.Data(),&fHEPVetoMCEvent);
      } else if (branchName=="ECal") {
	fECalMCEvent = new TECalMCEvent();
	fMCChain->SetBranchAddress(branchName.Data(),&fECalMCEvent);
      } else if (branchName=="SAC") {
	fSACMCEvent = new TSACMCEvent();
	fMCChain->SetBranchAddress(branchName.Data(),&fSACMCEvent);
      } else if (branchName=="TPix") {
	fTPixMCEvent = new TTPixMCEvent();
	fMCChain->SetBranchAddress(branchName.Data(),&fTPixMCEvent);
      }

    }

  }
  else std::cout << " Tree " << mcTreeName << " not found "<<std::endl;
        

  // input are reco hits
  nEntries = 0;
  TString recoTreeName = "Events";
  std::cout<<" Looking for tree named "<<recoTreeName<<std::endl;
  fRecoChain = NULL;
  fRecoChain = BuildChain(recoTreeName);
  if(fRecoChain) {

    nEntries = fRecoChain->GetEntries();
    std::cout<<" Tree named "<<recoTreeName<<" found with "<<nEntries<<" events"<<std::endl;
    TObjArray* branches = fRecoChain->GetListOfBranches();
    std::cout << "Found Tree '" << recoTreeName << "' with " << branches->GetEntries() << " branches and " << nEntries << " entries" << std::endl;

    for(Int_t iBranch = 0; iBranch < branches->GetEntries(); iBranch++){

      TString branchName = ((TBranch*)(*branches)[iBranch])->GetName();
      TClass* branchObjectClass = TClass::GetClass(((TBranch*)(*branches)[iBranch])->GetClassName());
      std::cout << "Found Branch " << branchName.Data() << " containing " << branchObjectClass->GetName() << std::endl;

      if (branchName=="RecoEvent") {
	fRecoEvent = new TRecoEvent();
	fRecoChain->SetBranchAddress(branchName.Data(),&fRecoEvent);
      } else if (branchName=="Target_Hits") {
	fTargetRecoEvent = new TTargetRecoEvent();
	fRecoChain->SetBranchAddress(branchName.Data(),&fTargetRecoEvent);
      } else if (branchName=="EVeto_Hits") {
	fEVetoRecoEvent = new TEVetoRecoEvent();
	fRecoChain->SetBranchAddress(branchName.Data(),&fEVetoRecoEvent);
      } else if (branchName=="PVeto_Hits") {
	fPVetoRecoEvent = new TPVetoRecoEvent();
	fRecoChain->SetBranchAddress(branchName.Data(),&fPVetoRecoEvent);
      } else if (branchName=="HEPVeto_Hits") {
	fHEPVetoRecoEvent = new THEPVetoRecoEvent();
	fRecoChain->SetBranchAddress(branchName.Data(),&fHEPVetoRecoEvent);
      } else if (branchName=="ECal_Hits") {
	fECalRecoEvent = new TECalRecoEvent();
	fRecoChain->SetBranchAddress(branchName.Data(),&fECalRecoEvent);
      } else if (branchName=="SAC_Hits") {
	fSACRecoEvent = new TSACRecoEvent();
	fRecoChain->SetBranchAddress(branchName.Data(),&fSACRecoEvent);
	//      } else if (branchName=="TPix") {
	//	fTPixRecoEvent = new TTPixRecoEvent();
	//	fRecoChain->SetBranchAddress(branchName.Data(),&fTPixRecoEvent);
      }

    }

  }
  else std::cout << " Tree " << recoTreeName << " not found "<<std::endl;

  nEntries = 0;
  TString rawTreeName = "RawEvents";
  fRawChain = NULL;
  fRawChain = BuildChain(rawTreeName);
  std::cout<<" Looking for tree named "<<rawTreeName<<std::endl;
  if(fRawChain) {
    fRawEvent = new TRawEvent();
    nEntries = fRawChain->GetEntries();
    std::cout<<" Tree named "<<rawTreeName<<" found with "<<nEntries<<" events"<<std::endl;
    TObjArray* branches = fRawChain->GetListOfBranches();
    std::cout << "Found Tree '" << rawTreeName << "' with " << branches->GetEntries() << " branches and " << nEntries << " entries" << std::endl;
    fRawChain->SetBranchAddress("RawEvent",&fRawEvent);
  }
  else std::cout << " Tree " << rawTreeName << " not found "<<std::endl;

  fNProcessedEventsInTotal = 0;

  // Initialize reconstruction for each subdetector
  InitDetectorsInfo();

}

Bool_t PadmeReconstruction::NextEvent()
{

  // Check if there is a new event to process
  if ( fMCChain && fMCChain->GetEntry(fNProcessedEventsInTotal) &&  (fNEvt == 0 || fNProcessedEventsInTotal < fNEvt) ) {

    if (fNProcessedEventsInTotal%100==0) {
      std::cout << "=== Read event in position " << fNProcessedEventsInTotal << " ===" << std::endl;
      std::cout << "--- PadmeReconstruction --- run/event/time " << fMCEvent->GetRunNumber()
		<< " " << fMCEvent->GetEventNumber() << " " << fMCEvent->GetTime() << std::endl;
    }

    // Reconstruct individual detectors (but check if they exist, first!)
    for (UInt_t iLib = 0; iLib < fRecoLibrary.size(); iLib++) {
      if (fRecoLibrary[iLib]->GetName() == "Target" && fTargetMCEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fTargetMCEvent,fMCEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "EVeto" && fEVetoMCEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fEVetoMCEvent,fMCEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "PVeto" && fPVetoMCEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fPVetoMCEvent,fMCEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "HEPVeto" && fHEPVetoMCEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fHEPVetoMCEvent,fMCEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "ECal" && fECalMCEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fECalMCEvent,fMCEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "SAC" && fSACMCEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fSACMCEvent,fMCEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "TPix" && fTPixMCEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fTPixMCEvent,fMCEvent);
      }
    }

    fNProcessedEventsInTotal++;
    return true;

  }

  // Check if there is a new event to process
  if ( fRecoChain && fRecoChain->GetEntry(fNProcessedEventsInTotal) &&  (fNEvt == 0 || fNProcessedEventsInTotal < fNEvt) ) {

    if (fNProcessedEventsInTotal%100==0) {
    std::cout << "=== Read (from Hits) event in position " << fNProcessedEventsInTotal << " ===" << std::endl;
    std::cout << "--- PadmeReconstruction --- run/event/time " << fRecoEvent->GetRunNumber()
	 << " " << fRecoEvent->GetEventNumber() << " " << fRecoEvent->GetTime() << std::endl;
    }
    // Reconstruct individual detectors (but check if they exist, first!)
    for (UInt_t iLib = 0; iLib < fRecoLibrary.size(); iLib++) {
      if (fRecoLibrary[iLib]->GetName() == "Target" && fTargetRecoEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fTargetRecoEvent,fRecoEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "EVeto" && fEVetoRecoEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fEVetoRecoEvent,fRecoEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "PVeto" && fPVetoRecoEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fPVetoRecoEvent,fRecoEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "HEPVeto" && fHEPVetoRecoEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fHEPVetoRecoEvent,fRecoEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "ECal" && fECalRecoEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fECalRecoEvent,fRecoEvent);
      } else if (fRecoLibrary[iLib]->GetName() == "SAC" && fSACRecoEvent) {
	fRecoLibrary[iLib]->ProcessEvent(fSACRecoEvent,fRecoEvent);
	//      } else if (fRecoLibrary[iLib]->GetName() == "TPix" && fTPixRecoEvent) {
	//	fRecoLibrary[iLib]->ProcessEvent(fTPixRecoEvent,fRecoEvent);
      }
    }

    ++fNProcessedEventsInTotal;
    //std::cout<<" fNProcessedEventsInTotal = "<<fNProcessedEventsInTotal<<std::endl;
    return true;
    
  }

  if ( fRawChain && fRawChain->GetEntry(fNProcessedEventsInTotal) && (fNEvt == 0 || fNProcessedEventsInTotal < fNEvt) ) {

    if (fNProcessedEventsInTotal%100==0) {
      std::cout << "=== Read raw event in position " << fNProcessedEventsInTotal << " ===" << std::endl;
      std::cout << "--- PadmeReconstruction --- run/event/time " << fRawEvent->GetRunNumber()
		<< " " << fRawEvent->GetEventNumber() << " " << fRawEvent->GetEventAbsTime() << std::endl;
    }
    // Reconstruct individual detectors (but check if they exist, first!)
    for (UInt_t iLib = 0; iLib < fRecoLibrary.size(); iLib++) {
      fRecoLibrary[iLib]->ProcessEvent(fRawEvent);
    }

    fNProcessedEventsInTotal++;
    return true;

  }

  return false;

}

void PadmeReconstruction::EndProcessing(){

  // Reconstruct individual detectors (but check if they exist, first!)
  for (UInt_t iLib = 0; iLib < fRecoLibrary.size(); iLib++) {
    fHistoFile->cd("/");
    fRecoLibrary[iLib]->EndProcessing();
  }
  fHistoFile->cd("/");


  //for(Int_t iReco = 0; iReco < fNReconstructions; iReco++){
  //  fReconstructions[iReco]->EvaluateROSettings();
  //}
  //for(UInt_t iTree=0;iTree<fOutputTrees.size();iTree++){
  //  fOutputTrees[iTree]->Write();
  //}
  //if(fMCOutputTree) fMCOutputTree->Write();

  //This goes in the PadmeReco core
  //RecoRootIOManager::GetInstance()->Close();

  //fHistoFile->Purge();
  //fHistoFile->Close();
  //PrintRecoSummary(std::cout);

}

TChain* PadmeReconstruction::BuildChain(TString treeName){
  TChain* chain = new TChain(treeName.Data());
  for(Int_t iFile = 0; iFile < fInputFileNameList->GetEntries(); iFile++)
    chain->AddFile(CheckProtocols(((TObjString*)fInputFileNameList->At(iFile))->GetString()));
  if(chain->GetEntries() == 0){
    delete chain;
    chain = 0;
  }
  return chain;
}

// Verify URL for each file
TString PadmeReconstruction::CheckProtocols(TString OldStr){
  TString NewStr=OldStr;
  if(NewStr.EndsWith("\r")) NewStr.Remove(NewStr.Last('\r'));
  //if(NewStr.Contains("/eos/") && !NewStr.Contains("root://eosna62")){
  //  NewStr = "root://eosna62.cern.ch/"+NewStr;
  //}
  //else if(NewStr.Contains("/castor/")) {
  //  if(!NewStr.Contains("root://")){
  //    NewStr = "root://castorpublic.cern.ch/"+NewStr;
  //  }
  //  if(!NewStr.Contains("svcClass")){
  //    NewStr = NewStr+"?svcClass="+fSvcClass;
  //  }
  //}
  return NewStr;
}

PadmeVReconstruction * PadmeReconstruction::FindReco(TString Name){
  for(UInt_t iLib = 0; iLib < fRecoLibrary.size(); iLib++)
    if(fRecoLibrary[iLib]->GetName().CompareTo(Name) == 0)
      return fRecoLibrary[iLib];
  return 0;
}

void PadmeReconstruction::ShowSubDetectorInfo(TDetectorInfo* detInfo, TString name)
{
  TSubDetectorInfo* subDetInfo = detInfo->FindSubDetectorInfo(name);
  if (subDetInfo) {
    std::cout << "--- " << name.Data() << " geometry parameters ---" << std::endl;
    std::vector<TString> subPar = subDetInfo->GetGeometryParameters();
    for(UInt_t iPar = 0; iPar < subPar.size(); iPar++) {
      std::cout << subPar[iPar].Data() << std::endl;
    }
  }
}
