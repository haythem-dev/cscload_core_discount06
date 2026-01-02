// DCallbackUpd.cpp : implementation file
//

#include "stdafx.h"
#include "AeFView.h"
#include <kndsel.h>
#include <kritiksatz.h>
#include <callback.h>
#include "DCallbackItem.h"
#include "DCallbackUpd.h"
#include "DNewCallback.h"
#include "DRrShift.h"
#include "DHPMakeCall.h"
#include "aeFax.h"
#include "DCallbackRemarkEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CDCallbackUpd dialog


CDCallbackUpd::CDCallbackUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCallbackUpd::IDD, pParent)
{
    m_CText = _T("");
    m_CGrund = _T("");
    m_CApotheke = _T("");
    m_CIdf = _T("");
    m_CInhaber = _T("");
    m_COrt = _T("");
    m_CPlz = _T("");
    m_CTel = _T("");
    m_CKw = _T("");
    m_CWertig = _T("");
    m_CFaxNr = _T("");
    m_CUser = _T("");
    m_bAuftr = FALSE;
    m_bCall = false;
    m_lRemarkno = 0;
}


void CDCallbackUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_EditText);
    DDX_Control(pDX, IDC_COMBO_CBREMARKS, m_Cobox_CBRemarks);
    DDX_Text(pDX, IDC_EDIT_TEXT, m_CText);
    DDX_Text(pDX, IDC_EDIT_GRUND, m_CGrund);
    DDX_Text(pDX, IDC_EDIT_REASON, m_Titel);
    DDX_Text(pDX, IDC_STATIC_APOTHEKE, m_CApotheke);
    DDX_Text(pDX, IDC_STATIC_IDF_NR, m_CIdf);
    DDX_Text(pDX, IDC_STATIC_INHABER, m_CInhaber);
    DDX_Text(pDX, IDC_STATIC_ORT, m_COrt);
    DDX_Text(pDX, IDC_STATIC_PLZ, m_CPlz);
    DDX_Text(pDX, IDC_STATIC_TEL, m_CTel);
    DDX_Text(pDX, IDC_STATIC_TEL_KW, m_CKw);
    DDX_Text(pDX, IDC_STATIC_WERTIG, m_CWertig);
    DDX_Text(pDX, IDC_STATIC_FAX, m_CFaxNr);
    DDX_Text(pDX, IDC_STATIC_USER, m_CUser);
    DDX_Control(pDX, IDC_STATIC_BITMAP, m_Static_Bitmap);
    DDX_Control(pDX, IDC_BUTTON_MAKE_CALL, m_CB_MakeCall);
    DDX_Control(pDX, IDC_COMBO_STATUS, m_ComboStatus);
    DDX_Control(pDX, IDC_EDIT_STATUS, m_EditStatus);
    DDX_Control(pDX, IDC_EDIT_REFERENCE, m_EditReference);
}


BEGIN_MESSAGE_MAP(CDCallbackUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
    ON_CBN_SELCHANGE(IDC_COMBO_CBREMARKS, OnCbnSelchangeComboCBRemarks)
    ON_BN_CLICKED(IDC_BUTTON_RR, OnButtonRr)
    ON_BN_CLICKED(IDC_BUTTON_SHIFT, OnButtonShift)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_BN_CLICKED(IDC_BUTTON_AUFTRAG, OnButtonAuftrag)
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BUTTON_MAKE_CALL, OnBnClickedButtonMakeCall)
    ON_BN_CLICKED(IDC_BUTTON_FAX, OnBnClickedButtonFax)
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_BUTTON_MAIL, &CDCallbackUpd::OnBnClickedButtonMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCallbackUpd message handlers

void CDCallbackUpd::OnChangeEditText()
{
    AllgLaengeKontr(&m_EditText, L_KRITIKPOS_KRITIKTEXT, L_KRITIKPOS_KRITIKTEXT, AeGetApp()->Modus());
}

void CDCallbackUpd::OnButtonRr()
{
    CString CStr;
    if (!AeGetApp()->IsNewCallback())
    {
        CDCallbackItem dlgCallbackItem;
        dlgCallbackItem.m_lIdf = m_lIdf;
        dlgCallbackItem.m_sVz = m_sVzNr;
        dlgCallbackItem.m_CTitel = m_Titel;
        GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(CStr);
        dlgCallbackItem.m_CGrund = CStr;
        if (dlgCallbackItem.DoModal() == IDOK)
        {
            m_RRItem.SetCallbackno(m_lRRNr);
            m_RRItem.SelNo();
            m_RRItem.SetPosnr_done(dlgCallbackItem.m_lPosNr);
            m_RRItem.SetLockkz('0');
            m_RRItem.UpdateItem();
            CDialogMultiLang::OnOK();
        }
    }
    else
    {
        CDNewCallback dlgNewCallback;
        dlgNewCallback.m_cReason = m_Titel;
        dlgNewCallback.m_lIdf = m_lIdf;
        dlgNewCallback.m_sBranchno = m_sVzNr;
        GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(CStr);
        dlgNewCallback.m_CGrund = CStr;
        if (dlgNewCallback.DoModal() == IDOK)
        {
            m_RRItem.SetCallbackno(m_lRRNr);
            m_RRItem.SelNo();
            m_RRItem.SetPosnr_done(dlgNewCallback.m_lPosNr);
            m_RRItem.SetLockkz('0');
            m_RRItem.UpdateItem();
            CDialogMultiLang::OnOK();
        }
    }
}

