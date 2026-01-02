// DPromotionen.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artsel.h>
#include <artikel.h>
#include <promo.h>
#include "DPromotionen.h"

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES Promo[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  40, LVCFMT_LEFT,
    2,  "", 150, LVCFMT_LEFT,
    3,  "",  70, LVCFMT_LEFT,
    4,  "",  70, LVCFMT_LEFT,
    5,  "",   0, LVCFMT_LEFT,
    6,  "",   0, LVCFMT_LEFT,
    7,  "",   0, LVCFMT_LEFT,
    8,  "",  65, LVCFMT_RIGHT,
    9,  "",  65, LVCFMT_RIGHT,
    10, "",   0, LVCFMT_LEFT,
    11, "",   0, LVCFMT_LEFT,
    12, "",   0, LVCFMT_LEFT,
    13, "",   0, LVCFMT_LEFT,
    14, "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};
#define NUM_PROMO 15

static COLUMNS_TYPES Members[] =
{
    0,  "", 150, LVCFMT_LEFT,
    1,  "",  60, LVCFMT_RIGHT,
    2,  "",  60, LVCFMT_RIGHT,
    3,  "",   0, LVCFMT_RIGHT,
    4,  "",   0, LVCFMT_RIGHT,
    5,  "",   0, LVCFMT_RIGHT,
    6,  "",   0, LVCFMT_RIGHT,
    7,  "",   0, LVCFMT_RIGHT,
    -1, "",   0, 0
};
#define NUM_MEMBERS 8

static COLUMNS_TYPES Rabatt[] =
{
    0,  "", 250, LVCFMT_LEFT,
    1,  "",  60, LVCFMT_RIGHT,
    2,  "",   0, LVCFMT_RIGHT,
    3,  "",   0, LVCFMT_RIGHT,
    4,  "",   0, LVCFMT_RIGHT,
    -1, "",   0, 0
};
#define NUM_RABATT 5


// CDPromotionen-Dialogfeld

IMPLEMENT_DYNAMIC(CDPromotionen, CDialog)
CDPromotionen::CDPromotionen(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPromotionen::IDD, pParent), CPageBrowser(0)
    , m_csSuch(_T(""))
{
    m_lKundennr = 0;
    m_sVznr = 0;
    m_sPromoNo = 0;
    m_ptrDoc = NULL;
    m_lMinMeng = 0;
    m_dMinValue = 0.0;
    m_cEKG = _T("");
    m_lDISCGRP = 0;
}

CDPromotionen::~CDPromotionen()
{
}

void CDPromotionen::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_LIST2, m_List2);
    DDX_Control(pDX, IDC_LIST3, m_List3);
    DDX_Text(pDX, IDC_EDIT_SUCH, m_csSuch);
}


BEGIN_MESSAGE_MAP(CDPromotionen, CDialogMultiLang)
    ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, OnSelChangeList1)
    ON_BN_CLICKED(IDC_BUTTON_SUCHE, OnBnClickedButtonSuche)
END_MESSAGE_MAP()


// CDPromotionen-Meldungshandler

