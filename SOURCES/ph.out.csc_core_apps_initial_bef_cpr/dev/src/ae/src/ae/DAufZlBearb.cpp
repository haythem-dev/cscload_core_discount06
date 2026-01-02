// DAufZlBearb.cpp : implementation file
//

#include "stdafx.h"
#include "AeFView.h"
#include <artsel.h>
#include <artikel.h>
#include <tender.h>
#include "DCheckNachl.h"
#include "DAufZlBearb.h"

#define MAXIMUM_PCT_STELLEN     4

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES Charge[] =
{
    0,  "", 150, LVCFMT_LEFT,
    1,  "",  90, LVCFMT_LEFT,
    2,  "",  60, LVCFMT_RIGHT,
    -1, "",   0, 0
};
#define NUM_CHARGE 3

/////////////////////////////////////////////////////////////////////////////
// CDAufZlBearb dialog


CDAufZlBearb::CDAufZlBearb(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAufZlBearb::IDD, pParent)
    , m_CPreis(_T(""))
    , m_CArtCode(_T(""))
{
    m_CArtNr = _T("");
    m_CBestMenge = _T("");
    m_AngefMenge = 0;
    m_CNatRabMenge = _T("");
    m_CArtName = _T("");
    m_CArtEinh = _T("");
    m_CBemerkung = _T("");
    m_CVerbundMenge = _T("");
    m_CVerbundFiliale = _T("");
    m_CNatRab = _T("");
    m_bNN = FALSE;
    m_BuchStat = 0;         //Buchungsart normal einstellen
    m_save_Typ = 0;
    m_CPct = _T("");
    m_CPctMan = _T("");
    m_CCharge = _T("");
    m_bFixCharge = FALSE;
    m_bChargenExist = FALSE;
    m_Plus = 0;
    m_CDiscountMode = 0;
}


void CDAufZlBearb::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_NATRAB, m_EditNatRab);
    DDX_Control(pDX, IDC_COMBO_BUCH_STAT, m_CBoxBuchStat);
    DDX_Control(pDX, IDC_EDITTEXT, m_EditBemerkung);
    DDX_Control(pDX, IDC_EDIT_BEST_MENGE, m_EditAngefMenge);
    DDX_Text(pDX, IDC_STATIC_ART_NR, m_CArtNr);
    DDX_Text(pDX, IDC_STATIC_LIF_MENGE, m_CBestMenge);
    DDX_Text(pDX, IDC_EDIT_BEST_MENGE, m_AngefMenge);
    DDX_Text(pDX, IDC_STATIC_NAT_RAB, m_CNatRabMenge);
    DDX_Text(pDX, IDC_STATIC_ART_NAME, m_CArtName);
    DDX_Text(pDX, IDC_STATIC_ART_EINH, m_CArtEinh);
    DDX_Text(pDX, IDC_EDITTEXT, m_CBemerkung);
    DDX_CBIndex(pDX, IDC_COMBO_BUCH_STAT, m_BuchStat);
    DDX_Text(pDX, IDC_STATIC_VERBUND, m_CVerbundMenge);
    DDX_Text(pDX, IDC_STATIC_VERBUND_FILIALE, m_CVerbundFiliale);
    DDX_Text(pDX, IDC_EDIT_NATRAB, m_CNatRab);
    DDX_Check(pDX, IDC_CHECK_NN, m_bNN);
    DDX_Control(pDX, IDC_COMBO_FREE_PRICE, m_Combo_FreePrice);
    DDX_Control(pDX, IDC_EDIT_PREIS, m_EditPreis);
    DDX_Text(pDX, IDC_EDIT_PREIS, m_CPreis);
    DDX_Control(pDX, IDC_COMBO_TYP, m_ComboTyp);
    DDX_Control(pDX, IDC_EDIT_RABATT, m_EditPct);
    DDX_Text(pDX, IDC_EDIT_RABATT, m_CPct);
    DDX_Control(pDX, IDC_EDIT_RABATT_MAN, m_EditPctMan);
    DDX_Text(pDX, IDC_EDIT_RABATT_MAN, m_CPctMan);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Text(pDX, IDC_STATIC_ART_CODE, m_CArtCode);
}


