// DOrderInformation1.cpp : implementation file
//

#include "stdafx.h"
#include "DOrderInformation1.h"
#include "AeDoc.h"
#include <kndsel.h>
#include "DKndInf.h"
#include <orders.h>
#include "DArtInf.h"
#include "zeitart.h"
#include "DAufTxt.h"
#include "DAuftrEreign.h"
#include "DDruckAuftrag.h"
#include "DAeAnzFrText.h"
#include <artsel.h>
#include <verbundcheck.h>
#include "DSeralog.h"
#include "MainFrm.h"
#include <auftraginfo.h>
#include <artikel.h>
#include "DNewCallback.h"
#include "DWannauswahl.h"
#include "taufartk.h"
#include "DHPMakeCall.h"
#include "tourdelay.h"


#define PROD_QUOTA       3
#define LIEFBER_BTM      4
#define LIEFBER_KUEHL    5
#define LIEFBER_KUEHL_U8 6
#define LIEFBER_COOL20   7
#define LIEFBER_DEGETTER 8

//Definition der Tabellenbreite und der Ueberschriften

// CDOrderInformation1 dialog

IMPLEMENT_DYNAMIC(CDOrderInformation1, CPropertyPage)

CDOrderInformation1::CDOrderInformation1()
    : CTabPageMultiLang(IDD_AE_ORDER_INFORMATION1)
{
    m_bCall = false;
    m_bNurDef = FALSE;
    m_TenderNo = 0;
    m_Datum = 0;
    m_LAuftNr = 0;
    m_ActDatum = 0;
    m_sFVRabkonto = 0;
    m_sKKRabkonto = 0;
    m_bSelProforma = FALSE;
    m_cRechnr = _T("");
    m_cIVCnr = _T("");
    m_ListCtl = new CAufInfListCtrl;
    assert(m_ListCtl);

}

CDOrderInformation1::~CDOrderInformation1()
{
    delete m_ListCtl;
    m_ListCtl = 0;
}

void CDOrderInformation1::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_NUR_DEF, m_CBNurDef);
    DDX_Control(pDX, IDC_LIST_AUFTRAG, *m_ListCtl);
    DDX_Check(pDX, IDC_CHECK_NUR_DEF, m_bNurDef);
}


BEGIN_MESSAGE_MAP(CDOrderInformation1, CTabPageMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_KOPF_FUSS, OnButtonKopfFuss)
    ON_BN_CLICKED(IDC_BUTTON_EREIGNIS, OnButtonEreignis)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_BN_CLICKED(IDC_CHECK_NUR_DEF, OnCheckNurDef)
    ON_BN_CLICKED(IDC_BUTTON_VB_BUCH, OnButtonVbBuch)
    ON_BN_CLICKED(IDC_BUTTON_DEFBUCH, OnButtonDefbuch)
    ON_BN_CLICKED(IDC_BUTTON_SERALOG, OnButtonSeralog)
    ON_BN_CLICKED(IDC_BUTTON_AUF_NEU, OnButtonAufNeu)
    ON_WM_CTLCOLOR()
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_AUFTRAG, OnLvnColumnclickListAuftrag)
    ON_BN_CLICKED(IDC_BUTTON_AUF_NEU_ALLE, OnBnClickedButtonAufNeuAlle)
    ON_BN_CLICKED(IDC_BUTTON_AUF_CALLBACK, OnBnClickedButtonAufCallback)
    ON_BN_CLICKED(IDC_BUTTON_CREMA_STORNO, OnBnClickedButtonCremaStorno)
    ON_BN_CLICKED(IDC_BUTTON_CREMA_CLOSE, &CDOrderInformation1::OnBnClickedButtonCremaClose)
    ON_BN_CLICKED(IDC_BUTTON_LIEF, &CDOrderInformation1::OnBnClickedButtonLief)
    ON_BN_CLICKED(IDC_BUTTON_CALL, OnButtonCall)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK2, &CDOrderInformation1::OnBnClickedButtonDruck2)
END_MESSAGE_MAP()


// CDOrderInformation1 message handlers

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CDOrderInformation1::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_AUFTRAGS_INFO);
    return _T(m_csTitle);
}

BOOL CDOrderInformation1::OnInitDialog()
{
    CTabPageMultiLang::OnInitDialog();
    m_ListCtl->init();
    if (AeGetApp()->IsBG())
    {
        m_ListCtl->SetExtendedStyle(m_ListCtl->GetExtendedStyle()
            | LVS_EX_GRIDLINES);        // Grid
    }
    m_ListCtl->SetFocus();
    CenterWindow();

    DWORD dwOldBits = m_ListCtl->GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES;
    m_ListCtl->SetExtendedStyle(dwOldBits);

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_OK_YELLOW);
    idResources.push_back(IDI_ICON_LAGER_DEFEKT);
    idResources.push_back(IDI_ICON2);
    idResources.push_back(IDI_ICON_PRODQUOTA);
    idResources.push_back(IDI_ICON_BTM);
    idResources.push_back(IDI_ICON_KUEHL);
    idResources.push_back(IDI_ICON_KUEHL_U8);
    idResources.push_back(IDI_ICON_K20);
    idResources.push_back(IDI_ICON_DE_BESORGER);
    CListCtrlHelper::CreateAndSetImageList(*m_ListCtl, m_ImageSmall, idResources);

    AllgSetColumnWidthUser(*m_ListCtl, "CDInfAnzAuft", KEY_PATH, COL_ANZ_LIST);

    if (!AeGetApp()->IsNewCallback())
    {
        GetDlgItem(IDC_BUTTON_AUF_CALLBACK)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_AUF_CALLBACK)->EnableWindow(FALSE);
    }
    if (AeGetApp()->m_ProCenter.IsHiPathLogon())
    {
        GetDlgItem(IDC_BUTTON_CALL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_CALL)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANRUFEN));
    }

    if (AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_WERT_NETTO)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_WERT_NETTO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NETTOWERT)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NETTOWERT)->ShowWindow(SW_SHOW);
    }

    if (AeGetApp()->IsCMI())
    {
        GetDlgItem(IDC_BUTTON_AUF_NEU)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_AUF_NEU)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_AUF_NEU_ALLE)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_AUF_NEU_ALLE)->ShowWindow(SW_SHOW);
    }

    AusgKopf();

    //Einlesen Positionen in verkettete Liste class list
    ReadPos();

    //Listbox fuellen
    AusgPos();

    //Entscheidung ob Kopf- und Fußzeilen
    IfKopfOrFussZln();

    if (AeGetApp()->IsBG())
    {
        if (AeGetApp()->IsBG())
        {
            CDRIVER driver;
            GetDlgItem(IDC_STATIC_DRIVER)->ShowWindow(SW_SHOW);
            ppString name;
            driver.SetKdauftragnr(m_AuftrNr);
            if (m_Datum == 0)
            {
                if (!driver.SelAct())
                {
                    driver.GetDrivername(name);
                }
            }
            else
            {
                driver.SetDatum(m_Datum);
                if (!driver.SelOld())
                {
                    driver.GetDrivername(name);
                }
            }
            GetDlgItem(IDC_STATIC_DRIVER)->SetWindowText(name);
            CCSTREBATETYPE rtyp;
            rtyp.SetVertriebszentrumnr(m_VzNr);
            rtyp.SetKundennr(m_KndNr);
            rtyp.SelRebateType();
            m_sFVRabkonto = rtyp.GetRebatemethfreesale();
            m_sKKRabkonto = rtyp.GetRebatemethhealthf();

        }

        if (AA == "RO")
        {
            GetDlgItem(IDC_BUTTON_VB_BUCH)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_VB_BUCH)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_BUTTON_DEFBUCH)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_DEFBUCH)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_BUTTON_AUF_NEU)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_AUF_NEU)->ShowWindow(SW_HIDE);
        }
    }
    if (m_Datum == 0)
    {
        if (ZuGrund.GetAt(ZU_KREDITLIMIT) == '1')
        {
            if (GetAeUser().IsStornoCremaOrder())
            {
                if (Status == ORD_ZURUECKGESTELLT || Status == ORD_DAFUE_FEHLER)
                {
                    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->EnableWindow(TRUE);
                    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->ShowWindow(SW_SHOW);
                }
            }
            if (GetAeUser().Is2ndLevel())
            {
                if (Status == ORD_ZURUECKGESTELLT || Status == ORD_DAFUE_FEHLER)
                {
                    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->EnableWindow(TRUE);
                    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->ShowWindow(SW_SHOW);
                }
            }
        }
    }

    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

