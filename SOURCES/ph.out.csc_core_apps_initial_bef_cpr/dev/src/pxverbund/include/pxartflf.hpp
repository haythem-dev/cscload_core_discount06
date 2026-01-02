/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXARTFLF.HPP
Article decision flags dependent on branch

REVISION HISTORY

4 Mar 1999 V1.00 REV 00 written by Dietmar Schloetel.
*/

#ifndef PXARTFLF_INC
#define PXARTFLF_INC

#include <bitmap.hpp>

class pxArtFFlags : public nBitMap
{

public:
   enum pxArtDecFlagsFiliale
   {
       // Byte 0:
       b0,																					// bitand(artikellokal.etartschalter1, 32768)
       b1,																					// bitand(artikellokal.etartschalter1, 16384)
       bSchnellDreher,																		// bitand(artikellokal.etartschalter1, 8192)
       b3,																					// bitand(artikellokal.etartschalter1, 4096)
       b4,																					// bitand(artikellokal.etartschalter1, 2048)
       b5,																					// bitand(artikellokal.etartschalter1, 1024)
       bNettoAktion,																		// bitand(artikellokal.etartschalter1, 512)
       bNettoArtikel,																		// bitand(artikellokal.etartschalter1, 256)
       // Byte 1:
       bGekuehlt08,                     // Gekuehlt unter 08 Grad							// bitand(artikellokal.etartschalter1, 128)
       b9,																					// bitand(artikellokal.etartschalter1, 64)
       bKuehlKette,																			// bitand(artikellokal.etartschalter1, 32)
       b11,																					// bitand(artikellokal.etartschalter1, 16)
       bNichtGeliefertHersteller,															// bitand(artikellokal.etartschalter1, 8)
       b13,																					// bitand(artikellokal.etartschalter1, 4)
       b14,																					// bitand(artikellokal.etartschalter1, 2)
       bRetourenSperre,																		// bitand(artikellokal.etartschalter1, 1)
       // Byte 2:
       b16,																					// bitand(artikellokal.etartschalter2, 32768)
       b17,																					// bitand(artikellokal.etartschalter2, 16384)
       b18,																					// bitand(artikellokal.etartschalter2, 8192)
       bVerfalldatumAnDatamobil,															// bitand(artikellokal.etartschalter2, 4096)
       b20,																					// bitand(artikellokal.etartschalter2, 2048)
       bBestandsBuchung,																	// bitand(artikellokal.etartschalter2, 1024)
       bContainerArtikel,																	// bitand(artikellokal.etartschalter2, 512)
       bVorkommiArtikel,																	// bitand(artikellokal.etartschalter2, 256)
       // Byte 3:
       b24,																					// bitand(artikellokal.etartschalter2, 128)
       bKuehlZelleOeffnen,																	// bitand(artikellokal.etartschalter2, 64)
       bAutomatikArtikel,																	// bitand(artikellokal.etartschalter2, 32)
       bDynArtikelRoboter,              // Dynamischer Artikel (Roboter)					// bitand(artikellokal.etartschalter2, 16)
       bWannenKommiArtikel,             // Dortmund											// bitand(artikellokal.etartschalter2, 8)
       bHochRegalArtikel,               // EPG												// bitand(artikellokal.etartschalter2, 4)
       bBeiPackMulti,																		// bitand(artikellokal.etartschalter2, 2)
       bArtikelGefuehrt,																	// bitand(artikellokal.etartschalter2, 1)
       // Byte 4:
       bAuto2,                          // Noch belegt (whatever this means?)				// bitand(artikellokal.etartschalter3, 32768)
       bAuto1,                          // Noch belegt (whatever this means?)				// bitand(artikellokal.etartschalter3, 16384)
       bAuto0,                          // Noch belegt (whatever this means?)				// bitand(artikellokal.etartschalter3, 8192)
       b35,																					// bitand(artikellokal.etartschalter3, 4096)
       b36,																					// bitand(artikellokal.etartschalter3, 2048)
       b37,																					// bitand(artikellokal.etartschalter3, 1024)
       b38,																					// bitand(artikellokal.etartschalter3, 512)
       bNatraArtikel,																		// bitand(artikellokal.etartschalter3, 256)
       // Byte 5:
       bUeberVorrat,																		// bitand(artikellokal.etartschalter3, 128)
       b41,																					// bitand(artikellokal.etartschalter3, 64)
       bGrosseWanneNoetig,																	// bitand(artikellokal.etartschalter3, 32)
       bSonderArtikel,																		// bitand(artikellokal.etartschalter3, 16)
       bAktuellerWe,																		// bitand(artikellokal.etartschalter3, 8)
       bSkontoFaehig,																		// bitand(artikellokal.etartschalter3, 4)
       b46,																					// bitand(artikellokal.etartschalter3, 2)
       bBarRabattUebwAuftrag,																// bitand(artikellokal.etartschalter3, 1)
       // Byte 6:
       bA3Laden,																			// bitand(artikellokal.etartschalter4, 32768)
       b49,																					// bitand(artikellokal.etartschalter4, 16384)
       bArtikelInUmlagerung,																// bitand(artikellokal.etartschalter4, 8192)
       bAAStaffelAktiv,																		// bitand(artikellokal.etartschalter4, 4096)
       bKzNurGrosseWanne,																	// bitand(artikellokal.etartschalter4, 2048)
       bKzDiabetesStaffel,																	// bitand(artikellokal.etartschalter4, 1024)
       bKzBlutArtikel,																		// bitand(artikellokal.etartschalter4, 512)
       bKzWechselArtikel,																	// bitand(artikellokal.etartschalter4, 256)
       // Byte 7:
       bVorsichtGlas,																		// bitand(artikellokal.etartschalter4, 128)
       bArtikelMitZentralPreis,																// bitand(artikellokal.etartschalter4, 64)
       bSommerKuehlArtikel,																	// bitand(artikellokal.etartschalter4, 32)
       bLichtGeschuetztLagern,																// bitand(artikellokal.etartschalter4, 16)
       bFeuerGefaehrlich,																	// bitand(artikellokal.etartschalter4, 8)
       bLagerortZweiAktiv,																	// bitand(artikellokal.etartschalter4, 4)
       b62,																					// bitand(artikellokal.etartschalter4, 2)
       b63,																					// bitand(artikellokal.etartschalter4, 1)
       // Byte 8:
       bEinkaufsSperre,																		// bitand(artikellokal.etartschalter5, 32768)
       b65,																					// bitand(artikellokal.etartschalter5, 16384)
       b66,																					// bitand(artikellokal.etartschalter5, 8192)
       b67,																					// bitand(artikellokal.etartschalter5, 4096)
       b68,																					// bitand(artikellokal.etartschalter5, 2048)
       b69,																					// bitand(artikellokal.etartschalter5, 1024)
       b70,																					// bitand(artikellokal.etartschalter5, 512)
       b71,																					// bitand(artikellokal.etartschalter5, 256)
       // Byte 9:
       b72,																					// bitand(artikellokal.etartschalter5, 128)
       b73,																					// bitand(artikellokal.etartschalter5, 64)
       b74,																					// bitand(artikellokal.etartschalter5, 32)
       b75,																					// bitand(artikellokal.etartschalter5, 16)
       b76,																					// bitand(artikellokal.etartschalter5, 8)
       b77,																					// bitand(artikellokal.etartschalter5, 4)
       bNeuerPreisWarten,																	// bitand(artikellokal.etartschalter5, 2)
       bNeuerPreisAktiv,																	// bitand(artikellokal.etartschalter5, 1)




