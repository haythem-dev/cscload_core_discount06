/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxcstdiscacc.hpp
CSTDISCACC  class

REVISION HISTORY

05 August 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCSTDISCACC_INC
#define PXCSTDISCACC_INC

#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"
#include <date.hpp>

class nMoney;
struct tCSTDISCACC;

class pxCstDiscAcc : public pxDBRecord
{
public:

// constructors:
                pxCstDiscAcc(pxCstDiscAcc& src);
                pxCstDiscAcc(pxSession *session);
                pxCstDiscAcc(pxSession *session, tCSTDISCACC& src);
                pxCstDiscAcc(pxSession *session, const pxCstDiscAcc* src);
                pxCstDiscAcc(pxSession *session, short BranchNo,
                                                 long  CustomerNo);
                pxCstDiscAcc(pxSession *session, short BranchNo,
                                                 long  CustomerNo,
                                                 nDate& InvoiceDate,
                                                 nString& InvoiceNo,
                                                 nString& VoucherTyp);

// destructor:
                virtual  ~pxCstDiscAcc();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCstDiscAcc&   operator=(const pxCstDiscAcc& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCstDiscAcc&   operator=(const tCSTDISCACC& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCstDiscAcc&
                Assign(pxCstDiscAcc& dest, const tCSTDISCACC& src);
    friend   tCSTDISCACC&
                Assign(tCSTDISCACC& dest, const pxCstDiscAcc& src);

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
    void              SetBalance(double balance)             { Balance_   = balance; SetDirty()      ;}
    void              SetMainCstNo(long MainCstNo)           { MainCstNo_ = MainCstNo; SetDirty()    ;}
    void              SetKdAuftragNr(long KdAuftragNr)       { KdAuftragNr_ = KdAuftragNr; SetDirty();}
    void              SetDate(const nDate& date)             { Date_      = date; SetDirty();         }
    nMoney            IncreaseBalance( nMoney value );
    nMoney            DecreaseBalance( nMoney value );
    void              SetInvoiceNumber(nString& num)         { InvoiceNumber_ = num; SetDirty();      }
    void              SetInvoiceAmount(double value)         { InvoiceAmount_ = value; SetDirty();    }
    void              SetInvoicePaid(double value)           { InvoicePaid_ = value;                  }
    void              SetVoucherTyp(nString& typ)            { VoucherTyp_ = typ; SetDirty();         }
    void              SetPreisTyp(PriceTypeEnum ptyp)        { PreisTyp_ = ptyp; SetDirty();          }
    void              SetPriority(short priority)            { Priority_ = priority; SetDirty();      }
    void              SetKdAuftragNrSplit(long tanu)         { KdAuftragNrSplit_ = tanu; SetDirty();  }
    void              SetPaymentTarget(short target)         { PaymentTarget_ = target; SetDirty();   }
    void              SetLfdNr(long num )                    { LfdNr_ = num; SetDirty();              }
    void              SetRemainInList()                      { RemainInList_ = true;                  }


//  Queries:
    short           BranchNo()         {return BranchNo_             ;}
    long            CustomerNo()       {return CustomerNo_           ;}
    long            MainCstNo()        {return MainCstNo_            ;}
    double          Balance()          {return Balance_              ;}
    long            KdAuftragNr()      {return KdAuftragNr_          ;}
    nDate&          Date()             {return Date_                 ;}
    nString&        InvoiceNumber()    {return InvoiceNumber_        ;}
    double          InvoiceAmount()    {return InvoiceAmount_       ;}
    nString&        VoucherTyp()       {return VoucherTyp_           ;}
    PriceTypeEnum   PreisTyp()         {return PreisTyp_             ;}
    short           Priority()         {return Priority_             ;}
    long            KdAuftragNrSplit() {return KdAuftragNrSplit_     ;}
    double          InvoicePaid()      {return InvoicePaid_          ;}
    short           PaymentTarget()    {return PaymentTarget_        ;}
    long            LfdNr()            {return LfdNr_                ;}

    bool            RemainInList()     {return RemainInList_         ;}
    bool            IsRemainInList()   {return RemainInList_         ;}


//  Methodes
    void            CalcPaymentTarget( long DueDate, long LastPaymentDate);



protected:
    void        Init();

    short      BranchNo_           ;      // Branch Number
    long       CustomerNo_         ;      // Customer Number
    long       MainCstNo_          ;      // Main Customer Number
    double     Balance_            ;      // Saldo
    long       KdAuftragNr_        ;      // Kundenauftragsnummer
    nDate      Date_               ;      // Date of creation
    nString    InvoiceNumber_      ;      // Invoice number
    double     InvoiceAmount_      ;      // Invoice Amount
    nString    VoucherTyp_         ;      // Vouchertyp
    PriceTypeEnum PreisTyp_        ;      // Preistyp
    short      Priority_           ;      // Priority
    long       KdAuftragNrSplit_   ;      // Kundenauftragsnummer Split
    double     InvoicePaid_        ;      // Invoice paid
    short      PaymentTarget_      ;      // PaymentTarget
    long       LfdNr_              ;      // LfdNr(belongs to invoice number)

    bool       RemainInList_       ;      // RemainInList

private:
    friend class pxCstDiscAccList;
};

class pxCstDiscAccList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCstDiscAccList(pxSession *session);
//  destructor:
                virtual ~pxCstDiscAccList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  CustomerNo,
                         const short TaxLevel,
                         const nDate& Date,
                         const int   count  = 1000
                       );
    size_t      Select ( const short BranchNo,
                         const long  CustomerNo,
                         const nDate& DateFrom,
                         const nDate& DateTo,
                         const int   count  = 1000
                       );
    size_t      Select ( const short BranchNo,
                         const long  CustomerNo,
                         const nDate& DateFrom,
                         const nDate& DateTo,
                         const nString& VoucherTyp,
                         const int   count  = 1000
                       );
    size_t      Select ( const long  MainCstNo,
                         const nDate& DateFrom,
                         const nDate& DateTo,
                         const int   count  = 1000
                       );
    size_t      Select ( const long  MainCstNo,
                         const nDate& DateFrom,
                         const nDate& DateTo,
                         const nString& VoucherTyp,
                         const int   count  = 1000
                       );
    size_t      Select ( const long  KdAuftragNr,
                         const int   count  = 1000
                       );
    pxCstDiscAcc* Find( );
    pxCstDiscAcc* Find(const short Branchno, const long CustomerNo,
                       const nDate& InvoiceDate,const nString& InvoiceNo,
                       const nString& VoucherTyp);
    pxCstDiscAcc* Find(const short Branchno, const long CustomerNo,
                       const nString& InvoiceNo, const nString& VoucherTyp, const long LfdNr);
    size_t        ShrinkAndUnlockRemainInList();
    size_t        MarkEntriesRemainInList();
    double        GetBalance( );
    nMoney        IncreaseBalance( nMoney value );
    int           DecreaseBalance( nMoney value );

    nDate&        DateTo()                      {return DateTo_   ;}
    void          SetDateTo(const nDate& DateTo){ DateTo_ = DateTo;}
    void          SetArrayBranchNo(const short brachno);   // methode for  ArrayBranchNo
    short         GetArrayBranchNo(const int index)
                  {return ArrayBranchNo_[index];}           // methode for  ArrayBranchNo
    bool          FindArrayBranchno(const short BranchNo); // methode for  ArrayBranchNo
    short*        ArrayBranchNo()
                  {return ArrayBranchNo_;  }
// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    nDate       DateTo_             ;      // non database member DateTo
    short      ArrayBranchNo_[10];
    int        ArrayBranchNoIndex_;
    friend class pxCstDiscAccListIter;
};

class pxCstDiscAccListIter : public nDListCollectIter
{

public:
// constructors:
    pxCstDiscAccListIter(pxCstDiscAccList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCstDiscAccListIter() {;}
};
#endif
