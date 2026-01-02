#include "stdafx.h"
#include "yesnoformatter.h"


YesNoFormatter::YesNoFormatter()
{
}

YesNoFormatter::~YesNoFormatter()
{
}

CString YesNoFormatter::format(const CString& entry)
{
    CString cs(entry);
    cs.MakeUpper();
    return cs;
}
