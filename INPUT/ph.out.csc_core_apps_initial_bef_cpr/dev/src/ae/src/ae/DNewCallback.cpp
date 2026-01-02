// DNewCallback.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <kritiksatz.h>
#include <sendmail.h>
#include <kndsel.h>
#include "DNewCallback.h"
#include "CallbackMailLink.h"
#include "CallbackStatusManager.h"


// CDNewCallback-Dialogfeld

IMPLEMENT_DYNAMIC(CDNewCallback, CDialog)
CDNewCallback::CDNewCallback(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDNewCallback::IDD, pParent)
    , m_cDivision(_T(""))
    , m_cReason(_T(""))
{
    m_CGrund = _T("");
    m_CContact = _T("");
    m_bKundeWunsch = FALSE;
    m_lKritiknr = 0;
    m_sBranchno = 0;
    m_sAuswahl = 0;
    m_sAuswahlReason = 0;
    m_lPosNr = 0;
    m_sLevel = 0;
    m_lStartNoCallback = 0;
    m_lEndNoCallback = 100;
}

CDNewCallback::~CDNewCallback()
{
}

void CDNewCallback::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATETIMEPICKER_RR_ZEIT, m_DT_Zeit);
    DDX_Control(pDX, IDC_DATETIMEPICKER_RR_DATUM, m_DT_Datum);
    DDX_Control(pDX, IDC_EDIT_GRUND, m_EditGrund);
    DDX_Control(pDX, IDC_CHECK_KUNDE_WUNSCH, m_CBKundeWunsch);
    DDX_Text(pDX, IDC_EDIT_GRUND, m_CGrund);
    DDX_Check(pDX, IDC_CHECK_KUNDE_WUNSCH, m_bKundeWunsch);
    DDX_Text(pDX, IDC_EDIT_DIVISION, m_cDivision);
    DDX_Text(pDX, IDC_EDIT_REASON, m_cReason);
    DDX_Text(pDX, IDC_EDIT_CONTACT, m_CContact);
    DDX_Control(pDX, IDC_COMBO_RR_WISH, m_CoboxRRWish);
    DDX_Control(pDX, IDC_EDIT_CONTACT, m_EditContact);
    DDX_Control(pDX, IDC_EDIT_REFERENCE, m_EditReference);
    DDX_Control(pDX, IDC_LIST_DIVISION, m_ListCtlDivision);
    DDX_Control(pDX, IDC_LIST_REASON, m_ListCtlReason);
}