void CDOrderInformation1::IfKopfOrFussZln()
{
    int Fuss, Kopf;
    CAUFTEXTE auftexte;
    auftexte.s.BEMERKUNGSART = AUF_TEXT_KOPF_INFO;
    auftexte.s.FETCH_REL = 1;
    for (Kopf = 0;; Kopf++)
    {
        if (m_Datum == 0)
            auftexte.Server(AasrvSelKopfZlnAuf, PIPE_AE_SRV);
        else
            auftexte.Server(AaauftSel_alt_kopf);
        if (auftexte.rc != SRV_OK)
            break;
    }
    // Schliessen Cursor
    if (m_Datum != 0)
    {
        auftexte.s.FETCH_REL = 0;
        auftexte.Server(AaauftSel_alt_kopf);
    }
    auftexte.s.BEMERKUNGSART = AUF_TEXT_FUSS_INFO;
    auftexte.s.FETCH_REL = 1;
    for (Fuss = 0;; Fuss++)
    {
        if (m_Datum == 0)
            auftexte.Server(AasrvSelKopfZlnAuf, PIPE_AE_SRV);
        else
            auftexte.Server(AaauftSel_alt_kopf);
        if (auftexte.rc != SRV_OK)
            break;
    }
    // Schliessen Cursor
    if (m_Datum != 0)
    {
        auftexte.s.FETCH_REL = 0;
        auftexte.Server(AaauftSel_alt_kopf);
    }
    if (Kopf == 0 && Fuss == 0) GetDlgItem(IDC_BUTTON_KOPF_FUSS)->EnableWindow(FALSE);
}

void CDOrderInformation1::ReadPos()
{
    m_lAuf.clear();
    CAUFPOSBUCH aufposbuch;
    BeginWaitCursor();
    for (int i = 1;; i++)
    {
        aufposbuch.s.MENGE = 0; //nase wird demnächst im server korrekt versorgt
        aufposbuch.s.FILIALNR1 = 0; //vorformatieren auf 0
        if (m_Datum == 0) aufposbuch.Server(AasrvSelposInfAuf, PIPE_AE_SRV);
        else
        {
            aufposbuch.s.FETCH_REL = 1;
            aufposbuch.Server(AaauftSel_alt_pos);
        }
        if (aufposbuch.rc != SRV_OK)
        {
            if (m_Datum == 0) break;
            else
            {
                aufposbuch.s.FETCH_REL = 0;
                aufposbuch.Server(AaauftSel_alt_pos);
                break;
            }
        }
        if (AeGetApp()->IsBG())
        {
            double dTax;
            char cStd;
            AeGetApp()->GetTaxRates(aufposbuch.s.TAXLEVEL, cStd, dTax);
            aufposbuch.s.PREISFAKTUR = aufposbuch.s.PREISFAKTUR*(100 + dTax) / 100;
        }
        m_lAuf.insert(m_lAuf.end(), aufposbuch.s);
    }
    EndWaitCursor();
}

