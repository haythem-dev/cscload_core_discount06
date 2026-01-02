/*----------------------------------------------------------------------------*/

#ifndef PXSTKTRA_INC
#define PXSTKTRA_INC

/*----------------------------------------------------------------------------*/

#include "pxbase/pxrecord.hpp"
#include "types/bookingtypeenum.inc"

/*----------------------------------------------------------------------------*/

struct tBUCHUNGSART;

/*----------------------------------------------------------------------------*/

class pxStockTrans : public pxDBRecord
{

public:


// constructors:
                pxStockTrans();
                pxStockTrans(pxSession *session);
                pxStockTrans(pxStockTrans& src);
                pxStockTrans(pxSession *session,tBUCHUNGSART& src);
                pxStockTrans(pxSession *session, const pxStockTrans* src);
                pxStockTrans(pxSession *session,short BranchNo,char BuchungsArt, DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxStockTrans();

    pxStockTrans&   operator=(const pxStockTrans& src);
    pxStockTrans&   operator=(const tBUCHUNGSART& src);
    friend pxStockTrans& Assign(pxStockTrans& dest, const tBUCHUNGSART& src);
    friend tBUCHUNGSART&  Assign(tBUCHUNGSART& dest, const pxStockTrans& src);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
             int  Compare(const char buchart);
             nString& Bezeichnung()     {return Bezeichnung_;}
             char BuchArt() const { return BuchArt_; }
             short BranchNo()         { return BranchNo_;}

             bool  IsDebit() const
                   { return ((BuchMethode_ == StockDebit) ||
                     (BuchMethode_ == StockDebitAndDemand));
                   }
             bool  IsDefaultTransaction() const
                   {return ((BuchMethode_ == StockDebitAndDemand));}
             bool  IsDemand() const
                   {return ((BuchMethode_ == StockDemand) ||
                            (BuchMethode_ == StockDebitAndDemand));}
             bool  IsNoTransaction() const
                   {return ((BuchMethode_ == StockNoTransaction));}
             bool  IsReturn() const
                   {return ((BuchMethode_ == StockReturn));}

             BookingTypeEnum StockTransactionCode() const
                                   {return BuchMethode_;}

protected:
    void            Init();
    virtual  int    Read(const void *record);
    virtual  int    Insert(const void *record);
    virtual  int    Update(const void *record);
    virtual  int    ReadLock(const void *record);

    char            BuchArt_;         // Buchungs-Art (key value)
    nString         Bezeichnung_;     // Beschreibung in Klartext
    short           BranchNo_;        // Branchnumber
    BookingTypeEnum BuchMethode_;     // Bewegungsart Lagerkonto

private:
    friend class pxStockTransList;
};

class pxStockTransList : public nDListCollect, public nDBRecordSet
{

public:

                         pxStockTransList(pxSession *session);
   virtual               ~pxStockTransList() {Clear();}
             pxSession*  Session()       { return (pxSession*) DataBase();}
             size_t      Select (const short BranchNo = 0, const int count = 50 );
             short      Find( const short BranchNo );
             void        Clear()        {nDBRecordSet::Clear();}
             pxStockTrans*  Find( const char BuchungsArt,const short BranchNo);
    virtual  int        EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int        GetNext(const void* record, const int cursorid);
    virtual  int        StartBrowse(const void *keys, const int cursorid);
//@CE
protected:

private:
    friend class pxStockTransListIter;
};

class pxStockTransListIter : public nDListCollectIter
{
public:
    pxStockTransListIter(pxStockTransList& list) : nDListCollectIter(list) {;}
    virtual  ~pxStockTransListIter() {;}
};


#endif
