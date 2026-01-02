// DVaVerbund.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <alterfil.h>
#include <kndsel.h>
#include <customer.h>
#include "DKndInf.h"
#include "DKndWahl.h"
#include "DVaVerbund.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  40, LVCFMT_LEFT,
    2,  "",  70, LVCFMT_LEFT,
    -1, "",   0, 0
};


// CDVaVerbund-Dialogfeld

IMPLEMENT_DYNAMIC(CDVaVerbund, CDialog)
CDVaVerbund::CDVaVerbund(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDVaVerbund::IDD, pParent)
    , m_CKundenNr(_T(""))
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
}

CDVaVerbund::~CDVaVerbund()
{
}

void CDVaVerbund::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_KUNDENNR, m_edit_KundenNr);
    DDX_Text(pDX, IDC_EDIT_KUNDENNR, m_CKundenNr);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDVaVerbund, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_KUNDENNR, OnEnChangeEditKundennr)
    ON_BN_CLICKED(IDC_BUTTON_KUNDE, OnBnClickedButtonKunde)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnBnClickedButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
    ON_NOTIFY(HDN_ITEMDBLCLICK, 0, OnHdnItemdblclickList1)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


// CDVaVerbund-Meldungshandler

BOOL CDVaVerbund::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDVaVerbund::OnEnChangeEditKundennr()
{
    CString str;

    m_edit_KundenNr.GetWindowText(str);                 //IDF lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CMC = str;
        OnBnClickedButtonKunde();
        m_CKundenNr.Format("%ld", m_lKunde);
        GetDlgItem(IDC_EDIT_KUNDENNR)->SetWindowText(m_CKundenNr);
        m_edit_KundenNr.SetFocus();
        m_edit_KundenNr.SetSel(0, -1, FALSE);
        m_edit_KundenNr.SetSel(-1, 0, FALSE);           //Selektion aufheben
        return;
    }
    AllgWertKontr(&m_edit_KundenNr, MAXIMUM_IDF);
}

void CDVaVerbund::OnBnClickedButtonKunde()
{
    CDKndWahl dlgKndWahl;
    dlgKndWahl.m_apo = m_CMC;
    BOOL bSave = GetAeUser().IsMehrVz();
    GetAeUser().SetIsMehrVz(FALSE); // nur eigenes VZ
    if (dlgKndWahl.DoModal() != IDOK)
    {
        m_lKunde = 0;
        GetAeUser().SetIsMehrVz(bSave);
        return;
    }
    GetAeUser().SetIsMehrVz(bSave);
    m_lKunde = dlgKndWahl.GetIdfNr();
    m_CKundenNr.Format("%ld", m_lKunde);
    GetDlgItem(IDC_EDIT_KUNDENNR)->SetWindowText(m_CKundenNr);
    m_CMC.Empty();
    OnBnClickedOk();
}

void CDVaVerbund::OnBnClickedOk()
{
    UpdateData();
    if (m_CKundenNr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_KUNDENNR);
        return;
    }
    m_lKunde = atol(m_CKundenNr);
    GetPage();
}

void CDVaVerbund::OnBnClickedButtonInsert()
{
    UpdateData();
    CDVaVerbundUpd upd;
    upd.m_iFunktion = 1;
    for (int pos = 0; pos < m_ListCtl.GetItemCount(); pos++)
    {
        upd.m_Filialen.Add(m_ListCtl.GetItemText(pos, 1));
    }
    if (upd.DoModal() == IDOK)
    {
        m_ShipAux.SetBranchno(AeGetApp()->VzNr());
        m_ShipAux.SetCustomerno(m_lKunde);
        m_ShipAux.SetAuxbgano(atol(upd.m_CBGA));
        m_ShipAux.SetAuxbranchno(static_cast<short>(atoi(upd.m_csFiliale)));
        if (m_ShipAux.Insert() == 0)
            GetPage();
    }
}

void CDVaVerbund::OnBnClickedButtonUpdate()
{
    UpdateData();
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDVaVerbundUpd upd;
        CString cDestBranch;
        upd.m_iFunktion = 0;
        upd.m_CBGA = m_ListCtl.GetItemText(pos, 2);
        upd.m_csFiliale = m_ListCtl.GetItemText(pos, 1);
        if (upd.DoModal() == IDOK)
        {
            m_ShipAux.SetBranchno(AeGetApp()->VzNr());
            m_ShipAux.SetCustomerno(m_lKunde);
            m_ShipAux.SetAuxbgano(atol(upd.m_CBGA));
            m_ShipAux.SetAuxbranchno(static_cast<short>(atoi(upd.m_csFiliale)));
            if (m_ShipAux.Update() == 0) GetPage();
        }
    }
}

void CDVaVerbund::OnBnClickedButtonDelete()
{
    UpdateData();
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            m_ShipAux.SetBranchno(AeGetApp()->VzNr());
            m_ShipAux.SetCustomerno(m_lKunde);
            m_ShipAux.SetAuxbgano(atol(m_ListCtl.GetItemText(pos, 1)));
            if (m_ShipAux.Delete() == 0) GetPage();
        }
    }
}

