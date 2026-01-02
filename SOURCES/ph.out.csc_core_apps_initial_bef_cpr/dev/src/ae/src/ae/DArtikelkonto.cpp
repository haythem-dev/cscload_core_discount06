// DArtikelkonto.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <statistics.h>
#include "DArtikelkonto.h"
#include <kndsel.h>
#include <controlling.h>
#include "DKndInf.h"
#include "DKndWahl.h"
#include "DArtInf.h"
#include "DAufInf.h"
#include "DArtDef.h"
#include "DDruckAuftrag.h"
#include "DAufAuswahl.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_AK_KB                0
#define NUM_AK_FIL               1
#define NUM_AK_ARTICELCODE       2
#define NUM_AK_DATUM             3
#define NUM_AK_ZEIT              4
#define NUM_AK_IDF               5
#define NUM_AK_KUNDE             6
#define NUM_AK_ART               7
#define NUM_AK_MEN               8
#define NUM_AK_MEN_NEU           9
#define NUM_AK_MEN_RESERV       10
#define NUM_AK_BELEG            11
#define NUM_AK_INVOICE          12
#define NUM_AK_UID              13
#define NUM_AK_KEY              14
#define NUM_AK_MOVE             15
#define NUM_AK_PZN              16
#define NUM_COLUMNS             17

static COLUMNS_TYPES Columns[] =
{
    NUM_AK_KB,          "",  20, LVCFMT_LEFT,
    NUM_AK_FIL,         "",  40, LVCFMT_LEFT,
    NUM_AK_ARTICELCODE, "",  60, LVCFMT_LEFT,
    NUM_AK_DATUM,       "",  70, LVCFMT_LEFT,
    NUM_AK_ZEIT,        "",  60, LVCFMT_LEFT,
    NUM_AK_IDF,         "",  60, LVCFMT_LEFT,
    NUM_AK_KUNDE,       "", 195, LVCFMT_LEFT,
    NUM_AK_ART,         "", 140, LVCFMT_LEFT,
    NUM_AK_MEN,         "",  50, LVCFMT_LEFT,
    NUM_AK_MEN_NEU,     "",  60, LVCFMT_LEFT,
    NUM_AK_MEN_RESERV,  "",   0, LVCFMT_LEFT,
    NUM_AK_BELEG,       "",  60, LVCFMT_LEFT,
    NUM_AK_INVOICE,     "",  80, LVCFMT_LEFT,
    NUM_AK_UID,         "",  40, LVCFMT_LEFT,
    NUM_AK_KEY,         "",  70, LVCFMT_LEFT,
    NUM_AK_MOVE,        "", 180, LVCFMT_LEFT,
    NUM_AK_PZN,         "",   0, LVCFMT_LEFT,
    -1,                 "",   0, 0
};

static char cBewegungsart[26][31];
static char cBewegungsartH[26][31];
static char cMoveType[13][31];

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDArtikelkonto


