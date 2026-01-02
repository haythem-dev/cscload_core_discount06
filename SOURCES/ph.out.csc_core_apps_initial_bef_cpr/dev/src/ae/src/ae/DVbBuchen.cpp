// DVbBuchen.cpp : implementation file
//

#include "stdafx.h"
#include "DVbBuchen.h"
#include "DBePosBearb.h"
#include "AeFView.h"
#include "AeDoc.h"
#include "DKndWahl.h"
#include <kndsel.h>
#include <vbbuch.h>
#include "DViewKnd.h"
#include <verbundcheck.h>
#include "DProductPromo.h"
#include "DServiceOrder.h"
#include "DTenderOrder.h"

//Definitionen Buchen
#define BUCHEN_YES      0
#define BUCHEN_NO       1

//Definitionen Herstellerkontingent
#define PRODUSER_QUOTA      2

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB          0
#define COL_AMGE        1
#define COL_BMGE        2
#define COL_NRME        3
#define COL_VERBME      4
#define COL_EINHEIT     5
#define COL_NAME        6
#define COL_ARTCODE     7
#define COL_FILIALE     8
#define COL_DAF         9
#define COL_CONT        10
#define COL_KZ          11
#define COL_BEMERK      12
#define COL_PREIS_TYP   13
#define COL_PZN         14
#define COL_PRODQUOTA   15
#define COL_FREEPRICE   16
#define COL_PCTMAN      17
#define NUM_COLUMNS     18

static COLUMNS_TYPES Columns[] =
{
    COL_KB,         "",         30,     LVCFMT_LEFT,
    COL_AMGE,       "",         35,     LVCFMT_RIGHT,
    COL_BMGE,       "",         35,     LVCFMT_RIGHT,
    COL_NRME,       "",         30,     LVCFMT_RIGHT,
    COL_VERBME,     "",         30,     LVCFMT_RIGHT,
    COL_EINHEIT,    "",         55,     LVCFMT_RIGHT,
    COL_NAME,       "",         120,    LVCFMT_LEFT,
    COL_ARTCODE,    "",         75,     LVCFMT_RIGHT,
    COL_FILIALE,    "",         30,     LVCFMT_RIGHT,
    COL_DAF,        "",         40,     LVCFMT_CENTER,
    COL_CONT,       "",         25,     LVCFMT_CENTER,
    COL_KZ,         "",         40,     LVCFMT_CENTER,
    COL_BEMERK,     "",         200,    LVCFMT_LEFT,
    COL_PREIS_TYP,  "",         0,      LVCFMT_LEFT,
    COL_PZN,        "",         55,     LVCFMT_RIGHT,
    COL_PRODQUOTA,  "",         0,      LVCFMT_LEFT,
    COL_FREEPRICE,  "",         0,      LVCFMT_LEFT,
    COL_PCTMAN,     "",         0,      LVCFMT_LEFT,
    -1, "",          0,     0
};

/////////////////////////////////////////////////////////////////////////////
// CDVbBuchen dialog


