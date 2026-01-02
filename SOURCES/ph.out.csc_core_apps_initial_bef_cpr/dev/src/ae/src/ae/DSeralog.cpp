// DSeralog.cpp : implementation file
//

#include "stdafx.h"
#include "DSeralog.h"
#include "DKndWahl.h"
#include "seralog.h"
#include "DDruckAuftrag.h"
#include <kndsel.h>

#define Zeilenende "\r\n"
#define ZEILEN 12    /* Anzahl der Zeilen der Listbox */

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     5

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 60, LVCFMT_RIGHT,
    2,  "", 70, LVCFMT_LEFT,
    3,  "", 50, LVCFMT_LEFT,
    4,  "", 70, LVCFMT_LEFT,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDSeralog dialog


CDSeralog::CDSeralog(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSeralog::IDD, pParent), CPageBrowser(ZEILEN)
{
    m_CTid = _T("");
    m_CDatum = _T("");
    m_CZeit = _T("");
    m_CIdf = _T("");
    m_ShowImmediately = 0;
    m_sVzNr = AeGetApp()->VzNr();

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_GERAET);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_KURZ_AUFTR_NR);
}

void CDSeralog::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ZEIT, m_EditZeit);
    DDX_Control(pDX, IDC_EDIT_DATUM, m_EditDatum);
    DDX_Control(pDX, IDC_EDIT_TID, m_EditTid);
    DDX_Control(pDX, IDC_EDIT_IDF, m_EditIdf);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_TID, m_CTid);
    DDX_Text(pDX, IDC_EDIT_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_EDIT_ZEIT, m_CZeit);
    DDX_Text(pDX, IDC_EDIT_IDF, m_CIdf);
}

BEGIN_MESSAGE_MAP(CDSeralog, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnButtonKnd)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnChangeEditIdf)
    ON_EN_CHANGE(IDC_EDIT_TID, OnChangeEditTid)
    ON_EN_CHANGE(IDC_EDIT_DATUM, OnChangeEditDatum)
    ON_EN_CHANGE(IDC_EDIT_ZEIT, OnChangeEditZeit)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSeralog message handlers

BOOL CDSeralog::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    if (m_ShowImmediately == 1)
    {
        GetPage();
        SelectEintrag();
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDSeralog::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    CSERALOGH seralogh;
    long helpdate;
    char cdate[11];
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        if (m_CDatum.IsEmpty())
        {
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_DATUM));
            return false;
        }
        if ((helpdate = AllgDatumEingKonv(m_CDatum, ALGF_FORM_DATUM_TTMMJJ)) < 0)
        {
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_DATUM));
            return false;
        }
        seralogh.s.DATUM = helpdate % 100 * 1000000 + (helpdate / 100) % 100 * 10000 + helpdate / 10000;
        datum = AllgDatumLong2CharTTMMJJJJ(helpdate, cdate);
        seralogh.s.IDF = atol(m_CIdf);
        if (m_CZeit.IsEmpty()) seralogh.s.ZEIT = 0;
        else if ((seralogh.s.ZEIT = AllgZeitEingKonv(m_CZeit)) < 0)
        {
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_ZEIT));
            return false;
        }
        strcpy(seralogh.s.TID, m_CTid);
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, seralogh.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        seralogh.Server(AaseraLes_dir);
        m_bCursorOpen = true;       //Datenbankcurser offen
        seralogh.s.FETCH_REL = 1;          //normaler Fetch
        if (seralogh.rc == SRV_SQLNOTFOUND)
        {
            if (m_bFirstDataset)      //kein Satz gefunden
            {
                CloseCursor();
                EndWaitCursor();
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Positionen letzte Seite
            break;
        }
        m_bFirstDataset = false;
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        s[1].Format("%d", seralogh.s.ZEIT);
        s[2].Format("%d", seralogh.s.IDF);
        s[3] = seralogh.s.TID;
        s[4] = seralogh.s.AUFTR;

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return false;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return true;
}

void CDSeralog::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDSeralog::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CSERALOGH seralogh;
    seralogh.s.FETCH_REL = 0;
    BeginWaitCursor();
    seralogh.Server(AaseraLes_dir);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDSeralog::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        SelectEintrag();
        return;
    }
    UpdateData();
    CloseCursor();
    GetPage();
}

