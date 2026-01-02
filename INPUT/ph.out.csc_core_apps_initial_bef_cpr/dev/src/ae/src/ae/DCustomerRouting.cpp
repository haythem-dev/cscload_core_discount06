// DCustomerRouting.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <kndsel.h>
#include "DKndWahl.h"
#include "DKndInf.h"
#include <customer.h>
#include "DDruckAuftrag.h"
#include "DCustomerRouting.h"
#include "DCustomerRouting_Upd.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "", 30, LVCFMT_LEFT,
    1,  "", 60, LVCFMT_RIGHT,
    2,  "", 60, LVCFMT_RIGHT,
    3,  "", 70, LVCFMT_LEFT,
    4,  "", 50, LVCFMT_LEFT,
    5,  "",  0, LVCFMT_LEFT,
    -1, "",  0, 0
};


// CDCustomerRouting-Dialogfeld

IMPLEMENT_DYNAMIC(CDCustomerRouting, CDialog)
CDCustomerRouting::CDCustomerRouting(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCustomerRouting::IDD, pParent), CPageBrowser(0)

    , m_CIDF(_T(""))
    , m_CVZ(_T(""))
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_VON);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_TAG);
}

CDCustomerRouting::~CDCustomerRouting()
{
}

void CDCustomerRouting::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_IDF, m_Edit_IDF);
    DDX_Text(pDX, IDC_EDIT_IDF, m_CIDF);
    DDX_Control(pDX, IDC_EDIT_VZ, m_Edit_VZ);
    DDX_Text(pDX, IDC_EDIT_VZ, m_CVZ);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDCustomerRouting, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnEnChangeEditIdf)
    ON_EN_CHANGE(IDC_EDIT_VZ, OnEnChangeEditVz)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnBnClickedButtonDruck)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnBnClickedButtonKnd)
    ON_BN_CLICKED(IDC_BUTTON_BEARB, OnBnClickedButtonBearb)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnBnClickedButtonNeu)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CDCustomerRouting-Meldungshandler

BOOL CDCustomerRouting::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    CString stVznr;
    stVznr.Format("%d", AeGetApp()->VzNr());
    GetDlgItem(IDC_EDIT_VZ)->SetWindowText(stVznr);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    m_iAnzZeilen = m_ListCtl.GetCountPerPage();
    Init(m_iAnzZeilen);
    GetDlgItem(IDC_BUTTON_NEU)->EnableWindow(FALSE);

    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_SUNDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_MONDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_TUESDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_WEDNESDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_THURSDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_FRIDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_SATURDAY));

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDCustomerRouting::OnOK()
{
    UpdateData(TRUE);
    CString stVznr;
    CString stKdnr;
    GetDlgItem(IDC_EDIT_IDF)->GetWindowText(stKdnr);
    GetDlgItem(IDC_EDIT_VZ)->GetWindowText(stVznr);
    CloseCursor();
    if (stVznr.IsEmpty())
    {
        MsgBoxOK(IDP_VZ_REQUIRED);
        return;
    }
    if (stKdnr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_KUNDENNR);
        return;
    }
    m_lKdnr = atol(stKdnr);
    m_sVznr = static_cast<short>(atoi(stVznr));
    CKNDSEL kndsel;
    kndsel.s.SKDKUNDEAEGESPERRT[0] = '0';
    kndsel.s.SKDKUNDEAEGESPERRT[1] = '\0';
    kndsel.s.VERTRIEBSZENTRUMNR = static_cast<short>(atoi(stVznr));
    kndsel.s.KUNDENNR = atol(stKdnr);
    BeginWaitCursor();
    kndsel.Server(AakundeSel_kndnr);
    if (kndsel.rc == SRV_OK)
    {
        GetDlgItem(IDC_STATIC_APO)->SetWindowText(kndsel.s.NAMEAPO);
        GetDlgItem(IDC_STATIC_ORT)->SetWindowText(kndsel.s.ORT);
        GetDlgItem(IDC_STATIC_TEL)->SetWindowText(kndsel.s.TELKURZWAHL);
        EndWaitCursor();
    }
    else
    {
        EndWaitCursor();
        return;
    }

    m_Routing.SetBranchno(static_cast<short>(atoi(stVznr)));
    m_Routing.SetCustomerno(atol(stKdnr));
    GetPage();
}

