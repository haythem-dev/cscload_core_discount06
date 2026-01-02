// ae\DIbtBranches.cpp : implementation file
//

#include "stdafx.h"
#include "DIbtBranches.h"
#include <filialpartner.h>
#include <customer.h>


//Definition der Tabellenbreite und der Ueberschriften

#define COL_VBFIL_KB            0
#define COL_VBFIL_FOLGE         1
#define COL_VBFIL_FILI          2
#define COL_VBFIL_AKTIV         3
#define COL_VBFIL_TYPTEXT       4
#define COL_VBFIL_TAGVB         5
#define COL_VBFIL_BGA           6
#define COL_VBFIL_STDBGA        7
#define COL_VBFIL_STDBGA        7
#define COL_VBFIL_IBTTYPE       8
#define COL_VBFIL_SORTIMENT     9
#define COL_VBFIL_KZ_AKTIV      10
#define COL_VBFIL_KZ_TAGVB      11
#define COL_VBFIL_TYPE          12
#define COL_VBFIL_KZ_STDBGA     13
#define COL_VBFIL_S_IBTTYPE     14
#define COL_VBFIL_S_SORTIMENT   15

#define NUM_COLUMNS     16

static COLUMNS_TYPES Columns[] =
{
    COL_VBFIL_KB,          "",  20, LVCFMT_LEFT,
    COL_VBFIL_FOLGE,       "",  45, LVCFMT_RIGHT,
    COL_VBFIL_FILI,        "",  45, LVCFMT_RIGHT,
    COL_VBFIL_AKTIV,       "",  40, LVCFMT_LEFT,
    COL_VBFIL_TYPTEXT,     "", 100, LVCFMT_LEFT,
    COL_VBFIL_TAGVB,       "",  40, LVCFMT_LEFT,
    COL_VBFIL_BGA,         "", 100, LVCFMT_RIGHT,
    COL_VBFIL_STDBGA,      "",  60, LVCFMT_LEFT,
    COL_VBFIL_IBTTYPE,     "", 100, LVCFMT_LEFT,
    COL_VBFIL_SORTIMENT,   "", 100, LVCFMT_LEFT,
    COL_VBFIL_KZ_AKTIV,    "",   0, LVCFMT_LEFT,
    COL_VBFIL_KZ_TAGVB,    "",   0, LVCFMT_LEFT,
    COL_VBFIL_TYPE,        "",   0, LVCFMT_LEFT,
    COL_VBFIL_KZ_STDBGA,   "",   0, LVCFMT_LEFT,
    COL_VBFIL_S_IBTTYPE,   "",   0, LVCFMT_LEFT,
    COL_VBFIL_S_SORTIMENT, "",   0, LVCFMT_LEFT,
    -1,                    "",   0, 0
};

// CDIbtBranches dialog

IMPLEMENT_DYNAMIC(CDIbtBranches, CDialog)

CDIbtBranches::CDIbtBranches(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDIbtBranches::IDD, pParent)
{
    Columns[COL_VBFIL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_VBFIL_FOLGE].Columns = CResString::ex().getStrTblText(AETXT_FOLGE);
    Columns[COL_VBFIL_FILI].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns[COL_VBFIL_AKTIV].Columns = CResString::ex().getStrTblText(AETXT_AKTIV);
    Columns[COL_VBFIL_TYPTEXT].Columns = CResString::ex().getStrTblText(AETXT_VB_TYP);
    Columns[COL_VBFIL_TAGVB].Columns = CResString::ex().getStrTblText(AETXT_TAG_VB);
    Columns[COL_VBFIL_BGA].Columns = CResString::ex().getStrTblText(AETXT_BGA_NR_TAG);
    Columns[COL_VBFIL_STDBGA].Columns = CResString::ex().getStrTblText(AETXT_STD_BGA_NR);
    Columns[COL_VBFIL_IBTTYPE].Columns = CResString::ex().getStrTblText(AETXT_IBT_TYPE);
    Columns[COL_VBFIL_SORTIMENT].Columns = CResString::ex().getStrTblText(AETXT_SORTIMENT);
    Columns[COL_VBFIL_KZ_AKTIV].Columns = CResString::ex().getStrTblText(AETXT_AKTIV);
    Columns[COL_VBFIL_KZ_TAGVB].Columns = CResString::ex().getStrTblText(AETXT_TAG_VB);
    Columns[COL_VBFIL_TYPE].Columns = CResString::ex().getStrTblText(AETXT_VB_TYP);
    Columns[COL_VBFIL_KZ_STDBGA].Columns = CResString::ex().getStrTblText(AETXT_STD_BGA_NR);
    Columns[COL_VBFIL_S_IBTTYPE].Columns = CResString::ex().getStrTblText(AETXT_IBT_TYPE);
    Columns[COL_VBFIL_S_SORTIMENT].Columns = CResString::ex().getStrTblText(AETXT_SORTIMENT);
    m_bNLevelIBT = FALSE;

}

