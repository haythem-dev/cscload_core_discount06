// DViewPos.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "AeFView.h"
#include <artikel.h>
#include <artsel.h>
#include "DBTMLicense.h"
#include "DViewRabs.h"
#include "DViewPos.h"
#include "PriceType.h"

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES Charge[] =
{
    0,  "", 150, LVCFMT_LEFT,
    1,  "",  90, LVCFMT_LEFT,
    2,  "",  60, LVCFMT_RIGHT,
    -1, "",   0, 0
};

#define NUM_CHARGE 3


// CDViewPos-Dialogfeld

IMPLEMENT_DYNAMIC(CDViewPos, CDialog)
CDViewPos::CDViewPos(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDViewPos::IDD, pParent)
    , m_csNatra(_T(""))
{
    m_csPZN = _T("");
    m_csARTIKELNAME = _T("");
    m_csMENGE = _T("1");
    m_csRabatt = _T("");
    m_cAArt = _T("");
    m_csTaxlevel = _T("0");
    m_csCharge = _T("");
    m_csAVP = _T("");
    m_csSpanne = _T("");
}

CDViewPos::~CDViewPos()
{
}

void CDViewPos::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_Edit_MENGE);
    DDX_Control(pDX, IDC_EDIT_RABATT, m_Edit_RABATT);
    DDX_Control(pDX, IDC_COMBO_TYP, m_ComboTyp);
    DDX_Control(pDX, IDC_EDIT_NAME, m_Edit_ARTIKELNAME);
    DDX_Control(pDX, IDC_EDIT_PZN, m_Edit_PZN);
    DDX_Control(pDX, IDC_EDIT_BESTAND, m_Edit_BESTAND);
    DDX_Control(pDX, IDC_EDIT_AEP, m_Edit_AEP);
    DDX_Control(pDX, IDC_EDIT_AVP, m_Edit_AVP);
    DDX_Control(pDX, IDC_EDIT_RAB_PREIS, m_Edit_PREIS_RAB);
    DDX_Control(pDX, IDC_EDIT_WERT_POS, m_Edit_WERT_POS);
    DDX_Control(pDX, IDC_EDIT_SPANNE, m_Edit_SPANNE);
    DDX_Text(pDX, IDC_EDIT_NAME, m_csARTIKELNAME);
    DDX_Text(pDX, IDC_EDIT_PZN, m_csPZN);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_csMENGE);
    DDX_Text(pDX, IDC_EDIT_BESTAND, m_csBestand);
    DDX_Text(pDX, IDC_EDIT_AEP, m_csAEP);
    DDX_Text(pDX, IDC_EDIT_AVP, m_csAVP);
    DDX_Text(pDX, IDC_EDIT_RAB_PREIS, m_csRabPreis);
    DDX_Text(pDX, IDC_EDIT_WERT_POS, m_csWertPos);
    DDX_Text(pDX, IDC_EDIT_RABATT, m_csRabatt);
    DDX_Text(pDX, IDC_EDIT_SPANNE, m_csSpanne);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_EDIT_MENGE_NATRA, m_Edit_Natra);
    DDX_Text(pDX, IDC_EDIT_MENGE_NATRA, m_csNatra);
}


BEGIN_MESSAGE_MAP(CDViewPos, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_CALC, OnButtonCalc)
    ON_BN_CLICKED(IDC_BUTTON_BUCH, OnButtonBuchen)
    ON_CBN_SELCHANGE(IDC_COMBO_TYP, OnCbnSelchangeComboTyp)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDViewPos-Meldungshandler
void CDViewPos::OnButtonBuchen()
{
    UpdateData();
    int selpos = m_ComboTyp.GetCurSel();
    CString chPreistyp;
    m_ComboTyp.GetLBText(selpos, chPreistyp);
    short sPreistyp = CharToShort(chPreistyp.GetAt(0));
    m_sPreistyp = CPriceType::CorrectPriceType3(sPreistyp, m_csOpi, m_csEinzelhandel);

    GetBTMLicense();

    if (AeGetApp()->IsAuftNoPromo())
    {
        m_csRabatt.Replace(',', '.');
    }
    else if (m_csSaveRabatt != m_csRabatt)
    {
        if (!ValidateRebateInput())
        {
            return;
        }
    }
    else
    {
        m_csRabatt = "0";
        UpdateData(FALSE);
    }
    if (m_List1.GetItemCount() > 0)
    {
        int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            m_csCharge = m_List1.GetItemText(pos, 0);
        }
    }

    CDialogMultiLang::OnOK();
}

