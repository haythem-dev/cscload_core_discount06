// DRabattOrder.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "rabattorder.h"
#include "DRabattOrder.h"
#include "DRODefine.h"


// CDRabattOrder-Dialogfeld

IMPLEMENT_DYNAMIC(CDRabattOrder, CDialog)
CDRabattOrder::CDRabattOrder(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDRabattOrder::IDD, pParent)
{
    m_CT_DatumBis = 0;
    m_CT_DatumVon = 0;
}

CDRabattOrder::~CDRabattOrder()
{
}

void CDRabattOrder::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATETIMEPICKER_VON, m_DT_DatumVon);
    DDX_Control(pDX, IDC_DATETIMEPICKER_BIS, m_DT_DatumBis);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIS, m_CT_DatumBis);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_VON, m_CT_DatumVon);
    DDX_Control(pDX, IDC_CHECK_KETTE, m_CheckKette);
}

BEGIN_MESSAGE_MAP(CDRabattOrder, CDialogMultiLang)
END_MESSAGE_MAP()


// CDRabattOrder-Meldungshandler

BOOL CDRabattOrder::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    CTime end = CTimeFromDateLongMinTime(zeit.s.DATUM);
    CTimeSpan y(3600, 0, 0, 0);
    CTime ctime = end - y;
    CTime anf(zeit.s.DATUM / 10000
            , zeit.s.DATUM / 100 % 100
            , 1
            , 0, 0, 0);
    m_DT_DatumVon.SetRange(&ctime, &end);
    m_DT_DatumVon.SetTime(&anf);
    m_DT_DatumBis.SetRange(&ctime, &end);
    m_DT_DatumBis.SetTime(&end);
    CenterWindow();
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDRabattOrder::OnOK()
{
    UpdateData();
    if (m_CT_DatumVon.GetTime() > m_CT_DatumBis.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_VON));
        return;
    }
    CRABATTORDER rb;
    rb.SetDatefrom(m_CT_DatumVon.GetYear() * 10000 +
                   m_CT_DatumVon.GetMonth() * 100 +
                   m_CT_DatumVon.GetDay());
    rb.SetDateto(m_CT_DatumBis.GetYear() * 10000 +
                 m_CT_DatumBis.GetMonth() * 100 +
                 m_CT_DatumBis.GetDay());
    rb.SetSwchain(IsDlgButtonChecked(IDC_CHECK_KETTE) ? 1 : 0);

    BeginWaitCursor();
    int rc = rc = rb.Server(AasrvSetROParam, PIPE_AE_SRV);
    if (rc) //Rabatt-Auftragsparameter setzen
    {
        EndWaitCursor();
        return;
    }
    else
    {
        EndWaitCursor();
        CDRODefine dlgRODefine;
        dlgRODefine.m_cVon.Format("%02d.%02d.%04d",
                    m_CT_DatumVon.GetDay(),
                    m_CT_DatumVon.GetMonth(),
                    m_CT_DatumVon.GetYear());
        dlgRODefine.m_cBis.Format("%02d.%02d.%04d",
                    m_CT_DatumBis.GetDay(),
                    m_CT_DatumBis.GetMonth(),
                    m_CT_DatumBis.GetYear());
        if (dlgRODefine.DoModal() == IDCANCEL)
        {
            rb.Server(AasrvClearROParam, PIPE_AE_SRV); //Rabatt-Auftragsparameter freigeben
            CDialogMultiLang::OnCancel();
            return;
        }
        rb.Server(AasrvConfirmRO, PIPE_AE_SRV); //Rabatt-Auftragsparameter auf db schreiben
    }
    CDialogMultiLang::OnOK();
}

void CDRabattOrder::OnCancel()
{
    CRABATTORDER rb;
    rb.Server(AasrvClearROParam, PIPE_AE_SRV); //Rabatt-Auftragsparameter loeschen

    CDialogMultiLang::OnCancel();
}
