// DNachlBearb.cpp : implementation file
//

#include "stdafx.h"
#include "AeFView.h"
#include "DNachlBearb.h"
#include "DVerbBestaet.h"
#include <nachlief.h>
#include "nachlprot.h"
#include <nachlart.h>
#include "DBePosBearb.h"

#define ZEILEN 12    /* *** Anzahl der Zeilen der Listbox *** */
#define AENDTYP_DELETE 1
#define AENDTYP_MENGENAENDERUNG 2
#define AENDTYP_LIEFERMOEGLICHKEIT 3

//Definitionen Buchen
#define BUCHEN_YES  0
#define BUCHEN_NO   1

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB           0
#define COL_ARTCODE      1
#define COL_MENGE        2
#define COL_MENGE_ALT    3
#define COL_POS          4
#define COL_EINHEIT      5
#define COL_NAME         6
#define COL_DAF          7
#define COL_BESTAND      8
#define COL_POSTYP       9
#define COL_NETTO        10
#define COL_CODE_TYPE    11
#define COL_PZN          12
#define COL_VALUEPCT     13
#define COL_MENGEBESTLLT 14
#define COL_PREIS_TYP    15
#define NUM_COLUMNS      16

static COLUMNS_TYPES Columns[] =
{
    COL_KB,           "",  30, LVCFMT_LEFT,
    COL_ARTCODE,      "",  70, LVCFMT_RIGHT,
    COL_MENGE,        "",  50, LVCFMT_RIGHT,
    COL_MENGE_ALT,    "",  63, LVCFMT_RIGHT,
    COL_POS,          "",  35, LVCFMT_RIGHT,
    COL_EINHEIT,      "",  60, LVCFMT_RIGHT,
    COL_NAME,         "", 172, LVCFMT_LEFT,
    COL_DAF,          "",  40, LVCFMT_CENTER,
    COL_BESTAND,      "",  50, LVCFMT_RIGHT,
    COL_POSTYP,       "",  50, LVCFMT_RIGHT,
    COL_NETTO,        "",  70, LVCFMT_RIGHT,
    COL_CODE_TYPE,    "",   0, LVCFMT_RIGHT,
    COL_PZN,          "",   0, LVCFMT_RIGHT,
    COL_VALUEPCT,     "",   0, LVCFMT_RIGHT,
    COL_MENGEBESTLLT, "",   0, LVCFMT_RIGHT,
    COL_PREIS_TYP,    "",   0, LVCFMT_RIGHT,
    -1,               "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDNachlBearb dialog


CDNachlBearb::CDNachlBearb(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDNachlBearb::IDD, pParent), CPageBrowser(0)
{
    ptrDoc        = NULL;   //Zeiger auf das Dokument
    m_lKndNr      = 0;
    m_IdfNr       = 0;
    m_lAuftrNr    = 0;
    m_AArt        = _T("");

    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_ARTCODE].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[COL_MENGE].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[COL_MENGE_ALT].Columns = CResString::ex().getStrTblText(AETXT_MENGE_ALT);
    Columns[COL_POS].Columns = CResString::ex().getStrTblText(AETXT_POS);
    Columns[COL_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[COL_NAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[COL_DAF].Columns = CResString::ex().getStrTblText(AETXT_DAF);
    Columns[COL_BESTAND].Columns = CResString::ex().getStrTblText(AETXT_BEST);
    Columns[COL_POSTYP].Columns = CResString::ex().getStrTblText(AETXT_POSTYP);
    Columns[COL_NETTO].Columns = CResString::ex().getStrTblText(AETXT_NETTO);
    Columns[COL_PZN].Columns = CResString::ex().getStrTblText(AETXT_PZN);
}


void CDNachlBearb::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDNachlBearb, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDNachlBearb message handlers

BOOL CDNachlBearb::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    //CenterWindow();

    startpos = NULL;

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_YES);
    idResources.push_back(IDI_ICON_NOT);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    if (!GetPage()) CDialogMultiLang::EndDialog(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDNachlBearb::GetPage(const int /*nKzUpDown=NEXT_PG*/)
{
    //Variablen
    CNACHLART nachlart;
    NACHLART sNachlart;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    struct nachladr* newpos;
    struct nachladr* oldpos;
    struct satzadr* actpos;

    //Anfangsinitialisierung durchfuehren
    nachlart.s.FETCH_REL = 1;          //normaler Fetch
    nachlart.s.IDFNR = m_IdfNr;

    //Filialnr1 wird misbraucht zur Übergabe der Ursprungsfiliale des Kunden
    if (((CAeFView*)AeGetApp()->m_pViewEing)->GetOrgFilNr() > 0) nachlart.s.FILIALNR1 = ((CAeFView*)AeGetApp()->m_pViewEing)->GetOrgFilNr();
    else nachlart.s.FILIALNR1 = m_VzNr;

    nachlart.s.VERTRIEBSZENTRUMNR = m_VzNr;
    strncpy(nachlart.s.KDAUFTRAGART, m_AArt, 2);
    nachlart.s.STATUS = AeGetApp()->IsNlSofort() ? 1 : 0;
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    nachlart.Server(AaauftSel_nachlart);
    m_bCursorOpen = true;       //Datenbankcurser offen
    if (nachlart.rc == SRV_SQLNOTFOUND)
    {
        CloseCursor();
        EndWaitCursor();
        return false;
    }
    m_bFirstDataset = false;
    sNachlart.ARTIKEL_NR = nachlart.s.ARTIKEL_NR;
    sNachlart.MENGE = nachlart.s.MENGE;
    sNachlart.BESTAND = nachlart.s.BESTAND;
    sNachlart.POSTYP = nachlart.s.POSTYP;
    sNachlart.PREISEKAPONETTO = nachlart.s.PREISEKAPONETTO;
    sNachlart.POSNR = 1;          //Anzahl Positionen
    strcpy(sNachlart.DARREICHFORM, nachlart.s.DARREICHFORM);
    strcpy(sNachlart.EINHEIT, nachlart.s.EINHEIT);
    strcpy(sNachlart.ARTIKEL_NAME, nachlart.s.ARTIKEL_NAME);
    sNachlart.CODE_TYPE = nachlart.s.CODE_TYPE;
    AllgEntfSpaces(nachlart.s.ARTICLE_CODE);
    strcpy(sNachlart.ARTICLE_CODE, nachlart.s.ARTICLE_CODE);
    sNachlart.DISCOUNTVALUEPCT = nachlart.s.DISCOUNTVALUEPCT;
    sNachlart.MENGEBESTELLT = nachlart.s.MENGEBESTELLT;
    sNachlart.PREIS_TYP = nachlart.s.PREIS_TYP;
    newpos = (struct nachladr*)malloc(sizeof(struct nachladr));
    startpos = newpos;
    newpos->artikel_nr = nachlart.s.ARTIKEL_NR;
    newpos->folgpos = NULL;
    actpos = (struct satzadr*)malloc(sizeof(struct satzadr));
    newpos->satzpos = actpos;
    actpos->kdauftragnr = nachlart.s.KDAUFTRAGNR;
    actpos->posnr = nachlart.s.POSNR;
    actpos->datum = nachlart.s.DATUM;
    actpos->postyp = nachlart.s.POSTYP;
    actpos->nextpos = NULL;
    CLetterMan kb;
    for (int i = 0; ; i++)
    {
        nachlart.Server(AaauftSel_nachlart);
        nachlart.s.FETCH_REL = 1;          //normaler Fetch
        if (nachlart.rc == SRV_OK)
        {
            oldpos = newpos;
            newpos = (struct nachladr*)malloc(sizeof(struct nachladr));
            oldpos->folgpos = newpos;
            newpos->artikel_nr = nachlart.s.ARTIKEL_NR;
            newpos->folgpos = NULL;
            actpos = (struct satzadr*)malloc(sizeof(struct satzadr));
            newpos->satzpos = actpos;
            actpos->kdauftragnr = nachlart.s.KDAUFTRAGNR;
            actpos->posnr = nachlart.s.POSNR;
            actpos->datum = nachlart.s.DATUM;
            actpos->postyp = nachlart.s.POSTYP;
            actpos->preisekaponetto = nachlart.s.PREISEKAPONETTO;
            actpos->nextpos = NULL;
        }
        if (nachlart.rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        m_bFirstDataset = false;
        InsList(kb.Next(), &sNachlart, s);
        sNachlart.ARTIKEL_NR = nachlart.s.ARTIKEL_NR;
        sNachlart.MENGE = nachlart.s.MENGE;
        sNachlart.BESTAND = nachlart.s.BESTAND;
        sNachlart.POSTYP = nachlart.s.POSTYP;
        sNachlart.PREISEKAPONETTO = nachlart.s.PREISEKAPONETTO;
        sNachlart.POSNR = 1;      //Anzahl Positionen
        strcpy(sNachlart.DARREICHFORM,nachlart.s.DARREICHFORM);
        strcpy(sNachlart.EINHEIT,nachlart.s.EINHEIT);
        strcpy(sNachlart.ARTIKEL_NAME,nachlart.s.ARTIKEL_NAME);
        sNachlart.CODE_TYPE = nachlart.s.CODE_TYPE;
        strcpy(sNachlart.ARTICLE_CODE,nachlart.s.ARTICLE_CODE);
        sNachlart.DISCOUNTVALUEPCT = nachlart.s.DISCOUNTVALUEPCT;
        sNachlart.MENGEBESTELLT = nachlart.s.MENGEBESTELLT;
        sNachlart.PREIS_TYP = nachlart.s.PREIS_TYP;
    } //Ende der for()-Schleife
    InsList(kb.Next(), &sNachlart, s);
    selectpos = 0;
    CloseCursor();
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return true;
}

BOOL CDNachlBearb::InsList(char* kb, struct NACHLART *nachlart, class CStringArray &s)
{
    CString CStr;
    //Ausgabe in die Listbox
    s[COL_KB] = kb;
    CStr.Format("%ld", nachlart->ARTIKEL_NR);
    s[COL_PZN] = CStr;
    CStr.Format("%ld", nachlart->MENGE);
    s[COL_MENGE] = CStr;
    s[COL_MENGE_ALT] = CStr;
    CStr.Format("%d", nachlart->POSNR);
    s[COL_POS] = CStr;
    s[COL_EINHEIT] = nachlart->EINHEIT;
    s[COL_NAME] = nachlart->ARTIKEL_NAME;
    s[COL_DAF] = nachlart->DARREICHFORM;
    CStr.Format("%ld", nachlart->BESTAND);
    s[COL_BESTAND] = CStr;
    CStr.Format("%d", nachlart->POSTYP);
    s[COL_POSTYP] = CStr;
    CStr.Format("%0.2lf", nachlart->PREISEKAPONETTO);
    s[COL_NETTO] = CStr;
    CStr.Format("%d", nachlart->CODE_TYPE);
    s[COL_CODE_TYPE] = CStr;
    s[COL_ARTCODE] = nachlart->ARTICLE_CODE;
    CStr.Format("%0.2lf", nachlart->DISCOUNTVALUEPCT);
    s[COL_VALUEPCT] = CStr;
    CStr.Format("%ld", nachlart->MENGEBESTELLT);
    s[COL_MENGEBESTLLT] = CStr;
    CStr.Format("%d", nachlart->PREIS_TYP);
    s[COL_PREIS_TYP] = CStr;

    if (!CListCtrlHelper::AppendImageItem(m_ListCtl, NUM_COLUMNS, s, BUCHEN_YES))
    {
        EndWaitCursor();
        return FALSE;
    }
    return TRUE;
}

void CDNachlBearb::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
    struct nachladr* newpos;
    struct nachladr* actpos;
    struct satzadr* freepos;
    struct satzadr* merkpos;
    if (startpos == NULL) return;
    for (actpos = startpos;;)
    {
        newpos = actpos->folgpos;
        for (freepos = actpos->satzpos;;)
        {
            merkpos = freepos->nextpos;
            free(freepos);
            if (merkpos == NULL) break;
            freepos = merkpos;
        }
        free(actpos);
        if (newpos == NULL) break;
        actpos = newpos;
    }
}

void CDNachlBearb::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CNACHLART nachlart;
    nachlart.s.FETCH_REL = 0;
    BeginWaitCursor();
    nachlart.Server(AaauftSel_nachlart);
    EndWaitCursor();
    ResetCursor();
}

void CDNachlBearb::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        SelectEintrag();
        return;
    }
}

