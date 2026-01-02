/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXARTFLM.HPP
Article decision flags (Master).

REVISION HISTORY

4 March 1999 V1.00 REV 00 written by Dietmar Schloetel.
*/

#ifndef PXARTFLM_INC
#define PXARTFLM_INC

#include <bitmap.hpp>

class pxArtMFlags : public nBitMap
{

public:
   enum pxArtDecFlagsMaster
   {
       // Byte 0:
       bSekundaerBezeichnung,           // For UNIPHARM compatibility
       bNachfolgeArtikel,               // Nachfolgeartikel vorhanden
       b2,
       bAusserHandel,
       bAuslaufArtikel,
       bRueckRufAktion,
       b6,
       b7,
       // Byte 1:
       b8,
       bGekuehlt20,                     //                20 Grad
       b10,
       bNichtLieferbarHersteller,
       b12,
       bNichtUeberGrossHandel,
       bKlinikPackung,
       b15,
       // Byte 2:
       bArtikelMeldePflichtig,
       bHerstellerDatum,
       bVerfallDatum,
       b19,
       bErmaessigtMwst,
       b21,
       b22,
       b23,
       // Byte 3:
       bFeuerGefaehrlich,
       b25,
       b26,
       b27,
       b28,
       b29,
       b30,
       b31,
       // Byte 4:
       b32,
       b33,
       b34,
       bAktuellerFestPreis,
       bNegativArtikel,
       bPoolArtikel,
       bHomeCare,
       b39,
       // Byte 5:
       b40,
       bKKH_VersandApo,                 // ???
       b42,
       b43,
       b44,
       b45,
       bPrismaArtikel,
       b47,
       // Byte 6:
       b48,
       bReimportArtikel,
       b50,
       b51,
       b52,
       b53,
       b54,
       b55,
       // Byte 7:
       b56,
       b57,
       b58,
       b59,
       b60,
       b61,
       bOhneZertifikat,
       bGefahrGutArtikel,
       // Byte 8:
       b64,
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
       b78,
       b79,

       cPXARTFLM_MAPWIDTH = 80          // max number of bits in this map
    };

                      ~pxArtMFlags()  {;}
                      pxArtMFlags() : nBitMap(cPXARTFLM_MAPWIDTH) {;}
                      pxArtMFlags(pxArtMFlags& src) : nBitMap(cPXARTFLM_MAPWIDTH)
                                              {(*this)=src;}

    pxArtMFlags&       operator=(const pxArtMFlags& src)
//  Assigns the bit map value of 'src' to self and returns a reference to it.
                      {return (pxArtMFlags&) nBitMap:: operator=(src);}

    pxArtMFlags&       operator=(const unsigned char *src)
//  The entire bit map of self is set from the contents of the byte array 'src'.
                      {return (pxArtMFlags&) nBitMap:: operator=(src);}

    void              Export(long& l1,long& l2,long& l3,long& l4,long& l5) const;
    void              Import(const long l1,const long l2,const long l3,
                             const long l4,const long l5);

//  Flag queries and settings:
    bool        IsSekundaerBezeichnung() {return TestBit( bSekundaerBezeichnung ); }
    bool        IsNachfolgeArtikel    () {return TestBit( bNachfolgeArtikel     ); }
    bool        IsAusserHandel        () {return TestBit( bAusserHandel         ); }
    bool        IsAuslaufArtikel      () {return TestBit( bAuslaufArtikel       ); }
    bool        IsRueckRufAktion      () {return TestBit( bRueckRufAktion       ); }

    bool        IsGekuehlt20              () {return TestBit(bGekuehlt20              ); }
    bool        IsNichtLieferbarHersteller() {return TestBit(bNichtLieferbarHersteller); }
    bool        IsNichtUeberGrossHandel   () {return TestBit(bNichtUeberGrossHandel   ); }
    bool        IsKlinikPackung           () {return TestBit(bKlinikPackung           ); }

    bool        IsArtikelMeldePflichtig   () {return TestBit(bArtikelMeldePflichtig   ); }
    bool        IsHerstellerDatum         () {return TestBit(bHerstellerDatum         ); }
    bool        IsVerfallDatum            () {return TestBit(bVerfallDatum            ); }
    bool        IsErmaessigtMwst          () {return TestBit(bErmaessigtMwst          ); }

    bool        IsFeuerGefaehrlich        () {return TestBit(bFeuerGefaehrlich        ); }

    bool        IsAktuellerFestPreis      () {return TestBit(bAktuellerFestPreis      ); }
    bool        IsNegativArtikel          () {return TestBit(bNegativArtikel          ); }
    bool        IsPoolArtikel             () {return TestBit(bPoolArtikel             ); }
    bool        IsHomeCare                () {return TestBit(bHomeCare                ); }

    bool        IsKKH_VersandApo          () {return TestBit(bKKH_VersandApo          ); }
    bool        IsPrismaArtikel           () {return TestBit(bPrismaArtikel           ); }

    bool        IsReimportArtikel         () {return TestBit(bReimportArtikel         ); }
    bool        IsOhneZertifikat          () {return TestBit(bOhneZertifikat          ); }
    bool        IsGefahrGutArtikel        () {return TestBit(bGefahrGutArtikel        ); }

