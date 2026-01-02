// DAeCSVImport.cpp : implementation file
//

#include "stdafx.h"
#include "DAeCSVImport.h"
#include <cscorderimportcsvformats.h>
#include <cscorderimportcsvfile.h>
#include <afxinet.h>
#include <istream>
#include <fstream>
#include "AeCopyCSV.h"
#include "DAeCSVImportLog.h"


// CDAeCSVImport dialog

IMPLEMENT_DYNAMIC(CDAeCSVImport, CDialog)

CDAeCSVImport::CDAeCSVImport(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(IDD_AE_CSV_IMPORT, pParent)
    , m_CDateiName(_T(""))
{
}

CDAeCSVImport::~CDAeCSVImport()
{
}

void CDAeCSVImport::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_CSV_FORMAT, m_combo_Format);
    DDX_Text(pDX, IDC_EDIT_DATEI_NAME, m_CDateiName);
    DDX_Control(pDX, IDC_EDIT_DATEI_NAME, m_editDateiName);
}


BEGIN_MESSAGE_MAP(CDAeCSVImport, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DATEI_AUSWAHL, &CDAeCSVImport::OnBnClickedButtonDateiAuswahl)
    ON_EN_CHANGE(IDC_EDIT_DATEI_NAME, &CDAeCSVImport::OnEnChangeEditDateiName)
END_MESSAGE_MAP()


// CDAeCSVImport message handlers


BOOL CDAeCSVImport::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CCSCORDERIMPORTCSVFORMATS format;
    ppString name;
    CString Anzeige;
    int rc = SRV_OK;
    char error_msg[81];

    BeginWaitCursor();
    format.SetIsvalid(1);   //nur gueltige Formate
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvGetCSCOrderImportCSVFormats, (void *)&format.s, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ, error_msg);
        if (rc < SRV_OK)
        {
            FehlerBehandlung(rc, error_msg);
            return TRUE;
        }
        if (rc != SRV_OK)
            break;
        Anzeige.Format("%s                                                                                                                       %08d", format.GetCsvformatname(name), format.GetCscorderimportformatid());
        m_combo_Format.AddString(Anzeige);
    }
    m_combo_Format.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAeCSVImport::OnOK()
{
    UpdateData();
    if (m_CDateiName.IsEmpty())
    {
        MsgBoxOK(AETXT_NO_FILE);
        return;
    }
    m_RemoteAdresse = AeGetApp()->ImportAdresse();
    m_CUsername = AeGetApp()->ImportUser();
    m_CPwd = AeGetApp()->ImportPWD();
    m_CServer = AeGetApp()->ImportServer();
    CAeCopyCSV copy;
    CString RemoteName;
    BeginWaitCursor();

    auto inputEncoding = std::string(AeGetApp()->InputEncoding().GetString());
    auto outputEncoding = std::string(AeGetApp()->OutputEncoding().GetString());

    if (false == inputEncoding.empty()
        && false == outputEncoding.empty()
        && false == CreateCompatibleFileEncoding(inputEncoding, outputEncoding))
    {
        MsgBoxOK(m_CFehlerText);
        EndWaitCursor();
        return;
    }

    if (TransferFile() != 0)
    {
        MsgBoxOK(m_CFehlerText);
        EndWaitCursor();
        return;
    }

    CCSCORDERIMPORTCSVFILE datei;
    int rc;
    char error_msg[80];
    int selpos;
    int formatid;
    CString Format;
    selpos = m_combo_Format.GetCurSel();
    m_combo_Format.GetLBText(selpos, Format);
    formatid = atoi(Format.Right(8));
    Format = Format.Left(Format.GetLength() - 8).Trim();
    datei.SetCsvformatname(Format);
    datei.SetCscorderimportformatid(formatid);
#ifndef LOCAL_WINDEBUG
    datei.SetDateiname(m_CRemoteFile);
#else
    datei.SetDateiname(m_CRemoteLocalDebugFile);
    m_CRemoteLocalDebugReportFile = "c:\\ftp_files\\" + m_CRemoteReportCSVFile;
#endif
    m_CRemoteReportCSVFile = m_RemoteAdresse + m_CRemoteReportCSVFile; // full path
#ifndef LOCAL_WINDEBUG
    datei.SetCsvreportfile(m_CRemoteReportCSVFile);
#else
    datei.SetCsvreportfile(m_CRemoteLocalDebugReportFile);
#endif
    datei.SetDateinameorg(m_CDateiName);
    datei.SetLanguage(AeGetApp()->Language());
    rc = ::ServerNr(PIPE_AE_SRV, AasrvCSCOrderImport, (void *)&datei.s, CSCORDERIMPORTCSVFILE_BES, CSCORDERIMPORTCSVFILE_ANZ, error_msg);
    if (rc < SRV_OK)
    {
        FehlerBehandlung(rc, error_msg);
        EndWaitCursor();
        return;
    }
    if (datei.GetFehler() == 1) //OrdImpRCFormatNotFound
    {
        ppString meld;
        MsgBoxOK(datei.GetCsvfehlertext(meld));
        return;
    }
    if (datei.GetFehler() == 2) //OrdImpRCInputFileFailed
    {
        ppString meld;
        MsgBoxOK(datei.GetCsvfehlertext(meld));
    }
    if (datei.GetFehler() == 3) //OrdImpRCReportFileFailed
    {
        ppString meld;
        MsgBoxOK(datei.GetCsvfehlertext(meld));
        return;
    }
    if (datei.GetFehler() == 4) //OrdImpRCCreateOrdersError
    {
        ppString meld;
        MsgBoxOK(datei.GetCsvfehlertext(meld));
    }
    if (datei.GetFehler() == 5) //OrdImpRCWrongFormat
    {
        ppString meld;
        MsgBoxOK(datei.GetCsvfehlertext(meld));
    }
    ppString logfile;
    m_CLogFile = datei.GetCsvlogfile(logfile);
    if (TransferLogReportFiles() != 0)
    {
        MsgBoxOK(m_CFehlerText);
        EndWaitCursor();
        return;
    }
    EndWaitCursor();
    CDAeCSVImportLog logdlg;
    logdlg.m_CLogFile = m_CLokalLogFile;
    logdlg.DoModal();
    CDialogMultiLang::OnOK();
}

