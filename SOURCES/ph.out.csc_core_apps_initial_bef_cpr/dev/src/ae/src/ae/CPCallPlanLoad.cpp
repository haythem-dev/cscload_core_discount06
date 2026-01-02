// CPCallPlanLoad.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CPCallPlanLoad.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCPCallPlanLoad


CCPCallPlanLoad::CCPCallPlanLoad(CWnd* pParent /*=NULL*/
                                 , ppCallPlanLoad* psrvCallPlanLoad
                                 ,const int iFunktion)
    : CDialogMultiLang(CCPCallPlanLoad::IDD, pParent)
{
    m_csTimeTo = _T("");
    m_csTimeFrom = _T("");
    m_CTDate = 0;
    m_psrvCallPlanLoad = psrvCallPlanLoad;
    m_iInsert = 0;
    m_iFunktion = iFunktion;
    m_bIsChanged = false;
}

void CCPCallPlanLoad::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATE, m_DateCtl_Date);
    DDX_Control(pDX, IDC_EDIT_TOURID, m_EditTourid);
    DDX_Control(pDX, IDC_EDIT_ZEITBIS, m_EditZeitBis);
    DDX_Control(pDX, IDC_EDIT_ZEITVON, m_EditZeitVon);
    DDX_Control(pDX, IDC_COMBO_NDL, m_CComboBoxNdl);
    DDX_Control(pDX, IDC_COMBO_COUNTRY, m_CComboBoxCountry);
    DDX_Control(pDX, IDC_COMBO_DAY, m_CComboBoxDay);
    DDX_Text(pDX, IDC_EDIT_ZEITBIS, m_csTimeTo);
    DDX_Text(pDX, IDC_EDIT_ZEITVON, m_csTimeFrom);
    DDX_DateTimeCtrl(pDX, IDC_DATE, m_CTDate);
}


BEGIN_MESSAGE_MAP(CCPCallPlanLoad, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_ZEITBIS, OnChangeEditZeitbis)
    ON_EN_CHANGE(IDC_EDIT_ZEITVON, OnChangeEditZeitvon)
    ON_EN_CHANGE(IDC_EDIT_TOURID, OnChangeEditTourid)
    ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE, OnDatetimechangeDate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CCPCallPlanLoad


//--- OnInitDialog (Wizard)------------------------------------------------//

BOOL CCPCallPlanLoad::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_bIsChanged = false;
    GetDlgItem(IDC_STATIC_DATE)->SetWindowText(AeGetApp()->GetCurrentDate());
    InitializeCombos();
    if (m_iFunktion == 0)
    {
        MakeEditable();
    }
    else
    {
        InitEditable();
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

//--- OnOK (Wizard)-------------------------------------------------------//

void CCPCallPlanLoad::OnOK()
{
    if (!GetDataFromScreen())
        return;
    UpdateDay();
    return;
}

//--- OnCancel (Wizard)----------------------------------------------------//

void CCPCallPlanLoad::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

//--- OnButtonReset (Wizard)-----------------------------------------------//

void CCPCallPlanLoad::OnButtonReset()
{
    m_EditTourid.SetWindowText("0");
    m_CComboBoxNdl.SetCurSel(0);
    m_CComboBoxCountry.SetCurSel(0);
}

//--- (ClassWizard)OnChangeeditZeitvon--------------------------------//

void CCPCallPlanLoad::OnChangeEditZeitvon()
{
    UpdateData(TRUE);
    ppTime p(m_csTimeFrom, ppTime::display_hhmm, true);
    if (p.GetState() == ppTime::is_false)
    {
        MsgBoxOK( IDS_ERROR_INPUT);
    }

    m_csTimeFrom = p;
    UpdateData(FALSE);
    m_EditZeitVon.SetSel(p.GetPos(), p.GetPos(), FALSE);
}

//--- (ClassWizard)OnChangeeditZeitbis--------------------------------//

void CCPCallPlanLoad::OnChangeEditZeitbis()
{
    UpdateData(TRUE);
    ppTime p(m_csTimeTo, ppTime::display_hhmm, true);
    if (p.GetState() == ppTime::is_false)
    {
        MsgBoxOK( IDS_ERROR_INPUT);
    }

    m_csTimeTo = p;
    UpdateData(FALSE);
    m_EditZeitBis.SetSel(p.GetPos(), p.GetPos(), FALSE);
}

//--- (ClassWizard)OnChangeeditTourid-----------------------------------//

void CCPCallPlanLoad::OnChangeEditTourid()
{
    AllgWertKontr(&m_EditTourid, 475999);

    CString Str;
    GetDlgItem(IDC_EDIT_TOURID)->GetWindowText(Str);
    m_iTourid = atoi(Str);
    if (Str.GetLength() > 5)
    {
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_ZEITVON));
    }

}

