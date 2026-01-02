#ifndef PXITEMDISCOUNT_INC
#define PXITEMDISCOUNT_INC

#include "pxbase/pxrecord.hpp"
#include "pxdiscountdef.h"

struct tKDAUFTRAGPOSRAB;

class pxItemDiscount : public pxDBRecord
{

public:


// constructors:
                pxItemDiscount(pxItemDiscount& src);
                pxItemDiscount(pxSession *session);
                pxItemDiscount(pxSession *session, tKDAUFTRAGPOSRAB& src);
                pxItemDiscount(pxSession *session, const long KdAuftragNr,
                                     const long PosNr,
                                     const short DiscountType,
                                     const nString& PharmacyGroupId,
                                     DBAccessMode mode = cDBGET_READONLY);
                pxItemDiscount(pxSession *session,
                                                                const long KdAuftragNr,
                                                                const long PosNr,
                                                                const short DiscountType,
                                                                const nString& PharmacyGroupId,
                                                                const short PaymentTargetNo,
                                                                DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxItemDiscount();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxItemDiscount&   operator=(const pxItemDiscount& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxItemDiscount&   operator=(const tKDAUFTRAGPOSRAB& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxItemDiscount&
                Assign(pxItemDiscount& dest, const tKDAUFTRAGPOSRAB& src);
    friend   tKDAUFTRAGPOSRAB&
                Assign(tKDAUFTRAGPOSRAB& dest, const pxItemDiscount& src);

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
    long              KdAuftragNr()          const {return KdAuftragNr_     ;}
    long              PosNr()                const {return PosNr_           ;}
    short             DiscountType()         const {return DiscountType_    ;}
    double            DiscountValuePct()     const {return DiscountValuePct_;}
    const nString&    PharmacyGroupId()      const {return PharmacyGroupId_ ;}
    short             PaymentTargetNo()      const {return PaymentTargetNo_ ;}
    double            DiscountValPctMan()    const {return DiscountValPctMan_;}
    double            SurchargePct()         const {return SurchargePct_;}
	tDiscountCategory DiscountCategory()     const {return DiscountCategory_;}
	short             InternalDiscountFlag() const {return InternalDiscountFlag_;}
	double            RefundValuePct()       const {return RefundValuePct_;}
	double            FixedPrice()           const {return FixedPrice_; }
    short             DiscountCalcFrom()     const {return DiscountCalcFrom_; }
    short             DiscountApplyTo()      const {return DiscountApplyTo_; }


//  Field Updates:
    void           SetDiscountType( short t)
                   {DiscountType_ = t;SetDirty();}
    void           SetDiscountValuePct( double q)
                   {DiscountValuePct_ = q;SetDirty();}
    void           SetPaymentTargetNo( short n)
                   {PaymentTargetNo_  = n;SetDirty();}
    void           SetDiscountValPctMan( double q)
                   {DiscountValPctMan_ = q;SetDirty();}
    void           SetSurchargePct( double q)
                   {SurchargePct_ = q;SetDirty();}
	void           SetDiscountCategory(enum tDiscountCategory c)
	               {DiscountCategory_ = c; SetDirty();}
	void           SetInternalDiscountFlag(short f)
	               {InternalDiscountFlag_ = f; SetDirty();}
	void           SetRefundValuePct(double r)
                   {RefundValuePct_ = r; SetDirty();}
	void           SetFixedPrice(double preis)
                   {FixedPrice_ = preis; SetDirty();}
	void           SetDiscountCalcFrom(short t)
                   {DiscountCalcFrom_ = t;SetDirty();}
	void           SetDiscountApplyTo(short t)
                   {DiscountApplyTo_ = t;SetDirty();}

	int				logKdAuftragPosRab(nString& m_str);

protected:
    void        Init();

    long              KdAuftragNr_;           // Ordernumber
    long              PosNr_;                 // PosNr
    short             DiscountType_;          // DiscountType
    double            DiscountValuePct_;      // DiscountValuePct
    nString           PharmacyGroupId_   ;    // Pharmacy Group Id
    short             PaymentTargetNo_;       // PaymentTargetNo
    double            DiscountValPctMan_;     // DiscountValuePct Manual
    double            SurchargePct_;          // Zuschlag PCT
	tDiscountCategory DiscountCategory_;
	short             InternalDiscountFlag_;
	double            RefundValuePct_;
	double            FixedPrice_;
    short             DiscountCalcFrom_;
    short             DiscountApplyTo_;


private:
    friend class pxItemDiscountList;

};

class pxItemDiscountList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxItemDiscountList(pxSession *session);
//  destructor:
                virtual ~pxItemDiscountList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const long KdAuftragNr, const long PosNr = 0, const int count = 500);
    void        Clear()        {nDBRecordSet::Clear();}
    pxItemDiscount*  Find( const int discounttype);
    pxItemDiscount*  FindDiscountValuePct();
    pxItemDiscount*  GetEntry( const int PosNr);
    pxItemDiscount*  FindDiscountValuePctPosNr(const long PosNr);
	pxItemDiscount*  FindFixedPrice();

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:
    friend class pxItemDiscountListIter;
};

class pxItemDiscountListIter : public nDListCollectIter
{

public:
// constructors:
    pxItemDiscountListIter(pxItemDiscountList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxItemDiscountListIter() {;}
};
#endif
