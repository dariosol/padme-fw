// --------------------------------------------------------------
// History:
//
// Created by Stefania Spagnolo (stefania.spagnolo@le.infn.it) 2019-03-14
//
// --------------------------------------------------------------
#include "Riostream.h"

#include "SACCalibration.hh"
#include "TRecoVHit.hh"
 
SACCalibration::SACCalibration()
  : PadmeVCalibration()
{
  std::cout<<"SACCalibration being created ............"<<std::endl ;
 
}

SACCalibration::~SACCalibration()
{;}

void SACCalibration::ReadCalibrationConstants(std::vector<TRecoVHit *> &Hits){
  std::ifstream Calib;
  char fname[50];

  sprintf(fname,"/home/taruggi/padme-fw/PadmeReco/config/CalibrationSAC.txt");
  Calib.open(fname);
  if (Calib.is_open()){
  	double temp;
  	for (int i=0;i<25;i++){
  	  Calib >> temp >> fCalibCh[i] >> temp >> temp;
	  fCalibMap[std::make_pair(27,i)] = fCalibCh[i];
	}
  Calib.close();
  }
  else{
  	std::cout<<"No previous data available, resorting to default calibration constant (1)"<<std::endl;
  }
  PadmeVCalibration::ReadCalibrationConstants(Hits);

  double hEnergy = 0.;
  int ich = 0;
  for(unsigned int iHit = 0;iHit < Hits.size();iHit++){
    ich     = Hits[iHit]->GetChannelId(); //GetChannelId gives raw/column position, NOT channel in the digitizer!
    hEnergy = Hits[iHit]->GetEnergy()*fCalibCh[ich];
    Hits[iHit]->SetEnergy(hEnergy);
  }

}





