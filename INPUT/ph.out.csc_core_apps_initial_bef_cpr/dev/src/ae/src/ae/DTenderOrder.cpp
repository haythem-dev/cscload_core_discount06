// DTenderOrder.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "AeDoc.h"
#include "AeFView.h"
#include "DBePosBearb.h"
#include "DArtInf.h"
#include <tender.h>
#include "DViewPos.h"
#include "DTenderOrder.h"


// CDTenderOrder-Dialogfeld

IMPLEMENT_DYNAMIC(CDTenderOrder, CDialog)
CDTenderOrder::CDTenderOrder(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTenderOrder::IDD, pParent)
{
    m_lTenderNo = 0;
    m_lKndNr = 0;
    m_dPct = -1;
    m_CMenge = _T("");
    m_CSuch = _T("");
    m_Charge = _T("");
    bgg = RGB(255,0,0);
    fgb = RGB(0,0,0);
    m_bChain = false;
}

CDTenderOrder::~CDTenderOrder()
{
}

void CDTenderOrder::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_CMenge);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_EditMenge);
    DDX_Text(pDX, IDC_EDIT_SUCH, m_CSuch);
    DDX_Control(pDX, IDC_EDIT_SUCH, m_EditSuch);
}


BEGIN_MESSAGE_MAP(CDTenderOrder, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
    ON_BN_CLICKED(IDC_BUTTON_BEARB, OnButtonBearb)
    ON_BN_CLICKED(IDC_BUTTON_SUCH, OnButtonSuch)
    ON_EN_CHANGE(IDC_EDIT_MENGE, OnChangeEditMenge)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


// CDTenderOrder-Meldungshandler

BOOL CDTenderOrder::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (AeGetApp()->IsBG())
    {
        GetDlgItem( IDC_STATIC_MENGE )->EnableWindow(FALSE);
        GetDlgItem( IDC_STATIC_MENGE )->ShowWindow(SW_HIDE);
        GetDlgItem( IDC_EDIT_MENGE )->EnableWindow(FALSE);
        GetDlgItem( IDC_EDIT_MENGE )->ShowWindow(SW_HIDE);
        GetDlgItem( IDC_STATIC_SUCH )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_SUCH )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_EDIT_SUCH )->EnableWindow(TRUE);
        GetDlgItem( IDC_EDIT_SUCH )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_BUTTON_SUCH )->EnableWindow(TRUE);
        GetDlgItem( IDC_BUTTON_SUCH )->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem( IDC_STATIC_MENGE )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_MENGE )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_EDIT_MENGE )->EnableWindow(TRUE);
        GetDlgItem( IDC_EDIT_MENGE )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_SUCH )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_SUCH )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_EDIT_SUCH )->EnableWindow(TRUE);
        GetDlgItem( IDC_EDIT_SUCH )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_BUTTON_SUCH )->EnableWindow(TRUE);
        GetDlgItem( IDC_BUTTON_SUCH )->ShowWindow(SW_SHOW);
    }

    if (m_dPct < 0)
    {
        CTENDERINFO info;
        info.SetTenderno(m_lTenderNo);
        if (info.SelTender())
        {
            CDialogMultiLang::OnCancel();
            return TRUE;
        }
        else
        {
            if (info.GetPharmacychainno() > 0)
                m_bChain = true;
            m_dPct = info.GetExceedancepct();
            AeGetApp()->IsTOStaat = (info.GetTendertype() == 0);
        }
    }

    m_List1.init();
    m_List1.SetExtendedStyle(m_List1.GetExtendedStyle()
                                | LVS_EX_FULLROWSELECT
                                | LVS_EX_GRIDLINES );        // Grid

    AeGetApp()->IsTOOpen = true;
    CTENDERSTOCK stock;
    CARTIKELRESERVE reserv;
    //Variablen
    ppString einheit;
    ppString name;
    CString Text;
    double dTax = 0.0;
    char cStd;

    //Anfangsinitialisierung durchfuehren
    m_List1.DeleteAllItems();

    CTENDERARTICLE tenderarticle;
    tenderarticle.SetTenderno(m_lTenderNo);
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (tenderarticle.SelList() != SRV_OK)
            break;
        stock.SetFilialnr(AeGetApp()->VzNr());
        stock.SetArtikel_nr(tenderarticle.GetArticleno());
        stock.SetTenderno(m_lTenderNo);
        if (stock.SelQty())
            continue;
        reserv.SetBranchno(AeGetApp()->VzNr());
        reserv.SetArticleno(tenderarticle.GetArticleno());
        reserv.SetCustomerno(m_lKndNr);
        if (!reserv.SelArtKnd())    //reservierte Bestaende mit beruecksichtigen
        {
            Text.Format("%d", (stock.GetBestand() + reserv.GetReservedqty()));
        }
        else
        {
            Text.Format("%d", stock.GetBestand());
        }
        if (atol(Text) <= 0 && AeGetApp()->IsRS())
            continue;
        int index = m_List1.GetItemCount();
        if (m_List1.InsertItem(index, "") == -1)
        {
            EndWaitCursor();
            return FALSE;
        }
        m_List1.SetItemText(index, TENDER_LC_COL_BESTAND, Text);
        m_List1.SetItemText(index, TENDER_LC_COL_KB, kb.Next());
        Text.Format("%d", (stock.GetDeliveryqty() - stock.GetReturnqty()));
        m_List1.SetItemText(index, TENDER_LC_COL_GELIEFERT, Text);
        Text.Format("%d", tenderarticle.GetContractqty());
        m_List1.SetItemText(index, TENDER_LC_COL_VEREINBART, Text);
        Text.Format("%d", tenderarticle.GetArticleno());
        m_List1.SetItemText(index, TENDER_LC_COL_PZN, Text);
        tenderarticle.GetEinheit(einheit);
        m_List1.SetItemText(index, TENDER_LC_COL_EINHEIT, einheit);
        if (AeGetApp()->IsBG())
        {
            tenderarticle.GetArtikel_langname(name);
        }
        else
        {
            tenderarticle.GetArtikel_name(name);
        }
        m_List1.SetItemText(index, TENDER_LC_COL_ARTIKELNAME, name);
        if (AeGetApp()->IsBG())
        {
            double Spanne;
            AeGetApp()->GetTaxRates(tenderarticle.GetTaxlevel(), cStd, dTax);
            Text.Format("%0.2lf", GetBrutto(tenderarticle.GetContractprice(), dTax));
            m_List1.SetItemText(index, TENDER_LC_COL_PREIS, Text);
            Text.Format("%0.2lf", GetBrutto(tenderarticle.GetPreisekapo(), dTax));
            m_List1.SetItemText(index, TENDER_LC_COL_AEP, Text);
            Spanne = ((tenderarticle.GetContractprice() - tenderarticle.GetPreisekgrossona()) / (tenderarticle.GetContractprice())) * 100;
            Text.Format("%0.2lf", Spanne);
            m_List1.SetItemText(index, TENDER_LC_COL_SPANNE, Text);
        }
        else
        {
            Text.Format("%0.2lf", tenderarticle.GetContractprice());
            m_List1.SetItemText(index, TENDER_LC_COL_PREIS, Text);
        }
        Text.Format("%0.2lf", tenderarticle.GetAdddiscountpct());
        m_List1.SetItemText(index, TENDER_LC_COL_RABATT, Text);
        Text.Format("%02d/%02d", stock.GetDatumverfall() % 100, stock.GetDatumverfall() / 100);
        m_List1.SetItemText(index, TENDER_LC_COL_VERFALL, Text);
        Text.Format("%d", tenderarticle.GetTaxlevel());
        m_List1.SetItemText(index, TENDER_LC_COL_TAXLEVEL, Text);
        Text.Format("%0.2lf", tenderarticle.GetPreisekgrosso());
        m_List1.SetItemText(index, TENDER_LC_COL_GROSSO, Text);
        if (AeGetApp()->IsBG())
        {
            if ((GetBrutto(tenderarticle.GetPreisekapo(), dTax)) < (GetBrutto(tenderarticle.GetContractprice(), dTax)))
            {
                m_List1.setItemColor(index, fgb, bgg);
            }
        }
    }
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);

    return TRUE;
}