void CDCallbackUpd::OnOK()
{
    CString woher;
    woher = "CDCallbackUpd::OnOK";
    CString strKritikText;
    CKRITIKPOS kritikpos;
    short currentStatusId = -1;
    short selectedStatusId = -1;

    GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(strKritikText);
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
        AllgStrCopy(kritikpos.s.KRITIKTEXT, strKritikText, LS_KRITIKPOS_KRITIKTEXT);
        kritikpos.Server(AakritikSchreibe_pos);
        m_RRItem.SetPosnr_done(kritikpos.s.POSNR);
    }
    m_RRItem.SetLockkz('0');
    if (AeGetApp()->IsCBStatusUsed())
    {
        m_RRItem.SetStatusId(selectedStatusId);
    }
    m_RRItem.UpdateItem();

    if (!m_bAuftr)
        AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);

    CDialogMultiLang::OnOK();
}

BOOL CDCallbackUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CString woher;
    woher = "CDCallbackUpd::OnInitDialog";

    if (!AeGetApp()->m_ProCenter.IsHiPathLogon())
    {
        m_CB_MakeCall.EnableWindow(FALSE);
    }

    AeGetApp()->m_ProCenter.SetUserAtWork(woher, TRUE);
    CKNDINF kndinf;
    CKRITIK kritik;
    CString cstr;
    char text[81];
    m_RRItem.SetCallbackno(m_lRRNr);
    m_RRItem.SelNo();
    if (m_RRItem.GetLockkz() == '1')
    {
        MsgBoxOK(IDP_CALL_IN_USE);
        CDialogMultiLang::OnCancel();
        return TRUE;
    }
    m_RRItem.SetLockkz('1');
    m_RRItem.UpdateItem();

    if (AeGetApp()->IsCBStatusUsed())
    {
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

    kndinf.s.IDFNR = m_lIdf;
    kndinf.s.KUNDENNR = m_lIdf;
    kndinf.s.VERTRIEBSZENTRUMNR = m_sVzNr;
    kndinf.Server(AakundeSel_knd_info);
    sprintf(text, "%ld", kndinf.s.IDFNR);
    GetDlgItem(IDC_STATIC_IDF_NR)->SetWindowText(text);
    GetDlgItem(IDC_STATIC_WERTIG)->SetWindowText(kndinf.s.KZKDKLASSE);
    GetDlgItem(IDC_STATIC_INHABER)->SetWindowText(kndinf.s.NAMEINHABER);
    GetDlgItem(IDC_STATIC_APOTHEKE)->SetWindowText(kndinf.s.NAMEAPO);
    AllgEntfFirstSpaces(kndinf.s.POSTLEITZAHL);
    GetDlgItem(IDC_STATIC_PLZ)->SetWindowText(kndinf.s.POSTLEITZAHL);
    GetDlgItem(IDC_STATIC_ORT)->SetWindowText(kndinf.s.ORT);
    GetDlgItem(IDC_STATIC_TEL)->SetWindowText(kndinf.s.TELNR);
    m_CTel = kndinf.s.TELNR;
    AllgEntfFirstSpaces(kndinf.s.FAXNR);
    GetDlgItem(IDC_STATIC_FAX)->SetWindowText(kndinf.s.FAXNR);
    m_CFaxNr = kndinf.s.FAXNR;
    if (m_CFaxNr.IsEmpty())
        GetDlgItem(IDC_BUTTON_FAX)->EnableWindow(FALSE);
    AllgEntfFirstSpaces(kndinf.s.EMAILADRESSE);
    m_CEmail = kndinf.s.EMAILADRESSE;
    if (m_CEmail.IsEmpty())
        GetDlgItem(IDC_BUTTON_MAIL)->EnableWindow(FALSE);
    cstr.Format("%s  /  %d", kndinf.s.TELKURZWAHL, kndinf.s.FILIALNR);
    m_CStrasse = kndinf.s.STRASSE;
    ((CAeFView*)AeGetApp()->m_pViewEing)->SetOrgFilNr(kndinf.s.ORIGINALFILIALNR == 0 ? kndinf.s.VERTRIEBSZENTRUMNR : kndinf.s.ORIGINALFILIALNR);
    GetDlgItem(IDC_STATIC_TEL_KW)->SetWindowText(cstr);
    kritik.s.KRITIKNR = m_lKritiknr;
    kritik.Server(AakritikSel_kritikuser);
    if (kritik.GetKritiklevel() == 0) SetBitmap(IDB_BITMAP_INFO);
    if (kritik.GetKritiklevel() == 1) SetBitmap(IDB_BITMAP_WICHTIG);
    if (kritik.GetKritiklevel() == 2) SetBitmap(IDB_BITMAP_WARNUNG);
    GetDlgItem(IDC_STATIC_USER)->SetWindowText(kritik.s.USERNAME64);
    GetDlgItem(IDC_BUTTON_MAKE_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANRUFEN));

    if (AeGetApp()->IsNewCallback())
    {
        ppString text2;
        GetDlgItem(IDC_STATIC_REMARK2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_REMARK2)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_CBREMARKS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_COMBO_CBREMARKS)->EnableWindow(TRUE);
        for (;;)
        {
            if (m_remarks.SelList() != SRV_OK)
                break;
            m_Cobox_CBRemarks.AddString(m_remarks.GetCallbackremarkheader(text2));
        }
    }
    else
    {
        GetDlgItem(IDC_BUTTON_MAIL)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_MAIL)->ShowWindow(SW_HIDE);
    }

    if (GetAeUser().KeinPlan())
    {
        GetDlgItem(IDC_BUTTON_AUFTRAG)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_AUFTRAG)->ShowWindow(SW_HIDE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCallbackUpd::OnCancel()
{
    CString woher;
    woher = "CDCallbackUpd::OnCancel";
    m_RRItem.SetCallbackno(m_lRRNr);
    m_RRItem.SelNo();
    m_RRItem.SetLockkz('0');
    m_RRItem.UpdateItem();
    AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);
    CDialogMultiLang::OnCancel();
}