BEGIN_MESSAGE_MAP(CDNewCallback, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_GRUND, OnChangeEditGrund)
    ON_BN_CLICKED(IDC_BUTTON101, OnBnClickedButton101)
    ON_BN_CLICKED(IDC_BUTTON102, OnBnClickedButton102)
    ON_BN_CLICKED(IDC_BUTTON103, OnBnClickedButton103)
    ON_BN_CLICKED(IDC_BUTTON104, OnBnClickedButton104)
    ON_BN_CLICKED(IDC_BUTTON105, OnBnClickedButton105)
    ON_BN_CLICKED(IDC_BUTTON106, OnBnClickedButton106)
    ON_BN_CLICKED(IDC_BUTTON107, OnBnClickedButton107)
    ON_BN_CLICKED(IDC_BUTTON108, OnBnClickedButton108)
    ON_BN_CLICKED(IDC_BUTTON109, OnBnClickedButton109)
    ON_BN_CLICKED(IDC_BUTTON110, OnBnClickedButton110)
    ON_BN_CLICKED(IDC_BUTTON111, OnBnClickedButton111)
    ON_BN_CLICKED(IDC_BUTTON112, OnBnClickedButton112)
    ON_BN_CLICKED(IDC_BUTTON113, OnBnClickedButton113)
    ON_BN_CLICKED(IDC_BUTTON114, OnBnClickedButton114)
    ON_BN_CLICKED(IDC_BUTTON115, OnBnClickedButton115)
    ON_BN_CLICKED(IDC_BUTTON116, OnBnClickedButton116)
    ON_BN_CLICKED(IDC_BUTTON201, OnBnClickedButton201)
    ON_BN_CLICKED(IDC_BUTTON202, OnBnClickedButton202)
    ON_BN_CLICKED(IDC_BUTTON203, OnBnClickedButton203)
    ON_BN_CLICKED(IDC_BUTTON204, OnBnClickedButton204)
    ON_BN_CLICKED(IDC_BUTTON205, OnBnClickedButton205)
    ON_BN_CLICKED(IDC_BUTTON206, OnBnClickedButton206)
    ON_BN_CLICKED(IDC_BUTTON207, OnBnClickedButton207)
    ON_BN_CLICKED(IDC_BUTTON208, OnBnClickedButton208)
    ON_BN_CLICKED(IDC_BUTTON209, OnBnClickedButton209)
    ON_BN_CLICKED(IDC_BUTTON210, OnBnClickedButton210)
    ON_BN_CLICKED(IDC_BUTTON211, OnBnClickedButton211)
    ON_BN_CLICKED(IDC_BUTTON212, OnBnClickedButton212)
    ON_BN_CLICKED(IDC_BUTTON213, OnBnClickedButton213)
    ON_BN_CLICKED(IDC_BUTTON214, OnBnClickedButton214)
    ON_BN_CLICKED(IDC_BUTTON215, OnBnClickedButton215)
    ON_BN_CLICKED(IDC_BUTTON216, OnBnClickedButton216)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DIVISION, &CDNewCallback::OnLvnItemchangedListDivision)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REASON, &CDNewCallback::OnLvnItemchangedListReason)
    ON_BN_CLICKED(IDC_BUTTON_UNKRITISCH, &CDNewCallback::OnBnClickedButtonUnkritisch)
    ON_BN_CLICKED(IDC_BUTTON_KRITISCH, &CDNewCallback::OnBnClickedButtonKritisch)
    ON_BN_CLICKED(IDC_BUTTON_SEHR_KRITISCH, &CDNewCallback::OnBnClickedButtonSehrKritisch)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


// CDNewCallback-Meldungshandler

