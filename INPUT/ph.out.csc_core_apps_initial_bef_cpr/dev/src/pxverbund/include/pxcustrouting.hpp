#ifndef PXCUSTROUTING_INC
#define PXCUSTROUTING_INC

#include "pxbase/pxrecord.hpp"
#include <clock.hpp>

struct tCUSTOMERROUTING;

class pxCustRouting : public pxDBRecord
{

public:
// constructors:
                pxCustRouting(pxCustRouting& src);
                pxCustRouting(pxSession *session);
                pxCustRouting(pxSession *session, tCUSTOMERROUTING& src);
                pxCustRouting(pxSession *session, long CustomerNo, short BranchNo,
                                 const nClock& TimeFrom, short WeekDay,
                                 DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxCustRouting();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustRouting&   operator=(const pxCustRouting& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustRouting&   operator=(const tCUSTOMERROUTING& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustRouting&
                Assign(pxCustRouting& dest, const tCUSTOMERROUTING& src);
    friend   tCUSTOMERROUTING&
                Assign(tCUSTOMERROUTING& dest, const pxCustRouting& src);

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
    long            CustomerNo()        {return CustomerNo_      ;}
    short           BranchNo()          {return BranchNo_        ;}
    const nClock&   TimeFrom()  const   {return TimeFrom_        ;}
    const nClock&   TimeTo()    const   {return TimeTo_          ;}
    short           DestBranchNo()      {return DestBranchNo_    ;}
    nString&        DayOfWeek()         {return DayOfWeek_       ;}
    short           WeekDay()           {return WeekDay_         ;}

    bool            TimeInWindow();

protected:
    void        Init();

    long        CustomerNo_        ;      // Customernumber
    short       BranchNo_          ;      // Branchnumber
    nClock      TimeFrom_          ;      // Time from
    nClock      TimeTo_            ;      // Time to
    short       DestBranchNo_      ;      // Destination Branchnumber
    nString     DayOfWeek_         ;      // Day of week string
    short       WeekDay_           ;      // Day of Week short

private:
    friend class pxCustRoutingList;
};

class pxCustRoutingList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCustRoutingList(pxSession *session);
//  destructor:
                virtual ~pxCustRoutingList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

	bool		hasRoutingStartingToday( const short BranchNo, const long CustomerNo, const short DestinationBranchNo );

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long CustomerNo, const short BranchNo,
                         const short WeekDay,
                         const int     count = 50 );
	size_t		SelectRoutingBackward(const long CustomerNo, const short DestinationBranchNo);

    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxCustRoutingListIter;
};

class pxCustRoutingListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustRoutingListIter(pxCustRoutingList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustRoutingListIter() {;}
};
#endif