void CDCallbackUpd::OnButtonShift()
{
    CString woher;
    woher = "CDCallbackUpd::OnButtonShift";
    CDRrShift dlgRrShift;
    long Zeit, Datum;
    char error_msg[81];
    CTM actzeit;
    dlgRrShift.m_CShiftTime = "10";
    if (dlgRrShift.DoModal() != IDOK)
    {
        MsgBoxOK(IDP_RR_NOT_SHIFTED);
        return;
    }
    actzeit.Server(AafilGetdatetime);
    Zeit = actzeit.s.ZEIT;
    Datum = actzeit.s.DATUM;
    m_RRItem.SetCallbackno(m_lRRNr);
    m_RRItem.SelNo();
    if (AllgAddTimeSpan(Zeit, atol(dlgRrShift.m_CShiftTime) * 60, &Zeit) != 0)
        Datum = AllgAddDate(Datum, 1, error_msg);
    Zeit = Zeit / 100;
    if (Datum < m_RRItem.GetCallbackdatewished())
    {
        MsgBoxOK(IDP_RR_NOT_SHIFTED);
        return;
    }
    else if (Datum == m_RRItem.GetCallbackdatewished() && Zeit <= m_RRItem.GetCallbacktimewished())
    {
        MsgBoxOK(IDP_RR_NOT_SHIFTED);
        return;
    }
    m_RRItem.SetCallbacktimewished(Zeit);
    m_RRItem.SetCallbackdatewished(Datum);
    m_RRItem.SetShiftcount(m_RRItem.GetShiftcount() + 1);
    m_RRItem.SetLockkz('0');
    m_RRItem.UpdateItem();
    AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);
    CDialogMultiLang::OnOK();
}

