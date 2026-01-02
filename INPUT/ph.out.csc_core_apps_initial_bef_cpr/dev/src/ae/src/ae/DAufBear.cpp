// daufbear.cpp : implementation file
//

#include "stdafx.h"
#include <kndsel.h>
#include "DKndInf.h"
#include "AeDoc.h"
#include "AeFView.h"
#include "DAufBear.h"
#include "DAufZlBearb.h"
#include "DArtInf.h"
#include "DBePosBearb.h"
#include "DVerbBestaet.h"
#include "DDruckAuftrag.h"
#include "DAufFrText.h"
#include <verbundcheck.h>
#include "MainFrm.h"
#include "DServicePos.h"
#include "DServiceZinsen.h"
#include "DViewKnd.h"
#include <artikel.h>
#include <ctype.h>
#include "DPromotionen.h"

//Definitionen Bearbeitet
#define DONE_YES        0
#define DONE_NO         1

//Definitionen Herstellerkontingent
#define PRODUSER_QUOTA  2

//Definitionen Positionsarten
#define AUFTRAG_FV      3
#define AUFTRAG_KK      4
#define AUFTRAG_EH      5

//Definitionen Artikelkennzeichen
#define LIEFBER_BTM       9
#define LIEFBER_KUEHL    12
#define LIEFBER_KUEHL_U8 13
#define LIEFBER_COOL20   16
#define LIEFBER_DEGETTER 20
//Definitionen Liste5
#define LIEFBER_L5       17

//Definitionen kurzes Verfallsdatum
#define VERFALL         18

/////////////////////////////////////////////////////////////////////////////
// CDAufBear dialog


CDAufBear::CDAufBear(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAufBear::IDD, pParent), CPageBrowser(0)
{
    m_CTelNr = _T("");
    m_CKurzWahl = _T("");
    ptrDoc              = NULL;
    m_bNatraDefs        = false;
    m_bDafueKz          = false;
    m_bDefektAnzeige    = FALSE;
    m_iDefNachPos       = FALSE;
    m_bDefSelVerbund    = FALSE;
    m_bDefSelDfDef      = FALSE;
    m_bDefSelPhonDef    = FALSE;
    m_bDefSelDfFrText   = FALSE;
    m_bDefSelPhonFrText = FALSE;
    m_bArtAnschreiben   = FALSE;
    m_bArtUebernehmen   = FALSE;
    m_bKndSchwerpunk3   = false;
    m_bKndSchwerpunk5   = false;
    m_CArtName          = "";
    m_CArtEinh          = "";
    m_CArtDarr          = "";
    m_VerbundZeitenKnd  = "";
    m_lMenge            = 0;
    m_lKndNr            = 0;
    m_bMengWarn         = false;
    m_ListCtl           = new CAIListCtrl;
    assert(m_ListCtl);
    m_CArticleCode      = "";
    m_OrgFilNr          = 0;

}

CDAufBear::~CDAufBear()
{
    delete m_ListCtl;
    m_ListCtl = 0;
}

void CDAufBear::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_VERBUND, m_CBVerbund);
    DDX_Control(pDX, IDC_CHECK_FT_PHON, m_CBFtPhon);
    DDX_Control(pDX, IDC_CHECK_FT_DAFUE, m_CBFtDafue);
    DDX_Control(pDX, IDC_CHECK_DEF_PHON, m_CBDefPhon);
    DDX_Control(pDX, IDC_CHECK_DEF_DAFUE, m_CBDefDafue);
    DDX_Control(pDX, IDC_EDIT_SUCHBEZ, m_EditSuchBez);
    DDX_Control(pDX, IDC_EDIT_POSITION, m_EditPosNr);
    DDX_Control(pDX, IDC_LIST_AUFTRAG, *m_ListCtl);
    DDX_Text(pDX, IDC_STATIC_TELNR, m_CTelNr);
    DDX_Text(pDX, IDC_STATIC_TEL_KW, m_CKurzWahl);
}


BEGIN_MESSAGE_MAP(CDAufBear, CDialogMultiLang)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_AUFTRAG, OnKeydownListAuftrag)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_AUFTRAG, OnDblclkListAuftrag)
    ON_EN_CHANGE(IDC_EDIT_POSITION, OnChangeEditPosition)
    ON_EN_CHANGE(IDC_EDIT_SUCHBEZ, OnChangeEditSuchbez)
    ON_BN_CLICKED(IDC_CHECK_DEF_DAFUE, OnCheckDefDafue)
    ON_BN_CLICKED(IDC_CHECK_DEF_PHON, OnCheckDefPhon)
    ON_BN_CLICKED(IDC_CHECK_FT_DAFUE, OnCheckFtDafue)
    ON_BN_CLICKED(IDC_CHECK_FT_PHON, OnCheckFtPhon)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_BN_CLICKED(IDC_BUTTON_ALL_POS, OnButtonAllPos)
    ON_BN_CLICKED(IDC_CHECK_VERBUND, OnCheckVerbund)
    ON_WM_DESTROY()
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDAufBear message handlers

