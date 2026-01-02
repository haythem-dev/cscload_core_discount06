/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXARTDSP.HPP
Dispo article class.

REVISION HISTORY

24 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#ifndef PXARTDSP_DOTH
#define PXARTDSP_DOTH

#include "pxbase/pxrecord.hpp"
#include <money.hpp>
#include "pxartcls.hpp"
#include "pxartflg.hpp"

struct tDISPOARTIKEL;

enum pxMWSTSchluessel
{
    FULLTAX = 0,
    HALFTAX = 1,
    FULLTAXFR = 3
};

/*----------------------------------------------------------------------------*/
/*  Structure to enter/update none-stocked product items.                     */
/*----------------------------------------------------------------------------*/
struct tDISPOITEM
{
    long          MengeBestellt;
    nString        Einheit;
    nString        Bezeichnung;
    nString        Darreichform;

    nMoney         PreisEKApo;
    nMoney         PreisEKGrosso;

    nMoney         RabattFestDM;        // Direkter Festrabatt in DM
    double         RabattFest;          // Direkter Festrabatt in Prozent

    pxMWSTSchluessel MWSTSchluessel;      // voll, halb
    bool           TaxPflichtig;        // true : taxpflichtig
    bool           Rabattfaehig;        // true : rabattierfaehig
    nString        Bemerkungen;
    nString        WarenGruppeEigen;    // Warengruppe

    nMoney         GebuehrBearb;
    long           UrsprungAuftragnr;
    long           UrsprungPosnr;
    double         NetPrice;
    short          Service_No;
    char           KzPriso;

//  Constructor:
    tDISPOITEM()
        : MengeBestellt(0),
          PreisEKApo(0.0), PreisEKGrosso(0.0), RabattFestDM(0.0),
          RabattFest(0), MWSTSchluessel(HALFTAX),
          TaxPflichtig(false), Rabattfaehig(false),
          GebuehrBearb(0.0),
          UrsprungAuftragnr(0), UrsprungPosnr(0),NetPrice(0.0),Service_No(0),
          KzPriso('0')
    {
    }
};


class pxArtDispo : public pxDBRecord
{

public:
// constructors:
                pxArtDispo(pxArtDispo& src);
                pxArtDispo(pxSession *session);
                pxArtDispo(pxSession *session, tDISPOARTIKEL& src);
                pxArtDispo(pxSession *session,
                           long     KdAuftragNr,
                           long     PosNr,
                           DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxArtDispo();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArtDispo&   operator=(const pxArtDispo& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArtDispo&   operator=(const tDISPOARTIKEL& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

    pxArtDispo&   operator=(const tDISPOITEM& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend pxArtDispo& Assign(pxArtDispo& dest, const tDISPOARTIKEL& src);
    friend tDISPOARTIKEL&  Assign(tDISPOARTIKEL& dest, const pxArtDispo& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();
    virtual  int     Read(const void *record);
    virtual  int     Delete(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);

    bool              SetOrder (long KdAuftragNr, long PosNr);
    void              DispoGet ( tDISPOITEM& s );
    void              SetParentPosNr(long Posnr)
                      {UrsprungPosnr_ = Posnr; SetDirty();}
    void              SetParentOrderNr(long OrderNr)
                      {UrsprungAuftragnr_ = OrderNr; SetDirty();}
    void              SetGeBuehrBearb(nMoney& Gebuehr)
                      {GebuehrBearb_ = Gebuehr;SetDirty();}

//  Queries:
    long             KdAuftragNr () const {return KdAuftragNr_;}
    long             PosNr       () const {return PosNr_;}
    const nString&    Darreichform() const {return Darreichform_;}
    const nString&    Einheit     () const {return Einheit_;}
    const nString&    Bezeichnung () const {return Bezeichnung_;}
    const nMoney&     PreisEKApo  () const {return PreisEKApo_;}
    const nMoney&     PreisEKGrosso() const{return PreisEKGrosso_;}
    const nMoney&     RabattFestDM() const {return RabattFestDM_;}
    double          RabattFest  () const {return RabattFest_;}
    const nString&    Rabattfaehig() const {return Rabattfaehig_;}
    pxArtClass&       ArtClass    () {return ETArtKlasse_;}
    pxArtFlags&       ArtFlags    () {return ETArtSchalter_;}
    const nString&    WarenGruppeEigen () const {return WarenGruppeEigen_;}
    const nMoney&     GebuehrBearb() const {return GebuehrBearb_;}
    long             UrsprungAuftragnr() const {return UrsprungAuftragnr_;}
    long             UrsprungPosnr() const {return UrsprungPosnr_;}
    short            TaxLevel     () const {return TaxLevel_;}
    double          NetPrice     () const {return NetPrice_;}
    short            Service_No   () const {return Service_No_;}
    char             KzPriso      () const {return KzPriso_;}

protected:
    void        Init();

private:
    long       KdAuftragNr_;           // Kunde Auftrag Nummer
    long       PosNr_;                 // Positionsnummer Kundenauftrag
    nString     Darreichform_;          // Darreichform
    nString     Einheit_;               // Einheit
    nString     Bezeichnung_;           // Bezeichnung
    pxArtClass  ETArtKlasse_;           // Bit Map Artikel Klassifizierung
    pxArtFlags  ETArtSchalter_;         // Bit Map Artikel Schalter
    nMoney      PreisEKApo_;            // Preis EK Apotheke
    nMoney      PreisEKGrosso_;         // Preis EK Grosso
    nMoney      RabattFestDM_;          // Rabatt Fest in DM
    double    RabattFest_;            // Rabatt Fest in Prozent
    nString     Rabattfaehig_;          // Schluessel Rabattfaehigkeit
    nString     WarenGruppeEigen_;      // Interne Warengruppe
    nMoney      GebuehrBearb_;          // Bearbeitungsgebuehr
    long       UrsprungAuftragnr_;     // Ursprungauftragsnummer
    long       UrsprungPosnr_;         // Ursprungposistionsnummer
    short      TaxLevel_;              // Taxlevel
    double    NetPrice_;              // Netto Price
    short      Service_No_;            // Service Number BG
    char       KzPriso_;                // Privatsortiment
};

class pxArtDispoList : public nDListCollect, public nDBRecordSet
{

public:
// constructors:
                pxArtDispoList(pxSession *session);
// destructor:
                virtual  ~pxArtDispoList() {Clear();}
// member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}
    size_t      Select ( const long KdAuftragNr,
                         const int  count = 100 );
    size_t      Select ( tDISPOARTIKEL *a,  const int count = 100 );
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
protected:

private:
    friend class pxArtDispoListIter;
};

class pxArtDispoListIter : public nDListCollectIter
{

public:
// constructors:
    pxArtDispoListIter(pxArtDispoList& list) : nDListCollectIter(list) {}
// destructor:
    virtual  ~pxArtDispoListIter() {}
};

#endif
