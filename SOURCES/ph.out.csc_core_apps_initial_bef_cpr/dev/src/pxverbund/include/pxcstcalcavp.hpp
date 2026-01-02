/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxcstcalcavp.hpp
CSTCALCAVP  class

REVISION HISTORY

06 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCSTCALCAVP_INC
#define PXCSTCALCAVP_INC

#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"

struct tCSTCALCAVP;

class pxCstCalcAvp : public pxDBRecord
{

public:

// constructors:
                pxCstCalcAvp(pxCstCalcAvp& src);
                pxCstCalcAvp(pxSession *session);
                pxCstCalcAvp(pxSession *session, tCSTCALCAVP& src);
                pxCstCalcAvp(pxSession *session, const pxCstCalcAvp* src);
                pxCstCalcAvp(pxSession *session, short BranchNo, long  CustomerNo, short PriceGroup, PriceTypeEnum PreisTyp, nString AbdaCode);

// destructor:
                virtual  ~pxCstCalcAvp();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCstCalcAvp&   operator=(const pxCstCalcAvp& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCstCalcAvp&   operator=(const tCSTCALCAVP& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCstCalcAvp&
                Assign(pxCstCalcAvp& dest, const tCSTCALCAVP& src);
    friend   tCSTCALCAVP&
                Assign(tCSTCALCAVP& dest, const pxCstCalcAvp& src);

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

// Update Fields

//  Queries:
    short          BranchNo()       {return BranchNo_             ;}
    long           CustomerNo()     {return CustomerNo_           ;}
    nString&       AbdaCode()       {return AbdaCode_             ;}
    short          SurchargeBasic() {return SurchargeBasic_       ;}
    short          DeductionBasic() {return DeductionBasic_       ;}
    double         SurchargePct()   {return SurchargePct_         ;}
    double         DeductionPct()   {return DeductionPct_         ;}
    short          PriceGroup()     {return PriceGroup_           ;}
    PriceTypeEnum  PreisTyp()       {return PreisTyp_             ;}


// Set Methodes


protected:
    void        Init();

    short         BranchNo_           ;      // Branch Number
    long          CustomerNo_         ;      // Customer Number
    nString       AbdaCode_           ;      // Abdacode
    short         SurchargeBasic_     ;      // basis Zuschlag
    short         DeductionBasic_     ;      // basis Abschlag
    double        SurchargePct_       ;      // Zuschlag %
    double        DeductionPct_       ;      // Abschlag %
    short         PriceGroup_         ; 
    PriceTypeEnum PreisTyp_           ; 


private:
    friend class pxCstCalcAvpList;
};

class pxCstCalcAvpList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCstCalcAvpList(pxSession *session);
//  destructor:
                virtual ~pxCstCalcAvpList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int count = 50 );
    size_t      Select ( const short BranchNo, const long CustomerNo, const short PriceGroup, const PriceTypeEnum PreisTyp, const int count = 1000);
// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxCstCalcAvpListIter;
};

class pxCstCalcAvpListIter : public nDListCollectIter
{

public:
// constructors:
    pxCstCalcAvpListIter(pxCstCalcAvpList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCstCalcAvpListIter() {;}
};
#endif
