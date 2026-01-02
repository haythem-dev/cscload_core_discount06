// DTelNr.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <kndsel.h>
#include "DKndWahl.h"
#include "DKndInf.h"
#include <customer.h>
#include "DTelNr.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     2

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "", 180, LVCFMT_LEFT,
    -1, "",   0, 0
};


// CDTelNr-Dialogfeld

IMPLEMENT_DYNAMIC(CDTelNr, CDialog)
CDTelNr::CDTelNr(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTelNr::IDD, pParent)
    , m_CKundennr(_T(""))
    , m_CVZ(_T(""))
    , m_CTelnr(_T(""))
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TELEFON_NR);
    m_lKdnr=0;
}

CDTelNr::~CDTelNr()
{
}

void CDTelNr::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_KUNDENNR, m_edit_Kundennr);
    DDX_Text(pDX, IDC_EDIT_KUNDENNR, m_CKundennr);
    DDX_Control(pDX, IDC_EDIT_VZ, m_edit_VZ);
    DDX_Text(pDX, IDC_EDIT_VZ, m_CVZ);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_EDIT_TELNR, m_edit_Telnr);
    DDX_Text(pDX, IDC_EDIT_TELNR, m_CTelnr);
}


BEGIN_MESSAGE_MAP(CDTelNr, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_INS, OnBnClickedButtonIns)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_KND_WAHL, OnBnClickedButtonKndWahl)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_EN_CHANGE(IDC_EDIT_KUNDENNR, OnEnChangeEditKundennr)
    ON_EN_CHANGE(IDC_EDIT_VZ, OnEnChangeEditVz)
    ON_EN_CHANGE(IDC_EDIT_TELNR, OnEnChangeEditTelnr)
END_MESSAGE_MAP()


// CDTelNr-Meldungshandler

void CDTelNr::OnBnClickedButtonIns()
{
    CString csTelnr;
    CString stVznr;
    CString stKdnr;
    CString csFehler;
    if (m_lKdnr == 0)
    {
        MsgBoxOK( IDP_MUSS_KUNDENNR );
        return;
    }
    m_CustPhon.SetVertriebszentrumnr(m_sVznr);
    m_CustPhon.SetKundennr(m_lKdnr);
    GetDlgItem(IDC_EDIT_TELNR)->GetWindowText(csTelnr);
    if (csTelnr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_TELNR);
        return;
    }
    m_CustPhon.SetTelnr(csTelnr);
    if (m_CustPhon.Insert() == 0)
    {
        GetPage();
    }
    else
    {
        if (m_CustPhon.SelPhoneNo() == 0)
        {
            csFehler.Format(CResString::ex().getStrTblText(AETXT_TEL_EXIST),m_CustPhon.GetKundennr());
            MsgBoxOK(csFehler);
        }
    }
}

void CDTelNr::OnBnClickedButtonDel()
{
    m_CustPhon.SetVertriebszentrumnr(m_sVznr);
    m_CustPhon.SetKundennr(m_lKdnr);
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_CustPhon.SetTelnr(m_ListCtl.GetItemText(pos, 1));
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
        return;
    }
    if (m_CustPhon.Delete() == 0)
        GetPage();
}

void CDTelNr::OnBnClickedButtonKndWahl()
{
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CString Str;
    Str.Format("%ld", dlgKndWahl.GetIdfNr());
    m_edit_Kundennr.SetWindowText(Str);
    m_edit_Kundennr.SetFocus();
    m_edit_Kundennr.SetSel(0, -1, FALSE);
    m_edit_Kundennr.SetSel(-1, 0, FALSE);       //Selektion aufheben
    OnBnClickedOk();
}

void CDTelNr::OnBnClickedOk()
{
    UpdateData(TRUE);
    CString stVznr;
    CString stKdnr;
    GetDlgItem(IDC_EDIT_KUNDENNR)->GetWindowText(stKdnr);
    GetDlgItem(IDC_EDIT_VZ)->GetWindowText(stVznr);
    if (stVznr.IsEmpty())
    {
        MsgBoxOK(IDP_VZ_REQUIRED);
        return;
    }
    if (stKdnr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_KUNDENNR);
        return;
    }
    m_lKdnr = atol(stKdnr);
    m_sVznr = static_cast<short>(atoi(stVznr));
    CKNDSEL kndsel;
    kndsel.s.SKDKUNDEAEGESPERRT[0] = '0';
    kndsel.s.SKDKUNDEAEGESPERRT[1] = '\0';
    kndsel.s.VERTRIEBSZENTRUMNR = static_cast<short>(atoi(stVznr));
    kndsel.s.KUNDENNR = atol(stKdnr);
    BeginWaitCursor();
    kndsel.Server(AakundeSel_kndnr);
    if (kndsel.rc == SRV_OK)
    {
        GetDlgItem(IDC_STATIC_APO)->SetWindowText(kndsel.s.NAMEAPO);
        GetDlgItem(IDC_STATIC_ORT)->SetWindowText(kndsel.s.ORT);
        GetDlgItem(IDC_STATIC_TEL)->SetWindowText(kndsel.s.TELKURZWAHL);
    }

    m_CustPhon.SetVertriebszentrumnr(static_cast<short>(atoi(stVznr)));
    m_CustPhon.SetKundennr(atol(stKdnr));

    GetPage();
}

BOOL CDTelNr::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    CString stVznr;
    stVznr.Format("%d", AeGetApp()->VzNr());
    GetDlgItem(IDC_EDIT_VZ)->SetWindowText(stVznr);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDTelNr::OnEnChangeEditKundennr()
{
    AllgWertKontr(&m_edit_Kundennr, MAXIMUM_IDF);
}

void CDTelNr::OnEnChangeEditVz()
{
    AllgWertKontr(&m_edit_VZ, MAXIMUM_FILIALNR);
}

void CDTelNr::OnEnChangeEditTelnr()
{
    AllgLaengeKontr(&m_edit_Telnr, L_CUSTPHON_TELNR,AeGetApp()->Modus());
}

BOOL CDTelNr::GetPage(int /*nKzUpDown*/)
{
    CStringArray s;
    ppString telnr;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    bool bErsterSatz = TRUE;
    m_CustPhon.CloseCursor();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0;; i++)
    {
        m_CustPhon.SelList();
        if (m_CustPhon.rc != SRV_OK)
        {
            if (bErsterSatz == TRUE)        //kein Satz gefunden
            {
                MsgBoxOK(IDP_NO_DATA);
                EndWaitCursor();
                return FALSE;
            }
            break;
        }
        bErsterSatz = FALSE;
        s[0] = kb.Next();
        s[1].Format("%s", m_CustPhon.GetTelnr(telnr));

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetFocusSelectedFocused(m_ListCtl, 0);
    return TRUE;
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDTelNr::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        CKndInf dlgKndInf;
        dlgKndInf.SetIdfNr(m_lKdnr);
        dlgKndInf.SetKndNr(m_lKdnr);
        dlgKndInf.SetKndVz(m_sVznr);
        dlgKndInf.DoModal();
        return 1L;
    }
    return 0L;
}
