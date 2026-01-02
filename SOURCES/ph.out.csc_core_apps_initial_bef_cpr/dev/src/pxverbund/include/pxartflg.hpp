/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXARTFLG.HPP
Article decision flags.

REVISION HISTORY

24 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#ifndef PXARTFLG_INC
#define PXARTFLG_INC

#include <bitmap.hpp>

class pxArtFlags : public nBitMap
{

public:
   enum pxArtDecFlags
   {
       // Byte 0:
       bSekundaerBezeichnung,           // For UNIPHARM compatibility
       bNachfolgeArtikel,               // Nachfolgeartikel vorhanden
       bSchnellDreher,
       bAusserHandel,
       bAuslaufArtikel,
       bRueckRufAktion,
       bNettoAktion,
       bNettoArtikel,
       // Byte 1:
       bGekuehlt08,                     // Gekuehlt unter 08 Grad
       bGekuehlt20,                     //                20 Grad
       bKuehlKette,
       bNichtLieferbarHersteller,
       bNichtGeliefertHersteller,
       bNichtUeberGrossHandel,
       bKlinikPackung,
       bRetourenSperre,
       // Byte 2:
       bArtikelMeldePflichtig,
       bHerstellerDatum,
       bVerfallDatum,
       bVerfalldatumAnDatamobil,
       bErmaessigtMwst,
       bBestandsBuchung,
       bContainerArtikel,
       bVorkommiArtikel,
       // Byte 3:
       bFeuerGefaehrlich,
       bKuehlZelleOeffnen,
       bAutomatikArtikel,
       bDynArtikelRoboter,              // Dynamischer Artikel (Roboter)
       bWannenKommiArtikel,             // Dortmund
       bHochRegalArtikel,               // EPG
       bBeiPackMulti,
       bArtikelGefuehrt,
       // Byte 4:
       bAuto2,                          // Noch belegt (whatever this means?)
       bAuto1,                          // Noch belegt (whatever this means?)
       bAuto0,                          // Noch belegt (whatever this means?)
       bAktuellerFestPreis,
       bNegativArtikel,
       bPoolArtikel,
       bHomeCare,
       bNatraArtikel,
       // Byte 5:
       bUeberVorrat,
       bKKH_VersandApo,                 // ???
       bGrosseWanneNoetig,
       bSonderArtikel,
       bAktuellerWe,
       bSkontoFaehig,
       bPrismaArtikel,
       bBarRabattUebwAuftrag,
       // Byte 6:
       bA3Laden,
       bReimportArtikel,
       bArtikelInUmlagerung,
       bAAStaffelAktiv,
       bKzNurGrosseWanne,
       bKzDiabetesStaffel,
       bKzBlutArtikel,
       bKzWechselArtikel,
       // Byte 7:
       bVorsichtGlas,
       bArtikelMitZentralPreis,
       bSommerKuehlArtikel,
       bLichtGeschuetztLagern,
       bBrandGefaehrlich,
       bLagerortZweiAktiv,
       bOhneZertifikat,
       bGefahrGutArtikel,
       // Byte 8:
       bEinkaufsSperre,
       bZytoStatikaArtikel,
       b66,
       b67,
       b68,
       b69,
       b70,
       bArtikelVerKnuepft,
       // Byte 9:
       b72,
       b73,
       b74,
       b75,
       b76,
       b77,
       bNeuerPreisWarten,
       bNeuerPreisAktiv,

       cPXARTFLG_MAPWIDTH = 80          // max number of bits in this map
    };

                      ~pxArtFlags()  {;}
                      pxArtFlags() : nBitMap(cPXARTFLG_MAPWIDTH) {;}
                      pxArtFlags(pxArtFlags& src) : nBitMap(cPXARTFLG_MAPWIDTH)
                                              {(*this)=src;}

    pxArtFlags&       operator=(const pxArtFlags& src)
//  Assigns the bit map value of 'src' to self and returns a reference to it.
                      {return (pxArtFlags&) nBitMap:: operator=(src);}

