// daltart.cpp : implementation file
//

#include "stdafx.h"
#include "DAltArt.h"
#include <kndsel.h>
#include "DKndInf.h"
#include "DArtInf.h"

/////////////////////////////////////////////////////////////////////////////
// CDAltArt dialog


CDAltArt::CDAltArt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAltArt::IDD, pParent)
    , m_CArtCodeOrg(_T(""))
    , m_CArtCodeAltern(_T(""))
{
    m_AltArtBest = _T("");
    m_AngArtBest = _T("");
    m_ArtName = _T("");
    m_ArtEinheit = _T("");
    m_ArtNr = _T("");
    m_CDarreichform = _T("");
    m_CArtNameOrg = _T("");
    m_CArtEinhOrg = _T("");
    m_CArtDarrOrg = _T("");
    m_CArtNrOrg = _T("");
    m_bOrigArt          = false;
    m_bNetto            = FALSE;
    m_bNatra            = FALSE;
    m_bKndSchwerpunk3   = false;
    m_bKndSchwerpunk5   = false;
    m_KundenNr          = 0;
}

void CDAltArt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ALT_ART_BEST, m_AltArtBest);
    DDX_Text(pDX, IDC_ANG_ART_BEST, m_AngArtBest);
    DDX_Text(pDX, IDC_ART_NAME, m_ArtName);
    DDX_Text(pDX, IDC_ART_EINH, m_ArtEinheit);
    DDX_Text(pDX, IDC_ART_NR, m_ArtNr);
    DDX_Text(pDX, IDC_ART_DARR, m_CDarreichform);
    DDX_Text(pDX, IDC_ART_NAME2, m_CArtNameOrg);
    DDX_Text(pDX, IDC_ART_EINH_ORG, m_CArtEinhOrg);
    DDX_Text(pDX, IDC_ART_DARR_ORG, m_CArtDarrOrg);
    DDX_Text(pDX, IDC_ART_NR_ORG, m_CArtNrOrg);
    DDX_Text(pDX, IDC_ART_CODE_ORG, m_CArtCodeOrg);
    DDX_Text(pDX, IDC_ART_CODE_ALTERN, m_CArtCodeAltern);
}


BEGIN_MESSAGE_MAP(CDAltArt, CDialogMultiLang)
    ON_BN_CLICKED(IDC_ORIG_ART, OnOrigArt)
    ON_BN_CLICKED(IDC_ORIG_ARTINFO, OnOrigArtinfo)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDAltArt message handlers

BOOL CDAltArt::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();
    if (m_bNetto)
        GetDlgItem(IDC_STATIC_NETTO)->ShowWindow(SW_SHOW);
    if (m_bNatra)
        GetDlgItem(IDC_STATIC_NATRA)->ShowWindow(SW_SHOW);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAltArt::OnOrigArt()
{
    m_bOrigArt = true;
    CDialogMultiLang::OnOK();
}

void CDAltArt::OnOrigArtinfo()
{
    CDArtInf dlgArtInf;
    dlgArtInf.m_CBemerkungKond.Empty();
    if (m_bKndSchwerpunk3)
        dlgArtInf.m_CBemerkungKond = CResString::ex().getStrTblText(AETXT_ARB_KREIS_AKTUELL);
    else
        dlgArtInf.m_bNoPriceGroup2 = TRUE;
    if (m_bKndSchwerpunk5)
    {
        if (dlgArtInf.m_CBemerkungKond.IsEmpty())
            dlgArtInf.m_CBemerkungKond = CResString::ex().getStrTblText(AETXT_DIABETES);
        else
        {
            dlgArtInf.m_CBemerkungKond += " / ";
            dlgArtInf.m_CBemerkungKond += CResString::ex().getStrTblText(AETXT_DIABETES);
        }
    }
    else
        dlgArtInf.m_bNoPriceGroup3 = TRUE;
    dlgArtInf.SetArtNr(atol(m_ArtNr));
    dlgArtInf.DoModal();
}

LRESULT CDAltArt::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        OnOrigArtinfo();
        return 1;
    }
    else if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        CKndInf dlgKndInf;
        dlgKndInf.SetIdfNr(m_KundenNr);
        dlgKndInf.SetKndVz(AeGetApp()->VzNr_Kunde());
        dlgKndInf.DoModal();
        return 1;
    }
    return 0;
}
