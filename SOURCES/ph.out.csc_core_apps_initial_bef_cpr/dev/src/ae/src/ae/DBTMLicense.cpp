// DBTMLicense.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DBTMLicense.h"


// CDBTMLicense-Dialogfeld

IMPLEMENT_DYNAMIC(CDBTMLicense, CDialog)
CDBTMLicense::CDBTMLicense(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBTMLicense::IDD, pParent)
{
    m_lDatum = 0;
    m_CBTMLicense = _T("");
    m_CT_Datum = 0;
}

CDBTMLicense::~CDBTMLicense()
{
}

void CDBTMLicense::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DT_BTM, m_DT_Datum);
    DDX_DateTimeCtrl(pDX, IDC_DT_BTM, m_CT_Datum);
    DDX_Control(pDX, IDC_EDIT_BTM_LICENSE, m_Edit_BTM_License);
    DDX_Text(pDX, IDC_EDIT_BTM_LICENSE, m_CBTMLicense);
}


BEGIN_MESSAGE_MAP(CDBTMLicense, CDialogMultiLang)
END_MESSAGE_MAP()


// CDBTMLicense-Meldungshandler
BOOL CDBTMLicense::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    if (m_lDatum == 0)
    {
        CTM zeit;
        zeit.Server(AafilGetdatetime);
        m_lDatum = zeit.s.DATUM;
    }

    CTime act = CTimeFromDateLongMinTime(m_lDatum);
    m_DT_Datum.SetTime(&act);
    m_CT_Datum = act;
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDBTMLicense::OnChangeEditBTMLicense()
{
    AllgLaengeKontr(&m_Edit_BTM_License, L_AUFTRAG_BTMFORMULARNR,AeGetApp()->Modus());
}

void CDBTMLicense::OnOK()
{
    UpdateData();

    //Anfangsinitialisierung durchfuehren
    if (m_CBTMLicense.IsEmpty())
    {
        MsgBoxOK(AETXT_NO_BTM_LICENSE);
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_BTM_LICENSE));
        return;
    }
    BeginWaitCursor();
    CAUFTRAG auftrag;
    auftrag.s.DATUMBTM = m_CT_Datum.GetYear()*10000
                 + m_CT_Datum.GetMonth()*100
                 + m_CT_Datum.GetDay();
    m_lDatum = auftrag.s.DATUMBTM;
    strcpy(auftrag.s.BTMFORMULARNR, m_CBTMLicense);
    auftrag.Server(AasrvSetBTMLicense, PIPE_AE_SRV);
    if (auftrag.rc < SRV_OK)
    {
        EndWaitCursor();
        return;
    }
    EndWaitCursor();
    CDialogMultiLang::OnOK();
}
