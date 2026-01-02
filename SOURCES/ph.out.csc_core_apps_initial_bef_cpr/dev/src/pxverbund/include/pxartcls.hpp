/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXARTCLS.HPP
Article classification flags.

REVISION HISTORY

24 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#ifndef PXARTCLS_INC
#define PXARTCLS_INC

#include "bitmap.hpp"

class pxArtClass : public nBitMap
{

public:
/*----------------------------------------------------------------------------*/
/*  Define article class flags.                                               */
/*  Bits are numbered from left to right, Bytes too.                          */
/*----------------------------------------------------------------------------*/
   enum pxArtClassFlags
   {
       // Byte 0:
       bGiftKlasse1,                    // bitand(etartklasse1, 16384) == 16384
       bGiftKlasse2,                    // bitand(etartklasse1,  8192) ==  8192
       bGiftKlasse3,                    // bitand(etartklasse1,  4096) ==  4096
       bRezeptPflichtig,                // bitand(etartklasse1,  2048) ==  2048
       bApothekenPflichtig,             // bitand(etartklasse1,  1024) ==  1024
       bTaxPflichtig,
       bOpiat,                          // bitand(etartklasse1,   512) ==   512
       bTierArznei,                     // bitand(etartklasse1,   256) ==   256
       // Byte 1:
       bVertriebsBindung1,              // bitand(etartklasse1,   128) ==   128     DE:IFA
       bVertriebsBindung2,              // bitand(etartklasse1,    64) ==    64     DE:Eucerin
       bVertriebsbindung3,              // bitand(etartklasse1,    32) ==    32     DE:Med.Cannabis (neu)
       bVertriebsbindung4,              // bitand(etartklasse1,    16) ==    16     DE:Ales Groupe
       bVertriebsbindung5,              // bitand(etartklasse1,     8) ==     8     DE:Wirkstoff (neu)
       bVertriebsbindung6,              // bitand(etartklasse1,     4) ==     4     DE:ELAC-Eigenmarken
       bVertriebsbindung7,              // bitand(etartklasse1,     2) ==     2     DE:MVDA-Eigenmarken
       bVertriebsbindung8,              // bitand(etartklasse1,     1) ==     1     DE:PHA Pet Health
       // Bytes 2-3 are unused:
       cPXARTCLS_MAPWIDTH = 32
    };


                      ~pxArtClass()  {;}
                      pxArtClass() : nBitMap(cPXARTCLS_MAPWIDTH) {;}
                      pxArtClass(pxArtClass& src) : nBitMap(cPXARTCLS_MAPWIDTH)
                                              {(*this)=src;}
    pxArtClass&       operator=(const pxArtClass& src)
//  Assigns the bit map value of 'src' to self and returns a reference to it.
                      {return (pxArtClass&) nBitMap:: operator=(src);}

    pxArtClass&       operator=(const unsigned char *src)
//  The entire bit map of self is set from the contents of the byte array 'src'.
                      {return (pxArtClass&) nBitMap:: operator=(src);}

    void              Export(long& l1, long& l2) const;
    void              Import(const long l1, const long l2);
    bool              IsAuthorized(const pxArtClass& cust) const;

//  Flag queries and settings:
    bool        IsGiftKlasse1        () const {return TestBit( bGiftKlasse1        ); }
    bool        IsGiftKlasse2        () const {return TestBit( bGiftKlasse2        ); }
    bool        IsGiftKlasse3        () const {return TestBit( bGiftKlasse3        ); }
    bool        IsRezeptPflichtig    () const {return TestBit( bRezeptPflichtig    ); }
    bool        IsApothekenPflichtig () const {return TestBit( bApothekenPflichtig ); }
    bool        IsTaxPflichtig       () const {return TestBit( bTaxPflichtig       ); }
    bool        IsOpiat              () const {return TestBit( bOpiat              ); }
    bool        IsTierArznei         () const {return TestBit( bTierArznei         ); }
    bool        IsVertriebsBindung1  () const {return TestBit( bVertriebsBindung1  ); }
    bool        IsVertriebsBindung2  () const {return TestBit( bVertriebsBindung2  ); }
    bool        IsVertriebsbindung3  () const {return TestBit( bVertriebsbindung3  ); }
    bool        IsVertriebsbindung4  () const {return TestBit( bVertriebsbindung4  ); }
    bool        IsVertriebsbindung5  () const {return TestBit( bVertriebsbindung5  ); }
    bool        IsVertriebsbindung6  () const {return TestBit( bVertriebsbindung6  ); }
    bool        IsVertriebsbindung7  () const {return TestBit( bVertriebsbindung7  ); }
    bool        IsVertriebsbindung8  () const {return TestBit( bVertriebsbindung8  ); }

    bool        IsLegallLinkage      () const {return TestBit( bVertriebsBindung1  ); }
    bool        IsBreizhLinkage      () const {return TestBit( bVertriebsBindung2  ); }

    void        ClearTaxPflichtig    () { ClearBit( bTaxPflichtig       ); }
    void        SetTaxPflichtig      () {   SetBit( bTaxPflichtig       ); }
};
#endif