void CDViewPos::GetBTMLicense()
{
    if (m_csOpi == "1")
    {
        if (m_CBTMLicense.IsEmpty())
        {
            CDBTMLicense dlgBTMLicense;
            if (dlgBTMLicense.DoModal() == IDOK)
            {
                m_lDatumBTM = dlgBTMLicense.m_lDatum;
                m_CBTMLicense = dlgBTMLicense.m_CBTMLicense;
            }
        }
    }
}

bool CDViewPos::ValidateRebateInput()
{
    m_csRabatt.Replace(',', '.');
    if (atof(m_csSaveRabatt) < atof(m_csRabatt))
    {
        if (!GetAeUser().IsDiscountUp())
        {
            MsgBoxOK(AETXT_RABATT_KLEIN);
            m_csRabatt = m_csSaveRabatt;
            m_Edit_RABATT.SetFocus();
            m_Edit_RABATT.SetSel(0, -1, FALSE);
            UpdateData(FALSE);
            return false;
        }
    }
    return true;
}

void CDViewPos::OnButtonCalc()
{
    GetBTMLicense();

    UpdateData();
    CAUFPOSBUCH aufposbuch;
    //Versorgung Übergabestruktur
    aufposbuch.s.MENGENATRA        = 0;
    aufposbuch.s.MENGEBESTELLT     = atol(m_csMENGE);
    aufposbuch.s.MENGEBESTAETIGT   = atol(m_csMENGE);
    aufposbuch.s.ARTIKEL_NR        = atol(m_csPZN);
    aufposbuch.s.STATUS            = ITEM_STAT_NORMAL;
    int selpos = m_ComboTyp.GetCurSel();
    CString chPreistyp;
    m_ComboTyp.GetLBText(selpos, chPreistyp);
    short sPreistyp = CharToShort(chPreistyp.GetAt(0));
    aufposbuch.s.PREIS_TYP         = CPriceType::CorrectPriceType3(sPreistyp, m_csOpi, m_csEinzelhandel);
    aufposbuch.s.DISCOUNTVALPCTMAN = 0;
    BeginWaitCursor();
    if (AeGetApp()->IsAuftNoPromo())
    {
        m_csRabatt.Replace(',', '.');
        aufposbuch.s.DISCOUNTVALPCTMAN = atof(m_csRabatt);
    }
    if (m_csSaveRabatt != m_csRabatt)
    {
        if (!ValidateRebateInput())
        {
            EndWaitCursor();
            return;
        }
        aufposbuch.s.DISCOUNTVALPCTMAN = atof(m_csRabatt);
    }
    if (m_bIgnore)
    {
        aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
    }
    aufposbuch.Server(AasrvCalcpos, PIPE_AE_SRV);
    EndWaitCursor();
    if (aufposbuch.rc == -2) //wenn ich nicht darf , dann raus
    {
        CDialogMultiLang::OnCancel();
    }
    if (aufposbuch.s.STATUS == ITEM_STAT_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE)          //zugelassener Preis überschritten
    {
        if (MsgBoxYesNo(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_1), MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
        {
            CDialogMultiLang::OnCancel();
        }
        m_bIgnore = TRUE;
        aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
    }

    else if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE)             //zugelassener Preis überschritten
    {
        if (MsgBoxYesNo(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_2), MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
        {
            CDialogMultiLang::OnCancel();
        }
        m_bIgnore = TRUE;
        aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
    }

    else if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION_06)             //zugelassener Preis überschritten
    {
        if (MsgBoxYesNo(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_3), MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
        {
            CDialogMultiLang::OnCancel();
        }
        m_bIgnore = TRUE;
        aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
    }

    else if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_MWP_EXCEEDANCE)            //zugelassener Preis überschritten
    {
        MsgBoxOK(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_0));
        m_bIgnore = TRUE;
        aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
    }

    else if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION)            //zugelassener Preis überschritten
    {
        MsgBoxOK(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_4));
        m_bIgnore = TRUE;
        aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
    }

    double dTax;
    char cStd;
    AeGetApp()->GetTaxRates(atoi(m_csTaxlevel), cStd, dTax);
    aufposbuch.s.PREISFAKTUR = aufposbuch.s.PREISFAKTUR * (100 + dTax) / 100;
    m_csRabPreis.Format("%0.2lf", aufposbuch.s.PREISFAKTUR);
    m_csAVP.Format("%0.2lf", aufposbuch.s.PREISVKAPO);
    m_csWertPos.Format("%0.2lf", (aufposbuch.s.PREISFAKTUR * aufposbuch.s.MENGEBESTAETIGT));
    UpdateData(FALSE);
    GetDlgItem(IDC_BUTTON_BUCH)->SetFocus();
}