void CDCallbackUpd::OnButtonDruck()
{
    CDruckAuftrag druckAuftrag;
    CString liste;
    CString text1;
    CString text2;
    CString text3;
    CTM zeit;
    BeginWaitCursor();
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    char underline[111];
    memset(underline, '-', 110);
    underline[110] = '\0';
    GetDlgItem(IDC_STATIC_IDF_NR)->GetWindowText(text1);
    GetDlgItem(IDC_STATIC_TEL)->GetWindowText(text2);
    liste.Format("%s %s             %s %s",
        CResString::ex().getStrTblText(AETXT_KUNDEN_NR).GetString(),
        text1.GetString(),
        CResString::ex().getStrTblText(AETXT_TELEFON).GetString(),
        text2.GetString());
    druckAuftrag.AddKopfZeile(liste);
    GetDlgItem(IDC_STATIC_INHABER)->GetWindowText(text1);
    GetDlgItem(IDC_STATIC_FAX)->GetWindowText(text2);
    liste.Format("%s: %s %s %s",
        CResString::ex().getStrTblText(AETXT_INHABER).GetString(),
        text1.GetString(),
        CResString::ex().getStrTblText(AETXT_FAX).GetString(),
        text2.GetString());
    druckAuftrag.AddKopfZeile(liste);
    GetDlgItem(IDC_STATIC_APOTHEKE)->GetWindowText(text1);
    GetDlgItem(IDC_STATIC_TEL_KW)->GetWindowText(text2);
    liste.Format("%s: %s %s: %s",
        CResString::ex().getStrTblText(AETXT_APOTHEKENNAME).GetString(),
        text1.GetString(),
        CResString::ex().getStrTblText(AETXT_KURZWAHL).GetString(),
        text2.GetString());
    druckAuftrag.AddKopfZeile(liste);
    GetDlgItem(IDC_STATIC_PLZ)->GetWindowText(text1);
    GetDlgItem(IDC_STATIC_ORT)->GetWindowText(text2);
    liste.Format("%s %s %s",
        CResString::ex().getStrTblText(AETXT_PLZ_ORT).GetString(),
        text1.GetString(),
        text2.GetString());
    druckAuftrag.AddKopfZeile(liste);
    liste = ' ';
    druckAuftrag.AddKopfZeile(liste);
    GetDlgItem(IDC_EDIT_REASON)->GetWindowText(text1);
    GetDlgItem(IDC_STATIC_USER)->GetWindowText(text2);
    liste.Format("%s: %s %s %s",
        CResString::ex().getStrTblText(AETXT_RUECKRUFGRUND).GetString(),
        text1.GetString(),
        CResString::ex().getStrTblText(AETXT_ERSTELLT).GetString(),
        text2.GetString());
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    liste = ' ';
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddFussZeile(underline);
    liste.Format("%s: %s   %s: %s",
        CResString::ex().getStrTblText(AETXT_DATUM).GetString(),
        DDMMYYYYStringFromDateLong(zeit.s.DATUM),
        CResString::ex().getStrTblText(IDS_TIME).GetString(),
        HHmmStringFromTimeLong(zeit.s.ZEIT));
    druckAuftrag.AddFussZeile(liste);
    Zeilendruck(druckAuftrag, m_CGrund);
    druckAuftrag.AddPosZeile(underline);
    liste = ' ';
    druckAuftrag.AddPosZeile(liste);
    liste = CResString::ex().getStrTblText(IDS_BEMERK);
    druckAuftrag.AddPosZeile(liste);
    druckAuftrag.AddPosZeile(underline);
    CString CStr;
    GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(CStr);
    Zeilendruck(druckAuftrag, CStr);
    druckAuftrag.Druck();
    druckAuftrag.DelAllData();
}

void CDCallbackUpd::OnButtonAuftrag()
{
    CString text1;
    GetDlgItem(IDC_STATIC_IDF_NR)->GetWindowText(text1);
    if (!((CAeFView*)AeGetApp()->m_pViewEing)->NewOrder(atol(text1), m_sVzNr))
    {
        return;
    }
    CString CStr;
    GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(CStr);
    text1.Format("%s\r\n\n%s %ld",
        CStr.GetString(),
        CResString::ex().getStrTblText(AETXT_AUFTRAG_AUF).GetString(),
        ((CAeFView*)AeGetApp()->m_pViewEing)->GetKdauftragNr());
    GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(text1);
    m_bAuftr = TRUE;
    OnOK();
}

void CDCallbackUpd::Zeilendruck(CAeOutputs& aeOutputs, CString text)
{
    CString zeile;
    CString liste;
    int len, pos, maxpos, ergebnis;
    if ((ergebnis = text.Find(CResString::ex().getStrTblText(AETXT_WITH_RR), 0)) >= 0)
    {
        zeile = text.Right(text.GetLength() - (CResString::ex().getStrTblText(AETXT_WITH_RR).GetLength() + 2));
    }
    else
    {
        zeile = text;
    }
    for (;;)
    {
        if ((len = zeile.GetLength()) == 0)
            break;
        liste.Empty();
        maxpos = (len < 80) ? len : 80;
        for (pos = 0; pos < maxpos; pos++)
        {
            if (zeile.GetAt(pos) == '\r')
            {
                liste = zeile.Left(pos);
                if (zeile.GetAt(pos + 1) == '\n')
                    ++pos;
                ++pos;
                zeile = zeile.Right(len - pos);
                aeOutputs.AddZeile(liste);
                break;
            }
        }
        if (!liste.IsEmpty())
        {
            int test;
            if ((test = liste.Find(CResString::ex().getStrTblText(AETXT_CONTACT), 0)) >= 0)
            {
                CString crlf = "\r\n";
                aeOutputs.AddZeile(crlf);
            }
            continue;
        }
        if (len <= 80)
        {
            liste = zeile;
            aeOutputs.AddZeile(liste);
            break;
        }
        for (pos = 80; pos > 0; pos--)
        {
            if (zeile.GetAt(pos) == ' ')
            {
                liste = zeile.Left(pos);
                zeile = zeile.Right(len - (++pos));
                aeOutputs.AddZeile(liste);
                break;
            }
        }
        if (pos == 0)
        {
            liste = zeile.Left(80);
            zeile = zeile.Right(len - 80);
            aeOutputs.AddZeile(liste);
        }
    }
}

HBRUSH CDCallbackUpd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEL_KW)
        pDC->SetTextColor(RGB(0, 0, 200));
    return hbr;
}

