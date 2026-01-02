#ifndef PXORDERPOSEVENT_INC
#define PXORDERPOSEVENT_INC

#include "pxbase/pxrecord.hpp"
#include <time.hpp>
#include <date.hpp>
#include <clock.hpp>

class pxOrderItem;
struct tKDAUFTRAGPOSEREIGNIS;

class pxOrderPosEvent : public pxDBRecord
{

public:
    enum EventType
    {
       // Event type definitions:
       LeaveAsIs = 0,                   // 0 Caution: do NEVER change this value!!
       EntryInProgress,                 // 1 Booking currently on progress
       UpdateInProgress                 // 2 update in progress
    };
// constructors:
                      pxOrderPosEvent(pxOrderPosEvent& src);
                      pxOrderPosEvent(pxSession *session);
                      pxOrderPosEvent(pxSession *session, tKDAUFTRAGPOSEREIGNIS& src);

                      pxOrderPosEvent(pxOrderItem& Item,
                                   pxOrderPosEvent::EventType PosEreignisArt = pxOrderPosEvent::LeaveAsIs);

                      pxOrderPosEvent(pxSession *session,
                                   long KdAuftragNr,
                                   long PosNr,
                                   nTime DateTime,
                                   pxOrderPosEvent::EventType PosEreignisArt,
                                   DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxOrderPosEvent();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderPosEvent&   operator=(const pxOrderPosEvent& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderPosEvent&   operator=(const tKDAUFTRAGPOSEREIGNIS& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderPosEvent&
                      Assign(      pxOrderPosEvent&       dest,
                             const tKDAUFTRAGPOSEREIGNIS& src);
    friend   tKDAUFTRAGPOSEREIGNIS&
                      Assign(      tKDAUFTRAGPOSEREIGNIS& dest,
                             const pxOrderPosEvent&       src);

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
             pxOrderPosEvent::EventType PosEreignisArt() const
                      {return PosEreignisArt_;}
             long    SendId() const
                      {return SendId_;}
             long    PosNr() const
                      {return PosNr_;}

protected:
             void     Init();

    long          KdAuftragNr_;        // Auftragnr.
    nTime          DateTime_;           // Date/Time stamp
    pxOrderPosEvent::EventType   PosEreignisArt_;
    long          SendId_;
    long          PosNr_;

private:
    friend class pxOrderPosEventList;
};

class pxOrderPosEventList : public nDBRecordSet, public nDListCollect
{

public:
//  constructors:
                      pxOrderPosEventList(pxSession *session);

//  destructor:
    virtual           ~pxOrderPosEventList() {Clear();}

//  member functions:
             pxSession*
                      Session()      { return (pxSession*) DataBase();}

             size_t   Select ( const int  count = 1000 );

             size_t   Select ( const long KdAuftragNr,
                               const int  count =100);
             size_t   Select ( const long KdAuftragNr,
                               const pxOrderPosEvent::EventType event,
                               const int  count);

             size_t   Select ( const tKDAUFTRAGPOSEREIGNIS *recordp,
                               const int               count);

             void     Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxOrderPosEventListIter;
};

class pxOrderPosEventListIter : public nDListCollectIter
{

public:
// constructors:
                      pxOrderPosEventListIter(pxOrderPosEventList& list)
                         : nDListCollectIter(list) {;}
// destructor:
    virtual           ~pxOrderPosEventListIter() {;}

};

#endif
