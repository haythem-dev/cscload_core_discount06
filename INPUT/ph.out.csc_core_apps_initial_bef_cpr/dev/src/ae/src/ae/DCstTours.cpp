// DCstTours.cpp : implementation file
//

#include "stdafx.h"
#include "DKndWahl.h"
#include "DCstTours.h"
#include <touren.h>
#include "TourListctrl.h"
#include <customer.h>


// CDCstTours dialog

IMPLEMENT_DYNAMIC(CDCstTours, CDialog)

CDCstTours::CDCstTours(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCstTours::IDD, pParent)
    , m_cIDF(_T(""))
    , m_cName(_T(""))
    , m_cOrt(_T(""))
{
    m_lKndNr = -1;
    m_VzNr = -1;
    m_List1 = new CTourListCtrl;
    m_check2 = TRUE;
    m_bUpdated = FALSE;
    m_bAnsicht = FALSE;
}

CDCstTours::~CDCstTours()
{
    m_data.clear();
    delete m_List1;
    m_List1 = 0;
}

void CDCstTours::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, *m_List1);
    DDX_Text(pDX, IDC_EDIT_IDF, m_cIDF);
    DDX_Text(pDX, IDC_EDIT_NAME, m_cName);
    DDX_Text(pDX, IDC_EDIT_ORT, m_cOrt);
}


BEGIN_MESSAGE_MAP(CDCstTours, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_NEW_CST, OnButtonNewCst)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
    ON_WM_CTLCOLOR()
    ON_MESSAGE(WM_QUICKLIST_CLICK, OnListClick)
    ON_MESSAGE(WM_QUICKLIST_GETLISTITEMDATA, OnGetListItem)
END_MESSAGE_MAP()


// CDCstTours message handlers

BOOL CDCstTours::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    m_List1->init();
    m_List1->SetExtendedStyle(m_List1->GetExtendedStyle()
                                | LVS_EX_FULLROWSELECT
                                | LVS_EX_GRIDLINES );        // Grid
    ListView_SetExtendedListViewStyleEx(m_List1->m_hWnd, LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES );


    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_lActDate = zeit.s.DATUM;
    GetDlgItem(IDC_STATIC_WARNUNG)->SetWindowText(CResString::ex().getStrTblText(AETXT_WARNUNG_TOURLADEN));

    GetDlgItem(IDC_BUTTON_CHANGE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CHANGE)->ShowWindow(SW_HIDE);

    if (m_lKndNr == -1)
    {
        if (!AuswahlKunde())
        {
            if (m_lKndNr == -1)
            {
                CDialogMultiLang::OnCancel();
            }
            return TRUE;
        }
    }

    GetPage();
    GetSpecials();
    if (m_bAnsicht)
    {
        this->SetWindowText(CResString::ex().getStrTblText(AETXT_ANZ_CSTTOURS));
        GetDlgItem(IDC_BUTTON_NEW_CST)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_NEW_CST)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_WARNUNG)->SetWindowText(CResString::ex().getStrTblText(AETXT_AKTUEL_STAND));
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCstTours::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    if (!m_bAnsicht)
    {
        OnButtonChange();
    }
    *pResult = 0L;
}

void CDCstTours::OnOK()
{
}

