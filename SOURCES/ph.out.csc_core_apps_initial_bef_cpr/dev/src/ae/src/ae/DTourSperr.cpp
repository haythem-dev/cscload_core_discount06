// DTourSperr.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <touren.h>
#include <callplanmaintenance.h>
#include "DTourSperr.h"

//Definitionen Buchen
#define BUCHEN_YES  0
#define BUCHEN_NO   1

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     5

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "",  50, LVCFMT_LEFT,
    2,  "", 150, LVCFMT_LEFT,
    3,  "",  60, LVCFMT_LEFT,
    4,  "",  30, LVCFMT_LEFT,
    -1, "",   0, 0
};

// CDTourSperr-Dialogfeld

IMPLEMENT_DYNAMIC(CDTourSperr, CDialog)
CDTourSperr::CDTourSperr(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTourSperr::IDD, pParent), CPageBrowser(0)
    , m_cAb(_T(""))
    , m_CT_Zeit(0)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TOURID);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_GESPERRT);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_VZ);
}

CDTourSperr::~CDTourSperr()
{
}

void CDTourSperr::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_ZU_VZ, m_CB_ZuVz);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_DATETIMEPICKER_ZEIT, m_DT_Zeit);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ZEIT, m_CT_Zeit);
    DDX_Control(pDX, IDC_COMBO_FILI, m_Combo_Fili);
}


BEGIN_MESSAGE_MAP(CDTourSperr, CDialogMultiLang)
    ON_BN_CLICKED(IDC_CHECK_ZU_VZ, OnBnClickedCheckZuVz)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_MARK_ALL, OnBnClickedButtonMarkAll)
    ON_BN_CLICKED(IDC_BUTTON_SPERR, OnBnClickedButtonSperr)
    ON_BN_CLICKED(IDC_BUTTON_ENTSPERR, OnBnClickedButtonEntsperr)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnLvnKeydownList1)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
END_MESSAGE_MAP()


// CDTourSperr-Meldungshandler

void CDTourSperr::OnBnClickedCheckZuVz()
{
    GetDlgItem(IDC_COMBO_FILI)->EnableWindow(IsDlgButtonChecked(IDC_CHECK_ZU_VZ) ? TRUE : FALSE);
}

void CDTourSperr::OnBnClickedOk()
{
    UpdateData();
    GetPage();
}

void CDTourSperr::OnBnClickedButtonMarkAll()
{
    int ende = m_ListCtl.GetItemCount();
    for (int pos = 0; pos < ende; pos++)
    {
        SetMarked(pos);
    }
}

void CDTourSperr::OnBnClickedButtonSperr()
{
    UpdateData();
    if (IsDlgButtonChecked(IDC_CHECK_ZU_VZ))
    {
        CString csBuf;
        GetDlgItem(IDC_COMBO_FILI)->GetWindowText(csBuf);
        m_TourSperre.SetErsatzfilialnr(static_cast<short>(atoi(csBuf)));
    }
    else
    {
        m_TourSperre.SetErsatzfilialnr(0);
    }
    m_TourSperre.SetTourinaktiv('1');
    Update();
    CDialogMultiLang::OnOK();
}

void CDTourSperr::OnBnClickedButtonEntsperr()
{
    m_TourSperre.SetTourinaktiv('0');
    m_TourSperre.SetErsatzfilialnr(0);
    Update();
    CDialogMultiLang::OnOK();
}

void CDTourSperr::Update()
{
    int max = m_ListCtl.GetItemCount();
    UpdateData();
    m_TourSperre.SetFilialnr(AeGetApp()->VzNr());
    BeginWaitCursor();
    for (int pos = 0; pos < max; pos++)
    {
        if (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES)
        {
            m_TourSperre.SetBezeichnung(m_ListCtl.GetItemText(pos, 2));
            m_TourSperre.SetTourid(m_ListCtl.GetItemText(pos, 1));
            m_TourSperre.Update();
        }
    }
    EndWaitCursor();
}

BOOL CDTourSperr::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_YES);
    idResources.push_back(IDI_ICON_NOT);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_CT_Zeit = CTimeFromDateLongMaxTime(zeit.s.DATUM);
    CheckDlgButton(IDC_CHECK_ZU_VZ, FALSE);
    GetDlgItem(IDC_COMBO_FILI)->EnableWindow(FALSE);

    CMSALECENTER Fili;
    CString csBuf;
    ppString cName;
    Fili.SetFilialnr(AeGetApp()->VzNr());
    for (;;)
    {
        if (Fili.SelList() != SRV_OK) break;
        csBuf.Format("%02d %s", Fili.GetFilialnr(), Fili.GetName(cName));
        m_Combo_Fili.AddString(csBuf);
    }
    m_Combo_Fili.SetCurSel(0);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDTourSperr::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES) DelMarked(pos);
    else SetMarked(pos);
}

void CDTourSperr::SetMarked(int pos)
{
    CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, BUCHEN_YES);
}

void CDTourSperr::DelMarked(int pos)
{
    CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, BUCHEN_NO);
}

bool CDTourSperr::GetPage(const int /*nKzUpDown=NEXT_PG*/)
{
    //Variablen
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    CString cTour;
    ppString cBez;
    ppString cId;
    UpdateData();

    //Anfangsinitialisierung durchfuehren
    m_TourSperre.CloseCursor();
    m_ListCtl.DeleteAllItems();
    m_TourSperre.SetFilialnr(AeGetApp()->VzNr());
    cTour.Format("%02d%02d00", m_CT_Zeit.GetHour(), m_CT_Zeit.GetMinute());
    m_TourSperre.SetTourid(cTour);
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_TourSperre.SelList() != SRV_OK) break;
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        s[1] = m_TourSperre.GetTourid(cId);
        s[2] = m_TourSperre.GetBezeichnung(cBez);
        if (m_TourSperre.GetTourinaktiv() == '1')
            s[3] = "J";
        else
            s[3] = "N";
        s[4].Format("%d", m_TourSperre.GetErsatzfilialnr());

        if (!CListCtrlHelper::AppendImageItem(m_ListCtl, NUM_COLUMNS, s, BUCHEN_NO))
        {
            return false;
        }

    } //Ende der for()-Schleife
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    UpdateData(FALSE);
    return true;
}

void CDTourSperr::OnLvnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    int pos;
    OnKeydownList(pNMHDR, pResult, m_ListCtl, pos);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InRange(pLVKeyDow->wVKey, m_ListCtl.GetItemCount()))
    {
        if (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES) DelMarked(pos);
        else SetMarked(pos);
    }
}

void CDTourSperr::OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES) DelMarked(pos);
    else SetMarked(pos);
    *pResult = 0L;
}