void CDOrderInformation1::AusgPos()
{
    CString cstr;
    CString PQ;
    CString cpreis;
    CString cpromonr;
    CString cpromoname;
    CString cpromotyp;
    ppString spromoname;

    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;
    //

    char str[81];
    int VSEStatus;      //VSE-Fehlerstatus
    long lRest;
    long testxx;
    CCHECKIMPORTARTICLE checkimport;
    CPROMOANZ promoanz;
    CVERBUNDMOEGL vbm;
    CAUFALTLAGORT ibt;
    CARTPSYCHO psy;
    CARTIKELQUOTA quota;
    BeginWaitCursor();
    m_bVbKunde = IsVbKunde();
    m_ListCtl->DeleteAllItems();
    for (vector<AUFPOSBUCH>::iterator it = m_lAuf.begin(); it != m_lAuf.end(); it++)
    {
        if (m_CBNurDef.GetCheck() != FALSE)
        {
            if (it->ARTIKEL_NR != 0 &&
                (it->MENGEABGEBUCHT + it->MENGENATRA) >= it->MENGEBESTELLT) continue;
        }
        int pos = m_ListCtl->GetItemCount();

        // wichtig für Sort
        lvi.lParam = (LPARAM)pos;

        VSEStatus = 0;
        if (it->SENDESTATUS == 2)   // Defekte von VSE
        {
            VSEStatus = 1;
        }
        else if (it->SENDESTATUS == 7)  // Defekte von VSE
        {
            VSEStatus = 2;
        }
        // wichtig für Sort
        if (m_ListCtl->InsertItem(&lvi) == -1)
            return;
        if (it->SENDESTATUS == 2)   // Defekte von VSE
        {
            VSEStatus = 1;
        }
        else if (it->SENDESTATUS == 7)  // Defekte von VSE
        {
            VSEStatus = 2;
        }
        CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AMGE, VSEStatus);

        m_ListCtl->SetItemText(lvi.iItem, COL_AMGE, _ltoa(it->MENGEBESTELLT, str, 10));
        m_ListCtl->SetItemText(lvi.iItem, COL_BMGE, _ltoa(it->MENGEGELIEFERT + it->MENGE, str, 10));
        m_ListCtl->SetItemText(lvi.iItem, COL_NRME, _ltoa(it->MENGENATRA, str, 10));
        m_ListCtl->SetItemText(lvi.iItem, COL_VERBME, _ltoa(it->MENGE, str, 10)); //Verbundmenge
        if (it->KZAUFGENOMMEN[0] == '1') m_ListCtl->SetItemText(lvi.iItem, COL_UMGESCHL, CResString::ex().getStrTblText(AETXT_KZ_JA));
        AllgEntfSpaces(it->EINHEIT);
        m_ListCtl->SetItemText(lvi.iItem, COL_EINHEIT, it->EINHEIT);
        if (it->STATUS == ITEM_STAT_ZUGESAGT)       cstr = "ZU";
        else if (it->STATUS == ITEM_STAT_DISPO)         cstr = "DI";
        else if (it->STATUS == ITEM_STAT_NACHLIEFERN)   cstr = "NL";
        else if (it->KZINFOTEXT[0] == '1')              cstr = "IT";
        else                                            cstr = "";
        m_ListCtl->SetItemText(lvi.iItem, COL_FU, cstr);
        if (AeGetApp()->IsBG())
        {
            AllgEntfSpaces(it->ARTIKEL_LANGNAME);
            m_ListCtl->SetItemText(lvi.iItem, COL_ARTIKELNAME, it->ARTIKEL_LANGNAME);
        }
        else
        {
            AllgEntfSpaces(it->ARTIKEL_NAME);
            m_ListCtl->SetItemText(lvi.iItem, COL_ARTIKELNAME, it->ARTIKEL_NAME);
        }
        bool bImport = false;
        if (it->ARTIKEL_NR > 0 && AeGetApp()->IsAT())
        {
            checkimport.SetArtikel_nr(it->ARTIKEL_NR);
            if (!checkimport.SelImport())
            {
                bImport = true;
                CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_ARTIKELNAME, LIEFBER_DEGETTER);
            }
        }
        if (bImport)
        {
        }
        else if (AllgBitleisteN((Bitleiste)it->ETARTKLASSE1, 6))  // opiat
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_ARTIKELNAME, LIEFBER_BTM);
        }
        else if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER1, 10))  // Kuehlkette
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_ARTIKELNAME, LIEFBER_KUEHL);
        }
        else if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER1, 8))
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_ARTIKELNAME, LIEFBER_KUEHL_U8);
        }
        else if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER1, 9) &&
            AeGetApp()->IsCool20())  // Kuehl unter 20 Grad
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_ARTIKELNAME, LIEFBER_COOL20);
        }
        AllgEntfSpaces(it->DARREICHFORM);
        m_ListCtl->SetItemText(lvi.iItem, COL_DAF, it->DARREICHFORM);
        m_ListCtl->SetItemText(lvi.iItem, COL_PA, it->POSART);
        m_ListCtl->SetItemText(lvi.iItem, COL_PNR, _ltoa(it->POSNR, str, 10));
        testxx = it->ETPOSSCHALTER2;
        if (AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 10)     // gesplittet in anderen Auftrag
            || (AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 7)))  // Verzoegert (z.B. Kuehlartikel)
        {
            m_ListCtl->SetItemText(lvi.iItem, COL_ETPOS, "1");
        }

        if (it->ARTIKEL_NR != 0)
        {
            psy.SetArtikel_nr(it->ARTIKEL_NR);
            if (!psy.SelArticle())
            {
                if (AllgBitleisteN((Bitleiste)psy.GetEtartklasse1(), 6))  // opiat
                {
                    m_ListCtl->SetItemText(lvi.iItem, COL_CONT, CResString::ex().getStrTblText(AETXT_BTM));
                }
                else if (psy.GetKzpsychostoffe() == 'J'
                    || psy.GetKzpsychostoffe() == 'P'
                    || psy.GetKzpsychostoffe() == 'T')  // psychotrop
                {
                    m_ListCtl->SetItemText(lvi.iItem, COL_CONT, CResString::ex().getStrTblText(AETXT_PTS));
                }
                else if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER2, 6))  //Containerartikel nase
                {
                    m_ListCtl->SetItemText(lvi.iItem, COL_CONT, CResString::ex().getStrTblText(AETXT_CONT));
                }
                else
                {
                    m_ListCtl->SetItemText(lvi.iItem, COL_CONT, _ltoa((long)(it->LAGERBEREICHNR), str, 10));
                }
            }
        }
        else
        {
            if (AllgBitleisteN((Bitleiste)it->ETARTSCHALTER2, 6))   //Containerartikel nase
                m_ListCtl->SetItemText(lvi.iItem, COL_CONT, CResString::ex().getStrTblText(AETXT_CONT));
            else
                m_ListCtl->SetItemText(lvi.iItem, COL_CONT, _ltoa((long)(it->LAGERBEREICHNR), str, 10));
        }

        if (it->ARTIKEL_NR == -1)
        {
            m_ListCtl->SetItemText(lvi.iItem, COL_PZN, " ");
        }
        else
        {
            if (it->ARTICLE_CODE[0] == ' ')     // wenn articlecode noch nicht versorgt, dann artikelnr
            {
                m_ListCtl->SetItemText(lvi.iItem, COL_ARTICLECODE, _ltoa((it->ARTIKEL_NR), str, 10));
            }
            else
            {
                AllgEntfSpaces(it->ARTICLE_CODE);
                m_ListCtl->SetItemText(lvi.iItem, COL_ARTICLECODE, it->ARTICLE_CODE);
            }
            m_ListCtl->SetItemText(lvi.iItem, COL_PZN, _ltoa((it->ARTIKEL_NR), str, 10));
        }
        cstr = "";
        PQ = "";
        if (it->ARTIKEL_NR > 0 && strlen(it->ARTIKEL_NAME) > 0)
        {
            GetArtKennz(it->ARTIKEL_NR, cstr, PQ);
        }
        m_ListCtl->SetItemText(lvi.iItem, COL_KENNZEICHEN, cstr);
        m_ListCtl->SetItemText(lvi.iItem, COL_PRODQUOTA, PQ);
        if ((atoi(PQ)) == 1)
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, lvi.iItem, COL_BMGE, PROD_QUOTA);
        }

        if (AeGetApp()->IsBG())
        {
            cpreis.Format("%0.2f", it->PREISFAKTUR);
        }
        else
        {
            cpreis.Format("%0.2f", it->PREISEKAPO);
        }
        m_ListCtl->SetItemText(lvi.iItem, COL_PREIS, cpreis);
        cpreis.Format("%0.2f", it->PREISEKAPOFREE);
        m_ListCtl->SetItemText(lvi.iItem, COL_PREISFREE, cpreis);
        cpreis.Format("%0.2f", it->PREISFAKTUR);
        m_ListCtl->SetItemText(lvi.iItem, COL_PREISFAKTUR, cpreis);

        AllgEntfSpaces(it->BEMERKUNG);
        m_ListCtl->SetItemText(lvi.iItem, COL_BEMERK, it->BEMERKUNG);
        cstr.Format("%.2lf", it->PREISVKAPO);
        m_ListCtl->SetItemText(lvi.iItem, COL_AVP, cstr);
        if (it->DISCOUNTVALPCTMAN > 0.00)
        {
            cstr.Format("%.2lf", it->DISCOUNTVALPCTMAN);
            m_ListCtl->SetItemText(lvi.iItem, COL_PCTMAN, cstr);
        }
        else
        {
            cstr.Format("%.2lf", it->DISCOUNTVALUEPCT);
        }
        m_ListCtl->SetItemText(lvi.iItem, COL_PCT, cstr);
        cstr.Format("%d", it->PREIS_TYP);
        m_ListCtl->SetItemText(lvi.iItem, COL_PREISTYP, cstr);

        if (it->PROMOTION_NO > 0)
        {
            if (it->PROMOTYP == 1)
            {
                m_ListCtl->setItemColor(lvi.iItem, RGB(0, 0, 0), RGB(255, 85, 0));
            }
            else if (it->PROMOTYP == 2)
            {
                m_ListCtl->setItemColor(lvi.iItem, RGB(0, 0, 0), RGB(255, 00, 0));
            }
            else
            {
                m_ListCtl->setItemColor(lvi.iItem, RGB(0, 0, 0), RGB(255, 80, 80));
            }
            cpromotyp.Format("%d", it->PROMOTYP);
            cpromonr.Format("%d", it->PROMOTION_NO);
            promoanz.SetPromotion_no(it->PROMOTION_NO);
            if (!promoanz.SelPromo())
                cpromoname = promoanz.GetName(spromoname);
            else
                cpromoname.Empty();
        }
        else
        {
            cpromotyp.Empty();
            cpromonr.Empty();
            cpromoname.Empty();
        }
        m_ListCtl->SetItemText(lvi.iItem, COL_PROMONO, cpromonr);
        m_ListCtl->SetItemText(lvi.iItem, COL_PROMONAME, cpromoname);
        m_ListCtl->SetItemText(lvi.iItem, COL_PROMOTYP, cpromotyp);

        if (it->FILIALNR1)
        {
            if (it->IBTTYPEID > 0)  //NLevel-Verbund
            {
                if (it->IBTTYPEID == 1)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_NATIONAL));
                }
                else if (it->IBTTYPEID == 2)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_REGIONAL));
                }
                else if (it->IBTTYPEID == 3)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_LOKAL));
                }
                else // if (it->IBTTYPEID == 4)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_SPEZIAL));
                }
            }
            else
            {
                if (it->IBTTYPE == 0)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_LOKAL));
                }
                else if (it->IBTTYPE == 1)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_PRIVATSORTIMENT));
                }
                else if (it->IBTTYPE == 2)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_VETO));
                }
                else if (it->IBTTYPE == 3)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_REGIONAL));
                }
                else if (it->IBTTYPE == 4)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_TAGVERBUND));
                }
                else // if (it->IBTTYPE == 5)
                {
                    m_ListCtl->SetItemText(pos, COL_VBTYP, CResString::ex().getStrTblText(AETXT_NATIONAL));
                }
            }

            AddDeliveryDateTimeToList(pos, it);

            m_ListCtl->SetItemText(lvi.iItem, COL_VERBUNDFIL, _ltoa((it->FILIALNR1), str, 10));
        }
        else
        {
            m_ListCtl->SetItemText(lvi.iItem, COL_VERBUNDFIL, "");

            if (   (   AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 10)    // gesplittet in anderen Auftrag
                    || AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 7) )   // Verzoegert (z.B. Kuehlartikel)
                && ((m_lTour != atol(it->TOURID)) || (it->DELIVERYDATE > m_lDatumAuftrag)) )  // Bei abweichender Tour oder abweichendem Datum Lieferzeit anzeigen
            {
                AddDeliveryDateTimeToList(pos, it);
            }
        }
        m_ListCtl->SetItemText(lvi.iItem, COL_VERBUND, "");
        if (it->ARTIKEL_NR != 0 &&
            (it->MENGEABGEBUCHT + it->MENGENATRA) < it->MENGEBESTELLT &&
            !AllgBitleisteN((Bitleiste)it->ETPOSSCHALTER2, 10) &&   //bei gesplitteten Positionen nicht Anzeigen Verbund möglich
            m_bVbKunde)
        {
            lRest = 1;
            quota.SetBranchno(m_VzNr);
            quota.SetArticleno(it->ARTIKEL_NR);
            quota.SetCustomerno(m_KndNr);
            short sQuotaInheritance = CharToShort(AeGetApp()->QuotaInheritance());
            quota.SetQuotainheritance(sQuotaInheritance);
            if (!quota.CheckQuota())
            {
                lRest = quota.GetQuota();
            }
            quota.CloseCursor();
            if (lRest > 0)
            {
                if (AeGetApp()->IsNLevelIBTCst())
                {
                    ibt.s.ARTIKEL_NR = it->ARTIKEL_NR;
                    ibt.s.FILIALNR = m_VzNr;
                    ibt.Server(AasrvCheckIBTStockLevel);
                    if (ibt.rc == SRV_OK)
                    {
                        m_ListCtl->SetItemText(lvi.iItem, COL_VERBUND, CResString::ex().getStrTblText(AETXT_KZ_JA));
                        m_ListCtl->SetItemText(lvi.iItem, COL_FILI, _itoa(ibt.s.FILIALNR, str, 10));
                    }
                }
                else
                {
                    vbm.s.ARTIKEL_NR = it->ARTIKEL_NR;
                    vbm.s.FILIALNR = m_VzNr;
                    vbm.SelVbBestandNeu();
                    if (vbm.rc == SRV_OK && vbm.s.BESTAND > 0)
                    {
                        m_ListCtl->SetItemText(lvi.iItem, COL_VERBUND, CResString::ex().getStrTblText(AETXT_KZ_JA));
                        m_ListCtl->SetItemText(lvi.iItem, COL_FILI, _itoa(vbm.s.FILIALNR, str, 10));
                    }
                }
                if (AeGetApp()->IsPrintCode())
                {
                    ppString text;
                    CCODEBLOCAGEINFO code;
                    code.SetFilialnr(m_VzNr);
                    code.SetArtikel_nr(it->ARTIKEL_NR);
                    if (!code.SelText())
                    {
                        CString cVolltext;
                        CString cBemtext;
                        code.GetPrintcode(text);
                        cBemtext = m_ListCtl->GetItemText(lvi.iItem, COL_BEMERK);
                        cVolltext = text;
                        cVolltext += " / ";
                        cVolltext += cBemtext;
                        m_ListCtl->SetItemText(lvi.iItem, COL_BEMERK, cVolltext);
                    }
                }
            }
        }
        // wichtig für Sort
        lvi.iItem++;
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(*m_ListCtl, 0);
    EndWaitCursor();
}