void CDNachlBearb::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (atoi(m_ListCtl.GetItemText(pos, COL_POSTYP)) == 5) return; /* reservierte nicht mehr ändern */
        CDNachlArtAen dlgNachlArtAen;
        dlgNachlArtAen.m_CBestand = m_ListCtl.GetItemText(pos, COL_BESTAND);
        dlgNachlArtAen.m_CPzn = m_ListCtl.GetItemText(pos, COL_PZN);
        dlgNachlArtAen.m_CName = m_ListCtl.GetItemText(pos, COL_NAME);
        dlgNachlArtAen.m_CEinheit = m_ListCtl.GetItemText(pos, COL_EINHEIT);
        dlgNachlArtAen.m_CDarr = m_ListCtl.GetItemText(pos, COL_DAF);
        dlgNachlArtAen.m_CMenge = m_ListCtl.GetItemText(pos, COL_MENGE);
        dlgNachlArtAen.m_CMengeAlt = m_ListCtl.GetItemText(pos, COL_MENGE_ALT);
        dlgNachlArtAen.m_CType = m_ListCtl.GetItemText(pos, COL_CODE_TYPE);
        dlgNachlArtAen.m_CCode = m_ListCtl.GetItemText(pos, COL_ARTCODE);
        if (dlgNachlArtAen.DoModal() == IDCANCEL) return;
        CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, BUCHEN_YES);
        m_ListCtl.SetItemText(pos, COL_MENGE, dlgNachlArtAen.m_CMenge);
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDNachlBearb::OnHookFkt( WPARAM /*wParam*/, LPARAM /*lpMsg*/ )
{
    return 0;
}