BEGIN_MESSAGE_MAP(CDAufZlBearb, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDITTEXT, OnChangeEdittext)
    ON_EN_CHANGE(IDC_EDIT_BEST_MENGE, OnChangeEditBestMenge)
    ON_CBN_SELCHANGE(IDC_COMBO_BUCH_STAT, OnSelchangeComboBuchStat)
    ON_EN_CHANGE(IDC_EDIT_NATRAB, OnChangeEditNatrab)
    ON_EN_CHANGE(IDC_EDIT_PREIS, OnChangeEditPreis)
    ON_CBN_SELCHANGE(IDC_COMBO_TYP, OnSelchangeComboTyp)
    ON_EN_CHANGE(IDC_EDIT_RABATT_MAN, OnChangeEditPctMan)
    ON_BN_CLICKED(IDC_RADIO_FIX_BATCH2, OnRadioBatch)
    ON_BN_CLICKED(IDC_RADIO_WISH_BATCH, OnRadioBatch)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDAufZlBearb::OnNMClickList1)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDAufZlBearb message handlers

BOOL CDAufZlBearb::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_hin.s.ARTIKEL_NR = atol (m_CArtNr);
    m_hin.s.FILIALNR = AeGetApp()->FilialNrActual();
    m_hin.s.ETARTKLASSE1 = AeGetApp()->KndKlasse1();
    m_hin.s.CODEBLOCAGE[0] = AeGetApp()->IsPrintCode() ? '1' : '0';
    BeginWaitCursor();
    m_hin.Server(AatartAa_sel_artnr);
    EndWaitCursor();

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
    CARTCHARGE charge;
    charge.SetBranchno(AeGetApp()->FilialNrActual());
    charge.SetArticleno(atol(m_CArtNr));
    CStringArray s;
    s.SetSize(NUM_CHARGE);
    ppString strcharge;
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

    int pos = 0;
    for (;;)
    {
        if (m_CAufArt == "QA")
        {
            if (charge.SelListQua() != SRV_OK) break;
        }
        else
        {
            if (charge.SelList() != SRV_OK) break;
        }
        m_bChargenExist = TRUE;
        charge.GetChargennr(strcharge);
        if (m_CCharge == strcharge)
        {
            pos = m_List1.GetItemCount();
        }
        s[0] = strcharge;
        s[1] = DDMMYYYYStringFromDateLong(charge.GetExpirydate());
        s[2].Format("%d", charge.GetStock());

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_CHARGE, s))
        {
            return TRUE;
        }
    }
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, pos);

    if (!m_bChargenExist)   //wenn keine Chargen vorhanden sind, auch keine Anzeige
    {
        GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_RADIO_FIX_BATCH2)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO_FIX_BATCH2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_RADIO_WISH_BATCH)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO_WISH_BATCH)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CHARGE_TYP)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_CHARGE_TYP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CHARGE)->ShowWindow(SW_HIDE);
    }
    //Ronnie
    if (m_bFixCharge)
    {
        CheckRadioButton(IDC_RADIO_WISH_BATCH, IDC_RADIO_FIX_BATCH2, IDC_RADIO_FIX_BATCH2);
    }
    else if (!m_CCharge.IsEmpty())
    {
        CheckRadioButton(IDC_RADIO_WISH_BATCH, IDC_RADIO_FIX_BATCH2, IDC_RADIO_WISH_BATCH);
    }

    if (AeGetApp()->IsTOOpen())
    {
        m_lTenderNo = ((CAeFView*)AeGetApp()->m_pViewEing)->GetTenderno();
        CTENDERARTICLE art;
        CTENDERSTOCK stock;
        CTENDERINFO info;
        info.SetTenderno(m_lTenderNo);
        info.SelTender();
        m_dPct = info.GetExceedancepct();
        art.SetArticleno(atol(m_CArtNr));
        art.SetTenderno(m_lTenderNo);
        art.SelArt();
        stock.SetFilialnr(AeGetApp()->VzNr());
        stock.SetArtikel_nr(art.GetArticleno());
        stock.SetTenderno(art.GetTenderno());
        stock.SelQty();
        m_lBestand = stock.GetBestand();
        m_lDeliveryqty = stock.GetDeliveryqty();
        m_lContractqty = art.GetContractqty();
        if (m_lBestand == 0)
            m_lMaxqty = m_AngefMenge;
        if (AeGetApp()->IsBG() && !AeGetApp()->IsTOStaat())
        {
            m_lMaxqty = m_lBestand + m_AngefMenge;
        }
        else
        {
            if ((atof(m_CPct) > 0) || GetAeUser().IsDiscountUp())
            {
                GetDlgItem(IDC_STATIC_PCT)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_STATIC_PCT_MAN)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_RABATT)->ShowWindow(SW_SHOW);
                GetDlgItem(IDC_EDIT_RABATT_MAN)->EnableWindow(TRUE);
                GetDlgItem(IDC_EDIT_RABATT_MAN)->ShowWindow(SW_SHOW);
            }
            double faktor = (m_dPct + 100) / 100;
            double dmax = (m_lContractqty * faktor) + 0.99;
            long maxmeng = (long)dmax;
            m_lMaxqty = maxmeng - (m_lDeliveryqty - m_AngefMenge);
        }
    }
    else if (AeGetApp()->IsBG())
    {
        GetDlgItem( IDC_COMBO_TYP )->EnableWindow(TRUE);
        GetDlgItem( IDC_COMBO_TYP )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_TYP )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_TYP )->ShowWindow(SW_SHOW);
        if (atof(m_CPct) > 0 || GetAeUser().IsDiscountUp())
        {
            GetDlgItem( IDC_STATIC_PCT )->ShowWindow(SW_SHOW);
            GetDlgItem( IDC_STATIC_PCT_MAN )->ShowWindow(SW_SHOW);
            GetDlgItem( IDC_EDIT_RABATT )->ShowWindow(SW_SHOW);
            GetDlgItem( IDC_EDIT_RABATT_MAN )->EnableWindow(TRUE);
            GetDlgItem( IDC_EDIT_RABATT_MAN )->ShowWindow(SW_SHOW);
        }
        m_ComboTyp.ResetContent();
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_FREIVERKAUF));
        if (AeGetApp()->IsKndKasse())
        {
            m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_KRANKENKASSE));
        }
        if (AeGetApp()->IsKndRetail())
        {
            if (!AllgBitleisteN((Bitleiste)m_hin.s.ETARTKLASSE1,6)) // kein opiat
            {
                if (AllgBitleisteN((Bitleiste)m_hin.s.ETARTKLASSE1,8)) // Preisgruppe 4
                {
                    if (GetAeUser().IsEinzelhandelApo())
                    {
                        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
                        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_MITUNDOHNE));
                    }
                }
                else
                {
                    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_EINZELHANDEL));
                    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_MITUNDOHNE));
                }
            }
        }
        int selpos;
        CString chPreistyp;
        chPreistyp.Format("%d",m_Typ);
        selpos = m_ComboTyp.FindString(-1,chPreistyp);
        m_ComboTyp.SetCurSel(selpos);
        m_save_Typ = m_Typ;
    }
    else if (AeGetApp()->IsBG() || AeGetApp()->IsRS() || (AeGetApp()->IsHR() && 
        (m_CDiscountMode == 0 || m_CDiscountMode == 3 || m_CDiscountMode == 4)))
    {
        if (atof(m_CPct) > 0 || GetAeUser().IsDiscountUp())
        {
            GetDlgItem(IDC_STATIC_PCT)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_PCT_MAN)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_RABATT)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_RABATT_MAN)->EnableWindow(TRUE);
            GetDlgItem(IDC_EDIT_RABATT_MAN)->ShowWindow(SW_SHOW);
        }
    }

    if (GetOrderType().IsFreePrice(AeGetApp()->FilialNrActual(), m_CAufArt))
    {
        CPRICEHIST hist;
        CString CStr;
        m_Combo_FreePrice.ResetContent();
        hist.SetArtikel_nr(atol(m_CArtNr));
        for (;;)
        {
            if (hist.Sel())
                break;
            CStr.Format("%.2lf", hist.GetAep());
            m_Combo_FreePrice.AddString(CStr);
        }
        if (!m_CPreis.IsEmpty())
        {
            if (m_Combo_FreePrice.SelectString(-1, m_CPreis) == CB_ERR)
            {
                m_Combo_FreePrice.SetWindowText(m_CPreis);
            }
        }
        GetDlgItem(IDC_COMBO_FREE_PRICE)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_FREE_PRICE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PREIS)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_PREIS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_PREIS)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PREIS)->ShowWindow(SW_HIDE);
    }
    else if (AeGetApp()->IsRS() && !AeGetApp()->IsTOOpen())
    {
        GetDlgItem(IDC_COMBO_FREE_PRICE)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_FREE_PRICE)->ShowWindow(SW_HIDE);
        if (GetAeUser().IsFreePrice())
        {
            GetDlgItem(IDC_EDIT_PREIS)->EnableWindow(TRUE);
            GetDlgItem(IDC_EDIT_PREIS)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_PREIS)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_PREIS)->ShowWindow(SW_SHOW);
        }
        else
        {
            GetDlgItem(IDC_EDIT_PREIS)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_PREIS)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_PREIS)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_PREIS)->ShowWindow(SW_HIDE);
            m_CPreis = "0";
        }
    }
    else
    {
        GetDlgItem(IDC_EDIT_PREIS)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PREIS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_FREE_PRICE)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_FREE_PRICE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PREIS)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_PREIS)->ShowWindow(SW_HIDE);
        m_CPreis = "0";
    }

    m_CBoxBuchStat.AddString(CResString::ex().getStrTblText(AETEXT_NORMAL));

    if (m_hin.s.IMPORTARTICLE == 1) //Importartikel
    {
        if (GetAeUser().IsDEGetter())
        {
            CCHECKIMEXBLOCKEXIST imex;
            imex.SetArticleno(m_hin.s.ARTIKEL_NR);
            if (imex.SelExist())
            {
                m_Plus = 1;
                m_CBoxBuchStat.AddString(CResString::ex().getStrTblText(AETXT_DISPONIEREN));
            }
        }
    }
    else
    {
        m_CBoxBuchStat.AddString(CResString::ex().getStrTblText(AETEXT_ZUGESAGT));
        if (   AllgBitleisteN((Bitleiste)m_hin.s.ETARTSCHALTER1, 3)             //ausser Handel
            || AllgBitleisteN((Bitleiste)m_hin.s.ETARTKLASSE1, 6)               //BTM
            || AllgBitleisteN((Bitleiste)m_hin.s.ETARTSCHALTER1, 4)             //Auslaufartikel
            || (   AeGetApp()->IsDE()                                           //in DE
                && (   m_hin.s.ARTIKELAKTIV[0] == '0'                           //Sperr- oder Löschkz
                    || m_hin.s.ARTIKEL_GESPERRT[0] == '1') )                    //gesperrt
             )
        {
            m_Plus = -1;
        }
        else
        {
            m_CBoxBuchStat.AddString(CResString::ex().getStrTblText(AETXT_DISPONIEREN));
        }

        m_CBoxBuchStat.AddString(CResString::ex().getStrTblText(AETXT_NACH));
    }
    m_CBoxBuchStat.SetCurSel(m_BuchStat);

    if (m_CAufArt == "UW" ||
        m_CAufArt == "AK" ||
        m_CAufArt == "MD" ||
        m_CAufArt == "OM" ||
        m_CAufArt == "UN")
    {
        GetDlgItem(IDC_STATIC_NAT_RAB)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_NN)->ShowWindow(SW_SHOW);
    }
    else if (AeGetApp()->IsBG())
    {
        GetDlgItem(IDC_STATIC_NAT_RAB)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_NN)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_NATRAB)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_NN)->ShowWindow(SW_HIDE);
    }
    m_save_CPreis       = m_CPreis;
    m_save_AngefMenge   = m_AngefMenge;
    m_save_BestMenge    = atol(m_CBestMenge);
    m_save_NatRab       = atol(m_CNatRabMenge);
    m_save_CBemerkung   = m_CBemerkung;
    m_save_BuchStat     = m_BuchStat;
    m_save_bNN          = m_bNN;
    m_save_CPctMan      = m_CPctMan;
    m_save_CCharge      = m_CCharge;
    m_save_bFixCharge   = m_bFixCharge;
    if (AllgBitleisteN((Bitleiste)m_hin.s.ETARTKLASSE1, 5)) // Tax-Artikel
    {
        GetDlgItem( IDC_COMBO_FREE_PRICE )->EnableWindow(FALSE);
        GetDlgItem( IDC_COMBO_FREE_PRICE )->ShowWindow(SW_HIDE);
        GetDlgItem( IDC_STATIC_PREIS )->EnableWindow(FALSE);
        GetDlgItem( IDC_STATIC_PREIS )->ShowWindow(SW_HIDE);
    }

    //Chargenauswahl
    if (m_bChargenExist)    //wenn keine Chargen vorhanden sind, auch keine Anzeige
    {
        if (AeGetApp()->IsOTforbiduserchangeBatch())
        {
            GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
            GetDlgItem(IDC_RADIO_FIX_BATCH2)->EnableWindow(FALSE);
            GetDlgItem(IDC_RADIO_WISH_BATCH)->EnableWindow(FALSE);
        }
        else
        {
            if (!AeGetApp()->IsOTwishBatch() && !AeGetApp()->IsOTfixBatch())
            {
                GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
            }
            if (AeGetApp()->IsOTfixBatch())
            {
                if (m_bFixCharge)
                {
                    CheckRadioButton(IDC_RADIO_WISH_BATCH, IDC_RADIO_FIX_BATCH2, IDC_RADIO_FIX_BATCH2);
                }
                GetDlgItem(IDC_RADIO_FIX_BATCH2)->EnableWindow(TRUE);
            }
            else
            {
                GetDlgItem(IDC_RADIO_FIX_BATCH2)->EnableWindow(FALSE);
            }
            if (AeGetApp()->IsOTwishBatch())
            {
                if (!m_CCharge.IsEmpty())
                {
                    CheckRadioButton(IDC_RADIO_WISH_BATCH, IDC_RADIO_FIX_BATCH2, IDC_RADIO_WISH_BATCH);
                }
                GetDlgItem(IDC_RADIO_WISH_BATCH)->EnableWindow(TRUE);
            }
            else
            {
                GetDlgItem(IDC_RADIO_WISH_BATCH)->EnableWindow(FALSE);
            }
        }
    }

    m_EditAngefMenge.SetFocus();
    CenterWindow();
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAufZlBearb::OnChangeEdittext()
{
    if (AeGetApp()->IsRS())
    {
        if (!AllgCheckPrintableSign(&m_EditBemerkung))
            return;
    }
    AllgLaengeKontr(&m_EditBemerkung, MAXIMUM_POS_BEM, AeGetApp()->Modus());
}