void CDViewPos::OnOK()
{
    UpdateData();
    if (GetFocus() == GetDlgItem(IDC_EDIT_MENGE))
    {
        if (AeGetApp()->IsNatraEingabe())
        {
            GetDlgItem(IDC_EDIT_MENGE_NATRA)->SetFocus();
            return;
        }
        if (GetDlgItem(IDC_EDIT_RABATT)->IsWindowEnabled())
        {
            ((CAeFView*)AeGetApp()->m_pViewEing)->m_pDlgRab->GetRabs(atol(m_csMENGE));
            UpdateRebateFromCstDiscount();
            UpdateData(FALSE);
            GetDlgItem( IDC_BUTTON_CALC )->SetFocus();
        }
        else
        {
            GetDlgItem(IDC_BUTTON_CALC)->SetFocus();
        }
        return;
    }
    if (GetFocus() == GetDlgItem(IDC_EDIT_MENGE_NATRA))
    {
        GetDlgItem(IDC_EDIT_RABATT)->SetFocus();
    }
    else if ((GetFocus() == GetDlgItem(IDC_EDIT_RABATT)) || (GetFocus() == GetDlgItem(IDC_BUTTON_CALC)))
    {
        OnButtonCalc();
    }
    else if (GetFocus() == GetDlgItem(IDC_BUTTON_BUCH))
    {
        OnButtonBuchen();
    }
    else
    {
        m_Edit_MENGE.SetFocus();
        m_Edit_MENGE.SetSel(0, -1, FALSE);
    }
}

void CDViewPos::UpdateRebateFromCstDiscount()
{
    CString strRebate;
    strRebate.Format("%0.2lf", ((CAeFView*)AeGetApp()->m_pViewEing)->m_dCstDiscount);
    if (m_csSaveRabatt != m_csRabatt)
    {
        if (atof(m_csRabatt) > atof(strRebate))
        {
            m_csSaveRabatt = strRebate;
            m_csRabatt = strRebate;
        }
    }
    else if (m_csRabatt != strRebate)
    {
        m_csSaveRabatt = strRebate;
        m_csRabatt = strRebate;
    }
}