CDVbBuchen::CDVbBuchen(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDVbBuchen::IDD, pParent), CPageBrowser(0)
{
    m_lKndNr        = 0;
    m_IdfNr         = 0;
    m_VzNr          = 0;
    m_lAuftrNr      = 0;
    m_bVersorgt     = false;
    m_ifunktion     = 0;    // Standard = Verbund buchen
    m_bNoCO         = false;
    m_cAufArt = _T("");

    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_AMGE].Columns = CResString::ex().getStrTblText(AETXT_AMGE);
    Columns[COL_BMGE].Columns = CResString::ex().getStrTblText(AETXT_BMGE);
    Columns[COL_NRME].Columns = CResString::ex().getStrTblText(AETXT_NRME);
    Columns[COL_VERBME].Columns = CResString::ex().getStrTblText(AETXT_VERBME);
    Columns[COL_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[COL_NAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[COL_ARTCODE].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[COL_FILIALE].Columns = CResString::ex().getStrTblText(AETXT_KZ_FILIALE);
    Columns[COL_DAF].Columns = CResString::ex().getStrTblText(AETXT_DAF);
    Columns[COL_CONT].Columns = CResString::ex().getStrTblText(AETXT_CONT);
    Columns[COL_KZ].Columns = CResString::ex().getStrTblText(AETXT_KZ_KENNZEICHEN);
    Columns[COL_BEMERK].Columns = CResString::ex().getStrTblText(IDS_BEMERK);
    Columns[COL_PREIS_TYP].Columns = CResString::ex().getStrTblText(AETXT_PREIS_TYP);
    Columns[COL_PZN].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Columns[COL_PRODQUOTA].Columns = CResString::ex().getStrTblText(AETXT_PROD_QUOTA);
    Columns[COL_FREEPRICE].Columns = CResString::ex().getStrTblText(AETXT_FREE_PRICE);
    Columns[COL_PCTMAN].Columns = CResString::ex().getStrTblText(AETXT_PCT_MAN);
}


void CDVbBuchen::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_LISTE, m_CStaticListe);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDVbBuchen, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_MARK, OnButtonMark)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDVbBuchen message handlers

