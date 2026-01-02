#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define PROMO_LC_COL_NAME           0
#define PROMO_LC_COL_RABATT         1
#define PROMO_LC_COL_WERT_NETTO     2
#define PROMO_LC_COL_MIN            3
#define PROMO_LC_COL_NR             4
#define PROMO_LC_COL_MAX            5
#define PROMO_LC_COL_VERFALL        6
#define PROMO_LC_COL_BESTAND        7
#define PROMO_LC_COL_MENGE          8
#define PROMO_LC_COL_WERT_BRUTTO    9
#define PROMO_LC_COL_WERT           10
#define PROMO_LC_COL_PZN            11
#define PROMO_LC_COL_PROPORT        12
#define PROMO_LC_COL_MIN_SOLO       13
#define PROMO_LC_COL_MAX_SOLO       14
#define PROMO_LC_COL_NR_SOLO        15
#define PROMO_LC_COL_AEP            16
#define PROMO_LC_COL_TAX            17

class CPMListCtrl : public scgui::VListCtrl
{
public:
    virtual bool init();
    virtual void refreshItem(const int iItem);

private:
    virtual bool isColEditable(const int iCol) const;
    virtual bool isColNumber(const int iCol) const;
    virtual UINT getLimitText(const int iCol) const;
    virtual bool setSubItem(const int iItem, const int iSubItem, CString& csText);

protected:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //DECLARE_MESSAGE_MAP()
};
