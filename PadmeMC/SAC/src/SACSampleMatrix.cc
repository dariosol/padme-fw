// --------------------------------------------------------------------
// History:
//
// Created by Domenico Di Filippo (difilippo@na.infn.it) 2010-03-15
// 2010-04-19 Domenico Di Filippo (difilippo@na.infn.it)
//   - Added method to set mean value
//
// --------------------------------------------------------------------

#include "SACSampleMatrix.hh"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "NA62Global.hh"

using namespace std;

MatrixDimension::MatrixDimension() : Division(nullptr), DivisionsNumber(0), Index(-1) {}

MatrixDimension::~MatrixDimension(){
  if (Division != 0) delete [] Division;
}

MatrixDimension& MatrixDimension::operator=(const MatrixDimension &that){
  if (&that == this)
    return *this;
  this->DivisionsNumber = that.DivisionsNumber;
  this->Index = that.Index;

  if (this->Division != 0) delete [] Division;
  this->Division = new double[that.DivisionsNumber];
  for (unsigned int i=0; i<that.DivisionsNumber; i++)
    this->Division[i] = that.Division[i];
  return *this;
}


void MatrixDimension::AddDivision(AxisType newdiv){

  // If it the first division
  if (Division == 0){
    DivisionsNumber = 1;
    Division = new AxisType[DivisionsNumber];
    Division[0] = newdiv;
    return;
  }

  // Find where to split the array
  unsigned int split;
  for (split=0; split<DivisionsNumber; split++){
    if (Division[split] > newdiv) break;
    else if (Division[split] == newdiv) return;
  }

  // Prepare new array
  AxisType *OldArray = Division;
  DivisionsNumber++;
  Division = new AxisType[DivisionsNumber];

  // Copy the old values and add the new division
  for (unsigned int j=0; j<DivisionsNumber; j++)
    if (j<split) Division[j] = OldArray[j];
    else if (j == split) Division[j] = newdiv;
    else Division[j] = OldArray[j-1];
  delete [] OldArray;
}

SACSampleMatrix::SACSampleMatrix(){
  Dimension = 0;
  DimensionsNumber = 0;
  Value = 0;
  Size = 0;
  OutValue = 0;
}

SACSampleMatrix::~SACSampleMatrix(){
  if (Dimension != 0){
    delete [] Dimension;
    Dimension = 0;
    DimensionsNumber = 0;
  }
  if (Value != 0){
    delete [] Value;
    Value = 0;
    Size = 0;
  }
}


SACSampleMatrix& SACSampleMatrix::operator=(const SACSampleMatrix &that){
   if (this == &that) return *this;
   if (Dimension != 0){
      delete [] Dimension;
      Dimension = 0;
      DimensionsNumber = 0;
   }
  this->SetDimensionsNumber(that.DimensionsNumber);
  for(unsigned int i=0; i<that.DimensionsNumber; i++)
    this->Dimension[i] = that.Dimension[i];
  Prepare();
  for (unsigned int k=0; k<Size; k++)
     Value[k] = that.Value[k];
  OutValue = that.OutValue;
  this->SetOutOfRangeValue(that.OutValue);
  return *this;
}

bool SACSampleMatrix::Load(const char* filename){
  fstream in;
  in.open(filename,ios_base::in);
  in.close();
  if (in.fail()){
    std::cerr<<"[SACSampleMatrix] Error: can't access "<<filename<<std::endl;
    exit(kGenericError);
    return false;
  } else {
    std::cout<<"[SACSampleMatrix] Loading "<<filename<<std::endl;
  }
  if (Dimension != 0){
    delete [] Dimension;
    Dimension = 0;
    DimensionsNumber = 0;
  }
  if (Value != 0){
    delete [] Value;
    Value = 0;
    Size = 0;
  }
  in.open(filename,ios_base::in);
  unsigned int ndimension;
  in >> ndimension;
  SetDimensionsNumber(ndimension);
  for (unsigned int d=0; d<ndimension; d++){
    unsigned int ndivision;
    in >> ndivision;
    for (unsigned int i=0; i<ndivision; i++){
      DataType valdivision;
      in >> valdivision;
      Dimension[d].AddDivision(valdivision);
    }
  }
  Prepare();
  for (unsigned int i=0;i<Size;i++)
    in >> Value[i];
  in.close();
  return true;
}

void SACSampleMatrix::SetDimensionsNumber(unsigned int Dim){
  if (Dim > 0){
    MatrixDimension *NewDimArray = new MatrixDimension[Dim];
    unsigned int maxdim = Dim;
    if (maxdim > DimensionsNumber) maxdim = DimensionsNumber;
    for (unsigned int i=0; i<maxdim; i++)
      NewDimArray[i] = Dimension[i];
    delete [] Dimension;
    Dimension = NewDimArray;
    DimensionsNumber = Dim;
  } else {
    delete [] Dimension;
    Dimension = 0;
    DimensionsNumber = 0;
  }
}

int SACSampleMatrix::GetIndex(){
      unsigned int index = 0, multiplier = 1;
      for (unsigned int d=0; d<DimensionsNumber;d++){
         int dind = Dimension[d].GetIndex();
         if(dind<0) return -1;
         index += multiplier*((unsigned int)dind);
         multiplier *= Dimension[d].GetBinsNumber();
      }
      return index;
}

bool SACSampleMatrix::SetIndex(int index) {
  int div = 1;
  if (index < 0 || index >= (int)Size) return false;
  for (unsigned int d=0; d<DimensionsNumber; d++){
    int dind = (index / div) % Dimension[d].GetBinsNumber();
    Dimension[d].SetIndex(dind);
    div *= Dimension[d].GetBinsNumber();
  }
  return true;
}

void SACSampleMatrix::Prepare(){
  if (Value != 0) delete [] Value;
  if (Dimension == 0){
    Size = 0;
    Value = 0;
    return;
  }
  Size = 1;
  for (unsigned int d=0; d<DimensionsNumber;d++)
    Size *= Dimension[d].GetBinsNumber();
  Value = new DataType [Size];
}

void SACSampleMatrix::Reset(DataType v){
  for(unsigned int i=0; i<Size; i++) Value[i]=v;
}

void SACSampleMatrix::Save(const char* filename){
  fstream out;
  out.open(filename,ios_base::out);
  out << DimensionsNumber << endl;
  for (unsigned int d=0; d<DimensionsNumber;d++){
    out << Dimension[d].GetBinsNumber()+1 << endl;
    for (unsigned int i=0; i<Dimension[d].GetBinsNumber()+1; i++)
      out << Dimension[d].GetDivision(i) << endl;
  }
  for (unsigned int i=0; i<Size ; i++)
    out << Value[i] << endl;
  out.close();
}

DataType SACSampleMatrix::GetMean(){
  //if(Size <= 0) return 0; // unsigned so impossible
  DataType Sum = 0;
  AxisType Area = 0;
  for (unsigned int i=0; i<Size; i++){
    SetIndex(i);
    Sum += GetValue() * GetBinMeasure();
    Area += GetBinMeasure();
  }
  return Sum/Area;
}

void SACSampleMatrix::SetMean(DataType newmean){
  //if(Size <= 0) return;  // unsigned so impossible
  const AxisType Factor = newmean / GetMean();
  if (Factor == 1) return;
  for (unsigned int i=0; i<Size; i++)
    Value[i] = Factor * Value[i];
}
