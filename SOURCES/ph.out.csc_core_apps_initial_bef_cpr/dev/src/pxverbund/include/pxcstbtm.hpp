/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXCSTBTM.HPP
CustBusinessTimes Class.

REVISION HISTORY

22 Nov 1995 V1.00 REV 00 written by Peter Hoernich.
*/

#ifndef PXCSTBTM_INC
#define PXCSTBTM_INC

#include "pxbase/pxrecord.hpp"
#include <clock.hpp>
#include <date.hpp>

struct tKDBETRIEBSENDE;

class pxCustBusinessTimes : public pxDBRecord
{

public:
//  Constructors:
                      pxCustBusinessTimes(pxSession *session);
//  Normal constructor
                      pxCustBusinessTimes(pxSession *session, short VZNr, long KdNr);
//  Constructs instance with default values
                      pxCustBusinessTimes(pxCustBusinessTimes& src);
//  Copy constructor
                      pxCustBusinessTimes(pxSession *session, tKDBETRIEBSENDE& src);
//  Constructs instance with values stored in src record
                      pxCustBusinessTimes(pxSession *session,
                                          short VZNr,
                                          long KdNr,
                                          short WeekDay,
                                          DBAccessMode mode = cDBGET_READONLY);
//  Constructs instance by reading record from database

//  destructor:
                virtual  ~pxCustBusinessTimes();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustBusinessTimes&   operator=(const pxCustBusinessTimes& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustBusinessTimes&   operator=(const tKDBETRIEBSENDE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustBusinessTimes&
                      Assign(pxCustBusinessTimes& dest,
                             const tKDBETRIEBSENDE& src);
    friend   tKDBETRIEBSENDE&
                      Assign(tKDBETRIEBSENDE& dest,
                             const pxCustBusinessTimes& src);
//  Functions for data exchange between object and record.

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
//  Compare function for sorting pxCustBusinessTimesList.

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
//  Reads data from database

    virtual  int     Put();
//  Writes data to database


//  Queries:
    long             KundenNr () const    {return KundenNr_;   }
    short            Vertriebszentrum () const    {return VertriebszentrumNr_;   }
    const nString&    TagesTyp () const    {return TagesTyp_;   }
    const nClock&     BeginAM  () const    {return ZeitBeginAM_;}
    const nClock&     EndAM    () const    {return ZeitEndeAM_; }
    const nClock&     BeginPM  () const    {return ZeitBeginPM_;}
    const nClock&     EndPM    () const    {return ZeitEndePM_; }
          short      WeekDay  () const    {return WeekDay_;    }

protected:
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
//  Database access functions.

    void              Init();
//  Initiates object's values.

    long             IDFNr_;           // Kundennummer IDF
    short            VertriebszentrumNr_;  // Vertriebszentrum
    long             KundenNr_;            // Kundennummer
    nString           TagesTyp_;        // Tagestyp
    nClock            ZeitBeginAM_;     // Zeit Betriebsanfang morgens
    nClock            ZeitEndeAM_;      // Zeit Betriebsende morgens
    nClock            ZeitBeginPM_;     // Zeit Betriebsanfang abends
    nClock            ZeitEndePM_;      // Zeit Betriebsende abends
    short            WeekDay_;         // Day of Week

private:
    friend class pxCustBusinessTimesList;
};

class pxCustBusinessTimesList : public nDBRecordSet, public nDListCollect
{

public:
//  constructor:
                      pxCustBusinessTimesList(pxSession *session);

//  destructor:
    virtual           ~pxCustBusinessTimesList() {Clear();}

//  member functions:
             pxSession*
                      Session()      { return (pxSession*) DataBase();}

             size_t   Select ( const short VZNr,
                               const long KdNr,
                               const int  count = 50 );
//  Reads all table entries with matching IDFNr into list,
//  calculates the "day of week" numbers and sorts list by them.

             pxCustBusinessTimes* Find( short weekday);
//  Returns pointer to list entry with matching "day of week" number.

             pxCustBusinessTimes* Find( nDate date );
//  Returns pointer to list entry with business times for 'date'.

             pxCustBusinessTimes* ThisDay();
//  Returns pointer to list entry with today's business times.

             void     Clear()        {nDBRecordSet::Clear();}
//  Removes and deletes all list entries

protected:

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxCustBusinessTimesListIter;
};

class pxCustBusinessTimesListIter : public nDListCollectIter
{

public:
// constructors:
                      pxCustBusinessTimesListIter(pxCustBusinessTimesList& list)
                         : nDListCollectIter(list) {;}
// destructor:
    virtual           ~pxCustBusinessTimesListIter() {;}


};

#endif
