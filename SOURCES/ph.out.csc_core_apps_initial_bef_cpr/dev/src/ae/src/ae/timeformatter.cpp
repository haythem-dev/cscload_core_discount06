#include "stdafx.h"
#include "timeformatter.h"

TimeFormatter::TimeFormatter()
{
}

TimeFormatter::~TimeFormatter()
{
}

CString TimeFormatter::format(const CString& entry)
{
    CString cs(entry);

    if (entry.GetLength() == 2)
    {
        cs += ':';
    }
    else if (3 == entry.GetLength())
    {
        if (-1 == entry.Find(':'))
        {
            cs.Insert(2, ':');
        }
    }

    return cs;
}