CDArtikelkonto::CDArtikelkonto(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDArtikelkonto::IDD, pParent)
{
    m_CArtikelNr = _T("");
    m_CFiliale = _T("");
    m_CT_DatumBis = 0;
    m_CT_DatumVon = 0;
    m_CT_ZeitBis = 0;
    m_CT_ZeitVon = 0;
    m_lActDate = 0;
    m_CIdfNr = _T("");

    Columns[NUM_AK_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[NUM_AK_FIL].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns[NUM_AK_ARTICELCODE].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[NUM_AK_DATUM].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[NUM_AK_ZEIT].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[NUM_AK_IDF].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[NUM_AK_KUNDE].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[NUM_AK_ART].Columns = CResString::ex().getStrTblText(AETXT_ART);
    Columns[NUM_AK_MEN].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[NUM_AK_MEN_NEU].Columns = CResString::ex().getStrTblText(AETXT_MENGE_NEU);
    Columns[NUM_AK_MEN_RESERV].Columns = CResString::ex().getStrTblText(AETXT_RESERVE);
    Columns[NUM_AK_BELEG].Columns = CResString::ex().getStrTblText(AETXT_BELEG_NR);
    Columns[NUM_AK_INVOICE].Columns = CResString::ex().getStrTblText(AETXT_RECHNR);
    Columns[NUM_AK_UID].Columns = CResString::ex().getStrTblText(AETXT_UID);
    Columns[NUM_AK_KEY].Columns = CResString::ex().getStrTblText(AETXT_KEY);
    Columns[NUM_AK_MOVE].Columns = CResString::ex().getStrTblText(AETXT_MOVE);
    Columns[NUM_AK_PZN].Columns = CResString::ex().getStrTblText(AETXT_PZN);
}

void CDArtikelkonto::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_IDF_NR, m_Edit_IdfNr);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
    DDX_Control(pDX, IDC_DATETIMEPICKER_ZEIT_VON, m_DT_ZeitVon);
    DDX_Control(pDX, IDC_DATETIMEPICKER_ZEIT_BIS, m_DT_ZeitBis);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DATUM_VON, m_DT_DatumVon);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DATUM_BIS, m_DT_DatumBis);
    DDX_Control(pDX, IDC_EDIT_FILIALE, m_Edit_Filiale);
    DDX_Control(pDX, IDC_EDIT_ARTIKEL_NR, m_Edit_ArtikelNr);
    DDX_Text(pDX, IDC_EDIT_ARTIKEL_NR, m_CArtikelNr);
    DDX_Text(pDX, IDC_EDIT_FILIALE, m_CFiliale);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATUM_BIS, m_CT_DatumBis);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATUM_VON, m_CT_DatumVon);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ZEIT_BIS, m_CT_ZeitBis);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ZEIT_VON, m_CT_ZeitVon);
    DDX_Text(pDX, IDC_EDIT_IDF_NR, m_CIdfNr);
}

BEGIN_MESSAGE_MAP(CDArtikelkonto, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_ARTIKEL_NR, OnChangeEditArtikelNr)
    ON_EN_CHANGE(IDC_EDIT_FILIALE, OnChangeEditFiliale)
    ON_BN_CLICKED(IDC_DRUCK, OnDruck)
    ON_EN_CHANGE(IDC_EDIT_IDF_NR, OnChangeEditIdfNr)
    ON_BN_CLICKED(IDC_BUTTON_ARTIKEL, OnButtonArtikel)
    ON_BN_CLICKED(IDC_BUTTON_KUNDE, OnButtonKunde)
    ON_BN_CLICKED(IDC_BUTTON_F6, OnButtonAufAnz)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDArtikelkonto

BOOL CDArtikelkonto::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    strcpy(cBewegungsart[0], (char*)CResString::ex().getStrTblText(AETXT_ABVERKAUF).GetString());                      //a
    strcpy(cBewegungsart[1], (char*)CResString::ex().getStrTblText(AETXT_WARENEINGANG).GetString());                   //b
    strcpy(cBewegungsart[2], (char*)CResString::ex().getStrTblText(AETXT_RETOURE_TITLE).GetString());                  //c
    strcpy(cBewegungsart[3], (char*)CResString::ex().getStrTblText(AETXT_LAGERREVISION).GetString());                  //d
    strcpy(cBewegungsart[4], (char*)CResString::ex().getStrTblText(AETXT_PERMANENTE_INVENTUR).GetString());            //e
    strcpy(cBewegungsart[5], (char*)CResString::ex().getStrTblText(AETXT_BESTANDKORREKTUR).GetString());               //f
    strcpy(cBewegungsart[6], (char*)CResString::ex().getStrTblText(AETXT_VERBUND_TITLE).GetString());                  //g
    strcpy(cBewegungsart[7], (char*)CResString::ex().getStrTblText(AETXT_OFFENE_BESTELLMENGE_EILDISPO).GetString());   //h
    strcpy(cBewegungsart[8], (char*)CResString::ex().getStrTblText(AETXT_OFFENE_BESTELLMENGE_HAUPTDISPO).GetString()); //i
    strcpy(cBewegungsart[9], (char*)CResString::ex().getStrTblText(AETXT_OFFENE_BESTELLMENGE_SONSTDISPO).GetString()); //j
    strcpy(cBewegungsart[10], (char*)CResString::ex().getStrTblText(AETXT_DEFEKT_TITLE).GetString());                  //k
    strcpy(cBewegungsart[11], (char*)CResString::ex().getStrTblText(AETXT_BESTANDKORREKTURNULL).GetString());          //l
    strcpy(cBewegungsart[12], (char*)CResString::ex().getStrTblText(AETXT_VERBUNDBUCHUNG).GetString());                //m
    strcpy(cBewegungsart[13], (char*)CResString::ex().getStrTblText(AETXT_BESTANDKORREKTURLC).GetString());            //n
    strcpy(cBewegungsart[14], (char*)CResString::ex().getStrTblText(AETXT_BESTANDKORREKTURWC).GetString());            //o
    strcpy(cBewegungsart[15], (char*)CResString::ex().getStrTblText(AETXT_DYNAMISCHES_LAGER).GetString());             //p
    strcpy(cBewegungsart[16], (char*)CResString::ex().getStrTblText(AETXT_BATCH_BESTAND).GetString());                 //q
    strcpy(cBewegungsart[17], (char*)CResString::ex().getStrTblText(AETXT_WAFO).GetString());                          //r
    strcpy(cBewegungsart[18], (char*)CResString::ex().getStrTblText(AETXT_WAFO_AUFL).GetString());                     //s
    strcpy(cBewegungsart[19], (char*)CResString::ex().getStrTblText(AETXT_VORRAUSBEZUG).GetString());                  //t
    strcpy(cBewegungsart[20], (char*)CResString::ex().getStrTblText(AETXT_RESERVIERT).GetString());                    //u
    strcpy(cBewegungsart[21], (char*)CResString::ex().getStrTblText(AETXT_KONT_DEFEKT).GetString());                   //v
    strcpy(cBewegungsart[22], (char*)CResString::ex().getStrTblText(AETXT_NL_RESERVIERUNG).GetString());               //w
    strcpy(cBewegungsart[23], (char*)CResString::ex().getStrTblText(AETXT_RESERV_ORDER).GetString());                  //x
    strcpy(cBewegungsart[24], (char*)CResString::ex().getStrTblText(AETXT_CODEBLOCAGE).GetString());                   //y
    strcpy(cBewegungsart[25], (char*)CResString::ex().getStrTblText(AETXT_STOCKTRANSFER).GetString());                 //z

    strcpy(cBewegungsartH[0], (char*)CResString::ex().getStrTblText(AETXT_POSITION_UPDATE).GetString());               //A
    strcpy(cBewegungsartH[1], " ");
    strcpy(cBewegungsartH[2], " ");
    strcpy(cBewegungsartH[3], " ");
    strcpy(cBewegungsartH[4], " ");
    strcpy(cBewegungsartH[5], " ");
    strcpy(cBewegungsartH[6], " ");
    strcpy(cBewegungsartH[7], " ");
    strcpy(cBewegungsartH[8], " ");
    strcpy(cBewegungsartH[9], " ");
    strcpy(cBewegungsartH[10], " ");
    strcpy(cBewegungsartH[11], " ");
    strcpy(cBewegungsartH[12], " ");
    strcpy(cBewegungsartH[13], " ");
    strcpy(cBewegungsartH[14], " ");
    strcpy(cBewegungsartH[15], " ");
    strcpy(cBewegungsartH[16], " ");
    strcpy(cBewegungsartH[17], " ");
    strcpy(cBewegungsartH[18], (char*)CResString::ex().getStrTblText(AETXT_WAFO_AUFL_HEUTE).GetString());              //S
    strcpy(cBewegungsartH[19], " ");
    strcpy(cBewegungsartH[20], " ");
    strcpy(cBewegungsartH[21], " ");
    strcpy(cBewegungsartH[22], " ");
    strcpy(cBewegungsartH[23], " ");
    strcpy(cBewegungsartH[24], " ");
    strcpy(cBewegungsartH[24], " ");
    strcpy(cBewegungsartH[25], " ");

    strcpy(cMoveType[0], (char*)CResString::ex().getStrTblText(AETXT_MOVE_EKG).GetString());
    strcpy(cMoveType[1], (char*)CResString::ex().getStrTblText(AETXT_MOVE_ANFRAGE).GetString());
    strcpy(cMoveType[2], (char*)CResString::ex().getStrTblText(AETXT_MOVE_NO_SELL).GetString());
    strcpy(cMoveType[3], (char*)CResString::ex().getStrTblText(AETXT_MOVE_ZERTIFIKAT).GetString());
    strcpy(cMoveType[4], (char*)CResString::ex().getStrTblText(AETXT_MOVE_BEIPACK).GetString());
    strcpy(cMoveType[5], (char*)CResString::ex().getStrTblText(AETXT_MOVE_CHARGE).GetString());
    strcpy(cMoveType[6], (char*)CResString::ex().getStrTblText(AETXT_MOVE_FROM_RESERV).GetString());
    strcpy(cMoveType[7], (char*)CResString::ex().getStrTblText(AETXT_MOVE_NACHL).GetString());
    strcpy(cMoveType[8], (char*)CResString::ex().getStrTblText(AETXT_MOVE_NACHL_RESERV).GetString());
    strcpy(cMoveType[9], (char*)CResString::ex().getStrTblText(AETXT_MOVE_VB).GetString());
    strcpy(cMoveType[10], (char*)CResString::ex().getStrTblText(AETXT_MOVE_VB_RESERV).GetString());
    strcpy(cMoveType[11], (char*)CResString::ex().getStrTblText(AETXT_MOVE_ORDER).GetString());
    strcpy(cMoveType[12], (char*)CResString::ex().getStrTblText(AETXT_MOVE_ORDER_RESERV).GetString());
    strcpy(cMoveType[13], (char*)CResString::ex().getStrTblText(AETXT_MOVE_TENDER).GetString());   //Tender
    strcpy(cMoveType[14], (char*)CResString::ex().getStrTblText(AETXT_MOVE_AUTOMAT).GetString());  //Automat
    strcpy(cMoveType[15], (char*)CResString::ex().getStrTblText(AETXT_MOVE_FMD).GetString());      //FMD

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_lActDate = zeit.s.DATUM;

    CTime end = CTimeFromDateLongMinTime(zeit.s.DATUM);

    CTimeSpan y(40, 0, 0, 0);
    if (AeGetApp()->IsBG())
    {
        CTimeSpan plus(50, 0, 0, 0);
        y += plus;
    }

    CTime ctime = end - y;
    m_DT_DatumVon.SetRange(&ctime, &end);
    m_DT_DatumVon.SetTime(&end);
    m_DT_DatumBis.SetRange(&ctime, &end);
    m_DT_DatumBis.SetTime(&end);
    m_CT_ZeitVon = CTimeFromDateLongMinTime(zeit.s.DATUM);
    m_CT_ZeitBis = CTimeFromDateLongMaxTime(zeit.s.DATUM);
    m_CFiliale.Format("%d", AeGetApp()->VzNr());

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    if (!AeGetApp()->IsBG())
    {
        m_ListCtl.SetColumnWidth(NUM_AK_KUNDE, 0);
        m_ListCtl.SetColumnWidth(NUM_AK_INVOICE, 0);
    }
    else
    {
        RepositionWindow();
    }
    CenterWindow();
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDArtikelkonto::OnChangeEditArtikelNr()
{
    //AllgWertKontr(&m_Edit_ArtikelNr, MAXIMUM_IDF);
}

