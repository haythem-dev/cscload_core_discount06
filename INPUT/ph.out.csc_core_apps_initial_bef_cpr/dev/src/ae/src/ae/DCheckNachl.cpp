// DCheckNachl.cpp : implementation file
//

#include "stdafx.h"
#include "AeFView.h"
#include "nachlprot.h"
#include "DCheckNachl.h"

#define AENDTYP_DELETE 1

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "", 80, LVCFMT_RIGHT,
    1,  "", 80, LVCFMT_RIGHT,
    2,  "", 80, LVCFMT_RIGHT,
    3,  "", 80, LVCFMT_RIGHT,
    4,  "",  0, LVCFMT_CENTER,
    5,  "",  0, LVCFMT_CENTER,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDCheckNachl dialog


CDCheckNachl::CDCheckNachl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCheckNachl::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_AUF_NR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
}


void CDCheckNachl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDCheckNachl, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_NEW_POS, OnButtonNewPos)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCheckNachl message handlers

BOOL CDCheckNachl::OnInitDialog()
{
    //Variablen
    char Out1[11];
    CStringArray s;
    CTM zeit;
    s.SetSize(NUM_COLUMNS);

    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    m_nachl.s.FETCH_REL = 1;
    m_nachl.s.IDFNR = m_lIdf;
    m_nachl.s.ARTIKEL_NR = m_lArtikelnr;
    m_nachl.s.POSTYP = 3;
    m_nachl.s.STATUS = 0;
    m_nachl.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr_Kunde();
    m_nachl.s.REGIONNR = AeGetApp()->VzNr();
    strcpy(m_nachl.s.KDAUFTRAGART, m_cAArt);
    long AuftrNr = ((CAeFView*)AeGetApp()->m_pViewEing)->GetKdauftragNr();
    BeginWaitCursor();
    zeit.Server(AafilGetdatetime);
    for (int i = 0;; i++)
    {
        m_nachl.Server(AaauftSel_nachl);
        if (m_nachl.rc == SRV_SQLNOTFOUND)
        {
            if (i == 0)
            {
                m_nachl.s.FETCH_REL = 0;    //Close Cursor
                m_nachl.Server(AaauftSel_nachl);
                EndWaitCursor();
                CDialogMultiLang::EndDialog(FALSE);
                return TRUE;
            }
            break;
        }
        if (m_nachl.s.DATUM == zeit.s.DATUM && m_nachl.s.KDAUFTRAGNR == AuftrNr)
        {
            --i;
            continue;
        }
        AllgDatumLong2CharTTMMJJJJ(m_nachl.s.DATUM, Out1),
            s[0] = Out1;
        s[1].Format("%d", m_nachl.s.KDAUFTRAGNR);
        s[2].Format("%d", m_nachl.s.ARTIKEL_NR);
        s[3].Format("%d", m_nachl.s.MENGE);
        s[4].Format("%d", m_nachl.s.POSNR);
        s[5].Format("%d", m_nachl.s.DATUM);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            m_nachl.s.FETCH_REL = 0;    //Close Cursor
            m_nachl.Server(AaauftSel_nachl);
            EndWaitCursor();
            return FALSE;
        }
    } //Ende der for()-Schleife

    m_nachl.s.FETCH_REL = 0;    //Close Cursor
    m_nachl.Server(AaauftSel_nachl);
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCheckNachl::OnOK()
{
    CDialogMultiLang::OnOK();
}

void CDCheckNachl::OnButtonNewPos()
{
    CNACHLPROT nachlprot;
    BeginWaitCursor();
    for ( int pos = 0 ; pos < m_ListCtl.GetItemCount() ; pos++)
    {
        nachlprot.s.DATUM = atol(m_ListCtl.GetItemText(pos, 5));
        nachlprot.s.POSNR = atol(m_ListCtl.GetItemText(pos, 4));
        nachlprot.s.KDAUFTRAGNR = atol(m_ListCtl.GetItemText(pos, 1));
        nachlprot.s.POSTYP = 3;
        nachlprot.s.NL_MENGE_GELIEFER = 0;
        nachlprot.s.NL_MENGE_NEU    = 0;
        nachlprot.s.NL_MENGE_ALT    = atol(m_ListCtl.GetItemText(pos, 3));
        nachlprot.s.ARTIKEL_NR      = m_lArtikelnr;
        nachlprot.s.AENDTYP         = AENDTYP_DELETE;
        nachlprot.s.UID             = GetAeUser().GetUID();
        nachlprot.s.KDAUFTRAG_NR_NEU = 0;
        nachlprot.s.IDFNR           = m_lIdf;
        m_lMenge += atol(m_ListCtl.GetItemText(pos, 3));
        nachlprot.Server( AaauftIns_prot );
    }
    EndWaitCursor();

    CDialogMultiLang::OnOK();
}

void CDCheckNachl::OnCancel()
{
    CDialogMultiLang::OnCancel();
}
