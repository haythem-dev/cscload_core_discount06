// DCSVFormat.cpp : implementation file
//

#include "stdafx.h"
#include "DCSVFormat.h"
#include <cscorderimportcsvformats.h>
#include <cscorderimportcsvcolumns.h>
#include <cscorderimportfields.h>


//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB              0
#define COL_NAME            1
#define COL_FORMATID        2
#define COL_POSTPONE        3
#define COL_START           4
#define NUM_COLUMNS_CSV     5

static COLUMNS_TYPES Columns[] =
{
    COL_KB,       "",  40, LVCFMT_LEFT,
    COL_NAME,     "", 240, LVCFMT_LEFT,
    COL_FORMATID, "",   0, LVCFMT_LEFT,
    COL_POSTPONE, "",   0, LVCFMT_LEFT,
    COL_START,    "",   0, LVCFMT_LEFT,
    -1,           "",   0, 0
};


// CDCSVFormat dialog

IMPLEMENT_DYNAMIC(CDCSVFormat, CDialogEx)

CDCSVFormat::CDCSVFormat(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(IDD_AE_CSV_FORMATS, pParent)
{
    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KB);
    Columns[COL_NAME].Columns = CResString::ex().getStrTblText(AETXT_CSV_FORMAT_NAME);
}

CDCSVFormat::~CDCSVFormat()
{
}

void CDCSVFormat::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDCSVFormat, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, &CDCSVFormat::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CDCSVFormat::OnBnClickedButtonDel)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDCSVFormat::OnNMDblclkList1)
END_MESSAGE_MAP()


// CDCSVFormat message handlers


BOOL CDCSVFormat::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }
    if (!GetAeUser().IsPflegeCSVImportParam())
    {
        GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_DEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDOK)->EnableWindow(FALSE);
        GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
    }

    ReadDataInListBox();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCSVFormat::OnBnClickedOk()
{
    if (!GetAeUser().IsPflegeCSVImportParam())
        return;

    CDCSVFormatUpd dlgCSVFormatUpd;
    if (dlgCSVFormatUpd.DoModal() == IDOK)
        ReadDataInListBox();
}

void CDCSVFormat::OnBnClickedButtonDel()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            char error_msg[81];
            CCSCORDERIMPORTCSVFORMATS format;
            //delete format
            format.SetCscorderimportformatid(atol(m_List1.GetItemText(pos, COL_FORMATID)));
            int rc = ::ServerNr(PIPE_AE_SRV, AasrvDeleteCSCOrderImportCSVFormats, (void *)&format.s, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ, error_msg);
            if (rc < 0)
            {
                FehlerBehandlung(rc, error_msg);
                return;
            }
            MsgBoxOK(AETXT_ROW_DELETED);
            ReadDataInListBox();
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDCSVFormat::OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDCSVFormatUpd dlgCSVFormatUpd;
        dlgCSVFormatUpd.m_update = TRUE;
        dlgCSVFormatUpd.m_CID = m_List1.GetItemText(pos, COL_FORMATID);
        dlgCSVFormatUpd.m_CName = m_List1.GetItemText(pos, COL_NAME);
        if (atoi(m_List1.GetItemText(pos, COL_POSTPONE)) == 1)
            dlgCSVFormatUpd.m_bPostpone = TRUE;
        dlgCSVFormatUpd.m_sStart = (short)atoi(m_List1.GetItemText(pos, COL_START));
        if (dlgCSVFormatUpd.DoModal() == IDOK)
            ReadDataInListBox();
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);    //kann eigentlich nicht sein
    }

    *pResult = 0L;
}

void CDCSVFormat::ReadDataInListBox()
{
    CCSCORDERIMPORTCSVFORMATS format;
    CStringArray s;
    s.SetSize(NUM_COLUMNS_CSV);
    ppString name;
    int rc = 0;
    char error_msg[81];

    CLetterMan kb;
    BeginWaitCursor();
    m_List1.DeleteAllItems();
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvGetCSCOrderImportCSVFormats, (void*)&format.s, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        if (rc != 0)
            break;
        s[COL_KB] = kb.Next();
        s[COL_NAME] = format.GetCsvformatname(name);
        s[COL_FORMATID].Format("%d", format.GetCscorderimportformatid());
        s[COL_POSTPONE].Format("%d", format.GetPostponeorder());
        s[COL_START].Format("%d", format.GetDatastartingline());

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS_CSV, s))
        {
            EndWaitCursor();
            return;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_List1, 0);
}


// C:\Source\Repos\pharmos.outbound.csc_core_applications\dev\src\ae\ae\DCSVFormat.cpp : implementation file
//


#define COL_COLUMNS_POS             0
#define COL_COLUMNS_NAME            1
#define COL_COLUMNS_GROUPING        2
#define COL_COLUMNS_FIELDNAMEID     3
#define COL_COLUMNS_NEW             4
#define NUM_COLUMNS_CSV_COL         5

