// daufinf.cpp : implementation file
//

#include "stdafx.h"
#include "DAufInf.h"
#include <kndsel.h>
#include "DKndInf.h"
#include "DArtDef.h"
#include "DKndWahl.h"
#include "DOrderInformation.h"
#include "DDruckAuftrag.h"
#include "aeorderstat.h"
#include "aaclasses.h"
#include "MainFrm.h"
#include <auftraginfo.h>
#include <orders.h>
#include "DChangeTour.h"

#define WAITFORIBT 10

#define ZEILEN 13

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB               0
#define COL_ZG               1
#define COL_IDF              2
#define COL_APO              3
#define COL_ORT              4
#define COL_AUFNR            5
#define COL_TOUR             6
#define COL_AART             7
#define COL_ZZ               8
#define COL_STATUS           9
#define COL_POS             10
#define COL_ZD              11
#define COL_TRM             12
#define COL_TIME            13
#define COL_VZ              14
#define COL_VSE             15
#define COL_ZUGRUND         16
#define COL_DATUM           17
#define COL_RECHNR          18
#define COL_DD              19
#define COL_ORDERLABEL      20
#define COL_ORDERPERIODID   21
#define COL_IVCNO           22
#define COL_DATE            23
#define COL_WAITIBT         24
#define NUM_COLUMNS         25

static COLUMNS_TYPES Columns[] =
{
    COL_KB,            "",  35, LVCFMT_LEFT,
    COL_ZG,            "",  35, LVCFMT_LEFT,
    COL_IDF,           "",  60, LVCFMT_RIGHT,
    COL_APO,           "", 120, LVCFMT_LEFT,
    COL_ORT,           "",  65, LVCFMT_LEFT,
    COL_AUFNR,         "",  50, LVCFMT_RIGHT,
    COL_TOUR,          "",  60, LVCFMT_LEFT,
    COL_AART,          "",  46, LVCFMT_LEFT,
    COL_ZZ,            "",   0, LVCFMT_RIGHT,
    COL_STATUS,        "",  30, LVCFMT_LEFT,
    COL_POS,           "",  35, LVCFMT_RIGHT,
    COL_ZD,            "",  35, LVCFMT_RIGHT,
    COL_TRM,           "",  40, LVCFMT_RIGHT,
    COL_TIME,          "",  40, LVCFMT_RIGHT,
    COL_VZ,            "",  30, LVCFMT_RIGHT,
    COL_VSE,           "",  50, LVCFMT_RIGHT,
    COL_ZUGRUND,       "",   0, LVCFMT_RIGHT,
    COL_DATUM,         "",   0, LVCFMT_LEFT,
    COL_RECHNR,        "",  50, LVCFMT_RIGHT,
    COL_DD,            "",   0, LVCFMT_LEFT,
    COL_ORDERLABEL,    "",  60, LVCFMT_LEFT,
    COL_ORDERPERIODID, "",  40, LVCFMT_LEFT,
    COL_IVCNO,         "",  70, LVCFMT_LEFT,
    COL_DATE,          "",   0, LVCFMT_LEFT,
    COL_WAITIBT,       "",   0, LVCFMT_LEFT,
    -1,                "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDAufInf dialog


CDAufInf::CDAufInf(CWnd* pParent /*=NULL*/,
                   const bool bDirectSelect /*=false*/)
    : CDialogMultiLang(CDAufInf::IDD, pParent)
    , m_CT_DD(0), CPageBrowser(ZEILEN)
{
    m_KndNr = _T("");
    m_Tour = _T("");
    m_ComboStatus = -1;
    m_COrderNr = _T("");
    m_CTermID = _T("");
    m_CDatum = _T("");
    m_RechnNr = _T("");
    m_CLauftnr = _T("");
    m_CPzn = _T("");
    m_COrderNrFili = _T("");
    m_ComboStatus = 0;
    m_AufNr = 0;
    m_Funktion = 0;
    m_bDirectSelect = bDirectSelect;
    m_IdfNr = 0;
    m_lKndNr = 0;
    m_Sort = _T("");
    m_bSelProforma = FALSE;
    m_bMSV3 = AeGetApp()->IsMSV3();

    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_ZG].Columns = CResString::ex().getStrTblText(AETXT_ZUGRUND);
    Columns[COL_IDF].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[COL_APO].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[COL_ORT].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[COL_AUFNR].Columns = CResString::ex().getStrTblText(AETXT_AUF_NR);
    Columns[COL_TOUR].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[COL_AART].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    Columns[COL_ZZ].Columns = CResString::ex().getStrTblText(AETXT_ZZ);
    Columns[COL_STATUS].Columns = CResString::ex().getStrTblText(AETXT_GRST);
    Columns[COL_POS].Columns = CResString::ex().getStrTblText(AETXT_POS);
    Columns[COL_ZD].Columns = CResString::ex().getStrTblText(AETXT_ZEILEN_DAFUE_KZ);
    Columns[COL_TRM].Columns = CResString::ex().getStrTblText(AETXT_TRM);
    Columns[COL_TIME].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[COL_VZ].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns[COL_VSE].Columns = CResString::ex().getStrTblText(AETXT_AUF_NR_FIL);
    Columns[COL_DATUM].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[COL_RECHNR].Columns = CResString::ex().getStrTblText(AETXT_RECHNUNG_NR);
    Columns[COL_DD].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[COL_ORDERLABEL].Columns = CResString::ex().getStrTblText(AETXT_ORDERLABEL);
    Columns[COL_ORDERPERIODID].Columns = CResString::ex().getStrTblText(AETXT_ORDERPERIODID);
    if (AeGetApp()->IsDE())
        Columns[COL_IVCNO].Columns = CResString::ex().getStrTblText(AETXT_IVC_NO);
    else if (AeGetApp()->IsFR())
        Columns[COL_IVCNO].Columns = CResString::ex().getStrTblText(AETXT_ORGINVOICE);
    Columns[COL_DATE].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[COL_WAITIBT].Columns = CResString::ex().getStrTblText(AETXT_WAIT__IBT);
}

