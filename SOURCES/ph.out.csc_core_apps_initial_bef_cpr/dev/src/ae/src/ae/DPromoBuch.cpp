//DPromoBuch.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "rebateprice.h"
#include "AeFView.h"
#include "AeDoc.h"
#include <artsel.h>
#include <artikel.h>
#include "PMListctrl.h"
#include "PRListctrl.h"
#include <promo.h>
#include "DPromotionen.h"
#include <promoinfo.h>
#include "DPromoBuch.h"


// CDPromoBuch-Dialogfeld

IMPLEMENT_DYNAMIC(CDPromoBuch, CDialog)
CDPromoBuch::CDPromoBuch(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPromoBuch::IDD, pParent)
    , m_csSuch(_T(""))
{
    m_ptrDoc = NULL;
    m_cMinMeng = _T("");
    m_cMinValue = _T("");
    m_cPromotion = _T("");
    m_cEKG = _T("");
    m_cDISCGRP = _T("");
    m_cAddDisc = _T("");
    m_sSpec = 0;
    m_sPromono = 0;
    m_iItem = 0;
    m_iItem2 = 0;
    m_iItem_old = 0;
    m_iItem2_old = 0;
    m_iStellerTyp = 0;
    m_bSteller = false;
    m_List1 = new CPMListCtrl;
    assert(m_List1);
    m_List2 = new CPRListCtrl;
    assert(m_List2);
    m_dPct = 0.0;
    m_lManu = 0;
    m_sVznr = 0;
    m_sAnzList = 0;
    m_lMinQty = 0;
    m_dMinValue = 0.0;
    m_iFaktor = 0;
    bg = RGB(200,200,0);
    fg = RGB(0,0,0);
    bg2 = RGB(0,200,200);
    fg2 = RGB(0,0,0);
    bgg = RGB(0,255,0);
    fgb = RGB(0,0,0);
    bgy = RGB(255,255,0);
    m_bReturn = false;
    m_plTobook = NULL;
    m_pListPromo = NULL;
    m_pListMember = NULL;
    m_pListRabatte = NULL;
}

CDPromoBuch::~CDPromoBuch()
{
    delete m_List1;
    m_List1 = 0;
    delete m_List2;
    m_List2 = 0;
}

void CDPromoBuch::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, *m_List1);
    DDX_Control(pDX, IDC_LIST2, *m_List2);
    DDX_Control(pDX, IDC_COMBO_TYP, m_ComboTyp);
    DDX_Control(pDX, IDC_COMBO_FAKTOR, m_ComboFaktor);
    DDX_Text(pDX, IDC_EDIT_SUCH, m_csSuch);
    DDX_Control(pDX, IDC_EDIT_SUCH, m_editSuch);
}


BEGIN_MESSAGE_MAP(CDPromoBuch, CDialogMultiLang)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedListCtrl)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, OnItemchangedListCtrl2)
    ON_CBN_SELCHANGE(IDC_COMBO_TYP, OnCbnSelchangeComboTyp)
    ON_CBN_SELCHANGE(IDC_COMBO_FAKTOR, OnCbnSelchangeComboFaktor)
    ON_MESSAGE(WM_SETITEM, OnSetItem)
    ON_MESSAGE(WM_SETITEM2, OnSetItem2)
    ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST1, OnItemchangedListCtrl)
    ON_NOTIFY(VK_RETURN, IDC_LIST1, OnItemchangedListCtrl)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_NOTIFY(NM_SETFOCUS, IDC_LIST1, OnNMSetfocusList1)
    ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST1, OnLvnItemActivateList1)
    ON_BN_CLICKED(IDC_BUTTON_SUCHE, OnBnClickedButtonSuche)
    ON_MESSAGE(WM_SETSUCH, OnSetSuch)
    ON_BN_CLICKED(IDC_BUTTON_BEST_TA, OnBnClickedButtonBestTA)
END_MESSAGE_MAP()


// CDPromoBuch-Meldungshandler

BOOL CDPromoBuch::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    AeGetApp()->PromoWnd = GetSafeHwnd();

    m_List1->init();
    m_List2->init();
    m_List1->SetExtendedStyle(m_List1->GetExtendedStyle()
                                | LVS_EX_FULLROWSELECT
                                | LVS_EX_GRIDLINES );        // Grid
    m_List2->SetExtendedStyle(m_List2->GetExtendedStyle()
                                | LVS_EX_FULLROWSELECT
                                | LVS_EX_GRIDLINES );        // Grid

    CenterWindow((AeGetApp()->m_pViewEing));
    if (m_pFather->m_sPromoNo > 0)   //aus F2
    {
        m_bScale = true;
    }
    else
    {
        CCHECKPROMOSCALE checkscale;
        checkscale.SetPromotion_no(m_sPromono);

        if (0 != checkscale.PromoScaleExist())
        {
            m_bScale = true;
        }
        else
        {
            m_bScale = false;
        }
    }

    if (m_bScale)    //keine Staffel
    {
        GetDlgItem(IDC_BUTTON_BEST_TA)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_BEST_TA)->ShowWindow(SW_HIDE);
    }
    FillDialog();
    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

void CDPromoBuch::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_EDIT_SUCH))
    {
        OnBnClickedButtonSuche();
        return;
    }
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        m_List1->setItemColor(m_iItem, RGB(0, 0, 0), RGB(255, 255, 255));
        if (m_iItem == m_List1->GetItemCount() - 1)
        {
            if (!CalcAufWert())
                return;
            if (m_bSteller && m_iStellerTyp == 4)
            {
                m_List2->SetFocus();
            }
            else
            {
                GetDlgItem(IDC_EDIT_SUCH)->SetFocus();
                m_editSuch.SetSel(0, -1, FALSE);
            }
        }
        else
        {
            CalcAufWert();
            GetDlgItem(IDC_EDIT_SUCH)->SetFocus();
            m_editSuch.SetSel(0, -1, FALSE);
        }
        return;
    }
    else if (GetFocus() == GetDlgItem(IDC_LIST2))
    {
        if (m_iItem2 == m_List2->GetItemCount() - 1)
            GetDlgItem(IDOK)->SetFocus();
        return;
    }
    if (!CalcAufWert())
        return;
    CString Text;
    GetDlgItem(IDC_EDIT_WERT)->GetWindowText(Text);
    double dAufWert = atof(Text);
    GetDlgItem(IDC_EDIT_SMENGE)->GetWindowText(Text);
    int iAnz = atoi(Text);
    int iAnzMin = atoi(m_cMinMeng);
    double dAufWertMin = atof(m_cMinValue);
    if (iAnzMin > iAnz)
    {
        MsgBoxOK(AETXT_MENGE_ZU_KLEIN);
        return;
    }
    if (dAufWertMin > dAufWert)
    {
        MsgBoxOK(AETXT_WERT_ZU_KLEIN);
        return;
    }
    if (m_bSteller && m_iStellerTyp == 4)
    {
        iAnz = 0;
        int iSoll = atol(m_List2->GetItemText(0, PROMO_LR_COL_MAX));
        for (int pos = 1; pos < m_List2->GetItemCount(); pos++)
        {
            iAnz += atol(m_List2->GetItemText(pos, PROMO_LR_COL_MENGE));    //Kummulieren Menge
            int iInMenge = atol(m_List2->GetItemText(pos, PROMO_LR_COL_MENGE));
            int iBestand = atol(m_List2->GetItemText(pos, PROMO_LR_COL_BESTAND));
            if (iInMenge > iBestand)
            {
                MsgBoxOK(AETXT_NO_BESTAND);
                return;
            }
        }
        if (iAnz > iSoll)
        {
            MsgBoxOK(AETXT_RAB_ZU_VIEL);
            return;
        }
        else if (iAnz < iSoll)
        {
            MsgBoxOK(AETXT_RAB_ZU_WENIG);
            return;
        }
    }
    if (!PosBuchen())
    {
        CDialogMultiLang::OnOK();
    }
}

