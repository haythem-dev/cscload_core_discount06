/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "ServiceListctrl.h"

#include <libscgm_iformatterptr.h>
#include <libscgm_iformatter.h>
#include "dateformatter.h"
#include "timeformatter.h"
#include "yesnoformatter.h"

#include <libscgm_ivalidatorptr.h>
#include <libscgm_ivalidator.h>
#include "datevalidator.h"
#include "timevalidator.h"
#include "yesnovalidator.h"

#include <assert.h>


bool CServiceListCtrl::init()
{
    using scgui::IFormatter;
    using scgui::IFormatterPtr;
    using scgui::IValidator;
    using scgui::IValidatorPtr;

    insertCol(COL_SP_KB,     CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE), LVCFMT_LEFT,  30);
    insertCol(COL_SP_DATUM,  CResString::ex().getStrTblText(AETXT_DATUM),         LVCFMT_LEFT,  80);
    insertCol(COL_SP_VON,    CResString::ex().getStrTblText(AETXT_VON),           LVCFMT_LEFT,  50);
    insertCol(COL_SP_BIS,    CResString::ex().getStrTblText(AETXT_BIS),           LVCFMT_LEFT,  50);
    insertCol(COL_SP_BTM,    CResString::ex().getStrTblText(AETXT_BTM),           LVCFMT_LEFT,  50);
    insertCol(COL_SP_KK,     CResString::ex().getStrTblText(AETXT_KK),            LVCFMT_LEFT,  50);
    insertCol(COL_SP_K08,    CResString::ex().getStrTblText(AETXT_K08),           LVCFMT_LEFT,  50);
    insertCol(COL_SP_K20,    CResString::ex().getStrTblText(AETXT_K20),           LVCFMT_LEFT,  50);
    insertCol(COL_SP_BEMERK, CResString::ex().getStrTblText(IDS_BEMERK),          LVCFMT_LEFT, 200);

    IFormatterPtr dateFormatter = IFormatterPtr(new DateFormatter());
    IFormatterPtr timeFormatter = IFormatterPtr(new TimeFormatter());
    IFormatterPtr yesnoFormatter = IFormatterPtr(new YesNoFormatter());

    IValidatorPtr dateValidator = IValidatorPtr(new DateValidator());
    IValidatorPtr timeValidator = IValidatorPtr(new TimeValidator());
    IValidatorPtr yesnoValidator = IValidatorPtr(new YesNoValidator());


    this->addFormatterToColumn(COL_SP_DATUM, dateFormatter);
    this->addFormatterToColumn(COL_SP_VON, timeFormatter);
    this->addFormatterToColumn(COL_SP_BIS, timeFormatter);
    this->addFormatterToColumn(COL_SP_BTM, yesnoFormatter);
    this->addFormatterToColumn(COL_SP_KK, yesnoFormatter);
    this->addFormatterToColumn(COL_SP_K08, yesnoFormatter);
    this->addFormatterToColumn(COL_SP_K20, yesnoFormatter);

    this->addValidatorToColumn(COL_SP_DATUM, dateValidator);
    this->addValidatorToColumn(COL_SP_VON, timeValidator);
    this->addValidatorToColumn(COL_SP_BIS, timeValidator);
    this->addValidatorToColumn(COL_SP_BTM, yesnoValidator);
    this->addValidatorToColumn(COL_SP_KK, yesnoValidator);
    this->addValidatorToColumn(COL_SP_K08, yesnoValidator);
    this->addValidatorToColumn(COL_SP_K20, yesnoValidator);

    this->setBehaviourOnReturnKey(scgui::NEXT_EDITABLE_IN_ROW);

    this->setFirstLineName(AeGetApp()->Letter_A());
    this->setLastLineName(AeGetApp()->Letter_Z());

    return VListCtrlEx::init();
}

void CServiceListCtrl::refreshItem(const int)
{
}

bool CServiceListCtrl::isColNumber(const int iCol) const
{
    switch (iCol)
    {
        case COL_SP_DATUM:
            return true;
        case COL_SP_VON:
            return true;
        case COL_SP_BIS:
            return true;
        case COL_SP_BTM:
            return false;
        case COL_SP_KK:
            return false;
        case COL_SP_K08:
            return false;
        case COL_SP_K20:
            return false;
        case COL_SP_BEMERK:
            return false;

        default:
            return false;
    }
}

bool CServiceListCtrl::isColEditable(const int iCol) const
{
    if (iCol == 0)      // erste Spalte kann nicht durch EditSubLabel editiert werden;
        return false;   // dies wird durch ListCtrl selbst unterstützt

    switch (iCol)
    {
        case COL_SP_DATUM:
            return true;
        case COL_SP_VON:
            return true;
        case COL_SP_BIS:
            return true;
        case COL_SP_BTM:
            return true;
        case COL_SP_KK:
            return true;
        case COL_SP_K08:
            return true;
        case COL_SP_K20:
            return true;
        case COL_SP_BEMERK:
            return true;

        default:
            return false;
    }
}

UINT CServiceListCtrl::getLimitText(const int iCol) const
{
    switch (iCol)
    {
        case COL_SP_DATUM:
            return 10;
        case COL_SP_VON:
            return 5;
        case COL_SP_BIS:
            return 5;
        case COL_SP_BTM:
            return 1;
        case COL_SP_KK:
            return 1;
        case COL_SP_K08:
            return 1;
        case COL_SP_K20:
            return 1;
        case COL_SP_BEMERK:
            return 200;

    default:
        return 0;
    }
}

bool CServiceListCtrl::setSubItem(const int, const int, CString&)
{
    return true;
}