void CDAufInf::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_AUFTR_NR_FILI, m_EditOrderNrFili);
    DDX_Control(pDX, IDC_CHECK_VZ, m_CheckVz);
    DDX_Control(pDX, IDC_EDIT_PZN, m_EditPzn);
    DDX_Control(pDX, IDC_EDIT_LAUFT_NR, m_EditLauftnr);
    DDX_Control(pDX, IDC_EDIT_RECHN_NR, m_EditRechnNr);
    DDX_Control(pDX, IDC_EDIT_DATUM, m_EditDatum);
    DDX_Control(pDX, IDC_EDIT_TERMINAL, m_EditTermID);
    DDX_Control(pDX, IDC_EDIT_AUFTR_NR, m_EditOrderNr);
    DDX_Control(pDX, IDC_EDIT_TOUR, m_EditTour);
    DDX_Control(pDX, IDC_EDIT_IDF, m_EditKndNr);
    DDX_Control(pDX, IDC_LIST_CTRL, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_IDF, m_KndNr);
    DDX_Text(pDX, IDC_EDIT_TOUR, m_Tour);
    DDX_Control(pDX, IDC_COMBO_KDAUFTRAGART, m_ComboKdAArt);
    DDX_CBIndex(pDX, IDC_COMBO_STATUS, m_ComboStatus);
    DDX_Text(pDX, IDC_EDIT_AUFTR_NR, m_COrderNr);
    DDX_Text(pDX, IDC_EDIT_TERMINAL, m_CTermID);
    DDX_Text(pDX, IDC_EDIT_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_EDIT_RECHN_NR, m_RechnNr);
    DDX_Text(pDX, IDC_EDIT_LAUFT_NR, m_CLauftnr);
    DDX_Text(pDX, IDC_EDIT_PZN, m_CPzn);
    DDX_Text(pDX, IDC_EDIT_AUFTR_NR_FILI, m_COrderNrFili);
    DDX_Control(pDX, IDC_COMBO_STATUS, m_Combobox_Status);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DD, m_DT_DD);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DD, m_CT_DD);
}


BEGIN_MESSAGE_MAP(CDAufInf, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnButtonKnd)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnChangeEditIdf)
    ON_EN_CHANGE(IDC_EDIT_TOUR, OnChangeEditTour)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CTRL, OnKeydownListCtrl)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_CTRL, OnDblclkListCtrl)
    ON_EN_CHANGE(IDC_EDIT_AUFTR_NR, OnChangeEditAuftrNr)
    ON_WM_DESTROY()
    ON_EN_CHANGE(IDC_EDIT_DATUM, OnChangeEditDatum)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_EN_CHANGE(IDC_EDIT_RECHN_NR, OnChangeEditRechnNr)
    ON_EN_CHANGE(IDC_EDIT_LAUFT_NR, OnChangeEditLauftNr)
    ON_BN_CLICKED(IDC_BUTTON_PZN, OnButtonPzn)
    ON_WM_SHOWWINDOW()
    ON_BN_CLICKED(IDC_CHECK_VZ, OnCheckVz)
    ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
    ON_EN_CHANGE(IDC_EDIT_AUFTR_NR_FILI, OnChangeEditAuftrNrFili)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_CBN_SELCHANGE(IDC_COMBO_STATUS, OnCbnSelchangeComboStatus)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CTRL, OnLvnColumnclickListCtrl)
    ON_BN_CLICKED(IDC_BUTTON_PROFORMA, OnBnClickedButtonProforma)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDAufInf message handlers

