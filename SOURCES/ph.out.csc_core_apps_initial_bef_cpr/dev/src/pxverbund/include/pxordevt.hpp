#ifndef PXORDEVT_INC
#define PXORDEVT_INC

#include "pxbase/pxrecord.hpp"
#include <time.hpp>
#include <date.hpp>
#include <clock.hpp>
#include "pxorder.hpp"

struct tKDAUFTRAGEREIGNIS;

class pxOrderEvent : public pxDBRecord
{

public:
// constructors:
                      pxOrderEvent(pxOrderEvent& src);
                      pxOrderEvent(pxSession *session);
                      pxOrderEvent(pxSession *session, tKDAUFTRAGEREIGNIS& src);

                      pxOrderEvent(pxOrder& Order,
                                   Order::States Event = Order::LeaveAsIs);

                      pxOrderEvent(pxSession *session,
                                   long KdAuftragNr,
                                   nTime DateTime,
                                   Order::States Event,
                                   DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxOrderEvent();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderEvent&   operator=(const pxOrderEvent& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderEvent&   operator=(const tKDAUFTRAGEREIGNIS& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderEvent&
                      Assign(      pxOrderEvent&       dest,
                             const tKDAUFTRAGEREIGNIS& src);
    friend   tKDAUFTRAGEREIGNIS&
                      Assign(      tKDAUFTRAGEREIGNIS& dest,
                             const pxOrderEvent&       src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

    void              Print();

    virtual  int     Read     (const void *record);
    virtual  int     ReadLock (const void *record);
    virtual  int     Insert   (const void *record);
    virtual  int     Update   (const void *record);

//  Queries:
             long    KdAuftragNr() const
                      {return KdAuftragNr_;}
             nTime&   DateTime   ()
                      {return DateTime_;}
             nDate    Date       () const
                      {return nDate(DateTime_);}
             nClock   Clock      () const
                      {return nClock(DateTime_);}
             Order::States Event() const
                      {return Event_;}
             long    PersonalNr ()
                      {return PersonalNr_;}
             nString& GeraetName ()
                      {return GeraetName_;}
             short   FilialNr()
                      {return FilialNr_ ;}
             pxEventReason::EventCodes EventCode()
                      {return EventCode_;}
             void    SetEvent( Order::States evnt)
                     { Event_ = evnt;  }

protected:
             void     Init();

    long                      KdAuftragNr_;        // Auftragnr.
    nTime                     DateTime_;           // Date/Time stamp
    Order::States             Event_;
    long                      PersonalNr_;
    nString                   GeraetName_;
    short                     FilialNr_;
    pxEventReason::EventCodes EventCode_;

private:
    friend class pxOrderEventList;
};

class pxOrderEventList : public nDBRecordSet, public nDListCollect
{

public:
//  constructors:
                      pxOrderEventList(pxSession *session);

//  destructor:
    virtual           ~pxOrderEventList() {Clear();}

//  member functions:
             pxSession*
                      Session()      { return (pxSession*) DataBase();}

             size_t   Select ( const int  count = 1000 );

             size_t   Select ( const long KdAuftragNr,
                               const int  count =100);
             size_t   Select ( const long KdAuftragNr,
                               const Order::States event,
                               const int  count);

             size_t   Select ( const tKDAUFTRAGEREIGNIS *recordp,
                               const int               count);

             void     Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxOrderEventListIter;
};

class pxOrderEventListIter : public nDListCollectIter
{

public:
// constructors:
                      pxOrderEventListIter(pxOrderEventList& list)
                         : nDListCollectIter(list) {;}
// destructor:
    virtual           ~pxOrderEventListIter() {;}

};

#endif
