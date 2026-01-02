/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "RangeListCtrl.h"

#include <assert.h>

bool CRangeListCtrl::init()
{
    insertCol(RL_COL_KB,          CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE),  LVCFMT_LEFT,    30);
    insertCol(RL_COL_GRPNO,       CResString::ex().getStrTblText(AETXT_GRUPPE),         LVCFMT_RIGHT,   50);
    insertCol(RL_COL_GRPNAME,     CResString::ex().getStrTblText(AETXT_GRP_NAME),       LVCFMT_LEFT,   150);
    insertCol(RL_COL_ARTNO,       CResString::ex().getStrTblText(AETXT_ARTICLE_CODE),   LVCFMT_RIGHT,   80);
    insertCol(RL_COL_BASEQTY,     CResString::ex().getStrTblText(AETXT_MIN_QTY),        LVCFMT_RIGHT,   50);
    insertCol(RL_COL_QTY,         CResString::ex().getStrTblText(AETXT_MENGE),          LVCFMT_RIGHT,   50);
    insertCol(RL_COL_QTY_DIFF,    CResString::ex().getStrTblText(AETXT_DIFF),           LVCFMT_RIGHT,   50);
    insertCol(RL_COL_BASEVALUE,   CResString::ex().getStrTblText(AETXT_MIN_VALUE),      LVCFMT_RIGHT,   70);
    insertCol(RL_COL_VALUE,       CResString::ex().getStrTblText(AETXT_WERT),           LVCFMT_RIGHT,   70);
    insertCol(RL_COL_VALUE_DIFF,  CResString::ex().getStrTblText(AETXT_DIFF),           LVCFMT_RIGHT,   70);
    insertCol(RL_COL_DISCVALUE,   CResString::ex().getStrTblText(AETXT_RABATT),         LVCFMT_RIGHT,   70);
    insertCol(RL_COL_DISCQTY,     CResString::ex().getStrTblText(AETXT_RABATT_QTY),     LVCFMT_CENTER,  70);
    insertCol(RL_COL_DISCARTICLE, CResString::ex().getStrTblText(AETXT_RABATT_ARTIKEL), LVCFMT_RIGHT,   80);
    insertCol(RL_COL_DISCARTNAME, CResString::ex().getStrTblText(AETXT_ARTIKELNAME),    LVCFMT_LEFT,   180);

    return VListCtrl::init();
}

void CRangeListCtrl::refreshItem(const int)
{
}

bool CRangeListCtrl::isColNumber(const int) const
{
    return false;
}

bool CRangeListCtrl::isColEditable(const int) const
{
    return false;
}

UINT CRangeListCtrl::getLimitText(const int) const
{
    return 0;
}
