/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "PRListctrl.h"

#include <assert.h>


bool CPRListCtrl::init()
{
    insertCol(PROMO_LR_COL_NAME,     CResString::ex().getStrTblText(AETXT_ARTIKELNAME), LVCFMT_LEFT,  200);
    insertCol(PROMO_LR_COL_MIN,      CResString::ex().getStrTblText(AETXT_MIN),         LVCFMT_RIGHT,  50);
    insertCol(PROMO_LR_COL_MAX,      CResString::ex().getStrTblText(AETXT_MAX),         LVCFMT_RIGHT,  50);
    insertCol(PROMO_LR_COL_BESTAND,  CResString::ex().getStrTblText(AETXT_BESTAND),     LVCFMT_RIGHT,  60);
    insertCol(PROMO_LR_COL_MENGE,    CResString::ex().getStrTblText(AETXT_MENGE),       LVCFMT_RIGHT,  50);
    insertCol(PROMO_LR_COL_PZN,      "",                                                LVCFMT_LEFT,    0);
    insertCol(PROMO_LR_COL_MAX_SOLO, "",                                                LVCFMT_LEFT,    0);
    insertCol(PROMO_LR_COL_MIN_SOLO, "",                                                LVCFMT_LEFT,    0);

    return VListCtrl::init();
}

void CPRListCtrl::refreshItem(const int)
{
}

bool CPRListCtrl::isColNumber(const int iCol) const
{
    switch (iCol)
    {
    case PROMO_LR_COL_MENGE:
        return true;

    default:
        return false;
    }
}

bool CPRListCtrl::isColEditable(const int iCol) const
{
    if (iCol == 0)          // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return false;       // dies wird durch ListCtrl selbst unterstützt

    if (m_bNoEdit)          // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return false;       // dies wird durch ListCtrl selbst unterstützt

    switch (iCol)
    {
    case PROMO_LR_COL_MENGE:
        return true;

    default:
        return false;
    }
}

UINT CPRListCtrl::getLimitText(const int iCol) const
{
    switch (iCol)
    {
    case PROMO_LR_COL_MENGE:
        return 5;

    default:
        return 0;
    }
}

bool CPRListCtrl::setSubItem(const int, const int /*iSubItem*/, CString& csText)
{
    csText.MakeUpper();

    return true;
}
