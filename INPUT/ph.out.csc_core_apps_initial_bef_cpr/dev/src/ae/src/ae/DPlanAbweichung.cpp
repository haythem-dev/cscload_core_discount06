/*******************************************************************************/
/*                                                                             */
/*  Quelle  : DPlanAbweichung.cpp                                              */
/*  Autor   : A.Schmidt-Rehschuh                                               */
/*  erstellt: 11.04.97                                                         */
/*  Aufgabe : Glopbale Voreinstellung für verschiedene Anrufarten              */
/*  Klassen : CDPlanAbweichung: Anzeige und Auswahl Änderung Zeit              */
/*            CDZeiteingabe   : Eingabe Zeit in Minuten                        */
/*                                                                             */
/*******************************************************************************/

/*** INCLUDE *******************************************************************/

#include "stdafx.h"
#include "DPlanAbweichung.h"
#include "aarufpl.h"

/*** TYPEDEF *******************************************************************/

enum { F_GET = 100, F_PUT };

#define I_MAX  3
#define MAX_MINUTE 999
#define WARN_DIFF  10

/*** DECLARATION ***************************************************************/

static CString DateTime();

/*** CDPlanAbweichung-KLASSE ***************************************************/

CDPlanAbweichung::CDPlanAbweichung(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPlanAbweichung::IDD, pParent)
{
    m_CStringPhon = _T("");
    m_CStringPara = _T("");
    m_CStringSera = _T("");
    m_CStringDatumZeit = _T("");
    m_sSaleCenterNo = AeGetApp()->FilialNr();
}

void CDPlanAbweichung::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_SERA, m_CStaticSera);
    DDX_Control(pDX, IDC_STATIC_PHON, m_CStaticPhon);
    DDX_Control(pDX, IDC_STATIC_PARA, m_CStaticPara);
    DDX_Text(pDX, IDC_STATIC_PHON, m_CStringPhon);
    DDX_Text(pDX, IDC_STATIC_PARA, m_CStringPara);
    DDX_Text(pDX, IDC_STATIC_SERA, m_CStringSera);
    DDX_Text(pDX, IDC_STATIC_DATUMZEIT, m_CStringDatumZeit);
}

BEGIN_MESSAGE_MAP(CDPlanAbweichung, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_PARA, OnButtonPara)
    ON_BN_CLICKED(IDC_BUTTON_PHON, OnButtonPhon)
    ON_BN_CLICKED(IDC_BUTTON_SERA, OnButtonSera)
END_MESSAGE_MAP()

/*** CDZeiteingabe-KLASSE *****************************************************/

CDZeiteingabe::CDZeiteingabe(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDZeiteingabe::IDD, pParent)
{
    m_CStringEditMinute = _T("");
    m_iMinute = 0;
    m_iMinuteOld = 0;
    m_CStringDatumZeit = _T("");
}


void CDZeiteingabe::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_MINUTE, m_CEditMinute);
    DDX_Text(pDX, IDC_EDIT_MINUTE, m_CStringEditMinute);
    DDX_Text(pDX, IDC_STATIC_DATUMZEIT, m_CStringDatumZeit);
}


BEGIN_MESSAGE_MAP(CDZeiteingabe, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_MINUTE, OnChangeEditMinute)
END_MESSAGE_MAP()


/*******************************************************************************/
/*** CDPlanAbweichung-ON-INIT-DIALOG *******************************************/
/*******************************************************************************/

