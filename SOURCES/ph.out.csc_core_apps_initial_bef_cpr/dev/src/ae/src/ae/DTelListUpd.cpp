// DTelListUpd.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DTelListUpd.h"
#include "allg.h"
#include <artsel.h>
#include <lieferinfo.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDTelListUpd


CDTelListUpd::CDTelListUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTelListUpd::IDD, pParent)
    , m_ArtCode(_T(""))
{
    m_csAlternativ = _T("");
    m_csBemerkung = _T("");
    m_csHinweis = _T("");
    m_csName = _T("");
    m_csPZN = _T("");
}


void CDTelListUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_ZURUECK, m_ZURUECK);
    DDX_Control(pDX, IDC_BUTTON_WEITER, m_WEITER);
    DDX_Control(pDX, IDC_BUTTON_UPDATE, m_UPDATE);
    DDX_Control(pDX, IDC_BUTTON_NEW, m_NEW);
    DDX_Control(pDX, IDC_BUTTON_DELETE, m_DELETE);
    DDX_Control(pDX, IDC_EDIT_PZN, m_edit_PZN);
    DDX_Control(pDX, IDC_EDIT_NAME, m_edit_Name);
    DDX_Control(pDX, IDC_EDIT_HINWEIS, m_edit_Hinweis);
    DDX_Control(pDX, IDC_EDIT_BEMERKUNG, m_edit_Bemerkung);
    DDX_Control(pDX, IDC_EDIT_ALTERNATIV, m_edit_Alternativ);
    DDX_Control(pDX, IDC_EDIT_LIEFERINFO, m_edit_LIEFERINFO);
    DDX_Control(pDX, IDC_CHK_HERST_BLOCKED, m_CHK_LIEFER_BLOCKED);
    DDX_Control(pDX, IDC_CHK_HERST_QUALIFIED, m_CHK_LIEFER_QUALIFIED);
    DDX_Text(pDX, IDC_EDIT_ALTERNATIV, m_csAlternativ);
    DDX_Text(pDX, IDC_EDIT_BEMERKUNG, m_csBemerkung);
    DDX_Text(pDX, IDC_EDIT_HINWEIS, m_csHinweis);
    DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
    DDX_Text(pDX, IDC_EDIT_PZN, m_csPZN);
    DDX_Text(pDX, IDC_EDIT_CODE, m_ArtCode);
}


BEGIN_MESSAGE_MAP(CDTelListUpd, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_WEITER, OnButtonWeiter)
    ON_BN_CLICKED(IDC_BUTTON_ZURUECK, OnButtonZurueck)
    ON_EN_CHANGE(IDC_EDIT_ALTERNATIV, OnChangeEditAlternativ)
    ON_EN_CHANGE(IDC_EDIT_BEMERKUNG, OnChangeEditBemerkung)
    ON_EN_CHANGE(IDC_EDIT_HINWEIS, OnChangeEditHinweis)
    ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
    ON_EN_CHANGE(IDC_EDIT_PZN, OnChangeEditPzn)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_EN_KILLFOCUS(IDC_EDIT_NAME, OnKillfocusEditName)
    ON_EN_KILLFOCUS(IDC_EDIT_CODE, OnKillfocusEditPZN)
    ON_WM_DESTROY()
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDTelListUpd

BOOL CDTelListUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_WEITER.EnableWindow(FALSE);
    m_ZURUECK.EnableWindow(FALSE);
    m_DELETE.EnableWindow(FALSE);
    m_UPDATE.EnableWindow(FALSE);
    m_NEW.EnableWindow(FALSE);

    // supplier info not editable
    m_edit_LIEFERINFO.SetReadOnly(TRUE);
    // default: controls for supplier info not visible
    ShowLieferInfoControls(FALSE);

    // TODO: Zusätzliche Initialisierung hier einfügen

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDTelListUpd::OnButtonDelete()
{
    if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
    {
        BeginWaitCursor();
        m_a.Server(IftselDel_tellistt);
        EndWaitCursor();
    }
}

