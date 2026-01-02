// DAufAuswahl.cpp : implementation file
//

#include "stdafx.h"
#include "DAufAuswahl.h"
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
#include "DChangeTour.h"
#include <orders.h>

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
#define COL_DATUM_DD        17
#define COL_RECHNR          18
#define COL_DATUM_AUF       19
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
    COL_DATUM_DD,      "",   0, LVCFMT_LEFT,
    COL_RECHNR,        "",  50, LVCFMT_RIGHT,
    COL_DATUM_AUF,     "",   0, LVCFMT_LEFT,
    COL_ORDERLABEL,    "",  60, LVCFMT_LEFT,
    COL_ORDERPERIODID, "",  40, LVCFMT_LEFT,
    COL_IVCNO,         "",  70, LVCFMT_LEFT,
    COL_DATE,          "",   0, LVCFMT_LEFT,
    COL_WAITIBT,       "",   0, LVCFMT_LEFT,
    -1,                "",   0, 0
};

// CDAufAuswahl dialog

IMPLEMENT_DYNAMIC(CDAufAuswahl, CDialog)

CDAufAuswahl::CDAufAuswahl(CWnd* pParent /*=NULL*/,
                   const bool bDirectSelect /*=false*/)
    : CDialogMultiLang(CDAufAuswahl::IDD, pParent)
    , m_CT_DD(0), CPageBrowser(ZEILEN)
{
    m_KndNr = _T("");
    m_Tour = _T("");
    m_ComboStatus = -1;
    m_COrderNr = _T("");
    m_COrderNrOnly = _T("");
    m_CTermID = _T("");
    m_CDatum = _T("");
    m_RechnNr = _T("");
    m_CPzn = _T("");
    m_COrderNrFili = _T("");
    m_COrderNrFiliOnly = _T("");
    m_SapReferenceNo = _T("");
    m_ComboStatus = 0;
    m_AufNr = 0;
    m_Funktion = 0;
    m_bDirectSelect = bDirectSelect;
    m_IdfNr = 0;
    m_lKndNr = 0;
    m_Sort = _T("");
    m_bSelProforma = false;
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
    Columns[COL_DATUM_DD].Columns = CResString::ex().getStrTblText(AETXT_DATUM_DD);
    Columns[COL_RECHNR].Columns = CResString::ex().getStrTblText(AETXT_RECHNUNG_NR);
    Columns[COL_DATUM_AUF].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[COL_ORDERLABEL].Columns = CResString::ex().getStrTblText(AETXT_ORDERLABEL);
    Columns[COL_ORDERPERIODID].Columns = CResString::ex().getStrTblText(AETXT_ORDERPERIODID);
    if (AeGetApp()->IsDE())
        Columns[COL_IVCNO].Columns = CResString::ex().getStrTblText(AETXT_IVC_NO);
    else if (AeGetApp()->IsFR())
        Columns[COL_IVCNO].Columns = CResString::ex().getStrTblText(AETXT_ORGINVOICE);
    Columns[COL_DATE].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[COL_WAITIBT].Columns = CResString::ex().getStrTblText(AETXT_WAIT__IBT);
}


CDAufAuswahl::~CDAufAuswahl()
{
}

void CDAufAuswahl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_AUFTR_NR_FILI, m_EditOrderNrFili);
    DDX_Control(pDX, IDC_EDIT_AUFTR_NR_FILI_ONLY, m_EditOrderNrFiliOnly);
    DDX_Control(pDX, IDC_CHECK_VZ, m_CheckVz);
    DDX_Control(pDX, IDC_CHECK_AKTUELL, m_CheckAktuell);
    DDX_Control(pDX, IDC_CHECK_HISTORY, m_CheckHistory);
    DDX_Control(pDX, IDC_EDIT_PZN, m_EditPzn);
    DDX_Control(pDX, IDC_EDIT_RECHN_NR, m_EditRechnNr);
    DDX_Control(pDX, IDC_EDIT_DATUM, m_EditDatum);
    DDX_Control(pDX, IDC_EDIT_TERMINAL, m_EditTermID);
    DDX_Control(pDX, IDC_EDIT_AUFTR_NR, m_EditOrderNr);
    DDX_Control(pDX, IDC_EDIT_AUFTR_NR_ONLY, m_EditOrderNrOnly);
    DDX_Control(pDX, IDC_EDIT_TOUR, m_EditTour);
    DDX_Control(pDX, IDC_EDIT_IDF, m_EditKndNr);
    DDX_Control(pDX, IDC_LIST_CTRL, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_IDF, m_KndNr);
    DDX_Text(pDX, IDC_EDIT_TOUR, m_Tour);
    DDX_Control(pDX, IDC_COMBO_KDAUFTRAGART, m_ComboKdAArt);
    DDX_CBIndex(pDX, IDC_COMBO_STATUS, m_ComboStatus);
    DDX_Text(pDX, IDC_EDIT_AUFTR_NR, m_COrderNr);
    DDX_Text(pDX, IDC_EDIT_AUFTR_NR_ONLY, m_COrderNrOnly);
    DDX_Text(pDX, IDC_EDIT_TERMINAL, m_CTermID);
    DDX_Text(pDX, IDC_EDIT_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_EDIT_RECHN_NR, m_RechnNr);
    DDX_Text(pDX, IDC_EDIT_PZN, m_CPzn);
    DDX_Text(pDX, IDC_EDIT_AUFTR_NR_FILI, m_COrderNrFili);
    DDX_Text(pDX, IDC_EDIT_AUFTR_NR_FILI_ONLY, m_COrderNrFiliOnly);
    DDX_Text(pDX, IDC_EDIT_SAP_REFERENCE_NO, m_SapReferenceNo);
    DDX_Control(pDX, IDC_COMBO_STATUS, m_Combobox_Status);
    DDX_Control(pDX, IDC_COMBO_BRANCHNO, m_Combobox_Branchno);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DD, m_DT_DD);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DD, m_CT_DD);
    DDX_Control(pDX, IDC_EDIT_SAP_REFERENCE_NO, m_EditSapReferenceNo);
    DDX_Control(pDX, IDC_STATIC_SAP_REFERENCE_NO, m_StaticSapReferenceNo);
}


