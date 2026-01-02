// DKritikAnz.cpp : implementation file
//

#include "stdafx.h"
#include <callback.h>
#include "DKritikAnz.h"
#include "CallbackStatusManager.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     7

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_RIGHT,
    1,  "",  75, LVCFMT_LEFT,
    2,  "",  70, LVCFMT_LEFT,
    3,  "", 100, LVCFMT_LEFT,
    4,  "", 135, LVCFMT_LEFT,
    5,  "", 140, LVCFMT_LEFT,
    6,  "", 500, LVCFMT_LEFT,
    -1, "",   0, 0
};


// CDKritikAnz dialog

// CDViewRabs-Dialogfeld

CDKritikAnz::CDKritikAnz(CView* pView)
{
    m_pView = pView;
}

IMPLEMENT_DYNAMIC(CDKritikAnz, CDialog)

CDKritikAnz::CDKritikAnz(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDKritikAnz::IDD, pParent)
{
    m_sBranchno = 0;
    m_lCustomerno = 0;

}

CDKritikAnz::~CDKritikAnz()
{
}

void CDKritikAnz::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDKritikAnz, CDialogMultiLang)
END_MESSAGE_MAP()


// CDKritikAnz message handlers

BOOL CDKritikAnz::Create()
{
    return CDialogMultiLang::Create(CDKritikAnz::IDD);
}


BOOL CDKritikAnz::OnInitDialog()
{
    CStringArray s;
    CString helptext;
    s.SetSize(NUM_COLUMNS);
    ppString text;

    CDialogMultiLang::OnInitDialog();
    RepositionWindow();

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_SHORT_KREDITLIMIT);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_STATUS_LANG);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[3].Columns = CResString::ex().getStrTblText(IDS_USER);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_CALLBACK_DIVISION);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_CALLBACK_REASON);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_TEXT);

    DWORD dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES;
    m_List1.SetExtendedStyle(dwOldBits);

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_LOW_CRITICAL);
    idResources.push_back(IDI_ICON_WARN);
    idResources.push_back(IDI_ICON_OK_GREEN);
    idResources.push_back(IDI_ICON_NO_AKTIV);
    idResources.push_back(IDI_ICON_WEISS);
    CListCtrlHelper::CreateAndSetImageList(m_List1, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    int count = 0;
    long kritiknr = 0;
    long done;

    CCALLBACKCRITICAL critik;
    critik.SetVertriebszentrumnr(m_sBranchno);
    critik.SetKundennr(m_lCustomerno);

    m_List1.DeleteAllItems();
    for (;;)
    {
        //break;
        if (critik.SelCritical())
            break;
        if (kritiknr == critik.GetKritiknr())
        {
            s[0].Empty();
            s[1].Empty();
            s[2].Empty();
            s[3].Empty();
            s[4].Empty();
            s[5].Empty();
            s[6] = critik.GetKritiktext(text);

            if (!CListCtrlHelper::AppendImageItem(m_List1, NUM_COLUMNS, s, 4))
            {
                //EndWaitCursor();
                return FALSE;
            }
        }
        else
        {
            if (count++ >= 3)
                break;
            kritiknr = critik.GetKritiknr();
            s[0].Empty();

            if (AeGetApp()->IsCBStatusUsed())
            {
                CCallbackStatusManager callbackStatusManager;
                if (callbackStatusManager.IsCloseStatus(critik.GetStatusID()))
                {
                    done = 2;
                }
                else
                {
                    done = 3;
                }
                s[1] = callbackStatusManager.GetStatusName(critik.GetStatusID());
            }
            else
            {
                if (critik.GetPosnr_done() > 0)
                {
                    s[1] = CResString::ex().getStrTblText(AETXT_RR_ERLEDIGT);
                    done = 2;
                }
                else
                {
                    s[1] = CResString::ex().getStrTblText(AETXT_RR_OFFEN);
                    done = 3;
                }
            }

            s[2] = DDMMYYYYStringFromDateLong(critik.GetDatum());
            s[3] = critik.GetUsername64(text);
            s[4] = critik.GetDivisionname(text);
            s[5] = critik.GetTitel(text);
            helptext = critik.GetKritiktext(text);
            int start = helptext.Find('\n', 0);
            if (start != -1)
            {
                int len;
                int start2 = helptext.Find('\n', start + 1);
                if (start2 == -1)
                {
                    len = helptext.GetLength();
                    len -= start + 1;
                    helptext = helptext.Right(len);
                }
                else
                {
                    len = helptext.GetLength();
                    len -= start2 + 1;
                    helptext = helptext.Right(len);
                }
            }
            s[6] = helptext;

            int index;
            if (!CListCtrlHelper::GetAppendImageItem(m_List1, NUM_COLUMNS, s, critik.GetKritiklevel() - 1, index))
            {
                //EndWaitCursor();
                return FALSE;
            }
            CListCtrlHelper::SetImageItem(m_List1, index, 1, done);
        }
    }

    ShowWindow((count == 0) ? SW_HIDE : SW_SHOW);
    EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDKritikAnz::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDKritikAnz::OnCancel()
{
    if (m_pView != NULL)
    {
        // falls nichtmodales Dialogfeld, OnCancel-Funktion der
        // Basisklasse nicht aufrufen
        m_pView->PostMessage(WM_GOODBYEBKRITIK, IDCANCEL);
    }
    else
    {
        CDialogMultiLang::OnCancel();   // falls modales Dialogfeld
    }
}

void CDKritikAnz::RepositionWindow()
{
    CRect rectDesk;
    CRect rectWin;

    GetDesktopWindow()->GetWindowRect( &rectDesk );   //fullscreen
    GetWindowRect( &rectWin );

    /* set to the left,buttom corner */

    int iLeft  = rectDesk.TopLeft().x + 2;
    int iTop   = rectDesk.BottomRight().y - rectWin.Height() - 50;
    int iRight = rectDesk.TopLeft().x + rectWin.Width() + 2;
    int iBottom = rectDesk.BottomRight().y - 50;

    rectWin.SetRect( iLeft, iTop, iRight, iBottom);
    MoveWindow(rectWin);
}
