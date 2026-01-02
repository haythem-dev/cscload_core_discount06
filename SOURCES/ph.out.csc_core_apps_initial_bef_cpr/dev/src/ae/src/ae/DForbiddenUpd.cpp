// DForbiddenUpd.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <controlling.h>
#include "DForbiddenUpd.h"


// CDForbiddenUpd-Dialogfeld

IMPLEMENT_DYNAMIC(CDForbiddenUpd, CDialog)
CDForbiddenUpd::CDForbiddenUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDForbiddenUpd::IDD, pParent)
    , m_CWord(_T(""))
    , m_CT_From(0)
    , m_CT_To(0)
{
    m_lDateFrom = 0;
    m_lDateTo = 0;
    m_iFunktion = 0;
}

CDForbiddenUpd::~CDForbiddenUpd()
{
}

void CDForbiddenUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_WORD, m_edit_Word);
    DDX_Text(pDX, IDC_EDIT_WORD, m_CWord);
    DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_DT_From);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_CT_From);
    DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_DT_To);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_CT_To);
}


BEGIN_MESSAGE_MAP(CDForbiddenUpd, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_EN_CHANGE(IDC_EDIT_WORD, OnEnChangeEditWord)
END_MESSAGE_MAP()


// CDForbiddenUpd-Meldungshandler

BOOL CDForbiddenUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    char error_msg[81];
    if (m_lDateFrom == 0)
    {
        CTM zeit;
        zeit.Server(AafilGetdatetime);
        m_lDateFrom = zeit.s.DATUM;
        m_lDateTo = AllgAddDate(zeit.s.DATUM,1,error_msg);
        m_iFunktion = 1;    //insert
        m_edit_Word.EnableWindow(TRUE);
    }
    else
    {
        m_edit_Word.EnableWindow(FALSE);
    }

    CTime von = CTimeFromDateLongAndHour(1, m_lDateFrom);
    m_DT_From.SetTime(&von);
    CTime bis = CTimeFromDateLongAndHour(1, m_lDateTo);
    m_DT_To.SetTime(&bis);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDForbiddenUpd::OnBnClickedOk()
{
    UpdateData();
    if (m_CT_From.GetTime() > m_CT_To.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_FROM));
        return;
    }
    if (m_CWord.IsEmpty())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(AETXT_WORT_EINGEB));
        return;
    }
    CFORBIDDENWORDS forbiddenwords;
    forbiddenwords.SetBranchno(AeGetApp()->VzNr());
    forbiddenwords.SetForbiddenword(m_CWord);
    forbiddenwords.SetDatefrom(m_CT_From.GetYear() * 10000
                + m_CT_From.GetMonth() * 100
                + m_CT_From.GetDay());
    forbiddenwords.SetDateto(m_CT_To.GetYear() * 10000
              + m_CT_To.GetMonth() * 100
              + m_CT_To.GetDay());

    if (m_iFunktion == 1)
    {
        if (!forbiddenwords.Insert())
        {
            MsgBoxOK(IDP_INSERTED);
        }
        else
        {
            MsgBoxOK(IDP_NOT_INSERTED);
            return;
        }
    }
    else
    {
        if (!forbiddenwords.UpdateWord())
        {
            MsgBoxOK(IDS_SET_CHANGED);
        }
        else
        {
            MsgBoxOK(IDP_NOT_UPDATED);
            return;
        }
    }
    CDialogMultiLang::OnOK();
}

void CDForbiddenUpd::OnEnChangeEditWord()
{
    AllgLaengeKontr(&m_edit_Word, L_FORBIDDENWORDS_FORBIDDENWORD, AeGetApp()->Modus());
}
