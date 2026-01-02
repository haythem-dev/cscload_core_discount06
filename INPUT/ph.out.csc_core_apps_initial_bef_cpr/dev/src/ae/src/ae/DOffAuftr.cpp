// DOffAuftr.cpp : implementation file
//

#include "stdafx.h"
#include "DOffAuftr.h"
#include "DInfAnzAuft.h"
#include "aeorderstat.h"
#include <auftraginfo.h>
#include "MainFrm.h"

#define ZEILEN 15

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     18

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 30, LVCFMT_LEFT,
    2,  "", 20, LVCFMT_CENTER,
    3,  "", 40, LVCFMT_RIGHT,
    4,  "", 55, LVCFMT_RIGHT,
    5,  "", 60, LVCFMT_CENTER,
    6,  "", 40, LVCFMT_LEFT,
    7,  "", 35, LVCFMT_RIGHT,
    8,  "", 35, LVCFMT_RIGHT,
    9,  "", 90, LVCFMT_LEFT,
    10, "", 45, LVCFMT_LEFT,
    11, "", 35, LVCFMT_CENTER,
    12, "", 60, LVCFMT_LEFT,
    13, "", 25, LVCFMT_CENTER,
    14, "", 40, LVCFMT_RIGHT,
    15, "", 30, LVCFMT_RIGHT,
    16, "",  0, LVCFMT_RIGHT,
    17, "", 60, LVCFMT_RIGHT,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDOffAuftr dialog


CDOffAuftr::CDOffAuftr(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDOffAuftr::IDD, pParent), CPageBrowser(ZEILEN)
{
    m_Geraet = _T("");
    m_SortArt = -1;
    m_bDafue = FALSE;
    m_bVz = FALSE;
    m_bDafue = AeGetApp()->IsNurDafue() ? TRUE : FALSE;
    m_KndNr     = 0;
    m_IdfNr     = 0;
    m_VzNr      = 0;
    m_RegionNr  = 0;
    m_Geraet    = "";
    m_cSortfield = "kdauftragnr";

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_ZUGRUND);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_KZ_PATA);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_KURZ_AUFTR_NR);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_DFU);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_PH);
    Columns[9].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[10].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[11].Columns = CResString::ex().getStrTblText(AETXT_ABC);
    Columns[12].Columns = CResString::ex().getStrTblText(AETXT_ENDE);
    Columns[13].Columns = CResString::ex().getStrTblText(AETXT_KZ_ANZ_ALPHA_TXT);
    Columns[14].Columns = CResString::ex().getStrTblText(AETXT_TRM);
    Columns[15].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns[16].Columns = CResString::ex().getStrTblText(AETXT_ZUGRUND);
    Columns[17].Columns = CResString::ex().getStrTblText(AETXT_ORDERLABEL);
}


void CDOffAuftr::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_AART, m_StaticAArt);
    DDX_Control(pDX, IDC_COMBO_AART, m_ComboAArt);
    DDX_Control(pDX, IDC_CHECK_VZ, m_CheckVz);
    DDX_Control(pDX, IDC_CHECK_DAFUE, m_CheckDafue);
    DDX_Control(pDX, IDC_COMBO_SORT, m_ComboSort);
    DDX_Control(pDX, IDC_EDIT_GERAET, m_EditGeraet);
    DDX_Control(pDX, IDC_LIST_AUFTRAG, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_GERAET, m_Geraet);
    DDX_CBIndex(pDX, IDC_COMBO_SORT, m_SortArt);
    DDX_Check(pDX, IDC_CHECK_DAFUE, m_bDafue);
    DDX_Check(pDX, IDC_CHECK_VZ, m_bVz);
    DDX_Control(pDX, IDC_CHECK_ALLE, m_CB_Alle);
}


BEGIN_MESSAGE_MAP(CDOffAuftr, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_AUFTRAG, OnDblclkListAuftrag)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_AUFTRAG, OnKeydownListAuftrag)
    ON_EN_CHANGE(IDC_EDIT_GERAET, OnChangeEditGeraet)
    ON_CBN_SELCHANGE(IDC_COMBO_SORT, OnSelchangeComboSort)
    ON_BN_CLICKED(IDC_CHECK_DAFUE, OnCheckDafue)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_CHECK_VZ, OnCheckVz)
    ON_CBN_SELCHANGE(IDC_COMBO_AART, OnSelchangeComboAart)
    ON_BN_CLICKED(IDC_CHECK_ALLE, OnBnClickedCheckAlle)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDOffAuftr message handlers