BOOL CDVbBuchen::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_SUBITEMIMAGES;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_YES);
    idResources.push_back(IDI_ICON_NOT);
    idResources.push_back(IDI_ICON_PRODQUOTA);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    if (m_ifunktion == 1)
    {
        m_CStaticListe.SetWindowText(CResString::ex().getStrTblText(IDS_DEF_ARTICLE));
        this->SetWindowText(CResString::ex().getStrTblText(IDS_WORK_DEF));
    }
    else if (m_ifunktion == 2)
    {
        m_CStaticListe.SetWindowText(CResString::ex().getStrTblText(IDS_HIST_ARTICLE));
        this->SetWindowText(CResString::ex().getStrTblText(IDS_NEW_HIST_ORDER));
    }

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    if (m_lKndNr == 0)
    {
        //Definition Kunde
        CDKndWahl dlgKndWahl;

        if (dlgKndWahl.DoModal() == IDOK)
        {
            m_lFilialNr = dlgKndWahl.GetKndFiliale();
            m_lKndNr = dlgKndWahl.GetKndNr();
            m_IdfNr = dlgKndWahl.GetIdfNr();
            m_VzNr = dlgKndWahl.GetKndVz();

            if (dlgKndWahl.GetKndOrgFiliale() == 0)
            {
                ((CAeFView*)AeGetApp()->m_pViewEing)->SetOrgFilNr(dlgKndWahl.GetKndVz());
            }
            else
            {
                ((CAeFView*)AeGetApp()->m_pViewEing)->SetOrgFilNr(dlgKndWahl.GetKndOrgFiliale());
            }
        }
        else
        {
            return IDCANCEL;
        }

        CKNDSCHALTER kndschalter;
        kndschalter.s.KUNDENNR = m_lKndNr;
        kndschalter.s.IDFNR = m_IdfNr;
        kndschalter.s.VERTRIEBSZENTRUMNR = m_VzNr;
        kndschalter.Server(AakundeSel_kndschalter);
        m_bKndMussKopfBem = kndschalter.s.SKDMUSSKOPF[0] == '1' ? true : false;
        m_bGiveProdQuota = kndschalter.s.SKDGIVEPRODQUOTA[0] == '1' ? true : false;
    }
    CPARAUFBEARB paraufbearb;
    BeginWaitCursor();
    paraufbearb.s.FILIALNR = m_VzNr;
    paraufbearb.Server( AafilSelaufbearb );
    EndWaitCursor();
    AeGetApp()->UseTourManagerCst = paraufbearb.s.USETOURMANAGER;
    AeGetApp()->IsAutoBuchungNachlieferung = (paraufbearb.s.AUTOMNACHLIEF[0] == '1');
    AeGetApp()->IsCool20 = (paraufbearb.s.SCOOL20 == 1);
    AeGetApp()->IsBTMextra = (paraufbearb.s.BTM_EXTRA[0] == '1');
    AeGetApp()->IsNoValuta = (paraufbearb.s.SNOCHANGEVAL[0] == '1');
    AeGetApp()->IsKumPos = (paraufbearb.s.SKUMPOS[0] == '1');
    AeGetApp()->IsPrintCode = (paraufbearb.s.SANZPRINTCODE[0] == '1');
    AeGetApp()->IsIBTdirect = (paraufbearb.s.SCLOSEIBTATONCE == 1);
    AeGetApp()->IsNewCallback = (paraufbearb.s.SWNEWCALLBACK == 1);
    AeGetApp()->IsStopCrema = (paraufbearb.s.SSTOPCREMA == 1);
    AeGetApp()->IsNLevelIBTCst = (paraufbearb.s.NLEVELIBT == 1);
    AeGetApp()->IsNlSofort = (paraufbearb.s.SCLOSERESTDELIVERYATONCE == 1);
    AeGetApp()->IsDispoSofort = (paraufbearb.s.SCLOSEDISPOATONCE == 1);
    AeGetApp()->TimeNoBTM = paraufbearb.s.TIME_NO_BTM;
    AeGetApp()->MaxPosEil = paraufbearb.s.MAXPOSEIL;
    AeGetApp()->PosZu = paraufbearb.s.ANZPOSZU;
    AeGetApp()->PriceRange = paraufbearb.s.RANGEPRICEPCT;
    AeGetApp()->DurchlaufZeit = paraufbearb.s.DURCHLAUFNORMAL;
    AeGetApp()->Verspaetung = paraufbearb.s.TOURVERSPAETUNG;
    AeGetApp()->Wake1 = paraufbearb.s.WAKETIME1;
    AeGetApp()->Wake2 = paraufbearb.s.WAKETIME2;

    if (!m_bVersorgt)
    {
        m_ListCtl.SetColumnWidth( COL_CONT , 0 );
        struct VbArtikel vbartikel;
        CVBBUCH verbund;
        vbartikel.ArtNr = "0";
        m_pl.clear();
        verbund.s.ARTIKEL_NR = m_lKndNr;
        verbund.s.FILIALNR = m_VzNr;
        verbund.s.PRODUSERQUOTA = (AeGetApp()->UseTourManagerCst() > 0) ? 1 : 0;    //wird misbraucht
        verbund.s.BESTAND = AeGetApp()->IsNLevelIBTCst() ? 1 : 0;  //wird misbraucht

        for (;;)
        {
            verbund.s.FETCH_REL = 1;
            verbund.Server(m_ifunktion == 0 ? Aaauft_Sel_vbmoegl : AaauftSel_defekte);

            if (verbund.rc == SRV_SQLNOTFOUND)
            {
                break;
            }

            if (atol(vbartikel.ArtNr) == verbund.s.ARTIKEL_NR)
            {
                continue;    // mehrmalige Bestellung ueberlesen
            }

            vbartikel.MengeBestellt.Format("%ld", verbund.s.MENGEBESTELLT);
            vbartikel.BestMenge.Format("%ld", verbund.s.MENGEBESTAETIGT);
            vbartikel.NatraMenge.Format("%ld", verbund.s.MENGENATRA);
            vbartikel.VerbMenge = "0";
            vbartikel.ArtEinh = verbund.s.EINHEIT;
            vbartikel.ArtName = verbund.s.ARTIKEL_NAME;
            vbartikel.ArtNr.Format("%ld", verbund.s.ARTIKEL_NR);
            vbartikel.VerbFiliale.Format("%d", verbund.s.FILIALNR);
            vbartikel.Darreichform = verbund.s.DARREICHFORM;
            vbartikel.Bemerkung = verbund.s.BEMERKUNGEN;
            vbartikel.Kennzeichen = verbund.s.KURZBEZKONDI;
            vbartikel.LagerBereich.Empty();
            vbartikel.Preistyp.Empty();
            vbartikel.Prodquota.Format("%d", verbund.s.PRODUSERQUOTA);
            vbartikel.PreisFree = "0.00";  //uninterresant bei VB
            vbartikel.PctMan = "0.00";     //uninterresant bei VB
            m_pl.insert(m_pl.end(), vbartikel);
        }

        verbund.s.FETCH_REL = 0;    //Close Cursor
        verbund.Server(m_ifunktion == 0 ? Aaauft_Sel_vbmoegl : AaauftSel_defekte);

        if (m_ifunktion != 0)   // Bei Defekten nachträglich nachsehen ob VB moeglich
        {
            CVERBUNDMOEGL verbundmoegl;
            CAUFALTLAGORT ibt;
            for (m_it = m_pl.begin(); m_it < m_pl.end(); m_it++)
            {
                if (AeGetApp()->IsNLevelIBTCst())
                {
                    ibt.s.ARTIKEL_NR = atol(m_it->ArtNr);
                    ibt.s.FILIALNR = m_VzNr;
                    ibt.Server(AasrvCheckIBTStockLevel);
                    if (ibt.rc == SRV_OK)
                    {
                        m_it->VerbFiliale.Format("%d", ibt.s.FILIALNR);
                    }
                }
                else
                {
                    verbundmoegl.s.ARTIKEL_NR = atol(m_it->ArtNr);
                    verbundmoegl.s.FILIALNR = m_VzNr;
                    verbundmoegl.SelVbBestandNeu();

                    if (verbundmoegl.rc == SRV_OK && verbundmoegl.GetBestand() > 0)
                    {
                        m_it->VerbFiliale.Format("%d", verbundmoegl.s.FILIALNR);
                    }
                }
            }
        }
    }

    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDVbBuchen::GetPage(const int /*nKzUpDown=NEXT_PG*/)
{
    //Variablen
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    CARTAESEL code;

    //Anfangsinitialisierung durchfuehren
    m_ListCtl.DeleteAllItems();

    CLetterMan kb;
    for (m_it = m_pl.begin() ; m_it < m_pl.end(); m_it++)
    {
        //Ausgabe in die Listbox
        s[COL_KB] = kb.Next();
        s[COL_AMGE] = m_it->MengeBestellt;
        s[COL_BMGE] = m_it->BestMenge;
        s[COL_NRME] = m_it->NatraMenge;
        s[COL_VERBME] = m_it->VerbMenge;
        s[COL_EINHEIT] = m_it->ArtEinh;
        s[COL_NAME] = m_it->ArtName;
        code.s.ARTIKEL_NR = atol(m_it->ArtNr);
        code.Server( AatartSel_Preferred );
        AllgEntfSpaces(code.s.ARTICLE_CODE);
        s[COL_ARTCODE] = code.s.ARTICLE_CODE;
        s[COL_FILIALE] = m_it->VerbFiliale;
        s[COL_DAF] = m_it->Darreichform;
        s[COL_CONT] = m_it->LagerBereich;
        s[COL_KZ] = m_it->Kennzeichen;
        s[COL_BEMERK] = m_it->Bemerkung;
        s[COL_PREIS_TYP] = m_it->Preistyp;
        s[COL_PZN] = m_it->ArtNr;
        s[COL_PRODQUOTA] = m_it->Prodquota;
        s[COL_FREEPRICE] = m_it->PreisFree;
        s[COL_PCTMAN] = m_it->PctMan;

        int index;
        CListCtrlHelper::GetAppendImageItem(m_ListCtl, NUM_COLUMNS, s, (m_ifunktion == 0) ? BUCHEN_YES : BUCHEN_NO, index);

        if ((atoi(m_it->Prodquota)) == 1)
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_AMGE, PRODUSER_QUOTA);
        }

    } //Ende der for()-Schleife

    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return true;
}