void CDTelListUpd::OnButtonNew()
{
    BeginWaitCursor();
    if (UpdateTelList(IftselIns_tellistt))
    {
        MsgBoxOK(IDP_INSERTED);
    }
    EndWaitCursor();
}

void CDTelListUpd::OnButtonUpdate()
{
    BeginWaitCursor();
    if (UpdateTelList(IftselUpd_tellistt))
    {
        MsgBoxOK(IDS_SET_CHANGED);
    }
    EndWaitCursor();
}

bool CDTelListUpd::UpdateTelList(int func)
{
    if (UpdateData() == FALSE)
        return false;
    if (m_csName.IsEmpty())
        return false;

    BeginWaitCursor();
    strcpy(m_a.s.BEZEICHNUNG, m_csName);
    strcpy(m_a.s.ALTERNATIV_NAME, m_csAlternativ);
    strcpy(m_a.s.DISPO_HINWEIS, m_csHinweis);
    strcpy(m_a.s.BEMERKUNG, m_csBemerkung);
    if (!m_ArtCode.IsEmpty())
    {
        if (m_csName.Left(2) == "HH")
        {
            m_a.s.PZN = atol(m_ArtCode);
        }
        else
        {
            CARTAESEL code;
            strcpy(code.s.ARTICLE_CODE, m_ArtCode);
            code.s.CODE_TYPE = 0;
            code.Server(AatartSel_NoByCode);
            if (code.rc != SRV_OK)
            {
                m_a.s.PZN = 0L;
            }
            else
            {
                m_a.s.PZN = code.s.ARTIKEL_NR;
            }
        }
    }
    else
    {
        m_a.s.PZN = 0L;
    }

    if (func == IftselIns_tellistt)
    {
        m_a.s.SATZNR = 0L;
    }

    m_a.Server(func);

    return (m_a.rc == SRV_OK);
}

void CDTelListUpd::OnButtonWeiter()
{
    // make supplier info controls visible if necessary
    ShowLieferInfoControls();

    BeginWaitCursor();
    if (LoadTelList(true))
    {
        m_ZURUECK.EnableWindow(TRUE);
    }
    else
    {
        m_WEITER.EnableWindow(FALSE);
    }
    EndWaitCursor();
    UpdateData(FALSE);
}

void CDTelListUpd::OnButtonZurueck()
{
    // make supplier info controls visible if necessary
    ShowLieferInfoControls();

    BeginWaitCursor();
    if (LoadTelList(false))
    {
        m_WEITER.EnableWindow(TRUE);
    }
    else
    {
        m_ZURUECK.EnableWindow(FALSE);
    }
    EndWaitCursor();
    UpdateData(FALSE);
}

// bNext == true  : Load next page
// bNext == false : Load previous page
bool CDTelListUpd::LoadTelList(bool bNext)
{
    m_a.s.FETCH_REL = bNext ? 1 : -1;
    m_a.Server(IftselSel_tellistt);
    if (m_a.rc != SRV_OK)
    {
        return false;
    }

    AllgEntfSpaces(m_a.s.BEZEICHNUNG);
    AllgEntfSpaces(m_a.s.ALTERNATIV_NAME);
    AllgEntfSpaces(m_a.s.DISPO_HINWEIS);
    AllgEntfSpaces(m_a.s.BEMERKUNG);
    m_csName = m_a.s.BEZEICHNUNG;
    m_csAlternativ = m_a.s.ALTERNATIV_NAME;
    m_csHinweis = m_a.s.DISPO_HINWEIS;
    m_csBemerkung = m_a.s.BEMERKUNG;
    m_csPZN.Format("%d", m_a.s.PZN);
    if (m_a.s.PZN > 0L)
    {
        if (m_csName.Left(2) == "HH")
        {
            m_ArtCode.Format("%d", m_a.s.PZN);
            // read supplier data from DB and display it
            GetLieferInfo(m_a.s.PZN);
        }
        else
        {
            CARTAESEL code;
            code.s.ARTIKEL_NR = m_a.s.PZN;
            code.Server(AatartSel_Preferred);
            AllgEntfSpaces(code.s.ARTICLE_CODE);
            m_ArtCode = code.s.ARTICLE_CODE;
        }
    }
    else
    {
        m_ArtCode.Empty();
        // delete shown supplier data
        GetLieferInfo(0L);
    }
    return true;
}

