#ifndef _RECOBASE_DETVPADMEELEMENT_HH_
#define _RECOBASE_DETVPADMEELEMENT_HH_
#include<stdio.h>
#include<memory>
#include<iostream>
#include<vector>
#include<map>
#include<stdarg.h>
#include <typeinfo>   // operator typeid

#include"fwk.hh"
#include"utl.hh"

//#include"detVDigitizerChannel.hh"
//#include"detVDigitizer.hh"
//#include"detVDetectorSystem.hh"
//#include"detVRODevice.hh"
//#include"detVDetector.hh"


namespace det{
  class VPadmeElement{
    protected:
      virtual~VPadmeElement(){INFO("Destructor  '"+fName+"'");}
      std::string fName;
    public:
      VPadmeElement& SetName(const std::string&n){fName=n;return *this;}
      const std::string& GetName()const{return fName;}
  };
}

#endif