    pxArtFlags&       operator=(const unsigned char *src)
//  The entire bit map of self is set from the contents of the byte array 'src'.
                      {return (pxArtFlags&) nBitMap:: operator=(src);}

    void              Export(long& l1,long& l2,long& l3,long& l4,long& l5) const;
    void              Import(const long l1,const long l2,const long l3,
                             const long l4,const long l5);

    bool              IsNotCertificated() const { return  IsOhneZertifikat();}
    bool              IsPurchaseStop()    const { return  IsEinkaufsSperre();}

//  Flag queries and settings:
    bool        IsSekundaerBezeichnung() const {return TestBit( bSekundaerBezeichnung ); }
    bool        IsNachfolgeArtikel    () const {return TestBit( bNachfolgeArtikel     ); }
    bool        IsSchnellDreher       () const {return TestBit( bSchnellDreher        ); }
    bool        IsAusserHandel        () const {return TestBit( bAusserHandel         ); }
    bool        IsAuslaufArtikel      () const {return TestBit( bAuslaufArtikel       ); }
    bool        IsRueckRufAktion      () const {return TestBit( bRueckRufAktion       ); }
    bool        IsNettoAktion         () const {return TestBit( bNettoAktion          ); }
    bool        IsNettoArtikel        () const {return TestBit( bNettoArtikel         ); }

    bool        IsGekuehlt08              () const {return TestBit(bGekuehlt08              ); }
    bool        IsGekuehlt20              () const {return TestBit(bGekuehlt20              ); }
    bool        IsKuehlKette              () const {return TestBit(bKuehlKette              ); }
    bool        IsNichtLieferbarHersteller() const {return TestBit(bNichtLieferbarHersteller); }
    bool        IsNichtGeliefertHersteller() const {return TestBit(bNichtGeliefertHersteller); }
    bool        IsNichtUeberGrossHandel   () const {return TestBit(bNichtUeberGrossHandel   ); }
    bool        IsKlinikPackung           () const {return TestBit(bKlinikPackung           ); }
    bool        IsRetourenSperre          () const {return TestBit(bRetourenSperre          ); }

    bool        IsArtikelMeldePflichtig   () const {return TestBit(bArtikelMeldePflichtig   ); }
    bool        IsHerstellerDatum         () const {return TestBit(bHerstellerDatum         ); }
    bool        IsVerfallDatum            () const {return TestBit(bVerfallDatum            ); }
    bool        IsVerfalldatumAnDatamobil () const {return TestBit(bVerfalldatumAnDatamobil ); }
    bool        IsErmaessigtMwst          () const {return TestBit(bErmaessigtMwst          ); }
    bool        IsBestandsBuchung         () const {return TestBit(bBestandsBuchung         ); }
    bool        IsContainerArtikel        () const {return TestBit(bContainerArtikel        ); }
    bool        IsVorkommiArtikel         () const {return TestBit(bVorkommiArtikel         ); }

    bool        IsFeuerGefaehrlich        () const {return TestBit(bFeuerGefaehrlich        ); }
    bool        IsKuehlZelleOeffnen       () const {return TestBit(bKuehlZelleOeffnen       ); }
    bool        IsAutomatikArtikel        () const {return TestBit(bAutomatikArtikel        ); }
    bool        IsDynArtikelRoboter       () const {return TestBit(bDynArtikelRoboter       ); }
    bool        IsWannenKommiArtikel      () const {return TestBit(bWannenKommiArtikel      ); }
    bool        IsHochRegalArtikel        () const {return TestBit(bHochRegalArtikel        ); }
    bool        IsBeiPackMulti            () const {return TestBit(bBeiPackMulti            ); }
    bool        IsArtikelGefuehrt         () const {return TestBit(bArtikelGefuehrt         ); }

    bool        IsAuto2                   () const {return TestBit(bAuto2                   ); }
    bool        IsAuto1                   () const {return TestBit(bAuto1                   ); }
    bool        IsAuto0                   () const {return TestBit(bAuto0                   ); }
    bool        IsAktuellerFestPreis      () const {return TestBit(bAktuellerFestPreis      ); }
    bool        IsNegativArtikel          () const {return TestBit(bNegativArtikel          ); }
    bool        IsPoolArtikel             () const {return TestBit(bPoolArtikel             ); }
    bool        IsHomeCare                () const {return TestBit(bHomeCare                ); }
    bool        IsNatraArtikel            () const {return TestBit(bNatraArtikel            ); }

