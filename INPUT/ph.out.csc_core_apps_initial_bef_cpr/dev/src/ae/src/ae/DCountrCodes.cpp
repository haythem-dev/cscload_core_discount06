// DCountrCodes.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include "DCountryUpd.h"
#include "DCountrCodes.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     9

static COLUMNS_TYPES Columns[] =
{
    0,  "",  40, LVCFMT_LEFT,
    1,  "",   0, LVCFMT_LEFT,
    2,  "",  35, LVCFMT_LEFT,
    3,  "",  00, LVCFMT_LEFT,
    4,  "",  30, LVCFMT_LEFT,
    5,  "", 120, LVCFMT_LEFT,
    6,  "", 150, LVCFMT_LEFT,
    7,  "",  70, LVCFMT_LEFT,
    8,  "", 350, LVCFMT_LEFT,
    -1, "",   0, 0
};

// CDCountrCodes-Dialogfeld

IMPLEMENT_DYNAMIC(CDCountrCodes, CDialog)
CDCountrCodes::CDCountrCodes(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCountrCodes::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_CODE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_AKTIV);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_AKTIV);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_VB);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_VB);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_SERA_TEXT);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_PRINT_TEXT);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_XML_CODE);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_XML_TEXT);
}

CDCountrCodes::~CDCountrCodes()
{
}

void CDCountrCodes::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDCountrCodes, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
END_MESSAGE_MAP()


// CDCountrCodes-Meldungshandler

BOOL CDCountrCodes::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

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

void CDCountrCodes::OnBnClickedOk()
{
    CDCountryUpd upd;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        upd.m_CCode = m_ListCtl.GetItemText(pos, 0);
        CString CStr = m_ListCtl.GetItemText(pos, 1);
        upd.m_bAktiv = (CStr.GetAt(0) == '1') ? true : false;
        CStr = m_ListCtl.GetItemText(pos, 3);
        upd.m_bVB = (CStr.GetAt(0) == '1') ? true : false;
        upd.m_CSera = m_ListCtl.GetItemText(pos, 5);
        upd.m_CPrint = m_ListCtl.GetItemText(pos, 6);
        upd.m_CXMLCode = m_ListCtl.GetItemText(pos, 7);
        upd.m_CXMLText = m_ListCtl.GetItemText(pos, 8);
        upd.m_CountryCode = &m_CountryCode;
        upd.m_sFunktion = 0;
        if (upd.DoModal() == IDOK)
            FillList();
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDCountrCodes::OnBnClickedButtonInsert()
{
    CDCountryUpd upd;
    upd.m_CountryCode = &m_CountryCode;
    upd.m_sFunktion = 1;
    if (upd.DoModal() == IDOK)
        FillList();
}

void CDCountrCodes::OnBnClickedButtonDelete()
{
    CDCountryUpd upd;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            m_CountryCode.SetBranchno( AeGetApp()->VzNr() );
            m_CountryCode.SetInfocode( m_ListCtl.GetItemText(pos, 0) );
            m_CountryCode.Delete();
            FillList();
        }
    }
    else
    {
        MsgBoxOK( IDP_KEIN_SATZ_SEL );
    }
}

void CDCountrCodes::FillList()
{
    CStringArray s;
    ppString csCode;
    ppString csSera;
    ppString csPrint;
    ppString csXMLCode;
    ppString csXMLText;
    s.SetSize(NUM_COLUMNS);

    m_CountryCode.SetBranchno(AeGetApp()->VzNr());
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        if (m_CountryCode.Sel()) break;
        s[0] = m_CountryCode.GetInfocode(csCode);
        s[1].Format("%c", m_CountryCode.GetArticleactiv());
        if (m_CountryCode.GetArticleactiv() == '1')
            s[2] = (char *)CResString::ex().getStrTblText(AETXT_KZ_JA).GetString();
        else
            s[2] = (char*)CResString::ex().getStrTblText(AETXT_KZ_NEIN).GetString();
        s[3].Format("%c", m_CountryCode.GetAuxdelivery());
        if (m_CountryCode.GetAuxdelivery() == '1')
            s[4] = (char*)CResString::ex().getStrTblText(AETXT_KZ_JA).GetString();
        else
            s[4] = (char*)CResString::ex().getStrTblText(AETXT_KZ_NEIN).GetString();
        s[5] = m_CountryCode.GetSeracode(csSera);;
        s[6] = m_CountryCode.GetPrintcode(csPrint);;
        s[7] = m_CountryCode.GetXmlcode(csXMLCode);;
        s[8] = m_CountryCode.GetXmltext(csXMLText);;

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_CountryCode.CloseCursor();
    EndWaitCursor();
}

void CDCountrCodes::OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedOk();
    *pResult = 0L;
}