BOOL CDAufInf::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_ActDatum = zeit.s.DATUM;
    CTime anf = CTimeFromDateLongMinTime(zeit.s.DATUM);
    CTime end(2030, 12, 31, 0, 0, 0);
    m_DT_DD.SetRange(&anf, &end);
    CTime zeitDD = CTimeFromDateLongMinTime(zeit.s.DATUM);
    m_DT_DD.SetTime(&zeitDD);
    GetDlgItem(IDC_STATIC_DD)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_HIDE);
    CenterWindow();

    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_GS));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_STORNO));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_DF));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_ZU));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_ER));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_KO));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_FA));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_NK));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_BF));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_IE));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_AE));
    m_Combobox_Status.AddString(CResString::ex().getStrTblText(AETXT_DD));
    if (AeGetApp()->IsCrema())
    {
        m_Combobox_Status.AddString(CResString::ex().getStrTblText(AeGetApp()->IsDE() ? AETXT_KL_DE : AETXT_KL));
    }

    m_ComboKdAArt.AddString(CResString::ex().getStrTblText(AETXT_ALLE));
    for (int i = 0; i < AeGetApp()->m_Auftragarten.GetSize(); i++)
    {
        m_ComboKdAArt.AddString(AeGetApp()->m_Auftragarten.GetAt(i));
    }
    m_ComboKdAArt.SetCurSel(0);

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES;
    //dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    GetDlgItem(IDC_STATIC_ORD_NR)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_EDIT_AUFTR_NR)->ShowWindow(SW_SHOW);


    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_OK_YELLOW);
    idResources.push_back(IDI_ICON_LAGER_DEFEKT);
    idResources.push_back(IDI_ICON_KUNDE_DEFEKT);
    idResources.push_back(IDI_ICON_TOUR_DEFEKT);
    idResources.push_back(IDI_ICON2);
    idResources.push_back(IDI_ICON3);
    idResources.push_back(IDI_ICON_FV);
    idResources.push_back(IDI_ICON_KK);
    idResources.push_back(IDI_ICON_EH);
    idResources.push_back(IDI_ICON_00);
    idResources.push_back(IDI_ICON_WAIT_IBT);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    AllgSetColumnWidthUser(m_ListCtl, "CDAufInf", KEY_PATH, NUM_COLUMNS);
    if (AeGetApp()->IsKundeHome())
       m_CheckVz.SetCheck(TRUE);
    if (!GetAeUser().IsMehrVz())
    {
        AeGetApp()->IsKundeHome = true;
        m_CheckVz.SetCheck(TRUE);
        m_CheckVz.EnableWindow(FALSE);
    }
    if (AeGetApp()->IsRS())
    {
        GetDlgItem(IDC_BUTTON_PROFORMA)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_PROFORMA)->ShowWindow(SW_SHOW);
    }
    if (!AeGetApp()->IsBG())
    {
        m_ListCtl.SetColumnWidth(COL_ZZ, 0);
    }

    if (m_bDirectSelect)
        GetPage(); //nur wenn man von Ausgesteuerte Anrufe kommt!

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDAufInf::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    UpdateData();

    CString CStrOrdStat;
    long status = GetStatus(m_ComboStatus, CStrOrdStat);

    CAUSTINF austinf;
    strcpy(austinf.s.SORTFIELD, m_Sort);
    austinf.s.FETCH_REL = 1;
    austinf.s.KDAUFTRAGNR = atol(m_COrderNr);

    CString TermIdEigen = GetAeUser().GetTermID();
    if (   !m_CTermID.IsEmpty()
        && !GetAeUser().IsAnzAuf()
        && (m_CTermID.GetAt(0) != AeGetApp()->Letter_Z())
        && (TermIdEigen != m_CTermID) )
    {
        CStrOrdStat = AEORD_IN_ERFASSUNG;
    }
    m_CTermID += "%";
    AllgStrCopy(austinf.s.GERAETNAME, m_CTermID, L_AUSTINF_GERAETNAME);
    AllgStrCopy(austinf.s.KDAUFTRAGSTAT, CStrOrdStat, L_AUSTINF_KDAUFTRAGSTAT);
    if (m_CDatum.IsEmpty())
    {
        austinf.s.DATUM = 0;
        m_Datum = 0;
    }
    else
    {
        austinf.s.DATUM = AllgDatumEingKonv(m_CDatum, ALGF_FORM_DATUM_TTMMJJ);
        if (austinf.s.DATUM < 0)
        {
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_DATUM));
            return false;
        }
        m_Datum = austinf.s.DATUM;
    }

    m_lKndNr = atol(m_KndNr);
    austinf.s.IDFNR = m_lKndNr;   // alt
    austinf.s.KUNDENNR = m_lKndNr;
    austinf.s.REGIONNR = AeGetApp()->VzNr();
    austinf.s.VERTRIEBSZENTRUMNR = AeGetApp()->IsKundeHome() ? AeGetApp()->VzNr() : 0;
    austinf.s.ANZPOS = atol(m_RechnNr);
    strcpy(austinf.s.INVOICENUMBER, m_RechnNr);
    if (m_CPzn.IsEmpty())
    {
        austinf.s.ZEITENDEAM = 0;
    }
    else
    {
        CARTAESEL code;
        BeginWaitCursor();
        strcpy(code.s.ARTICLE_CODE, m_CPzn);
        code.Server(AatartSel_NoByCode);
        EndWaitCursor();
        if (code.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_PZN));
            return false;
        }
        austinf.s.ZEITENDEAM = code.s.ARTIKEL_NR;
    }
    strcpy(austinf.s.TOURID, m_Tour);

    // neues where- Kriterium kdauftrag.kdauftragart
    CString KdAuftrArt = "";

    if (m_ComboKdAArt.GetCurSel() > 0)
        m_ComboKdAArt.GetLBText(m_ComboKdAArt.GetCurSel(), KdAuftrArt);

    strcpy(austinf.s.KDAUFTRAGART, KdAuftrArt);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        memset(austinf.s.ZUGRUND, ' ', L_AUFTRAG_ZUGRUND);
        austinf.s.ZUGRUND[0] = '%';
        if (m_bSelProforma)
        {
            m_Funktion = AaauftSelProLink; // hier wird bereits nur nach kdauftragart = PF gesucht.
            austinf.s.KDAUFTRAGNRFILIALE = atol(m_COrderNrFili);
        }
        else if (!m_COrderNrFili.IsEmpty())
        {
            m_Funktion = AaauftSel_fili_auft_nr;
            austinf.s.KDAUFTRAGNRFILIALE = atol(m_COrderNrFili);
        }
        else if (!m_CLauftnr.IsEmpty())
        {
            m_Funktion = AaauftSel_lager_auft_nr; // hier wird nur nach einer speziellen LagerauftragNr gesucht = kdauftragart ist kein zusätzliches Suchkriterium!
            austinf.s.KDAUFTRAGNR = atol(m_CLauftnr);
        }
        else if (austinf.s.ZEITENDEAM)
        {
            m_Funktion = AaauftSelzurauftpzn;
        }
        else if (austinf.s.IDFNR)
        {
            m_Funktion = AaauftSelzurauftknde;
        }
        else
        {
            m_Funktion = AaauftSelzurauft;
        }
        austinf.s.BATCHSCHREIBEN = 1;

        if (m_Tour.IsEmpty())
        {
            strcpy(austinf.s.TOURID, "%");
        }

        if (KdAuftrArt.IsEmpty())
        {
            strcpy(austinf.s.KDAUFTRAGART, "%");
        }
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, austinf.s.FETCH_REL))
    {
        return false;
    }

    if (status == ORD_DELAYED_DELIVERY)
    {
        m_Funktion = AaauftSelzurauftDD;
        austinf.s.DATUMAUSLIEFERUNG = (m_CT_DD.GetYear() * 10000 +
            m_CT_DD.GetMonth() * 100 +
            m_CT_DD.GetDay());
        //m_ListCtl.SetColumnWidth(COL_DATUM, 80);
    }
    /*else
    {
        m_ListCtl.SetColumnWidth(COL_DATUM, 0);
    }
    */
    if (status == ORD_DELAYED_KL)
    {
        memset(austinf.s.ZUGRUND, '_', L_AUFTRAG_ZUGRUND);
        austinf.s.ZUGRUND[ZU_KREDITLIMIT] = '1';
    }

    m_ListCtl.DeleteAllItems();

    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        austinf.s.DATUM = m_Datum;
        austinf.Server(m_Funktion);

        m_bCursorOpen = true;      //Datenbankcurser offen
        austinf.s.FETCH_REL = 1;         //normaler Fetch
        if (austinf.rc != SRV_OK)
        {
            if (austinf.rc < SRV_OK)
            {
                break;
            }

            if (m_bFirstDataset)     //kein Satz gefunden
            {
                MsgBoxOK(IDP_KEIN_AUFTRAG);
                CloseCursor();
                EndWaitCursor();
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Artikel letzte Seite
            break;
        }
        m_bFirstDataset = false;
        int ipro = 0;
        if (AeGetApp()->IsRS())
        {
            //if (!strncmp(austinf.s.KDAUFTRAGART, "PF", 2))
            {
                int selProLink;
                if ((m_Datum == 0) && !m_bSelProforma)
                {
                    CPROLINKACT proact;
                    proact.SetKdauftragnr(austinf.s.KDAUFTRAGNR);
                    selProLink = proact.SelProLink();
                }
                else
                {
                    CPROLINK pro;
                    pro.SetKdauftragnr(austinf.s.KDAUFTRAGNR);
                    pro.SetDatum(m_Datum);
                    selProLink = pro.SelProLink();
                }
                if (selProLink == 0)
                {
                    ipro = 1;
                }
            }
        }

        //Ausgabe in die Listbox
        CStringArray s;
        s.SetSize(NUM_COLUMNS);

        s[COL_KB] = kb.Next();
        s[COL_ZG].Empty();
        if (austinf.s.ZUGRUND[ZU_KREDITLIMIT] == '1')
        {
            CCHECKKLRELEASED rel;
            rel.SetKdauftragnr(austinf.s.KDAUFTRAGNR);    //Auftrag bereits freigegeben ?
            s[COL_ZG] = CResString::ex().getStrTblText(rel.SelReleased() ? AETXT_SHORT_KREDITLIMIT : AETXT_SHORT_KREDITLIMIT_FREI);
        }
        else if (austinf.s.ZUGRUND[ZU_INTERNET] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_SHORT_INTERNET);
        else if (austinf.s.ZUGRUND[ZU_BACKROUTING] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_SHORT_BACKROUTING);
        else if (austinf.s.ZUGRUND[ZU_DD_OHNE] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_SHORT_DD);
        else if (austinf.s.ZUGRUND[ZU_BTM] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_BTM);
        else if (austinf.s.ZUGRUND[ZU_OV] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_OV);
        else if (austinf.s.ZUGRUND[ZU_WAHL_STELLER] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_WS);
        else if (austinf.s.ZUGRUND[ZU_NO_QTY_NR] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_NO_RAB_QTY);
        else if (austinf.s.ZUGRUND[ZU_NO_CICS] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_SHORT_NO_CICS);
        else if (austinf.s.ZUGRUND[ZU_NULL_DOKU] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_NULL_DOKU);
        else if (austinf.s.ZUGRUND[ZU_HIGH_VALUE] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_HIGH_VALUE);
        if (austinf.s.ZUGRUND[ZU_INVENTUR_HERST] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_IV);
        if (austinf.s.ZUGRUND[ZU_INVENTUR_KONSIG] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_IV);

        char str[260] = { 0 };
        sprintf(str, "%d", austinf.s.IDFNR);
        s[COL_IDF] = str;

        AllgEntfSpaces(austinf.s.NAMEAPO);
        AllgEntfSpaces(austinf.s.NAMEINHABER);
        s[COL_APO] = austinf.s.NAMEAPO;
        if (AeGetApp()->IsHR())
        {
            s[COL_APO] += " ";
            s[COL_APO] += austinf.s.NAMEINHABER;
        }
        AllgEntfSpaces(austinf.s.ORT);
        s[COL_ORT] = austinf.s.ORT;

        sprintf(str, "%d", austinf.s.KDAUFTRAGNR);
        s[COL_AUFNR] = str;

        AllgEntfSpaces(austinf.s.TOURID);
        CString ATour;
        if (atol(austinf.s.TOURID))
        {
            AllgTourAusgKonv(ATour, austinf.s.TOURID);
        }
        else
        {
            ATour = "";
        }
        s[COL_TOUR] = ATour;

        s[COL_ZZ].Empty();
        if (AeGetApp()->IsBG() && (austinf.s.PAYMENTDATE > 0))
        {
            long ldatum = (m_Datum > 0) ? m_Datum : m_ActDatum;

            CTime jetzt = CTimeFromDateLongMinTime(ldatum);
            CTime ziel = CTimeFromDateLongMinTime(austinf.s.PAYMENTDATE);
            CTimeSpan tage = ziel - jetzt;
            s[COL_ZZ].Format("%d", tage.GetDays());
        }

        CString CStr;
        CStr.Format("%s%s%s", austinf.s.KDAUFTRAGART, austinf.s.KOART, austinf.s.BUCHART);
        s[COL_AART] = CStr;

        COrdStat ordStat;
        ordStat.SetOrdStat(austinf.s.KDAUFTRAGSTAT);
        ordStat.GetOrdStatCStr(s[COL_STATUS]);
        sprintf(str, "%ld", austinf.s.ANZPOS);
        s[COL_POS] = str;
        sprintf(str, "%ld", austinf.s.ANZPOSDAFUE);
        s[COL_ZD] = str;
        AllgEntfSpaces(austinf.s.GERAETNAME);
        s[COL_TRM] = austinf.s.GERAETNAME;
        char timeStr[81];
        austinf.s.ZEITERSTEGUELTIGK /= 1000;
        s[COL_TIME] = ppGTimeLongToCharHHMM(austinf.s.ZEITERSTEGUELTIGK, timeStr);
        s[COL_VZ].Format("%d", austinf.s.VERTRIEBSZENTRUMNR);
        s[COL_VSE].Format("%d", austinf.s.KDAUFTRAGNRFILIALE);
        s[COL_ZUGRUND] = austinf.s.ZUGRUND;    //zwichenspeichern
        AllgEntfSpaces(austinf.s.ORDERLABEL);
        s[COL_ORDERLABEL] = austinf.s.ORDERLABEL;
        sprintf(str, "%ld", austinf.s.ORDERPERIODID);
        s[COL_ORDERPERIODID] = str;
        char dateStr[81];
        s[COL_DATUM] = AllgDatumLong2CharTTMMJJJJ(austinf.s.DATUMAUSLIEFERUNG, dateStr);
        if (AeGetApp()->IsBG())
        {
            s[COL_RECHNR] = austinf.s.INVOICENUMBER;
        }
        else
        {
            s[COL_RECHNR].Format("%d", austinf.s.RECHNUNGNR);
        }
        s[COL_DD].Format("%d", austinf.s.DATUM);
        s[COL_DATE].Format("%d", austinf.s.DATUM);    //hier der Longwert für weitere Bearbeitung
        s[COL_WAITIBT].Format("%d", austinf.s.WAITFORIBTPICKING);
        s[COL_IVCNO].Empty();
        //Check ob Auftragart mit IVC-Nummer
        if (GetOrderType().IsAufArtIVCNo(AeGetApp()->VzNr(), austinf.s.KDAUFTRAGART))
        {
            FormatRelationNo(s[COL_IVCNO], 2, austinf.s.KDAUFTRAGNR);
        }
        //Check ob Auftragart mit orginal Rechnungs-Nummer
        if (GetOrderType().IsAufArtOriginalInvoiceNo(AeGetApp()->VzNr(), austinf.s.KDAUFTRAGART))
        {
            FormatRelationNo(s[COL_IVCNO], 3, austinf.s.KDAUFTRAGNR);
        }

        int VSEStatus = 0;  // VSE-Fehlerstatus
        if ((austinf.s.SENDESTATUS > 1) && (austinf.s.SENDESTATUS < 5)) // Defekte von VSE
        {
            VSEStatus = austinf.s.SENDESTATUS - 1;
        }
        else if (austinf.s.SENDESTATUS == 7)
        {
            VSEStatus = 4;
        }

        int auftyp = 0;

        if (AeGetApp()->IsBG())
        {
            if (   (s[COL_STATUS] == CResString::ex().getStrTblText(AETXT_ORDSTAT_FAKTURENDE))
                || (s[COL_STATUS] == CResString::ex().getStrTblText(AETXT_ORDSTAT_ERFASST)) )
            {
                if (m_Datum == 0)
                {
                    CAUFTRAGWERTE aufwerte;
                    aufwerte.SetKdauftragnr(austinf.s.KDAUFTRAGNR);
                    aufwerte.SelWerte();
                    auftyp = GetAufTypToValue(
                        (aufwerte.GetOrdvalftaxfsdisc() + aufwerte.GetOrdvalltaxfsdisc()),
                        (aufwerte.GetOrdvalftaxhfdisc() + aufwerte.GetOrdvalltaxhfdisc()),
                        (aufwerte.GetOrdvalftaxrsdisc() + aufwerte.GetOrdvalltaxrsdisc()) );
                }
                else
                {
                    CAUFTRAGWERTEALT aufwertealt;
                    aufwertealt.SetKdauftragnr(austinf.s.KDAUFTRAGNR);
                    aufwertealt.SetDatum(m_Datum);
                    aufwertealt.SelWerte();
                    auftyp = GetAufTypToValue(
                        (aufwertealt.GetOrdvalftaxfsdisc() + aufwertealt.GetOrdvalltaxfsdisc()),
                        (aufwertealt.GetOrdvalftaxhfdisc() + aufwertealt.GetOrdvalltaxhfdisc()),
                        (aufwertealt.GetOrdvalftaxrsdisc() + aufwertealt.GetOrdvalltaxrsdisc()) );
                }
            }
            if (auftyp == 9)
            {
                auftyp = 0;
                VSEStatus = 9;
            }
        }

        int index;
        if (!CListCtrlHelper::GetAppendImageItem(m_ListCtl, NUM_COLUMNS, s, VSEStatus, index))
        {
            EndWaitCursor();
            return false;
        }
        if (ipro == 1)
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_AART, 5);
        }
        if (austinf.s.WAITFORIBTPICKING == 1)
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_AART, WAITFORIBT);
        }
        // Ronnie
        if (AeGetApp()->IsBG() && (auftyp > 0))
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_AART, auftyp);
        }
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
    EndWaitCursor();

    return true;
}

