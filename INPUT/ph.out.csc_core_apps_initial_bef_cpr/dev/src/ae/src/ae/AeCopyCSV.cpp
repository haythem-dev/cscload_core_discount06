// AeFax.cpp : implementation file
//
#include "stdafx.h"
#include "AeCopyCSV.h"

extern "C"
{
    #include "allg.h"
}

CAeCopyCSV::CAeCopyCSV()
{
    m_Fehlertext = _T("");
}

int CAeCopyCSV::OpenLokalFile()
{
    CFileException e;
    if (!lokal.Open(m_CLokalFile, CFile::modeRead, &e))
    {
        TCHAR error[255];
        e.GetErrorMessage(error, 255);
        m_Fehlertext = error;
        return 1;
    }
    return 0;
}

void CAeCopyCSV::ReadLokalFile()
{
    CString Text;

    for (;;)
    {
        if (lokal.ReadString(Text) != NULL)
        {
            m_CZeilen.Add(Text);
        }
        else
            break;
    }
}

int CAeCopyCSV::CreateRemoteFileName()
{
    UUID uuid;
    if (UuidCreate(&uuid) == RPC_S_OK)
    {
        PUCHAR szUuid;
        CString Output;
        if (UuidToString(&uuid, &szUuid) == RPC_S_OK)
        {
            Output = szUuid;
            Output.MakeUpper();
            RpcStringFree(&szUuid);
            m_CRemoteFile.Format("CSV%s.csv", Output.GetString());
            return 0;
        }
    }
    return 1;
}

int CAeCopyCSV::OpenRemoteFile()
{
    CFileException e;
    CString OutputFileName;
    OutputFileName.Format("%s\\%s", m_RemoteAdresse, m_CRemoteFile.GetString());
    if (!remote.Open(OutputFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary, &e))
    {
        TCHAR error[255];
        e.GetErrorMessage(error, 255);
        m_Fehlertext = error;
        return 1;
    }
    return 0;
}

int CAeCopyCSV::ConnectSamba()
{
    DWORD dwResult;
    NETRESOURCE nr;
    int rc = 0;
    char Username[80];
    char Pwd[80];
    strcpy(m_RemoteAdresse, AeGetApp()->ImportAdresse());
    strcpy(Username, AeGetApp()->ImportUser());
    strcpy(Pwd, AeGetApp()->ImportPWD());
    nr.dwScope = 0;
    nr.dwType = RESOURCETYPE_ANY;
    nr.dwDisplayType = 0;
    nr.dwUsage = 0;
    nr.lpLocalName = NULL;
    nr.lpRemoteName = m_RemoteAdresse;
    nr.lpComment = NULL;
    nr.lpProvider = NULL;
    dwResult = WNetAddConnection2(&nr,  // NETRESOURCE from enumeration
        Pwd,                            // password
        Username,                       // logged-in user
        CONNECT_INTERACTIVE);           // reconnect next logon
    if (dwResult != NO_ERROR)
    {
        LPSTR lpMsgBuf;
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dwResult,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            (LPSTR)&lpMsgBuf,
            0,
            NULL);
        m_Fehlertext.Format("%s", (LPCTSTR)lpMsgBuf);
        LocalFree(lpMsgBuf);
        rc = dwResult;
        return rc;
    }
    return rc;
}

int CAeCopyCSV::WriteRemoteFile()   // Datei auf Server schreiben
{
    CString Ausgabe;
    for (int i = 0; i < m_CZeilen.GetCount(); i++)
    {
        Ausgabe = m_CZeilen.GetAt(i) + "\n";;
        remote.Write(Ausgabe, Ausgabe.GetLength());
    }
    remote.Close();
    return 0;
}

int CAeCopyCSV::DisconnectSamba()   // Verbindung trennen
{
    DWORD dwResult = WNetCancelConnection2(m_RemoteAdresse, 0, FALSE);      // NETRESOURCE from enumeration

    return dwResult;
}

CString CAeCopyCSV::PerformCopy(CString Input)  // Datei kopieren
{
    m_CLokalFile = Input;
    if (OpenLokalFile())
    {
        m_CRemoteFile.Empty();
        return m_CRemoteFile;
    }
    ReadLokalFile();
    lokal.Close();
    CreateRemoteFileName();
    if (ConnectSamba())
    {
        m_CRemoteFile.Empty();
        return m_CRemoteFile;
    }

    if (OpenRemoteFile())
    {
        m_CRemoteFile.Empty();
        return m_CRemoteFile;
    }
    if (WriteRemoteFile())
    {
        m_CRemoteFile.Empty();
        return m_CRemoteFile;
    }
    if (DisconnectSamba())
    {
        m_CRemoteFile.Empty();
        return m_CRemoteFile;
    }

    return m_CRemoteFile;
}