void CDCallbackUpd::OnBnClickedButtonMakeCall()
{
    if (m_bCall)
    {
        AeGetApp()->m_ProCenter.DisconnectCall();
        GetDlgItem(IDC_BUTTON_MAKE_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANRUFEN));
        m_bCall = false;
    }
    else
    {
        CString sTelNr;
        GetDlgItem(IDC_STATIC_TEL)->GetWindowText(sTelNr);
        if (sTelNr.IsEmpty())
        {
            CDHPMakeCall dlgHPMakeCall;
            if (dlgHPMakeCall.DoModal() == IDOK)
            {
                sTelNr = dlgHPMakeCall.m_csTelNr;
            }
            else
                return;
        }
        sTelNr = '0' + sTelNr;
        sTelNr.TrimRight();
        AeGetApp()->m_ProCenter.MakeCall(sTelNr);

        GetDlgItem(IDC_BUTTON_MAKE_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_AUFLEGEN));
        m_bCall = true;
    }
}

void CDCallbackUpd::OnBnClickedButtonFax()
{
    if (AeGetApp()->IsNewCallback())
    {
        if (m_lRemarkno == 0)
        {
            MsgBoxOK(CResString::ex().getStrTblText(AETXT_NO_REMARK_SEL));
        }
        else if (MsgBoxYesNo(AETXT_FAXEN) == IDYES)
        {
            NewFax();
        }
        return;
    }

    if (MsgBoxYesNo(AETXT_FAXEN) == IDNO)
        return;

    CTM zeit;
    BeginWaitCursor();
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    CString CFaxNr;
    CString CInhaber;
    CString CApo;
    CString COrt;
    CString CPlz;
    CString CStr;
    CString CLeer = " ";
    GetDlgItem(IDC_STATIC_FAX)->GetWindowText(CFaxNr);
    CFaxNr.TrimRight();
    GetDlgItem(IDC_STATIC_INHABER)->GetWindowText(CInhaber);
    GetDlgItem(IDC_STATIC_APOTHEKE)->GetWindowText(CApo);
    GetDlgItem(IDC_STATIC_ORT)->GetWindowText(COrt);
    GetDlgItem(IDC_STATIC_PLZ)->GetWindowText(CPlz);

    CAeFax fax;
    fax.m_Apo = CApo;
    fax.m_Strasse = m_CStrasse;
    fax.m_Ort = COrt;
    fax.m_PLZ = CPlz;
    fax.SetFaxNr(CFaxNr);
    fax.SetFaxName("ksc");
    fax.SetVzNr(m_sVzNr);
    fax.SetKundenNr(m_lIdf);
    fax.AddInfoText(CApo);
    fax.AddInfoText(COrt);
    CStr.Format("%s.: %s",
        CResString::ex().getStrTblText(AETXT_TEL).GetString(),
        m_CTel.GetString());
    fax.AddFreiText(CStr);
    CStr.Format("%s %s",
        CResString::ex().getStrTblText(AETXT_FAX).GetString(),
        m_CFaxNr.GetString());
    fax.AddFreiText(CStr);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    CStr.Format("%s,", CResString::ex().getStrTblText(AETXT_APOTHEKERIN).GetString());
    fax.AddFreiText(CStr);
    CStr.Format("%s,", CResString::ex().getStrTblText(AETXT_APOTHEKER).GetString());
    fax.AddFreiText(CStr);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    CStr.Format("%s %s",
        CResString::ex().getStrTblText(AETXT_ANFRAGE).GetString(),
        DDMMYYYYStringFromDateLong(zeit.s.DATUM));
    fax.AddFreiText(CStr);
    CStr = CResString::ex().getStrTblText(AETXT_ANTWORT);
    fax.AddFreiText(CStr);
    fax.AddFreiText(CLeer);
    GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(CStr);
    Zeilendruck(fax, CStr);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    CStr = CResString::ex().getStrTblText(AETXT_RUECKFRAGEN);
    fax.AddFreiText(CStr);
    fax.AddFreiText(CLeer);
    CStr = CResString::ex().getStrTblText(AETXT_MFG);
    fax.AddFreiText(CStr);
    fax.AddFreiText(CLeer);
    if (m_sVzNr == 21)
    {
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_HAGEDA).GetString());
        fax.AddFreiText(CStr);
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_KSC).GetString());
        fax.AddFreiText(CStr);
    }
    else
    {
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_KSC).GetString());
        fax.AddFreiText(CStr);
        CStr.Format("%s", AeGetApp()->Region().GetString());
        fax.AddFreiText(CStr);
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_PHOENIX).GetString());
        fax.AddFreiText(CStr);
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_AKTIE).GetString());
        fax.AddFreiText(CStr);
    }
    int rc = fax.Fax();
    if (rc != 0)
    {
        CStr.Format(CResString::ex().getStrTblText(AETXT_NO_FAX), rc, fax.m_Fehlertext.GetString());
        MsgBoxOK(CStr);
    }
    else
    {
        MsgBoxOK(AETXT_FAX_OK);
    }
}

