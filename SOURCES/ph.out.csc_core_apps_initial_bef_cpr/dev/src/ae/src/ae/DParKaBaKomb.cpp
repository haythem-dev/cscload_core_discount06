// DParKaBaKomb.cpp : implementation file
//


#include "stdafx.h"
#include "DParKaBaKomb.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "",  40, LVCFMT_CENTER,
    2,  "",  40, LVCFMT_LEFT,
    3,  "",  40, LVCFMT_LEFT,
    4,  "",  60, LVCFMT_LEFT,
    5,  "", 100, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDParKaBaKomb dialog


CDParKaBaKomb::CDParKaBaKomb(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParKaBaKomb::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KZ_AUFTRAGSART);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_KZ_KOMMIART);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_KZ_BUCHART);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_KZ_STANDARD);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_ZUSCHLAG);
}


void CDParKaBaKomb::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDParKaBaKomb, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnButtonNeu)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParKaBaKomb message handlers

BOOL CDParKaBaKomb::OnInitDialog()
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

void CDParKaBaKomb::AddPosToList(CString AArt,
                                 CString BArt,
                                 CString KArt,
                                 CString CStd,
                                 CString Tour,
                                 CString Zuschlag)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    s[0] = AArt;
    s[1] = KArt;
    s[2] = BArt;
    s[3] = CStd;
    s[4] = Tour;
    s[5] = Zuschlag;

    CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s);
}

void CDParKaBaKomb::ReadDataInListBox()
{
    CPARKABAKOMB parkabakomb;
    CString Cstr;
    CString Zuschlag;
    parkabakomb.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr(); //nur eigenes VZ
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    for (;;)
    {
        parkabakomb.s.FETCH_REL = 1;                  //normaler Fetch
        parkabakomb.Server( AafilSelkabakomb );
        if (parkabakomb.rc == SRV_SQLNOTFOUND)
        {
            parkabakomb.s.FETCH_REL = 0;              //close Cursor
            parkabakomb.Server(AafilSelkabakomb);
            break;
        }
        AllgEntfSpaces(parkabakomb.s.KDAUFTRAGART);
        AllgEntfSpaces(parkabakomb.s.BUCHART);
        AllgEntfSpaces(parkabakomb.s.KOART);
        AllgEntfSpaces(parkabakomb.s.TOURID);
        if (parkabakomb.s.KZSTANDARD[0] == '1')
            Cstr = CResString::ex().getStrTblText(AETXT_KZ_JA);
        else
            Cstr.Empty();
        if (parkabakomb.s.CALCEXPRESSDELIVERYCHARGE[0] == '1')
            Zuschlag = CResString::ex().getStrTblText(AETXT_KZ_JA);
        else
            Zuschlag.Empty();
        AddPosToList(parkabakomb.s.KDAUFTRAGART, parkabakomb.s.BUCHART, parkabakomb.s.KOART, Cstr, parkabakomb.s.TOURID, Zuschlag);

    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDParKaBaKomb::OnButtonDel()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    CString AA = m_ListCtl.GetItemText(pos, 0);
    CString KA = m_ListCtl.GetItemText(pos, 1);
    CString BA = m_ListCtl.GetItemText(pos, 2);

    CPARKABAKOMB parkabakomb;
    AllgStrCopy(parkabakomb.s.KDAUFTRAGART, AA, L_PARKABAKOMB_KDAUFTRAGART);
    AllgStrCopy(parkabakomb.s.BUCHART,      BA, L_PARKABAKOMB_BUCHART);
    AllgStrCopy(parkabakomb.s.KOART,        KA, L_PARKABAKOMB_KOART);
    CString CStr;
    CStr.Format(CResString::ex().getStrTblText(IDP_PAR_KABAKOMB_DEL).GetString(), AA.GetString());
    if (MsgBoxYesNo(CStr) != IDYES) return;
    parkabakomb.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr(); //nur eigenes VZ
    BeginWaitCursor();
    parkabakomb.Server(AafilDelkabakomb);
    /*if (parkabakomb.rc >= -1)
    {
        m_ListCtl.DeleteItem(pos);
        CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, pos-1);
    }*/
    EndWaitCursor();
    ReadDataInListBox();
}

void CDParKaBaKomb::OnButtonNeu()
{
    CDParKaBaKombUpd dlgParKaBaKombUpd;
    dlgParKaBaKombUpd.DoModal();
    ReadDataInListBox();
}

void CDParKaBaKomb::OnButtonUpd()
{
    CDParKaBaKombUpd dlgParKaBaKombUpd;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    dlgParKaBaKombUpd.m_CAA = m_ListCtl.GetItemText(pos, 0);
    dlgParKaBaKombUpd.m_CKA = m_ListCtl.GetItemText(pos, 1);
    dlgParKaBaKombUpd.m_CBA = m_ListCtl.GetItemText(pos, 2);
    dlgParKaBaKombUpd.m_CTour = m_ListCtl.GetItemText(pos, 4);
    if (m_ListCtl.GetItemText(pos, 3) == CResString::ex().getStrTblText(AETXT_KZ_JA))
        dlgParKaBaKombUpd.m_bStd = TRUE;
    if (m_ListCtl.GetItemText(pos, 5) == CResString::ex().getStrTblText(AETXT_KZ_JA))
        dlgParKaBaKombUpd.m_bZuschlag = TRUE;
    dlgParKaBaKombUpd.m_bUpd = TRUE;
    dlgParKaBaKombUpd.DoModal();
    ReadDataInListBox();
}

/////////////////////////////////////////////////////////////////////////////
// CDParKaBaKombUpd dialog


CDParKaBaKombUpd::CDParKaBaKombUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParKaBaKombUpd::IDD, pParent)
{
    m_CAA = _T("");
    m_CBA = _T("");
    m_CKA = _T("");
    m_bStd = FALSE;
    m_CTour = _T("");
    m_bZuschlag = FALSE;
    m_bUpd = FALSE;
}


void CDParKaBaKombUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_TOUR, m_EditTour);
    DDX_Control(pDX, IDC_CHECK_STD, m_CBStd);
    DDX_Control(pDX, IDC_EDIT_KA, m_EditKA);
    DDX_Control(pDX, IDC_EDIT_BA, m_EditBA);
    DDX_Control(pDX, IDC_EDIT_AA, m_EditAA);
    DDX_Control(pDX, IDC_CHECK_EILZUSCHLAG, m_CBZuschlag);
    DDX_Text(pDX, IDC_EDIT_AA, m_CAA);
    DDX_Text(pDX, IDC_EDIT_BA, m_CBA);
    DDX_Text(pDX, IDC_EDIT_KA, m_CKA);
    DDX_Check(pDX, IDC_CHECK_STD, m_bStd);
    DDX_Text(pDX, IDC_EDIT_TOUR, m_CTour);
    DDX_Check(pDX, IDC_CHECK_EILZUSCHLAG, m_bZuschlag);
}


BEGIN_MESSAGE_MAP(CDParKaBaKombUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_AA, OnChangeEditAa)
    ON_EN_CHANGE(IDC_EDIT_BA, OnChangeEditBa)
    ON_EN_CHANGE(IDC_EDIT_KA, OnChangeEditKa)
    ON_EN_CHANGE(IDC_EDIT_TOUR, OnChangeEditTour)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParKaBaKombUpd message handlers


BOOL CDParKaBaKombUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParKaBaKombUpd::OnOK()
{
    CPARKABAKOMB parkabakomb;
    UpdateData();
    AllgStrCopy(parkabakomb.s.KDAUFTRAGART, m_CAA, L_PARKABAKOMB_KDAUFTRAGART);
    AllgStrCopy(parkabakomb.s.BUCHART,      m_CBA, L_PARKABAKOMB_BUCHART);
    AllgStrCopy(parkabakomb.s.KOART,        m_CKA, L_PARKABAKOMB_KOART);
    AllgStrCopy(parkabakomb.s.TOURID,       m_CTour, L_PARKABAKOMB_TOURID);
    parkabakomb.s.KZSTANDARD[0] = m_bStd ? '1' : '0';
    parkabakomb.s.CALCEXPRESSDELIVERYCHARGE[0] = m_bZuschlag ? '1' : '0';
    parkabakomb.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();    //nur eigenes VZ
    BeginWaitCursor();
    if (!m_CTour.IsEmpty())
    {
        parkabakomb.Server(AafilChecktour);
        if (parkabakomb.rc == -2)
        {
            EndWaitCursor();
            GetDlgItem(IDC_EDIT_TOUR)->SetFocus();
            return;
        }
    }
    if (m_bUpd)
    {
        parkabakomb.Server(AafilUpdkabakomb);
    }
    else
    {
        parkabakomb.Server(AafilInskabakomb);
    }
    if (parkabakomb.rc == -2)
        GetDlgItem(IDC_EDIT_AA)->SetFocus();
    EndWaitCursor();
    if (parkabakomb.rc < SRV_OK)
        return;

    CDialogMultiLang::OnOK();
}

void CDParKaBaKombUpd::OnChangeEditAa()
{
    AllgLaengeKontr(&m_EditAA, L_PARKABAKOMB_KDAUFTRAGART,AeGetApp()->Modus());
}

void CDParKaBaKombUpd::OnChangeEditBa()
{
    AllgLaengeKontr(&m_EditBA, L_PARKABAKOMB_BUCHART,AeGetApp()->Modus());
}

void CDParKaBaKombUpd::OnChangeEditKa()
{
    AllgLaengeKontr(&m_EditKA, L_PARKABAKOMB_KOART,AeGetApp()->Modus());
}

void CDParKaBaKombUpd::OnChangeEditTour()
{
    AllgLaengeKontr(&m_EditTour, L_PARKABAKOMB_TOURID,AeGetApp()->Modus());
}