void CDCustomerRouting::OnEnChangeEditIdf()
{
    CString str;

    m_Edit_IDF.GetWindowText(str);                  //IDF lesen
    if (str.IsEmpty())
        return;                                     //Feld ist leer
    char chN = str[str.GetLength() - 1];            //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CMC = str;
        m_Edit_IDF.SetWindowText("");               //IDF löschen
        OnBnClickedButtonKnd();
        m_Edit_IDF.SetFocus();
        m_Edit_IDF.SetSel(0, -1, FALSE);
        m_Edit_IDF.SetSel(-1, 0, FALSE);            //Selektion aufheben
        return;
    }
    GetDlgItem(IDC_BUTTON_NEU)->EnableWindow(FALSE);
    AllgWertKontr(&m_Edit_IDF, MAXIMUM_IDF);
}

void CDCustomerRouting::OnEnChangeEditVz()
{
    AllgWertKontr(&m_Edit_VZ, MAXIMUM_FILIALNR);
}

void CDCustomerRouting::OnBnClickedButtonDruck()
{
    if (m_ListCtl.GetItemCount() == 0)
        return;
    CDruckAuftrag druckAuftrag;
    CTM zeit;
    CString liste, apo, ort, name;
    char Datum[11];
    int pos, maxpos;
    char underline[111];
    memset(underline, '-', 110);
    underline[110] = '\0';
    zeit.Server(AafilGetdatetime);
    AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, Datum);
    this->GetWindowText(name);
    GetDlgItem(IDC_STATIC_APO)->GetWindowText(apo);
    GetDlgItem(IDC_STATIC_ORT)->GetWindowText(ort);
    liste.Format("%s %s %s",
                    name.GetString(),
                    apo.GetString(),
                    ort.GetString());
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);

    liste.Format("%-5.5s %-5.5s %7s %3s",
                CResString::ex().getStrTblText(AETXT_VON).GetString(),
                CResString::ex().getStrTblText(AETXT_BIS).GetString(),
                CResString::ex().getStrTblText(AETXT_FILIALE).GetString(),
                CResString::ex().getStrTblText(AETXT_TAG).GetString()
                );
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
    liste.Format("%-5.5s %-5.5s %7s %3s",
            m_ListCtl.GetItemText(pos, 1).GetString(),
            m_ListCtl.GetItemText(pos, 2).GetString(),
            m_ListCtl.GetItemText(pos, 3).GetString(),
            m_ListCtl.GetItemText(pos, 4).GetString()
            );
    druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(1);
    druckAuftrag.DelAllData();
}

bool CDCustomerRouting::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    CStringArray s;
    long FETCH_REL;
    ppString cTag;
    s.SetSize(NUM_COLUMNS);

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < m_iAnzZeilen; i++)
    {
        m_Routing.SelList(FETCH_REL);
        m_bCursorOpen = true;   //Datenbankcurser offen
        if (m_Routing.rc != SRV_OK)
        {
            if (m_bFirstDataset)     //kein Satz gefunden
            {
                //CloseCursor();
                GetDlgItem(IDC_BUTTON_NEU)->EnableWindow(TRUE);
                MsgBoxOK(IDP_NO_DATA);
                EndWaitCursor();
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Positionen letzte Seite
            break;
        }
        FETCH_REL = 1;          //normaler Fetch
        m_bFirstDataset = false;
        s[0] = kb.Next();
        s[1].Format("%02d:%02d", m_Routing.GetTimefrom() / 100, m_Routing.GetTimefrom() % 100);
        s[2].Format("%02d:%02d", m_Routing.GetTimeto() / 100, m_Routing.GetTimeto() % 100);
        s[3].Format("%d", m_Routing.GetDestbranchno());
        s[4] = m_Tagtab.GetAt(m_Routing.GetWeekday());
        s[5].Format("%d", m_Routing.GetWeekday());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return false;
        }
    }
    EndWaitCursor();
    GetDlgItem(IDC_BUTTON_NEU)->EnableWindow(TRUE);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetFocusSelectedFocused(m_ListCtl, 0);

    return true;
}

void CDCustomerRouting::OnBnClickedButtonKnd()
{
    CDKndWahl dlgKndWahl;
    dlgKndWahl.m_apo = m_CMC;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CString Str;
    Str.Format("%ld", dlgKndWahl.GetIdfNr());
    m_CMC.Empty();
    m_Edit_IDF.SetWindowText(Str);
    m_Edit_IDF.SetFocus();
    m_Edit_IDF.SetSel(0, -1, FALSE);
    m_Edit_IDF.SetSel(-1, 0, FALSE);        //Selektion aufheben
    OnOK();
}