BEGIN_MESSAGE_MAP(CDAufAuswahl, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnButtonKnd)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnChangeEditIdf)
    ON_EN_CHANGE(IDC_EDIT_TOUR, OnChangeEditTour)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CTRL, OnKeydownListCtrl)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_CTRL, OnDblclkListCtrl)
    ON_EN_CHANGE(IDC_EDIT_AUFTR_NR, OnChangeEditAuftrNr)
    ON_EN_CHANGE(IDC_EDIT_AUFTR_NR_ONLY, OnChangeEditAuftrNrOnly)
    ON_WM_DESTROY()
    ON_EN_CHANGE(IDC_EDIT_DATUM, OnChangeEditDatum)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_EN_CHANGE(IDC_EDIT_RECHN_NR, OnChangeEditRechnNr)
    ON_BN_CLICKED(IDC_BUTTON_PZN, OnButtonPzn)
    ON_EN_CHANGE(IDC_EDIT_PZN, OnChangeEditPzn)
    ON_WM_SHOWWINDOW()
    ON_BN_CLICKED(IDC_CHECK_VZ, OnCheckVz)
    ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
    ON_EN_CHANGE(IDC_EDIT_AUFTR_NR_FILI, OnChangeEditAuftrNrFili)
    ON_EN_CHANGE(IDC_EDIT_AUFTR_NR_FILI_ONLY, OnChangeEditAuftrNrFiliOnly)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_CBN_SELCHANGE(IDC_COMBO_STATUS, OnCbnSelchangeComboStatus)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CTRL, OnLvnColumnclickListCtrl)
    ON_BN_CLICKED(IDC_BUTTON_PROFORMA, OnBnClickedButtonProforma)
    ON_BN_CLICKED(IDC_CHECK_AKTUELL, OnCheckAktuell)
    ON_BN_CLICKED(IDC_CHECK_HISTORY, OnCheckHistory)
    ON_EN_CHANGE(IDC_EDIT_SAP_REFERENCE_NO, OnChangeEditSapReferenceNo)
END_MESSAGE_MAP()


// CDAufAuswahl message handlers

BOOL CDAufAuswahl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    AeGetApp()->m_AeLogging.WriteLine(1, "CDAufAuswahl.cpp", "AuftragsAnzeige", "Dialog started");

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

    m_Combobox_Branchno.AddString(CResString::ex().getStrTblText(AETXT_ALL_BRANCHES));

    CREGIONBRANCHES regio;
    regio.SetRegionnr(AeGetApp()->VzNr());
    for (;;)
    {
        if (regio.SelList() != SRV_OK)
            break;

        CString fili;
        ppString ort;
        fili.Format("%d %s", regio.GetRegionteilnr(), regio.GetStandort_lang(ort));
        m_Combobox_Branchno.AddString(fili);
        if (m_Regionliste.IsEmpty())
            m_Regionliste.Format("%d", regio.GetRegionteilnr());
        else
            m_Regionliste.AppendFormat(",%d", regio.GetRegionteilnr());
    }
    m_Combobox_Branchno.SetCurSel(0);
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
    GetDlgItem(IDC_STATIC_ORD_NR_FIL)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_EDIT_AUFTR_NR_FILI)->ShowWindow(SW_SHOW);
    //GetDlgItem(IDC_STATIC_ORD_NR)->SetWindowTextA( CResString::ex().getStrTblText(AETXT_NUR_AUFNR));
    //GetDlgItem(IDC_STATIC_ORD_NR_FIL)->SetWindowTextA( CResString::ex().getStrTblText(AETXT_NUR_AUFNR_FILI));

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
    //idResources.push_back(IDI_ICON_WAIT_IBT);
    idResources.push_back(IDI_ICON_IBT_WAIT);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    AllgSetColumnWidthUser(m_ListCtl, "CDAufInf", KEY_PATH, NUM_COLUMNS);
    m_CheckAktuell.SetCheck(TRUE);
    m_CheckHistory.SetCheck(FALSE);
    if (AeGetApp()->IsKundeHome() || !GetAeUser().IsMehrVz())
    {
        m_CheckVz.SetCheck(TRUE);
        GetDlgItem(IDC_STATIC_BRANCHNO)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_BRANCHNO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_BRANCHNO)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_BRANCHNO)->ShowWindow(SW_HIDE);
    }
    if (!GetAeUser().IsMehrVz())
    {
        AeGetApp()->IsKundeHome = true;
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

    if (AeGetApp()->UseSapReferenceNo())
    {
        m_EditSapReferenceNo.ShowWindow(SW_SHOW);
        m_StaticSapReferenceNo.ShowWindow(SW_SHOW);
    }

    if (m_bDirectSelect)
        GetPage(); //nur wenn man von Ausgesteuerte Anrufe kommt!

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDAufAuswahl::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    UpdateData();

    CAUSTINF austinf;
    if (!FillServerRequest(austinf.s))
    {
        return false;
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, austinf.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();

    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        austinf.s.DATUM = m_Datum;
        austinf.Server(m_Funktion);

        m_bCursorOpen = true;       //Datenbankcurser offen
        austinf.s.FETCH_REL = 1;          //normaler Fetch
        if (austinf.rc != SRV_OK)
        {
            if (austinf.rc < SRV_OK)
            {
                break;
            }

            if (m_bFirstDataset)      //kein Satz gefunden
            {
                MsgBoxOK(IDP_KEIN_AUFTRAG);
                CloseCursor();
                EndWaitCursor();
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Artikel letzte Seite
            break;
        }
        if (m_bFirstDataset)     //kein Satz gefunden
        {
            AeGetApp()->m_AeLogging.WriteLine(1, "CDAufAuswahl.cpp", "AuftragsAnzeige", "Entries found");
        }
        m_bFirstDataset = false;

        ReadCustomer(austinf.s);

        //Ausgabe in die Listbox
        CStringArray s;
        FormatResultLine(austinf.s, kb.Next(), s);

        int vseState;
        int ordertype;
        GetOrderTypeAndVseState(austinf.s, s[COL_STATUS], vseState, ordertype);

        int index;
        if (!CListCtrlHelper::GetAppendImageItem(m_ListCtl, NUM_COLUMNS, s, vseState, index))
        {
            EndWaitCursor();
            return false;
        }
        if (IsProforma(austinf.s.KDAUFTRAGNR))
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_AART, 5);
        }
        if (austinf.s.WAITFORIBTPICKING == 1)
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_AART, WAITFORIBT);
        }
        // Ronnie
        if (AeGetApp()->IsBG() && (ordertype > 0))
        {
            CListCtrlHelper::SetImageItem(m_ListCtl, index, COL_AART, ordertype);
        }
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
    EndWaitCursor();
    return true;
}

