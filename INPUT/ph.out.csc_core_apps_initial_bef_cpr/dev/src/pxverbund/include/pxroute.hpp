/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXROUTE.HPP
Classes dealing with routes scheduled for a day.

REVISION HISTORY

28 August 1995 V1.00 REV 00 written by Dietmar Schloetel.
*/

#ifndef PXROUTE_INC
#define PXROUTE_INC

#include "pxbase/pxrecord.hpp"
#include <time.hpp>
#include <date.hpp>
#include <clock.hpp>

struct tTOUR;

class pxRoute : public pxDBRecord
{
public:
enum tRouteState
{
    RouteStateDefault     = 0,
    PickingInProgress    = 1,           // Kommissionierung begonnen
    ClosedForOrderEntry  = 2,           // Geschlossen für Auftragserfassung
    DeliveryInProgress   = 4            // Tour abgefahren
};

// constructors:
                pxRoute(pxSession *session);
              // Default mit Session Informationen
                pxRoute(const pxRoute& src);
              // Copy constructor
                pxRoute(pxSession *session,tTOUR& src);
              // record constructor
                pxRoute(pxSession *session,
                       const nString& TourId,
                       const nDate&   DatumKommi,
                       short FilialNr,
                       DBAccessMode mode = cDBGET_READONLY);
              // Read contructor
//@DE
// destructor:
                virtual  ~pxRoute();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxRoute&   operator=(const pxRoute& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxRoute&   operator=(const tTOUR& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxRoute&  Assign(pxRoute& dest, const tTOUR& src);
    friend   tTOUR&   Assign(tTOUR& dest, const pxRoute& src);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);

// Queries:
    const nString&    TourId() const
                      {return TourId_;    }
    nDate             DatumKommi() const
                      {return nDate(DateTimePick_);}
    nClock            ZeitKommiEnde() const
                      {return nClock(DateTimePick_);}
    nTime&            DateTimePick()
                      {return DateTimePick_;}
    nDate             DatumVersand() const
                      {return nDate(DateTimeShip_);}
    nClock            ZeitVersand() const
                      {return nClock(DateTimeShip_);}
    nTime&            DateTimeShip()
                      {return DateTimeShip_;}
    short            BahnhofVersand() const
                      {return BahnhofVersand_;}
    tRouteState       RouteState() const
                      {return TourStat_;}
    long             LagRechTourId() const
                      {return LagRechTour_;}
    bool              IsClosed() const
                      {return TourStat_ >= ClosedForOrderEntry;}
    nString&          KdAuftragArt()
                      {return KdAuftragArt_;      }
    char             TourInaktiv()
                      {return TourInaktiv_;       }
    short            ErsatzFilialNr()
                      {return ErsatzFilialNr_;    }
    short            KippZeit() const
                      {return TiltingTime_;       }
    short            TiltingTime() const
                      {return TiltingTime_;       }
    short             CheckTimeToTour() const
                      {return  CheckTimeToTour_;  }
    short             ScheckOrder() const
                      {return  ScheckOrder_;      }
    short             KarenzZeit() const
                      {return  KarenzZeit_;       }
    bool              IsTourInaktiv() const
                      {return TourInaktiv_ == '1'; }
    bool              IsPXTourInaktiv() const
                      {return TourInaktiv_ == '1'; }
//update fields
    void              SetTiltingTime(const short t)
                      {TiltingTime_ = t;}

protected:
    void              Init();

    nString           TourId_;          // Tour Identifikation
    nTime             DateTimePick_;    // Date/Time Kommi-Ende
    nTime             DateTimeShip_;    // Date/Time Versand
    short            BahnhofVersand_;  // Versandort
    tRouteState       TourStat_;        // Status der Tour
    long             LagRechTour_;     // Tour Id Lagerrechner
    short            FilialNr_;
    nString           KdAuftragArt_;    // Kunde Auftrag Art
    char             TourInaktiv_;     // Tour ist inaktiv
    short            ErsatzFilialNr_;  // wenn inaktiv tour aus ErsatzFiliale
    short            TiltingTime_;     // Tourkippzeit
    short            CheckTimeToTour_; // CheckTimeToTour
    short            ScheckOrder_;     // ScheckOrder
    short            KarenzZeit_;      // KarenzZeit
private:
    friend class pxRouteList;
};

class pxRouteList : public nDListCollect, public nDBRecordSet
{

public:
// constructors:
                pxRouteList(pxSession *session);
// destructor:
                virtual  ~pxRouteList() {Clear();}
// member functions:
             pxSession*  Session()       { return (pxSession*) DataBase();}
             size_t      Select ( const nDate&  date,
                                  const int    count = 50 );
             size_t      Select ( tTOUR* Tour,
                                  const int    count = 50 );
             void        Clear()        {nDBRecordSet::Clear();}
             pxRoute*  Find( const char *TourId);
             // Liefert Pointer auf gesuchte Tour

    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
protected:

private:
    friend class pxRouteListIter;
};

class pxRouteListIter : public nDListCollectIter
{
public:
// constructors:
    pxRouteListIter(pxRouteList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxRouteListIter() {;}
};

#endif

