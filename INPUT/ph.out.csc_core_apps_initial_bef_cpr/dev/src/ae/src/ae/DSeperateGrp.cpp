// DSeperateGrp.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <controlling.h>
#include "DSeperatUpd.h"
#include "DSeperateGrp.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     9

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",   0, LVCFMT_LEFT,
    2,  "", 120, LVCFMT_LEFT,
    3,  "",  40, LVCFMT_LEFT,
    4,  "",  30, LVCFMT_LEFT,
    5,  "",  30, LVCFMT_LEFT,
    6,  "",   0, LVCFMT_LEFT,
    7,  "",  50, LVCFMT_LEFT,
    8,  "",  80, LVCFMT_RIGHT,
    -1, "",   0, 0
};


// CDSeperateGrp-Dialogfeld

IMPLEMENT_DYNAMIC(CDSeperateGrp, CDialog)
CDSeperateGrp::CDSeperateGrp(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSeperateGrp::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_GRUPPE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_GRUPPE);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_KZ_KOMMIART);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_KZ_BUCHART);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_ZURUECK);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_ZURUECK);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_HERSTEL);
}

CDSeperateGrp::~CDSeperateGrp()
{
}

void CDSeperateGrp::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDSeperateGrp, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)
END_MESSAGE_MAP()


// CDSeperateGrp-Meldungshandler

BOOL CDSeperateGrp::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_BTM).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_KK).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_K08).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_K20).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_RESERVE_HOSPITAL).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_CONTAINER).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_GROSS_VOL).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_ZYTO).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_VERBUND).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_POSITIVLISTE).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_KRANKENKASSEN_POS).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_EINZELHANDEL_POS).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_LISTE5).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_CAP).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_HERSTEL).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_KONSIGPARTNER).GetString());
    m_Gruppen.Add((char *)CResString::ex().getStrTblText(AETXT_PSYCHO).GetString());

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    FillList();

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDSeperateGrp::OnBnClickedOk()
{
    CDSeperatUpd upd;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString CStr;
        upd.m_sGruppe = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 1)));
        upd.m_cAArt = m_ListCtl.GetItemText(pos, 3);
        upd.m_cKoArt = m_ListCtl.GetItemText(pos, 4);
        upd.m_cBuArt = m_ListCtl.GetItemText(pos, 5);
        CStr = m_ListCtl.GetItemText(pos, 6);
        upd.m_cHerst = m_ListCtl.GetItemText(pos, 8);
        if (CStr.GetAt(0) == '1')
            upd.m_bDefer = true;
        upd.m_Gruppen = &m_Gruppen;
        upd.m_SepOrder = &m_SepOrder;
        upd.m_sFunktion = 0;
        if (upd.DoModal() == IDOK)
            FillList();
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDSeperateGrp::OnBnClickedButtonInsert()
{
    CDSeperatUpd upd;
    upd.m_Gruppen = &m_Gruppen;
    upd.m_SepOrder = &m_SepOrder;
    upd.m_sFunktion = 1;
    if (upd.DoModal() == IDOK)
        FillList();
}

void CDSeperateGrp::OnBnClickedButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            m_SepOrder.SetBranchno(AeGetApp()->VzNr());
            m_SepOrder.SetArtgrp(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 1))));
            m_SepOrder.SetManufacturerno(atoi(m_ListCtl.GetItemText(pos, 8)));
            m_SepOrder.Delete();
            FillList();
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDSeperateGrp::FillList()
{
    CStringArray s;
    ppString csAArt;
    s.SetSize(NUM_COLUMNS);

    m_SepOrder.SetBranchno(AeGetApp()->VzNr());
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_SepOrder.Sel()) break;
        s[0] = kb.Next();
        s[1].Format("%d", m_SepOrder.GetArtgrp());
        s[2] = m_Gruppen.GetAt(m_SepOrder.GetArtgrp());
        s[3] = m_SepOrder.GetKdauftragart(csAArt);
        s[4].Format("%c", m_SepOrder.GetKoart());
        s[5].Format("%c", m_SepOrder.GetBuchart());
        s[6].Format("%c", m_SepOrder.GetDeferorder());
        s[8].Format("%d", m_SepOrder.GetManufacturerno());
        if (m_SepOrder.GetDeferorder() == '1')
            s[7] = (char*)CResString::ex().getStrTblText(AETXT_KZ_JA).GetString();
        else
            s[7] = (char*)CResString::ex().getStrTblText(AETXT_KZ_NEIN).GetString();

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_SepOrder.CloseCursor();
    EndWaitCursor();
}

void CDSeperateGrp::OnNMDblclkList(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedOk();
    *pResult = 0L;
}
