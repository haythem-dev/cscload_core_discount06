#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define RO_LC_COL_BENUTZEN      0
#define RO_LC_COL_PRIORITAET    1
#define RO_LC_COL_RECHNR        2
#define RO_LC_COL_DATUM         3
#define RO_LC_COL_RECH_TYP      4
#define RO_LC_COL_WERT          5
#define RO_LC_COL_BEZAHLT       6
#define RO_LC_COL_RABATT        7
#define RO_LC_COL_TAGE_ZAHLUNG  8

class CROListCtrl : public scgui::VListCtrl
{
public:
    virtual bool init();
    virtual void refreshItem(const int );
    void setEdit(const int iItem, const int iSubItem);

private:
    virtual bool isColEditable(const int iCol) const;
    virtual bool isColNumber(const int iCol) const;
    virtual UINT getLimitText(const int iCol) const;
    virtual bool setSubItem(const int, const int iSubItem, CString& csText);
};
