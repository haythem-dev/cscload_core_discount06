// DAeKundeVerbundFiliale.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <kndsel.h>
#include "DKndWahl.h"
#include "DAeKundeVerbundFiliale.h"

//Definition der Tabellenbreite und der Ueberschriften

#define MAXIMUM_FOLGE   10

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 80, LVCFMT_LEFT,
    2,  "", 60, LVCFMT_LEFT,
    -1, "",  0, 0
};


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeKundeVerbundFiliale


CDAeKundeVerbundFiliale::CDAeKundeVerbundFiliale(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeKundeVerbundFiliale::IDD, pParent)
{
    m_lCustomerNo = -1;
    m_sSaleCenterNo = -1;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_FOLGE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
}


void CDAeKundeVerbundFiliale::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDAeKundeVerbundFiliale, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDAeKundeVerbundFiliale

BOOL CDAeKundeVerbundFiliale::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();
    SelKunde();
    if (GetKundenNr() == -1)
    {
        CDialogMultiLang::OnCancel();
        return IDCANCEL;
    }

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    SetHeader();
    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDAeKundeVerbundFiliale::OnButtonChange()
{
    if (SelKunde())
    {
        SetHeader();
        GetPage();
    }
}

void CDAeKundeVerbundFiliale::OnButtonUpdate()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDAeKundeVerbundFilialeUpd upd;
        upd.SetFunktion(1);     //Update
        upd.SetKundenNr(GetKundenNr());
        upd.SetVbFiliale(static_cast<short>( atoi(m_ListCtl.GetItemText(pos, 2))) );
        upd.SetFolge(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 1))) );
        if (upd.DoModal() == IDOK)
        {
            if (upd.GetFolge() == atoi(m_ListCtl.GetItemText(pos, 1)))
                return;
            m_DkVbFil.SetVertriebszentrumnr(GetVzNr());
            m_DkVbFil.SetKundennr(GetKundenNr());
            m_DkVbFil.SetReihenfolgenr(upd.GetFolge());
            m_DkVbFil.SetVerbundfilialnr(upd.GetVbFiliale());
            MsgBoxOK(m_DkVbFil.Update() == 0 ? IDP_UPDATED : IDP_NOT_UPDATED);
            GetPage();
        }
    }
}

void CDAeKundeVerbundFiliale::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonUpdate();

    *pResult = 0L;
}

void CDAeKundeVerbundFiliale::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        OnButtonUpdate();
        return;
    }
    CDialogMultiLang::OnOK();
}

void CDAeKundeVerbundFiliale::GetPage()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_DkVbFil.SetVertriebszentrumnr(GetVzNr());
    m_DkVbFil.SetKundennr(GetKundenNr());
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_DkVbFil.Sel() != 0)
            break;
        s[0] = kb.Next();
        s[1].Format("%d", m_DkVbFil.GetReihenfolgenr());
        s[2].Format("%d", m_DkVbFil.GetVerbundfilialnr());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
    m_DkVbFil.CloseCursor();
    EndWaitCursor();
}

void CDAeKundeVerbundFiliale::SetHeader()
{
    CKNDINF kndinf;
    char text[81];
    kndinf.s.KUNDENNR           = m_lCustomerNo;
    kndinf.s.VERTRIEBSZENTRUMNR = m_sSaleCenterNo;
    BeginWaitCursor();
    kndinf.Server(AakundeSel_knd_info);
    EndWaitCursor();
    GetDlgItem(IDC_OUT_CUSTOMERNAME)->SetWindowText(kndinf.s.NAMEINHABER);
    AllgEntfFirstSpaces(kndinf.s.POSTLEITZAHL);
    GetDlgItem(IDC_OUT_ZIPCODE)->SetWindowText(kndinf.s.POSTLEITZAHL);
    sprintf(text, "%ld", kndinf.s.IDFNR);
    GetDlgItem(IDC_OUT_CUSTOMERID)->SetWindowText(text);
    GetDlgItem(IDC_OUT_PHARMACY)->SetWindowText(kndinf.s.NAMEAPO);
    GetDlgItem(IDC_OUT_STREET)->SetWindowText(kndinf.s.STRASSE);
    GetDlgItem(IDC_OUT_CITY)->SetWindowText(kndinf.s.ORT);
    GetDlgItem(IDC_OUT_TEL)->SetWindowText(kndinf.s.TELNR);
    sprintf(text, "%ld", kndinf.s.VERTRIEBSZENTRUMNR);
    GetDlgItem(IDC_OUT_SALECENTER)->SetWindowText(text);
}