bool CDCstTours::AuswahlKunde()
{
    //Definition Kunde
    CDKndWahl dlgKndWahl;
    dlgKndWahl.SetEnableAeGesperrt();
    if (dlgKndWahl.DoModal() == IDOK)
    {
        m_lKndNr = dlgKndWahl.GetKndNr();
        m_VzNr = dlgKndWahl.GetKndVz();
        m_cOrt = dlgKndWahl.m_COrt;
        m_cName = dlgKndWahl.m_CApotheke;
        m_cIDF.Format("%d", m_lKndNr);
        UpdateData(FALSE);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CDCstTours::GetPage()
{
    //Variablen
    int index;
    ppString tourid;

    CTOURPLANPFLEGE pflege;
    pflege.SetDatumkommi(m_lActDate);
    pflege.SetVertriebszentrumnr(m_VzNr);
    pflege.SetKundennr(m_lKndNr);

    //Anfangsinitialisierung durchfuehren
    m_data.clear();
    m_List1->DeleteAllItems();

    CTourData touren;
    touren.m_BTM = " ";
    touren.m_KK = " ";
    touren.m_K08 = " ";
    touren.m_K20 = " ";

    CLetterMan kb;
    for (;;)
    {
        if (pflege.SelList() != SRV_OK) break;
        //Ausgabe in die Listbox
        index = m_List1->GetItemCount();
        if (m_List1->InsertItem(index, "") == -1)
        {
            return FALSE;
        }
        m_iUpdateKZ[index] = 0;
        touren.m_kb.Format(" %s", kb.Next());
        touren.m_tourid.Format(" %s", pflege.GetTourid(tourid));
        touren.m_auto.Format(" %s", CResString::ex().getStrTblText(pflege.GetKzautozuord() == '1' ? AETXT_JA : AETXT_NEIN).GetString());
        touren.m_check1 = (pflege.GetIsbtm() == 0) ? FALSE : TRUE;
        touren.m_check2 = (pflege.GetIskk() == 0) ? FALSE : TRUE;
        touren.m_check3 = (pflege.GetIsk08() == 0) ? FALSE : TRUE;
        touren.m_check4 = (pflege.GetIsk20() == 0) ? FALSE : TRUE;
        m_data.push_back(touren);
    }
    UpdateList();

    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, 0);

    return TRUE;
}

void CDCstTours::OnButtonNewCst()
{
    if (m_bUpdated)
    {
        if (MsgBoxYesNo(AETXT_NOT_SAVED,MB_ICONEXCLAMATION | MB_DEFBUTTON2) != IDYES)
            return;
    }
    long knd = m_lKndNr;
    AuswahlKunde();
    if (knd != m_lKndNr)
    {
        GetPage();
        GetSpecials();
        m_bUpdated = FALSE;
        GetDlgItem(IDC_BUTTON_CHANGE)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_CHANGE)->ShowWindow(SW_HIDE);
    }
}

void CDCstTours::OnButtonChange()
{
    CString Name = GetAeUser().GetTermID();

    CTOURPLANPFLEGE pflege;
    pflege.SetTermid(Name);
    pflege.SetDatumkommi(m_lActDate);
    pflege.SetVertriebszentrumnr(m_VzNr);
    pflege.SetKundennr(m_lKndNr);
    for (unsigned int item = 0; item < m_data.size(); item++)
    {
        if (m_iUpdateKZ[item] == 0)
            continue;
        CTourData& tourdata = m_data[item];
        pflege.SetTourid(tourdata.m_tourid.Right(tourdata.m_tourid.GetLength() - 1));
        pflege.SetKzautozuord(tourdata.m_auto.Right(tourdata.m_auto.GetLength() - 1) == CResString::ex().getStrTblText(AETXT_JA) ? '1' : '0');
        pflege.SetIsbtm(tourdata.m_check1 ? 1 : 0);
        pflege.SetIskk(tourdata.m_check2 ? 1 : 0);
        pflege.SetIsk08(tourdata.m_check3 ? 1 : 0);
        pflege.SetIsk20(tourdata.m_check4 ? 1 : 0);
        pflege.Update();
        m_iUpdateKZ[item] = 0;
    }
    m_bUpdated = FALSE;
    GetDlgItem(IDC_BUTTON_CHANGE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CHANGE)->ShowWindow(SW_HIDE);
}