static COLUMNS_TYPES ColumnsCol[] =
{
    COL_COLUMNS_POS,         "", 110, LVCFMT_LEFT,
    COL_COLUMNS_NAME,        "", 240, LVCFMT_LEFT,
    COL_COLUMNS_GROUPING,    "", 120, LVCFMT_LEFT,
    COL_COLUMNS_FIELDNAMEID, "",   0, LVCFMT_LEFT,
    COL_COLUMNS_NEW,         "",   0, LVCFMT_LEFT,
    -1,                      "",   0, 0
};

// CDCSVFormatUpd dialog

IMPLEMENT_DYNAMIC(CDCSVFormatUpd, CDialogEx)

CDCSVFormatUpd::CDCSVFormatUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(IDD_AE_CSV_FORMATS_UPD, pParent)
    , m_CName(_T(""))
    , m_CID(_T(""))
    , m_update(FALSE)
    , m_bPostpone(FALSE)
    , m_sStart(1)
    , m_CPos(_T(""))
    , m_bGrouping(FALSE)
{
    ColumnsCol[COL_COLUMNS_POS].Columns = CResString::ex().getStrTblText(AETXT_POSITION);
    ColumnsCol[COL_COLUMNS_NAME].Columns = CResString::ex().getStrTblText(AETXT_FELDINHALT);
    ColumnsCol[COL_COLUMNS_GROUPING].Columns = CResString::ex().getStrTblText(AETXT_AA_CHANGE);
}

CDCSVFormatUpd::~CDCSVFormatUpd()
{
}

void CDCSVFormatUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_EDIT_NAME, m_edit_Name);
    DDX_Text(pDX, IDC_EDIT_NAME, m_CName);
    DDX_Control(pDX, IDC_COMBO_START, m_combo_Start);
    DDX_Control(pDX, IDC_CHECK_POSTPONE, m_cb_Postpone);
    DDX_Text(pDX, IDC_STATIC_ID_WERT, m_CID);
    DDX_Check(pDX, IDC_CHECK_POSTPONE, m_bPostpone);
    DDX_Text(pDX, IDC_EDIT_POS, m_CPos);
    DDX_Control(pDX, IDC_COMBO_INHALT, m_combo_Inhalt);
    DDX_Control(pDX, IDC_CHECK_GROUPING, m_check_Grouping);
    DDX_Check(pDX, IDC_CHECK_GROUPING, m_bGrouping);
}


BEGIN_MESSAGE_MAP(CDCSVFormatUpd, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_PLUS, &CDCSVFormatUpd::OnBnClickedButtonPlus)
    ON_BN_CLICKED(IDC_BUTTON_MINUS, &CDCSVFormatUpd::OnBnClickedButtonMinus)
    ON_EN_CHANGE(IDC_EDIT_NAME, &CDCSVFormatUpd::OnEnChangeEditName)
    ON_BN_CLICKED(IDC_BUTTON_INS, &CDCSVFormatUpd::OnBnClickedButtonIns)
    ON_BN_CLICKED(IDC_BUTTON_ABBRUCH, &CDCSVFormatUpd::OnBnClickedButtonAbbruch)
    ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDCSVFormatUpd::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CDCSVFormatUpd message handlers


