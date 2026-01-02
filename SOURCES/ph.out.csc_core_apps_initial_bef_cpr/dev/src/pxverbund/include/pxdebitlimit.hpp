#ifndef PXDEBITLIMIT_INC
#define PXDEBITLIMIT_INC

#include "pxbase/pxrecord.hpp"
#include <money.hpp>

struct tDEBTLIMIT;

class pxDebitLimit : public pxDBRecord
{

public:
// constructors:
                pxDebitLimit(pxDebitLimit& src);
                pxDebitLimit(pxSession *session);
                pxDebitLimit(pxSession *session, tDEBTLIMIT& src);
                pxDebitLimit(pxSession *session, long PartnerNo, short LimitType = 0,
                         DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxDebitLimit();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxDebitLimit&   operator=(const pxDebitLimit& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxDebitLimit&   operator=(const tDEBTLIMIT& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxDebitLimit&
                Assign(pxDebitLimit& dest, const tDEBTLIMIT& src);
    friend   tDEBTLIMIT&
                Assign(tDEBTLIMIT& dest, const pxDebitLimit& src);

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

//  Field updates

//  Queries:
    long             PartnerNo()          {return PartnerNo_         ;}
    nString&          PartnerName()        {return PartnerName_       ;}
    nMoney            Limit()              {return Limit_             ;}
    nMoney            SumDebitSide()       {return SumDebitSide_      ;}
    nMoney            SumCreditSide()      {return SumCreditSide_     ;}
    nMoney            SumMonTurnOver()     {return SumMonTurnOver_    ;}
    nMoney            SumDayTurnOver()     {return SumDayTurnOver_    ;}
    nMoney            SumReturns()         {return SumReturns_        ;}
    nMoney            SumGoodsReceipt()    {return SumGoodsReceipt_   ;}
    short            LimitType()          {return LimitType_         ;}
    char             Liste5()             {return Liste5_            ;}

    nMoney      SumAdvanceAccount();      // Sum total credit
    nMoney      IncreaseDayTurnOver( nMoney value );
    nMoney      DecreaseDayTurnOver( nMoney value );
    nMoney      SetSumDebitSide( nMoney value );
    nMoney      IncreaseSumDebitSide( nMoney value );
    nMoney      DecreaseSumDebitSide( nMoney value );
    nMoney      IncreaseSumGoodsReceipt( nMoney value );
    nMoney      DecreaseSumGoodsReceipt( nMoney value );
    nMoney      IncreaseSumReturns( nMoney value );
    nMoney      DecreaseSumReturns( nMoney value );
    nMoney      RestCreditLimit();
    void        SetLimit(nMoney Value )
                { Limit_ = Value; SetDirty();}
    void        SetSumDayTurnOver(nMoney Value )
                { SumDayTurnOver_ = Value; SetDirty();}
    bool        IsListe5() const
                {return Liste5_ == '1';    }
    bool        IsLimitTypeK1() const
                {return LimitType_ == 1;    }
    bool        IsLimitTypeK2() const
                {return LimitType_ == 2;    }

protected:
    void        Init();

    long       PartnerNo_         ;      // Partner Number
    nString     PartnerName_       ;      // Partner Name
    nMoney      Limit_             ;      // Credit Limit
    nMoney      SumDebitSide_      ;      // Sum Debit Side
    nMoney      SumCreditSide_     ;      // Sum Credit Side
    nMoney      SumMonTurnOver_    ;      // Sum Months turnover
    nMoney      SumDayTurnOver_    ;      // Sum Day turnover
    nMoney      SumReturns_        ;      // Sum Returns
    nMoney      SumGoodsReceipt_   ;      // Sum Good Receipts
    short      LimitType_         ;      // LimitType(K1,K2)
    char       Liste5_            ;      // mit Liste 5

private:
    friend class pxDebitLimitList;
};

class pxDebitLimitList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxDebitLimitList(pxSession *session);
//  destructor:
                virtual ~pxDebitLimitList() {Clear();}
//  member functions:
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
    friend class pxDebitLimitListIter;
};

class pxDebitLimitListIter : public nDListCollectIter
{

public:
// constructors:
    pxDebitLimitListIter(pxDebitLimitList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxDebitLimitListIter() {;}
};
#endif