CDIbtBranches::~CDIbtBranches()
{
}

void CDIbtBranches::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDIbtBranches, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_INSERT, &CDIbtBranches::OnBnClickedInsert)
    ON_BN_CLICKED(IDC_DELETE, &CDIbtBranches::OnBnClickedDelete)
END_MESSAGE_MAP()


// CDIbtBranches message handlers
BOOL CDIbtBranches::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    if (!m_bNLevelIBT)
    {
        m_ListCtl.SetColumnWidth( COL_VBFIL_IBTTYPE , 0 );
        m_ListCtl.SetColumnWidth( COL_VBFIL_SORTIMENT , 0 );
    }
    else
    {
        m_ListCtl.SetColumnWidth( COL_VBFIL_TYPTEXT , 0 );
    }

    GetPage();
    return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

void CDIbtBranches::OnBnClickedInsert()
{
    CDIbtBranchesUpd dlgIbtBranchesUpd;
    dlgIbtBranchesUpd.m_bUpdate = FALSE;
    dlgIbtBranchesUpd.m_pListCtl = &m_ListCtl;
    dlgIbtBranchesUpd.m_bNLevelIBT = m_bNLevelIBT;
    if (dlgIbtBranchesUpd.DoModal() == IDOK)
    {
        CString cType;
        CIBTBRANCHESADMIN ibt;
        ibt.SetBranchno(AeGetApp()->VzNr());
        ibt.SetIbtbranchno((short)atoi(dlgIbtBranchesUpd.m_cVBFil));
        ibt.SetIbttype(dlgIbtBranchesUpd.m_sType);
        ibt.SetPriority(dlgIbtBranchesUpd.m_sFolge);
        ibt.SetNlevelibttypeid(dlgIbtBranchesUpd.m_sIBT_Type);
        ibt.SetNlevelibtassortmenttypeid(dlgIbtBranchesUpd.m_sAssorment);
        ibt.SetActive_flag(dlgIbtBranchesUpd.m_bActiv ? 1 : 0);
        ibt.SetDayibt(dlgIbtBranchesUpd.m_bDay ? 1 : 0);
        long lBGA = atol(dlgIbtBranchesUpd.m_cBGA);
        ibt.SetIbtcustomerno(lBGA == AeGetApp()->BGANR_EK() ? 0 : lBGA);
        if (!ibt.Insert())
            GetPage();
    }
}

void CDIbtBranches::OnBnClickedDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_ALTFIL_DEL) == IDYES)
        {
            CIBTBRANCHESADMIN ibt;
            ibt.SetBranchno(AeGetApp()->VzNr());
            ibt.SetPriority((short)atoi(m_ListCtl.GetItemText(pos, COL_VBFIL_FOLGE)));
            ibt.Delete();
            GetPage();
        }
    }
}

