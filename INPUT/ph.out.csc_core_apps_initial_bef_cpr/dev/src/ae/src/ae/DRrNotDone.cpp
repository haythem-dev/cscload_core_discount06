// DRrNotDone.cpp : implementation file
//

#include "stdafx.h"
#include <callback.h>
#include "DRrNotDone.h"

/////////////////////////////////////////////////////////////////////////////
// CDRrNotDone dialog

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     7

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "",  60, LVCFMT_CENTER,
    2,  "",  50, LVCFMT_CENTER,
    3,  "", 100, LVCFMT_LEFT,
    4,  "", 140, LVCFMT_LEFT,
    5,  "", 100, LVCFMT_LEFT,
    6,  "", 190, LVCFMT_LEFT,
    -1, "",   0, 0
};


CDRrNotDone::CDRrNotDone(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDRrNotDone::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[2].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_RRPARTNER);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
}


void CDRrNotDone::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDRrNotDone, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRrNotDone message handlers

BOOL CDRrNotDone::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    //Variablen
    CStringArray s;
    ppString hilfe;
    s.SetSize(NUM_COLUMNS);
    char error_msg[81];
    CString Str;

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_WEISS);
    idResources.push_back(IDI_ICON_LOW_CRITICAL);
    idResources.push_back(IDI_ICON_WARN);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    if (AeGetApp()->IsNewCallback())
    {
        CCALLBACKTODONEW todonew;
        todonew.SetVertriebszentrumnr(AeGetApp()->VzNr());
        todonew.SetRegionnr(AeGetApp()->VzNr());
        CLetterMan kb;
        for (;;)
        {
            Str.Empty();
            if (AeGetApp()->IsKundeHome())
                todonew.SelAllNotDoneVz();
            else
                todonew.SelAllNotDone();
            if (todonew.rc == SRV_SQLNOTFOUND)
                break;
            s[0] = kb.Next();
            s[1] = AllgDatumLong2CharTTMMJJ(todonew.GetCallbackdatewished(), error_msg);
            s[2] = AllgZeit2CharHHMM(todonew.GetCallbacktimewished() * 100);
            s[3] = todonew.GetDivisionname(hilfe);
            s[4] = todonew.GetNameapo(hilfe);
            s[5] = todonew.GetOrt(hilfe);
            s[6] = todonew.GetKritiktext(hilfe);

            if (!CListCtrlHelper::AppendImageItem(m_ListCtl, NUM_COLUMNS, s, todonew.GetKritiklevel()))
            {
                EndWaitCursor();
                return FALSE;
            }
        }
        if (AeGetApp()->IsKundeHome())
            todonew.SelAllNotDoneVz(0);
        else
            todonew.SelAllNotDone(0);
    }
    else
    {
        CCALLBACKTODO todo;
        todo.SetVertriebszentrumnr( AeGetApp()->VzNr() );
        todo.SetRegionnr( AeGetApp()->VzNr() );
        CLetterMan kb;
        for (;;)
        {
            Str.Empty();
            if (AeGetApp()->IsKundeHome())
                todo.SelAllNotDoneVz();
            else
                todo.SelAllNotDone();
            if (todo.rc == SRV_SQLNOTFOUND)
                break;
            s[0] = kb.Next();
            s[1] = AllgDatumLong2CharTTMMJJ(todo.GetCallbackdatewished(), error_msg);
            s[2] = AllgZeit2CharHHMM(todo.GetCallbacktimewished() * 100);
            s[3] = todo.GetCallbackpartner(hilfe);
            s[4] = todo.GetNameapo(hilfe);
            s[5] = todo.GetOrt(hilfe);
            s[6] = todo.GetKritiktext(hilfe);

            if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
            {
                EndWaitCursor();
                return FALSE;
            }
        }
        if (AeGetApp()->IsKundeHome())
            todo.SelAllNotDoneVz(0);
        else
            todo.SelAllNotDone(0);
    }
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