void CDPromoBuch::OnCbnSelchangeComboTyp()
{
    int selpos = m_ComboTyp.GetCurSel();
    CString chPreistyp;
    m_ComboTyp.GetLBText(selpos, chPreistyp);
    short sPreistyp = CharToShort(chPreistyp.GetAt(0));
    if (m_sPreistyp != sPreistyp)
    {
        m_sPreistyp = sPreistyp;
        GetMembers();
    }
}

double CDPromoBuch::GetNetPrice(double preis,double discount)
{
    char error_msg[81];
    CREBATEPRICE m_Rebates;     //Rabattstuktur
    m_Rebates.SetPreisekapo(preis);
    m_Rebates.SetDiscountvaluepct(discount);
    ::ServerNr(PIPE_AE_SRV, AasrvGetRebatePrice, (void*)&m_Rebates.s, REBATEPRICE_BES, REBATEPRICE_ANZ, error_msg);
    return m_Rebates.GetPreisfaktur();
}

void CDPromoBuch::SetPrices()
{
    for (int pos = 0; pos < m_sAnzList; pos++)
    {
        CARTINF art;
        CARTPREIS preis;
        preis.s.ARTIKEL_NR = art.s.ARTIKEL_NR = atol(m_List1->GetItemText(pos, PROMO_LC_COL_PZN));
        preis.s.PREIS_TYP = m_sPreistyp;
        art.Server(AatartInf_art_nr);
        preis.Server(AatartInf_preis);
        char cStd;
        double dTax;
        AeGetApp()->GetTaxRates(art.s.TAXLEVEL, cStd, dTax);
        CString hilfe;
        hilfe.Format("%0.2lf", GetBrutto(GetNetPrice(preis.s.PREISEKAPO, atof(m_List1->GetItemText(pos, 1))), dTax));  //Fakturpreis
        m_List1->SetItemText(pos, PROMO_LC_COL_WERT_NETTO, hilfe);
        hilfe.Format("%0.2lf", GetBrutto(preis.s.PREISEKAPO, dTax));    //AEP
        m_List1->SetItemText(pos, PROMO_LC_COL_WERT_BRUTTO, hilfe);
        hilfe.Format("%0.2lf", preis.s.PREISEKAPO);     //AEP
        m_List1->SetItemText(pos, PROMO_LC_COL_AEP, hilfe);
        hilfe.Format("%d", art.s.TAXLEVEL);     //AEP
        m_List1->SetItemText(pos, PROMO_LC_COL_TAX, hilfe);
    }
    CalcAufWert();
}

double CDPromoBuch::GetBrutto(double preis,double tax)
{
    return (preis*((100+tax)/100));
}

void CDPromoBuch::SetZeilenWert(int pos)
{
    CString Text;
    Text.Format("%0.2lf", atof(m_List1->GetItemText(pos, PROMO_LC_COL_WERT_BRUTTO))
        * atoi(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE))); //Zeilenwert
    m_List1->SetItemText(pos, PROMO_LC_COL_WERT, Text); //Zeilenwert
}

bool CDPromoBuch::CheckInput(int pos)
{
    int iInMenge = atoi(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE));
    int iMinMenge = atoi(m_List1->GetItemText(pos, PROMO_LC_COL_MIN));
    int iMaxMenge = atoi(m_List1->GetItemText(pos, PROMO_LC_COL_MAX));
    int iBestand = atoi(m_List1->GetItemText(pos, PROMO_LC_COL_BESTAND));
    if (iInMenge < iMinMenge)
    {
        MsgBoxOK(AETXT_UNTER_MIN);
        return false;
    }
    if (iMaxMenge > 0)
    {
        if (iInMenge > iMaxMenge)
        {
            MsgBoxOK(AETXT_UEBER_MAX);
            CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, pos);
            return false;
        }
    }
    if (iInMenge > iBestand)
    {
        MsgBoxOK(AETXT_NO_BESTAND);
        return false;
    }
    return true;
}

bool CDPromoBuch::CheckRabInput(int pos)
{
    if (m_iStellerTyp == 3) return true;

    int iInMenge = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MENGE));
    int iMinMenge = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MIN));
    int iMaxMenge = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MAX));
    int iBestand = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_BESTAND));
    if (iInMenge < iMinMenge)
    {
        MsgBoxOK(AETXT_UNTER_MIN);
        return false;
    }
    if (iInMenge > iMaxMenge)
    {
        MsgBoxOK(AETXT_UEBER_MAX);
        CListCtrlHelper::SetItemStateSelectedFocused(*m_List2, pos);
        return false;
    }
    if (iInMenge > iBestand)
    {
        MsgBoxOK(AETXT_NO_BESTAND);
        return false;
    }
    return true;
}

bool CDPromoBuch::CalcAufWert()
{
    double dAufWert = 0.0;
    double dAufWertAEP[10];
    double dWertZeile;
    double dTax;
    char cStd;
    int taxlevel;
    int iAnz = 0;
    CString Text;
    for (int i = 0; i < 10; i++) //auf 0 initialisieren
    {
        dAufWertAEP[i] = 0.0;
    }
    for (int pos = 0; pos < m_sAnzList; pos++)
    {
        if (!CheckInput(pos))
            return false;
        SetZeilenWert(pos);
        dWertZeile = atof(m_List1->GetItemText(pos, PROMO_LC_COL_AEP)) * atoi(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE));   //Zeilenwert
        taxlevel = atol(m_List1->GetItemText(pos, PROMO_LC_COL_TAX));
        dAufWertAEP[taxlevel] += dWertZeile;
        iAnz += atol(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE));    //Kummulieren Menge
    }
    for (int i = 0; i < 10; i++)
    {
        if (dAufWertAEP[i] > 0.0)
        {
            AeGetApp()->GetTaxRates(i, cStd, dTax);
            dAufWert = GetBrutto(dAufWertAEP[i], dTax); //AEP
        }
    }
    Text.Format("%0.2lf", dAufWert);
    GetDlgItem(IDC_EDIT_WERT)->SetWindowText(Text);
    Text.Format("%d", iAnz);
    GetDlgItem(IDC_EDIT_SMENGE)->SetWindowText(Text);
    return true;
}

void CDPromoBuch::OnItemchangedListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    if ((pNMLV->uChanged & LVIF_STATE) == LVIF_STATE)   // Status-Änderung
    {
        UINT uiNewState = (pNMLV->uNewState & LVIS_STATEIMAGEMASK);
        UINT uiOldState = (pNMLV->uOldState & LVIS_STATEIMAGEMASK);

        if (uiOldState != uiNewState)
        {
            switch (uiNewState >> 12)
            {
            case 0x0001:    // uncheck
                if ((uiOldState >> 12) == 0x02)
                {
                    CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, pNMLV->iItem);
                }
                break;

            case 0x0002:    // check
                CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, pNMLV->iItem);
                break;

            case 0x0000:    // kommt aus InsertItem()
            default:
                assert(0);
                break;
            }
        }
    }

    if (m_iItem != pNMLV->iItem)
    {
        if (pNMLV->uNewState == 3)
        {
            if (CalcAufWert())
            {
                if (m_sAnzList == 1)
                {
                    this->PostMessage(WM_SETITEM, 0, 0);
                }
                else
                {
                    m_iItem_old = m_iItem;
                    m_iItem = pNMLV->iItem;
                    m_List1->setItemColor(m_iItem, RGB(255, 255, 255), RGB(0, 0, 255));
                    m_List1->setItemColor(m_iItem_old, RGB(0, 0, 0), RGB(255, 255, 255));
                    //m_List1->setColumnColor(PROMO_LC_COL_MENGE,fg,bg);
                }
            }
            else
                this->PostMessage(WM_SETITEM, 0, 0);
            //m_List1->selectItem(m_iItem);
            //CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, m_iItem);
        }
        if (m_bReturn)
        {
            this->PostMessage(WM_SETSUCH, 0, 0);
            m_bReturn = false;
        }
    }

    *pResult = 0L;
}