void CDOrderInformation1::AddDeliveryDateTimeToList(int pos, vector<AUFPOSBUCH>::iterator& it)
{
    if ((atol(it->TOURID) != 0) || (it->DELIVERYDATE != 0))
    {
        CString str;
        str = DDMMYYYYStringFromDateLong(it->DELIVERYDATE);
        m_ListCtl->SetItemText(pos, COL_DELIVERYDATE, str);
        str = HHmmStringFromShortTimeLong(it->DELIVERYTIME);
        m_ListCtl->SetItemText(pos, COL_DELIVERYTIME, str);
    }
}

void CDOrderInformation1::OnButtonKopfFuss()
{
    CDAufTxt dlgAufTxt;
    dlgAufTxt.m_ldatum = m_Datum;
    dlgAufTxt.m_bInfoOrder = TRUE;
    dlgAufTxt.DoModal();
}

void CDOrderInformation1::OnButtonEreignis()
{
    CDAuftrEreign dlgAuftrEreign;
    dlgAuftrEreign.m_AuftragsNr = m_AuftrNr;
    dlgAuftrEreign.m_Datum = m_Datum;
    dlgAuftrEreign.DoModal();
}

void CDOrderInformation1::OnButtonDruck()
{
    char underline[111];
    int pos, maxpos;
    CString liste;
    CString Verbund;
    CDruckAuftrag druckAuftrag;
    memset(underline, '-', 110);
    underline[110] = '\0';

    liste.Format("%-15.15s %07.7s % 27.27s %-16.16s %-14.14s %-8.8s %-10.10s %-2.2s",
        CResString::ex().getStrTblText(AETXT_KUNDEN_NR).GetString(), IDF_Nr.GetString(),
        CResString::ex().getStrTblText(AETXT_TELEFON).GetString(), Tel.GetString(),
        CResString::ex().getStrTblText(AETXT_ZEILEN).GetString(), Zln.GetString(),
        CResString::ex().getStrTblText(AETXT_A_ART).GetString(), AA.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-26.26s % 8.8s %-16.16s %-14.14s %-8.8s %-10.10s %-2.2s",
        CResString::ex().getStrTblText(AETXT_INHABER).GetString(), Inhaber.GetString(),
        CResString::ex().getStrTblText(AETXT_KURZWAHL).GetString(), Tel_KW.GetString(),
        CResString::ex().getStrTblText(AETXT_AUF_WERT).GetString(), AW.GetString(),
        CResString::ex().getStrTblText(AETXT_KOM_ART).GetString(), KA.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-26.26s % 4.4s-%-3.3s %-16.16s %-14.14s %-8.8s %-10.10s %-2.2s",
        CResString::ex().getStrTblText(AETXT_APOTHEKENNAME).GetString(), Apotheke.GetString(),
        CResString::ex().getStrTblText(AETXT_ZEILEN_DAFUE).GetString(), CResString::ex().getStrTblText(AETXT_ART).GetString(), Dafue_Typ.GetString(),
        CResString::ex().getStrTblText(AETXT_LIF_WERT).GetString(), Lif_Wert.GetString(),
        CResString::ex().getStrTblText(AETXT_BUCH_ART).GetString(), BA.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-8.8s %-6.6s %-26.26s % 8.8s %-16.16s %-14.14s %-8.8s %-4s: %-10.10s",
        CResString::ex().getStrTblText(AETXT_PLZ_ORT).GetString(), PLZ.GetString(), Ort.GetString(),
        CResString::ex().getStrTblText(AETXT_AUF_NR).GetString(), Auftr_Nr.GetString(),
        CResString::ex().getStrTblText(AETXT_D_ZEILEN_WERT).GetString(), Dzw.GetString(),
        CResString::ex().getStrTblText(AETXT_TOUR).GetString(), Tour.GetString());
    druckAuftrag.AddKopfZeile(liste);

    if (m_LAuftNr != 0)
    {
        liste.Format("                                           %-8.8s %-16.16s %-14.14s %-8.8s %-11.11s %ld",
            CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(), Vsenr.GetString(),
            CResString::ex().getStrTblText(AETXT_RECHNR).GetString(), Rech_Nr.GetString(),
            Lauft_Nr.GetString(), m_LAuftNr);
    }
    else
    {
        liste.Format("                                           %-8.8s %-16.16s %-14.14s %-8.8s",
            CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(), Vsenr.GetString(),
            CResString::ex().getStrTblText(AETXT_RECHNR).GetString(), Rech_Nr.GetString());
    }
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-52.52s",
        CResString::ex().getStrTblText(AETXT_PHONIE_INFO).GetString(), Kndtext.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-52.52s",
        CResString::ex().getStrTblText(IDS_BEMERK).GetString(), Bemerk.GetString());
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    liste.Format("% 4.4s % 4.4s % 4.4s % 4.4s %-9.9s % 4.4s %-24.24s % 4.4s % 2.2s % 4.4s %13.13s %-9.9s VB %-60.60s",
        CResString::ex().getStrTblText(AETXT_AMGE).GetString(),
        CResString::ex().getStrTblText(AETXT_BMGE).GetString(),
        CResString::ex().getStrTblText(AETXT_NRME).GetString(),
        CResString::ex().getStrTblText(AETXT_VERBME).GetString(),
        CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
        CResString::ex().getStrTblText(AETXT_FU).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTIKELNAME).GetString(),
        CResString::ex().getStrTblText(AETXT_DAF).GetString(),
        CResString::ex().getStrTblText(AETXT_PA).GetString(),
        CResString::ex().getStrTblText(AETXT_PNR).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTICLE_CODE).GetString(),
        CResString::ex().getStrTblText(AETXT_PREIS).GetString(),
        CResString::ex().getStrTblText(IDS_BEMERK).GetString());
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    liste += "                                        ";
    liste += CResString::ex().getStrTblText(AETXT_DATUM);
    liste += ": ";
    liste += Datum;
    druckAuftrag.AddFussZeile(liste);
    maxpos = m_ListCtl->GetItemCount();
    for (pos = 0; pos<maxpos; pos++)
    {
        Verbund = m_ListCtl->GetItemText(pos, COL_VERBUND);
        if (Verbund.IsEmpty()) Verbund = m_ListCtl->GetItemText(pos, COL_VERBUNDFIL);
        liste.Format("% 4.4s % 4.4s % 4.4s % 4.4s %-9.9s % 4.4s %-24.24s % 4.4s % 2.2s % 4.4s %13.13s % 9.9s %-2.2s %-60.60s",
            m_ListCtl->GetItemText(pos, COL_AMGE).GetString(),
            m_ListCtl->GetItemText(pos, COL_BMGE).GetString(),
            m_ListCtl->GetItemText(pos, COL_NRME).GetString(),
            m_ListCtl->GetItemText(pos, COL_VERBME).GetString(),
            m_ListCtl->GetItemText(pos, COL_EINHEIT).GetString(),
            m_ListCtl->GetItemText(pos, COL_FU).GetString(),
            m_ListCtl->GetItemText(pos, COL_ARTIKELNAME).GetString(),
            m_ListCtl->GetItemText(pos, COL_DAF).GetString(),
            m_ListCtl->GetItemText(pos, COL_PA).GetString(),
            m_ListCtl->GetItemText(pos, COL_PNR).GetString(),
            m_ListCtl->GetItemText(pos, COL_ARTICLECODE).GetString(),
            m_ListCtl->GetItemText(pos, COL_PREIS).GetString(),
            Verbund.GetString(),
            m_ListCtl->GetItemText(pos, COL_BEMERK).GetString());
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(2);
    druckAuftrag.DelAllData();

}

