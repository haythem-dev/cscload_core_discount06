// DParKomArt.cpp : implementation file
//

#include "stdafx.h"
#include "DParKomArt.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "",  40, LVCFMT_CENTER,
    2,  "", 140, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDParKomArt dialog


CDParKomArt::CDParKomArt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParKomArt::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KZ_KOMMIART);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_KZ_KOMMIMETHODE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
}


void CDParKomArt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDParKomArt, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnButtonNeu)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParKomArt message handlers

BOOL CDParKomArt::OnInitDialog()
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

void CDParKomArt::AddPosToList(CString KArt,
                               long KMeth,
                               CString KText)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    s[0] = KArt;
    s[1].Format("%ld", KMeth);
    s[2] = KText;

    CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s);
}

void CDParKomArt::ReadDataInListBox()
{
    CPARKOART parkoart;
    parkoart.s.BRANCHNO = AeGetApp()->VzNr();   //nur eigenes VZ
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    for (;;)
    {
        parkoart.s.FETCH_REL = 1;                  //normaler Fetch
        parkoart.Server(AafilSelkoart);
        if (parkoart.rc == SRV_SQLNOTFOUND)
        {
            parkoart.s.FETCH_REL = 0;              //close Cursor
            parkoart.Server(AafilSelkoart);
            break;
        }
        AllgEntfSpaces(parkoart.s.KOART);
        AllgEntfSpaces(parkoart.s.BEZEICHNUNG);
        AddPosToList(parkoart.s.KOART, parkoart.s.KOMETHODE, parkoart.s.BEZEICHNUNG);
    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDParKomArt::OnButtonDel()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    CString KBst = m_ListCtl.GetItemText(pos, 0);
    CString CStr;
    CStr.Format(CResString::ex().getStrTblText(IDP_PAR_KART_DEL), KBst.GetString());
    if (MsgBoxYesNo(CStr) != IDYES) return;
    CPARKOART parkoart;
    AllgStrCopy(parkoart.s.KOART,KBst,L_PARKOART_KOART);
    parkoart.s.BRANCHNO = AeGetApp()->VzNr();   //nur eigenes VZ
    BeginWaitCursor();
    parkoart.Server(AafilDelkoart);
    /*if (parkoart.rc >= -1)
    {
        m_ListCtl.DeleteItem(pos);
        CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, pos-1);
    }*/
    EndWaitCursor();
    ReadDataInListBox();
}

void CDParKomArt::OnButtonNeu()
{
    CDParKomArtUpd dlgParKomArtUpd;
    dlgParKomArtUpd.m_bUpdate = FALSE;
    dlgParKomArtUpd.DoModal();
    ReadDataInListBox();
}

void CDParKomArt::OnButtonUpd()
{
    CDParKomArtUpd dlgParKomArtUpd;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    dlgParKomArtUpd.m_CBezeichnung    = m_ListCtl.GetItemText(pos, 2);
    dlgParKomArtUpd.m_CKomArt         = m_ListCtl.GetItemText(pos, 0);
    dlgParKomArtUpd.m_lKomMeth        = atol(m_ListCtl.GetItemText(pos, 1));
    dlgParKomArtUpd.m_bUpdate = TRUE;
    dlgParKomArtUpd.DoModal();
    ReadDataInListBox();
}

/////////////////////////////////////////////////////////////////////////////
// CDParKomArtUpd dialog

CDParKomArtUpd::CDParKomArtUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParKomArtUpd::IDD, pParent)
{
    m_CBezeichnung = _T("");
    m_CKomArt = _T("");
    m_lKomMeth = 0;
    m_bUpdate = FALSE;
}


void CDParKomArtUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_KOMMMETH, m_EditKomMeth);
    DDX_Control(pDX, IDC_EDIT_KOMMART, m_EditKomArt);
    DDX_Control(pDX, IDC_EDIT_BEZEICHNUNG, m_EditBezeichnung);
    DDX_Text(pDX, IDC_EDIT_BEZEICHNUNG, m_CBezeichnung);
    DDX_Text(pDX, IDC_EDIT_KOMMART, m_CKomArt);
    DDX_Text(pDX, IDC_EDIT_KOMMMETH, m_lKomMeth);
}


BEGIN_MESSAGE_MAP(CDParKomArtUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_BEZEICHNUNG, OnChangeEditBezeichnung)
    ON_EN_CHANGE(IDC_EDIT_KOMMART, OnChangeEditKommart)
    ON_EN_CHANGE(IDC_EDIT_KOMMMETH, OnChangeEditKommmeth)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParKomArtUpd message handlers

BOOL CDParKomArtUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (m_bUpdate)
    {
        GetDlgItem( IDC_EDIT_KOMMMETH )->SetFocus();
        GetDlgItem( IDC_STATIC_KA )->EnableWindow(FALSE);
        GetDlgItem( IDC_EDIT_KOMMART )->EnableWindow(FALSE);
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParKomArtUpd::OnOK()
{
    CPARKOART parkoart;
    UpdateData();
    AllgStrCopy(parkoart.s.KOART, m_CKomArt, L_PARKOART_KOART);
    AllgStrCopy(parkoart.s.BEZEICHNUNG, m_CBezeichnung, L_PARKOART_BEZEICHNUNG);
    parkoart.s.KOMETHODE = m_lKomMeth;
    parkoart.s.BRANCHNO = AeGetApp()->VzNr();  //nur eigenes VZ
    BeginWaitCursor();
    if (m_bUpdate)
        parkoart.Server(AafilUpdkoart);
    else
    {
        parkoart.Server(AafilInskoart);
        if (parkoart.rc == -2)
            GetDlgItem(IDC_EDIT_KOMMART)->SetFocus();
    }
    EndWaitCursor();
    if (parkoart.rc < SRV_OK)
        return;
    CDialogMultiLang::OnOK();
}

void CDParKomArtUpd::OnChangeEditBezeichnung()
{
    AllgLaengeKontr(&m_EditBezeichnung, L_PARKOART_BEZEICHNUNG,AeGetApp()->Modus());
}

void CDParKomArtUpd::OnChangeEditKommart()
{
    AllgLaengeKontr(&m_EditKomArt, L_PARKOART_KOART,AeGetApp()->Modus());
}

void CDParKomArtUpd::OnChangeEditKommmeth()
{
    AllgWertKontr(&m_EditKomMeth, MAXIMUM_KOMMIARTTYP);
}
