/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "TListctrl.h"
#include <assert.h>

bool CTListCtrl::init()
{
    insertCol(TENDER_LC_COL_KB,          CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE), LVCFMT_LEFT,   20);
    insertCol(TENDER_LC_COL_BESTAND,     CResString::ex().getStrTblText(AETXT_KURZ_BESTAND),  LVCFMT_RIGHT,  50);
    insertCol(TENDER_LC_COL_GELIEFERT,   CResString::ex().getStrTblText(AETXT_GELIEFERT),     LVCFMT_RIGHT,  55);
    insertCol(TENDER_LC_COL_VEREINBART,  CResString::ex().getStrTblText(AETXT_VEREINBART),    LVCFMT_RIGHT,  60);
    insertCol(TENDER_LC_COL_PZN,         CResString::ex().getStrTblText(AETXT_PZN),           LVCFMT_RIGHT,  50);
    insertCol(TENDER_LC_COL_EINHEIT,     CResString::ex().getStrTblText(AETXT_EINHEIT),       LVCFMT_RIGHT,  65);
    insertCol(TENDER_LC_COL_ARTIKELNAME, CResString::ex().getStrTblText(AETXT_ARTIKELNAME),   LVCFMT_RIGHT, 200);
    insertCol(TENDER_LC_COL_PREIS,       CResString::ex().getStrTblText(AETXT_PREIS),         LVCFMT_RIGHT,  70);
    insertCol(TENDER_LC_COL_RABATT,      CResString::ex().getStrTblText(AETXT_RABATT),        LVCFMT_RIGHT,  50);
    insertCol(TENDER_LC_COL_VERFALL,     CResString::ex().getStrTblText(AETXT_VERFALLDATUM),  LVCFMT_RIGHT,  80);
    insertCol(TENDER_LC_COL_TAXLEVEL,    "",                                                  LVCFMT_RIGHT,   0);
    insertCol(TENDER_LC_COL_AEP,         CResString::ex().getStrTblText(AETXT_AEP),           LVCFMT_RIGHT,  70);
    insertCol(TENDER_LC_COL_SPANNE,      CResString::ex().getStrTblText(AETXT_SPANNE),        LVCFMT_RIGHT,  70);
    insertCol(TENDER_LC_COL_GROSSO,      CResString::ex().getStrTblText(AETXT_GROSSO),        LVCFMT_RIGHT,   0);

    return VListCtrl::init();
}

void CTListCtrl::refreshItem(const int)
{
}

bool CTListCtrl::isColNumber(const int) const
{
    return false;
}

bool CTListCtrl::isColEditable(const int) const
{
    return false;
}

UINT CTListCtrl::getLimitText(const int) const
{
    return 0;
}
