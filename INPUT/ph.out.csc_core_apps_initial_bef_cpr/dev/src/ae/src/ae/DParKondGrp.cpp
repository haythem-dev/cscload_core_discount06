// DParKondGrp.cpp : implementation file
//

#include "stdafx.h"
#include "DParKondGrp.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     2

static COLUMNS_TYPES Columns[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "", 140, LVCFMT_LEFT,
    -1, "",  0,  0
};

#define MAXIMUM_KNDGRPNR    99

/////////////////////////////////////////////////////////////////////////////
// CDParKondGrp dialog


CDParKondGrp::CDParKondGrp(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParKondGrp::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KZ_KUNDENGRUPPE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
}


void CDParKondGrp::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDParKondGrp, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnButtonNeu)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParKondGrp message handlers

BOOL CDParKondGrp::OnInitDialog()
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

void CDParKondGrp::AddPosToList(long KndGrp, CString KText)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    s[0].Format("%ld", KndGrp);
    s[1] = KText;

    CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s);
}

void CDParKondGrp::ReadDataInListBox()
{
    CPARKONGRP parkongrp;
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    for (;;)
    {
        parkongrp.s.FETCH_REL = 1;              //normaler Fetch
        parkongrp.Server(AafilSelkondgr);
        if (parkongrp.rc == SRV_SQLNOTFOUND)
        {
            parkongrp.s.FETCH_REL = 0;          //close Cursor
            parkongrp.Server(AafilSelkondgr);
            break;
        }
        AllgEntfSpaces(parkongrp.s.BEZEICHNUNG);
        AddPosToList(parkongrp.s.KONDGRUPPENNR, parkongrp.s.BEZEICHNUNG);
    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDParKondGrp::OnButtonDel()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    CString KBst = m_ListCtl.GetItemText(pos, 0);

    CString CStr;
    CStr.Format(CResString::ex().getStrTblText(IDP_PAR_KNDGRP_DEL), KBst.GetString());
    if (MsgBoxYesNo(CStr) != IDYES)
        return;
    CPARKONGRP parkongrp;
    parkongrp.s.KONDGRUPPENNR = atol(KBst);
    BeginWaitCursor();
    parkongrp.Server(AafilDelkondgr);

    EndWaitCursor();
    ReadDataInListBox();
}

void CDParKondGrp::OnButtonNeu()
{
    CDParKondGrpUpd dlgParKondGrpUpd;
    dlgParKondGrpUpd.m_bUpdate = FALSE;
    dlgParKondGrpUpd.DoModal();
    ReadDataInListBox();
}

void CDParKondGrp::OnButtonUpd()
{
    CDParKondGrpUpd dlgParKondGrpUpd;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    dlgParKondGrpUpd.m_CBezeichnung = m_ListCtl.GetItemText(pos, 1);
    dlgParKondGrpUpd.m_lGrpNr       = atol(m_ListCtl.GetItemText(pos, 0));
    dlgParKondGrpUpd.m_bUpdate = TRUE;
    dlgParKondGrpUpd.DoModal();
    ReadDataInListBox();
}

/////////////////////////////////////////////////////////////////////////////
// CDParKondGrpUpd dialog

CDParKondGrpUpd::CDParKondGrpUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParKondGrpUpd::IDD, pParent)
{
    m_CBezeichnung = _T("");
    m_lGrpNr = 0;
    m_bUpdate = FALSE;
}


void CDParKondGrpUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_GRPNR, m_EditGrpNr);
    DDX_Control(pDX, IDC_EDIT_BEZEICHNUNG, m_EditBezeichnung);
    DDX_Text(pDX, IDC_EDIT_BEZEICHNUNG, m_CBezeichnung);
    DDX_Text(pDX, IDC_EDIT_GRPNR, m_lGrpNr);
}


BEGIN_MESSAGE_MAP(CDParKondGrpUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_BEZEICHNUNG, OnChangeEditBezeichnung)
    ON_EN_CHANGE(IDC_EDIT_GRPNR, OnChangeEditGrpnr)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParKondGrpUpd message handlers

BOOL CDParKondGrpUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (m_bUpdate)
    {
        GetDlgItem( IDC_EDIT_BEZEICHNUNG )->SetFocus();
        GetDlgItem( IDC_EDIT_GRPNR )->EnableWindow(FALSE);
        GetDlgItem( IDC_STATIC_GRPNR )->EnableWindow(FALSE);
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParKondGrpUpd::OnOK()
{
    CPARKONGRP parkongrp;
    UpdateData();
    AllgStrCopy(parkongrp.s.BEZEICHNUNG, m_CBezeichnung, L_PARKONGRP_BEZEICHNUNG);
    parkongrp.s.KONDGRUPPENNR = m_lGrpNr;
    BeginWaitCursor();
    if (m_bUpdate)
        parkongrp.Server(AafilUpdkondgr);
    else
    {
        parkongrp.Server(AafilInskondgr);
        if (parkongrp.rc == -2)
            GetDlgItem(IDC_EDIT_GRPNR)->SetFocus();
    }
    EndWaitCursor();
    if (parkongrp.rc < SRV_OK)
        return;

    CDialogMultiLang::OnOK();
}

void CDParKondGrpUpd::OnChangeEditBezeichnung()
{
    AllgLaengeKontr(&m_EditBezeichnung, L_PARKONGRP_BEZEICHNUNG,AeGetApp()->Modus());
}

void CDParKondGrpUpd::OnChangeEditGrpnr()
{
    AllgWertKontr(&m_EditGrpNr, MAXIMUM_KNDGRPNR);
}
