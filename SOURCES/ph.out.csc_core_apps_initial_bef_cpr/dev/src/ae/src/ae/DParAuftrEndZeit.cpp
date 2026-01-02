// DParAuftrendzeit.cpp : implementation file
//

#include "stdafx.h"
#include "DParAuftrendzeit.h"

//Definition der Tabellenbreite und der Ueberschriften

#define VB              1
#define CL              2
#define ER              3
#define LA              4
#define LV              5
#define IR              6
#define SH              7
#define KF              8
#define UE              9
#define BC              16
#define VU              18
#define CC              19
#define IT              20
#define D               1
#define E               2
#define P               3
#define X               4
#define NUM_COLUMNS     5

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "", 230, LVCFMT_LEFT,
    2,  "",  70, LVCFMT_CENTER,
    3,  "",  60, LVCFMT_LEFT,
    4,  "",  50, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDParAuftrendzeit dialog


CDParAuftrendzeit::CDParAuftrendzeit(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParAuftrendzeit::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KZ_FILIALE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_HERKUNFT);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_MODUS);
    Columns[4].Columns = CResString::ex().getStrTblText(IDS_TIME);
}


void CDParAuftrendzeit::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDParAuftrendzeit, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnButtonNeu)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParAuftrendzeit message handlers

BOOL CDParAuftrendzeit::OnInitDialog()
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
void CDParAuftrendzeit::AddPosToList(int Filiale,
                                     long Art,
                                     int HFili,
                                     int Modus,
                                     long Zeit)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    char CZeit[10];
    CString CArt;
    CString CModus;

    s[0].Format("%d", Filiale);
    Art2Char(Art, CArt);
    s[1] = CArt;
    s[2].Format("%d", HFili);
    Modus2Char(static_cast<short>(Modus), CModus);
    s[3] = CModus;
    ppGTimeLongToCharHHMM(Zeit, CZeit);
    s[4] = CZeit;

    CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s);
}

void CDParAuftrendzeit::ReadDataInListBox()
{
    CPARAUFTRENDZEIT parauftrendzeit;
    CString Art;
    CString HFili;
    CString Modus;
    CString Zeit;
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    parauftrendzeit.s.FILIALNR = m_FilialNr;
    for (;;)
    {
        parauftrendzeit.s.FETCH_REL = 1;          //normaler Fetch
        parauftrendzeit.Server(AafilSel_auftrendzeit);
        if (parauftrendzeit.rc == SRV_SQLNOTFOUND)
        {
            parauftrendzeit.s.FETCH_REL = 0;      //close Cursor
            parauftrendzeit.Server(AafilSel_auftrendzeit);
            break;
        }
        AddPosToList(parauftrendzeit.s.FILIALNR, parauftrendzeit.s.BATCHSCHREIBEN, parauftrendzeit.s.HERKUNFTSFILIALNR, parauftrendzeit.s.ABSCHLUSSMODUS, parauftrendzeit.s.ABSCHLUSSZEIT);

    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDParAuftrendzeit::OnButtonDel()
{
    CPARAUFTRENDZEIT parauftrendzeit;
    CString EingZeit;
    CString CArt;
    CString CModus;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    parauftrendzeit.s.FILIALNR = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 0)));
    CArt = m_ListCtl.GetItemText(pos, 1);
    Art2Long(&parauftrendzeit.s.BATCHSCHREIBEN, CArt);
    parauftrendzeit.s.HERKUNFTSFILIALNR = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 2)));
    CModus = m_ListCtl.GetItemText(pos, 3);
    Modus2Int(&parauftrendzeit.s.ABSCHLUSSMODUS,CModus);
    EingZeit = m_ListCtl.GetItemText(pos, 4);
    if (EingZeit.IsEmpty())
        parauftrendzeit.s.ABSCHLUSSZEIT = 0;
    else if ((parauftrendzeit.s.ABSCHLUSSZEIT = AllgZeitEingKonv(EingZeit)) == -1)
        parauftrendzeit.s.ABSCHLUSSZEIT = 0;
    if (MsgBoxYesNo(IDP_SOLL_DEL_SATZ) != IDYES)
        return;
    BeginWaitCursor();
    parauftrendzeit.Server(AafilDel_auftrendzeit);
    EndWaitCursor();
    ReadDataInListBox();
}