BOOL CDOffAuftr::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    CenterWindow();
    if (AeGetApp()->IsKundeHome())
    {
        m_CheckVz.SetCheck(TRUE);
    }
    if (AeGetApp()->IsAlleVz())
    {
        m_CB_Alle.SetCheck(TRUE);
    }
    if (IsDlgButtonChecked(IDC_CHECK_VZ))
    {
        m_CB_Alle.ShowWindow(SW_HIDE);
    }

    if (!GetAeUser().IsMehrVz())
    {
        m_CheckVz.SetCheck(TRUE);
        m_CheckVz.EnableWindow(FALSE);
    }

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    AllgSetColumnWidthUser(m_ListCtl, "CDoffAuft", KEY_PATH, NUM_COLUMNS);

    m_ComboSort.AddString(CResString::ex().getStrTblText(AETXT_AUFTRAGSNUMMER));
    m_ComboSort.AddString(CResString::ex().getStrTblText(AETXT_TOUR));
    m_ComboSort.AddString(CResString::ex().getStrTblText(AETXT_IDF_NUMMER));
    m_ComboSort.AddString(CResString::ex().getStrTblText(AETXT_SCHLIESSZEIT));
    m_ComboSort.AddString(CResString::ex().getStrTblText(AETXT_AUFTRAGSART));
    m_ComboSort.AddString(CResString::ex().getStrTblText(AETXT_KDKLASSE));
    m_ComboSort.AddString(CResString::ex().getStrTblText(AETXT_ANZ_POS));
    m_ComboSort.AddString(CResString::ex().getStrTblText(AETXT_FILIALE));

    if      (AeGetApp()->OrderSort() == SORT_ORDER_APO_ENDE)  m_SortArt = 3;
    else if (AeGetApp()->OrderSort() == SORT_ORDER_IDF)       m_SortArt = 2;
    else if (AeGetApp()->OrderSort() == SORT_ORDER_TOUR)      m_SortArt = 1;
    else if (AeGetApp()->OrderSort() == SORT_ORDER_AART)      m_SortArt = 4;
    else if (AeGetApp()->OrderSort() == SORT_ORDER_KDKLASSE)  m_SortArt = 5;
    else if (AeGetApp()->OrderSort() == SORT_ORDER_ANZPOS)    m_SortArt = 6;
    else if (AeGetApp()->OrderSort() == SORT_ORDER_BRANCHNO)  m_SortArt = 7;
    else                                                         m_SortArt = 0;
    m_ComboSort.SetCurSel(m_SortArt);

    for (int i = 0; i < AeGetApp()->m_Auftragarten.GetSize(); i++)
    {
        m_ComboAArt.AddString(AeGetApp()->m_Auftragarten.GetAt(i));
    }
    m_ComboAArt.SelectString(-1, AeGetApp()->SelectedAArt());
    if (AeGetApp()->OrderSort() == SORT_ORDER_AART )
    {
        m_ComboAArt.ShowWindow(SW_SHOW);
        m_StaticAArt.ShowWindow(SW_SHOW);
    }
    else
    {
        m_ComboAArt.ShowWindow(SW_HIDE);
        m_StaticAArt.ShowWindow(SW_HIDE);
    }

    if (m_KndNr != 0 || !m_Geraet.IsEmpty() || m_CheckDafue.GetCheck() == 1)
    {
        CloseCursor();
        AusgAuftraege(m_KndNr, m_VzNr, m_Geraet);
        return FALSE;  // return TRUE unless you set the focus to a control
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

int CDOffAuftr::DoModIfZROrdKnd(long KndNr, short VzNr) //Dialog öffnen falls für den Kunden etwas zurückgestellt
{
    CAUSTINF austinf;
    austinf.s.IDFNR = KndNr;
    austinf.s.KUNDENNR = KndNr;
    austinf.s.VERTRIEBSZENTRUMNR = VzNr;
    austinf.s.REGIONNR = AeGetApp()->VzNr();
    if (AeGetApp()->IsNoBatch())
    {
        austinf.s.BATCHSCHREIBEN = 0; // wieder ausgebaut
    }
    else
    {
        austinf.s.BATCHSCHREIBEN = 1; // weil ich nicht mehr weiß, warum.
    }
    AllgStrCopy(austinf.s.KDAUFTRAGSTAT, AEORD_ZURUECKGESTELLT, L_AUSTINF_KDAUFTRAGSTAT);
    if (AeGetApp()->IsCrema() && !AeGetApp()->IsStopCrema())
    {
        memset(austinf.s.ZUGRUND, '_', L_AUFTRAG_ZUGRUND);
        austinf.s.ZUGRUND[ZU_KREDITLIMIT] = '0';
    }
    else
    {
        memset(austinf.s.ZUGRUND, ' ', L_AUFTRAG_ZUGRUND);
        austinf.s.ZUGRUND[0] = '%';
    }
    if (GetAeUser().IsMSV3bearb())
        austinf.s.SENDESTATUS = 2;
    else if (GetAeUser().IsMSV3bearbNo())
        austinf.s.SENDESTATUS = 1;
    else
        austinf.s.SENDESTATUS = 0;
    austinf.Server(AaauftAnz_zur_knd);
    if (austinf.rc < SRV_OK || austinf.s.FETCH_REL < 1)
        return IDCANCEL;

    m_KndNr = KndNr;
    m_VzNr = VzNr;
    AeGetApp()->m_AeLogging.WriteLine(1, "DOffAuftr.cpp", "DoModIfZROrdKnd", "Start Anzeige");
    return DoModal();
}

int CDOffAuftr::DoModIfZROrdGer()
{
    CAUFSESS aufsess;
    aufsess.Server(AasrvGetsession, PIPE_AE_SRV);
    if (aufsess.rc < SRV_OK)
        return IDCANCEL;
    CString Geraet = aufsess.s.GERAETNAME;

    CAUSTINF austinf;
    AllgStrCopy(austinf.s.GERAETNAME, Geraet, L_AUSTINF_GERAETNAME);
    AllgStrCopy(austinf.s.KDAUFTRAGSTAT, AEORD_ZURUECKGEST_PHON, L_AUSTINF_KDAUFTRAGSTAT);
    austinf.s.REGIONNR = AeGetApp()->VzNr();
    if (AeGetApp()->IsCrema() && !AeGetApp()->IsStopCrema())
    {
        memset(austinf.s.ZUGRUND, '_', L_AUFTRAG_ZUGRUND);
        austinf.s.ZUGRUND[ZU_KREDITLIMIT] = '0';
    }
    else
    {
        memset(austinf.s.ZUGRUND, ' ', L_AUFTRAG_ZUGRUND);
        austinf.s.ZUGRUND[0] = '%';
    }
    austinf.Server(AaauftAnz_zur_geraet);
    if (austinf.rc < SRV_OK || austinf.s.FETCH_REL < 1)
        return IDCANCEL;

    m_Geraet = Geraet;
    AeGetApp()->m_AeLogging.WriteLine(1, "DOffAuftr.cpp", "DoModIfZROrdGer", "Start Anzeige");
    return DoModal();
}

CString CDOffAuftr::GetSortfield()
{
    if      (AeGetApp()->OrderSort() == SORT_ORDER_ORDNUMBER)
            return "kdauftragnr";
    else if (AeGetApp()->OrderSort() == SORT_ORDER_TOUR )
            return "tourid";
    else if (AeGetApp()->OrderSort() == SORT_ORDER_IDF )
            return "idfnr";
    else if (AeGetApp()->OrderSort() == SORT_ORDER_APO_ENDE )
            return "zeitendeam";
    else if (AeGetApp()->OrderSort() == SORT_ORDER_AART )
            return "kdauftragart,koart";
    else if (AeGetApp()->OrderSort() == SORT_ORDER_KDKLASSE )
            return "kzkdklasse";
    else if (AeGetApp()->OrderSort() == SORT_ORDER_ANZPOS )
            return "anzpos";
    else if (AeGetApp()->OrderSort() == SORT_ORDER_BRANCHNO )
            return "VERTRIEBSZENTRUMNR";
    else
            return "kdauftragnr";
}

long CDOffAuftr::GetNextOpenOrder()
{
    CAUSTINF austinf;
    long OrderNr;
    m_cSortfield = GetSortfield();
    AeGetApp()->IsMSV3 = false;
    AeGetApp()->IsCMI = false;
    do
    {
        austinf.s.FETCH_REL = 1;
        strcpy(austinf.s.GERAETNAME, "%");
        austinf.s.WAITFORIBTPICKING = 1;  //in F9 keine Auftraege mit diesem Kennzeichen
        austinf.s.KDAUFTRAGNR = 0;        // alle Aufträge >= 0;
        strcpy(austinf.s.TOURID, "%");    // egal welche Tour
        strcpy(austinf.s.KDAUFTRAGART, "%");
        austinf.s.DATUM = 0;              //nur aktuelle Auftraege
        austinf.s.REGIONNR = m_RegionNr;
        //Steuerung erfolgt über Menupunkt "extra" oder später in Maske selbst"
        if (AeGetApp()->IsKundeHome())
            austinf.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
        else austinf.s.VERTRIEBSZENTRUMNR = 0;
        AllgStrCopy(austinf.s.KDAUFTRAGSTAT, AEORD_ZURUECKGEST_DAFUE, L_AUSTINF_KDAUFTRAGSTAT);
        if (AeGetApp()->IsCrema() && !AeGetApp()->IsStopCrema())
        {
            memset(austinf.s.ZUGRUND, '_', L_AUFTRAG_ZUGRUND);
            austinf.s.ZUGRUND[ZU_KREDITLIMIT] = '0';
        }
        else
        {
            memset(austinf.s.ZUGRUND, ' ', L_AUFTRAG_ZUGRUND);
            austinf.s.ZUGRUND[0] = '%';
        }
        sprintf(austinf.s.SORTFIELD, "%s", m_cSortfield.GetString());
        if (GetAeUser().IsMSV3bearb())
            austinf.s.SENDESTATUS = 2;
        else if (GetAeUser().IsMSV3bearbNo())
            austinf.s.SENDESTATUS = 1;
        else
            austinf.s.SENDESTATUS = 0;
        austinf.Server(AaauftSelzurauft_o_sortfield);
        OrderNr = (austinf.rc == SRV_OK) ? austinf.s.KDAUFTRAGNR : 0;
    } while (   austinf.rc == SRV_OK
             && austinf.s.KDAUFTRAGSTAT[AEORD_POS_PARA_AUFTRAG] == '1'
             && (AeGetApp()->IsNoParaCall() || AeGetApp()->IsFastOpenOrder())
            );  //keine Paraaufträge selektieren bei fastopen bzw mitarbeiter macht kein para
    if (OrderNr != 0)
    {
        AllgEntfSpaces(austinf.s.ORDERLABEL);
        if (austinf.s.ORDERLABEL[0] != '\0')
            AeGetApp()->IsMSV3 = true;
        if (std::strstr(austinf.s.KDAUFTRAGART, "DG") != NULL)
            AeGetApp()->IsCMI = true;
    }
    austinf.s.FETCH_REL = 0;
    austinf.Server(AaauftSelzurauft_o_sortfield);
    m_AufNr = OrderNr;
    return OrderNr;
}

bool CDOffAuftr::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    AusgAuftraege(0, 0, "", nKzUpDown);
    return true;
}

