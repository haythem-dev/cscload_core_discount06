/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

 pxcpvalidityperiod.hpp
 CPVALIDITYPERIOD

REVISION HISTORY

18 Aug 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCPVALIDITYPERIOD_INC
   #define PXCPVALIDITYPERIOD_INC


#include "pxbase/pxrecord.hpp"
#include <date.hpp>

struct tCPVALIDITYPERIOD;

class pxCPValidityPeriod : public pxDBRecord
{

public:


/*----------------------------------------------------------------------------*/
/*  CPValidityPeriod Type enumeration.                                        */
/*----------------------------------------------------------------------------*/
enum  tCPValidityPeriodType
{
   PeriodType_Default,               // default type                  = 0
   PeriodType_NoActivity,            // No Activity                   = 1
   PeriodType_AddMembers,            // add members                   = 2
   PeriodType_ReplaceByMembers,      // replace by members (BG Promo) = 3
   PeriodType_ReplaceDiscArticle     // owner is discountarticle      = 4
};



// constructors:
                pxCPValidityPeriod(pxCPValidityPeriod& src);
                pxCPValidityPeriod(pxSession *session);
                pxCPValidityPeriod(pxSession *session, tCPVALIDITYPERIOD& src);
                pxCPValidityPeriod(pxSession *session, const pxCPValidityPeriod* src);

// destructor:
                virtual  ~pxCPValidityPeriod();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCPValidityPeriod&   operator=(const pxCPValidityPeriod& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCPValidityPeriod&   operator=(const tCPVALIDITYPERIOD& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCPValidityPeriod&
                Assign(pxCPValidityPeriod& dest, const tCPVALIDITYPERIOD& src);
    friend   tCPVALIDITYPERIOD&
                Assign(tCPVALIDITYPERIOD& dest, const pxCPValidityPeriod& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

//  Queries:
    long           ArticleNoPack()     {return ArticleNoPack_   ;}
    nDate&          DateFrom()          {return DateFrom_        ;}
    nDate&          DateTo()            {return DateTo_          ;}
    short          Type()              {return Type_            ;}

    bool            IsNoActivity()        {return Type_ == PeriodType_NoActivity          ;}
    bool            IsAddMembers()        {return Type_ == PeriodType_AddMembers          ;}
    bool            IsReplaceByMembers()  {return Type_ == PeriodType_ReplaceByMembers    ;}
    bool            IsReplaceDiscArticle(){return Type_ == PeriodType_ReplaceDiscArticle  ;}

// Set Methodes


protected:
    void        Init();

    long       ArticleNoPack_     ;      // Article number Pack(Steller(Pseudoartikelno)
    nDate       DateFrom_          ;      // Date from
    nDate       DateTo_            ;      // Date to
    short      Type_              ;      // Type

private:
    friend class pxCPValidityPeriodList;
};

class pxCPValidityPeriodList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCPValidityPeriodList(pxSession *session);
//  destructor:
                virtual ~pxCPValidityPeriodList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long  ArticleNoPack,
                         const int   count  = 100
                       );

    int        ReduceToValidEntries();
// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxCPValidityPeriodListIter;
};

class pxCPValidityPeriodListIter : public nDListCollectIter
{

public:
// constructors:
    pxCPValidityPeriodListIter(pxCPValidityPeriodList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCPValidityPeriodListIter() {;}
};
#endif