BOOL CDViewPos::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_bIgnore = FALSE;
    Charge[0].Columns = CResString::ex().getStrTblText(AETXT_CHARGE);
    Charge[1].Columns = CResString::ex().getStrTblText(AETXT_VERFALLDATUM);
    Charge[2].Columns = CResString::ex().getStrTblText(AETXT_BESTAND);

    DWORD dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_List1.SetExtendedStyle(dwOldBits);

    m_List1.ModifyStyle(0, LVS_SHOWSELALWAYS);

    if (!CListCtrlHelper::AddColumns(Charge, m_List1))
    {
        return FALSE;
    }

    if (AeGetApp()->IsNatraEingabe())
    {
        GetDlgItem(IDC_STATIC_NATRA)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NATRA)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_MENGE_NATRA)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MENGE_NATRA)->ShowWindow(SW_SHOW);
    }

    CenterWindow((AeGetApp()->m_pViewEing));
    m_ComboTyp.ResetContent();
    int counttyp = ((CAeFView*)AeGetApp()->m_pViewEing)->m_ComboTyp.GetCount();
    CString typtext;
    for (int i = 0; i < counttyp; i++)
    {
        ((CAeFView*)AeGetApp()->m_pViewEing)->m_ComboTyp.GetLBText(i, typtext);
        m_ComboTyp.AddString(typtext);
    }

    int selpos;
    CString chPreistyp;
    chPreistyp.Format("%d", m_sPreistyp);
    selpos = m_ComboTyp.FindString(-1, chPreistyp);
    if (selpos < 0)
        selpos = 0;
    m_ComboTyp.SetCurSel(selpos);
    UpdateData(FALSE);
    OnCbnSelchangeComboTyp();
    if ((m_cAArt == "RO") || (m_cAArt == "TO") || (m_cAArt == "TI"))
    {
        GetDlgItem(IDC_STATIC_RABATT)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_RABATT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_RABATT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_RABATT)->ShowWindow(SW_HIDE);
    }
    m_csSaveRabatt = m_csRabatt;

    GetDlgItem(IDC_STATIC_VERFALL)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_VERFALL)->ShowWindow(SW_HIDE);
    CARTCHARGE charge;
    charge.SetBranchno(AeGetApp()->FilialNrActual());
    charge.SetArticleno(atol(m_csPZN));
    CStringArray s;
    s.SetSize(NUM_CHARGE);
    char error_msg[80];
    long lDate = AeGetApp()->GetCurrentDate();
    long lDateMin = AllgAddDate(lDate, 90, error_msg);
    long datumverfall = 99999999;
    m_List1.DeleteAllItems();
    BeginWaitCursor();

    // standardmaesig keine Chargenauswahl
    // daher erster Satz leer
    s[0].Empty();
    s[1].Empty();
    s[2].Empty();

    if (!CListCtrlHelper::AppendItem(m_List1, NUM_CHARGE, s))
    {
        return TRUE;
    }

    for (;;)
    {
        if (charge.SelList() != SRV_OK)
            break;
        if (charge.GetStock() == 0)
            continue;
        ppString strcharge;
        charge.GetChargennr(strcharge);
        s[0] = strcharge;
        s[1] = DDMMYYYYStringFromDateLong(charge.GetExpirydate());
        s[2].Format("%d", charge.GetStock());
        datumverfall = (charge.GetExpirydate() < datumverfall) ? charge.GetExpirydate() : 99999999;
        if (lDateMin > datumverfall)
        {
            CString csFehler;
            csFehler.Format(CResString::ex().getStrTblText(AETXT_VERFALL_KRIT), s[1].GetString());
            GetDlgItem(IDC_STATIC_VERFALL)->SetWindowText(csFehler);
            GetDlgItem(IDC_STATIC_VERFALL)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_VERFALL)->ShowWindow(SW_SHOW);
        }

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_CHARGE, s))
        {
            return TRUE;
        }
    }
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);

    OnButtonCalc();
    EndWaitCursor();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDViewPos::OnCbnSelchangeComboTyp()
{
    if (m_cAArt == "TO" || m_cAArt == "TI")
    {
        return;
    }
    UpdateData();
    CPREISANZTYP typ;
    int selpos = m_ComboTyp.GetCurSel();
    CString chPreistyp;
    m_ComboTyp.GetLBText(selpos, chPreistyp);
    short sPreistyp = CharToShort(chPreistyp.GetAt(0));
    if (sPreistyp == 0)
    {
        typ.SetArtikel_nr(atol(m_csPZN));
        typ.SetPreis_typ(sPreistyp);
        if (!typ.SelPreis())
        {
            if (typ.GetPreisekapo() == 0.00)
            {
                MsgBoxOK(AETXT_NO_VALID_PRICE);
                chPreistyp.Format("%d", m_sPreistyp);
                selpos = m_ComboTyp.FindString(-1, chPreistyp);
                m_ComboTyp.SetCurSel(selpos);
                UpdateData(FALSE);
                return;
            }
        }
        chPreistyp.Format("%d", m_sPreistyp);
        selpos = m_ComboTyp.FindString(-1, chPreistyp);
        m_ComboTyp.SetCurSel(selpos);
    }
    if (sPreistyp == 1)
    {
        if (m_csKKCode.IsEmpty())
        {
            MsgBoxOK(AETXT_NO_KK_CODE);
            if (m_sPreistyp == 1)
            {
                m_ComboTyp.SetCurSel(0);
                m_sPreistyp = 0;
                UpdateData(FALSE);
                return;
            }
        }
        if (!AeGetApp()->IsKndKasse())
        {
            MsgBoxOK(AETXT_NO_KK_CODE_KND);
            if (m_sPreistyp == 1)
            {
                m_ComboTyp.SetCurSel(0);
                m_sPreistyp = 0;
                UpdateData(FALSE);
                return;
            }
            else
            {
                typ.SetArtikel_nr(atol(m_csPZN));
                typ.SetPreis_typ(sPreistyp);
                if (!typ.SelPreis())
                {
                    if (typ.GetPreisekapo() == 0.00)
                    {
                        MsgBoxOK(AETXT_NO_VALID_PRICE);
                        m_ComboTyp.SetCurSel(0);
                        m_sPreistyp = 0;
                        UpdateData(FALSE);
                        return;
                    }
                }
                chPreistyp.Format("%d", m_sPreistyp);
                selpos = m_ComboTyp.FindString(-1, chPreistyp);
                m_ComboTyp.SetCurSel(selpos);
            }
        }
    }
    else if (sPreistyp == 2)
    {
        if (m_csOpi == "1")
        {
            MsgBoxOK(AETXT_NO_RETAIL);
            if (m_sPreistyp == 2)
            {
                m_ComboTyp.SetCurSel(0);
                m_sPreistyp = 0;
                UpdateData(FALSE);
                return;
            }
            else
            {
                typ.SetArtikel_nr(atol(m_csPZN));
                typ.SetPreis_typ(sPreistyp);
                if (!typ.SelPreis())
                {
                    if (typ.GetPreisekapo() == 0.00)
                    {
                        MsgBoxOK(AETXT_NO_VALID_PRICE);
                        m_ComboTyp.SetCurSel(0);
                        m_sPreistyp = 0;
                        UpdateData(FALSE);
                        return;
                    }
                }
                chPreistyp.Format("%d", m_sPreistyp);
                selpos = m_ComboTyp.FindString(-1, chPreistyp);
                m_ComboTyp.SetCurSel(selpos);
            }
        }
        else if (m_csEinzelhandel == "1")
        {
            if (!GetAeUser().IsEinzelhandelApo())
            {
                MsgBoxOK(AETXT_NO_RETAIL);
                if (m_sPreistyp == 2)
                {
                    m_ComboTyp.SetCurSel(0);
                    m_sPreistyp = 0;
                    UpdateData(FALSE);
                    return;
                }
                else
                {
                    chPreistyp.Format("%d", m_sPreistyp);
                    selpos = m_ComboTyp.FindString(-1, chPreistyp);
                    m_ComboTyp.SetCurSel(selpos);
                }
            }
        }
        if (!AeGetApp()->IsKndRetail())
        {
            MsgBoxOK(AETXT_NO_RETAIL_KND);
            if (m_sPreistyp == 2)
            {
                m_ComboTyp.SetCurSel(0);
                m_sPreistyp = 0;
                UpdateData(FALSE);
                return;
            }
            else
            {
                chPreistyp.Format("%d", m_sPreistyp);
                selpos = m_ComboTyp.FindString(-1, chPreistyp);
                m_ComboTyp.SetCurSel(selpos);
            }
        }
    }
    if (((CAeFView*)AeGetApp()->m_pViewEing)->m_pDlgRab->m_sPreistyp != sPreistyp)
    {
        ((CAeFView*)AeGetApp()->m_pViewEing)->m_pDlgRab->m_sPreistyp = sPreistyp;
        if (!AeGetApp()->IsAuftNoPromo())
        {
            ((CAeFView*)AeGetApp()->m_pViewEing)->m_pDlgRab->GetRabs(atol(m_csMENGE));
            ((CAeFView*)AeGetApp()->m_pViewEing)->m_pDlgRab->GetPage();
        }
    }
    if (!AeGetApp()->IsAuftNoPromo())
    {
        UpdateRebateFromCstDiscount();
    }

    typ.SetArtikel_nr(atol(m_csPZN));
    typ.SetPreis_typ(sPreistyp);
    if (!typ.SelPreis())
    {
        double dTax;
        char cStd;
        AeGetApp()->GetTaxRates(atoi(m_csTaxlevel), cStd, dTax);
        if (AeGetApp()->KndGruppe() == 0)
        {
            m_csAEP.Format("%0.2lf", typ.GetPreisekapo() * (100 + dTax) / 100);
        }
        else if (AeGetApp()->KndGruppe() == 0)
        {
            if (typ.GetPreisekgrossona() > 0)
            {
                m_csAEP.Format("%0.2lf", typ.GetPreisekgrossona() * (100 + dTax) / 100);
            }
            else
            {
                m_csAEP.Format("%0.2lf", typ.GetPreisekgrosso() * (100 + dTax) / 100);
            }
        }
        else
        {
            m_csAEP.Format("%0.2lf", typ.GetPreisekgrosso() * (100 + dTax) / 100);
        }
    }
    UpdateData(FALSE);
}

HBRUSH CDViewPos::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_VERFALL)
        pDC->SetTextColor(RGB(200, 0, 0));
    return hbr;
}
