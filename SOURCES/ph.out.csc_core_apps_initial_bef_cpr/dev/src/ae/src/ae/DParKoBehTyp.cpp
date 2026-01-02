// DParKoBehTyp.cpp : implementation file
//

#include "stdafx.h"
#include "DParKoBehTyp.h"

//Definition der Tabellenbreite und der Ueberschriften

#define MAXIMUM_LAENGE          1000
#define MAXIMUM_VOLUMEN         1000000
#define MAXIMUM_BEHAELTERTYP    99
#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "", 40, LVCFMT_LEFT,
    1,  "", 40, LVCFMT_CENTER,
    2,  "", 50, LVCFMT_RIGHT,
    3,  "", 50, LVCFMT_RIGHT,
    4,  "", 50, LVCFMT_RIGHT,
    5,  "", 70, LVCFMT_RIGHT,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDParKoBehTyp dialog


CDParKoBehTyp::CDParKoBehTyp(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParKoBehTyp::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KZ_FILIALE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TYP);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_LAENGE);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_HOEHE);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_BREITE);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_VOLUMEN);
}


void CDParKoBehTyp::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDParKoBehTyp, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnButtonNeu)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParKoBehTyp message handlers

BOOL CDParKoBehTyp::OnInitDialog()
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

void CDParKoBehTyp::AddPosToList(int Filiale,
                                 int Typ,
                                 long Laenge,
                                 long Hoehe,
                                 long Breite,
                                 long Volumen)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    s[0].Format("%d", Filiale);
    s[1].Format("%d", Typ);
    s[2].Format("%ld", Laenge);
    s[3].Format("%ld", Hoehe);
    s[4].Format("%ld", Breite);
    s[5].Format("%ld", Volumen);

    CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s);
}

void CDParKoBehTyp::ReadDataInListBox()
{
    CPARKOBEHTYP parkobehtyp;
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    parkobehtyp.s.FILIALNR = m_FilialNr;
    for (;;)
    {
        parkobehtyp.s.FETCH_REL = 1;              //normaler Fetch
        parkobehtyp.Server(AafilSelkobehtyp);
        if (parkobehtyp.rc == SRV_SQLNOTFOUND)
        {
            parkobehtyp.s.FETCH_REL = 0;          //close Cursor
            parkobehtyp.Server(AafilSelkobehtyp);
            break;
        }
        AddPosToList(parkobehtyp.s.FILIALNR,
            parkobehtyp.s.KOBEHAELTTYP,
            parkobehtyp.s.LAENGE,
            parkobehtyp.s.HOEHE,
            parkobehtyp.s.BREITE,
            parkobehtyp.s.VOLUMEN);
    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDParKoBehTyp::OnButtonDel()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos< 0)
    {
        return;
    }
    CString Filiale = m_ListCtl.GetItemText(pos, 0);
    CString Typ = m_ListCtl.GetItemText(pos, 1);
    if (MsgBoxYesNo(IDP_PAR_KOBEHTYP_DEL) != IDYES)
        return;
    CPARKOBEHTYP parkobehtyp;
    parkobehtyp.s.FILIALNR = static_cast<short>(atoi(Filiale));
    parkobehtyp.s.KOBEHAELTTYP = static_cast<short>(atoi(Typ));
    BeginWaitCursor();
    parkobehtyp.Server(AafilDelkobehtyp);

    EndWaitCursor();
    ReadDataInListBox();
}

void CDParKoBehTyp::OnButtonNeu()
{
    CDParKoBehTypUpd dlgParKoBehTypUpd;
    dlgParKoBehTypUpd.m_bUpdate = FALSE;
    dlgParKoBehTypUpd.m_iFiliale = AeGetApp()->FilialNr();
    dlgParKoBehTypUpd.DoModal();
    ReadDataInListBox();
}

void CDParKoBehTyp::OnButtonUpd()
{
    CDParKoBehTypUpd dlgParKoBehTypUpd;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    dlgParKoBehTypUpd.m_iFiliale = atoi(m_ListCtl.GetItemText(pos, 0));
    dlgParKoBehTypUpd.m_iTyp     = atoi(m_ListCtl.GetItemText(pos, 1));
    dlgParKoBehTypUpd.m_lLaenge  = atol(m_ListCtl.GetItemText(pos, 2));
    dlgParKoBehTypUpd.m_lHoehe   = atol(m_ListCtl.GetItemText(pos, 3));
    dlgParKoBehTypUpd.m_lBreite  = atol(m_ListCtl.GetItemText(pos, 4));
    dlgParKoBehTypUpd.m_lVolumen = atol(m_ListCtl.GetItemText(pos, 5));
    dlgParKoBehTypUpd.m_bUpdate = TRUE;
    dlgParKoBehTypUpd.DoModal();
    ReadDataInListBox();
}

