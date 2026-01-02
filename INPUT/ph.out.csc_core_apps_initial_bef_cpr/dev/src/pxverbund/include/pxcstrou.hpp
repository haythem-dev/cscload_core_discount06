/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXCSTROU.HPP
Customer-related route classes.
Defines classes to for daily customer shipment planning.

REVISION HISTORY

28 August 1995 V1.00 REV 00 written by Dietmar Schloetel.
*/

#ifndef PXCSTROU_INC
   #define PXCSTROU_INC

#include "pxroute.hpp"

struct tTOURPLANTAG;

class pxCustRoute : public pxRoute
{

public:
                   pxCustRoute(pxSession *session);
                   pxCustRoute(const pxCustRoute& src);
                   pxCustRoute(pxSession *session,tTOURPLANTAG& src, short FilialNr);

                   virtual  ~pxCustRoute();

    pxCustRoute&   operator=(const pxCustRoute& src);
    pxCustRoute&   operator=(const tTOURPLANTAG& src);

    friend
    pxCustRoute&   Assign(pxCustRoute& dest, const tTOURPLANTAG& src);
    friend
    tTOURPLANTAG&  Assign(tTOURPLANTAG& dest, const pxCustRoute& src);
    virtual  int   Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int   Put();
    virtual  int   CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    long           FahrtZeit() const      {return FahrtZeit_;}
    long           ReihenFolgeNr() const  {return ReihenFolgeNr_;}
    const nString& TourId() const    {return TourId_;}
    char           IstVerbundTour() const {  return  IstVerbundTour_ ;}

    long           GetTourIdSeconds();
    nTime          Arrival();
                   //{return DateTimeShip() + ((long) FahrtZeit_ * 60L);}

    bool           IsPseudoTour() const;
                   
    bool           IsVerbundTour() const
                   {return (IstVerbundTour_ == '1');}
    char           KoArt()         {return KoArt_;                  }
    char           KZAutoZuord()   {return KZAutoZuord_;            }
    bool           IsAutoAllocation() {return (KZAutoZuord_ == '1');}
    short          KippZeit()      {return (KippZeit_ > 0 ) ? KippZeit_ : TiltingTime();}
    bool           IsTourInaktiv() const
                   {return (TourInaktiv_ == '1') || IsPXTourInaktiv(); }
    bool           IsVaTour() const
                   {return (IstVaTour_ == '1');}

    bool           IsSencloserDone() const
                   {return  SencloserDone_ == '1';}

    nString&       KdAuftragArt()
                   {return KdAuftragArt_;      }
    short         DeliverBranchNo()
                   {return DeliverBranchNo_;   }
    char          SencloserDone()
                   {return SencloserDone_;     }
    short          OrderLabelCount()
                   {return  OrderLabelCount_;   }

    nString&       OrderType()     {return (KdAuftragArt_ > "" ) ? KdAuftragArt_ : pxRoute :: KdAuftragArt();}
// update fields
   void            SetTourenKippZeit(const short t)
                   {KippZeit_ = t; SetTiltingTime(t);}
   void            SetSencloserDone()
                   {SencloserDone_ = '1'; SetDirty();}

protected :
    void           Init();
    virtual  int  Read(const void *record);
    virtual  int  ReadLock(const void *record);
    virtual  int  Insert(const void *record);
    virtual  int  Update(const void *record);

    long          IDFNr_;              // Kundennummer IDF
    nDate          DatumKommi_;         // Datum Kommi
    nString        TourId_;             // Tour Identifikation
    long          ReihenFolgeNr_;      // Reihenfolgenummer
    long          FahrtZeit_;          // Fahrtzeit zum Kunden
    nString        Bemerkungen_;        // Bemerkungen
    char          KZUpd_;              // Update Kennzeichen
    char          IstVerbundTour_;     // Schalter ist Verbundtour
    short         VertriebszentrumNr_; // Vertriebszentrum
    long          KundenNr_;           // Kunden Nummer VZ
    char           KoArt_;              // Kommissionierungs-Art
    char          TourInaktiv_;        // TourInaktiv
    short         KippZeit_;           // Kunden Tourenkippzeit
    char          KZAutoZuord_;        // KZ Tour automatisch zuordnen
    char          IstVaTour_;          // Schalter ist VersandApoTour
    nString        KdAuftragArt_;       // KdAuftragArt
    short         DeliverBranchNo_;    // Lieferfiliale der Shuttle Touren(FR new suivra)
    char          SencloserDone_;      // Beifueger getaetigt(CH XML Beifueger)
    short         OrderLabelCount_;    // OrderLabelCount

private:
    friend class pxCustRouteList;
};

class pxCustRouteList : public nDListCollect, public nDBRecordSet
{

public:
                   pxCustRouteList(pxSession *session);
    virtual        ~pxCustRouteList() {Clear();}

    pxSession*     Session()         { return (pxSession*) DataBase();}
    //size_t         Select (const long IDF, const int count = 200);
    size_t         Select (short VertriebszentrumNr, long KundenNr,
                           short FilialNr, const nDate& Datum, int count = 200);
    size_t         Select (short VertriebszentrumNr, long KundenNr,
                           short FilialNr, char vbtour, const nDate& Datum, int count = 200);
    void           Clear()           {nDBRecordSet::Clear();}
    int            Shrink(const nTime& TimeLimit);
    int            Shrink(const nTime& TimeLimit,long * KippZeit);
    int            Shrink(const nString& AuftragArt);
    int            ShrinkForOrderType();
    int            ShrinkForOrderType(const nString& KdAuftragArt);
    pxCustRoute*   Find(const nString& TourId);
    pxCustRoute*   Find(const nTime& ExpTime);
    pxCustRoute*   FindAllocatableRoute();
    pxCustRoute*   FindVaTour();
    bool           OrderTypesInList();
    bool           IsOrderTypeInList(const nString& KdAuftragArt);
    pxCustRouteList*  NewList();
    pxCustRoute*   FindNextAllocatableRoute(const nString& TourId);
    pxCustRoute*   FindNextAllocatableRoute(const nString& TourId, const nTime& time);

    pxCustRoute*   GetDefault();
    pxCustRoute*   GetLast();
    short         WeekDay() { return WeekDay_ ;}
    int           SetWeekDay();

protected:
    size_t         Select (tTOURPLANTAG* plan, const int count = 200 );
    virtual  int  EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int  GetNext(const void* record, const int cursorid);
    virtual  int  StartBrowse(const void *keys, const int cursorid);


private:
    short FilialNr_;
    short WeekDay_ ;

    friend class pxCustRouteListIter;
};

class pxCustRouteListIter : public nDListCollectIter
{
public:
                   pxCustRouteListIter(pxCustRouteList& list)
                                       : nDListCollectIter(list) {;}
    virtual        ~pxCustRouteListIter() {;}
};
#endif