void CDOffAuftr::AusgAuftraege(long KndNr, short VzNr, CString Geraet, int nKzUpDown)
{
    char str[260];
    short count;
    CString Tour;
    CString CStr;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    long status = (m_CheckDafue.GetCheck() == 1) ? ORD_DAFUE_FEHLER : ORD_ZURUECKGESTELLT;

    CAUSTINF austinf;
    austinf.s.IDFNR = KndNr;
    austinf.s.KUNDENNR = KndNr;
    austinf.s.REGIONNR = m_RegionNr;
    if (AeGetApp()->IsCrema() && !AeGetApp()->IsStopCrema())
    {
        memset(austinf.s.ZUGRUND, '_', L_AUFTRAG_ZUGRUND);
        austinf.s.ZUGRUND[ZU_KREDITLIMIT] = '0';
    }
    else
    {
        memset(austinf.s.ZUGRUND, ' ', L_AUFTRAG_ZUGRUND);
        austinf.s.ZUGRUND[0] = '%';
    }
    if (IsDlgButtonChecked(IDC_CHECK_VZ))
    {
        austinf.s.VERTRIEBSZENTRUMNR = VzNr;
        count = 2;
    }
    else if (IsDlgButtonChecked(IDC_CHECK_ALLE))
    {
        austinf.s.VERTRIEBSZENTRUMNR = 0;
        count = 1;
    }
    else
    {
        austinf.s.VERTRIEBSZENTRUMNR = VzNr;
        count = 0;
    }
    do
    {
        strcpy(austinf.s.TOURID, "");
        strcpy(austinf.s.GERAETNAME, Geraet);

        //Anfangsinitialisierung durchfuehren
        if (m_bFirstDataset)  //Erstmaliger Aufruf
        {
            austinf.s.FETCH_REL = 1;
            austinf.s.BATCHSCHREIBEN = AeGetApp()->IsNoBatch() ? 0 : 1; // wieder ausgebaut, weil ich nicht mehr weiß, warum.

            strcpy(austinf.s.TOURID, "%");    // egal welche Tour
            austinf.s.KDAUFTRAGNR = 0;        // alle Aufträge >= 0;

            AllgStrCopy(austinf.s.KDAUFTRAGSTAT, (status == ORD_DAFUE_FEHLER) ? AEORD_ZURUECKGEST_DAFUE : AEORD_ZURUECKGESTELLT, L_AUSTINF_KDAUFTRAGSTAT);

            if (Geraet.IsEmpty())
                strcpy(austinf.s.GERAETNAME, "%");

            if (KndNr != 0L)
                m_cSortfield = "kdauftragnr";
            else
                m_cSortfield = GetSortfield();
        }

        if (m_cSortfield != "kdauftragart,koart")   // hier nicht die Auftragsart auf Default "%" setzen !!!
            strcpy(austinf.s.KDAUFTRAGART, "%");          // sonst, egal welche Auftragsart
        else
            sprintf(austinf.s.KDAUFTRAGART, "%s%%", AeGetApp()->SelectedAArt().GetString());

        sprintf(austinf.s.SORTFIELD, "%s", m_cSortfield.GetString());
        if (GetAeUser().IsMSV3bearb())
            austinf.s.SENDESTATUS = 2;
        else if (GetAeUser().IsMSV3bearbNo())
            austinf.s.SENDESTATUS = 1;
        else
            austinf.s.SENDESTATUS = 0;

        if (!GetFetchPositionOnPageSwitch(nKzUpDown, austinf.s.FETCH_REL))
        {
            return;
        }

        m_ListCtl.DeleteAllItems();
        CLetterMan kb;
        BeginWaitCursor();

        for (int i = 0; i < ZEILEN; i++)
        {
            austinf.s.DATUM = 0;                  // nur aktuelle Auftraege
            austinf.Server(AaauftSelzurauft_o_sortfield);
            m_bCursorOpen = true;           //Datenbankcurser offen
            austinf.s.FETCH_REL = 1;              //normaler Fetch

            if (austinf.rc != SRV_OK)
            {
                if (austinf.rc < SRV_OK)
                {
                    count = 2;
                    break;
                }

                if (m_bFirstDataset)     //kein Satz gefunden
                {
                    if (count > 0)
                    {
                        MsgBoxOK(IDP_KEIN_AUFTRAG);
                        CloseCursor();
                        EndWaitCursor();
                        return;
                    }
                    else
                    {
                        ++count;
                        CloseCursor();
                        austinf.s.VERTRIEBSZENTRUMNR = 0;
                        break;
                    }
                }
                SetItemCountOfCurrentPage(i); //Anzahl Artikel letzte Seite
                break;
            }
            count = 2;
            m_bFirstDataset = false;
        //Ausgabe in die Listbox
            s[0] = kb.Next();

            if (AeGetApp()->IsNoParaCall() && austinf.s.KDAUFTRAGSTAT[AEORD_POS_PARA_AUFTRAG] == '1')
                continue;
            s[2] = austinf.s.KDAUFTRAGSTAT[AEORD_POS_PARA_AUFTRAG] == '1' ? "P" : "";
            s[12] = HHmmStringFromTimeLong(austinf.s.ZEITENDEPM);

            s[1].Empty();
            if (austinf.s.ZUGRUND[ZU_KREDITLIMIT] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_SHORT_KREDITLIMIT);
            else if (austinf.s.ZUGRUND[ZU_INTERNET] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_SHORT_INTERNET);
            else if (austinf.s.ZUGRUND[ZU_BACKROUTING] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_SHORT_BACKROUTING);
            else if (austinf.s.ZUGRUND[ZU_DD_OHNE] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_SHORT_DD);
            else if (austinf.s.ZUGRUND[ZU_BTM] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_ZU_BTM);
            else if (austinf.s.ZUGRUND[ZU_OV] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_ZU_OV);
            else if (austinf.s.ZUGRUND[ZU_WAHL_STELLER] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_ZU_WS);
            else if (austinf.s.ZUGRUND[ZU_NO_QTY_NR] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_NO_RAB_QTY);
            else if (austinf.s.ZUGRUND[ZU_NO_CICS] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_SHORT_NO_CICS);
            if (austinf.s.ZUGRUND[ZU_INVENTUR_HERST] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_ZU_IV);
            if (austinf.s.ZUGRUND[ZU_INVENTUR_KONSIG] == '1')
                s[1] = CResString::ex().getStrTblText(AETXT_ZU_IV);
            sprintf(str, "%d", austinf.s.KDAUFTRAGNR);
            s[3] = str;
            sprintf(str, "%d", austinf.s.IDFNR);
            s[4] = str;
            AllgEntfSpaces(austinf.s.TOURID);
            if (atol(austinf.s.TOURID))
            {
                Tour.Format("%2.2s:%2.2s/%2.2s", austinf.s.TOURID, austinf.s.TOURID + 2, austinf.s.TOURID + 4);
            }
            else
            {
                Tour = "";
            }
            s[5] = Tour;
            CStr.Format("%s%s%s", austinf.s.KDAUFTRAGART, austinf.s.KOART, austinf.s.BUCHART);
            s[6] = CStr;
            sprintf(str, "%ld", austinf.s.ANZPOSDAFUE);
            s[7] = str;
            sprintf(str, "%ld", austinf.s.ANZPOS - austinf.s.ANZPOSDAFUE);
            s[8] = str;
            AllgEntfSpaces(austinf.s.NAMEAPO);
            AllgEntfSpaces(austinf.s.NAMEINHABER);
            s[9] = austinf.s.NAMEAPO;
            if (AeGetApp()->IsHR())
            {
                s[9] += " ";
                s[9] += austinf.s.NAMEINHABER;
            }
            AllgEntfSpaces(austinf.s.ORT);
            s[10] = austinf.s.ORT;
            AllgEntfSpaces(austinf.s.KZKDKLASSE);
            s[11] = austinf.s.KZKDKLASSE;
            sprintf(str, "%ld", austinf.s.ANZALPHATEXT);
            s[13] = str;
            AllgEntfSpaces(austinf.s.GERAETNAME);
            s[14] = austinf.s.GERAETNAME;
            s[15].Format("%d", austinf.s.VERTRIEBSZENTRUMNR);
            s[16] = austinf.s.ZUGRUND;    //zwichenspeichern
            AllgEntfSpaces(austinf.s.ORDERLABEL);
            s[17] = austinf.s.ORDERLABEL;

            if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
            {
                EndWaitCursor();
                return;
            }
        }
    } while (count < 2);
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
    EndWaitCursor();
}