void CDPromoBuch::OnItemchangedListCtrl2(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    if ((pNMLV->uChanged & LVIF_STATE) == LVIF_STATE)   // Status-Änderung
    {
        UINT uiNewState = (pNMLV->uNewState & LVIS_STATEIMAGEMASK);
        UINT uiOldState = (pNMLV->uOldState & LVIS_STATEIMAGEMASK);

        if (uiOldState != uiNewState)
        {
            switch (uiNewState >> 12)
            {
            case 0x0001:    // uncheck
                if ((uiOldState >> 12) == 0x02)
                {
                    CListCtrlHelper::SetItemStateSelectedFocused(*m_List2, pNMLV->iItem);
                }

                break;

            case 0x0002:    // check
                CListCtrlHelper::SetItemStateSelectedFocused(*m_List2, pNMLV->iItem);
                break;

            case 0x0000:    // kommt aus InsertItem()
            default:
                assert(0);
                break;
            }
        }
    }
    if (pNMLV->iItem > 0)
    {
        if (m_iStellerTyp == 4)
        {
            m_List2->SetNoEdit(false);
        }
    }
    else
    {
        m_List2->SetNoEdit(true);
    }

    if (m_iItem2 != pNMLV->iItem)
    {
        if (pNMLV->uNewState == 3)
        {
            if (CheckRabInput(m_iItem2))
            {
                m_iItem2_old = m_iItem2;
                m_iItem2 = pNMLV->iItem;
                if (m_bSteller && m_iItem2 == 0)
                {
                    m_iItem2 = 1;
                }
            }
            else
                this->PostMessage(WM_SETITEM2, 0, 0);
        }
    }

    *pResult = 0L;
}

LRESULT CDPromoBuch::OnSetItem(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    m_List1->selectItem(m_iItem);
    m_List1->setItemColor(m_iItem,RGB(255,255,255),RGB(0,0,255));
    m_List1->setItemColor(m_iItem_old,RGB(0,0,0),RGB(255,255,255));
    return 0L;
}

LRESULT CDPromoBuch::OnSetItem2(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    m_List2->selectItem(m_iItem2);
    return 0L;
}

LRESULT CDPromoBuch::OnSetSuch(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    GetDlgItem(IDC_EDIT_SUCH)->SetFocus();
    m_editSuch.SetSel( 0, -1, FALSE );
    return 0L;
}

int CDPromoBuch::PosBuchen()
{
    if (m_pFather->m_sPromoNo == 0)  //nicht aus F2
    {
        OnBnClickedButtonBestTA();
    }
    int nrab;
    bool bChange;
    int selpos = m_ComboTyp.GetCurSel();
    CString chPreistyp;
    m_ComboTyp.GetLBText(selpos, chPreistyp);
    short sPreistyp = CharToShort(chPreistyp.GetAt(0));
    CAUFPOSBUCH aufposbuch;
    AUFPOSBUCH* ptrPos = nullptr;

    if (m_ptrDoc != NULL)
    {
        ptrPos = m_ptrDoc->GetPosListe();   //Zeiger auf Beginn der Liste
    }
    for (int pos = 0; pos < m_List1->GetItemCount(); pos++)
    {
        bChange = false;
        nrab = 0;
        aufposbuch.s.ARTIKEL_NR        = atol(m_List1->GetItemText(pos, PROMO_LC_COL_PZN));
        aufposbuch.s.MENGEBESTAETIGT   = atol(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE));
        aufposbuch.s.MENGEBESTELLT     = 0;
        aufposbuch.s.DISCOUNTGRPNO     = atol(m_cDISCGRP);
        aufposbuch.s.BASEQTY           = m_lMinQty;
        aufposbuch.s.BASE_VALUE        = m_dMinValue;
        aufposbuch.s.ADDONSTDDISCOK[0] = m_cAddDisc.GetAt(0);
        if (m_ptrDoc != NULL)
        {
            for (int i = 0;; i++)
            {
                ptrPos = m_ptrDoc->GetListPosition(i);
                if (ptrPos == NULL)
                    break;
                if (ptrPos->ARTIKEL_NR == aufposbuch.s.ARTIKEL_NR
                    && ptrPos->PROMOTYP == 1
                    && ptrPos->PROMOTION_NO == m_sPromono)
                {
                    bChange = true;
                    aufposbuch.s.POSNR = ptrPos->POSNR;
                    aufposbuch.s.STATUS = ptrPos->STATUS;
                    break;
                }
            }
            if (!bChange && (aufposbuch.s.MENGEBESTAETIGT == 0))
            {
                continue;
            }
        }
        else if (aufposbuch.s.MENGEBESTAETIGT == 0)
        {
            continue;
        }
        aufposbuch.s.DISCOUNTVALUEPCT  = atof(m_List1->GetItemText(pos, PROMO_LC_COL_RABATT)) + m_dPct;
        aufposbuch.s.PROMOTYP          = 1;
        if (atoi(m_List1->GetItemText(pos, PROMO_LC_COL_NR)) > 0)
        {
            nrab = atol(m_List1->GetItemText(pos, PROMO_LC_COL_NR));
            if (m_List1->GetItemText(pos, PROMO_LC_COL_PROPORT) != "1")
            {
                nrab *= (atol(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE))) /
                        (atol(m_List1->GetItemText(pos, PROMO_LC_COL_MIN)) );
            }

        }
        aufposbuch.s.MENGENATRA   = nrab;
        strcpy(aufposbuch.s.PHARMACYGROUPID, (LPCTSTR)m_cEKG);
        aufposbuch.s.PROMOTION_NO = m_sPromono;
        aufposbuch.s.PREIS_TYP    = sPreistyp;

        for (;;)
        {
            aufposbuch.s.STATUS = ITEM_STAT_NORMAL;
            //Buchungsversuch
            if (bChange)
            {
                aufposbuch.Server(AasrvChangepos, PIPE_AE_SRV);
            }
            else
            {
                aufposbuch.Server(AasrvWritePromoPos, PIPE_AE_SRV);
            }
            if (aufposbuch.rc < SRV_OK)                                //Fehler
            {
                return -1;
            }
            if (aufposbuch.s.STATUS == ITEM_STAT_KREDITLIMIT)          //Kreditlimit ueberschritten
            {
                if (MsgBoxYesNo(IDP_CHANGE_CO) == IDYES)
                {
                    CAUFTRAG auftrag;
                    ((CAeFView*)AeGetApp()->m_pViewEing)->m_PaymentType.SetAt(0, 'C');
                    auftrag.s.PAYMENTTYPE[0] = 'C';
                    auftrag.Server(AasrvSetOrderToCash, PIPE_AE_SRV);
                    auftrag.s.VALUTAMONATE = 0L;
                    auftrag.Server(AasrvChangeValuta, PIPE_AE_SRV);
                    ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_PAYMENTTYPE)->ShowWindow(SW_SHOW);
                }
                else
                    return -1;
            }
            else if (aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE)             //Verfügbare Menge reichte nicht aus
            {
                return -1;
            }
            else
                break;
        }
        if (bChange)
        {
            m_ptrDoc->UpdPosition(ptrPos->POSNR, aufposbuch.s);    //Positionsliste aktualisieren
        }
        else
        {
            ((CAeDoc*)AeGetApp()->m_Doc)->AddPosition(aufposbuch.s);   //Positionsliste erstellen
        }
    } //Ende der for(;;)

    int pos = m_bSteller ? 1 : 0;

    for (;pos < m_List2->GetItemCount(); pos++)
    {
        bChange = false;
        aufposbuch.s.ARTIKEL_NR        = atol(m_List2->GetItemText(pos, PROMO_LR_COL_PZN));
        aufposbuch.s.MENGEBESTAETIGT   = atol(m_List2->GetItemText(pos, PROMO_LR_COL_MENGE));
        aufposbuch.s.MENGEBESTELLT     = 0;
        aufposbuch.s.DISCOUNTGRPNO     = atol(m_cDISCGRP);
        aufposbuch.s.BASEQTY           = atol(m_cMinMeng);
        aufposbuch.s.BASE_VALUE        = atof(m_cMinValue);
        if (m_ptrDoc != NULL)
        {
            for (int i = 0;; i++)
            {
                ptrPos = m_ptrDoc->GetListPosition(i);
                if (ptrPos == NULL)
                    break;
                if (   ptrPos->ARTIKEL_NR == aufposbuch.s.ARTIKEL_NR
                    && ptrPos->PROMOTYP == 2
                    && ptrPos->PROMOTION_NO == m_sPromono)
                {
                    aufposbuch.s.POSNR = ptrPos->POSNR;
                    aufposbuch.s.STATUS = ptrPos->STATUS;
                    bChange = true;
                    break;
                }
            }
            if (!bChange && (aufposbuch.s.MENGEBESTAETIGT == 0))
            {
                continue;
            }
        }
        else if (aufposbuch.s.MENGEBESTAETIGT == 0)
            continue;
        aufposbuch.s.DISCOUNTVALUEPCT  = 0.0;
        aufposbuch.s.PROMOTYP          = 2;
        aufposbuch.s.MENGENATRA        = 0;
        strcpy(aufposbuch.s.PHARMACYGROUPID, (LPCTSTR)m_cEKG);
        aufposbuch.s.PROMOTION_NO      = m_sPromono;
        aufposbuch.s.PREIS_TYP         = sPreistyp;

        //Buchungsversuch
        if (bChange)
        {
            aufposbuch.s.MENGENATRA      = aufposbuch.s.MENGEBESTAETIGT;
            aufposbuch.s.MENGEBESTAETIGT = 0;
            aufposbuch.Server(AasrvChangepos, PIPE_AE_SRV);
        }
        else
        {
            aufposbuch.Server(AasrvWritePromoPos, PIPE_AE_SRV);
        }
        if (aufposbuch.rc < SRV_OK)                                //Fehler
        {
            return -1;
        }
        if (aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE)          //Verfügbare Menge reichte nicht aus
        {
            return -1;
        }
        ((CAeDoc*)AeGetApp()->m_Doc)->AddPosition(aufposbuch.s);   //Positionsliste erstellen
    } //Ende der for(;;)

    ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerte(aufposbuch.s.ANZPOS, aufposbuch.s.WERTAUFTRAG, aufposbuch.s.WERTLIEFERUNG, aufposbuch.s.WERTZEILEN, aufposbuch.s.BALANCE, aufposbuch.s.BALANCE2);
    ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerteBG(aufposbuch.s.WERTNETTO_FV, aufposbuch.s.WERTTAX_FV, aufposbuch.s.WERTNETTO_KK, aufposbuch.s.WERTTAX_KK, aufposbuch.s.WERTNETTO_EH, aufposbuch.s.WERTTAX_EH, aufposbuch.s.WERTEXCLUSIVE);
    return 0;
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDPromoBuch::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    if (((LPMSG)lpMsg)->wParam == VK_RETURN)
    {
        if (GetFocus() == GetDlgItem(IDC_EDIT_SUCH))
        {
            OnBnClickedButtonSuche();
            return 1L;
        }
        m_bReturn = true;
        return 1L;
    }

    return 0L;
}

