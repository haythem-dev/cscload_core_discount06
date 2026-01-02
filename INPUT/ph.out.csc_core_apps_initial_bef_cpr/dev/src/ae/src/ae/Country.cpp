#include "StdAfx.h"
#include "Country.h"

CCountry::CCountry()
    : _country(DE)
{
    InitCountries();
}

void CCountry::InitCountries()
{
    _countries.insert(std::pair<std::string, Country>("AT", AT));
    _countries.insert(std::pair<std::string, Country>("BA", BA));
    _countries.insert(std::pair<std::string, Country>("BG", BG));
    _countries.insert(std::pair<std::string, Country>("CH", CH));
    _countries.insert(std::pair<std::string, Country>("DE", DE));
    _countries.insert(std::pair<std::string, Country>("FR", FR));
    _countries.insert(std::pair<std::string, Country>("HR", HR));
    _countries.insert(std::pair<std::string, Country>("MK", MK));
    _countries.insert(std::pair<std::string, Country>("PF", PF));
    _countries.insert(std::pair<std::string, Country>("RS", RS));
}

void CCountry::SetCountry(std::string country)
{
    country.erase(country.find_last_not_of(" ") + 1);
    std::map<std::string, Country>::iterator iter = _countries.find(country);
    _country = (iter == _countries.end()) ? DE : iter->second; // DE: Fallback
}

bool CCountry::IsAT() const
{
    return _country == AT;
}

bool CCountry::IsBA() const
{
    return _country == BA;
}

bool CCountry::IsBG() const
{
    return _country == BG;
}

bool CCountry::IsCH() const
{
    return _country == CH;
}

bool CCountry::IsDE() const
{
    return _country == DE;
}

bool CCountry::IsFR() const
{
    return _country == FR;
}

bool CCountry::IsHR() const
{
    return _country == HR;
}

bool CCountry::IsMK() const
{
    return _country == MK;
}

bool CCountry::IsPF() const
{
    return _country == PF;
}

bool CCountry::IsRS() const
{
    return _country == RS;
}
