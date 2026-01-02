// DChangeTour.cpp : implementation file
//

#include "stdafx.h"
#include <kndsel.h>
#include "DChangeTour.h"


// CDChangeTour dialog

IMPLEMENT_DYNAMIC(CDChangeTour, CDialogEx)

CDChangeTour::CDChangeTour(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDChangeTour::IDD, pParent)
    , m_bDD(FALSE)
    , m_CT_DD(0)
    , m_bMixExist(false)
    , m_bMixShown(false)
    , m_bAnzSonder(false)
    , m_lDatum(0)
    , m_lDatumDD(0)
{
    m_cKA[0] = '0';
}

CDChangeTour::~CDChangeTour()
{
}

void CDChangeTour::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_TOUR, m_CoboxTour);
    DDX_Check(pDX, IDC_CHECK_DD, m_bDD);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DD, m_DT_DD);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DD, m_CT_DD);
    DDX_Control(pDX, IDC_COMBO_TOUR_NAKT, m_CoboxNakt);
    DDX_Control(pDX, IDC_COMBO_FUTUR, m_CoboxFutur);
    DDX_Control(pDX, IDC_COMBO_MIX, m_CoboxMix);
    DDX_Control(pDX, IDC_STATIC_SONDER_TOUR, m_cs_SonderTour);
}


BEGIN_MESSAGE_MAP(CDChangeTour, CDialogMultiLang)
    ON_WM_CTLCOLOR()
    ON_CBN_SELCHANGE(IDC_COMBO_TOUR, OnSelchangeComboTour)
    ON_CBN_SELCHANGE(IDC_COMBO_TOUR_NAKT, OnCbnSelchangeComboTourNakt)
    ON_CBN_SELCHANGE(IDC_COMBO_MIX, OnCbnSelchangeComboMix)
    ON_BN_CLICKED(IDC_BUTTON_SONDER, OnBnClickedButtonSonder)
    ON_BN_CLICKED(IDC_CHECK_DD, OnBnClickedCheckDd)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DD, OnDtnDatetimechangeDatetimepickerDd)
END_MESSAGE_MAP()


// CDChangeTour message handlers