void CDParAuftrendzeit::OnButtonNeu()
{
    CDParAuftrendzeitUpd dlgParAuftrendzeitUpd;
    CPARAUFTRENDZEIT parauftrendzeit;
    dlgParAuftrendzeitUpd.m_iFiliale = m_FilialNr;
    dlgParAuftrendzeitUpd.m_IModus = 1;
    dlgParAuftrendzeitUpd.m_LArt = 1;
    if (dlgParAuftrendzeitUpd.DoModal() != IDOK)
        return;
    BeginWaitCursor();
    parauftrendzeit.s.FILIALNR = static_cast<short>(dlgParAuftrendzeitUpd.m_iFiliale);
    parauftrendzeit.s.HERKUNFTSFILIALNR = static_cast<short>(atoi(dlgParAuftrendzeitUpd.m_CHerkunft));
    parauftrendzeit.s.ABSCHLUSSMODUS = static_cast<short>(dlgParAuftrendzeitUpd.m_IModus);
    parauftrendzeit.s.BATCHSCHREIBEN = dlgParAuftrendzeitUpd.m_LArt;
    if (dlgParAuftrendzeitUpd.m_CZeit.IsEmpty())
        parauftrendzeit.s.ABSCHLUSSZEIT = 0;
    else if ((parauftrendzeit.s.ABSCHLUSSZEIT = AllgZeitEingKonv(dlgParAuftrendzeitUpd.m_CZeit)) == -1)
        parauftrendzeit.s.ABSCHLUSSZEIT = 0;
    parauftrendzeit.Server(AafilIns_auftrendzeit);
    EndWaitCursor();
    ReadDataInListBox();
}

void CDParAuftrendzeit::OnButtonUpd()
{
    CDParAuftrendzeitUpd dlgParAuftrendzeitUpd;
    CPARAUFTRENDZEIT parauftrendzeit_del;
    CPARAUFTRENDZEIT parauftrendzeit_ins;
    CString CArt;
    CString CModus;
    CString EingZeit;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    parauftrendzeit_del.s.FILIALNR = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 0)));
    CArt = m_ListCtl.GetItemText(pos, 1);
    Art2Long(&parauftrendzeit_del.s.BATCHSCHREIBEN, CArt);
    parauftrendzeit_del.s.HERKUNFTSFILIALNR = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 2)));
    CModus = m_ListCtl.GetItemText(pos, 3);
    Modus2Int(&parauftrendzeit_del.s.ABSCHLUSSMODUS, CModus);
    EingZeit = m_ListCtl.GetItemText(pos, 4);
    dlgParAuftrendzeitUpd.m_CZeit = EingZeit;
    dlgParAuftrendzeitUpd.m_iFiliale = parauftrendzeit_del.s.FILIALNR;
    dlgParAuftrendzeitUpd.m_CHerkunft = m_ListCtl.GetItemText(pos, 2);
    dlgParAuftrendzeitUpd.m_IModus = parauftrendzeit_del.s.ABSCHLUSSMODUS;
    dlgParAuftrendzeitUpd.m_LArt = parauftrendzeit_del.s.BATCHSCHREIBEN;
    if (EingZeit.IsEmpty())
        parauftrendzeit_del.s.ABSCHLUSSZEIT = 0;
    else if ((parauftrendzeit_del.s.ABSCHLUSSZEIT = AllgZeitEingKonv(EingZeit)) == -1)
        parauftrendzeit_del.s.ABSCHLUSSZEIT = 0;
    if (dlgParAuftrendzeitUpd.DoModal() != IDOK)
        return;
    BeginWaitCursor();
    parauftrendzeit_del.Server(AafilDel_auftrendzeit);
    parauftrendzeit_ins.s.FILIALNR = static_cast<short>(dlgParAuftrendzeitUpd.m_iFiliale);
    parauftrendzeit_ins.s.HERKUNFTSFILIALNR = static_cast<short>(atoi(dlgParAuftrendzeitUpd.m_CHerkunft));
    parauftrendzeit_ins.s.ABSCHLUSSMODUS = static_cast<short>(dlgParAuftrendzeitUpd.m_IModus);
    parauftrendzeit_ins.s.BATCHSCHREIBEN = dlgParAuftrendzeitUpd.m_LArt;
    if (dlgParAuftrendzeitUpd.m_CZeit.IsEmpty())
        parauftrendzeit_ins.s.ABSCHLUSSZEIT = 0;
    else if ((parauftrendzeit_ins.s.ABSCHLUSSZEIT = AllgZeitEingKonv(dlgParAuftrendzeitUpd.m_CZeit)) == -1)
        parauftrendzeit_ins.s.ABSCHLUSSZEIT = 0;
    parauftrendzeit_ins.Server(AafilIns_auftrendzeit);
    EndWaitCursor();
    ReadDataInListBox();
}