void CDTenderOrder::OnOK()
{
    UpdateData();

    if (!AeGetApp()->IsBG())
    {
        if (GetFocus() == GetDlgItem(IDC_EDIT_SUCH))
        {
            OnButtonSuch();
            return;
        }
        else if (m_CMenge.IsEmpty())
        {
            MsgBoxOK(IDP_MENGE_EINGEBEN);
            m_EditMenge.SetFocus();
            return;
        }
    }
    else
    {
        if (GetFocus() == GetDlgItem(IDC_EDIT_SUCH))
        {
            OnButtonSuch();
            return;
        }
    }

    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
        return;
    }
    if (AeGetApp()->IsBG())
    {
        if (!Auswahl(pos))
            return;
    }

    long geliefert;
    long bestand;
    long wished;
    long soll;
    long frei;
    long hoch;
    double faktor;
    long maxmeng;
    double dmax;
    double dPreis;
    double dGrosso;
    if (m_bChain)
    {
        CTENDERSTOCK stock;
        CARTIKELRESERVE reserv;
        CString Text;
        stock.SetFilialnr(AeGetApp()->VzNr());
        stock.SetArtikel_nr(atol(m_List1.GetItemText(pos, TENDER_LC_COL_PZN)));
        stock.SetTenderno(m_lTenderNo);
        stock.SelQty();
        reserv.SetBranchno(AeGetApp()->VzNr());
        reserv.SetArticleno(atol(m_List1.GetItemText(pos, TENDER_LC_COL_PZN)));
        reserv.SetCustomerno(m_lKndNr);
        if (!reserv.SelArtKnd())    //reservierte Bestaende mit beruecksichtigen
        {
            Text.Format("%d",(stock.GetBestand() + reserv.GetReservedqty()));
        }
        else
        {
            Text.Format("%d",stock.GetBestand());
        }
        m_List1.SetItemText(pos,TENDER_LC_COL_BESTAND,Text);
        Text.Format("%d",(stock.GetDeliveryqty()-stock.GetReturnqty()));
        m_List1.SetItemText(pos,TENDER_LC_COL_GELIEFERT,Text);
    }
    dPreis = atof(m_List1.GetItemText(pos, TENDER_LC_COL_PREIS));
    dGrosso = atof(m_List1.GetItemText(pos, TENDER_LC_COL_GROSSO));
    bestand = atol(m_List1.GetItemText(pos, TENDER_LC_COL_BESTAND));
    if (atol(m_CMenge) > bestand)
    {
        MsgBoxOK( AETXT_MENGE_BESTAND );
        return;
    }
    if (   (atol(m_CMenge) * dPreis) >= 10000000.00
        || (atol(m_CMenge) * dGrosso) >= 10000000.00 )
    {
        MsgBoxOK(IDP_WARN_HOHER_WERT);
        return;
    }
    geliefert = atol(m_List1.GetItemText(pos, TENDER_LC_COL_GELIEFERT));
    soll = atol(m_List1.GetItemText(pos, TENDER_LC_COL_VEREINBART));
    wished = atol(m_CMenge);
    frei = soll - geliefert;
    if (AeGetApp()->IsBG() && !AeGetApp()->IsTOStaat())
    {
    }
    else if (wished > frei)
    {
        faktor = (m_dPct + 100)/100;
        dmax = (soll * faktor) + 0.99;
        maxmeng = (long)dmax;
        hoch = maxmeng - geliefert;
        if (wished > hoch)
        {
            CString meldtext;
            long qty = frei;
            long max = maxmeng-soll;
            if (frei < 0)
            {
                qty = 0;
                max = max + frei;
            }
            meldtext.Format(CResString::ex().getStrTblText(AETXT_ERL_MAX_MENGE), qty, max);
            MsgBoxOK(meldtext);
            m_EditMenge.SetFocus();
            m_EditMenge.SetSel(0, -1, FALSE);
            return;
        }
        else
        {
            CString meldtext;
            meldtext.Format(CResString::ex().getStrTblText(AETXT_UEBER_MENGE), frei, (maxmeng - soll));
            if (MsgBoxYesNo(meldtext) == IDNO)
                wished = frei;
            if (wished <= 0)
            {
                m_EditMenge.SetFocus();
                m_EditMenge.SetSel(0, -1, FALSE);
                return;
            }
        }
    }
    CAUFPOSBUCH aufposbuch;
    long MengeAlt = 0;
    long PosStat;
    bool bChangePos = FALSE;
    CString Bemerkung;
    long MengeBestellt = wished;
    AUFPOSBUCH* ptrPos = ptrDoc->GetPosListe(); //Zeiger auf Beginn der Liste
    if (MengeBestellt != 0)
    {
        long lArtnr = atol(m_List1.GetItemText(pos, TENDER_LC_COL_PZN));
        for (int i = 0;; i++)
        {
            ptrPos = ptrDoc->GetListPosition(i);
            if (ptrPos == NULL)
                break;
            if (ptrPos->ARTIKEL_NR == lArtnr)
            {
                if (AeGetApp()->IsBG())
                {
                    CString abcd;
                    abcd = ptrPos->CHARGENNR;
                    abcd.TrimRight();
                    if (m_Charge != abcd)
                        continue;
                }
                MengeAlt = ptrPos->MENGEBESTELLT;
                if (((MengeAlt + MengeBestellt) * dPreis) >= 10000000.00)
                {
                    continue;
                }
                MengeBestellt = aufposbuch.s.MENGEBESTELLT = ptrPos->MENGEBESTELLT + MengeBestellt;
                aufposbuch.s.POSNR = ptrPos->POSNR;
                PosStat = aufposbuch.s.STATUS = ptrPos->STATUS;
                bChangePos = TRUE;
                break;
            }
        }
    }
    if (MengeBestellt != 0)
    {
        long MengeAbbuchung = MengeBestellt;
        PosStat = ITEM_STAT_NORMAL;
        for (;;)
        {
            aufposbuch.s.DISCOUNTVALUEPCT  = 0.0;  //nur bei TargetPromo
            aufposbuch.s.MENGEBESTELLT     = MengeBestellt;
            aufposbuch.s.MENGEBESTAETIGT   = MengeAbbuchung;
            aufposbuch.s.ARTIKEL_NR        = atol(m_List1.GetItemText(pos, TENDER_LC_COL_PZN));
            aufposbuch.s.MENGENATRA        = 0;
            aufposbuch.s.STATUS = AeGetApp()->IsBG() && m_bIgnore ? ITEM_STAT_IGNORE_PRICELIMIT : PosStat;
            strcpy(aufposbuch.s.BEMERKUNG, (LPCTSTR)Bemerkung);
            strcpy(aufposbuch.s.CHARGENNR, (LPCTSTR)m_Charge);

            //Buchungsversuch
            aufposbuch.Server(bChangePos ? AasrvChangepos : AasrvWritepos, PIPE_AE_SRV);
            if (aufposbuch.rc < SRV_OK)                                    //Fehler
            {
                return;
            }
            if (aufposbuch.s.STATUS == ITEM_STAT_KREDITLIMIT)              //Kreditlimit ueberschritten
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
                    continue; //Position erneut buchen
                }
            }
