/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxOrderPosCalcMode Class.

REVISION HISTORY

06 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXORDERPOSCALCMODE_INC
   #define PXORDERPOSCALCMODE_INC

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRPOSRECHART;

class pxOrderPosCalcMode : public pxDBRecord
{

public:


// constructors:
                pxOrderPosCalcMode(pxOrderPosCalcMode& src);
                pxOrderPosCalcMode(pxSession *session);
                pxOrderPosCalcMode(pxSession *session, tKDAUFTRPOSRECHART& src);
                pxOrderPosCalcMode(pxSession *session, const long KdAuftragNr, const long PosNr);
// destructor:
                virtual  ~pxOrderPosCalcMode();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderPosCalcMode&   operator=(const pxOrderPosCalcMode& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderPosCalcMode&   operator=(const tKDAUFTRPOSRECHART& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderPosCalcMode&
                Assign(pxOrderPosCalcMode& dest, const tKDAUFTRPOSRECHART& src);
    friend   tKDAUFTRPOSRECHART&
                Assign(tKDAUFTRPOSRECHART& dest, const pxOrderPosCalcMode& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

//  Queries:

    long          KdAuftragNr()          {return KdAuftragNr_      ;}
    long          PosNr()                {return PosNr_            ;}
    double       SurchargePct()         {return SurchargePct_     ;}
    double       DeductionPct()         {return DeductionPct_     ;}
    double       SurchargeCalc()        {return SurchargeCalc_    ;}
    double       CalcAvp()              {return CalcAvp_          ;}
    double       SurchargeCalcDis()        {return SurchargeCalcDis_    ;}
    double       CalcAvpDis()              {return CalcAvpDis_          ;}

//  Field Updates:
    void           SetSurchargePct(double SurchargePct)
                   {SurchargePct_ = SurchargePct; SetDirty();}
    void           SetDeductionPct(double DeductionPct)
                   {DeductionPct_ = DeductionPct; SetDirty();}
    void           SetSurchargeCalc(double SurchargeCalc)
                   {SurchargeCalc_ = SurchargeCalc; SetDirty();}
    void           SetCalcAvp(double CalcAvp)
                   {CalcAvp_ = CalcAvp; SetDirty();}
    void           SetSurchargeCalcDis(double SurchargeCalcDis)
                   {SurchargeCalcDis_ = SurchargeCalcDis; SetDirty();}
    void           SetCalcAvpDis(double CalcAvpDis)
                   {CalcAvpDis_ = CalcAvpDis; SetDirty();}

protected:
    void        Init();

    long          KdAuftragNr_;           // Ordernumber
    long          PosNr_;                // PosNr
    double       SurchargePct_;         // SurchargePct
    double       DeductionPct_;         // DeductionPct
    double       SurchargeCalc_;        // Surcharge_Calc
    double       CalcAvp_;              // Calculated Customer purchase price
    double       SurchargeCalcDis_;        // Surcharge_Calc_Dis discounted
    double       CalcAvpDis_;              // Calculated Customer purchase price discounted

private:
    friend class pxOrderPosCalcModeList;

};

class pxOrderPosCalcModeList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxOrderPosCalcModeList(pxSession *session);
//  destructor:
                virtual ~pxOrderPosCalcModeList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const long KdAuftragNr,const long PosNr, const int count = 100);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:
    friend class pxOrderPosCalcModeListIter;
};

class pxOrderPosCalcModeListIter : public nDListCollectIter
{

public:
// constructors:
    pxOrderPosCalcModeListIter(pxOrderPosCalcModeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOrderPosCalcModeListIter() {;}
};
#endif
