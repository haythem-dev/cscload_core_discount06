#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_AMGE        0
#define COL_BMGE        1
#define COL_NRME        2
#define COL_VERBME      3
#define COL_UMGESCHL    4
#define COL_EINHEIT     5
#define COL_FU          6
#define COL_ARTIKELNAME 7
#define COL_DAF         8
#define COL_PA          9
#define COL_PNR         10
#define COL_CONT        11
#define COL_ARTICLECODE 12
#define COL_PZN         13
#define COL_VERBUND     14
#define COL_VERBUNDFIL  15
#define COL_KENNZEICHEN 16
#define COL_PREIS       17
#define COL_PREISFAKTUR 18
#define COL_AVP         19
#define COL_PCT         20
#define COL_BEMERK      21
#define COL_FILI        22
#define COL_PREISTYP    23
#define COL_PROMONO     24
#define COL_PROMONAME   25
#define COL_ETPOS       26
#define COL_PROMOTYP    27
#define COL_PRODQUOTA   28
#define COL_VBTYP       29
#define COL_DELIVERYDATE 30
#define COL_DELIVERYTIME 31
#define COL_PREISFREE   32
#define COL_PCTMAN      33
#define COL_ANZ_LIST    34

class CAufInfListCtrl : public scgui::VListCtrl
{
public:
    virtual bool                 init                  ();
    virtual void                 refreshItem           (const int iItem);

private:
    virtual bool                 isColEditable         (const int iCol) const;
    virtual bool                 isColNumber           (const int iCol) const;
    virtual UINT                 getLimitText          (const int iCol) const;
};