// Pricelimit Anfang
            else if (aufposbuch.s.STATUS == ITEM_STAT_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE)             //zugelassener Preis überschritten
            {
                if (MsgBoxYesNo(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_1), MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDYES)
                {
                    aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
                    continue;
                }
                return;
            }

            else if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE)             //zugelassener Preis überschritten
            {
                if (MsgBoxYesNo(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_2), MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDYES)
                {
                    aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
                    continue;
                }
                return;
            }

            else if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION_06)             //zugelassener Preis überschritten
            {
                if (MsgBoxYesNo(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_3), MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDYES)
                {
                    aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
                    continue;
                }
                return;
            }
            else if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_MWP_EXCEEDANCE)            //zugelassener Preis überschritten
            {
                MsgBoxOK(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_0));
                aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
                continue;
            }

            else if (aufposbuch.s.STATUS == ITEM_STAT_LIMIT_PRODUCT_PRICE_DELETION)            //zugelassener Preis überschritten
            {
                MsgBoxOK(CResString::ex().getStrTblText(AETXT_PRICELIMIT_EXCEEDED_4));
                aufposbuch.s.STATUS = ITEM_STAT_IGNORE_PRICELIMIT;
            }
            // Pricelimit Ende

            if (aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE) //bei tender aktuell nur vorhandene Menge Buchen       //Verfügbare Menge reichte nicht aus
            {
                MsgBoxOK(AETXT_MENGE_BESTAND);
                CString buf;
                buf.Format("%d", aufposbuch.s.BESTAND);
                m_List1.SetItemText(pos, 1, buf);
                return;
            }
            if (aufposbuch.s.STATUS == ITEM_STAT_NACHLIEFUPD) //bei tender aktuell nur vorhandene Menge (wg. Kontigent) Buchen       //Verfügbare Menge reichte nicht aus
            {
                CString meld;
                meld.Format(CResString::ex().getStrTblText(AETXT_MAX_QUOTA), aufposbuch.s.BESTAND);
                MsgBoxOK(meld);
                CString buf;
                buf.Format("%d", aufposbuch.s.BESTAND);
                m_List1.SetItemText(pos, 1, buf);
                return;
            }
            if (aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE)            //Verfügbare Menge reichte nicht aus
            {
                CDBePosBearb dlgBePosBearb;
                dlgBePosBearb.SetBestMengeStr("%ld", MengeBestellt);
                dlgBePosBearb.m_CArtName        = m_List1.GetItemText(pos, TENDER_LC_COL_ARTIKELNAME);
                dlgBePosBearb.m_CArtEinh        = m_List1.GetItemText(pos, TENDER_LC_COL_EINHEIT);
                dlgBePosBearb.SetArtNr(m_List1.GetItemText(pos, TENDER_LC_COL_PZN));
                dlgBePosBearb.m_CArtCode        = m_List1.GetItemText(pos, TENDER_LC_COL_PZN);
                dlgBePosBearb.SetBestand("%d", aufposbuch.s.BESTAND);
                dlgBePosBearb.SetVerbMenge(aufposbuch.s.MENGE);
                dlgBePosBearb.SetVerbFiliale(aufposbuch.s.FILIALNR1);
                dlgBePosBearb.m_CDarreichform.Empty();
                dlgBePosBearb.m_LiefMenge       = aufposbuch.s.BESTAND;
                dlgBePosBearb.SetBestMenge(MengeBestellt);
                dlgBePosBearb.m_CBemerkung      = Bemerkung;
                dlgBePosBearb.SetPosStat(ITEM_STAT_NACHLIEFERN);
                dlgBePosBearb.m_KndNr           = m_lKndNr;
                dlgBePosBearb.m_IdfNr           = m_lKndNr;
                if (dlgBePosBearb.DoModal() == IDOK)
                {
                    MengeAbbuchung  = dlgBePosBearb.m_Menge;
                    PosStat         = dlgBePosBearb.GetPosStat();
                    Bemerkung       = dlgBePosBearb.m_CBemerkung;
                    aufposbuch.s.FILIALNR1 = dlgBePosBearb.GetVerbFiliale();
                    continue; //Position erneut buchen
                }
                else
                {
                    return;
                }
            }
            else if (aufposbuch.s.STATUS == ITEM_STAT_VERBUND_NICHT_MOEGLICH)
            {
                MsgBoxOK(IDP_AUX_BAD_STATE);
                return;
            }
            break;
        } //Ende der for(;;)

        if (aufposbuch.s.STATUS == ITEM_STAT_VERBUND_REICHT_NICHT)   //Verfügbare Verbundmenge reichte nicht aus
        {
            CString Str;
            Str.Format(CResString::ex().getStrTblText(IDS_MENGE_BEST_BEST),
                aufposbuch.s.MENGEBESTELLT,
                aufposbuch.s.MENGEBESTAETIGT,
                aufposbuch.s.MENGE);
            CString CStr;
            CStr.Format(CResString::ex().getStrTblText(IDP_VB_MENGE_WENIG), Str.GetString());
            MsgBoxOK(CStr);
        }

        if (bChangePos)
        {
            ptrDoc->UpdPosition(ptrPos->POSNR, aufposbuch.s);  //Positionsliste aktualisieren
        }
        else
        {
            ((CAeDoc*)AeGetApp()->m_Doc)->AddPosition(aufposbuch.s);  //Positionsliste erstellen
        }
        ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerte(aufposbuch.s.ANZPOS, aufposbuch.s.WERTAUFTRAG, aufposbuch.s.WERTLIEFERUNG, aufposbuch.s.WERTZEILEN, aufposbuch.s.BALANCE, aufposbuch.s.BALANCE2);
        ((CAeFView*)AeGetApp()->m_pViewEing)->AusgAufWerteBG(aufposbuch.s.WERTNETTO_FV, aufposbuch.s.WERTTAX_FV, aufposbuch.s.WERTNETTO_KK, aufposbuch.s.WERTTAX_KK, aufposbuch.s.WERTNETTO_EH, aufposbuch.s.WERTTAX_EH, aufposbuch.s.WERTEXCLUSIVE);
    }
    CString Buffer;
    Buffer.Format("%d", aufposbuch.s.BESTAND);
    m_List1.SetItemText(pos, 1, Buffer);
    geliefert = atol(m_List1.GetItemText(pos, TENDER_LC_COL_GELIEFERT)) + (aufposbuch.s.MENGEBESTAETIGT - MengeAlt);
    Buffer.Format("%d", geliefert);
    m_List1.SetItemText(pos, TENDER_LC_COL_GELIEFERT, Buffer);
    if (AeGetApp()->IsBG())
    {
        m_EditSuch.SetFocus();
        m_EditSuch.SetSel(0, -1, FALSE);
    }
    else
    {
        m_EditMenge.SetFocus();
        m_EditMenge.SetSel(0, -1, FALSE);
    }
    // Selection aufheben
    CListCtrlHelper::SetItemStateClear(m_List1, pos);
}

