// DShowRebates.cpp : implementation file
//

#include "stdafx.h"
#include "DShowRebates.h"
#include "AeFView.h"
#include <artsel.h>

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES SpaltenNetto[] =
{
    0,  "",  53, LVCFMT_LEFT,
    1,  "",  55, LVCFMT_RIGHT,
    2,  "",  30, LVCFMT_CENTER,
    3,  "",   0, LVCFMT_RIGHT,
    4,  "",  73, LVCFMT_LEFT,
    5,  "",  73, LVCFMT_LEFT,
    6,  "", 150, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_NETTO 7

static COLUMNS_TYPES SpaltenNatra[] =
{
    0,  "",  55, LVCFMT_LEFT,
    1,  "",  55, LVCFMT_LEFT,
    2,  "",  30, LVCFMT_CENTER,
    3,  "",  30, LVCFMT_LEFT,
    4,  "", 150, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_NATRA 5

//Definition der Tabellenbreite und der Ueberschriften
static COLUMNS_TYPES Rabatte[] =
{
    0,  "",  50, LVCFMT_CENTER,
    1,  "",  50, LVCFMT_RIGHT,
    2,  "",  40, LVCFMT_RIGHT,
    3,  "",  80, LVCFMT_LEFT,
    4,  "",   0, LVCFMT_RIGHT,
    5,  "",  70, LVCFMT_LEFT,
    6,  "",  70, LVCFMT_LEFT,
    7,  "", 150, LVCFMT_LEFT,
    8,  "",  80, LVCFMT_LEFT,
    9,  "",   0, LVCFMT_RIGHT,
    10, "",   0, LVCFMT_LEFT,
    11, "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_RABATTE 12

// CDShowRebates dialog

IMPLEMENT_DYNAMIC(CDShowRebates, CDialog)

CDShowRebates::CDShowRebates(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDShowRebates::IDD, pParent)
    , m_cName(_T(""))
    , m_cNumber(_T(""))
    , m_cAEP(_T(""))
    , m_cMenge(_T(""))
{
}

CDShowRebates::~CDShowRebates()
{
}

void CDShowRebates::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_STATIC_ART_NAME, m_cName);
    DDX_Text(pDX, IDC_STATIC_ART_NUMMER, m_cNumber);
    DDX_Text(pDX, IDC_STATIC_AEP, m_cAEP);
    DDX_Text(pDX, IDC_STATIC_MEN_BOOKED, m_cMenge);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDShowRebates, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()


// CDShowRebates message handlers


void CDShowRebates::OnOK()
{
    ((CAeFView *) AeGetApp()->m_pViewEing)->OnAuftrBearbCode(m_cNumber);

    CDialog::OnOK();
}

BOOL CDShowRebates::OnInitDialog()
{
    CDialog::OnInitDialog();
    int nomore = 0;
    int casa = 0;
    CARTINF artinf;
    artinf.s.ARTIKEL_NR = m_ArtikelNr;
    artinf.s.FILIALNR = GetFilialNr();
    artinf.Server( AatartInf_art_nr );
    m_Discount.SetBranchno(GetFilialNr());
    m_Discount.SetArticleno(m_ArtikelNr);
    m_Discount.SetCustomerno(m_lKndNr);

    for (;;)
    {
        if (m_Discount.SelListGrp() != SRV_OK)
            break;
        else if (m_Discount.GetCustomerno() > 0)
        {
            if (m_Discount.GetCustomerno() != m_lKndNr)
                continue;
        }
        nomore = 1;
        m_pldisc.insert(m_pldisc.end(), m_Discount.GetStruct());
        if (m_Discount.GetPaymenttargetno() > 0)
        {
            casa = 1;
        }
        if (m_Discount.GetDiscounttype() == 10)
        {
        // Bei Sonderangebot -> loeschen weitere Rabatte aus Liste
            m_pldisc.clear();
            m_pldisc.insert(m_pldisc.end(), m_Discount.GetStruct());
            nomore = 1;
            break;
        }
        else if (m_Discount.GetDiscounttype() == 8)
        {
            if (m_Discount.GetAddondiscountok() == '0')
            {
                if (m_lKndNr != -1 && m_Discount.GetBaseqty() <= 1)
                {
        // Bei Promotion und keine weiteren Rabatte -> loeschen weitere Rabatte aus Liste
                    for (m_itdisc = m_pldisc.begin(); m_itdisc < m_pldisc.end(); m_itdisc++)
                    {
                        if (m_itdisc->DISCOUNTTYPE != 8)
                        {
                            m_pldisc.erase(m_itdisc);
                        }
                    }
                    nomore = 1;
                }
            }
        }
    }
    if (nomore == 0)
    {
        m_Discount.SetBranchno(GetFilialNr());
        m_Discount.SetManufacturerno(artinf.s.HERSTELLER_NR);
        m_Discount.SetCustomerno(m_lKndNr);
        for (;;)
        {
            if (m_Discount.SelListGrpHerst() != SRV_OK)
                break;
            else if (m_Discount.GetCustomerno() > 0)
            {
                if (m_Discount.GetCustomerno() != m_lKndNr)
                    continue;
            }
            nomore = 1;
            m_pldisc.insert(m_pldisc.end(), m_Discount.GetStruct());
            if (m_Discount.GetPaymenttargetno() > 0)
            {
                casa = 1;
            }
        }
    }
    if (nomore == 0)
    {
        m_Discount.SetBranchno(GetFilialNr());
        m_Discount.SetArticleno(m_ArtikelNr);
        m_Discount.SetCustomerno(m_lKndNr);
        for (;;)
        {
            if (m_Discount.SellListGrpDG())
                break;
            else if (m_Discount.GetCustomerno() > 0)
            {
                if (m_Discount.GetCustomerno() != m_lKndNr)
                    continue;
            }
            m_pldisc.insert(m_pldisc.end(), m_Discount.GetStruct());
            if (m_Discount.GetPaymenttargetno() > 0)
            {
                casa = 1;
            }
        }
    }
    if (casa != 0)
    {
        CPAYTERM payterm;
        payterm.SetVertriebszentrumnr(m_FilialNr);
        payterm.SetKundennr(m_lKndNr);
        m_plpay.clear();
        int count;
        for (count = 0;; count++)
        {
            if (payterm.SelList() != SRV_OK)
                break;
            m_plpay.insert(m_plpay.end(), payterm.GetStruct());
        }
        payterm.SetPaymentarget(0);
        for (;count < 10;count++)
        {
            m_plpay.insert(m_plpay.end(), payterm.GetStruct());
        }
    }
    m_itdisc = m_pldisc.begin();
    if (m_itdisc->DISCOUNTQTY > 0)
        m_Typ = Natra;
    else if (m_itdisc->FIXEDPRICE > 0)
        m_Typ = Netto;
    else
        m_Typ = Other;

    if (m_Typ == Natra)
    {
        InitListNatra();
        FillListNatra();
    }
    else if (m_Typ == Netto)
    {
        InitListNetto();
        FillListNetto();
    }
    else
    {
        InitListOther();
        FillListOther();
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDShowRebates::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnOK();
    *pResult = 0L;
}

void CDShowRebates::InitListNatra()
{
    SpaltenNatra[0].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    SpaltenNatra[1].Columns = CResString::ex().getStrTblText(AETXT_STUECK);
    SpaltenNatra[2].Columns = CResString::ex().getStrTblText(AETXT_RG);
    SpaltenNatra[3].Columns = CResString::ex().getStrTblText(AETXT_ART);
    SpaltenNatra[4].Columns = CResString::ex().getStrTblText(AETXT_EK_GRP);

    CListCtrlHelper::AddColumns(SpaltenNatra, m_List1);
}

void CDShowRebates::InitListNetto()
{
    SpaltenNetto[0].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    SpaltenNetto[1].Columns = CResString::ex().getStrTblText(AETXT_PREIS);
    SpaltenNetto[2].Columns = CResString::ex().getStrTblText(AETXT_RG);
    SpaltenNetto[3].Columns = CResString::ex().getStrTblText(AETXT_ZZ);
    SpaltenNetto[4].Columns = CResString::ex().getStrTblText(AETXT_VON);
    SpaltenNetto[5].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    SpaltenNetto[6].Columns = CResString::ex().getStrTblText(AETXT_EK_GRP);

    CListCtrlHelper::AddColumns(SpaltenNetto, m_List1);
}

void CDShowRebates::InitListOther()
{
    Rabatte[0].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Rabatte[1].Columns = CResString::ex().getStrTblText(AETXT_RABATT);
    Rabatte[2].Columns = CResString::ex().getStrTblText(AETXT_WERT);
    Rabatte[3].Columns = CResString::ex().getStrTblText(AETXT_ART);
    Rabatte[4].Columns = CResString::ex().getStrTblText(AETXT_ZZ);
    Rabatte[5].Columns = CResString::ex().getStrTblText(AETXT_VON);
    Rabatte[6].Columns = CResString::ex().getStrTblText(AETXT_BIS);
    Rabatte[7].Columns = CResString::ex().getStrTblText(AETXT_EKGRUPPE);
    Rabatte[8].Columns = CResString::ex().getStrTblText(AETXT_RABATT_FORM);
    Rabatte[9].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Rabatte[10].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Rabatte[11].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);

    CListCtrlHelper::AddColumns(Rabatte, m_List1);
}

void CDShowRebates::FillListNatra()
{
    char str[81];
    CStringArray s;
    CPHARMGRP pharmgrp;
    ppString GrpName;

    //Natralistbox füllen
    s.SetSize(NUM_SPALT_NATRA);
    for (m_itdisc = m_pldisc.begin(); m_itdisc < m_pldisc.end(); m_itdisc++)
    {
        if (m_itdisc->DISCOUNTQTY == 0)
            continue;
        if (m_itdisc->DISCOUNTQTY > 0 && m_itdisc->DISCOUNTARTICLE > 0)
            continue;
        if (m_itdisc->CUSTOMERNO != 0 &&
            m_lKndNr != -1 &&
            m_itdisc->CUSTOMERNO != m_lKndNr)
            continue;
        //Ausgabe in die Listbox
        sprintf(str, "%d", m_itdisc->BASEQTY);
        s[0] = str;
        sprintf(str, "%d", m_itdisc->DISCOUNTQTY);
        s[1] = str;
        sprintf(str, "%d", m_itdisc->DISCOUNTTYPE);
        s[2] = str;
        if (m_itdisc->INTERNALDISCOUNT[0] == '1')
            s[3] = CResString::ex().getStrTblText(AETXT_INTERN);
        else
            s[3].Empty();
        pharmgrp.SetPharmacygroupid(m_itdisc->PHARMACYGROUPID);
        pharmgrp.SetBranchno(m_FilialNr);
        if (!pharmgrp.Sel())
            s[4] = pharmgrp.GetGroup_name(GrpName);
        else
            s[4] = m_itdisc->PHARMACYGROUPID;

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_SPALT_NATRA, s))
        {
            EndWaitCursor();
            return;
        }
    }
}

