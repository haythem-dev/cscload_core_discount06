/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "VacationListctrl.h"

#include <libscgm_iformatterptr.h>
#include <libscgm_ivalidatorptr.h>
#include "dateformatter.h"
#include "datevalidator.h"
#include <assert.h>


bool CVacationListCtrl::init()
{
    using scgui::IFormatterPtr;
    using scgui::IValidatorPtr;

    insertCol(COL_VA_KB, CResString::ex().getStrTblText(AETXT_KB), LVCFMT_LEFT, 30);
    insertCol(COL_VA_VON, CResString::ex().getStrTblText(AETXT_VON), LVCFMT_RIGHT, 80);
    insertCol(COL_VA_BIS, CResString::ex().getStrTblText(AETXT_BIS), LVCFMT_RIGHT, 80);

    IFormatterPtr dateFormatter = IFormatterPtr(new DateFormatter());
    IValidatorPtr dateValidator = IValidatorPtr(new DateValidator());

    this->addFormatterToColumn(COL_VA_VON, dateFormatter);
    this->addFormatterToColumn(COL_VA_BIS, dateFormatter);
    this->addValidatorToColumn(COL_VA_VON, dateValidator);
    this->addValidatorToColumn(COL_VA_BIS, dateValidator);

    this->setBehaviourOnReturnKey(scgui::NEXT_EDITABLE_IN_ROW);

    this->setFirstLineName(AeGetApp()->Letter_A());
    this->setLastLineName(AeGetApp()->Letter_Z());

    return (VListCtrlEx::init());
}

void CVacationListCtrl::refreshItem(const int)
{
}

bool CVacationListCtrl::isColNumber(const int iCol) const
{
    switch (iCol)
    {
    case COL_VA_VON:
        return true;

    case COL_VA_BIS:
        return true;

    default:
        return false;
    }
}

bool CVacationListCtrl::isColEditable(const int iCol) const
{
    if (iCol == 0)          // erste Spalte kann nicht durch EditSubLabel editiert werden;
    {
        return false;    // dies wird durch ListCtrl selbst unterstützt
    }

    switch (iCol)
    {
    case COL_VA_VON:
        return true;

    case COL_VA_BIS:
        return true;

    default:
        return false;
    }
}

UINT CVacationListCtrl::getLimitText(const int iCol) const
{
    switch (iCol)
    {
    case COL_VA_VON:
        return 10;

    case COL_VA_BIS:
        return 10;

    default:
        return 0;
    }
}

bool CVacationListCtrl::setSubItem(const int, const int, CString&)
{
    return true;
}