void CDCallbackUpd::SetBitmap(const UINT id)
{
    if (m_bHasPicture)
    {
        // Need to DeleteObject() the bitmap which was loaded.
        m_Bitmap.DeleteObject();
        m_dcMem.DeleteDC();
    }
    m_Bitmap.LoadBitmap(id);
    m_Bitmap.GetObject(sizeof(BITMAP), &m_bmInfo);

    CClientDC dc(this);

    m_dcMem.CreateCompatibleDC(&dc);               // DC erzeugen
    m_dcMem.SelectObject(&m_Bitmap);

    m_bHasPicture = true;
}

void CDCallbackUpd::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (m_bHasPicture)
    {
        m_Static_Bitmap.GetClientRect(m_Rect);
        m_Static_Bitmap.ClientToScreen(m_Rect); // Convert to Dialog coordinates
        ScreenToClient(m_Rect);
        dc.BitBlt(m_Rect.left
            , m_Rect.top
            , m_bmInfo.bmWidth
            , m_bmInfo.bmHeight
            , &m_dcMem
            , 0, 0, SRCCOPY
        );
    }

    return;

    // Do not call CDialogMultiLang::OnPaint() for painting messages
}

void CDCallbackUpd::OnCbnSelchangeComboCBRemarks()
{
    ppString text;
    UpdateData();
    int pos = m_Cobox_CBRemarks.GetCurSel();
    m_remarks.SetData(pos);
    CDCallbackRemarkEdit remarkedit;
    remarkedit.m_CBHead = m_remarks.GetCallbackremarkheader(text);
    remarkedit.m_CBText = m_remarks.GetCallbackremarktext(text);
    if (m_sVzNr == 21)
        remarkedit.m_CBText.Replace(CResString::ex().getStrTblText(AETXT_PHOENIX_KURZ), CResString::ex().getStrTblText(AETXT_HAGEDA));
    remarkedit.m_CBTextFree = m_CText;  //Falls bereits was eingegeben ist
    remarkedit.m_lRemarkNo = m_remarks.GetRemarkno();
    if (remarkedit.DoModal() != IDOK)
        return;
    long lwisheddate;
    lwisheddate = m_RRItem.GetCallbackdatewished();
    CString cDatum = DDMMYYYYStringFromDateLong(lwisheddate);
    m_RemarkHead = remarkedit.m_CBHead;
    if (remarkedit.m_CBText.Find("%s"))  //Platzhalter für Datum vorhanden ?
    {
        m_RemarkText.Format(remarkedit.m_CBText, cDatum.GetString());
    }
    else
    {
        m_RemarkText = remarkedit.m_CBText;
    }
    m_RemarkTextFree = remarkedit.m_CBTextFree;
    m_lRemarkno = remarkedit.m_lRemarkNo;
    m_CText = m_RemarkTextFree;
    GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_RemarkTextFree);
}

void CDCallbackUpd::NewFax()
{
    CTM zeit;
    BeginWaitCursor();
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    CAeFax fax;
    CString CFaxNr;
    CString CInhaber;
    CString CApo;
    CString COrt;
    CString CPlz;
    CString CStr;
    CString CLeer = " ";
    GetDlgItem(IDC_STATIC_FAX)->GetWindowText(CFaxNr);
    CFaxNr.TrimRight();
    GetDlgItem(IDC_STATIC_INHABER)->GetWindowText(CInhaber);
    GetDlgItem(IDC_STATIC_APOTHEKE)->GetWindowText(CApo);
    GetDlgItem(IDC_STATIC_ORT)->GetWindowText(COrt);
    GetDlgItem(IDC_STATIC_PLZ)->GetWindowText(CPlz);
    fax.m_Apo = CApo;
    fax.m_Strasse = m_CStrasse;
    fax.m_Ort = COrt;
    fax.m_PLZ = CPlz;
    fax.SetFaxNr(CFaxNr);
    fax.SetFaxName("ksc");
    fax.SetVzNr(m_sVzNr);
    fax.SetKundenNr(m_lIdf);
    fax.AddInfoText(CApo);
    fax.AddInfoText(COrt);
    CStr.Format("%s.: %s",
        CResString::ex().getStrTblText(AETXT_TEL).GetString(),
        m_CTel.GetString());
    fax.AddFreiText(CStr);
    CStr.Format("%s %s",
        CResString::ex().getStrTblText(AETXT_FAX).GetString(),
        m_CFaxNr.GetString());
    fax.AddFreiText(CStr);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(m_RemarkHead);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    CStr.Format("%s,", CResString::ex().getStrTblText(AETXT_APOTHEKERIN).GetString());
    fax.AddFreiText(CStr);
    CStr.Format("%s,", CResString::ex().getStrTblText(AETXT_APOTHEKER).GetString());
    fax.AddFreiText(CStr);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(m_RemarkText);
    fax.AddFreiText(CLeer);
    Zeilendruck(fax, m_RemarkTextFree);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    fax.AddFreiText(CLeer);
    CStr = CResString::ex().getStrTblText(AETXT_RUECKFRAGEN);
    fax.AddFreiText(CStr);
    fax.AddFreiText(CLeer);
    CStr = CResString::ex().getStrTblText(AETXT_MFG);
    fax.AddFreiText(CStr);
    fax.AddFreiText(CLeer);
    if (m_sVzNr == 21)
    {
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_HAGEDA).GetString());
        fax.AddFreiText(CStr);
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_KSC).GetString());
        fax.AddFreiText(CStr);
    }
    else
    {
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_KSC).GetString());
        fax.AddFreiText(CStr);
        CStr.Format("%s", AeGetApp()->Region().GetString());
        fax.AddFreiText(CStr);
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_PHOENIX).GetString());
        fax.AddFreiText(CStr);
        CStr.Format("%s", CResString::ex().getStrTblText(AETXT_AKTIE).GetString());
        fax.AddFreiText(CStr);
    }
    int rc = fax.Fax();
    if (rc != 0)
    {
        CStr.Format(CResString::ex().getStrTblText(AETXT_NO_FAX), rc, fax.m_Fehlertext.GetString());
        MsgBoxOK(CStr);
    }
    else
    {
        MsgBoxOK(AETXT_FAX_OK);
    }
}