bool CDAufAuswahl::FillServerRequest(AUSTINF& austinf)
{
    austinf.AKTUELL[0] = IsDlgButtonChecked(IDC_CHECK_AKTUELL) ? '1' : '0';

    austinf.HISTORY[0] = IsDlgButtonChecked(IDC_CHECK_HISTORY) ? '1' : '0';

    austinf.FETCH_REL = 1;

    austinf.ONLYORDER[0] = m_COrderNrOnly.IsEmpty() ? '0' : '1';
    austinf.KDAUFTRAGNR = atol(m_COrderNrOnly.IsEmpty() ? m_COrderNr : m_COrderNrOnly);

    CString CStrOrdStat;
    long status = GetStatus(m_ComboStatus, CStrOrdStat);

    CString TermIdEigen = GetAeUser().GetTermID();
    if (!m_CTermID.IsEmpty())
    {
        if (   !GetAeUser().IsAnzAuf()
            && (m_CTermID.GetAt(0) != AeGetApp()->Letter_Z())
            && (TermIdEigen != m_CTermID))
        {
            CStrOrdStat = AEORD_IN_ERFASSUNG;
        }
        m_CTermID += "%";
    }
    AllgStrCopy(austinf.GERAETNAME, m_CTermID, L_AUSTINF_GERAETNAME);
    AllgStrCopy(austinf.KDAUFTRAGSTAT, CStrOrdStat, L_AUSTINF_KDAUFTRAGSTAT);
    if (m_CDatum.IsEmpty())
    {
        austinf.DATUM = 0;
        m_Datum = 0;
    }
    else
    {
        austinf.DATUM = AllgDatumEingKonv(m_CDatum, ALGF_FORM_DATUM_TTMMJJ);
        if (austinf.DATUM < 0)
        {
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_DATUM));
            return false;
        }
        m_Datum = austinf.DATUM;
    }

    m_lKndNr = atol(m_KndNr);
    austinf.KUNDENNR = m_lKndNr;
    austinf.REGIONNR = AeGetApp()->VzNr();

    if (AeGetApp()->IsKundeHome())
    {
        austinf.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    }
    else
    {
        int filpos;
        CString branchtext;
        filpos = m_Combobox_Branchno.GetCurSel();
        m_Combobox_Branchno.GetLBText(filpos, branchtext);
        austinf.VERTRIEBSZENTRUMNR = static_cast<short>(atoi(branchtext.Left(2)));
        strcpy(austinf.REGIONLIST, m_Regionliste);
    }

    austinf.ANZPOS = atol(m_RechnNr);
    strcpy(austinf.INVOICENUMBER, m_RechnNr);
    if (m_CPzn.IsEmpty())
    {
        austinf.ZEITENDEAM = 0;
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
        austinf.ZEITENDEAM = code.s.ARTIKEL_NR;
    }
    strcpy(austinf.TOURID, m_Tour);

    // neues where- Kriterium kdauftrag.kdauftragart
    CString KdAuftrArt;

    if (m_ComboKdAArt.GetCurSel() > 0)
    {
        m_ComboKdAArt.GetLBText(m_ComboKdAArt.GetCurSel(), KdAuftrArt);
    }

    strcpy(austinf.KDAUFTRAGART, KdAuftrArt);
    if (m_Sort.IsEmpty())
    {
        m_Sort = (!m_COrderNrFili.IsEmpty() || !m_COrderNrFiliOnly.IsEmpty()) ? "17" : "1";
    }
    strcpy(austinf.SORTFIELD, m_Sort);

    austinf.KDAUFTRAGNRFILIALE = m_COrderNrFiliOnly.IsEmpty() ? atol(m_COrderNrFili) : atol(m_COrderNrFiliOnly);
    austinf.ONLYORDERFILI[0] = m_COrderNrFiliOnly.IsEmpty() ? '0' : '1';

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        memset(austinf.ZUGRUND, ' ', L_AUFTRAG_ZUGRUND);
        //a.s.ZUGRUND[0] = '%';
        m_Funktion = m_bSelProforma ? AaauftSelProLink : AaauftSelList_Auftrag; // hier wird bereits nur nach kdauftragart = PF gesucht.
        austinf.BATCHSCHREIBEN = 1;
        AeGetApp()->m_AeLogging.WriteLine(1, "CDAufAuswahl.cpp", "AuftragsAnzeige", "Start search");
    }

    if (status == ORD_DELAYED_DELIVERY)
    {
        austinf.DATUMAUSLIEFERUNG = (m_CT_DD.GetYear() * 10000 +
                               m_CT_DD.GetMonth() * 100 +
                               m_CT_DD.GetDay());
    }
    if (status == ORD_DELAYED_KL)
    {
        memset(austinf.ZUGRUND, '_', L_AUFTRAG_ZUGRUND);
        austinf.ZUGRUND[ZU_KREDITLIMIT] = '1';
    }

    strcpy(austinf.SAP_REFERENCENO, m_SapReferenceNo.Trim());

    return true;
}

void CDAufAuswahl::ReadCustomer(AUSTINF& austinf)
{
    //Hier Kunde lesen
    CKNDSEL kndsel;
    kndsel.s.KUNDENNR = austinf.IDFNR;
    kndsel.s.VERTRIEBSZENTRUMNR = austinf.VERTRIEBSZENTRUMNR;
    kndsel.s.SKDKUNDEAEGESPERRT[0] = '1';
    kndsel.s.SKDKUNDEAEGESPERRT[1] = '\0';
    kndsel.Server(AakundeSel_kndnr);
    if (kndsel.rc != SRV_OK)  //sollte eigentlich nicht passieren
    {
        austinf.NAMEAPO[0] = '\0';
        austinf.ORT[0] = '\0';
        austinf.KZKDKLASSE[0] = '\0';
        austinf.NAMEINHABER[0] = '\0';
    }
    else
    {
        AllgEntfSpaces(kndsel.s.NAMEAPO);
        AllgEntfSpaces(kndsel.s.NAMEINHABER);
        AllgEntfSpaces(kndsel.s.ORT);
        AllgEntfSpaces(kndsel.s.KZKDKLASSE);
        sprintf(austinf.NAMEAPO, "%s", kndsel.s.NAMEAPO);
        sprintf(austinf.NAMEINHABER, "%s", kndsel.s.NAMEINHABER);
        sprintf(austinf.ORT, "%s", kndsel.s.ORT);
        sprintf(austinf.KZKDKLASSE, "%s", kndsel.s.KZKDKLASSE);
    }
}