       // Byte 7:

       cPXARTFLF_MAPWIDTH = 80          // max number of bits in this map
    };

                      ~pxArtFFlags()  {;}
                      pxArtFFlags() : nBitMap(cPXARTFLF_MAPWIDTH) {;}
                      pxArtFFlags(pxArtFFlags& src) : nBitMap(cPXARTFLF_MAPWIDTH)
                                              {(*this)=src;}

    pxArtFFlags&       operator=(const pxArtFFlags& src)
//  Assigns the bit map value of 'src' to self and returns a reference to it.
                      {return (pxArtFFlags&) nBitMap:: operator=(src);}

    pxArtFFlags&       operator=(const unsigned char *src)
//  The entire bit map of self is set from the contents of the byte array 'src'.
                      {return (pxArtFFlags&) nBitMap:: operator=(src);}

    void              Export(long& l1,long& l2,long& l3,long& l4,long& l5) const;
    void              Import(const long l1,const long l2,const long l3,
                             const long l4,const long l5);

//  Flag queries and settings:
    bool        IsSchnellDreher       () {return TestBit( bSchnellDreher        ); }
    bool        IsNettoAktion         () {return TestBit( bNettoAktion          ); }
    bool        IsNettoArtikel        () {return TestBit( bNettoArtikel         ); }
    bool        IsGekuehlt08          () {return TestBit(bGekuehlt08            ); }
    bool        IsKuehlKette          () {return TestBit(bKuehlKette            ); }