int CDPromoBuch::CheckMultiple()
{
    int mult = 99;
    double dAufWert = 0.0;
    int iAnz = 0;
    int calcmult = 1;
    int iMin;
    for (int pos = 0; pos < m_sAnzList; pos++)
    {
        SetZeilenWert(pos);
        dAufWert += atof(m_List1->GetItemText(pos, PROMO_LC_COL_WERT)); //Kummulieren Zeilenwert
        iAnz += atol(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE));    //Kummulieren Menge
    }
    if (m_lMinQty > 0)
    {
        if (iAnz == 0)
            return 0;
        calcmult = iAnz / m_lMinQty;
        if (calcmult < 1)
        {
            return calcmult;
        }
        if (calcmult < mult)
        {
            mult = calcmult;
            if (mult < 1)
                return mult;
        }
    }
    if (m_dMinValue > 0)
    {
        calcmult = static_cast<int>(dAufWert / m_dMinValue);
        if (calcmult < 1)
        {
            return calcmult;
        }
        if (calcmult < mult)
        {
            mult = calcmult;
            if (mult < 1) return mult;
        }
    }
    for (int pos = 0; pos < m_List1->GetItemCount(); pos++)
    {
        iAnz = atol(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE));
        iMin = atol(m_List1->GetItemText(pos, PROMO_LC_COL_MIN_SOLO));
        if (iMin == 0)
            continue;
        calcmult = iAnz / iMin;
        if (calcmult < 1)
        {
            return calcmult;
        }
        if (calcmult < mult)
        {
            mult = calcmult;
            if (mult < 1)
                return mult;
        }
    }
    return mult;
}

void CDPromoBuch::OnCbnSelchangeComboFaktor()
{
    int rc;
    int iFaktor = m_ComboFaktor.GetCurSel();
    if (m_iFaktor == iFaktor) return;
    rc = ChangeFaktor(iFaktor);
    if (rc != iFaktor)      //bei nicht ausreichenden Mengen mit alten Faktor wieder einstellen
    {
        m_ComboFaktor.SetCurSel(rc);
        ChangeFaktor(rc);
    }
}


int CDPromoBuch::ChangeFaktor(int iFaktor)
{
    int iMin;
    int iMax;
    int iQty;
    int iNatra;
    int rc = iFaktor;
    CString csMin;
    CString csMax;
    CString csNatra;
    double dMinWert;
    for (int pos = 0; pos < m_List1->GetItemCount(); pos++)
    {
        if (m_List1->GetItemText(pos, PROMO_LR_COL_PZN).IsEmpty())
            break;  // Leerzeile bei nur einem Artikel bedeutet Ende der Liste
        iMin = atoi(m_List1->GetItemText(pos, PROMO_LC_COL_MIN_SOLO));  //min.Menge
        iMin = iMin * iFaktor;
        csMin.Format("%d", iMin);
        m_List1->SetItemText(pos, PROMO_LC_COL_MIN, csMin);             //min.Menge
        iMax = atoi(m_List1->GetItemText(pos, PROMO_LC_COL_MAX_SOLO));  //max.Menge
        iMax = iMax * iFaktor;
        csMax.Format("%d", iMax);
        m_List1->SetItemText(pos, PROMO_LC_COL_MAX, csMax);             //max.Menge
        iNatra = atoi(m_List1->GetItemText(pos, PROMO_LC_COL_NR_SOLO)); //NR.Menge
        iNatra = iNatra * iFaktor;
        csNatra.Format("%d", iNatra);
        m_List1->SetItemText(pos, PROMO_LC_COL_NR, csNatra);        //NR.Menge
        iQty = atoi(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE)); //Menge
        if (m_iFaktor != 0)
        {
            iQty = ((iQty / m_iFaktor) * iFaktor);
            if (iQty < iMin) iQty = iMin;
            csMin.Format("%d", iQty);
        }
        m_List1->SetItemText(pos, PROMO_LC_COL_MENGE, csMin);       //min.Menge
        if (!CheckInput(pos))
        {
            rc = m_iFaktor;
        }
        SetZeilenWert(pos);
    }
    for (int pos = 0; pos < m_List2->GetItemCount(); pos++)
    {
        iMin = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MIN_SOLO));  //min.Menge
        iMin = iMin * iFaktor;
        csMin.Format("%d", iMin);
        m_List2->SetItemText(pos, PROMO_LR_COL_MIN, csMin);             //min.Menge
        iMax = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MAX_SOLO));  //max.Menge
        csMax.Format("%d", iMax * iFaktor);
        m_List2->SetItemText(pos, PROMO_LR_COL_MAX, csMax);             //max.Menge
        iQty = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MENGE));     //Menge
        if (m_iFaktor != 0)
        {
            iQty = ((iQty / m_iFaktor) * iFaktor);
            if (iQty < iMin)
                iQty = iMin;
            csMin.Format("%d", iQty);
        }
        m_List2->SetItemText(pos, PROMO_LR_COL_MENGE, csMin);           //min.Menge
        if (m_iStellerTyp == 4 && pos == 0) // bei Steller Typ 4
        {                                   // immer max Menge in bestellte Menge
            iMin = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MAX_SOLO));  //max.Menge
            csMin.Format("%d", iMin * iFaktor);
            m_List2->SetItemText(pos, PROMO_LR_COL_MENGE, csMin);           //max.Menge
        }
        else
        {
            if (!CheckRabInput(pos))
            {
                rc = m_iFaktor;
            }
        }
    }
    iMin = m_lMinQty * iFaktor;
    m_cMinMeng.Format("%d", iMin);
    GetDlgItem(IDC_EDIT_MENGE)->SetWindowText(m_cMinMeng);
    dMinWert = m_dMinValue * iFaktor;
    m_cMinValue.Format("%0.2lf", dMinWert);
    GetDlgItem(IDC_EDIT_VALUE)->SetWindowText(m_cMinValue);
    CalcAufWert();
    m_iFaktor = iFaktor;
    return rc;
}
void CDPromoBuch::OnNMSetfocusList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    m_List1->setItemColor(m_iItem,RGB(255,255,255),RGB(0,0,255));
    *pResult = 0L;
}

