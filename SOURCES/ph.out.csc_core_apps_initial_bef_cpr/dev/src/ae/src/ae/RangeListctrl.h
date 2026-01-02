
#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define RL_COL_KB           0
#define RL_COL_GRPNO        1
#define RL_COL_GRPNAME      2
#define RL_COL_ARTNO        3
#define RL_COL_BASEQTY      4
#define RL_COL_QTY          5
#define RL_COL_QTY_DIFF     6
#define RL_COL_BASEVALUE    7
#define RL_COL_VALUE        8
#define RL_COL_VALUE_DIFF   9
#define RL_COL_DISCVALUE    10
#define RL_COL_DISCQTY      11
#define RL_COL_DISCARTICLE  12
#define RL_COL_DISCARTNAME  13
#define NUM_COLUMNS         14

class CRangeListCtrl : public scgui::VListCtrl
{
public:
    virtual bool init();
    virtual void refreshItem(const int);

private:
    virtual bool isColEditable(const int) const;
    virtual bool isColNumber(const int) const;
    virtual UINT getLimitText(const int) const;
};
