/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxRouteConsTime Class.

REVISION HISTORY

27 April 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXROUTECONSTIME_INC
   #define PXROUTECONSTIME_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include <clock.hpp>

struct tTOURCONSTIME;

class pxRouteConsTime : public pxDBRecord
{

public:


// constructors:
                pxRouteConsTime(const pxRouteConsTime& src);
                pxRouteConsTime(pxSession *session);
                pxRouteConsTime(pxSession *session, tTOURCONSTIME& src);
                pxRouteConsTime(pxSession *session,
                                const short FilialNr,
                                const nString& TourId,
                                const nDate&   DatumKommi,
                                const nClock&  ConsTime,
                                DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxRouteConsTime();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxRouteConsTime&   operator=(const pxRouteConsTime& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxRouteConsTime&   operator=(const tTOURCONSTIME& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxRouteConsTime&
                Assign(pxRouteConsTime& dest, const tTOURCONSTIME& src);
    friend   tTOURCONSTIME&
                Assign(tTOURCONSTIME& dest, const pxRouteConsTime& src);

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
    nDate          DatumKommi() const      {return DatumKommi_      ;}
    const nClock&  ConsTime  () const      {return ConsTime_        ;}
    char          ProcessState()          {return ProcessState_    ;}

    bool           IsEntryDone()           {return ProcessState_ == '1';}
    void           SetEntryDone()          {ProcessState_ = '1'        ;}

protected:
    void        Init();

    short         FilialNr_;              // Filialnummer
    nString        TourId_;                // Tourid
    nDate          DatumKommi_;            // Datumkommi
    nClock         ConsTime_;              // Consolidation Close Time
    char          ProcessState_;          // Process State 0=not workedup,1= worked up

private:
    friend class pxRouteConsTimeList;

};

class pxRouteConsTimeList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxRouteConsTimeList(pxSession *session);
//  destructor:
                virtual ~pxRouteConsTimeList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short FilialNr,const nString& TourId,
                         const nDate& DatumKommi,
                         const int count = 50);
    size_t      Select ( const short FilialNr,
                         const nDate& DatumKommi,
                         const nClock& ConsTime,
                         const int count = 50);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxRouteConsTimeListIter;
};

class pxRouteConsTimeListIter : public nDListCollectIter
{

public:
// constructors:
    pxRouteConsTimeListIter(pxRouteConsTimeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxRouteConsTimeListIter() {;}
};
#endif
