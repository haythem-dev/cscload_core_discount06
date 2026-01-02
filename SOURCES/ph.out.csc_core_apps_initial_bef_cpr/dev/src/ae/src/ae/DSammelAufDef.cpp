// DSammelAufDef.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DSammelAufDef.h"


// CDSammelAufDef-Dialogfeld

IMPLEMENT_DYNAMIC(CDSammelAufDef, CDialog)
CDSammelAufDef::CDSammelAufDef(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSammelAufDef::IDD, pParent)
    , m_CBemerkung(_T(""))
    , m_CValuta(_T(""))
{
    m_lValuta = 0;
}

CDSammelAufDef::~CDSammelAufDef()
{
}

void CDSammelAufDef::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_AUF_ART, m_Combo_AArt);
    DDX_Control(pDX, IDC_EDIT_BEMERKUNG, m_edit_Bemerkung);
    DDX_Text(pDX, IDC_EDIT_BEMERKUNG, m_CBemerkung);
    DDX_Control(pDX, IDC_GENERIC1, m_CSpinValuta);
    DDX_Text(pDX, IDC_EDIT_VAL_MON2, m_CValuta);
    DDX_Control(pDX, IDC_EDIT_VAL_MON2, m_edit_Valuta);
}


BEGIN_MESSAGE_MAP(CDSammelAufDef, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_BEMERKUNG, OnEnChangeEditBemerkung)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_CHECK_VALUTA, OnBnClickedCheckValuta)
    ON_EN_CHANGE(IDC_EDIT_VAL_MON2, OnEnChangeEditValMon2)
END_MESSAGE_MAP()


// CDSammelAufDef-Meldungshandler

BOOL CDSammelAufDef::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_Combo_AArt.ResetContent();
    for (int i = 0; ; i++)
    {
        CString AArt;
        int rc = GetOrderType().GetAufArtenListeVZ(AeGetApp()->VzNr(), i, AArt);
        if (rc == -1)
            break;
        m_Combo_AArt.AddString(AArt);
        if (rc == SRV_SQLNOTFOUND)
            m_Combo_AArt.SetCurSel(i);
    }
    //Valuta

    if (ValutaInDays())
    {
        GetDlgItem(IDC_ST_VAL_MON)->SetWindowText(CResString::ex().getStrTblText(AETXT_TAGE));
        m_CSpinValuta.SetBuddy(GetDlgItem(IDC_EDIT_VAL_MON2));
        m_CSpinValuta.SetRange(1, MAXIMUM_MON_VALUTA * 30);
    }
    else
    {
        GetDlgItem(IDC_ST_VAL_MON)->SetWindowText(CResString::ex().getStrTblText(AETXT_MONATE));
        m_CSpinValuta.SetBuddy(GetDlgItem(IDC_EDIT_VAL_MON2));
        m_CSpinValuta.SetRange(1, MAXIMUM_MON_VALUTA);
    }

    CheckRadioButton(IDC_RADIO20, IDC_RADIO23, IDC_RADIO20);
    CheckRadioButton(IDC_RADIO10, IDC_RADIO18, IDC_RADIO10);

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_lActDatum = zeit.s.DATUM;

    GetDlgItem(IDC_STATIC_VALUTA_DATUM)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ST_VALDAT)->ShowWindow(SW_HIDE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDSammelAufDef::OnEnChangeEditBemerkung()
{
    AllgLaengeKontr(&m_edit_Bemerkung, MAXIMUM_AUFT_BEM, AeGetApp()->Modus());
}

void CDSammelAufDef::OnBnClickedOk()
{
    UpdateData();

    //Auftragsart bestimmen
    CString AArt;
    m_Combo_AArt.GetLBText(m_Combo_AArt.GetCurSel(), AArt);
    m_CAufArt = AArt.Left(2);

    //Kommissionierart bestimmen
    m_CKoArt = GetKommiType();

    //Buchungsart bestimmen
    m_CBuArt = GetBookingType();

    //Check ob Kombination erlaubt
    if (!AeGetApp()->IsKABAKomb(AeGetApp()->VzNr(), m_CAufArt, m_CKoArt, m_CBuArt))
    {
        CString ftext;
        ftext.Format(CResString::ex().getStrTblText(AETXT_KABAKOMB_NOT),
            m_CAufArt.GetString(),
            m_CKoArt.GetString(),
            m_CBuArt.GetString());
        MsgBoxOK(ftext);
        return;
    }

    //Valuta setzen
    if (IsDlgButtonChecked(IDC_CHECK_VALUTA))
    {
        m_lValuta = atol(m_CValuta);
    }

    OnOK();
}

CString CDSammelAufDef::GetKommiType()
{
    int id = GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO18);
    switch (id)
    {
    case IDC_RADIO10:
        return "0";
    case IDC_RADIO11:
        return "3";
    case IDC_RADIO12:
        return "4";
    case IDC_RADIO13:
        return "5";
    case IDC_RADIO14:
        return "6";
    case IDC_RADIO15:
        return "1";
    case IDC_RADIO16:
        return "2";
    case IDC_RADIO17:
        return "8";
    case IDC_RADIO18:
        return "7";
    default:
        return "0";
    }
}

