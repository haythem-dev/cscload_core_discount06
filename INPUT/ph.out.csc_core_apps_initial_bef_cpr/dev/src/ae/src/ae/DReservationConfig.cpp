// DReservationConfig.cpp : implementation file
//

#include "stdafx.h"
#include "DOrderTypeManager.h"
#include "DReservationConfig.h"
#include <ordertypereservationconfig.h>
#include <ordertypereservationconfigcpg.h>
#include <cscreservationtypes.h>


// CDReservationConfig dialog

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB              0
#define COL_NUMMER          1
#define COL_NEW             2
#define COL_CPG_ID          3
#define NUM_COLUMNS_CONFIG  4

static COLUMNS_TYPES Columns[] =
{
    COL_KB,     "", 35, LVCFMT_LEFT,
    COL_NUMMER, "", 70, LVCFMT_LEFT,
    COL_NEW,    "",  0, LVCFMT_LEFT,
    COL_CPG_ID, "",  0, LVCFMT_LEFT,
    -1,         "",  0, 0
};

IMPLEMENT_DYNAMIC(CDReservationConfig, CDialog)

CDReservationConfig::CDReservationConfig(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(IDD_AE_RESERVATION_CONFIG, pParent)
    , m_cBez(_T(""))
    , m_bOnlyRes(FALSE)
    , m_bFreeFirst(FALSE)
    , m_iConfigID(0)
    , m_sMitEKG(0)
    , m_sPriority(0)
{
    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KB);
    Columns[COL_NUMMER].Columns = CResString::ex().getStrTblText(AETXT_EK_GRP);
    Columns[COL_NEW].Columns = "Neu";
    Columns[COL_CPG_ID].Columns = "ID";
}

CDReservationConfig::~CDReservationConfig()
{
}

void CDReservationConfig::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_BEZ, m_edit_Bez);
    DDX_Text(pDX, IDC_EDIT_BEZ, m_cBez);
    DDX_Control(pDX, IDC_COMBO_RES_TYP, m_combo_ResTyp);
    DDX_Control(pDX, IDC_COMBO_PRIORITY, m_combo_Priority);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Check(pDX, IDC_CHECK_ONLY_RES, m_bOnlyRes);
    DDX_Check(pDX, IDC_CHECK_FREE_FIRST, m_bFreeFirst);
}


BEGIN_MESSAGE_MAP(CDReservationConfig, CDialogMultiLang)
    ON_BN_CLICKED(IDC_CHECK_ONLY_RES, &CDReservationConfig::OnBnClickedCheckOnlyRes)
    ON_BN_CLICKED(IDC_BUTTON_PLUS, &CDReservationConfig::OnBnClickedButtonPlus)
    ON_BN_CLICKED(IDC_BUTTON_MINUS, &CDReservationConfig::OnBnClickedButtonMinus)
    ON_EN_CHANGE(IDC_EDIT_BEZ, &CDReservationConfig::OnEnChangeEditBez)
    ON_CBN_SELCHANGE(IDC_COMBO_RES_TYP, &CDReservationConfig::OnCbnSelchangeComboResTyp)
END_MESSAGE_MAP()


// CDReservationConfig message handlers


