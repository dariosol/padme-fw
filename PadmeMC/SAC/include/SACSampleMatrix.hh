// --------------------------------------------------------------------
// History:
//
// Created by Domenico Di Filippo (difilippo@na.infn.it) 2010-03-15
//
//  2010-04-19 Domenico Di Filippo: added method to set mean value
// --------------------------------------------------------------------

#ifndef SACSampleMatrix_hh
#define SACSampleMatrix_hh

typedef double AxisType;
typedef double DataType;

class MatrixDimension{

public:
   MatrixDimension();
   ~MatrixDimension();

   MatrixDimension& operator=(const MatrixDimension &);
   
   AxisType GetDivision(unsigned int n) const {return Division[n];}
   AxisType* GetDivisions() {return Division;}
   unsigned int GetBinsNumber() const {
      if (DivisionsNumber < 2) return 0;
      return DivisionsNumber-1;}
   void AddDivision(AxisType);

   void SetIndex(int i){
      if (i < (int)GetBinsNumber() && i >= 0) Index = i;
      else Index = -1;
   }
   int GetIndex(){return Index;}

   void Query(AxisType a){
      if (a < Division[0]) return;
      if (a > Division[DivisionsNumber-1]) return;
      for (Index=0; Index<(int)DivisionsNumber; Index++)
         if (Division[Index] > a) break;
      Index--;
   }

   bool IsOut() const {
      if (Index < 0 || Index >= (int) DivisionsNumber) return true;
      return false;
   }
   AxisType GetBinCenter() const {
      if (IsOut()) return (GetDivision(0) + GetDivision(DivisionsNumber-1))/2;;
      return (GetDivision(Index) + GetDivision(Index+1))/2;
   }
   AxisType GetLowEdge() const {
      if (Division == 0) return 0; 
      return Division[0]; 
   }
   AxisType GetTopEdge() const {
      if (Division == 0) return 0; 
      return Division[DivisionsNumber-1]; 
   }
   AxisType GetBinLowEdge() const {
      if (IsOut()) return GetDivision(0);
      return GetDivision(Index);
   }
   AxisType GetBinTopEdge() const {
      if (IsOut()) return GetDivision(DivisionsNumber-1);
      return GetDivision(Index+1);
   }
   AxisType GetBinSize() const{
      return GetBinTopEdge()-GetBinLowEdge();
   }


private:
   AxisType *Division;
   unsigned int DivisionsNumber;
   int Index;

};

class SACSampleMatrix{

public:
   SACSampleMatrix();
   ~SACSampleMatrix();

   SACSampleMatrix& operator=(const SACSampleMatrix &);

   bool Load(const char*);
   void Save(const char*);
   
   void Prepare();
   void Reset(DataType v=0);

   void SetDimensionsNumber(unsigned int);
   unsigned int GetDimensionsNumber() const {return DimensionsNumber;}
   MatrixDimension* GetDimension(unsigned int n) {
      if (n<DimensionsNumber) return Dimension+n;
      return 0;
   }


   int GetIndex();
   bool SetIndex(int);
   
   void SetOutOfRangeValue(DataType a){OutValue = a;}
   DataType GetOutOfRangeValue(){return OutValue;}

   void SetValue(DataType v){
      int tind = GetIndex();
      if (tind >= 0) if (tind < (int)Size)
         Value[(unsigned int)tind] = v;}
   DataType GetValue(){
      int tind = GetIndex(); 
      if (tind < 0 || tind >= (int)Size) return OutValue;
      return Value[tind];}

   AxisType GetRegionMeasure(){
      AxisType toret = 1;
      for (unsigned int i=0; i<DimensionsNumber; i++)
	 toret *= GetDimension(i)->GetDivision(GetDimension(i)->GetBinsNumber()) 
	          - GetDimension(i)->GetDivision(0);
      return toret;
   }
   AxisType GetBinMeasure(){
      AxisType toret = 1;
      for (unsigned int i=0; i<DimensionsNumber; i++)
	 toret *= GetDimension(i)->GetBinSize();
      return toret;
   }

   unsigned int GetSize() const {return Size;}
   void SetMean(DataType);
   DataType GetMean();
   DataType *GetArray() {return Value;}
   
private:
   MatrixDimension *Dimension;
   unsigned int DimensionsNumber;
   DataType *Value;
   DataType OutValue;
   unsigned int Size;
};

#endif
