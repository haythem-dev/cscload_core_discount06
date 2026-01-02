// CPCallPlanLoadListe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DDruckAuftrag.h"
#include "CPCallPlanLoadListe.h"
#include "CPCallPlanLoad.h"


//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     8

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 80, LVCFMT_LEFT,
    2,  "", 50, LVCFMT_LEFT,
    3,  "", 80, LVCFMT_LEFT,
    4,  "", 80, LVCFMT_LEFT,
    5,  "", 80, LVCFMT_LEFT,
    6,  "", 50, LVCFMT_LEFT,
    7,  "", 50, LVCFMT_LEFT,
    -1, "",  0, 0
};


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCPCallPlanLoadListe


CCPCallPlanLoadListe::CCPCallPlanLoadListe(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CCPCallPlanLoadListe::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_TAG);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ZEIT_AB);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_BUNDESLAND);
}


void CCPCallPlanLoadListe::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CCPCallPlanLoadListe, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_COMMAND(IDOK, OnOk)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CCPCallPlanLoadListe

BOOL CCPCallPlanLoadListe::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    m_srvCallPlanLoad.SetCountPerPage(366); //theoretisch für jeden Tag ein Eintrag
    m_srvCallPlanLoad.SetVertriebsZentrumNr(GetVzNr());
    m_srvCallPlanLoad.StartBrowse();
    m_srvCallPlanLoad.SetNextPage();
    GetPage();
    if (m_ListCtl.GetItemCount() > 0)
    {
        CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
        m_srvCallPlanLoad.SetElement(0);
    }

    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

bool CCPCallPlanLoadListe::GetPage()
{
    m_ListCtl.DeleteAllItems();
    while (m_srvCallPlanLoad.GetNext())
    {
        int index = m_ListCtl.GetItemCount();
        if (!SetValueIntoList(index))
        {
            EndWaitCursor();
            return false;
        }
    }
    if (m_ListCtl.GetItemCount() > 0)
    {
        CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
        m_srvCallPlanLoad.SetElement(0);
        GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    }
    return TRUE;
}

//---- SetValueIntoList ------------------------------------------------------//

bool CCPCallPlanLoadListe::SetValueIntoList(int pos)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    int index = pos;

    s[0].Format("%s", m_kb.Next() );
    s[1].Format("%s", (const char*)m_srvCallPlanLoad.GetLadeDatum());
    s[2].Format("%s", (const char*)m_srvCallPlanLoad.GetWochenTag());
    s[3].Format("%s", (const char*)m_srvCallPlanLoad.GetLadeZeitAb());
    s[4].Format("%s", (const char*)m_srvCallPlanLoad.GetLadeZeitBis());
    s[5].Format("%s", (const char*)m_srvCallPlanLoad.GetTourID());
    s[6].Format("%d", m_srvCallPlanLoad.GetLadeVZ());
    s[7].Format("%s", (const char*)m_srvCallPlanLoad.GetBundesLand());

    if (m_ListCtl.GetItemCount() <= index)
    {
        if (m_ListCtl.InsertItem(index, s[0], 0) == -1)
            return false;
    }
    CListCtrlHelper::SetItemTexts(m_ListCtl, NUM_COLUMNS, s, index);
    m_ListCtl.SetFocus();
    return true;
}

void CCPCallPlanLoadListe::OnButtonDruck()
{
    int index;
    int max;
    int x;
    int len;
    char feld[100];
    LV_COLUMN lvC;
    lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvC.pszText = feld;
    CDruckAuftrag druckAuftrag;
    CString liste;
    CString ausgab;
    CString str;
    char underline[111];
    memset(underline,'-',110);
    underline[110] = '\0';
    liste.Empty();
    for (x = 1; x < NUM_COLUMNS; x++)
    {
        m_ListCtl.GetColumn(x, &lvC);
        len = lvC.cx / 7 + 1;
        str = feld;
        if (lvC.fmt == LVCFMT_RIGHT)
        {
            ausgab.Format("% *.*s ", len, len, str.GetString());
        }
        else
        {
            str.TrimLeft();
            ausgab.Format("%-*.*s ", len, len, str.GetString());
        }
        liste += ausgab;
    }
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    max = m_ListCtl.GetItemCount();
    for (index = 0; index < max; index++)
    {
        liste.Empty();
        for (x = 1; x < NUM_COLUMNS; x++)
        {
            m_ListCtl.GetColumn(x, &lvC);
            len = lvC.cx / 7 + 1;
            str = m_ListCtl.GetItemText(index, x);
            if (lvC.fmt == LVCFMT_RIGHT)
            {
                ausgab.Format("% *.*s ", len, len, str.GetString());
            }
            else
            {
                str.TrimLeft();
                ausgab.Format("%-*.*s ", len, len, str.GetString());
            }
            liste += ausgab;
        }
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(1);
    druckAuftrag.DelAllData();
}

void CCPCallPlanLoadListe::OnButtonInsert()
{
    CCPCallPlanLoad upd(this, &m_srvCallPlanLoad, 1);
    if (upd.DoModal() == IDOK)
    {
        int index = m_ListCtl.GetItemCount();
        SetValueIntoList(index);
    }
}

void CCPCallPlanLoadListe::OnButtonUpdate()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_srvCallPlanLoad.SetElement(pos);
        CCPCallPlanLoad upd(this, &m_srvCallPlanLoad, 0);
        if (upd.DoModal() == IDOK)
            SetValueIntoList(pos);
    }
}

void CCPCallPlanLoadListe::OnButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            m_srvCallPlanLoad.SetElement(pos);
            if (m_srvCallPlanLoad.Delete())
            {
                MsgBoxOK(IDP_DELETED);
                m_ListCtl.DeleteItem(pos);
            }
            else
                MsgBoxOK(IDP_NOT_DELETED);
        }
    }
}

void CCPCallPlanLoadListe::OnOk()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        OnButtonUpdate();
        return;
    }
    CDialogMultiLang::OnOK();
}

void CCPCallPlanLoadListe::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonUpdate();

    *pResult = 0L;
}