void CDAufAuswahl::FormatResultLine(AUSTINF& austinf, char* kb, CStringArray& s)
{
    s.SetSize(NUM_COLUMNS);

    s[COL_KB] = kb;
    s[COL_ZG].Empty();
    if (austinf.ZUGRUND[ZU_KREDITLIMIT] == '1')
    {
        CCHECKKLRELEASED rel;
        rel.SetKdauftragnr(austinf.KDAUFTRAGNR);    //Auftrag bereits freigegeben ?
        s[COL_ZG] = CResString::ex().getStrTblText(rel.SelReleased() ? AETXT_SHORT_KREDITLIMIT : AETXT_SHORT_KREDITLIMIT_FREI);
    }
    else if (austinf.ZUGRUND[ZU_INTERNET] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_SHORT_INTERNET);
    else if (austinf.ZUGRUND[ZU_BACKROUTING] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_SHORT_BACKROUTING);
    else if (austinf.ZUGRUND[ZU_DD_OHNE] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_SHORT_DD);
    else if (austinf.ZUGRUND[ZU_BTM] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_BTM);
    else if (austinf.ZUGRUND[ZU_OV] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_OV);
    else if (austinf.ZUGRUND[ZU_WAHL_STELLER] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_WS);
    else if (austinf.ZUGRUND[ZU_NO_QTY_NR] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_NO_RAB_QTY);
    else if (austinf.ZUGRUND[ZU_NO_CICS] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_SHORT_NO_CICS);
    else if (austinf.ZUGRUND[ZU_NULL_DOKU] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_NULL_DOKU);
    else if (austinf.ZUGRUND[ZU_HIGH_VALUE] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_HIGH_VALUE);
    if (austinf.ZUGRUND[ZU_INVENTUR_HERST] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_IV);
    if (austinf.ZUGRUND[ZU_INVENTUR_KONSIG] == '1') s[COL_ZG] = CResString::ex().getStrTblText(AETXT_ZU_IV);

    s[COL_IDF].Format("%d", austinf.IDFNR);

    AllgEntfSpaces(austinf.NAMEAPO);
    s[COL_APO] = austinf.NAMEAPO;
    if (AeGetApp()->IsHR())
    {
        s[COL_APO] += " ";
        s[COL_APO] += austinf.NAMEINHABER;
    }

    AllgEntfSpaces(austinf.ORT);
    s[COL_ORT] = austinf.ORT;

    s[COL_AUFNR].Format("%d", austinf.KDAUFTRAGNR);

    AllgEntfSpaces(austinf.TOURID);
    CString ATour;
    if (atol(austinf.TOURID))
    {
        AllgTourAusgKonv(ATour, austinf.TOURID);
    }
    s[COL_TOUR] = ATour;

    s[COL_AART].Format("%s%s%s", austinf.KDAUFTRAGART, austinf.KOART, austinf.BUCHART);

    s[COL_ZZ].Empty();
    if (AeGetApp()->IsBG() && (austinf.PAYMENTDATE > 0))
    {
        long ldatum = (m_Datum > 0) ? m_Datum : m_ActDatum;
        CTime jetzt = CTimeFromDateLongMinTime(ldatum);
        CTime ziel = CTimeFromDateLongMinTime(austinf.PAYMENTDATE);
        CTimeSpan tage = ziel - jetzt;
        s[COL_ZZ].Format("%d", tage.GetDays());
    }

    COrdStat ordStat;
    ordStat.SetOrdStat(austinf.KDAUFTRAGSTAT);
    ordStat.GetOrdStatCStr(s[COL_STATUS]);

    s[COL_POS].Format("%ld", austinf.ANZPOS);

    s[COL_ZD].Format("%ld", austinf.ANZPOSDAFUE);

    AllgEntfSpaces(austinf.GERAETNAME);
    s[COL_TRM] = austinf.GERAETNAME;

    char timeStr[81];
    austinf.ZEITERSTEGUELTIGK /= 1000;
    s[COL_TIME] = ppGTimeLongToCharHHMM(austinf.ZEITERSTEGUELTIGK, timeStr);

    s[COL_VZ].Format("%d", austinf.VERTRIEBSZENTRUMNR);

    s[COL_VSE].Format("%d", austinf.KDAUFTRAGNRFILIALE);

    s[COL_ZUGRUND] = austinf.ZUGRUND;    //zwichenspeichern

    AllgEntfSpaces(austinf.ORDERLABEL);
    s[COL_ORDERLABEL] = austinf.ORDERLABEL;

    s[COL_ORDERPERIODID].Format("%ld", austinf.ORDERPERIODID);

    char dateStrDD[81];
    s[COL_DATUM_DD] = (austinf.DATUMAUSLIEFERUNG > 0) ? AllgDatumLong2CharTTMMJJJJ(austinf.DATUMAUSLIEFERUNG, dateStrDD) : "";

    if (AeGetApp()->IsBG())
    {
        s[COL_RECHNR] = austinf.INVOICENUMBER;
    }
    else
    {
        s[COL_RECHNR].Format("%d", austinf.RECHNUNGNR);
    }

    char dateStr[81];
    s[COL_DATUM_AUF] = (austinf.DATUM > 0) ? AllgDatumLong2CharTTMMJJJJ(austinf.DATUM, dateStr) : "";

    s[COL_DATE].Format("%d", austinf.DATUM);    //hier der Longwert für weitere Bearbeitung

    s[COL_WAITIBT].Format("%d", austinf.WAITFORIBTPICKING);

    s[COL_IVCNO].Empty();
    //Check ob Auftragart mit IVC-Nummer
    if (GetOrderType().IsAufArtIVCNo(AeGetApp()->VzNr(), austinf.KDAUFTRAGART))
    {
        s[COL_IVCNO] = FormatRelationNo(2, austinf);
    }
    //Check ob Auftragart mit orginal Rechnungs-Nummer
    if (GetOrderType().IsAufArtOriginalInvoiceNo(AeGetApp()->VzNr(), austinf.KDAUFTRAGART))
    {
        s[COL_IVCNO] = FormatRelationNo(3, austinf);
    }
}

void CDAufAuswahl::GetOrderTypeAndVseState(AUSTINF& austinf, CString state, int& vseState, int& ordertype)
{
    if ((austinf.SENDESTATUS > 1) && (austinf.SENDESTATUS < 5)) // Defekte von VSE
    {
        vseState = austinf.SENDESTATUS - 1;
    }
    else if (austinf.SENDESTATUS == 7)
    {
        vseState = 4;
    }
    else
    {
        vseState = 0;
    }

    ordertype = 0;

    if (AeGetApp()->IsBG())
    {
        if (   (state == CResString::ex().getStrTblText(AETXT_ORDSTAT_FAKTURENDE))
            || (state == CResString::ex().getStrTblText(AETXT_ORDSTAT_ERFASST)))
        {
            if (m_Datum == 0)
            {
                CAUFTRAGWERTE aufwerte;
                aufwerte.SetKdauftragnr(austinf.KDAUFTRAGNR);
                aufwerte.SelWerte();
                ordertype = GetAufTypToValue(
                    (aufwerte.GetOrdvalftaxfsdisc() + aufwerte.GetOrdvalltaxfsdisc()),
                    (aufwerte.GetOrdvalftaxhfdisc() + aufwerte.GetOrdvalltaxhfdisc()),
                    (aufwerte.GetOrdvalftaxrsdisc() + aufwerte.GetOrdvalltaxrsdisc()));
            }
            else
            {
                CAUFTRAGWERTEALT aufwertealt;
                aufwertealt.SetKdauftragnr(austinf.KDAUFTRAGNR);
                aufwertealt.SetDatum(m_Datum);
                aufwertealt.SelWerte();
                ordertype = GetAufTypToValue(
                    (aufwertealt.GetOrdvalftaxfsdisc() + aufwertealt.GetOrdvalltaxfsdisc()),
                    (aufwertealt.GetOrdvalftaxhfdisc() + aufwertealt.GetOrdvalltaxhfdisc()),
                    (aufwertealt.GetOrdvalftaxrsdisc() + aufwertealt.GetOrdvalltaxrsdisc()));
            }
        }
        if (ordertype == 9)
        {
            ordertype = 0;
            vseState = 9;
        }
    }
}

