/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXCUSTDISCCONDITION.HPP
Customer Discount Condition Class
REVISION HISTORY

29 November 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCUSTDISCCONDITION_INC
#define PXCUSTDISCCONDITION_INC

#include "pxbase/pxrecord.hpp"

struct tCSTDISCOUNTCONT;

class pxCustDiscCondition : public pxDBRecord
{

public:

// constructors:
                pxCustDiscCondition(pxCustDiscCondition& src);
                pxCustDiscCondition(pxSession *session);
                pxCustDiscCondition(pxSession *session, tCSTDISCOUNTCONT& src);
                pxCustDiscCondition(pxSession *session, const short BranchNo,const long CustomerNo,
                                    const nString& OrderType, const nString& SubOrderType);
// destructor:
                virtual  ~pxCustDiscCondition();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustDiscCondition&   operator=(const pxCustDiscCondition& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustDiscCondition&   operator=(const tCSTDISCOUNTCONT& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustDiscCondition&
                Assign(pxCustDiscCondition& dest, const tCSTDISCOUNTCONT& src);
    friend   tCSTDISCOUNTCONT&
                Assign(tCSTDISCOUNTCONT& dest, const pxCustDiscCondition& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);

//  Queries:
    short          BranchNo()          {return BranchNo_        ;}
    long           CustomerNo()        {return CustomerNo_      ;}
    nString&        OrderType()         {return OrderType_       ;}
    nString&        SubOrderType()      {return SubOrderType_    ;}
    nString&        PaymentTerm()       {return PaymentTerm_     ;}
    short          ValutaDays()        {return ValutaDays_      ;}
    double        MinOrderValue()     {return MinOrderValue_   ;}
    short          MinTubes()          {return MinTubes_        ;}
    double        LossInDiscount()    {return LossInDiscount_  ;}

//  Field Updates:

protected:
    void        Init();

    short      BranchNo_          ;      // Branchnumber
    long       CustomerNo_        ;      // Customernumber
    nString     OrderType_         ;      // ordertype
    nString     SubOrderType_      ;      // subordertype
    nString     PaymentTerm_       ;      // payment terms
    short      ValutaDays_        ;      // count of valutadays
    double    MinOrderValue_     ;      // Minimum Order Value
    short      MinTubes_          ;      // Minimum count of Tubes
    double    LossInDiscount_    ;      // percentage value (= Abschlag)

private:
    friend class pxCustDiscConditionList;
};

class pxCustDiscConditionList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCustDiscConditionList(pxSession *session);
//  destructor:
                virtual ~pxCustDiscConditionList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short BranchNo, const long CustomerNo, const nString& OrderType_,
                         const int     count = 50 );
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxCustDiscConditionListIter;
};

class pxCustDiscConditionListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustDiscConditionListIter(pxCustDiscConditionList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustDiscConditionListIter() {;}
};
#endif
