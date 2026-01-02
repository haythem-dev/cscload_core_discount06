/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

 pxartspecialcond.hpp
 ARTSPECIALCOND   class

REVISION HISTORY

20 Jan 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTSPECIALCOND_INC
   #define PXARTSPECIALCOND_INC

#include "pxbase/pxrecord.hpp"

struct tARTSPECIALCOND;

class pxArtSpecialCond : public pxDBRecord
{

public:

// constructors:
                pxArtSpecialCond(pxArtSpecialCond& src);
                pxArtSpecialCond(pxSession *session);
                pxArtSpecialCond(pxSession *session, tARTSPECIALCOND& src);
                pxArtSpecialCond(pxSession *session, const pxArtSpecialCond* src);
                pxArtSpecialCond(pxSession *session, const long ArticleNo,
                                 DBAccessMode mode = cDBGET_READONLY );

// destructor:
                virtual  ~pxArtSpecialCond();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArtSpecialCond&   operator=(const pxArtSpecialCond& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArtSpecialCond&   operator=(const tARTSPECIALCOND& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArtSpecialCond&
                Assign(pxArtSpecialCond& dest, const tARTSPECIALCOND& src);
    friend   tARTSPECIALCOND&
                Assign(tARTSPECIALCOND& dest, const pxArtSpecialCond& src);

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
    long          ArticleNo()         const { return ArticleNo_             ;}
    double        InvoiceRebatePct()  const { return InvoiceRebatePct_      ;}
    double        RebateInKindPct()   const { return RebateInKindPct_       ;}
    double        AnnualInvRebPct()   const { return AnnualInvRebPct_       ;}
    double        AnnualRebIKPct()    const { return AnnualRebIKPct_        ;}
    double        CustRebRedPct()     const { return CustRebRedPct_         ;}
    double        HiReimBursement()   const { return HiReimBursement_       ;}
    double        SupplHiReimb()      const { return SupplHiReimb_          ;}
    double        SupplFsReimb()      const { return SupplFsReimb_          ;}
    double        SupplDiscountPct()  const { return SupplDiscountPct_      ;}

// Set Methodes


protected:
    void        Init();

    long      ArticleNo_         ;      // Article number
    double    InvoiceRebatePct_  ;      // InvoiceRebatePct
    double    RebateInKindPct_   ;      // RebateInKindPct
    double    AnnualInvRebPct_   ;      // AnnualInvRebPct
    double    AnnualRebIKPct_    ;      // AnnualRebIKPct
    double    CustRebRedPct_     ;      // CustRebRedPct
    double    HiReimBursement_   ;      // HiReimBursement
    double    SupplHiReimb_      ;      // Supplier HiReimBursement
    double    SupplFsReimb_      ;      // Supplier FSReimBursement
    double    SupplDiscountPct_  ;      // Supplier Discount Pct
private:
    friend class pxArtSpecialCondList;
};

class pxArtSpecialCondList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxArtSpecialCondList(pxSession *session);
//  destructor:
                virtual ~pxArtSpecialCondList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long ArticleNo,
                         const int  count  = 100
                       );

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxArtSpecialCondListIter;
};

class pxArtSpecialCondListIter : public nDListCollectIter
{

public:
// constructors:
    pxArtSpecialCondListIter(pxArtSpecialCondList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArtSpecialCondListIter() {;}
};
#endif
