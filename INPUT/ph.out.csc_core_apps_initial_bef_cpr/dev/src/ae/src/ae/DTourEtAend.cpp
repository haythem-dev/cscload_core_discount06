// DTourEtAend.cpp : implementation file
//

#include "stdafx.h"
#include "DTourEtAend.h"
#include "aatour.h"

/////////////////////////////////////////////////////////////////////////////
// CDTourEtAend dialog


CDTourEtAend::CDTourEtAend(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTourEtAend::IDD, pParent)
{
    m_CAuftrNr = _T("");
    m_CKndOrt = _T("");
    m_CKndName = _T("");
    m_Eingabe = _T("");
}


void CDTourEtAend::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_STATIC_AUFTR_NR, m_CAuftrNr);
    DDX_Text(pDX, IDC_STATIC_ORT, m_CKndOrt);
    DDX_Text(pDX, IDC_STATIC_KUNDE, m_CKndName);
    DDX_Text(pDX, IDC_EDIT_EINGABE, m_Eingabe);
}


BEGIN_MESSAGE_MAP(CDTourEtAend, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTourEtAend message handlers

void CDTourEtAend::OnOK()
{
    UpdateData();
    if (m_iAendArt == ETAA_TOUR)
    {
        CTOURINHALT tourinhalt;
        CString CTourid;
        AllgTourEingKonv(CTourid,m_Eingabe);
        AllgStrCopy(tourinhalt.s.TOURID, CTourid, L_TOURINHALT_TOURID);
        tourinhalt.s.KDAUFTRAGNR = atol(m_CAuftrNr);
        tourinhalt.s.ANZBTM = 0; //Keine neue Tour für Kunden anlegen
        tourinhalt.Server(AatourUpd_auf_tour);
        if (tourinhalt.rc == -2)
            return;
        if (tourinhalt.rc == SRV_SQLNOTFOUND)
        {
            if (MsgBoxYesNo(IDP_TOUR_UPD) == IDYES)
            {
                AllgStrCopy(tourinhalt.s.TOURID, CTourid, L_TOURINHALT_TOURID);
                tourinhalt.s.KDAUFTRAGNR = atol(m_CAuftrNr);
                tourinhalt.s.ANZBTM = 1; //Neue Tour für Kunden anlegen
                tourinhalt.s.REIHENFOLGENR = 1;
                tourinhalt.Server(AatourUpd_auf_tour);
            }
            else
                return;
        }

    }
    else if (m_iAendArt == ETAA_SONDERWANNE)
    {
        CTOURINHALT tourinhalt;
        tourinhalt.s.ANZSONDERWANNE = atol(m_Eingabe);
        tourinhalt.s.KDAUFTRAGNR = atol(m_CAuftrNr);
        if (tourinhalt.s.ANZSONDERWANNE == 0)
        {
            char s[81];
            AllgStrCopy(s, m_Eingabe, 80);
            AllgEntfAllSpaces(s);
            if (s[0] != '0' || s[1] != '\0')
            {
                MsgBoxOK(IDP_AE_NICHT_ZUL);
                return;
            }
        }
        tourinhalt.Server(AatourUpd_sond_wann);
    }
    else if (m_iAendArt == ETAA_TOURFOLGE)
    {
        CTOURINHALT tourinhalt;
        AllgStrCopy(tourinhalt.s.TOURID, m_CTour, L_TOURINHALT_TOURID);
        tourinhalt.s.REIHENFOLGENR = atol(m_Eingabe);
        if (tourinhalt.s.REIHENFOLGENR == 0)
        {
            MsgBoxOK(IDP_AE_NICHT_ZUL);
            return;
        }
        tourinhalt.s.KDAUFTRAGNR = atol(m_CAuftrNr);
        tourinhalt.Server(AatourUpd_folgenr);
    }
    CDialogMultiLang::OnOK();
}

BOOL CDTourEtAend::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    if (m_iAendArt == ETAA_TOUR)
        GetDlgItem(IDC_STATIC_AENDART)->SetWindowText(CResString::ex().getStrTblText(IDS_TOUR));
    else if (m_iAendArt == ETAA_SONDERWANNE)
        GetDlgItem(IDC_STATIC_AENDART)->SetWindowText(CResString::ex().getStrTblText(IDS_SONDW));
    else if (m_iAendArt == ETAA_TOURFOLGE)
        GetDlgItem(IDC_STATIC_AENDART)->SetWindowText(CResString::ex().getStrTblText(IDS_TOUR_ROW));
    else CDialogMultiLang::OnCancel();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