void CDOffAuftr::MarkListPosChar(int Letter)
{
    int pos;
    if (CListCtrlHelper::GetListPositionByChar(m_ListCtl, Letter, pos))
    {
        CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, pos);
    }
}

void CDOffAuftr::OnKeydownListAuftrag(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (OnKeydownList(pNMHDR, pResult, m_ListCtl, false))
    {
        return;
    }

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InAZRange(pLVKeyDow->wVKey))
    {
        MarkListPosChar((int)(pLVKeyDow->wVKey));
        if ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000)
        {
            CDInfAnzAuft dlgInfAnzAuft;
            dlgInfAnzAuft.m_AuftrNr = GetAuftrNr();
            if (dlgInfAnzAuft.m_AuftrNr != 0) dlgInfAnzAuft.DoModal();
            return;
        }
        *pResult = 1L;
    }
}

void CDOffAuftr::OnDblclkListAuftrag(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SetAuftrNr();
    *pResult = 0L;
}

long CDOffAuftr::GetAuftrNr()
{
    CString AufNr;

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return 0L;
    }
    AeGetApp()->IsMSV3 = false;
    AeGetApp()->IsCMI = false;
    CString ZuGrund = m_ListCtl.GetItemText(pos, 16);
    if (ZuGrund.GetAt(ZU_KREDITLIMIT) == '1' && !GetAeUser().IsKreditAbschluss())
    {
        MsgBoxOK(IDP_NO_OPEN_DEBLIMIT);
        return 0L;
    }
    else if (ZuGrund.GetAt(ZU_INTERNET) == '1' && !GetAeUser().IsInternetAbschluss())
    {
        MsgBoxOK(IDP_NO_OPEN_INTERNET);
        return 0L;
    }
    else if (ZuGrund.GetAt(ZU_BTM) == '1' && !GetAeUser().IsAbschlussBTM())
    {
        MsgBoxOK(IDP_NO_OPEN_BTM);
        return 0L;
    }
    else if (ZuGrund.GetAt(ZU_BACKROUTING) == '1' && AeGetApp()->VzNr() !=
        atoi(m_ListCtl.GetItemText(pos, 15)))
    {
        MsgBoxOK(IDP_OPEN_NUR_EIGEN);
        return 0L;
    }
    else if (ZuGrund.GetAt(ZU_INVENTUR_HERST) == '1')
    {
        CCHECKORDERIV check;
        check.SetKdauftragnr(m_AufNr);
        if (!check.SelManu())
        {
            MsgBoxOK(IDP_NO_OPEN_IV);
            return 0L;
        }
    }
    else if (ZuGrund.GetAt(ZU_INVENTUR_KONSIG) == '1')
    {
        CCHECKORDERIV check;
        check.SetKdauftragnr(m_AufNr);
        if (!check.SelKonsig())
        {
            MsgBoxOK(IDP_NO_OPEN_IV);
            return 0L;
        }
    }
    AufNr = m_ListCtl.GetItemText(pos, 3);
    if (!m_ListCtl.GetItemText(pos, 17).IsEmpty())
        AeGetApp()->IsMSV3 = true;

    if (std::strstr(m_ListCtl.GetItemText(pos, 6), "DG") != NULL)
        AeGetApp()->IsCMI = true;

    return atol(AufNr);
}