//--- InitializeCombos ---------------------------------------------------------//

void CCPCallPlanLoad::InitializeCombos()
{
    //füllen Combobox mit Wochentagen
    m_CComboBoxDay.AddString(CResString::ex().getStrTblText(IDS_SHORT_SUNDAY));
    m_CComboBoxDay.AddString(CResString::ex().getStrTblText(IDS_SHORT_MONDAY));
    m_CComboBoxDay.AddString(CResString::ex().getStrTblText(IDS_SHORT_TUESDAY));
    m_CComboBoxDay.AddString(CResString::ex().getStrTblText(IDS_SHORT_WEDNESDAY));
    m_CComboBoxDay.AddString(CResString::ex().getStrTblText(IDS_SHORT_THURSDAY));
    m_CComboBoxDay.AddString(CResString::ex().getStrTblText(IDS_SHORT_FRIDAY));
    m_CComboBoxDay.AddString(CResString::ex().getStrTblText(IDS_SHORT_SATURDAY));

    //füllen Combobox mit Bundesländern
    m_CComboBoxCountry.AddString("");    //keine Vorgabe   //TO_DO
    m_CComboBoxCountry.AddString("BW");    //Baden-Würtemberg
    m_CComboBoxCountry.AddString("BY");    //Bayern
    m_CComboBoxCountry.AddString("BE");    //Berlin
    m_CComboBoxCountry.AddString("BB");    //Brandenburg
    m_CComboBoxCountry.AddString("HB");    //Bremen
    m_CComboBoxCountry.AddString("HH");    //Hamburg
    m_CComboBoxCountry.AddString("HE");    //Hessen
    m_CComboBoxCountry.AddString("MV");    //Mecklenburg-Vorpommern
    m_CComboBoxCountry.AddString("NI");    //Niedersachsen
    m_CComboBoxCountry.AddString("NW");    //Nordrhein-Westfalen
    m_CComboBoxCountry.AddString("RP");    //Rheinland-Pfalz
    m_CComboBoxCountry.AddString("SL");    //Saarland
    m_CComboBoxCountry.AddString("SN");    //Sachsen
    m_CComboBoxCountry.AddString("ST");    //Sachsen-Anhalt
    m_CComboBoxCountry.AddString("SH");    //Schleswig-Holstein
    m_CComboBoxCountry.AddString("TH");    //Thüringen
    m_CComboBoxCountry.SetCurSel(0);

    //füllen Combobox mit Niederlassungs-Nummern
    const std::vector<Filiale>& filialen = AeGetApp()->HoleFilialen();
    for (std::vector<Filiale>::const_iterator iter = filialen.begin(); iter != filialen.end(); ++iter)
    {
        CString csFiliale;
        csFiliale.Format("%02d", iter->RegionTeilNr);
        m_CComboBoxNdl.AddString(csFiliale);
    }
    m_CComboBoxNdl.SetCurSel(0);
}

//--- MakeEditable -----------------------------------------------------------//

