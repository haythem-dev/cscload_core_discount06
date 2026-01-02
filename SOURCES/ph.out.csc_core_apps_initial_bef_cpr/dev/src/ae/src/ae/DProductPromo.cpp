// DProductPromo.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "AeFView.h"
#include "AeDoc.h"
#include "rebateprice.h"
#include <promo.h>
#include "DProductPromo.h"

struct Sort
{
    int FeldID;
    int SortTyp;
} PBSort;

// CDProductPromo-Dialogfeld

IMPLEMENT_DYNAMIC(CDProductPromo, CDialog)
CDProductPromo::CDProductPromo(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDProductPromo::IDD, pParent), m_CSuch(_T(""))
{
    m_ptrDoc = NULL;
    m_lCustomerno = 0;
    m_sBranchno = 0;
    PBSort.FeldID = -1;
    PBSort.SortTyp = 0;
}

CDProductPromo::~CDProductPromo()
{
}

void CDProductPromo::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_EDIT_SUCH, m_EditSuch);
    DDX_Text(pDX, IDC_EDIT_SUCH, m_CSuch);
}


BEGIN_MESSAGE_MAP(CDProductPromo, CDialogMultiLang)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedListCtrl)
    ON_MESSAGE(WM_SETITEM, OnSetItem)
    ON_BN_CLICKED(IDC_BUTTON_BUCHEN, OnButtonBuchen)
    ON_BN_CLICKED(IDC_BUTTON_ENDE, OnButtonEnde)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_EN_CHANGE(IDC_EDIT_SUCH, OnEnChangeEditSuch)
    ON_BN_CLICKED(IDC_BUTTON_SUCH, OnBnClickedButtonSuch)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnLvnColumnclickList1)
END_MESSAGE_MAP()


// CDProductPromo-Meldungshandler

BOOL CDProductPromo::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_List1.init();
    m_List1.SetExtendedStyle(m_List1.GetExtendedStyle() | LVS_EX_GRIDLINES );       // Grid

    CenterWindow((AeGetApp()->m_pViewEing));
    m_List1.DeleteAllItems();
    CPRODUCTPROMO promo;
    CString Text;
    ppString cText;
    double dTax;
    char cStd;

    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;
    //
    promo.SetBranchno(m_sBranchno);
    promo.SetCustomerno(m_lCustomerno);
    AUFPOSBUCH* ptrPos;
    if (m_ptrDoc != NULL)
    {
        ptrPos = m_ptrDoc->GetPosListe();   //Zeiger auf Beginn der Liste
    }
    BeginWaitCursor();
    for (;;)
    {
        if (promo.SelList() != SRV_OK) break;
        int pos = m_List1.GetItemCount();

        // wichtig für Sort
        lvi.lParam = (LPARAM)pos;

        // wichtig für Sort
        if (m_List1.InsertItem(&lvi) == -1)
        {
            return TRUE;
        }
        AeGetApp()->GetTaxRates(promo.GetTaxlevel(), cStd, dTax);
        Text.Format("%d", promo.GetPromotion_no());
        m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_PROMONR, Text);
        m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_NAME, promo.GetArtikel_langname(cText));
        Text.Format("%0.2lf", GetBrutto(promo.GetPreisekapo(), dTax));
        m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_AEP, Text);
        Text.Format("%0.2lf", promo.GetDiscountvaluepct());
        m_List1.SetItemText(pos, PROMO_PP_COL_RAB, Text);
        Text.Format("%0.2lf", GetBrutto(GetNetPrice(promo.GetPreisekapo(), promo.GetDiscountvaluepct()), dTax));
        m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_RABWERT, Text);
        Text.Format("%d", promo.GetMaxqty());
        m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_MAX, Text);
        if (promo.GetArtikelaktiv() != '1')
        {
            Text = "0";
        }
        else
        {
            Text.Format("%d", promo.GetBestand());
        }
        m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_BESTAND, Text);
        if (m_ptrDoc != NULL)
        {
            bool bHit = false;
            for (int i = 0;; i++)
            {
                ptrPos = m_ptrDoc->GetListPosition(i);
                if (ptrPos == NULL) break;
                if (ptrPos->ARTIKEL_NR == promo.GetArticleno() && ptrPos->PROMOTION_NO == promo.GetPromotion_no())
                {
                    Text.Format("%d", ptrPos->MENGEBESTELLT);
                    m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_MENGE, Text);   //Wunschmenge
                    m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_GEBUCHT, Text); //gebuchte Menge
                    bHit = true;
                    break;
                }
            }
            if (!bHit)
            {
                m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_MENGE, "0");    //Wunschmenge
                m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_GEBUCHT, "0");  //gebuchte Menge
            }
        }
        else
        {
            m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_MENGE, "0");    //Wunschmenge
            m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_GEBUCHT, "0");  //gebuchte Menge
        }
        Text.Format("%d", promo.GetArticleno());
        m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_PZN, Text);
        Text.Format("%c", promo.GetAddonstddiscok());
        m_List1.SetItemText(lvi.iItem, PROMO_PP_COL_ADDON, Text);
        // wichtig für Sort
        lvi.iItem++;
    }

    EndWaitCursor();
    CalcAufWert();

    COLORREF bg = RGB(200, 200, 0);
    COLORREF fg = RGB(0, 0, 0);
    m_List1.setColumnColor(PROMO_PP_COL_MENGE, fg, bg);

    return FALSE;
}