void CDIbtBranches::GetPage( )
{
    //Variablen
    CIBTBRANCHESADMIN ibtbranchesadmin;
    ibtbranchesadmin.SetBranchno(AeGetApp()->VzNr());
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (ibtbranchesadmin.SelList() != SRV_OK) break;
        //Ausgabe in die Listbox
        s[COL_VBFIL_KB] = kb.Next();
        s[COL_VBFIL_FOLGE].Format("%d", ibtbranchesadmin.GetPriority());
        s[COL_VBFIL_FILI].Format("%d", ibtbranchesadmin.GetIbtbranchno());
        if (ibtbranchesadmin.GetActive_flag() == 1) s[COL_VBFIL_AKTIV] = CResString::ex().getStrTblText(AETXT_JA);
        else s[COL_VBFIL_AKTIV] = CResString::ex().getStrTblText(AETXT_NEIN);

        //VB-TYPEN
        if (ibtbranchesadmin.GetIbttype() == 0) s[COL_VBFIL_TYPTEXT] = CResString::ex().getStrTblText(AETEXT_NORMAL);
        else if (ibtbranchesadmin.GetIbttype() == 1) s[COL_VBFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_PRIVATSORTIMENT);
        else if (ibtbranchesadmin.GetIbttype() == 2) s[COL_VBFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_VETO);
        else if (ibtbranchesadmin.GetIbttype() == 3) s[COL_VBFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_REGIONAL);
        else if (ibtbranchesadmin.GetIbttype() == 4) s[COL_VBFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_TAGVERBUND);    //gibts nicht mehr
        else if (ibtbranchesadmin.GetIbttype() == 5) s[COL_VBFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_NATIONAL);
        else s[COL_VBFIL_TYPTEXT].Empty();  //Huch, wie kann das denn sein

        //IBT-TYPEN
        if (ibtbranchesadmin.GetNlevelibttypeid() == 0) s[COL_VBFIL_IBTTYPE] = CResString::ex().getStrTblText(AETXT_NO_IBT);
        else if (ibtbranchesadmin.GetNlevelibttypeid() == 1) s[COL_VBFIL_IBTTYPE] = CResString::ex().getStrTblText(AETXT_NATIONAL);
        else if (ibtbranchesadmin.GetNlevelibttypeid() == 2) s[COL_VBFIL_IBTTYPE] = CResString::ex().getStrTblText(AETXT_REGIONAL);
        else if (ibtbranchesadmin.GetNlevelibttypeid() == 3) s[COL_VBFIL_IBTTYPE] = CResString::ex().getStrTblText(AETXT_LOKAL);
        else if (ibtbranchesadmin.GetNlevelibttypeid() == 4) s[COL_VBFIL_IBTTYPE] = CResString::ex().getStrTblText(AETXT_SPEZIAL);
        else s[COL_VBFIL_IBTTYPE].Empty();  //Huch, wie kann das denn sein

        //Sortiment-Typen
        if (ibtbranchesadmin.GetNlevelibtassortmenttypeid() == 0) s[COL_VBFIL_SORTIMENT] = CResString::ex().getStrTblText(AETXT_GENERAL);
        else if (ibtbranchesadmin.GetNlevelibtassortmenttypeid() == 1) s[COL_VBFIL_SORTIMENT] = CResString::ex().getStrTblText(AETXT_PRIVAT);
        else if (ibtbranchesadmin.GetNlevelibtassortmenttypeid() == 2) s[COL_VBFIL_SORTIMENT] = CResString::ex().getStrTblText(AETXT_VETERINARY);
        else s[COL_VBFIL_SORTIMENT].Empty();    //Huch, wie kann das denn sein

        if (ibtbranchesadmin.GetDayibt() == 1) s[COL_VBFIL_TAGVB] = CResString::ex().getStrTblText(AETXT_JA);
        else s[COL_VBFIL_TAGVB] = CResString::ex().getStrTblText(AETXT_NEIN);
        if (ibtbranchesadmin.GetIbtcustomerno() == 0)
        {
            s[COL_VBFIL_BGA].Format("%d", ibtbranchesadmin.GetBganr_ek());
            s[COL_VBFIL_STDBGA] = CResString::ex().getStrTblText(AETXT_JA);
            s[COL_VBFIL_KZ_STDBGA] = "1";
        }
        else if (ibtbranchesadmin.GetIbtcustomerno() == ibtbranchesadmin.GetBganr_ek())
        {
            s[COL_VBFIL_BGA].Format("%d", ibtbranchesadmin.GetBganr_ek());
            s[COL_VBFIL_STDBGA] = CResString::ex().getStrTblText(AETXT_JA);
            s[COL_VBFIL_KZ_STDBGA] = "1";
        }
        else
        {
            s[COL_VBFIL_BGA].Format("%d", ibtbranchesadmin.GetIbtcustomerno());
            s[COL_VBFIL_STDBGA] = CResString::ex().getStrTblText(AETXT_NEIN);
            s[COL_VBFIL_KZ_STDBGA] = "0";
        }
        s[COL_VBFIL_KZ_AKTIV].Format("%d", ibtbranchesadmin.GetActive_flag());
        s[COL_VBFIL_KZ_TAGVB].Format("%d", ibtbranchesadmin.GetDayibt());
        s[COL_VBFIL_TYPE].Format("%d", ibtbranchesadmin.GetIbttype());
        s[COL_VBFIL_S_IBTTYPE].Format("%d", ibtbranchesadmin.GetNlevelibttypeid());
        s[COL_VBFIL_S_SORTIMENT].Format("%d", ibtbranchesadmin.GetNlevelibtassortmenttypeid());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return;
}