void CDVbBuchen::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDVbBuchen::OnOK()
{
    int max = m_ListCtl.GetItemCount();

    BeginWaitCursor();

    if ((m_cAufArt == "CO") || (m_cAufArt == "PO"))   //bei CO (Cash order) und PO (Proforma order) als Folgeauftragsart NO vorgeben
    {
        m_cAufArt = "NO";
    }

    CAeFView* pViewEing = (CAeFView*)AeGetApp()->m_pViewEing;
    if (m_lAuftrNr == 0)
    {
        //nase muß noch über select korrekt versorgt werden
        pViewEing->SetOrgFilNr(m_VzNr);

        if (!pViewEing->NewOrder(m_lKndNr, m_VzNr))
        {
            m_lAuftrNr = pViewEing->GetKdauftragNr();
        }

        pViewEing->GetDlgItem(IDC_STATIC_AA)->SetWindowText(m_cAufArt);
        pViewEing->SetTenderno(m_TenderNo);
        pViewEing->OnABKArtDef(FALSE, FALSE, TRUE);
    }

    if (pViewEing->GetServType() <= 0)
    {
        for (int pos = 0; pos < max; pos++)
        {
            if (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES)
            {
                Buchen(pos);
            }
        }
    }

    EndWaitCursor();
    pViewEing->GetDlgItem(IDC_STATIC_AA)->GetWindowText(m_cAufArt);

    if (pViewEing->GetTenderno() > 0)
    {
        CDTenderOrder dlgTenderOrder;
        dlgTenderOrder.ptrDoc = (CAeDoc*)pViewEing->GetDocument();
        dlgTenderOrder.m_lKndNr = m_IdfNr;
        dlgTenderOrder.m_lTenderNo = pViewEing->GetTenderno();
        dlgTenderOrder.DoModal();
    }
    else if (pViewEing->GetServType() > 0)
    {
        CDServiceOrder dlgServiceOrder;
        dlgServiceOrder.m_ptrDoc = (CAeDoc*)pViewEing->GetDocument();
        dlgServiceOrder.m_lKndNr = m_IdfNr;
        dlgServiceOrder.m_sServType = pViewEing->GetServType();
        dlgServiceOrder.DoModal();
    }
    else if (m_cAufArt == "MP")
    {
        CDProductPromo dlgProductPromo;
        dlgProductPromo.m_ptrDoc = (CAeDoc*)pViewEing->GetDocument();
        dlgProductPromo.m_lCustomerno = m_IdfNr;
        dlgProductPromo.m_sBranchno = m_VzNr;
        dlgProductPromo.DoModal();
    }

    CDialogMultiLang::OnOK();
}

