// AeFax.cpp : implementation file
//
#include "stdafx.h"
#include "AeFax.h"

extern "C"
{
    #include "allg.h"
}

// #define FAXADRESSE "\\\\nu1f0001\\dgspool$" jetzt über Parametertabelle

CAeFax::CAeFax()
{
    m_CFaxNr.Empty();
    m_sVzNr = AeGetApp()->VzNr();
    m_lKundenNr = 0;
    m_CFaxName = "Fax";
    m_Fehlertext = _T("");
}

void CAeFax::SetFaxNr (CString CFaxNr)
{
    if (AeGetApp()->FaxLand().IsEmpty())
    {
        m_CFaxNr=CFaxNr;
    }
    else
    {
        m_CFaxNr.Format("%s%s", AeGetApp()->FaxLand().GetString(), CFaxNr.Right(CFaxNr.GetLength()-1).GetString());
    }
}

void CAeFax::SetFaxName (CString CFaxName)
{
    // max. 3 Zeichen fuer Dateinamen frei
    m_CFaxName = (CFaxName.GetLength() > 3) ? CFaxName.Left(3) : CFaxName;
}

void CAeFax::SetVzNr (short sVzNr)
{
    m_sVzNr=sVzNr;
}

void CAeFax::SetKundenNr (long lKundenNr)
{
    m_lKundenNr=lKundenNr;
}

int CAeFax::AddInfoText (CString CText)
{
    int len = m_CInfoText.GetLength() + CText.GetLength();
    if (len > 62)
    {
        return len;
    }
    else
        m_CInfoText += CText;
    return 0;
}

void CAeFax::AddFreiText (CString CText)
{
    m_CArrayFreiText.Add(CText);
}

