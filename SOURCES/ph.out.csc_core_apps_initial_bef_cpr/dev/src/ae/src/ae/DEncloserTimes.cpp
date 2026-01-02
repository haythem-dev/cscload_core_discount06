// DEncloserTimes.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <customer.h>
#include <kndsel.h>
#include "DKndInf.h"
#include "DKndWahl.h"
#include "DEncloserTimes.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 70, LVCFMT_RIGHT,
    2,  "", 70, LVCFMT_RIGHT,
    -1, "",  0, 0
};

// CDEncloserTimes-Dialogfeld

IMPLEMENT_DYNAMIC(CDEncloserTimes, CDialog)
CDEncloserTimes::CDEncloserTimes(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDEncloserTimes::IDD, pParent)
    , m_cKndNr(_T(""))
    , m_cKndNr2(_T(""))
{
}

CDEncloserTimes::~CDEncloserTimes()
{
}

void CDEncloserTimes::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_KNDNR, m_edit_KndNr);
    DDX_Text(pDX, IDC_EDIT_KNDNR, m_cKndNr);
    DDX_Control(pDX, IDC_EDIT_KUNDE2, m_edit_KndNr2);
    DDX_Text(pDX, IDC_EDIT_KUNDE2, m_cKndNr2);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDEncloserTimes, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnBnClickedButtonKnd)
    ON_BN_CLICKED(IDC_BUTTON_COPY, OnBnClickedButtonCopy)
    ON_BN_CLICKED(IDC_BUTTON_COPY2, OnBnClickedButtonCopy2)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnBnClickedButtonUpd)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
    ON_EN_CHANGE(IDC_EDIT_KNDNR, OnEnChangeEditKndnr)
    ON_EN_CHANGE(IDC_EDIT_KUNDE2, OnEnChangeEditKunde2)
END_MESSAGE_MAP()


// CDEncloserTimes-Meldungshandler

void CDEncloserTimes::OnBnClickedButtonKnd()
{
    CDKndWahl dlgKndWahl;
    dlgKndWahl.m_apo = m_CMC;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        m_lKunde = 0;
        return;
    }
    m_lKunde = dlgKndWahl.GetIdfNr();
    m_CMC.Empty();
    m_cKndNr.Format("%ld", m_lKunde);
    GetDlgItem(IDC_EDIT_KNDNR)->SetWindowText(m_cKndNr);
    m_edit_KndNr.SetFocus();
    m_edit_KndNr.SetSel(0, -1, FALSE);
    m_edit_KndNr.SetSel(-1, 0, FALSE);              //Selektion aufheben
}

void CDEncloserTimes::OnBnClickedButtonCopy()
{
    GetDlgItem(IDC_EDIT_KUNDE2)->EnableWindow();
    GetDlgItem(IDC_EDIT_KUNDE2)->ShowWindow(SW_SHOW);
    m_edit_KndNr2.SetFocus();
    m_edit_KndNr2.SetSel(0, -1, FALSE);
    m_edit_KndNr2.SetSel(-1, 0, FALSE);             //Selektion aufheben
}

void CDEncloserTimes::OnBnClickedButtonCopy2()
{
    UpdateData();
    if (m_lKunde2 == 0)
    {
        CKNDAUSKU kndausku;
        kndausku.s.KUNDENNR = kndausku.s.IDFNR = atol(m_cKndNr2);
        kndausku.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
        kndausku.Server(AakundeSel_ausku);
        if (kndausku.rc < SRV_OK)
        {
            MsgBoxOK(IDP_KEIN_KUNDE);
            m_edit_KndNr2.SetFocus();
            m_edit_KndNr2.SetSel(0, -1, FALSE);
            m_edit_KndNr2.SetSel(-1, 0, FALSE);     //Selektion aufheben
            GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow(FALSE);
            return;
        }
        m_lKunde2 = kndausku.s.KUNDENNR;
    }
    m_EncTimes.SetBranchno(AeGetApp()->VzNr());
    m_EncTimes.SetCustomerno(atol(m_cKndNr));
    m_EncTimes.SetKundennr(m_lKunde2);
    if (!m_EncTimes.CopyEncloser())
    {
        CString CStr;
        CStr.Format(CResString::ex().getStrTblText(AETXT_INSERTED), m_EncTimes.GetCustomerno());
        MsgBoxOK(CStr);
    }
    GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow(FALSE);
    m_edit_KndNr2.SetFocus();
    m_edit_KndNr2.SetSel(0, -1, FALSE);
    m_lKunde2 = 0;
}

void CDEncloserTimes::OnBnClickedOk()
{
    UpdateData();
    if (m_cKndNr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_KUNDENNR);
        return;
    }
    m_lKunde = 0;
    GetPage();
}

void CDEncloserTimes::OnBnClickedButtonInsert()
{
    UpdateData();
    if (m_cKndNr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_KUNDENNR);
        return;
    }
    CDEncloserUpd dlgEncloserUpd;
    dlgEncloserUpd.m_bUpdate = FALSE;
    if (dlgEncloserUpd.DoModal() == IDCANCEL)
        return;
    m_EncTimes.SetBranchno(AeGetApp()->VzNr());
    m_EncTimes.SetCustomerno(atol(m_cKndNr));
    m_EncTimes.SetTimediff(static_cast<short>(atoi(dlgEncloserUpd.m_cDiff)));
    m_EncTimes.SetMaxpositions(static_cast<short>(atoi(dlgEncloserUpd.m_cMax)));
    if (m_EncTimes.Insert() == 0)
    {
        m_lKunde = atol(m_cKndNr);
    }

    GetPage();
}