HBRUSH CDCstTours::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_STATIC_WARNUNG)
    {
        if (m_bAnsicht)
        {
            pDC->SetTextColor(RGB(0, 200, 0));
        }
        else
        {
            pDC->SetTextColor(RGB(200, 0, 0));
        }
    }
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_NOTDIENST)
    {
        pDC->SetTextColor(RGB(200, 0, 0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_DD_GENERELL)
    {
        pDC->SetTextColor(RGB(200, 0, 0));
    }

    return hbr;
}

//User clicked on list. Toggle checkbox/image if hit
LRESULT CDCstTours::OnListClick(WPARAM /*wParam*/, LPARAM lParam)
{
    CListHitInfo* hit = (CListHitInfo*)lParam;

    TRACE(_T("User hit item %d, subitem %d "), hit->m_item, hit->m_subitem);

    if (hit->m_onButton && !m_bAnsicht)
    {
        TRACE(_T("On check box. "));
        if      (hit->m_subitem == COL_BTM)
            m_data[hit->m_item].m_check1 = !m_data[hit->m_item].m_check1;       // Umsetzen Check-Button
        else if (hit->m_subitem == COL_KK)
            m_data[hit->m_item].m_check2 = !m_data[hit->m_item].m_check2;       // Umsetzen Check-Button
        else if (hit->m_subitem == COL_K08)
            m_data[hit->m_item].m_check3 = !m_data[hit->m_item].m_check3;       // Umsetzen Check-Button
        else if (hit->m_subitem == COL_K20)
            m_data[hit->m_item].m_check4 = !m_data[hit->m_item].m_check4;       // Umsetzen Check-Button

        m_bUpdated = TRUE;
        m_iUpdateKZ[hit->m_item] = 1;
        GetDlgItem(IDC_BUTTON_CHANGE)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_CHANGE)->ShowWindow(SW_SHOW);

        m_List1->RedrawCheckBoxs(hit->m_item, hit->m_item, hit->m_subitem);
    }

    TRACE(_T("\n"));

    return 0L;
}

//Get item data
LRESULT CDCstTours::OnGetListItem(WPARAM /*wParam*/, LPARAM lParam)
{
    //lParam is a pointer to the data that is needed for the element
    CListItemData* data = (CListItemData*)lParam;

    //Get which item and subitem that is asked for.
    int item = data->GetItem();
    int subItem = data->GetSubItem();

    CTourData& tourdata = m_data[item];

    UpdateData();

    data->m_noSelection = FALSE;

    if (subItem == COL_BTM || subItem == COL_KK || subItem == COL_K08 || subItem == COL_K20)
    {
        data->m_button.m_draw = true;
        data->m_button.m_noSelection = FALSE;
        data->m_button.m_style = DFCS_BUTTONCHECK;

        if (subItem == COL_BTM)
        {
            if (tourdata.m_check1)
                data->m_button.m_style |= DFCS_CHECKED;
            data->m_text = " ";
        }
        else if (subItem == COL_KK)
        {
            if (tourdata.m_check2)
                data->m_button.m_style |= DFCS_CHECKED;
            data->m_text = " ";
        }
        else if (subItem == COL_K08)
        {
            if (tourdata.m_check3)
                data->m_button.m_style |= DFCS_CHECKED;
            data->m_text = " ";
        }
        else
        {
            if (tourdata.m_check4)
                data->m_button.m_style |= DFCS_CHECKED;
            data->m_text = " ";
        }
    }

    if (data->GetSubItem() == COL_KB)
    {
        data->m_text = tourdata.m_kb;
    }
    else if (data->GetSubItem() == COL_TOUR)
    {
        data->m_text = tourdata.m_tourid;
    }
    else if (data->GetSubItem() == COL_AUTO)
    {
        data->m_text = tourdata.m_auto;
    }

    return 0;
}

void CDCstTours::UpdateList()
{
    m_List1->LockWindowUpdate();
    m_List1->SetItemCount((int)m_data.size());
    m_List1->UnlockWindowUpdate();
    m_List1->RedrawItems(m_List1->GetTopIndex(), m_List1->GetTopIndex()+m_List1->GetCountPerPage());
}

void CDCstTours::OnCancel()
{
    if (m_bUpdated)
    {
        if (MsgBoxYesNo(AETXT_NOT_SAVED, MB_ICONEXCLAMATION | MB_DEFBUTTON2) != IDYES)
            return;
    }

    CDialogMultiLang::OnCancel();
}

