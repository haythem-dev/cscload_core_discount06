// DAeArtVerbundFiliale.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artsel.h>
#include <artikel.h>
#include "DArtDef.h"
#include "DAeKundeVerbundFiliale.h"
#include "DAeArtVerbundFiliale.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 80, LVCFMT_LEFT,
    2,  "", 60, LVCFMT_LEFT,
    -1, "",  0, 0
};

// CDAeArtVerbundFiliale-Dialogfeld

IMPLEMENT_DYNAMIC(CDAeArtVerbundFiliale, CDialog)
CDAeArtVerbundFiliale::CDAeArtVerbundFiliale(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeArtVerbundFiliale::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_FOLGE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
}

CDAeArtVerbundFiliale::~CDAeArtVerbundFiliale()
{
}

void CDAeArtVerbundFiliale::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDAeArtVerbundFiliale, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnBnClickedButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnBnClickedButtonChange)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
END_MESSAGE_MAP()


// CDAeArtVerbundFiliale-Meldungshandler

BOOL CDAeArtVerbundFiliale::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();
    SelArtikel();
    if (GetArtikelNr() == -1)
    {
        CDialogMultiLang::OnCancel();
        return IDCANCEL;
    }

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    SetHeader();
    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDAeArtVerbundFiliale::OnBnClickedButtonUpdate()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDAeKundeVerbundFilialeUpd upd;
        GetWindowText(upd.m_cHeader);
        upd.m_cStaticKunde = CResString::ex().getStrTblText(AETXT_PZN);
        upd.SetFunktion(1);     //Update
        upd.SetKundenNr(GetArtikelNr());
        upd.SetVbFiliale(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 2))));
        upd.SetFolge(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 1))));
        if (upd.DoModal() == IDOK)
        {
            if (upd.GetFolge() == atoi(m_ListCtl.GetItemText(pos, 1)))
                return;
            m_DkVbFil.SetBranchno(AeGetApp()->VzNr());
            m_DkVbFil.SetArticleno(GetArtikelNr());
            m_DkVbFil.SetRanking(upd.GetFolge());
            m_DkVbFil.SetAuxbranchno(upd.GetVbFiliale());
            if (m_DkVbFil.Update() == 0)
                MsgBoxOK(IDP_UPDATED);
            else
                MsgBoxOK(IDP_NOT_UPDATED);
            GetPage();
        }
    }
}

void CDAeArtVerbundFiliale::OnBnClickedButtonInsert()
{
    CDAeKundeVerbundFilialeUpd upd;
    GetWindowText(upd.m_cHeader);
    upd.SetFunktion(0);
    upd.SetKundenNr(GetArtikelNr());
    upd.SetVbFiliale(0);
    upd.SetFolge(0);
    if (upd.DoModal() == IDOK)
    {
        m_DkVbFil.SetBranchno(AeGetApp()->VzNr());
        m_DkVbFil.SetArticleno(GetArtikelNr());
        m_DkVbFil.SetRanking(upd.GetFolge());
        m_DkVbFil.SetAuxbranchno(upd.GetVbFiliale());
        MsgBoxOK(m_DkVbFil.Insert() == 0 ? IDP_NEUANLAGE : IDP_DOPPELT);
        GetPage();
    }
}

void CDAeArtVerbundFiliale::OnBnClickedButtonDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            m_DkVbFil.SetBranchno(AeGetApp()->VzNr());
            m_DkVbFil.SetArticleno(GetArtikelNr());
            m_DkVbFil.SetRanking(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 1))) );
            m_DkVbFil.SetAuxbranchno(static_cast<short>(atoi(m_ListCtl.GetItemText(pos, 2))) );
            MsgBoxOK(m_DkVbFil.Delete() == 0 ? IDP_DELETED : IDP_NOT_DELETED);
            GetPage();
        }
    }
}

void CDAeArtVerbundFiliale::OnBnClickedButtonChange()
{
    if (SelArtikel())
    {
        SetHeader();
        GetPage();
    }
}

void CDAeArtVerbundFiliale::OnNMDblclkList1(NMHDR * /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedButtonUpdate();

    *pResult = 0L;
}

void CDAeArtVerbundFiliale::GetPage()
{
    ppString text;
    CString str;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_DkVbFil.SetBranchno(AeGetApp()->VzNr());
    m_DkVbFil.SetArticleno(GetArtikelNr());
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_DkVbFil.SelList() != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%d", m_DkVbFil.GetRanking());
        s[2].Format("%d", m_DkVbFil.GetAuxbranchno());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
    m_DkVbFil.CloseCursor();
    EndWaitCursor();
}

void CDAeArtVerbundFiliale::SetHeader()
{
    CARTINF artinf;
    char text[81];
    artinf.s.ARTIKEL_NR = m_lArticleNo;
    artinf.s.FILIALNR = AeGetApp()->VzNr();
    BeginWaitCursor();
    artinf.s.IMPORTARTICLE = 0;  //Importartikel machen hier keinen Sinn
    artinf.Server(AatartInf_art_nr);
    EndWaitCursor();
    GetDlgItem(IDC_OUT_ARTICLENAME)->SetWindowText(artinf.s.ARTIKEL_NAME);
    GetDlgItem(IDC_OUT_UNIT)->SetWindowText(artinf.s.EINHEIT);
    GetDlgItem(IDC_OUT_HANDOUT)->SetWindowText(artinf.s.DARREICHFORM);
    sprintf(text, "%ld", artinf.s.ARTIKEL_NR);
    GetDlgItem(IDC_OUT_PZN)->SetWindowText(text);
    GetDlgItem(IDC_OUT_ARTCODE)->SetWindowText(m_cArticleCode);
}

bool CDAeArtVerbundFiliale::SelArtikel()
{
    //Definition Artikel
    CDArtDef dlgArtDef;
    if (dlgArtDef.DoModal() == IDOK)
    {
        SetArtikelNr(dlgArtDef.GetArtNr());
        SetArticleCode(dlgArtDef.GetArticleCode());
        return true;
    }
    return false;
}
