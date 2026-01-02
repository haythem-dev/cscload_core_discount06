// dauftxt.cpp : implementation file
//

#include "stdafx.h"
#include "DAufTxt.h"
#include "usertexte.h"

#define MAX_TEXTE_DEL 300

/////////////////////////////////////////////////////////////////////////////
// CDAufTxt dialog


CDAufTxt::CDAufTxt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAufTxt::IDD, pParent)
{
    m_CKopf = _T("");
    m_CFuss = _T("");
    m_bInfoOrder        = FALSE;
    m_bSeraNachBearb    = FALSE;
    m_ldatum            = 0;
}


void CDAufTxt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FUSS, m_ComboFuss);
    DDX_Control(pDX, IDC_COMBO_KOPF, m_ComboKopf);
    DDX_Control(pDX, IDC_LIST_KOPF, m_ListKopf);
    DDX_Control(pDX, IDC_LIST_FUSS, m_ListFuss);
    DDX_CBString(pDX, IDC_COMBO_KOPF, m_CKopf);
    DDX_CBString(pDX, IDC_COMBO_FUSS, m_CFuss);
}


BEGIN_MESSAGE_MAP(CDAufTxt, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_DEL_FUSS, OnButtonDelFuss)
    ON_BN_CLICKED(IDC_BUTTON_DEL_KOPF, OnButtonDelKopf)
    ON_BN_CLICKED(IDC_BUTTON_INS_FUSS, OnButtonInsFuss)
    ON_BN_CLICKED(IDC_BUTTON_INS_KOPF, OnButtonInsKopf)
    ON_CBN_EDITCHANGE(IDC_COMBO_FUSS, OnEditchangeComboFuss)
    ON_CBN_EDITCHANGE(IDC_COMBO_KOPF, OnEditchangeComboKopf)
    ON_LBN_DBLCLK(IDC_LIST_FUSS, OnDblclkListFuss)
    ON_LBN_DBLCLK(IDC_LIST_KOPF, OnDblclkListKopf)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDAufTxt message handlers

void CDAufTxt::OnOK()
{
    CAUFTEXTE auftexte;
    CString Kopf, Fuss;
    GetDlgItem(IDC_COMBO_KOPF)->GetWindowText(Kopf);
    GetDlgItem(IDC_COMBO_FUSS)->GetWindowText(Fuss);
    AllgStrCopy(auftexte.s.BEMERKUNGEN, Kopf, L_AUFTEXTE_BEMERKUNGEN);
    AllgEntfSpaces(auftexte.s.BEMERKUNGEN);
    if (auftexte.s.BEMERKUNGEN[0] != '\0')
    {
        auftexte.s.BEMERKUNGSART = AUF_TEXT_KOPF,
        auftexte.Server(AasrvInsKopfZlnAuf, PIPE_AE_SRV);
    }
    AllgStrCopy(auftexte.s.BEMERKUNGEN, Fuss, L_AUFTEXTE_BEMERKUNGEN);
    AllgEntfSpaces(auftexte.s.BEMERKUNGEN);
    if (auftexte.s.BEMERKUNGEN[0] != '\0')
    {
        auftexte.s.BEMERKUNGSART = AUF_TEXT_FUSS,
        auftexte.Server(AasrvInsKopfZlnAuf, PIPE_AE_SRV);
    }
    GetDlgItem(IDC_COMBO_KOPF)->SetWindowText("");
    GetDlgItem(IDC_COMBO_FUSS)->SetWindowText("");
    UpdateLists();
}