void CDProductPromo::OnOK()
{
    UpdateData();

    if (GetFocus() == GetDlgItem(IDC_EDIT_SUCH))
    {
        OnBnClickedButtonSuch();
    }
    else if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        m_EditSuch.SetFocus();
        m_EditSuch.SetSel(0, -1, FALSE);
    }
}

void CDProductPromo::OnItemchangedListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
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
                    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, pNMLV->iItem);
                }
                break;

            case 0x0002:    // check
                CListCtrlHelper::SetItemStateSelectedFocused(m_List1, pNMLV->iItem);
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
                m_iItem = pNMLV->iItem;
            else
                this->PostMessage(WM_SETITEM, 0, 0);
        }
    }

    *pResult = 0L;
}

double CDProductPromo::GetBrutto(double preis, double tax)
{
    return (preis * ((100 + tax) / 100));
}

double CDProductPromo::GetNetPrice(double preis, double discount)
{
    CREBATEPRICE Rebates;       //Rabattstuktur
    Rebates.SetPreisekapo(preis);
    Rebates.SetDiscountvaluepct(discount);
    char error_msg[81];
    ::ServerNr(PIPE_AE_SRV, AasrvGetRebatePrice, (void*)&Rebates.s, REBATEPRICE_BES, REBATEPRICE_ANZ, error_msg);
    return Rebates.GetPreisfaktur();
}

void CDProductPromo::OnButtonEnde()
{
    for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
    {
        if (atol(m_List1.GetItemText(pos, PROMO_PP_COL_MENGE)) != atol(m_List1.GetItemText(pos, PROMO_PP_COL_GEBUCHT)))
        {
            if (MsgBoxYesNo(IDP_BUCHEN_NEU) == IDYES)
            {
                OnButtonBuchen();
            }
        }
    }

    if (!((CAeFView*)AeGetApp()->m_pViewEing)->AuftragSave())
    {
        CListCtrlHelper::SetFocusSelectedFocused(m_List1, m_iItem);
        return;
    }
    CDialogMultiLang::OnOK();
}

