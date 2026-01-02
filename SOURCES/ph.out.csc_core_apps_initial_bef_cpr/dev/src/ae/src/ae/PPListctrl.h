
#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define PROMO_PP_COL_PROMONR        0
#define PROMO_PP_COL_NAME           1
#define PROMO_PP_COL_AEP            2
#define PROMO_PP_COL_RAB            3
#define PROMO_PP_COL_RABWERT        4
#define PROMO_PP_COL_MAX            5
#define PROMO_PP_COL_BESTAND        6
#define PROMO_PP_COL_MENGE          7
#define PROMO_PP_COL_GEBUCHT        8
#define PROMO_PP_COL_PZN            9
#define PROMO_PP_COL_ADDON         10

class CPPListCtrl : public scgui::VListCtrl
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
};
