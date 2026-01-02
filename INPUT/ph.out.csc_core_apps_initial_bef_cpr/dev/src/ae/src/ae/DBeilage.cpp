// DBeilage.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include "DArtDef.h"
#include "DBeilage.h"


// CDBeilage-Dialogfeld

IMPLEMENT_DYNAMIC(CDBeilage, CDialog)
CDBeilage::CDBeilage(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBeilage::IDD, pParent)
    , m_cArtikel(_T(""))
    , m_cText(_T(""))
{
    m_lArtNr = 0;
}

CDBeilage::~CDBeilage()
{
}

void CDBeilage::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PZN, m_cArtikel);
    DDX_Text(pDX, IDC_EDIT_TEXT, m_cText);
    DDX_Control(pDX, IDC_EDIT_PZN, m_edit_Artikel);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_edit_Text);
}


BEGIN_MESSAGE_MAP(CDBeilage, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnBnClickedButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDelete)
    ON_EN_CHANGE(IDC_EDIT_PZN, OnEnChangeEditArtkelnr)
END_MESSAGE_MAP()


// CDBeilage-Meldungshandler

BOOL CDBeilage::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    if (m_lArtNr == 0)
    {
        //Definition Artikel
        CDArtDef dlgArtDef;
        if (dlgArtDef.DoModal() == IDOK)
        {
            m_lArtNr = dlgArtDef.GetArtNr();
            m_cArtikel = dlgArtDef.GetArticleCode();
        }
        else
        {
            return IDCANCEL;
        }
    }
    UpdateData(FALSE);
    OnBnClickedOk();
    m_edit_Text.SetFocus();
    return FALSE;  // return TRUE unless you set the focus to a control
                   // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDBeilage::OnBnClickedOk()
{
    UpdateData();
    if (m_cArtikel.IsEmpty())
    {
        MsgBoxOK(IDP_NO_PZN);
        return;
    }
    CARTAESEL code;
    strcpy(code.s.ARTICLE_CODE, m_cArtikel);
    code.s.CODE_TYPE = 0;
    BeginWaitCursor();
    code.Server(AatartSel_NoByCode);
    if (code.rc != SRV_OK)
    {
        MsgBoxOK(AETXT_NO_ARTICLECODE);
        m_edit_Artikel.SetFocus();
        EndWaitCursor();
        return;
    }
    m_lArtNr = code.s.ARTIKEL_NR;
    m_cText.Empty();
    m_Beilage.SetArticleno(m_lArtNr);
    m_Beilage.SetArtinfotype(0);
    ppString text;
    CString helptext;
    CString spaces(' ', 256);
    int len;
    for (;;)
    {
        if (m_Beilage.SelBeilage())
            break;
        m_Beilage.GetInfotext(text);
        helptext = text;
        len = 256 - helptext.GetLength();
        helptext.Format("%s%*.*s"
            , helptext.GetString()
            , len
            , len
            , spaces.GetString());
        m_cText += helptext;
    }
    m_cText.TrimRight();
    m_Beilage.CloseCursor();
    EndWaitCursor();
    UpdateData(FALSE);
}

void CDBeilage::OnBnClickedButtonUpdate()
{
    UpdateData();
    if (m_cArtikel.IsEmpty())
    {
        MsgBoxOK(IDP_NO_PZN);
        return;
    }
    if (m_cText.IsEmpty())
    {
        MsgBoxOK(AETXT_NO_TEXT);
        return;
    }
    BeginWaitCursor();
    CARTAESEL code;
    strcpy(code.s.ARTICLE_CODE, m_cArtikel);
    code.s.CODE_TYPE = 0;
    code.Server(AatartSel_NoByCode);
    if (code.rc != SRV_OK)
    {
        MsgBoxOK(AETXT_NO_ARTICLECODE);
        m_edit_Artikel.SetFocus();
        EndWaitCursor();
        return;
    }
    m_lArtNr = code.s.ARTIKEL_NR;
    m_Beilage.SetArticleno(m_lArtNr);
    m_Beilage.SetArtinfotype(0);
    m_Beilage.Delete();
    CString rest = m_cText;
    CString wText;
    for (int i = 0;; i++)
    {
        wText = rest.Left(256);
        if (wText.IsEmpty())
            break;
        if (rest.GetLength() < 256)
        {
            rest.Empty();
        }
        else
        {
            rest = rest.Right(rest.GetLength() - 256);
        }
        m_Beilage.SetSequenceno(static_cast<short>(i));
        m_Beilage.SetInfotext(wText);
        m_Beilage.Insert();
    }
    EndWaitCursor();
    MsgBoxOK(AETXT_ROW_UPDATED);
}

void CDBeilage::OnBnClickedButtonDelete()
{
    UpdateData();
    if (m_cArtikel.IsEmpty())
    {
        MsgBoxOK(IDP_NO_PZN);
        return;
    }
    if (MsgBoxYesNo(IDP_SOLL_DEL_SATZ) == IDYES)
    {
        BeginWaitCursor();
        CARTAESEL code;
        strcpy(code.s.ARTICLE_CODE, m_cArtikel);
        code.s.CODE_TYPE = 0;
        code.Server(AatartSel_NoByCode);
        if (code.rc != SRV_OK)
        {
            MsgBoxOK(AETXT_NO_ARTICLECODE);
            m_edit_Artikel.SetFocus();
            EndWaitCursor();
            return;
        }
        m_lArtNr = code.s.ARTIKEL_NR;
        m_Beilage.SetArticleno(m_lArtNr);
        m_Beilage.SetArtinfotype(0);
        m_Beilage.Delete();
        EndWaitCursor();
        MsgBoxOK(AETXT_ROW_DELETED);
        m_cText.Empty();
        UpdateData(FALSE);
    }
}

void CDBeilage::OnEnChangeEditArtkelnr()
{
    CString str;

    m_edit_Artikel.GetWindowText( str );            //PZN lesen
    if (str.IsEmpty())
        return;                                     //Feld ist leer
    char chN = str[str.GetLength() - 1];            //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        CDArtDef dlgArtDef;
        dlgArtDef.m_CMatchCode = str;
        if (dlgArtDef.DoModal() != IDOK)
        {
            m_lArtNr = 0;
            return;
        }
        m_lArtNr = dlgArtDef.GetArtNr();
        m_cArtikel = dlgArtDef.GetArticleCode();
        GetDlgItem(IDC_EDIT_PZN)->SetWindowText(m_cArtikel);
        m_edit_Artikel.SetFocus();
        m_edit_Artikel.SetSel(0, -1, FALSE);
        m_edit_Artikel.SetSel(-1, 0, FALSE);        //Selektion aufheben
        return;
    }
}