void CDOffAuftr::SetAuftrNr()
{
    m_AufNr = GetAuftrNr();
    if (m_AufNr == 0)
        return;
    CDialogMultiLang::OnOK();
}

void CDOffAuftr::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST_AUFTRAG))
    {
        SetAuftrNr();
        CString Text;
        Text.Format("OrderNo %d", m_AufNr);
        AeGetApp()->m_AeLogging.WriteLine(1, "DOffAuftr.cpp", "OnOK", Text);
        return;
    }
    UpdateData();
    CloseCursor();
    AeGetApp()->m_AeLogging.WriteLine(1, "DOffAuftr.cpp", "OnOK", "Show List");
    AusgAuftraege(m_KndNr, m_VzNr, m_Geraet);
}

void CDOffAuftr::OnChangeEditGeraet()
{
    AllgLaengeKontr(&m_EditGeraet, L_AUFTRAG_GERAETNAME, AeGetApp()->Modus());
}

void CDOffAuftr::OnCancel()
{
    m_KndNr     = 0;
    m_VzNr      = 0;
    m_RegionNr  = 0;
    UpdateData();
    AeGetApp()->m_AeLogging.WriteLine(1, "DOffAuftr.cpp", "OnCancel", "Nothing happens");
    CDialogMultiLang::OnCancel();
}