void CDOrderInformation1::OnOK()
{
    CDArtInf dlgArtInf;
    long ArtNr = 0;
    int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString CStr;
        CStr = m_ListCtl->GetItemText(pos, COL_PZN);
        ArtNr = atol(CStr);
        if (ArtNr == 0)
        {
            CDAeAnzFrText dlgAeAnzFrText;
            CStr = m_ListCtl->GetItemText(pos, COL_PNR);
            dlgAeAnzFrText.m_posnr = atol(CStr);
            dlgAeAnzFrText.m_datum = m_Datum;
            dlgAeAnzFrText.m_auftragnr = m_AuftrNr;
            dlgAeAnzFrText.DoModal();
        }
        else
        {
            dlgArtInf.SetArtNr(ArtNr);
            dlgArtInf.SetKndNr(m_KndNr);
            dlgArtInf.DoModal();
        }
    }
}

void CDOrderInformation1::OnCheckNurDef()
{

    //Listbox neu fuellen je nach Schalter
    AusgPos();
}

void CDOrderInformation1::GetArtKennz(long artikelnr, CString &ArtKZ, CString &ProdQuota)
{
    //nase
    //ist noch einmal in aasrv.cpp definiert !!!!!!
    CString CStr;
    ArtKZ = "";
    CARTAESEL artaesel;
    artaesel.s.ARTIKEL_NR = artikelnr;
    artaesel.s.FILIALNR = AeGetApp()->FilialNrActual();
    artaesel.s.ETARTKLASSE1 = 65535;   //alles - select wird nur fuer KK-Code gebraucht
    if (AeGetApp()->IsPrintCode())
        artaesel.s.CODEBLOCAGE[0] = '1';
    else
        artaesel.s.CODEBLOCAGE[0] = '0';
    artaesel.Server(AatartAa_sel_artnr);

    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 0))   CStr += "9";        // Sekundaerbezeichner
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 1))   CStr += "E";        // Nachfolgeartikel
    if (artaesel.s.PRISOART[0] != '0')
    {
        if (artaesel.s.PRISOART[0] == '1')         CStr += "SL";
        else if (artaesel.s.PRISOART[0] == '2')    CStr += "SZ";
        else if (artaesel.s.PRISOART[0] == '3')    CStr += "SB";
    }
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 3))   CStr += "A";        // ausser Handel
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 4))   CStr += "AV";       // Auslaufartikel
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 13))  CStr += "G";        // nicht ueber Grosshandel
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 12))  CStr += "H";        // vom Hersteller nicht geliefert
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 11))  CStr += "L";        // vom Hersteller nicht lieferbar
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER1, 6))   CStr += "P";        // Netto
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER3, 7))   CStr += "N";        // Natra
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER4, 1))   CStr += "R";        // Reimport
    if (AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER4, 14))  CStr += "T";        // Nahrungsmittel gesperrt
    if (!AllgBitleisteN((Bitleiste)artaesel.s.ETARTSCHALTER2, 15)
        && artaesel.s.BESTAND == 0)
    {
        if (artaesel.s.WAFOTYP[0] > '0') CStr += "W";      // Artikel darf als NL erfasst werden
        CStr += "F";        // Artikel wird nicht gefuehrt
    }
    ArtKZ = CStr;
    ProdQuota.Format("%d", artaesel.s.PRODUSERQUOTA);
}

void CDOrderInformation1::OnButtonVbBuch()
{
    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.m_pl.clear();
    for (int pos = 0; pos < m_ListCtl->GetItemCount(); pos++)
    {
        if (m_ListCtl->GetItemText(pos, COL_VERBUND) == CResString::ex().getStrTblText(AETXT_KZ_JA))
        {
            InitVbArtikel(dlgVbBuchen.m_pl, pos);
        }
    }
    InitVbBuchenDlg(dlgVbBuchen);
    if (dlgVbBuchen.DoModal() == IDOK)
        CTabPageMultiLang::OnOK();
}

void CDOrderInformation1::InitVbArtikel(vector<CDVbBuchen::VbArtikel>& destlist, int pos, bool bUseAmgeAsBmge /*=false*/)
{
    struct CDVbBuchen::VbArtikel VB;
    VB.MengeBestellt = m_ListCtl->GetItemText(pos, COL_AMGE);
    VB.BestMenge = m_ListCtl->GetItemText(pos, bUseAmgeAsBmge ? COL_AMGE : COL_BMGE); // bUseAmgeAsBmge==true: erneuter Versuch der Menge
    VB.NatraMenge = m_ListCtl->GetItemText(pos, COL_NRME);
    VB.VerbMenge = m_ListCtl->GetItemText(pos, COL_VERBME);
    VB.ArtEinh = m_ListCtl->GetItemText(pos, COL_EINHEIT);
    VB.ArtName = m_ListCtl->GetItemText(pos, COL_ARTIKELNAME);
    VB.ArtNr = m_ListCtl->GetItemText(pos, COL_PZN);
    VB.VerbFiliale = m_ListCtl->GetItemText(pos, COL_FILI);
    VB.Darreichform = m_ListCtl->GetItemText(pos, COL_DAF);
    VB.Bemerkung = m_ListCtl->GetItemText(pos, COL_BEMERK);
    VB.Kennzeichen = m_ListCtl->GetItemText(pos, COL_KENNZEICHEN);
    VB.LagerBereich = m_ListCtl->GetItemText(pos, COL_CONT);
    VB.Preistyp = m_ListCtl->GetItemText(pos, COL_PREISTYP);
    VB.Prodquota = m_ListCtl->GetItemText(pos, COL_PRODQUOTA);
    VB.PreisFree = m_ListCtl->GetItemText(pos, COL_PREISFREE);
    VB.PctMan = m_ListCtl->GetItemText(pos, COL_PCTMAN);
    destlist.insert(destlist.end(), VB);
}

void CDOrderInformation1::InitVbBuchenDlg(CDVbBuchen& dlgVbBuchen)
{
    dlgVbBuchen.m_lKndNr = m_KndNr;
    dlgVbBuchen.m_IdfNr = m_IdfNr;
    dlgVbBuchen.m_VzNr = m_VzNr;
    dlgVbBuchen.m_bVersorgt = true;
    dlgVbBuchen.m_TenderNo = m_TenderNo;
    dlgVbBuchen.m_cAufArt = AA;

    CKNDSCHALTER kndschalter;
    kndschalter.s.IDFNR = m_IdfNr;
    kndschalter.s.KUNDENNR = m_KndNr;
    kndschalter.s.VERTRIEBSZENTRUMNR = m_VzNr;
    kndschalter.Server(AakundeSel_kndschalter);

    dlgVbBuchen.m_bKndMussKopfBem = kndschalter.s.SKDMUSSKOPF[0] == '1' ? true : false;
}

void CDOrderInformation1::OnButtonDefbuch()
{
    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.m_pl.clear();
    for (int pos = 0; pos < m_ListCtl->GetItemCount(); pos++)
    {
        if (   (atoi(m_ListCtl->GetItemText(pos, COL_BMGE)) < atoi(m_ListCtl->GetItemText(pos, 0)))
            && (atoi(m_ListCtl->GetItemText(pos, COL_ETPOS)) != 1) )
        {
            InitVbArtikel(dlgVbBuchen.m_pl, pos);
        }
    }
    InitVbBuchenDlg(dlgVbBuchen);
    dlgVbBuchen.m_ifunktion = 1;
    if (dlgVbBuchen.DoModal() == IDOK)
        CTabPageMultiLang::OnOK();
}

void CDOrderInformation1::OnButtonSeralog()
{
    CDSeralog dlgSeralog;
    dlgSeralog.m_CIdf.Format("%ld", m_IdfNr);
    dlgSeralog.m_CDatum = Datum;
    dlgSeralog.m_CDatum.Remove('.');
    CAUFEREIG aufereig;
    CString CStr;
    aufereig.s.KDAUFTRAGNR = m_LAuftNr;
    aufereig.s.DATUM = m_Datum;
    aufereig.s.FETCH_REL = 1;              //normaler Fetch
    aufereig.Server(AaauftAusg_auft_ereig);
    if (aufereig.rc == SRV_OK)
    {
        if (aufereig.s.ZEIT > 23999999)
            aufereig.s.ZEIT /= 100000;
        else if (aufereig.s.ZEIT > 239999)
            aufereig.s.ZEIT /= 10000;
        long lSerazeit = aufereig.s.ZEIT - 1;
        if (lSerazeit < 0)
            lSerazeit = 0;
        else if ((lSerazeit % 100) > 59)
        {
            lSerazeit = lSerazeit - 40;
        }
        dlgSeralog.m_CZeit.Format("%04d", lSerazeit);
    }
    aufereig.s.FETCH_REL = 0;      //close Cursor
    aufereig.s.DATUM = m_Datum;
    aufereig.Server(AaauftAusg_auft_ereig);
    dlgSeralog.m_ShowImmediately = 1;
    dlgSeralog.DoModal();
}

