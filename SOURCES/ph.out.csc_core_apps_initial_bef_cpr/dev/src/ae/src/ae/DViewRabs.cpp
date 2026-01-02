// DViewRabs.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "AeFView.h"
#include <artikel.h>
#include <artsel.h>
#include "DViewRabs.h"

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES Rabatte[] =
{
    COL_PROMOLIST_MENGE,       "",  45, LVCFMT_CENTER,
    COL_PROMOLIST_RABATT,      "",  45, LVCFMT_RIGHT,
    COL_PROMOLIST_WERT,        "",  35, LVCFMT_RIGHT,
    COL_PROMOLIST_ART,         "",  60, LVCFMT_LEFT,
    COL_PROMOLIST_ZZ,          "",   0, LVCFMT_RIGHT,
    COL_PROMOLIST_VON,         "",  70, LVCFMT_LEFT,
    COL_PROMOLIST_BIS,         "",  70, LVCFMT_LEFT,
    COL_PROMOLIST_PROMOTION,   "", 130, LVCFMT_LEFT,
    COL_PROMOLIST_PROMOTYP,    "",  60, LVCFMT_LEFT,
    COL_PROMOLIST_PROMONO,     "",  50, LVCFMT_RIGHT,
    COL_PROMOLIST_QUOTA,       "",   0, LVCFMT_RIGHT,
    COL_PROMOLIST_MIN,         "",   0, LVCFMT_LEFT,
    COL_PROMOLIST_REST,        "",   0, LVCFMT_LEFT,
    COL_PROMOLIST_PZN,         "",   0, LVCFMT_RIGHT,
    COL_PROMOLIST_EINHEIT,     "",   0, LVCFMT_LEFT,
    COL_PROMOLIST_ARTIKELNAME, "",   0, LVCFMT_LEFT,
    -1,                        "",   0, 0
};

// CDViewRabs-Dialogfeld

CDViewRabs::CDViewRabs(CView* pView)
{
    m_pView = pView;
}

IMPLEMENT_DYNAMIC(CDViewRabs, CDialog)
CDViewRabs::CDViewRabs(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDViewRabs::IDD, pParent)
{
    m_sFilialnr = 0;
    m_ArtikelNr = 0;
    m_lKndNr = 0;
    m_iFound = 0;
    m_iBasis = 0;
}

CDViewRabs::~CDViewRabs()
{
}

void CDViewRabs::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDViewRabs, CDialogMultiLang)
END_MESSAGE_MAP()


// CDViewRabs-Meldungshandler

BOOL CDViewRabs::Create()
{
    return CDialogMultiLang::Create(CDViewRabs::IDD);
}

BOOL CDViewRabs::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    Rabatte[COL_PROMOLIST_MENGE].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Rabatte[COL_PROMOLIST_RABATT].Columns = CResString::ex().getStrTblText(AETXT_RABATT);
    Rabatte[COL_PROMOLIST_WERT].Columns = CResString::ex().getStrTblText(AETXT_WERT);
    Rabatte[COL_PROMOLIST_ART].Columns = CResString::ex().getStrTblText(AETXT_ART);
    Rabatte[COL_PROMOLIST_ZZ].Columns = CResString::ex().getStrTblText(AETXT_ZZ);
    Rabatte[COL_PROMOLIST_VON].Columns = CResString::ex().getStrTblText(AETXT_VON);
    Rabatte[COL_PROMOLIST_BIS].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    Rabatte[COL_PROMOLIST_PROMOTION].Columns = CResString::ex().getStrTblText(AETXT_PROMOTION);
    Rabatte[COL_PROMOLIST_PROMOTYP].Columns = CResString::ex().getStrTblText(AETXT_PROMO_TYP);
    Rabatte[COL_PROMOLIST_PROMONO].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
    Rabatte[COL_PROMOLIST_QUOTA].Columns = CResString::ex().getStrTblText(AETXT_PROMO_QTY);
    Rabatte[COL_PROMOLIST_MIN].Columns = CResString::ex().getStrTblText(AETXT_MIN_QTY);
    Rabatte[COL_PROMOLIST_REST].Columns = CResString::ex().getStrTblText(AETXT_REST);
    Rabatte[COL_PROMOLIST_PZN].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Rabatte[COL_PROMOLIST_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Rabatte[COL_PROMOLIST_ARTIKELNAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);

    COLORREF cr = RGB(250,0,0);
    m_List1.SetBkColor(cr);
    m_List1.SetTextBkColor(cr);

    if (!CListCtrlHelper::AddColumns(Rabatte, m_List1))
    {
        return FALSE;
    }
    GetRabs(0);
    GetPage();
    RepositionWindow();

    return FALSE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDViewRabs::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDViewRabs::OnCancel()
{
}

void CDViewRabs::GetRabs(long qty)
{
    char error_msg[81];
    ::buf_default((void *)&m_Discount.s, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
    m_Discount.SetBranchno(m_sFilialnr);
    m_Discount.SetArticleno(m_ArtikelNr);
    m_Discount.SetCustomerno(m_lKndNr);
    m_Discount.SetPreis_typ(m_sPreistyp);
    if (qty == 0)
        qty = 1;
    m_Discount.SetBaseqty(qty);
    int rc = 0;
    m_iFound = 0;
    m_iBasis = 0;

    ((CAeFView*)AeGetApp()->m_pViewEing)->m_dCstDiscount = 0.0;

    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvGetRebates, (void*)&m_Discount.s, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ, error_msg);
        if (rc != 0)
            break;

        if (m_Discount.s.DISCOUNTQTY != 0) continue;
        if (m_Discount.GetPromotion_no() > 0) continue;
        if (m_Discount.s.DISCOUNTVALUEPCT > 0)
        {
            if (((CAeFView*)AeGetApp()->m_pViewEing)->m_dCstDiscount < m_Discount.s.DISCOUNTVALUEPCT)
            {
                ((CAeFView*)AeGetApp()->m_pViewEing)->m_dCstDiscount = m_Discount.s.DISCOUNTVALUEPCT;
            }
            m_iFound = 1;
        }
    }
}

