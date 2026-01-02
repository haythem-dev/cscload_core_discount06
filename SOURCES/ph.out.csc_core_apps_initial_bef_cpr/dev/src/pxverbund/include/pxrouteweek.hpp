/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxRouteWeek Class.

REVISION HISTORY

10 May   2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXROUTEWEEK_INC
#define PXROUTEWEEK_INC

#include "pxbase/pxrecord.hpp"

struct tTOURPLANWOCHE;

class pxRouteWeek : public pxDBRecord
{

public:


// constructors:
                pxRouteWeek(const pxRouteWeek& src);
                pxRouteWeek(pxSession *session);
                pxRouteWeek(pxSession *session, tTOURPLANWOCHE& src);
                pxRouteWeek(pxSession *session,
                                const short FilialNr,
                                const nString& TourId,
                                const nString& TagesTyp,
                                DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxRouteWeek();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxRouteWeek&   operator=(const pxRouteWeek& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxRouteWeek&   operator=(const tTOURPLANWOCHE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxRouteWeek&
                Assign(pxRouteWeek& dest, const tTOURPLANWOCHE& src);
    friend   tTOURPLANWOCHE&
                Assign(tTOURPLANWOCHE& dest, const pxRouteWeek& src);

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
    short         FilialNr()              {return FilialNr_        ;}
    nString&       TourId()                {return TourId_          ;}
    nString&       TagesTyp ()             {return TagesTyp_        ;}
    short         WeekDay ()              {return WeekDay_         ;}
    long          LagRechTour()   const   {return LagRechTour_     ;}
    short         KarenzZeit()            {return KarenzZeit_      ;}

protected:
    void        Init();

    short         FilialNr_;              // Filialnummer
    nString        TourId_;                // Tourid
    nString        TagesTyp_;              // Tagestyp
    short         WeekDay_;               // DayOfWeek
    long          LagRechTour_;           // Tour Id Lagerrechner
    short         KarenzZeit_;            // Karenzzeit

private:
    friend class pxRouteWeekList;

};

class pxRouteWeekList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxRouteWeekList(pxSession *session);
//  destructor:
                virtual ~pxRouteWeekList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short FilialNr,const nString& TourId,
                         const int count = 300);

    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxRouteWeekListIter;
};

class pxRouteWeekListIter : public nDListCollectIter
{

public:
// constructors:
    pxRouteWeekListIter(pxRouteWeekList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxRouteWeekListIter() {;}
};
#endif
