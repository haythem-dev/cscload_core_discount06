// DAutrStat.cpp : implementation file
//

#include "stdafx.h"
#include "DDruckAuftrag.h"
#include "DAutrStat.h"

#define MINIMUM_MIN         5
#define MAXIMUM_UHR_MIN     59

/////////////////////////////////////////////////////////////////////////////
// CDAutrStat dialog

void CDAutrStat::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_VZ, m_EditVzNr);
    DDX_Control(pDX, IDC_EDIT_DATUM, m_EditDatum);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
    DDX_Control(pDX, IDC_EDIT_UHR_VON_MIN, m_EditUhrVonMin);
    DDX_Control(pDX, IDC_EDIT_UHR_VON, m_EditUhrVon);
    DDX_Control(pDX, IDC_EDIT_UHR_BIS_MIN, m_EditUhrBisMin);
    DDX_Control(pDX, IDC_EDIT_UHR_BIS, m_EditUhrBis);
    DDX_Control(pDX, IDC_EDIT_INTERVALL, m_EditIntervall);
    DDX_Text(pDX, IDC_EDIT_INTERVALL, m_iIntervall);
    DDX_Text(pDX, IDC_EDIT_UHR_BIS, m_iUhrBis);
    DDX_Text(pDX, IDC_EDIT_UHR_BIS_MIN, m_iUhrBisMin);
    DDX_Text(pDX, IDC_EDIT_UHR_VON, m_iUhrVon);
    DDX_Text(pDX, IDC_EDIT_UHR_VON_MIN, m_iUhrVonMin);
    DDX_Text(pDX, IDC_EDIT_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_EDIT_VZ, m_CVzNr);
}


BEGIN_MESSAGE_MAP(CDAutrStat, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_INTERVALL, OnChangeEditIntervall)
    ON_EN_CHANGE(IDC_EDIT_UHR_BIS, OnChangeEditUhrBis)
    ON_EN_CHANGE(IDC_EDIT_UHR_BIS_MIN, OnChangeEditUhrBisMin)
    ON_EN_CHANGE(IDC_EDIT_UHR_VON, OnChangeEditUhrVon)
    ON_EN_CHANGE(IDC_EDIT_UHR_VON_MIN, OnChangeEditUhrVonMin)
    ON_BN_CLICKED(IDC_DRUCK, OnDruck)
    ON_EN_CHANGE(IDC_EDIT_DATUM, OnChangeEditDatum)
    ON_EN_CHANGE(IDC_EDIT_VZ, OnChangeEditVz)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAutrStat message handlers


/////////////////////////////////////////////////////////////////////////////
// CDArtInf1 property page

//Definition der Tabellenbreite und der Ueberschriften

static COLUMNS_TYPES Columns[] =
{
    0,  "", 40, LVCFMT_RIGHT,
    1,  "", 40, LVCFMT_RIGHT,
    2,  "", 65, LVCFMT_RIGHT,
    3,  "", 65, LVCFMT_RIGHT,
    4,  "", 55, LVCFMT_RIGHT,
    5,  "", 55, LVCFMT_RIGHT,
    6,  "", 55, LVCFMT_RIGHT,
    7,  "", 65, LVCFMT_RIGHT,
    -1, "",  0, 0
};

CDAutrStat::CDAutrStat(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAutrStat::IDD, pParent)
{
    m_iIntervall = 0;
    m_iUhrBis = 0;
    m_iUhrBisMin = 0;
    m_iUhrVon = 0;
    m_iUhrVonMin = 0;
    m_CDatum = _T("");
    m_CVzNr = _T("");

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_VON);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_AUFTRZ);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ZEILEN);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_ZEILEN_DAFUE);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_ZEILEN_PHON);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_ZEILEN_ALPHA);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_WERT);
}

#define NUM_COLUMNS 8

BOOL CDAutrStat::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    m_iUhrVon = 0;
    m_iUhrVonMin = 0;
    m_iUhrBis = 23;
    m_iUhrBisMin = 59;
    m_iIntervall = 15;

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    m_CVzNr.Format("%d", AeGetApp()->VzNr());
    if (!GetAeUser().IsMehrVz())
    {
        m_EditVzNr.EnableWindow(FALSE);
    }
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAutrStat::OnChangeEditIntervall()
{
    AllgWertKontr(&m_EditIntervall, MAXIMUM_MIN);

}

void CDAutrStat::OnChangeEditUhrBis()
{
    AllgWertKontr(&m_EditUhrBis, MAXIMUM_HOUR);

}

void CDAutrStat::OnChangeEditUhrBisMin()
{
    AllgWertKontr(&m_EditUhrBisMin, MAXIMUM_UHR_MIN);

}

void CDAutrStat::OnChangeEditUhrVon()
{
    AllgWertKontr(&m_EditUhrVon, MAXIMUM_HOUR);

}

void CDAutrStat::OnChangeEditUhrVonMin()
{
    AllgWertKontr(&m_EditUhrVonMin, MAXIMUM_UHR_MIN);

}