void CDTenderOrder::OnChangeEditMenge()
{
    CString str;
    CString CMenge;

    m_EditMenge.GetWindowText(str);
    if (str.IsEmpty())                              //Feld ist leer
        return;
    char chN = str[str.GetLength() - 1];            //letztes Zeichen lesen
    if (isdigit((int)chN))
    {
        AllgWertKontr(&m_EditMenge, MAXIMUM_BUCH_MENGE);
        return;
    }
    str = str.Left(str.GetLength() - 1);            //letztes Zeichen löschen
    m_EditMenge.SetWindowText(str);                 //String zurückschreiben
    if (CLetterMan::InRange(chN, m_List1.GetItemCount()))
    {
        int pos = chN - AeGetApp()->Letter_A();
        CListCtrlHelper::SetFocusSelectedFocused(m_List1, pos);
    }
}

void CDTenderOrder::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnOK();
    *pResult = 0L;
}

void CDTenderOrder::OnButtonSave()
{
    if (!((CAeFView*)AeGetApp()->m_pViewEing)->AuftragSave())
    {
        if (AeGetApp()->IsTOOpen())
        {
            m_EditMenge.SetFocus();
            m_EditMenge.SetSel(0, -1, FALSE);
            return;
        }
    }
    CDialogMultiLang::OnOK();
}

