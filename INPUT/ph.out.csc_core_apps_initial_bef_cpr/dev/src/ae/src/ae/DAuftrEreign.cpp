// DAuftrEreign.cpp : implementation file
//

#include "stdafx.h"
#include "DAuftrEreign.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     7

static COLUMNS_TYPES Columns[] =
{
    0,  "",  60, LVCFMT_LEFT,
    1,  "",  60, LVCFMT_LEFT,
    2,  "", 118, LVCFMT_LEFT,
    3,  "",  60, LVCFMT_CENTER,
    4,  "",  80, LVCFMT_LEFT,
    5,  "",  70, LVCFMT_LEFT,
    6,  "", 200, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDAuftrEreign dialog


CDAuftrEreign::CDAuftrEreign(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAuftrEreign::IDD, pParent)
{
    m_AuftragsNr = 0;
    m_Datum = 0;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[1].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_EREIGNIS);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_TERMINAL);
    Columns[4].Columns = CResString::ex().getStrTblText(IDS_ANWENDER);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_EVENT_CODE);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_DF_GRUND);
}


void CDAuftrEreign::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDAuftrEreign, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAuftrEreign message handlers

BOOL CDAuftrEreign::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    CAUFEREIG aufereig;
    aufereig.s.KDAUFTRAGNR = m_AuftragsNr;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    char str[81];
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    for (;;)
    {
        aufereig.s.DATUM=m_Datum;
        aufereig.s.FETCH_REL = 1;                  //normaler Fetch
        aufereig.Server(AaauftAusg_auft_ereig);
        if (aufereig.rc == SRV_SQLNOTFOUND)
        {
            aufereig.s.FETCH_REL = 0;              //close Cursor
            aufereig.Server(AaauftAusg_auft_ereig);
            break;
        }
        AllgEntfSpaces(aufereig.s.GERAETNAME);
        AllgEntfSpaces(aufereig.s.USERNAME);
        aufereig.s.ZEIT /= 1000;
        AllgDatumLong2CharTTMMJJ(aufereig.s.DATUM, str);
        s[0] = str;
        AllgZeitLong2CharHHMMSS(aufereig.s.ZEIT, str);
        s[1] = str;
        if      (aufereig.s.EREIGNISART == 1)   s[2] = CResString::ex().getStrTblText(AETXT_IN_ERFASSUNG);
        else if (aufereig.s.EREIGNISART == 2)   s[2] = CResString::ex().getStrTblText(AETXT_IN_AENDERUNG);
        else if (aufereig.s.EREIGNISART == 3)   s[2] = CResString::ex().getStrTblText(AETXT_ZURUECKGESTELLT);
        else if (aufereig.s.EREIGNISART == 4)   s[2] = CResString::ex().getStrTblText(AETXT_ENDE_ERFASSUNG);
        else if (aufereig.s.EREIGNISART == 5)   s[2] = CResString::ex().getStrTblText(AETXT_IN_KOMMI);
        else if (aufereig.s.EREIGNISART == 6)   s[2] = CResString::ex().getStrTblText(AETXT_ENDE_KOMMI);
        else if (aufereig.s.EREIGNISART == 7)   s[2] = CResString::ex().getStrTblText(AETXT_FAKTURIERBEREIT);
        else if (aufereig.s.EREIGNISART == 8)   s[2] = CResString::ex().getStrTblText(AETXT_FAKTURIERT);
        else if (aufereig.s.EREIGNISART == 9)   s[2] = CResString::ex().getStrTblText(AETXT_STORNIERT);
        else if (aufereig.s.EREIGNISART == 10)  s[2] = CResString::ex().getStrTblText(AETXT_IN_UEBERTRAGUNG);
        else if (aufereig.s.EREIGNISART == 11)  s[2] = CResString::ex().getStrTblText(AETXT_UEBERTRAGEN);
        else if (aufereig.s.EREIGNISART == 12)  s[2] = CResString::ex().getStrTblText(AETXT_REAK);
        else if (aufereig.s.EREIGNISART == 101) s[2] = CResString::ex().getStrTblText(AETXT_CHANGE_CST);
        else if (aufereig.s.EREIGNISART == 102) s[2] = CResString::ex().getStrTblText(AETXT_CHANGE_TOUR);
        else if (aufereig.s.EREIGNISART == 103) s[2] = CResString::ex().getStrTblText(AETXT_CHANGE_KOART);
        else if (aufereig.s.EREIGNISART == 104) s[2] = CResString::ex().getStrTblText(AETXT_ENDE_KL);
        else if (aufereig.s.EREIGNISART == 105) s[2] = CResString::ex().getStrTblText(AETXT_CHANGE_ORDERTYPE);
        else if (aufereig.s.EREIGNISART == 106) s[2] = CResString::ex().getStrTblText(AETXT_RESET_LABEL);
        else if (aufereig.s.EREIGNISART == 109) s[2] = CResString::ex().getStrTblText(AETXT_CANCEL_KL);
        else if (aufereig.s.EREIGNISART == 110) s[2] = CResString::ex().getStrTblText(AETXT_ORDER_CREATION);
        else                             s[2].Format("%d",aufereig.s.EREIGNISART);
        s[3] = aufereig.s.GERAETNAME;
        s[4] = aufereig.s.USERNAME;
        s[5].Format("%d",aufereig.s.EVENTCODE);
        if (aufereig.s.EVENTCODE > 0)
        {
            if      (aufereig.s.EVENTCODE == 1) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_1);
            else if (aufereig.s.EVENTCODE == 2) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_2);
            else if (aufereig.s.EVENTCODE == 3) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_3);
            else if (aufereig.s.EVENTCODE == 4) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_4);
            else if (aufereig.s.EVENTCODE == 5) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_5);
            else if (aufereig.s.EVENTCODE == 6) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_6);
            else if (aufereig.s.EVENTCODE == 7) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_7);
            else if (aufereig.s.EVENTCODE == 8) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_8);
            else if (aufereig.s.EVENTCODE == 9) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_9);
            else if (aufereig.s.EVENTCODE == 10) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_10);
            else if (aufereig.s.EVENTCODE == 11) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_11);
            else if (aufereig.s.EVENTCODE == 12) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_12);
            else if (aufereig.s.EVENTCODE == 13) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_13);
            else if (aufereig.s.EVENTCODE == 14) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_14);
            else if (aufereig.s.EVENTCODE == 15) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_15);
            else if (aufereig.s.EVENTCODE == 16) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_16);
            else if (aufereig.s.EVENTCODE == 17) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_17);
            else if (aufereig.s.EVENTCODE == 18) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_18);
            else if (aufereig.s.EVENTCODE == 19) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_19);
            else if (aufereig.s.EVENTCODE == 20) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_20);
            else if (aufereig.s.EVENTCODE == 21) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_21);
            else if (aufereig.s.EVENTCODE == 22) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_22);
            else if (aufereig.s.EVENTCODE == 23) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_23);
            else if (aufereig.s.EVENTCODE == 24) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_24);
            else if (aufereig.s.EVENTCODE == 25) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_25);
            else if (aufereig.s.EVENTCODE == 26) s[6] = CResString::ex().getStrTblText(AETXT_EVENTREASON_26);
            else s[6] = CResString::ex().getStrTblText(IDS_UNKNOWN);
        }
        else
        {
            s[6].Empty();
        }

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            return FALSE;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();

    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