bool CDAeKundeVerbundFiliale::SelKunde()
{
    //Definition Kunde
    CDKndWahl dlgKndWahl;
    dlgKndWahl.SetEnableAeGesperrt();    // Checkbutton muß enabled werden
    if (dlgKndWahl.DoModal() == IDOK)
    {
        SetVzNr(dlgKndWahl.GetKndVz());
        SetKundenNr(dlgKndWahl.GetKndNr());
        return true;
    }
    return false;
}

void CDAeKundeVerbundFiliale::OnButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            m_DkVbFil.SetVertriebszentrumnr(GetVzNr());
            m_DkVbFil.SetKundennr(GetKundenNr());
            m_DkVbFil.SetReihenfolgenr(atoi(m_ListCtl.GetItemText(pos, 1)));
            m_DkVbFil.SetVerbundfilialnr(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 2))));
            MsgBoxOK(m_DkVbFil.Delete() == 0 ? IDP_DELETED : IDP_NOT_DELETED);
            GetPage();
        }
    }
}

void CDAeKundeVerbundFiliale::OnButtonInsert()
{
    CDAeKundeVerbundFilialeUpd upd;
    upd.SetFunktion(0);
    upd.SetKundenNr(GetKundenNr());
    upd.SetVbFiliale(0);
    upd.SetFolge(0);
    if (upd.DoModal() == IDOK)
    {
        m_DkVbFil.SetVertriebszentrumnr(GetVzNr());
        m_DkVbFil.SetKundennr(GetKundenNr());
        m_DkVbFil.SetReihenfolgenr(upd.GetFolge());
        m_DkVbFil.SetVerbundfilialnr(upd.GetVbFiliale());
        MsgBoxOK(m_DkVbFil.Insert() == 0 ? IDP_NEUANLAGE : IDP_DOPPELT);
        GetPage();
    }
}
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeKundeVerbundFilialeUpd


CDAeKundeVerbundFilialeUpd::CDAeKundeVerbundFilialeUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeKundeVerbundFilialeUpd::IDD, pParent)
    , m_cStaticKunde(_T(""))
{
    m_cHeader.Empty();
}


void CDAeKundeVerbundFilialeUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_VB_FILIALE, m_edit_VbFiliale);
    DDX_Control(pDX, IDC_EDIT_KDNR, m_edit_KdNr);
    DDX_Control(pDX, IDC_EDIT_FOLGE, m_edit_Folge);
    DDX_Text(pDX, IDC_STATIC_KUNDE, m_cStaticKunde);
}


BEGIN_MESSAGE_MAP(CDAeKundeVerbundFilialeUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_FOLGE, OnChangeEditFolge)
    ON_EN_CHANGE(IDC_EDIT_KDNR, OnChangeEditKdnr)
    ON_EN_CHANGE(IDC_EDIT_VB_FILIALE, OnChangeEditVbFiliale)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDAeKundeVerbundFilialeUpd

BOOL CDAeKundeVerbundFilialeUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    char text[81];

    if (!m_cHeader.IsEmpty())
    {
        SetWindowText(m_cHeader);
    }

    CenterWindow();
    sprintf(text,"%ld",GetKundenNr());
    GetDlgItem(IDC_EDIT_KDNR)->SetWindowText(text);
    sprintf(text,"%ld",GetVbFiliale());
    GetDlgItem(IDC_EDIT_VB_FILIALE)->SetWindowText(text);
    sprintf(text,"%ld",GetFolge());
    GetDlgItem(IDC_EDIT_FOLGE)->SetWindowText(text);
    GetDlgItem(IDC_EDIT_KDNR)->EnableWindow(FALSE);
    if (GetFunktion() == 1) //update
    {
        GetDlgItem(IDC_EDIT_VB_FILIALE)->EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDAeKundeVerbundFilialeUpd::OnChangeEditFolge()
{
    AllgWertKontr(&m_edit_Folge, MAXIMUM_FOLGE);
}

void CDAeKundeVerbundFilialeUpd::OnChangeEditKdnr()
{
    AllgWertKontr(&m_edit_KdNr, MAXIMUM_IDF);
}

void CDAeKundeVerbundFilialeUpd::OnChangeEditVbFiliale()
{
    AllgWertKontr(&m_edit_VbFiliale, MAXIMUM_FILIALNR);
}

void CDAeKundeVerbundFilialeUpd::OnOK()
{
    CString text;
    GetDlgItem(IDC_EDIT_VB_FILIALE)->GetWindowText(text);
    SetVbFiliale(static_cast<short>(atoi(text)));
    GetDlgItem(IDC_EDIT_KDNR)->GetWindowText(text);
    SetKundenNr(atol(text));
    GetDlgItem(IDC_EDIT_FOLGE)->GetWindowText(text);
    SetFolge(static_cast<short>(atoi(text)));
    CDialogMultiLang::OnOK();
}