BOOL CDNewCallback::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    if (AeGetApp()->IsCBStatusUsed())
    {
        m_ListCtlDivision.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
        m_ListCtlReason.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
        m_ListCtlDivision.ShowWindow(SW_SHOW);
        m_ListCtlReason.ShowWindow(SW_SHOW);

        // Get the client width of each list control
        CRect rectDivision, rectReason;
        m_ListCtlDivision.GetClientRect(&rectDivision);
        m_ListCtlReason.GetClientRect(&rectReason);

        // Calculate column widths (subtracting scrollbar width)
        int scrollbarWidth = GetSystemMetrics(SM_CXVSCROLL);
        int divisionColumnWidth = rectDivision.Width() - scrollbarWidth;
        int reasonColumnWidth = rectReason.Width() - scrollbarWidth;

        // Insert columns with calculated widths
        m_ListCtlDivision.InsertColumn(0, CResString::ex().getStrTblText(AETXT_CALLBACK_DIVISION), LVCFMT_LEFT, divisionColumnWidth);
        m_ListCtlReason.InsertColumn(0, CResString::ex().getStrTblText(AETXT_CALLBACK_REASON), LVCFMT_LEFT, reasonColumnWidth);
    }
    else
    {
        m_ButtonTab1[0] = GetDlgItem(IDC_BUTTON101);
        m_ButtonTab1[1] = GetDlgItem(IDC_BUTTON102);
        m_ButtonTab1[2] = GetDlgItem(IDC_BUTTON103);
        m_ButtonTab1[3] = GetDlgItem(IDC_BUTTON104);
        m_ButtonTab1[4] = GetDlgItem(IDC_BUTTON105);
        m_ButtonTab1[5] = GetDlgItem(IDC_BUTTON106);
        m_ButtonTab1[6] = GetDlgItem(IDC_BUTTON107);
        m_ButtonTab1[7] = GetDlgItem(IDC_BUTTON108);
        m_ButtonTab1[8] = GetDlgItem(IDC_BUTTON109);
        m_ButtonTab1[9] = GetDlgItem(IDC_BUTTON110);
        m_ButtonTab1[10] = GetDlgItem(IDC_BUTTON111);
        m_ButtonTab1[11] = GetDlgItem(IDC_BUTTON112);
        m_ButtonTab1[12] = GetDlgItem(IDC_BUTTON113);
        m_ButtonTab1[13] = GetDlgItem(IDC_BUTTON114);
        m_ButtonTab1[14] = GetDlgItem(IDC_BUTTON115);
        m_ButtonTab1[15] = GetDlgItem(IDC_BUTTON116);

        m_ButtonTab2[0] = GetDlgItem(IDC_BUTTON201);
        m_ButtonTab2[1] = GetDlgItem(IDC_BUTTON202);
        m_ButtonTab2[2] = GetDlgItem(IDC_BUTTON203);
        m_ButtonTab2[3] = GetDlgItem(IDC_BUTTON204);
        m_ButtonTab2[4] = GetDlgItem(IDC_BUTTON205);
        m_ButtonTab2[5] = GetDlgItem(IDC_BUTTON206);
        m_ButtonTab2[6] = GetDlgItem(IDC_BUTTON207);
        m_ButtonTab2[7] = GetDlgItem(IDC_BUTTON208);
        m_ButtonTab2[8] = GetDlgItem(IDC_BUTTON209);
        m_ButtonTab2[9] = GetDlgItem(IDC_BUTTON210);
        m_ButtonTab2[10] = GetDlgItem(IDC_BUTTON211);
        m_ButtonTab2[11] = GetDlgItem(IDC_BUTTON212);
        m_ButtonTab2[12] = GetDlgItem(IDC_BUTTON213);
        m_ButtonTab2[13] = GetDlgItem(IDC_BUTTON214);
        m_ButtonTab2[14] = GetDlgItem(IDC_BUTTON215);
        m_ButtonTab2[15] = GetDlgItem(IDC_BUTTON216);

        GetDlgItem(IDC_STATIC_PARTNER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_GRUND)->ShowWindow(SW_SHOW);
    }

    m_CoboxRRWish.AddString(CResString::ex().getStrTblText(AETXT_WITH_RR));
    m_CoboxRRWish.AddString(CResString::ex().getStrTblText(AETXT_WITHOUT_RR));
    m_CoboxRRWish.SetCurSel(0);

    m_lStartNoCallback = AeGetApp()->StartNoCallback();
    m_lEndNoCallback = m_lStartNoCallback + 100;

    if (AeGetApp()->IsCBStatusUsed())
    {
        m_EditReference.SetLimitText(L_CALLBACKITEMS_REFERENCE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_REFERENCE)->ShowWindow(SW_HIDE);
        m_EditReference.ShowWindow(SW_HIDE);
    }

    m_division.SetBranchno(m_sBranchno);
    m_division.SetCallbackstart(m_lStartNoCallback);
    m_division.SetCallbackend(m_lEndNoCallback);
    BeginWaitCursor();
    ppString name;
    for (int i = 0;; i++)
    {
        if (m_division.SelList() != SRV_OK)
            break;
        if (AeGetApp()->IsCBStatusUsed())
        {
            m_ListCtlDivision.InsertItem(i, m_division.GetDivisionname(name));
        }
        else if (i < 16)
        {
            m_ButtonTab1[i]->EnableWindow(TRUE);
            m_ButtonTab1[i]->ShowWindow(SW_SHOW);
            m_ButtonTab1[i]->SetWindowText(m_division.GetDivisionname(name));
        }
        else break;
    }
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    CTime ctime = CTimeFromDateLongAndHour(1, zeit.s.DATUM);
    CTimeSpan y(365, 0, 0, 0);
    CTime end = ctime + y;
    m_DT_Datum.SetRange(&ctime,&end);

    CTime czeit;
//  CTimeSpan diff(0,0,1,0);    eine Minute ist zu wenig
    CTimeSpan diff(0,0,5,0);
    m_DT_Zeit.GetTime(czeit);
    CTime rufzeit = czeit + diff;
    m_DT_Zeit.SetTime(&rufzeit);
    UpdateData(FALSE);
    if (AeGetApp()->IsConcernWording())
    {
        GetDlgItem(IDC_BUTTON_KRITISCH)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_KRITISCH)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_UNKRITISCH)->SetWindowText(CResString::ex().getStrTblText(AETXT_INFORMATION));
        GetDlgItem(IDC_BUTTON_SEHR_KRITISCH)->SetWindowText(CResString::ex().getStrTblText(AETXT_REKLAMATION));
    }
    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