void CDTelListUpd::OnChangeEditAlternativ()
{
    AllgLaengeKontr(&m_edit_Alternativ, L_KOPLIST_ALTERNATIV_NAME, AeGetApp()->Modus());
}

void CDTelListUpd::OnChangeEditBemerkung()
{
    AllgLaengeKontr(&m_edit_Bemerkung, L_KOPLIST_BEMERKUNG, AeGetApp()->Modus());
}

void CDTelListUpd::OnChangeEditHinweis()
{
    AllgLaengeKontr(&m_edit_Hinweis, L_KOPLIST_DISPO_HINWEIS, AeGetApp()->Modus());
}

void CDTelListUpd::OnChangeEditName()
{
    m_NEW.EnableWindow(TRUE);
    AllgLaengeKontr(&m_edit_Name, L_KOPLIST_BEZEICHNUNG, AeGetApp()->Modus());
}

void CDTelListUpd::OnChangeEditPzn()
{
    AllgWertKontr(&m_edit_PZN, MAXIMUM_IDF);
}

void CDTelListUpd::OnOK()
{
    if (UpdateData() == FALSE)
        return;

    // make supplier info controls visible if necessary
    ShowLieferInfoControls();

    BeginWaitCursor();
    m_a.s.FETCH_REL = 0;
    m_a.Server(IftselSel_tellistt);

    sprintf (m_a.s.BEZEICHNUNG, "%s%%", m_csName.GetString());  //lesen ab eingegebenem suchbegriff
    m_ZURUECK.EnableWindow(FALSE);
    m_WEITER.EnableWindow(TRUE);

    if (LoadTelList(true))
    {
        m_UPDATE.EnableWindow(TRUE);
        m_DELETE.EnableWindow(TRUE);
    }
    else
    {
        m_csAlternativ = "";
        m_csHinweis = "";
        m_csBemerkung = "";
        m_csPZN = "";
        m_ArtCode.Empty();
        m_UPDATE.EnableWindow(FALSE);
        m_DELETE.EnableWindow(FALSE);
        m_WEITER.EnableWindow(FALSE);
        // delete shown supplier data
        GetLieferInfo(0);
    }
    EndWaitCursor();
    UpdateData(FALSE);
}

void CDTelListUpd::OnKillfocusEditName()
{
    // make supplier info controls visible if necessary
    ShowLieferInfoControls();

}

void CDTelListUpd::OnKillfocusEditPZN()
{
    CString name;
    CString number;

    GetDlgItemText(IDC_EDIT_NAME, name);
    GetDlgItemText(IDC_EDIT_CODE, number);

    // if we don't display a supplier/manufacturer entry,
    // there is nothing more to be done
    if (name.Left(2) != "HH")
    {
        return;
    }

    // interpret the entered number as BESLA_NR, search
    // for the corresponding supplier data and display it in
    // IDC_EDIT_LIEFERINFO and the checkboxes
    long besla_nr = atoi(number);

    GetLieferInfo(besla_nr);
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDTelListUpd::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    if (((LPMSG)lpMsg)->wParam == VK_NEXT)
    {
        if (!m_WEITER.IsWindowEnabled())
            return 1L;
        OnButtonWeiter( );
        return 1L;                                  //Message wird nicht weitergeleitet
    }
    else if (((LPMSG)lpMsg)->wParam == VK_PRIOR)
    {
        if (!m_ZURUECK.IsWindowEnabled())
            return 1L;
        OnButtonZurueck( );
        return 1L;                                  //Message wird nicht weitergeleitet
    }
    else if (((LPMSG)lpMsg)->wParam == VK_F7)
    {
        OnButtonNew( );
        return 1L;                                  //Message wird nicht weitergeleitet
    }
    else if (((LPMSG)lpMsg)->wParam == VK_F5)
    {
        OnButtonUpdate( );
        return 1L;                                  //Message wird nicht weitergeleitet
    }
    else if (((LPMSG)lpMsg)->wParam == VK_F6)
    {
        OnButtonDelete( );
        return 1L;                                  //Message wird nicht weitergeleitet
    }
    return 0L;
}

