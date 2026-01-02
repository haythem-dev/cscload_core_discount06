#pragma once

class CCountry;

class CDAufDefImpl
{
private:
    const CCountry& _country;

public:
    CDAufDefImpl(const CCountry& country);

    bool RemoveBGOrderTypes(CString currentOrdertype, CString ordertype);
    bool RemoveBGAndRSOrderTypes(CString currentOrdertype, CString ordertype);

private:
    bool RemoveOrderType(CString currentOrdertype, CString ordertype, CString testtype);
};
