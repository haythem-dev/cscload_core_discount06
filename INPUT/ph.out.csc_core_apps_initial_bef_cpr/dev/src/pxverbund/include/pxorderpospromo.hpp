/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxOrderPosPromo Class.

REVISION HISTORY

20 AU 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXORDERPOSPROMO_INC
   #define PXORDERPOSPROMO_INC

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAGPOSPROMO;

class pxOrderPosPromo : public pxDBRecord
{

public:


// constructors:
                pxOrderPosPromo(pxOrderPosPromo& src);
                pxOrderPosPromo(pxSession *session);
                pxOrderPosPromo(pxSession *session, tKDAUFTRAGPOSPROMO& src);
                pxOrderPosPromo(pxSession *session, const long KdAuftragNr, const long PosNr);
// destructor:
                virtual  ~pxOrderPosPromo();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderPosPromo&   operator=(const pxOrderPosPromo& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderPosPromo&   operator=(const tKDAUFTRAGPOSPROMO& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderPosPromo&
                Assign(pxOrderPosPromo& dest, const tKDAUFTRAGPOSPROMO& src);
    friend   tKDAUFTRAGPOSPROMO&
                Assign(tKDAUFTRAGPOSPROMO& dest, const pxOrderPosPromo& src);

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
    long          KdAuftragNr()           {return KdAuftragNr_     ;}
    long          PosNr()                 {return PosNr_           ;}
    nString&       PharmacyGroupId()       {return PharmacyGroupId_ ;}
    long          DiscountGrpNo()         {return DiscountGrpNo_   ;}
    long          BaseQty()               {return BaseQty_         ;}
    double       BaseValue()             {return BaseValue_       ;}
    long          CustomerNo()            {return CustomerNo_      ;}
    long          PromotionNo()           {return PromotionNo_     ;}
    char          InternalDiscount()      {return InternalDiscount_;}
    double       DiscountValuePct()      {return DiscountValuePct_;}

//  Field Updates:
    void           SetPharmacyGroupId( const nString& PharmacyGroupId )
                   {PharmacyGroupId_ = PharmacyGroupId;SetDirty();   }
    void           SetDiscountGrpNo( long DiscountGrpNo )
                   {DiscountGrpNo_ = DiscountGrpNo;SetDirty();       }
    void           SetBaseQty( long BaseQty )
                   {BaseQty_ = BaseQty;SetDirty();                   }
    void           SetBaseValue( double BaseValue )
                   {BaseValue_ = BaseValue;SetDirty();               }
    void           SetCustomerNo( long CustomerNo )
                   {CustomerNo_ = CustomerNo;SetDirty();             }
    void           SetPromotionNo(short PromotionNo )
                   {PromotionNo_ = PromotionNo;SetDirty();           }
    void           SetInternalDiscount(char InternalDiscount )
                   {InternalDiscount_ = InternalDiscount;SetDirty(); }
    void           SetDiscountValuePct( double DiscountValuePct)
                   {DiscountValuePct_ = DiscountValuePct;SetDirty(); }

protected:
    void        Init();

    long          KdAuftragNr_;           // Ordernumber
    long          PosNr_;                 // PosNr
    nString        PharmacyGroupId_   ;    // Pharmacy Group Id
    long          DiscountGrpNo_     ;    // DiscountGroupNumber(Range)
    long          BaseQty_           ;    // Base Quanty
    double       BaseValue_         ;    // Base Value
    long          CustomerNo_        ;    // Customer Number
    short         PromotionNo_       ;    // Promotion Number
    char          InternalDiscount_  ;    // Internal Discount
    double       DiscountValuePct_  ;    // DiscountValuePct

private:
    friend class pxOrderPosPromoList;

};

class pxOrderPosPromoList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxOrderPosPromoList(pxSession *session);
//  destructor:
                virtual ~pxOrderPosPromoList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const long KdAuftragNr, const long PosNr = 0, const int count = 500);
    void        Clear()        {nDBRecordSet::Clear();}
    pxOrderPosPromo* Find(const short PomotionNo);
    double    GetDiscountValuePct();

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:
    friend class pxOrderPosPromoListIter;
};

class pxOrderPosPromoListIter : public nDListCollectIter
{

public:
// constructors:
    pxOrderPosPromoListIter(pxOrderPosPromoList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOrderPosPromoListIter() {;}
};
#endif
