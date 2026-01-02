#include "stdafx.h"
#include <libsccdate.h>
#include "datevalidator.h"


DateValidator::DateValidator()
{
}

DateValidator::~DateValidator()
{
}

bool DateValidator::isEntryValid(const CString& entry)
{
    CString csTT = entry.Left(2);
    CString csMM = entry.Mid(3, 2);
    CString csJJJJ = entry.Right(4);

    int iTT = atoi(csTT);
    int iMM = atoi(csMM);
    int iJJJJ = atoi(csJJJJ);

    //logic:
    //entered dates are valid if
    //1) entry is a valid date
    //2) date is today or further in the future
    //3) date is no further in the future than end of next year
    //example: entry is "23.09.2014", this is valid from 01.01.2013 up to 23.09.2014

    if (0 != SCCdtCheckDate(iTT, iMM, iJJJJ))
    {
        //no valid date entered
        return false;
    }
    else
    {
        long enteredDate = SCCdtDate(iTT, iMM, iJJJJ);

        struct tm now;

        SCCdtGetTM( &now );

        int nextYear = 1900 + now.tm_year + 1;

        if (enteredDate < SCCdtGetDate())
        {
            //entered date is in the past
            return false;
        }
        else if (enteredDate > SCCdtDate(31, 12, nextYear))
        {
            //entered date is more than end of next year in the future
            return false;
        }
    }

    return true;
}

void DateValidator::showPostValidationMessage()
{
    MessageWrongDate();
}

void DateValidator::MessageWrongDate()
{
    AfxMessageBox(IDS_TXT_FEHL_DATUM);
}
