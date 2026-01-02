// DKritikUpd.cpp : implementation file
//

#include "stdafx.h"
#include <callback.h>
#include <kndsel.h>
#include <kritiksatz.h>
#include "DKritikUpd.h"
#include "DCallbackItem.h"
#include "DNewCallback.h"

/////////////////////////////////////////////////////////////////////////////
// CDKritikUpd dialog


CDKritikUpd::CDKritikUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDKritikUpd::IDD, pParent)
{
    m_CKundenName = _T("");
    m_CApotheke = _T("");
    m_CPlz = _T("");
    m_COrt = _T("");
    m_CStrasse = _T("");
    m_CTelefon = _T("");
    m_CKurzwahl = _T("");
    m_CIdf = _T("");
    m_CReaktion = _T("");
    m_CTitel = _T("");
    m_CDatum = _T("");
    m_CUser = _T("");
    m_CZeit = _T("");
    m_CList = _T("");
}


void CDKritikUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_REAKTION, m_EditReaktion);
    DDX_Text(pDX, IDC_KA_KUNDE_NAME, m_CKundenName);
    DDX_Text(pDX, IDC_KA_APO_NAME, m_CApotheke);
    DDX_Text(pDX, IDC_KA_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_KA_ORT, m_COrt);
    DDX_Text(pDX, IDC_KA_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_KA_TELE_NR, m_CTelefon);
    DDX_Text(pDX, IDC_KA_TELE_KW, m_CKurzwahl);
    DDX_Text(pDX, IDC_KA_IDF_NUMMER, m_CIdf);
    DDX_Text(pDX, IDC_EDIT_REAKTION, m_CReaktion);
    DDX_Text(pDX, IDC_EDIT_TITEL, m_CTitel);
    DDX_Text(pDX, IDC_STATIC_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_STATIC_USER, m_CUser);
    DDX_Text(pDX, IDC_STATIC_ZEIT, m_CZeit);
    DDX_Text(pDX, IDC_EDIT_LIST, m_CList);
    DDX_Control(pDX, IDC_COMBO_STATUS, m_ComboStatus);
    DDX_Control(pDX, IDC_EDIT_STATUS, m_EditStatus);
    DDX_Control(pDX, IDC_EDIT_REFERENCE, m_EditReference);
}


BEGIN_MESSAGE_MAP(CDKritikUpd, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BUTTON_RR, OnButtonRr)
    ON_WM_CTLCOLOR()
    ON_EN_CHANGE(IDC_EDIT_REAKTION, OnChangeEditReaktion)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDKritikUpd message handlers

