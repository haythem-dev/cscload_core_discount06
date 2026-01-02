// DAuftragartKd.cpp : implementation file
//

#include "stdafx.h"
#include <kndsel.h>
#include "DKndWahl.h"
#include "DAuftragartkd.h"

/////////////////////////////////////////////////////////////////////////////
// CDAuftragartKd dialog


CDAuftragartKd::CDAuftragartKd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAuftragartKd::IDD, pParent)
{
    m_bBANR = FALSE;
    m_bMonatrab = FALSE;
    m_bNatra = FALSE;
    m_bNetto = FALSE;
    m_bValutasperre = FALSE;
    m_bVerbund = FALSE;
    m_CAart = _T("");
    m_CIdf = _T("");
    m_CValutamon = _T("");
    m_CValutamonauto = _T("");
}


void CDAuftragartKd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_VALUTAMONAUTO, m_Edit_Valutamonauto);
    DDX_Control(pDX, IDC_EDIT_VALUTAMON, m_Edit_Valutamon);
    DDX_Control(pDX, IDC_EDIT_IDF, m_Edit_Idf);
    DDX_Control(pDX, IDC_EDIT_AART, m_Edit_Aart);
    DDX_Control(pDX, IDC_BUTTON_EFG, m_CBEfg);
    DDX_Control(pDX, IDC_BUTTON_DEL, m_CBDel);
    DDX_Check(pDX, IDC_CHECK_BANR, m_bBANR);
    DDX_Check(pDX, IDC_CHECK_MONATRAB, m_bMonatrab);
    DDX_Check(pDX, IDC_CHECK_NATRA, m_bNatra);
    DDX_Check(pDX, IDC_CHECK_NETTO, m_bNetto);
    DDX_Check(pDX, IDC_CHECK_VALUTASPERRE, m_bValutasperre);
    DDX_Check(pDX, IDC_CHECK_VERBUND, m_bVerbund);
    DDX_Text(pDX, IDC_EDIT_AART, m_CAart);
    DDX_Text(pDX, IDC_EDIT_IDF, m_CIdf);
    DDX_Text(pDX, IDC_EDIT_VALUTAMON, m_CValutamon);
    DDX_Text(pDX, IDC_EDIT_VALUTAMONAUTO, m_CValutamonauto);
}


BEGIN_MESSAGE_MAP(CDAuftragartKd, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_EFG, OnButtonEfg)
    ON_EN_CHANGE(IDC_EDIT_AART, OnChangeEditAart)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnChangeEditIdf)
    ON_EN_CHANGE(IDC_EDIT_VALUTAMON, OnChangeEditValutamon)
    ON_EN_CHANGE(IDC_EDIT_VALUTAMONAUTO, OnChangeEditValutamonauto)
    ON_BN_CLICKED(IDC_BUTTON_KNDWAHL, OnButtonKndwahl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAuftragartKd message handlers

BOOL CDAuftragartKd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAuftragartKd::OnButtonDel()
{
    CString CStr;
    CKNDAUFART kndaufart;
    UpdateData();
    kndaufart.s.IDFNR = atol(m_CIdf);
    kndaufart.s.KUNDENNR = atol(m_CIdf);
    //nur eigenes VZ
    kndaufart.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    strcpy(kndaufart.s.KDAUFTRAGART,m_CAart);
    CStr.Format(CResString::ex().getStrTblText(IDP_PAR_AART_DEL), m_CAart.GetString());
    if (MsgBoxYesNo(CStr) == IDYES)
        kndaufart.Server(AakundeDel_aufart);
}

void CDAuftragartKd::OnButtonEfg()
{
    CKNDAUFART kndaufart;
    UpdateData();
    kndaufart.s.IDFNR = atol(m_CIdf);
    kndaufart.s.KUNDENNR = atol(m_CIdf);
    //nur eigenes VZ
    kndaufart.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    strcpy(kndaufart.s.KDAUFTRAGART, m_CAart);
    kndaufart.s.VALUTAMONATE = static_cast<short>(atoi(m_CValutamon));
    kndaufart.s.VALUTAMONAUTO = static_cast<short>(atoi(m_CValutamonauto));
    kndaufart.s.SKDAUFTRAGARTNATRA[0] = (m_bNatra == FALSE) ? '0' : '1';
    kndaufart.s.SKDAUFTRAGARTNETTO[0] = (m_bNetto == FALSE) ? '0' : '1';
    kndaufart.s.SKDAUFTRAGARTBANR[0] = (m_bBANR == FALSE) ? '0' : '1';
    kndaufart.s.SKDAUFTRAGARTMONAT[0] = (m_bMonatrab == FALSE) ? '0' : '1';
    kndaufart.s.SKDAUFTRAGVERBUND[0] = (m_bVerbund == FALSE) ? '0' : '1';
    kndaufart.s.SKDAUFTRAGARTVALS[0] = (m_bValutasperre == FALSE) ? '0' : '1';
    kndaufart.Server(AakundeIns_aufart);
}

void CDAuftragartKd::OnChangeEditAart()
{
    AllgLaengeKontr(&m_Edit_Aart, L_KNDAUFART_KDAUFTRAGART, AeGetApp()->Modus());
}

void CDAuftragartKd::OnChangeEditIdf()
{
    AllgWertKontr(&m_Edit_Idf, MAXIMUM_IDF);
}

void CDAuftragartKd::OnChangeEditValutamon()
{
    AllgWertKontr(&m_Edit_Valutamon, MAXIMUM_MON_VALUTA);
}

void CDAuftragartKd::OnChangeEditValutamonauto()
{
    AllgWertKontr(&m_Edit_Valutamonauto, MAXIMUM_MON_VALUTA);
}

void CDAuftragartKd::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

void CDAuftragartKd::OnButtonKndwahl()
{
    CString CStr;
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CStr.Format("%ld", dlgKndWahl.GetKndNr());
    GetDlgItem(IDC_EDIT_IDF)->SetWindowText(CStr);
    m_CIdf = CStr;
}
