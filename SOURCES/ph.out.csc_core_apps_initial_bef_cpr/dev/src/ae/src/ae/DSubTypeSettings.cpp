// DSubTypeSettings.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <orders.h>
#include "DSubTypesSettings.h"
#include "DSubTypeSettings.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     7

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 120, LVCFMT_LEFT,
    2,  "",  50, LVCFMT_LEFT,
    3,  "",  70, LVCFMT_LEFT,
    4,  "",  60, LVCFMT_LEFT,
    5,  "",  50, LVCFMT_LEFT,
    6,  "",   0, LVCFMT_RIGHT,
    -1, "",   0, 0
};


// CDSubTypeSettings-Dialogfeld

IMPLEMENT_DYNAMIC(CDSubTypeSettings, CDialog)
CDSubTypeSettings::CDSubTypeSettings(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSubTypeSettings::IDD, pParent)
{
    m_sBranchNo = 0;
}

CDSubTypeSettings::~CDSubTypeSettings()
{
}

void CDSubTypeSettings::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDSubTypeSettings, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_INS, OnBnClickedButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CDSubTypeSettings-Meldungshandler


BOOL CDSubTypeSettings::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_ORIGIN);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_AKTIV);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ZUSAMMEN);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_ENDE);
    Columns[5].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_KL_TYP);
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    GetPage();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDSubTypeSettings::OnBnClickedOk()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDSubTypesSettingsUpd upd;
        upd.m_sBranchNo = m_sBranchNo;
        if (atoi(m_ListCtl.GetItemText(pos, 2)) == 1)
            upd.m_bAktiv = TRUE;
        if (atoi(m_ListCtl.GetItemText(pos, 3)) == 1)
            upd.m_bMerge = TRUE;
        upd.m_csEndeZeit = m_ListCtl.GetItemText(pos, 4);
        upd.m_csDuration = m_ListCtl.GetItemText(pos, 5);
        upd.m_csOrigin.Format("%d %s", atoi(m_ListCtl.GetItemText(pos, 6)), m_ListCtl.GetItemText(pos, 1).GetString());
        upd.DoModal();
        GetPage();
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDSubTypeSettings::OnBnClickedButtonInsert()
{
    CDSubTypesSettingsUpd upd;
    upd.m_sBranchNo = m_sBranchNo;
    upd.m_bInsert = TRUE;
    upd.DoModal();
    GetPage();
}

void CDSubTypeSettings::OnBnClickedButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_OriginTypeSettings.SetBranchno(m_sBranchNo);
        m_OriginTypeSettings.SetOrigintype(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 6))));
        m_OriginTypeSettings.Delete();
        GetPage();
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDSubTypeSettings::GetPage()
{
    ppString cOrigin;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    m_OriginTypeSettings.SetBranchno(m_sBranchNo);
    CLetterMan kb;
    for (;;)
    {
        if (m_OriginTypeSettings.SelList() != SRV_OK) break;
        s[0] = kb.Next();
        s[1] = m_OriginTypeSettings.GetOrigindevice(cOrigin);
        s[2].Format("%d", m_OriginTypeSettings.GetSettingactivated());
        s[3].Format("%d", m_OriginTypeSettings.GetIsorderconsolidation());
        s[4].Format("%d", m_OriginTypeSettings.GetEndofordercons());
        s[5].Format("%d", m_OriginTypeSettings.GetOrderconsduration());
        s[6].Format("%d", m_OriginTypeSettings.GetOrigintype());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_OriginTypeSettings.CloseCursor();
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}