void CDNachlBearb::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDNachlBearb::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (OnKeydownList(pNMHDR, pResult, m_ListCtl, false, false))
    {
        return;
    }

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InAZRange(pLVKeyDow->wVKey))
    {
        MarkListPosChar((int)(pLVKeyDow->wVKey));
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == ' ')
    {
        UpdBearbkz(m_ListCtl.GetNextItem(-1, LVNI_SELECTED));
        *pResult = 1L;
        return;
    }
}

void CDNachlBearb::MarkListPosChar(int Letter)
{
    int pos;
    if (CListCtrlHelper::GetListPositionByChar(m_ListCtl, Letter, pos))
    {
        if (pos == m_ListCtl.GetNextItem(-1, LVNI_SELECTED))
        {
            UpdBearbkz(pos);
        }
        else
        {
            MarkListPos(pos);
        }
    }
}

void CDNachlBearb::MarkListPos(int pos)
{
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, pos);
    selectpos = pos;
}

void CDNachlBearb::OnClickList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos == selectpos)
        UpdBearbkz(pos);
    selectpos = pos;
    *pResult = 0L;
}

//Aktualisierung der Bestandsinformation nach einer Buchung
void CDNachlBearb::UpdBearbkz(int pos)
{
    if (atoi(m_ListCtl.GetItemText(pos, COL_POSTYP)) == 5) return; /* reservierte nicht mehr ändern */
    int kz = (CListCtrlHelper::GetImage(m_ListCtl, pos) == BUCHEN_YES) ? BUCHEN_NO : BUCHEN_YES;
    CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, kz);
}

