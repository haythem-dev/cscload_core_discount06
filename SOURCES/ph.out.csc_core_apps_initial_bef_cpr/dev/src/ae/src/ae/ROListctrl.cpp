/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "ROListctrl.h"

#include <assert.h>


bool CROListCtrl::init()
{
    insertCol(RO_LC_COL_BENUTZEN,     " ",                                           LVCFMT_LEFT,   40);
    insertCol(RO_LC_COL_PRIORITAET,   CResString::ex().getStrTblText(AETXT_PRIO),    LVCFMT_RIGHT,  30);
    insertCol(RO_LC_COL_RECHNR,       CResString::ex().getStrTblText(AETXT_RECHNR),  LVCFMT_RIGHT, 100);
    insertCol(RO_LC_COL_DATUM,        CResString::ex().getStrTblText(AETXT_DATUM),   LVCFMT_RIGHT,  70);
    insertCol(RO_LC_COL_RECH_TYP,     CResString::ex().getStrTblText(AETXT_TYP),     LVCFMT_RIGHT,  30);
    insertCol(RO_LC_COL_WERT,         CResString::ex().getStrTblText(AETXT_WERT),    LVCFMT_RIGHT,  70);
    insertCol(RO_LC_COL_BEZAHLT,      CResString::ex().getStrTblText(AETXT_BEZAHLT), LVCFMT_RIGHT,  70);
    insertCol(RO_LC_COL_RABATT,       CResString::ex().getStrTblText(AETXT_RABATT),  LVCFMT_RIGHT,  70);
    insertCol(RO_LC_COL_TAGE_ZAHLUNG, CResString::ex().getStrTblText(AETXT_ZAHLUNG), LVCFMT_RIGHT,  30);

    SetExtendedStyle(GetExtendedStyle() | LVS_EX_CHECKBOXES);   // checkboxes

    return VListCtrl::init();
}

void CROListCtrl::refreshItem(const int)
{
}

bool CROListCtrl::isColNumber(const int iCol) const
{
    switch (iCol)
    {
    case RO_LC_COL_PRIORITAET:
        return true;

    default:
        return false;
    }
}

bool CROListCtrl::isColEditable(const int iCol) const
{
    if (iCol == 0)          // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return false;       // dies wird durch ListCtrl selbst unterstützt

    switch (iCol)
    {
    case RO_LC_COL_PRIORITAET:
        return true;

    default:
        return false;
    }
}

UINT CROListCtrl::getLimitText(const int iCol) const
{
    switch (iCol)
    {
    case RO_LC_COL_PRIORITAET:
        return 1;

    default:
        return 0;
    }
}

bool CROListCtrl::setSubItem(const int, const int iSubItem, CString& csText)
{
    csText.MakeUpper();

    switch (iSubItem)
    {
    case RO_LC_COL_PRIORITAET:
        if (atoi(csText) > 1)
            csText = "1";
        break;

    default:
        assert(0);
    }

    return true;
}

/*----------------------------------------------------------------------------*/
void CROListCtrl::setEdit  (const int iItem, const int iSubItem)
{
    editSubItem(iItem, iSubItem);
}