void CDIbtBranches::OnOK()
{
    SelectEintrag();
    GetPage();
}

void CDIbtBranches::SelectEintrag()
{
    CDIbtBranchesUpd dlgIbtBranchesUpd;
    dlgIbtBranchesUpd.m_bNLevelIBT = m_bNLevelIBT;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        dlgIbtBranchesUpd.m_sFolge = (short)atoi(m_ListCtl.GetItemText(pos, COL_VBFIL_FOLGE));
        dlgIbtBranchesUpd.m_cVBFil = m_ListCtl.GetItemText(pos, COL_VBFIL_FILI);
        dlgIbtBranchesUpd.m_sType = (short)atoi(m_ListCtl.GetItemText(pos, COL_VBFIL_TYPE));
        dlgIbtBranchesUpd.m_sIBT_Type = (short)atoi(m_ListCtl.GetItemText(pos, COL_VBFIL_S_IBTTYPE));
        dlgIbtBranchesUpd.m_sAssorment = (short)atoi(m_ListCtl.GetItemText(pos, COL_VBFIL_S_SORTIMENT));
        int test1 = atoi(m_ListCtl.GetItemText(pos, COL_VBFIL_KZ_TAGVB));
        dlgIbtBranchesUpd.m_bDay = (test1 == 1) ? TRUE : FALSE;
        int test2 = atoi(m_ListCtl.GetItemText(pos, COL_VBFIL_KZ_STDBGA));
        if (test2 == 0)
            dlgIbtBranchesUpd.m_cBGA = m_ListCtl.GetItemText(pos, COL_VBFIL_BGA);
        int test3 = atoi(m_ListCtl.GetItemText(pos, COL_VBFIL_KZ_AKTIV));
        dlgIbtBranchesUpd.m_bActiv = (test3 == 1) ? TRUE : FALSE;
        dlgIbtBranchesUpd.m_bUpdate = TRUE;
        dlgIbtBranchesUpd.m_pListCtl = &m_ListCtl;
        if (dlgIbtBranchesUpd.DoModal() == IDOK)
        {
            CIBTBRANCHESADMIN ibt;
            ibt.SetBranchno(AeGetApp()->VzNr());
            ibt.SetIbttype(dlgIbtBranchesUpd.m_sType);
            ibt.SetPriority(dlgIbtBranchesUpd.m_sFolge);
            ibt.SetIbtbranchno((short)atoi(dlgIbtBranchesUpd.m_cVBFil));
            ibt.SetNlevelibttypeid(dlgIbtBranchesUpd.m_sIBT_Type);
            ibt.SetNlevelibtassortmenttypeid(dlgIbtBranchesUpd.m_sAssorment);
            ibt.SetActive_flag(dlgIbtBranchesUpd.m_bActiv ? 1 : 0);
            ibt.SetDayibt(dlgIbtBranchesUpd.m_bDay ? 1 : 0);
            long lBGA = atol(dlgIbtBranchesUpd.m_cBGA);
            ibt.SetIbtcustomerno(lBGA == AeGetApp()->BGANR_EK() ? 0 : lBGA);
            if (!ibt.Update())
                GetPage();
        }
    }
}