void CDArtikelkonto::OnChangeEditFiliale()
{
    AllgWertKontr(&m_Edit_Filiale, MAXIMUM_FILIALNR);
}

void CDArtikelkonto::OnChangeEditIdfNr()
{
    AllgWertKontr(&m_Edit_IdfNr, MAXIMUM_IDF);
}

void CDArtikelkonto::OnOK()
{
    //Variablen
    static CARTIKELKONTOANZ artikelkontoanz;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    UpdateData();

    //Anfangsinitialisierung durchfuehren
    if (m_CArtikelNr.IsEmpty())
    {
        MsgBoxOK(IDP_NO_PZN);
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_ARTIKEL_NR));
        return;
    }
    if (m_CT_DatumVon.GetTime() > m_CT_DatumBis.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_DATUM_VON));
        return;
    }
    if (m_CT_ZeitVon.GetTime() > m_CT_ZeitBis.GetTime() &&
        m_CT_DatumVon.GetTime() == m_CT_DatumBis.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_ZEIT_VON));
        return;
    }
    artikelkontoanz.SetFilialnr(static_cast<short>(atoi(m_CFiliale)));
    CARTAESEL code;
    BeginWaitCursor();
    strcpy(code.s.ARTICLE_CODE,m_CArtikelNr);
    code.Server(AatartSel_NoByCode);
    EndWaitCursor();
    artikelkontoanz.SetArtikel_nr(code.s.ARTIKEL_NR);
    if (code.s.ARTIKEL_NR == 0)
    {
        MsgBoxOK(IDP_PZN_UNBEKANNT);
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_ARTIKEL_NR));
        return;
    }
    artikelkontoanz.SetIdfnr(atol(m_CIdfNr));
    CTime von(m_CT_DatumVon.GetYear(),
        m_CT_DatumVon.GetMonth(),
        m_CT_DatumVon.GetDay(),
        m_CT_ZeitVon.GetHour(),
        m_CT_ZeitVon.GetMinute(),
        m_CT_ZeitVon.GetSecond());
    CTime bis(m_CT_DatumBis.GetYear(),
        m_CT_DatumBis.GetMonth(),
        m_CT_DatumBis.GetDay(),
        m_CT_ZeitBis.GetHour(),
        m_CT_ZeitBis.GetMinute(),
        m_CT_ZeitBis.GetSecond());
    artikelkontoanz.SetZeitunix(static_cast<long>(von.GetTime()));
    artikelkontoanz.SetZeit_bis(static_cast<long>(bis.GetTime()));
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (artikelkontoanz.SelList() != SRV_OK) break;
        CTime ctime = artikelkontoanz.GetZeitunix();
        s[NUM_AK_KB] = kb.Next();
        s[NUM_AK_FIL].Format("%d", artikelkontoanz.GetFilialnr());
        s[NUM_AK_ARTICELCODE] = m_CArtikelNr;
        s[NUM_AK_PZN].Format("%d", code.s.ARTIKEL_NR);
        s[NUM_AK_DATUM].Format("%d.%d.%d", ctime.GetDay(), ctime.GetMonth(), ctime.GetYear());
        s[NUM_AK_ZEIT].Format("%d:%02d:%02d", ctime.GetHour(), ctime.GetMinute(), ctime.GetSecond() );
        s[NUM_AK_IDF].Format("%ld", artikelkontoanz.GetIdfnr());
        if (AeGetApp()->IsBG())
        {
            if (   (   artikelkontoanz.GetBewegungsart() == 'a'   //Abverkauf
                    || artikelkontoanz.GetBewegungsart() == 'c'   //Retoure
                    || artikelkontoanz.GetBewegungsart() == 'g'   //Verbund
                    || artikelkontoanz.GetBewegungsart() == 'k'   //Defekt
                    || artikelkontoanz.GetBewegungsart() == 'm'   //Verbund
                    || artikelkontoanz.GetBewegungsart() == 'r'   //Wafo
                    || artikelkontoanz.GetBewegungsart() == 's'   //Wafoaufloesung
                    || artikelkontoanz.GetBewegungsart() == 'u'   //Reservierung
                    || artikelkontoanz.GetBewegungsart() == 'v'   //Kontingent
                    || artikelkontoanz.GetBewegungsart() == 'w'   //Reservierung fur NL
                    || artikelkontoanz.GetBewegungsart() == 'x'   //BTM Umbuchung
                    || artikelkontoanz.GetBewegungsart() == 'S' ) //Wafoaufloesung heute
                && artikelkontoanz.GetIdfnr() > 0 )
            {
                CKNDINF kndinfo;
                kndinfo.s.VERTRIEBSZENTRUMNR = artikelkontoanz.GetFilialnr();
                kndinfo.s.KUNDENNR = artikelkontoanz.GetIdfnr();
                kndinfo.Server(AakundeSel_knd_info);
                if (kndinfo.rc < SRV_OK)
                {
                    s[NUM_AK_KUNDE].Empty();
                }
                else
                {
                    s[NUM_AK_KUNDE] = kndinfo.s.NAMEAPO;
                }
                ppString InvoiceNo;
                if (m_lActDate != (ctime.GetDay()+ctime.GetMonth()*100+ctime.GetYear()*10000))
                {
                    CINVOICENUMBEROLD rechnrold;
                    rechnrold.SetDatum(ctime.GetDay()+ctime.GetMonth()*100+ctime.GetYear()*10000);
                    rechnrold.SetKdauftragnr(artikelkontoanz.GetBelegnr());
                    if (!rechnrold.GetNumber())
                    {
                        rechnrold.GetInvoicenumber(InvoiceNo);
                        s[NUM_AK_INVOICE] = InvoiceNo;
                    }
                    else
                    {
                        s[NUM_AK_INVOICE].Empty();
                    }
                }
                else
                {
                    CINVOICENUMBER rechnr;
                    rechnr.SetKdauftragnr(artikelkontoanz.GetBelegnr());
                    if (!rechnr.GetNumber())
                    {
                        rechnr.GetInvoicenumber(InvoiceNo);
                        s[NUM_AK_INVOICE] = InvoiceNo;
                    }
                    else
                    {
                        s[NUM_AK_INVOICE].Empty();
                    }
                }
            }
            else
            {
                s[NUM_AK_KUNDE].Empty();
                s[NUM_AK_INVOICE].Empty();
            }
        }
        if (artikelkontoanz.GetBewegungsart() >= 'A' && artikelkontoanz.GetBewegungsart() <= 'Z')
        {
            s[NUM_AK_ART].Format("%s", cBewegungsartH[artikelkontoanz.GetBewegungsart() - 'A']);
        }
        else
        {
            s[NUM_AK_ART].Format("%s", cBewegungsart[artikelkontoanz.GetBewegungsart() - 'a']);
        }
        s[NUM_AK_MEN].Format("%ld", artikelkontoanz.GetMenge());
        s[NUM_AK_MEN_NEU].Format("%ld", artikelkontoanz.GetMengeneu());
        s[NUM_AK_MEN_RESERV].Format("%ld", artikelkontoanz.GetStockreserved());
        s[NUM_AK_BELEG].Format("%ld", artikelkontoanz.GetBelegnr());
        s[NUM_AK_UID].Format("%ld", artikelkontoanz.GetUid());
        s[NUM_AK_KEY].Format("%ld", artikelkontoanz.GetBewegungschluessel());
        if (artikelkontoanz.GetBewegungsart() == 'x')
        {
            s[NUM_AK_MOVE].Format("%s", cMoveType[artikelkontoanz.GetMovetype()]);
        }
        else
        {
            s[NUM_AK_MOVE].Empty();
        }

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    artikelkontoanz.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}