BOOL CDAufBear::OnInitDialog()
{
    if (AeGetApp()->IsBG() || AeGetApp()->IsSchrift())
    {
        scgui::CResizeManager::ex().setIsActive(true);
        scgui::CResizeManager::ex().setFit2Screen(true);
        CDialogMultiLang::OnInitDialog();
        scgui::CResizeManager::ex().setIsActive(false);
    }
    else
    {
        CDialogMultiLang::OnInitDialog();
    }

    m_ListCtl->init();
    if (AeGetApp()->IsBG())
    {
        m_ListCtl->SetExtendedStyle(m_ListCtl->GetExtendedStyle()
                                | LVS_EX_GRIDLINES );        // Grid
    }
    m_ListCtl->SetFocus();
    //CenterWindow();

    DWORD dwOldBits = m_ListCtl->GetExtendedStyle();
    dwOldBits |= LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT;
    m_ListCtl->SetExtendedStyle(dwOldBits);

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_OK);
    idResources.push_back(IDI_ICON_NO);
    idResources.push_back(IDI_ICON_PRODQUOTA);
    idResources.push_back(IDI_ICON_FV);
    idResources.push_back(IDI_ICON_KK);
    idResources.push_back(IDI_ICON_EH);
    idResources.push_back(IDI_ICON_PP);
    idResources.push_back(IDI_ICON_TP);
    idResources.push_back(IDI_ICON_NO_RAB);
    idResources.push_back(IDI_ICON_BTM);
    idResources.push_back(IDI_ICON_PRIVAT);
    idResources.push_back(IDI_ICON_QUOTA);
    idResources.push_back(IDI_ICON_KUEHL);
    idResources.push_back(IDI_ICON_KUEHL_U8);
    idResources.push_back(IDI_ICON_PTS);
    idResources.push_back(IDI_ICON_PRODQUOTA);
    idResources.push_back(IDI_ICON_K20);
    idResources.push_back(IDI_ICON_L5);
    idResources.push_back(IDI_ICON_VERFALL);
    idResources.push_back(IDI_ICON_TFG);
    idResources.push_back(IDI_ICON_DE_BESORGER);
    CListCtrlHelper::CreateAndSetImageList(*m_ListCtl, m_ImageSmall, idResources);

    SetColumnWidthUser(m_ListCtl, "CDaufBearb", KEY_PATH, COL_AI_ANZ_LIST);
    AeGetApp()->m_AeLogging.WriteLine(2, "DaufBearb.cpp", "OnInitDialog", "Dialog started");

    //Listbox fuellen
    FillPosList();
    FillList();
    AeGetApp()->m_AeLogging.WriteLine(2, "DaufBearb.cpp", "OnInitDialog", "List filled");
    if (!m_CArticleCode.IsEmpty())
    {
        SelArtNo();
        OnOK();
        return TRUE;
    }

    if (m_bMengWarn)
        MsgBoxOK(IDP_WARN_MENGE);

    if (m_bDefektAnzeige)
    {
        CString CStr = CResString::ex().getStrTblText(IDP_MASKE_DEFANZ);
        this->SetWindowText(CStr);
        GetDlgItem(IDC_STATIC_POSNR)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_POSITION)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_SUCHBEGR)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_SUCHBEZ)->ShowWindow(FALSE);
        GetDlgItem(IDC_BUTTON_ALL_POS)->ShowWindow(FALSE);
        MarkListPos(m_iDefNachPos);
        if (m_bDefSelVerbund) CheckDlgButton(IDC_CHECK_VERBUND, TRUE);
        if (m_bDefSelDfDef) CheckDlgButton(IDC_CHECK_DEF_DAFUE, TRUE);
        if (m_bDefSelPhonDef) CheckDlgButton(IDC_CHECK_DEF_PHON, TRUE);
        if (m_bDefSelDfFrText) CheckDlgButton(IDC_CHECK_FT_DAFUE, TRUE);
        if (m_bDefSelPhonFrText) CheckDlgButton(IDC_CHECK_FT_PHON, TRUE);
    }
    else if (m_bNatraDefs)
    {
        CString CStr = CResString::ex().getStrTblText(IDP_MASKE_DEFRABS);
        this->SetWindowText(CStr);
        GetDlgItem(IDC_CHECK_VERBUND)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_DEF_DAFUE)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_DEF_PHON)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_FT_DAFUE)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_FT_PHON)->ShowWindow(FALSE);
    }
    else
    {
        GetDlgItem(IDC_CHECK_VERBUND)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_DEF_DAFUE)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_DEF_PHON)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_FT_DAFUE)->ShowWindow(FALSE);
        GetDlgItem(IDC_CHECK_FT_PHON)->ShowWindow(FALSE);
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAufBear::FillList()
{
    long vvdate = 0;

    if (AeGetApp()->IsHR())
    {
        zeit.Server(AafilGetdatetime);
        vvdate = zeit.s.DATUM / 100 % 10000;
        long mm = vvdate % 100;
        long jj = vvdate / 100;
        mm += 6;
        if (mm > 12)
        {
            mm -= 12;
            ++jj;
        }
        vvdate = jj * 100 + mm;
    }

    if (m_bDafueKz)
    {
        m_CBVerbund.EnableWindow(FALSE);
        m_CBDefDafue.EnableWindow(FALSE);
        m_CBDefPhon.EnableWindow(FALSE);
        m_CBFtDafue.EnableWindow(FALSE);
        m_CBFtPhon.EnableWindow(FALSE);
    }

    AUFPOSBUCH* ptrPos = ptrDoc->GetPosListe(); //Zeiger auf Beginn der Liste

    m_ListCtl->DeleteAllItems();

//nase alphabetisch for(;ptrPos != NULL;ptrPos =(AUFPOSBUCH *)(ptrPos->FETCH_REL))
    CLetterMan kb;
    bool first = true;
    for (int i = 0; ; i++)
    {
        CString cstr = kb.Next();
        ptrPos = ptrDoc->GetListPosition(i);
        if (ptrPos == NULL)
            break;
        if (m_bDefektAnzeige)
        {
            BOOL bIns = FALSE;
            if (m_bDefSelVerbund && ptrPos->MENGE != 0)
                bIns = TRUE;
            if (m_bDefSelDfDef && ptrPos->DAFUEART[0] != ITEM_ART_NO_DAFUE && ptrPos->KZDEFEKT[0] == '1')
                bIns = TRUE;
            if (m_bDefSelPhonDef && ptrPos->DAFUEART[0] == ITEM_ART_NO_DAFUE && ptrPos->KZDEFEKT[0] == '1')
                bIns = TRUE;
            if (m_bDefSelDfFrText && ptrPos->DAFUEART[0] != ITEM_ART_NO_DAFUE && ptrPos->KZFREITEXT[0] == '1')
                bIns = TRUE;
            if (m_bDefSelPhonFrText && ptrPos->DAFUEART[0] == ITEM_ART_NO_DAFUE && ptrPos->KZFREITEXT[0] == '1')
                bIns = TRUE;
            if (ptrPos->KZLIMITCHK[0] == '1')
                bIns = TRUE;

            if (!bIns)
                continue;
        }
        else if (m_bNatraDefs)
        {
            if (ptrPos->PROBLEMSTATE == 0)
                continue;
        }

        int index = m_ListCtl->GetItemCount();
        int kz;
        if (m_bDafueKz)
        {
            if (ptrPos->KZNACHBEARB[0] == '1')
            {
                kz = DONE_NO;
                first = false;
            }
            else kz = DONE_YES;
            if (m_ListCtl->InsertItem(index, cstr, kz) == -1)
                return;
        }
        else if (AeGetApp()->IsRS())
        {
            kz = (ptrPos->ARTICLE_NO_PACK > 0) ? DONE_NO : DONE_YES;
            if (m_ListCtl->InsertItem(index, cstr, kz ) == -1)
                return;
        }
        else if (AeGetApp()->IsBG())
        {
            if ((ptrPos->ARTICLE_NO_PACK > 0) || AllgBitleisteN((Bitleiste)ptrPos->ETPOSSCHALTER2, 11))
            {
                kz = DONE_NO;
            }
            else if (ptrPos->PREIS_TYP == 0)
            {
                kz = AUFTRAG_FV;
            }
            else if (ptrPos->PREIS_TYP == 1)
            {
                kz = AUFTRAG_KK;
            }
            else
                kz = AUFTRAG_EH;
            if (m_ListCtl->InsertItem(index, cstr, kz) == -1)
                return;
        }
        else if (AeGetApp()->IsHR())
        {
            CARTIKELVERFALL Verfall;
            Verfall.SetArtikel_nr(ptrPos->ARTIKEL_NR);
            Verfall.SetFilialnr(m_VzNr);
            Verfall.SetDatumverfall(static_cast<short>(vvdate));
            kz = Verfall.CheckShortExpiry() ? DONE_YES : VERFALL;
            if (m_ListCtl->InsertItem(index, cstr, kz) == -1)
                return;
        }
        else
        {
            kz = DONE_YES;
            if (m_ListCtl->InsertItem(index, cstr, kz) == -1)
                return;
        }
        UpdateListPos(index, ptrPos->POSNR);
    }
    if (m_bDafueKz && first)
    {
        m_CBVerbund.EnableWindow(FALSE);
        m_CBDefDafue.EnableWindow(TRUE);
        m_CBDefPhon.EnableWindow(TRUE);
        m_CBFtDafue.EnableWindow(TRUE);
        m_CBFtPhon.EnableWindow(TRUE);
        m_bDafueKz = false;
    }
    MarkListPos(0);
}

void CDAufBear::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST_AUFTRAG))
    {
        ChangePos();
        return;
    }
    else if (GetFocus() == GetDlgItem(IDC_EDIT_POSITION))
    {
        SelPosNr();
        return;
    }
    else if (GetFocus() == GetDlgItem(IDC_EDIT_SUCHBEZ))
    {
        SelSuchBez();
        return;
    }
    if (m_bDefektAnzeige)
    {
        m_iDefNachPos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
    }
    CDialogMultiLang::OnOK();
}

void CDAufBear::OnCancel()
{
    if (m_bDefektAnzeige)
    {
        m_iDefNachPos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
    }
    CDialogMultiLang::OnCancel();
}

void CDAufBear::SelPosNr()
{
    CString str;
    m_EditPosNr.GetWindowText(str);
    m_EditPosNr.SetWindowText("");
    int Pos = atol(str);
    if (Pos == 0)
    {
        Pos = GetMaxAufPos();
    }
    int max = m_ListCtl->GetItemCount();
    for (int i = 0; i < max; i++)
    {
        str = m_ListCtl->GetItemText(i, COL_AI_PNR);
        if (atol(str) == Pos)
        {
            MarkListPos(i);
            return;
        }
    }
}

int CDAufBear::GetMaxAufPos()
{
    int MaxPos = 0;
    int max = m_ListCtl->GetItemCount();
    for (int i=0; i < max; i++)
    {
        CString str = m_ListCtl->GetItemText(i, COL_AI_PNR);
        int pos = atol(str);
        MaxPos = (pos > MaxPos) ? pos : MaxPos;
    }
    return MaxPos;
}

void CDAufBear::SelSuchBez()
{
    AUFPOSBUCH* ptrPos = ptrDoc->GetPosListe(); //Zeiger auf Beginn der Liste

    m_ListCtl->DeleteAllItems();

    CString SuchBez;
    m_EditSuchBez.GetWindowText(SuchBez);
    m_EditSuchBez.SetWindowText("");

    CLetterMan kb;
    for (; ptrPos != NULL; ptrPos = (AUFPOSBUCH*)(ptrPos->FETCH_REL))
    {
        if (ptrPos == NULL)
            break;
        CString str1 = ptrPos->ARTIKEL_NAME;
        //Leerzeichen entfernen
        str1.Remove(' ');
        SuchBez.Remove(' ');
        CString str2 = str1.Left(SuchBez.GetLength());
        if (str2 == SuchBez)
        {
            int index = m_ListCtl->GetItemCount();
            if (m_ListCtl->InsertItem(index, kb.Next()) == -1)
                return ;
            UpdateListPos(index, ptrPos->POSNR);
        }
    }
    if (m_ListCtl->GetItemCount() > 0) MarkListPos(0);
}

long CDAufBear::GetAufPos(int pos)
{
    CString CStr = m_ListCtl->GetItemText(pos, COL_AI_PNR);
    return atol(CStr);
}