BOOL CDKritikUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    char czeit[11];
    char cdatum[11];
    CKNDINF kndinf;
    CKRITIKPOS kritikpos;
    CCALLBACKITEMS callback;
    CCALLBACKPARTNER partner;
    CCALLBACKDIVISION division;
    CString ausgabe;
    ppString Name;

    kndinf.s.IDFNR = atol(m_CIdf);
    kndinf.s.KUNDENNR = atol(m_CIdf);
    kndinf.s.VERTRIEBSZENTRUMNR = m_sVzNr;
    kndinf.Server(AakundeSel_knd_info);
    if (kndinf.rc != SRV_OK)
    {
        OnCancel();
        return FALSE;
    }

    if (AeGetApp()->IsCBStatusUsed())
    {
        m_RRItem.SetCallbackno(m_lRRNr);
        m_RRItem.SelNo();
        if (m_RRItem.GetLockkz() == '1')
        {
            MsgBoxOK(IDP_CALL_IN_USE);
            CDialogMultiLang::OnCancel();
            return FALSE;
        }
        m_RRItem.SetLockkz('1');
        m_RRItem.UpdateItem();

        m_CallbackStatusManager.FillCombobox(m_ComboStatus);
        ppString strCurrentStatusName = m_CallbackStatusManager.GetStatusName(m_RRItem.GetStatusId());
        if (m_CallbackStatusManager.IsCloseStatus(m_RRItem.GetStatusId()))
        {
            m_ComboStatus.ShowWindow(SW_HIDE);
            m_EditStatus.ShowWindow(SW_SHOW);
            m_EditStatus.SetWindowText(strCurrentStatusName.c_str());
        }
        else
        {
            m_EditStatus.ShowWindow(SW_HIDE);
            m_ComboStatus.ShowWindow(SW_SHOW);
            int comboIndex = m_ComboStatus.FindStringExact(-1, strCurrentStatusName);
            if (comboIndex != CB_ERR)
            {
                m_ComboStatus.SetCurSel(comboIndex);
            }
        }
        ppString strReference;
        m_RRItem.GetReference(strReference);
        m_EditReference.SetWindowText(strReference.c_str());
    }
    else
    {
        GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
        m_EditStatus.ShowWindow(SW_HIDE);
        m_ComboStatus.ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_REFERENCE)->ShowWindow(SW_HIDE);
        m_EditReference.ShowWindow(SW_HIDE);
    }

    AllgEntfSpaces(kndinf.s.NAMEINHABER);
    m_CKundenName = kndinf.s.NAMEINHABER;
    AllgEntfSpaces(kndinf.s.POSTLEITZAHL);
    m_CPlz = kndinf.s.POSTLEITZAHL;
    AllgEntfSpaces(kndinf.s.ORT);
    m_COrt = kndinf.s.ORT;
    AllgEntfSpaces(kndinf.s.TELNR);
    m_CTelefon = kndinf.s.TELNR;
    AllgEntfSpaces(kndinf.s.NAMEAPO);
    m_CApotheke = kndinf.s.NAMEAPO;
    AllgEntfSpaces(kndinf.s.STRASSE);
    m_CStrasse = kndinf.s.STRASSE;
    AllgEntfSpaces(kndinf.s.TELKURZWAHL);
    m_CKurzwahl = kndinf.s.TELKURZWAHL;
    kritikpos.s.KRITIKNR = m_lKritiknr;
    kritikpos.s.FETCH_REL = 1;
    kritikpos.s.FILIALNR = AeGetApp()->VzNr();
    BeginWaitCursor();
    for (;;)
    {
        kritikpos.Server(AakritikSelect_pos);
        if (kritikpos.rc == SRV_SQLNOTFOUND)
            break;

        //Ausgabe in die Listboxen
        ausgabe.Empty();
        ausgabe += AllgDatumLong2CharTTMMJJJJ(kritikpos.s.DATUM, cdatum);
        ausgabe += " ";
        ausgabe += AllgZeitLong2CharHHMMSS(kritikpos.s.ZEIT, czeit);
        ausgabe += " ";
        CString username(kritikpos.s.USERNAME64);
        username.Trim();
        ausgabe += username;
        callback.SetKritiknr(kritikpos.s.KRITIKNR);
        callback.SetPosnr(kritikpos.s.POSNR);
        callback.SetKzposart(kritikpos.s.KZPOSART[0]);
        callback.SelCallbackWish();
        if (callback.rc == SRV_OK)
        {
            ausgabe += " ";
            ausgabe += CResString::ex().getStrTblText(AETXT_RUECKRUF);
            ausgabe += " ";
            ausgabe += AllgDatumLong2CharTTMMJJJJ(callback.GetCallbackdatewished(), cdatum);
            ausgabe += " ";
            ausgabe += AllgZeitLong2CharHHMM(callback.GetCallbacktimewished() * 100, czeit);
            ausgabe += " ";
            ausgabe += CResString::ex().getStrTblText(AETXT_DURCH);
            ausgabe += " ";
            if (AeGetApp()->IsNewCallback())
            {
                division.SetBranchno(m_sVzNr);
                division.SetCallbackdivisionno((short)callback.GetCallbackpartno());
                division.SelDivision();
                ausgabe += division.GetDivisionname(Name);
            }
            else
            {
                partner.SetCallbackpartno(callback.GetCallbackpartno());
                partner.SelPartner();
                ausgabe += partner.GetCallbackpartner(Name);
            }
            if (!AeGetApp()->IsCBStatusUsed())
            {
                ausgabe += "\r\n";
                ausgabe += CResString::ex().getStrTblText(AETXT_STATUS_LANG);
                ausgabe += ": ";
                ausgabe += CResString::ex().getStrTblText(callback.GetPosnr_done() == 0 ? AETXT_RR_OFFEN : AETXT_RR_ERLEDIGT);
            }
        }
        callback.CloseCursor();
        ausgabe += "\r\n";
        m_CList += ausgabe;
        AllgEntfSpaces(kritikpos.s.KRITIKTEXT);
        ausgabe = kritikpos.s.KRITIKTEXT;
        ausgabe += "\r\n";
        m_CList += ausgabe;
        m_CList += "\r\n";
    }
    kritikpos.s.FETCH_REL = 0;  // close cursor
    kritikpos.Server(AakritikSelect_pos);
    EndWaitCursor();

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDKritikUpd::OnOK()
{
    CString strKritikText;
    CKRITIKPOS kritikpos;
    short currentStatusId = -1;
    short selectedStatusId = -1;

    GetDlgItem(IDC_EDIT_REAKTION)->GetWindowText(strKritikText);

    if (AeGetApp()->IsCBStatusUsed())
    {
        currentStatusId = m_RRItem.GetStatusId();
        selectedStatusId = currentStatusId;
        int selectedIndex = m_ComboStatus.GetCurSel();
        if (selectedIndex != CB_ERR)
        {
            CString selectedText;
            m_ComboStatus.GetLBText(selectedIndex, selectedText);
            selectedStatusId = m_CallbackStatusManager.GetStatusID(selectedText);
        }

        if (strKritikText.IsEmpty())
        {
            if (currentStatusId == selectedStatusId)
            {
                MsgBoxOK(IDP_RR_NO_BEMERK);
                return;
            }
            else if (MsgBoxYesNo(IDP_RR_NO_BEMERK_STATUS) == IDNO) return;
        }
    }
    else
    {
        if (strKritikText.IsEmpty())
        {
            MsgBoxOK(IDP_RR_NO_BEMERK);
            return;
        }
    }

    if (!strKritikText.IsEmpty())
    {
        kritikpos.s.KRITIKNR = m_lKritiknr;
        kritikpos.s.KZPOSART[0] = '1';
        kritikpos.s.UID = GetAeUser().GetUID();
        kritikpos.s.FILIALNR = AeGetApp()->VzNr();
        AllgStrCopy(kritikpos.s.KRITIKTEXT, strKritikText, L_KRITIKPOS_KRITIKTEXT);
        kritikpos.Server(AakritikSchreibe_pos);
    }
    if (AeGetApp()->IsCBStatusUsed())
    {
        m_RRItem.SetLockkz('0');
        m_RRItem.SetStatusId(selectedStatusId);
        m_RRItem.UpdateItem();
    }

    CDialogMultiLang::OnOK();
}