BOOL CDAufTxt::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    int AnzEintraege = UpdateLists();

    // Bei Sera-Nachbearbeitung nur Anzeigen, wenn Eintraege
    // vorhanden sind ( Satzart 06 Freitext 256 Zeichen )
    if (m_bSeraNachBearb && !AnzEintraege)
    {
        OnCancel();
        return FALSE;
    }

    //  Standard-texte in Comboboxen
    CUSERTEXTV txt;
    txt.s.UID = -1;
    txt.s.TEXTART = 1;
    txt.s.FETCH_REL = 1;
    BeginWaitCursor();
    for (;;)
    {
        txt.Server(AafilSel_usertext);
        if (txt.rc == SRV_SQLNOTFOUND)
            break;
        //Ausgabe in die Comboboxen
        AllgEntfSpaces(txt.s.TEXT);
        m_ComboKopf.AddString(txt.s.TEXT);
    }
    txt.s.FETCH_REL = 0;        // close Cursor
    txt.Server(AafilSel_usertext);
    txt.s.UID = -1;
    txt.s.TEXTART = 2;
    txt.s.FETCH_REL = 1;
    for (;;)
    {
        txt.Server(AafilSel_usertext);
        if (txt.rc == SRV_SQLNOTFOUND)
            break;
        //Ausgabe in die Comboboxen
        AllgEntfSpaces(txt.s.TEXT);
        m_ComboFuss.AddString(txt.s.TEXT);
    }
    txt.s.FETCH_REL = 0;        // close Cursor
    txt.Server(AafilSel_usertext);
    txt.s.UID = GetAeUser().GetUID();
    txt.s.TEXTART = 1;
    txt.s.FETCH_REL = 1;
    BeginWaitCursor();
    for (;;)
    {
        txt.Server(AafilSel_usertext);
        if (txt.rc == SRV_SQLNOTFOUND)
            break;
        //Ausgabe in die Comboboxen
        AllgEntfSpaces(txt.s.TEXT);
        m_ComboKopf.AddString(txt.s.TEXT);
    }
    txt.s.FETCH_REL = 0;        // close Cursor
    txt.Server(AafilSel_usertext);
    txt.s.UID = GetAeUser().GetUID();
    txt.s.TEXTART = 2;
    txt.s.FETCH_REL = 1;
    for (;;)
    {
        txt.Server(AafilSel_usertext);
        if (txt.rc == SRV_SQLNOTFOUND)
            break;
        //Ausgabe in die Comboboxen
        AllgEntfSpaces(txt.s.TEXT);
        m_ComboFuss.AddString(txt.s.TEXT);
    }
    txt.s.FETCH_REL = 0;        // close Cursor
    txt.Server(AafilSel_usertext);
    EndWaitCursor();

    m_ListKopf.SetHorizontalExtent(2048);
    if (m_bInfoOrder)
    {
        GotoDlgCtrl(GetDlgItem(IDCANCEL));
        SetWindowText(CResString::ex().getStrTblText(AETXT_KUF_ANZ));
        GetDlgItem(IDC_COMBO_KOPF)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_FUSS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_INS_KOPF)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_INS_FUSS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_DEL_KOPF)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_DEL_FUSS)->EnableWindow(FALSE);
        GetDlgItem(IDOK)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(FALSE);
        return FALSE;
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

int CDAufTxt::UpdateLists(bool bWithOutput)
{
    CAUFTEXTE auftexte;
    int AnzEintraege = 0;
    auftexte.s.BEMERKUNGSART = m_bInfoOrder ? AUF_TEXT_KOPF_INFO : AUF_TEXT_KOPF;
    if (bWithOutput)
        m_ListKopf.ResetContent();
    auftexte.s.FETCH_REL = 1;
    for (;;)
    {
        if (m_ldatum == 0)
            auftexte.Server(AasrvSelKopfZlnAuf, PIPE_AE_SRV);
        else
            auftexte.Server(AaauftSel_alt_kopf);
        if (auftexte.rc != SRV_OK)
            break;
        ++AnzEintraege;
        AllgEntfSpaces(auftexte.s.BEMERKUNGEN);
        if (bWithOutput)
            m_ListKopf.AddString(auftexte.s.BEMERKUNGEN);
    }
    if (m_ldatum != 0)
    {
        auftexte.s.FETCH_REL = 0;
        auftexte.Server(AaauftSel_alt_kopf);
    }
    auftexte.s.BEMERKUNGSART = m_bInfoOrder ? AUF_TEXT_FUSS_INFO : AUF_TEXT_FUSS;

    if (bWithOutput)
        m_ListFuss.ResetContent();
    auftexte.s.FETCH_REL = 1;
    for (;;)
    {
        if (m_ldatum == 0)
            auftexte.Server(AasrvSelKopfZlnAuf, PIPE_AE_SRV);
        else
            auftexte.Server(AaauftSel_alt_kopf);
        if (auftexte.rc != SRV_OK)
            break;
        ++AnzEintraege;
        AllgEntfSpaces(auftexte.s.BEMERKUNGEN);
        if (bWithOutput)
            m_ListFuss.AddString(auftexte.s.BEMERKUNGEN);
    }
    if (m_ldatum != 0)
    {
        auftexte.s.FETCH_REL = 0;
        auftexte.Server(AaauftSel_alt_kopf);
    }
    AeGetApp()->AnzKopfFuss = AnzEintraege;
    return AnzEintraege;
}