void CDAeCSVImport::OnBnClickedButtonDateiAuswahl()
{
    CFileDialog fileName(OFN_EXPLORER);
    if (fileName.DoModal() == IDOK)
    {
        m_CDateiName.Format("%s", fileName.GetPathName().GetString());
        m_CLokalPath = fileName.GetFolderPath();
        UpdateData(FALSE);
    }
}

void CDAeCSVImport::OnEnChangeEditDateiName()
{
    AllgLaengeKontr(&m_editDateiName, L_CSCORDERIMPORTCSVFILE_DATEINAME, AeGetApp()->Modus());
}

bool CDAeCSVImport::CreateCompatibleFileEncoding(std::string input_encoding, std::string output_encoding)
{
    auto input_file = std::string(m_CDateiName.GetString());
    std::ifstream input_stream(input_file, std::ios::binary);

    auto dot_position = input_file.find_last_of('.');
    auto output_file = std::string(input_file.substr(0, dot_position) + "_encoding_" + output_encoding + input_file.substr(dot_position));

    std::ofstream output_stream(output_file, std::ios::binary);

    std::string inputString((std::istreambuf_iterator<char>(input_stream)), std::istreambuf_iterator<char>());

    // Convert from Windows-1251 to Wide Characters (UTF-16)
    UINT ui_in_enc = std::stoi(input_encoding);
    int wideCharSize = MultiByteToWideChar(ui_in_enc, 0, inputString.c_str(), -1, NULL, 0);
    std::vector<wchar_t> wideString(wideCharSize);
    MultiByteToWideChar(ui_in_enc, 0, inputString.c_str(), -1, &wideString[0], wideCharSize);

    // Convert from Wide Characters (UTF-16) to ISO 8859-5
    UINT ui_uo_enc = std::stoi(output_encoding);
    int multiByteSize = WideCharToMultiByte(ui_uo_enc, 0, &wideString[0], -1, NULL, 0, NULL, NULL);
    std::vector<char> outputString(multiByteSize);
    WideCharToMultiByte(ui_uo_enc, 0, &wideString[0], -1, &outputString[0], multiByteSize, NULL, NULL);

    // Write the converted string to the output file
    output_stream.write(&outputString[0], outputString.size() - 1);

    input_stream.close();
    output_stream.close();

    m_CDateiName = CString(output_file.c_str());

    return true;
}