void CDViewRabs::GetPage()
{
    if (AeGetApp()->IsNoPromo())
        return;
    if (AeGetApp()->IsAuftNoPromo())
        return;

    char error_msg[81];
    ::buf_default((void*)&m_Discount.s, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ);
    m_Discount.SetBranchno(m_sFilialnr);
    m_Discount.SetArticleno(m_ArtikelNr);
    m_Discount.SetCustomerno(m_lKndNr);
    m_Discount.SetPreis_typ(m_sPreistyp);
    int rc = 0;
    m_iFound = 0;
    m_iBasis = 0;
    m_List1.DeleteAllItems();
    m_pldisc.clear();

    CPROMOANZ promo;
    ppString PromoName;
    spromolist liste;
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvGetPromotions, (void*)&m_Discount.s, DISCOUNTANZ_BES, DISCOUNTANZ_ANZ, error_msg);
        if (rc != 0) break;
        m_iFound++;
        liste.anz = m_Discount.GetStruct();
        promo.SetPromotion_no(m_Discount.GetPromotion_no());
        if (!promo.SelPromo())
        {
            strcpy(liste.promoname, promo.GetName(PromoName));
            liste.promotyp = promo.GetPromotion_type();
        }
        else
        {
            liste.promoname[0] = '\0';
            liste.promotyp = 0;
        }

        m_pldisc.insert(m_pldisc.end(), liste);
    }
    if (m_iFound == 0)
    {
        this->ShowWindow(SW_HIDE);
        return;
    }
    else
    {
        this->ShowWindow(SW_SHOW);
    }
    m_List1.DeleteAllItems();
    for (m_itdisc = m_pldisc.begin();m_itdisc < m_pldisc.end();m_itdisc++)
    {
        if (m_itdisc->anz.FIXEDPRICE > 0 && m_itdisc->anz.DISCOUNTVALUEPCT == 0) continue;
        if (m_itdisc->anz.CUSTOMERNO != 0 &&
            m_lKndNr != -1 &&
            m_itdisc->anz.CUSTOMERNO != m_lKndNr) continue;
        if (m_itdisc->promotyp == 3)
            FillListBox();
    }
    for (m_itdisc = m_pldisc.begin();m_itdisc < m_pldisc.end();m_itdisc++)
    {
        if (m_itdisc->anz.FIXEDPRICE > 0 && m_itdisc->anz.DISCOUNTVALUEPCT == 0) continue;
        if (m_itdisc->anz.CUSTOMERNO != 0 &&
            m_lKndNr != -1 &&
            m_itdisc->anz.CUSTOMERNO != m_lKndNr) continue;
        if (m_itdisc->promotyp == 2)
            FillListBox();
    }
}