void CDTenderOrder::OnButtonSuch()
{
    UpdateData();
    int numeric = 1;
    int found = 0;
    CString vergl;
    int len = m_CSuch.GetLength();
    if (len == 0)
        return;
    for (int i = 0; i < len; i++)
    {
        if (m_CSuch.GetAt(i) < '0' || m_CSuch.GetAt(i) > '9')
        {
            numeric = 0;
            break;
        }
    }
    for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
    {
        if (numeric)
        {
            vergl = m_List1.GetItemText(pos, TENDER_LC_COL_PZN);
            if (atol(vergl) == atol(m_CSuch))
                found = 1;
        }
        else
        {
            vergl = m_List1.GetItemText(pos, TENDER_LC_COL_ARTIKELNAME);
            if (!strncmp(vergl, m_CSuch, len))
                found = 1;
        }
        if (found)
        {
            CListCtrlHelper::SetFocusSelectedFocused(m_List1, pos);
            //Zeilenhoehe ermitteln
            CRect itemRect;
            m_List1.GetItemRect(0, itemRect, LVIR_BOUNDS);
            int hoehe = itemRect.Height();
            //zuerst auf Listanfang
            CSize scrollback(0, (m_List1.GetItemCount() * hoehe * (-1)));
            int rc = m_List1.Scroll(scrollback);
            //jetzt auf gesuchte Position
            CSize scrollfaktor(0, pos * hoehe);
            rc = m_List1.Scroll(scrollfaktor);
            break;
        }
    }
}