void CDAufBear::ChangePos()
{
    if (GetOrderType().IsNoVideoAufArt(AeGetApp()->VzNr_Kunde(), m_CAufArt))
    {
        MsgBoxOK(AETXT_NO_NEW_POS);
        return;
    }

    int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    long OrdPos = GetAufPos(pos);
    AUFPOSBUCH* ptrPos = ptrDoc->GetPosition(OrdPos);
    if (ptrPos->ARTICLE_NO_PACK > 0)
    {
        MsgBoxOK(AETXT_NO_MEMBER);
        return;
    }
    if (AllgBitleisteN((Bitleiste)ptrPos->ETPOSSCHALTER2, 11))
    {
        MsgBoxOK(AETXT_NO_REBAT);
        return;
    }
    if (ptrPos->PRODUSERQUOTA == 1)
    {
        if (!AeGetApp()->IsGiveProdQuota())
        {
            MsgBoxOK(AETXT_NO_PRODQUOTA);
            return;
        }
        else
        {
            if (MsgBoxYesNo(AETXT_BOOK_PRODQUOTA) != IDYES)
                return;
        }
    }
    if (ptrPos->MENGE > 0)
    {
        if (AeGetApp()->IsIBTdirect())
        {
            CAUFPOSBUCH checkvb;
            checkvb.s.FILIALNR1 = m_VzNr;
            checkvb.s.KDAUFTRAGNR = m_lAuftrNr;
            checkvb.s.POSNR = ptrPos->POSNR;
            checkvb.Server(AasrvIBTPosDone, PIPE_AE_SRV);
            if (checkvb.rc == SRV_SQLNOTFOUND)
            {
                MsgBoxOK(AETXT_NO_CHANGE_IBT);
                return;
            }
        }
    }
    CAUFPOSBUCH checknl;
    checknl.s.POSNR = ptrPos->POSNR;
    checknl.Server(AasrvSpecialPosDone, PIPE_AE_SRV);
    if (checknl.rc == SRV_SQLNOTFOUND)
    {
        MsgBoxOK(AETXT_NO_CHANGE_NL);
        return;
    }

    m_ArtNr = ToString(ptrPos->ARTIKEL_NR);
    CString BestMenge   = ToString(ptrPos->MENGEABGEBUCHT);
    CString NatRabMenge = ToString(ptrPos->MENGENATRA);
    CString NatRabMengeBestellt = ToString(ptrPos->MENGEBESTELLTNATRA);
    m_CPreis.Format("%2.2f", ptrPos->PREISEKAPOFREE);
    m_ArtName = ptrPos->ARTIKEL_NAME;
    m_ArtEinh = ptrPos->EINHEIT;
    CString AufPos = ToString(ptrPos->POSNR);
    AllgEntfSpaces(ptrPos->BEMERKUNG);
    CString Bemerkung = ptrPos->BEMERKUNG;
    if (AeGetApp()->IsBG())
    {
        if ((m_CAufArt == "RO") && AeGetApp()->IsReOpen())
        {
            MsgBoxOK(AETXT_NO_CHANGE_POS);
            return;
        }
        if (m_CAufArt.GetAt(0) == 'S')   //Service-Auftragsart
        {
            if (m_CAufArt.GetAt(1) == '6')
            {
                CDServiceZinsen dlgServiceZinsen;
                dlgServiceZinsen.m_PosNr = atol(AufPos);
                dlgServiceZinsen.m_ptrDoc = ptrDoc;
                dlgServiceZinsen.m_iTax = atoi(ptrPos->MWSTSCHLUESSEL);
                char cStd;
                double dTax;
                AeGetApp()->GetTaxRates(dlgServiceZinsen.m_iTax, cStd, dTax);
                dlgServiceZinsen.m_csPrice.Format("%0.2lf", (ptrPos->PREISEKAPO * (100 + dTax) / 100));
                dlgServiceZinsen.m_csName = ptrPos->ARTIKEL_NAME;
                if (dlgServiceZinsen.DoModal() == IDOK)
                {
                    UpdateListPos(pos, OrdPos);
                }
            }
            else
            {
                CDServicePos dlgServicePos;
                dlgServicePos.m_PosNr = atol(AufPos);
                dlgServicePos.m_ptrDoc = ptrDoc;
                dlgServicePos.m_csQty.Format("%d", ptrPos->MENGEABGEBUCHT);
                dlgServicePos.m_iTax = atoi(ptrPos->MWSTSCHLUESSEL);
                char cStd;
                double dTax;
                AeGetApp()->GetTaxRates(dlgServicePos.m_iTax, cStd, dTax);
                dlgServicePos.m_csPrice.Format("%0.2lf", (ptrPos->PREISEKAPO * (100 + dTax) / 100));
                dlgServicePos.m_csName = ptrPos->ARTIKEL_NAME;
                if (dlgServicePos.DoModal() == IDOK)
                {
                    UpdateListPos(pos, OrdPos);
                }
            }
            return;
        }
        else if ((ptrPos->PROMOTYP == 1) || (ptrPos->PROMOTYP == 2))
        {
            CDPromotionen dlgPromotionen;
            dlgPromotionen.m_sPromoNo = ptrPos->PROMOTION_NO;
            dlgPromotionen.m_lKundennr = AeGetApp()->VzNr_Kunde();
            dlgPromotionen.m_sVznr = m_VzNr;
            dlgPromotionen.m_ptrDoc = ptrDoc;
            dlgPromotionen.m_lMinMeng = ptrPos->BASEQTY;
            dlgPromotionen.m_dMinValue = ptrPos->BASE_VALUE;
            dlgPromotionen.m_cEKG = ptrPos->PHARMACYGROUPID;
            dlgPromotionen.m_lDISCGRP = ptrPos->DISCOUNTGRPNO;
            dlgPromotionen.m_lCustomerno = ptrPos->CUSTOMERNO;
            if (dlgPromotionen.DoModal()== IDOK)
            {
                FillPosList();
                FillList();
            }
            return;
        }
    }
    else if (ptrPos->KZFREITEXT[0] == '1') //Freitextposition
    {
        CDAufFrText dlgAufFrText;
        dlgAufFrText.PosNr  = atol(AufPos);
        dlgAufFrText.ptrDoc = ptrDoc;
        if (dlgAufFrText.DoModal() == IDOK)
        {
            UpdateListPos(pos, OrdPos);
        }
        return;
    }

    CDAufZlBearb dlgAufZlBearb;
    dlgAufZlBearb.m_lKndNr = m_lKndNr;
    if (ptrPos->LINKPOSNR > 0)
    {
        //AUFPOSBUCH* ptrLink = ptrDoc->GetPosition(ptrPos->LINKPOSNR);
        //dlgAufZlBearb.m_AngefMenge      = ptrPos->MENGEBESTELLT + ptrLink->MENGEBESTELLT;
        //dlgAufZlBearb.m_CBestMenge      = ToString((atol(BestMenge) + ptrLink->MENGEABGEBUCHT));
        dlgAufZlBearb.m_AngefMenge      = ptrPos->MENGEBESTELLT;
        dlgAufZlBearb.m_CBestMenge      = ToString(atol(BestMenge));
        dlgAufZlBearb.m_CNatRabMenge    = NatRabMenge;
        if (atol(NatRabMengeBestellt) > 0)
        {
            dlgAufZlBearb.m_CNatRab     = NatRabMengeBestellt;
        }
        else
        {
            dlgAufZlBearb.m_CNatRab     = NatRabMenge;
        }
        //dlgAufZlBearb.m_CVerbundMenge   = ToString((ptrPos->MENGE + ptrLink->MENGE));
        dlgAufZlBearb.m_CVerbundMenge   = ToString(ptrPos->MENGE);
    }
    else
    {
        dlgAufZlBearb.m_AngefMenge      = ptrPos->MENGEBESTELLT;
        dlgAufZlBearb.m_CBestMenge      = BestMenge;
        dlgAufZlBearb.m_CNatRabMenge    = NatRabMenge;
        if (atol(NatRabMengeBestellt) > 0)
        {
            dlgAufZlBearb.m_CNatRab     = NatRabMengeBestellt;
        }
        else
        {
            dlgAufZlBearb.m_CNatRab     = NatRabMenge;
        }
        dlgAufZlBearb.m_CVerbundMenge   = ToString(ptrPos->MENGE);
    }
    dlgAufZlBearb.m_CPreis          = m_CPreis;
    dlgAufZlBearb.m_CArtName        = m_ArtName;
    dlgAufZlBearb.m_CArtEinh        = m_ArtEinh;
    dlgAufZlBearb.m_CArtNr          = m_ArtNr;
    dlgAufZlBearb.m_CArtCode        = ptrPos->ARTICLE_CODE;
    dlgAufZlBearb.m_CVerbundFiliale = ToString(ptrPos->FILIALNR1);
    dlgAufZlBearb.m_CBemerkung      = Bemerkung;
    dlgAufZlBearb.m_BuchStat        = ptrPos->STATUS;
    dlgAufZlBearb.m_Typ             = ptrPos->PREIS_TYP;
    dlgAufZlBearb.m_CAufArt         = m_CAufArt;
    dlgAufZlBearb.m_CPct.Format("%.2lf", ptrPos->DISCOUNTVALUEPCT);
    dlgAufZlBearb.m_CPctMan.Format("%.2lf", ptrPos->DISCOUNTVALPCTMAN);
    dlgAufZlBearb.m_CCharge         = ptrPos->CHARGENNR;
    dlgAufZlBearb.m_CCharge.TrimRight(' ');
    dlgAufZlBearb.m_bFixCharge = (ptrPos->FIXBATCH == 1);
    //alle Auftragsarten prinzipiell NN-fähig ausser s.u.
    dlgAufZlBearb.m_bNN = true;
    if (m_CAufArt == "UW" ||
        m_CAufArt == "AK" ||
        m_CAufArt == "MD" ||
        m_CAufArt == "OM" ||
        m_CAufArt == "UN")
    {
        dlgAufZlBearb.m_bNN = false;
    }
    if (AeGetApp()->IsHR())
    {
        CAUFPOSBUCH checkl;
        checkl.s.KDAUFTRAGNR = m_lAuftrNr;
        checkl.s.POSNR = ptrPos->POSNR;
        checkl.Server(AasrvDiscountMode, PIPE_AE_SRV);
        dlgAufZlBearb.m_CDiscountMode = checkl.s.DISCOUNTMODE;
    }
    if (dlgAufZlBearb.DoModal() == IDOK)
    {
        int PosNr = atol(AufPos);
        if (dlgAufZlBearb.m_AngefMenge > WARN_BUCH_MENGE)
        {
            MsgBoxOK(IDP_WARN_MENGE);
        }
        ptrPos->FEHLERMENGE = dlgAufZlBearb.m_bNN ? (short)dlgAufZlBearb.m_AngefMenge : 0;
        AlterPosition(ptrPos, PosNr, dlgAufZlBearb.m_AngefMenge, atoi(dlgAufZlBearb.m_CBestMenge), dlgAufZlBearb.m_CBemerkung, dlgAufZlBearb.m_BuchStat, dlgAufZlBearb.m_CNatRab, dlgAufZlBearb.m_CPreis, dlgAufZlBearb.m_Typ, dlgAufZlBearb.m_CPctMan, dlgAufZlBearb.m_CCharge, dlgAufZlBearb.m_bFixCharge);
    }
}

