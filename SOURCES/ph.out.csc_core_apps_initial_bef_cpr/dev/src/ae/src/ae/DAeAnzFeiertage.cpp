// DAeAnzFeiertage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <phodate.h>
#include "DAeAnzFeiertage.h"
#include "DAeUpdFeiertage.h"
#include "DDruckAuftrag.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     8

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 200, LVCFMT_LEFT,
    2,  "",  80, LVCFMT_LEFT,
    3,  "", 160, LVCFMT_LEFT,
    4,  "",  60, LVCFMT_LEFT,
    5,  "",  60, LVCFMT_LEFT,
    6,  "",  60, LVCFMT_LEFT,
    7,  " ",  0, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeAnzFeiertage


CDAeAnzFeiertage::CDAeAnzFeiertage(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeAnzFeiertage::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_TAG);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_MODUS);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_VON_JAHR);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_BIS_JAHR);
}


void CDAeAnzFeiertage::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDAeAnzFeiertage, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDAeAnzFeiertage

BOOL CDAeAnzFeiertage::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    m_iYear = AeGetApp()->GetCurrentDate() / 10000;
    m_Ostern = GetEastern(AeGetApp()->GetCurrentDate());
    GetPage(); //nur wenn man von Ausgesteuerte Anrufe kommt!

    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDAeAnzFeiertage::GetPage()
{
    char Tagtab[7][11];
    strcpy(Tagtab[0],CResString::ex().getStrTblText(IDS_MONDAY).GetString());
    strcpy(Tagtab[1],CResString::ex().getStrTblText(IDS_TUESDAY).GetString());
    strcpy(Tagtab[2],CResString::ex().getStrTblText(IDS_WEDNESDAY).GetString());
    strcpy(Tagtab[3],CResString::ex().getStrTblText(IDS_THURSDAY).GetString());
    strcpy(Tagtab[4],CResString::ex().getStrTblText(IDS_FRIDAY).GetString());
    strcpy(Tagtab[5],CResString::ex().getStrTblText(IDS_SATURDAY).GetString());
    strcpy(Tagtab[6],CResString::ex().getStrTblText(IDS_SUNDAY).GetString());

    char Montab[12][10];
    strcpy(Montab[0],CResString::ex().getStrTblText(IDS_JANUARY).GetString());
    strcpy(Montab[1],CResString::ex().getStrTblText(IDS_FEBRUARY).GetString());
    strcpy(Montab[2],CResString::ex().getStrTblText(IDS_MARCH).GetString());
    strcpy(Montab[3],CResString::ex().getStrTblText(IDS_APRIL).GetString());
    strcpy(Montab[4],CResString::ex().getStrTblText(IDS_MAY).GetString());
    strcpy(Montab[5],CResString::ex().getStrTblText(IDS_JUNE).GetString());
    strcpy(Montab[6],CResString::ex().getStrTblText(IDS_JULY).GetString());
    strcpy(Montab[7],CResString::ex().getStrTblText(IDS_AUGUST).GetString());
    strcpy(Montab[8],CResString::ex().getStrTblText(IDS_SEPTEMBER).GetString());
    strcpy(Montab[9],CResString::ex().getStrTblText(IDS_OCTOBER).GetString());
    strcpy(Montab[10],CResString::ex().getStrTblText(IDS_NOVEMBER).GetString());
    strcpy(Montab[11],CResString::ex().getStrTblText(IDS_DECEMBER).GetString());

    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_Feiertag.SetFilialnr(GetVzNr());
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_Feiertag.SelAll() != 0) break;
        s[0] = kb.Next();
        if (m_Feiertag.GetModus() == 0)
        {
            s[3].Format("%02d.%02d.", m_Feiertag.GetTag() % 100, m_Feiertag.GetTag() / 100);
            s[2].Format("%02d.%02d.%04d", m_Feiertag.GetTag() % 100, m_Feiertag.GetTag() / 100, m_iYear);
        }
        else if (m_Feiertag.GetModus() == 1)
        {
            if (m_Feiertag.GetTag() >= 0)
            {
                s[3].Format(CResString::ex().getStrTblText(IDS_DAYS_AFTER_EASTERN), m_Feiertag.GetTag());
                CTimeSpan y(((long)m_Feiertag.GetTag()), 0, 0, 0);
                CTime x = m_Ostern + (y);
                s[2].Format("%02d.%02d.%04d", x.GetDay(), x.GetMonth(), x.GetYear());
            }
            else
            {
                s[3].Format(CResString::ex().getStrTblText(IDS_DAYS_BEFORE_EASTERN), m_Feiertag.GetTag() * (-1));
                CTimeSpan y(((long)m_Feiertag.GetTag() * -1), 0, 0, 0);
                CTime x = m_Ostern - (y);
                s[2].Format("%02d.%02d.%04d", x.GetDay(), x.GetMonth(), x.GetYear());
            }
        }
        else
        {
            s[3].Format("%d. ", m_Feiertag.GetTag() / 10 % 10);
            s[3] += Tagtab[m_Feiertag.GetTag() % 10];
            s[3] += " im ";
            s[3] += Montab[(m_Feiertag.GetTag()/100) - 1];
            long diff;
            CTime z(m_iYear, m_Feiertag.GetTag()/100, 1, 0, 0, 0, 0);
            if ((diff = z.GetDayOfWeek() - 2) < 0) diff += 7;
            if ((diff = (m_Feiertag.GetTag()%10) - diff) < 0) diff += 7;
            diff += ((m_Feiertag.GetTag()/10%10) - 1) * 7;
            CTimeSpan y(diff, 0, 0, 0);
            CTime x = z + (y);
            s[2].Format("%02d.%02d.%04d", x.GetDay(), x.GetMonth(), x.GetYear());
        }
        s[4].Format("%d", m_Feiertag.GetModus());
        s[5].Format("%d", m_Feiertag.GetVon_jahr());
        s[6].Format("%d", m_Feiertag.GetBis_jahr());
        ppString text;
        s[1] = m_Feiertag.GetTagname(text);
        s[7].Format("%04d", m_Feiertag.GetTag());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
    m_Feiertag.CloseCursor();
    EndWaitCursor();
}