void CDSeralog::SelectEintrag()
{
    char suf[11];
    char czeit[11];
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDSeralogAuftr dlgSeralogAuftr;
        long zeit = atol(m_ListCtl.GetItemText(pos, 1));
        long idf = atol(m_ListCtl.GetItemText(pos, 2));
        strcpy(suf, m_ListCtl.GetItemText(pos, 4));
        AllgEntfSpaces(suf);
        dlgSeralogAuftr.m_CIdf = m_ListCtl.GetItemText(pos, 2);
        dlgSeralogAuftr.m_CAuftr = suf;
        dlgSeralogAuftr.m_CTid = m_ListCtl.GetItemText(pos, 3);
        dlgSeralogAuftr.m_CDatum = datum;
        dlgSeralogAuftr.m_CUhr = AllgZeitLong2CharHHMMSS(zeit, czeit);
        dlgSeralogAuftr.m_sVzNr = m_sVzNr;
        if ((strlen(suf)) != 0)
            sprintf(dlgSeralogAuftr.m_Filename, "O%07ld%s%06ld.%s", idf, m_ListCtl.GetItemText(pos, 3).GetString(), zeit, suf);
        else
            sprintf(dlgSeralogAuftr.m_Filename, "O%07ld%s%06ld", idf, m_ListCtl.GetItemText(pos, 3).GetString(), zeit);
        dlgSeralogAuftr.DoModal();
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabh‰ngig vom ausgew‰hlten Bedienelement)
LRESULT CDSeralog::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDSeralog::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDSeralog::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CDSeralog::OnButtonKnd()
{
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CString CStr;
    CStr.Format("%ld", dlgKndWahl.GetIdfNr());
    GetDlgItem(IDC_EDIT_IDF)->SetWindowText(CStr);
    m_CIdf = CStr;
    m_sVzNr = dlgKndWahl.GetKndVz();
    UpdateData();
    CloseCursor();
    GetPage();
}

void CDSeralog::OnChangeEditIdf()
{
    AllgWertKontr(&m_EditIdf, MAXIMUM_IDF);
}

void CDSeralog::OnChangeEditTid()
{
    AllgLaengeKontr(&m_EditTid, L_SERALOG_TID,AeGetApp()->Modus());
}

void CDSeralog::OnChangeEditDatum()
{
    AllgDatumKontr(&m_EditDatum,ALGF_FORM_DATUM_TTMMJJ);
}

void CDSeralog::OnChangeEditZeit()
{
    AllgZeitKontr(&m_EditZeit);
}

/////////////////////////////////////////////////////////////////////////////
// CDSeralogAuftr dialog


CDSeralogAuftr::CDSeralogAuftr(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSeralogAuftr::IDD, pParent)
{
    m_sVzNr = AeGetApp()->VzNr();
    m_CApo = _T("");
    m_CDatum = _T("");
    m_CName = _T("");
    m_COrt = _T("");
    m_CStrasse = _T("");
    m_CUhr = _T("");
    m_CAuftr = _T("");
    m_CTid = _T("");
    m_CIdf = _T("");
    m_CListAuftr = _T("");
}


void CDSeralogAuftr::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_AUFTR, m_LBAuftr);
    DDX_Control(pDX, IDC_STATIC_STRASSE, m_StaticStrasse);
    DDX_Control(pDX, IDC_STATIC_ORT, m_StaticOrt);
    DDX_Control(pDX, IDC_STATIC_NAME, m_StaticName);
    DDX_Control(pDX, IDC_STATIC_APO, m_StaticApo);
    DDX_Text(pDX, IDC_STATIC_APO, m_CApo);
    DDX_Text(pDX, IDC_STATIC_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_STATIC_NAME, m_CName);
    DDX_Text(pDX, IDC_STATIC_ORT, m_COrt);
    DDX_Text(pDX, IDC_STATIC_STRASSE, m_CStrasse);
    DDX_Text(pDX, IDC_STATIC_UHR, m_CUhr);
    DDX_Text(pDX, IDC_STATIC_AUFTR, m_CAuftr);
    DDX_Text(pDX, IDC_STATIC_TID, m_CTid);
    DDX_Text(pDX, IDC_STATIC_IDF, m_CIdf);
    DDX_Text(pDX, IDC_LIST_AUFTR, m_CListAuftr);
}


