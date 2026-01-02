/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxCustRouteWeek Class.

REVISION HISTORY

27 April 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCUSTROUTEWEEK_INC
#define PXCUSTROUTEWEEK_INC

#include "pxrouteweek.hpp"

struct tTOURPLANTAGWOCHE;

class pxCustRouteWeek : pxRouteWeek
{

public:


// constructors:
                pxCustRouteWeek(pxCustRouteWeek& src);
                pxCustRouteWeek(pxSession *session);
                pxCustRouteWeek(pxSession *session, tTOURPLANTAGWOCHE& src);
// destructor:
                virtual  ~pxCustRouteWeek();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustRouteWeek&   operator=(const pxCustRouteWeek& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustRouteWeek&   operator=(const tTOURPLANTAGWOCHE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustRouteWeek&
                Assign(pxCustRouteWeek& dest, const tTOURPLANTAGWOCHE& src);
    friend   tTOURPLANTAGWOCHE&
                Assign(tTOURPLANTAGWOCHE& dest, const pxCustRouteWeek& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    int              ConvertDayTyp(const nString& TagesTyp);

//  Queries:
    short            VertriebszentrumNr() {return VertriebszentrumNr_ ;}
    long             KundenNr()           {return KundenNr_           ;}
    nString&          TourId()             {return TourId_             ;}
    nString&          TagesTyp()           {return TagesTyp_           ;}
    int              WochenTag()          {return WochenTag_          ;}
    short            WeekDay()            {return WeekDay_            ;}
    long             LagRechTourId()      {return LagRechTour()       ;}
    nString&          KdAuftragArt()       {return KdAuftragArt_       ;}
    long             FahrtZeit() const    {return FahrtZeit_          ;}
    short            WaitingPeriod()      {return KarenzZeit()        ;}

    bool              IsVerbundTour() const
                      {return (IstVerbundTour_ == '1');}
    long             GetTourIdHHMM();
    long             Arrival();
protected:
    void        Init();

    short            VertriebszentrumNr_;     // VertriebszentrumNr
    long             KundenNr_;               // Kundennummer
    nString           TourId_;                 // TourId
    nString           TagesTyp_;               // Tagestyp
    int              WochenTag_;              // Wochentag 0 - 6
    short            WeekDay_;                // Day of Week
    char             IstVerbundTour_;         // Schalter ist Verbundtour
    nString           KdAuftragArt_;           // KdAuftragArt
    long             FahrtZeit_;              // Fahrtzeit zum Kunden
private:
    friend class pxCustRouteWeekList;

};

class pxCustRouteWeekList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCustRouteWeekList(pxSession *session);
//  destructor:
                virtual ~pxCustRouteWeekList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short VertriebszentrumNr,
                         const long  KundeNr,const short FilialNr,
                         const int     count = 300);
    size_t      Select ( const short VertriebszentrumNr,
                         const long  KundeNr,const short FilialNr,
                         const short DayType,
                         const int     count = 300);
    size_t      Select ( const short VertriebszentrumNr,
                         const long  KundeNr,const short FilialNr,
                         const char  IBTFlag,
                         const int     count = 300);
    void        Clear()        {nDBRecordSet::Clear();}

    long       GetNextDayFromNow(const long Day = -1);
    pxCustRouteWeek* FindNextDay(const long dayofweek, const nString& KdAuftragArt = "");
    pxCustRouteWeek* Find(const long dayofweek, const nString& KdAuftragArt);
    bool             Find(const nString& TourId, const long dayofweek);
    pxCustRouteWeek* GetEntry(const nString& TourId, const long dayofweek);
    nString          GetNextTourId(const nString& TourId, const long dayofweek);
    bool           OrderTypesInList();
    bool           IsOrderTypeInList(const nString& KdAuftragArt);
    int            ShrinkForOrderType();
    int            ShrinkForOrderType(const nString& KdAuftragArt);
    pxCustRouteWeekList*  NewList();

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:

    short FilialNr_;
    friend class pxCustRouteWeekListIter;
};

class pxCustRouteWeekListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustRouteWeekListIter(pxCustRouteWeekList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustRouteWeekListIter() {;}
};
#endif
