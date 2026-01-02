#pragma once
//BasisKlasse für Ausgaben auf Fax und Drucker

class CAeOutputs
{
public:
    virtual void AddZeile(CString&) = 0;
};