void CDOffAuftr::OnSelchangeComboSort()
{
    UpdateData();
    m_ComboAArt.ShowWindow(SW_HIDE);
    m_StaticAArt.ShowWindow(SW_HIDE);
    if      (m_ComboSort.GetCurSel() == 3)
    {
        AeGetApp()->OrderSort = SORT_ORDER_APO_ENDE;
    }
    else if (m_ComboSort.GetCurSel() == 2)
    {
        AeGetApp()->OrderSort = SORT_ORDER_IDF;
    }
    else if (m_ComboSort.GetCurSel() == 1)
    {
        AeGetApp()->OrderSort = SORT_ORDER_TOUR;
    }
    else if (m_ComboSort.GetCurSel() == 4)
    {
        AeGetApp()->OrderSort = SORT_ORDER_AART;
        m_ComboAArt.ShowWindow(SW_SHOW);
        m_StaticAArt.ShowWindow(SW_SHOW);
    }
    else if (m_ComboSort.GetCurSel() == 5)
    {
        AeGetApp()->OrderSort = SORT_ORDER_KDKLASSE;
    }
    else if (m_ComboSort.GetCurSel() == 6)
    {
        AeGetApp()->OrderSort = SORT_ORDER_ANZPOS;
    }
    else
    {
        AeGetApp()->OrderSort = SORT_ORDER_ORDNUMBER;
    }
    CloseCursor();
    AusgAuftraege(m_KndNr, m_VzNr, m_Geraet);
}

