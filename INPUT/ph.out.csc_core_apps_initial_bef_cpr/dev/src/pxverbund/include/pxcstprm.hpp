/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

pxcstprm.hpp
Customer permission flags.

REVISION HISTORY

16 Nov 1995 V1.00 REV 00 written by Peter Hoernich.
*/

#ifndef PXCSTPRM_INC
   #define PXCSTPRM_INC

class pxCustPermission : public nBitMap
{

public:
/*----------------------------------------------------------------------------*/
/*  Define customer group flags.                                              */
/*  Bits are numbered from left to right, Bytes too.                          */
/*----------------------------------------------------------------------------*/
    enum pxCustPermissionFlags
    {
       // Byte 0:
       bGiftKlasse1,
       bGiftKlasse2,
       bGiftKlasse3,
       bRezeptPflichtig,
       bApothekenPflichtig,
       bTaxPflichtig,
       bOpiat,
       bTierArznei,
       // Byte 1:
       bVertriebsBindung,
       bLieferSperre,                   // 55% Regelung
       bAbschlag,                       // 55% Regelung
       bPreisErmaessigung,              // 55% Regelung
       bVertriebsbindung1,              // Vichy
       bVertriebsbindung2,              // Bouhon
       bVertriebsbindung3,              // Pool
       bVertriebsbindung4,              // Dental 2000
       cPXCSTPRM_MAPWIDTH = 16
    };

// constructors:
                pxCustPermission() : nBitMap(cPXCSTPRM_MAPWIDTH) {;}
                pxCustPermission(pxCustPermission& src) : nBitMap(cPXCSTPRM_MAPWIDTH)
                                              {(*this)=src;}
// destructor:
                ~pxCustPermission()  {;}
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustPermission& operator=(const pxCustPermission& src)
//  Assigns the bit map value of 'src' to self and returns a reference to it.
                         {return (pxCustPermission&) nBitMap:: operator=(src);}

    pxCustPermission& operator=(const unsigned char *src)
//  The entire bit map of self is set from the contents of the byte array 'src'.
                         {return (pxCustPermission&) nBitMap:: operator=(src);}

//  member functions:
    pxCustPermission& CustPermission()              {return *this; }

    bool        IsGiftKlasse1        () {return TestBit(bGiftKlasse1       ); }
    bool        IsGiftKlasse2        () {return TestBit(bGiftKlasse2       ); }
    bool        IsGiftKlasse3        () {return TestBit(bGiftKlasse3       ); }
    bool        IsRezeptPflichtig    () {return TestBit(bRezeptPflichtig   ); }
    bool        IsApothekenPflichtig () {return TestBit(bApothekenPflichtig); }
    bool        IsTaxPflichtig       () {return TestBit(bTaxPflichtig      ); }
    bool        IsOpiat              () {return TestBit(bOpiat             ); }
    bool        IsTierArznei         () {return TestBit(bTierArznei        ); }

    bool        IsVertriebsBindung   () {return TestBit(bVertriebsBindung  ); }
    bool        IsLieferSperre       () {return TestBit(bLieferSperre      ); }
    bool        IsAbschlag           () {return TestBit(bAbschlag          ); }
    bool        IsPreisErmaessigung  () {return TestBit(bPreisErmaessigung ); }
    bool        IsVertriebsbindung1  () {return TestBit(bVertriebsbindung1 ); }
    bool        IsVertriebsbindung2  () {return TestBit(bVertriebsbindung2 ); }
    bool        IsVertriebsbindung3  () {return TestBit(bVertriebsbindung3 ); }
    bool        IsVertriebsbindung4  () {return TestBit(bVertriebsbindung4 ); }

    void        ClearGiftKlasse1         () { ClearBit( bGiftKlasse1       ); }
    void        ClearGiftKlasse2         () { ClearBit( bGiftKlasse2       ); }
    void        ClearGiftKlasse3         () { ClearBit( bGiftKlasse3       ); }
    void        ClearRezeptPflichtig     () { ClearBit( bRezeptPflichtig   ); }
    void        ClearApothekenPflichtig  () { ClearBit( bApothekenPflichtig); }
    void        ClearTaxPflichtig        () { ClearBit( bTaxPflichtig      ); }
    void        ClearOpiat               () { ClearBit( bOpiat             ); }
    void        ClearTierArznei          () { ClearBit( bTierArznei        ); }

    void        ClearVertriebsBindung    () { ClearBit( bVertriebsBindung  ); }
    void        ClearLieferSperre        () { ClearBit( bLieferSperre      ); }
    void        ClearAbschlag            () { ClearBit( bAbschlag          ); }
    void        ClearPreisErmaessigung   () { ClearBit( bPreisErmaessigung ); }
    void        ClearVertriebsbindung1   () { ClearBit( bVertriebsbindung1 ); }
    void        ClearVertriebsbindung2   () { ClearBit( bVertriebsbindung2 ); }
    void        ClearVertriebsbindung3   () { ClearBit( bVertriebsbindung3 ); }
    void        ClearVertriebsbindung4   () { ClearBit( bVertriebsbindung4 ); }

    void        SetGiftKlasse1           () {   SetBit( bGiftKlasse1       ); }
    void        SetGiftKlasse2           () {   SetBit( bGiftKlasse2       ); }
    void        SetGiftKlasse3           () {   SetBit( bGiftKlasse3       ); }
    void        SetRezeptPflichtig       () {   SetBit( bRezeptPflichtig   ); }
    void        SetApothekenPflichtig    () {   SetBit( bApothekenPflichtig); }
    void        SetTaxPflichtig          () {   SetBit( bTaxPflichtig      ); }
    void        SetOpiat                 () {   SetBit( bOpiat             ); }
    void        SetTierArznei            () {   SetBit( bTierArznei        ); }

    void        SetVertriebsBindung      () {   SetBit( bVertriebsBindung  ); }
    void        SetLieferSperre          () {   SetBit( bLieferSperre      ); }
    void        SetAbschlag              () {   SetBit( bAbschlag          ); }
    void        SetPreisErmaessigung     () {   SetBit( bPreisErmaessigung ); }
    void        SetVertriebsbindung1     () {   SetBit( bVertriebsbindung1 ); }
    void        SetVertriebsbindung2     () {   SetBit( bVertriebsbindung2 ); }
    void        SetVertriebsbindung3     () {   SetBit( bVertriebsbindung3 ); }
    void        SetVertriebsbindung4     () {   SetBit( bVertriebsbindung4 ); }
};

#endif
