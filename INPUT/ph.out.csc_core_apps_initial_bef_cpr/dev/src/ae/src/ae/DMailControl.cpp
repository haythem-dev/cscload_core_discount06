// DMailControl.cpp : implementation file
//

#include "stdafx.h"
#include <mailsystem.h>
#include "DMailControl.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  80, LVCFMT_LEFT,
    2,  "",  50, LVCFMT_LEFT,
    3,  "",  50, LVCFMT_LEFT,
    4,  "", 200, LVCFMT_LEFT,
    5,  "",  50, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_COLUMNS2    5

static COLUMNS_TYPES Columns2[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  30, LVCFMT_LEFT,
    2,  "",  30, LVCFMT_LEFT,
    3,  "", 100, LVCFMT_LEFT,
    4,  "",  50, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDMailControl dialog


CDMailControl::CDMailControl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDMailControl::IDD, pParent)
{
    m_CDatum = _T("");

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[2].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_TEXT);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_RR_OFFEN);

    Columns2[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns2[1].Columns = CResString::ex().getStrTblText(AETXT_KZ_FILIALE);
    Columns2[2].Columns = CResString::ex().getStrTblText(AETXT_KURZ_TOUR_ID);
    Columns2[3].Columns = CResString::ex().getStrTblText(IDS_ANWENDER);
    Columns2[4].Columns = CResString::ex().getStrTblText(AETXT_GRUPPE);
}


void CDMailControl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_DATUM, m_Edit_Datum);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Text(pDX, IDC_EDIT_DATUM, m_CDatum);
}


BEGIN_MESSAGE_MAP(CDMailControl, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_ANZEIGE, OnButtonAnzeige)
    ON_EN_CHANGE(IDC_EDIT_DATUM, OnChangeEditDatum)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMailControl message handlers

void CDMailControl::OnButtonAnzeige()
{
    SelectEintrag();
}

void CDMailControl::OnChangeEditDatum()
{
    AllgDatumKontr(&m_Edit_Datum, ALGF_FORM_DATUM_TTMMJJ);
}

void CDMailControl::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDMailControl::OnOK()
{
    //Variablen
    long datum;
    ppString text;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    UpdateData();

    if (m_CDatum.IsEmpty())
        datum = 0;
    else
    {
        datum = AllgDatumEingKonv(m_CDatum, ALGF_FORM_DATUM_TTMMJJ);
        if (datum < 0)
        {
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_DATUM));
            return;
        }
    }

    //Select bestimmen
    int id = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO1);

    //Anfangsinitialisierung durchfuehren
    m_List1.DeleteAllItems();
    m_mes.SetTm_date(datum);
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        int rc = (id == IDC_RADIO1) ? m_mes.SelNotRead() : m_mes.SelAllMessage();
        if (rc != SRV_OK)
        {
            break;
        }
        s[0] = kb.Next();
        s[1] = DDMMYYYYStringFromDateLong(m_mes.GetTm_date());
        s[2] = HHmmStringFromTimeLong(m_mes.GetTm_time());
        s[3].Format("%ld", m_mes.GetNewsno());
        m_mes.GetMessage(text);
        s[4] = text.c_str();
        s[5].Format("%d", m_mes.GetUid());

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    } //Ende der for()-Schleife
    m_mes.CloseCursor();
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);
}

BOOL CDMailControl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }
    zeit.Server(AafilGetdatetime);
    m_CDatum = DDMMYYYYStringNoDotsFromDateLong(zeit.s.DATUM);
    CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDMailControl::SelectEintrag()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDMailControlUsers dlgMailControlUsers;
        if ((dlgMailControlUsers.m_iCount = atol(m_List1.GetItemText(pos, 5))) == 0)
            return;
        dlgMailControlUsers.m_CNo = m_List1.GetItemText(pos, 3);
        dlgMailControlUsers.m_CText = m_List1.GetItemText(pos, 4);
        dlgMailControlUsers.DoModal();
        CString anzahl;
        anzahl.Format("%d", dlgMailControlUsers.m_iCount);
        m_List1.SetItemText(pos, 5, anzahl);
        int id = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO1);
        if (id == IDC_RADIO1)
        {
            if (dlgMailControlUsers.m_iCount <= 0)
                m_List1.DeleteItem(pos);
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
// CDMailControlUsers dialog


CDMailControlUsers::CDMailControlUsers(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDMailControlUsers::IDD, pParent)
{
    m_CText = _T("");
    m_CNo = _T("");
}


void CDMailControlUsers::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, m_List2);
    DDX_Text(pDX, IDC_EDIT_TEXT, m_CText);
    DDX_Text(pDX, IDC_STATIC_NO, m_CNo);
}


BEGIN_MESSAGE_MAP(CDMailControlUsers, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMailControlUsers message handlers

BOOL CDMailControlUsers::OnInitDialog()
{
    //Variablen
    ppString name;
    CStringArray s;
    s.SetSize(NUM_COLUMNS2);
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns2, m_List2))
    {
        return FALSE;
    }
    GetDlgItem(IDC_EDIT_TEXT)->EnableWindow(FALSE);
    m_List2.DeleteAllItems();
    m_def.SetGroupno(atol(m_CNo));
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_def.SelOpenMail() != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%d", m_def.GetFilialnr());
        s[2].Format("%ld", m_def.GetUid());
        m_def.GetUsername(name);
        s[3] = name.c_str();
        s[4].Format("%ld", m_def.GetGroupno());

        if (!CListCtrlHelper::AppendItem(m_List2, NUM_COLUMNS2, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    } //Ende der for()-Schleife
    m_def.CloseCursor();
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST2));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List2, 0);

    return FALSE;   // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDMailControlUsers::OnButtonDel()
{
    CMAILITEMS item;
    int pos = m_List2.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        item.SetFilialnr(static_cast<short>(atoi(m_List2.GetItemText(pos, 1))));
        item.SetUid(atol(m_List2.GetItemText(pos, 2)));
        item.SetNewsno(atol(m_CNo));
        item.DeleteMessage();
        m_List2.DeleteItem(pos);
        --m_iCount;
        GotoDlgCtrl(GetDlgItem(IDC_LIST2));
        CListCtrlHelper::SetItemStateSelectedFocused(m_List2, 0);
    }
}