void CDIbtBranches::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}


// CDIbtBranchesUpd dialog

IMPLEMENT_DYNAMIC(CDIbtBranchesUpd, CDialog)

CDIbtBranchesUpd::CDIbtBranchesUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDIbtBranchesUpd::IDD, pParent)
    , m_cVBFil(_T(""))
    , m_bDay(FALSE)
    , m_cBGA(_T(""))
    , m_bActiv(TRUE)
    , m_bUpdate(FALSE)
{
    m_sAssorment = 0;
    m_sType = 0;
    m_sFolge = 0;
    m_bNLevelIBT = FALSE;
}

CDIbtBranchesUpd::~CDIbtBranchesUpd()
{
}

void CDIbtBranchesUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FOLGE, m_Combo_Folge);
    DDX_Text(pDX, IDC_EDIT_VB_FILIALE, m_cVBFil);
    DDX_Control(pDX, IDC_COMBO_VB_TYPE, m_Combo_Type);
    DDX_Check(pDX, IDC_CHECK_DAY_VB, m_bDay);
    DDX_Text(pDX, IDC_EDIT_BGA, m_cBGA);
    DDX_Check(pDX, IDC_CHECK_ACTIV, m_bActiv);
    DDX_Control(pDX, IDC_EDIT_VB_FILIALE, m_edit_vbfil);
    DDX_Control(pDX, IDC_EDIT_BGA, m_edit_BGA);
    DDX_Control(pDX, IDC_COMBO_IBT_TYPE, m_Combo_IBT_Type);
    DDX_Control(pDX, IDC_COMBO__IBT_ASSORTEMNT, m_Combo_Assortment);
}


BEGIN_MESSAGE_MAP(CDIbtBranchesUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_VB_FILIALE, &CDIbtBranchesUpd::OnEnChangeEditVbFiliale)
    ON_EN_CHANGE(IDC_EDIT_BGA, &CDIbtBranchesUpd::OnEnChangeEditBga)
END_MESSAGE_MAP()


// CDIbtBranchesUpd message handlers