BOOL CDPromotionen::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    // Liste Promotionen
    Promo[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Promo[1].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
    Promo[2].Columns = CResString::ex().getStrTblText(AETXT_PROMOTION);
    Promo[3].Columns = CResString::ex().getStrTblText(AETXT_VON);
    Promo[4].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    Promo[8].Columns = CResString::ex().getStrTblText(AETXT_MIN_MENGE);
    Promo[9].Columns = CResString::ex().getStrTblText(AETXT_MIN_VALUE);

    DWORD dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_List1.SetExtendedStyle(dwOldBits);

    m_List1.ModifyStyle(0,LVS_SHOWSELALWAYS);

    if (!CListCtrlHelper::AddColumns(Promo, m_List1))
    {
        return FALSE;
    }

    // Liste Mitglieder der Promotion
    Members[0].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Members[1].Columns = CResString::ex().getStrTblText(AETXT_RABATT);
    Members[2].Columns = CResString::ex().getStrTblText(AETXT_MIN_MENGE);

    if (!CListCtrlHelper::AddColumns(Members, m_List2))
    {
        return FALSE;
    }

    // Liste Rabatte der Promotion
    Rabatt[0].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Rabatt[1].Columns = CResString::ex().getStrTblText(AETXT_MENGE);

    if (!CListCtrlHelper::AddColumns(Rabatt, m_List3))
    {
        return FALSE;
    }
    //CenterWindow((AeGetApp()->m_pViewEing->GetSafeHwnd()));
    CenterWindow((AeGetApp()->m_pViewEing));

    CStringArray s;
    s.SetSize(NUM_PROMO);
    CPROMOTIONEN CPromo;
    CPromo.SetBranchno(m_sVznr);
    CPromo.SetCustomerno(m_lKundennr);
    m_List1.DeleteAllItems();
    ppString name;
    ppString ekg;
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_sPromoNo > 0) //wurde aus F2 versorgt
        {
            CPromo.SetPromotion_no(m_sPromoNo);
            CPromo.SetBaseqty(m_lMinMeng);
            CPromo.SetBase_value(m_dMinValue);
            CPromo.SetPharmacygroupid(m_cEKG);
            CPromo.SetCustomerno(m_lCustomerno);
            CPromo.SetDiscountgrpno(m_lDISCGRP);
            if (CPromo.SelPromoNo() != 0)
            {
                break;
            }
        }
        else if (CPromo.SelList() != SRV_OK)
        {
            break;
        }
        if ((CPromo.GetDiscountspec() == 9) && !AeGetApp()->IsKndKasse())
        {
            continue;
        }
        s[0] = kb.Next();
        s[1].Format("%d", CPromo.GetPromotion_no());
        CPromo.GetName(name);
        s[2] = name;
        s[3] = DDMMYYYYStringFromDateLong(CPromo.GetDatefrom());
        s[4] = DDMMYYYYStringFromDateLong(CPromo.GetDateto());
        s[5].Format("%d", CPromo.GetDiscountqty());
        s[6].Format("%d", CPromo.GetDiscountarticle());
        s[7].Format("%d", CPromo.GetDiscountspec());
        s[8].Format("%d", CPromo.GetBaseqty());
        s[9].Format("%0.2lf", CPromo.GetBase_value());
        s[10].Format("%d", CPromo.GetDiscountgrpno());
        CPromo.GetPharmacygroupid(ekg);
        s[11] = ekg;
        s[12].Format("%0.2lf", CPromo.GetDiscountvaluepct());
        s[13].Format("%d", CPromo.GetManufacturerno());
        s[14].Format("%c", CPromo.GetAddondiscountok());

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_PROMO, s))
        {
            return TRUE;
        }
        if (m_sPromoNo > 0)
        {
            break;
        }
    }
    if (m_List1.GetItemCount() == 0)
    {
        CString CStr;
        CStr.Format("%s %s", CResString::ex().getStrTblText(AETXT_KEINE).GetString(),
                             CResString::ex().getStrTblText(AETXT_PROMOTION).GetString());
        MsgBoxOK(CStr);
        EndWaitCursor();
        CDialogMultiLang::OnCancel();
        return TRUE;
    }

    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);
    GetMembers(0);
    GetRabs(0);
    EndWaitCursor();
    if (m_sPromoNo > 0) //wurde aus F2 versorgt
    {
        OnOK();
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDPromotionen::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_EDIT_SUCH))
    {
        OnBnClickedButtonSuche();
        return;
    }
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    m_buch.m_pFather = this;
    SetzeWerte(pos);
    if (m_sPromoNo > 0)  //wurde aus F2 versorgt
    {
        if (m_buch.DoModal() == IDOK)
        {
            CDialogMultiLang::OnOK();
            return;
        }
        else
        {
            CDialogMultiLang::OnCancel();
            return;
        }
    }
    else
    {
        AUFPOSBUCH *ptrPos;
        if (m_ptrDoc != NULL)
        {
            ptrPos = m_ptrDoc->GetPosListe();   //Zeiger auf Beginn der Liste
            int found = 0;
            for (int i = 0;; i++)
            {
                ptrPos = m_ptrDoc->GetListPosition(i);
                if (ptrPos == NULL)
                    break;
                if (ptrPos->PROMOTYP == 1 && ptrPos->PROMOTION_NO == m_buch.m_sPromono)
                {
                    if (MsgBoxYesNo(AETXT_CUMULATE_PROMOTION) == IDNO)
                    {
                        found = 1;
                        break;
                    }
                    found = 1;
                    m_buch.DoModal();
                    break;
                }
            }
            if (!found)
            {
                m_buch.m_ptrDoc = NULL;
                m_buch.DoModal();
            }
        }
        else
        {
            m_buch.m_ptrDoc = NULL;
            m_buch.DoModal();
        }
    }
}