void CDAufInf::FormatRelationNo(CString& ivcNo, short relationNoType, long orderno)
{
    if (m_Datum == 0)
    {
        CSPECIALNUMBERS ivc;
        ivc.SetCscorderno(orderno);
        ivc.SetRelationnotype(relationNoType);
        if (!ivc.SelNumber())
        {
            ivcNo.Format("%d", ivc.GetRelationno());
        }
    }
    else
    {
        CSPECIALNUMBERSOLD ivcold;
        ivcold.SetCscorderno(orderno);
        ivcold.SetRelationnotype(relationNoType);
        ivcold.SetDate(m_Datum);
        if (!ivcold.SelNumber())
        {
            ivcNo.Format("%d", ivcold.GetRelationno());
        }
    }
}

/*static*/
int CDAufInf::GetAufTypToValue(double aufTyp6Value, double aufTyp7Value, double aufTyp8Value)
{
    if (aufTyp6Value > 0)
    {
        return 6;
    }
    if (aufTyp7Value > 0)
    {
        return 7;
    }
    if (aufTyp8Value > 0)
    {
        return 8;
    }
    return 9;
}

long CDAufInf::GetStatus(int statLisPos, CString& ordStatus)
{
        if (statLisPos == 4)
        {
            ordStatus = AEORD_ERFASST;
            return ORD_ERFASST;
        }
        else if (statLisPos == 3)
        {
            ordStatus = AEORD_ZURUECKGESTELLT;
            return ORD_ZURUECKGESTELLT   ;
        }
        else if (statLisPos == 1)
        {
            ordStatus = AEORD_STORNIERT;
            return ORD_STORNIERT;
        }
        else if (statLisPos == 2)
        {
            ordStatus = AEORD_ZURUECKGEST_DAFUE;
            return ORD_DAFUE_FEHLER;
        }
        else if (statLisPos == 5)
        {
            ordStatus = AEORD_KOMMI_ENDE;
            return ORD_KOMMI_ENDE;
        }
        else if (statLisPos == 6)
        {
            ordStatus = AEORD_FAKTUR_ENDE;
            return ORD_FAKTUR_ENDE;
        }
        else if (statLisPos == 7)
        {
            ordStatus = AEORD_IN_KOMMI;
            return ORD_IN_KOMMI;
        }
        else if (statLisPos == 8)
        {
            ordStatus = AEORD_BEREIT_ZUR_FAKTUR;
            return ORD_BEREIT_ZUR_FAKTUR;
        }
        else if (statLisPos == 9)
        {
            ordStatus = AEORD_IN_ERFASSUNG;
            return ORD_IN_ERFASSUNG;
        }
        else if (statLisPos == 10)
        {
            ordStatus = AEORD_IN_AENDERUNG;
            return ORD_IN_AENDERUNG;
        }
        else if (statLisPos == 11)
        {
            ordStatus = AEORD_ALLESTATIS;
            return ORD_DELAYED_DELIVERY;
        }
        else if (statLisPos == 12)
        {
            ordStatus = AEORD_ALLESTATIS;
            return ORD_DELAYED_KL;
        }
        else if (statLisPos == 0)
        {
            ordStatus = AEORD_ALLESTATIS;
            return ORD_UNBEKANNT;
        }
        else
        {
            ordStatus = AEORD_ALLESTATIS;
            return ORD_UNBEKANNT;
        }
}

