#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_VA_KB       0
#define COL_VA_VON      1
#define COL_VA_BIS      2
#define COL_VA_ANZ_LIST 3

class CVacationListCtrl : public scgui::VListCtrlEx
{
public:
    virtual bool init();
    virtual void refreshItem(const int);

private:
    virtual bool isColEditable(const int iCol) const;
    virtual bool isColNumber(const int iCol) const;
    virtual UINT getLimitText(const int iCol) const;
    virtual bool setSubItem(const int, const int, CString&);
};
