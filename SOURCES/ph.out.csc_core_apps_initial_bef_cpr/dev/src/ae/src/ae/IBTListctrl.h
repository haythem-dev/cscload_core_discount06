#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>
#include "IBTListctrlDefines.h"

class CIBTListCtrl : public scgui::VListCtrl
{
public:
    virtual bool init();
    virtual void refreshItem(const int iItem);

private:
    virtual bool isColEditable(const int iCol) const;
    virtual bool isColNumber(const int iCol) const;
    virtual UINT getLimitText(const int iCol) const;
};