BOOL CDChangeTour::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    m_Tagtab.Add( (char *)CResString::ex().getStrTblText(IDS_SUNDAY).GetString());
    m_Tagtab.Add((char *)CResString::ex().getStrTblText(IDS_MONDAY).GetString());
    m_Tagtab.Add((char *)CResString::ex().getStrTblText(IDS_TUESDAY).GetString());
    m_Tagtab.Add((char *)CResString::ex().getStrTblText(IDS_WEDNESDAY).GetString());
    m_Tagtab.Add((char *)CResString::ex().getStrTblText(IDS_THURSDAY).GetString());
    m_Tagtab.Add((char *)CResString::ex().getStrTblText(IDS_FRIDAY).GetString());
    m_Tagtab.Add((char *)CResString::ex().getStrTblText(IDS_SATURDAY).GetString());
    m_Tagtab.Add((char *)CResString::ex().getStrTblText(AETXT_HEUTE).GetString());
    m_Tagtab.Add((char *)CResString::ex().getStrTblText(AETXT_SONDERTOUR).GetString());
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_lActDatum = zeit.s.DATUM;
    m_lDatumDD = m_pAuftrag->s.DATUMAUSLIEFERUNG;
    m_sWeekday = (short)zeit.s.WTAG;
    CTime anf = CTimeFromDateLongMinTime(zeit.s.DATUM);
    char error_msg[81];
    zeit.s.DATUM = AllgAddDate(zeit.s.DATUM, 1, error_msg);
    CTime end(2030, 12, 31, 0, 0, 0);
    m_DT_DD.SetRange(&anf,&end);
    if (m_lDatumDD > 0)
    {
        zeit.s.DATUM = m_lDatumDD;
    }
    CTime zeitDD = CTimeFromDateLongMinTime(zeit.s.DATUM);
    m_DT_DD.SetTime(&zeitDD);

    if (m_lDatumDD > m_lActDatum) m_bDD = TRUE;
    GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_HIDE);
    CheckDlgButton(IDC_CHECK_DD,FALSE);
    m_bSonder = false;
    m_AArt = m_pAuftrag->s.KDAUFTRAGART;
    VersorgeTouren(m_AArt);

    m_saveTour = m_pAuftrag->s.TOURID;

    CFont* pobjCFont = m_cs_SonderTour.GetFont();
    LOGFONT lf;
    pobjCFont->GetLogFont(&lf);
    lf.lfWeight *= 2;
    CFont objCFont;
    objCFont.CreateFontIndirect(&lf);

    m_cs_SonderTour.SetFont(&objCFont);

    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDChangeTour::InsTouren(CString& AArt)
{
    //Tour
    CString STour;      //Tour für Ausgabe formatiert
    CString Tour;       //Tournummer
    CKNDTOUREN kndtouren;
    kndtouren.s.IDFNR = m_pAuftrag->s.KUNDENNR;
    kndtouren.s.KUNDENNR = m_pAuftrag->s.KUNDENNR;
    kndtouren.s.VERTRIEBSZENTRUMNR = m_pAuftrag->s.VERTRIEBSZENTRUMNR;
    strcpy(kndtouren.s.KDAUFTRAGART, AArt);
    m_CoboxTour.ResetContent();
    m_CoboxNakt.ResetContent();
    m_CoboxMix.ResetContent();
    for (;;)
    {
        kndtouren.Server(AasrvGettouren, PIPE_AE_SRV);
        if (kndtouren.rc != SRV_OK)
            break;
        Tour = kndtouren.s.TOURID;
        if (kndtouren.s.KZAUTOZUORD[0] == '1')
        {
            TourToString(Tour, STour, kndtouren.s.FAHRTZEIT, kndtouren.s.KOART[0], 7);
        }
        else
        {
            TourToString(Tour, STour, kndtouren.s.FAHRTZEIT, kndtouren.s.KOART[0], 8);
        }
        m_CoboxMix.AddString(STour);
        if (kndtouren.s.KZAUTOZUORD[0] == '1')
        {
            m_CoboxTour.AddString(STour);
        }
        else
        {
            m_bMixExist = true;
            m_CoboxNakt.AddString(STour);
        }
    }
    if (GetOrderType().IsNoDD(AeGetApp()->VzNr(), AArt.GetString()))
    {
        if (m_CoboxTour.GetCount() == 0)
        {
            ShowSonder();
        }
        else
        {
            ShowAkt();
        }
    }
    else if (m_CoboxTour.GetCount() == 0)
    {
        m_bMixExist = false;
        m_CoboxMix.ResetContent();
        HoleWochenTouren(AArt);
        LadeWochenTouren(9);
        if (m_CoboxNakt.GetCount() > 0)
        {
            ShowSonder();
            m_bSonder = true;
        }
        else
        {
            ShowFutur();
            m_bSonder = false;
        }
    }
    UpdateData(FALSE);
}

void CDChangeTour::TourToString(CString& Tour, CString& STour, long Fahrzeit, char cKA, short sWeekday)
{
    char str[81];
    strncpy(str, Tour, 2);
    str[2] = '\0';
    int h = atol(str);
    STour  = str;
    STour += ":";
    strncpy(str, Tour.Right(4), 2);
    str[2] = '\0';
    int min = atol(str);
    int ah = h + Fahrzeit / 60;
    int amin = min + Fahrzeit % 60;
    if (amin > 59)
    {
        ah   += 1;
        amin -= 60;
    }
    if (ah > 23)
    {
        ah -= 24;
    }
    STour.Format("%02d:%02d % 11.11s% 2.2s% 7.7s%02d:%02d % 5.5s % 2.2s: %c  %s                       %d",
        h,
        min,
        CResString::ex().getStrTblText(AETXT_UHR_BHF).GetString(),
        Tour.Right(2).GetString(),
        CResString::ex().getStrTblText(AETXT_SP_ANKUNFT).GetString(),
        ah,
        amin,
        CResString::ex().getStrTblText(AETXT_UHR).GetString(),
        CResString::ex().getStrTblText(AETXT_KZ_KOMMIART).GetString(),
        cKA,
        m_Tagtab[sWeekday].GetString(),
        sWeekday);
}

void CDChangeTour::StringToTour(char* tour, CString& STour)
{
    strncpy(tour,STour,2);
    strncpy(tour+2,(const char*)STour + 3,2);
    strncpy(tour+4,(const char*)STour + 17,2);
    tour[6] = '\0';
}