void CDAufZlBearb::OnChangeEditBestMenge()
{
    long buchmeng = AeGetApp()->IsTOOpen() ? m_lMaxqty : MAXIMUM_BUCH_MENGE;
    AllgWertKontr(&m_EditAngefMenge, buchmeng);
}

void CDAufZlBearb::OnSelchangeComboBuchStat()
{
    int old = m_BuchStat;
    if ((m_CBoxBuchStat.GetCurSel()) == (ITEM_STAT_NACHLIEFERN + m_Plus))
    {
        if (AllgBitleisteN((Bitleiste)m_hin.s.ETARTSCHALTER1, 3))
        {
            MsgBoxOK(IDP_NO_NACHL_AH);
            m_CBoxBuchStat.SetCurSel(old);
        }
        else if (!AllgBitleisteN((Bitleiste)m_hin.s.ETARTSCHALTER2, 15))
        {
            MsgBoxOK(IDP_NO_NACHL_NGEF);
            m_CBoxBuchStat.SetCurSel(old);
        }
        else if (!GetOrderType().IsNachlief(AeGetApp()->VzNr(), m_CAufArt))
        {
            MsgBoxOK(AETXT_NO_RESTDEL);
            m_CBoxBuchStat.SetCurSel(old);
        }
    }
    if ((m_CBoxBuchStat.GetCurSel()) == (ITEM_STAT_DISPO + m_Plus))
    {
        if (AllgBitleisteN((Bitleiste)m_hin.s.ETARTKLASSE1, 6)) // opiat
        {
            MsgBoxOK(IDP_NO_DISP_BTM);
            m_CBoxBuchStat.SetCurSel(old);
        }
    }
    m_BuchStat = m_CBoxBuchStat.GetCurSel() + m_Plus;
    if (m_Plus < 0 && m_BuchStat < 1)
        ++m_BuchStat;
}

