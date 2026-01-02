#pragma once
#include <map>
#include <string>

enum Country
{
    AT, // Austria
    BA, // Bosnia
    BG, // Bulgaris
    CH, // Switzerland
    DE, // Germany
    FR, // France
    HR, // Croatia
    MK, // Macedonia
    PF, // Prewhole France
    RS  // Serbia
};

class CCountry
{
private:
    std::map<std::string, Country> _countries;
    Country _country;

public:
    CCountry();

    void SetCountry(std::string country);

    bool IsAT() const;
    bool IsBA() const;
    bool IsBG() const;
    bool IsCH() const;
    bool IsDE() const;
    bool IsFR() const;
    bool IsHR() const;
    bool IsMK() const;
    bool IsPF() const;
    bool IsRS() const;

private:
    void InitCountries();
};
