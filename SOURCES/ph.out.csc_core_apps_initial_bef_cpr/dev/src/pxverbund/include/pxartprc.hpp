/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXARTPRC.HPP
Artikel Base Class.

REVISION HISTORY

24 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#ifndef PXARTPRC_DOTH
#define PXARTPRC_DOTH

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include <money.hpp>
#include "types/pricetypeenum.inc"

struct tARTIKELPREIS;

class pxArtPrice : public pxDBRecord
{

public:

    virtual           ~pxArtPrice();
                      pxArtPrice(pxArtPrice& src);
                      pxArtPrice(pxSession *session);
                      pxArtPrice(pxSession *session, long ArtikelNr,
                                 DBAccessMode mode = cDBGET_READONLY);

    pxArtPrice&       operator=(const pxArtPrice& src);
    pxArtPrice&       operator=(const tARTIKELPREIS& src);

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);

//  Queries:
    long              ArtikelNr         () {return ArtikelNr_        ; }
    nDate&            DatumGueltigAb    () {return DatumGueltigAb_   ; }
    nDate&            DatumGueltigBis   () {return DatumGueltigBis_  ; }
    nMoney            PreisEKApo        () {return PreisEKApo_       ; }
    nMoney            PreisVKApo        () {return PreisVKApo_       ; }
    nMoney            PreisEKGrosso     () {return PreisEKGrosso_    ; }
    nMoney            PreisEKGrossoNA   () {return PreisEKGrossoNA_  ; }
    double            RabattFest        () {return RabattFest_       ; }
    nMoney            PreisFest         () {return PreisFest_        ; }
    double            PreisProzent      () {return PreisProzent_     ; }
    double            PreisAGP          () {return PreisAGP_         ; }
    PriceTypeEnum     PreisTyp          () {return Preis_Typ_        ; }
    nMoney            MaxAvp            () {return MaxAvp_           ; }

//  Updates:
    void              PreisEKApo(double aep){ PreisEKApo_ = aep; SetDirty();}
    void              PreisVKApo(double avp){ PreisVKApo_ = avp; SetDirty();}
    void              PreisEKGrosso(double gep){ PreisEKGrosso_ = gep; SetDirty();}
protected:
                      pxArtPrice(pxSession *session, tARTIKELPREIS& src);
    void              Init();
    friend
    pxArtPrice&       Assign(pxArtPrice& dest, const tARTIKELPREIS& src);
    friend
    tARTIKELPREIS&    Assign(tARTIKELPREIS& dest, const pxArtPrice& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    long              ArtikelNr_;             // Artikelnummer
    nDate             DatumGueltigAb_;        // Datum gueltig ab
    nDate             DatumGueltigBis_;       // Datum gueltig bis
    nMoney            PreisEKApo_;            // Preis EK Apotheke
    nMoney            PreisVKApo_;            // Preis VK Apotheke
    nMoney            PreisEKApoNetto_;       // Preis EK Apotheke Nettoaktion
    nMoney            PreisEKGrosso_;         // Preis EK Grosso
    nMoney            PreisEKGrossoNA_;       // Preis EK Grosso Nettoaktion
    double            RabattFest_;            // Rabatt Fest in Prozent
    nMoney            RabattFestDM_;          // Rabatt Fest in DM
    nMoney            PreisFest_;             // Preis Fest
    double            PreisProzent_;          // Zu-/Abschlag(Vorzeichen) in %
    double            PreisAGP_;              // Spezial Preis Schweiz
    PriceTypeEnum     Preis_Typ_;             // Price Type 0,1,2
    nMoney            MaxAvp_;                // Preis Max Avp

private:
                      pxArtPrice();
    friend class pxArtPriceList;
};

class pxArtPriceList : public nDListCollect, public nDBRecordSet
{

public:
// constructors:
                pxArtPriceList(pxSession *session);
// destructor:
                virtual  ~pxArtPriceList() {Clear();}
// member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}
    size_t      Select ( const long   ArtikelNr );
    size_t      Select(const long ArtikelNr, const PriceTypeEnum Preis_Typ, const int count=50);
    int         DeleteExpired();
    pxArtPrice* Find(const PriceTypeEnum pricetyp = FREESALE_PRICE);
    void        Clear()        {nDBRecordSet::Clear();}
    nMoney      GetPreisEKApo(const PriceTypeEnum pricetyp = FREESALE_PRICE);
    nMoney      GetPreisVKApo(const PriceTypeEnum pricetyp = FREESALE_PRICE);
    nMoney      GetPreisEKGrosso(const PriceTypeEnum pricetyp = FREESALE_PRICE);
    nMoney      GetPreisEKGrossoNA(const PriceTypeEnum pricetyp = FREESALE_PRICE);
    double      GetRabattFest(const PriceTypeEnum pricetyp = FREESALE_PRICE);
    nMoney      GetPreisFest(const PriceTypeEnum pricetyp = FREESALE_PRICE);
    double      GetPreisProzent(const PriceTypeEnum pricetyp = FREESALE_PRICE);
    double      GetPreisAGP(const PriceTypeEnum pricetyp = FREESALE_PRICE);
    nMoney      GetMaxAvp(const PriceTypeEnum pricetyp = FREESALE_PRICE);

    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
protected:

private:
    size_t      Select ( tARTIKELPREIS *a,  const int count = 50 );
    friend class pxArtPriceListIter;
};

class pxArtPriceListIter : public nDListCollectIter
{

public:
// constructors:
    pxArtPriceListIter(pxArtPriceList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArtPriceListIter() {;}
};

#endif