void CDKritikUpd::OnDestroy()
{
    CDialogMultiLang::OnDestroy();

    if (AeGetApp()->IsCBStatusUsed())
    {
        m_RRItem.SetLockkz('0');
        m_RRItem.UpdateItem();
    }
}

void CDKritikUpd::OnButtonRr()
{
    CString CStr;
    if (!AeGetApp()->IsNewCallback())
    {
        CDCallbackItem dlgCallbackItem;
        GetDlgItem(IDC_EDIT_REAKTION)->GetWindowText(CStr);
        dlgCallbackItem.m_CGrund = CStr;
        GetDlgItem(IDC_EDIT_TITEL)->GetWindowText(CStr);
        dlgCallbackItem.m_CTitel = CStr;
        dlgCallbackItem.m_lKritiknr = m_lKritiknr;
        if (dlgCallbackItem.DoModal() == IDOK)
        {
            GetDlgItem(IDC_EDIT_REAKTION)->SetWindowText("");
        }
    }
    else
    {
        CDNewCallback dlgNewCallback;
        GetDlgItem(IDC_EDIT_REAKTION)->GetWindowText(CStr);
        dlgNewCallback.m_CGrund = CStr;
        GetDlgItem(IDC_EDIT_TITEL)->GetWindowText(CStr);
        dlgNewCallback.m_CTitel = CStr;
        dlgNewCallback.m_lIdf = atol(m_CIdf);
        dlgNewCallback.m_sBranchno = m_sVzNr;
        dlgNewCallback.DoModal();
    }
}

HBRUSH CDKritikUpd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_EDIT_LIST)
    {
        pDC->SetTextColor(RGB(0, 0, 0));        // schwarz
        pDC->SetBkColor(RGB(255, 255, 255));    // weiß
    }
    return hbr;
}

void CDKritikUpd::OnChangeEditReaktion()
{
    AllgLaengeKontr(&m_EditReaktion, L_KRITIKPOS_KRITIKTEXT, L_KRITIKPOS_KRITIKTEXT, AeGetApp()->Modus());
}
