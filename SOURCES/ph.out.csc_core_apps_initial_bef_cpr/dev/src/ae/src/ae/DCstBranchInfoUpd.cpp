// DCstBranchInfoUpd.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <customer.h>
#include "DChooseFiliale.h"
#include "DCstBranchInfoUpd.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     5

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 400, LVCFMT_LEFT,
    2,  "",  80, LVCFMT_LEFT,
    3,  "",  80, LVCFMT_LEFT,
    4,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};


// CDCstBranchInfoUpd-Dialogfeld

IMPLEMENT_DYNAMIC(CDCstBranchInfoUpd, CDialog)
CDCstBranchInfoUpd::CDCstBranchInfoUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCstBranchInfoUpd::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_INFO);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_DATE_TO);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_TIME_TO);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_LFDNR);
    m_sBranchNo = AeGetApp()->VzNr();
}

CDCstBranchInfoUpd::~CDCstBranchInfoUpd()
{
}

void CDCstBranchInfoUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDCstBranchInfoUpd, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
END_MESSAGE_MAP()


// CDCstBranchInfoUpd-Meldungshandler

BOOL CDCstBranchInfoUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    CDChooseFiliale dlgChooseFiliale;
    if (dlgChooseFiliale.DoModal() == IDOK)
    {
        m_sBranchNo = dlgChooseFiliale.m_FilialNr;
    }

    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCstBranchInfoUpd::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonUpdate();
    *pResult = 0L;
}

void CDCstBranchInfoUpd::OnButtonInsert()
{
    CDCstBranchInfoDetails dlgCstBranchInfoDetails;
    dlgCstBranchInfoDetails.m_bNew = true;
    if (dlgCstBranchInfoDetails.DoModal() == IDOK)
    {
        m_Info.SetBranchno(m_sBranchNo);
        m_Info.SetLfdnr(0);
        m_Info.SetDateto(dlgCstBranchInfoDetails.m_lDateTo);
        m_Info.SetTimeto(dlgCstBranchInfoDetails.m_lTimeTo);
        m_Info.SetInfotext(dlgCstBranchInfoDetails.m_InfoText);
        m_Info.Insert();
        GetPage();
    }
}