BOOL CDCSVFormatUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(ColumnsCol, m_List1))
    {
        return FALSE;
    }

    if (!GetAeUser().IsPflegeCSVImportParam())
    {
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_COMBO_START)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_POSTPONE)->EnableWindow(FALSE);
    }
    if (m_update)
    {
        GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);
    }
    CCSCORDERIMPORTCSVCOLUMNS col;
    CCSCORDERIMPORTFIELDS fields;
    CString Ausgabe;
    CStringArray s;
    s.SetSize(NUM_COLUMNS_CSV_COL);
    ppString name;
    int rc = 0;
    char error_msg[81];
    char mandotory[2];

    BeginWaitCursor();
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvGetCSCOrderImportFields, (void*)&fields.s, CSCORDERIMPORTFIELDS_BES, CSCORDERIMPORTFIELDS_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return FALSE;
        }
        if (rc != 0)
            break;
        strcpy(mandotory, fields.GetImportmandatory() == 1 ? "*" : " ");
        Ausgabe.Format("%03d %s %s", fields.GetFieldnameid(), mandotory, fields.GetDisplayname(name));
        m_combo_Inhalt.AddString(Ausgabe);
        m_array_Inhalt.Add(Ausgabe);
    }
    m_combo_Start.SetCurSel(m_update ? m_sStart - 1 : 0);

    GetDlgItem(IDC_STATIC_NEW)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_NEW)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_POS)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_POS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_POS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_POS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_INHALT)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_INHALT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_INHALT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_INHALT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_INS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_ABBRUCH)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_ABBRUCH)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_CHECK_GROUPING)->EnableWindow(FALSE);
    GetDlgItem(IDC_CHECK_GROUPING)->ShowWindow(SW_HIDE);
    if (GetAeUser().IsPflegeCSVImportParam())
    {
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_SHOW);
    }

    m_List1.DeleteAllItems();
    col.SetCscorderimportformatid(atoi(m_CID));
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvGetCSCOrderImportCSVColumns, (void*)&col.s, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return FALSE;
        }
        if (rc != 0)
            break;
        s[COL_COLUMNS_POS].Format("%d", col.GetColumnno());
        Ausgabe.Format("%03d", col.GetFieldnameid());
        int pos = m_combo_Inhalt.FindString(0, Ausgabe);
        m_combo_Inhalt.GetLBText(pos, Ausgabe);
        m_combo_Inhalt.DeleteString(pos);   //bereits im Format vorhandenes Feld aus der Auswahl entfernen
        s[COL_COLUMNS_NAME] = Ausgabe.Right(Ausgabe.GetLength() - 4);
        s[COL_COLUMNS_FIELDNAMEID].Format("%d", col.GetFieldnameid());
        s[COL_COLUMNS_GROUPING].Format("%d", col.GetGrouping());
        s[COL_COLUMNS_NEW] = "0";

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS_CSV_COL, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    m_combo_Inhalt.SetCurSel(0);

    if (m_update)
    {
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_NAME));
    }
    else
    {
        CListCtrlHelper::SetFocusSelectedFocusedVisible(m_List1, 0);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCSVFormatUpd::OnBnClickedButtonPlus()
{
    GetDlgItem(IDC_STATIC_NEW)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_NEW)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_POS)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_POS)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_EDIT_POS)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_POS)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_INHALT)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_INHALT)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_INHALT)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_INHALT)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BUTTON_INS)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_INS)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BUTTON_ABBRUCH)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_ABBRUCH)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_CHECK_GROUPING)->EnableWindow(TRUE);
    GetDlgItem(IDC_CHECK_GROUPING)->ShowWindow(SW_SHOW);
    if (GetAeUser().IsPflegeCSVImportParam())
    {
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_HIDE);
    }

    m_check_Grouping.SetCheck(FALSE);
}

void CDCSVFormatUpd::OnBnClickedButtonMinus()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            char error_msg[81];
            CCSCORDERIMPORTCSVCOLUMNS col;
            //delete format
            if (atoi(m_List1.GetItemText(pos, COL_COLUMNS_NEW)) == 0)
            {
                col.SetColumnno((short)atoi(m_List1.GetItemText(pos, COL_COLUMNS_POS)));
                col.SetCscorderimportformatid(atol(m_CID));
                int rc = ::ServerNr(PIPE_AE_SRV, AasrvDeleteCSCOrderImportCSVColumns, (void*)&col.s, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ, error_msg);
                if (rc < 0)
                {
                    FehlerBehandlung(rc, error_msg);
                    return;
                }
                MsgBoxOK(AETXT_ROW_DELETED);
            }
            CString NameID;
            NameID.Format("%03s", m_List1.GetItemText(pos, COL_COLUMNS_FIELDNAMEID).GetString());
            m_List1.DeleteItem(pos);
            for (int i = 0; i < m_array_Inhalt.GetCount(); i++)
            {
                if (m_array_Inhalt.GetAt(i).Find(NameID,0) != -1 )
                {
                    m_combo_Inhalt.AddString(m_array_Inhalt.GetAt(i));  //Feld wieder in Auswahl
                    break;
                }
            }
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
    m_combo_Inhalt.SetCurSel(0);
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_List1, 0);
}

void CDCSVFormatUpd::OnEnChangeEditName()
{
    AllgLaengeKontr(&m_edit_Name, L_CSCORDERIMPORTCSVFORMATS_CSVFORMATNAME, AeGetApp()->Modus());
}