void CDPromoBuch::OnLvnItemActivateList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    m_List1->setItemColor(m_iItem,RGB(255,255,255),RGB(0,0,255));

    *pResult = 0L;
}

void CDPromoBuch::GetMembers()
{
    CStringArray s;
    CARTAESEL art;
    CARTPRICE preis;
    CString Text;
    ppString cText;
    double dTax;
    char cStd;
    int index = 0;
    long lQuota;
    m_List1->DeleteAllItems();
    AUFPOSBUCH* ptrPos;
    BeginWaitCursor();
    long lBestand;
    if (m_lManu > 0)
    {
        CPROMOHERST herst;
        herst.SetFilialnr(m_sVznr);
        herst.SetHersteller_nr(m_lManu);
        herst.SetPreis_typ(m_sPreistyp);
        herst.SetPromotion_no(m_sPromono);
        for (int pos = 0;; pos++)
        {
            if (herst.SelList() != SRV_OK)
                break;
            Text = herst.GetHealthfundcode(cText);
            if (m_sPreistyp == 1 && Text.IsEmpty())
                continue;
            index = m_List1->GetItemCount();
            if (m_List1->InsertItem(index, "") == -1)
            {
                return;
            }
            AeGetApp()->GetTaxRates(herst.GetTaxlevel(), cStd, dTax);
            Text.Format("%d", herst.GetArtikel_nr());
            m_List1->SetItemText(index, PROMO_LC_COL_PZN, Text);        //name
            m_List1->SetItemText(index, PROMO_LC_COL_NAME, herst.GetArtikel_langname(cText));       //name
            m_List1->SetItemText(index, PROMO_LC_COL_RABATT, "0.00");   //%rabatt
            Text.Format("%0.2lf", GetBrutto(GetNetPrice(herst.GetPreisekapo(), m_dPct), dTax));     //Fakturpreis
            m_List1->SetItemText(index, PROMO_LC_COL_WERT_NETTO, Text);                             //Fakturpreis
            m_List1->SetItemText(index, PROMO_LC_COL_MIN, "0");         //min.Menge
            m_List1->SetItemText(index, PROMO_LC_COL_MAX, "0");         //max.Menge
            lBestand = herst.GetBestand();
            CARTIKELQUOTA quota;

            quota.SetBranchno(AeGetApp()->FilialNrActual());
            quota.SetArticleno(herst.GetArtikel_nr());
            quota.SetCustomerno(((CAeFView*)AeGetApp()->m_pViewEing)->GetKundenNr());
            short sQuotaInheritance = CharToShort(AeGetApp()->QuotaInheritance());
            quota.SetQuotainheritance(sQuotaInheritance);
            if (!quota.CheckQuota())
            {
                lQuota = quota.GetQuota();
                if (lBestand > lQuota)
                {
                    lBestand = lQuota;
                }
            }

            Text.Format("%d", lBestand);
            m_List1->SetItemText(index, PROMO_LC_COL_BESTAND, Text);                                    //Bestand
            Text.Format("%02d.%02d", herst.GetDatumverfall() % 100, herst.GetDatumverfall() / 100);
            m_List1->SetItemText(index, PROMO_LC_COL_VERFALL, Text);                                    //Bestand
            if (m_ptrDoc != NULL)
            {
                bool bHit = false;
                for (int i = 0;;i++)
                {
                    ptrPos = m_ptrDoc->GetListPosition(i);
                    if (ptrPos == NULL) break;
                    if (ptrPos->ARTIKEL_NR == herst.GetArtikel_nr()
                        && ptrPos->PROMOTYP == 1
                        && ptrPos->PROMOTION_NO == m_sPromono)
                    {
                        lBestand = atol(m_List1->GetItemText(index, PROMO_LC_COL_BESTAND));
                        lBestand += ptrPos->MENGEBESTELLT;  //Gesamtbestand = bestellt und noch vorhandener
                        Text.Format("%d", lBestand);
                        m_List1->SetItemText(index, PROMO_LC_COL_BESTAND, Text);
                        Text.Format("%d", ptrPos->MENGEBESTELLT);
                        m_List1->SetItemText(index, PROMO_LC_COL_MENGE, Text);      //Wunschmenge
                        bHit = true;
                        break;
                    }
                }
                if (!bHit)
                {
                    m_List1->SetItemText(index, PROMO_LC_COL_MENGE, "0");       //Wunschmenge
                }
            }
            else
            {
                m_List1->SetItemText(index, PROMO_LC_COL_MENGE, "0");       //Wunschmenge
            }
            Text.Format("%0.2lf", herst.GetPreisekapo());       //AEP
            m_List1->SetItemText(pos, PROMO_LC_COL_AEP, Text);
            Text.Format("%0.2lf", GetBrutto(herst.GetPreisekapo(), dTax));
            m_List1->SetItemText(index, PROMO_LC_COL_WERT_BRUTTO, Text);                                //AEP
            m_List1->SetItemText(index, PROMO_LC_COL_NR, "0");          //Naturalrabatt
            m_List1->SetItemText(index, PROMO_LC_COL_PROPORT, "0");     //Kennzeichen proportional
        }
        if (index == 0) //Wenn nur ein Member -> Leerzeile Einfügen für colchange-Methode
        {
            m_sAnzList = 1;
            index = m_List1->GetItemCount();
            if (m_List1->InsertItem(index, "") == -1)
            {
                return;
            }
        }
        else
        {
            m_sAnzList = static_cast<short>(index + 1);
        }
    }
    else
    {
        for (int pos = 0; pos < m_pListMember->GetItemCount(); pos++)
        {
            art.s.ARTIKEL_NR = atol(m_pListMember->GetItemText(pos, 3));
            preis.SetArtikel_nr(art.s.ARTIKEL_NR);
            preis.SetPreis_typ(m_sPreistyp);
            if (preis.SelPrice())
                continue;
            art.s.FILIALNR = AeGetApp()->FilialNrActual();
            art.s.ETARTKLASSE1 = 65535; //alles - select wird nur fuer KK-Code gebraucht
            art.s.CODEBLOCAGE[0] = '0';
            art.Server( AatartAa_sel_artnr );
            index = m_List1->GetItemCount();
            AllgEntfSpaces(art.s.HEALTHFUNDCODE);
            if (m_sPreistyp == 1 && art.s.HEALTHFUNDCODE[0] == '\0')
                continue;
            if (m_List1->InsertItem(index, "") == -1)
            {
                return;
            }
            lBestand = art.s.BESTAND;
            CARTIKELQUOTA quota;
            quota.SetBranchno(AeGetApp()->FilialNrActual());
            quota.SetArticleno(art.s.ARTIKEL_NR);
            quota.SetCustomerno(((CAeFView *)AeGetApp()->m_pViewEing)->GetKundenNr());
            short sQuotaInheritance = CharToShort(AeGetApp()->QuotaInheritance());
            quota.SetQuotainheritance(sQuotaInheritance);
            if (!quota.CheckQuota())
            {
                lQuota = quota.GetQuota();
                if (lBestand > lQuota)
                {
                    lBestand = lQuota;
                }
            }
            if (m_ptrDoc != NULL)
            {
                bool bHit = false;
                for (int i = 0;; i++)
                {
                    if (m_ptrDoc == NULL)
                        break;
                    ptrPos = m_ptrDoc->GetListPosition(i);
                    if (ptrPos == NULL)
                        break;
                    if (   ptrPos->ARTIKEL_NR == art.s.ARTIKEL_NR
                        && ptrPos->PROMOTYP == 1
                        && ptrPos->PROMOTION_NO == m_sPromono )
                    {
                        lBestand = art.s.BESTAND;
                        lBestand += ptrPos->MENGEBESTELLT;  //Gesamtbestand = bestellt und noch vorhandener
                        Text.Format("%d", lBestand);
                        m_List1->SetItemText(index, PROMO_LC_COL_BESTAND, Text);
                        Text.Format("%d", ptrPos->MENGEBESTELLT);
                        m_List1->SetItemText(index, PROMO_LC_COL_MENGE, Text);       //Wunschmenge
                        art.s.BESTAND = lBestand;
                        bHit = true;
                        break;
                    }
                }
                if (!bHit)
                {
                    m_List1->SetItemText(index, PROMO_LC_COL_MENGE, m_pListMember->GetItemText(pos, 2));      //Wunschmenge
                }
            }
            else
            {
                m_List1->SetItemText(index, PROMO_LC_COL_MENGE, m_pListMember->GetItemText(pos, 2));      //Wunschmenge
            }
            if (lBestand < atol(m_pListMember->GetItemText(pos, 2)))
            {
                CString csFehler;
                csFehler.Format(CResString::ex().getStrTblText(AETXT_NO_BESTAND_ARTIKEL),
                    m_pListMember->GetItemText(pos, 3).GetString(),
                    m_pListMember->GetItemText(pos, 0).GetString(),
                    m_pListMember->GetItemText(pos, 2).GetString(),
                    art.s.BESTAND);
                MsgBoxOK(csFehler);
                CDialogMultiLang::OnCancel();
                return;
            }
            AeGetApp()->GetTaxRates(art.s.TAXLEVEL, cStd, dTax);
            m_List1->SetItemText(index, PROMO_LC_COL_PZN, m_pListMember->GetItemText(pos, 3));          //name
            m_List1->SetItemText(index, PROMO_LC_COL_NAME, m_pListMember->GetItemText(pos, 0));         //name
            m_List1->SetItemText(index, PROMO_LC_COL_RABATT, m_pListMember->GetItemText(pos, 1));       //%rabatt
            Text.Format("%0.2lf", GetBrutto(GetNetPrice(preis.GetPreisekapo(), atof(m_pListMember->GetItemText(pos, 1))), dTax));   //Fakturpreis
            m_List1->SetItemText(index, PROMO_LC_COL_WERT_NETTO, Text);                                 //Fakturpreis
            m_List1->SetItemText(index, PROMO_LC_COL_MIN, m_pListMember->GetItemText(pos, 2));          //min.Menge
            m_List1->SetItemText(index, PROMO_LC_COL_MIN_SOLO, m_pListMember->GetItemText(pos, 2));     //min.Menge
            m_List1->SetItemText(index, PROMO_LC_COL_MAX, m_pListMember->GetItemText(pos, 4));          //max.Menge
            Text.Format("%d", lBestand);
            m_List1->SetItemText(index, PROMO_LC_COL_BESTAND, Text);                                    //Bestand
            Text.Format("%0.2lf", GetBrutto(preis.s.PREISEKAPO, dTax));
            m_List1->SetItemText(index, PROMO_LC_COL_WERT_BRUTTO, Text);                                //AEP
            m_List1->SetItemText(index, PROMO_LC_COL_NR, m_pListMember->GetItemText(pos, 5));           //Naturalrabatt
            m_List1->SetItemText(index, PROMO_LC_COL_PROPORT, m_pListMember->GetItemText(pos, 6));      //Kennzeichen proportional
            m_List1->SetItemText(index, PROMO_LC_COL_VERFALL, m_pListMember->GetItemText(pos, 7));      //Kennzeichen proportional
            Text.Format("%0.2lf", preis.s.PREISEKAPO);      //AEP
            m_List1->SetItemText(pos, PROMO_LC_COL_AEP, Text);
        }
        if (index == 0)  //Wenn nur ein Member -> Leerzeile Einfügen für colchange-Methode
        {
            m_sAnzList = 1;
            index = m_List1->GetItemCount();
            if (m_List1->InsertItem(index, "") == -1)
            {
                return;
            }
        }
        else
        {
            m_sAnzList = static_cast<short>(m_List1->GetItemCount());
        }
    }
}

