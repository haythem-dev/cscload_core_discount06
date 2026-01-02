#pragma once


// CDAeCSVImportLog dialog

class CDAeCSVImportLog : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDAeCSVImportLog)

public:
    CDAeCSVImportLog(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDAeCSVImportLog();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_SHOW_IMPORT_LOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    DECLARE_MESSAGE_MAP()

public:
    CString m_CLog;
    CString m_Fehlertext;
    virtual BOOL OnInitDialog();
    CString m_CLogFile;     // Name des Log Files
    int OpenLogFile();      // Log Datei öffnen
    void ReadLogFile();     // Log Datei lesen
    CStdioFile logfile;
};
