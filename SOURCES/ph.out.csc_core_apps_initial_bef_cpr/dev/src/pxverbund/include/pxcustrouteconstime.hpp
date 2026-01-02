/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxCustRouteConsTime Class.

REVISION HISTORY

28 April 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCUSTROUTECONSTIME_INC
   #define PXCUSTROUTECONSTIME_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include <clock.hpp>

struct tTOURPLANCONSTIME;

class pxCustRouteConsTime : public pxDBRecord
{

public:


// constructors:
                pxCustRouteConsTime(const pxCustRouteConsTime& src);
                pxCustRouteConsTime(pxSession *session);
                pxCustRouteConsTime(pxSession *session, tTOURPLANCONSTIME& src);
                pxCustRouteConsTime(pxSession *session,
                                    const short VertriebszentrumNr,
                                    const long  KundenNr,
                                    const nString& TourId,
                                    const nDate&   DatumKommi,
                                    const nClock&  ConsTime,
                                    DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxCustRouteConsTime();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustRouteConsTime&   operator=(const pxCustRouteConsTime& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustRouteConsTime&   operator=(const tTOURPLANCONSTIME& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustRouteConsTime&
                Assign(pxCustRouteConsTime& dest, const tTOURPLANCONSTIME& src);
    friend   tTOURPLANCONSTIME&
                Assign(tTOURPLANCONSTIME& dest, const pxCustRouteConsTime& src);

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
    short         VertriebszentrumNr()    {return VertriebszentrumNr_ ;}
    long          KundenNr()              {return KundenNr_           ;}
    nString&       TourId()                {return TourId_             ;}
    nDate          DatumKommi() const      {return DatumKommi_         ;}
    const nClock&  ConsTime  () const      {return ConsTime_           ;}
    char          ProcessState()          {return ProcessState_       ;}

    bool           IsEntryDone()           {return ProcessState_ == '1';}
    void           SetEntryDone()          {ProcessState_ = '1'        ;}

protected:
    void        Init();

    short         VertriebszentrumNr_;    // Filialnummer
    long          KundenNr_;              // Kundennummer
    nString        TourId_;                // Tourid
    nDate          DatumKommi_;            // Datumkommi
    nClock         ConsTime_;              // Consolidation Close Time
    char          ProcessState_;          // Process State 0=not workedup,1= worked up

private:
    friend class pxCustRouteConsTimeList;

};

class pxCustRouteConsTimeList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCustRouteConsTimeList(pxSession *session);
//  destructor:
                virtual ~pxCustRouteConsTimeList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short FilialNr,const long KundeNr,
                         const nString& TourId,
                         const nDate& DatumKommi,
                         const int count = 50);
    size_t      Select ( const short FilialNr,
                         const nDate& DatumKommi,
                         const nClock& ConsTime,
                         const char  ProcessState,
                         const int count = cDEFAULT);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxCustRouteConsTimeListIter;
};

class pxCustRouteConsTimeListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustRouteConsTimeListIter(pxCustRouteConsTimeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustRouteConsTimeListIter() {;}
};
#endif