void CDViewRabs::RepositionWindow()
{
    int iExpand = 0;
    int iListTop = 0;
    int iListBottom = 0;
    int iListHeight = 0;
    int iListNewHeight = 0;
    int iListLeft = 0;
    int iListRight = 0;
    int iMax = m_List1.GetItemCount();
    if (iMax > 20)
        iMax = 20;
    CRect rectDesk;
    CRect rectWin;
    CRect rectList;

    GetDesktopWindow()->GetWindowRect(&rectDesk);   //fullscreen
    GetWindowRect(&rectWin);

    if (iMax > 6)
    {
        m_List1.GetWindowRect(&rectList);
        iListHeight = rectList.Height();
        iListNewHeight = (iListHeight / 6) * iMax;
        iExpand = iListNewHeight - iListHeight;
    }

    /* set to the left,upper corner */
    int iLeft  = rectDesk.TopLeft().x + 2;
    int iTop   = rectDesk.BottomRight().y - rectWin.Height() - 50 - iExpand;
    int iRight = rectDesk.TopLeft().x + rectWin.Width() + 2;
    int iBottom = rectDesk.BottomRight().y - 50;

    //komplettes Fenster anpassen
    rectWin.SetRect(iLeft, iTop, iRight, iBottom);
    MoveWindow(rectWin);

    if (iMax > 6)
    {
        //Listbox anpassen
        m_List1.GetClientRect(&rectList);
        m_List1.ClientToScreen(&rectList); // Convert to Dialog coordinates
        iListTop = rectList.TopLeft().y;
        iListBottom = rectList.BottomRight().y + iExpand;
        iListLeft = rectList.TopLeft().x;
        iListRight = rectList.BottomRight().x;
        iExpand = iListNewHeight - iListHeight;
        rectList.SetRect(iListLeft, iListTop, iListRight, iListBottom);
        ScreenToClient(rectList);
        m_List1.MoveWindow(rectList, true);
    }
}