void CDChangeTour::SetTour()
{
    CString STour;
    int iPos;
    TourToString(m_Tour,STour, 0,' ',7);
    if (( iPos = m_CoboxTour.SelectString(-1, STour.Left(18)) ) == CB_ERR)
    {
        if (m_CoboxMix.SelectString(-1, STour.Left(18)) == CB_ERR)
        {
            if (m_CoboxNakt.SelectString(-1, STour.Left(18)) == CB_ERR)
            {
                if (m_iCombo == 0)
                {
                    ShowAkt();
                    m_CoboxTour.SetCurSel(0);
                }
                else if (m_iCombo == 1)
                {
                    ShowSonder();
                    m_CoboxNakt.SetCurSel(0);
                }
                else if (m_iCombo == 2)
                {
                    ShowFutur();
                    m_CoboxFutur.SetCurSel(0);
                }
                else
                {
                    ShowMix();
                    m_CoboxMix.SetCurSel(0);
                }
            }
        }
        else
        {
            ShowMix();
            m_CoboxMix.SetCurSel(0);
            GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AUS));
            m_bMixShown = true;
            m_CoboxMix.SelectString(-1, STour.Left(18));
        }
    }
    else
    {
        m_CoboxTour.SetCurSel(iPos);
        m_CoboxTour.UpdateWindow();
    }
}

void CDChangeTour::SetTourFutur()
{
    CString STour;
    TourToString(m_Tour,STour, 0,' ',7);
    if (m_CoboxFutur.SelectString(-1, STour.Left(18)) == CB_ERR)
    {
        m_CoboxFutur.SetCurSel(0);
    }
}

void CDChangeTour::OnOK()
{
    CAUFTRAG auftrag;
    UpdateData();

    if (m_cKA[0] != m_pAuftrag->s.KOART[0])
    {
        strncpy(auftrag.s.KDAUFTRAGART,m_pAuftrag->s.KDAUFTRAGART,2);
        auftrag.s.KOART[0] = m_pAuftrag->s.KOART[0];
        auftrag.s.BUCHART[0] = m_pAuftrag->s.BUCHART[0];
        auftrag.Server(AasrvChangeorder, PIPE_AE_SRV); //Auftrags-, Kommi- und Buchungsart setzen
        if (auftrag.rc < SRV_OK)
        {
            return;
        }
    }

    //Verzoegerte Auslieferung
    if (IsDlgButtonChecked(IDC_CHECK_DD))
    {
        long newDD = (m_CT_DD.GetYear() * 10000 +
                      m_CT_DD.GetMonth() * 100 +
                      m_CT_DD.GetDay());
        if (newDD != m_lDatumDD)
        {
            auftrag.s.DATUMAUSLIEFERUNG = newDD;
            auftrag.Server(AasrvSetdelayeddate, PIPE_AE_SRV);
            m_lDatumDD = newDD;
        }
    }
    else if (m_lDatumDD > m_lActDatum)
    {
        auftrag.s.DATUMAUSLIEFERUNG = m_lActDatum;
        auftrag.Server(AasrvSetdelayeddate, PIPE_AE_SRV);
        m_lDatumDD = m_lActDatum;
    }
    else
    {
        m_lDatumDD = 0;
    }

    //Tour setzen
    CString Tour;
    int toursel;
    if (m_iCombo == 2)
    {
        toursel = m_CoboxFutur.GetCurSel();
        if (toursel != CB_ERR)
        {
            m_CoboxFutur.GetLBText(toursel,Tour);
        }
        else
        {
            Tour = "";
        }
    }
    else if (m_iCombo == 0)
    {
        toursel = m_CoboxTour.GetCurSel();
        if (toursel != CB_ERR)
        {
            m_CoboxTour.GetLBText(toursel,Tour);
        }
        else
        {
            Tour = "";
        }
    }
    else if (m_iCombo == 3)
    {
        toursel = m_CoboxMix.GetCurSel();
        if (toursel != CB_ERR)
        {
            m_CoboxMix.GetLBText(toursel,Tour);
        }
        else
        {
            Tour = "";
        }
    }
    else
    {
        toursel = m_CoboxNakt.GetCurSel();
        if (toursel != CB_ERR)
        {
            m_CoboxNakt.GetLBText(toursel,Tour);
        }
        else
        {
            Tour = "";
        }
    }
    if (Tour.GetLength() >= 18)
    {
        StringToTour(auftrag.s.TOURID, Tour);
        auftrag.Server(AasrvChangeTour, PIPE_AE_SRV);
        if (auftrag.rc < SRV_OK)
        {
            return;
        }
    }
    CDialogMultiLang::OnOK();
}

