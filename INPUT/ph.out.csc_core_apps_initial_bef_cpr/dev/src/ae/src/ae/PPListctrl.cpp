/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "PPListctrl.h"
#include <assert.h>

/**---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*/
bool CPPListCtrl::init()
{
    insertCol(PROMO_PP_COL_PROMONR, CResString::ex().getStrTblText(AETXT_PROMO_NR),      LVCFMT_RIGHT,  65);
    insertCol(PROMO_PP_COL_NAME,    CResString::ex().getStrTblText(AETXT_ARTIKELNAME),   LVCFMT_LEFT,  200);
    insertCol(PROMO_PP_COL_AEP,     CResString::ex().getStrTblText(AETXT_WERT_BRUTTO),   LVCFMT_RIGHT,  60);
    insertCol(PROMO_PP_COL_RAB,     CResString::ex().getStrTblText(AETXT_RABATT),        LVCFMT_RIGHT,  60);
    insertCol(PROMO_PP_COL_RABWERT, CResString::ex().getStrTblText(AETXT_WERT_NETTO),    LVCFMT_RIGHT,  60);
    insertCol(PROMO_PP_COL_MAX,     CResString::ex().getStrTblText(AETXT_MAX),           LVCFMT_RIGHT,  60);
    insertCol(PROMO_PP_COL_BESTAND, CResString::ex().getStrTblText(AETXT_BESTAND),       LVCFMT_RIGHT,  50);
    insertCol(PROMO_PP_COL_MENGE,   CResString::ex().getStrTblText(AETXT_MENGE),         LVCFMT_RIGHT,  50);
    insertCol(PROMO_PP_COL_GEBUCHT, CResString::ex().getStrTblText(AETXT_MENGE_GEBUCHT), LVCFMT_RIGHT,  52);
    insertCol(PROMO_PP_COL_PZN,     CResString::ex().getStrTblText(AETXT_PZN),           LVCFMT_RIGHT,   0);
    insertCol(PROMO_PP_COL_ADDON,   " ",                                                 LVCFMT_RIGHT,   0);

    return (VListCtrl::init());
}

void CPPListCtrl::refreshItem(const int /*iItem*/)
{
}

bool CPPListCtrl::isColNumber(const int iCol) const
{
    return iCol == PROMO_PP_COL_MENGE ? true : false;
}

bool CPPListCtrl::isColEditable(const int iCol) const
{
    if (iCol == 0)          // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return false;       // dies wird durch ListCtrl selbst unterstützt

    return isColNumber(iCol);
}

UINT CPPListCtrl::getLimitText(const int iCol) const
{
    return iCol == PROMO_PP_COL_MENGE ? 5 : 0;
}

bool CPPListCtrl::setSubItem(const int /*iItem*/, const int iSubItem, CString& csText)
{
    if (iSubItem != PROMO_PP_COL_MENGE)
    {
        assert(0);
    }

    csText = csText.MakeUpper();

    return true;
}

BOOL CPPListCtrl::PreTranslateMessage(MSG* pMsg)
{
    switch (pMsg->wParam)
    {
    case VK_RETURN:
        if (this != GetFocus())
        {
            ::PostMessage(GetParent()->m_hWnd, WM_COMMAND, IDOK, 0);
            this->SetFocus();
            return TRUE;
        }
        break;
    default:
        break;
    }

    return VListCtrl::PreTranslateMessage(pMsg);
}