void CDAufZlBearb::OnOK()
{
    UpdateData();
    if (GetDlgItem(IDC_COMBO_FREE_PRICE)->IsWindowEnabled())
    {
        double aep;
        CString cPreis;
        m_Combo_FreePrice.GetWindowText(m_CPreis);
        m_CPreis.Replace(',', '.');
        if (m_save_CPreis == m_CPreis)
        {
        }
        else if (!m_CPreis.IsEmpty())
        {
            double preis;
            if (m_CPreis.Find('%', 0) == -1)
            {
                preis = atof(m_CPreis);
            }
            else
            {
                aep = m_hin.s.PREISEKAPO;
                preis = aep * ((100 - (atof(m_CPreis))) / 100);
                m_CPreis.Format("%.2lf", preis);
            }
        }
        UpdateData(FALSE);
    }
    else if (GetDlgItem(IDC_EDIT_PREIS)->IsWindowEnabled())
    {
        if (m_save_CPreis == m_CPreis)
        {
        }
        else if (!m_CPreis.IsEmpty())
        {
            double aep;
            CString cPreis;
            cPreis = m_CPreis;
            AllgCStrCharToChar(cPreis, ',', '.');
            aep = m_hin.s.PREISEKAPO;
            double preis = atof(cPreis);
            if (preis > aep)
            {
                aep = aep + (aep * AeGetApp()->PriceRange() / 100);
                if (preis > aep)
                {
                    CString CStr;
                    CString CAep;
                    CAep.Format("%2.2f", m_hin.s.PREISEKAPO);
                    AllgCStrCharToChar(CAep, '.', ',');
                    CStr.Format(CResString::ex().getStrTblText(IDS_PRICE_OUT), m_CPreis.GetString(), CAep.GetString());
                    if (MsgBoxYesNo(CStr, MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
                    {
                        m_EditPreis.SetFocus();
                        m_EditPreis.SetSel(0, -1, FALSE);
                        return;
                    }
                }
            }
            else
            {
                aep = aep - (aep * AeGetApp()->PriceRange() / 100);
                if (preis < aep)
                {
                    CString CAep;
                    CAep.Format("%2.2f", m_hin.s.PREISEKAPO);
                    AllgCStrCharToChar(CAep, '.', ',');
                    CString CStr;
                    CStr.Format(CResString::ex().getStrTblText(IDS_PRICE_OUT), m_CPreis.GetString(), CAep.GetString());
                    if (MsgBoxYesNo(CStr, MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
                    {
                        m_EditPreis.SetFocus();
                        m_EditPreis.SetSel(0, -1, FALSE);
                        return;
                    }
                }
            }
        }
    }
    if (GetDlgItem(IDC_EDIT_RABATT_MAN)->IsWindowEnabled())
    {
        if (m_save_CPctMan == m_CPctMan)
        {
        }
        else if (!m_CPctMan.IsEmpty())
        {
            AllgCStrCharToChar(m_CPctMan, ',', '.');
            m_EditPctMan.SetWindowText(m_CPctMan);
        }
    }

    if (m_List1.GetItemCount() > 0)
    {
        int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            m_CCharge = m_List1.GetItemText(pos, 0);
        }
    }

    if (m_bChargenExist)
    {
        if (!AeGetApp()->IsOTforbiduserchangeBatch())
        {
            if (AeGetApp()->IsOTfixBatch() || AeGetApp()->IsOTwishBatch())
            {
                if (m_save_CCharge != m_CCharge)
                {
                    if (m_CCharge.IsEmpty())
                    {
                        if (AeGetApp()->IsOTfixBatch())
                        {
                            if (MsgBoxYesNo(AETXT_DEL_FIX_BATCH, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDNO) return;
                        }
                        else
                        {
                            if (MsgBoxYesNo(AETXT_DEL_WISH_BATCH, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDNO) return;
                        }
                    }
                    else
                    {
                        if (AeGetApp()->IsOTfixBatch())
                        {
                            CString CStr;
                            CStr.Format(CResString::ex().getStrTblText(AETXT_FIX_BATCH), m_CCharge.GetString());
                            if (MsgBoxYesNo(CStr, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDNO) return;
                        }
                        else
                        {
                            CString CStr;
                            CStr.Format(CResString::ex().getStrTblText(AETXT_WISH_BATCH), m_CCharge.GetString());
                            if (MsgBoxYesNo(CStr, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDNO) return;
                        }
                    }
                }
            }
        }
    }
    if (AeGetApp()->IsBG())
    {
        if (!AeGetApp()->IsTOOpen())
        {
            int selpos = m_ComboTyp.GetCurSel();
            CString chPreistyp;
            m_ComboTyp.GetLBText(selpos, chPreistyp);
            m_Typ = CharToShort(chPreistyp.GetAt(0));
        }
    }
    if (AeGetApp()->IsBG())
    {
        if (m_CAufArt != "FC") //bei FC-Order egal
        {
            if (m_save_NatRab < atol(m_CNatRab))
            {
                MsgBoxOK(AETXT_NATRA_DOWN);
                return;
            }
        }
    }
    if (m_save_AngefMenge != m_AngefMenge)
    {
        double preis;
        if (m_CPreis.IsEmpty())
        {
            preis = atof(m_CPreis);
        }
        else
        {
            preis = m_hin.s.PREISEKAPO;
        }
        // bei zu hohem Wert keine Zusammenfuehrung
        if (   AeGetApp()->IsRS()
            || AeGetApp()->IsBG()
            || AeGetApp()->IsHR() )
        {
            if ((m_AngefMenge * preis) >= 10000000)
            {
                MsgBoxOK(IDP_WARN_HOHER_WERT);
                return;
            }
            else if (AeGetApp()->IsRS())
            {
                if ((m_AngefMenge * m_hin.s.PREISEKGROSSO) >= 10000000)
                {
                    MsgBoxOK(IDP_WARN_HOHER_WERT);
                    return;
                }
            }
        }
        else if ((m_AngefMenge * preis) >= 100000)
        {
            MsgBoxOK(IDP_WARN_HOHER_WERT);
            return;
        }
    }
    if (m_save_AngefMenge == m_AngefMenge &&
        m_save_CBemerkung == m_CBemerkung &&
        m_save_CPreis == m_CPreis &&
        m_save_AngefMenge == m_save_BestMenge &&
        m_save_NatRab == atol(m_CNatRab) &&
        m_save_BuchStat == m_BuchStat &&
        m_save_Typ == m_Typ &&
        m_save_CPctMan == m_CPctMan &&
        m_save_CCharge == m_CCharge &&
        m_save_bNN == m_bNN &&
        m_save_bFixCharge == m_bFixCharge)
    {
        CDialogMultiLang::OnCancel();
        return;
    }
    CDialogMultiLang::OnOK();
}

void CDAufZlBearb::OnChangeEditNatrab()
{
    AllgWertKontr(&m_EditNatRab, MAXIMUM_NR_MENGE);
}

void CDAufZlBearb::OnChangeEditPreis()
{
    AllgWedDezimalKontr(&m_EditPreis, MAXIMUM_PREIS_STELLEN,MAXIMUM_NACHKOMMA);
}

void CDAufZlBearb::OnSelchangeComboTyp()
{
    int old = m_Typ;
    if ((m_ComboTyp.GetCurSel()) == 1)
    {
        if (!AeGetApp()->IsKndKasse())
        {
            MsgBoxOK(AETXT_NO_KK);
            m_ComboTyp.SetCurSel(old);
        }
    }
    m_Typ = m_CBoxBuchStat.GetCurSel();
}

void CDAufZlBearb::OnChangeEditPctMan()
{
    AllgWedDezimalKontr(&m_EditPctMan, MAXIMUM_PCT_STELLEN,MAXIMUM_NACHKOMMA);
    if (!GetAeUser().IsDiscountUp())
    {
        CString pct;
        m_EditPctMan.GetWindowText(pct);
        AllgCStrCharToChar(pct, ',', '.');
        if (atof(m_CPct) < atof(pct))
        {
            MsgBoxOK(AETXT_RABATT_KLEIN);
            m_EditPctMan.SetWindowText("");
            m_EditPctMan.SetFocus();
        }
    }
}

void CDAufZlBearb::OnRadioBatch()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos > 0)
    {
        if (GetCheckedRadioButton(IDC_RADIO_WISH_BATCH, IDC_RADIO_FIX_BATCH2) == IDC_RADIO_FIX_BATCH2)
        {
            m_bFixCharge = TRUE;
        }
        else
        {
            m_bFixCharge = FALSE;
        }
    }
    else
    {
        MsgBoxOK(AETXT_NO_BATCH);
        CheckRadioButton(IDC_RADIO_WISH_BATCH, IDC_RADIO_FIX_BATCH2, 0);
        m_bFixCharge = FALSE;
    }
}


void CDAufZlBearb::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    pNMItemActivate;
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos > 0)
    {
        if (AeGetApp()->IsOTwishBatch())
        {
            CheckRadioButton(IDC_RADIO_WISH_BATCH, IDC_RADIO_FIX_BATCH2, IDC_RADIO_WISH_BATCH);
            m_bFixCharge = FALSE;
        }
        else
        {
            CheckRadioButton(IDC_RADIO_WISH_BATCH, IDC_RADIO_FIX_BATCH2, IDC_RADIO_FIX_BATCH2);
            m_bFixCharge = TRUE;
        }
    }
    else
    {
        CheckRadioButton(IDC_RADIO_WISH_BATCH, IDC_RADIO_FIX_BATCH2, 0);
        m_bFixCharge = FALSE;
    }

    *pResult = 0L;
}