HBRUSH CDChangeTour::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_STATIC_SONDER_TOUR)
        pDC->SetTextColor(RGB(200, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_COMBO_TOUR_NAKT)
        pDC->SetTextColor(RGB(200, 0, 0));
    else if (pWnd->GetDlgCtrlID() == IDC_COMBO_FUTUR)
        pDC->SetTextColor(RGB(0, 0, 200));
    else if (pWnd->GetDlgCtrlID() == IDC_COMBO_MIX)
    {
        if (m_bAnzSonder)
        {
            pDC->SetTextColor(RGB(200, 0, 0));
        }
        else
        {
            pDC->SetTextColor(RGB(0, 0, 0));
        }
    }
    return hbr;
}

void CDChangeTour::OnSelchangeComboTour()
{
    CString Tour;
    char ctour[10];
    int toursel = m_CoboxTour.GetCurSel();
    if (toursel != CB_ERR)
    {
        m_CoboxTour.GetLBText(toursel,Tour);
    }
    else
    {
        return;
    }
    if (Tour.GetLength() >= 17)
    {
        StringToTour(ctour, Tour);
    }
    m_Tour = ctour;
    m_saveTour = m_Tour;
}

void CDChangeTour::OnBnClickedCheckDd()
{
    UpdateData();
    if (IsDlgButtonChecked(IDC_CHECK_DD))
    {
        GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_SHOW);
        HoleWochenTouren(m_AArt);
        CTimeSpan y(1, 0, 0, 0);

        for (int i = 0; i < 6; i++)
        {
            LadeWochenTouren(static_cast<short>(m_CT_DD.GetDayOfWeek() - 1));

            if (m_CoboxFutur.GetCount() > 0)
            {
                break;
            }

            m_CT_DD += y;
        }
        long newDD = (m_CT_DD.GetYear() * 10000 +
                      m_CT_DD.GetMonth() * 100 +
                      m_CT_DD.GetDay());
        if (newDD > m_lActDatum)
        {
            ShowFutur();
            m_CoboxFutur.SetCurSel(0);
            GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_HIDE);
        }
        else if (m_CoboxTour.GetCount() == 0)
        {
            ShowSonder();
            m_bSonder = true;
            m_CoboxNakt.SetCurSel(0);
        }
        else
        {
            ShowAkt();
            m_CoboxTour.SetCurSel(0);
        }
    }
    else
    {
        GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_HIDE);
        if (m_CoboxTour.GetCount() == 0)
        {
            ShowSonder();
            GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_SHOW);
            m_bSonder = true;
            if (m_CoboxNakt.GetCount() == 0)
            {
                MsgBoxOK(IDP_NO_TOURID);
            }
            else
            {
                m_CoboxNakt.SetCurSel(0);
                OnCbnSelchangeComboTourNakt();
            }
        }
        else
        {
            ShowAkt();
            m_bSonder = false;
            m_CoboxTour.SetCurSel(0);
        }
    }
    UpdateData(FALSE);
}

void CDChangeTour::OnDtnDatetimechangeDatetimepickerDd(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    UpdateData();
    LadeWochenTouren( static_cast<short>(m_CT_DD.GetDayOfWeek()-1));

    long newDD = m_CT_DD.GetYear() * 10000 +
                 m_CT_DD.GetMonth() * 100 +
                 m_CT_DD.GetDay();
    if (newDD > m_lActDatum)
    {
        ShowFutur();
        m_bSonder = false;
        m_CoboxFutur.SetCurSel(0);
    }
    else if (m_CoboxTour.GetCount() == 0)
    {
        ShowSonder();
        m_bSonder = true;
        m_CoboxNakt.SetCurSel(0);
    }
    else
    {
        ShowAkt();
        m_bSonder = false;
        m_CoboxTour.SetCurSel(0);
    }

    *pResult = 0L;
}