void CCPCallPlanLoad::MakeEditable()
{
    CString vz;
    long datum = m_psrvCallPlanLoad->GetLadeDatum();
    m_CTDate = CTimeFromDateLongMinTime(datum);
    UpdateData(FALSE);

    m_CComboBoxDay.SetCurSel(m_psrvCallPlanLoad->GetWochenTag());
    GetDlgItem(IDC_EDIT_ZEITVON)->SetWindowText(m_psrvCallPlanLoad->GetLadeZeitAb());
    GetDlgItem(IDC_EDIT_ZEITBIS)->SetWindowText(m_psrvCallPlanLoad->GetLadeZeitBis());
    GetDlgItem(IDC_EDIT_TOURID)->SetWindowText(m_psrvCallPlanLoad->GetTourID());
    vz.Format("%02d", m_psrvCallPlanLoad->GetLadeVZ());
    m_CComboBoxNdl.SelectString(-1, vz);
    m_CComboBoxCountry.SelectString(-1, m_psrvCallPlanLoad->GetBundesLand());
}

//--- InitEditable -----------------------------------------------------------//

void CCPCallPlanLoad::InitEditable()
{
    char error[81];
    long datum = ppGAddDate(AeGetApp()->GetCurrentDate(), 1, error);
    m_CTDate = CTimeFromDateLongMinTime(datum);
    UpdateData(FALSE);
    m_CComboBoxDay.SetCurSel(m_CTDate.GetDayOfWeek()-1);
    GetDlgItem(IDC_EDIT_ZEITVON)->SetWindowText("00:00");
    GetDlgItem(IDC_EDIT_ZEITBIS)->SetWindowText("24:00");
    GetDlgItem(IDC_EDIT_TOURID)->SetWindowText("0");
}

//--- GetDataFromScreen ------------------------------------------------------//

bool CCPCallPlanLoad::GetDataFromScreen()
{
    CString cs;
    ppTime m_TimeBuf;
    ppDate m_DateBuf;
    UpdateData(TRUE);

    GetDlgItem(IDC_COMBO_DAY)->GetWindowText(cs);
    m_psrvCallPlanLoad->SetWochentag(static_cast<short>(m_CComboBoxDay.GetCurSel()) );

    GetDlgItem(IDC_COMBO_COUNTRY)->GetWindowText(cs);
    m_psrvCallPlanLoad->SetBundesland(cs);


    GetDlgItem(IDC_COMBO_NDL)->GetWindowText(cs);
    m_psrvCallPlanLoad->SetLadeVZ(static_cast<short>(atol(cs)));

    GetDlgItem(IDC_EDIT_ZEITVON)->GetWindowText(cs);
    m_TimeBuf.SetTime(cs);
    m_psrvCallPlanLoad->SetLadeZeitAb(m_TimeBuf);

    GetDlgItem(IDC_EDIT_ZEITBIS)->GetWindowText(cs);
    m_TimeBuf.SetTime(cs);
    m_psrvCallPlanLoad->SetLadeZeitBis(m_TimeBuf);

    cs.Format("%02d%02d%04d", m_CTDate.GetDay(), m_CTDate.GetMonth(), m_CTDate.GetYear());
    m_DateBuf.SetDate(cs);
    m_psrvCallPlanLoad->SetLadeDatum(m_DateBuf);

    GetDlgItem(IDC_EDIT_TOURID)->GetWindowText(cs);
    m_psrvCallPlanLoad->SetTourID(atol(cs));

    return true;
}

//--- Update single day --------------------------------//

void CCPCallPlanLoad::UpdateDay()
{
    BeginWaitCursor();
    if (m_iFunktion == 0)
    {
        if (!m_psrvCallPlanLoad->Update())
        {
            EndWaitCursor();
            MsgBoxOK(IDP_NOT_UPDATED);
            return;
        }
        EndWaitCursor();
        MsgBoxOK(IDP_UPDATED);
    }
    else
    {
        if (!m_psrvCallPlanLoad->Insert())
        {
            EndWaitCursor();
            MsgBoxOK(IDP_NOT_INSERTED);
            return;
        }
        EndWaitCursor();
        MsgBoxOK(IDP_INSERTED);
    }
    CDialogMultiLang::OnOK();
}

void CCPCallPlanLoad::OnDatetimechangeDate(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    CTime x;
    m_DateCtl_Date.GetTime(x);
    m_CComboBoxDay.SetCurSel(x.GetDayOfWeek() - 1);

    *pResult = 0L;
}