    bool        IsNichtGeliefertHersteller() {return TestBit(bNichtGeliefertHersteller); }
    bool        IsRetourenSperre          () {return TestBit(bRetourenSperre          ); }

    bool        IsVerfalldatumAnDatamobil () {return TestBit(bVerfalldatumAnDatamobil ); }
    bool        IsBestandsBuchung         () {return TestBit(bBestandsBuchung         ); }
    bool        IsContainerArtikel        () {return TestBit(bContainerArtikel        ); }
    bool        IsVorkommiArtikel         () {return TestBit(bVorkommiArtikel         ); }

    bool        IsKuehlZelleOeffnen       () {return TestBit(bKuehlZelleOeffnen       ); }
    bool        IsAutomatikArtikel        () {return TestBit(bAutomatikArtikel        ); }
    bool        IsDynArtikelRoboter       () {return TestBit(bDynArtikelRoboter       ); }
    bool        IsWannenKommiArtikel      () {return TestBit(bWannenKommiArtikel      ); }
    bool        IsHochRegalArtikel        () {return TestBit(bHochRegalArtikel        ); }
    bool        IsBeiPackMulti            () {return TestBit(bBeiPackMulti            ); }
    bool        IsArtikelGefuehrt         () {return TestBit(bArtikelGefuehrt         ); }

    bool        IsAuto2                   () {return TestBit(bAuto2                   ); }
    bool        IsAuto1                   () {return TestBit(bAuto1                   ); }
    bool        IsAuto0                   () {return TestBit(bAuto0                   ); }
    bool        IsNatraArtikel            () {return TestBit(bNatraArtikel            ); }

    bool        IsUeberVorrat             () {return TestBit(bUeberVorrat             ); }
    bool        IsGrosseWanneNoetig       () {return TestBit(bGrosseWanneNoetig       ); }
    bool        IsSonderArtikel           () {return TestBit(bSonderArtikel           ); }
    bool        IsAktuellerWe             () {return TestBit(bAktuellerWe             ); }
    bool        IsSkontoFaehig            () {return TestBit(bSkontoFaehig            ); }
    bool        IsBarRabattUebwAuftrag    () {return TestBit(bBarRabattUebwAuftrag    ); }

    bool        IsA3Laden                 () {return TestBit(bA3Laden                 ); }
    bool        IsArtikelInUmlagerung     () {return TestBit(bArtikelInUmlagerung     ); }
    bool        IsAAStaffelAktiv          () {return TestBit(bAAStaffelAktiv          ); }
    bool        IsKzNurGrosseWanne        () {return TestBit(bKzNurGrosseWanne        ); }
    bool        IsKzDiabetesStaffel       () {return TestBit(bKzDiabetesStaffel       ); }
    bool        IsKzBlutArtikel           () {return TestBit(bArtikelMitZentralPreis  ); }
    bool        IsKzWechselArtikel        () {return TestBit(bKzWechselArtikel        ); }

    bool        IsVorsichtGlas            () {return TestBit(bVorsichtGlas            ); }
    bool        IsArtikelMitZentralPreis  () {return TestBit(bArtikelMitZentralPreis  ); }
    bool        IsSommerKuehlArtikel      () {return TestBit(bSommerKuehlArtikel      ); }
    bool        IsLichtGeschuetztLagern   () {return TestBit(bLichtGeschuetztLagern   ); }
    bool        IsFeuerGefaehrlich        () {return TestBit(bFeuerGefaehrlich        ); }
    bool        IsLagerortZweiAktiv       () {return TestBit(bLagerortZweiAktiv       ); }

