#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define KC_COL_CHECK          0
#define KC_COL_AUF_NR         1
#define KC_COL_KUNDE          2
#define KC_COL_ARTIKEL        3
#define KC_COL_BESTELLT       4
#define KC_COL_BESTAETIGT     5
#define KC_COL_MENGE_ALT      6
#define KC_COL_RECHNUNG       7
#define KC_COL_POSNR          8

class CKCListCtrl : public scgui::VListCtrl
{
public:
    virtual bool init();
    virtual void refreshItem(const int iItem);

private:
    virtual bool isColEditable(const int iCol) const;
    virtual bool isColNumber(const int iCol) const;
    virtual UINT getLimitText(const int iCol) const;
};