void CDAufTxt::OnButtonDel()
{
    int buf[MAX_TEXTE_DEL];
    if (m_ListKopf.GetSelCount() > MAX_TEXTE_DEL || m_ListFuss.GetSelCount() > MAX_TEXTE_DEL)
    {
        MsgBoxOK(IDP_NO_MORE_SEL);
        return;
    }
    int anz = m_ListKopf.GetSelItems(MAX_TEXTE_DEL, buf);
    CAUFTEXTE auftexte;
    auftexte.s.BEMERKUNGSART = AUF_TEXT_KOPF;
    for (int i = anz - 1; i > -1; i--)
    {
        auftexte.s.BEMERKUNGSNR = static_cast<short>(buf[i]);
        auftexte.Server(AasrvDelKopfZlnAuf, PIPE_AE_SRV);
    }
    anz = m_ListFuss.GetSelItems(MAX_TEXTE_DEL, buf);
    auftexte.s.BEMERKUNGSART = AUF_TEXT_FUSS;
    for (int i = anz - 1; i > -1; i--)
    {
        auftexte.s.BEMERKUNGSNR = static_cast<short>(buf[i]);
        auftexte.Server(AasrvDelKopfZlnAuf, PIPE_AE_SRV);
    }
    UpdateLists();
}

void CDAufTxt::OnButtonDelFuss()
{
    CUSERTEXTV txt;
    txt.s.UID = GetAeUser().GetUID();
    txt.s.TEXTART = 2;

    int index = m_ComboFuss.GetCurSel();
    if (index == CB_ERR)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
    else if (MsgBoxYesNo(IDP_SOLL_DEL_SATZ) == IDYES)
    {
        m_ComboFuss.GetLBText(index, txt.s.TEXT);
        txt.Server(AafilDel_usertext);
        if (txt.rc == 4)
            MsgBoxOK(IDP_NO_SEL_ZENTRAL);
        else
            m_ComboFuss.DeleteString(index);
    }
}

void CDAufTxt::OnButtonDelKopf()
{
    CUSERTEXTV txt;
    txt.s.UID = GetAeUser().GetUID();
    txt.s.TEXTART = 1;

    int index = m_ComboKopf.GetCurSel();
    if (index == CB_ERR)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
    else if (MsgBoxYesNo(IDP_SOLL_DEL_SATZ) == IDYES)
    {
        m_ComboKopf.GetLBText(index, txt.s.TEXT);
        txt.Server(AafilDel_usertext);
        if (txt.rc == 4)
            MsgBoxOK(IDP_NO_SEL_ZENTRAL);
        else
            m_ComboKopf.DeleteString(index);
    }
}

void CDAufTxt::OnButtonInsFuss()
{
    CUSERTEXTV txt;
    CString Str;
    txt.s.UID = GetAeUser().GetUID();
    txt.s.TEXTART = 2;
    m_ComboFuss.GetWindowText(Str);
    strcpy(txt.s.TEXT, Str);
    txt.Server(AafilIns_usertext);
    if (txt.rc == SRV_OK)
        AllgEntfSpaces(txt.s.TEXT);
    m_ComboFuss.AddString(txt.s.TEXT);
}

void CDAufTxt::OnButtonInsKopf()
{
    CUSERTEXTV txt;
    CString Str;
    txt.s.UID = GetAeUser().GetUID();
    txt.s.TEXTART = 1;
    m_ComboKopf.GetWindowText(Str);
    strcpy(txt.s.TEXT, Str);
    txt.Server(AafilIns_usertext);
    if (txt.rc == SRV_OK)
        AllgEntfSpaces(txt.s.TEXT);
    m_ComboKopf.AddString(txt.s.TEXT);
}

void CDAufTxt::OnEditchangeComboFuss()
{
    if (AeGetApp()->IsRS())
    {
        if (!AllgCheckPrintableSignWnd(&m_ComboFuss))
            return;
    }
    AllgLaengeKontrWnd(&m_ComboFuss, MAXIMUM_POS_BEM, AeGetApp()->Modus());
}

void CDAufTxt::OnEditchangeComboKopf()
{
    if (AeGetApp()->IsRS())
    {
        if (!AllgCheckPrintableSignWnd(&m_ComboKopf))
            return;
    }
    AllgLaengeKontrWnd(&m_ComboKopf, MAXIMUM_POS_BEM, AeGetApp()->Modus());
}


void CDAufTxt::OnDblclkListFuss()
{
    CString Str;
    int index = m_ListFuss.GetCurSel();
    m_ListFuss.GetText(index, Str);
    m_ComboFuss.SetWindowText(Str);
}

void CDAufTxt::OnDblclkListKopf()
{
    CString Str;
    int index = m_ListKopf.GetCurSel();
    m_ListKopf.GetText(index, Str);
    m_ComboKopf.SetWindowText(Str);
}