void CDArtikelkonto::OnDruck()
{
    CDruckAuftrag druckAuftrag;
    CString liste;

    char underline[111];
    memset(underline, '-', 110);
    underline[110] = '\0';

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    char datum[11];
    AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, datum);
    liste.Format(CResString::ex().getStrTblText(IDS_ATICLE_KONTO_LIST), datum);
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);

    liste = AeGetApp()->IsBG() ? GetHeaderLineTitlesBG() : GetHeaderLineTitles();
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);

    liste = GetBottomLine(datum);
    druckAuftrag.AddFussZeile(liste);

    int maxpos = m_ListCtl.GetItemCount();
    for (int pos = 0; pos < maxpos; pos++)
    {
        liste = AeGetApp()->IsBG() ? GetPositionLineBG(pos) : GetPositionLine(pos);
        druckAuftrag.AddPosZeile(liste);
    }

    druckAuftrag.Druck(AeGetApp()->IsBG() ? 1 : 0);
    druckAuftrag.DelAllData();
}

/*static*/
CString CDArtikelkonto::GetHeaderLineTitlesBG()
{
    CString list;
    list.Format("%-2.2s %-13.13s %-10.10s %8.8s %-7.7s %-25.25s %-25.25s %-5.5s %-7.7s %-7.7s %-10.10s %-3.3s %-7.7s",
        CResString::ex().getStrTblText(AETXT_FILIALE).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTICLE_CODE).GetString(),
        CResString::ex().getStrTblText(AETXT_DATUM).GetString(),
        CResString::ex().getStrTblText(IDS_TIME).GetString(),
        CResString::ex().getStrTblText(AETXT_IDF_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_APOTHEKE).GetString(),
        CResString::ex().getStrTblText(AETXT_ART).GetString(),
        CResString::ex().getStrTblText(AETXT_MENGE).GetString(),
        CResString::ex().getStrTblText(AETXT_MENGE_NEU).GetString(),
        CResString::ex().getStrTblText(AETXT_BELEG_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_RECHNR).GetString(),
        CResString::ex().getStrTblText(AETXT_UID).GetString(),
        CResString::ex().getStrTblText(AETXT_KEY).GetString()
    );
    return list;
}

