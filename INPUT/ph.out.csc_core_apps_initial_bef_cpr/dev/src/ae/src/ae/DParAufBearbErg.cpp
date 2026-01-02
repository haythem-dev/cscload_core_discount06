// DParAufBearbErg.cpp : implementation file
//

#include "stdafx.h"
#include "DParAufBearbErg.h"

#define MAXIMUM_ANZ_KUNDEN  10

/////////////////////////////////////////////////////////////////////////////
// CDParAufBearbErg dialog


CDParAufBearbErg::CDParAufBearbErg(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParAufBearbErg::IDD, pParent)
{
    m_lEndZeit = 0;
    m_iFiliale = 0;
    m_iKippZeit = 0;
    m_iMaxKun = 0;
    m_iMaxPos = 0;
    m_CZusAa = _T("");
    m_bNein = FALSE;
    m_bJa = FALSE;
    m_CVb1 = _T("");
    m_CVb2 = _T("");
    m_CVb3 = _T("");
    m_CVb4 = _T("");
    m_CVb5 = _T("");
}


void CDParAufBearbErg::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_VB5, m_EditVb5);
    DDX_Control(pDX, IDC_EDIT_VB4, m_EditVb4);
    DDX_Control(pDX, IDC_EDIT_VB3, m_EditVb3);
    DDX_Control(pDX, IDC_EDIT_VB2, m_EditVb2);
    DDX_Control(pDX, IDC_EDIT_VB1, m_EditVb1);
    DDX_Control(pDX, IDC_CHECK_NEIN, m_CBNein);
    DDX_Control(pDX, IDC_CHECK_JA, m_CBJa);
    DDX_Control(pDX, IDC_EDIT_ZUSAA, m_EditZusAa);
    DDX_Control(pDX, IDC_EDIT_MAXPOS, m_EditMaxPos);
    DDX_Control(pDX, IDC_EDIT_MAXKUN, m_EditMaxKun);
    DDX_Control(pDX, IDC_EDIT_KIPPZEIT, m_EditKippZeit);
    DDX_Control(pDX, IDC_EDIT_FILIALE, m_EditFiliale);
    DDX_Control(pDX, IDC_EDIT_ENDZEIT, m_EditEndZeit);
    DDX_Text(pDX, IDC_EDIT_ENDZEIT, m_lEndZeit);
    DDX_Text(pDX, IDC_EDIT_FILIALE, m_iFiliale);
    DDX_Text(pDX, IDC_EDIT_KIPPZEIT, m_iKippZeit);
    DDX_Text(pDX, IDC_EDIT_MAXKUN, m_iMaxKun);
    DDX_Text(pDX, IDC_EDIT_MAXPOS, m_iMaxPos);
    DDX_Text(pDX, IDC_EDIT_ZUSAA, m_CZusAa);
    DDX_Check(pDX, IDC_CHECK_NEIN, m_bNein);
    DDX_Check(pDX, IDC_CHECK_JA, m_bJa);
    DDX_Text(pDX, IDC_EDIT_VB1, m_CVb1);
    DDX_Text(pDX, IDC_EDIT_VB2, m_CVb2);
    DDX_Text(pDX, IDC_EDIT_VB3, m_CVb3);
    DDX_Text(pDX, IDC_EDIT_VB4, m_CVb4);
    DDX_Text(pDX, IDC_EDIT_VB5, m_CVb5);
}


BEGIN_MESSAGE_MAP(CDParAufBearbErg, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_ENDZEIT, OnChangeEditEndzeit)
    ON_EN_CHANGE(IDC_EDIT_KIPPZEIT, OnChangeEditKippzeit)
    ON_EN_CHANGE(IDC_EDIT_MAXKUN, OnChangeEditMaxkun)
    ON_EN_CHANGE(IDC_EDIT_MAXPOS, OnChangeEditMaxpos)
    ON_EN_CHANGE(IDC_EDIT_ZUSAA, OnChangeEditZusaa)
    ON_BN_CLICKED(IDC_CHECK_JA, OnCheckJa)
    ON_BN_CLICKED(IDC_CHECK_NEIN, OnCheckNein)
    ON_EN_CHANGE(IDC_EDIT_VB1, OnChangeEditVb1)
    ON_EN_CHANGE(IDC_EDIT_VB2, OnChangeEditVb2)
    ON_EN_CHANGE(IDC_EDIT_VB3, OnChangeEditVb3)
    ON_EN_CHANGE(IDC_EDIT_VB4, OnChangeEditVb4)
    ON_EN_CHANGE(IDC_EDIT_VB5, OnChangeEditVb5)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParAufBearbErg message handlers