void CDViewRabs::FillListBox()
{
    CStringArray s;
    s.SetSize(NUM_PROMOLIST_COLUMNS);
    int quota;
    int rest;

    char str[81];

    m_check.SetArticleno(m_ArtikelNr);
    m_check.SetBranchno(m_sFilialnr);
    m_check.SetCustomerno(m_lKndNr);
    m_check.SetPromotion_no(m_itdisc->anz.PROMOTION_NO);
    if (m_check.SelQuota())
    {
        s[COL_PROMOLIST_QUOTA].Empty();
        s[COL_PROMOLIST_MIN].Empty();
        s[COL_PROMOLIST_REST].Empty();
    }
    else
    {
        if (m_check.GetCustomerquotaqty() > 0)
        {
            quota = m_check.GetCustomerquotaqty();
            if (m_check.GetSoldqtycst() < 0)
            {
                rest = quota;
            }
            else
            {
                rest = quota - m_check.GetSoldqtycst();
            }
        }
        else
        {
            quota = m_check.GetBranchquotaqty();
            rest = quota - m_check.GetSoldqtybranch();
        }
        m_List1.SetColumnWidth(COL_PROMOLIST_QUOTA, 50);
        m_List1.SetColumnWidth(COL_PROMOLIST_MIN, 50);
        m_List1.SetColumnWidth(COL_PROMOLIST_REST, 50);
        s[COL_PROMOLIST_QUOTA].Format("%d", quota);
        s[COL_PROMOLIST_MIN].Format("%d", m_check.GetCustomerminqty());
        s[COL_PROMOLIST_REST].Format("%d", rest);
    }
    //Ausgabe in die Listbox
    sprintf(str, "%d", m_itdisc->anz.BASEQTY);
    s[COL_PROMOLIST_MENGE] = str;
    sprintf(str, "%0.2lf", m_itdisc->anz.DISCOUNTVALUEPCT);
    s[COL_PROMOLIST_RABATT] = str;
    s[COL_PROMOLIST_WERT].Empty();
    if (m_itdisc->anz.DISCOUNTQTY != 0 && m_itdisc->anz.DISCOUNTARTICLE == 0)
    {
        s[COL_PROMOLIST_WERT].Format("%d", m_itdisc->anz.DISCOUNTQTY);
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_NATRA);
    }
    else if (m_itdisc->anz.DISCOUNTTYPE == 1)
    {
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_SHORT);
    }
    else if (m_itdisc->anz.DISCOUNTTYPE == 2)
    {
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_AKTION);
    }
    else if (m_itdisc->anz.DISCOUNTTYPE == 3)
    {
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_DIABETES);
    }
    else if (m_itdisc->anz.DISCOUNTTYPE == 4)
    {
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_GENERICA);
    }
    else if (m_itdisc->anz.DISCOUNTTYPE == 5)
    {
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_PARTERNARIAT);
    }
    else if (m_itdisc->anz.DISCOUNTTYPE == 7)
    {
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_BAR);
    }
    else if (m_itdisc->anz.DISCOUNTTYPE == 8)
    {
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_PROMOTION);
    }
    else if (m_itdisc->anz.GROSSPROFITPCT > 0)
    {
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_ROHERTRAG);
        sprintf(str, "%0.2lf", m_itdisc->anz.GROSSPROFITPCT);
        ((CAeFView*)AeGetApp()->m_pViewEing)->m_dCstDiscount = m_itdisc->anz.DISCOUNTVALUEPCT;
        s[COL_PROMOLIST_WERT] = str;
    }
    else if (   m_itdisc->anz.CUSTOMERNO > 0
             && m_itdisc->anz.DISCOUNTGRPNO == 0
             && m_itdisc->anz.MANUFACTURERNO == 0
             && m_itdisc->anz.ARTICLENO == 0
             && m_itdisc->anz.DISCOUNTVALUEPCT > 0 )
    {
        s[COL_PROMOLIST_ART]=CResString::ex().getStrTblText(AETXT_KND_RAB);
        ((CAeFView*)AeGetApp()->m_pViewEing)->m_dCstDiscount = m_itdisc->anz.DISCOUNTVALUEPCT;
    }
    else if (m_itdisc->anz.DISCOUNTARTICLE != 0)
    {
        s[COL_PROMOLIST_ART] = CResString::ex().getStrTblText(AETXT_NATRA);
        sprintf(str, "%d", m_itdisc->anz.DISCOUNTQTY);
        s[COL_PROMOLIST_WERT] = str;
    }
    else
    {
        s[COL_PROMOLIST_ART].Empty();
    }
    s[COL_PROMOLIST_ZZ].Empty();
    AllgDatumLong2CharTTMMJJJJ(m_itdisc->anz.DATEFROM, str);
    s[COL_PROMOLIST_VON] = str;
    AllgDatumLong2CharTTMMJJJJ(m_itdisc->anz.DATETO, str);
    s[COL_PROMOLIST_BIS] = str;
    s[COL_PROMOLIST_PROMOTION] = m_itdisc->promoname;
    if (m_itdisc->promotyp == 2)
    {
        s[COL_PROMOLIST_PROMOTYP] = CResString::ex().getStrTblText(AETXT_TARGET);
    }
    else if (m_itdisc->promotyp == 3)
    {
        s[COL_PROMOLIST_PROMOTYP] = CResString::ex().getStrTblText(AETXT_PRODUCT);
    }
    else
    {
        s[COL_PROMOLIST_PROMOTYP].Empty();
    }
    s[COL_PROMOLIST_PROMONO].Format("%d", m_itdisc->anz.PROMOTION_NO);


    if (m_itdisc->anz.DISCOUNTARTICLE > 0)
    {
        CARTINF artinf;
        artinf.s.ARTIKEL_NR = m_itdisc->anz.DISCOUNTARTICLE;
        artinf.s.FILIALNR = m_sFilialnr;
        artinf.Server(AatartInf_art_nr);
        if (artinf.rc < SRV_OK)
        {
            s[COL_PROMOLIST_PZN].Empty();
            s[COL_PROMOLIST_EINHEIT].Empty();
            s[COL_PROMOLIST_ARTIKELNAME].Empty();
        }
        else
        {
            m_List1.SetColumnWidth(COL_PROMOLIST_PZN, 54);
            m_List1.SetColumnWidth(COL_PROMOLIST_EINHEIT, 50);
            m_List1.SetColumnWidth(COL_PROMOLIST_ARTIKELNAME, 140);
            s[COL_PROMOLIST_PZN].Format("%d", m_itdisc->anz.DISCOUNTARTICLE);
            s[COL_PROMOLIST_EINHEIT] = artinf.s.EINHEIT;
            s[COL_PROMOLIST_ARTIKELNAME] = artinf.s.ARTIKEL_NAME;
        }
    }

    if (!CListCtrlHelper::AppendItem(m_List1, NUM_PROMOLIST_COLUMNS, s))
    {
        EndWaitCursor();
    }
}