void CDCstBranchInfoUpd::OnButtonUpdate()
{
    long year,month,day,hour,minutes,seconds;
    CString hilfe;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDCstBranchInfoDetails dlgCstBranchInfoDetails;
        dlgCstBranchInfoDetails.m_bNew = false;
        dlgCstBranchInfoDetails.m_InfoText = m_ListCtl.GetItemText(pos, 1);
        hilfe = m_ListCtl.GetItemText(pos, 2);
        day = atol(hilfe.Left(2));
        month = atol(hilfe.Mid(3,2));
        year = atol(hilfe.Right(4));
        dlgCstBranchInfoDetails.m_lDateTo = day + month * 100 + year * 10000;
        hilfe = m_ListCtl.GetItemText(pos, 3);
        hour = atol(hilfe.Left(2));
        minutes = atol(hilfe.Mid(3,2));
        seconds = 0;
        dlgCstBranchInfoDetails.m_lTimeTo = minutes * 100 + hour * 10000;
        if (dlgCstBranchInfoDetails.DoModal() == IDOK)
        {
            m_Info.SetBranchno(m_sBranchNo);
            m_Info.SetLfdnr(atol(m_ListCtl.GetItemText(pos, 4)));
            m_Info.SetDateto(dlgCstBranchInfoDetails.m_lDateTo);
            m_Info.SetTimeto(dlgCstBranchInfoDetails.m_lTimeTo);
            m_Info.SetInfotext(dlgCstBranchInfoDetails.m_InfoText);
            m_Info.Update();
            GetPage();
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDCstBranchInfoUpd::OnButtonDelete()
{
    int del = 0;
    CString hilfe;
    for (;;)
    {
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            if (del == 0)
            {
                if (MsgBoxYesNo(AETXT_SOLL_DEL) == IDNO)
                    return;
            }

            m_Info.SetLfdnr(atol(m_ListCtl.GetItemText(pos, 4)));
            m_Info.Delete();
            ++del;
            m_ListCtl.DeleteItem(pos);
        }
        else
        {
            break;
        }
    }
    if (del == 0)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDCstBranchInfoUpd::GetPage()
{
    ppString infotext;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    m_Info.SetBranchno(m_sBranchNo);
    CLetterMan kb;
    for (;;)
    {
        if (m_Info.SelList() != SRV_OK)
            break;
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        s[1] = m_Info.GetInfotext(infotext);
        s[2] = DDMMYYYYStringFromDateLong(m_Info.GetDateto());
        s[3] = HHmmSSStringFromTimeLong(m_Info.GetTimeto());
        s[4].Format("%d", m_Info.GetLfdnr());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_Info.CloseCursor();

    EndWaitCursor();
}


// DCstBranchInfoUpd.cpp : Implementierungsdatei
//

// CDCstBranchInfoDetails-Dialogfeld

IMPLEMENT_DYNAMIC(CDCstBranchInfoDetails, CDialog)
CDCstBranchInfoDetails::CDCstBranchInfoDetails(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCstBranchInfoDetails::IDD, pParent)
{
    m_InfoText = _T("");
    m_bNew = false;
    m_CT_DatumBis = 0;
    m_CT_ZeitBis = 0;
    m_lActDate = 0;
    m_lDateTo = 0;
    m_lTimeTo = 0;
}

CDCstBranchInfoDetails::~CDCstBranchInfoDetails()
{
}

void CDCstBranchInfoDetails::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_INFOTEXT, m_Edit_InfoText);
    DDX_Control(pDX, IDC_DATETIMEPICKER_TIME, m_DT_ZeitBis);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DATE, m_DT_DatumBis);
    DDX_Text(pDX, IDC_EDIT_INFOTEXT, m_InfoText);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE, m_CT_DatumBis);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME, m_CT_ZeitBis);
}


BEGIN_MESSAGE_MAP(CDCstBranchInfoDetails, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_INFOTEXT, OnChangeEditInfotext)
END_MESSAGE_MAP()


// CDCstBranchInfoDetails-Meldungshandler

BOOL CDCstBranchInfoDetails::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_lActDate = zeit.s.DATUM;
    CTime anf = CTimeFromDateLongMinTime(zeit.s.DATUM);
    CTimeSpan y(40, 0, 0, 0);
    CTime end = anf + y;
    m_DT_DatumBis.SetRange(&anf,&end);
    if (m_bNew)
    {
        m_DT_DatumBis.SetTime(&anf);
        CTime zeitbis = CTimeFromDateLongMaxTime(zeit.s.DATUM);
        //m_DT_ZeitBis.SetTime(&zeitbis);
        m_CT_ZeitBis = zeitbis;
    }
    else
    {
        if (m_lDateTo < m_lActDate)
            m_lDateTo = m_lActDate;
        CTime old = CTimeFromDateLongMinTime(m_lDateTo);
        m_DT_DatumBis.SetTime(&old);
        CTime zeitold = CTimeFromDateTimeLong(zeit.s.DATUM, m_lTimeTo);
        //m_DT_ZeitBis.SetTime(&zeitold);
        m_CT_ZeitBis = zeitold;
    }
    CenterWindow();
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDCstBranchInfoDetails::OnChangeEditInfotext()
{
    AllgLaengeKontr(&m_Edit_InfoText, 240,AeGetApp()->Modus());
}

void CDCstBranchInfoDetails::OnOK()
{
    UpdateData();
    if (m_InfoText.IsEmpty())
    {
        MsgBoxOK(AETXT_TEXT_INPUT);
        return;
    }
    m_lDateTo = m_CT_DatumBis.GetYear()*10000 + m_CT_DatumBis.GetMonth() * 100 + m_CT_DatumBis.GetDay();
    m_lTimeTo = m_CT_ZeitBis.GetHour() * 10000 + m_CT_ZeitBis.GetMinute() * 100 + m_CT_ZeitBis.GetSecond();
    CDialogMultiLang::OnOK();
}