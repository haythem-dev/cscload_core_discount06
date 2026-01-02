// DBePosBearb.cpp : implementation file
//

#include "stdafx.h"
#include "AeFView.h"
#include "DBePosBearb.h"
#include <artikel.h>
#include "DCheckNachl.h"

/////////////////////////////////////////////////////////////////////////////
// CDBePosBearb dialog


CDBePosBearb::CDBePosBearb(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBePosBearb::IDD, pParent), m_Presenter(m_Data, m_Model)
{
    m_CBemerkung = _T("");
    m_CArtName = _T("");
    m_CArtEinh = _T("");
    m_LiefMenge = 0;
    m_LiefMengeNatra = 0;
    m_CDarreichform = _T("");
    m_VerbundZeitKnd = _T("");
    m_CArtCode = _T("");
    m_List1 = new CIBTListCtrl;
    assert(m_List1);
}

CDBePosBearb::~CDBePosBearb()
{
    delete m_List1;
    m_List1 = NULL;
}

void CDBePosBearb::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_OFF_BEST, m_ListOffBest);
    DDX_Control(pDX, IDC_COMBO_VERB_FILIALE, m_ComboVerbund);
    DDX_Control(pDX, IDC_EDIT_LIEF_MENGE, m_EditLiefMenge);
    DDX_Control(pDX, IDC_EDIT_LIEF_MENGE_NATRA, m_EditLiefMengeNatra);
    DDX_Control(pDX, IDC_EDITTEXT, m_EditBemerkung);
    DDX_Text(pDX, IDC_EDITTEXT, m_CBemerkung);
    DDX_Text(pDX, IDC_ART_NAME, m_CArtName);
    DDX_Text(pDX, IDC_ART_EINH, m_CArtEinh);
    DDX_Text(pDX, IDC_ART_NR, m_Data.m_strArtNr);
    DDX_Text(pDX, IDC_BESTAND, m_Data.m_strBestand);
    DDX_Text(pDX, IDC_BEST_MENGE, m_Data.m_strBestMenge);
    DDX_Text(pDX, IDC_BEST_MENGE_NATRA, m_Data.m_strBestMengeNatra);
    DDX_Text(pDX, IDC_EDIT_LIEF_MENGE, m_LiefMenge);
    DDX_Text(pDX, IDC_EDIT_LIEF_MENGE_NATRA, m_LiefMengeNatra);
    DDX_Text(pDX, IDC_ART_DARR, m_CDarreichform);
    DDX_Check(pDX, IDC_CHECK_VERBUND, m_Data.m_bVerbund);
    DDX_Text(pDX, IDC_STATIC_VERBZ2, m_VerbundZeitKnd);
    DDX_Text(pDX, IDC_ART_CODE, m_CArtCode);
    DDX_Control(pDX, IDC_LIST1, *m_List1);
}


BEGIN_MESSAGE_MAP(CDBePosBearb, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDITTEXT, OnChangeEdittext)
    ON_EN_CHANGE(IDC_EDIT_LIEF_MENGE, OnChangeEditLiefMenge)
    ON_EN_CHANGE(IDC_EDIT_LIEF_MENGE_NATRA, OnChangeEditLiefMengeNatra)
    ON_BN_CLICKED(IDC_BUTTON_DISPO, OnButtonDispo)
    ON_BN_CLICKED(IDC_BUTTON_NACH_LF, OnButtonNachLf)
    ON_BN_CLICKED(IDC_BUTTON_ZUGESAGT, OnButtonZugesagt)
    ON_BN_CLICKED(IDC_CHECK_VERBUND, OnCheckVerbund)
    ON_CBN_SELCHANGE(IDC_COMBO_VERB_FILIALE, OnSelchangeComboVerbFiliale)
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_VERBUND, &CDBePosBearb::OnBnClickedVerbund)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_BN_CLICKED(IDCANCEL2, &CDBePosBearb::OnBnClickedCancel2)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDBePosBearb message handlers