    bool        IsZytoStatikaArtikel      () {return TestBit(bZytoStatikaArtikel      ); }
    bool        IsArtikelVerKnuepft       () {return TestBit(bArtikelVerKnuepft       ); }

    void  ClearSekundaerBezeichnung    () {ClearBit( bSekundaerBezeichnung   ); }
    void  ClearNachfolgeArtikel        () {ClearBit( bNachfolgeArtikel       ); }
    void  ClearAusserHandel            () {ClearBit( bAusserHandel           ); }
    void  ClearAuslaufArtikel          () {ClearBit( bAuslaufArtikel         ); }
    void  ClearRueckRufAktion          () {ClearBit( bRueckRufAktion         ); }

    void  ClearGekuehlt20              () {ClearBit(bGekuehlt20              ); }
    void  ClearNichtLieferbarHersteller() {ClearBit(bNichtLieferbarHersteller); }
    void  ClearNichtUeberGrossHandel   () {ClearBit(bNichtUeberGrossHandel   ); }
    void  ClearKlinikPackung           () {ClearBit(bKlinikPackung           ); }

    void  ClearArtikelMeldePflichtig   () {ClearBit(bArtikelMeldePflichtig   ); }
    void  ClearHerstellerDatum         () {ClearBit(bHerstellerDatum         ); }
    void  ClearVerfallDatum            () {ClearBit(bVerfallDatum            ); }
    void  ClearErmaessigtMwst          () {ClearBit(bErmaessigtMwst          ); }

    void  ClearFeuerGefaehrlich        () {ClearBit(bFeuerGefaehrlich        ); }

    void  ClearAktuellerFestPreis      () {ClearBit(bAktuellerFestPreis      ); }
    void  ClearNegativArtikel          () {ClearBit(bNegativArtikel          ); }
    void  ClearPoolArtikel             () {ClearBit(bPoolArtikel             ); }
    void  ClearHomeCare                () {ClearBit(bHomeCare                ); }

    void  ClearKKH_VersandApo          () {ClearBit(bKKH_VersandApo          ); }
    void  ClearPrismaArtikel           () {ClearBit(bPrismaArtikel           ); }

    void  ClearReimportArtikel         () {ClearBit(bReimportArtikel         ); }
    void  ClearOhneZertifikat         ()  {ClearBit(bOhneZertifikat          ); }
    void  ClearGefahrGutArtikel       ()  {ClearBit(bGefahrGutArtikel        ); }

    void  ClearZytoStatikaArtikel     ()  {ClearBit(bZytoStatikaArtikel      ); }
    void  ClearArtikelVerKnuepft      ()  {ClearBit(bArtikelVerKnuepft       ); }

    void   SetSekundaerBezeichnung    () {SetBit( bSekundaerBezeichnung   ); }
    void   SetNachfolgeArtikel        () {SetBit( bNachfolgeArtikel       ); }
    void   SetAusserHandel            () {SetBit( bAusserHandel           ); }
    void   SetAuslaufArtikel          () {SetBit( bAuslaufArtikel         ); }
    void   SetRueckRufAktion          () {SetBit( bRueckRufAktion         ); }

    void   SetGekuehlt20              () {SetBit(bGekuehlt20              ); }
    void   SetNichtLieferbarHersteller() {SetBit(bNichtLieferbarHersteller); }
    void   SetNichtUeberGrossHandel   () {SetBit(bNichtUeberGrossHandel   ); }
    void   SetKlinikPackung           () {SetBit(bKlinikPackung           ); }

    void   SetArtikelMeldePflichtig   () {SetBit(bArtikelMeldePflichtig   ); }
    void   SetHerstellerDatum         () {SetBit(bHerstellerDatum         ); }
    void   SetVerfallDatum            () {SetBit(bVerfallDatum            ); }
    void   SetErmaessigtMwst          () {SetBit(bErmaessigtMwst          ); }

    void   SetFeuerGefaehrlich        () {SetBit(bFeuerGefaehrlich        ); }

    void   SetAktuellerFestPreis      () {SetBit(bAktuellerFestPreis      ); }
    void   SetNegativArtikel          () {SetBit(bNegativArtikel          ); }
    void   SetPoolArtikel             () {SetBit(bPoolArtikel             ); }
    void   SetHomeCare                () {SetBit(bHomeCare                ); }

    void   SetKKH_VersandApo          () {SetBit(bKKH_VersandApo          ); }
    void   SetPrismaArtikel           () {SetBit(bPrismaArtikel           ); }

    void   SetReimportArtikel         () {SetBit(bReimportArtikel         ); }
    void   SetOhneZertifikat          () {SetBit(bOhneZertifikat          ); }
    void   SetGefahrGutArtikel        () {SetBit(bGefahrGutArtikel        ); }

    void   SetZytoStatikaArtikel      () {SetBit(bZytoStatikaArtikel      ); }
    void   SetArtikelVerKnuepft       () {SetBit(bArtikelVerKnuepft       ); }
};

#endif