void CDParAuftrendzeit::Art2Char(long Art, CString &CArt)
{
    if      (Art == VB) CArt = CResString::ex().getStrTblText(AETXT_VERBUND);
    else if (Art == CL) CArt = CResString::ex().getStrTblText(AETXT_CLEARING);
    else if (Art == ER) CArt = CResString::ex().getStrTblText(AETXT_EINRICHT);
    else if (Art == LA) CArt = CResString::ex().getStrTblText(AETXT_VORRAT);
    else if (Art == LV) CArt = CResString::ex().getStrTblText(AETXT_UEBERVORRAT);
    else if (Art == IR) CArt = CResString::ex().getStrTblText(AETXT_RETOURE);
    else if (Art == SH) CArt = CResString::ex().getStrTblText(AETXT_STAMMHAUS);
    else if (Art == KF) CArt = CResString::ex().getStrTblText(AETXT_FEHLERAUFTRAG);
    else if (Art == UE) CArt = CResString::ex().getStrTblText(AETXT_UW);
    else if (Art == BC) CArt = CResString::ex().getStrTblText(AETXT_CHARGEN_RUECKRUF);
    else if (Art == CC) CArt = CResString::ex().getStrTblText(AETXT_CANCEL_CREMA);
    else if (Art == VU) CArt = CResString::ex().getStrTblText(AETXT_VB_UMBUCH);
    else if (Art == IT) CArt = CResString::ex().getStrTblText(AETXT_IT_TRANSFERORDER);
}

void CDParAuftrendzeit::Modus2Char(short Modus, CString &CModus)
{
    if      (Modus == D) CModus = CResString::ex().getStrTblText(AETXT_DOZ);
    else if (Modus == E) CModus = CResString::ex().getStrTblText(AETXT_EMZ);
    else if (Modus == P) CModus = CResString::ex().getStrTblText(AETXT_PMZ);
    else                 CModus = CResString::ex().getStrTblText(AETXT_INTERN);
}

void CDParAuftrendzeit::Modus2Int(short *Modus, CString CModus)
{
    if      (CModus == CResString::ex().getStrTblText(AETXT_DOZ)) *Modus = D;
    else if (CModus == CResString::ex().getStrTblText(AETXT_EMZ)) *Modus = E;
    else if (CModus == CResString::ex().getStrTblText(AETXT_PMZ)) *Modus = P;
    else                                                          *Modus = X;
}

void CDParAuftrendzeit::Art2Long(long *Art, CString CArt)
{
    if      (CArt == CResString::ex().getStrTblText(AETXT_VERBUND))           *Art = VB;
    else if (CArt == CResString::ex().getStrTblText(AETXT_CLEARING))          *Art = CL;
    else if (CArt == CResString::ex().getStrTblText(AETXT_EINRICHT))          *Art = ER;
    else if (CArt == CResString::ex().getStrTblText(AETXT_VORRAT))            *Art = LA;
    else if (CArt == CResString::ex().getStrTblText(AETXT_UEBERVORRAT))       *Art = LV;
    else if (CArt == CResString::ex().getStrTblText(AETXT_RETOURE))           *Art = IR;
    else if (CArt == CResString::ex().getStrTblText(AETXT_STAMMHAUS))         *Art = SH;
    else if (CArt == CResString::ex().getStrTblText(AETXT_FEHLERAUFTRAG))     *Art = KF;
    else if (CArt == CResString::ex().getStrTblText(AETXT_UW))                *Art = UE;
    else if (CArt == CResString::ex().getStrTblText(AETXT_CHARGEN_RUECKRUF))  *Art = BC;
    else if (CArt == CResString::ex().getStrTblText(AETXT_CANCEL_CREMA))      *Art = CC;
    else if (CArt == CResString::ex().getStrTblText(AETXT_VB_UMBUCH))         *Art = VU;
    else if (CArt == CResString::ex().getStrTblText(AETXT_IT_TRANSFERORDER))  *Art = IT;
}

/////////////////////////////////////////////////////////////////////////////
// CDParAuftrendzeitUpd dialog