CString CDArtikelkonto::GetPositionLineBG(int pos)
{
    CString list;
    list.Format("%-2.2s %-13.13s %-10.10s %8.8s %-7.7s %-25.25s %-25.25s %-5.5s %-7.7s %-7.7s %-10.10s %-3.3s %-7.7s",
        m_ListCtl.GetItemText(pos, NUM_AK_FIL).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_ARTICELCODE).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_DATUM).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_ZEIT).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_IDF).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_KUNDE).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_ART).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_MEN).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_MEN_NEU).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_BELEG).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_INVOICE).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_UID).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_KEY).GetString()
    );
    return list;
}

/*static*/
CString CDArtikelkonto::GetHeaderLineTitles()
{
    CString list;
    list.Format("%-2.2s %-13.13s %-10.10s %8.8s %-7.7s %-30.30s %-5.5s %-7.7s %-7.7s %-3.3s %-7.7s",
        CResString::ex().getStrTblText(AETXT_FILIALE).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTICLE_CODE).GetString(),
        CResString::ex().getStrTblText(AETXT_DATUM).GetString(),
        CResString::ex().getStrTblText(IDS_TIME).GetString(),
        CResString::ex().getStrTblText(AETXT_IDF_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_ART).GetString(),
        CResString::ex().getStrTblText(AETXT_MENGE).GetString(),
        CResString::ex().getStrTblText(AETXT_MENGE_NEU).GetString(),
        CResString::ex().getStrTblText(AETXT_BELEG_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_UID).GetString(),
        CResString::ex().getStrTblText(AETXT_KEY).GetString()
    );
    return list;
}

