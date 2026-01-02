// DParBuchArt.cpp : implementation file
//

#include "stdafx.h"
#include "DParBuchArt.h"

//Definition der Tabellenbreite und der Ueberschriften

#define MAXIMUM_BUCHUNGSARTTYP  99
#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "",  40, LVCFMT_CENTER,
    2,  "", 140, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDParBuchArt dialog


CDParBuchArt::CDParBuchArt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParBuchArt::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KZ_BUCHART);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_KZ_BUCHMETHODE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
}


void CDParBuchArt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDParBuchArt, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnButtonNeu)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParBuchArt message handlers

BOOL CDParBuchArt::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    ReadDataInListBox();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParBuchArt::AddPosToList(CString BArt,
                               long BMeth,
                               CString BText)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    s[0] = BArt;
    s[1].Format("%ld", BMeth);
    s[2] = BText;

    CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s);
}

void CDParBuchArt::ReadDataInListBox()
{
    CPARBUCHART parbuchart;
    parbuchart.s.BRANCHNO = AeGetApp()->VzNr();   //nur eigenes VZ
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    for (;;)
    {
        parbuchart.s.FETCH_REL = 1;                  //normaler Fetch
        parbuchart.Server(AafilSelbuchart);
        if (parbuchart.rc == SRV_SQLNOTFOUND)
        {
            parbuchart.s.FETCH_REL = 0;              //close Cursor
            parbuchart.Server(AafilSelbuchart);
            break;
        }
        AllgEntfSpaces(parbuchart.s.BUCHART);
        AllgEntfSpaces(parbuchart.s.BEZEICHNUNG);
        AddPosToList(parbuchart.s.BUCHART, parbuchart.s.BUCHMETHODE, parbuchart.s.BEZEICHNUNG);

    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDParBuchArt::OnButtonNeu()
{
    CDParBuchArtUpd dlgParBuchArtUpd;
    dlgParBuchArtUpd.m_bUpdate = FALSE;
    dlgParBuchArtUpd.DoModal();
    ReadDataInListBox();
}

void CDParBuchArt::OnButtonUpd()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    CDParBuchArtUpd dlgParBuchArtUpd;
    dlgParBuchArtUpd.m_CBezeichnung = m_ListCtl.GetItemText(pos, 2);
    dlgParBuchArtUpd.m_CBuchArt     = m_ListCtl.GetItemText(pos, 0);
    dlgParBuchArtUpd.m_lBuchMeth    = atol(m_ListCtl.GetItemText(pos, 1));
    dlgParBuchArtUpd.m_bUpdate = TRUE;
    if (dlgParBuchArtUpd.DoModal() == IDOK)
    {
    }
    ReadDataInListBox();
}

void CDParBuchArt::OnButtonDel()
{
    CPARBUCHART parbuchart;
    CString KBst, CStr;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    KBst = m_ListCtl.GetItemText(pos, 0);
    CStr.Format(CResString::ex().getStrTblText(IDP_PAR_BART_DEL), KBst.GetString());
    if (MsgBoxYesNo(CStr) != IDYES)
        return;
    AllgStrCopy(parbuchart.s.BUCHART, KBst, L_PARBUCHART_BUCHART);
    parbuchart.s.BRANCHNO = AeGetApp()->VzNr();   //nur eigenes VZ
    BeginWaitCursor();
    parbuchart.Server(AafilDelbuchart);

    EndWaitCursor();
    ReadDataInListBox();
}

/////////////////////////////////////////////////////////////////////////////
// CDParBuchArtUpd dialog


CDParBuchArtUpd::CDParBuchArtUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParBuchArtUpd::IDD, pParent)
{
    m_CBuchArt = _T("");
    m_CBezeichnung = _T("");
    m_lBuchMeth = 0;
    m_bUpdate = FALSE;
}


void CDParBuchArtUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_BUCHMETH, m_EditBuchMeth);
    DDX_Control(pDX, IDC_EDIT_BUCHART, m_EditBuchArt);
    DDX_Control(pDX, IDC_EDIT_BEZEICHNUNG, m_EditBezeichnung);
    DDX_Text(pDX, IDC_EDIT_BUCHART, m_CBuchArt);
    DDX_Text(pDX, IDC_EDIT_BEZEICHNUNG, m_CBezeichnung);
    DDX_Text(pDX, IDC_EDIT_BUCHMETH, m_lBuchMeth);
}


BEGIN_MESSAGE_MAP(CDParBuchArtUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_BEZEICHNUNG, OnChangeEditBezeichnung)
    ON_EN_CHANGE(IDC_EDIT_BUCHART, OnChangeEditBuchart)
    ON_EN_CHANGE(IDC_EDIT_BUCHMETH, OnChangeEditBuchmeth)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParBuchArtUpd message handlers

BOOL CDParBuchArtUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (m_bUpdate)
    {
        GetDlgItem(IDC_EDIT_BUCHMETH)->SetFocus();
        GetDlgItem(IDC_EDIT_BUCHART)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_BA)->EnableWindow(FALSE);
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParBuchArtUpd::OnOK()
{
    CPARBUCHART parbuchart;
    UpdateData();
    AllgStrCopy(parbuchart.s.BUCHART, m_CBuchArt, L_PARBUCHART_BUCHART);
    AllgStrCopy(parbuchart.s.BEZEICHNUNG, m_CBezeichnung, L_PARBUCHART_BEZEICHNUNG);
    parbuchart.s.BUCHMETHODE = m_lBuchMeth;
    parbuchart.s.BRANCHNO = AeGetApp()->VzNr();  //nur eigenes VZ
    BeginWaitCursor();
    if (m_bUpdate)
        parbuchart.Server(AafilUpdbuchart);
    else
    {
        parbuchart.Server(AafilInsbuchart);
        if (parbuchart.rc == -2)
            GetDlgItem( IDC_EDIT_BUCHART )->SetFocus();
    }
    EndWaitCursor();
    if (parbuchart.rc < SRV_OK)
        return;
    CDialogMultiLang::OnOK();
}

void CDParBuchArtUpd::OnChangeEditBezeichnung()
{
    AllgLaengeKontr(&m_EditBezeichnung, L_PARBUCHART_BEZEICHNUNG,AeGetApp()->Modus());
}

void CDParBuchArtUpd::OnChangeEditBuchart()
{
    AllgLaengeKontr(&m_EditBuchArt, L_PARBUCHART_BUCHART,AeGetApp()->Modus());
}

void CDParBuchArtUpd::OnChangeEditBuchmeth()
{
    AllgWertKontr(&m_EditBuchMeth, MAXIMUM_BUCHUNGSARTTYP);
}