void CDChangeTour::OnCbnSelchangeComboTourNakt()
{
    CString Tour;
    char ctour[10];
    int toursel = m_CoboxNakt.GetCurSel();
    if (toursel != CB_ERR)
    {
        m_CoboxNakt.GetLBText(toursel,Tour);
    }
    else
    {
        return;
    }
    if (Tour.GetLength() >= 17)
    {
        StringToTour(ctour, Tour);
    }
    if (Tour.GetLength() >= 42)
    {
        m_cKA[0] = Tour.GetAt(42);
    }
    m_Tour = ctour;
    m_saveTour = m_Tour;
}

void CDChangeTour::HoleWochenTouren(CString& AArt)
{
    //Tour
    CString STour;      //Tour für Ausgabe formatiert
    CString Tour;       //Tournummer
    CKNDTOUREN kndtouren;
    kndtouren.s.IDFNR = m_pAuftrag->s.KUNDENNR;
    kndtouren.s.KUNDENNR = m_pAuftrag->s.KUNDENNR;
    kndtouren.s.VERTRIEBSZENTRUMNR = m_pAuftrag->s.VERTRIEBSZENTRUMNR;
    strcpy(kndtouren.s.KDAUFTRAGART, AArt);
    m_aWochentouren.RemoveAll();
    for (;;)
    {
        kndtouren.Server(AasrvGetWeektouren, PIPE_AE_SRV);
        if (kndtouren.rc != SRV_OK)
            break;
        Tour = kndtouren.s.TOURID;
        TourToString(Tour, STour, kndtouren.s.FAHRTZEIT, kndtouren.s.KOART[0], kndtouren.s.WEEKDAY);
        m_aWochentouren.Add(STour);
    }
}

void CDChangeTour::LadeWochenTouren(short sWeekday)
{
    //Tour
    m_CoboxFutur.ResetContent();
    for (int i = 0;i < m_aWochentouren.GetCount();i++)
    {
        if (sWeekday == 9)
        {
            m_CoboxFutur.AddString(m_aWochentouren.GetAt(i));
        }
        else
        {
            if (atoi(m_aWochentouren.GetAt(i).Right(1)) == sWeekday)
            {
                m_CoboxFutur.AddString(m_aWochentouren.GetAt(i));
            }
        }
    }
    if (sWeekday == 9)
    {
        char cWeekday[2];
        int i;
        CString csTour;
        sprintf(cWeekday, "%d", m_sWeekday);
        for (i = 0; i < m_CoboxFutur.GetCount(); i++)
        {
            m_CoboxFutur.GetLBText(i, csTour);
            if (cWeekday[0] < csTour.GetAt(50))
            {
                m_CoboxFutur.SetCurSel(i);
                i = 99;
                break;
            }
        }
        if (i < 99)
        {
            sprintf(cWeekday, "%d", m_sWeekday - 7);
            for (i = 0; i < m_CoboxFutur.GetCount(); i++)
            {
                m_CoboxFutur.GetLBText(i,csTour);
                if (cWeekday[0] < csTour.GetAt(48))
                {
                    m_CoboxFutur.SetCurSel(i);
                    break;
                }
            }
        }
    }
    else
    {
        m_CoboxFutur.SetCurSel(0);
    }
}

void CDChangeTour::OnBnClickedButtonSonder()
{
    if (m_bMixShown)
    {
        if (m_bSonder)
        {
            ShowSonder();
        }
        else
        {
            ShowAkt();
        }
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
        m_bMixShown = false;
    }
    else
    {
        ShowMix();
        m_CoboxMix.SetCurSel(0);
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AUS));
        m_bMixShown = true;
    }
}

void CDChangeTour::OnCbnSelchangeComboMix()
{
    CString Tour;
    int toursel = m_CoboxMix.GetCurSel();
    if (toursel != CB_ERR)
    {
        m_CoboxMix.GetLBText(toursel,Tour);
    }
    else
    {
        return;
    }
    if (Tour.GetLength() >= 42)
    {
        m_cKA[0] = Tour.GetAt(42);
    }
    CString Tourtyp;
    Tourtyp = Tour.Mid(45,m_Tagtab.GetAt(8).GetLength());
    m_bAnzSonder = (m_Tagtab.GetAt(8) == Tourtyp) ? true : false;
}