    bool        IsEinkaufsSperre          () {return TestBit(bEinkaufsSperre          ); }

    void  ClearSchnellDreher           () {ClearBit( bSchnellDreher          ); }
    void  ClearNettoAktion             () {ClearBit( bNettoAktion            ); }
    void  ClearNettoArtikel            () {ClearBit( bNettoArtikel           ); }
    void  ClearGekuehlt08              () {ClearBit(bGekuehlt08              ); }
    void  ClearKuehlKette              () {ClearBit(bKuehlKette              ); }

    void  ClearNichtGeliefertHersteller() {ClearBit(bNichtGeliefertHersteller); }
    void  ClearRetourenSperre          () {ClearBit(bRetourenSperre          ); }

    void  ClearVerfalldatumAnDatamobil () {ClearBit(bVerfalldatumAnDatamobil ); }
    void  ClearBestandsBuchung         () {ClearBit(bBestandsBuchung         ); }
    void  ClearContainerArtikel        () {ClearBit(bContainerArtikel        ); }
    void  ClearVorkommiArtikel         () {ClearBit(bVorkommiArtikel         ); }

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
    void  ClearNatraArtikel            () {ClearBit(bNatraArtikel            ); }

    void  ClearUeberVorrat             () {ClearBit(bUeberVorrat             ); }
    void  ClearGrosseWanneNoetig       () {ClearBit(bGrosseWanneNoetig       ); }
    void  ClearSonderArtikel           () {ClearBit(bSonderArtikel           ); }
    void  ClearAktuellerWe             () {ClearBit(bAktuellerWe             ); }
    void  ClearSkontoFaehig            () {ClearBit(bSkontoFaehig            ); }
    void  ClearBarRabattUebwAuftrag    () {ClearBit(bBarRabattUebwAuftrag    ); }

    void  ClearA3Laden                 () {ClearBit(bA3Laden                 ); }
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
    void  ClearFeuerGefaehrlich        () {ClearBit(bFeuerGefaehrlich        ); }
    void  ClearLagerortZweiAktiv       () {ClearBit(bLagerortZweiAktiv       ); }

    void  ClearEinkaufsSperre          () {ClearBit(bEinkaufsSperre          ); }

    void   SetSchnellDreher           () {SetBit( bSchnellDreher          ); }
    void   SetNettoAktion             () {SetBit( bNettoAktion            ); }
    void   SetNettoArtikel            () {SetBit( bNettoArtikel           ); }
    void   SetGekuehlt08              () {SetBit(bGekuehlt08              ); }
    void   SetKuehlKette              () {SetBit(bKuehlKette              ); }

    void   SetNichtGeliefertHersteller() {SetBit(bNichtGeliefertHersteller); }
    void   SetRetourenSperre          () {SetBit(bRetourenSperre          ); }

    void   SetVerfalldatumAnDatamobil () {SetBit(bVerfalldatumAnDatamobil ); }
    void   SetBestandsBuchung         () {SetBit(bBestandsBuchung         ); }
    void   SetContainerArtikel        () {SetBit(bContainerArtikel        ); }
    void   SetVorkommiArtikel         () {SetBit(bVorkommiArtikel         ); }

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
    void   SetNatraArtikel            () {SetBit(bNatraArtikel            ); }

    void   SetUeberVorrat             () {SetBit(bUeberVorrat             ); }
    void   SetGrosseWanneNoetig       () {SetBit(bGrosseWanneNoetig       ); }
    void   SetSonderArtikel           () {SetBit(bSonderArtikel           ); }
    void   SetAktuellerWe             () {SetBit(bAktuellerWe             ); }
    void   SetSkontoFaehig            () {SetBit(bSkontoFaehig            ); }
    void   SetBarRabattUebwAuftrag    () {SetBit(bBarRabattUebwAuftrag    ); }

    void   SetA3Laden                 () {SetBit(bA3Laden                 ); }
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
    void   SetFeuerGefaehrlich        () {SetBit(bFeuerGefaehrlich        ); }
    void   SetLagerortZweiAktiv       () {SetBit(bLagerortZweiAktiv       ); }

    void   SetEinkaufsSperre          () {SetBit(bEinkaufsSperre          ); }
};

#endif
