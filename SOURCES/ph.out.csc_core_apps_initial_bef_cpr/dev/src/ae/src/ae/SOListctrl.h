#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_KB          0
#define COL_AMGE        1
#define COL_BMGE        2
#define COL_NRME        3
#define COL_VERBME      4
#define COL_UMGESCHL    5
#define COL_EINHEIT     6
#define COL_FU          7
#define COL_ARTIKELNAME 8
#define COL_DAF         9
#define COL_KENNZEICHEN 10
#define COL_PA          11
#define COL_PNR         12
#define COL_ARTICLE_CODE 13
#define COL_VERBUND     14
#define COL_PREIS       15
#define COL_RABATT      16
#define COL_RABATT_MAN  17
#define COL_AVP         18
#define COL_BEMERK      19
#define COL_FILI        20
#define COL_CHARGE      21
#define COL_PROMOTYP    22
#define COL_PROMONR     23
#define COL_PHARMACYGROUPID 24
#define COL_DISCOUNTGRPNO   25
#define COL_BASEQTY     26
#define COL_BASE_VALUE  27
#define COL_PZN         28
#define COL_ANZ_LIST    29

class CSOListCtrl : public scgui::VListCtrl
{
public:
    virtual bool init();
    virtual void refreshItem(const int);

private:
    virtual bool isColEditable(const int) const;
    virtual bool isColNumber(const int) const;
    virtual UINT getLimitText(const int) const;
};