void CDProductPromo::OnButtonBuchen()
{
    CAUFPOSBUCH aufposbuch;
    AUFPOSBUCH* ptrPos;
    if (m_ptrDoc != NULL)
    {
        ptrPos = m_ptrDoc->GetPosListe();   //Zeiger auf Beginn der Liste
    }
    for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
    {
        bool bChange = false;
        aufposbuch.s.ARTIKEL_NR      = atol(m_List1.GetItemText(pos, PROMO_PP_COL_PZN));
        aufposbuch.s.MENGEBESTAETIGT = atol(m_List1.GetItemText(pos, PROMO_PP_COL_MENGE));
        aufposbuch.s.MENGEBESTELLT   = 0;
        if (m_ptrDoc != NULL)
        {
            for (int i = 0;; i++)
            {
                ptrPos = m_ptrDoc->GetListPosition(i);
                if (ptrPos == NULL)
                    break;
                if (   ptrPos->ARTIKEL_NR == aufposbuch.s.ARTIKEL_NR
                    && ptrPos->PROMOTION_NO == atoi(m_List1.GetItemText(pos, PROMO_PP_COL_PROMONR)) )
                {
                    bChange = true;
                    aufposbuch.s.POSNR = ptrPos->POSNR;
                    aufposbuch.s.STATUS = ptrPos->STATUS;
                    break;
                }
            }
            if (   !bChange                         // wenn noch keine Position vorhanden
                && (aufposbuch.s.MENGEBESTAETIGT == 0) )   // und nichts gewuenscht -> ueberlesen
            {
                continue;
            }   // Position vorhanden aber keine Aenderung -> ueberlesen
            else if (aufposbuch.s.MENGEBESTAETIGT == atol(m_List1.GetItemText(pos, PROMO_PP_COL_GEBUCHT)))
            {
                continue;
            }
        }
        else if (aufposbuch.s.MENGEBESTAETIGT == 0) // keine Pos. und auch nichts gewuenscht -> ueberlesen
        {
            continue;
        }
        aufposbuch.s.DISCOUNTVALUEPCT  = atof(m_List1.GetItemText(pos, PROMO_PP_COL_RAB));
        aufposbuch.s.PROMOTION_NO      = static_cast<short>(atoi(m_List1.GetItemText(pos, PROMO_PP_COL_PROMONR)));
        aufposbuch.s.PROMOTYP          = (aufposbuch.s.PROMOTION_NO == 0) ? 0 : 1;
        aufposbuch.s.PREIS_TYP         = 0;
        aufposbuch.s.ADDONSTDDISCOK[0] = m_List1.GetItemText(pos, PROMO_PP_COL_PROMONR).GetAt(0);
        CString Text;
        if (PosBuchen(&aufposbuch, bChange))
        {
            Text.Format("%d", aufposbuch.s.BESTAND);
            m_List1.SetItemText(pos, PROMO_PP_COL_BESTAND, Text);
            m_List1.SetItemText(pos, PROMO_PP_COL_MENGE, "0");
            m_List1.SetItemText(pos, PROMO_PP_COL_GEBUCHT, "0");
        }
        else
        {
            Text.Format("%d", aufposbuch.s.MENGEBESTAETIGT);
            m_List1.SetItemText(pos, PROMO_PP_COL_GEBUCHT, Text);
        }
        ((CAeDoc*)AeGetApp()->m_Doc)->AddPosition(aufposbuch.s);   //Positionsliste erstellen
    } //Ende der for(;;)
    ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerte(aufposbuch.s.ANZPOS, aufposbuch.s.WERTAUFTRAG, aufposbuch.s.WERTLIEFERUNG, aufposbuch.s.WERTZEILEN, aufposbuch.s.BALANCE, aufposbuch.s.BALANCE2);
    ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerteBG(aufposbuch.s.WERTNETTO_FV, aufposbuch.s.WERTTAX_FV, aufposbuch.s.WERTNETTO_KK, aufposbuch.s.WERTTAX_KK, aufposbuch.s.WERTNETTO_EH, aufposbuch.s.WERTTAX_EH, aufposbuch.s.WERTEXCLUSIVE);

}

void CDProductPromo::OnCancel()
{
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDProductPromo::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F4)
    {
        OnButtonEnde();
        return 1;
    }
    return 0;
}

