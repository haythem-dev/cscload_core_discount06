#pragma once
//Klasse zum Kopieren CSVImportFile

class CAeCopyCSV
{
public:
    CAeCopyCSV();                   // standard constructor
    CString m_CLokalFile;           // Lokales File
    CString m_CRemoteFile;          // Zu erstellendes File
    CString m_Fehlertext;           // Fehlermeldung
    CStringArray m_CZeilen;         // Zeilen
    int OpenLokalFile();
    int CreateRemoteFileName();
    int ConnectSamba();             // Verbinden auf Samba-share
    int DisconnectSamba();          // Verbindung auf Samba-share trennen
    int OpenRemoteFile();           // Remote Datei öffnen
    void ReadLokalFile();           // Lokale Datei lesen
    int  WriteRemoteFile();         // Datei auf Server schreiben
    CStdioFile lokal;
    CStdioFile remote;
    char m_RemoteAdresse[80];       // Adresse des Samba-share
    CString PerformCopy(CString Input);// Datei kopieren
};