void CDOrderInformation1::OnButtonAufNeu()
{
    int ipro = 0;
    if (AeGetApp()->IsRS() && (AA == "PF"))
    {
        if (m_Datum == 0 && !m_bSelProforma)
        {
            CPROLINKACT proact;
            proact.SetKdauftragnr(atol(Auftr_Nr));
            if (!proact.SelProLink())
                ipro = 1;
        }
        else
        {
            CPROLINK pro;
            pro.SetKdauftragnr(atol(Auftr_Nr));
            pro.SetDatum(m_Datum);
            if (!pro.SelProLink())
                ipro = 1;
        }
    }
    if (ipro == 1)
    {
        if (MsgBoxYesNo(AETXT_PRO_DONE, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDNO)
        {
            return;
        }
    }

    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.m_pl.clear();
    for (int pos = 0; pos < m_ListCtl->GetItemCount(); pos++)
    {
        if (atol(m_ListCtl->GetItemText(pos, COL_BMGE)) == 0) continue;
        InitVbArtikel(dlgVbBuchen.m_pl, pos);
    }
    InitVbBuchenDlg(dlgVbBuchen);
    dlgVbBuchen.m_ifunktion = 2;

    if (AA == "PF")
    {
        AeGetApp()->ProAufnr = atol(Auftr_Nr);
        AeGetApp()->ProDatum = (m_Datum == 0) ? m_ActDatum : m_Datum;

        AeGetApp()->ProInvoiceno = Rech_Nr;
    }

    if (dlgVbBuchen.DoModal() == IDOK)
    {
        CTabPageMultiLang::OnOK();
    }
    else
    {
        AeGetApp()->ProAufnr = 0;
        AeGetApp()->ProDatum = 0;
        AeGetApp()->ProInvoiceno = "";
    }
}

HBRUSH CDOrderInformation1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CTabPageMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == IDC_EDIT_FV_BRUTTO)
    {
        if (m_sFVRabkonto)
            pDC->SetTextColor(RGB(0, 0, 200));
        else
            pDC->SetTextColor(RGB(0, 0, 0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_FV_NETTO)
    {
        if (!m_sFVRabkonto)
            pDC->SetTextColor(RGB(0, 0, 200));
        else
            pDC->SetTextColor(RGB(0, 0, 0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_KK_BRUTTO)
    {
        if (m_sKKRabkonto)
            pDC->SetTextColor(RGB(0, 0, 200));
        else
            pDC->SetTextColor(RGB(0, 0, 0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_EDIT_KK_NETTO)
    {
        if (!m_sKKRabkonto)
            pDC->SetTextColor(RGB(0, 0, 200));
        else
            pDC->SetTextColor(RGB(0, 0, 0));
    }
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_SPERRE)
    {
        pDC->SetTextColor(RGB(255, 0, 0));
    }
    return hbr;
}

BOOL CDOrderInformation1::DestroyWindow()
{
    AllgWriteColumnWidthUser(*m_ListCtl, "CDInfAnzAuft", KEY_PATH, COL_ANZ_LIST);

    return CTabPageMultiLang::DestroyWindow();
}

// CompareListe ist eine stand alone Funktion
/////////////////////////////////////////////////////////////////////////////
// CompareListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
/////////////////////////////////////////////////////////////////////////////
int CALLBACK CompareOrderInfoListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    if (s->GetAt(lParam1) == s->GetAt(lParam2)) return 0;
    else if (s->GetAt(lParam1) > s->GetAt(lParam2)) return 1;
    else return -1;
}

int CALLBACK CompareOrderInfoListeDouble(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    double feld1, feld2;
    feld1 = atof(s->GetAt(lParam1));
    feld2 = atof(s->GetAt(lParam2));
    if (feld1 == feld2) return 0;
    else if (feld1 > feld2) return 1;
    else return -1;
}

int CALLBACK CompareOrderInfoListeLong(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    long feld1, feld2;
    feld1 = atol(s->GetAt(lParam1));
    feld2 = atol(s->GetAt(lParam2));
    if (feld1 == feld2) return 0;
    else if (feld1 > feld2) return 1;
    else return -1;
}

void CDOrderInformation1::OnLvnColumnclickListAuftrag(NMHDR *pNMHDR, LRESULT *pResult)
{
    int col;
    int max;
    int index;
    //Wegen Sort
    LV_ITEM lvi;
    //
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    col = pNMListView->iSubItem;
    max = m_ListCtl->GetItemCount();
    CStringArray s;
    s.SetSize(max);
    for (index = 0; index<max; index++)
    {
        //StringArray an der ursprünglichen Position setzen
        lvi.iItem = index;
        lvi.mask = LVIF_PARAM;      //muss gesetzt sein, um lParam abzuholen
        m_ListCtl->GetItem(&lvi);   //Ursprungadresse steht in lParam
        s[(int)lvi.lParam] = m_ListCtl->GetItemText(index, col);
    }
    if (col == COL_PREIS || col == COL_AVP || col == COL_PCT)
        m_ListCtl->SortItems(CompareOrderInfoListeDouble, (LPARAM)&s);

    else if (col == COL_AMGE || col == COL_BMGE || col == COL_NRME
        || col == COL_VERBME || col == COL_PNR || col == COL_PZN)
        m_ListCtl->SortItems(CompareOrderInfoListeLong, (LPARAM)&s);

    else
        m_ListCtl->SortItems(CompareOrderInfoListe, (LPARAM)&s);

    for (index = 0; index<max; index++)
    {
        if (atoi(m_ListCtl->GetItemText(index, COL_PROMONO)) > 0)
        {
            if (atoi(m_ListCtl->GetItemText(index, COL_PROMOTYP)) == 1)
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 85, 0));
            }
            else if (atoi(m_ListCtl->GetItemText(index, COL_PROMOTYP)) == 2)
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 00, 0));
            }
            else
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 80, 80));
            }
        }
        else
        {
            m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 255, 255));
        }
    }
    *pResult = 0L;
}

void CDOrderInformation1::OnBnClickedButtonAufNeuAlle()
{
    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.m_pl.clear();
    for (int pos = 0; pos < m_ListCtl->GetItemCount(); pos++)
    {
        InitVbArtikel(dlgVbBuchen.m_pl, pos, true);
    }
    InitVbBuchenDlg(dlgVbBuchen);
    dlgVbBuchen.m_ifunktion = 2;
    if (dlgVbBuchen.DoModal() == IDOK)
    {
        CTabPageMultiLang::OnOK();
    }
    else
    {
        AeGetApp()->ProAufnr = 0;
        AeGetApp()->ProDatum = 0;
        AeGetApp()->ProInvoiceno = "";
    }
}

bool CDOrderInformation1::IsVbKunde()
{
    CKNDSCHALTER kndschalter;
    kndschalter.s.IDFNR = m_IdfNr;
    kndschalter.s.KUNDENNR = m_KndNr;
    kndschalter.s.VERTRIEBSZENTRUMNR = m_VzNr;
    kndschalter.Server(AakundeSel_kndschalter);
    if (kndschalter.s.SKDVERBUNDGANZ[0] == '1')
        return true;

    CZEITARTV zeitartv;
    sprintf(zeitartv.s.ZEITSCHLUESSEL, "%ld", m_KndNr);
    zeitartv.s.VERTRIEBSZENTRUMNR = m_VzNr;
    zeitartv.s.FETCH_REL = 1;  // normaler Fetch
    zeitartv.Server(AafilSel_verbund);
    bool bRes = (zeitartv.rc == SRV_OK) ? true : false;
    zeitartv.s.FETCH_REL = 0;  // Schliessen cursor
    zeitartv.Server(AafilSel_verbund);
    return bRes;
}

void CDOrderInformation1::OnBnClickedButtonAufCallback()
{
    CString Text;
    if (m_Datum > 0)
        Datum = DDMMYYYYStringFromDateLong(m_Datum);    //Fakturdatum

    Text.Format("%s %s\r\n%s %s\r\n%s %s\r\n%s %s\r\n%s %s\r\n",
        CResString::ex().getStrTblText(AETXT_DATUM).GetString(),
        Datum.GetString(),
        CResString::ex().getStrTblText(IDS_TOUR).GetString(),
        Tour.GetString(),
        CResString::ex().getStrTblText(AETXT_AUFTRZ).GetString(),
        Auftr_Nr.GetString(),
        CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(),
        Vsenr.GetString(),
        CResString::ex().getStrTblText(AETXT_RECHNUNG_NR).GetString(),
        Rech_Nr.GetString());
    CDNewCallback dlgNewCallback;
    dlgNewCallback.m_lIdf = m_IdfNr;
    dlgNewCallback.m_sBranchno = m_VzNr;
    dlgNewCallback.m_CGrund = Text;
    dlgNewCallback.DoModal();
}