CDParAuftrendzeitUpd::CDParAuftrendzeitUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParAuftrendzeitUpd::IDD, pParent)
{
    m_iFiliale = 0;
    m_CHerkunft = _T("");
    m_CZeit = _T("");
    m_IRadio11 = -1;
    m_IRadio31 = -1;
}


void CDParAuftrendzeitUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ZEIT, m_EditZeit);
    DDX_Control(pDX, IDC_EDIT_HERKUNFT, m_EditHerkunft);
    DDX_Control(pDX, IDC_EDIT_FILIALE, m_EditFiliale);
    DDX_Text(pDX, IDC_EDIT_FILIALE, m_iFiliale);
    DDX_Text(pDX, IDC_EDIT_HERKUNFT, m_CHerkunft);
    DDX_Text(pDX, IDC_EDIT_ZEIT, m_CZeit);
    DDX_Radio(pDX, IDC_RADIO11, m_IRadio11);
    DDX_Radio(pDX, IDC_RADIO31, m_IRadio31);
}


BEGIN_MESSAGE_MAP(CDParAuftrendzeitUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_ZEIT, OnChangeEditZeit)
    ON_EN_CHANGE(IDC_EDIT_HERKUNFT, OnChangeEditHerkunft)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParAuftrendzeitUpd message handlers

BOOL CDParAuftrendzeitUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    GetDlgItem( IDC_EDIT_FILIALE )->EnableWindow(FALSE);
    if      (m_IModus == 1) CheckRadioButton(IDC_RADIO31,IDC_RADIO33,IDC_RADIO31);
    else if (m_IModus == 2) CheckRadioButton(IDC_RADIO31,IDC_RADIO33,IDC_RADIO32);
    else if (m_IModus == 3) CheckRadioButton(IDC_RADIO31,IDC_RADIO33,IDC_RADIO33);
    if      (m_LArt == 1) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO11);
    else if (m_LArt == 2) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO12);
    else if (m_LArt == 3) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO13);
    else if (m_LArt == 4) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO14);
    else if (m_LArt == 5) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO15);
    else if (m_LArt == 6) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO16);
    else if (m_LArt == 7) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO17);
    else if (m_LArt == 8) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO18);
    else if (m_LArt == 9) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO19);
    else if (m_LArt == 16) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO20);
    else if (m_LArt == 19) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO21);
    else if (m_LArt == 18) CheckRadioButton(IDC_RADIO11, IDC_RADIO23, IDC_RADIO22);
    else if (m_LArt == 20) CheckRadioButton(IDC_RADIO11,IDC_RADIO23,IDC_RADIO23);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParAuftrendzeitUpd::OnOK()
{
    int id;         //ID of the checked radio button
    CPARAUFTRENDZEIT parauftrendzeit;
    UpdateData();
    id = GetCheckedRadioButton(IDC_RADIO11, IDC_RADIO23);
    if      (id == IDC_RADIO11) m_LArt = 1;
    else if (id == IDC_RADIO12) m_LArt = 2;
    else if (id == IDC_RADIO13) m_LArt = 3;
    else if (id == IDC_RADIO14) m_LArt = 4;
    else if (id == IDC_RADIO15) m_LArt = 5;
    else if (id == IDC_RADIO16) m_LArt = 6;
    else if (id == IDC_RADIO17) m_LArt = 7;
    else if (id == IDC_RADIO18) m_LArt = 8;
    else if (id == IDC_RADIO19) m_LArt = 9;
    else if (id == IDC_RADIO20) m_LArt = 16;
    else if (id == IDC_RADIO21) m_LArt = 19;
    else if (id == IDC_RADIO22) m_LArt = 18;
    else if (id == IDC_RADIO23) m_LArt = 20;
    id = GetCheckedRadioButton(IDC_RADIO31, IDC_RADIO33);
    if      (id == IDC_RADIO31) m_IModus = 1;
    else if (id == IDC_RADIO32) m_IModus = 2;
    else if (id == IDC_RADIO33) m_IModus = 3;
    CDialogMultiLang::OnOK();
}


void CDParAuftrendzeitUpd::OnChangeEditZeit()
{
    AllgZeitKontr(&m_EditZeit);
}

void CDParAuftrendzeitUpd::OnChangeEditHerkunft()
{
    AllgWertKontr(&m_EditHerkunft, MAXIMUM_FILIALE);
}