void CDNachlBearb::OnButtonUpd()
{
    CAUFPOSBUCH aufposbuch;
    CNACHLPROT nachlprot;
    int max = m_ListCtl.GetItemCount();
    nachladr* actpos = startpos;
    BeginWaitCursor();
    for (int pos = 0; pos < max; pos++, actpos = actpos->folgpos)
    {
        long AltStat = 0;
        nachlprot.s.NL_MENGE_GELIEFER = 0;
        nachlprot.s.NL_MENGE_NEU      = 0;
        nachlprot.s.POSTYP            = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, COL_POSTYP)));
        nachlprot.s.POSNR             = atoi(m_ListCtl.GetItemText(pos, COL_POS));
        nachlprot.s.NL_MENGE_ALT      = atol(m_ListCtl.GetItemText(pos, COL_MENGE_ALT));
        nachlprot.s.ARTIKEL_NR        = atol(m_ListCtl.GetItemText(pos, COL_PZN));
        nachlprot.s.AENDTYP           = AENDTYP_LIEFERMOEGLICHKEIT;
        nachlprot.s.UID               = GetAeUser().GetUID();
        nachlprot.s.KDAUFTRAG_NR_NEU  = m_lAuftrNr;
        nachlprot.s.IDFNR             = m_IdfNr;

        int anz = atol(m_ListCtl.GetItemText(pos, COL_POS));
        int nImage = CListCtrlHelper::GetImage(m_ListCtl, pos);
        if (nImage != BUCHEN_YES)
        {
            CString CStr;
            CStr.Format(CResString::ex().getStrTblText(AETXT_LOE_NACHL),
                m_ListCtl.GetItemText(pos, COL_MENGE).GetString(),
                m_ListCtl.GetItemText(pos, COL_PZN).GetString(),
                m_ListCtl.GetItemText(pos, COL_EINHEIT).GetString(),
                m_ListCtl.GetItemText(pos, COL_NAME).GetString());
            if (MsgBoxYesNo(CStr, MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
            {
                nImage = BUCHEN_YES;
            }
        }
        if (nImage != BUCHEN_YES)
        {
            nachlprot.s.NL_MENGE_AKTUELL = 0;
        }
        else
        {
            long MengeBestellt = atol(m_ListCtl.GetItemText(pos, COL_MENGE));
            nachlprot.s.NL_MENGE_AKTUELL = MengeBestellt;
            if (MengeBestellt != 0)
            {
                long MengeAbbuchung = MengeBestellt;
                long PosStat   = ITEM_STAT_NORMAL;
                CString Bemerkung = CResString::ex().getStrTblText(AETXT_NACHLIEFERUNG);
                long MengeBestelltOrg = atol(m_ListCtl.GetItemText(pos, COL_MENGEBESTLLT));
                short Preistyp = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, COL_PREIS_TYP)));
                bool bDefMaske = false;
                for (;;)
                {
                    aufposbuch.s.MENGEBESTELLT     = MengeBestellt;
                    aufposbuch.s.MENGEBESTAETIGT   = MengeAbbuchung;
                    aufposbuch.s.ARTIKEL_NR        = atol(m_ListCtl.GetItemText(pos, COL_PZN));
                    aufposbuch.s.MENGENATRA        = 0;
                    aufposbuch.s.STATUS            = PosStat;
                    aufposbuch.s.POSTYP            = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, COL_POSTYP)));
                    aufposbuch.s.POSNR             = atoi(m_ListCtl.GetItemText(pos, COL_POS));
                    aufposbuch.s.PREISEKGROSSO     = atof(m_ListCtl.GetItemText(pos, COL_NETTO));
                    aufposbuch.s.CODE_TYPE         = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, COL_CODE_TYPE)));
                    strcpy( aufposbuch.s.ARTICLE_CODE,m_ListCtl.GetItemText(pos, COL_ARTCODE));
                    strcpy( aufposbuch.s.BEMERKUNG, (LPCTSTR) Bemerkung);
                    aufposbuch.s.DISCOUNTVALUEPCT  = atof(m_ListCtl.GetItemText(pos, COL_VALUEPCT));
                    aufposbuch.s.MENGEGELIEFERT    = MengeBestelltOrg; //wird zweckentfremdet
                    aufposbuch.s.PREIS_TYP         = Preistyp;

                    //Buchungsversuch
                    aufposbuch.Server(AasrvWriteposNL, PIPE_AE_SRV);
                    if (aufposbuch.rc < SRV_OK)            //Fehler
                    {
                        return;
                    }
                    if (   aufposbuch.s.STATUS == ITEM_STAT_KEINE_MENGE        //Verfügbare Menge reichte nicht aus
                        || aufposbuch.s.STATUS == ITEM_STAT_NACHLIEFUPD )      //Verfügbare Menge reichte nicht aus wg. Kontigent
                    {
                        AltStat = aufposbuch.s.STATUS;
                        char str[81];
                        CDBePosBearb dlgBePosBearb;
                        CDVerbBestaet dlgVerbBestaet;
                        dlgVerbBestaet.m_VerbundZeitenKnd = m_VerbundZeitenKnd;
                        dlgBePosBearb.SetBestMengeStr("%ld", MengeBestellt);
                        dlgVerbBestaet.m_CBestMenge      = dlgBePosBearb.GetBestMengeStr();
                        dlgVerbBestaet.m_CArtName        = dlgBePosBearb.m_CArtName      = m_ListCtl.GetItemText(pos, COL_NAME);
                        dlgVerbBestaet.m_CArtEinh        = dlgBePosBearb.m_CArtEinh      = m_ListCtl.GetItemText(pos, COL_EINHEIT);
                        dlgVerbBestaet.m_CArtNr                              = m_ListCtl.GetItemText(pos, COL_PZN);
                        dlgBePosBearb.SetArtNr(dlgVerbBestaet.m_CArtNr);
                        dlgVerbBestaet.m_CArtCode        = dlgBePosBearb.m_CArtCode      = m_ListCtl.GetItemText(pos, COL_ARTCODE);
                        dlgVerbBestaet.m_CBestand                            = _ltoa(aufposbuch.s.BESTAND, str, 10);
                        dlgBePosBearb.SetBestand(dlgVerbBestaet.m_CBestand);
                        dlgVerbBestaet.m_VerbMenge                           = aufposbuch.s.MENGE;
                        dlgBePosBearb.SetVerbMenge(dlgVerbBestaet.m_VerbMenge);
                        dlgVerbBestaet.m_VerbFiliale                         = aufposbuch.s.FILIALNR1;
                        dlgBePosBearb.SetVerbFiliale(dlgVerbBestaet.m_VerbFiliale);
                        dlgVerbBestaet.m_CDarreichform   = dlgBePosBearb.m_CDarreichform = m_ListCtl.GetItemText(pos, COL_DAF);
                        dlgBePosBearb.m_LiefMenge       = aufposbuch.s.BESTAND;
                        dlgBePosBearb.SetBestMenge(MengeBestellt);
                        dlgBePosBearb.m_CBemerkung      = Bemerkung;
                        dlgBePosBearb.SetPosStat(ITEM_STAT_NACHLIEFERN);
                        dlgBePosBearb.m_IdfNr           = m_IdfNr;
                        dlgBePosBearb.m_KndNr           = m_lKndNr;

                        //aufposbuch.s.MENGE ist die moegliche Verbundmenge
                        if (aufposbuch.s.MENGE > 0 && aufposbuch.s.MENGE + aufposbuch.s.BESTAND >= MengeBestellt)
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
                            dlgBePosBearb.SetIgnoreNoWafo(true);
                            if (dlgBePosBearb.DoModal() == IDOK)
                            {
                                MengeAbbuchung  = dlgBePosBearb.m_Menge;
                                PosStat         = dlgBePosBearb.GetPosStat();
                                if (   AltStat == ITEM_STAT_NACHLIEFUPD
                                    && PosStat == ITEM_STAT_NACHLIEFERN )
                                {
                                    PosStat = ITEM_STAT_NACHLIEFUPD;
                                }
                                Bemerkung       = dlgBePosBearb.m_CBemerkung;
                                aufposbuch.s.FILIALNR1 = dlgBePosBearb.GetVerbFiliale();
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

                nachlprot.s.NL_MENGE_GELIEFER = aufposbuch.s.MENGEABGEBUCHT;
                if (aufposbuch.s.STATUS == ITEM_STAT_NACHLIEFERN)
                {
                    nachlprot.s.NL_MENGE_NEU = nachlprot.s.NL_MENGE_AKTUELL - aufposbuch.s.MENGEABGEBUCHT;
                }
                ptrDoc->AddPosition(aufposbuch.s); //Positionsliste erstellen
                ptrFView->AusgAufWerte(aufposbuch.s.ANZPOS, aufposbuch.s.WERTAUFTRAG, aufposbuch.s.WERTLIEFERUNG, aufposbuch.s.WERTZEILEN, aufposbuch.s.BALANCE, aufposbuch.s.BALANCE2);
                ptrFView->AusgAufWerteBG(aufposbuch.s.WERTNETTO_FV, aufposbuch.s.WERTTAX_FV, aufposbuch.s.WERTNETTO_KK, aufposbuch.s.WERTTAX_KK, aufposbuch.s.WERTNETTO_EH, aufposbuch.s.WERTTAX_EH, aufposbuch.s.WERTEXCLUSIVE);
            }
        }

        for (satzadr* freepos = actpos->satzpos; anz > 0; anz--, freepos = freepos->nextpos)
        {
            nachlprot.s.KDAUFTRAGNR = freepos->kdauftragnr;
            nachlprot.s.POSNR = freepos->posnr;
            nachlprot.s.DATUM = freepos->datum;
            nachlprot.s.POSTYP = freepos->postyp;
            nachlprot.Server(AaauftIns_prot);
        }
    }
    EndWaitCursor();
    CDialogMultiLang::OnCancel();
}

/////////////////////////////////////////////////////////////////////////////
// CDNachlArtAen dialog


CDNachlArtAen::CDNachlArtAen(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDNachlArtAen::IDD, pParent)
{
    m_CMenge = _T("");
    m_CBestand = _T("");
    m_CName = _T("");
    m_CPzn = _T("");
    m_CMengeAlt = _T("");
    m_CDarr = _T("");
    m_CEinheit = _T("");
}


void CDNachlArtAen::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_EditMenge);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_CMenge);
    DDX_Text(pDX, IDC_STATIC_BESTAND, m_CBestand);
    DDX_Text(pDX, IDC_STATIC_NAME, m_CName);
    DDX_Text(pDX, IDC_STATIC_PZN, m_CPzn);
    DDX_Text(pDX, IDC_STATIC_MENGE_ALT, m_CMengeAlt);
    DDX_Text(pDX, IDC_STATIC_DARR, m_CDarr);
    DDX_Text(pDX, IDC_STATIC_EINHEIT, m_CEinheit);
}


BEGIN_MESSAGE_MAP(CDNachlArtAen, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDNachlArtAen message handlers

void CDNachlArtAen::OnOK()
{
    CDialogMultiLang::OnOK();
}