BOOL CDIbtBranchesUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    if (!m_bNLevelIBT)
    {
        GetDlgItem(IDC_STATIC_IBT_TYPE)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_IBT_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_IBT_TYPE)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_IBT_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_IBT_ASSORTEMNT)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_IBT_ASSORTEMNT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO__IBT_ASSORTEMNT)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO__IBT_ASSORTEMNT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_NLEVEL_IBT)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_NLEVEL_IBT)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_VB_TYPE)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_VB_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_VB_TYPE)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_VB_TYPE)->ShowWindow(SW_HIDE);
    }

    //VB-Typen
    m_Combo_Type.ResetContent();
    CString Type;
    Type.Format("0 %s", CResString::ex().getStrTblText(AETEXT_NORMAL).GetString());
    m_Combo_Type.AddString(Type);
    Type.Format("1 %s", CResString::ex().getStrTblText(AETXT_PRIVATSORTIMENT).GetString());
    m_Combo_Type.AddString(Type);
    Type.Format("2 %s", CResString::ex().getStrTblText(AETXT_VETO).GetString());
    m_Combo_Type.AddString(Type);
    Type.Format("3 %s", CResString::ex().getStrTblText(AETXT_REGIONAL).GetString());
    m_Combo_Type.AddString(Type);
    Type.Format("5 %s", CResString::ex().getStrTblText(AETXT_NATIONAL).GetString());
    m_Combo_Type.AddString(Type);
    Type.Format("%d", m_sType);
    int iPos = m_Combo_Type.FindString(-1, Type);
    m_Combo_Type.SetCurSel(iPos);
    //IBT-Typen
    m_Combo_IBT_Type.ResetContent();
    Type.Format("0 %s", CResString::ex().getStrTblText(AETXT_NO_IBT).GetString());
    m_Combo_IBT_Type.AddString(Type);
    Type.Format("1 %s", CResString::ex().getStrTblText(AETXT_NATIONAL).GetString());
    m_Combo_IBT_Type.AddString(Type);
    Type.Format("2 %s", CResString::ex().getStrTblText(AETXT_REGIONAL).GetString());
    m_Combo_IBT_Type.AddString(Type);
    Type.Format("3 %s", CResString::ex().getStrTblText(AETXT_LOKAL).GetString());
    m_Combo_IBT_Type.AddString(Type);
    Type.Format("%d", m_sIBT_Type);
    iPos = m_Combo_IBT_Type.FindString(-1, Type);
    m_Combo_IBT_Type.SetCurSel(iPos);
    //Sortiment-Typen
    m_Combo_Assortment.ResetContent();
    Type.Format("0 %s", CResString::ex().getStrTblText(AETXT_GENERAL).GetString());
    m_Combo_Assortment.AddString(Type);
    Type.Format("1 %s", CResString::ex().getStrTblText(AETXT_PRIVAT).GetString());
    m_Combo_Assortment.AddString(Type);
    Type.Format("2 %s", CResString::ex().getStrTblText(AETXT_VETERINARY).GetString());
    m_Combo_Assortment.AddString(Type);
    Type.Format("%d", m_sAssorment);
    iPos = m_Combo_Assortment.FindString(-1, Type);
    m_Combo_Assortment.SetCurSel(iPos);

    CString cFolge;
    if (m_bUpdate)
    {
        GetDlgItem(IDC_COMBO_FOLGE)->EnableWindow(FALSE);
        cFolge.Format("%d", m_sFolge);
        m_Combo_Folge.AddString(cFolge);
        m_Combo_Folge.SetCurSel(0);
    }
    else
    {
        bool bnotfound;
        int ende = m_pListCtl->GetItemCount();
        for (int i = 1; i < 100; i++)
        {
            bnotfound = true;
            for (int pos = 0; pos < ende; pos++)
            {
                if (i == atoi(m_pListCtl->GetItemText(pos, COL_VBFIL_FOLGE)))
                {
                    bnotfound = false;
                    break;
                }
            }
            if (bnotfound)
            {
                cFolge.Format("%d", i);
                m_Combo_Folge.AddString(cFolge);
            }
        }
        m_Combo_Folge.SetCurSel(0);
    }
    UpdateData(FALSE);
    return TRUE;
}

void CDIbtBranchesUpd::OnEnChangeEditVbFiliale()
{
    AllgWertKontr(&m_edit_vbfil,MAXIMUM_FILIALNR);
}

void CDIbtBranchesUpd::OnEnChangeEditBga()
{
    AllgWertKontr(&m_edit_BGA,MAXIMUM_IDF);
}

void CDIbtBranchesUpd::OnOK()
{
    UpdateData();
    if (m_cVBFil.IsEmpty())
    {
        MsgBoxOK(AETXT_SET_IBTBRANCH);
        m_edit_vbfil.SetFocus();
        m_edit_vbfil.SetSel(0, -1, FALSE);
        return;
    }
    if (!m_cBGA.IsEmpty())
    {
        CCHECKCUSTOMEREXIST checkexist;
        checkexist.SetVertriebszentrumnr((short)atoi(m_cVBFil));
        checkexist.SetKundennr(atol(m_cBGA));
        if (checkexist.SelExist())
        {
            MsgBoxOK(AETXT_EVENTREASON_23);
            m_edit_BGA.SetFocus();
            m_edit_BGA.SetSel(0, -1, FALSE);
            return;
        }
    }
    CString cFolge;
    m_Combo_Folge.GetLBText(m_Combo_Folge.GetCurSel(), cFolge);
    m_sFolge = (short)atoi(cFolge);
    CString cType;
    m_Combo_Type.GetLBText(m_Combo_Type.GetCurSel(), cType);
    m_sType = (short)atoi(cType);
    CString cIBT_Type;
    m_Combo_IBT_Type.GetLBText(m_Combo_IBT_Type.GetCurSel(), cIBT_Type);
    m_sIBT_Type = (short)atoi(cIBT_Type);
    CString cAssorment;
    m_Combo_Assortment.GetLBText(m_Combo_Assortment.GetCurSel(), cAssorment);
    m_sAssorment = (short)atoi(cAssorment);
    CDialogMultiLang::OnOK();
}