CString CDArtikelkonto::GetPositionLine(int pos)
{
    CString list;
    list.Format("%-2.2s %-7.7s %-10.10s %8.8s %-7.7s %-30.30s %-5.5s %-7.7s %-7.7s %-3.3s %-7.7s",
        m_ListCtl.GetItemText(pos, NUM_AK_FIL).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_PZN).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_DATUM).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_ZEIT).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_IDF).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_ART).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_MEN).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_MEN_NEU).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_BELEG).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_UID).GetString(),
        m_ListCtl.GetItemText(pos, NUM_AK_KEY).GetString()
    );
    return list;
}

/*static*/
CString CDArtikelkonto::GetBottomLine(CString date)
{
    CString list;
    list.Format("%s%%d                                        %s: %s",
        CResString::ex().getStrTblText(AETXT_SEITE),
        CResString::ex().getStrTblText(AETXT_DATUM),
        date
    );
    return list;
}

void CDArtikelkonto::OnButtonArtikel()
{
    CDArtDef dlgArtDef;
    if (dlgArtDef.DoModal() != IDOK) return;
    m_CArtikelNr = dlgArtDef.GetArticleCode();
    GetDlgItem(IDC_EDIT_ARTIKEL_NR)->SetWindowText(m_CArtikelNr);
    m_Edit_IdfNr.SetFocus();
    m_Edit_IdfNr.SetSel(0, -1, FALSE);
}

void CDArtikelkonto::OnButtonKunde()
{
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    m_CIdfNr.Format("%ld", dlgKndWahl.GetIdfNr());
    GetDlgItem(IDC_EDIT_IDF_NR)->SetWindowText(m_CIdfNr);
    m_Edit_IdfNr.SetFocus();
    m_Edit_IdfNr.SetSel(0, -1, FALSE);
    m_Edit_IdfNr.SetSel(-1, 0, FALSE);            //Selektion aufheben
}

