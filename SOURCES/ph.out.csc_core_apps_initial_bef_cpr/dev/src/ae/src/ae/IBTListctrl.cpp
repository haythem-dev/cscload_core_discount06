/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "IBTListctrl.h"

#include <assert.h>


bool CIBTListCtrl::init()
{
    insertCol(COL_IBT_BRANCHNAME, CResString::ex().getStrTblText(AETXT_FILIALE),      LVCFMT_RIGHT, 100);
    insertCol(COL_IBT_BESTAND,    CResString::ex().getStrTblText(AETXT_BESTAND),      LVCFMT_RIGHT,  60);
    insertCol(COL_IBT_TYPE,       CResString::ex().getStrTblText(AETXT_IBT_TYPE),     LVCFMT_LEFT,   70);
    insertCol(COL_IBT_DATUM,      CResString::ex().getStrTblText(AETXT_DELIVERYDATE), LVCFMT_LEFT,   80);
    insertCol(COL_IBT_ZEIT,       CResString::ex().getStrTblText(AETXT_DELIVERYTIME), LVCFMT_RIGHT,  75);
    insertCol(COL_IBT_FILI,       CResString::ex().getStrTblText(AETXT_FILIALE),      LVCFMT_RIGHT,   0);

    return VListCtrl::init();
}

void CIBTListCtrl::refreshItem(const int /*iItem*/)
{
}

bool CIBTListCtrl::isColNumber(const int /*iCol*/) const
{
    return false;
}

bool CIBTListCtrl::isColEditable(const int /*iCol*/) const
{
    return false;
}

UINT CIBTListCtrl::getLimitText(const int /*iCol*/) const
{
    return 0;
}
