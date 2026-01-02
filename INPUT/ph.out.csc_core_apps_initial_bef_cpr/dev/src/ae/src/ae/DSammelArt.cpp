// DSammelArt.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artsel.h>
#include "DArtDef.h"
#include "DSammelArt.h"


// CDSammelArt-Dialogfeld

IMPLEMENT_DYNAMIC(CDSammelArt, CDialog)
CDSammelArt::CDSammelArt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSammelArt::IDD, pParent)
    , m_CMenge(_T(""))
    , m_CPZN(_T(""))
    , m_CArtNr(_T(""))
{
}

CDSammelArt::~CDSammelArt()
{
}

void CDSammelArt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_edit_Menge);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_CMenge);
    DDX_Control(pDX, IDC_EDIT_PZN, m_edit_PZN);
    DDX_Text(pDX, IDC_EDIT_PZN, m_CPZN);
}


BEGIN_MESSAGE_MAP(CDSammelArt, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_ART, OnBnClickedButtonArt)
    ON_EN_CHANGE(IDC_EDIT_MENGE, OnEnChangeEditMenge)
    ON_EN_CHANGE(IDC_EDIT_PZN, OnEnChangeEditPzn)
END_MESSAGE_MAP()


// CDSammelArt-Meldungshandler

BOOL CDSammelArt::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_CMenge = "1";
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDSammelArt::OnBnClickedOk()
{
    UpdateData();
    CARTINF artinf;
    CARTAESEL code;
    strcpy(code.s.ARTICLE_CODE, m_CPZN);
    BeginWaitCursor();
    code.Server(AatartSel_NoByCode);
    if (code.rc != SRV_OK)
    {
        EndWaitCursor();
        MsgBoxOK(IDP_NO_DATA);
        m_edit_PZN.SetFocus();
        m_edit_PZN.SetSel(0, -1, FALSE);
        return;
    }
    m_CArtNr.Format("%d", code.s.ARTIKEL_NR);
    artinf.s.ARTIKEL_NR = atol(m_CArtNr);
    artinf.s.IMPORTARTICLE = 0;  //Importartikel machen hier keinen Sinn
    artinf.s.FILIALNR = AeGetApp()->VzNr();
    artinf.Server(AatartInf_art_nr);
    if (artinf.rc < SRV_OK)
    {
        EndWaitCursor();
        MsgBoxOK(IDP_NO_DATA);
        m_edit_PZN.SetFocus();
        m_edit_PZN.SetSel(0, -1, FALSE);
        return;
    }
    int index = m_pListCtl->GetItemCount();
    int iKb;
    if (index == 0)
    {
        iKb = 1;
    }
    else
    {
        for (int pos = 0; pos < index; pos++)
        {
            if (m_CPZN == m_pListCtl->GetItemText(pos, 2))
            {
                EndWaitCursor();
                MsgBoxOK(AETXT_VORHANDEN);
                return;
            }
        }
        iKb = atoi(m_pListCtl->GetItemText(index - 1, 0));
        iKb++;
    }
    CStringArray s;
    s.SetSize(m_sListCount);
    s[0].Format("%d", iKb);
    s[1] = m_CMenge;
    //s[2].Format("%ld", artinf.s.ARTIKEL_NR);
    s[2] = m_CPZN;
    AllgEntfSpaces(artinf.s.EINHEIT);
    s[3] = artinf.s.EINHEIT;
    AllgEntfSpaces(artinf.s.ARTIKEL_NAME);
    s[4] = artinf.s.ARTIKEL_NAME;
    s[5] = m_CArtNr;

    if (!CListCtrlHelper::InsertItem(*m_pListCtl, m_sListCount, s, index))
    {
        EndWaitCursor();
        return;
    }

    m_edit_PZN.SetFocus();
    m_edit_PZN.SetSel( 0, -1, FALSE );
    m_edit_PZN.SetSel( -1, 0, FALSE );      //Selektion aufheben
    m_edit_PZN.SetWindowText("");           //PZN löschen
    EndWaitCursor();
}

void CDSammelArt::OnBnClickedButtonArt()
{
    CDArtDef dlgArtDef;
    dlgArtDef.m_CMatchCode = m_CArt;
    m_CArt.Empty();
    if (dlgArtDef.DoModal() != IDOK)
        return;
    m_CPZN = dlgArtDef.GetArticleCode();
    m_CArtNr.Format("%ld", dlgArtDef.GetArtNr());
    GetDlgItem(IDC_EDIT_PZN)->SetWindowText(m_CPZN);
    OnBnClickedOk();
}

void CDSammelArt::OnEnChangeEditMenge()
{
    AllgWertKontr(&m_edit_Menge, MAXIMUM_BUCH_MENGE);
}

void CDSammelArt::OnEnChangeEditPzn()
{
    CString str;

    m_edit_PZN.GetWindowText(str);                      //PZN lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CArt = str;
        OnBnClickedButtonArt();
        m_edit_PZN.SetWindowText("");                   //PZN löschen
    }
}
