// DParNachart.cpp : implementation file
//

#include "stdafx.h"
#include "DParNachart.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     4

static COLUMNS_TYPES Columns[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "",  40, LVCFMT_CENTER,
    2,  "",  40, LVCFMT_CENTER,
    3,  "", 140, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDParNachart dialog


CDParNachart::CDParNachart(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParNachart::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KZ_FILIALE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_KZ_FORMULARKENNUNG);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_KZ_LAGEREBENE);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_NACHRICHT);
}


void CDParNachart::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDParNachart, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnButtonNeu)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParNachart message handlers

BOOL CDParNachart::OnInitDialog()
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

void CDParNachart::AddPosToList(int Filiale, CString Formk, CString Lb, CString Na)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    s[0].Format("%d", Filiale);
    s[1] = Formk;
    s[2] = Lb;
    s[3] = Na;

    CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s);
}

void CDParNachart::ReadDataInListBox()
{
    CPARNACHRART parnachrart;
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    parnachrart.s.FILIALNR = m_FilialNr;
    for (;;)
    {
        parnachrart.s.FETCH_REL = 1;              //normaler Fetch
        parnachrart.Server(AafilSelnachart);
        if (parnachrart.rc == SRV_SQLNOTFOUND)
        {
            parnachrart.s.FETCH_REL = 0;          //close Cursor
            parnachrart.Server(AafilSelnachart);
            break;
        }
        AllgEntfSpaces(parnachrart.s.FORMULARKUERZEL);
        AllgEntfSpaces(parnachrart.s.LAGERBEREICHNR);
        AllgEntfSpaces(parnachrart.s.NACHRICHTENART);
        AddPosToList(parnachrart.s.FILIALNR, parnachrart.s.FORMULARKUERZEL, parnachrart.s.LAGERBEREICHNR, parnachrart.s.NACHRICHTENART);

    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDParNachart::OnButtonDel()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    CString Filiale = m_ListCtl.GetItemText(pos, 0);
    CString Formk = m_ListCtl.GetItemText(pos, 1);
    CString Lbnr = m_ListCtl.GetItemText(pos, 2);
    if (MsgBoxYesNo(IDP_PAR_NACHART_DEL) != IDYES)
        return;
    CPARNACHRART parnachrart;
    parnachrart.s.FILIALNR = static_cast<short>(atoi(Filiale));
    AllgStrCopy(parnachrart.s.FORMULARKUERZEL, Formk, L_PARNACHRART_FORMULARKUERZEL);
    AllgStrCopy(parnachrart.s.LAGERBEREICHNR, Lbnr, L_PARNACHRART_LAGERBEREICHNR);
    BeginWaitCursor();
    parnachrart.Server(AafilDelnachart);

    EndWaitCursor();
    ReadDataInListBox();
}

void CDParNachart::OnButtonNeu()
{
    CDParNachartUpd dlgParNachartUpd;
    dlgParNachartUpd.m_bUpdate = FALSE;
    dlgParNachartUpd.m_iFiliale = m_FilialNr;
    dlgParNachartUpd.DoModal();
    ReadDataInListBox();
}

void CDParNachart::OnButtonUpd()
{
    CDParNachartUpd dlgParNachartUpd;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    dlgParNachartUpd.m_CFormk   = m_ListCtl.GetItemText(pos, 1);
    dlgParNachartUpd.m_CLbnr    = m_ListCtl.GetItemText(pos, 2);
    dlgParNachartUpd.m_CNa      = m_ListCtl.GetItemText(pos, 3);
    dlgParNachartUpd.m_iFiliale = atoi(m_ListCtl.GetItemText(pos, 0));
    dlgParNachartUpd.m_bUpdate = TRUE;
    dlgParNachartUpd.DoModal();
    ReadDataInListBox();
}

/////////////////////////////////////////////////////////////////////////////
// CDParNachartUpd dialog

CDParNachartUpd::CDParNachartUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParNachartUpd::IDD, pParent)
{
    m_iFiliale = 0;
    m_CFormk = _T("");
    m_CLbnr = _T("");
    m_CNa = _T("");
}


void CDParNachartUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_NA, m_EditNa);
    DDX_Control(pDX, IDC_EDIT_LBNR, m_EditLbnr);
    DDX_Control(pDX, IDC_EDIT_FORMK, m_EditFormk);
    DDX_Control(pDX, IDC_EDIT_FILIALE, m_EditFiliale);
    DDX_Text(pDX, IDC_EDIT_FILIALE, m_iFiliale);
    DDX_Text(pDX, IDC_EDIT_FORMK, m_CFormk);
    DDX_Text(pDX, IDC_EDIT_LBNR, m_CLbnr);
    DDX_Text(pDX, IDC_EDIT_NA, m_CNa);
}


BEGIN_MESSAGE_MAP(CDParNachartUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_FORMK, OnChangeEditFormk)
    ON_EN_CHANGE(IDC_EDIT_LBNR, OnChangeEditLbnr)
    ON_EN_CHANGE(IDC_EDIT_NA, OnChangeEditNa)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParNachartUpd message handlers

BOOL CDParNachartUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    GetDlgItem( IDC_EDIT_FILIALE )->EnableWindow(FALSE);
    GetDlgItem( IDC_STATIC_FILIALE )->EnableWindow(FALSE);

    if (m_bUpdate)
    {
        GetDlgItem(IDC_EDIT_NA)->SetFocus();
        GetDlgItem(IDC_EDIT_FORMK)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_LBNR)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_FK)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_LB)->EnableWindow(FALSE);
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParNachartUpd::OnOK()
{
    CPARNACHRART parnachrart;
    UpdateData();
    AllgStrCopy(parnachrart.s.FORMULARKUERZEL, m_CFormk, L_PARNACHRART_FORMULARKUERZEL);
    AllgStrCopy(parnachrart.s.LAGERBEREICHNR, m_CLbnr, L_PARNACHRART_LAGERBEREICHNR);
    AllgStrCopy(parnachrart.s.NACHRICHTENART, m_CNa, L_PARNACHRART_NACHRICHTENART);
    parnachrart.s.FILIALNR = static_cast<short>(m_iFiliale);
    BeginWaitCursor();
    if (m_bUpdate)
        parnachrart.Server(AafilUpdnachart);
    else
    {
        parnachrart.Server(AafilInsnachart);
        if (parnachrart.rc == -2)
            GetDlgItem(IDC_EDIT_NA)->SetFocus();
    }
    EndWaitCursor();
    if (parnachrart.rc < SRV_OK)
        return;
    CDialogMultiLang::OnOK();
}

void CDParNachartUpd::OnChangeEditFormk()
{
    AllgLaengeKontr(&m_EditFormk, L_PARNACHRART_FORMULARKUERZEL, AeGetApp()->Modus());
}

void CDParNachartUpd::OnChangeEditLbnr()
{
    AllgLaengeKontr(&m_EditLbnr, L_PARNACHRART_LAGERBEREICHNR, AeGetApp()->Modus());
}

void CDParNachartUpd::OnChangeEditNa()
{
    AllgLaengeKontr(&m_EditNa, L_PARNACHRART_NACHRICHTENART, AeGetApp()->Modus());
}