BOOL CDBePosBearb::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    BeginWaitCursor();

    // Read data from UI
    ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_AA)->GetWindowText(m_Data.m_strAArt);

    m_Presenter.InitDialog();

    GetDlgItem(IDC_BUTTON_NACH_LF)->EnableWindow(m_Data.m_bEnableBtnNachlieferung ? TRUE : FALSE);
    GetDlgItem(IDC_BUTTON_DISPO)->EnableWindow(m_Data.m_bEnableBtnDispo ? TRUE : FALSE);
    GetDlgItem(IDC_STATIC_AH)->SetWindowText(m_Data.m_strAH);
    GetDlgItem(IDC_BUTTON_ZUGESAGT)->EnableWindow(m_Data.m_bEnableBtnZugesagt ? TRUE : FALSE);

    GetDlgItem(IDC_LIST_OFF_BEST)->ShowWindow(m_Data.m_bShowListOffBest ? SW_SHOW : SW_HIDE);

    if (m_Data.m_bShowListOffBest)
    {
        for (int i = 0; i < m_Data.m_ListOpenOrders.GetCount(); ++i)
    {
            m_ListOffBest.AddString(m_Data.m_ListOpenOrders[i]);
    }
    }

    EndWaitCursor();

    SetDefID(m_Data.m_uiDefID);
    GetDlgItem(m_Data.m_uiFocusId)->SetFocus();

    m_List1->init();

    if (AeGetApp()->IsNLevelIBTCst())
    {
        GetDlgItem(IDCANCEL2)->SetWindowTextA(CResString::ex().getStrTblText(AETXT_NO_BOOKING));
        GetDlgItem(IDOK)->SetWindowTextA(CResString::ex().getStrTblText(AETXT_DEFEKT_SMALL_TITLE));
    }

    (m_Data.m_lVerbMenge == 0) ? DeaktVerbund() : InitVerbund();

    if (m_Data.m_bShowNatra)
    {
        GetDlgItem(IDC_STATIC_BEST_NATRA)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_BEST_NATRA)->EnableWindow(TRUE);
        GetDlgItem(IDC_BEST_MENGE_NATRA)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BEST_MENGE_NATRA)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NATRA)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NATRA)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_LIEF_MENGE_NATRA)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_LIEF_MENGE_NATRA)->EnableWindow(TRUE);
    }
    CenterWindow();

    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

void CDBePosBearb::InitVerbund()
{
    //Verbund moeglich

    m_Presenter.InitVerbund();

    if (m_Data.m_bIsNLevelIBTCst)
    {
        DWORD dwOldBits = m_List1->GetExtendedStyle();
        dwOldBits |= LVS_EX_FULLROWSELECT;
        m_List1->SetExtendedStyle(dwOldBits);

        GetDlgItem(IDC_CHECK_VERBUND)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_VERBUND)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_VERB1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VERB1)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_VERB_FILIALE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_VERB_FILIALE)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_LISTE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_LISTE)->EnableWindow(TRUE);
        GetDlgItem(IDC_VERBUND)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_VERBUND)->EnableWindow(TRUE);
        GetDlgItem(IDC_LIST1)->ShowWindow(SW_SHOW);

        m_List1->DeleteAllItems();

        for (int i = 0; i < (int)m_Data.m_List1.size(); ++i)
        {
            int index = m_List1->GetItemCount();
            m_List1->InsertItem(index, "");
            m_List1->SetItemText(index, COL_IBT_BRANCHNAME, m_Data.m_List1[i][COL_IBT_BRANCHNAME]);
            m_List1->SetItemText(index, COL_IBT_FILI, m_Data.m_List1[i][COL_IBT_FILI]);
            m_List1->SetItemText(index, COL_IBT_BESTAND, m_Data.m_List1[i][COL_IBT_BESTAND]);
            m_List1->SetItemText(index, COL_IBT_TYPE, m_Data.m_List1[i][COL_IBT_TYPE]);
            m_List1->SetItemText(index, COL_IBT_DATUM, m_Data.m_List1[i][COL_IBT_DATUM]);
            m_List1->SetItemText(index, COL_IBT_ZEIT, m_Data.m_List1[i][COL_IBT_ZEIT]);
        }
        if (m_Data.m_bStockTooLowAlert)
        {
            m_List1->setItemColor(m_Data.m_nPosVB, RGB(0, 0, 0), RGB(255, 0, 0));
        }
        else
        {
            m_List1->setItemColor(m_Data.m_nPosVB, RGB(0, 0, 0), RGB(0, 255, 0));
        }
    }
    else
    {
        for (int i = 0; i < (int)m_Data.m_List1.size(); ++i)
        {
            m_ComboVerbund.AddString(m_Data.m_List1[i][0]);
        }

        if (!m_Data.m_List1.empty())
        {
            m_ComboVerbund.SetCurSel(m_Data.m_nCbxVerbundPos);
            m_ComboVerbund.SetTopIndex(m_Data.m_nCbxVerbundPos);
            SetVerbund(false);
            }
        }

    if (m_Data.m_List1.empty())
        {
            DeaktVerbund();
        }
        }

