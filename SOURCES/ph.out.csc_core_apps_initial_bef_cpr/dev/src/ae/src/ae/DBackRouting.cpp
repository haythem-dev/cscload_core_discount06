// DBackRouting.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <filialpartner.h>
#include "DBackRouting.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 120, LVCFMT_LEFT,
    2,  "", 120, LVCFMT_LEFT,
    -1, "",   0, 0
};


// CDBackRouting-Dialogfeld

IMPLEMENT_DYNAMIC(CDBackRouting, CDialog)
CDBackRouting::CDBackRouting(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBackRouting::IDD, pParent)
    , m_cAbteilung(_T(""))
    , m_cTelNr(_T(""))
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_ABTEILUNG);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_TELEFON_NR);
}

CDBackRouting::~CDBackRouting()
{
}

void CDBackRouting::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_EDIT_ABTEILUNG, m_exit_Abteilung);
    DDX_Text(pDX, IDC_EDIT_ABTEILUNG, m_cAbteilung);
    DDX_Control(pDX, IDC_EDIT_TELNR, m_edit_TelNr);
    DDX_Text(pDX, IDC_EDIT_TELNR, m_cTelNr);
}


BEGIN_MESSAGE_MAP(CDBackRouting, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_ABTEILUNG, OnEnChangeEditAbteilung)
    ON_EN_CHANGE(IDC_EDIT_TELNR, OnEnChangeEditTelnr)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CDBackRouting-Meldungshandler


BOOL CDBackRouting::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDBackRouting::OnEnChangeEditAbteilung()
{
    AllgLaengeKontr(&m_exit_Abteilung, L_BACKROUT_DEPARTEMENT,AeGetApp()->Modus());
}

void CDBackRouting::OnEnChangeEditTelnr()
{
    AllgLaengeKontr(&m_edit_TelNr, L_BACKROUT_PHONENO,AeGetApp()->Modus());
}

void CDBackRouting::OnBnClickedButtonInsert()
{
    UpdateData(TRUE);
    if (m_cTelNr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_TELNR);
        return;
    }
    if (m_cAbteilung.IsEmpty())
    {
        MsgBoxOK(AETXT_MUSS_ABTEILUNG);
        return;
    }
    m_BackRouting.SetBranchno(AeGetApp()->VzNr());
    m_BackRouting.SetDepartement(m_cAbteilung);
    m_BackRouting.SetPhoneno(m_cTelNr);
    if (m_BackRouting.Insert() == 0)
        GetPage();
}

void CDBackRouting::OnBnClickedButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            m_BackRouting.SetBranchno(AeGetApp()->VzNr());
            m_BackRouting.SetDepartement(m_ListCtl.GetItemText(pos, 1));
            m_BackRouting.SetPhoneno(m_ListCtl.GetItemText(pos, 2));
            if (m_BackRouting.Delete() == 0)
                GetPage();
        }
    }
}

void CDBackRouting::GetPage()
{
    ppString cDepartement;
    ppString cPhoneno;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    m_BackRouting.SetBranchno(AeGetApp()->VzNr());
    for (;;)
    {
        if (m_BackRouting.SelList() != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%s",m_BackRouting.GetDepartement(cDepartement));
        s[2].Format("%s",m_BackRouting.GetPhoneno(cPhoneno));

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_BackRouting.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}
