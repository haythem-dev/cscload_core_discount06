// DAeCSVImportLog.cpp : implementation file
//

#include "stdafx.h"
#include "DAeCSVImportLog.h"


// CDAeCSVImportLog dialog

IMPLEMENT_DYNAMIC(CDAeCSVImportLog, CDialogEx)

CDAeCSVImportLog::CDAeCSVImportLog(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(IDD_AE_SHOW_IMPORT_LOG, pParent)
    , m_CLog(_T(""))
{
}

CDAeCSVImportLog::~CDAeCSVImportLog()
{
}

void CDAeCSVImportLog::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_LOG, m_CLog);
}


BEGIN_MESSAGE_MAP(CDAeCSVImportLog, CDialogMultiLang)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDAeCSVImportLog message handlers


BOOL CDAeCSVImportLog::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    if (OpenLogFile() != 0)     // Log Datei ˆffnen
    {
        m_CLog = m_Fehlertext;
        UpdateData(FALSE);
        return TRUE;
    }
    ReadLogFile();              // Log Datei lesen
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

int CDAeCSVImportLog::OpenLogFile()
{
    CFileException e;
    if (!logfile.Open(m_CLogFile, CFile::modeRead, &e))
    {
        TCHAR error[255];
        e.GetErrorMessage(error, 255);
        m_Fehlertext = error;
        return 1;
    }
    return 0;
}

void CDAeCSVImportLog::ReadLogFile()
{
    CString Text;

    for (;;)
    {
        if (logfile.ReadString(Text) != NULL)
        {
            m_CLog += Text;
            m_CLog += "\r\n";
        }
        else break;
    }
    logfile.Close();
}

HBRUSH CDAeCSVImportLog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_EDIT_LOG)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiﬂ
    }
    return hbr;
}
