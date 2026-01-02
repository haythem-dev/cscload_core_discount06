/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "KCListctrl.h"

#include <assert.h>

bool CKCListCtrl::init()
{
    insertCol(KC_COL_CHECK,      CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE), LVCFMT_LEFT,   40);
    insertCol(KC_COL_AUF_NR,     CResString::ex().getStrTblText(AETXT_AUF_NR),        LVCFMT_RIGHT,  70);
    insertCol(KC_COL_KUNDE,      CResString::ex().getStrTblText(AETXT_APOTHEKENNAME), LVCFMT_LEFT,  200);
    insertCol(KC_COL_ARTIKEL,    CResString::ex().getStrTblText(AETXT_ARTIKELNAME),   LVCFMT_LEFT,  200);
    insertCol(KC_COL_BESTELLT,   CResString::ex().getStrTblText(AETXT_AMGE),          LVCFMT_RIGHT,  50);
    insertCol(KC_COL_BESTAETIGT, CResString::ex().getStrTblText(AETXT_BMGE),          LVCFMT_RIGHT,  50);
    insertCol(KC_COL_MENGE_ALT,  CResString::ex().getStrTblText(AETXT_MENGE_ALT_KZ),  LVCFMT_RIGHT,  70);
    insertCol(KC_COL_RECHNUNG,   CResString::ex().getStrTblText(AETXT_RECHNUNG_NR),   LVCFMT_LEFT,  100);
    insertCol(KC_COL_POSNR,      CResString::ex().getStrTblText(AETXT_PNR),           LVCFMT_LEFT,    0);

    SetExtendedStyle(GetExtendedStyle() | LVS_EX_CHECKBOXES);   // checkboxes

    return VListCtrl::init();
}

void CKCListCtrl::refreshItem(const int /*iItem*/)
{
}

bool CKCListCtrl::isColNumber(const int /*iCol*/) const
{
    return false;
}

bool CKCListCtrl::isColEditable(const int /*iCol*/) const
{
    return false;
}

UINT CKCListCtrl::getLimitText(const int /*iCol*/) const
{
    return 0;
}