BEGIN_MESSAGE_MAP(CDSeralogAuftr, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSeralogAuftr message handlers

void CDSeralogAuftr::OnButtonDruck()
{
    CDruckAuftrag druckAuftrag;
    CString liste;
    CString apo;
    CString name;
    CString ort;
    CString str;
    CString ausgabe;

    m_StaticApo.GetWindowText(apo);
    m_StaticName.GetWindowText(name);
    m_StaticOrt.GetWindowText(ort);
    m_StaticStrasse.GetWindowText(str);
    liste.Format("%s:%s  %s:%s  %s:%s  %s:%s  %s:%s",
                    CResString::ex().getStrTblText(AETXT_DATUM).GetString(), m_CDatum.GetString(),
                    CResString::ex().getStrTblText(IDS_TIME).GetString(), m_CUhr.GetString(),
                    CResString::ex().getStrTblText(AETXT_GERAET).GetString(), m_CTid.GetString(),
                    CResString::ex().getStrTblText(AETXT_AUFTRZ).GetString(), m_CAuftr.GetString(),
                    CResString::ex().getStrTblText(AETXT_IDF_NR).GetString(), m_CIdf.GetString());
    druckAuftrag.AddKopfZeile(liste);
    liste = " ";
    druckAuftrag.AddKopfZeile(liste);
    liste.Format("%-10s:%-40s  %-10s:%-40s",
                    CResString::ex().getStrTblText(AETXT_APOTHEKE).GetString(), apo.GetString(),
                    CResString::ex().getStrTblText(AETXT_INHABER).GetString(), name.GetString());
    druckAuftrag.AddPosZeile(liste);
    liste.Format("%-10s:%-40s  %-10s:%-40s",
        CResString::ex().getStrTblText(AETXT_ORT).GetString(), ort.GetString(),
        CResString::ex().getStrTblText(AETXT_STRASSE).GetString(), str.GetString());
    druckAuftrag.AddPosZeile(liste);
    liste = " ";
    druckAuftrag.AddPosZeile(liste);
    druckAuftrag.AddFussZeile(" ");      // Leerzeile
    liste = "          ";
    liste += CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d/%d";
    druckAuftrag.AddFussZeile(liste);

    CString cs(m_CListAuftr);   // multi line edit control evt. mit Status "read-only"
    int len = m_CListAuftr.GetLength();
    int i = 1;
    while (i > 0)
    {
        ausgabe.Empty();
        i = cs.Find("\r\n");
        if (i >= 0)
        {
            ausgabe = cs.Left(i);   // ausgabe enth‰lt eine zeile !
            len = cs.GetLength();
            cs = cs.Right(len-i-2);
        }
        druckAuftrag.AddPosZeile(ausgabe);
    }
    druckAuftrag.Druck(TRUE);
    druckAuftrag.DelAllData();
}

void CDSeralogAuftr::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

BOOL CDSeralogAuftr::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    CSERALOGD seralogd;
    CKNDSEL kndsel;
    kndsel.s.IDFNR = atol(m_CIdf);
    kndsel.s.KUNDENNR = atol(m_CIdf);
    kndsel.s.SKDKUNDEAEGESPERRT[0] = '1';
    kndsel.s.REGIONNR = AeGetApp()->VzNr();
    kndsel.s.VERTRIEBSZENTRUMNR = m_sVzNr;
    BeginWaitCursor();
    kndsel.s.FETCH_REL = 1;
    kndsel.Server( AakundeSel_idf );
    kndsel.s.FETCH_REL = 0;
    kndsel.Server( AakundeSel_idf );
    m_StaticApo.SetWindowText(kndsel.s.NAMEAPO);
    m_StaticName.SetWindowText(kndsel.s.NAMEINHABER);
    m_StaticOrt.SetWindowText(kndsel.s.ORT);
    m_StaticStrasse.SetWindowText(kndsel.s.STRASSE);
    UpdateData();
    char Cstr[L_SERALOG_DATEN+1];
    strcpy(seralogd.s.DATEN , m_Filename);
    for (;;)
    {
        seralogd.Server(AaseraLes_data);
        if (seralogd.rc == SRV_SQLNOTFOUND)
            break;      //Dateiende
        strcpy(Cstr, seralogd.s.DATEN);
        AllgEntfSpaces(Cstr);
        SetSpace2Sign(Cstr);
        m_CListAuftr += LinePartition(Cstr);
    }
    EndWaitCursor();
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDSeralogAuftr::SetSpace2Sign(char* input)
{
    int len = strlen(input);
    for (int i = 0; i < len; i++)
    {
        if (input[i] == ' ')
        {
            input[i] = '_';
        }
    }
}

CString CDSeralogAuftr::LinePartition(char *buffer)
{
    CString liste;
    char outbuf[300];
    char lenbuf[4];
    int pos, satzlen, x;
    if (buffer[20] == 'D')
    {
        int len = strlen(buffer);
        if (!strncmp(&buffer[22], "02", 2) || !strncmp(&buffer[22], "03", 2) || !strncmp(&buffer[22], "04", 2))
        {
            liste.Format("%*.*s",22,22,buffer);
            liste += Zeilenende;
            for (pos = 22; pos < len; pos += satzlen)
            {
                memcpy(lenbuf, &buffer[0] + pos + 2, 3);
                lenbuf[3] = '\0';
                satzlen = atoi(lenbuf);
                if (satzlen <= 0)
                    break;
                memcpy(outbuf, &buffer[0] + pos, satzlen);
                outbuf[satzlen] = '\0';
                liste += "*                     ";
                liste += outbuf;
                liste += Zeilenende;
            }
        }
        else
        {
            for (x = 0; x < 22; x++)
            {
                liste += buffer[x];
            }
            liste += Zeilenende;
            liste += "                      ";
            for (x = 22; x < len; x++)
            {
                liste += buffer[x];
                if (buffer[x] == '<')
                {
                    liste += Zeilenende;
                    liste += "                      ";
                }
            }
            liste += Zeilenende;
        }
    }
    else
    {
        liste = buffer;
        liste += Zeilenende;
    }
    return liste;
}

HBRUSH CDSeralogAuftr::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_LIST_AUFTR)
    {
        pDC->SetTextColor(RGB(0,0,0));      // schwarz
        pDC->SetBkColor(RGB(255,255,255));  // weiﬂ
    }
    return hbr;
}
