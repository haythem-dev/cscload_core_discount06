// DUpdDivision.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <callback.h>
#include "DUpdDivision.h"
#include "DUpdReason.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     4

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 220, LVCFMT_LEFT,
    2,  "", 240, LVCFMT_LEFT,
    3,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

// CDUpdDivision-Dialogfeld

IMPLEMENT_DYNAMIC(CDUpdDivision, CDialog)
CDUpdDivision::CDUpdDivision(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDUpdDivision::IDD, pParent)
{
    m_sVzNr            = 0;
    m_lStartNoCallback = 0;
    m_lEndNoCallback   = 100;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_RRPARTNER);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_EMAIL_ADR);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
}

CDUpdDivision::~CDUpdDivision()
{
}

void CDUpdDivision::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CDUpdDivision, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
END_MESSAGE_MAP()


// CDUpdDivision-Meldungshandler

BOOL CDUpdDivision::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    m_lStartNoCallback = AeGetApp()->StartNoCallback();
    m_lEndNoCallback = m_lStartNoCallback + 100;

    GetPage();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDUpdDivision::GetPage(int /*nKzUpDown*/)
{
    //Variablen
    ppString Partner_name;
    ppString mailadr;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    m_Partner.SetBranchno(GetVzNr());
    m_Partner.SetCallbackstart(m_lStartNoCallback);
    m_Partner.SetCallbackend(m_lEndNoCallback);

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_Partner.SelList() != SRV_OK)
            break;
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        s[1] = m_Partner.GetDivisionname(Partner_name);
        s[2] = m_Partner.GetMailinglist(mailadr);
        s[3].Format("%d", m_Partner.GetCallbackdivisionno());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    } //Ende der for()-Schleife
    m_Partner.CloseCursor();
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;
}

void CDUpdDivision::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDUpdDivision::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDUpdReason dlgUpdReason;
        dlgUpdReason.m_new = FALSE;
        dlgUpdReason.m_sPartnerNo = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 3)));
        dlgUpdReason.m_CName = m_ListCtl.GetItemText(pos, 1);
        dlgUpdReason.m_CMail = m_ListCtl.GetItemText(pos, 2);
        dlgUpdReason.SetVzNr(GetVzNr());
        dlgUpdReason.DoModal();
        GetPage();
    }
}

void CDUpdDivision::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDUpdDivision::OnButtonChange()
{
    SelectEintrag();
}

void CDUpdDivision::OnButtonDelete()
{
    if (MsgBoxYesNo(IDP_SOLL_RR_DELETE) == IDNO)
        return;

    CCALLBACKREASONS reason;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_Partner.SetCallbackdivisionno(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 3))));
        m_Partner.Delete();
        reason.SetCallbackdivisionno(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 3))));
        reason.DeleteAllNo();
        GetPage();
    }
}

void CDUpdDivision::OnButtonNew()
{
    CDUpdReason dlgUpdReason;
    dlgUpdReason.m_new = TRUE;
    dlgUpdReason.SetVzNr(GetVzNr());
    dlgUpdReason.DoModal();
    GetPage();
}