void CDOffAuftr::OnCheckDafue()
{
    HKEY hKey;
    char szBuffer[30];
    UpdateData();
    AeGetApp()->IsNurDafue = IsDlgButtonChecked(IDC_CHECK_DAFUE) ? true : false;
    strcpy(szBuffer, AeGetApp()->IsNurDafue() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_NURDAFUE, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }
    CloseCursor();
    AusgAuftraege(m_KndNr, m_VzNr, m_Geraet);
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDOffAuftr::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDOffAuftr::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CAUSTINF austinf;
    austinf.s.FETCH_REL = 0;
    BeginWaitCursor();
    austinf.Server(AaauftSelzurauft_o_sortfield);
    EndWaitCursor();
    ResetCursor();
    Reset();
}


void CDOffAuftr::OnDestroy()
{
    AllgWriteColumnWidthUser(m_ListCtl, "CDoffAuft", KEY_PATH, NUM_COLUMNS);

    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDOffAuftr::OnCheckVz()
{
    if (IsDlgButtonChecked(IDC_CHECK_VZ))
    {
        AeGetApp()->IsKundeHome = true;
        m_CB_Alle.ShowWindow(SW_HIDE);
    }
    else
    {
        AeGetApp()->IsKundeHome = false;
        m_CB_Alle.ShowWindow(SW_SHOW);
    }
    UpdateData();
    CloseCursor();
    AusgAuftraege(m_KndNr, m_VzNr, m_Geraet);
}

void CDOffAuftr::OnSelchangeComboAart()
{
    CString str;
    m_ComboAArt.GetLBText(m_ComboAArt.GetCurSel(), str);
    AeGetApp()->SelectedAArt = str;
}

void CDOffAuftr::OnBnClickedCheckAlle()
{
    UpdateData();
    CloseCursor();
    AusgAuftraege(m_KndNr, m_VzNr, m_Geraet);
}

BOOL CDOffAuftr::DestroyWindow()
{
    HKEY hKey;
    char szBuffer[30];
    if (AeGetApp()->Geraet() != m_Geraet)
    {
        AeGetApp()->Geraet = m_Geraet;
        sprintf(szBuffer, "%s", AeGetApp()->Geraet().GetString());
        if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
        {
            RegSetValueEx(hKey, KEY_NAME_TERMINAL, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
            RegCloseKey(hKey);
        }
    }

    if (static_cast<unsigned int>(AeGetApp()->IsAlleVz()) != IsDlgButtonChecked(IDC_CHECK_ALLE))
    {
        AeGetApp()->IsAlleVz = IsDlgButtonChecked(IDC_CHECK_ALLE) ? true : false;

        strcpy(szBuffer, AeGetApp()->IsAlleVz() ? "1" : "0");

        if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
        {
            RegSetValueEx(hKey, KEY_NAME_ALLEVZ, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
            RegCloseKey(hKey);
        }
    }

    return CDialogMultiLang::DestroyWindow();
}
