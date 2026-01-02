#include "stdafx.h"
#include "dateformatter.h"


DateFormatter::DateFormatter()
{
}

DateFormatter::~DateFormatter()
{
}

CString DateFormatter::format(const CString& entry)
{
    CString cs(entry);

    if (entry.GetLength() == 2)
    {
        cs += '.';
    }
    else if (3 == entry.GetLength())
    {
        //check if . is present
        if (-1 == entry.Find('.'))
        {
            //if not, insert it
            cs.Insert(2, '.');
        }
    }
    else if (entry.GetLength() == 5)
    {
        cs += '.';
    }
    else if (6 == entry.GetLength())
    {
        //check if . is present, assume the first 3 chars <XX.> are ok
        if (-1 == entry.Find('.', 3))
        {
            //if not, insert it
            cs.Insert(5, '.');
        }
    }

    return cs;
}
