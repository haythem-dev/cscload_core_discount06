/*----------------------------------------------------------------------------*/

#ifndef PXARTACC_INC
#define PXARTACC_INC

/*----------------------------------------------------------------------------*/

#include "pxbase/pxrecord.hpp"
#include "types/pickingtypeenum.inc"
#include "types/bookingtypeenum.inc"
#include "types/reservationtypeenum.inc"
#include "pxordtyp.hpp"
/*----------------------------------------------------------------------------*/

struct tARTIKELKONTO;

class pxArtAccount : public pxDBRecord
{
public:
// constructors:
                      pxArtAccount(pxArtAccount& src);
                      pxArtAccount(pxSession *session);
                      pxArtAccount(pxSession *session, const tARTIKELKONTO& src);
                      pxArtAccount(pxSession *session, const char transactiontype);

// destructor:
    virtual           ~pxArtAccount();

// public member operators
    pxArtAccount&    operator=(const pxArtAccount& src);
    pxArtAccount&    operator=(const tARTIKELKONTO& src);

// public member functions
    virtual  int      Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int      Put();
    virtual  int      Delete();

    long              TransActionKey(const enum BookingTypeEnum bookingType,
                                     const enum PickingTypeEnum pickingType);

//  Field updates
    void              FilialNr( const short company)
                      {FilialNr_  = company;    }
    void              ArtikelNr( const long article)
                      {ArtikelNr_ = article;    }
    void              Menge( const long q)
                      {Menge_  = q;             }
    void              MengeNeu( const long q)
                      {MengeNeu_  = q;          }
    void              IDFNr( const long idfnr)
                      {IDFNr_  = idfnr;         }
    void              BelegNr( const long belegnr)
                      {BelegNr_  = belegnr;     }
    void              PosNr(const long posnr)
                      {PosNr_ = posnr;          }
    void              Uid( const long uid)
                      {Uid_  = uid;             }
    void              SetBewegungsArt(const char bart)
                      {BewegungsArt_ = bart;}
    void              StockReserved( const long q )
                      {StockReserved_  = q;     }
    void              MoveType( const ReservationTypeEnum t)
                      {MoveType_  = t;          }
    void              BelegArt(const nString& b)
                      {BelegArt_ = b;    }

// Queries:
    long                LfdNr              () const {return LfdNr_              ;}
    short               FilialNr           () const {return FilialNr_           ;}
    long                ArtikelNr          () const {return ArtikelNr_          ;}
    char                BewegungsArt       () const {return BewegungsArt_       ;}
    long                Menge              () const {return Menge_              ;}
    long                BeLegNr            () const {return BelegNr_            ;}
    long                Uid                () const {return Uid_                ;}
    long                IDFNr              () const {return IDFNr_              ;}
    long                MengeNeu           () const {return MengeNeu_           ;}
    long                ZeitUnix           () const {return ZeitUnix_           ;}
    long                BewegungSchluessel () const {return BewegungSchluessel_ ;}
    long                StockReserved      () const {return StockReserved_      ;}
    ReservationTypeEnum MoveType           () const {return MoveType_           ;}
    long                PosNr              () const {return PosNr_              ;}
    nString&            BelegArt           ()       {return BelegArt_           ;}

protected:
                      pxArtAccount();
    friend
    pxArtAccount&     Assign(pxArtAccount& dest, const tARTIKELKONTO& src);
    friend
    tARTIKELKONTO&    Assign(tARTIKELKONTO& dest, const pxArtAccount& src);

    void              Init();
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

/*----------------------------------------------------------------------------*/
/*  Data members.                                                             */
/*----------------------------------------------------------------------------*/
    long                LfdNr_;              // Laufende Nummer(type serial)
    short               FilialNr_;           // Filialnummer
    long                ArtikelNr_;          // Artikelnummer
    char                BewegungsArt_;       // Bewegungs Art
    long                Menge_;              // Menge
    long                BelegNr_;            // Beleg Nummer
    long                Uid_;                // Benutzer
    long                IDFNr_;              // Kundennummer
    long                MengeNeu_;           // Neue Menge
    long                ZeitUnix_;           // Zeit Unix
    long                BewegungSchluessel_; // Bewegungs Schluessel
    long                StockReserved_;      // Menge Reserviert
    ReservationTypeEnum MoveType_;           // Bewegungs type
    long                PosNr_;              // Positionsnummer
    nString             BelegArt_;           // BelegArt

//private:
//    friend class pxArtAcccountList;
};

class pxArtAccountList : public nDBRecordSet, public nDListCollect
{

public:
//  constructors:
                pxArtAccountList(pxSession *session);
//  destructor:
                virtual ~pxArtAccountList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long BelegNr, const long IDFNr,
                         const int  count  = 50 );

    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int           StartBrowse(const void *keys, const int cursorid);
    virtual  int           GetNext(const void* record, const int cursorid);
    virtual  int           EndBrowse(const int cursorid);

protected:

private:
//    friend class pxArtAccountListIter;
};

class pxArtAccountListIter : public nDListCollectIter
{

public:
// constructors:
    pxArtAccountListIter(pxArtAccountList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArtAccountListIter() {;}
};
#endif
