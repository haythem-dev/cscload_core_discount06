#include "stdafx.h"
#include "yesnovalidator.h"


YesNoValidator::YesNoValidator()
{
}

YesNoValidator::~YesNoValidator()
{
}

bool YesNoValidator::isEntryValid(const CString& entry)
{
    CString Upper = entry;
    Upper.MakeUpper();

    if ((Upper == CResString::ex().getStrTblText(AETXT_KZ_JA).Left(1)) || (Upper == CResString::ex().getStrTblText(AETXT_KZ_NEIN).Left(1)))
        return true;
    return false;
}

void YesNoValidator::showPostValidationMessage()
{
    MessageWrongYesNo();
}

void YesNoValidator::MessageWrongYesNo()
{
    CString cst;
    cst.Format(CResString::ex().getStrTblText(AETXT_NUR_YES_NO), CResString::ex().getStrTblText(AETXT_KZ_JA).Left(1).GetString(), CResString::ex().getStrTblText(AETXT_KZ_NEIN).Left(1).GetString());
    AfxMessageBox(cst);
}