void CDTenderOrder::OnButtonBearb()
{
    struct SaveArtikel Save;
    m_pl.clear();
    AUFPOSBUCH *ptrPos = ptrDoc->GetPosListe(); //Zeiger auf Beginn der Liste

    for (int i = 0;; i++)
    {
        ptrPos = ptrDoc->GetListPosition(i);
        if (ptrPos == NULL)
            break;
        Save.ArtNo = ptrPos->ARTIKEL_NR;
        Save.Menge = ptrPos->MENGEBESTELLT;
        m_pl.insert(m_pl.end(), Save);
    }
    ((CAeFView*)AeGetApp()->m_pViewEing)->OnAuftrBearb();
    CString Buffer;
    long bestand;
    long geliefert;
    for (int i = 0;; i++)
    {
        ptrPos = ptrDoc->GetListPosition(i);
        if (ptrPos == NULL)
            break;
        if (ptrPos->MENGEBESTELLT != m_pl.at(i).Menge)
        {
            for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
            {
                if (atol(m_List1.GetItemText(pos, TENDER_LC_COL_PZN)) == m_pl.at(i).ArtNo)
                {
                    bestand = atol(m_List1.GetItemText(pos, 1))
                            - (ptrPos->MENGEBESTELLT - m_pl.at(i).Menge);
                    Buffer.Format("%d", bestand);
                    m_List1.SetItemText(pos, 1, Buffer);
                    geliefert = atol(m_List1.GetItemText(pos, TENDER_LC_COL_GELIEFERT))
                              + (ptrPos->MENGEBESTELLT - m_pl.at(i).Menge);
                    Buffer.Format("%d", geliefert);
                    m_List1.SetItemText(pos, TENDER_LC_COL_GELIEFERT, Buffer);
                    break;
                }
            }
        }
    }
    m_EditMenge.SetFocus();
    m_EditMenge.SetSel(0, -1, FALSE);
}

