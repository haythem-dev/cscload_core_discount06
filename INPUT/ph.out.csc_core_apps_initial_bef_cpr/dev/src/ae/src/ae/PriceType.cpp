#include "StdAfx.h"
#include "PriceType.h"

short CPriceType::CorrectPriceType3(const short sPriceType, const CString& strOpi, const CString& strEinzelhandel)
{
    if (sPriceType == 3)
    {
        return static_cast<short>(((strOpi == "1") || (strEinzelhandel == "1")) ? 0 : 2);
    }

    return sPriceType;
}