void CDCSVFormatUpd::OnBnClickedButtonIns()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS_CSV_COL);

    UpdateData();
    if (m_CPos.IsEmpty())
    {
        MsgBoxOK(AETXT_INS_COL);
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_POS));
        return;
    }
    int idx = m_combo_Inhalt.GetCurSel();
    CString Eingabe;
    m_combo_Inhalt.GetLBText(idx, Eingabe);
    CString Feldname = Eingabe.Right(Eingabe.GetLength() - 4);
    CString ID = Eingabe.Left(3);
    for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
    {
        if (m_CPos == m_List1.GetItemText(pos, COL_COLUMNS_POS))
        {
            MsgBoxOK(AETXT_POS_EXIST);
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_POS));
            return;
        }
        if (ID == m_List1.GetItemText(pos, COL_COLUMNS_FIELDNAMEID))
        {
            MsgBoxOK(AETXT_FIELD_EXIST);
            GotoDlgCtrl(GetDlgItem(IDC_COMBO_INHALT));
            return;
        }
    }
    s[COL_COLUMNS_POS] = m_CPos;
    s[COL_COLUMNS_NAME] = Feldname;
    s[COL_COLUMNS_FIELDNAMEID] = ID;
    s[COL_COLUMNS_GROUPING] = m_bGrouping ? "1" : "0";
    s[COL_COLUMNS_NEW] = "1";

    if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS_CSV_COL, s))
    {
        EndWaitCursor();
        return;
    }
    int spalte = atoi(m_CPos) + 1;  //Spaltennummer auf nächst höheren Wert setzen
    m_CPos.Format("%d", spalte);
    GetDlgItem(IDC_EDIT_POS)->SetWindowTextA(m_CPos);
    m_combo_Inhalt.DeleteString(idx);   //bereits im Format vorhandenes Feld aus der Auswahl entfernen
    m_combo_Inhalt.SetCurSel(0);

    GetDlgItem(IDC_STATIC_NEW)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_NEW)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_POS)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_POS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_POS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_POS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_INHALT)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_INHALT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_INHALT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_INHALT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_INS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_ABBRUCH)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_ABBRUCH)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_CHECK_GROUPING)->EnableWindow(FALSE);
    GetDlgItem(IDC_CHECK_GROUPING)->ShowWindow(SW_HIDE);
    if (GetAeUser().IsPflegeCSVImportParam())
    {
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_SHOW);
    }
}

void CDCSVFormatUpd::OnBnClickedButtonAbbruch()
{
    GetDlgItem(IDC_STATIC_NEW)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_NEW)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_POS)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_POS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_POS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_POS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_INHALT)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_INHALT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_INHALT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_INHALT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_INS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_ABBRUCH)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_ABBRUCH)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_CHECK_GROUPING)->EnableWindow(FALSE);
    GetDlgItem(IDC_CHECK_GROUPING)->ShowWindow(SW_HIDE);
    if (GetAeUser().IsPflegeCSVImportParam())
    {
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_SHOW);
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_List1, 0);
}

void CDCSVFormatUpd::OnBnClickedButtonSave()
{
    UpdateData();
    if (!m_update)
    {
        if (m_CName.IsEmpty())
        {
            MsgBoxOK(AETXT_NEW_BEZEICHNUNG);
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_NAME));
            return;
        }
    }
    bool gefunden;
    char error_msg[81];
    int ID;
    for (int i = 0; i < m_array_Inhalt.GetCount(); i++)
    {
        gefunden = false;
        if (m_array_Inhalt.GetAt(i).Mid(4, 1) == "*")
        {
            ID = atoi(m_array_Inhalt.GetAt(i).Left(3));
            for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
            {
                if (ID == atoi((m_List1.GetItemText(pos, COL_COLUMNS_FIELDNAMEID))))
                {
                    gefunden = true;
                    break;
                }
            }
            if (!gefunden)
            {
                if (MsgBoxYesNo(AETXT_NOT_ALL_MANDATORY, MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO) return;
            }
        }
    }
    CCSCORDERIMPORTCSVFORMATS format;
    format.SetCscorderimportformatid(atoi(m_CID));
    format.SetCsvformatname(m_CName);
    format.SetDatastartingline((short)(m_combo_Start.GetCurSel() + 1));
    format.SetPostponeorder(m_bPostpone ? 1 : 0);

    int rc;
    if (!m_update)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvInsertCSCOrderImportCSVFormats, (void*)&format.s, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        m_CID.Format("%d", format.GetCscorderimportformatid());
    }
    else
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvUpdateCSCOrderImportCSVFormats, (void*)&format.s, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
    }
    // Now insert new column entries
    CCSCORDERIMPORTCSVCOLUMNS col;
    for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
    {
        if (atoi(m_List1.GetItemText(pos, COL_COLUMNS_NEW)) == 1)
        {
            col.SetColumnno((short)(atoi(m_List1.GetItemText(pos, COL_COLUMNS_POS))));
            col.SetCscorderimportformatid(atoi(m_CID));
            col.SetFieldnameid(atoi(m_List1.GetItemText(pos, COL_COLUMNS_FIELDNAMEID)));
            col.SetGrouping((short)(atoi(m_List1.GetItemText(pos, COL_COLUMNS_GROUPING))));
            rc = ::ServerNr(PIPE_AE_SRV, AasrvInsertCSCOrderImportCSVColumns, (void*)&col.s, CSCORDERIMPORTCSVCOLUMNS_BES, CSCORDERIMPORTCSVCOLUMNS_ANZ, error_msg);
            if (rc < 0)
            {
                FehlerBehandlung(rc, error_msg);
                return;
            }
        }
    }
    CDialogMultiLang::OnOK();
}