void CDNewCallback::OnBnClickedButton101()
{
    m_sAuswahl = 1;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton102()
{
    m_sAuswahl = 2;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton103()
{
    m_sAuswahl = 3;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton104()
{
    m_sAuswahl = 4;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton105()
{
    m_sAuswahl = 5;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton106()
{
    m_sAuswahl = 6;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton107()
{
    m_sAuswahl = 7;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton108()
{
    m_sAuswahl = 8;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton109()
{
    m_sAuswahl = 9;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton110()
{
    m_sAuswahl = 10;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton111()
{
    m_sAuswahl = 11;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton112()
{
    m_sAuswahl = 12;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton113()
{
    m_sAuswahl = 13;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton114()
{
    m_sAuswahl = 14;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton115()
{
    m_sAuswahl = 15;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton116()
{
    m_sAuswahl = 16;
    GetReasons();
}

void CDNewCallback::OnBnClickedButton201()
{
    m_sAuswahlReason = 1;
    GetDlgItem(IDC_BUTTON201)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton202()
{
    m_sAuswahlReason = 2;
    GetDlgItem(IDC_BUTTON202)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton203()
{
    m_sAuswahlReason = 3;
    GetDlgItem(IDC_BUTTON203)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton204()
{
    m_sAuswahlReason = 4;
    GetDlgItem(IDC_BUTTON204)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton205()
{
    m_sAuswahlReason = 5;
    GetDlgItem(IDC_BUTTON205)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton206()
{
    m_sAuswahlReason = 6;
    GetDlgItem(IDC_BUTTON206)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton207()
{
    m_sAuswahlReason = 7;
    GetDlgItem(IDC_BUTTON207)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton208()
{
    m_sAuswahlReason = 8;
    GetDlgItem(IDC_BUTTON208)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton209()
{
    m_sAuswahlReason = 9;
    GetDlgItem(IDC_BUTTON209)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton210()
{
    m_sAuswahlReason = 10;
    GetDlgItem(IDC_BUTTON210)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton211()
{
    m_sAuswahlReason = 11;
    GetDlgItem(IDC_BUTTON211)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton212()
{
    m_sAuswahlReason = 12;
    GetDlgItem(IDC_BUTTON212)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton213()
{
    m_sAuswahlReason = 13;
    GetDlgItem(IDC_BUTTON213)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton214()
{
    m_sAuswahlReason = 14;
    GetDlgItem(IDC_BUTTON214)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton215()
{
    m_sAuswahlReason = 15;
    GetDlgItem(IDC_BUTTON215)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::OnBnClickedButton216()
{
    m_sAuswahlReason = 16;
    GetDlgItem(IDC_BUTTON216)->GetWindowText(m_cReason);
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
}

void CDNewCallback::GetReasons()
{
    int              i = 0;
    ppString         name;
    ppString         mailadr;
    CCALLBACKREASONS reason;

    m_division.SetData(m_sAuswahl - 1);
    m_cReason.Empty();
    GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
    m_cDivision = m_division.GetDivisionname(name);
    GetDlgItem(IDC_EDIT_DIVISION)->SetWindowText(m_cDivision);

    if (AeGetApp()->IsCBStatusUsed())
    {
        m_ListCtlReason.DeleteAllItems();
    }
    else
    {
        for (i = 0; i < 16; i++)
        {
            m_ButtonTab2[i]->EnableWindow(FALSE);
            m_ButtonTab2[i]->ShowWindow(SW_HIDE);
        }
    }
    m_nurMailTab.clear();
    m_ReasonnoTab.clear();
    m_ReasonMail.RemoveAll();
    reason.SetCallbackdivisionno(m_division.GetCallbackdivisionno());
    reason.SetBranchno(m_division.GetBranchno());
    for (i = 0;; i++)
    {
        if (reason.SelList() != SRV_OK)
            break;
        if (AeGetApp()->IsCBStatusUsed())
        {
            m_ListCtlReason.InsertItem(i, reason.GetCallbackreason(name));
            m_nurMailTab.push_back(reason.GetSwonlymail());
            m_ReasonnoTab.push_back(reason.GetReasonno());
            m_ReasonMail.Add(reason.GetMailinglist(mailadr));
        }
        else if (i < 16)
        {
            m_ButtonTab2[i]->EnableWindow(TRUE);
            m_ButtonTab2[i]->ShowWindow(SW_SHOW);
            m_ButtonTab2[i]->SetWindowText(reason.GetCallbackreason(name));
            m_nurMailTab.push_back(reason.GetSwonlymail());
            m_ReasonnoTab.push_back(reason.GetReasonno());
            m_ReasonMail.Add(reason.GetMailinglist(mailadr));
        }
        else break;
    }
}

void CDNewCallback::OnChangeEditGrund()
{
    int iTextlen = L_KRITIKPOS_KRITIKTEXT - m_CoboxRRWish.GetLBTextLen(m_CoboxRRWish.GetCurSel()) - m_cReason.GetLength();
    AllgLaengeKontr(&m_EditGrund, iTextlen, L_KRITIKPOS_KRITIKTEXT, AeGetApp()->Modus());
}

void CDNewCallback::OnOK()
{
    if (m_sAuswahl == 0)
    {
        MsgBoxOK(AETXT_CHOOSE_PARTNER);
        return;
    }
    if (m_cReason.IsEmpty())
    {
        MsgBoxOK(AETXT_CHOOSE_REASON);
        return;
    }
    UpdateData();
    int selRR = m_CoboxRRWish.GetCurSel();
    if (!selRR)
    {
        if (m_CContact.IsEmpty())
        {
            MsgBoxOK(AETXT_SET_CONTACT);
            m_EditContact.SetFocus();
            m_EditContact.SetSel(0, -1, FALSE);
            return;
        }
    }
    long datum;
    long rrzeit;
    int time_ok;
    CString WochenTag;
    CString str;
    CString vonzeit;
    CString biszeit;
    CString RRWish;
    CString Freitext;

    m_division.SetData(m_sAuswahl - 1);
    BeginWaitCursor();
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    CTime czeit;
    m_DT_Zeit.GetTime(czeit);
    rrzeit = (czeit.GetHour() * 100 + czeit.GetMinute());
    CTime ctime;
    m_DT_Datum.GetTime(ctime);
    datum = (ctime.GetYear() * 10000 + ctime.GetMonth() * 100 + ctime.GetDay());
    if (zeit.s.DATUM == datum && zeit.s.ZEIT > rrzeit * 100)
    {
        MsgBoxOK(IDP_RR_IN_PAST);
        m_DT_Zeit.SetFocus();
        return;
    }
    time_ok = 0;

    m_CoboxRRWish.GetLBText(selRR,RRWish);

    if (m_lKritiknr == 0)        // nock kein Kopfsatz
    {
        CKRITIKKOPF kopf;
        kopf.s.IDFNR = m_lIdf;
        kopf.s.KUNDENNR = m_lIdf;
        kopf.s.UID = GetAeUser().GetUID();
        kopf.s.FILIALNR = AeGetApp()->VzNr();
        kopf.s.VERTRIEBSZENTRUMNR = m_sBranchno;
        AllgStrCopy(kopf.s.TITEL, m_cReason, L_KRITIKKOPF_TITEL);
        kopf.s.KRITIKLEVEL = m_sLevel;
        kopf.Server(AakritikSchreibe_kopf);
        m_lKritiknr = kopf.s.KRITIKNR;
    }
    CKRITIKPOS kritikpos;
    kritikpos.s.KRITIKNR = m_lKritiknr;
    kritikpos.s.KZPOSART[0] = '1';
    kritikpos.s.UID = GetAeUser().GetUID();
    kritikpos.s.FILIALNR = AeGetApp()->VzNr();

    Freitext.Format("%s\r\n%s: %s\r\n%s",
        RRWish.GetString(),
        CResString::ex().getStrTblText(AETXT_CONTACT).GetString(),
        m_CContact.GetString(),
        m_CGrund.GetString());
    AllgStrCopy(kritikpos.s.KRITIKTEXT, Freitext, L_KRITIKPOS_KRITIKTEXT);
    kritikpos.Server(AakritikSchreibe_pos);
    m_lPosNr = kritikpos.s.POSNR;
    m_Callbackitem.SetCallbackpartno(m_division.GetCallbackdivisionno());
    m_Callbackitem.SetKritiknr(m_lKritiknr);
    m_Callbackitem.SetPosnr(kritikpos.s.POSNR);
    m_Callbackitem.SetKzposart(kritikpos.s.KZPOSART[0]);

    CCALLBACKMAILLINK callbackMailLink;
    callbackMailLink.SetBranchno(AeGetApp()->VzNr());
    callbackMailLink.Server(AasrvCallbackGetMailLink);
    if (callbackMailLink.GetEnabled() == 1)
    {
        m_Callbackitem.SetPosnr_done(0);    //bei nur Mail Rueckruf als erledigt kennzeichnen -> gilt nicht mehr bei Web-Lösung!
    }
    else
    {
        m_Callbackitem.SetPosnr_done(m_nurMailTab[m_sAuswahlReason-1]); //bei nur Mail Rueckruf als erledigt kennzeichnen
    }
    m_Callbackitem.SetReasonno(m_ReasonnoTab[m_sAuswahlReason-1]);
    m_Callbackitem.SetCallbacktimewished(rrzeit);
    m_Callbackitem.SetCallbackdatewished(datum);
    m_Callbackitem.SetCallbacktime(30);
    m_Callbackitem.SetState(m_bKundeWunsch ? '1' : '0');
    if (AeGetApp()->IsCBStatusUsed())
    {
        TCHAR strRefernce[L_CALLBACKITEMS_REFERENCE + 1];
        m_EditReference.GetWindowText(strRefernce, L_CALLBACKITEMS_REFERENCE + 1);
        m_Callbackitem.SetReference(strRefernce);
        CCallbackStatusManager callbackStatusManager;
        m_Callbackitem.SetStatusId(callbackStatusManager.GetOpenStatusID());
    }
    else
    {
        m_Callbackitem.SetStatusId(0);
    }
    m_Callbackitem.SetLockkz('0');
    m_Callbackitem.InsertWithNewNo();

    //Jetzt die mail
    sendMail(RRWish);

    CDialogMultiLang::OnOK();
}

void CDNewCallback::sendMail(CString& rrWish)
{
    CString MailAdr;
    ppString hilfe;

    const int idx = m_sAuswahlReason - 1;
    const int reasonCount = static_cast<int>(m_ReasonMail.GetCount());
    if (0 <= idx && idx < reasonCount && !m_ReasonMail.GetAt(idx).IsEmpty())
    {
        MailAdr = m_ReasonMail.GetAt(idx);
    }
    else
    {
        MailAdr = m_division.GetMailinglist(hilfe);
    }

    if (!MailAdr.IsEmpty())
    {
        CSENDMAIL smail;
        smail.ClearStruct();
        smail.SetBranchno(m_sBranchno);
        smail.SetMailinglist(MailAdr.GetString());
        smail.SetMailtext(getMailText(rrWish).GetString());
        smail.SetMailsubject(getMailSubject().GetString());
        if (m_sBranchno == 21)
        {
            smail.SetEmailadresse("ae@hagedastumpf.de");
        }
        else
        {
            smail.SetEmailadresse("ae@phoenixgroup.eu");
        }
        smail.Server(AasrvSendEMail, PIPE_AE_SRV);
    }
}

CString CDNewCallback::getMailSubject()
{
    CString critLevel = CResString::ex().getStrTblText(AETXT_CRITLEVEL_0 + m_sLevel);
    CString mailSubject;
    mailSubject.Format("%s: %s/%s", critLevel.GetString(), m_cDivision.GetString(), m_cReason.GetString());
    return mailSubject;
}

CString CDNewCallback::getMailText(CString& rrWish)
{
    CString username = GetAeUser().GetUserName();

    CKNDINF knd;
    knd.s.IDFNR = m_lIdf;
    knd.s.KUNDENNR = m_lIdf;
    knd.s.VERTRIEBSZENTRUMNR = m_sBranchno;
    knd.Server(AakundeSel_knd_info);

    CString text = formatMailText(knd, username, rrWish);

    short branchNoMail = AeGetApp()->VzNr();
    CCALLBACKMAILLINK callbackMailLink;
    callbackMailLink.SetBranchno(branchNoMail);
    callbackMailLink.Server(AasrvCallbackGetMailLink);
    if (callbackMailLink.GetEnabled() == 1)
    {
        CString maillink;
        ppString hilfe;
        maillink.Format("<%s?callbackno=%d&branchno=%d>", callbackMailLink.GetWebsitebaseurl(hilfe), m_Callbackitem.GetCallbackno(), branchNoMail);
        text.AppendFormat("\n\n%s: %s", CResString::ex().getStrTblText(AETXT_CALLBACK_LINK).GetString(), maillink.GetString());
    }

    if (!m_CGrund.IsEmpty())
    {
        text.AppendFormat("\n\n%s:\n%s", CResString::ex().getStrTblText(AETXT_ZUSATZ_INFO).GetString(), m_CGrund.GetString());
    }

    if (text.GetLength() > L_SENDMAIL_MAILTEXT)
    {
        text = text.Left(L_SENDMAIL_MAILTEXT - 5); // 5 = NewLine[1] + Ellipsis[3] + (last dot is deleted by SendMail - so give it another one)[1]
        text.Append("\n....");
    }
    return text;
}

CString CDNewCallback::formatMailText(CKNDINF& knd, CString& username, CString& rrWish)
{
    CString text;
    text.Format("%s %s\n%s\n\n%s\n%s %s\n%s: %s\n%s %s\n%s %s / %d\n%s: %d"
//      ,CResString::ex().getStrTblText(IDP_BITTE_RUECKRUF)
        ,CResString::ex().getStrTblText(AETXT_ERSTELLT).GetString()
        ,username.GetString()
        ,rrWish.GetString()
        ,knd.s.NAMEAPO
        ,knd.s.POSTLEITZAHL
        ,knd.s.ORT
        ,CResString::ex().getStrTblText(AETXT_CONTACT).GetString()
        ,m_CContact.GetString()
        ,CResString::ex().getStrTblText(AETXT_TELEFON).GetString()
        ,knd.s.TELNR
        ,CResString::ex().getStrTblText(AETXT_KURZWAHL).GetString()
        ,knd.s.TELKURZWAHL
        ,knd.s.FILIALNR
        ,CResString::ex().getStrTblText(AETXT_IDF_NUMMER).GetString()
        ,knd.s.IDFNR);
    return text;
}

void CDNewCallback::OnBnClickedButtonUnkritisch()
{
    m_sLevel = 0;
    OnOK();
}

void CDNewCallback::OnBnClickedButtonKritisch()
{
    m_sLevel = 1;
    OnOK();
}

void CDNewCallback::OnBnClickedButtonSehrKritisch()
{
    m_sLevel = 2;
    OnOK();
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDNewCallback::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_RETURN)
    {
        if (GetFocus() == GetDlgItem(IDC_EDIT_GRUND))
            return 0L;
        return 1L;                                  //Message wird nicht weitergeleitet
    }

    return 0L;
}

void CDNewCallback::OnLvnItemchangedListDivision(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    if (pNMLV->uChanged & LVIF_STATE)
    {
        if (pNMLV->uNewState & LVIS_SELECTED)
        {
            int nSelectedIdex = pNMLV->iItem;
            if (nSelectedIdex != -1)
            {
                m_sAuswahl = (short)nSelectedIdex + 1;
                GetReasons();
            }
        }
    }
    *pResult = FALSE;
}

void CDNewCallback::OnLvnItemchangedListReason(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    if (pNMLV->uChanged & LVIF_STATE)
    {
        if (pNMLV->uNewState & LVIS_SELECTED)
        {
            int nSelectedIdex = pNMLV->iItem;
            if (nSelectedIdex != -1)
            {
                m_sAuswahlReason = (short)nSelectedIdex + 1;
                m_cReason = m_ListCtlReason.GetItemText(nSelectedIdex, 0);
                GetDlgItem(IDC_EDIT_REASON)->SetWindowText(m_cReason);
            }
        }
    }
    *pResult = FALSE;
}
