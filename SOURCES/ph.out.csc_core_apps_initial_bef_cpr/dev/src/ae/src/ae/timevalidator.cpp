#include "stdafx.h"
#include "timevalidator.h"

TimeValidator::TimeValidator()
{
}

TimeValidator::~TimeValidator()
{
}

bool TimeValidator::isEntryValid(const CString& entry)
{
    CString csHH = entry.Left(2);
    CString csMM = entry.Right(2);
    int iHH = atol(csHH);
    if (iHH < 0 || iHH > 24)
    {
        return false;
    }
    int iMM = atol(csMM);
    if (iMM < 0 || iMM > 59)
    {
        return false;
    }
    return true;
}

void TimeValidator::showPostValidationMessage()
{
    AfxMessageBox(IDS_TXT_FEHL_ZEIT);
}