void CDCallbackUpd::OnBnClickedButtonMail()
{
    if (m_lRemarkno == 0)
    {
        MsgBoxOK(CResString::ex().getStrTblText(AETXT_NO_REMARK_SEL));
        return;
    }
    if (MsgBoxYesNo(AETXT_EMAIL) == IDNO)
        return;
    CString hilfe = CResString::ex().getStrTblText(AETXT_AKTIE);
    hilfe.Replace("&", "%26");
    CString CStr;
    if (m_sVzNr == 21)
    {
        CStr.Format("%s%%0A%s%%0A", CResString::ex().getStrTblText(AETXT_HAGEDA).GetString(),
            CResString::ex().getStrTblText(AETXT_KSC).GetString());
    }
    else
    {
        CStr.Format("%s%%0A%s%%0A%s%%0A%s%%0A", CResString::ex().getStrTblText(AETXT_KSC).GetString(),
            AeGetApp()->Region().GetString(),
            CResString::ex().getStrTblText(AETXT_PHOENIX).GetString(),
            hilfe.GetString());
    }
    CString remarktext = m_RemarkText;
    int rc = remarktext.Replace("\r", "%0A");
    CString remarkfree = m_RemarkTextFree;
    rc = remarkfree.Replace("\r", "%0A");
    CString body;
    body.Format("%s,%%0A%s%%0A%%0A%s%%0A%%0A%s%%0A%%0A%s%%0A%%0A%s%%0A%%0A%s",
        CResString::ex().getStrTblText(AETXT_APOTHEKERIN).GetString(),
        CResString::ex().getStrTblText(AETXT_APOTHEKER).GetString(),
        remarktext.GetString(),
        remarkfree.GetString(),
        CResString::ex().getStrTblText(AETXT_RUECKFRAGEN).GetString(),
        CResString::ex().getStrTblText(AETXT_MFG).GetString(),
        CStr.GetString());
    CString MailKopfDaten;
    MailKopfDaten.Format("mailto:%s?subject=%s&body=%s", m_CEmail.GetString(), m_RemarkHead.GetString(), body.GetString());

    ShellExecute(this->GetSafeHwnd(), "open", MailKopfDaten, NULL, NULL, SW_SHOW);
}