void CDTenderOrder::OnCancel()
{
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDTenderOrder::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F2)
    {
        OnButtonBearb();
        return 1L;
    }
    if (((LPMSG)lpMsg)->wParam == VK_F4)
    {
        OnButtonSave();
        return 1L;
    }
    if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
        if (pos < 0)
            return 0L;
        CDArtInf dlgArtInf(atol(m_List1.GetItemText(pos, TENDER_LC_COL_PZN)));
        dlgArtInf.DoModal();
        return 1L;
    }
    return 0L;
}

bool CDTenderOrder::Auswahl(int pos)
{
    CDViewPos dlgViewPos;
    dlgViewPos.m_sPreistyp = 0;
    ((CAeFView*)AeGetApp()->m_pViewEing)->GetDlgItem(IDC_STATIC_AA)->GetWindowText(dlgViewPos.m_cAArt);
    dlgViewPos.m_csARTIKELNAME = m_List1.GetItemText(pos, TENDER_LC_COL_ARTIKELNAME);
    dlgViewPos.m_csPZN = m_List1.GetItemText(pos, TENDER_LC_COL_PZN);
    dlgViewPos.m_csAEP = m_List1.GetItemText(pos, TENDER_LC_COL_PREIS);
    dlgViewPos.m_csBestand = m_List1.GetItemText(pos, TENDER_LC_COL_BESTAND);
    dlgViewPos.m_csTaxlevel = m_List1.GetItemText(pos, TENDER_LC_COL_TAXLEVEL);
    dlgViewPos.m_csRabatt = m_List1.GetItemText(pos, TENDER_LC_COL_RABATT);
    dlgViewPos.m_csSpanne = m_List1.GetItemText(pos, TENDER_LC_COL_SPANNE);

    if (dlgViewPos.DoModal() != IDOK)
        return FALSE;
    m_bIgnore = dlgViewPos.m_bIgnore;
    m_CMenge = dlgViewPos.m_csMENGE;
    m_Charge = dlgViewPos.m_csCharge;
    return TRUE;
}

double CDTenderOrder::GetBrutto(double preis, double tax)
{
    return (preis * ((100 + tax) / 100));
}