void CDBePosBearb::DeaktVerbund()
{
    m_Presenter.DeaktVerbund();

    GetDlgItem(IDC_STATIC_VERB1      )->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_VERBZ1     )->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_VERBZ2     )->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_VERB_FILIALE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_CHECK_VERBUND     )->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_LISTE      )->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LIST1             )->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_VERBUND)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_VERBUND)->EnableWindow(FALSE);
}

void CDBePosBearb::CheckVerbund()
{
    if (m_Data.m_bVerbund && (m_Data.m_lVerbMenge != 0L))
    {
        if (m_Data.m_bIsNLevelIBTCst)
        {
            m_Data.m_sVerbFiliale = (short)atol(m_Data.m_List1[m_Data.m_nPosVB][COL_IBT_FILI]);
        }
        else
        {
            CString cstr;
            m_ComboVerbund.GetLBText(m_ComboVerbund.GetCurSel(), cstr);
            m_Data.m_sVerbFiliale = (short)atol(cstr);
        }
    }
    else
    {
        m_Data.m_sVerbFiliale = 0;
    }
}

void CDBePosBearb::OnChangeEdittext()
{
    AllgLaengeKontr(&m_EditBemerkung, MAXIMUM_POS_BEM, AeGetApp()->Modus());
}

void CDBePosBearb::OnChangeEditLiefMenge()
{
    int anzahl = atol(m_Data.m_strBestand) + m_Data.m_lMengeVerbund;
    if (anzahl > m_Data.m_lBestMenge)
        anzahl = m_Data.m_lBestMenge;
    AllgWertKontr(&m_EditLiefMenge, anzahl);
}

void CDBePosBearb::OnChangeEditLiefMengeNatra()
{
    int anzahl = atol(m_Data.m_strBestand) - m_LiefMenge;
    if (anzahl > m_BestMengeNatra)
        anzahl = m_BestMengeNatra;
    AllgWertKontr(&m_EditLiefMengeNatra, anzahl);
}

void CDBePosBearb::OnButtonDispo()
{
    UpdateData();
    CString cInfo;
    if (m_Model.ReadDispoInfo(atol(m_Data.m_strArtNr), cInfo))
    {
        if (MsgBoxYesNo(cInfo, MB_ICONEXCLAMATION | MB_DEFBUTTON1, (CResString::ex().getStrTblText(AETXT_DISPONIEREN))) == IDNO)
        {
            return;
        }
    }
    m_Menge = m_LiefMenge;
    m_Data.m_lPosState = ITEM_STAT_DISPO;
    CheckVerbund();
    CDialogMultiLang::OnOK();
}

