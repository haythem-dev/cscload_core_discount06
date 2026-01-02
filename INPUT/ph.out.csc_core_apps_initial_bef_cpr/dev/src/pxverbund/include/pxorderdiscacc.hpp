/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxorderdiscacc.hpp
KDAUFTRAGDISCACC  class

REVISION HISTORY

08 January 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXORDERDISCACC_INC
   #define PXORDERDISCACC_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include <money.hpp>

struct tKDAUFTRAGDISCACC;

class pxOrderDiscAcc : public pxDBRecord
{

public:

// constructors:
                pxOrderDiscAcc(pxOrderDiscAcc& src);
                pxOrderDiscAcc(pxSession *session);
                pxOrderDiscAcc(pxSession *session, tKDAUFTRAGDISCACC& src);
                pxOrderDiscAcc(pxSession *session, const pxOrderDiscAcc* src);
                pxOrderDiscAcc(pxSession *session, short BranchNo,
                                                   long  KdauftragNr);

// destructor:
                virtual  ~pxOrderDiscAcc();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderDiscAcc&   operator=(const pxOrderDiscAcc& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderDiscAcc&   operator=(const tKDAUFTRAGDISCACC& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderDiscAcc&
                Assign(pxOrderDiscAcc& dest, const tKDAUFTRAGDISCACC& src);
    friend   tKDAUFTRAGDISCACC&
                Assign(tKDAUFTRAGDISCACC& dest, const pxOrderDiscAcc& src);

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
    void              SetKdAuftragNr(const long KdAuftragNr){ KdAuftragNr_ = KdAuftragNr; SetDirty();}
    void              SetSwChain(const short SwChain)       { SwChain_ = SwChain; SetDirty()        ;}
    void              SetDateFrom(const nDate& DateFrom)     { DateFrom_ = DateFrom; SetDirty()      ;}
    void              SetDateTo(const nDate& DateTo)         { DateTo_ = DateTo; SetDirty()          ;}
    void              SetBranchNo(const short BranchNo)     { BranchNo_ = BranchNo; SetDirty()      ;}
    nMoney            IncreaseBalance( nMoney value );
    nMoney            DecreaseBalance( nMoney value );

//  Queries:
    long           KdAuftragNr()   {return KdAuftragNr_           ;}
    short          SwChain()       {return SwChain_               ;}
    nDate&          DateFrom()      {return DateFrom_              ;}
    nDate&          DateTo()        {return DateTo_                ;}
    short          BranchNo()      {return BranchNo_              ;}


// Set Methodes


protected:
    void        Init();

    long       KdAuftragNr_        ;      // Kundenauftragsnummer
    short      SwChain_            ;      // Switch Chain
    nDate       DateFrom_           ;      // Date from
    nDate       DateTo_             ;      // Date to
    short      BranchNo_           ;      // Branch Number


private:
    friend class pxOrderDiscAccList;
};

class pxOrderDiscAccList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxOrderDiscAccList(pxSession *session);
//  destructor:
                virtual ~pxOrderDiscAccList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  KdAuftragNr,
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

    friend class pxOrderDiscAccListIter;
};

class pxOrderDiscAccListIter : public nDListCollectIter
{

public:
// constructors:
    pxOrderDiscAccListIter(pxOrderDiscAccList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOrderDiscAccListIter() {;}
};
#endif