/////////////////////////////////////////////////////////////////////////////
// CDParKoBehTypUpd dialog


CDParKoBehTypUpd::CDParKoBehTypUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParKoBehTypUpd::IDD, pParent)
{
    m_lBreite = 0;
    m_iFiliale = 0;
    m_lHoehe = 0;
    m_lLaenge = 0;
    m_iTyp = 0;
    m_lVolumen = 0;
}


void CDParKoBehTypUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_VOLUMEN, m_EditVolumen);
    DDX_Control(pDX, IDC_EDIT_TYP, m_EditTyp);
    DDX_Control(pDX, IDC_EDIT_LAENGE, m_EditLaenge);
    DDX_Control(pDX, IDC_EDIT_HOEHE, m_EditHoehe);
    DDX_Control(pDX, IDC_EDIT_FILIALE, m_EditFiliale);
    DDX_Control(pDX, IDC_EDIT_BREITE, m_EditBreite);
    DDX_Text(pDX, IDC_EDIT_BREITE, m_lBreite);
    DDX_Text(pDX, IDC_EDIT_FILIALE, m_iFiliale);
    DDX_Text(pDX, IDC_EDIT_HOEHE, m_lHoehe);
    DDX_Text(pDX, IDC_EDIT_LAENGE, m_lLaenge);
    DDX_Text(pDX, IDC_EDIT_TYP, m_iTyp);
    DDX_Text(pDX, IDC_EDIT_VOLUMEN, m_lVolumen);
}


BEGIN_MESSAGE_MAP(CDParKoBehTypUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_BREITE, OnChangeEditBreite)
    ON_EN_CHANGE(IDC_EDIT_HOEHE, OnChangeEditHoehe)
    ON_EN_CHANGE(IDC_EDIT_LAENGE, OnChangeEditLaenge)
    ON_EN_CHANGE(IDC_EDIT_TYP, OnChangeEditTyp)
    ON_EN_CHANGE(IDC_EDIT_VOLUMEN, OnChangeEditVolumen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParKoBehTypUpd message handlers

BOOL CDParKoBehTypUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    GetDlgItem(IDC_EDIT_FILIALE)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_FILIALE)->EnableWindow(FALSE);

    if (m_bUpdate)
    {
        GetDlgItem(IDC_EDIT_LAENGE)->SetFocus();
        GetDlgItem(IDC_EDIT_TYP)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_TYP)->EnableWindow(FALSE);
        return FALSE;
    }


    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParKoBehTypUpd::OnOK()
{
    CPARKOBEHTYP parkobehtyp;
    UpdateData();
    parkobehtyp.s.FILIALNR = static_cast<short>(m_iFiliale);
    parkobehtyp.s.KOBEHAELTTYP = static_cast<short>(m_iTyp);
    parkobehtyp.s.LAENGE = m_lLaenge;
    parkobehtyp.s.HOEHE = m_lHoehe;
    parkobehtyp.s.BREITE = m_lBreite;
    parkobehtyp.s.VOLUMEN = m_lVolumen;
    BeginWaitCursor();
    if (m_bUpdate)
        parkobehtyp.Server(AafilUpdkobehtyp);
    else
    {
        parkobehtyp.Server(AafilInskobehtyp);
        if (parkobehtyp.rc == -2)
            GetDlgItem(IDC_EDIT_NA)->SetFocus();
    }
    EndWaitCursor();
    if (parkobehtyp.rc < SRV_OK)
        return;
    CDialogMultiLang::OnOK();
}

void CDParKoBehTypUpd::OnChangeEditBreite()
{
    AllgWertKontr(&m_EditBreite, MAXIMUM_LAENGE);
}

void CDParKoBehTypUpd::OnChangeEditHoehe()
{
    AllgWertKontr(&m_EditHoehe, MAXIMUM_LAENGE);
}

void CDParKoBehTypUpd::OnChangeEditLaenge()
{
    AllgWertKontr(&m_EditLaenge, MAXIMUM_LAENGE);
}

void CDParKoBehTypUpd::OnChangeEditTyp()
{
    AllgWertKontr(&m_EditLaenge, MAXIMUM_BEHAELTERTYP);
}

void CDParKoBehTypUpd::OnChangeEditVolumen()
{
    AllgWertKontr(&m_EditVolumen, MAXIMUM_VOLUMEN);
}