void CDPromotionen::GetMembers(int pos)
{
    CStringArray s;
    s.SetSize(NUM_MEMBERS);
    m_List2.DeleteAllItems();
    CPROMOMEMBERS CMember;
    CPROMOMANUFACT Manufact;
    ppString name;
    CMember.SetBranchno(m_sVznr);
    CMember.SetDiscountgrpno(atol(m_List1.GetItemText(pos, 10)));
    BeginWaitCursor();
    for (;;)
    {
        Manufact.SetBranchno(m_sVznr);
        Manufact.SetPromotion_no(static_cast<short>(atoi(m_List1.GetItemText(pos, 10))));
        if (!Manufact.SelManuNo())
        {
            CString manuno;
            manuno.Format("%d", Manufact.GetManufacturerno());
            m_List1.SetItemText(pos, 13, manuno);   //Hersteller-Promotion
            name = CResString::ex().getStrTblText(AETXT_HERSTELLER_PROMO);
            s[0] = name;
            s[1].Empty();
            s[2].Empty();
            s[3].Empty();
            s[4].Empty();
            s[5].Empty();
            s[6].Empty();
        }
        else if (CMember.SelList() != SRV_OK)
            break;
        else
        {
            CMember.GetArtikel_langname(name);
            s[0] = name;
            s[1].Format("%0.2lf", CMember.GetDiscountvaluepct());
            s[2].Format("%d", CMember.GetBaseqty());
            s[3].Format("%d", CMember.GetArtikel_nr());
            s[4].Format("%d", CMember.GetMaxqty());
            s[5].Format("%d", CMember.GetDiscountqty());
            s[6] = CMember.GetNo_multiple_qty();
            CString test;
            test.Format("%02d.%02d", CMember.GetDatumverfall() % 100, CMember.GetDatumverfall() / 100);
            s[7].Format("%02d.%02d", CMember.GetDatumverfall() % 100, CMember.GetDatumverfall() / 100);
        }
        if (!CListCtrlHelper::AppendItem(m_List2, NUM_MEMBERS, s))
        {
            return;
        }
        if (atol(m_List1.GetItemText(pos, 13)) > 0)     //Hersteller-Promotion
        {
            break;
        }
    }
    EndWaitCursor();
}

void CDPromotionen::GetRabs(int pos)
{
    CStringArray s;
    CARTINF artinf;
    s.SetSize(NUM_RABATT);
    m_List3.DeleteAllItems();
    artinf.s.ARTIKEL_NR = atol(m_List1.GetItemText(pos, 6));
    if (artinf.s.ARTIKEL_NR == 0)
        return;
    artinf.s.FILIALNR = AeGetApp()->VzNr();
    BeginWaitCursor();
    artinf.Server(AatartInf_art_nr);
    if (artinf.rc < SRV_OK)
    {
        EndWaitCursor();
        return;
    }
    s[0] = artinf.s.ARTIKEL_LANGNAME;
    s[1] = m_List1.GetItemText(pos, 5);
    s[2] = m_List1.GetItemText(pos, 6);
    s[3].Format("%1s", artinf.s.STELLER);

    if (!CListCtrlHelper::AppendItem(m_List3, NUM_RABATT, s))
    {
        EndWaitCursor();
        return;
    }
    if (artinf.s.STELLER[0] == 'S')
    {
        CSTELLERTYP typ;
        typ.SetArticle_no_pack(atol(m_List1.GetItemText(pos, 6)));
        if (typ.SelTyp())
        {
            EndWaitCursor();
            return;
        }
        if (typ.GetCompack_type() != 3 && typ.GetCompack_type() != 4)
        {
            EndWaitCursor();
            return;
        }
        CString steltyp;
        steltyp.Format("%d", typ.GetCompack_type());
        m_List3.SetItemText(0, 4, steltyp);
        ppString name;
        CSTELLER stell;
        stell.SetArticle_no_pack(atol(m_List1.GetItemText(pos, 6)));
        stell.SetFilialnr(m_sVznr);
        for (;;)
        {
            if (stell.SelList() != SRV_OK) break;
            stell.GetArtikel_langname(name);
            s[0] = name;
            s[4].Format("%d", typ.GetCompack_type());
            if (typ.GetCompack_type() == 3)
            {
                s[1].Format("%d", stell.GetQuantity());
            }
            else
            {
                s[1] = "0";
            }
            s[2].Format("%d", stell.GetArticle_no_element());

            if (!CListCtrlHelper::AppendItem(m_List3, NUM_RABATT, s))
            {
                EndWaitCursor();
                return;
            }
        }
    }
    EndWaitCursor();
}

