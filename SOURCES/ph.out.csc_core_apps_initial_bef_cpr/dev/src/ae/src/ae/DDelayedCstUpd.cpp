// DDelayedCstUpd.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "allg.h"
#include <customer.h>
#include "DKndWahl.h"
#include "DDelayedCstUpd.h"


// CDDelayedCstUpd-Dialogfeld

IMPLEMENT_DYNAMIC(CDDelayedCstUpd, CDialog)
CDDelayedCstUpd::CDDelayedCstUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDDelayedCstUpd::IDD, pParent)
    , m_CWTag(_T(""))
    , m_CTour(_T(""))
    , m_bAktiv(FALSE)
    , m_CTourMax(_T(""))
    , m_bBTM(FALSE)
    , m_bKK(FALSE)
    , m_bK08(FALSE)
    , m_bK20(FALSE)
{
    m_Tag = CResString::ex().getStrTblText(IDS_MONDAY);
    m_CDDTag.Empty();
    m_CDDTour.Empty();
    m_bAktiv = TRUE;
    m_bBTM = TRUE;
    m_bKK = TRUE;
    m_bK08 = TRUE;
    m_bK20 = TRUE;
}

CDDelayedCstUpd::~CDDelayedCstUpd()
{
}

void CDDelayedCstUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_WTAG, m_combo_WTag);
    DDX_CBString(pDX, IDC_COMBO_WTAG, m_CWTag);
    DDX_Control(pDX, IDC_COMBO_TOUR, m_combo_Tour);
    DDX_CBString(pDX, IDC_COMBO_TOUR, m_CTour);
    DDX_Control(pDX, IDC_CHECK_AKTIV, m_CB_Aktiv);
    DDX_Check(pDX, IDC_CHECK_AKTIV, m_bAktiv);
    DDX_Control(pDX, IDC_COMBO_TOUR_MAX, m_combo_TourMax);
    DDX_CBString(pDX, IDC_COMBO_TOUR_MAX, m_CTourMax);
    DDX_Control(pDX, IDC_CHECK_BTM, m_CB_BTM);
    DDX_Check(pDX, IDC_CHECK_BTM, m_bBTM);
    DDX_Control(pDX, IDC_CHECK_KK, m_CB_KK);
    DDX_Check(pDX, IDC_CHECK_KK, m_bKK);
    DDX_Control(pDX, IDC_CHECK_K08, m_CB_K08);
    DDX_Check(pDX, IDC_CHECK_K08, m_bK08);
    DDX_Control(pDX, IDC_CHECK_K20, m_CB_K20);
    DDX_Check(pDX, IDC_CHECK_K20, m_bK20);
}


BEGIN_MESSAGE_MAP(CDDelayedCstUpd, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_CBN_SELCHANGE(IDC_COMBO_WTAG, OnCbnSelchangeComboWtag)
END_MESSAGE_MAP()


// CDDelayedCstUpd-Meldungshandler

BOOL CDDelayedCstUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    ppString csTour;
    CString csWoTour;
    m_combo_WTag.ResetContent();
    m_combo_WTag.AddString(CResString::ex().getStrTblText(IDS_SUNDAY));
    m_combo_WTag.AddString(CResString::ex().getStrTblText(IDS_MONDAY));
    m_combo_WTag.AddString(CResString::ex().getStrTblText(IDS_TUESDAY));
    m_combo_WTag.AddString(CResString::ex().getStrTblText(IDS_WEDNESDAY));
    m_combo_WTag.AddString(CResString::ex().getStrTblText(IDS_THURSDAY));
    m_combo_WTag.AddString(CResString::ex().getStrTblText(IDS_FRIDAY));
    m_combo_WTag.AddString(CResString::ex().getStrTblText(IDS_SATURDAY));

    int tourcount = 0;

    if (!m_CDDTag.IsEmpty())
        m_combo_WTag.EnableWindow(FALSE);

    // Touren der ganzen Woche
    m_Cst.SetBranchno(AeGetApp()->VzNr());
    m_Cst.SetCustomerno(m_lKdNr);
    m_combo_Tour.ResetContent();
    for (int i = 0; i < 7; i++) //Touren für ganze Woche
    {
        m_Cst.SetWeekday(static_cast<short>(i));
        for (;!m_Cst.SelectActTouren();)
        {
            m_Cst.GetTourid(csTour);
            csWoTour.Format("%s  %s", m_pTagtab->GetAt(i).GetString(), csTour.c_str());
            m_combo_Tour.AddString(csWoTour);
            ++tourcount;
        }
        m_Cst.CloseCursor();
    }

    if (tourcount == 0)
    {
        MsgBoxOK(AETXT_CONS_TIME_NODATAFOUND);
        CDialogMultiLang::OnCancel();
        return TRUE;
    }
    SetTag();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDDelayedCstUpd::OnBnClickedOk()
{
    UpdateData();
    CDialogMultiLang::OnOK();
}

void CDDelayedCstUpd::OnCbnSelchangeComboWtag()
{
    ppString csTour;

    // Touren aktueller Tag
    m_Cst.SetBranchno(AeGetApp()->VzNr());
    m_Cst.SetCustomerno(m_lKdNr);
    m_Cst.SetWeekday(static_cast<short>(m_combo_WTag.GetCurSel()));

    int i = -1;
    m_combo_TourMax.ResetContent();
    m_combo_TourMax.AddString("000000");
    for (; !m_Cst.SelectActTouren();)
    {
        m_Cst.GetTourid(csTour);
        m_combo_TourMax.AddString(csTour);
        if (i == -1)
        {
            long zeitmax = atol(m_CTourMax);
            long tourzeit = atol(csTour) / 100;
            if (zeitmax <= tourzeit)
                i = m_combo_TourMax.GetCount() - 1;
        }
    }
    m_Cst.CloseCursor();
    m_combo_TourMax.SetCurSel(i);
    CString csWoTag = m_CDDTag;

    if (csWoTag.IsEmpty())
    {
        int iTag = m_combo_WTag.GetCurSel();
        if (iTag > 5)
            iTag = 0;
        ++iTag;
        csWoTag = m_pTagtab->GetAt(iTag);
    }
    int iSel = m_combo_Tour.FindString(-1, csWoTag);
    if (iSel == CB_ERR)
    {
        iSel = 0;
    }
    else if (!m_CDDTour.IsEmpty())
    {
        CString csFind;
        csFind.Format("%s  %s", m_CDDTag.GetString(), m_CDDTour.GetString());
        int iSelTour = m_combo_Tour.FindString(iSel - 1, csFind);
        if (iSelTour != CB_ERR)
        {
            if (iSelTour > iSel)
            {
                CString Str,CStr;
                m_combo_Tour.GetLBText(iSelTour,Str);
                if (csWoTag == Str.Left(csWoTag.GetLength()))
                {
                    iSel = iSelTour;
                }
            }
        }
    }
    m_combo_Tour.SetCurSel(iSel);
}

void CDDelayedCstUpd::SetTag()
{
    m_combo_WTag.SelectString(-1,m_Tag);
    OnCbnSelchangeComboWtag();
}
