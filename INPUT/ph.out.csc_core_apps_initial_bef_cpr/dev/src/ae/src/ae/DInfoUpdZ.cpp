// DInfoUpdZ.cpp : implementation file
//

#include "stdafx.h"
#include "koplist.h"
#include "allg.h"
#include "DInfoUpdZ.h"

/////////////////////////////////////////////////////////////////////////////
// CDInfoUpd dialog


CDInfoUpd::CDInfoUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDInfoUpd::IDD, pParent)
{
    m_CInfoLokal = _T("");
}


void CDInfoUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_INFO_LOKAL, m_EditInfoLokal);
    DDX_Text(pDX, IDC_EDIT_INFO_LOKAL, m_CInfoLokal);
}


BEGIN_MESSAGE_MAP(CDInfoUpd, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDInfoUpd message handlers

void CDInfoUpd::OnOK()
{
    CKOPLIST koplist;
    UpdateData(TRUE);

    strcpy(koplist.s.BEMERKUNG,m_CInfoLokal);
    koplist.s.PZN = AeGetApp()->VzNr() * (-1);
    koplist.s.SATZNR = m_SatznrLokal;
    if (m_SatznrLokal == 0) koplist.Server(IftselIns_tellistt);
    else koplist.Server(IftselUpd_tellistt);

    CDialogMultiLang::OnOK();
}

BOOL CDInfoUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    CKOPLIST koplist;
    koplist.s.PZN = AeGetApp()->VzNr() * (-1);
    koplist.Server(IftselSel_info);
    if (koplist.rc == SRV_OK)
    {
        AllgEntfSpaces(koplist.s.BEMERKUNG);
        m_CInfoLokal = koplist.s.BEMERKUNG;
        m_SatznrLokal = koplist.s.SATZNR;
    }
    else
    {
        m_CInfoLokal = "\0";
        m_SatznrLokal = 0;
    }
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CDInfoUpdZ dialog


CDInfoUpdZ::CDInfoUpdZ(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDInfoUpdZ::IDD, pParent)
{
    m_CInfoZentral = _T("");
}


void CDInfoUpdZ::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_INFO_ZENTRAL, m_EditInfoZentral);
    DDX_Text(pDX, IDC_EDIT_INFO_ZENTRAL, m_CInfoZentral);
}


BEGIN_MESSAGE_MAP(CDInfoUpdZ, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDInfoUpdZ message handlers

void CDInfoUpdZ::OnOK()
{
    CKOPLIST koplist;
    UpdateData(TRUE);
    strcpy(koplist.s.BEMERKUNG,m_CInfoZentral);
    koplist.s.PZN = -1;
    koplist.s.SATZNR = m_SatznrZentral;
    if (m_SatznrZentral == 0) koplist.Server(IftselIns_tellistt);
    else koplist.Server(IftselUpd_tellistt);

    CDialogMultiLang::OnOK();
}

BOOL CDInfoUpdZ::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    CKOPLIST koplist;
    koplist.s.PZN = -1;
    koplist.Server(IftselSel_info);
    if (koplist.rc == SRV_OK)
    {
        AllgEntfSpaces(koplist.s.BEMERKUNG);
        m_CInfoZentral = koplist.s.BEMERKUNG;
        m_SatznrZentral = koplist.s.SATZNR;
    }
    else
    {
        m_CInfoZentral = "\0";
        m_SatznrZentral = 0;
    }
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
