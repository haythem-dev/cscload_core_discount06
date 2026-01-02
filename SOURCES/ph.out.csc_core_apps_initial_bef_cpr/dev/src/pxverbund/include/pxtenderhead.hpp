/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxtenderhead.hpp
TENDERHEAD  class

REVISION HISTORY

16 Sept 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXTENDERHEAD_INC
#define PXTENDERHEAD_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>

struct tTENDERHEAD;

class pxTenderHead : public pxDBRecord
{

public:
                pxTenderHead(pxTenderHead& src);
                pxTenderHead(pxSession *session);
                pxTenderHead(pxSession *session, tTENDERHEAD& src);
                pxTenderHead(pxSession *session, const pxTenderHead* src);
                pxTenderHead(pxSession *session, long TenderNo);

                virtual  ~pxTenderHead();
    pxTenderHead&   operator=(const pxTenderHead& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxTenderHead&   operator=(const tTENDERHEAD& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


    friend   pxTenderHead&
                Assign(pxTenderHead& dest, const tTENDERHEAD& src);
    friend   tTENDERHEAD&
                Assign(tTENDERHEAD& dest, const pxTenderHead& src);

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
    long            TenderNo()        const {return TenderNo_             ;}
    long            TenderType()      const {return TenderType_           ;}
    const nString&  ContractNo()      const {return ContractNo_           ;}
    short           BranchNo()        const {return BranchNo_             ;}
    long            CustomerNo()      const {return CustomerNo_           ;}
    short           AccBranchNo()     const {return AccBranchNo_          ;}
    long            AccCustomerNo()   const {return AccCustomerNo_        ;}
    const nDate&    DateFrom()        const {return DateFrom_             ;}
    const nDate&    DateTo()          const {return DateTo_               ;}
    double          ExceedancePct()   const {return ExceedancePct_        ;}
    char            TenderState()     const {return TenderState_          ;}
    const nDate&    ChangeDate()      const {return ChangeDate_           ;}
    const nString&  NameOfUser()      const {return NameOfUser_           ;}
    long            PharmacyChainNo() const {return PharmacyChainNo_      ;}

    bool            IsAutoBlocked()    const { return TenderState_ == '9';}
    bool            IsStateTender()    const { return TenderType_  ==  2; }
    bool            IsHospitalTender() const { return TenderType_  ==  1; }

// Set Methodes
   void             SetAutoBlocked()  { TenderState_ =  '9'; ChangeDate_ = nDate(); SetDirty(); }
   void				SetDateTo( const nDate & dateTo ) { DateTo_ = dateTo; SetDirty(); }

protected:
    void        Init();

    long        TenderNo_           ;      // Tender Number
    long        TenderType_         ;      // Tender Type
    nString     ContractNo_         ;      // Contract Number
    short       BranchNo_           ;      // Branch Number
    long        CustomerNo_         ;      // Customer Number
    short       AccBranchNo_        ;      // Account Branch Number
    long        AccCustomerNo_      ;      // Customer Number
    nDate       DateFrom_           ;      // Date from
    nDate       DateTo_             ;      // Date to
    double      ExceedancePct_      ;      // Exceedance Percentage
    char        TenderState_        ;      // Tender State
                                           // 0 = Tender not ready for production
                                           // 1 = Tender normal state for production
                                           // 8 = Tender manualy closed
                                           // 9 = Tender automaticly closed
    nDate       ChangeDate_         ;      // Date of change
    nString     NameOfUser_         ;      // name of user
    long        PharmacyChainNo_    ;      // Chain numbere

private:
    friend class pxTenderHeadList;
};

class pxTenderHeadList : public nDBRecordSet, public nDListCollect
{

public:
                pxTenderHeadList(pxSession *session);
                virtual ~pxTenderHeadList() {Clear();}

                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );

    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxTenderHeadListIter;
};

class pxTenderHeadListIter : public nDListCollectIter
{

public:
// constructors:
    pxTenderHeadListIter(pxTenderHeadList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxTenderHeadListIter() {;}
};
#endif