LRESULT CDArtikelkonto::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString str;
            str = m_ListCtl.GetItemText(pos, NUM_AK_IDF);
            long kndNr = atol(str);
            CKndInf dlgKndInf;
            dlgKndInf.SetIdfNr(kndNr);
            dlgKndInf.SetKndNr(kndNr);
            str = m_ListCtl.GetItemText(pos, NUM_AK_FIL);
            dlgKndInf.SetKndVz(static_cast<short>(atoi(str)));
            dlgKndInf.DoModal();
        }
        return 1;
    }
    else if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString str;
            str = m_ListCtl.GetItemText(pos, NUM_AK_PZN);
            long artNr = atol(str);
            CDArtInf dlgArtInf;
            dlgArtInf.SetArtNr(artNr);
            str = m_ListCtl.GetItemText(pos, NUM_AK_FIL);
            dlgArtInf.SetFilialNr(static_cast<short>(atoi(str)));
            dlgArtInf.DoModal();
        }
        return 1;
    }
    else if (((LPMSG)lpMsg)->wParam == VK_F6)
    {
        OnButtonAufAnz();
        return 1;
    }
    return 0;
}

void CDArtikelkonto::OnNMDblclkList(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    /*int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_ListCtl.DeleteItem(pos);
    }*/
    *pResult = 0L;
}

void CDArtikelkonto::OnButtonAufAnz()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
        return;
    }

    long aufnr = atol(m_ListCtl.GetItemText(pos, NUM_AK_BELEG));
    if (aufnr == 0)
    {
        MsgBoxOK(IDS_NO_AUFTR);
        return;
    }

    if (AeGetApp()->IsNewF6())
    {
        CDAufAuswahl dlgAufAuswahl;
        dlgAufAuswahl.m_COrderNr = m_ListCtl.GetItemText(pos, NUM_AK_BELEG);
        long datum = GetDateFromItem(pos);
        if (datum == m_lActDate)
            dlgAufAuswahl.m_CDatum.Empty();
        else
            dlgAufAuswahl.m_CDatum = DDMMYYYYStringFromDateLong(datum);
        dlgAufAuswahl.m_KndNr = m_ListCtl.GetItemText(pos, NUM_AK_IDF);
        dlgAufAuswahl.DoModal();
    }
    else
    {
        CDAufInf dlgAufInf;
        dlgAufInf.m_COrderNr = m_ListCtl.GetItemText(pos, NUM_AK_BELEG);
        long datum = GetDateFromItem(pos);
        if (datum == m_lActDate)
            dlgAufInf.m_CDatum.Empty();
        else
            dlgAufInf.m_CDatum = DDMMYYYYStringFromDateLong(datum);
        dlgAufInf.m_KndNr = m_ListCtl.GetItemText(pos, NUM_AK_IDF);
        dlgAufInf.DoModal();
    }
}

long CDArtikelkonto::GetDateFromItem(int pos)
{
    CString cDatum = m_ListCtl.GetItemText(pos, NUM_AK_DATUM);
    int iDaylen = cDatum.Find('.', 0);
    int iMonthlen = cDatum.Find('.', iDaylen + 1) - iDaylen + 1;
    return atol(cDatum.Left(iDaylen))
         + atol(cDatum.Mid(iDaylen + 1, iMonthlen)) * 100
         + atol(cDatum.Right(4)) * 10000;
}

void CDArtikelkonto::RepositionWindow()
{
    int iExpand = 200;
    int iListTop;
    int iListBottom;
    int iListLeft;
    int iListRight;
    int iMax = m_ListCtl.GetItemCount();
    if (iMax > 20)
        iMax = 20;
    CRect rectDesk;
    CRect rectWin;
    CRect rectList;

    GetDesktopWindow()->GetWindowRect( &rectDesk );   //fullscreen
    GetWindowRect( &rectWin );

    /* set to the left,upper corner */
    int iLeft  = rectWin.TopLeft().x;
    int iTop   = rectWin.TopLeft().y;
    int iRight = rectWin.BottomRight().x + iExpand;
    int iBottom = rectWin.BottomRight().y;

    //komplettes Fenster anpassen
    rectWin.SetRect( iLeft, iTop, iRight, iBottom);
    MoveWindow(rectWin);

    //Listbox anpassen
    m_ListCtl.GetClientRect( &rectList );
    m_ListCtl.ClientToScreen( &rectList ); // Convert to Dialog coordinates
    iListTop = rectList.TopLeft().y;
    iListBottom = rectList.BottomRight().y;
    iListLeft = rectList.TopLeft().x;
    iListRight = rectList.BottomRight().x + iExpand;
    rectList.SetRect( iListLeft, iListTop, iListRight, iListBottom);
    ScreenToClient( rectList );
    m_ListCtl.MoveWindow(rectList,true);
}