int CAeFax::Fax()   // Daten an Server zum Faxen übergeben
{
    if (m_CFaxNr.IsEmpty())
        return FALSE;
    if (AeGetApp()->FaxAdresse().IsEmpty())
        return FALSE;
    CString CLogo = (m_sVzNr == 21) ? "hsksc" : "phoenixgrksc";

    long datum = AllgGetDate();
    long uhrzeit = AllgGetTime();
    char filename[81];
    sprintf(filename,"%02d.%s.fax.%08d.%06d00.txt",
        AeGetApp()->VzNr(),
        m_CFaxName.GetString(),
        datum,
        uhrzeit);
        m_CCommandLine.Format("##TO:%s! ##PRIORITY:%01d! ##ORG:administrator! ##REF:"\
        "KSC! ##REFX:%02d%14ld! ##REFL:%.62s! "\
        "##SUBJ:%.32s! ##FAIL:administrator! ##CLOGO:%.20s! "\
        "##LPI:6! ##CPI:11! ##SKIP:15!\r\n"
        , m_CFaxNr.GetString()
        , 3
        , m_sVzNr
        , m_lKundenNr
        , m_CInfoText.GetString()
        , filename
        , CLogo.GetString()
        );
    char filenamefax[81];
    sprintf(filenamefax,"%s\\%02d.%s.fax.%08d.%06d00.txt",
        AeGetApp()->FaxAdresse().GetString(),
        AeGetApp()->VzNr(),
        m_CFaxName.GetString(),
        datum,
        uhrzeit);
    char filenameflg[81];
    sprintf(filenameflg,"%s\\%02d.%s.flg.%08d.%06d00",
        AeGetApp()->FaxAdresse().GetString(),
        AeGetApp()->VzNr(),
        m_CFaxName.GetString(),
        datum,
        uhrzeit);

    char Faxname[80];
    if (AeGetApp()->IsNewFax())
    {
        strcpy(Faxname, AeGetApp()->FaxAdresse());
        char Username[80];
        strcpy(Username, AeGetApp()->FaxUser());
        char Pwd[80];
        strcpy(Pwd, AeGetApp()->FaxPWD());
        NETRESOURCE nr;
        nr.dwScope = 0;
        nr.dwType = RESOURCETYPE_ANY;
        nr.dwDisplayType = 0;
        nr.dwUsage = 0;
        nr.lpLocalName = NULL;
        nr.lpRemoteName = Faxname;
        nr.lpComment = NULL;
        nr.lpProvider = NULL;
        DWORD dwResult = WNetAddConnection2(&nr,    // NETRESOURCE from enumeration
            Pwd,                                    // password
            Username,                               // logged-in user
            CONNECT_INTERACTIVE);                   // reconnect next logon
        if (dwResult != NO_ERROR)
        {
            LPSTR lpMsgBuf;
            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                dwResult,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPSTR)&lpMsgBuf,
                0,
                NULL );
            m_Fehlertext.Format("%s", (LPCTSTR)lpMsgBuf);
            LocalFree(lpMsgBuf);
            return dwResult;
        }
    }
    CFile fax;
    CFileException e;
    if (!fax.Open(filenamefax, CFile::modeCreate | CFile::modeWrite, &e))
    {
        return e.m_cause;
    }

    fax.Write(m_CCommandLine,m_CCommandLine.GetLength());

    CString CAusgabe;
    if (m_sVzNr == 21)
    {
        CAusgabe.Format("                                                             %s\r\n",
            CResString::ex().getStrTblText(AETXT_HAGEDA).GetString());
        fax.Write(CAusgabe, CAusgabe.GetLength());
    }
    else
    {
        CAusgabe.Format("                                                             %s\r\n",
            CResString::ex().getStrTblText(AETXT_PHOENIX).GetString());
        fax.Write(CAusgabe, CAusgabe.GetLength());
        CAusgabe.Format("                                                             %s\r\n",
            CResString::ex().getStrTblText(AETXT_AKTIE).GetString());
        fax.Write(CAusgabe, CAusgabe.GetLength());
    }
    CAusgabe.Format("%30.30s                               %s\r\n",
        m_Apo.GetString(),
        AeGetApp()->Region().GetString());
    fax.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe.Format("%30.30s\r\n",
        m_Strasse.GetString());
    fax.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe.Format("\r\n%5.5s %30.30s                         %s\r\n",
        m_PLZ.GetString(),
        m_Ort.GetString(),
        AeGetApp()->VzStrasse().GetString());
    fax.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe.Format("                                                             %s %s\r\n",
        AeGetApp()->VzPLZ().Trim().GetString(),
        AeGetApp()->VzOrt().GetString());
    fax.Write(CAusgabe, CAusgabe.GetLength());
    if (AeGetApp()->VzTelnr().GetAt(0) == '0')
    {
        CAusgabe.Format("                                                             %s %s\r\n",
            CResString::ex().getStrTblText(AETXT_TELEFON).GetString(),
            AeGetApp()->VzTelnr().GetString());
    }
    else
    {
        CAusgabe.Format("                                                             %s %s %s\r\n",
            CResString::ex().getStrTblText(AETXT_TELEFON).GetString(),
            AeGetApp()->Vorwahl().GetString(),
            AeGetApp()->VzTelnr().GetString());
    }
    fax.Write(CAusgabe, CAusgabe.GetLength());
    if (AeGetApp()->VzFaxnr().GetAt(0) == '0')
    {
        CAusgabe.Format("                                                             %s %s\r\n",
            CResString::ex().getStrTblText(AETXT_FAX).GetString(),
            AeGetApp()->VzFaxnr().GetString());
    }
    else
    {
        CAusgabe.Format("                                                             %s %s %s\r\n",
            CResString::ex().getStrTblText(AETXT_FAX).GetString(),
            AeGetApp()->Vorwahl().GetString(),
            AeGetApp()->VzFaxnr().GetString());
    }
    fax.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe = "\r\n";
    fax.Write(CAusgabe, CAusgabe.GetLength());
    for (int i = 0; i < m_CArrayFreiText.GetCount(); i++)
    {
        CAusgabe = m_CArrayFreiText.GetAt(i) + "\r\n";
        fax.Write(CAusgabe, CAusgabe.GetLength());
    }
    fax.Write("##PAGE!\r\n", 9);
    fax.Close();

    if (AeGetApp()->IsNewFax())
    {
        CFile flg;
        if (!flg.Open(filenameflg, CFile::modeCreate | CFile::modeWrite, &e))
        {
            return e.m_cause;
        }
        flg.Close();
        DWORD dwResult;
        dwResult = WNetCancelConnection2(Faxname, 0, FALSE);    // NETRESOURCE from enumeration
    }

    return 0;
}

void CAeFax::AddZeile (CString &CText)
{
    AddFreiText(CText);
}