BOOL CDParAufBearbErg::OnInitDialog()
{
    CPARAUFERG parauferg;
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    parauferg.s.FILIALNR = m_FilialNr;
    BeginWaitCursor();
    parauferg.Server(AafilSelauferg);
    AllgEntfSpaces(parauferg.s.AUFTRAGSARTENFREI);
    AllgEntfSpaces(parauferg.s.SKDSAMMELBEHAELTVB);
    m_iFiliale = parauferg.s.FILIALNR;
    m_iMaxPos = parauferg.s.ANZPOSBEHAELT;
    m_iMaxKun = parauferg.s.ANZKUNDEBEHAELT;
    m_lEndZeit = parauferg.s.ZEITENDEAUTO;
    m_iKippZeit = parauferg.s.KIPPZEIT;
    m_CZusAa = parauferg.s.AUFTRAGSARTENFREI;
    m_CVb1 = parauferg.s.VBFILIALNR1;
    m_CVb2 = parauferg.s.VBFILIALNR2;
    m_CVb3 = parauferg.s.VBFILIALNR3;
    m_CVb4 = parauferg.s.VBFILIALNR4;
    m_CVb5 = parauferg.s.VBFILIALNR5;
    if (parauferg.s.SKDSAMMELBEHAELTVB[0] == '0')
        m_bNein = TRUE;
    else
        m_bJa = TRUE;

    EndWaitCursor();
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParAufBearbErg::OnOK()
{
    CPARAUFERG parauferg;
    UpdateData();
    parauferg.s.FILIALNR = static_cast<short>(m_iFiliale);
    parauferg.s.ANZPOSBEHAELT = static_cast<short>(m_iMaxPos);
    parauferg.s.ANZKUNDEBEHAELT = static_cast<short>(m_iMaxKun);
    parauferg.s.ZEITENDEAUTO = m_lEndZeit;
    parauferg.s.KIPPZEIT = static_cast<short>(m_iKippZeit);
    AllgStrCopy(parauferg.s.VBFILIALNR1, m_CVb1, L_PARAUFERG_VBFILIALNR1);
    AllgStrCopy(parauferg.s.VBFILIALNR2, m_CVb2, L_PARAUFERG_VBFILIALNR2);
    AllgStrCopy(parauferg.s.VBFILIALNR3, m_CVb3, L_PARAUFERG_VBFILIALNR3);
    AllgStrCopy(parauferg.s.VBFILIALNR4, m_CVb4, L_PARAUFERG_VBFILIALNR4);
    AllgStrCopy(parauferg.s.VBFILIALNR5, m_CVb5, L_PARAUFERG_VBFILIALNR5);
    AllgStrCopy(parauferg.s.AUFTRAGSARTENFREI, m_CZusAa, L_PARAUFERG_AUFTRAGSARTENFREI);
    parauferg.s.SKDSAMMELBEHAELTVB[0] = (m_bNein == TRUE) ? '0' : '1';

    BeginWaitCursor();

    EndWaitCursor();
    if (parauferg.rc < SRV_OK)
        return;
    CDialogMultiLang::OnOK();
}

void CDParAufBearbErg::OnChangeEditEndzeit()
{
    AllgWertKontr(&m_EditEndZeit, MAXIMUM_END_ZEIT);
}

void CDParAufBearbErg::OnChangeEditKippzeit()
{
    AllgWertKontr(&m_EditKippZeit, MAXIMUM_END_ZEIT);
}

void CDParAufBearbErg::OnChangeEditMaxkun()
{
    AllgWertKontr(&m_EditMaxKun, MAXIMUM_ANZ_KUNDEN);
}

void CDParAufBearbErg::OnChangeEditMaxpos()
{
    AllgWertKontr(&m_EditMaxPos, MAXIMUM_ANZ_POS);
}

void CDParAufBearbErg::OnChangeEditZusaa()
{
    AllgLaengeKontr(&m_EditZusAa, L_PARAUFERG_AUFTRAGSARTENFREI, AeGetApp()->Modus());
}

void CDParAufBearbErg::OnCheckJa()
{
    m_CBNein.SetCheck(m_CBJa.GetCheck() ? 0 : 1);
}

void CDParAufBearbErg::OnCheckNein()
{
    m_CBJa.SetCheck(m_CBNein.GetCheck() ? 0 : 1);
}

void CDParAufBearbErg::OnChangeEditVb1()
{
    AllgWertKontr(&m_EditVb1, MAXIMUM_FILIALE);
}

void CDParAufBearbErg::OnChangeEditVb2()
{
    AllgWertKontr(&m_EditVb2, MAXIMUM_FILIALE);
}

void CDParAufBearbErg::OnChangeEditVb3()
{
    AllgWertKontr(&m_EditVb3, MAXIMUM_FILIALE);
}

void CDParAufBearbErg::OnChangeEditVb4()
{
    AllgWertKontr(&m_EditVb4, MAXIMUM_FILIALE);
}

void CDParAufBearbErg::OnChangeEditVb5()
{
    AllgWertKontr(&m_EditVb5, MAXIMUM_FILIALE);
}
