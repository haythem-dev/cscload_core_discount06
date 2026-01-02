#pragma once
//Klasse zum Faxen
#include "AeOutputs.h"

class CAeFax : public CAeOutputs
{
private:
    CString m_CFaxNr;               // Faxnummer
    CString m_CInfoText;            // Infotext für Commandzeile
    CString m_CCommandLine;         // Kommandozeile für Fax-Server
    CStringArray m_CArrayFreiText;  // zu faxende Textzeilen
    short m_sVzNr;                  // Filiale
    long m_lKundenNr;               // Kundennr
    CString m_CFaxName;             // evtl. Name des Ursprungmoduls

public:
    CAeFax();   // standard constructor
    virtual void AddZeile(CString& s);
    void SetFaxNr (CString CFaxNr);
    void SetFaxName (CString CFaxName);
    void SetVzNr (short sVzNr);
    void SetKundenNr (long lKundenNr);
    int  AddInfoText (CString CText);
    void AddFreiText (CString CText);
    int  Fax(); // Daten an Server zum Faxen übergeben
    CString m_Fehlertext;
    CString m_Apo;
    CString m_PLZ;
    CString m_Ort;
    CString m_Strasse;

};
