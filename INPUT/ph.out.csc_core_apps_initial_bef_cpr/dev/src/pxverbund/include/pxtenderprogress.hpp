/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxtenderprogress.hpp
TENDEROROGRESS  class

REVISION HISTORY

17 Sept 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXTENDERPROGRESS_INC
   #define PXTENDERPROGRESS_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include <money.hpp>
#include <libbasarcmnutil_bstring.h>

struct tTENDERPROGRESS;

class pxTenderProgress : public pxDBRecord
{

public:

// constructors:
                pxTenderProgress(pxTenderProgress& src);
                pxTenderProgress(pxSession *session);
                pxTenderProgress(pxSession *session, tTENDERPROGRESS& src);
                pxTenderProgress(pxSession *session, const pxTenderProgress* src);
                pxTenderProgress(pxSession *session, long TenderNo,
                                                     long ArticleNo,
                                                     long KdAuftragNr,
                                                     nDate& OrderDate,
                                                     long  PosNr
                                     );

// destructor:
                virtual  ~pxTenderProgress();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxTenderProgress&   operator=(const pxTenderProgress& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxTenderProgress&   operator=(const tTENDERPROGRESS& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxTenderProgress&
                Assign(pxTenderProgress& dest, const tTENDERPROGRESS& src);
    friend   tTENDERPROGRESS&
                Assign(tTENDERPROGRESS& dest, const pxTenderProgress& src);

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
    long           TenderNo()      {return TenderNo_             ;}
    long           ArticleNo()     {return ArticleNo_            ;}
    long           KdAuftragNr()   {return KdAuftragNr_          ;}
    nDate&          OrderDate()     {return OrderDate_            ;}
    long           DeliveryQty()   {return DeliveryQty_          ;}
    nMoney          ChargedPrice()  {return ChargedPrice_         ;}
    long           PosNr()         {return PosNr_                ;}
    long           ReturnQty()     {return ReturnQty_            ;}

	long		OrderTime() { return OrderTime_; }
    long		CustomerNo() { return CustomerNo_; }
    nMoney		AEP() { return AEP_; }
    long		BookingTenderNo() { return BookingTenderNo_; }
    long		InvoiceNo() { return InvoiceNo_; }
    long		InvoiceDate() { return InvoiceDate_; }
    const basar::VarString &	KdAuftragArt() { return KdAuftragArt_; }
    nMoney		GEP() { return GEP_; }
    long		InvoiceTime() { return InvoiceTime_; }
    short		BranchNo() { return BranchNo_; }
    double		DiscountPct() { return DiscountPct_; }


// Set Methodes
   void             SetDeliveryQty( const long Qty)
                    { DeliveryQty_ = Qty;}
   void             SetChargedPrice( const nMoney& price)
                    { ChargedPrice_ = price; }
   void             SetPosNr( const long num)
                    { PosNr_ = num;          }
   void             SetReturnQty( const long qty)
                    { ReturnQty_ = qty;      }
   void             SetChangeDate( const nDate & changeDate )
                    { ChangeDate_ = changeDate;      }

   void SetOrderTime( const long OrderTime ) { OrderTime_ = OrderTime; }
   void SetCustomerNo( const long CustomerNo ) { CustomerNo_ = CustomerNo; }
   void SetAEP( const nMoney & AEP ) { AEP_ = AEP; }
   void SetBookingTenderNo( const long BookingTenderNo ) { BookingTenderNo_ = BookingTenderNo; }
   void SetInvoiceNo( const long InvoiceNo ) { InvoiceNo_ = InvoiceNo; }
   void SetInvoiceDate( const long InvoiceDate ) { InvoiceDate_ = InvoiceDate; }
   void SetKdAuftragArt( const basar::VarString & KdAuftragArt ) { KdAuftragArt_ = KdAuftragArt; }
   void SetGEP( const nMoney & GEP ) { GEP_ = GEP; }
   void SetInvoiceTime( const long InvoiceTime ) { InvoiceTime_ = InvoiceTime; }
   void SetBranchNo( const short BranchNo ) { BranchNo_ = BranchNo; }   
   void SetDiscountPct( const double DiscountPct ) { DiscountPct_ = DiscountPct; }

protected:
    void        Init();

    long				TenderNo_           ;      // Tender Number
    long				ArticleNo_          ;      // ArticleNo
    long				KdAuftragNr_        ;      // KdAuftragNr
    nDate				OrderDate_          ;      // OrderDate
    long				DeliveryQty_        ;      // DeliveryQty
    nMoney				ChargedPrice_       ;      // ChargedPrice
    long				PosNr_              ;      // Position number
    long				ReturnQty_          ;      // Return Quantity(Gutschriften)
    long				OrderTime_;
    long				CustomerNo_;
    nMoney				AEP_;
    long				BookingTenderNo_;
    long				InvoiceNo_;
    long				InvoiceDate_;
    basar::VarString	KdAuftragArt_;
    nMoney				GEP_;
    long				InvoiceTime_;
    short				BranchNo_;
    double				DiscountPct_;
    nDate				ChangeDate_;

private:
    friend class pxTenderProgressList;
};

class pxTenderProgressList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxTenderProgressList(pxSession *session);
//  destructor:
                virtual ~pxTenderProgressList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 500 );

    size_t      Select ( const long ArticleNo,
                         const long KdAuftragNr,
                         const nDate& OrderDate,
                         const int   count  = cDEFAULT
                       );

    size_t      Select ( const long TenderNo,
                         const long ArticleNo,
                         const long KdAuftragNr,
                         const nDate& OrderDate,
                         const int   count  = cDEFAULT
                       );
    size_t      Select ( const long TenderNo,
                         const long ArticleNo,
                         const int   count  = cDEFAULT
                       );
    long       SumDeliveryQty();
    long       SumReturnQty();

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxTenderProgressListIter;
};

class pxTenderProgressListIter : public nDListCollectIter
{

public:
// constructors:
    pxTenderProgressListIter(pxTenderProgressList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxTenderProgressListIter() {;}
};
#endif
