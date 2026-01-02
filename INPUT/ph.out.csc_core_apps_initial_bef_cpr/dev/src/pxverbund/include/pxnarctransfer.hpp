/*----------------------------------------------------------------------------*/

#ifndef PXNARCTRANSFER_INC
#define PXNARCTRANSFER_INC

/*----------------------------------------------------------------------------*/

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include <clock.hpp>

/*----------------------------------------------------------------------------*/

struct tNARCTRANSACTIONTRANSFER;

/*----------------------------------------------------------------------------*/

class pxNarcTransfer : public pxDBRecord
{

public:
// constructors:
                      pxNarcTransfer(pxNarcTransfer& src);
                      pxNarcTransfer(pxSession *session);
                      pxNarcTransfer(pxSession *session, const tNARCTRANSACTIONTRANSFER& src);
                      pxNarcTransfer(pxSession *session,
                                     const short  BranchNo,
                                     const long   ArticleNo,
                                     const long   OrderNo,
                                     const long   PosNo
                                     );
// destructor:
    virtual           ~pxNarcTransfer();

// public member operators
    pxNarcTransfer&    operator=(const pxNarcTransfer& src);
    pxNarcTransfer&    operator=(const tNARCTRANSACTIONTRANSFER& src);

// public member functions
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();


//  Field updates
    void              BranchNo( short company)
                      {BranchNo_  = company;                }
    void              ArticleNo( long ArticleNo)
                      {ArticleNo_ = ArticleNo;              }
    void              TransactionDate( nDate& date)
                      {TransactionDate_ = date;             }
    void              TransactionTime ( nClock& time)
                      {TransactionTime_ = time;             }
    void              CustomerSupplierNo( long customerno)
                      {CustomerSupplierNo_  = customerno;   }
    void              TransactionType( nString& transtype)
                      {TransactionType_  = transtype;       }
    void              PurchaseOrderNo( long Porderno)
                      {PurchaseOrderNo_  = Porderno;        }
    void              QtyTransaction( long Qtytrans )
                      {QtyTransaction_ = Qtytrans;          }
    void              QtyInStock( long Qtyinstock)
                      {QtyInStock_ = Qtyinstock;            }
    void              CompletedFlag( char flag)
                      {CompletedFlag_ = flag;               }
    void              PosNo( long PosNo)
                      {PosNo_ = PosNo;                      }
    void              SetTourId(const nString& tourid)
                      {TourId_ = tourid;                    }

// Queries:
             long          TransferID         ()  {return TransferID_         ;}
             short         BranchNo           ()  {return BranchNo_           ;}
             long          ArticleNo          ()  {return ArticleNo_          ;}
             nDate&        TransactionDate    ()  {return TransactionDate_    ;}
             const nClock& TransactionTime    ()  {return TransactionTime_    ;}
             long          CustomerSupplierNo ()  {return CustomerSupplierNo_ ;}
             nString&      TransactionType    ()  {return TransactionType_    ;}
             long          PurchaseOrderNo    ()  {return PurchaseOrderNo_    ;}
             long          OrderNo            ()  {return OrderNo_            ;}
             long          QtyTransaction     ()  {return QtyTransaction_     ;}
             long          QtyInStock         ()  {return QtyInStock_         ;}
             char          CompletedFlag      ()  {return CompletedFlag_      ;}
             long          PosNo              ()  {return PosNo_              ;}
             nString&      TourId             ()  {return TourId_             ;}

protected:
                      pxNarcTransfer();
    friend
    pxNarcTransfer&     Assign(pxNarcTransfer& dest, const tNARCTRANSACTIONTRANSFER& src);
    friend
    tNARCTRANSACTIONTRANSFER&    Assign(tNARCTRANSACTIONTRANSFER& dest, const pxNarcTransfer& src);

    void              Init();
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

/*----------------------------------------------------------------------------*/
/*  Data members.                                                             */
/*----------------------------------------------------------------------------*/
    long             TransferID_;         // Laufende Nummer(type serial)
    short            BranchNo_;           // Filialnummer
    long             ArticleNo_;          // Artikelnummer
    nDate            TransactionDate_;    // date
    nClock           TransactionTime_;    // time
    long             CustomerSupplierNo_; // customerid or supplierno
    nString          TransactionType_;    // transactiontyp (WE...etc)
    long             PurchaseOrderNo_;    // VSE Orderno/orderno supplier
    long             OrderNo_;            // ordernumber orderentry
    long             QtyTransaction_;     // quantity delivered from stock
    long             QtyInStock_;         // quantity current in stock
    char             CompletedFlag_;      // complete flag 1 = complete, 0 = not complete
    long             PosNo_;              // positionnumber
    nString          TourId_;             // Tour Identifikation

private:
    friend class pxNarcTransferList;
};

class pxNarcTransferList : public nDBRecordSet, public nDListCollect
{

public:
//  constructors:
                pxNarcTransferList(pxSession *session);
//  destructor:
                virtual ~pxNarcTransferList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int    count = 500);
    size_t      Select ( const short  BranchNo, const long ArticleNo,
                         const long   OrderNo,
                         const int    count  = 500);
    size_t      Select ( const short  BranchNo, const long OrderNo,
                         const int    count  = 500);
    size_t      Select ( const long   OrderNo, const long PosNo,
                         const int    count  = 500);

    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxNarcTransferListIter;
};

class pxNarcTransferListIter : public nDListCollectIter
{

public:
// constructors:
    pxNarcTransferListIter(pxNarcTransferList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxNarcTransferListIter() {;}
};
#endif
