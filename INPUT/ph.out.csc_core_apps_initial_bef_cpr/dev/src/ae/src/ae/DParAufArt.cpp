// DParAufArt.cpp : implementation file
//

#include "stdafx.h"
#include "DParAufArt.h"
#include <auftragsart.h>
#include "DOrderTypeManager.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS_AART     4

static COLUMNS_TYPES Columns[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "",  50, LVCFMT_CENTER,
    2,  "", 140, LVCFMT_LEFT,
    3,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDParAufArt dialog


CDParAufArt::CDParAufArt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParAufArt::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KZ_AUFTRAGSART);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_GLOB);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
}


void CDParAufArt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDParAufArt, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnButtonNeu)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParAufArt message handlers

void CDParAufArt::OnOK()
{
    CDialogMultiLang::OnOK();
}

BOOL CDParAufArt::OnInitDialog()
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

void CDParAufArt::AddPosToList(CString AArt,
                               CString AText,
                               CString AGlobal,
                               CString AStandard)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS_AART);

    s[0] = AArt;
    s[1] = (AGlobal == "1") ? "J" : "N";
    s[2] = AText;
    s[3] = AStandard;

    CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS_AART, s);
}

void CDParAufArt::ReadDataInListBox()
{
    int rc;
    char error_msg[81];
    CAUFTRAGSART aart;
    CString cStandard;
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    aart.SetBranchno(AeGetApp()->VzNr());   //nur eigenes VZ
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvSelAllCscOrderType, (void*)&aart.s, AUFTRAGSART_BES, AUFTRAGSART_ANZ, error_msg);
        if (rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        AllgEntfSpaces(aart.s.KDAUFTRAGART);
        AllgEntfSpaces(aart.s.BEZEICHNUNG);
        cStandard = aart.GetSstandard();
        AddPosToList(aart.s.KDAUFTRAGART, aart.s.BEZEICHNUNG, aart.s.SGLOBAL, cStandard);

    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDParAufArt::OnButtonDel()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    if (m_ListCtl.GetItemText(pos, 3).GetAt(0) == '1')
    {
        MsgBoxOK(AETXT_NO_DEL_STD);
        return;
    }
    CString KBst = m_ListCtl.GetItemText(pos, 0);
    CString CStr;
    CStr.Format(CResString::ex().getStrTblText(IDP_PAR_AART_DEL), KBst.GetString());
    if (MsgBoxYesNo(CStr) != IDYES)
        return;
    CAUFTRAGSART aart;
    aart.SetBranchno(AeGetApp()->VzNr());    //nur eigenes VZ
    aart.SetKdauftragart(KBst);
    BeginWaitCursor();
    char error_msg[81];
    ::ServerNr(PIPE_AE_SRV, AasrvDelCscOrderType, (void*)&aart.s, AUFTRAGSART_BES, AUFTRAGSART_ANZ, error_msg);

    EndWaitCursor();
    ReadDataInListBox();
}

void CDParAufArt::OnButtonNeu()
{
    CDOrderTypeManager typemanager;
    typemanager.m_sSaleCenterNo = AeGetApp()->VzNr();    //nur eigenes VZ
    typemanager.m_bUpdate = FALSE;
    if (typemanager.DoModal() == IDOK)
    {
        ReadDataInListBox();
    }
}

void CDParAufArt::OnButtonUpd()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    CDOrderTypeManager typemanager;
    typemanager.m_sSaleCenterNo = AeGetApp()->VzNr();   //nur eigenes VZ
    typemanager.m_CKBst         = m_ListCtl.GetItemText(pos, 0);
    typemanager.m_bUpdate = TRUE;
    if (typemanager.DoModal() == IDOK)
    {
        ReadDataInListBox();
    }
}

void CDParAufArt::OnCancel()
{
    CDialogMultiLang::OnCancel();
}