void CDAeAnzFeiertage::OnButtonDruck()
{
    char underline[111];
    memset(underline,'-',110);
    underline[110] = '\0';

    CTM zeit;
    zeit.Server(AafilGetdatetime);

    char datum[11];
    AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, datum);

    CString liste;
    liste.Format(CResString::ex().getStrTblText(IDS_HOLIDAY_LIST), m_sVzNr, datum);

    CDruckAuftrag druckAuftrag;
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);

    liste.Format("%-20.20s %-10.10s %-25.25s %05.5s %-8.8s %-8.8s",
                CResString::ex().getStrTblText(AETXT_BEZEICHNUNG).GetString(),
                CResString::ex().getStrTblText(AETXT_DATUM).GetString(),
                CResString::ex().getStrTblText(AETXT_TAG).GetString(),
                CResString::ex().getStrTblText(AETXT_MODUS).GetString(),
                CResString::ex().getStrTblText(AETXT_VON_JAHR).GetString(),
                CResString::ex().getStrTblText(AETXT_BIS_JAHR).GetString()
                );
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    liste += "                                        ";
    liste += CResString::ex().getStrTblText(AETXT_DATUM);
    liste += ": ";
    liste += datum;
    druckAuftrag.AddFussZeile(liste);
    int maxpos = m_ListCtl.GetItemCount();
    for (int pos = 0; pos < maxpos; pos++)
    {
        liste.Format("%-20.20s %-10.10s %-25.25s %05.5s %-8.8s %-8.8s",
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

void CDAeAnzFeiertage::OnButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if ((pos >= 0) && (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES))
    {
        m_Feiertag.SetFilialnr(GetVzNr());
        m_Feiertag.SetModus(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 4))));
        m_Feiertag.SetTag(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 7))));
        MsgBoxOK((m_Feiertag.Delete() == 0) ? IDP_DELETED : IDP_NOT_DELETED);
        GetPage();
    }
}

void CDAeAnzFeiertage::OnButtonInsert()
{
    CDAeUpdFeiertage upd;
    upd.m_sVzNr = m_sVzNr;
    if (upd.DoModal() == IDOK)
    {
        m_Feiertag.SetFilialnr(m_sVzNr);
        m_Feiertag.SetModus(upd.m_sModus);
        m_Feiertag.SetTag(upd.m_sDatum);
        m_Feiertag.SetVon_jahr(static_cast<short>(atoi(upd.m_csVonJahr)));
        m_Feiertag.SetBis_jahr(static_cast<short>(atoi(upd.m_csBisJahr)));
        m_Feiertag.SetTagname(upd.m_csName);
        MsgBoxOK((m_Feiertag.Insert() == 0) ? IDP_NEUANLAGE : IDP_DOPPELT);
        GetPage();
    }
}

void CDAeAnzFeiertage::OnButtonUpdate()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }

    CDAeUpdFeiertage upd;
    upd.m_sModus = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 4)));
    upd.m_csVonJahr = m_ListCtl.GetItemText(pos, 5);
    upd.m_csBisJahr = m_ListCtl.GetItemText(pos, 6);
    upd.m_csName = m_ListCtl.GetItemText(pos, 1);
    upd.m_sDatum = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 7)));
    upd.m_sVzNr = m_sVzNr;
    if (upd.DoModal() == IDOK)
    {
        if (   (upd.m_sModus == atoi(m_ListCtl.GetItemText(pos, 4)))
            && (upd.m_csVonJahr == m_ListCtl.GetItemText(pos, 5))
            && (upd.m_csBisJahr == m_ListCtl.GetItemText(pos, 6))
            && (upd.m_csName == m_ListCtl.GetItemText(pos, 1))
            && (upd.m_sDatum == atoi(m_ListCtl.GetItemText(pos, 7))) )
        {
            return;
        }
        m_Feiertag.SetModus_alt(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 4))));
        m_Feiertag.SetTag_alt(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 7))));
        m_Feiertag.SetFilialnr(m_sVzNr);
        m_Feiertag.SetModus(upd.m_sModus);
        m_Feiertag.SetTag(upd.m_sDatum);
        m_Feiertag.SetVon_jahr(static_cast<short>(atoi(upd.m_csVonJahr)));
        m_Feiertag.SetBis_jahr(static_cast<short>(atoi(upd.m_csBisJahr)));
        m_Feiertag.SetTagname(upd.m_csName);
        MsgBoxOK((m_Feiertag.Update() == 0) ? IDP_UPDATED : IDP_NOT_UPDATED);
        GetPage();
    }
}

void CDAeAnzFeiertage::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonUpdate();
    *pResult = 0L;
}