void CDAutrStat::OnOK()
{
    char str[81];
    long phono;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    CAUFZLNSTAT aufzlnstat;
    if (!UpdateData())
        return;
    m_ListCtl.DeleteAllItems();
    if (m_iIntervall < MINIMUM_MIN)
        m_iIntervall = MINIMUM_MIN;
    aufzlnstat.s.ZEIT_VON = (m_iUhrVon * 100 + m_iUhrVonMin) * 100;
    aufzlnstat.s.ZEIT_BIS = (m_iUhrBis * 100 + m_iUhrBisMin) * 100;
    aufzlnstat.s.ANZAHL = m_iIntervall * 100;
    // nase WERT wird zweckentfremdet für VZ-Nr benutzt
    aufzlnstat.s.WERT = atol(m_CVzNr);
    if (m_CDatum.IsEmpty())
        aufzlnstat.s.DATUM = 0;
    else
    {
        if ((aufzlnstat.s.DATUM = AllgDatumEingKonv(m_CDatum, ALGF_FORM_DATUM_TTMMJJ)) < 0)
        {
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_DATUM));
            return;
        }
    }
    BeginWaitCursor();
    for (;;)
    {
        aufzlnstat.Server(AaauftZeilenstatistik);
        if (aufzlnstat.rc < SRV_OK)
        {
            EndWaitCursor();
            return;
        }
        //Ausgabe in die Listbox

        if (aufzlnstat.rc == SRV_SQLNOTFOUND)
            break;
        m_ddatum = aufzlnstat.s.DATUM;
        s[0] = AllgZeitLong2CharHHMM(aufzlnstat.s.ZEIT_VON, str);
        s[1] = AllgZeitLong2CharHHMM(aufzlnstat.s.ZEIT_BIS, str);
        sprintf(str, "%ld", aufzlnstat.s.ANZAHL_AUFTRAG);
        s[2] = str;
        sprintf(str, "%ld", aufzlnstat.s.ANZAHL);
        s[3] = str;
        sprintf(str, "%ld", aufzlnstat.s.ANZAHL_DAFUE);
        s[4] = str;
        phono = aufzlnstat.s.ANZAHL - aufzlnstat.s.ANZAHL_DAFUE;
        sprintf(str, "%ld", phono);
        s[5] = str;
        sprintf(str, "%ld", aufzlnstat.s.ANZAHL_ALPHA);
        s[6] = str;
        sprintf(str, "%ld", aufzlnstat.s.WERT);
        s[7] = str;

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            return;
        }
    }

    /* Fehlermeldung, wenn kein Auftrag gefunden wurde */
    EndWaitCursor();
    if (!m_ListCtl.GetItemCount())
        MsgBoxOK(IDP_KEIN_AUFTRAG);

    UpdateData(FALSE);
    return;
}

void CDAutrStat::OnDruck()
{
    int i = 0;
    long sumtab[6] = {0,0,0,0,0,0};
    int pos, maxpos;
    char underline[10 + 8 * 8 + 1];
    CTM zeit;
    CDruckAuftrag druckAuftrag;
    CString liste;
    CString Str;
    memset(underline, ' ', 10);
    memset(underline + 10, '-', 8*8);
    underline[10 + 8 * 8] = '\0';
    zeit.Server(AafilGetdatetime);
    char Out1[10 + 1];
    char Out2[5 + 1];
    if (zeit.s.DATUM == m_ddatum)
    {
        liste.Format("          %s% 30s% 24s",
            AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, Out1),
            CResString::ex().getStrTblText(AETXT_AUFTRAGSTATISTIK).GetString(),
            AllgZeitLong2CharHHMM(zeit.s.ZEIT, Out2));
    }
    else
    {
        liste.Format("          %s% 30s",
            AllgDatumLong2CharTTMMJJJJ(m_ddatum, Out1),
            CResString::ex().getStrTblText(AETXT_AUFTRAGSTATISTIK).GetString());
    }
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(" ");           // Leerzeile
    liste.Format("          % 8s% 8s% 8s% 8s% 8s% 8s% 8s% 8s",
                                CResString::ex().getStrTblText(AETXT_VON).GetString(),
                                CResString::ex().getStrTblText(AETXT_BIS).GetString(),
                                CResString::ex().getStrTblText(AETXT_AUFTRZ).GetString(),
                                CResString::ex().getStrTblText(AETXT_ZEILEN).GetString(),
                                CResString::ex().getStrTblText(AETXT_ZEILEN_DAFUE).GetString(),
                                CResString::ex().getStrTblText(AETXT_ZEILEN_PHON).GetString(),
                                CResString::ex().getStrTblText(AETXT_ZEILEN_ALPHA).GetString(),
                                CResString::ex().getStrTblText(AETXT_WERT).GetString());
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(" ");           // Leerzeile
    Str = "          ";
    Str += CResString::ex().getStrTblText(AETXT_SEITE);
    Str += "%d";
    liste.Format("%s% 57.57s", Str.GetString(), theApp.FilialName().GetString());
    druckAuftrag.AddFussZeile(liste);
    maxpos = m_ListCtl.GetItemCount();
    for (pos = 0; pos < maxpos; pos++)
    {
        for (liste = "          ", i=0; i < 8; i++)
        {
            Str.Format("% 8s", m_ListCtl.GetItemText(pos, i).GetString());
            if (i > 1)
            {
                sumtab[i-2] = sumtab[i-2] + atol(m_ListCtl.GetItemText(pos, i));
            }
            liste += Str;
        }
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.AddPosZeile(underline);
    liste = "          ";
    liste += CResString::ex().getStrTblText(AETXT_GESAMT);
    liste += "         ";
    for (i = 0; i < 6; i++)
    {
        Str.Format("% 8ld", sumtab[i]);
        liste += Str;
    }
    druckAuftrag.AddPosZeile(liste);
    druckAuftrag.Druck(TRUE);
    druckAuftrag.DelAllData();
}

void CDAutrStat::OnChangeEditDatum()
{
    AllgDatumKontr(&m_EditDatum, ALGF_FORM_DATUM_TTMMJJ);
}

void CDAutrStat::OnChangeEditVz()
{
    AllgWertKontr(&m_EditVzNr, MAXIMUM_FILIALNR);
}