BOOL CDPlanAbweichung::OnInitDialog()
{
    // ServerCall

    m_CStringPhon.Format("%03d", ServerCall(AaplanVor_sel_uni, F_PHON, 0));
    m_CStringPara.Format("%03d", ServerCall(AaplanVor_sel_uni, F_PARA, 0));
    m_CStringSera.Format("%03d", ServerCall(AaplanVor_sel_uni, F_SERA, 0));

    m_CStringDatumZeit = DateTime();
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

/*** CDPlanAbweichung-ON-BUTTON-PARA *******************************************/

void CDPlanAbweichung::OnButtonPara()
{
    CString cstMinute;
    m_CStaticPara.GetWindowText(cstMinute);

    if (UpdateZeiteingabe(cstMinute, F_PARA))
    {
        m_CStaticPara.SetWindowText(cstMinute);
    }
}

/*** CDPlanAbweichung-ON-BUTTON-PHON *******************************************/

void CDPlanAbweichung::OnButtonPhon()
{
    CString cstMinute;
    m_CStaticPhon.GetWindowText(cstMinute);
    if (UpdateZeiteingabe(cstMinute, F_PHON))
    {
        m_CStaticPhon.SetWindowText(cstMinute);
    }
}

/*** CDPlanAbweichung-ON-BUTTON-SERA *******************************************/

void CDPlanAbweichung::OnButtonSera()
{
    CString cstMinute;
    m_CStaticSera.GetWindowText(cstMinute);
    if (UpdateZeiteingabe(cstMinute, F_SERA))
    {
        m_CStaticSera.SetWindowText(cstMinute);
    }
}

bool CDPlanAbweichung::UpdateZeiteingabe(CString& cstMinute, rufArt eArt)
{
    CDZeiteingabe dlgZeiteingabe;
    dlgZeiteingabe.m_CStringEditMinute = cstMinute;
    if (dlgZeiteingabe.DoModal() && (atoi(cstMinute) != dlgZeiteingabe.m_iMinute))
    {
        ServerCall(AaplanVor_sel_upd, eArt, dlgZeiteingabe.m_iMinute);
        cstMinute.Format("%03d", dlgZeiteingabe.m_iMinute);
        return true;
    }
    return false;
}

/*** SERVER-CALL *****************************************************************/

int CDPlanAbweichung::ServerCall(int iFunction, rufArt eArt, int iMinute)
{
    CRUFPTAGVOR rufptagvor;

    if (!CheckServerCall(eArt, F_GET, 0) && (iFunction == AaplanVor_sel_upd))
        iFunction = AaplanVor_sel_ins;

    rufptagvor.s.NUMMERTYP  = static_cast<short>(eArt);
    rufptagvor.s.NUMMERWERT = iMinute;
    rufptagvor.s.NUMMERMINDEST = m_sSaleCenterNo;
    rufptagvor.s.NUMMERHOECHST = 0;

    rufptagvor.Server(iFunction);
    if (iFunction == AaplanVor_sel_uni)
        CheckServerCall(eArt, F_PUT, rufptagvor.rc);

    return (rufptagvor.rc < SRV_OK ? -1 : (rufptagvor.rc == SRV_OK) ? (int)rufptagvor.s.NUMMERWERT : 0);
}

/*** CHECK-SERVER-CALL ***********************************************************/

int CDPlanAbweichung::CheckServerCall(rufArt eArt, int iFunction, int iSql)
{
    static int iArray[I_MAX];

    switch( iFunction )
    {
    case F_GET:
        return iArray[eArt - F_PHON];
    case F_PUT:
        return iArray[eArt - F_PHON] = (iSql == 0) ? 1 : 0;
    default:
        return 0;
    }
}

/*******************************************************************************/
/*** CDZeiteingabe-ON-INIT-DIALOG **********************************************/
/*******************************************************************************/

BOOL CDZeiteingabe::OnInitDialog()
{
    m_CStringDatumZeit = DateTime();
    m_iMinuteOld = atoi(m_CStringEditMinute);     // save
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    CheckRadioButton(IDC_RADIO_VOR, IDC_RADIO_NACH, (atoi(m_CStringEditMinute) >= 0) ? IDC_RADIO_VOR : IDC_RADIO_NACH);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

/*** CDZeiteingabe-ON-OK *******************************************************/

void CDZeiteingabe::OnOK()
{
    CString cstMinute;

    m_CEditMinute.GetWindowText(cstMinute);
    m_iMinute = atoi(cstMinute);

    int id = GetCheckedRadioButton(IDC_RADIO_VOR, IDC_RADIO_NACH);
    switch (id)
    {
    case IDC_RADIO_VOR:
        break;
    case IDC_RADIO_NACH:
        m_iMinute *= -1;
        break;
    default:
        break;
    }

    if ((m_iMinuteOld - m_iMinute >= WARN_DIFF) && (MsgBoxYesNo(IDS_ACT_TIME_CHANGE) == IDNO))
    {
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_MINUTE));
        return;
    }

    CDialogMultiLang::OnOK();
}

/*** CDZeiteingabe-ON-OK *******************************************************/

void CDZeiteingabe::OnCancel()
{
    m_iMinute = m_iMinuteOld;
    CDialogMultiLang::OnCancel();
}

/*** CDZeiteingabe-ON-CHANGE-EDIT-MINUTE ***************************************/

void CDZeiteingabe::OnChangeEditMinute()
{
    CString cstMinute;

    m_CEditMinute.GetWindowText(cstMinute);
    if (cstMinute.IsEmpty())
        return;
    AllgWertKontr(&m_CEditMinute, MAX_MINUTE);
}

/*** DATE-TIME *******************************************************************/

static CString DateTime()
{
    CTime ctTime = CTime::GetCurrentTime();
    CTM cServerTime;
    cServerTime.Server(AafilGetdatetime);

    CString cstDateTime;
    if (cServerTime.rc != SRV_OK)
    {
        cstDateTime.Format("%02d.%02d.%04d %02d:%02d:%02d",
                           ctTime.GetDay(),
                           ctTime.GetMonth(),
                           ctTime.GetYear(),
                           ctTime.GetHour(),
                           ctTime.GetMinute(),
                           ctTime.GetSecond());
    }
    else
    {
        cstDateTime.Format("%s %s",
            DDMMYYYYStringFromDateLong(cServerTime.s.DATUM),
            HHmmSSStringFromTimeLong(cServerTime.s.ZEIT));
    }
    return cstDateTime;
}