/*static*/
int CDAufAuswahl::GetAufTypToValue(double aufTyp6Value, double aufTyp7Value, double aufTyp8Value)
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

bool CDAufAuswahl::IsProforma(long orderno)
{
    if (AeGetApp()->IsRS())
    {
        //if (!strncmp(a.s.KDAUFTRAGART, "PF", 2))
        {
            if ((m_Datum == 0) && !m_bSelProforma)
            {
                CPROLINKACT proact;
                proact.SetKdauftragnr(orderno);
                if (proact.SelProLink() != SRV_OK)
                {
                    return true;
                }
            }

            CPROLINK pro;
            pro.SetKdauftragnr(orderno);
            pro.SetDatum(m_Datum);
            if (pro.SelProLink() != SRV_OK)
            {
                return true;
            }
        }
    }
    return false;
}

CString CDAufAuswahl::FormatRelationNo(short relationNoType, AUSTINF& austinf)
{
    CString ivcNo;

    if (austinf.DATUM == m_ActDatum)
    {
        CSPECIALNUMBERS ivc;
        ivc.SetCscorderno(austinf.KDAUFTRAGNR);
        ivc.SetRelationnotype(relationNoType);
        if (!ivc.SelNumber())
        {
            ivcNo.Format("%d", ivc.GetRelationno());
        }
    }
    else
    {
        CSPECIALNUMBERSOLD ivcold;
        ivcold.SetCscorderno(austinf.KDAUFTRAGNR);
        ivcold.SetRelationnotype(relationNoType);
        ivcold.SetDate(austinf.DATUM);
        if (!ivcold.SelNumber())
        {
            ivcNo.Format("%d", ivcold.GetRelationno());
        }
    }
    return ivcNo;
}

long CDAufAuswahl::GetStatus(int StatLisPos, CString& OrdStatus)
{
        if (StatLisPos == 4)
        {
            OrdStatus = AEORD_ERFASST;
            return ORD_ERFASST;
        }
        else if (StatLisPos == 3)
        {
            OrdStatus = AEORD_ZURUECKGESTELLT;
            return ORD_ZURUECKGESTELLT   ;
        }
        else if (StatLisPos == 1)
        {
            OrdStatus = AEORD_STORNIERT;
            return ORD_STORNIERT;
        }
        else if (StatLisPos == 2)
        {
            OrdStatus = AEORD_ZURUECKGEST_DAFUE;
            return ORD_DAFUE_FEHLER;
        }
        else if (StatLisPos == 5)
        {
            OrdStatus = AEORD_KOMMI_ENDE;
            return ORD_KOMMI_ENDE;
        }
        else if (StatLisPos == 6)
        {
            OrdStatus = AEORD_FAKTUR_ENDE;
            return ORD_FAKTUR_ENDE;
        }
        else if (StatLisPos == 7)
        {
            OrdStatus = AEORD_IN_KOMMI;
            return ORD_IN_KOMMI;
        }
        else if (StatLisPos == 8)
        {
            OrdStatus = AEORD_BEREIT_ZUR_FAKTUR;
            return ORD_BEREIT_ZUR_FAKTUR;
        }
        else if (StatLisPos == 9)
        {
            OrdStatus = AEORD_IN_ERFASSUNG;
            return ORD_IN_ERFASSUNG;
        }
        else if (StatLisPos == 10)
        {
            OrdStatus = AEORD_IN_AENDERUNG;
            return ORD_IN_AENDERUNG;
        }
        else if (StatLisPos == 11)
        {
            OrdStatus = AEORD_ALLESTATIS;
            return ORD_DELAYED_DELIVERY;
        }
        else if (StatLisPos == 12)
        {
            OrdStatus = AEORD_ALLESTATIS;
            return ORD_DELAYED_KL;
        }
        else if (StatLisPos == 0)
        {
            OrdStatus = AEORD_ALLESTATIS;
            return ORD_UNBEKANNT;
        }
        else
        {
            OrdStatus = AEORD_ALLESTATIS;
            return ORD_UNBEKANNT;
        }
}

void CDAufAuswahl::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST_CTRL))
    {
        SetAuftrNr();
        return;
    }
    CloseCursor();
    if (!CheckCriteria())
    {
        MsgBoxOK( AETXT_MUST_CRITERIA );
        return;
    }
    //m_Sort.Empty();   //wird frisch versorgt
    GetPage();
}

void CDAufAuswahl::OnButtonKnd()
{
    CString CStr;
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CStr.Format("%ld",dlgKndWahl.GetIdfNr());
    GetDlgItem(IDC_EDIT_IDF)->SetWindowText(CStr);
    CloseCursor();
    GetPage();
}

void CDAufAuswahl::OnChangeEditIdf()
{
    AllgWertKontr(&m_EditKndNr, MAXIMUM_IDF);
}

void CDAufAuswahl::OnChangeEditTour()
{
   AllgLaengeKontr(&m_EditTour, MAXIMUM_ANZ_TOUR,AeGetApp()->Modus());
}

void CDAufAuswahl::MarkListPosChar(int Letter)
{
    int pos;
    if (CListCtrlHelper::GetListPositionByChar(m_ListCtl, Letter, pos))
    {
        CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, pos);
    }
}