void CDVaVerbund::OnHdnItemdblclickList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedButtonUpdate();

    *pResult = 0L;
}

void CDVaVerbund::GetPage()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    m_ShipAux.SetBranchno(AeGetApp()->VzNr());
    m_ShipAux.SetCustomerno(m_lKunde);
    CLetterMan kb;
    for (int sw = 0;sw == 0;)
    {
        if (m_ShipAux.SelList() != SRV_OK) break;
        s[0] = kb.Next();
        s[1].Format("%d", m_ShipAux.GetAuxbranchno());
        s[2].Format("%d", m_ShipAux.GetAuxbgano());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_ShipAux.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}

LRESULT CDVaVerbund::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        if (m_lKunde != 0)
        {
            CKndInf dlgKndInf;
            dlgKndInf.SetIdfNr(m_lKunde);
            dlgKndInf.SetKndNr(m_lKunde);
            dlgKndInf.SetKndVz(AeGetApp()->VzNr());
            dlgKndInf.DoModal();
        }
        return 1L;
    }
    return 0L;
}

// DVaVerbund.cpp : Implementierungsdatei
//

// CDVaVerbundUpd-Dialogfeld

IMPLEMENT_DYNAMIC(CDVaVerbundUpd, CDialog)
CDVaVerbundUpd::CDVaVerbundUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDVaVerbundUpd::IDD, pParent)
    , m_CBGA(_T(""))
{
}

CDVaVerbundUpd::~CDVaVerbundUpd()
{
}

void CDVaVerbundUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FILIALE, m_combo_Filiale);
    DDX_Control(pDX, IDC_EDIT_BGA, m_edit_BGA);
    DDX_Text(pDX, IDC_EDIT_BGA, m_CBGA);
}


BEGIN_MESSAGE_MAP(CDVaVerbundUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_BGA, OnEnChangeEditBga)
    ON_CBN_SELCHANGE(IDC_COMBO_FILIALE, OnCbnSelchangeComboFiliale)
END_MESSAGE_MAP()


// CDVaVerbundUpd-Meldungshandler

BOOL CDVaVerbundUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_combo_Filiale.EnableWindow(TRUE);
    CALTFIL altfil;
    CString cDestBranch;
    int found = 0;
    BeginWaitCursor();
    altfil.s.FILIALNR = AeGetApp()->VzNr();
    altfil.s.FETCH_REL = 1;

    if (m_iFunktion == 1)   // insert
    {
        for (;;)
        {
            altfil.Server(AafilSel_altfil);
            m_bCursorOpen = true;   //Datenbankcurser offen
            altfil.s.FETCH_REL = 1;      //normaler Fetch
            if (altfil.rc == SRV_SQLNOTFOUND)
            {
                if (m_bErsterSatz)  //kein Satz gefunden
                {
                    CloseCursor();
                    EndWaitCursor();
                    return FALSE;
                }
                break;
            }
            m_bErsterSatz = false;
            found = 0;
            for (int i = 0;i < m_Filialen.GetCount();i++)
            {
                if ((atoi(m_Filialen.GetAt(i))) == altfil.s.VERBUNDFILIALNR)
                {
                    found = 1;
                    break;
                }
            }
            if (found == 1) continue;
            cDestBranch.Format("%2d", altfil.s.VERBUNDFILIALNR);
            m_combo_Filiale.AddString(cDestBranch);
        }
        int iSel;
        m_combo_Filiale.SetCurSel(0);
        iSel = m_combo_Filiale.GetCurSel();
        m_combo_Filiale.GetLBText(iSel, m_csFiliale);
        EndWaitCursor();
        CloseCursor();
    }
    else
    {
        m_combo_Filiale.AddString(m_csFiliale);
        m_combo_Filiale.SetCurSel(0);
        m_combo_Filiale.EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDVaVerbundUpd::OnEnChangeEditBga()
{
    AllgWertKontr(&m_edit_BGA, MAXIMUM_IDF);
}

void CDVaVerbundUpd::OnCbnSelchangeComboFiliale()
{
    m_combo_Filiale.GetLBText(m_combo_Filiale.GetCurSel(), m_csFiliale);
}

void CDVaVerbundUpd::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CALTFIL altfil;
    altfil.s.FETCH_REL = 0;
    BeginWaitCursor();
    altfil.Server(AafilSel_altfil);
    EndWaitCursor();
    m_bCursorOpen = false;
    m_bErsterSatz = true;
}

void CDVaVerbundUpd::OnOK()
{
    UpdateData();
    CCHECKCUSTOMEREXIST exist;
    exist.SetVertriebszentrumnr(static_cast<short>(atoi(m_csFiliale)));
    exist.SetKundennr(atol(m_CBGA));
    BeginWaitCursor();
    if (exist.SelExist())
    {
        MsgBoxOK(IDP_KEIN_KUNDE);
        EndWaitCursor();
        return;
    }
    EndWaitCursor();

    CDialogMultiLang::OnOK();
}