void CDChangeTour::ShowAkt()
{
    m_iCombo = 0;
    GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR_NAKT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR_NAKT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_MIX)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_MIX)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_TOUR)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_FUTUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_FUTUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
    if (m_bMixExist)
    {
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(FALSE);
    }
    if (m_CoboxTour.GetCurSel() == CB_ERR)
        m_CoboxTour.SetCurSel(0);
}

void CDChangeTour::ShowSonder()
{
    m_iCombo = 1;
    GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_TOUR_NAKT)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_TOUR_NAKT)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_MIX)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_MIX)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_TOUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_FUTUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_FUTUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
    if (m_CoboxNakt.GetCurSel() == CB_ERR)
        m_CoboxNakt.SetCurSel(0);
}

void CDChangeTour::ShowFutur()
{
    m_iCombo = 2;
    GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR_NAKT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR_NAKT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_MIX)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_MIX)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_TOUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_FUTUR)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_FUTUR)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AN));
    if (m_CoboxFutur.GetCurSel() == CB_ERR)
        m_CoboxFutur.SetCurSel(0);
}

void CDChangeTour::ShowMix()
{
    m_iCombo = 3;
    GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR_NAKT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR_NAKT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_MIX)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_COMBO_MIX)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_TOUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_TOUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_FUTUR)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_FUTUR)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SONDER)->SetWindowText(CResString::ex().getStrTblText(AETXT_SONDER_AUS));
    OnCbnSelchangeComboMix();
}

void CDChangeTour::VersorgeTouren(CString& AArt)
{
    InsTouren(AArt);
    SetTour();

    if (m_lDatumDD > 0)
    {
        CTime zeitDD = CTimeFromDateLongMinTime(m_lDatumDD);
        HoleWochenTouren(AArt);

        LadeWochenTouren(static_cast<short>(zeitDD.GetDayOfWeek() - 1));

        if (m_lDatumDD > m_lActDatum)
        {
            if (GetOrderType().IsNoDD(AeGetApp()->VzNr(), AArt.GetString()))
            {
                GetDlgItem(IDC_CHECK_DD)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_CHECK_DD)->EnableWindow(FALSE);
                GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_HIDE);
                GetDlgItem(IDC_DATETIMEPICKER_DD)->EnableWindow(FALSE);
            }
            else
            {
                CheckDlgButton(IDC_CHECK_DD,TRUE);
                GetDlgItem(IDC_CHECK_DD)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_CHECK_DD)->EnableWindow(TRUE);
                GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_HIDE);
                ShowFutur();
                SetTourFutur();
            }
        }
        else if (m_CoboxTour.GetCount() == 0)
        {
            GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_SHOW);
            ShowSonder();
            m_bSonder = true;
            m_CoboxNakt.SetCurSel(0);
        }
        else
        {
            GetDlgItem(IDC_STATIC_SONDER_TOUR)->ShowWindow(SW_HIDE);
            m_bSonder = false;
        }
    }
    else
    {
        if (GetOrderType().IsNoDD(AeGetApp()->VzNr(), AArt.GetString()))
        {
            GetDlgItem(IDC_CHECK_DD)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_CHECK_DD)->EnableWindow(FALSE);
            GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_DATETIMEPICKER_DD)->EnableWindow(FALSE);
            if (m_CoboxTour.GetCount() == 0)
            {
                ShowSonder();
            }
            else
            {
                ShowAkt();
            }
        }
        else
        {
            CheckDlgButton(IDC_CHECK_DD,FALSE);
            GetDlgItem(IDC_CHECK_DD)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_CHECK_DD)->EnableWindow(TRUE);
            GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_HIDE);
            HoleWochenTouren(AArt);
            if (m_CoboxTour.GetCount() == 0)
            {
                if (m_aWochentouren.IsEmpty())
                {
                    ShowSonder();
                }
                else
                {
                    CheckDlgButton(IDC_CHECK_DD,TRUE);
                    OnBnClickedCheckDd();
                }
            }
            else
            {
                ShowAkt();
            }
        }
    }
    if (m_bMixExist && m_lDatumDD <= m_lActDatum)
    {
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_BUTTON_SONDER)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_SONDER)->EnableWindow(FALSE);
    }
}