void CDAufAuswahl::OnKeydownListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (OnKeydownList(pNMHDR, pResult, m_ListCtl, false))
    {
        return;
    }

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (!CLetterMan::InAZRange(pLVKeyDow->wVKey))
    {
        return;
    }

    MarkListPosChar((int)(pLVKeyDow->wVKey));
    if ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000)
    {
        CString CStr,VZ,ZuGrund;
        //CDInfAnzAuft dlgInfAnzAuft;
        CDOrderInformation dlgOrderInformation;
        dlgOrderInformation.m_bSelProforma = m_bSelProforma;
        dlgOrderInformation.m_AuftrNr = GetAuftrNr(CStr,VZ,ZuGrund);
        dlgOrderInformation.m_ActDatum = m_ActDatum;

        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            long ldatum = atol(m_ListCtl.GetItemText(pos, COL_DATE));
            if (m_bSelProforma)
            {
                dlgOrderInformation.m_Datum = ldatum;
            }
            else
            {
                dlgOrderInformation.m_Datum = (m_ActDatum == ldatum) ? 0 : ldatum;
            }

            dlgOrderInformation.m_cRechnr = m_ListCtl.GetItemText(pos, COL_RECHNR);
        }
        if ((dlgOrderInformation.m_AuftrNr != 0) && (dlgOrderInformation.DoModal() == IDOK))
        {
            AeGetApp()->m_AeLogging.WriteLine(1, "CDAufAuswahl.cpp", "AuftragsAnzeige", "Dialog canceled");
            CDialogMultiLang::OnCancel();
        }
        return;
    }

    *pResult = 1L;
}

void CDAufAuswahl::OnDblclkListCtrl(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SetAuftrNr();
    *pResult = 0L;
}

long CDAufAuswahl::GetAuftrNr(CString& Status, CString& VZ, CString& ZuGrund)
{
    CString AufNr;

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return 0;
    }
    AeGetApp()->IsMSV3 = false;
    AeGetApp()->IsCMI = false;
    AufNr  = m_ListCtl.GetItemText(pos, COL_AUFNR);
    Status = m_ListCtl.GetItemText(pos, COL_STATUS);
    VZ = m_ListCtl.GetItemText(pos, COL_VZ);
    ZuGrund = m_ListCtl.GetItemText(pos, COL_ZUGRUND);
    if (!m_ListCtl.GetItemText(pos, COL_ORDERLABEL).IsEmpty())
        AeGetApp()->IsMSV3 = true;
    if (std::strstr(m_ListCtl.GetItemText(pos, COL_AART), "DG") != NULL)
        AeGetApp()->IsCMI = true;
    return atol(AufNr);
}

void CDAufAuswahl::SetAuftrNr()
{
    CString status;
    CString vz;
    CString zuGrund;
    m_AufNr = GetAuftrNr(status, vz, zuGrund);
    if (m_AufNr == 0)
    {
        return;
    }

    bool bNoOpen = false;
    if (IsDeferredOrRecording(status))
    {
        if (zuGrund.GetAt(ZU_INVENTUR_HERST) == '1')
        {
            CCHECKORDERIV check;
            check.SetKdauftragnr(m_AufNr);
            if (check.SelManu() != SRV_OK)
                bNoOpen = true;
        }
        else if (zuGrund.GetAt(ZU_INVENTUR_KONSIG) == '1')
        {
            CCHECKORDERIV check;
            check.SetKdauftragnr(m_AufNr);
            if (check.SelKonsig() != SRV_OK)
                bNoOpen = true;
        }
    }

    CPARAUFBEARB paraaufbearb;
    paraaufbearb.s.FILIALNR = (short)atoi(vz);
    paraaufbearb.Server(AafilSelaufbearb);
    AeGetApp()->IsStopCrema = (paraaufbearb.s.SSTOPCREMA == 1);

    bool bWaitIBT = false;
    CString orderlabel;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        orderlabel = m_ListCtl.GetItemText(pos, COL_ORDERLABEL);
        if (atoi(m_ListCtl.GetItemText(pos, COL_WAITIBT)) > 0)
            bWaitIBT = true;
    }
    bool bMSV3 = false;
    if (IsDeferredOrRecording(status) && !GetAeUser().KeinPlan())
    {
        if (!orderlabel.IsEmpty())
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

    long ldatum = m_Datum;
    if (pos >= 0)
    {
        ldatum = atol(m_ListCtl.GetItemText(pos, COL_DATE));
        if (m_ActDatum == ldatum)
        {
            ldatum = 0;
        }
    }
    if (   !IsDeferredOrRecording(status)
        || ldatum != 0
        || (GetAeUser().IsOnlyInfo() && !GetAeUser().IsAeUser())
        || ((zuGrund.GetAt(ZU_KREDITLIMIT) == '1') && AeGetApp()->IsCrema() && !AeGetApp()->IsStopCrema())
        || bNoOpen
        || bMSV3
        || bWaitIBT )
    {
        if (   !GetAeUser().KeinPlan()
            && (zuGrund.GetAt(ZU_KREDITLIMIT) == '1') && AeGetApp()->IsCrema() && !AeGetApp()->IsStopCrema()
            && GetAeUser().IsCremaChangeTour()
            && IsDeferredOrRecording(status) )
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

        OpenOrderInformationDlg(bNoOpen, pos, ldatum, orderlabel);
        return;
    }
    if (!GetAeUser().IsMehrVz() && (AeGetApp()->VzNr() != atoi(vz)))
    {
        MsgBoxOK(IDP_OPEN_NUR_EIGEN);
        return;
    }
    if ((zuGrund.GetAt(ZU_KREDITLIMIT) == '1') && !GetAeUser().IsKreditAbschluss())
    {
        MsgBoxOK(IDP_NO_OPEN_DEBLIMIT);
        return;
    }
    if ((zuGrund.GetAt(ZU_INTERNET) == '1') && !GetAeUser().IsInternetAbschluss())
    {
        MsgBoxOK(IDP_NO_OPEN_INTERNET);
        return;
    }
    if ((zuGrund.GetAt(ZU_BTM) == '1') && !GetAeUser().IsAbschlussBTM())
    {
        MsgBoxOK(IDP_NO_OPEN_BTM);
        return;
    }
    if ((zuGrund.GetAt(ZU_BACKROUTING) == '1') && (AeGetApp()->VzNr() != atoi(vz)))
    {
        MsgBoxOK(IDP_OPEN_NUR_EIGEN);
        return;
    }
    if (GetAeUser().KeinPlan())
    {
        OpenOrderInformationDlg(bNoOpen, pos, ldatum, orderlabel);
        return;
    }
    CDialogMultiLang::OnOK();
}

bool CDAufAuswahl::IsDeferredOrRecording(CString status)
{
    return (status == CResString::ex().getStrTblText(AETXT_ORDSTAT_ZURUECKG))
        || (status == CResString::ex().getStrTblText(AETXT_ORDSTAT_DFZURUECKG))
        || (status == CResString::ex().getStrTblText(AETXT_ORDSTAT_INERFASSUNG));
}