BOOL CDReservationConfig::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    int rc = 0;
    char error_msg[81];

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_EKG)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_EKG)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
    GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);

    if (m_iConfigID > 0)
    {
        //Lesen vorhandenen Satz
        ppString name;
        CCSCRESERVATIONTYPES restyp;
        CString Ausgabe;
        restyp.SetCscreservationtype(m_iReserveType);
        rc = ::ServerNr(PIPE_AE_SRV, AasrvGetCSCReservationTypeByTyp, (void *)&restyp.s, CSCRESERVATIONTYPES_BES, CSCRESERVATIONTYPES_ANZ, error_msg);
        if (rc != 0) return FALSE;
        Ausgabe.Format("%d %s %d", restyp.GetCscreservationtype(), restyp.GetCscreservationtypename(name), restyp.GetWithpharmacygroup());
        m_combo_ResTyp.AddString(Ausgabe);
        if ((m_sMitEKG = restyp.GetWithpharmacygroup()) == 1)
        {
            GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_EKG)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_EKG)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_LIST1)->EnableWindow(TRUE);
            GetDlgItem(IDC_LIST1)->ShowWindow(SW_SHOW);
        }
        m_combo_Priority.SetCurSel(m_sPriority - 1);
    }
    else
    {
        ppString name;
        CCSCRESERVATIONTYPES restyp;
        CString Ausgabe;
        for (;;)
        {
            //Reservierungstypen
            //Lesen vohandene Typen
            rc = ::ServerNr(PIPE_AE_SRV, AasrvGetCSCReservationTypeList, (void*)&restyp.s, CSCRESERVATIONTYPES_BES, CSCRESERVATIONTYPES_ANZ, error_msg);
            if (rc < 0)
            {
                FehlerBehandlung(rc, error_msg);
                return FALSE;
            }
            if (rc != 0)
                break;
            Ausgabe.Format("%d %s %d", restyp.GetCscreservationtype(), restyp.GetCscreservationtypename(name), restyp.GetWithpharmacygroup());
            m_combo_ResTyp.AddString(Ausgabe);
        }
        m_combo_Priority.SetCurSel(0);
    }
    m_combo_ResTyp.SetCurSel(0);
    CString type;
    m_combo_ResTyp.GetLBText(0, type);
    if (type.Right(1) == "1")   //mit EKG
    {
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_EKG)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_EKG)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_LIST1)->EnableWindow(TRUE);
        GetDlgItem(IDC_LIST1)->ShowWindow(SW_SHOW);
        m_sMitEKG = 1;
        LeseEKG();
    }
    if (m_bOnlyRes)
    {
        GetDlgItem(IDC_CHECK_FREE_FIRST)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_FREE_FIRST)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_CHECK_FREE_FIRST)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_FREE_FIRST)->ShowWindow(SW_SHOW);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDReservationConfig::OnBnClickedCheckOnlyRes()
{
    UpdateData();
    if (m_bOnlyRes)
    {
        m_bFreeFirst = FALSE;
        GetDlgItem(IDC_CHECK_FREE_FIRST)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_FREE_FIRST)->ShowWindow(SW_HIDE);
    }
    else
    {
        GetDlgItem(IDC_CHECK_FREE_FIRST)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_FREE_FIRST)->ShowWindow(SW_SHOW);
    }
}

void CDReservationConfig::OnBnClickedButtonPlus()
{
    CDNewEKG newekg;
    CStringArray s;
    s.SetSize(NUM_COLUMNS_CONFIG);
    newekg.m_pListCtl = &m_ListCtl;
    if (newekg.DoModal() == IDOK)
    {
        CLetterMan kb;
        int index = m_ListCtl.GetItemCount() -1;
        if (index < 0)
        {
            kb.Next();
        }
        else
        {
            kb.SetSeed(m_ListCtl.GetItemText(index, COL_KB).GetAt(0));
        }
        s[COL_KB] = kb.Current();
        s[COL_NUMMER] = newekg.m_cEKG;
        s[COL_NEW] = "1";
        s[COL_CPG_ID] = "0";

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS_CONFIG, s))
        {
            EndWaitCursor();
        }
    }
}

void CDReservationConfig::OnBnClickedButtonMinus()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            if (atoi(m_ListCtl.GetItemText(pos, COL_NEW)) == 0)
            {
                CORDERTYPERESERVATIONCONFIGCPG cpg;
                cpg.SetOrdertypereservationconfig_id(m_iConfigID);
                cpg.SetId(atoi(m_ListCtl.GetItemText(pos, COL_CPG_ID)));
                char error_msg[81];
                int rc = ::ServerNr(PIPE_AE_SRV, AasrvDeleteReservationConfigcpg, (void *)&cpg.s, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ, error_msg);
                if (rc < 0)
                {
                    FehlerBehandlung(rc, error_msg);
                    return;
                }
            }
            m_ListCtl.DeleteItem(pos);
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}


void CDReservationConfig::OnEnChangeEditBez()
{
    AllgLaengeKontr(&m_edit_Bez, L_ORDERTYPERESERVATIONCONFIG_ORDERTYPERESERVATIONCONFIGNAME, AeGetApp()->Modus());
}