void CDTelListUpd::OnDestroy()
{
    CDialogMultiLang::OnDestroy();

    BeginWaitCursor();
    m_a.s.FETCH_REL = 0;
    m_a.Server(IftselSel_tellistt);
    EndWaitCursor();
}

void CDTelListUpd::GetLieferInfo(long besla_nr)
{
    CString strLieferInfo;
    CString strLieferBlocked = "";
    CString strLieferQualified = "";
    if (besla_nr > 0)
    {
        CLIEFERINFO lieferinfo;

        lieferinfo.s.FETCH_REL = 0;
        lieferinfo.s.BESLA_NR = besla_nr;
        lieferinfo.Server(LieferselSel_info);
        if (lieferinfo.rc == 0)
        {
            AllgEntfFirstSpaces(lieferinfo.s.BESLA_NAME);
            AllgEntfFirstSpaces(lieferinfo.s.PLZ_STRASSE);
            AllgEntfFirstSpaces(lieferinfo.s.ORT);
            AllgEntfFirstSpaces(lieferinfo.s.E_MAIL);
            AllgEntfSpaces(lieferinfo.s.BESLA_NAME);
            AllgEntfSpaces(lieferinfo.s.PLZ_STRASSE);
            AllgEntfSpaces(lieferinfo.s.ORT);
            AllgEntfSpaces(lieferinfo.s.E_MAIL);

            strLieferInfo =
                lieferinfo.s.BESLA_NAME + CString("\r\n")
                + lieferinfo.s.PLZ_STRASSE + CString(" ") + lieferinfo.s.ORT + CString("\r\n")
                + lieferinfo.s.E_MAIL;
            strLieferBlocked = lieferinfo.s.EINKAUFSVERBOT;
            strLieferQualified = "1";
            if (strcmp(lieferinfo.s.ARZNEIMITTELBEZUG, "K") == 0 || strcmp(lieferinfo.s.ARZNEIMITTELBEZUG, "N") == 0)
            {
                strLieferQualified = "0";
            }
        }
        else
        {
            CString strBeslaNr;
            strBeslaNr.Format("%d", besla_nr);
            strLieferInfo = "<keine Daten für Bestell-Lieferanten-Nr. " + strBeslaNr + ">";
        }
    }
    m_edit_LIEFERINFO.SetWindowText(strLieferInfo);
    m_CHK_LIEFER_BLOCKED.SetCheck(strLieferBlocked == "1" ? BST_CHECKED : BST_UNCHECKED);
    m_CHK_LIEFER_QUALIFIED.SetCheck(strLieferQualified == "1" ? BST_CHECKED : BST_UNCHECKED);
}

void CDTelListUpd::ShowLieferInfoControls()
{
    CString name;

    GetDlgItemText(IDC_EDIT_NAME, name);

    // if the current text in EDIT_NAME starts with "HH",
    // we are editing a supplier/manufacturer entry
    // --> show supplier info, else don't
    ShowLieferInfoControls(name.Left(2) == "HH");
}

void CDTelListUpd::ShowLieferInfoControls(BOOL fShow)
{
    GetDlgItem(IDC_STATIC_HERSTINFO)->ShowWindow(fShow);
    m_edit_LIEFERINFO.ShowWindow(fShow);
    m_CHK_LIEFER_BLOCKED.ShowWindow(fShow);
    m_CHK_LIEFER_QUALIFIED.ShowWindow(fShow);
}
