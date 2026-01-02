// DLagerrevision.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <statistics.h>
#include <artsel.h>
#include "DLagerrevision.h"
#include "DDruckAuftrag.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     7

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 80, LVCFMT_LEFT,
    2,  "", 80, LVCFMT_LEFT,
    3,  "", 80, LVCFMT_LEFT,
    4,  "", 80, LVCFMT_LEFT,
    5,  "", 80, LVCFMT_LEFT,
    6,  "", 80, LVCFMT_LEFT,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDLagerrevision


CDLagerrevision::CDLagerrevision(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDLagerrevision::IDD, pParent)
{
    m_CTime_Datum = 0;
    m_CArtikel_nr = _T("");
    m_CFiliale = _T("");

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[4].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_BEST_KSC);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_BEST_VSE);
}

void CDLagerrevision::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
    DDX_Control(pDX, IDC_EDIT_FILIALE, m_Edit_Filiale);
    DDX_Control(pDX, IDC_EDIT_ARTIKEL_NR, m_Edit_Artikel_nr);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DATUM, m_DT_Datum);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATUM, m_CTime_Datum);
    DDX_Text(pDX, IDC_EDIT_ARTIKEL_NR, m_CArtikel_nr);
    DDX_Text(pDX, IDC_EDIT_FILIALE, m_CFiliale);
}


BEGIN_MESSAGE_MAP(CDLagerrevision, CDialogMultiLang)
    ON_BN_CLICKED(IDC_DRUCK, OnDruck)
    ON_EN_CHANGE(IDC_EDIT_ARTIKEL_NR, OnChangeEditArtikelNr)
    ON_EN_CHANGE(IDC_EDIT_FILIALE, OnChangeEditFiliale)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDLagerrevision

BOOL CDLagerrevision::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    CTime ctime(2002, 1, 1, 0, 0, 0);
    CTime end = CTimeFromDateLongMinTime(zeit.s.DATUM);
    m_DT_Datum.SetRange(&ctime, &end);
    m_DT_Datum.SetTime(&end);

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDLagerrevision::OnDruck()
{
    CDruckAuftrag druckAuftrag;
    CTM zeit;
    CString liste;
    char Datum[11];
    int pos,maxpos;
    char underline[111];
    memset(underline,'-',110);
    underline[110] = '\0';
    zeit.Server(AafilGetdatetime);
    AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, Datum);
    liste.Format(CResString::ex().getStrTblText(IDS_LAGER_DIFF_LIST), Datum);
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);

    liste.Format("%-7.7s %-25.25s %-10.10s %8.8s %-9.9s %-9.9s",
                CResString::ex().getStrTblText(AETXT_FILIALE).GetString(),
                CResString::ex().getStrTblText(AETXT_ARTICLE_CODE).GetString(),
                CResString::ex().getStrTblText(AETXT_DATUM).GetString(),
                CResString::ex().getStrTblText(IDS_TIME).GetString(),
                CResString::ex().getStrTblText(AETXT_BEST_KSC).GetString(),
                CResString::ex().getStrTblText(AETXT_BEST_VSE).GetString());
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
    maxpos = m_ListCtl.GetItemCount();
    for (pos = 0; pos < maxpos; pos++)
    {
        liste.Format("%-7.7s %-25.25s %-10.10s %8.8s %-9.9s %-9.9s",
            m_ListCtl.GetItemText(pos, 1).GetString(),
            m_ListCtl.GetItemText(pos, 2).GetString(),
            m_ListCtl.GetItemText(pos, 3).GetString(),
            m_ListCtl.GetItemText(pos, 4).GetString(),
            m_ListCtl.GetItemText(pos, 5).GetString(),
            m_ListCtl.GetItemText(pos, 6).GetString());
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(1);
    druckAuftrag.DelAllData();
}

void CDLagerrevision::OnChangeEditArtikelNr()
{
    //AllgWertKontr(&m_Edit_Artikel_nr, MAXIMUM_IDF);
}

void CDLagerrevision::OnChangeEditFiliale()
{
    AllgWertKontr(&m_Edit_Filiale, MAXIMUM_IDF);
}

void CDLagerrevision::OnOK()
{
    //Variablen
    CARTAESEL artaesel;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    CTime ctime;

    UpdateData();

    long lPZN;
    if (!m_CArtikel_nr.IsEmpty())
    {
        strcpy(artaesel.s.ARTICLE_CODE, m_CArtikel_nr);
        artaesel.s.CODE_TYPE = 0;
        artaesel.Server(AatartSel_NoByCode);
        lPZN = artaesel.s.ARTIKEL_NR;
    }
    else
    {
        lPZN = 0;
    }

    // Anfangsinitialisierung durchfuehren
    static CLAGERREVISIONANZ lagerrevisionanz;
    lagerrevisionanz.SetFilialnr(static_cast<short>(atoi(m_CFiliale)));
    lagerrevisionanz.SetArtikel_nr(lPZN);
    m_DT_Datum.GetTime(ctime);
    lagerrevisionanz.SetDatum(ctime.GetYear() * 10000 + ctime.GetMonth() * 100 + ctime.GetDay());
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (lagerrevisionanz.SelList() != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%d", lagerrevisionanz.GetFilialnr());
        if (!m_CArtikel_nr.IsEmpty())
        {
            s[2] = m_CArtikel_nr;
        }
        else
        {
            artaesel.s.ARTIKEL_NR = lagerrevisionanz.GetArtikel_nr();
            artaesel.s.CODE_TYPE = 0;
            artaesel.Server(AatartSel_Preferred);
            AllgEntfSpaces(artaesel.s.ARTICLE_CODE);
            s[2] = artaesel.s.ARTICLE_CODE;
        }
        s[3] = DDMMYYYYStringFromDateLong(lagerrevisionanz.GetDatum());
        s[4] = HHmmSSStringFromTimeLong(lagerrevisionanz.GetUhrzeit());
        s[5].Format("%ld", lagerrevisionanz.GetBestandksc());
        s[6].Format("%ld", lagerrevisionanz.GetBestandvse());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    lagerrevisionanz.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST));
}