    bool        IsUeberVorrat             () const {return TestBit(bUeberVorrat             ); }
    bool        IsKKH_VersandApo          () const {return TestBit(bKKH_VersandApo          ); }
    bool        IsGrosseWanneNoetig       () const {return TestBit(bGrosseWanneNoetig       ); }
    bool        IsSonderArtikel           () const {return TestBit(bSonderArtikel           ); }
    bool        IsAktuellerWe             () const {return TestBit(bAktuellerWe             ); }
    bool        IsSkontoFaehig            () const {return TestBit(bSkontoFaehig            ); }
    bool        IsPrismaArtikel           () const {return TestBit(bPrismaArtikel           ); }
    bool        IsBarRabattUebwAuftrag    () const {return TestBit(bBarRabattUebwAuftrag    ); }

    bool        IsA3Laden                 () const {return TestBit(bA3Laden                 ); }
    bool        IsReimportArtikel         () const {return TestBit(bReimportArtikel         ); }
    bool        IsArtikelInUmlagerung     () const {return TestBit(bArtikelInUmlagerung     ); }
    bool        IsAAStaffelAktiv          () const {return TestBit(bAAStaffelAktiv          ); }
    bool        IsKzNurGrosseWanne        () const {return TestBit(bKzNurGrosseWanne        ); }
    bool        IsKzDiabetesStaffel       () const {return TestBit(bKzDiabetesStaffel       ); }
    bool        IsKzBlutArtikel           () const {return TestBit(bArtikelMitZentralPreis  ); }
    bool        IsKzWechselArtikel        () const {return TestBit(bKzWechselArtikel        ); }

    bool        IsVorsichtGlas            () const {return TestBit(bVorsichtGlas            ); }
    bool        IsArtikelMitZentralPreis  () const {return TestBit(bArtikelMitZentralPreis  ); }
    bool        IsSommerKuehlArtikel      () const {return TestBit(bSommerKuehlArtikel      ); }
    bool        IsLichtGeschuetztLagern   () const {return TestBit(bLichtGeschuetztLagern   ); }
    bool        IsBrandGefaehrlich        () const {return TestBit(bBrandGefaehrlich        ); }
    bool        IsLagerortZweiAktiv       () const {return TestBit(bLagerortZweiAktiv       ); }

    bool        IsOhneZertifikat          () const {return TestBit(bOhneZertifikat          ); }
    bool        IsGefahrGutArtikel        () const {return TestBit(bGefahrGutArtikel        ); }

    bool        IsEinkaufsSperre          () const {return TestBit(bEinkaufsSperre          ); }
    bool        IsZytoStatikaArtikel      () const {return TestBit(bZytoStatikaArtikel      ); }
    bool        IsArtikelVerKnuepft       () const {return TestBit(bArtikelVerKnuepft       ); }
    bool        IsNeuerPreisAktiv         () const {return TestBit(bNeuerPreisAktiv         ); }

    void  ClearSekundaerBezeichnung    () {ClearBit( bSekundaerBezeichnung   ); }
    void  ClearNachfolgeArtikel        () {ClearBit( bNachfolgeArtikel       ); }
    void  ClearSchnellDreher           () {ClearBit( bSchnellDreher          ); }
    void  ClearAusserHandel            () {ClearBit( bAusserHandel           ); }
    void  ClearAuslaufArtikel          () {ClearBit( bAuslaufArtikel         ); }
    void  ClearRueckRufAktion          () {ClearBit( bRueckRufAktion         ); }
    void  ClearNettoAktion             () {ClearBit( bNettoAktion            ); }
    void  ClearNettoArtikel            () {ClearBit( bNettoArtikel           ); }

