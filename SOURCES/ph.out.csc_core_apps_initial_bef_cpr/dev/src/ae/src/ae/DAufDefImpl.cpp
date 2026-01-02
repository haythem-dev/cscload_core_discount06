#include "stdafx.h"
#include "DAufDefImpl.h"
#include "Country.h"

/////////////////////////////////////////////////////////////////////////////
// CDAufDef dialog


CDAufDefImpl::CDAufDefImpl(const CCountry& country)
    : _country(country)
{
}

// returns true if type is to be removed
bool CDAufDefImpl::RemoveBGOrderTypes(CString currentOrdertype, CString ordertype)
{
    if (!_country.IsBG())
    {
        return false;
    }

    if (currentOrdertype == "CO")
    {
        if (ordertype != "CO")
        {
            return true;
        }
    }
    else if (currentOrdertype == "NO")  //NO darf auch zu CO werden
    {
        if ((ordertype != "CO") && (ordertype != "NO"))
        {
            return true;
        }
    }
    if (   RemoveOrderType(currentOrdertype, ordertype, "MP")
        || RemoveOrderType(currentOrdertype, ordertype, "EH")
        || RemoveOrderType(currentOrdertype, ordertype, "RO")
        || RemoveOrderType(currentOrdertype, ordertype, "S1")
        || RemoveOrderType(currentOrdertype, ordertype, "S2")
        || RemoveOrderType(currentOrdertype, ordertype, "S3")
        || RemoveOrderType(currentOrdertype, ordertype, "S4")
        || RemoveOrderType(currentOrdertype, ordertype, "S5")
        || RemoveOrderType(currentOrdertype, ordertype, "S6") )
    {
        return true;
    }
    return false;
}

// returns true if type is to be removed
bool CDAufDefImpl::RemoveBGAndRSOrderTypes(CString currentOrdertype, CString ordertype)
{
    if (!_country.IsBG() && !_country.IsRS())
    {
        return false;
    }

    if (   RemoveOrderType(currentOrdertype, ordertype, "TO")
        || RemoveOrderType(currentOrdertype, ordertype, "TI") )
    {
        return true;
    }
    return false;
}

// returns true if type is to be removed
bool CDAufDefImpl::RemoveOrderType(CString currentOrdertype, CString ordertype, CString testtype)
{
    if (currentOrdertype == testtype)
    {
        if (ordertype != testtype)
        {
            return true;
        }
    }
    else
    {
        if (ordertype == testtype)
        {
            return true;
        }
    }
    return false;
}