void CDAufInf::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST_CTRL))
    {
        SetAuftrNr();
        return;
    }
    CloseCursor();
    GetPage();
}

void CDAufInf::OnButtonKnd()
{
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CString CStr;
    CStr.Format("%ld", dlgKndWahl.GetIdfNr());
    GetDlgItem(IDC_EDIT_IDF)->SetWindowText(CStr);
    CloseCursor();
    GetPage();
}

void CDAufInf::OnChangeEditIdf()
{
    AllgWertKontr(&m_EditKndNr, MAXIMUM_IDF);
}

void CDAufInf::OnChangeEditTour()
{
   AllgLaengeKontr(&m_EditTour, MAXIMUM_ANZ_TOUR,AeGetApp()->Modus());
}

void CDAufInf::MarkListPosChar(int Letter)
{
    int pos;
    if (CListCtrlHelper::GetListPositionByChar(m_ListCtl, Letter, pos))
    {
        CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, pos);
    }
}

void CDAufInf::OnKeydownListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl, false);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (!CLetterMan::InAZRange(pLVKeyDow->wVKey))
    {
        return;
    }

    MarkListPosChar((int)(pLVKeyDow->wVKey));
    if ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000)
    {
        CString CStr, VZ, ZuGrund;
        //CDInfAnzAuft dlgInfAnzAuft;
        CDOrderInformation dlgOrderInformation;
        dlgOrderInformation.m_bSelProforma = m_bSelProforma;
        dlgOrderInformation.m_AuftrNr = GetAuftrNr(CStr, VZ, ZuGrund);
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            if (m_bSelProforma)
            {
                dlgOrderInformation.m_Datum = atol(m_ListCtl.GetItemText(pos, COL_DD));
            }
            else
            {
                dlgOrderInformation.m_Datum = m_Datum;
            }

            dlgOrderInformation.m_cRechnr = m_ListCtl.GetItemText(pos, COL_RECHNR);
        }
        dlgOrderInformation.m_ActDatum = m_ActDatum;
        if ((dlgOrderInformation.m_AuftrNr != 0) && (dlgOrderInformation.DoModal() == IDOK))
            CDialogMultiLang::OnCancel();
        return;
    }

    *pResult = 1L;
}