void CDAufAuswahl::OpenOrderInformationDlg(bool bNoOpen, int pos, long ldatum, CString orderlabel)
{
    CDOrderInformation dlgOrderInformation;
    dlgOrderInformation.m_AuftrNr = m_AufNr;
    if (pos >= 0)
    {
        dlgOrderInformation.m_lDatumAuftrag = atol(m_ListCtl.GetItemText(pos, COL_DATE));
    }
    if (m_bSelProforma)
    {
        if (pos >= 0)
        {
            dlgOrderInformation.m_Datum = atol(m_ListCtl.GetItemText(pos, COL_DATE));
        }
    }
    else
    {
        dlgOrderInformation.m_Datum = ldatum;
    }
    if (pos >= 0)
    {
        dlgOrderInformation.m_cRechnr = m_ListCtl.GetItemText(pos, COL_RECHNR);
    }
    dlgOrderInformation.m_bSelProforma = m_bSelProforma;
    dlgOrderInformation.m_bNoOpen = bNoOpen;
    dlgOrderInformation.m_cIVCnr = m_ListCtl.GetItemText(pos, COL_IVCNO);
    dlgOrderInformation.OrderLabel = orderlabel;
    dlgOrderInformation.m_ActDatum = m_ActDatum;

    if (dlgOrderInformation.DoModal() == IDOK)
    {
        AeGetApp()->m_AeLogging.WriteLine(1, "CDAufAuswahl.cpp", "AuftragsAnzeige", "Dialog canceled");
        CDialogMultiLang::OnCancel();
    }
}

void CDAufAuswahl::OnChangeEditAuftrNr()
{
    AllgWertKontr(&m_EditOrderNr, MAXIMUM_AUFTRAG_NR);
}

void CDAufAuswahl::OnChangeEditAuftrNrOnly()
{
    AllgWertKontr(&m_EditOrderNrOnly, MAXIMUM_AUFTRAG_NR);
}