void CDPromoBuch::OnBnClickedButtonSuche()
{
    UpdateData();
    CString vergl;
    int found = 0;
    int len = m_csSuch.GetLength();
    for (int pos = 0; pos < m_List1->GetItemCount(); pos++)
    {
        vergl = m_List1->GetItemText(pos, 0);
        if (!strncmp(vergl, m_csSuch, len))
        {
            found = 1;
            CListCtrlHelper::SetFocusSelectedFocused(*m_List1, pos);
            //Zeilenhoehe ermitteln
            CRect itemRect;
            m_List1->GetItemRect(0, itemRect, LVIR_BOUNDS);
            int hoehe = itemRect.Height();
            int rc;
            //zuerst auf Listanfang
            CSize scrollback(0, (m_List1->GetItemCount() * hoehe * (-1)));
            rc = m_List1->Scroll(scrollback);
            //jetzt auf gesuchte Position
            CSize scrollfaktor(0, pos * hoehe);
            rc = m_List1->Scroll(scrollfaktor);
            break;
        }
    }
    GetDlgItem(IDC_BUTTON_SUCHE)->SetFocus();
    if (!found)
    {
        MsgBoxOK(AETXT_NOT_FOUND);
        GetDlgItem(IDC_EDIT_SUCH)->SetFocus();
        m_editSuch.SetSel(0, -1, FALSE);
    }
    else
    {
        GetDlgItem(IDC_LIST1)->SetFocus();
    }
}