    void  ClearGekuehlt08              () {ClearBit(bGekuehlt08              ); }
    void  ClearGekuehlt20              () {ClearBit(bGekuehlt20              ); }
    void  ClearKuehlKette              () {ClearBit(bKuehlKette              ); }
    void  ClearNichtLieferbarHersteller() {ClearBit(bNichtLieferbarHersteller); }
    void  ClearNichtGeliefertHersteller() {ClearBit(bNichtGeliefertHersteller); }
    void  ClearNichtUeberGrossHandel   () {ClearBit(bNichtUeberGrossHandel   ); }
    void  ClearKlinikPackung           () {ClearBit(bKlinikPackung           ); }
    void  ClearRetourenSperre          () {ClearBit(bRetourenSperre          ); }

    void  ClearArtikelMeldePflichtig   () {ClearBit(bArtikelMeldePflichtig   ); }
    void  ClearHerstellerDatum         () {ClearBit(bHerstellerDatum         ); }
    void  ClearVerfallDatum            () {ClearBit(bVerfallDatum            ); }
    void  ClearVerfalldatumAnDatamobil () {ClearBit(bVerfalldatumAnDatamobil ); }
    void  ClearErmaessigtMwst          () {ClearBit(bErmaessigtMwst          ); }
    void  ClearBestandsBuchung         () {ClearBit(bBestandsBuchung         ); }
    void  ClearContainerArtikel        () {ClearBit(bContainerArtikel        ); }
    void  ClearVorkommiArtikel         () {ClearBit(bVorkommiArtikel         ); }

    void  ClearFeuerGefaehrlich        () {ClearBit(bFeuerGefaehrlich        ); }
    void  ClearKuehlZelleOeffnen       () {ClearBit(bKuehlZelleOeffnen       ); }
    void  ClearAutomatikArtikel        () {ClearBit(bAutomatikArtikel        ); }
    void  ClearDynArtikelRoboter       () {ClearBit(bDynArtikelRoboter       ); }
    void  ClearWannenKommiArtikel      () {ClearBit(bWannenKommiArtikel      ); }
    void  ClearHochRegalArtikel        () {ClearBit(bHochRegalArtikel        ); }
    void  ClearBeiPackMulti            () {ClearBit(bBeiPackMulti            ); }
    void  ClearArtikelGefuehrt         () {ClearBit(bArtikelGefuehrt         ); }

    void  ClearAuto2                   () {ClearBit(bAuto2                   ); }
    void  ClearAuto1                   () {ClearBit(bAuto1                   ); }
    void  ClearAuto0                   () {ClearBit(bAuto0                   ); }
    void  ClearAktuellerFestPreis      () {ClearBit(bAktuellerFestPreis      ); }
    void  ClearNegativArtikel          () {ClearBit(bNegativArtikel          ); }
    void  ClearPoolArtikel             () {ClearBit(bPoolArtikel             ); }
    void  ClearHomeCare                () {ClearBit(bHomeCare                ); }
    void  ClearNatraArtikel            () {ClearBit(bNatraArtikel            ); }

    void  ClearUeberVorrat             () {ClearBit(bUeberVorrat             ); }
    void  ClearKKH_VersandApo          () {ClearBit(bKKH_VersandApo          ); }
    void  ClearGrosseWanneNoetig       () {ClearBit(bGrosseWanneNoetig       ); }
    void  ClearSonderArtikel           () {ClearBit(bSonderArtikel           ); }
    void  ClearAktuellerWe             () {ClearBit(bAktuellerWe             ); }
    void  ClearSkontoFaehig            () {ClearBit(bSkontoFaehig            ); }
    void  ClearPrismaArtikel           () {ClearBit(bPrismaArtikel           ); }
    void  ClearBarRabattUebwAuftrag    () {ClearBit(bBarRabattUebwAuftrag    ); }

