// DAeUpdFeiertage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <phodate.h>
#include <fscincl.h>
#include "DAeUpdFeiertage.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeUpdFeiertage


CDAeUpdFeiertage::CDAeUpdFeiertage(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeUpdFeiertage::IDD, pParent)
{
    m_Datum = 0;
    m_csBisJahr = _T("");
    m_csVonJahr = _T("");
    m_csName = _T("");
    m_sModus = 0;
    m_sDatum = 0;
}


void CDAeUpdFeiertage::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, m_Combo_Modus);
    DDX_Control(pDX, IDC_EDIT_NAME, m_edit_Name);
    DDX_Control(pDX, IDC_EDIT_VON_JAHR, m_edit_VonJahr);
    DDX_Control(pDX, IDC_EDIT_BIS_JAHR, m_edit_BisJahr);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Datum);
    DDX_Text(pDX, IDC_EDIT_BIS_JAHR, m_csBisJahr);
    DDX_Text(pDX, IDC_EDIT_VON_JAHR, m_csVonJahr);
    DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
}


BEGIN_MESSAGE_MAP(CDAeUpdFeiertage, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_VON_JAHR, OnChangeEditVonJahr)
    ON_EN_CHANGE(IDC_EDIT_BIS_JAHR, OnChangeEditBisJahr)
    ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDAeUpdFeiertage

BOOL CDAeUpdFeiertage::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_zeit.Server(AafilGetdatetime);
    m_Combo_Modus.AddString(CResString::ex().getStrTblText(AETXT_FEIERTAG0));
    m_Combo_Modus.AddString(CResString::ex().getStrTblText(AETXT_FEIERTAG1));
    m_Combo_Modus.AddString(CResString::ex().getStrTblText(AETXT_FEIERTAG2));
    m_Combo_Modus.SetCurSel(m_sModus);

    if (m_sModus == 0)
    {
        if (m_sDatum == 0)
        {
            m_Datum = CTimeFromDateLong(0, 0, 0, m_zeit.s.DATUM, 0);
        }
        else
        {
            m_Datum = CTime(m_zeit.s.DATUM/10000, m_sDatum/100, m_sDatum%100, 0, 0, 0, 0);
        }
    }
    else if (m_sModus == 1)
    {
        if (m_sDatum < 0)
        {
            CTimeSpan y(((long)m_sDatum * -1), 0, 0, 0);
            m_Datum = GetEastern(m_zeit.s.DATUM) - (y);
        }
        else
        {
            CTimeSpan y(((long)m_sDatum), 0, 0, 0);
            m_Datum = GetEastern(m_zeit.s.DATUM) + (y);
        }
    }
    else
    {
        long diff;
        CTime x(m_zeit.s.DATUM/10000, m_sDatum/100, 1, 0, 0, 0, 0);
        if ((diff = x.GetDayOfWeek() - 2) < 0) diff += 7;
        if ((diff = (m_sDatum%10) - diff) < 0) diff += 7;
        diff += ((m_sDatum / 10 % 10) - 1) * 7;
        CTimeSpan y(diff, 0, 0, 0);
        m_Datum = x + (y);
    }
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDAeUpdFeiertage::OnOK()
{
    UpdateData(TRUE);
    if (m_csName.IsEmpty())
    {
        MsgBoxOK(IDP_FEIERTAG_NAME);
        return;
    }
    m_sModus = static_cast<short>(m_Combo_Modus.GetCurSel());
    if (m_sModus == 0)
    {
        m_sDatum = static_cast<short>((m_Datum.GetMonth()*100) + m_Datum.GetDay());
    }
    else if (m_sModus == 1)
    {
        CTimeSpan y(m_Datum - GetEastern(m_zeit.s.DATUM));
        m_sDatum = (short)y.GetDays();
    }
    else
    {
        int day;
        if ((day = m_Datum.GetDayOfWeek()-2) < 0)
        {
            day = 6;
        }
        m_sDatum = static_cast<short>( (m_Datum.GetMonth()*100)
            + ((((m_Datum.GetDay() - 1) / 7) + 1) * 10)
            + day );
    }
    CDialogMultiLang::OnOK();
}

void CDAeUpdFeiertage::OnChangeEditVonJahr()
{
    AllgWertKontr(&m_edit_VonJahr, MAXIMUM_ZEIT);
}

void CDAeUpdFeiertage::OnChangeEditBisJahr()
{
    AllgWertKontr(&m_edit_BisJahr, MAXIMUM_ZEIT);
}

void CDAeUpdFeiertage::OnChangeEditName()
{
    AllgLaengeKontr(&m_edit_Name, 20, AeGetApp()->Modus());
}
