// --------------------------------------------------------------
// History:
//
// Created by Stefania Spagnolo (stefania.spagnolo@le.infn.it) 2019-03-14
//
// --------------------------------------------------------------
#ifndef SACCalibration_H
#define SACCalibration_H

#include "PadmeVCalibration.hh"
#include <vector>


class SACCalibration : public PadmeVCalibration
{

public:
  
  SACCalibration();
  ~SACCalibration();
  void ReadCalibrationConstants(std::vector<TRecoVHit *> &hitArray);
  
private:

  Double_t fCalibCh[24];
  std::map < std::pair<int,int>,double> fCalibMap;

};
#endif