CString CDSammelAufDef::GetBookingType()
{
    int id = GetCheckedRadioButton(IDC_RADIO20, IDC_RADIO23);
    switch (id)
    {
    case IDC_RADIO20:
        return "0";
    case IDC_RADIO21:
        return "4";
    case IDC_RADIO22:
        return "3";
    case IDC_RADIO23:
        return "2";
    default:
        return "0";
    }
}

void CDSammelAufDef::OnBnClickedCheckValuta()
{
    if (IsDlgButtonChecked(IDC_CHECK_VALUTA))
    {
        GetDlgItem(IDC_STATIC_VALUTA_DATUM)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_ST_VALDAT)->ShowWindow(SW_SHOW);
        m_edit_Valuta.EnableWindow();
        m_CSpinValuta.EnableWindow();
        m_edit_Valuta.SetFocus();
        m_edit_Valuta.SetSel( 0, -1, FALSE );
        m_CSpinValuta.SetPos(1);
        SetValutaDatum();
    }
    else
    {
        GetDlgItem(IDC_STATIC_VALUTA_DATUM)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_ST_VALDAT)->ShowWindow(SW_HIDE);
        m_edit_Valuta.EnableWindow(FALSE);
        m_CSpinValuta.EnableWindow(FALSE);
    }
}

void CDSammelAufDef::OnEnChangeEditValMon2()
{
    int wert = MAXIMUM_MON_VALUTA;
    if (ValutaInDays())
    {
        wert *= 30;
    }
    AllgWertKontr(&m_edit_Valuta, wert);
    SetValutaDatum();
}

void CDSammelAufDef::SetValutaDatum()
{
    long ldatum;
    long ltag = m_lActDatum % 100;
    long lmonat = m_lActDatum / 100 % 100;
    long ljahr = m_lActDatum / 10000;
    CString cvaluta;
    m_edit_Valuta.GetWindowText(cvaluta);
    long lvaluta = atol(cvaluta);
    if (ValutaInDays())
    {
        CTime Valutadatum = CTimeFromDateLongMinTime(m_lActDatum);
        CTimeSpan Spanne(lvaluta, 0, 0, 0);
        Valutadatum += Spanne;
        ldatum = (Valutadatum.GetYear() * 10000)
               + (Valutadatum.GetMonth() * 100)
               + (Valutadatum.GetDay());
    }
    else
    {
        lmonat += lvaluta;
        long lFac = (lmonat > 12) ? 1L : (lmonat < 1) ? -1L : 0L;
        ljahr += lFac;
        lmonat += lFac * -12L;

        ldatum = ljahr * 10000 + lmonat * 100 + ltag;
    }
    char cdatum[11];
    AllgDatumLong2CharTTMMJJJJ(ldatum, cdatum);
    GetDlgItem(IDC_STATIC_VALUTA_DATUM)->SetWindowText(cdatum);
}

bool CDSammelAufDef::ValutaInDays()
{
    return AeGetApp()->IsRS()
        || AeGetApp()->IsBG()
        || AeGetApp()->IsDE();

}
