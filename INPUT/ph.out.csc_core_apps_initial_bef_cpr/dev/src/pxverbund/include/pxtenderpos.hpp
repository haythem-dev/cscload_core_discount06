/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxtenderpos.hpp
TENDERPOS  class

REVISION HISTORY

16 Sept 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXTENDERPOS_INC
   #define PXTENDERPOS_INC

#include "pxbase/pxrecord.hpp"
#include <money.hpp>
#include <date.hpp>

struct tTENDERPOS;

class pxTenderPos : public pxDBRecord
{

public:
// constructors:
                pxTenderPos(pxTenderPos& src);
                pxTenderPos(pxSession *session);
                pxTenderPos(pxSession *session, tTENDERPOS& src);
                pxTenderPos(pxSession *session, const pxTenderPos* src);
                pxTenderPos(pxSession *session, long TenderNo,
                                                long ArticleNo);

// destructor:
                virtual  ~pxTenderPos();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxTenderPos&   operator=(const pxTenderPos& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxTenderPos&   operator=(const tTENDERPOS& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxTenderPos&
                Assign(pxTenderPos& dest, const tTENDERPOS& src);
    friend   tTENDERPOS&
                Assign(tTENDERPOS& dest, const pxTenderPos& src);

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
    long            TenderNo()      {return TenderNo_             ;}
    long            ArticleNo()     {return ArticleNo_            ;}
    long            ContractQty()   {return ContractQty_          ;}
    nMoney          ContractPrice() {return ContractPrice_        ;}
    long            RemainingLife() {return RemainingLife_        ;}
    double          AddDiscountPct(){return AddDiscountPct_       ;}
    nMoney          Aep()           {return Aep_                  ;}
    char            TenderState()   {return TenderState_          ;}
    nDate&          ChangeDate()    {return ChangeDate_           ;}
    nString&        NameOfUser()    {return NameOfUser_           ;}
    double          PriceDiff()     {return PriceDiff_            ;}


    bool            IsAutoBlocked() { return TenderState_ == '9';}

// Set Methodes
   void             SetAutoBlock()  { TenderState_ =  '9'; ChangeDate_ = nDate(); SetDirty(); }
   void             SetUnblocked()  { TenderState_ =  '1'; ChangeDate_ = nDate(); SetDirty(); }

protected:
    void        Init();

    long        TenderNo_           ;      // Tender Number
    long        ArticleNo_          ;      // ArticleNo
    long        ContractQty_        ;      // ContractQty
    nMoney      ContractPrice_      ;      // Contract Price
    long        RemainingLife_      ;      // Remaining Life in months
    double      AddDiscountPct_     ;      // AddDiscountPct
    nMoney      Aep_                ;      // Aep
    char        TenderState_        ;      // Tender State
                                           // 1 = Normal
                                           // 8 = Blocked Manual
                                           // 9 = Blocked Automaticly
    nDate       ChangeDate_         ;      // Date of change
    nString     NameOfUser_         ;      // name of user
    double      PriceDiff_          ;      // Price difference

private:
    friend class pxTenderPosList;
};

class pxTenderPosList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxTenderPosList(pxSession *session);
//  destructor:
                virtual ~pxTenderPosList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long TenderNo,
                         const long ArticleNo,
                         const int   count  = 1000
                       );
    size_t      Select ( const long TenderNo,
                         const char TenderState,
                         const int   count  = 1000
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

    friend class pxTenderPosListIter;
};

class pxTenderPosListIter : public nDListCollectIter
{

public:
// constructors:
    pxTenderPosListIter(pxTenderPosList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxTenderPosListIter() {;}
};
#endif