void CDShowRebates::FillListNetto()
{
    //Nettolistbox füllen
    char str[81];
    CStringArray s;
    s.SetSize(NUM_SPALT_NETTO);
    CPHARMGRP pharmgrp;
    ppString GrpName;
    for (m_itdisc = m_pldisc.begin(); m_itdisc < m_pldisc.end(); m_itdisc++)
    {
        if (m_itdisc->FIXEDPRICE == 0)
            continue;
        if (m_itdisc->FIXEDPRICE > 0 && m_itdisc->DISCOUNTVALUEPCT > 0)
            continue;
        if (m_itdisc->CUSTOMERNO != 0 &&
            m_lKndNr != -1 &&
            m_itdisc->CUSTOMERNO != m_lKndNr)
            continue;
        //Ausgabe in die Listbox
        sprintf(str, "%d", m_itdisc->BASEQTY);
        s[0] = str;
        sprintf(str, "%0.2f", m_itdisc->FIXEDPRICE);
        s[1] = str;
        sprintf(str, "%d", m_itdisc->DISCOUNTTYPE);
        s[2] = str;
        s[3].Empty();
        if (m_itdisc->PAYMENTTARGETNO > 0)
        {
            m_List1.SetColumnWidth(3, 27);
            s[3].Format("%d", m_plpay.at(m_itdisc->PAYMENTTARGETNO - 1).PAYMENTARGET);
        }
        AllgDatumLong2CharTTMMJJJJ(m_itdisc->DATEFROM, str);
        s[4] = str;
        AllgDatumLong2CharTTMMJJJJ(m_itdisc->DATETO, str);
        s[5] = str;
        pharmgrp.SetPharmacygroupid(m_itdisc->PHARMACYGROUPID);
        pharmgrp.SetBranchno(m_FilialNr);
        if (!pharmgrp.Sel())
            s[6] = pharmgrp.GetGroup_name(GrpName);
        else
            s[6] = m_itdisc->PHARMACYGROUPID;

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_SPALT_NETTO, s))
        {
            return;
        }
    }
}