    void  ClearA3Laden                 () {ClearBit(bA3Laden                 ); }
    void  ClearReimportArtikel         () {ClearBit(bReimportArtikel         ); }
    void  ClearArtikelInUmlagerung     () {ClearBit(bArtikelInUmlagerung     ); }
    void  ClearAAStaffelAktiv          () {ClearBit(bAAStaffelAktiv          ); }
    void  ClearKzNurGrosseWanne        () {ClearBit(bKzNurGrosseWanne        ); }
    void  ClearKzDiabetesStaffel       () {ClearBit(bKzDiabetesStaffel       ); }
    void  ClearKzBlutArtikel           () {ClearBit(bArtikelMitZentralPreis  ); }
    void  ClearKzWechselArtikel        () {ClearBit(bKzWechselArtikel        ); }

    void  ClearVorsichtGlas            () {ClearBit(bVorsichtGlas            ); }
    void  ClearArtikelMitZentralPreis  () {ClearBit(bArtikelMitZentralPreis  ); }
    void  ClearSommerKuehlArtikel      () {ClearBit(bSommerKuehlArtikel      ); }
    void  ClearLichtGeschuetztLagern   () {ClearBit(bLichtGeschuetztLagern   ); }
    void  ClearBrandGefaehrlich        () {ClearBit(bBrandGefaehrlich        ); }
    void  ClearLagerortZweiAktiv       () {ClearBit(bLagerortZweiAktiv       ); }

    void  ClearOhneZertifikat         ()  {ClearBit(bOhneZertifikat          ); }
    void  ClearGefahrGutArtikel       ()  {ClearBit(bGefahrGutArtikel        ); }

    void  ClearEinkaufsSperre          () {ClearBit(bEinkaufsSperre          ); }
    void  ClearZytoStatikaArtikel      () {ClearBit(bZytoStatikaArtikel      ); }
    void  ClearArtikelVerKnuepft       ()  {ClearBit(bArtikelVerKnuepft      ); }
    void  ClearNeuerPreisAktiv         ()  {ClearBit(bNeuerPreisAktiv        ); }

    void   SetSekundaerBezeichnung    () {SetBit( bSekundaerBezeichnung   ); }
    void   SetNachfolgeArtikel        () {SetBit( bNachfolgeArtikel       ); }
    void   SetSchnellDreher           () {SetBit( bSchnellDreher          ); }
    void   SetAusserHandel            () {SetBit( bAusserHandel           ); }
    void   SetAuslaufArtikel          () {SetBit( bAuslaufArtikel         ); }
    void   SetRueckRufAktion          () {SetBit( bRueckRufAktion         ); }
    void   SetNettoAktion             () {SetBit( bNettoAktion            ); }
    void   SetNettoArtikel            () {SetBit( bNettoArtikel           ); }

    void   SetGekuehlt08              () {SetBit(bGekuehlt08              ); }
    void   SetGekuehlt20              () {SetBit(bGekuehlt20              ); }
    void   SetKuehlKette              () {SetBit(bKuehlKette              ); }
    void   SetNichtLieferbarHersteller() {SetBit(bNichtLieferbarHersteller); }
    void   SetNichtGeliefertHersteller() {SetBit(bNichtGeliefertHersteller); }
    void   SetNichtUeberGrossHandel   () {SetBit(bNichtUeberGrossHandel   ); }
    void   SetKlinikPackung           () {SetBit(bKlinikPackung           ); }
    void   SetRetourenSperre          () {SetBit(bRetourenSperre          ); }

    void   SetArtikelMeldePflichtig   () {SetBit(bArtikelMeldePflichtig   ); }
    void   SetHerstellerDatum         () {SetBit(bHerstellerDatum         ); }
    void   SetVerfallDatum            () {SetBit(bVerfallDatum            ); }
    void   SetVerfalldatumAnDatamobil () {SetBit(bVerfalldatumAnDatamobil ); }
    void   SetErmaessigtMwst          () {SetBit(bErmaessigtMwst          ); }
    void   SetBestandsBuchung         () {SetBit(bBestandsBuchung         ); }
    void   SetContainerArtikel        () {SetBit(bContainerArtikel        ); }
    void   SetVorkommiArtikel         () {SetBit(bVorkommiArtikel         ); }