bool CDProductPromo::CheckInput(int pos)
{
    int iInMenge = atoi(m_List1.GetItemText(pos, PROMO_PP_COL_MENGE));
    int iMaxMenge = atoi(m_List1.GetItemText(pos, PROMO_PP_COL_MAX));
    int iBestand = atoi(m_List1.GetItemText(pos, PROMO_PP_COL_BESTAND));
    if (iMaxMenge > 0)
    {
        if (iInMenge > iMaxMenge)
        {
            MsgBoxOK(AETXT_UEBER_MAX);
            CListCtrlHelper::SetItemStateSelectedFocused(m_List1, pos);
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

LRESULT CDProductPromo::OnSetItem(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    m_List1.selectItem(m_iItem);
    return 0L;
}

bool CDProductPromo::CalcAufWert()
{
    double dAufWert = 0.0;
    for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
    {
        if (!CheckInput(pos))
            return false;
        double dZeilWert = (atof(m_List1.GetItemText(pos, PROMO_PP_COL_RABWERT))
            * atol(m_List1.GetItemText(pos, PROMO_PP_COL_MENGE)));
        dAufWert += dZeilWert;
    }
    CString Text;
    Text.Format("%0.2lf", dAufWert);
    GetDlgItem(IDC_EDIT_WERT)->SetWindowText(Text);
    return true;
}

int CDProductPromo::PosBuchen(CAUFPOSBUCH* aufposbuch, bool bChange)
{
    for (;;)
    {
        aufposbuch->s.DISCOUNTVALUEPCT = 0.0;  //nur bei TargetPromo
        //Buchungsversuch
        int fkt_nr = bChange ? AasrvChangepos : AasrvWritePromoPos;
        aufposbuch->Server(fkt_nr, PIPE_AE_SRV);
        if (aufposbuch->rc < 0)    //Fehler
        {
            return -1;
        }
        if (aufposbuch->s.STATUS == ITEM_STAT_KREDITLIMIT)     //Kreditlimit ueberschritten
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
        else if (aufposbuch->s.STATUS == ITEM_STAT_KEINE_MENGE)    //Verfügbare Menge reichte nicht aus
        {
            return -1;
        }
        else
            break;
    }
    return 0;
}

void CDProductPromo::OnEnChangeEditSuch()
{
    if (PBSort.FeldID != PROMO_PP_COL_NAME && PBSort.FeldID != -1)
    {
        PBSort.FeldID = -1;
        PBSort.SortTyp = 0;
    }
    SortList1(PROMO_PP_COL_NAME);
}

void CDProductPromo::OnBnClickedButtonSuch()
{
    UpdateData();

    int len = m_CSuch.GetLength();
    for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
    {
        CString vergl = m_List1.GetItemText(pos, PROMO_PP_COL_NAME);
        if (!strncmp(vergl, m_CSuch, len))
        {
            CListCtrlHelper::SetFocusSelectedFocused(m_List1, pos);
            //Zeilenhoehe ermitteln
            CRect itemRect;
            m_List1.GetItemRect(0, itemRect, LVIR_BOUNDS);
            int hoehe = itemRect.Height();
            //zuerst auf Listanfang
            CSize scrollback(0, (m_List1.GetItemCount() * hoehe * (-1)));
            m_List1.Scroll(scrollback);
            //jetzt auf gesuchte Position
            CSize scrollfaktor(0, pos * hoehe);
            m_List1.Scroll(scrollfaktor);
            break;
        }
    }
}

// CompareListe ist eine stand alone Funktion
/////////////////////////////////////////////////////////////////////////////
// CompareListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
/////////////////////////////////////////////////////////////////////////////
int CALLBACK ComparePBListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    int rc;
    if (s->GetAt(lParam1) == s->GetAt(lParam2))
        rc = 0;
    else if (s->GetAt(lParam1) > s->GetAt(lParam2))
        rc = 1;
    else
        rc = -1;

    if (PBSort.SortTyp == 1)
        rc *= -1;
    return rc;
}

int CALLBACK ComparePBListeDouble(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    int rc;
    double feld1 = atof(s->GetAt(lParam1));
    double feld2 = atof(s->GetAt(lParam2));
    if (feld1 == feld2)
        rc = 0;
    else if (feld1 > feld2)
        rc = 1;
    else
        rc = -1;

    if (PBSort.SortTyp == 1)
        rc *= -1;
    return rc;
}

int CALLBACK ComparePBListeLong(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    int rc;
    long feld1 = atol(s->GetAt(lParam1));
    long feld2 = atol(s->GetAt(lParam2));
    if (feld1 == feld2)
        rc = 0;
    else if (feld1 < feld2)
        rc = 1;
    else
        rc = -1;

    if (PBSort.SortTyp == 1)
        rc *= -1;
    return rc;
}

void CDProductPromo::OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int col = pNMListView->iSubItem;
    SortList1(col);
    *pResult = 0L;
}

void CDProductPromo::SortList1(int col)
{
    //Wegen Sort
    LV_ITEM lvi;
    //
    int max = m_List1.GetItemCount();
    CStringArray s;
    s.SetSize(max);
    for (int index = 0; index < max; index++)
    {
        //StringArray an der ursprünglichen Position setzen
        lvi.iItem = index;
        lvi.mask = LVIF_PARAM;  //muss gesetzt sein, um lParam abzuholen
        m_List1.GetItem(&lvi);  //Ursprungadresse steht in lParam
        s[(int)lvi.lParam] = m_List1.GetItemText(index, col);
    }
    if (PBSort.FeldID == col)
    {
        PBSort.SortTyp = (PBSort.SortTyp == 0) ? 1 : 0;
    }
    else
    {
        PBSort.FeldID = col;
        PBSort.SortTyp = 0;
    }

    if (col == PROMO_PP_COL_AEP || col == PROMO_PP_COL_RAB || col == PROMO_PP_COL_RABWERT)
        m_List1.SortItems(ComparePBListeDouble, (LPARAM)&s);

    else if (   col == PROMO_PP_COL_PROMONR || col == PROMO_PP_COL_MAX || col == PROMO_PP_COL_BESTAND
             || col == PROMO_PP_COL_MENGE || col == PROMO_PP_COL_GEBUCHT || col == PROMO_PP_COL_PZN
             || col == PROMO_PP_COL_ADDON )
        m_List1.SortItems(ComparePBListeLong, (LPARAM)&s);
    else
        m_List1.SortItems(ComparePBListe, (LPARAM)&s);

    //nach Sort immer auf Listanfang positionieren
    //Zeilenhoehe ermitteln
    CRect itemRect;
    m_List1.GetItemRect(0, itemRect, LVIR_BOUNDS);
    int hoehe = itemRect.Height();
    //zuerst auf Listanfang
    CSize scrollback(0, (m_List1.GetItemCount() * hoehe * (-1)));
    m_List1.Scroll(scrollback);
}
