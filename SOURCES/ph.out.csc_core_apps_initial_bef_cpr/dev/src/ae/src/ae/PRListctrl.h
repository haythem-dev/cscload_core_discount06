#pragma once

#include <libsccpattern.h>
#include <libsccstring.h>
#include <libscgmmultilang.h>
#include <libscgmctrl.h>

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define PROMO_LR_COL_NAME           0
#define PROMO_LR_COL_MIN            1
#define PROMO_LR_COL_MAX            2
#define PROMO_LR_COL_BESTAND        3
#define PROMO_LR_COL_MENGE          4
#define PROMO_LR_COL_PZN            5
#define PROMO_LR_COL_MAX_SOLO       6
#define PROMO_LR_COL_MIN_SOLO       7


class CPRListCtrl : public scgui::VListCtrl
{
public:
    virtual bool init();
    virtual void refreshItem(const int);
    void SetNoEdit(bool bNoEdit = true) { m_bNoEdit = bNoEdit; }   //Feld nicht editierbar machen

private:
    virtual bool isColEditable(const int iCol) const;
    virtual bool isColNumber(const int iCol) const;
    virtual UINT getLimitText(const int iCol) const;
    virtual bool setSubItem(const int, const int iSubItem, CString& csText);
    bool m_bNoEdit;

protected:
};