void CDPromotionen::OnDblclkList1()
{
    OnOK();
}

//void CDPromotionen::OnSelChangeList1()
void CDPromotionen::OnSelChangeList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        GetMembers(pos);
        GetRabs(pos);
    }
    *pResult = 0L;
}

void CDPromotionen::OnKeydownList1(NMHDR* pNMHDR, LRESULT *pResult)
{
    int pos;
    OnKeydownList(pNMHDR, pResult, m_List1, pos, true, false);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (pLVKeyDow->wVKey == VK_UP)
    {
        if (pos >= 0)
        {
            --pos;
            if (pos < 0) pos = 0;
            GetMembers(pos);
            GetRabs(pos);
        }
        return;                                     //Message wird weitergeleitet
    }
    if (pLVKeyDow->wVKey == VK_DOWN)
    {
        if (pos >= 0)
        {
            CListCtrlHelper::StepDownLinePosition(pos, m_List1.GetItemCount());
            GetMembers(pos);
            GetRabs(pos);
        }
        return;                                     //Message wird weitergeleitet
    }
    if (CLetterMan::InRange(pLVKeyDow->wVKey, m_List1.GetItemCount()))
    {
        GetMembers(pos);
        GetRabs(pos);
    }
}

void CDPromotionen::OnBnClickedButtonSuche()
{
    UpdateData();
    bool found = false;
    int len = m_csSuch.GetLength();
    for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
    {
        CString vergl = m_List1.GetItemText(pos, 2);
        if (!strncmp(vergl, m_csSuch, len))
        {
            found = true;
            HandleSearchResult(pos);
            break;
        }
    }
    if (!found) MsgBoxOK(AETXT_NOT_FOUND);
}

void CDPromotionen::SuchePromoNo(int no)
{
    for (int pos = 0; pos < m_List1.GetItemCount(); pos++)
    {
        if (no == atoi(m_List1.GetItemText(pos, 1)))
        {
            HandleSearchResult(pos);
            SetzeWerte(pos);
            break;
        }
    }
}

void CDPromotionen::HandleSearchResult(int pos)
{
    CListCtrlHelper::SetFocusSelectedFocused(m_List1, pos);
    //Zeilenhoehe ermitteln
    CRect itemRect;
    m_List1.GetItemRect(0, itemRect, LVIR_BOUNDS);
    int hoehe = itemRect.Height();
    int rc;
    //zuerst auf Listanfang
    CSize scrollback(0, (m_List1.GetItemCount() * hoehe * (-1)));
    rc = m_List1.Scroll(scrollback);
    //jetzt auf gesuchte Position
    CSize scrollfaktor(0, pos * hoehe);
    rc = m_List1.Scroll(scrollfaktor);
    GetMembers(pos);
    GetRabs(pos);
}

void CDPromotionen::SetzeWerte(int pos)
{
    m_buch.m_cPromotion = m_List1.GetItemText(pos, 2);
    m_buch.m_sSpec = static_cast<short>(atoi(m_List1.GetItemText(pos, 7)));
    m_buch.m_sPromono = static_cast<short>(atoi(m_List1.GetItemText(pos, 1)));
    m_buch.m_cMinMeng = m_List1.GetItemText(pos, 8);
    m_buch.m_cMinValue = m_List1.GetItemText(pos, 9);
    m_buch.m_pListPromo = &m_List1;
    m_buch.m_pListMember = &m_List2;
    m_buch.m_pListRabatte = &m_List3;
    m_buch.m_cDISCGRP = m_List1.GetItemText(pos, 10);
    m_buch.m_cEKG = m_List1.GetItemText(pos, 11);
    m_buch.m_ptrDoc = m_ptrDoc;
    m_buch.m_dPct = atof(m_List1.GetItemText(pos, 12));
    m_buch.m_lManu = atol(m_List1.GetItemText(pos, 13));
    m_buch.m_sVznr = m_sVznr;
    m_buch.m_cAddDisc = m_List1.GetItemText(pos, 14);
}
