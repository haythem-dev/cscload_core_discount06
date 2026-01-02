#pragma once


// CDAeCSVImport dialog
//#define LOCAL_WINDEBUG 

class CDAeCSVImport : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDAeCSVImport)

public:
    CDAeCSVImport(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDAeCSVImport();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_CSV_IMPORT };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

public:
    CComboBox m_combo_Format;
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    char Username[80];
    char Pwd[80];
    CString m_RemoteAdresse;
    CString m_CUsername;
    CString m_CPwd;
    CString m_CServer;
    CString m_CDateiName;
    CEdit m_editDateiName;
    CString m_CRemoteFile;
    CString m_CRemoteReportCSVFile;
#ifdef LOCAL_WINDEBUG
    CString m_CRemoteLocalDebugFile;
    CString m_CRemoteLocalDebugReportFile;
#endif
    CString m_CFehlerText;
    CString m_CLogFile;
    CString m_CRemoteLogFile;
    CString m_CLokalPath;
    CString m_CLokalLogFile;
    bool CreateCompatibleFileEncoding(std::string inputEncoding, std::string outputEncoding);
    CString m_CLokalReportFile;
    int TransferFile();
    int TransferLogReportFiles();
    int CreateRemoteFileName();
    afx_msg void OnBnClickedButtonDateiAuswahl();
    afx_msg void OnEnChangeEditDateiName();
};
