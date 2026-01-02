// DServicePos.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "AeDoc.h"
#include "AeFView.h"
#include "DServicePos.h"


// CDServicePos-Dialogfeld

IMPLEMENT_DYNAMIC(CDServicePos, CDialog)
CDServicePos::CDServicePos(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDServicePos::IDD, pParent)
{
    m_csQty = _T("");
    m_csPrice = _T("");
    m_csName = _T("");
    m_ptrDoc = NULL;
    m_PosNr = -1;
    m_iTax = 0;
}

CDServicePos::~CDServicePos()
{
}

void CDServicePos::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_TAX, m_ComboTax);
    DDX_Control(pDX, IDC_EDIT_QTY, m_Edit_Qty);
    DDX_Control(pDX, IDC_EDIT_PRICE, m_Edit_Price);
    DDX_Text(pDX, IDC_EDIT_QTY, m_csQty);
    DDX_Text(pDX, IDC_EDIT_PRICE, m_csPrice);
}


BEGIN_MESSAGE_MAP(CDServicePos, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_BUCHEN, OnButtonBuchen)
END_MESSAGE_MAP()


// CDServicePos-Meldungshandler

void CDServicePos::OnButtonBuchen()
{
    UpdateData();
    m_csPrice.Replace(',', '.');
    CAUFPOSBUCH aufposbuch;
    double dTax;
    double dPrice;
    char cStd;
    CString cPreis;
    AllgStrCopy(aufposbuch.s.ARTIKEL_NAME, m_csName, L_AUFPOSBUCH_ARTIKEL_NAME);
    dPrice = atof(m_csPrice);
    aufposbuch.s.MENGEBESTELLT = atol(m_csQty);
    sprintf(aufposbuch.s.MWSTSCHLUESSEL, "%d", m_ComboTax.GetCurSel());
    AeGetApp()->GetTaxRates(m_ComboTax.GetCurSel(), cStd, dTax);
    aufposbuch.s.NETPRICE = (dPrice / (100 + dTax)) * 100;
    cPreis.Format("%0.2lf", aufposbuch.s.NETPRICE);
    aufposbuch.s.NETPRICE = atof(cPreis);
    aufposbuch.s.PREISEKAPO = aufposbuch.s.NETPRICE;
    aufposbuch.s.PREISEKGROSSO = aufposbuch.s.NETPRICE;
    aufposbuch.s.CODE_TYPE = m_sServiceNo;
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
    ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerteBG(
        aufposbuch.s.WERTNETTO_FV,
        aufposbuch.s.WERTTAX_FV,
        aufposbuch.s.WERTNETTO_KK,
        aufposbuch.s.WERTTAX_KK,
        aufposbuch.s.WERTNETTO_EH,
        aufposbuch.s.WERTTAX_EH,
        aufposbuch.s.WERTEXCLUSIVE );
    EndWaitCursor();

    CDialogMultiLang::OnOK();
}

void CDServicePos::OnOK()
{
    UpdateData();
    if (GetFocus() == GetDlgItem(IDC_EDIT_QTY))
    {
        if (m_csQty.IsEmpty())
        {
            MsgBoxOK(IDP_MENGE_EINGEBEN);
            return;
        }
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
        GetDlgItem(IDC_COMBO_TAX)->SetFocus();
        return;
    }

    OnButtonBuchen();
}

BOOL CDServicePos::OnInitDialog()
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
    if (m_PosNr != -1)
    {
        m_ComboTax.SetCurSel(m_iTax);
    }
    else
    {
        m_ComboTax.SetCurSel(iStd);
    }
    GetDlgItem(IDC_STATIC_NAME)->SetWindowText(m_csName);

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