//Suchen beste TA
int CDPromoBuch::CheckBestTA()
{
    int nrab;
    bool bChange;
    int selpos = m_ComboTyp.GetCurSel();
    CString chPreistyp;
    m_ComboTyp.GetLBText(selpos, chPreistyp);
    short sPreistyp = CharToShort(chPreistyp.GetAt(0));
    CAUFPOSBUCH aufposbuch;
    AUFPOSBUCH *ptrPos;
    //evtl vorhandene Liste löschen
    if (!m_plTobook)
    {
        m_plTobook = new vector<sTobook>;
    }
    else
    {
        if (!m_plTobook->empty())
            m_plTobook->clear();
    }
    iAnzPl = 0;
    if (m_ptrDoc != NULL)
    {
        ptrPos = m_ptrDoc->GetPosListe();   //Zeiger auf Beginn der Liste
    }
    for (int pos = 0; pos < m_List1->GetItemCount(); pos++)
    {
        bChange = false;
        nrab = 0;
        aufposbuch.s.ARTIKEL_NR        = atol(m_List1->GetItemText(pos, PROMO_LC_COL_PZN));
        aufposbuch.s.MENGEBESTAETIGT   = atol(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE));
        aufposbuch.s.MENGEBESTELLT     = 0;
        aufposbuch.s.DISCOUNTGRPNO     = atol(m_cDISCGRP);
        aufposbuch.s.BASEQTY           = m_lMinQty;
        aufposbuch.s.BASE_VALUE        = m_dMinValue;
        aufposbuch.s.ADDONSTDDISCOK[0] = m_cAddDisc.GetAt(0);
        if (aufposbuch.s.MENGEBESTAETIGT == 0)
        {
            continue;
        }
        sTobook tb;
        tb.MENGE = aufposbuch.s.MENGEBESTAETIGT;
        tb.PZN = aufposbuch.s.ARTIKEL_NR;
        m_plTobook->insert(m_plTobook->end(),tb);
        ++iAnzPl;
        aufposbuch.s.DISCOUNTVALUEPCT  = atof(m_List1->GetItemText(pos, PROMO_LC_COL_RABATT)) + m_dPct;
        aufposbuch.s.PROMOTYP          = 1;
        if (atoi(m_List1->GetItemText(pos, PROMO_LC_COL_NR)) > 0)
        {
            nrab = atol(m_List1->GetItemText(pos, PROMO_LC_COL_NR));
            if (m_List1->GetItemText(pos, PROMO_LC_COL_PROPORT) != "1")
            {
                nrab *= (atol(m_List1->GetItemText(pos, PROMO_LC_COL_MENGE))) /
                        (atol(m_List1->GetItemText(pos, PROMO_LC_COL_MIN)) );
            }

        }
        aufposbuch.s.MENGENATRA   = nrab;
        strcpy(aufposbuch.s.PHARMACYGROUPID, (LPCTSTR)m_cEKG);
        aufposbuch.s.PROMOTION_NO = m_sPromono;
        aufposbuch.s.PREIS_TYP    = sPreistyp;

        for (;;)
        {
            aufposbuch.s.STATUS = ITEM_STAT_NORMAL;
            //Buchungsversuch
            aufposbuch.Server(AasrvWriteProformaPos, PIPE_AE_SRV);
            if (aufposbuch.rc < SRV_OK)                                //Fehler
            {
                return -1;
            }
            else if (aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE)     //Verfügbare Menge reichte nicht aus
            {
                return -1;
            }
            else break;
        }
    } //Ende der for(;;)
    aufposbuch.Server(AasrvGetBestTA, PIPE_AE_SRV);
    return aufposbuch.s.PROMOTION_NO;
}

void CDPromoBuch::OnBnClickedButtonBestTA()
{
    if (m_bScale)
    {
        return; //keine Staffel
    }

    short sPromoNo = static_cast<short>(CheckBestTA());
    if (sPromoNo == 0)
    {
        MsgBoxOK(AETXT_NOT_FULLFILLED);
        return;
    }
    if (m_sPromono != sPromoNo)
    {
        int suchpos;

        CString Text;
        for (suchpos = 0; suchpos < m_pListPromo->GetItemCount(); suchpos++)
        {
            if (sPromoNo == atoi(m_pListPromo->GetItemText(suchpos, 1)))
            {
                if (m_sPromono < sPromoNo)
                {
                    Text.Format(CResString::ex().getStrTblText(AETXT_BETTER_TA), m_pListPromo->GetItemText(suchpos, 2).GetString());
                    break;
                }
                else
                {
                    Text.Format(CResString::ex().getStrTblText(AETXT_WORSE_TA), m_pListPromo->GetItemText(suchpos, 2).GetString());
                    break;
                }
            }
        }
        if (MsgBoxYesNo(Text) == IDYES)
        {
            CString cMenge;
            m_pFather->SuchePromoNo(sPromoNo);
            FillDialog();
            sTobook tb;
            for (int i = 0; i < iAnzPl; i++)
            {
                tb = m_plTobook->at(i);
                for (int pos = 0; pos < m_List1->GetItemCount(); pos++)
                {
                    if (tb.PZN == atol(m_List1->GetItemText(pos, PROMO_LC_COL_PZN)))
                    {
                        cMenge.Format("%d", tb.MENGE);
                        m_List1->SetItemText(pos, PROMO_LC_COL_MENGE, cMenge);
                        break;
                    }
                }
            }
            CalcAufWert();
            m_iFaktor = CheckMultiple();
            m_ComboFaktor.SetCurSel(m_iFaktor);
            ChangeFaktor(m_iFaktor);
            //UpdateData(FALSE);
        }
    }
}

