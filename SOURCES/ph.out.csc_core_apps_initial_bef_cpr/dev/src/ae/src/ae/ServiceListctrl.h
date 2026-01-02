#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_SP_KB       0
#define COL_SP_DATUM    1
#define COL_SP_VON      2
#define COL_SP_BIS      3
#define COL_SP_BTM      4
#define COL_SP_KK       5
#define COL_SP_K08      6
#define COL_SP_K20      7
#define COL_SP_BEMERK   8
#define COL_SP_ANZ_LIST 9

class CServiceListCtrl : public scgui::VListCtrlEx
{
public:
    virtual bool init();
    virtual void refreshItem(const int);

protected:
    virtual bool isColEditable(const int iCol) const;
    virtual bool isColNumber(const int iCol) const;
    virtual UINT getLimitText(const int iCol) const;
    virtual bool setSubItem(const int, const int, CString&);
};