void CDAufBear::UpdateListPos(int pos, long OrdPos)
{   //nase Problem insert lösen
    CString cstr;

    AUFPOSBUCH* ptrPos = ptrDoc->GetPosition(OrdPos);
    if (ptrPos->MENGEBESTELLT > WARN_BUCH_MENGE)
        m_bMengWarn = true;
    m_ListCtl->SetItemText(pos, COL_AI_AMGE, ToString(ptrPos->MENGEBESTELLT));
    m_ListCtl->SetItemText(pos, COL_AI_BMGE, ToString(ptrPos->MENGEGELIEFERT + ptrPos->MENGE));
    m_ListCtl->SetItemText(pos, COL_AI_NRME, ToString(ptrPos->MENGENATRA));
    m_ListCtl->SetItemText(pos, COL_AI_NATRABESTELLT, ToString(ptrPos->MENGEBESTELLTNATRA));
    m_ListCtl->SetItemText(pos, COL_AI_VERBME, ToString(ptrPos->MENGE)); //Verbundmenge

    if (m_Tour != CString(ptrPos->TOURID) || ptrPos->DELIVERYDATE > m_lDeliveryDate) // Bei abweichender Tour oder abweichendem Datum Lieferzeit anzeigen
    {
        cstr = DDMMYYYYStringFromDateLong(ptrPos->DELIVERYDATE);
        m_ListCtl->SetItemText(pos, COL_AI_DELIVERYDATE, cstr);
        cstr = HHmmStringFromShortTimeLong(ptrPos->DELIVERYTIME);
        m_ListCtl->SetItemText(pos, COL_AI_DELIVERYTIME, cstr);
    }

    if (ptrPos->MENGE > 0)
    {
        if (ptrPos->IBTTYPEID > 0)   //NLevel-Verbund
        {
            if (ptrPos->IBTTYPEID == 1)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_NATIONAL));
            }
            else if (ptrPos->IBTTYPEID == 2)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_REGIONAL));
            }
            else if (ptrPos->IBTTYPEID == 3)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_LOKAL));
            }
            else // (ptrPos->IBTTYPEID == 4)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_SPEZIAL));
            }
        }
        else
        {
            if (ptrPos->IBTTYPE == 0)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_LOKAL));
            }
            else if (ptrPos->IBTTYPE == 1)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_PRIVATSORTIMENT));
            }
            else if (ptrPos->IBTTYPE == 2)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_VETO));
            }
            else if (ptrPos->IBTTYPE == 3)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_REGIONAL));
            }
            else if (ptrPos->IBTTYPE == 4)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_TAGVERBUND));
            }
            else if (ptrPos->IBTTYPE == 5)
            {
                m_ListCtl->SetItemText(pos, COL_AI_VBTYP, CResString::ex().getStrTblText(AETXT_NATIONAL));
            }
        }

    }
    if (ptrPos->KZAUFGENOMMEN[0] == '1') m_ListCtl->SetItemText(pos, COL_AI_UMGESCHL, CResString::ex().getStrTblText(AETXT_KZ_JA));
    else m_ListCtl->SetItemText(pos, COL_AI_UMGESCHL, "");
    AllgEntfSpaces( ptrPos->EINHEIT );
    m_ListCtl->SetItemText(pos, COL_AI_EINHEIT, ptrPos->EINHEIT);
    if      (ptrPos->STATUS == ITEM_STAT_ZUGESAGT)      cstr = "ZU";
    else if (ptrPos->STATUS == ITEM_STAT_DISPO)         cstr = "DI";
    else if (ptrPos->STATUS == ITEM_STAT_NACHLIEFERN)   cstr = "NL";
    else if (ptrPos->KZINFOTEXT[0] == '1')              cstr = "IT";
    else                                                cstr = "";
    m_ListCtl->SetItemText(pos, COL_AI_FU, cstr);
    AllgEntfSpaces( ptrPos->ARTIKEL_LANGNAME );
    AllgEntfSpaces( ptrPos->ARTIKEL_NAME );
    AllgEntfSpaces( ptrPos->BEMERKUNG );
    if (AeGetApp()->IsBG())
    {
        if (strlen(ptrPos->ARTIKEL_LANGNAME) > 0)
            m_ListCtl->SetItemText(pos, COL_AI_ARTIKELNAME, ptrPos->ARTIKEL_LANGNAME);
        else if (strlen(ptrPos->ARTIKEL_NAME) > 0)
            m_ListCtl->SetItemText(pos, COL_AI_ARTIKELNAME, ptrPos->ARTIKEL_NAME);
        else
            m_ListCtl->SetItemText(pos, COL_AI_ARTIKELNAME, ptrPos->BEMERKUNG);
    }
    else if (strlen(ptrPos->ARTIKEL_NAME) > 0)
            m_ListCtl->SetItemText(pos, COL_AI_ARTIKELNAME, ptrPos->ARTIKEL_NAME);
    else
        m_ListCtl->SetItemText(pos, COL_AI_ARTIKELNAME, ptrPos->BEMERKUNG);
    if (AllgBitleisteN((Bitleiste)ptrPos->ETARTKLASSE1, 6))  // opiat
    {
        CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AI_ARTIKELNAME, LIEFBER_BTM);
    }
    else if (AllgBitleisteN((Bitleiste)ptrPos->ETARTSCHALTER1, 10))  // Kuehlkette
    {
        CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AI_ARTIKELNAME, LIEFBER_KUEHL);
    }
    else if (AllgBitleisteN((Bitleiste)ptrPos->ETARTSCHALTER1, 8))
    {
        CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AI_ARTIKELNAME, LIEFBER_KUEHL_U8);
    }
    else if (AllgBitleisteN((Bitleiste)ptrPos->ETARTSCHALTER1, 9) && AeGetApp()->IsCool20())  // Kuehl unter 20 Grad
    {
        CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AI_ARTIKELNAME, LIEFBER_COOL20);
    }

    AllgEntfSpaces( ptrPos->DARREICHFORM );
    m_ListCtl->SetItemText(pos, COL_AI_DAF, ptrPos->DARREICHFORM);
    AllgEntfSpaces( ptrPos->KURZBEZKONDI );
    m_ListCtl->SetItemText(pos, COL_AI_KENNZEICHEN, ptrPos->KURZBEZKONDI);
    m_ListCtl->SetItemText(pos, COL_AI_PA, ptrPos->POSART);
    if (ptrPos->ARTICLE_CODE[0] == ' ')      // wenn articlecode noch nicht versorgt, dann artikelnr
    {
        m_ListCtl->SetItemText(pos, COL_AI_ARTICLE_CODE, ToString((ptrPos->ARTIKEL_NR)));
    }
    else
    {
        m_ListCtl->SetItemText(pos, COL_AI_ARTICLE_CODE, ptrPos->ARTICLE_CODE);
    }
    m_ListCtl->SetItemText(pos, COL_AI_PNR, ToString(ptrPos->POSNR));
    if (ptrPos->ARTIKEL_NR == -1)
    {
        if (ptrPos->KZAPODINL[0] == ITEM_APO_DISPO)
            m_ListCtl->SetItemText(pos, COL_AI_PZN, CResString::ex().getStrTblText(AETXT_DISPO));
        else if (ptrPos->KZAPODINL[0] == ITEM_APO_NACHL)
            m_ListCtl->SetItemText(pos, COL_AI_PZN, CResString::ex().getStrTblText(AETXT_NACHL));
        else
            m_ListCtl->SetItemText(pos, COL_AI_PZN, " ");
    }
    else    m_ListCtl->SetItemText(pos, COL_AI_PZN, ToString((ptrPos->ARTIKEL_NR)));
    if (AeGetApp()->IsBG())
    {
        double dTax;
        char cStd;
        AeGetApp()->GetTaxRates(ptrPos->TAXLEVEL, cStd, dTax);
        if (ptrPos->ARTIKEL_NR == -1)
        {
            cstr.Format("%.2lf", (ptrPos->PREISEKAPO * (100 + dTax) / 100));
        }
        else
        {
            cstr.Format("%.2lf", (ptrPos->PREISFAKTUR * (100 + dTax) / 100));
            CCHECKLISTE5ZENTRAL cl5z;
            cl5z.SetArtikel_nr(ptrPos->ARTIKEL_NR);
            if (!cl5z.IsListe5())
            {
                CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AI_PREIS, LIEFBER_L5);
            }
            else
            {
                CCHECKLISTE5 cl5;
                cl5.SetBranchno(m_VzNr);
                cl5.SetArticleno(ptrPos->ARTIKEL_NR);
                cl5.SetCustomerno(m_lKndNr);
                if (!cl5.IsListe5())
                {
                    CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AI_PREIS, LIEFBER_L5);
                }
            }
        }

        int kz;
        if (ptrPos->PREIS_TYP == 0)
        {
            kz = AUFTRAG_FV;
        }
        else if (ptrPos->PREIS_TYP == 1)
        {
            kz = AUFTRAG_KK;
        }
        else kz = AUFTRAG_EH;
        CListCtrlHelper::SetImageItemSelected(*m_ListCtl, pos, kz);
    }
    else
    {
        cstr.Format("%.2lf", ptrPos->PREISEKAPO);
    }
    m_ListCtl->SetItemText(pos, COL_AI_PREIS, cstr);
    cstr.Format("%.2lf", ptrPos->DISCOUNTVALUEPCT);
    m_ListCtl->SetItemText(pos, COL_AI_RABATT, cstr);
    cstr.Format("%.2lf", ptrPos->DISCOUNTVALPCTMAN);
    m_ListCtl->SetItemText(pos, COL_AI_RABATT_MAN, cstr);
    m_ListCtl->SetItemText(pos, COL_AI_BEMERK, ptrPos->BEMERKUNG);
    cstr.Format("%.2lf", ptrPos->PREISVKAPO);
    m_ListCtl->SetItemText(pos, COL_AI_AVP, cstr);
    m_ListCtl->SetItemText(pos, COL_AI_CHARGE, ptrPos->CHARGENNR);
    cstr.Format("%d", ptrPos->PROMOTYP);
    m_ListCtl->SetItemText(pos, COL_AI_PROMOTYP, cstr);
    cstr.Format("%d", ptrPos->PROMOTION_NO);
    m_ListCtl->SetItemText(pos, COL_AI_PROMONR, cstr);
    cstr.Format("%d", ptrPos->PHARMACYGROUPID);
    m_ListCtl->SetItemText(pos, COL_AI_PHARMACYGROUPID, cstr);
    cstr.Format("%d", ptrPos->DISCOUNTGRPNO);
    m_ListCtl->SetItemText(pos, COL_AI_DISCOUNTGRPNO, cstr);
    cstr.Format("%d", ptrPos->BASEQTY);
    m_ListCtl->SetItemText(pos, COL_AI_BASEQTY, cstr);
    cstr.Format("%.2lf", ptrPos->BASE_VALUE);
    m_ListCtl->SetItemText(pos, COL_AI_BASE_VALUE, cstr);
    // vbm.s.ARTIKEL_NR = ptrPos->ARTIKEL_NR;  // old-Style. do not use any more
    m_ListCtl->SetItemText(pos, COL_AI_VERBUND, "");
    cstr.Format("%.2lf", ptrPos->PREISFAKTUR);
    m_ListCtl->SetItemText(pos, COL_AI_PREISFAKTUR, cstr);
    if (ptrPos->PROMOTION_NO > 0)
    {
        if (ptrPos->PROMOTYP == 1)
        {
            m_ListCtl->setItemColor(pos, RGB(0, 0, 0), RGB(255, 85, 0));
        }
        else if (ptrPos->PROMOTYP == 2)
        {
            m_ListCtl->setItemColor(pos, RGB(0, 0, 0), RGB(255, 0, 0));
        }
        else
        {
            m_ListCtl->setItemColor(pos, RGB(0, 0, 0), RGB(255, 80, 80));
        }
    }
    if ((ptrPos->ARTIKEL_NR > 0) && ((ptrPos->MENGEABGEBUCHT + ptrPos->MENGENATRA) < ptrPos->MENGEBESTELLT))
    {
        if (m_bKz_Kunde_Verbund)
        {
            CVERBUNDMOEGL vbm;
            vbm.s.ARTIKEL_NR = ptrPos->ARTIKEL_NR;
            vbm.s.FILIALNR = m_VzNr;
            vbm.SelVbBestandNeu();
            if ((vbm.rc == SRV_OK) && (vbm.GetBestand() > 0))
            {
                m_ListCtl->SetItemText(pos, COL_AI_VERBUND, CResString::ex().getStrTblText(AETXT_KZ_JA));
                m_ListCtl->SetItemText(pos, COL_AI_FILI, ToString(vbm.s.FILIALNR));
            }
        }
        if (AeGetApp()->IsPrintCode())
        {
            ppString text;
            CCODEBLOCAGEINFO code;
            code.SetFilialnr(m_VzNr);
            code.SetArtikel_nr(ptrPos->ARTIKEL_NR);
            if (!code.SelText())
            {
                CString cVolltext;
                CString cBemtext;
                code.GetPrintcode(text);
                cBemtext = m_ListCtl->GetItemText(pos, COL_AI_BEMERK);
                cVolltext = text;
                cVolltext += " / ";
                cVolltext += cBemtext;
                m_ListCtl->SetItemText(pos, COL_AI_BEMERK, cVolltext);
            }
        }
    }
    if (ptrPos->PRODUSERQUOTA == 1)
    {
        CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AI_AMGE, PRODUSER_QUOTA);
    }
    if ((ptrPos->ARTIKEL_NR > 0) && AeGetApp()->IsAT())
    {
        CCHECKIMPORTARTICLE checkimport;
        checkimport.SetArtikel_nr(ptrPos->ARTIKEL_NR);
        if (!checkimport.SelImport())
        {
            CListCtrlHelper::SetImageItem(*m_ListCtl, pos, COL_AI_ARTIKELNAME, LIEFBER_DEGETTER);
        }
    }
}

