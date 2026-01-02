// DServiceZinsen.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "AeDoc.h"
#include "AeFView.h"
#include "DServiceZinsen.h"


// CDServiceZinsen-Dialogfeld

IMPLEMENT_DYNAMIC(CDServiceZinsen, CDialog)
CDServiceZinsen::CDServiceZinsen(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDServiceZinsen::IDD, pParent)
{
    m_csPrice = _T("");
    m_csName = _T("");
    m_CT_From = 0;
    m_CT_To = 0;
    m_iTax = 2;
    m_lActDate = 0;
    m_ptrDoc = NULL;
    m_PosNr = -1;
}

CDServiceZinsen::~CDServiceZinsen()
{
}

void CDServiceZinsen::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_TAX, m_ComboTax);
    DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_DT_From);
    DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_DT_To);
    DDX_Control(pDX, IDC_EDIT_PRICE, m_Edit_Price);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_CT_From);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_CT_To);
    DDX_Text(pDX, IDC_EDIT_PRICE, m_csPrice);
}


BEGIN_MESSAGE_MAP(CDServiceZinsen, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_BUCHEN, OnButtonBuchen)
END_MESSAGE_MAP()


// CDServiceZinsen-Meldungshandler

BOOL CDServiceZinsen::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow((AeGetApp()->m_pViewEing));
    m_ComboTax.ResetContent();
    double dTax;
    CString Tax;
    char cStd;
    int rc;
    int iStd = 0;

    for (int i = 0;; i++)
    {
        rc = AeGetApp()->GetTaxRates(i, cStd, dTax);
        if (rc == -1)
            break;
        Tax.Format("%0.2lf %%", dTax);
        m_ComboTax.AddString(Tax);
        if (cStd == '1')
            iStd = i;
    }
    m_ComboTax.SetCurSel(m_iTax);

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_lActDate = zeit.s.DATUM;
    CTime heute = CTimeFromDateLongMinTime(zeit.s.DATUM);
    CTimeSpan vor(360, 0, 0, 0);
    CTimeSpan nach(60, 0, 0, 0);
    CTime begin = heute - vor;
    CTime max = heute + nach;
    m_DT_From.SetRange(&begin, &max);
    m_DT_To.SetRange(&begin, &max);

    if (m_PosNr == -1)
    {
        m_DT_From.SetTime(&heute);
        m_DT_To.SetTime(&heute);
    }
    else
    {
        int startpos = m_csName.GetLength() -23;

        //long test;
        CTime anfang(atol(m_csName.Mid(startpos + 6, 4))
                    ,atol(m_csName.Mid(startpos + 3, 2))
                    ,atol(m_csName.Mid(startpos, 2))
                    , 0, 0, 0);
        CTime ende(atol(m_csName.Right(4 ))
                  ,atol(m_csName.Mid(startpos + 16, 2))
                  ,atol(m_csName.Mid(startpos + 13, 2))
                  , 0, 0, 0);
        m_DT_From.SetTime(&anfang);
        m_DT_To.SetTime(&ende);
        m_csName = m_csName.Left(startpos - 1);
    }
    GetDlgItem(IDC_STATIC_NAME)->SetWindowText(m_csName);
    m_DT_From.SetFocus();

    UpdateData(FALSE);

    return FALSE;

    //return TRUE;  // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDServiceZinsen::OnOK()
{
    UpdateData();
    if (GetFocus() == GetDlgItem(IDC_DATETIMEPICKER_FROM))
    {
        m_DT_To.SetFocus();
        return;
    }
    if (GetFocus() == GetDlgItem(IDC_DATETIMEPICKER_TO))
    {
        m_Edit_Price.SetFocus();
        m_Edit_Price.SetSel(0, -1, FALSE);
        return;
    }
    if (GetFocus() == GetDlgItem(IDC_EDIT_PRICE))
    {
        if (m_csPrice.IsEmpty())
        {
            MsgBoxOK(AETXT_INS_PRICE);
            return;
        }
        OnButtonBuchen();
        return;
    }

    OnButtonBuchen();
}

void CDServiceZinsen::OnButtonBuchen()
{
    UpdateData();
    m_csPrice.Replace(',', '.');
    if (m_CT_From.GetTime() > m_CT_To.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_FROM));
        return;
    }
    m_csName.Format("%6.6s %02d.%02d.%04d - %02d.%02d.%04d"
                    ,m_csName.GetString()
                    ,m_CT_From.GetDay()
                    ,m_CT_From.GetMonth()
                    ,m_CT_From.GetYear()
                    ,m_CT_To.GetDay()
                    ,m_CT_To.GetMonth()
                    ,m_CT_To.GetYear() );
    CAUFPOSBUCH aufposbuch;
    AllgStrCopy(aufposbuch.s.ARTIKEL_NAME, m_csName, L_AUFPOSBUCH_ARTIKEL_NAME);
    aufposbuch.s.CODE_TYPE = m_sServiceNo;
    double dPrice = atof(m_csPrice);
    aufposbuch.s.MENGEBESTELLT = 1;
    sprintf(aufposbuch.s.MWSTSCHLUESSEL, "%d", m_ComboTax.GetCurSel());
    aufposbuch.s.NETPRICE = dPrice;
    aufposbuch.s.PREISEKAPO = aufposbuch.s.NETPRICE;
    aufposbuch.s.PREISEKGROSSO = aufposbuch.s.NETPRICE;
    //Buchung
    BeginWaitCursor();
    if (m_PosNr == -1)
    {
        aufposbuch.Server(AasrvWritetextpos, PIPE_AE_SRV);
        if (aufposbuch.rc < SRV_OK)
            return;
        m_ptrDoc->AddPosition(aufposbuch.s);
    }
    else
    {
        aufposbuch.s.POSNR = m_PosNr;
        aufposbuch.Server(AasrvChangetextpos, PIPE_AE_SRV);
        if (aufposbuch.rc < SRV_OK)
            return;
        m_ptrDoc->UpdPosition(m_PosNr, aufposbuch.s);
    }
    //Kopfinformationen aktualisieren
    ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerte(
        aufposbuch.s.ANZPOS,
        aufposbuch.s.WERTAUFTRAG,
        aufposbuch.s.WERTLIEFERUNG,
        aufposbuch.s.WERTZEILEN,
        aufposbuch.s.BALANCE,
        aufposbuch.s.BALANCE2 );
    ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerteBG(aufposbuch.s.WERTNETTO_FV,
        aufposbuch.s.WERTTAX_FV,
        aufposbuch.s.WERTNETTO_KK,
        aufposbuch.s.WERTTAX_KK,
        aufposbuch.s.WERTNETTO_EH,
        aufposbuch.s.WERTTAX_EH,
        aufposbuch.s.WERTEXCLUSIVE );
    EndWaitCursor();

    CDialogMultiLang::OnOK();
}