void CDCustomerRouting::OnBnClickedButtonBearb()
{
    if (!UpdateData())
        return;

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    CDCustomerRouting_Upd dlgCustomerRouting_Upd;
    dlgCustomerRouting_Upd.m_ifunktion = CDCustomerRouting_Upd::UPDATE;
    GetDlgItem(IDC_STATIC_APO)->GetWindowText(dlgCustomerRouting_Upd.m_CApo);
    GetDlgItem(IDC_STATIC_ORT)->GetWindowText(dlgCustomerRouting_Upd.m_COrt);
    GetDlgItem(IDC_EDIT_VZ)->GetWindowText(dlgCustomerRouting_Upd.m_CVz);
    dlgCustomerRouting_Upd.m_sVznr = m_sVznr;
    dlgCustomerRouting_Upd.m_lKundennr = m_lKdnr;
    CString von = m_ListCtl.GetItemText(pos, 1);
    CString bis = m_ListCtl.GetItemText(pos, 2);
    long vonHH = atol(von.Left(2));
    long vonMM = atol(von.Right(2));
    long bisHH = atol(bis.Left(2));
    long bisMM = atol(bis.Right(2));
    dlgCustomerRouting_Upd.m_CT_Von = CTimeFromDateLong(vonHH, vonMM, 0, zeit.s.DATUM);
    dlgCustomerRouting_Upd.m_CT_Bis = CTimeFromDateLong(bisHH, bisMM, 0, zeit.s.DATUM);
    dlgCustomerRouting_Upd.m_Zeitalt = vonHH*100 + vonMM;
    dlgCustomerRouting_Upd.m_CVz2 = m_ListCtl.GetItemText(pos, 3);
    dlgCustomerRouting_Upd.m_pTagtab = &m_Tagtab;
    dlgCustomerRouting_Upd.m_iTag = atol(m_ListCtl.GetItemText(pos, 5));
    if (dlgCustomerRouting_Upd.DoModal() == IDCANCEL) return;
    CloseCursor();
    GetPage();
}

void CDCustomerRouting::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    BeginWaitCursor();
    m_Routing.CloseCursor();
    EndWaitCursor();
    ResetCursor();
    Reset();
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDCustomerRouting::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    LRESULT res = CPageBrowser::OnHookNextPrev(lpMsg);
    if (res != 0L)
    {
        return res;
    }

    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        CKndInf dlgKndInf;
        dlgKndInf.SetIdfNr(m_lKdnr);
        dlgKndInf.SetKndNr(m_lKdnr);
        dlgKndInf.SetKndVz(m_sVznr);
        dlgKndInf.DoModal();
        return 1L;
    }
    return 0L;
}

void CDCustomerRouting::OnBnClickedButtonNeu()
{
    if (m_lKdnr == 0)
    {
        MsgBoxOK(IDP_MUSS_KUNDENNR);
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_IDF));
        return;
    }

    CDCustomerRouting_Upd dlgCustomerRouting_Upd;
    // Vorbelegen mit aktuellem Datum
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    dlgCustomerRouting_Upd.m_CT_Von = CTimeFromDateLongMinTime(zeit.s.DATUM);
    dlgCustomerRouting_Upd.m_CT_Bis = CTimeFromDateLongMinTime(zeit.s.DATUM);
    dlgCustomerRouting_Upd.m_ifunktion = CDCustomerRouting_Upd::INSERT;
    GetDlgItem(IDC_STATIC_APO)->GetWindowText(dlgCustomerRouting_Upd.m_CApo);
    GetDlgItem(IDC_STATIC_ORT)->GetWindowText(dlgCustomerRouting_Upd.m_COrt);
    GetDlgItem(IDC_EDIT_VZ)->GetWindowText(dlgCustomerRouting_Upd.m_CVz);
    dlgCustomerRouting_Upd.m_sVznr = m_sVznr;
    dlgCustomerRouting_Upd.m_lKundennr = m_lKdnr;
    dlgCustomerRouting_Upd.m_pTagtab = &m_Tagtab;
    if (dlgCustomerRouting_Upd.DoModal() == IDCANCEL) return;
    CloseCursor();
    GetPage();
}

void CDCustomerRouting::OnBnClickedButtonDel()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString CStr;
        CStr.Format(CResString::ex().getStrTblText(IDP_LOESCHEN_JA));
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
        m_Routing.SetBranchno(m_sVznr);
        m_Routing.SetCustomerno(m_lKdnr);
        m_Routing.SetDayofweek(m_ListCtl.GetItemText(pos, 4));
        m_Routing.SetWeekday(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 5))));
        CString Zeit = m_ListCtl.GetItemText(pos, 1);
        m_Routing.SetTimefrom(atol(Zeit.Left(2)) * 100 + atol(Zeit.Right(2)));
        m_Routing.Delete();
        CloseCursor();
        GetPage();
    }
}