void CDAufBear::AlterPosition(AUFPOSBUCH *ptrPos, int posNr, int menge, int buchmenge, CString bemerkung, int buchStat, CString natRabMenge,
    CString preis, int preisTyp, CString pctMan, CString charge, BOOL fixCharge)
{
    long natraAlt;
    if (GetOrderType().IsNatraAufArt(AeGetApp()->VzNr_Kunde(), m_CAufArt))
    {
        natraAlt = ptrPos->MENGEBESTELLTNATRA;
    }
    else
    {
        natraAlt = ptrPos->MENGENATRA;
    }
    long NatraNeu = atol(natRabMenge);

    CAUFPOSBUCH aufposbuch;
    aufposbuch.s.FEHLERMENGE = ptrPos->FEHLERMENGE;    // Fehlemenge wird für netto-netto misbraucht
    long lMengeBestellt = menge;
    long lMengeAbbuchung;
    if ((buchStat != ITEM_STAT_NORMAL) && (buchStat != ITEM_STAT_ZUGESAGT))
    {
       lMengeAbbuchung = buchmenge;
    }
    else
    {
       lMengeAbbuchung = lMengeBestellt;
    }

    bool bDefMaske = false;
    for (;;)
    {
        if (GetOrderType().IsNatraAufArt(AeGetApp()->VzNr_Kunde(), m_CAufArt))
        {
            aufposbuch.s.MENGENATRA = atol(natRabMenge);
            aufposbuch.s.MENGEBESTELLTNATRA = natraAlt;
        }
        else
        {
            aufposbuch.s.MENGENATRA = 0;
            aufposbuch.s.MENGEBESTELLTNATRA = 0;
        }
        aufposbuch.s.DISCOUNTVALUEPCT  = 0.0;  //nur bei TargetPromo
        aufposbuch.s.MENGEBESTAETIGT   = lMengeAbbuchung;
        aufposbuch.s.MENGEBESTELLT     = lMengeBestellt;
        aufposbuch.s.POSNR             = (long)posNr;
        aufposbuch.s.STATUS            = buchStat;
        aufposbuch.s.PREIS_TYP         = static_cast<short>(preisTyp);
        AllgCStrCharToChar(preis, ',', '.');
        aufposbuch.s.PREISEKAPOFREE = atof(preis);
        aufposbuch.s.DISCOUNTVALPCTMAN = atof(pctMan);
        strcpy(aufposbuch.s.BEMERKUNG, (LPCTSTR)bemerkung);
        strcpy(aufposbuch.s.CHARGENNR, (LPCTSTR)charge);
        aufposbuch.s.FIXBATCH = fixCharge ? 1 : 0;
        BeginWaitCursor();
        aufposbuch.Server(AasrvChangepos, PIPE_AE_SRV);
        EndWaitCursor();
        if (aufposbuch.rc < SRV_OK)
        {
            return;
        }
        if (aufposbuch.s.STATUS == ITEM_STAT_KREDITLIMIT)            //Kreditlimit ueberschritten
        {
            if (AeGetApp()->IsBG())
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
                else
                    return;
            }
        }
        else if (aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE)
        {
            CDBePosBearb dlgBePosBearb;
            dlgBePosBearb.SetKndMussKopfBem(m_bKndMussKopfBem);
            dlgBePosBearb.m_KndNr           = m_lKndNr;
            dlgBePosBearb.m_IdfNr           = m_IdfNr;
            CDVerbBestaet dlgVerbBestaet;
            dlgBePosBearb.m_VerbundZeitKnd    = m_VerbundZeitenKnd;
            dlgVerbBestaet.m_VerbundZeitenKnd  = m_VerbundZeitenKnd;
            dlgVerbBestaet.m_CArtName    = dlgBePosBearb.m_CArtName      = m_ArtName;
            dlgVerbBestaet.m_CArtEinh    = dlgBePosBearb.m_CArtEinh      = m_ArtEinh;
            dlgVerbBestaet.m_CArtNr                          = m_ArtNr;
            dlgBePosBearb.SetArtNr(dlgVerbBestaet.m_CArtNr);
            dlgVerbBestaet.m_CArtCode    = dlgBePosBearb.m_CArtCode      = ptrPos->ARTICLE_CODE;
            dlgVerbBestaet.m_CBestand                        = ToString(aufposbuch.s.BESTAND);
            dlgBePosBearb.SetBestand(dlgVerbBestaet.m_CBestand);
            dlgVerbBestaet.m_VerbMenge                       = aufposbuch.s.MENGE;
            dlgBePosBearb.SetVerbMenge(dlgVerbBestaet.m_VerbMenge);
            dlgVerbBestaet.m_VerbFiliale                     = aufposbuch.s.FILIALNR1;
            dlgBePosBearb.SetVerbFiliale(dlgVerbBestaet.m_VerbFiliale);
            dlgVerbBestaet.m_CDarreichform = dlgBePosBearb.m_CDarreichform = ptrPos->DARREICHFORM;
            if (aufposbuch.s.BESTAND > lMengeBestellt)
            {
                dlgBePosBearb.m_LiefMenge = lMengeBestellt;
                if (natraAlt) //muss eigentlich sein, wenn die Menge nicht ausreicht
                {
                    dlgBePosBearb.m_LiefMengeNatra = aufposbuch.s.BESTAND - dlgBePosBearb.m_LiefMenge;
                }
            }
            else
            {
                dlgBePosBearb.m_LiefMenge = aufposbuch.s.BESTAND;
            }
            dlgBePosBearb.SetBestMenge(lMengeBestellt);
            char str[260];
            if (natraAlt)
                sprintf(str, "%d + %d", lMengeBestellt, natraAlt);
            else
                sprintf(str, "%d", lMengeBestellt);
            dlgVerbBestaet.m_CBestMenge  = str;
            dlgBePosBearb.SetBestMengeStr("%d", lMengeBestellt);
            dlgBePosBearb.m_CBemerkung  = bemerkung;
            dlgBePosBearb.SetPosStat(buchStat);

            //aufposbuch.s.MENGE ist die moegliche Verbundmenge
            if (aufposbuch.s.MENGE > 0 && aufposbuch.s.MENGE + aufposbuch.s.BESTAND >= lMengeBestellt)
            {
                if (dlgVerbBestaet.DoModal() == IDOK)
                {
                    aufposbuch.s.FILIALNR1 = dlgVerbBestaet.m_VerbFiliale;
                    continue; //Position erneut buchen
                }
                else
                {
                    bDefMaske = true;
                }
            }
            else
            {
                bDefMaske = true;
            }

            if (bDefMaske)
            {
                bDefMaske = false;
                dlgBePosBearb.SetBestMengeNatra("%d", natraAlt);
                if (dlgBePosBearb.DoModal() == IDOK)
                {
                    lMengeAbbuchung= dlgBePosBearb.m_Menge;
                    buchStat        = dlgBePosBearb.GetPosStat();
                    bemerkung       = dlgBePosBearb.m_CBemerkung;
                    aufposbuch.s.FILIALNR1 = dlgBePosBearb.GetVerbFiliale();
                    lMengeBestellt = dlgBePosBearb.GetBestMenge();
                    natRabMenge.Format("%d", dlgBePosBearb.m_LiefMengeNatra);
                    if (dlgBePosBearb.GetBestMenge() <= lMengeBestellt)
                    {
                        lMengeBestellt = dlgBePosBearb.GetBestMenge();
                    }
                    continue; //Position erneut buchen
                }
                else
                {
                    return;
                }
            }
        }
        break;
    } //Ende der for(;;)
    long NatraBooked = aufposbuch.s.MENGENATRA;

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
    if (AeGetApp()->IsBG())
    {
        ((CAeFView*)AeGetApp()->m_pViewEing)->m_pDlgKnd->SetAndShowCreditLimitValue1(aufposbuch.s.WERTKL1);
        ((CAeFView*)AeGetApp()->m_pViewEing)->m_pDlgKnd->SetAndShowCreditLimitValue2(aufposbuch.s.WERTKL);
        if (!GetOrderType().IsNatraAufArt(     //Wenn Auftragsart mit Natraeingabe, dann ist der Natraweret beteits richtig gebucht
            AeGetApp()->VzNr_Kunde(), m_CAufArt))
        {
            if (natraAlt != NatraNeu)
            {
                CAUFPOSBUCH rab;
                rab.s.MENGENATRA = NatraNeu;
                rab.s.POSNR = (long)posNr;
                BeginWaitCursor();
                rab.Server(AasrvSetNatra, PIPE_AE_SRV);
                EndWaitCursor();
                aufposbuch.s.MENGENATRA = NatraNeu;
                aufposbuch.s.MENGEGELIEFERT = aufposbuch.s.MENGEGELIEFERT + NatraNeu - NatraBooked;
            }
        }
    }

    //gebuchte Zeile ausgeben
    int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);    //Nummer in der Listbox
    if (pos >= 0)
    {
        long OrdPos = GetAufPos(pos);
        ptrDoc->UpdPosition(OrdPos, aufposbuch.s); //Positionsliste aktualisieren
        UpdateListPos(pos, OrdPos);
    }
    CheckLinkPos(ptrPos->LINKPOSNR);
}

