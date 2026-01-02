// DTourAnz.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <kndsel.h>
#include "DKndWahl.h"
#include "DTourAnz.h"
#include "DTourUpd.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  80, LVCFMT_LEFT,
    2,  "",  60, LVCFMT_LEFT,
    3,  "",  80, LVCFMT_LEFT,
    4,  "",  60, LVCFMT_LEFT,
    5,  "", 240, LVCFMT_LEFT,
    -1, "",   0, 0
};


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDTourAnz


CDTourAnz::CDTourAnz(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTourAnz::IDD, pParent)
{
    m_lCustomerNo = -1;
    m_sSaleCenterNo = -1;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_KURZ_FOLGE);
    Columns[3].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_KZ_KOMMIART);
    Columns[5].Columns = CResString::ex().getStrTblText(IDS_BEMERK);
}


void CDTourAnz::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDTourAnz, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f¸r Nachrichten CDTourAnz

BOOL CDTourAnz::OnInitDialog()
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
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur¸ckgeben
}

void CDTourAnz::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        OnButtonUpdate();
        return;
    }
    CDialogMultiLang::OnOK();
}

void CDTourAnz::OnButtonUpdate()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDTourUpd upd;
        upd.m_csTour = m_ListCtl.GetItemText(pos, 1);
        upd.m_csFolge = m_ListCtl.GetItemText(pos, 2);
        upd.m_csZeit = m_ListCtl.GetItemText(pos, 3);
        upd.m_csBemerkung = m_ListCtl.GetItemText(pos, 5);
        upd.m_sVz = GetVzNr();
        CString csKA = m_ListCtl.GetItemText(pos, 4);
        upd.m_sKA = (csKA.GetAt(0) == ' ') ? 0 : static_cast<short>(atoi(csKA) + 1);

        if (upd.DoModal() == IDOK)
        {
            if (upd.m_sKA == 0)
                csKA = " ";
            else
                csKA.Format("%d", (upd.m_sKA - 1));
            if (csKA == m_ListCtl.GetItemText(pos, 4))
                return;
            m_Touren.SetKoart(csKA.GetAt(0));
            CString tour;
            tour = m_ListCtl.GetItemText(pos, 1).Left(2) +
                   m_ListCtl.GetItemText(pos, 1).Mid(3,2) +
                   m_ListCtl.GetItemText(pos, 1).Right(2);
            m_Touren.SetTourid(tour);
            m_Touren.SetVertriebszentrumnr(GetVzNr());
            m_Touren.SetKundennr(GetKundenNr());
            m_Touren.SetLoginid( GetAeUser().GetUID() );
            if (upd.m_sKA == 0)
                csKA = " ";
            else
                csKA.Format("%d", (upd.m_sKA - 1));
            m_Touren.SetKoart(csKA.GetAt(0));
            m_ListCtl.SetItemText(pos, 4, csKA);
            MsgBoxOK(m_Touren.Update() == 0 ? IDP_UPDATED : IDP_NOT_UPDATED);
        }
    }
    m_ListCtl.EnsureVisible(0, 0);
    m_ListCtl.SetFocus();
}

void CDTourAnz::GetPage()
{
    ppString text;
    CString str;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_Touren.SetVertriebszentrumnr(GetVzNr());
    m_Touren.SetKundennr(GetKundenNr());
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_Touren.SelTourenKunde() != 0)
            break;
        s[0] = kb.Next();
        str = m_Touren.GetTourid(text);
        if (str.IsEmpty())
            s[1] = str;
        else
            s[1].Format("%.2s:%.2s/%.2s", str.Left(2).GetString(), str.Mid(2, 2).GetString(), str.Right(2).GetString());
        s[2].Format("%d", m_Touren.GetReihenfolgenr());
        s[3].Format("%d", m_Touren.GetFahrtzeit());
        s[4] = m_Touren.GetKoart();
        s[5] = m_Touren.GetBemerkungen(text);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
    m_Touren.CloseCursor();
    EndWaitCursor();
}

void CDTourAnz::SetHeader()
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

void CDTourAnz::OnButtonChange()
{
    if (SelKunde())
    {
        SetHeader();
        GetPage();
    }
}

bool CDTourAnz::SelKunde()
{
    //Definition Kunde
    CDKndWahl dlgKndWahl;
    dlgKndWahl.SetEnableAeGesperrt();    // Checkbutton muﬂ enabled werden
    if (dlgKndWahl.DoModal() == IDOK)
    {
        SetVzNr(dlgKndWahl.GetKndVz());
        SetKundenNr(dlgKndWahl.GetKndNr());
        return true;
    }
    return false;
}

void CDTourAnz::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonUpdate();

    *pResult = 0L;
}