void CDOrderInformation1::OnBnClickedButtonCremaStorno()
{
    CAUFTRAG auftrag;
    auftrag.s.KDAUFTRAGNR = m_AuftrNr;
    BeginWaitCursor();
    auftrag.Server(AasrvOpenorder, PIPE_AE_SRV);
    if (auftrag.rc < SRV_OK)
    {
        EndWaitCursor();
        return;
    }
    auftrag.Server(AasrvCancelorderDebtLimit, PIPE_AE_SRV);
    EndWaitCursor();
    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->ShowWindow(SW_HIDE);
}

void CDOrderInformation1::OnBnClickedButtonCremaClose()
{
    CAUFTRAG auftrag;
    auftrag.s.KDAUFTRAGNR = m_AuftrNr;
    BeginWaitCursor();
    auftrag.Server(AasrvOpenorder, PIPE_AE_SRV);
    if (auftrag.rc < SRV_OK)
    {
        EndWaitCursor();
        return;
    }
    auftrag.Server(AasrvCloseorderDebtLimit, PIPE_AE_SRV);
    EndWaitCursor();
    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CREMA_STORNO)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_CREMA_CLOSE)->ShowWindow(SW_HIDE);
}

BOOL CDOrderInformation1::OnSetActive()
{
    CListCtrlHelper::SetFocusSelectedFocusedVisible(*m_ListCtl, 0);

    return CTabPageMultiLang::OnSetActive();
}

void CDOrderInformation1::AusgKopf()
{
    GetDlgItem(IDC_STATIC_DATUM)->SetWindowText(Datum);
    GetDlgItem(IDC_STATIC_KNDTEXT)->SetWindowText(Kndtext);
    GetDlgItem(IDC_STATIC_AUFTRBEM)->SetWindowText(Bemerk);
    GetDlgItem(IDC_STATIC_ZLN)->SetWindowText(Zln);
    GetDlgItem(IDC_STATIC_AW)->SetWindowText(AW);
    GetDlgItem(IDC_STATIC_LIF_WERT)->SetWindowText(Lif_Wert);
    GetDlgItem(IDC_STATIC_DZW)->SetWindowText(Dzw);
    if (AeGetApp()->IsHR())
    {
        GetDlgItem(IDC_STATIC_NETTOWERT)->SetWindowText(Net_Wert);
    }
    if (!ValutaMon.IsEmpty())
    {
        GetDlgItem(IDC_STATIC_VALUTA)->SetWindowText(ValutaMon);
        GetDlgItem(IDC_STATIC_VALUTA_DATUM)->SetWindowText(ValutaDatum);
        GetDlgItem(IDC_STATIC_VALUTA)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_VALUTA_DATUM)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_VAL)->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_STATIC_VALUTA)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VALUTA_DATUM)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VAL)->ShowWindow(SW_HIDE);
    }
    GetDlgItem(IDC_STATIC_TOUR)->SetWindowText(Tour);

    if (AeGetApp()->IsDE())
    {
        GetDlgItem(IDC_STATIC_DELAY)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_DELAY)->EnableWindow(TRUE);
        //Tourverspätung
        CTOURDELAY tourdelay;
        char error_msg[81];
        int rc;
        ppString text;
        tourdelay.SetVertriebszentrumnr(m_VzNr);
        tourdelay.SetKundennr(m_KndNr);
        tourdelay.SetTourid(m_lTour);
        tourdelay.SetDatumkommi(m_Datum);
        tourdelay.SetKdauftragnr(m_AuftrNr);
        rc = ::ServerNr(PIPE_AE_SRV, AasrvSelTourDelay, (void *)&tourdelay.s, TOURDELAY_BES, TOURDELAY_ANZ, error_msg);
        if (rc < SRV_OK)
        {
            FehlerBehandlung(rc, error_msg);
            GetDlgItem(IDC_STATIC_DELAY)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_DELAY)->EnableWindow(FALSE);
        }
        if (rc == SRV_SQLNOTFOUND)    //Kein ETA-Eintrag
        {
            GetDlgItem(IDC_STATIC_DELAY)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_DELAY)->EnableWindow(FALSE);
        }
        else
        {
            CString cDelay;
            tourdelay.GetDelaytext(text);
            cDelay.Format(text, CResString::ex().getStrTblText(AETXT_DELAY_TEXT).GetString());
            GetDlgItem(IDC_STATIC_DELAY)->SetWindowTextA(cDelay);
        }
    }

    if (AeGetApp()->IsBG())
    {
        if (Paymenttype.GetAt(0) == 'C' ||
            (Paymenttype.GetAt(0) == ' ' &&
                Paymentdate.IsEmpty()))
        {
            GetDlgItem(IDC_STATIC_ZA)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_ZA)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZA)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZA)->SetWindowText(CResString::ex().getStrTblText(AETXT_CASH));
        }
        else if (Paymenttype.GetAt(0) == 'Z' ||
            (Paymenttype.GetAt(0) == ' ' &&
                !Paymentdate.IsEmpty()))
        {
            GetDlgItem(IDC_STATIC_ZA)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZA)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZA)->SetWindowText(CResString::ex().getStrTblText(AETXT_ZAHLUNG));
            GetDlgItem(IDC_STATIC_ZZ)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_ZZ)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZZ)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ZZ)->SetWindowText(Paymentdate);
        }

        GetDlgItem(IDC_STATIC_AUFWERTE)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_AUFWERTE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NETTO)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NETTO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_MWST)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_MWST)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_BRUTTO)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_BRUTTO)->ShowWindow(SW_SHOW);
        if (!WertNettoFV.IsEmpty())
        {
            GetDlgItem(IDC_STATIC_FV)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_FV)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_FV_NETTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_FV_TAX)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_FV_BRUTTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_FV_NETTO)->SetWindowText(WertNettoFV);
            GetDlgItem(IDC_EDIT_FV_TAX)->SetWindowText(WertTaxFV);
            GetDlgItem(IDC_EDIT_FV_BRUTTO)->SetWindowText(WertBruttoFV);
        }
        else
        {
            GetDlgItem(IDC_STATIC_FV)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_FV)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_FV_NETTO)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_FV_TAX)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_FV_BRUTTO)->ShowWindow(SW_HIDE);
        }
        if (!WertNettoKK.IsEmpty())
        {
            GetDlgItem(IDC_STATIC_KK)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_KK)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_KK_NETTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_KK_TAX)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_KK_BRUTTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_KK_NETTO)->SetWindowText(WertNettoKK);
            GetDlgItem(IDC_EDIT_KK_TAX)->SetWindowText(WertTaxKK);
            GetDlgItem(IDC_EDIT_KK_BRUTTO)->SetWindowText(WertBruttoKK);
        }
        else
        {
            GetDlgItem(IDC_STATIC_KK)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_KK)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_KK_NETTO)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_KK_TAX)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_KK_BRUTTO)->ShowWindow(SW_HIDE);
        }
        if (!WertNettoEH.IsEmpty())
        {
            GetDlgItem(IDC_STATIC_EH)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_EH)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_EH_NETTO)->SetWindowText(WertNettoEH);
            GetDlgItem(IDC_EDIT_EH_TAX)->SetWindowText(WertTaxEH);
            GetDlgItem(IDC_EDIT_EH_BRUTTO)->SetWindowText(WertBruttoEH);
        }
        else
        {
            GetDlgItem(IDC_STATIC_EH)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_EH)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_EH_NETTO)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_EH_TAX)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_EDIT_EH_BRUTTO)->ShowWindow(SW_HIDE);
        }
    }

    if (AeGetApp()->IsRS())
    {
        if (AA != "PF")
        {
            GetDlgItem(IDC_STATIC_PROFORMANR)->SetWindowText(PFDatum);
            GetDlgItem(IDC_STATIC_PROFORMA)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_PROFORMA)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_PROFORMANR)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_PROFORMANR)->ShowWindow(SW_SHOW);
        }
    }

    if (!m_cIVCnr.IsEmpty())
    {
        if (AeGetApp()->IsFR())
            GetDlgItem(IDC_STATIC_IVC)->SetWindowText(CResString::ex().getStrTblText(AETXT_ORGINVOICE));
        GetDlgItem(IDC_STATIC_IVCNR)->SetWindowText(m_cIVCnr);
        GetDlgItem(IDC_STATIC_IVC)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_IVC)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_IVCNR)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_IVCNR)->ShowWindow(SW_SHOW);
    }

    if (!OrderLabelCount.IsEmpty())
    {
        GetDlgItem(IDC_STATIC_ORDERLABELCOUNT)->SetWindowText(OrderLabelCount);
        GetDlgItem(IDC_STATIC_ORDERLABELCOUNT)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_ORDERLABCNT)->ShowWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_ORDERLABELCOUNT)->SetWindowText("");
        GetDlgItem(IDC_STATIC_ORDERLABELCOUNT)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_ORDERLABCNT)->ShowWindow(FALSE);
    }

    if (!OrderLabel.IsEmpty())
    {
        GetDlgItem(IDC_STATIC_LABEL_USED)->SetWindowText(OrderLabel);
        GetDlgItem(IDC_STATIC_LABEL_USED)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_LABEL)->ShowWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_LABEL_USED)->SetWindowText("");
        GetDlgItem(IDC_STATIC_LABEL_USED)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_LABEL)->ShowWindow(FALSE);
    }

}