void CDAufBear::OnKeydownListAuftrag(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (OnKeydownList(pNMHDR, pResult, *m_ListCtl, false, false))
    {
        return;
    }

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (pLVKeyDow->wVKey == ' ')
    {
        int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
        if (pos < 0)
        {
            return;
        }
        SetMarked(pos);
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == 226)
    {
        int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
        if (pos < 0)
        {
            return;
        }
        m_ListCtl->SetItemText(pos, COL_AI_UMGESCHL, CResString::ex().getStrTblText(AETXT_KZ_JA));
        SetMarked(pos);
        *pResult = 1L;
        return;
    }
    if (CLetterMan::InAZRange(pLVKeyDow->wVKey))
    {
        MarkListPosChar((int)(pLVKeyDow->wVKey));
        if ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000)
        {
            long lArtikelNr = SelListPos();
            if (lArtikelNr != 0)
            {
                RunArtInfDlg(lArtikelNr);
            }
        }
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == VK_F11)
    {
        long lArtikelNr = SelListPos();
        if (lArtikelNr != 0)
        {
            RunArtInfDlg(lArtikelNr);
        }
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == VK_F9)
    {
        if (SelListPos(&m_lMenge, m_CArtName, m_CArtEinh, m_CArtDarr))
            return;
        m_bArtUebernehmen = TRUE;
        OnCancel();
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == VK_F8)
    {
        if (SelListPos(&m_lMenge, m_CArtName, m_CArtEinh, m_CArtDarr))
            return;
        m_bArtAnschreiben = TRUE;
        OnCancel();
        *pResult = 1L;
        return;
    }
}

void CDAufBear::RunArtInfDlg(long lArtikelNr)
{
    CDArtInf dlgArtInf;
    if (lArtikelNr != 0)
    {
        dlgArtInf.SetArtNr(lArtikelNr);
    }
    dlgArtInf.SetKndNr(m_lKndNr);
    dlgArtInf.SetOrgFilialNr(m_OrgFilNr);
    dlgArtInf.m_CBemerkungKond.Empty();
    if (m_bKndSchwerpunk3)
    {
        dlgArtInf.m_CBemerkungKond = CResString::ex().getStrTblText(AETXT_ARB_KREIS_AKTUELL);
    }
    else
    {
        dlgArtInf.m_bNoPriceGroup2 = TRUE;
    }
    if (m_bKndSchwerpunk5)
    {
        if (!dlgArtInf.m_CBemerkungKond.IsEmpty())
        {
            dlgArtInf.m_CBemerkungKond += " / ";
        }
        dlgArtInf.m_CBemerkungKond += CResString::ex().getStrTblText(AETXT_DIABETES);
    }
    else
    {
        dlgArtInf.m_bNoPriceGroup3 = TRUE;
    }
    dlgArtInf.DoModal();
}

