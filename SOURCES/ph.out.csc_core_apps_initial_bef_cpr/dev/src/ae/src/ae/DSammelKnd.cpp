// DSammelKnd.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <kndsel.h>
#include "DKndWahl.h"
#include "DSammelKnd.h"


// CDSammelKnd-Dialogfeld

IMPLEMENT_DYNAMIC(CDSammelKnd, CDialog)
CDSammelKnd::CDSammelKnd(CWnd* pParent /*=NULL*/)
: CDialogMultiLang(CDSammelKnd::IDD, pParent), m_CIdf(_T("")), m_EnableAeGesperrt(false), m_Title("")
{
}

CDSammelKnd::~CDSammelKnd()
{
}

void CDSammelKnd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_IDF, m_edit_IDF);
    DDX_Text(pDX, IDC_EDIT_IDF, m_CIdf);
}


BEGIN_MESSAGE_MAP(CDSammelKnd, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnBnClickedButtonKnd)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnEnChangeEditIdf)
END_MESSAGE_MAP()


// CDSammelKnd-Meldungshandler

BOOL CDSammelKnd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    // Kennzeichen auf nur eigenes VZ
    m_bKundeHome = AeGetApp()->IsKundeHome();
    AeGetApp()->IsKundeHome = true;

    if (!m_Title.IsEmpty())
    {
        SetWindowText(m_Title);
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDSammelKnd::OnBnClickedOk()
{
    UpdateData();
    CKNDSEL kndsel;
    kndsel.s.KUNDENNR = atol(m_CIdf);
    kndsel.s.IDFNR = atol(m_CIdf);
    kndsel.s.VERTRIEBSZENTRUMNR = (AeGetApp()->VzNr());
    kndsel.s.REGIONNR = AeGetApp()->VzNr();
    kndsel.s.SKDKUNDEAEGESPERRT[0] = m_EnableAeGesperrt ? '1' : '0';
    kndsel.s.SKDKUNDEAEGESPERRT[1] = '\0';
    kndsel.s.FETCH_REL = 1;
    BeginWaitCursor();
    kndsel.Server(AakundeSel_idf);
    if (kndsel.rc != SRV_OK)
    {
        EndWaitCursor();
        MsgBoxOK(IDP_NO_DATA);
        kndsel.s.FETCH_REL = 0;
        kndsel.Server(AakundeSel_idf);
        m_edit_IDF.SetFocus();
        m_edit_IDF.SetSel(0, -1, FALSE);
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
            if (m_CIdf == m_pListCtl->GetItemText(pos, 1))
            {
                EndWaitCursor();
                MsgBoxOK(AETXT_VORHANDEN);
                return;
            }
        }
        iKb = atoi(m_pListCtl->GetItemText(index - 1, 0));
        ++iKb;
    }
    CStringArray s;
    s.SetSize(m_sListCount);
    s[0].Format("%d", iKb);
    s[1].Format("%ld", kndsel.s.KUNDENNR);
    AllgEntfSpaces(kndsel.s.NAMEAPO);
    s[2] = kndsel.s.NAMEAPO;
    AllgEntfSpaces(kndsel.s.ORT);
    s[3] = kndsel.s.ORT;

    if (!CListCtrlHelper::InsertImageItem(*m_pListCtl, m_sListCount, s, kndsel.s.SKDKUNDEAEGESPERRT[0] - '0', index))
    {
        EndWaitCursor();
        return;
    }

    m_edit_IDF.SetFocus();
    m_edit_IDF.SetSel(0, -1, FALSE);
    m_edit_IDF.SetSel(-1, 0, FALSE);        //Selektion aufheben
    m_edit_IDF.SetWindowText("");           //IDF löschen
    m_CMC.Empty();
    kndsel.s.FETCH_REL = 0;
    kndsel.Server(AakundeSel_idf);
    EndWaitCursor();
}

void CDSammelKnd::OnBnClickedButtonKnd()
{
    CDKndWahl dlgKndWahl;
    //dlgKndWahl.SetEnableAeGesperrt( m_EnableAeGesperrt );
    if (!m_EnableAeGesperrt)
    {
        dlgKndWahl.SetDisableAeGesperrt();
    }
    else
    {
        dlgKndWahl.SetEnableAeGesperrt(FALSE);
    }

    dlgKndWahl.m_apo = m_CMC;
    m_CMC.Empty();
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    m_CIdf.Format("%ld", dlgKndWahl.GetIdfNr());
    GetDlgItem(IDC_EDIT_IDF)->SetWindowText(m_CIdf);
    OnBnClickedOk();
}

void CDSammelKnd::OnEnChangeEditIdf()
{
    CString str;

    m_edit_IDF.GetWindowText(str);                  //IDF lesen
    if (str.IsEmpty())
        return;                                     //Feld ist leer
    char chN = str[str.GetLength() - 1];            //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CMC = str;
        OnBnClickedButtonKnd();
        m_edit_IDF.SetWindowText("");               //IDF löschen
        return;
    }
    AllgWertKontr(&m_edit_IDF, MAXIMUM_IDF);
}

BOOL CDSammelKnd::DestroyWindow()
{
    //Kennzeichen wieder auf original
    m_bKundeHome = AeGetApp()->IsKundeHome();
    AeGetApp()->IsKundeHome = m_bKundeHome;

    return CDialogMultiLang::DestroyWindow();
}