    void   SetFeuerGefaehrlich        () {SetBit(bFeuerGefaehrlich        ); }
    void   SetKuehlZelleOeffnen       () {SetBit(bKuehlZelleOeffnen       ); }
    void   SetAutomatikArtikel        () {SetBit(bAutomatikArtikel        ); }
    void   SetDynArtikelRoboter       () {SetBit(bDynArtikelRoboter       ); }
    void   SetWannenKommiArtikel      () {SetBit(bWannenKommiArtikel      ); }
    void   SetHochRegalArtikel        () {SetBit(bHochRegalArtikel        ); }
    void   SetBeiPackMulti            () {SetBit(bBeiPackMulti            ); }
    void   SetArtikelGefuehrt         () {SetBit(bArtikelGefuehrt         ); }

    void   SetAuto2                   () {SetBit(bAuto2                   ); }
    void   SetAuto1                   () {SetBit(bAuto1                   ); }
    void   SetAuto0                   () {SetBit(bAuto0                   ); }
    void   SetAktuellerFestPreis      () {SetBit(bAktuellerFestPreis      ); }
    void   SetNegativArtikel          () {SetBit(bNegativArtikel          ); }
    void   SetPoolArtikel             () {SetBit(bPoolArtikel             ); }
    void   SetHomeCare                () {SetBit(bHomeCare                ); }
    void   SetNatraArtikel            () {SetBit(bNatraArtikel            ); }

    void   SetUeberVorrat             () {SetBit(bUeberVorrat             ); }
    void   SetKKH_VersandApo          () {SetBit(bKKH_VersandApo          ); }
    void   SetGrosseWanneNoetig       () {SetBit(bGrosseWanneNoetig       ); }
    void   SetSonderArtikel           () {SetBit(bSonderArtikel           ); }
    void   SetAktuellerWe             () {SetBit(bAktuellerWe             ); }
    void   SetSkontoFaehig            () {SetBit(bSkontoFaehig            ); }
    void   SetPrismaArtikel           () {SetBit(bPrismaArtikel           ); }
    void   SetBarRabattUebwAuftrag    () {SetBit(bBarRabattUebwAuftrag    ); }

    void   SetA3Laden                 () {SetBit(bA3Laden                 ); }
    void   SetReimportArtikel         () {SetBit(bReimportArtikel         ); }
    void   SetArtikelInUmlagerung     () {SetBit(bArtikelInUmlagerung     ); }
    void   SetAAStaffelAktiv          () {SetBit(bAAStaffelAktiv          ); }
    void   SetKzNurGrosseWanne        () {SetBit(bKzNurGrosseWanne        ); }
    void   SetKzDiabetesStaffel       () {SetBit(bKzDiabetesStaffel       ); }
    void   SetKzBlutArtikel           () {SetBit(bArtikelMitZentralPreis  ); }
    void   SetKzWechselArtikel        () {SetBit(bKzWechselArtikel        ); }

    void   SetVorsichtGlas            () {SetBit(bVorsichtGlas            ); }
    void   SetArtikelMitZentralPreis  () {SetBit(bArtikelMitZentralPreis  ); }
    void   SetSommerKuehlArtikel      () {SetBit(bSommerKuehlArtikel      ); }
    void   SetLichtGeschuetztLagern   () {SetBit(bLichtGeschuetztLagern   ); }
    void   SetBrandGefaehrlich        () {SetBit(bBrandGefaehrlich        ); }
    void   SetLagerortZweiAktiv       () {SetBit(bLagerortZweiAktiv       ); }

    void   SetOhneZertifikat          () {SetBit(bOhneZertifikat          ); }
    void   SetGefahrGutArtikel        () {SetBit(bGefahrGutArtikel        ); }

    void   SetEinkaufsSperre          () {SetBit(bEinkaufsSperre          ); }
    void   SetZytoStatikaArtikel      () {SetBit(bZytoStatikaArtikel      ); }
    void   SetArtikelVerKnuepft       () {SetBit(bArtikelVerKnuepft       ); }
    void   SetNeuerPreisAktiv         () {SetBit(bNeuerPreisAktiv       ); }
};

#endif
