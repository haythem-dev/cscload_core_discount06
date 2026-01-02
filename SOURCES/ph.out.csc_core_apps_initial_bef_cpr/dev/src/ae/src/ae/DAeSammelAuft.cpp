//----------------------------------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------------------------------//
#include "stdafx.h"
#include <kndsel.h>
#include "DSammelKnd.h"
#include "DSammelArt.h"
#include "DAeSammelAuft.h"
#include "DSammelAufDef.h"
#include "DAeCollOrderGrp.h"
#include "CustomerGroups.h"
#include <sstream>
#include <iomanip>

//----------------------------------------------------------------------------------------------------//
// Definition der Tabellenbreite und der Ueberschriften
//----------------------------------------------------------------------------------------------------/

#define NUM_COLUMNS     4

COLUMNS_TYPES Columns[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "",  60, LVCFMT_RIGHT,
    2,  "", 140, LVCFMT_LEFT,
    3,  "", 140, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_COLUMNS2     6

static COLUMNS_TYPES Columns2[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "",  50, LVCFMT_RIGHT,
    2,  "",  70, LVCFMT_RIGHT,
    3,  "",  70, LVCFMT_LEFT,
    4,  "", 160, LVCFMT_LEFT,
    5,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

//----------------------------------------------------------------------------------------------------//
// c'tor: CDAeSammelAuft-Dialogfeld
//----------------------------------------------------------------------------------------------------/
IMPLEMENT_DYNAMIC(CDAeSammelAuft, CDialog)
CDAeSammelAuft::CDAeSammelAuft(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeSammelAuft::IDD, pParent), m_curCustGrp( "" )
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ORT);

    Columns2[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns2[1].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns2[2].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns2[3].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns2[4].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns2[5].Columns = CResString::ex().getStrTblText(AETXT_ARTIKEL_NR);

}
//----------------------------------------------------------------------------------------------------//
// d'tor
//----------------------------------------------------------------------------------------------------/
CDAeSammelAuft::~CDAeSammelAuft()
{
}
//----------------------------------------------------------------------------------------------------//
// DoDataExchange(CDataExchange* pDX)
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_LIST2, m_ListCtl2);
    DDX_Control(pDX, IDC_CBO_CUSTGRPS, m_cboCustGrps);
}