void CDCstTours::GetSpecials()
{
    char error_msg[81];
    CString not;
    CMCUSTOMEREMERGENCYSERVICEPLAN emergency;
    emergency.SetDatum(m_lActDate);
    emergency.SetKundennr(m_lKndNr);
    emergency.SetVertriebszentrumnr(m_VzNr);
    if (!emergency.SelUni())
    {
        not.Format(CResString::ex().getStrTblText(AETXT_SHOW_NOTDIENST), AllgZeit2CharHHMM(emergency.GetUhrzeitbis() / 100));
        GetDlgItem(IDC_STATIC_NOTDIENST)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NOTDIENST)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NOTDIENST)->SetWindowText(not);
    }
    else
    {
        GetDlgItem(IDC_STATIC_NOTDIENST)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_NOTDIENST)->ShowWindow(SW_HIDE);
    }
    CDELAYEDDELIVERYCSTSPECIAL special;
    special.SetWeekday(static_cast<short>(AllgGetWeekDay(m_lActDate, error_msg)));
    special.SetBranchno(m_VzNr);
    special.SetCustomerno(0);
    if (!special.SelUni())
    {
        not.Format(CResString::ex().getStrTblText(AETXT_DD_GENERELL), AllgZeit2CharHHMM(special.GetTime()));
        GetDlgItem(IDC_STATIC_DD_GENERELL)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_DD_GENERELL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_DD_GENERELL)->SetWindowText(not);
    }
    else
    {
        GetDlgItem(IDC_STATIC_DD_GENERELL)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_DD_GENERELL)->ShowWindow(SW_HIDE);
    }
}

// DCstTours.cpp : implementation file
//

// CDCstTourUpd dialog

IMPLEMENT_DYNAMIC(CDCstTourUpd, CDialog)

CDCstTourUpd::CDCstTourUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCstTourUpd::IDD, pParent)
    , m_bBTM(FALSE)
    , m_bKK(FALSE)
    , m_bK08(FALSE)
    , m_bK20(FALSE)
    , m_bAktiv(FALSE)
    , m_bAuto(FALSE)
    , m_cVz(_T(""))
    , m_cKnd(_T(""))
    , m_cTour(_T(""))
{
}

CDCstTourUpd::~CDCstTourUpd()
{
}

void CDCstTourUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_BTM, m_bBTM);
    DDX_Check(pDX, IDC_CHECK_KK, m_bKK);
    DDX_Check(pDX, IDC_CHECK_K08, m_bK08);
    DDX_Check(pDX, IDC_CHECK_K20, m_bK20);
    DDX_Check(pDX, IDC_CHECK_AKTIV, m_bAktiv);
    DDX_Check(pDX, IDC_CHECK_AUTO, m_bAuto);
    DDX_Text(pDX, IDC_EDIT_VZ, m_cVz);
    DDX_Text(pDX, IDC_EDIT_KND, m_cKnd);
    DDX_Text(pDX, IDC_EDIT_TOUR, m_cTour);
}


BEGIN_MESSAGE_MAP(CDCstTourUpd, CDialogMultiLang)
END_MESSAGE_MAP()


// CDCstTourUpd message handlers

void CDCstTourUpd::OnOK()
{
    UpdateData();
    CTOURPLANPFLEGE pflege;
    pflege.SetDatumkommi(m_lActDate);
    pflege.SetVertriebszentrumnr(static_cast<short>(atoi(m_cVz)));
    pflege.SetKundennr(atol(m_cKnd));
    pflege.SetTourid(m_cTour);
    pflege.SetKzautozuord(m_bAuto ? '1' : '0');
    pflege.SetIsbtm(m_bBTM ? 1 : 0);
    pflege.SetIskk(m_bKK ? 1 : 0);
    pflege.SetIsk08(m_bK08 ? 1 : 0);
    pflege.SetIsk20(m_bK20 ? 1 : 0);
    pflege.Update();
    CDialogMultiLang::OnOK();
}