void CDAufBear::MarkListPosChar(int Letter)
{
    int pos;
    if (CListCtrlHelper::GetListPositionByChar(*m_ListCtl, Letter, pos))
    {
        MarkListPos(pos);
    }
}

void CDAufBear::MarkListPos(int pos)
{
    CListCtrlHelper::SetFocusSelectedFocusedVisible(*m_ListCtl, pos);
}

long CDAufBear::SelListPos(long* Menge, CString& ArtName, CString& ArtEinh, CString& ArtDarr)
{
    int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString str1 = m_ListCtl->GetItemText(pos, COL_AI_PZN);
        CString str2 = m_ListCtl->GetItemText(pos, COL_AI_AMGE);
        ArtName = m_ListCtl->GetItemText(pos, COL_AI_ARTIKELNAME);
        ArtEinh = m_ListCtl->GetItemText(pos, COL_AI_EINHEIT);
        ArtDarr = m_ListCtl->GetItemText(pos, COL_AI_DAF);
        *Menge  = atol(str2);
        return atol(str1);
    }
    return -1L;
}

long CDAufBear::SelListPos()
{
    int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString str1 = m_ListCtl->GetItemText(pos, COL_AI_PZN);
        return atol(str1);
    }
    return -1L;
}

void CDAufBear::OnDblclkListAuftrag(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    ChangePos();
    *pResult = 0L;
}

void CDAufBear::OnChangeEditPosition()
{
    CString str;

    m_EditPosNr.GetWindowText(str);
    if (str.IsEmpty( ))                                 //Feld ist leer
        return;
    char chN = str[ str.GetLength() - 1 ];              //letztes Zeichen lesen
    if (isdigit((int)chN))
    {
        AllgWertKontr(&m_EditPosNr, MAXIMUM_ANZ_POS);
        return;
    }                                               //Kein Ende der Eingabe
    str = str.Left( str.GetLength() -1 );           //letztes Zeichen löschen
    m_EditPosNr.SetWindowText(str);                 //String zurückschreiben
    if ((chN >= AeGetApp()->Letter_A()) && (chN <= AeGetApp()->Letter_Z()))
    {
        MarkListPosChar((int)chN);
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDAufBear::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    if (m_bDefektAnzeige)
    {
        if (((LPMSG)lpMsg)->wParam == VK_F2)
        {
            ((CAeFView*)AeGetApp()->m_pViewEing)->PostMessage(WM_COMMAND, ID_AUFTR_BEARB);
            CDialogMultiLang::OnOK();
            return 1L;
        }
        else if (((LPMSG)lpMsg)->wParam == VK_F3)
        {
            ((CAeFView*)AeGetApp()->m_pViewEing)->PostMessage(WM_COMMAND, ID_AUFTR_DEF);
            CDialogMultiLang::OnOK();
            return 1L;
        }
        else if (((LPMSG)lpMsg)->wParam == VK_F4)
        {
            ((CAeFView*)AeGetApp()->m_pViewEing)->PostMessage(WM_COMMAND, ID_AUFTRAG_SAVE);
            CDialogMultiLang::OnOK();
            return 1L;
        }
    }
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        CKndInf dlgKndInf;
        if (m_lKndNr != 0)
            dlgKndInf.SetIdfNr(m_lKndNr);
        dlgKndInf.SetKndVz(m_VzNr);
        dlgKndInf.DoModal();
        return 1L;
    }
    else if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        long lArtikelNr = 0;
        int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString sPzn = m_ListCtl->GetItemText(pos, COL_AI_PZN);
            lArtikelNr = atol(sPzn);
        }
        RunArtInfDlg(lArtikelNr);
        return 1L;
    }
    return 0L;
}

void CDAufBear::OnChangeEditSuchbez()
{
    AllgLaengeKontr(&m_EditSuchBez, L_ARTSEL_ARTIKEL_NAME, AeGetApp()->Modus());
}

void CDAufBear::OnCheckDefDafue()
{
    m_bDefSelDfDef = IsDlgButtonChecked(IDC_CHECK_DEF_DAFUE) ? TRUE : FALSE;
    FillList();
}

void CDAufBear::OnCheckDefPhon()
{
    m_bDefSelPhonDef = IsDlgButtonChecked(IDC_CHECK_DEF_PHON) ? TRUE : FALSE;
    FillList();
}

void CDAufBear::OnCheckFtDafue()
{
    m_bDefSelDfFrText = IsDlgButtonChecked(IDC_CHECK_FT_DAFUE) ? TRUE : FALSE;
    FillList();
}

void CDAufBear::OnCheckFtPhon()
{
    m_bDefSelPhonFrText = IsDlgButtonChecked(IDC_CHECK_FT_PHON) ? TRUE : FALSE;
    FillList();
}

void CDAufBear::OnButtonDruck()
{
    char underline[96 + 1];
    memset(underline, ' ', 10);
    memset(underline + 10, '-', 86);
    underline[10 + 86] = '\0';

    CKNDSEL knd;
    knd.s.IDFNR = m_IdfNr;
    knd.s.KUNDENNR = m_lKndNr;
    knd.s.VERTRIEBSZENTRUMNR = m_VzNr;
    knd.s.SKDKUNDEAEGESPERRT[0] = '1';
    BeginWaitCursor();
    knd.Server(AakundeSel_kndnr);
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();

    CString liste;
    CString Str;
    char Out1[10 + 1];
    char Out2[10 + 1];
    this->GetWindowText(Str);
    liste.Format("          %s     % 30s% 24s %s",
        AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, Out1),
        Str.GetString(),
        CResString::ex().getStrTblText(AETXT_STAND_UM).GetString(),
        AllgZeitLong2CharHHMMSS(zeit.s.ZEIT, Out2));

    CDruckAuftrag druckAuftrag;
    druckAuftrag.AddKopfZeile(liste);
    liste.Format("          %s: %s   %s: %s",
        CResString::ex().getStrTblText(AETXT_APOTHEKENNAME).GetString(),
        knd.s.NAMEAPO,
        CResString::ex().getStrTblText(AETXT_ORT).GetString(),
        knd.s.ORT);
    druckAuftrag.AddKopfZeile(liste);
    liste.Format("          %s %ld        %s: %ld",
        CResString::ex().getStrTblText(AETXT_KUNDEN_NR).GetString(),
        m_IdfNr,
        CResString::ex().getStrTblText(AETXT_AUFTRZ).GetString(),
        m_lAuftrNr);
    druckAuftrag.AddKopfZeile(liste);
    if (m_bDefektAnzeige)
    {
        const CString sDistance = "         ";

        liste = "          ";
        if (m_bDefSelVerbund)
        {
            GetDlgItem(IDC_CHECK_VERBUND)->GetWindowText(Str);
            Str.Remove('&');
            liste += Str;
            liste += sDistance;
        }
        if (m_bDefSelDfDef)
        {
            GetDlgItem(IDC_CHECK_DEF_DAFUE)->GetWindowText(Str);
            Str.Remove('&');
            liste += Str;
            liste += sDistance;
        }
        if (m_bDefSelPhonDef)
        {
            GetDlgItem(IDC_CHECK_DEF_PHON)->GetWindowText(Str);
            Str.Remove('&');
            liste += Str;
            liste += sDistance;
        }
        if (m_bDefSelDfFrText)
        {
            GetDlgItem(IDC_CHECK_FT_DAFUE)->GetWindowText(Str);
            Str.Remove('&');
            liste += Str;
            liste += sDistance;
        }
        if (m_bDefSelPhonFrText)
        {
            GetDlgItem(IDC_CHECK_FT_PHON)->GetWindowText(Str);
            Str.Remove('&');
            liste += Str;
        }
        druckAuftrag.AddKopfZeile(liste);
    }
    liste.Format("          % 4s% 4s% 4s% 4s % 8s %-9s%4s %-30s%4s% 4s% 4s% 4s % 9s",
        CResString::ex().getStrTblText(AETXT_AMGE).GetString(),
        CResString::ex().getStrTblText(AETXT_BMGE).GetString(),
        CResString::ex().getStrTblText(AETXT_NRME).GetString(),
        CResString::ex().getStrTblText(AETXT_VERBME).GetString(),
        CResString::ex().getStrTblText(AETXT_ART_UMGESCHL).GetString(),
        CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
        CResString::ex().getStrTblText(AETXT_FU).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTIKELNAME).GetString(),
        CResString::ex().getStrTblText(AETXT_DAF).GetString(),
        CResString::ex().getStrTblText(AETXT_KZ_KENNZEICHEN).GetString(),
        CResString::ex().getStrTblText(AETXT_PA).GetString(),
        CResString::ex().getStrTblText(AETXT_PNR).GetString(),
        CResString::ex().getStrTblText(AETXT_PZN).GetString());
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(" ");         // Leerzeile

    Str = "          ";
    Str += CResString::ex().getStrTblText(AETXT_SEITE);
    Str += "%d";
    liste.Format("%s% 57.57s", Str.GetString(), theApp.FilialName().GetString());
    druckAuftrag.AddFussZeile(liste);

    int maxpos = m_ListCtl->GetItemCount();

    for (int pos = 0; pos < maxpos; pos++)
    {
        liste.Format("          % 4s% 4s% 4s% 4s % 8s %-9s%4s %-30s%4s% 4s% 4s% 4s % 9s",
            m_ListCtl->GetItemText(pos, COL_AI_AMGE).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_BMGE).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_NRME).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_VERBME).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_UMGESCHL).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_EINHEIT).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_FU).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_ARTIKELNAME).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_DAF).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_KENNZEICHEN).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_PA).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_PNR).GetString(),
            m_ListCtl->GetItemText(pos, COL_AI_ARTICLE_CODE).GetString());
        druckAuftrag.AddPosZeile(liste);
        Str = m_ListCtl->GetItemText(pos, COL_AI_BEMERK);
        if (!Str.IsEmpty())
        {
            liste.Format("          %s: %-90s",
                CResString::ex().getStrTblText(IDS_BEMERK).GetString(),
                m_ListCtl->GetItemText(pos, COL_AI_BEMERK).GetString());
            druckAuftrag.AddPosZeile(liste);
        }
    }
    druckAuftrag.Druck(TRUE);
    druckAuftrag.DelAllData();
}