void CDVbBuchen::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES)
    {
        DelMarked(pos);
    }
    else
    {
        SetMarked(pos);
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDVbBuchen::OnHookFkt( WPARAM /*wParam*/, LPARAM /*lpMsg*/ )
{
    return 0L;
}

void CDVbBuchen::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDVbBuchen::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    int pos;
    OnKeydownList(pNMHDR, pResult, m_ListCtl, pos);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InRange(pLVKeyDow->wVKey, m_ListCtl.GetItemCount()))
    {
        if (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES)
        {
            DelMarked(pos);
        }
        else
        {
            SetMarked(pos);
        }
    }
}

void CDVbBuchen::SetMarked(int pos)
{
    if ((atoi(m_ListCtl.GetItemText(pos, COL_PRODQUOTA))) == 1)
    {
        if (m_bGiveProdQuota)
        {
            if (MsgBoxYesNo(AETXT_BOOK_PRODQUOTA) != IDYES)
            {
                return;
            }
        }
        else
        {
            MsgBoxOK(AETXT_NO_PRODQUOTA);
            return;
        }
    }

    CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, BUCHEN_YES);
}

void CDVbBuchen::DelMarked(int pos)
{
    CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, BUCHEN_NO);
}

void CDVbBuchen::Buchen(int pos)
{
    if (m_bNoCO)
    {
        return;
    }

    long lMengeBestellt;

    if (m_ifunktion == 2)
    {
        // Bei Historie alte Liefermenge buchen
        if (atol(m_ListCtl.GetItemText(pos, COL_AMGE)) < atol(m_ListCtl.GetItemText(pos, COL_BMGE)) )
        {
            lMengeBestellt = atol(m_ListCtl.GetItemText(pos, COL_AMGE));
        }
        else
        {
            lMengeBestellt = atol(m_ListCtl.GetItemText(pos, COL_BMGE));
        }
    }
    else
    {
        // nur die Defektmenge buchen
        lMengeBestellt = atol(m_ListCtl.GetItemText(pos, COL_AMGE)) - atol(m_ListCtl.GetItemText(pos, COL_BMGE));
    }

    //Rabatteingabe nur bei FC
    long MengeNatra = (m_cAufArt == "FC") ? atol(m_ListCtl.GetItemText(pos, COL_NRME)) : 0L;

    CString cBemerkung = m_ListCtl.GetItemText(pos, COL_BEMERK);
    short sPreistyp = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, COL_PREIS_TYP)));
    double dPctMan = static_cast<double>(atof(m_ListCtl.GetItemText(pos, COL_PCTMAN)));
    double dFreePrice = static_cast<double>(atof(m_ListCtl.GetItemText(pos, COL_FREEPRICE)));

    if (lMengeBestellt != 0 || ((m_cAufArt == "FC") && MengeNatra > 0))
    {
        long lMengeAbbuchung = lMengeBestellt;
        long lPosStat = ITEM_STAT_NORMAL;

        CAUFPOSBUCH aufposbuch;

        if (m_ifunktion == 0)
        {
            aufposbuch.s.FILIALNR1 = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, COL_FILIALE)));
            aufposbuch.s.MENGE     = lMengeBestellt;
        }

        CAeFView* pViewEing = (CAeFView*)AeGetApp()->m_pViewEing;

        for (;;)
        {
            aufposbuch.s.MENGEBESTELLT     = lMengeBestellt;
            aufposbuch.s.MENGEBESTAETIGT   = lMengeAbbuchung;
            aufposbuch.s.ARTIKEL_NR        = atol(m_ListCtl.GetItemText(pos, COL_PZN));
            aufposbuch.s.MENGENATRA        = MengeNatra;
            aufposbuch.s.STATUS            = lPosStat;
            aufposbuch.s.PREIS_TYP         = sPreistyp;
            aufposbuch.s.DISCOUNTVALPCTMAN = dPctMan;
            aufposbuch.s.PREISEKAPOFREE    = dFreePrice;
            strcpy(aufposbuch.s.BEMERKUNG, (LPCTSTR)cBemerkung);

            //Buchungsversuch
            aufposbuch.Server(AasrvWritepos, PIPE_AE_SRV);

            if (aufposbuch.rc < SRV_OK)                            //Fehler
            {
                return;
            }
            if (aufposbuch.s.STATUS == ITEM_STAT_KREDITLIMIT)     //Kreditlimit ueberschritten
            {
                if (AeGetApp()->IsBG())
                {
                    if (MsgBoxYesNo(IDP_CHANGE_CO) == IDYES)
                    {
                        pViewEing->m_PaymentType.SetAt(0, 'C');
                        CAUFTRAG auftrag;
                        auftrag.s.PAYMENTTYPE[0] = 'C';
                        auftrag.Server(AasrvSetOrderToCash, PIPE_AE_SRV);
                        auftrag.s.VALUTAMONATE = 0L;
                        auftrag.Server(AasrvChangeValuta, PIPE_AE_SRV);
                        pViewEing->GetDlgItem(IDC_STATIC_PAYMENTTYPE)->ShowWindow(SW_SHOW);
                        continue; //Position erneut buchen
                    }

                    m_bNoCO = true;
                    return;
                }
            }
            else if (   aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE       //Verfügbare Menge reichte nicht aus
                     || aufposbuch.s.STATUS == ITEM_STAT_NACHLIEFUPD )     //Verfügbare Menge reichte nicht aus wg. Kontigent
            {
                char str[81];
                CDBePosBearb dlgBePosBearb;
                dlgBePosBearb.SetKndMussKopfBem(m_bKndMussKopfBem);
                dlgBePosBearb.SetBestMengeStr("%ld", lMengeBestellt);
                dlgBePosBearb.m_CArtName        = m_ListCtl.GetItemText(pos, COL_NAME);
                dlgBePosBearb.m_CArtEinh        = m_ListCtl.GetItemText(pos, COL_EINHEIT);
                dlgBePosBearb.SetArtNr(m_ListCtl.GetItemText(pos, COL_PZN));
                dlgBePosBearb.m_CArtCode        = m_ListCtl.GetItemText(pos, COL_ARTCODE);
                dlgBePosBearb.SetBestand(_ltoa(aufposbuch.s.BESTAND, str, 10));
                dlgBePosBearb.SetVerbMenge(aufposbuch.s.MENGE);
                dlgBePosBearb.SetVerbFiliale(aufposbuch.s.FILIALNR1);
                dlgBePosBearb.m_CDarreichform   = m_ListCtl.GetItemText(pos, COL_DAF);
                dlgBePosBearb.m_LiefMenge       = aufposbuch.s.BESTAND;
                dlgBePosBearb.SetBestMenge(lMengeBestellt);
                dlgBePosBearb.m_CBemerkung      = cBemerkung;
                dlgBePosBearb.SetPosStat(ITEM_STAT_NACHLIEFERN);
                dlgBePosBearb.m_KndNr           = m_lKndNr;
                dlgBePosBearb.m_IdfNr           = m_IdfNr;

                if (dlgBePosBearb.DoModal() == IDOK)
                {
                    lMengeAbbuchung  = dlgBePosBearb.m_Menge;
                    lPosStat         = dlgBePosBearb.GetPosStat();
                    cBemerkung       = dlgBePosBearb.m_CBemerkung;
                    aufposbuch.s.FILIALNR1 = dlgBePosBearb.GetVerbFiliale();
                    continue; //Position erneut buchen
                }
                return;
            }
            else if (aufposbuch.s.STATUS == ITEM_STAT_VERBUND_NICHT_MOEGLICH)
            {
                MsgBoxOK( IDP_AUX_BAD_STATE );
                return;
            }

            break;
        } //Ende der for(;;)

        if (aufposbuch.s.STATUS == ITEM_STAT_VERBUND_REICHT_NICHT)   //Verfügbare Verbundmenge reichte nicht aus
        {
            CString str;
            str.Format(CResString::ex().getStrTblText(IDS_MENGE_BEST_BEST), aufposbuch.s.MENGEBESTELLT, aufposbuch.s.MENGEBESTAETIGT, aufposbuch.s.MENGE);
            CString cstr;
            cstr.Format(CResString::ex().getStrTblText(IDP_VB_MENGE_WENIG), str.GetString());
            MsgBoxOK(cstr);
        }

        ((CAeDoc*)AeGetApp()->m_Doc)->AddPosition(aufposbuch.s);   //Positionsliste erstellen
        pViewEing->AusgAufWerte(aufposbuch.s.ANZPOS, aufposbuch.s.WERTAUFTRAG, aufposbuch.s.WERTLIEFERUNG, aufposbuch.s.WERTZEILEN, aufposbuch.s.BALANCE, aufposbuch.s.BALANCE2);
        pViewEing->AusgAufWerteBG(aufposbuch.s.WERTNETTO_FV, aufposbuch.s.WERTTAX_FV, aufposbuch.s.WERTNETTO_KK, aufposbuch.s.WERTTAX_KK, aufposbuch.s.WERTNETTO_EH, aufposbuch.s.WERTTAX_EH, aufposbuch.s.WERTEXCLUSIVE);

        if (AeGetApp()->IsBG())
        {
            pViewEing->m_pDlgKnd->SetAndShowCreditLimitValue1(aufposbuch.s.WERTKL1);
            pViewEing->m_pDlgKnd->SetAndShowCreditLimitValue2(aufposbuch.s.WERTKL);
        }
    }
}

void CDVbBuchen::OnButtonMark()
{
    int pos, ende;
    ende = m_ListCtl.GetItemCount();

    for (pos = 0; pos < ende; pos++)
    {
        SetMarked(pos);
    }
}