int CDPromoBuch::FillDialog()
{
    GetDlgItem(IDC_STATIC_PROMOTION)->SetWindowText(m_cPromotion);
    m_lMinQty = atol(m_cMinMeng);
    if (m_lMinQty > 0)
    {
        GetDlgItem(IDC_STATIC_MENGE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_MENGE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_MENGE)->SetWindowText(m_cMinMeng);
    }
    m_dMinValue = atof(m_cMinValue);
    if (m_dMinValue > 0)
    {
        GetDlgItem(IDC_STATIC_VALUE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_VALUE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_VALUE)->SetWindowText(m_cMinValue);
    }
    if (m_dPct > 0)
    {
        CString cPct;
        cPct.Format("%0.2lf", m_dPct);
        GetDlgItem(IDC_STATIC_PCT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_PCT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_PCT)->SetWindowText(cPct);
    }

    int selpos;
    CString chPreistyp;
    m_ComboTyp.ResetContent();
    if (m_sSpec == 8)
    {
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_FREIVERKAUF));
        m_ComboTyp.SetCurSel(0);
    }
    else if (m_sSpec == 9)
    {
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_KRANKENKASSE));
        m_ComboTyp.SetCurSel(0);
    }
    else if (AeGetApp()->IsKndKasse())
    {
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_FREIVERKAUF));
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_KRANKENKASSE));
        selpos = ((CAeFView*)AeGetApp()->m_pViewEing)->m_ComboTyp.GetCurSel();
        ((CAeFView*)AeGetApp()->m_pViewEing)->m_ComboTyp.GetLBText(selpos, chPreistyp);
        short sPreistyp = CharToShort(chPreistyp.GetAt(0));
        m_ComboTyp.SetCurSel(sPreistyp == 1 ? 1 : 0);
    }
    else
    {
        m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_FREIVERKAUF));
        m_ComboTyp.SetCurSel(0);
    }
    selpos = m_ComboTyp.GetCurSel();
    m_ComboTyp.GetLBText(selpos, chPreistyp);
    m_sPreistyp = CharToShort(chPreistyp.GetAt(0));

    CStringArray s;
    CARTINF art;
    CString Text;
    ppString cText;
    int index;
    AUFPOSBUCH* ptrPos;
    if (m_ptrDoc != NULL)
    {
        ptrPos = m_ptrDoc->GetPosListe();   //Zeiger auf Beginn der Liste
        GetDlgItem(IDC_COMBO_TYP)->EnableWindow(FALSE);
    }
    BeginWaitCursor();
    long lBestand;
    GetMembers();
    m_List2->DeleteAllItems();
    for (int pos = 0; pos < m_pListRabatte->GetItemCount(); pos++)
    {
        index = m_List2->GetItemCount();
        if (m_List2->InsertItem(index, "") == -1)
        {
            return TRUE;
        }
        art.s.ARTIKEL_NR = atol(m_pListRabatte->GetItemText(pos, 2));
        if (pos == 0)
        {
            CString hilfe;
            hilfe = m_pListRabatte->GetItemText(pos, 3);
            if (hilfe == "S")
            {
                m_iStellerTyp = atoi(m_pListRabatte->GetItemText(pos, 4));
                m_bSteller = true;
                m_List2->setItemColor(0, fgb, bgg);
                if (m_iStellerTyp == 4)
                {
                    m_List2->SetNoEdit(false);
                }
            }
        }
        if (pos == 0 && m_bSteller)
        {
            art.s.BESTAND = 0;
        }
        else
        {
            art.s.FILIALNR = AeGetApp()->VzNr();
            art.Server(AatartInf_art_nr);
            lBestand = art.s.BESTAND;
            if (m_ptrDoc != NULL)
            {
                bool bHit = false;
                for (int i = 0; ; i++)
                {
                    ptrPos = m_ptrDoc->GetListPosition(i);
                    if (ptrPos == NULL) break;
                    if (ptrPos->ARTIKEL_NR == art.s.ARTIKEL_NR
                        && ptrPos->PROMOTYP == 2
                        && ptrPos->PROMOTION_NO == m_sPromono)
                    {
                        lBestand = art.s.BESTAND;
                        lBestand += ptrPos->MENGENATRA; //Gesamtbestand = bestellt und noch vorhandener
                        Text.Format("%d", lBestand);
                        m_List2->SetItemText(pos, PROMO_LC_COL_BESTAND, Text);
                        Text.Format("%d", ptrPos->MENGENATRA);
                        m_List2->SetItemText(pos, PROMO_LR_COL_MENGE, Text);        //Wunschmenge
                        art.s.BESTAND = lBestand;
                        bHit = true;
                        break;
                    }
                }
                if (!bHit)
                {
                    m_List2->SetItemText(pos, PROMO_LR_COL_MENGE, m_pListRabatte->GetItemText(pos, 1));     //Wunsch Menge
                }
            }
            else
            {
                m_List2->SetItemText(pos, PROMO_LR_COL_MENGE, m_pListRabatte->GetItemText(pos, 1));       //Wunsch Menge
            }
        }
        if (!m_bSteller)
        {
            if (art.s.BESTAND < atol(m_pListRabatte->GetItemText(pos, 1)))
            {
                CString csFehler;
                csFehler.Format(CResString::ex().getStrTblText(AETXT_NO_BESTAND_RAB)
                    , m_pListRabatte->GetItemText(pos, 2).GetString()
                    , m_pListRabatte->GetItemText(pos, 0).GetString()
                    , m_pListRabatte->GetItemText(pos, 1).GetString()
                    , art.s.BESTAND);
                MsgBoxOK(csFehler);
                CDialogMultiLang::OnCancel();
                return TRUE;
            }
        }
        else
        {
            if (pos > 0)
            {
                m_List2->setItemColor(pos, fgb, bgy);
                //m_List2->setColumnColor(PROMO_LR_COL_MENGE,fg2,bg2);
                if (art.s.BESTAND < atol(m_pListRabatte->GetItemText(pos, 1)))
                {
                    CString csFehler;
                    csFehler.Format(CResString::ex().getStrTblText(AETXT_NO_BESTAND_RAB)
                        , m_pListRabatte->GetItemText(pos, 2).GetString()
                        , m_pListRabatte->GetItemText(pos, 0).GetString()
                        , m_pListRabatte->GetItemText(pos, 1).GetString()
                        , art.s.BESTAND);
                    MsgBoxOK(csFehler);
                    CDialogMultiLang::OnCancel();
                    return TRUE;
                }
            }
        }
        m_List2->SetItemText(pos, PROMO_LR_COL_PZN, m_pListRabatte->GetItemText(pos, 2));       //name
        m_List2->SetItemText(pos, PROMO_LR_COL_NAME, m_pListRabatte->GetItemText(pos, 0));      //name
        m_List2->SetItemText(pos, PROMO_LR_COL_MIN, m_pListRabatte->GetItemText(pos, 1));       //min.Menge
        m_List2->SetItemText(pos, PROMO_LR_COL_MIN_SOLO, m_pListRabatte->GetItemText(pos, 1));  //min.Menge
        m_List2->SetItemText(pos, PROMO_LR_COL_MAX, m_pListRabatte->GetItemText(0, 1));         //max.Menge
        m_List2->SetItemText(pos, PROMO_LR_COL_MAX_SOLO, m_pListRabatte->GetItemText(0, 1));    //max.Menge
        Text.Format("%d", art.s.BESTAND);
        m_List2->SetItemText(pos, PROMO_LR_COL_BESTAND, Text);                                  //Bestand
        if (pos == 0)
        {
            CString hilfe;
            hilfe = m_pListRabatte->GetItemText(pos, 3);
            if (hilfe == "S")
            {
                m_bSteller = true;
                if (m_iStellerTyp == 4)
                {
                    m_List2->SetNoEdit(false);
                }
            }
        }
    }
    CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, 0);

    if (m_bSteller)
    {
        if (m_iStellerTyp == 4)
        {
            m_iItem2 = 1;
            m_iItem2_old = 1;
            m_List2->selectItem(1);
        }
        else
        {
            m_iItem2 = 0;
            m_iItem2_old = 0;
            m_List2->selectItem(0);
        }
    }
    EndWaitCursor();
    CString csFaktor;
    for (int faktor = 0;faktor < 100;faktor++)
    {
        csFaktor.Format("%d", faktor);
        m_ComboFaktor.AddString(csFaktor);
    }
    if (m_ptrDoc != NULL)
    {
        m_iFaktor = CheckMultiple();
        m_ComboFaktor.SetCurSel(m_iFaktor);
        if (m_iFaktor != 1)
        {
            int iMin;
            CString csMin;
            for (int pos = 0; pos < m_List1->GetItemCount(); pos++)
            {
                iMin = atoi(m_List1->GetItemText(pos, PROMO_LC_COL_MIN_SOLO));  //min.Menge
                csMin.Format("%d", iMin * m_iFaktor);
                m_List1->SetItemText(pos, PROMO_LC_COL_MIN, csMin);     //min.Menge
            }
            for (int pos = 0; pos < m_List2->GetItemCount(); pos++)
            {
                if (pos == 0 && m_bSteller && m_iStellerTyp == 4)
                {
                    iMin = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MENGE)); //max.Menge
                    csMin.Format("%d", iMin * m_iFaktor);
                    m_List2->SetItemText(pos, PROMO_LR_COL_MENGE, csMin);       //max.Menge
                }
                iMin = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MAX_SOLO));  //max.Menge
                csMin.Format("%d", iMin * m_iFaktor);
                m_List2->SetItemText(pos, PROMO_LR_COL_MAX, csMin);     //max.Menge
                iMin = atoi(m_List2->GetItemText(pos, PROMO_LR_COL_MIN_SOLO));  //min.Menge
                csMin.Format("%d", iMin * m_iFaktor);
                m_List2->SetItemText(pos, PROMO_LR_COL_MIN, csMin);     //min.Menge
            }
            double dMinWert;
            iMin = m_lMinQty * m_iFaktor;
            m_cMinMeng.Format("%d", iMin);
            GetDlgItem(IDC_EDIT_MENGE)->SetWindowText(m_cMinMeng);
            dMinWert = m_dMinValue * m_iFaktor;
            m_cMinValue.Format("%0.2lf", dMinWert);
            GetDlgItem(IDC_EDIT_VALUE)->SetWindowText(m_cMinValue);
        }
    }
    else
    {
        m_iFaktor = 1;
        m_ComboFaktor.SetCurSel(m_iFaktor);
    }
    CalcAufWert();
    CListCtrlHelper::SetFocusSelectedFocused(*m_List1, 0);
    m_List1->setItemColor(m_iItem, RGB(255, 255, 255), RGB(0, 0, 255));
    //m_List1->setColumnColor(PROMO_LC_COL_MENGE,fg,bg);
    if (m_sAnzList < 13)
    {
        GetDlgItem(IDC_EDIT_SUCH)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_SUCHE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_SUCH)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_SUCHE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SUCHE)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_SUCH)->SetFocus();
        m_editSuch.SetSel(0, -1, FALSE);
    }
    return FALSE;
}