int CDCallbackUpd::WriteAttachment()
{
    CFile attachdat;
    CFileException ex;
    long datum, uhrzeit;
    datum = AllgGetDate(),
        uhrzeit = AllgGetTime();
    sprintf(filenameattach, "D:\\temp\\email.%08d.%06d.txt", datum, uhrzeit);
    if (!attachdat.Open(filenameattach, CFile::modeCreate | CFile::modeWrite, &ex))
    {
        TCHAR szError[1024];
        ex.GetErrorMessage(szError, 1024);
        _tprintf_s(_T("Couldn't open source file: %1024s"), szError);
        return false;
    }
    CString CFaxNr;
    CString CInhaber;
    CString CApo;
    CString COrt;
    CString CPlz;
    CString CStr;
    CString CLeer = "\r\n";
    GetDlgItem(IDC_STATIC_FAX)->GetWindowText(CFaxNr);
    CFaxNr.TrimRight();
    GetDlgItem(IDC_STATIC_INHABER)->GetWindowText(CInhaber);
    GetDlgItem(IDC_STATIC_APOTHEKE)->GetWindowText(CApo);
    GetDlgItem(IDC_STATIC_ORT)->GetWindowText(COrt);
    GetDlgItem(IDC_STATIC_PLZ)->GetWindowText(CPlz);
    CString CAusgabe;
    if (m_sVzNr == 21)
    {
        CAusgabe.Format("                                                             %s\r\n",
            CResString::ex().getStrTblText(AETXT_HAGEDA).GetString());
        attachdat.Write(CAusgabe, CAusgabe.GetLength());
    }
    else
    {
        CAusgabe.Format("                                                             %s\r\n",
            CResString::ex().getStrTblText(AETXT_PHOENIX).GetString());
        attachdat.Write(CAusgabe, CAusgabe.GetLength());
        CAusgabe.Format("                                                             %s\r\n",
            CResString::ex().getStrTblText(AETXT_AKTIE).GetString());
        attachdat.Write(CAusgabe, CAusgabe.GetLength());
    }
    CAusgabe.Format("%30.30s                               %s\r\n",
        CApo.GetString(),
        AeGetApp()->Region().GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe.Format("%30.30s\r\n",
        CStr.GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe.Format("\r\n%5.5s %30.30s                         %s\r\n",
        CPlz.GetString(),
        COrt.GetString(),
        AeGetApp()->VzStrasse().GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe.Format("                                                             %s %s\r\n",
        AeGetApp()->VzPLZ().Trim().GetString(),
        AeGetApp()->VzOrt().GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    if (AeGetApp()->VzTelnr().GetAt(0) == '0')
    {
        CAusgabe.Format("                                                             %s %s\r\n",
            CResString::ex().getStrTblText(AETXT_TELEFON).GetString(),
            AeGetApp()->VzTelnr().GetString());
    }
    else
    {
        CAusgabe.Format("                                                             %s %s %s\r\n",
            CResString::ex().getStrTblText(AETXT_TELEFON).GetString(),
            AeGetApp()->Vorwahl().GetString(),
            AeGetApp()->VzTelnr().GetString());
    }
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    if (AeGetApp()->VzFaxnr().GetAt(0) == '0')
    {
        CAusgabe.Format("                                                             %s %s\r\n",
            CResString::ex().getStrTblText(AETXT_FAX).GetString(),
            AeGetApp()->VzFaxnr().GetString());
    }
    else
    {
        CAusgabe.Format("                                                             %s %s %s\r\n",
            CResString::ex().getStrTblText(AETXT_FAX).GetString(),
            AeGetApp()->Vorwahl().GetString(),
            AeGetApp()->VzFaxnr().GetString());
    }
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe = "\r\n";
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe.Format("%s.: %s\r\n",
        CResString::ex().getStrTblText(AETXT_TEL).GetString(),
        m_CTel.GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe.Format("%s %s\r\n",
        CResString::ex().getStrTblText(AETXT_FAX).GetString(),
        m_CFaxNr.GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    CAusgabe.Format("%s\r\n", m_RemarkHead.GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    CAusgabe.Format("%s,\r\n", CResString::ex().getStrTblText(AETXT_APOTHEKERIN).GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    CAusgabe.Format("%s\r\n", CResString::ex().getStrTblText(AETXT_APOTHEKER).GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    CString remarktext;
    CString remarkfree;
    remarktext.Format("%s\r\n", m_RemarkText.GetString());
    remarkfree.Format("%s\r\n", m_RemarkTextFree.GetString());
    CAusgabe = remarktext;
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    CAusgabe = remarkfree;
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    CAusgabe.Format("%s\r\n", CResString::ex().getStrTblText(AETXT_RUECKFRAGEN).GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    CAusgabe.Format("%s\r\n", CResString::ex().getStrTblText(AETXT_MFG).GetString());
    attachdat.Write(CAusgabe, CAusgabe.GetLength());
    attachdat.Write(CLeer, CLeer.GetLength());
    if (m_sVzNr == 21)
    {
        CAusgabe.Format("%s\r\n", CResString::ex().getStrTblText(AETXT_HAGEDA).GetString());
        attachdat.Write(CAusgabe, CAusgabe.GetLength());
        CAusgabe.Format("%s\r\n", CResString::ex().getStrTblText(AETXT_KSC).GetString());
        attachdat.Write(CAusgabe, CAusgabe.GetLength());
    }
    else
    {
        CAusgabe.Format("%s\r\n", CResString::ex().getStrTblText(AETXT_KSC).GetString());
        attachdat.Write(CAusgabe, CAusgabe.GetLength());
        CAusgabe.Format("%s\r\n", AeGetApp()->Region().GetString());
        attachdat.Write(CAusgabe, CAusgabe.GetLength());
        CAusgabe.Format("%s\r\n", CResString::ex().getStrTblText(AETXT_PHOENIX).GetString());
        attachdat.Write(CAusgabe, CAusgabe.GetLength());
        CAusgabe.Format("%s\r\n", CResString::ex().getStrTblText(AETXT_AKTIE).GetString());
        attachdat.Write(CAusgabe, CAusgabe.GetLength());
    }
    attachdat.Close();
    return TRUE;
}
