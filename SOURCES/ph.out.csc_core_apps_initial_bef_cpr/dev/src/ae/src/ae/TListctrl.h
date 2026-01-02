#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define TENDER_LC_COL_KB             0
#define TENDER_LC_COL_BESTAND        1
#define TENDER_LC_COL_GELIEFERT      2
#define TENDER_LC_COL_VEREINBART     3
#define TENDER_LC_COL_PZN            4
#define TENDER_LC_COL_EINHEIT        5
#define TENDER_LC_COL_ARTIKELNAME    6
#define TENDER_LC_COL_PREIS          7
#define TENDER_LC_COL_RABATT         8
#define TENDER_LC_COL_VERFALL        9
#define TENDER_LC_COL_TAXLEVEL       10
#define TENDER_LC_COL_AEP            11
#define TENDER_LC_COL_SPANNE         12
#define TENDER_LC_COL_GROSSO         13

class CTListCtrl : public scgui::VListCtrl
{
public:
    virtual bool init();
    virtual void refreshItem(const int);

private:
    virtual bool isColEditable(const int) const;
    virtual bool isColNumber(const int) const;
    virtual UINT getLimitText(const int) const;
};