void CDAufBear::SetMarked(int pos)
{
    int nextpos = pos + 1;

    if (m_bDafueKz)
    {
        int index = GetAufPos(pos);
        AUFPOSBUCH* ptrPos = ptrDoc->GetPosition(index);
        CListCtrlHelper::SetImageItemSelected(*m_ListCtl, pos, DONE_YES);

        MarkListPos(nextpos);

        CAUFPOSNACH aufposnach;
        aufposnach.s.KZAUFGENOMMEN[0] = '0';
        aufposnach.s.KZAUFGENOMMEN[1] = '\0';
        if (m_ListCtl->GetItemText(pos, COL_AI_UMGESCHL) ==  CResString::ex().getStrTblText(AETXT_KZ_JA))
            aufposnach.s.KZAUFGENOMMEN[0] = '1';
        if ((ptrPos->KZNACHBEARB[0] == '0') && (aufposnach.s.KZAUFGENOMMEN[0] == ptrPos->KZAUFGENOMMEN[0]))
            return;    // bereits gekennzeichnet
        ptrPos->KZNACHBEARB[0] = '0';
        aufposnach.s.KZNACHBEARB[0] = '0';
        aufposnach.s.KZNACHBEARB[1] = '\0';
        aufposnach.s.POSNR = ptrPos->POSNR;
        aufposnach.Server(AasrvChangeKzNachBearb, PIPE_AE_SRV);
        int anz = m_ListCtl->GetItemCount();
        int i;
        for (i = 0; i < anz; i++)
        {
            index = GetAufPos(i);
            ptrPos = ptrDoc->GetPosition(index);
            if (ptrPos->KZNACHBEARB[0] == '1') break;
        }
        if (i == anz)
        {
            m_CBVerbund.EnableWindow(TRUE);
            m_CBDefDafue.EnableWindow(TRUE);
            m_CBDefPhon.EnableWindow(TRUE);
            m_CBFtDafue.EnableWindow(TRUE);
            m_CBFtPhon.EnableWindow(TRUE);
            m_bDafueKz = false;
        }
    }
    else
    {
        MarkListPos(nextpos);
    }
}

void CDAufBear::FillPosList()
{
    BeginWaitCursor();
    ptrDoc->DelPosListe();              //Loeschen der Positionsliste
    for (;;)
    {
        CAUFPOSBUCH aufposbuch;
        memset(&aufposbuch.s, 0, sizeof(struct AUFPOSBUCH));
        aufposbuch.Server(AasrvSelpos, PIPE_AE_SRV);
        if (aufposbuch.rc != SRV_OK)
            break;
        ptrDoc->AddPosition(aufposbuch.s);
    }
    ptrDoc->m_bAllItemsInList = true;
    GetDlgItem(IDC_BUTTON_ALL_POS)->ShowWindow(FALSE);
    MarkListPos(0);
    EndWaitCursor();
}

void CDAufBear::OnButtonAllPos()
{
    FillPosList();
    FillList();
}

void CDAufBear::OnCheckVerbund()
{
    if (IsDlgButtonChecked(IDC_CHECK_VERBUND)) m_bDefSelVerbund = TRUE;
    else m_bDefSelVerbund = FALSE;
    FillList();
}

void CDAufBear::OnDestroy()
{
    WriteColumnWidthUser(m_ListCtl, "CDaufBearb", KEY_PATH, COL_AI_ANZ_LIST);
    AeGetApp()->m_AeLogging.WriteLine(2, "DaufBearb.cpp", "OnDestroy", "beendet");
    CDialogMultiLang::OnDestroy();
}

// Vom User eingestellte Spaltenbreiten aus Win-DB
void CDAufBear::SetColumnWidthUser(CListCtrl* lc, char* name, char* keypath, int anz)
{
    HKEY hKey;
    if (RegOpenKey(HKEY_CURRENT_USER, keypath, &hKey) == ERROR_SUCCESS)
    {
        char szBuffer[250 + 1];
        DWORD len = sizeof(szBuffer) - 1;
        long xx = RegQueryValueEx(hKey, name, 0, NULL, (BYTE*)szBuffer, &len);
        if (xx == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            CString Spalten = szBuffer;
            for (int i = 0; i < anz ; i++)
            {
                int width;
                if (sscanf(Spalten, "%d", &width) == 0) break;
                lc->SetColumnWidth(i, width);
                int pos = Spalten.Find(", ");
                if (pos == -1) break;
                Spalten = Spalten.Right(Spalten.GetLength() - pos - 2);
            }
        }
        RegCloseKey(hKey);
    }
}

// Vom User eingestellte Spaltenbreiten in Win-DB
void CDAufBear::WriteColumnWidthUser(CListCtrl* lc, char* name, char* keypath, int anz)
{
    CString sBuffer;
    for (int i = 0; i < anz ; i++)
    {
        if (i == 0) sBuffer.Format("%d", lc->GetColumnWidth(i));
        else
        {
            CString sNext;
            sNext.Format(", %d", lc->GetColumnWidth(i));
            sBuffer += sNext;
        }
    }
    HKEY hKey;
    if (RegCreateKey(HKEY_CURRENT_USER, keypath, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        RegSetValueEx(hKey, name, 0, REG_SZ, (BYTE *)sBuffer.operator LPCTSTR(), sBuffer.GetLength());
        RegCloseKey(hKey);
    }
}

void CDAufBear::CheckLinkPos(int linkpos)
{
    if (linkpos == 0)
        return;
    bool found = false;

    CAUFPOSBUCH kettPos;
    kettPos.s.POSNR = linkpos;
    kettPos.Server(AasrvInfposnr, PIPE_AE_SRV);
    if (kettPos.rc != SRV_OK)
        return;

    AUFPOSBUCH *ptrPos = ptrDoc->GetPosListe(); //Zeiger auf Beginn der Liste

    for (; ptrPos != NULL; ptrPos = (AUFPOSBUCH*)(ptrPos->FETCH_REL))
    {
        if (ptrPos->POSNR == kettPos.s.POSNR)
        {
            ptrDoc->UpdPosition(kettPos.s.POSNR, kettPos.s);
            int max = m_ListCtl->GetItemCount();
            for (int pos = 0; pos < max; pos++)
            {
                CString str = m_ListCtl->GetItemText(pos, COL_AI_PNR);

                if (atol(str) == kettPos.s.POSNR)
                {
                    found = true;
                    UpdateListPos(pos, kettPos.s.POSNR); //vorhandenen Eintrag aendern
                    break;
                }
            }
        }
    }
    if (!found)  //wenn keine Position gefunden, dann einfuegen neue
    {
        ptrDoc->AddPosition(kettPos.s);
        FillList();
    }
}

void CDAufBear::SelArtNo()
{
    AUFPOSBUCH* ptrPos = ptrDoc->GetPosListe(); //Zeiger auf Beginn der Liste

    m_ListCtl->DeleteAllItems();

    char str[81];
    strcpy(str, m_CArticleCode);
    AllgEntfAllSpaces(str);
    m_CArticleCode = str;

    CLetterMan kb;
    for (; ptrPos != NULL; ptrPos = (AUFPOSBUCH*)(ptrPos->FETCH_REL))
    {
        if (ptrPos == NULL)
            break;

        CString str1 = ptrPos->ARTICLE_CODE;
        //Leerzeichen entfernen
        strcpy(str, str1);
        AllgEntfAllSpaces(str);
        str1 = str;
        CString str2 = str1.Left(m_CArticleCode.GetLength());
        if (str2 == m_CArticleCode)
        {
            int index = m_ListCtl->GetItemCount();
            if (m_ListCtl->InsertItem(index, kb.Next()) == -1)
                return ;
            UpdateListPos(index, ptrPos->POSNR);
        }
    }
    if (m_ListCtl->GetItemCount() > 0)
        MarkListPos(0);
}

CString CDAufBear::ToString(long lValue)
{
    char str[260];
    return _ltoa(lValue, str, 10);
}