void CDEncloserTimes::OnBnClickedButtonUpd()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDEncloserUpd dlgEncloserUpd;
        dlgEncloserUpd.m_bUpdate = TRUE;
        dlgEncloserUpd.m_cDiff = m_List1.GetItemText(pos, 1);
        dlgEncloserUpd.m_cMax = m_List1.GetItemText(pos, 2);
        if (dlgEncloserUpd.DoModal() == IDCANCEL)
            return;
        m_EncTimes.SetBranchno(AeGetApp()->VzNr());
        m_EncTimes.SetCustomerno(atol(m_cKndNr));
        m_EncTimes.SetTimediff(static_cast<short>(atoi(dlgEncloserUpd.m_cDiff)));
        m_EncTimes.SetMaxpositions(static_cast<short>(atoi(dlgEncloserUpd.m_cMax)));
        if (m_EncTimes.Update() == 0)
            GetPage();
    }
}

void CDEncloserTimes::OnBnClickedButtonDel()
{
    UpdateData();
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            m_EncTimes.SetBranchno(AeGetApp()->VzNr());
            m_EncTimes.SetCustomerno(atol(m_cKndNr));
            m_EncTimes.SetTimediff(static_cast<short>(atoi(m_List1.GetItemText(pos, 1))));
            m_EncTimes.SetMaxpositions(static_cast<short>(atoi(m_List1.GetItemText(pos, 2))));
            if (m_EncTimes.Delete() == 0)
                GetPage();
        }
    }
}

void CDEncloserTimes::OnEnChangeEditKndnr()
{
    CString str;

    m_edit_KndNr.GetWindowText(str);                //IDF lesen
    if (str.IsEmpty())
        return;                                     //Feld ist leer
    char chN = str[str.GetLength() - 1];            //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CMC = str;
        OnBnClickedButtonKnd();
        return;
    }
    AllgWertKontr(&m_edit_KndNr, MAXIMUM_IDF);
}

void CDEncloserTimes::OnEnChangeEditKunde2()
{
    CString str;

    m_edit_KndNr2.GetWindowText(str);                   //IDF lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CMC = str;
        OnBnClickedButtonKnd();
        m_lKunde2 = m_lKunde;
        m_cKndNr2.Format("%ld", m_lKunde);
        GetDlgItem(IDC_EDIT_KUNDE2)->SetWindowText(m_cKndNr2);
        m_edit_KndNr2.SetFocus();
        m_edit_KndNr2.SetSel(0, -1, FALSE);
        m_edit_KndNr2.SetSel(-1, 0, FALSE);             //Selektion aufheben
        GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow();
        return;
    }
    AllgWertKontr(&m_edit_KndNr2, MAXIMUM_IDF);
    GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow();
}

BOOL CDEncloserTimes::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_ENCLOSER_TIME);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_ENCLOSER_POS);
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_COPY)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_COPY2)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_COPY2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_KUNDE2)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_KUNDE2)->ShowWindow(SW_HIDE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDEncloserTimes::GetPage()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_List1.DeleteAllItems();
    m_EncTimes.SetBranchno(AeGetApp()->VzNr());
    m_EncTimes.SetCustomerno(atol(m_cKndNr));
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_EncTimes.SelList() != SRV_OK) break;
        s[0] = kb.Next();
        s[1].Format("%d", m_EncTimes.GetTimediff());
        s[2].Format("%d", m_EncTimes.GetMaxpositions());

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_EncTimes.CloseCursor();
    EndWaitCursor();
    if (m_List1.GetItemCount() == 0)
    {
        MsgBoxOK(IDP_NO_DATA);
    }
    else
    {
        GetDlgItem(IDC_BUTTON_COPY)->EnableWindow();
        GetDlgItem(IDC_BUTTON_COPY)->ShowWindow(SW_SHOW);
    }
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);
}

// CDEncloserUpd-Dialogfeld

IMPLEMENT_DYNAMIC(CDEncloserUpd, CDialog)
CDEncloserUpd::CDEncloserUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDEncloserUpd::IDD, pParent)
    , m_cDiff(_T(""))
    , m_cMax(_T(""))
{
    m_bUpdate = FALSE;
}

CDEncloserUpd::~CDEncloserUpd()
{
}

void CDEncloserUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_DIFF, m_cDiff);
    DDX_Text(pDX, IDC_EDIT_MAX, m_cMax);
    DDX_Control(pDX, IDC_EDIT_DIFF, m_edit_Diff);
    DDX_Control(pDX, IDC_EDIT_MAX, m_edit_Max);
}


BEGIN_MESSAGE_MAP(CDEncloserUpd, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDEncloserUpd-Meldungshandler

BOOL CDEncloserUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CString CStr;
    CStr = CResString::ex().getStrTblText(m_bUpdate ? AETXT_ENCLOSER_UPDATE : AETXT_ENCLOSER_INSERT);
    this->SetWindowText(CStr);
    if (m_bUpdate)
    {
        GetDlgItem(IDC_EDIT_DIFF)->EnableWindow(FALSE);
    }

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDEncloserUpd::OnBnClickedOk()
{
    UpdateData();
    if (m_cDiff.IsEmpty())
    {
        MsgBoxOK(AETXT_DIFF_INPUT);
        m_edit_Diff.SetFocus();
        m_edit_Diff.SetSel(0, -1, FALSE);
        return;
    }
    if (m_cMax.IsEmpty())
    {
        MsgBoxOK(AETXT_MAX_INPUT);
        m_edit_Max.SetFocus();
        m_edit_Max.SetSel(0, -1, FALSE);
        return;
    }
    CDialogMultiLang::OnOK();
}