void CDAufInf::OnDblclkListCtrl(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SetAuftrNr();
    *pResult = 0L;
}

long CDAufInf::GetAuftrNr(CString& Status, CString& VZ, CString& ZuGrund)
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return 0;
    }
    AeGetApp()->IsMSV3 = false;
    AeGetApp()->IsCMI = false;
    CString AufNr = m_ListCtl.GetItemText(pos, COL_AUFNR);
    Status = m_ListCtl.GetItemText(pos, COL_STATUS);
    VZ = m_ListCtl.GetItemText(pos, COL_VZ);
    ZuGrund = m_ListCtl.GetItemText(pos, COL_ZUGRUND);
    if (!m_ListCtl.GetItemText(pos, COL_ORDERLABEL).IsEmpty())
        AeGetApp()->IsMSV3 = true;
    if (std::strstr(m_ListCtl.GetItemText(pos, COL_AART), "DG") != NULL)
        AeGetApp()->IsCMI = true;
    return atol(AufNr);
}

void CDAufInf::SetAuftrNr()
{
    CString Status;
    CString VZ;
    CString ZuGrund;
    m_AufNr = GetAuftrNr(Status,VZ,ZuGrund);
    bool m_bNoOpen = false;
    if (   ZuGrund.GetAt(ZU_INVENTUR_HERST) == '1'
        && (   (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_ZURUECKG))
            || (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_DFZURUECKG))
            || (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_INERFASSUNG)) ) )
    {
        CCHECKORDERIV check;
        check.SetKdauftragnr(m_AufNr);
        if (!check.SelManu())
            m_bNoOpen = true;
    }
    else if (   ZuGrund.GetAt(ZU_INVENTUR_KONSIG) == '1'
             && (   (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_ZURUECKG))
                 || (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_DFZURUECKG))
                 || (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_INERFASSUNG)) ) )
    {
        CCHECKORDERIV check;
        check.SetKdauftragnr(m_AufNr);
        if (!check.SelKonsig())
            m_bNoOpen = true;
    }
    if (m_AufNr == 0)
        return;
    bool bMSV3 = false;
    bool bWaitIBT = false;
    CString Orderlabel;
    CPARAUFBEARB paraaufbearb;
    paraaufbearb.s.FILIALNR = (short)atoi(VZ);
    paraaufbearb.Server( AafilSelaufbearb );
    AeGetApp()->IsStopCrema = (paraaufbearb.s.SSTOPCREMA == 1);

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        Orderlabel = m_ListCtl.GetItemText(pos, COL_ORDERLABEL);
        if (atoi(m_ListCtl.GetItemText(pos, COL_WAITIBT)) > 0)
            bWaitIBT = true;
    }
    if (   (   (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_ZURUECKG))
            || (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_DFZURUECKG))
            || (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_INERFASSUNG)) )
        && !GetAeUser().KeinPlan() )
    {
        if (!Orderlabel.IsEmpty())
        {
            if (!GetAeUser().IsMSV3bearb() && !GetAeUser().IsMSV3bearbNo())
            {
                bMSV3 = true;
            }
            else
            {
                CCHECKORDERLABEL label;
                label.SetKdauftragnr(m_AufNr);
                label.SelLabelType();
                if (label.GetOrderlabeltyp() == 2 && !GetAeUser().IsMSV3bearb())
                {
                    bMSV3 = true;
                }
            }
            if (!bMSV3)
            {
                if (MsgBoxYesNo(AETXT_NUR_ANZEIGE, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDYES)
                {
                    bMSV3 = true;
                }
            }
        }
    }

    if (   (   (Status != CResString::ex().getStrTblText(AETXT_ORDSTAT_ZURUECKG))
            && (Status != CResString::ex().getStrTblText(AETXT_ORDSTAT_DFZURUECKG))
            && (Status != CResString::ex().getStrTblText(AETXT_ORDSTAT_INERFASSUNG)) )
        || m_Datum != 0
        || (GetAeUser().IsOnlyInfo() && !GetAeUser().IsAeUser())
        || (   ZuGrund.GetAt(ZU_KREDITLIMIT) == '1'
            && AeGetApp()->IsCrema() && !AeGetApp()->IsStopCrema() )
        || m_bNoOpen
        || bMSV3
        || bWaitIBT )
    {
        if (!GetAeUser().KeinPlan())
        {
            if (   ZuGrund.GetAt(ZU_KREDITLIMIT) == '1'
                && GetAeUser().IsCremaChangeTour()
                && AeGetApp()->IsCrema()
                && !AeGetApp()->IsStopCrema()
                && (   (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_ZURUECKG))
                    || (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_DFZURUECKG))
                    || (Status == CResString::ex().getStrTblText(AETXT_ORDSTAT_INERFASSUNG)) ) )
            {
                CCHECKKLRELEASED rel;
                rel.SetKdauftragnr(m_AufNr);    //Auftrag bereits freigegeben ?
                if (!rel.SelReleased())
                {
                    if (MsgBoxYesNo(AETXT_CHANGE_TOUR_KL, MB_ICONEXCLAMATION | MB_DEFBUTTON1) == IDYES)
                    {
                        //Neue Touränderungsmaske aufrufen um Tour zu ändern
                        CAUFTRAG auftrag;
                        auftrag.s.KDAUFTRAGNR = m_AufNr;
                        BeginWaitCursor();
                        auftrag.Server(AasrvOpenorder, PIPE_AE_SRV);
                        EndWaitCursor();
                        if (auftrag.rc < SRV_OK)
                            return;
                        CDChangeTour changetour;
                        changetour.m_pAuftrag = &auftrag;
                        changetour.DoModal();
                        auftrag.s.STATUS = ORD_UNBEDINGT;
                        auftrag.Server(AasrvCloseorder, PIPE_AE_SRV);
                        return;
                    }
                }
            }
        }

        //CDInfAnzAuft dlgInfAnzAuft;
        CDOrderInformation dlgOrderInformation;
        dlgOrderInformation.m_LAuftNr = atol(m_CLauftnr);
        dlgOrderInformation.m_AuftrNr = m_AufNr;
        if (pos >= 0)
        {
            dlgOrderInformation.m_lDatumAuftrag = atol(m_ListCtl.GetItemText(pos, COL_DATE));
        }
        if (m_bSelProforma)
        {
            int pos2 = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
            if (pos2 >= 0)
            {
                dlgOrderInformation.m_Datum = atol(m_ListCtl.GetItemText(pos2, COL_DD));
            }
        }
        else
        {
            dlgOrderInformation.m_Datum = m_Datum;
        }
        if (pos >= 0)
        {
            dlgOrderInformation.m_cRechnr = m_ListCtl.GetItemText(pos, COL_RECHNR);
        }
        dlgOrderInformation.m_bSelProforma = m_bSelProforma;
        dlgOrderInformation.m_bNoOpen = m_bNoOpen;
        dlgOrderInformation.m_cIVCnr = m_ListCtl.GetItemText(pos, COL_IVCNO);
        dlgOrderInformation.OrderLabel = Orderlabel;
        dlgOrderInformation.m_ActDatum = m_ActDatum;

        if (dlgOrderInformation.DoModal() == IDOK)
            CDialogMultiLang::OnCancel();
        return;
    }
    if (!GetAeUser().IsMehrVz())
    {
        if (atoi(VZ) != AeGetApp()->VzNr())
        {
            MsgBoxOK(IDP_OPEN_NUR_EIGEN);
            return;
        }
    }
    if (ZuGrund.GetAt(ZU_KREDITLIMIT) == '1' && !GetAeUser().IsKreditAbschluss())
    {
        MsgBoxOK(IDP_NO_OPEN_DEBLIMIT);
        return;
    }
    else if (ZuGrund.GetAt(ZU_INTERNET) == '1' && !GetAeUser().IsInternetAbschluss())
    {
        MsgBoxOK(IDP_NO_OPEN_INTERNET);
        return;
    }
    else if (ZuGrund.GetAt(ZU_BTM) == '1' && !GetAeUser().IsAbschlussBTM())
    {
        MsgBoxOK(IDP_NO_OPEN_BTM);
        return;
    }
    else if (ZuGrund.GetAt(ZU_BACKROUTING) == '1' && AeGetApp()->VzNr() != atoi(VZ))
    {
        MsgBoxOK(IDP_OPEN_NUR_EIGEN);
        return;
    }
    CDialogMultiLang::OnOK();
}

