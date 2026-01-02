#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_AI_KB           0
#define COL_AI_AMGE         1
#define COL_AI_BMGE         2
#define COL_AI_NRME         3
#define COL_AI_VERBME       4
#define COL_AI_VBTYP        5
#define COL_AI_UMGESCHL     6
#define COL_AI_EINHEIT      7
#define COL_AI_FU           8
#define COL_AI_ARTIKELNAME  9
#define COL_AI_DAF          10
#define COL_AI_KENNZEICHEN  11
#define COL_AI_PA           12
#define COL_AI_PNR          13
#define COL_AI_ARTICLE_CODE 14
#define COL_AI_VERBUND      15
#define COL_AI_PREIS        16
#define COL_AI_PREISFAKTUR  17
#define COL_AI_RABATT       18
#define COL_AI_RABATT_MAN   19
#define COL_AI_AVP          20
#define COL_AI_BEMERK       21
#define COL_AI_FILI         22
#define COL_AI_CHARGE       23
#define COL_AI_PROMOTYP     24
#define COL_AI_PROMONR      25
#define COL_AI_PHARMACYGROUPID  26
#define COL_AI_DISCOUNTGRPNO    27
#define COL_AI_BASEQTY      28
#define COL_AI_BASE_VALUE   29
#define COL_AI_PZN          30
#define COL_AI_DELIVERYDATE 31
#define COL_AI_DELIVERYTIME 32
#define COL_AI_NATRABESTELLT    33
#define COL_AI_ANZ_LIST     34

class CAIListCtrl : public scgui::VListCtrl
{
public:
    virtual bool                 init                  ();
    virtual void                 refreshItem           (const int iItem);

private:
    virtual bool                 isColEditable         (const int iCol) const;
    virtual bool                 isColNumber           (const int iCol) const;
    virtual UINT                 getLimitText          (const int iCol) const;
};