void CDAufAuswahl::OnChangeEditSapReferenceNo()
{
    AllgLaengeKontr(&m_EditSapReferenceNo, L_AUSTINF_SAP_REFERENCENO, AeGetApp()->Modus());
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDAufAuswahl::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
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

void CDAufAuswahl::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    m_bSelProforma = false;
    CAUSTINF austinf;
    austinf.s.DATUM = m_Datum;
    austinf.s.FETCH_REL = 0;
    BeginWaitCursor();
    austinf.Server(m_Funktion);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDAufAuswahl::OnDestroy()
{
    AllgWriteColumnWidthUser(m_ListCtl, "CDAufInf", KEY_PATH, NUM_COLUMNS);
    AeGetApp()->IsMSV3 = m_bMSV3; //auf alten Zustand zurücksetzen
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDAufAuswahl::OnChangeEditDatum()
{
    AllgDatumKontr(&m_EditDatum, ALGF_FORM_DATUM_TTMMJJ);
}

void CDAufAuswahl::OnButtonDruck()
{
    if (m_bFirstDataset)
        return;
    CDruckAuftrag druckAuftrag;
    CAUSTINF austinf;
    CString liste;
    CString hilfe;
    char underline[122];
    char timeStr[81];
    int satzzahl;
    memset(underline, '-', 121);
    underline[121] = '\0';
    liste.Format("%-7.7s %-26.26s %-25.25s %-6.6s %-8.8s %-2.2s %-3.3s %-3.3s %-3.3s %-4.4s %-5.5s %-2.2s %-5.5s",
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

    CKNDSEL kndsel;
    austinf.s.FETCH_REL = GetFetchStartPosition();
    BeginWaitCursor();
    for (satzzahl = 0;; satzzahl++)
    {
        austinf.s.DATUM = m_Datum;
        austinf.Server(m_Funktion);
        if (austinf.rc != SRV_OK)
            break;
        austinf.s.FETCH_REL = 1;
        COrdStat ordStat;
        ordStat.SetOrdStat(austinf.s.KDAUFTRAGSTAT);
        ordStat.GetOrdStatCStr(hilfe);
        AllgEntfSpaces(austinf.s.TOURID);
        if (austinf.s.ZEITERSTEGUELTIGK > 23999999)
            austinf.s.ZEITERSTEGUELTIGK /= 1000;
        else if (austinf.s.ZEITERSTEGUELTIGK > 239999)
            austinf.s.ZEITERSTEGUELTIGK /= 100;
        CString ATour;
        if (atol(austinf.s.TOURID))
        {
            AllgTourAusgKonv(ATour, austinf.s.TOURID);
        }

        //Hier Kunde lesen
        kndsel.s.KUNDENNR = austinf.s.IDFNR;
        kndsel.s.VERTRIEBSZENTRUMNR = austinf.s.VERTRIEBSZENTRUMNR;
        kndsel.s.SKDKUNDEAEGESPERRT[0] = '1';
        kndsel.s.SKDKUNDEAEGESPERRT[1] = '\0';
        kndsel.Server(AakundeSel_kndnr);
        if (kndsel.rc != SRV_OK) //sollte eigentlich nicht passieren
        {
            austinf.s.NAMEAPO[0] = '\0';
            austinf.s.ORT[0] = '\0';
            austinf.s.KZKDKLASSE[0] = '\0';
        }
        else
        {
            AllgEntfSpaces(kndsel.s.NAMEAPO);
            AllgEntfSpaces(kndsel.s.ORT);
            AllgEntfSpaces(kndsel.s.KZKDKLASSE);
            sprintf(austinf.s.NAMEAPO, "%s", kndsel.s.NAMEAPO);
            sprintf(austinf.s.ORT, "%s", kndsel.s.ORT);
            sprintf(austinf.s.KZKDKLASSE, "%s", kndsel.s.KZKDKLASSE);
        }

        liste.Format("%-7.7ld %-26.26s %-25.25s %6.6ld %-8.8s %-2.2s %-3.3s %3.3ld %3.3ld %-4.4s %-5.5s %-2.2d %-5.5d",
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

void CDAufAuswahl::OnChangeEditRechnNr()
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

void CDAufAuswahl::OnButtonPzn()
{
    CDArtDef dlgArtDef;
    if (dlgArtDef.DoModal() != IDOK)
        return;
    m_CPzn = dlgArtDef.GetArticleCode();
    GetDlgItem(IDC_EDIT_PZN)->SetWindowText(m_CPzn);
    CloseCursor();
    GetPage();
}

void CDAufAuswahl::OnChangeEditPzn()
{
    //AllgWertKontr(&m_EditOrderNr, MAXIMUM_ART_NR);
}

/*wenn gleich die listbox gefüllt wird, muss der Cursor auch in der Listbox gesetzt
  werden, da aber vom Layout die Taborder im IDF-Edit feld beginnt, muss man zu diesem
  Trick greifen, weil der Cursor erst bei Anzeigen des Fensters gesetzt wird */
void CDAufAuswahl::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialogMultiLang::OnShowWindow(bShow, nStatus);
    if (m_bDirectSelect)
    {
        GotoDlgCtrl(GetDlgItem(IDC_LIST_CTRL));
        m_bDirectSelect = false;
    }

}

void CDAufAuswahl::OnCheckVz()
{
    if (IsDlgButtonChecked(IDC_CHECK_VZ))
    {
        AeGetApp()->IsKundeHome = true;
        GetDlgItem( IDC_STATIC_BRANCHNO )->EnableWindow(FALSE);
        GetDlgItem( IDC_STATIC_BRANCHNO )->ShowWindow(SW_HIDE);
        GetDlgItem( IDC_COMBO_BRANCHNO )->EnableWindow(FALSE);
        GetDlgItem( IDC_COMBO_BRANCHNO )->ShowWindow(SW_HIDE);
    }
    else
    {
        AeGetApp()->IsKundeHome = false;
        GetDlgItem( IDC_STATIC_BRANCHNO )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_BRANCHNO )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_COMBO_BRANCHNO )->EnableWindow(TRUE);
        GetDlgItem( IDC_COMBO_BRANCHNO )->ShowWindow(SW_SHOW);
    }
}

void CDAufAuswahl::OnButtonSelect()
{
    CloseCursor();
    if (!CheckCriteria())
    {
        MsgBoxOK(AETXT_MUST_CRITERIA);
        return;
    }
    GetPage();
}

void CDAufAuswahl::OnChangeEditAuftrNrFili()
{
    AllgWertKontr(&m_EditOrderNrFili, MAXIMUM_AUFTRAG_NR);
}

void CDAufAuswahl::OnChangeEditAuftrNrFiliOnly()
{
    AllgWertKontr(&m_EditOrderNrFiliOnly, MAXIMUM_AUFTRAG_NR);
}

void CDAufAuswahl::OnCbnSelchangeComboStatus()
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

void CDAufAuswahl::OnLvnColumnclickListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
    int col = 0;
    //
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    col = pNMListView->iSubItem;
    if (m_bSelProforma)  //kein Sort bei Proforma-Select
    {
        *pResult = 0L;
        return;
    }
    CString oldsort = m_Sort;
    if      (col == COL_ZG) m_Sort = "19";
    else if (col == COL_IDF) m_Sort = "3";
    else if (col == COL_AUFNR) m_Sort = "1";
    else if (col == COL_TOUR) m_Sort = "5";
    else if (col == COL_AART) m_Sort = "7";
    else if (col == COL_POS) m_Sort = "10";
    else if (col == COL_ZD) m_Sort = "11";
    else if (col == COL_DATUM_DD) m_Sort = "20";
    else if (col == COL_TRM) m_Sort = "4";
    else if (col == COL_VSE) m_Sort = "17";
    else if (col == COL_ORDERLABEL) m_Sort = "25";
    else if (col == COL_ORDERPERIODID) m_Sort = "26";
    else if (col == COL_DATUM_AUF) m_Sort = "27";
    else if (col == COL_RECHNR)
    {
        m_Sort = AeGetApp()->IsBG() ? "22" : "21";
    }
    else
    {
        *pResult = 0L;
        return;
    }

    if (oldsort.GetLength() > 2)
    {
    }
    else
    {
        if (oldsort == m_Sort)
            m_Sort += " desc"; // bei gleicher Auswahl wechseln auf absteigende Sortierung
    }

    if (!m_bCursorOpen)
    {
        *pResult = 0L;
        return;
    }
    if (!CheckCriteria())
    {
        MsgBoxOK(AETXT_MUST_CRITERIA);
        return;
    }
    CloseCursor();
    GetPage();

    *pResult = 0L;
}

void CDAufAuswahl::OnBnClickedButtonProforma()
{
    CloseCursor();
    m_bSelProforma = true;
    GetPage();
}

BOOL CDAufAuswahl::CheckCriteria()
{
    UpdateData();
    CString CStrOrdStat;
    GetStatus(m_ComboStatus, CStrOrdStat);
    if (CStrOrdStat != AEORD_ALLESTATIS)
    {
        return TRUE;
    }
    if (IsDlgButtonChecked(IDC_CHECK_AKTUELL))
    {
        return TRUE;
    }
    if (!m_CTermID.IsEmpty())
    {
        return TRUE;
    }
    if (AeGetApp()->IsKundeHome())
    {
        return TRUE;
    }
    if (!m_CPzn.IsEmpty())
    {
        return TRUE;
    }
    if (!m_RechnNr.IsEmpty())
    {
        return TRUE;
    }
    if (!m_COrderNr.IsEmpty() && IsDlgButtonChecked(IDC_CHECK_AKTUELL))
    {
        return TRUE;
    }
    if (!m_COrderNrOnly.IsEmpty())
    {
        return TRUE;
    }
    if (!m_KndNr.IsEmpty())
    {
        return TRUE;
    }
    if (!m_Tour.IsEmpty())
    {
        return TRUE;
    }
    if (m_ComboKdAArt.GetCurSel() > 0)
    {
        return TRUE;
    }
    if (!m_CDatum.IsEmpty())
    {
        return TRUE;
    }
    if (!m_COrderNrFili.IsEmpty() && IsDlgButtonChecked(IDC_CHECK_AKTUELL))
    {
        return TRUE;
    }
    if (!m_COrderNrFiliOnly.IsEmpty())
    {
        return TRUE;
    }
    if (m_bSelProforma)
    {
        return TRUE;
    }
    return FALSE;
}

void CDAufAuswahl::OnCheckAktuell()
{
    if (IsDlgButtonChecked(IDC_CHECK_AKTUELL))
    {
        if (IsDlgButtonChecked(IDC_CHECK_HISTORY))
        {
            m_CheckHistory.SetCheck(FALSE);
        }
        GetDlgItem(IDC_EDIT_AUFTR_NR)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_AUFTR_NR_FILI)->EnableWindow(TRUE);
    }
    else
    {
        m_COrderNr.Empty();
        m_COrderNrFili.Empty();
        GetDlgItem(IDC_EDIT_AUFTR_NR)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AUFTR_NR_FILI)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AUFTR_NR)->SetWindowText(m_COrderNr);
        GetDlgItem(IDC_EDIT_AUFTR_NR_FILI)->SetWindowText(m_COrderNrFili);
    }
}

void CDAufAuswahl::OnCheckHistory()
{
    if (IsDlgButtonChecked(IDC_CHECK_HISTORY))
    {
        if (IsDlgButtonChecked(IDC_CHECK_AKTUELL))
        {
            m_CheckAktuell.SetCheck(FALSE);
            m_COrderNr.Empty();
            m_COrderNrFili.Empty();
            GetDlgItem(IDC_EDIT_AUFTR_NR)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_AUFTR_NR_FILI)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_AUFTR_NR)->SetWindowText(m_COrderNr);
            GetDlgItem(IDC_EDIT_AUFTR_NR_FILI)->SetWindowText(m_COrderNrFili);
        }
    }
}