void CDOrderInformation1::OnBnClickedButtonLief()
{
    CDWannauswahl dlgWannauswahl;
    dlgWannauswahl.m_lAuf = &m_lAuf;
    dlgWannauswahl.m_datum = m_Datum;
    dlgWannauswahl.m_Datum = Datum;
    dlgWannauswahl.m_IDF_Nr = IDF_Nr;
    dlgWannauswahl.m_Wertig = Wertig;
    dlgWannauswahl.m_Inhaber = Inhaber;
    dlgWannauswahl.m_Apotheke = Apotheke;
    dlgWannauswahl.m_PLZ = PLZ;
    dlgWannauswahl.m_Kndtext = Kndtext;
    dlgWannauswahl.m_Ort = Ort;
    dlgWannauswahl.m_Tel = Tel;
    dlgWannauswahl.m_Tel_KW = Tel_KW;
    dlgWannauswahl.m_Dafue_Typ = Dafue_Typ;
    dlgWannauswahl.m_Zln = Zln;
    dlgWannauswahl.m_AW = AW;
    dlgWannauswahl.m_Lif_Wert = Lif_Wert;
    dlgWannauswahl.m_Dzw = Dzw;
    dlgWannauswahl.m_AA = AA;
    dlgWannauswahl.m_BA = BA;
    dlgWannauswahl.m_KA = KA;
    dlgWannauswahl.m_Auftr_Nr = Auftr_Nr;
    dlgWannauswahl.m_Rech_Nr = Rech_Nr;
    dlgWannauswahl.m_Tour = Tour;
    dlgWannauswahl.m_LA_Nr = Lauft_Nr;
    dlgWannauswahl.m_Lauft_Nr = Lauft_Nr;
    dlgWannauswahl.m_Bemerk = Bemerk;
    dlgWannauswahl.m_Vsenr = Vsenr;
    dlgWannauswahl.DoModal();
}

void CDOrderInformation1::OnButtonCall()
{
    if (m_bCall)
    {
        AeGetApp()->m_ProCenter.DisconnectCall();
        GetDlgItem(IDC_BUTTON_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_ANRUFEN));
        m_bCall = false;
    }
    else
    {
        CString cTelNr = Tel;
        if (cTelNr.IsEmpty())
        {
            CDHPMakeCall dlgHPMakeCall;
            if (dlgHPMakeCall.DoModal() == IDOK)
            {
                cTelNr = dlgHPMakeCall.m_csTelNr;
            }
            else return;
        }
        cTelNr = '0' + cTelNr;
        cTelNr.TrimRight();
        AeGetApp()->m_ProCenter.MakeCall(cTelNr);
        GetDlgItem(IDC_BUTTON_CALL)->SetWindowText(CResString::ex().getStrTblText(AETXT_AUFLEGEN));
        m_bCall = true;
    }
}

void CDOrderInformation1::OnBnClickedButtonDruck2()
{
    char underline[111];
    int pos, maxpos;
    CString liste;
    CString Verbund;
    CDruckAuftrag druckAuftrag;
    memset(underline, '-', 110);
    underline[110] = '\0';

    liste.Format("%-15.15s %07.7s % 27.27s %-16.16s %-10.10s %-2.2s",
        CResString::ex().getStrTblText(AETXT_KUNDEN_NR).GetString(), IDF_Nr.GetString(),
        CResString::ex().getStrTblText(AETXT_TELEFON).GetString(), Tel.GetString(),
        CResString::ex().getStrTblText(AETXT_A_ART).GetString(), AA.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-26.26s % 8.8s %-16.16s %-10.10s %-2.2s",
        CResString::ex().getStrTblText(AETXT_INHABER).GetString(), Inhaber.GetString(),
        CResString::ex().getStrTblText(AETXT_KURZWAHL).GetString(), Tel_KW.GetString(),
        CResString::ex().getStrTblText(AETXT_KOM_ART).GetString(), KA.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-26.26s % 4.4s-%-3.3s %-16.16s %-10.10s %-2.2s",
        CResString::ex().getStrTblText(AETXT_APOTHEKENNAME).GetString(), Apotheke.GetString(),
        CResString::ex().getStrTblText(AETXT_ZEILEN_DAFUE).GetString(), CResString::ex().getStrTblText(AETXT_ART).GetString(), Dafue_Typ.GetString(),
        CResString::ex().getStrTblText(AETXT_BUCH_ART).GetString(), BA.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-8.8s %-6.6s %-26.26s % 8.8s %-16.16s %-4s: %-10.10s",
        CResString::ex().getStrTblText(AETXT_PLZ_ORT).GetString(), PLZ.GetString(), Ort.GetString(),
        CResString::ex().getStrTblText(AETXT_AUF_NR).GetString(), Auftr_Nr.GetString(),
        CResString::ex().getStrTblText(AETXT_TOUR).GetString(), Tour.GetString());
    druckAuftrag.AddKopfZeile(liste);

    if (m_LAuftNr != 0)
    {
        liste.Format("                                           %-8.8s %-16.16s %-14.14s %-8.8s %-11.11s %ld",
            CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(), Vsenr.GetString(),
            CResString::ex().getStrTblText(AETXT_RECHNR).GetString(), Rech_Nr.GetString(),
            Lauft_Nr.GetString(), m_LAuftNr);
    }
    else
    {
        liste.Format("                                           %-8.8s %-16.16s %-14.14s %-8.8s",
            CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(), Vsenr.GetString(),
            CResString::ex().getStrTblText(AETXT_RECHNR).GetString(), Rech_Nr.GetString());
    }
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-52.52s",
        CResString::ex().getStrTblText(AETXT_PHONIE_INFO).GetString(), Kndtext.GetString());
    druckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-52.52s",
        CResString::ex().getStrTblText(IDS_BEMERK).GetString(), Bemerk.GetString());
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    liste.Format("% 4.4s % 4.4s % 4.4s % 4.4s %-9.9s % 4.4s %-24.24s % 4.4s % 2.2s % 4.4s %13.13s VB %-60.60s",
        CResString::ex().getStrTblText(AETXT_AMGE).GetString(),
        CResString::ex().getStrTblText(AETXT_BMGE).GetString(),
        CResString::ex().getStrTblText(AETXT_NRME).GetString(),
        CResString::ex().getStrTblText(AETXT_VERBME).GetString(),
        CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
        CResString::ex().getStrTblText(AETXT_FU).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTIKELNAME).GetString(),
        CResString::ex().getStrTblText(AETXT_DAF).GetString(),
        CResString::ex().getStrTblText(AETXT_PA).GetString(),
        CResString::ex().getStrTblText(AETXT_PNR).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTICLE_CODE).GetString(),
        CResString::ex().getStrTblText(IDS_BEMERK).GetString());
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    liste += "                                        ";
    liste += CResString::ex().getStrTblText(AETXT_DATUM);
    liste += ": ";
    liste += Datum;
    druckAuftrag.AddFussZeile(liste);
    maxpos = m_ListCtl->GetItemCount();
    for (pos = 0; pos<maxpos; pos++)
    {
        Verbund = m_ListCtl->GetItemText(pos, COL_VERBUND);
        if (Verbund.IsEmpty()) Verbund = m_ListCtl->GetItemText(pos, COL_VERBUNDFIL);
        liste.Format("% 4.4s % 4.4s % 4.4s % 4.4s %-9.9s % 4.4s %-24.24s % 4.4s % 2.2s % 4.4s %13.13s %-2.2s %-60.60s",
            m_ListCtl->GetItemText(pos, COL_AMGE).GetString(),
            m_ListCtl->GetItemText(pos, COL_BMGE).GetString(),
            m_ListCtl->GetItemText(pos, COL_NRME).GetString(),
            m_ListCtl->GetItemText(pos, COL_VERBME).GetString(),
            m_ListCtl->GetItemText(pos, COL_EINHEIT).GetString(),
            m_ListCtl->GetItemText(pos, COL_FU).GetString(),
            m_ListCtl->GetItemText(pos, COL_ARTIKELNAME).GetString(),
            m_ListCtl->GetItemText(pos, COL_DAF).GetString(),
            m_ListCtl->GetItemText(pos, COL_PA).GetString(),
            m_ListCtl->GetItemText(pos, COL_PNR).GetString(),
            m_ListCtl->GetItemText(pos, COL_ARTICLECODE).GetString(),
            Verbund.GetString(),
            m_ListCtl->GetItemText(pos, COL_BEMERK).GetString());
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(2);
    druckAuftrag.DelAllData();
}