int CDAeCSVImport::TransferFile()
{
    CInternetSession session;
    CFtpConnection* conn = NULL;
    try
    {
#ifdef LOCAL_WINDEBUG
        m_CServer = "localhost";
#endif
        conn = session.GetFtpConnection(m_CServer, m_CUsername, m_CPwd, 21);
    }
    catch (CInternetException& e)
    {
        char error[256];
        e.GetErrorMessage(error,250);
        m_CFehlerText = error;
        return 1;
    }
    CreateRemoteFileName();
    CString generatedRemoteFileName = m_CRemoteFile;
    m_CRemoteFile = m_RemoteAdresse + m_CRemoteFile;
    if (!conn->PutFile(m_CDateiName, m_CRemoteFile, FTP_TRANSFER_TYPE_ASCII))
    {
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf,
            0, NULL);
        m_CFehlerText.Format("%s failed with error %d: %s", "TransferFile", dw, lpMsgBuf);
        conn->Close();
        delete conn;
        return dw;
    }
    conn->Close();
    delete conn;
#ifdef LOCAL_WINDEBUG
    m_CRemoteLocalDebugFile = "C:\\ftp_files\\" + generatedRemoteFileName;
#endif
    return 0;
}

int CDAeCSVImport::CreateRemoteFileName()
{
    UUID uuid;
    CString Output;

    // create remote input csv filename and remote report csv filename
    if (UuidCreate(&uuid) == RPC_S_OK)
    {
        PUCHAR szUuid;
        if (UuidToString(&uuid, &szUuid) == RPC_S_OK)
        {
            Output = szUuid;
            Output.MakeUpper();
            RpcStringFree(&szUuid);
            m_CRemoteFile.Format("CSV%s.csv", Output.GetString());
            m_CRemoteReportCSVFile.Format("CSV%s-Report-%08i-%06i.csv", Output.GetString(), ppGGetDate(), ppGGetTime());
            return 0;
        }
    }
    return 1;
}

int CDAeCSVImport::TransferLogReportFiles()
{
    CInternetSession session;
    CFtpConnection* conn = NULL;
    try
    {
        conn = session.GetFtpConnection(m_CServer, m_CUsername, m_CPwd, 21);
    }
    catch (CInternetException &e)
    {
        char error[256];
        e.GetErrorMessage(error, 250);
        m_CFehlerText = error;
        return 1;
    }
    CString nameLog = m_CLogFile.Right(m_CLogFile.GetLength() - m_RemoteAdresse.GetLength()); //nur Dateiname
    m_CLokalLogFile = m_CLokalPath + "\\" + nameLog;
    if (!conn->GetFile(m_CLogFile, m_CLokalLogFile, TRUE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_ASCII))
    {
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf,
            0, NULL);
        m_CFehlerText.Format("%s failed with error %d: %s", "TransferLogFile", dw, lpMsgBuf);
        conn->Close();
        delete conn;
        return dw;
    }

    CString nameReport = m_CRemoteReportCSVFile.Right(m_CRemoteReportCSVFile.GetLength() - m_RemoteAdresse.GetLength());
    m_CLokalReportFile = m_CLokalPath + "\\" + nameReport;
    if (!conn->GetFile(m_CRemoteReportCSVFile, m_CLokalReportFile, TRUE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_ASCII))
    {
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf,
            0, NULL);
        m_CFehlerText.Format("%s failed with error %d: %s", "TransferLogFile", dw, lpMsgBuf);
        conn->Close();
        delete conn;
        return dw;
    }

    conn->Close();
    delete conn;
    return 0;
}
