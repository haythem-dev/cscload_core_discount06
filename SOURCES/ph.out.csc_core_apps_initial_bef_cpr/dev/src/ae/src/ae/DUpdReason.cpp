// DUpdReason.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <callback.h>
#include "DUpdReason.h"
#include "DCallbackReason.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 220, LVCFMT_LEFT,
    2,  "", 240, LVCFMT_LEFT,
    3,  "",  20, LVCFMT_LEFT,
    4,  "",   0, LVCFMT_LEFT,
    5,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};


// CDUpdReason-Dialogfeld

IMPLEMENT_DYNAMIC(CDUpdReason, CDialog)
CDUpdReason::CDUpdReason(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDUpdReason::IDD, pParent)
{
    m_sPartnerNo = 0;
    m_sVzNr      = 0;
    m_new        = FALSE;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_RUECKRUFGRUND);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_EMAIL_ADR);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ONLY_MAIL);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_ONLY_MAIL);
}

CDUpdReason::~CDUpdReason()
{
}

void CDUpdReason::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_NAME, m_CName);
    DDX_Text(pDX, IDC_EDIT_MAIL_ADR, m_CMail);
}


BEGIN_MESSAGE_MAP(CDUpdReason, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_NEW_REASON, OnButtonNewreason)
    ON_BN_CLICKED(IDC_BUTTON_DEL_REASON, OnButtonDelreason)
END_MESSAGE_MAP()


// CDUpdReason-Meldungshandler

BOOL CDUpdReason::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    if (!m_new)
    {
        GetDlgItem( IDC_EDIT_NAME )->EnableWindow(FALSE);
    }

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    GetPage();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDUpdReason::GetPage(int /*nKzUpDown*/)
{
    //Variablen
    ppString reason;
    ppString mailadr;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    m_Callbackreasons.SetCallbackdivisionno(m_sPartnerNo);
    m_Callbackreasons.SetBranchno(m_sVzNr);

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_Callbackreasons.SelList() != SRV_OK) break;
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        s[1] = m_Callbackreasons.GetCallbackreason(reason);
        s[2] = m_Callbackreasons.GetMailinglist(mailadr);
        if (m_Callbackreasons.GetSwonlymail() == 1)
        {
            s[3] = (char*)CResString::ex().getStrTblText(AETXT_KZ_JA).GetString();
        }
        else
        {
            s[3] = (char*)CResString::ex().getStrTblText(AETXT_KZ_NEIN).GetString();
        }
        s[4].Format("%d", m_Callbackreasons.GetReasonno());
        s[5].Format("%d", m_Callbackreasons.GetSwonlymail());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    } //Ende der for()-Schleife
    m_Callbackreasons.CloseCursor();
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;
}

void CDUpdReason::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDUpdReason::OnOK()
{
    UpdateData();
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        SelectEintrag();
        return;
    }
    else
    {
        if (m_CName.IsEmpty())
        {
            MsgBoxOK(IDP_RR_NO_REASON);
            GetDlgItem(IDC_EDIT_NAME)->SetFocus();
            return;
        }
        CCALLBACKDIVISION Partner;
        Partner.SetBranchno(m_sVzNr);
        Partner.SetCallbackdivisionno(m_sPartnerNo);
        Partner.SetDivisionname(m_CName);
        Partner.SetMailinglist(m_CMail);
        Partner.SetCallbackstart(AeGetApp()->StartNoCallback());
        Partner.SetCallbackend(AeGetApp()->StartNoCallback() + 100);
        if (m_new)
        {
            Partner.InsertWithNewNo();
        }
        else
        {
            Partner.Update();
        }
        CDialogMultiLang::OnOK();
    }
    GetPage();
}

void CDUpdReason::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDCallbackReason dlgCallbackReason;
        dlgCallbackReason.m_sPartnerNo = m_sPartnerNo;
        dlgCallbackReason.m_bMainMailAdr = !m_CMail.IsEmpty();
        dlgCallbackReason.m_ReasonNo = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 4)));
        dlgCallbackReason.m_Reason = m_ListCtl.GetItemText(pos, 1);
        dlgCallbackReason.m_Mailadr = m_ListCtl.GetItemText(pos, 2);
        dlgCallbackReason.m_bOnlyMail = (atoi(m_ListCtl.GetItemText(pos, 5)) == 1) ? TRUE : FALSE;
        dlgCallbackReason.m_new = FALSE;
        dlgCallbackReason.SetVzNr(GetVzNr());
        dlgCallbackReason.DoModal();
        GetPage();
    }
}

void CDUpdReason::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDUpdReason::OnButtonNewreason()
{
    UpdateData();
    CDCallbackReason dlgCallbackReason;
    dlgCallbackReason.m_bMainMailAdr = !m_CMail.IsEmpty();
    dlgCallbackReason.m_sPartnerNo = m_sPartnerNo;
    dlgCallbackReason.SetVzNr( GetVzNr() );
    dlgCallbackReason.m_bOnlyMail = FALSE;
    dlgCallbackReason.m_new = TRUE;
    dlgCallbackReason.DoModal();
    GetPage();
}

void CDUpdReason::OnButtonDelreason()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(AETXT_RG_DELETE) == IDNO)
            return;
        m_Callbackreasons.SetCallbackdivisionno(m_sPartnerNo);
        m_Callbackreasons.SetBranchno(m_sVzNr);
        m_Callbackreasons.SetReasonno(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 4))));
        m_Callbackreasons.Delete();
        GetPage();
    }
}