void CDAufInf::OnChangeEditAuftrNr()
{
    AllgWertKontr(&m_EditOrderNr, MAXIMUM_AUFTRAG_NR);
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDAufInf::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    LRESULT res = CPageBrowser::OnHookNextPrev(lpMsg);
    if (res != 0L)
    {
        return res;
    }

    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        CKndInf kndInf;
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString CStr = m_ListCtl.GetItemText(pos, COL_IDF);
            kndInf.SetIdfNr(atol(CStr));
            //nase VZ muß noch über select korrekt versorgt werden
            CStr = m_ListCtl.GetItemText(pos, COL_VZ);
            kndInf.SetKndVz(static_cast<short>(atoi(CStr)));
            kndInf.DoModal();
            return 1L;                      //Message wird nicht weitergeleitet
        }
        if (!m_KndNr.IsEmpty())
        {
            kndInf.SetIdfNr(atol(m_KndNr));
            //nase VZ muß noch über select korrekt versorgt werden
            kndInf.SetKndVz(AeGetApp()->VzNr());
            kndInf.DoModal();
            return 1L;                      //Message wird nicht weitergeleitet
        }
    }
    return 0;
}

void CDAufInf::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    m_bSelProforma = FALSE;
    CAUSTINF austinf;
    austinf.s.DATUM = m_Datum;
    austinf.s.FETCH_REL = 0;
    BeginWaitCursor();
    austinf.Server(m_Funktion);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDAufInf::OnDestroy()
{
    AllgWriteColumnWidthUser(m_ListCtl, "CDAufInf", KEY_PATH, NUM_COLUMNS);
    AeGetApp()->IsMSV3 = m_bMSV3; //auf alten Zustand zurücksetzen
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDAufInf::OnChangeEditDatum()
{
    AllgDatumKontr(&m_EditDatum,ALGF_FORM_DATUM_TTMMJJ);
}

void CDAufInf::OnButtonDruck()
{
    if (m_bFirstDataset) return;
    CDruckAuftrag druckAuftrag;
    CAUSTINF austinf;
    CString liste;
    CString ATour;
    COrdStat ordStat;
    CString hilfe;
    char underline[122];
    char timeStr[81];
    int satzzahl;
    memset(underline, '-', 121);
    underline[121] = '\0';
    liste.Format("%-7.7s %-26.26s %-26.26s %-6.6s %-8.8s %-2.2s %-3.3s %-3.3s %-3.3s %-4.4s %-8.8s %-2.2s %-5.5s",
        CResString::ex().getStrTblText(AETXT_IDF_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_APOTHEKENNAME).GetString(),
        CResString::ex().getStrTblText(AETXT_ORT).GetString(),
        CResString::ex().getStrTblText(AETXT_AUF_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_TOUR).GetString(),
        CResString::ex().getStrTblText(AETXT_A_ART).GetString(),
        CResString::ex().getStrTblText(AETXT_GRST).GetString(),
        CResString::ex().getStrTblText(AETXT_POS).GetString(),
        CResString::ex().getStrTblText(AETXT_ZEILEN_DAFUE_KZ).GetString(),
        CResString::ex().getStrTblText(AETXT_TRM).GetString(),
        CResString::ex().getStrTblText(IDS_TIME).GetString(),
        CResString::ex().getStrTblText(AETXT_VZ).GetString(),
        CResString::ex().getStrTblText(AETXT_AUF_NR_FIL).GetString() );

    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    druckAuftrag.AddFussZeile(liste);

    austinf.s.FETCH_REL = GetFetchStartPosition();
    BeginWaitCursor();
    for (satzzahl = 0;;satzzahl++)
    {
        austinf.s.DATUM = m_Datum;
        austinf.Server(m_Funktion);
        if (austinf.rc != SRV_OK)
            break;
        austinf.s.FETCH_REL = 1;
        ordStat.SetOrdStat(austinf.s.KDAUFTRAGSTAT);
        ordStat.GetOrdStatCStr(hilfe);
        AllgEntfSpaces(austinf.s.TOURID);
        if (austinf.s.ZEITERSTEGUELTIGK > 23999999) austinf.s.ZEITERSTEGUELTIGK /= 1000;
        else if (austinf.s.ZEITERSTEGUELTIGK > 239999) austinf.s.ZEITERSTEGUELTIGK /= 100;
        if (atol(austinf.s.TOURID))
        {
            AllgTourAusgKonv(ATour, austinf.s.TOURID);
        }
        else
        {
            ATour = "";
        }

        liste.Format("%-7.7ld %-26.26s %-26.26s %6.6ld %-8.8s %-2.2s %-3.3s %3.3ld %3.3ld %-4.4s %-8.8s %-2.2d %-5.5d",
            austinf.s.IDFNR,
            austinf.s.NAMEAPO,
            austinf.s.ORT,
            austinf.s.KDAUFTRAGNR,
            ATour.GetString(),
            austinf.s.KDAUFTRAGART,
            hilfe.GetString(),
            austinf.s.ANZPOS,
            austinf.s.ANZPOSDAFUE,
            austinf.s.GERAETNAME,
            ppGTimeLongToCharHHMM(austinf.s.ZEITERSTEGUELTIGK, timeStr),
            austinf.s.VERTRIEBSZENTRUMNR,
            austinf.s.KDAUFTRAGNRFILIALE);
        druckAuftrag.AddPosZeile(liste);
    }
    austinf.s.FETCH_REL = GetFetchPosition(satzzahl);
    if (austinf.s.FETCH_REL != 0)
    {
        austinf.s.DATUM = m_Datum;
        austinf.Server(m_Funktion);
    }
    EndWaitCursor();
    druckAuftrag.Druck(2);
    druckAuftrag.DelAllData();
}

void CDAufInf::OnChangeEditRechnNr()
{
    if (AeGetApp()->IsBG())
    {
        AllgLaengeKontr(&m_EditRechnNr, MAXIMUM_LENG_RECHNUNGS_NR);
    }
    else
    {
        AllgWertKontr(&m_EditRechnNr, MAXIMUM_RECHNUNGS_NR);
    }
    UpdateData();
}

void CDAufInf::OnChangeEditLauftNr()
{
    AllgWertKontr(&m_EditLauftnr, MAXIMUM_RECHNUNGS_NR);
    UpdateData();
}

void CDAufInf::OnButtonPzn()
{
    CDArtDef dlgArtDef;
    if (dlgArtDef.DoModal() != IDOK)
        return;
    m_CPzn = dlgArtDef.GetArticleCode();
    GetDlgItem(IDC_EDIT_PZN)->SetWindowText(m_CPzn);
    CloseCursor();
    GetPage();
}

/*wenn gleich die listbox gefüllt wird, muss der Cursor auch in der Listbox gesetzt
  werden, da aber vom Layout die Taborder im IDF-Edit feld beginnt, muss man zu diesem
  Trick greifen, weil der Cursor erst bei Anzeigen des Fensters gesetzt wird */
void CDAufInf::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialogMultiLang::OnShowWindow(bShow, nStatus);
    if (m_bDirectSelect)
    {
        GotoDlgCtrl(GetDlgItem(IDC_LIST_CTRL));
       m_bDirectSelect = false;
    }
}