void CDBePosBearb::OnButtonNachLf()
{
    UpdateData();
    m_Menge = m_LiefMenge;
    m_Data.m_lPosState = ITEM_STAT_NACHLIEFERN;
    CheckVerbund();
    if (m_Data.m_strAArt == "NO")
    {
        CDCheckNachl nachl;
        nachl.m_lMenge = m_Data.m_lBestMenge;
        nachl.m_lArtikelnr = atol(m_Data.m_strArtNr);
        nachl.m_lIdf = m_IdfNr;
        nachl.m_cAArt = m_Data.m_strAArt;
        if (nachl.DoModal() == IDCANCEL)
        {
            CDialogMultiLang::OnCancel();
            return;
        }
        m_Data.m_lBestMenge = nachl.m_lMenge;
    }
    CDialogMultiLang::OnOK();
}

void CDBePosBearb::OnOK()
{
    UpdateData();
    m_Menge = m_LiefMenge;
    m_Data.m_lPosState = ITEM_STAT_NORMAL;
    CheckVerbund();
    CDialogMultiLang::OnOK();
}

void CDBePosBearb::OnButtonZugesagt()
{
    UpdateData();
    m_Menge = m_LiefMenge;
    m_Data.m_lPosState = ITEM_STAT_ZUGESAGT;
    CheckVerbund();
    CDialogMultiLang::OnOK();
}

void CDBePosBearb::OnCheckVerbund()
{
    bool bSetVerbund = IsDlgButtonChecked(IDC_CHECK_VERBUND) ? true : false;
    SetVerbund(bSetVerbund);
}

void CDBePosBearb::SetVerbund(bool bVerbund)
{
    m_Presenter.SetVerbund(bVerbund);

    GetDlgItem(IDC_EDIT_LIEF_MENGE)->SetWindowText(m_Data.m_strLiefMenge);

    if (!m_Data.m_bIsNLevelIBTCst)
    {
        GetDlgItem(IDC_STATIC_VERB1)->EnableWindow(m_Data.m_bEnableStcVerb1 ? TRUE : FALSE);
        GetDlgItem(IDC_COMBO_VERB_FILIALE)->EnableWindow(m_Data.m_bEnableCbxVerbFiliale ? TRUE : FALSE);

        if (bVerbund)
        {
            OnSelchangeComboVerbFiliale();
        }
        }
    }

 void CDBePosBearb::OnSelchangeComboVerbFiliale()
{
    CString cstr1, cstr2;
    int pos = 0;

    m_ComboVerbund.GetLBText(m_ComboVerbund.GetCurSel(), cstr1);
    for (int i = 0; i < cstr1.GetLength() - 1; i++)
    {
        if (cstr1.GetAt(i) == ' ')
        {
            pos = i + 1;
            break;
        }
    }
    cstr2 = cstr1.Right(cstr1.GetLength() - pos);
    m_Data.m_lMengeVerbund = (short)atol(cstr2);
    int anzahl = atol(m_Data.m_strBestand) + m_Data.m_lMengeVerbund;
    if (anzahl > m_Data.m_lBestMenge)
        anzahl = m_Data.m_lBestMenge;
    cstr1.Format("%ld", anzahl);
    GetDlgItem(IDC_EDIT_LIEF_MENGE)->SetWindowText(cstr1);
}

HBRUSH CDBePosBearb::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_STATIC_AH)
        pDC->SetTextColor(RGB(200,0,0));

    return hbr;
}

void CDBePosBearb::OnBnClickedVerbund()
{
    m_Data.m_sVerbFiliale = (short)atol(m_List1->GetItemText(m_Data.m_nPosVB, COL_IBT_FILI));
    SetVerbund();
    UpdateData();
    m_Menge = m_LiefMenge;
    m_Data.m_lPosState = ITEM_STAT_NORMAL;
    CDialogMultiLang::OnOK();
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDBePosBearb::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_ESCAPE)
    {
        if (AeGetApp()->IsNLevelIBTCst())  //Escap-Taste in N-Level-Verbund gesperrt
        {
            return 1L;      //Message wird nicht weitergeleitet
        }
    }

    return 0L;
}

void CDBePosBearb::OnBnClickedCancel2()
{
    CDialogMultiLang::OnCancel();
}