void CDShowRebates::FillListOther()
{
    char str[81];
    CStringArray s;
    s.SetSize(NUM_RABATTE);
    CPHARMGRP pharmgrp;
    ppString GrpName;
    for (m_itdisc = m_pldisc.begin(); m_itdisc < m_pldisc.end(); m_itdisc++)
    {
        if (m_itdisc->FIXEDPRICE > 0 && m_itdisc->DISCOUNTVALUEPCT == 0)
        {
            if (AeGetApp()->IsRS())
            {
                if (m_itdisc->PAYMENTTARGETNO == 0)
                    continue;
            }
            else
            {
                continue;
            }
        }
        if (m_itdisc->DISCOUNTQTY != 0 && m_itdisc->DISCOUNTARTICLE == 0)
            continue;
        if (m_itdisc->CUSTOMERNO != 0 &&
            m_lKndNr != -1 &&
            m_itdisc->CUSTOMERNO != m_lKndNr)
            continue;
        //Ausgabe in die Listbox
        sprintf(str, "%d", m_itdisc->BASEQTY);
        s[0] = str;
        sprintf(str, "%0.2lf", m_itdisc->DISCOUNTVALUEPCT);
        s[1] = str;
        s[2].Empty();
        if (m_itdisc->DISCOUNTTYPE == 1)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_SHORT);
        }
        else if (m_itdisc->DISCOUNTTYPE == 2)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_AKTION);
        }
        else if (m_itdisc->DISCOUNTTYPE == 3)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_DIABETES);
        }
        else if (m_itdisc->DISCOUNTTYPE == 4)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_GENERICA);
        }
        else if (m_itdisc->DISCOUNTTYPE == 5)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_PARTERNARIAT);
        }
        else if (m_itdisc->DISCOUNTTYPE == 7)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_BAR);
        }
        else if (m_itdisc->DISCOUNTTYPE == 8)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_PROMOTION);
        }
        else if (m_itdisc->GROSSPROFITPCT > 0)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_ROHERTRAG);
            sprintf(str, "%0.2lf", m_itdisc->GROSSPROFITPCT);
            s[2] = str;
        }
        else if (m_iBasis == 1)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_KND_RAB);
        }
        else if (m_itdisc->DISCOUNTARTICLE != 0)
        {
            s[3] = CResString::ex().getStrTblText(AETXT_NATRA);
            sprintf(str, "%d", m_itdisc->DISCOUNTQTY);
            s[2] = str;
        }
        else
        {
            s[3].Empty();
        }
        s[4].Empty();
        if (m_itdisc->PAYMENTTARGETNO > 0)
        {
            m_List1.SetColumnWidth(4, 27);
            s[4].Format("%d", m_plpay.at(m_itdisc->PAYMENTTARGETNO - 1).PAYMENTARGET);
        }
        AllgDatumLong2CharTTMMJJJJ(m_itdisc->DATEFROM, str);
        s[5] = str;
        AllgDatumLong2CharTTMMJJJJ(m_itdisc->DATETO, str);
        s[6] = str;
        pharmgrp.SetPharmacygroupid(m_itdisc->PHARMACYGROUPID);
        pharmgrp.SetBranchno(m_FilialNr);
        if (!pharmgrp.Sel())
            s[7] = pharmgrp.GetGroup_name(GrpName);
        else
            s[7] = m_itdisc->PHARMACYGROUPID;
        if (m_itdisc->DISCOUNTSPEC == 1)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_LOG);
            sprintf(str, "%0.2lf", m_itdisc->SURCHARGEPCT);
            s[2] = str;
        }
        else if (m_itdisc->DISCOUNTSPEC == 2)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_WH);
        }
        else if (m_itdisc->DISCOUNTSPEC == 3)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_RE);
        }
        else if (m_itdisc->DISCOUNTSPEC == 4)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_MON_POS);
        }
        else if (m_itdisc->DISCOUNTSPEC == 5)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_MON_MON);
        }
        else if (m_itdisc->DISCOUNTSPEC == 6)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_MON_QUA);
        }
        else if (m_itdisc->DISCOUNTSPEC == 7)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_INDUSTRIE);
        }
        else if (m_itdisc->DISCOUNTSPEC == 8)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_RAB_FREI);
        }
        else if (m_itdisc->DISCOUNTSPEC == 9)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_RAB_KKH);
        }
        else if (m_itdisc->DISCOUNTSPEC == 10)
        {
            s[8] = CResString::ex().getStrTblText(AETXT_OCCASSION);
        }
        else
        {
            s[8].Empty();
        }
        if (m_itdisc->DISCOUNTARTICLE > 0)
        {
            CARTINF artinf;
            artinf.s.ARTIKEL_NR = m_itdisc->DISCOUNTARTICLE;
            artinf.s.FILIALNR = GetFilialNr();
            artinf.Server(AatartInf_art_nr);
            if (artinf.rc < SRV_OK)
            {
                s[9].Empty();
                s[10].Empty();
                s[11].Empty();
            }
            else
            {
                m_List1.SetColumnWidth(9, 50);
                m_List1.SetColumnWidth(10, 64);
                m_List1.SetColumnWidth(11, 170);
                s[9].Format("%d", m_itdisc->DISCOUNTARTICLE);
                s[10] = artinf.s.EINHEIT;
                s[11] = artinf.s.ARTIKEL_NAME;
            }
        }

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_RABATTE, s))
        {
            EndWaitCursor();
        }
    }
}