void CDReservationConfig::OnOK()
{
    UpdateData();
    CORDERTYPERESERVATIONCONFIG config;
    int type;
    int len;
    int rc = 0;
    char error_msg[81];
    CString restyp;
    config.SetCscordertype(m_cAArt);
    if (m_cBez.IsEmpty())
    {
        MsgBoxOK(AETXT_NEW_BEZEICHNUNG);
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_BEZ));
        return;
    }
    int pos = m_combo_ResTyp.GetCurSel();
    if (pos < 0)
    {
        MsgBoxOK(AETXT_NO_TYPE);
        GotoDlgCtrl(GetDlgItem(IDC_COMBO_RES_TYP));
        return;
    }
    m_combo_ResTyp.GetLBText(pos, restyp);
    len = restyp.Find(' ', 0);
    type = atoi(restyp.Left(len));
    config.SetCscreservationtype(type);
    config.SetPriority((short)m_combo_Priority.GetCurSel()+1);
    m_sPriority = config.GetPriority();
    config.SetOrdertypereservationconfigname(m_cBez);
    //Check auf bereits vorhandene Kombi
    //Lese config

    if (m_bOnlyRes)
    {
        config.SetReservedstockonly(1);
    }
    else
    {
        config.SetReservedstockonly(0);
        if (m_bFreeFirst)
        {
            config.SetFreestockhaspriority(1);
        }
        else
        {
            config.SetFreestockhaspriority(0);
        }
    }
    if (m_iConfigID == 0)   //neuer Eintrag
    {

        config.SetId(0);    //serial
        if ((CDOrderTypeManager*)m_pFather->CheckExist(config.GetCscreservationtype(), config.GetPriority()))
        {
            MsgBoxOK(IDS_SATZ_VORH);
            return;
        }
        rc = ::ServerNr(PIPE_AE_SRV, AasrvInsertReservationConfig, (void*)&config.s, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        m_iConfigID = config.GetId();
    }
    else
    {
        config.SetId(m_iConfigID);
        rc = ::ServerNr(PIPE_AE_SRV, AasrvUpdateReservationConfig, (void*)&config.s, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
    }
    if (m_sMitEKG == 1)
    {
        CORDERTYPERESERVATIONCONFIGCPG cpg;
        for (int i = 0; i < m_ListCtl.GetItemCount(); i++)
        {
            if (atoi(m_ListCtl.GetItemText(i, COL_NEW)) == 1)   //nur neue einfügen
            {
                cpg.SetId(0);
                cpg.SetOrdertypereservationconfig_id(m_iConfigID);
                cpg.SetPharmacygroupid(m_ListCtl.GetItemText(i, COL_NUMMER));
                rc = ::ServerNr(PIPE_AE_SRV, AasrvInsertReservationConfigcpg, (void*)&cpg.s, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ, error_msg);
                if (rc < 0)
                {
                    FehlerBehandlung(rc, error_msg);
                    return;
                }
            }
        }
    }

    CDialogMultiLang::OnOK();
}


void CDReservationConfig::LeseEKG()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS_CONFIG);
    ppString nummer;
    int rc = 0;
    char error_msg[81];
    CORDERTYPERESERVATIONCONFIGCPG cpg;
    cpg.SetOrdertypereservationconfig_id(m_iConfigID);
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    for (;;)
    {
        //Einkaufsgruppen
        rc = ::ServerNr(PIPE_AE_SRV, AasrvGetReservationConfigcpgListByConfigID, (void*)&cpg.s, ORDERTYPERESERVATIONCONFIGCPG_BES, ORDERTYPERESERVATIONCONFIGCPG_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        if (rc != 0)
            break;
        s[COL_KB] = kb.Next();
        s[COL_NUMMER] = cpg.GetPharmacygroupid(nummer);
        s[COL_NEW] = "0";
        s[COL_CPG_ID].Format("%d", cpg.GetId());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS_CONFIG, s))
        {
            EndWaitCursor();
            return;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() > 0)
    {
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_HIDE);
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDReservationConfig::OnCbnSelchangeComboResTyp()
{
    int nummer;
    CString restyp;
    nummer = m_combo_ResTyp.GetCurSel();
    m_combo_ResTyp.GetLBText(nummer, restyp);
    if (restyp.Right(1) == "1") //mit EKG
    {
        m_sMitEKG = 1;
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_EKG)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_EKG)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_LIST1)->EnableWindow(TRUE);
        GetDlgItem(IDC_LIST1)->ShowWindow(SW_SHOW);
    }
    else
    {
        m_sMitEKG = 0;
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_EKG)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_EKG)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
    }
}


// CDNewEKG dialog

IMPLEMENT_DYNAMIC(CDNewEKG, CDialog)

CDNewEKG::CDNewEKG(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(IDD_AE_NEW_EKG, pParent)
    , m_cEKG(_T(""))
{
}

CDNewEKG::~CDNewEKG()
{
}

void CDNewEKG::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_EKG, m_edit_EKG);
    DDX_Text(pDX, IDC_EDIT_EKG, m_cEKG);
}


BEGIN_MESSAGE_MAP(CDNewEKG, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_EKG, &CDNewEKG::OnEnChangeEditEkg)
END_MESSAGE_MAP()


// CDNewEKG message handlers


void CDNewEKG::OnEnChangeEditEkg()
{
    AllgLaengeKontr(&m_edit_EKG, L_ORDERTYPERESERVATIONCONFIGCPG_PHARMACYGROUPID, AeGetApp()->Modus());
}


BOOL CDNewEKG::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDNewEKG::OnOK()
{
    UpdateData();
    //Check ob EKG bereits vorhanden
    for (int i = 0; i < m_pListCtl->GetItemCount(); i++)
    {
        if (m_pListCtl->GetItemText(i, COL_NUMMER) == m_cEKG)
        {
            MsgBoxOK(AETXT_VORHANDEN);
            return;
        }
    }

    CDialogMultiLang::OnOK();
}