//----------------------------------------------------------------------------------------------------//
// message map
//----------------------------------------------------------------------------------------------------/
BEGIN_MESSAGE_MAP(CDAeSammelAuft, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnBnClickedButtonKnd)
    ON_BN_CLICKED(IDC_BUTTON_KND_DEL, OnBnClickedButtonKndDel)
    ON_BN_CLICKED(IDC_BUTTON_ART, OnBnClickedButtonArt)
    ON_BN_CLICKED(IDC_BUTTON_ART_DEL, OnBnClickedButtonArtDel)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnNMDblclkList2)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_ZU, OnBnClickedButtonZu)
    ON_BN_CLICKED(ID_BT_NEW_LOAD, OnBnClickedBtNewLoad)
    ON_BN_CLICKED(ID_BT_NEW_CUSTGRP, OnBnClickedBtNewCustGrp)
    ON_CBN_SELCHANGE( IDC_CBO_CUSTGRPS, OnCbnSelchangeCboCustGrps )
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------------//
// CDAeSammelAuft-Meldungshandler
//----------------------------------------------------------------------------------------------------/
BOOL CDAeSammelAuft::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns List1.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    // mark the whole line of the list ctrl with selecting a row
    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);


    // Add the columns List2.
    if (!CListCtrlHelper::AddColumns(Columns2, m_ListCtl2))
    {
        return FALSE;
    }
    // mark the whole line of the list ctrl with selecting a row
    dwOldBits = m_ListCtl2.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl2.SetExtendedStyle(dwOldBits);

    // loads all dc specific customer groups for collective orders
    showCollOrderGrp( &m_cboCustGrps );

    // switch on/off the right to create customer groups for collective orders
    GetDlgItem( ID_BT_NEW_CUSTGRP )->EnableWindow( GetAeUser().IsAdminCustGrps() );

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
//----------------------------------------------------------------------------------------------------//
// OnBnClickedButtonKnd()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnBnClickedButtonKnd()
{
    CDSammelKnd knd;
    knd.m_pListCtl = &m_ListCtl;
    knd.m_sListCount = NUM_COLUMNS;
    knd.DoModal();
}
//----------------------------------------------------------------------------------------------------//
// OnBnClickedButtonKndDel()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnBnClickedButtonKndDel()
{
    int max;
    int iKb;
    CString cKb;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        iKb = atoi(m_ListCtl.GetItemText(pos, 0));
        m_ListCtl.DeleteItem(pos);
        max = m_ListCtl.GetItemCount();
        for (; pos < max; pos++)
        {
            cKb.Format("%d", iKb);
            m_ListCtl.SetItemText(pos, 0, cKb);
            ++iKb;
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}
//----------------------------------------------------------------------------------------------------//
// OnBnClickedButtonArt()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnBnClickedButtonArt()
{
    CDSammelArt art;
    art.m_pListCtl = &m_ListCtl2;
    art.m_sListCount = NUM_COLUMNS2;
    art.DoModal();
}
//----------------------------------------------------------------------------------------------------//
// OnBnClickedButtonArtDel()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnBnClickedButtonArtDel()
{
    int max;
    int iKb;
    CString cKb;
    int pos = m_ListCtl2.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        iKb = atoi(m_ListCtl2.GetItemText(pos, 0));
        m_ListCtl2.DeleteItem(pos);
        max = m_ListCtl2.GetItemCount();
        for (; pos < max; pos++)
        {
            cKb.Format("%d", iKb);
            m_ListCtl2.SetItemText(pos, 0, cKb);
            ++iKb;
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

//----------------------------------------------------------------------------------------------------//
// OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnNMDblclkList2(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    int max;
    int iKb;
    CString cKb;
    int pos = m_ListCtl2.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDSammelArt art;
        art.m_pListCtl = &m_ListCtl2;
        art.m_sListCount = NUM_COLUMNS2;
        art.m_CMenge = m_ListCtl2.GetItemText(pos, 1);
        art.m_CPZN = m_ListCtl2.GetItemText(pos, 2);
        art.m_CArtNr = m_ListCtl2.GetItemText(pos, 5);
        iKb = atoi( m_ListCtl2.GetItemText(pos, 0) );
        m_ListCtl2.DeleteItem(pos);
        max = m_ListCtl2.GetItemCount();
        for (; pos < max; pos++)
        {
            cKb.Format("%d", iKb);
            m_ListCtl2.SetItemText(pos, 0, cKb);
            ++iKb;
        }
        art.DoModal();
    }
    *pResult = 0L;
}

//----------------------------------------------------------------------------------------------------//
// saveCustGrpbyRigth()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::saveCustGrpbyRigth()
{
    // request if the currently displayed customer group should be saved
    // if it differs from the group read in from the db
    // AND the user has the right for manipulating customer groups
    if (GetAeUser().IsAdminCustGrps())
    {
        collectDisplayedMembers();
        CString str;
        m_cboCustGrps.GetLBText(m_cboCustGrps.GetCurSel(), str);
        if (false == CustomerGroups::Ex()->isSame(CustomerGroups::Ex()->getMembers(str), m_displayedMems))
        {
            if (MsgBoxYesNo(AETXT_CHANGES_SAVE_CUSTGRP) == IDYES)
            {
                // save the newly modified customer group
                ppString ppGrpname = str;
                CustomerGroups::Ex()->setGroupName(ppGrpname);
                CustomerGroups::Ex()->setMembers(m_displayedMems);
                if (!CustomerGroups::Ex()->save())
                {
                    MsgBoxOK(CustomerGroups::Ex()->strError.c_str());
                }
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------//
// OnBnClickedButtonZu()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnBnClickedButtonZu()
{
    saveCustGrpbyRigth();
    m_lOrgStatus = ORD_ZURUECKGEST_DAFUE;
    Erfassen();
}
//----------------------------------------------------------------------------------------------------//
// OnBnClickedOk()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnBnClickedOk()
{
    saveCustGrpbyRigth();
    m_lOrgStatus = ORD_ERFASST;
    Erfassen();
}
//----------------------------------------------------------------------------------------------------//
// Erfassen()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::Erfassen()
{
    CAUFIE tm;
    tm.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    tm.Server(AafilIs_new_order_possi);
    if (!tm.s.ANZ_IE) //RZ hat Erfassung neuer Auftraege gesperrt
    {
        MsgBoxOK(AETXT_NEW_ORDER_NOT_POSS);
        return;
    }

    if ((m_lCountCustomer = m_ListCtl.GetItemCount()) == 0)
    {
        MsgBoxOK(AETXT_NO_CUSTOMER);
        return;
    }
    if ((m_lCountArticle = m_ListCtl2.GetItemCount()) == 0)
    {
        MsgBoxOK(AETXT_NO_ARTICLE);
        return;
    }
    CDSammelAufDef def;
    if (def.DoModal() == IDOK)
    {
        m_CBemerkung = def.m_CBemerkung;
        m_CKoArt = def.m_CKoArt;
        m_CBuArt = def.m_CBuArt;
        m_CAufArt = def.m_CAufArt;
        m_lValuta = def.m_lValuta;
    }
    else
    {
        return;
    }

    for (int pos = 0; pos < m_lCountCustomer; pos++)
    {
        if (!OpenOrder(atol(m_ListCtl.GetItemText(pos, 1))))
            continue;
        for (int pos2 = 0; pos2 < m_lCountArticle; pos2++)
        {
            WritePositions(atol(m_ListCtl2.GetItemText(pos2, 1)),
                           atol(m_ListCtl2.GetItemText(pos2, 5)));
        }
        CloseOrder();
    }

    CDialogMultiLang::OnOK();
}

//----------------------------------------------------------------------------------------------------//
// OpenOrder(long lcustomer)
//----------------------------------------------------------------------------------------------------/
BOOL CDAeSammelAuft::OpenOrder(long lcustomer)
{
    CAUFTRAG auftrag;
    auftrag.s.KUNDENNR = lcustomer;
    auftrag.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    BeginWaitCursor();
    auftrag.Server(AasrvNeworder, PIPE_AE_SRV);
    EndWaitCursor();
    if (auftrag.rc < SRV_OK)
        return FALSE;
    m_lStatus = m_lOrgStatus;
    bool first = TRUE;
    if (!m_CAufArt.IsEmpty())
    {
        strcpy(auftrag.s.KDAUFTRAGART, m_CAufArt);
        strcpy(auftrag.s.KOART, m_CKoArt);
        strcpy(auftrag.s.BUCHART, m_CBuArt);
        auftrag.Server(AasrvChangeorder, PIPE_AE_SRV); //Auftrags- und Buchungsart setzen
        if (auftrag.rc < SRV_OK)
        {
            CAUFTEXTE text;
            m_lStatus = ORD_ZURUECKGEST_DAFUE;
            sprintf(text.s.BEMERKUNGEN,
                CResString::ex().getStrTblText(AETXT_KABAKOMB_NOT),
                m_CAufArt.GetString(),
                m_CKoArt.GetString(),
                m_CBuArt.GetString());
            text.s.BEMERKUNGSART = AUF_TEXT_KOPF,
                text.Server(AasrvInsKopfZlnAuf, PIPE_AE_SRV);
        }
        if (!m_CBemerkung.IsEmpty())
        {
            strcpy(auftrag.s.BEMERKUNGEN, m_CBemerkung);
            auftrag.Server(AasrvChangeOrdBem, PIPE_AE_SRV);   //Bemerkung setzen
        }
        if (m_lValuta > 0)
        {
            auftrag.s.VALUTAMONATE = m_lValuta;
            auftrag.Server(AasrvChangeValuta, PIPE_AE_SRV);
            if (auftrag.rc < SRV_OK)
            {
                CAUFTEXTE text;
                m_lStatus = ORD_ZURUECKGEST_DAFUE;
                if (AeGetApp()->IsRS()
                    || AeGetApp()->IsBG()
                    || AeGetApp()->IsDE())
                {
                    sprintf(text.s.BEMERKUNGEN,
                        CResString::ex().getStrTblText(AETXT_NO_VALUTA_TAGE),
                        m_lValuta);
                }
                else
                {
                    sprintf(text.s.BEMERKUNGEN,
                        CResString::ex().getStrTblText(AETXT_NO_VALUTA),
                        m_lValuta);
                }
                text.s.BEMERKUNGSART = AUF_TEXT_KOPF,
                    text.Server(AasrvInsKopfZlnAuf, PIPE_AE_SRV);
            }
        }
        //Auftragsartbezogene Tour auswaehlen
        CKNDTOUREN kndtouren;
        kndtouren.s.IDFNR = lcustomer;
        kndtouren.s.KUNDENNR = lcustomer;
        kndtouren.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
        strncpy(kndtouren.s.KDAUFTRAGART, m_CAufArt, 2);
        for (;;)
        {
            kndtouren.Server(AasrvGettouren, PIPE_AE_SRV);
            if (kndtouren.rc != SRV_OK)
                break;
            if (first)  //erste gueltige Tour nehmen
            {
                first = FALSE;
                if (kndtouren.s.KZAUTOZUORD[0] == '1')
                {
                    strcpy(auftrag.s.TOURID, kndtouren.s.TOURID);
                    auftrag.Server(AasrvChangeTour, PIPE_AE_SRV);
                }
            }
        }
    }

    return TRUE;
}

//----------------------------------------------------------------------------------------------------//
// CloseOrder()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::CloseOrder()
{
    CAUFTRAG auftrag;
    auftrag.s.STATUS = m_lStatus;
    auftrag.Server(AasrvCloseorder, PIPE_AE_SRV);
    if (auftrag.rc < SRV_OK)
    {
        auftrag.s.STATUS = ORD_ZURUECKGEST_DAFUE;
        auftrag.Server(AasrvCloseorder, PIPE_AE_SRV);
    }
}

//----------------------------------------------------------------------------------------------------//
// WritePositions(long lmenge, long larticleno)
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::WritePositions(long lmenge, long larticleno)
{
    CAUFPOSBUCH aufposbuch;

    //Versorgung Übergabestruktur
    aufposbuch.s.MENGENATRA        = 0;
    aufposbuch.s.MENGEBESTELLT     = lmenge;
    aufposbuch.s.MENGEBESTAETIGT   = lmenge;
    aufposbuch.s.ARTIKEL_NR        = larticleno;
    aufposbuch.s.STATUS            = ITEM_STAT_NORMAL;
    aufposbuch.s.BEMERKUNG[0] = '\0';

    //Buchungsversuch
    aufposbuch.Server(AasrvWritepos, PIPE_AE_SRV);
}

//----------------------------------------------------------------------------------------------------//
// collectDisplayedMembers()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::collectDisplayedMembers()
{
    m_displayedMems.clear();
    const int cnt = m_ListCtl.GetItemCount();
    for (int i = 0; i < cnt; ++i)
    {
        m_displayedMems.push_back(atol(m_ListCtl.GetItemText(i, 1)));
    }
}

//----------------------------------------------------------------------------------------------------//
// showCollOrderGrp( CComboBox* pCbo )
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::showCollOrderGrp( CComboBox* pCbo, bool newLoad )
{
    assert(0 != pCbo);

    BeginWaitCursor();
    if (CustomerGroups::Ex()->load(newLoad))
    {
        pCbo->ResetContent();
        CString str = "[" + CResString::ex().getStrTblText(AETXT_BITTE_AUSWAEHLEN) + "]";

        pCbo->AddString(str);
        CustomerGroups::T_GROUPS::iterator it = CustomerGroups::Ex()->begin();
        int idx;
        for (; it != CustomerGroups::Ex()->end(); ++it)
        {
            idx = pCbo->AddString(it->COLLORDERGRPNAME);
            pCbo->SetItemData(idx, it->COLLORDERGRPID);
        }
        pCbo->SetCurSel(0);
    }
    EndWaitCursor();
}

//----------------------------------------------------------------------------------------------------//
// OnBnClickedBtNewLoad()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnBnClickedBtNewLoad()
{
    // buffer the currently selected customer group to display this group after loading newly
    m_cboCustGrps.GetWindowText(m_curCustGrp);

    m_ListCtl.DeleteAllItems();
    showCollOrderGrp(&m_cboCustGrps, true);

    // display the last selected customer group
    const CString str = "[" + CResString::ex().getStrTblText(AETXT_BITTE_AUSWAEHLEN) + "]";
    if (str == m_curCustGrp)
    {
        m_cboCustGrps.SetCurSel(0);
    }
    else
    {
        m_cboCustGrps.SelectString(0, m_curCustGrp);
        OnCbnSelchangeCboCustGrps();
    }
}

//----------------------------------------------------------------------------------------------------//
// OnBnClickedBtNewCustGrp()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnBnClickedBtNewCustGrp()
{
    CDAeCollOrderGrp collOrdGrp;
    collOrdGrp.m_pCDAeSammelAuft = this;
    collOrdGrp.m_idx = m_cboCustGrps.GetCurSel();
    collOrdGrp.DoModal();
    OnBnClickedBtNewLoad();
}

//----------------------------------------------------------------------------------------------------//
// OnCbnSelchangeCombo_KundenGruppe()
//----------------------------------------------------------------------------------------------------/
void CDAeSammelAuft::OnCbnSelchangeCboCustGrps()
{
    m_ListCtl.DeleteAllItems();
    m_cboCustGrps.GetWindowText(m_curCustGrp);
    const CString cstr = "[" + CResString::ex().getStrTblText(AETXT_BITTE_AUSWAEHLEN) + "]";
    if (cstr == m_curCustGrp)
    {
        // if the first entry representing no real customer group is selected,
        // no customer group members have to be displayed.
        return;
    }

    int iKb = 1;
    ppString str;
    const int idx   = m_cboCustGrps.GetCurSel();
    const int grpID = m_cboCustGrps.GetItemData(idx);

    CustomerGroups::Ex()->getMembers(grpID);
    if (CustomerGroups::Ex()->getMembers(grpID).empty())
        return;
    CustomerGroups::T_MEMBERS::iterator it = CustomerGroups::Ex()->getMembers(grpID).begin();
    for (int i = 0; it != CustomerGroups::Ex()->getMembers(grpID).end(); ++it, ++i, ++iKb)
    {
        str.format("%d", iKb);
        m_ListCtl.InsertItem(i, str.c_str());
        str.format("%ld", it->IDFNR);
        m_ListCtl.SetItemText(i, 1, str.c_str());
        m_ListCtl.SetItemText(i, 2, it->NAMEAPO);
        m_ListCtl.SetItemText(i, 3, it->ORT);
    }
}