void CDAufInf::OnCheckVz()
{
    AeGetApp()->IsKundeHome = IsDlgButtonChecked(IDC_CHECK_VZ) ? true : false;
}

void CDAufInf::OnButtonSelect()
{
    CloseCursor();
    GetPage();
}

void CDAufInf::OnChangeEditAuftrNrFili()
{
    AllgWertKontr(&m_EditOrderNrFili, MAXIMUM_AUFTRAG_NR);
}

void CDAufInf::OnCbnSelchangeComboStatus()
{
    UpdateData();
    if (m_ComboStatus == 11)
    {
        GetDlgItem(IDC_STATIC_DD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_STATIC_DD)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_DATETIMEPICKER_DD)->ShowWindow(SW_HIDE);
    }
}

void CDAufInf::OnLvnColumnclickListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
    int col = 0;

    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    col = pNMListView->iSubItem;
    if (m_bSelProforma)  //kein Sort bei Proforma-Select
    {
        *pResult = 0L;
        return;
    }
    if (col == COL_ZG) m_Sort = "zugrund";
    else if (col == COL_IDF) m_Sort = "kunde.idfnr";
    else if (col == COL_APO) m_Sort = "kunde.nameapo";
    else if (col == COL_ORT) m_Sort = "kunde.ort";
    else if (col == COL_AUFNR) m_Sort = "kdauftragnr";
    else if (col == COL_TOUR) m_Sort = "tourid";
    else if (col == COL_AART) m_Sort = "kdauftragart";
    else if (col == COL_POS) m_Sort = "anzpos";
    else if (col == COL_ZD) m_Sort = "anzposdafue";
    else if (col == COL_TRM) m_Sort = "geraetname";
    else if (col == COL_VSE) m_Sort = "kdauftragnrfiliale";
    else if (col == COL_ORDERLABEL) m_Sort = "orderlabel desc";
    else if (col == COL_ORDERPERIODID) m_Sort = "orderperiodid";
    else if (col == COL_RECHNR)
    {
        m_Sort = AeGetApp()->IsBG() ? "invoicenumber" : "rechnungnr";
    }
    if (!m_bCursorOpen)
    {
        *pResult = 0L;
        return;
    }
    CloseCursor();
    GetPage();

    *pResult = 0L;
}

void CDAufInf::OnBnClickedButtonProforma()
{
    CloseCursor();
    m_bSelProforma = TRUE;
    GetPage();
}
