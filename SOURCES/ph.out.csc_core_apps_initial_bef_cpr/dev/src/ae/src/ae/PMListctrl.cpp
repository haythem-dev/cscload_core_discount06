/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "PMListctrl.h"

#include <assert.h>


bool CPMListCtrl::init()
{
    insertCol(PROMO_LC_COL_NAME,        CResString::ex().getStrTblText(AETXT_ARTIKELNAME), LVCFMT_LEFT,  200);
    insertCol(PROMO_LC_COL_RABATT,      CResString::ex().getStrTblText(AETXT_RABATT),      LVCFMT_RIGHT,  50);
    insertCol(PROMO_LC_COL_WERT_NETTO,  CResString::ex().getStrTblText(AETXT_WERT_NETTO),  LVCFMT_RIGHT,  50);
    insertCol(PROMO_LC_COL_MIN,         CResString::ex().getStrTblText(AETXT_MIN),         LVCFMT_RIGHT,  50);
    insertCol(PROMO_LC_COL_NR,          CResString::ex().getStrTblText(AETXT_NATRA),       LVCFMT_RIGHT,  50);
    insertCol(PROMO_LC_COL_MAX,         CResString::ex().getStrTblText(AETXT_MAX),         LVCFMT_RIGHT,  50);
    insertCol(PROMO_LC_COL_VERFALL,     CResString::ex().getStrTblText(AETXT_VERFALL),     LVCFMT_RIGHT,  60);
    insertCol(PROMO_LC_COL_BESTAND,     CResString::ex().getStrTblText(AETXT_BESTAND),     LVCFMT_RIGHT,  60);
    insertCol(PROMO_LC_COL_MENGE,       CResString::ex().getStrTblText(AETXT_MENGE),       LVCFMT_RIGHT,  50);
    insertCol(PROMO_LC_COL_WERT_BRUTTO, CResString::ex().getStrTblText(AETXT_WERT_BRUTTO), LVCFMT_RIGHT,  50);
    insertCol(PROMO_LC_COL_WERT,        CResString::ex().getStrTblText(AETXT_WERT),        LVCFMT_RIGHT,  60);
    insertCol(PROMO_LC_COL_PZN,         " ",                                               LVCFMT_RIGHT,   0);
    insertCol(PROMO_LC_COL_PROPORT,     " ",                                               LVCFMT_RIGHT,   0);
    insertCol(PROMO_LC_COL_MIN_SOLO,    " ",                                               LVCFMT_RIGHT,   0);
    insertCol(PROMO_LC_COL_MAX_SOLO,    " ",                                               LVCFMT_RIGHT,   0);
    insertCol(PROMO_LC_COL_NR_SOLO,     " ",                                               LVCFMT_RIGHT,   0);
    insertCol(PROMO_LC_COL_AEP,         CResString::ex().getStrTblText(AETXT_AEP),         LVCFMT_RIGHT,   0);
    insertCol(PROMO_LC_COL_TAX,         CResString::ex().getStrTblText(AETXT_WERT_TAX),    LVCFMT_RIGHT,   0);

    return VListCtrl::init();
}

void CPMListCtrl::refreshItem(const int /*iItem*/)
{
}

bool CPMListCtrl::isColNumber(const int iCol) const
{
    switch (iCol)
    {
    case PROMO_LC_COL_MENGE:
        return true;

    default:
        return false;
    }
}

bool CPMListCtrl::isColEditable(const int iCol) const
{
    if (iCol == 0)          // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return false;       // dies wird durch ListCtrl selbst unterstützt

    switch (iCol)
    {
    case PROMO_LC_COL_MENGE:
        return true;

    default:
        return false;
    }
}

UINT CPMListCtrl::getLimitText(const int iCol) const
{
    switch (iCol)
    {
    case PROMO_LC_COL_MENGE:
        return 5;

    default:
        return 0;
    }
}

bool CPMListCtrl::setSubItem(const int /*iItem*/, const int /*iSubItem*/, CString& csText)
{
    csText.MakeUpper();

    return true;
}

BOOL CPMListCtrl::PreTranslateMessage(MSG* pMsg)
{

    switch (pMsg->wParam)
    {
    case VK_RETURN:
        this->SetFocus();
        ::PostMessage(AeGetApp()->PromoWnd(), WM_COMMAND, IDOK, 0);
        return TRUE;

    default:
        break;
    }

    return VListCtrl::PreTranslateMessage(pMsg);
}
