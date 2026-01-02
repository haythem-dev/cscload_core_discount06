
//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCallPlanChangeData.cpp
   Author: A.Schmidt-Rehschuh/v.d.Grün
   made  : 19.04.2000

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "CPCallPlanChangeData.h"
#include <kndsel.h>
#include "DKndInf.h"

//----------------------------------------------------------------------------//
//--- public methodes --------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- SetIsInsert ------------------------------------------------------------//

void CCPCallPlanChangeData::SetIsInsert(const bool isInsert)
{
    m_bIsInsert = isInsert;
}

//--- SetIsDelete ------------------------------------------------------------//

void CCPCallPlanChangeData::SetIsDelete(const bool isDelete)
{
    m_bIsDelete = isDelete;
}

//--- SetIsDisable -----------------------------------------------------------//

void CCPCallPlanChangeData::SetIsDisable(const bool isDisable)
{
    m_bIsDisabled = isDisable;
}

//--- SetStockRunningTime ----------------------------------------------------//

void CCPCallPlanChangeData::SetStockRunningTimeExpress(const short iShortTime)
{
    m_iShortTime = iShortTime;
}

//--- SetStockRunningTime ----------------------------------------------------//

void CCPCallPlanChangeData::SetStockRunningTime(const short iNormalTime)
{
    m_iNormalTime = iNormalTime;
}

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CCPCallPlanChangeData::CCPCallPlanChangeData(ppCustomerCallPlan* pCustomerPlan,
                                             const ppDayType::t_day eDay,
                                             CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CCPCallPlanChangeData::IDD, pParent)
    , m_constTime(pCustomerPlan->GetUrRufzeit())
    , m_CInfo(_T(""))
{
    m_csTime = _T("");
    m_pCustomerPlan = pCustomerPlan;
    m_bIsInsert = false;
    m_bIsDelete = false;
    m_bIsDisabled = false;
    m_eDay = eDay;
    m_iShortTime = 20;
    m_iNormalTime = 40;
    m_pCustomerTour = new ppCustomerCallPlanTour(m_pCustomerPlan->GetCustomer());
}

//--- deconstructor ----------------------------------------------------------//

CCPCallPlanChangeData::~CCPCallPlanChangeData()
{
    if (m_pCustomerTour)
        delete m_pCustomerTour;
}

//--- DoDataExchange ---------------------------------------------------------//

void CCPCallPlanChangeData::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_MUSTCALL, m_CButtonMustCall);
    DDX_Control(pDX, IDC_CHECK_DISABLES, m_CButtonDisable);
    DDX_Control(pDX, IDC_EDIT_CALLTIME, m_CEditCalltime);
    DDX_Control(pDX, IDC_COMBO_POOLNO, m_CComboBoxPoolno);
    DDX_Control(pDX, IDC_COMBO_PRIORITY, m_CComboBoxPriority);
    DDX_Text(pDX, IDC_EDIT_CALLTIME, m_csTime);
    DDX_Text(pDX, IDC_EDIT_INFO, m_CInfo);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCPCallPlanChangeData, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_CALLTIME, OnChangeEditCalltime)
    ON_EN_KILLFOCUS(IDC_EDIT_CALLTIME, OnKillfocusEditCalltime)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCPCallPlanChangeData message handlers (ClassWizard) -------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCPCallPlanChangeData::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    InitializeCombos();
    SetHeader();
    if (m_bIsInsert)
        MakeInsertable();
    else
        MakeEditable();

    return TRUE;
}

//--- (ClassWizard)OnChangeEditCalltime --------------------------------------//

void CCPCallPlanChangeData::OnChangeEditCalltime()
{
    UpdateData(TRUE);
    ppTime p(m_csTime, ppTime::display_hhmm, true);
    if (p.GetState() == ppTime::is_false)
    {
        MsgBoxOK(IDS_ERROR_INPUT);
    }

    m_csTime = p;
    UpdateData(FALSE);
    m_CEditCalltime.SetSel(p.GetPos(), p.GetPos(), FALSE);
}

//--- (ClassWizard)OnKillfocusEditCalltime -----------------------------------//

void CCPCallPlanChangeData::OnKillfocusEditCalltime()
{
    CString cs;

    GetDlgItem(IDC_EDIT_CALLTIME)->GetWindowText(cs);
    ppTime Time(cs);

    m_pCustomerPlan->SetUrRufzeit(Time);
}

//--- (ClassWizard)OnOK ------------------------------------------------------//

void CCPCallPlanChangeData::OnOK()
{
    OnKillfocusEditCalltime();
    if (!CheckCallTime())
        return;

    if (m_bIsDisabled)
        m_pCustomerPlan->SetCallDisabled(m_CButtonDisable.GetCheck());
    else
        GetDataFromScreen();

    int iID = GetCheckedRadioButton(IDC_RADIO10, IDC_RADIO12); //one day, all days or all days without saturday

    if (m_bIsInsert)
    {
        if (!InsertPlanData(iID))
            return;
    }
    else if (m_bIsDelete)
    {
        if (!DeletePlanData(iID))
            return;
    }
    else
    {
        if (!UpdatePlanData(iID))
            return;
    }

    CDialogMultiLang::OnOK();
}


//--- (ClassWizard)OnCancel --------------------------------------------------//

void CCPCallPlanChangeData::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

//----------------------------------------------------------------------------//
//--- private methodes -------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- OnHookFkt --------------------------------------------------------------//

LRESULT CCPCallPlanChangeData::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        CKndInf dlgCustomerInfo;
        dlgCustomerInfo.SetKndNr(m_pCustomerPlan->GetCustomer()->GetKundenNr());
        dlgCustomerInfo.SetKndVz(m_pCustomerPlan->GetCustomer()->GetVertriebsZentrumNr());
        dlgCustomerInfo.DoModal();
        return 1L;
    }
    return 0L;
}

//--- SetHeader --------------------------------------------------------------//

void CCPCallPlanChangeData::SetHeader()
{
    if (m_bIsInsert)
    {
        SetWindowText(CResString::ex().getStrTblText(IDS_MASTERPL_NEW_SET));
    }
    else if (m_bIsDelete)
    {
        SetWindowText(CResString::ex().getStrTblText(IDS_MASTERPL_DEL_SET));
    }
    else
    {
        SetWindowText(CResString::ex().getStrTblText(IDS_MASTERPL_PFL_SET));
    }

    ppCustomerDisplay* pCustomer = (ppCustomerDisplay*)m_pCustomerPlan->GetCustomer();
    GetDlgItem(IDC_OUT_CUSTOMERNAME)->SetWindowText(pCustomer->GetNameInhaber());
    GetDlgItem(IDC_OUT_ZIPCODE)->SetWindowText(pCustomer->GetPostleitZahl());
    GetDlgItem(IDC_OUT_CITY)->SetWindowText(pCustomer->GetOrt());
    GetDlgItem(IDC_OUT_CUSTOMERID)->SetWindowText(ppString(pCustomer->GetIdfNr()).c_str());
    GetDlgItem(IDC_OUT_PHARMACY)->SetWindowText(pCustomer->GetNameApo());
    GetDlgItem(IDC_OUT_STREET)->SetWindowText(pCustomer->GetStrasse());
    GetDlgItem(IDC_OUT_SALECENTER)->SetWindowText(ppString((long)pCustomer->GetVertriebsZentrumNr()).c_str());
    GetDlgItem(IDC_OUT_SALECENTERNAME)->SetWindowText(AeGetApp()->FilialName());
}

//--- MakeEditable -----------------------------------------------------------//

void CCPCallPlanChangeData::MakeEditable()
{
    ppString strCallTime = (long)m_pCustomerPlan->GetRufSteuerung();
    m_CComboBoxPriority.SetCurSel(m_CComboBoxPriority.FindString(0, strCallTime.c_str()));
    m_CComboBoxPoolno.SetCurSel(m_pCustomerPlan->GetPoolNr());
    GetDlgItem(IDC_EDIT_CALLTIME)->SetWindowText(ppString(m_pCustomerPlan->GetUrRufzeit()).c_str());
    GetDlgItem(IDC_EDIT_INFO)->SetWindowText(m_pCustomerPlan->GetBemerkung());

    m_CButtonMustCall.SetCheck(m_pCustomerPlan->GetSkdAnrufGenerell());

//  vorbesetzen Rufart mit Wert aus DB-Tabelle
    UINT iIDRadio = IDC_RADIO13;

    if (m_pCustomerPlan->GetNormalCall())
        iIDRadio = IDC_RADIO13;
    if (m_pCustomerPlan->GetDoNotCall())
        iIDRadio = IDC_RADIO14;
    if (m_pCustomerPlan->GetSpecialCall())
        iIDRadio = IDC_RADIO15;

    CheckRadioButton(IDC_RADIO13, IDC_RADIO15, iIDRadio);

//  vorbesetzen Gültigkeitszeitraum der Änderung mit: "Tag"
    CheckRadioButton( IDC_RADIO10,IDC_RADIO12, IDC_RADIO10 );
    m_CButtonDisable.SetCheck(m_pCustomerPlan->GetCallDisabled());
    m_CButtonDisable.EnableWindow(FALSE);

    if (m_bIsDelete || m_bIsDisabled)
    {
        m_CComboBoxPriority.EnableWindow(FALSE);
        m_CComboBoxPoolno.EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_CALLTIME)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO13)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO14)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO15)->EnableWindow(FALSE);
        m_CButtonMustCall.EnableWindow(FALSE);
        if (m_bIsDisabled)
        {
            //hier machen wir den umkehrschwung damit man nur noch mit return bestätigen muss
            m_CButtonDisable.EnableWindow(TRUE);
            CheckRadioButton(IDC_RADIO10, IDC_RADIO12, IDC_RADIO11);
            m_CButtonDisable.SetCheck(m_pCustomerPlan->GetCallDisabled() ? FALSE : TRUE);
        }
    }
}


//--- MakeInsertable -----------------------------------------------------------//

void CCPCallPlanChangeData::MakeInsertable()
{
    CString cs;
    GetDlgItem(IDC_EDIT_CALLTIME)->SetWindowText(cs);

    CheckRadioButton(IDC_RADIO13, IDC_RADIO15, IDC_RADIO13); //  vorbesetzen Rufart mit "Normalruf"
    CheckRadioButton(IDC_RADIO10, IDC_RADIO12, IDC_RADIO12); //  vorbesetzen Gültigkeitszeitraum "Tag"
    GetDlgItem(IDC_STATIC_INFO)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_INFO)->ShowWindow(SW_HIDE);

    m_CComboBoxPriority.SetCurSel(m_CComboBoxPriority.FindString(0, m_pCustomerPlan->GetCallInit()));
    m_CComboBoxPoolno.SetCurSel(m_CComboBoxPoolno.FindString(0, "00"));
}


//--- InitializeCombos ---------------------------------------------------------//

void CCPCallPlanChangeData::InitializeCombos()
{
    CString cs;
    ppString strCallText;

    while (m_pCustomerPlan->GetListCallControl(strCallText))
    {
        m_CComboBoxPriority.AddString(strCallText);
    }

    for (int j = 0; j < 99; j++)
    {
        cs.Format("%02d", j);
        m_CComboBoxPoolno.AddString(cs);
    }
}

//--- GetDataFromScreen ------------------------------------------------------//

void CCPCallPlanChangeData::GetDataFromScreen()
{
    CString cs;

    GetDlgItem(IDC_COMBO_PRIORITY)->GetWindowText(cs);
    m_pCustomerPlan->SetRufSteuerung((ppCustomerCallPlan::t_calltime)atoi(cs));
    GetDlgItem(IDC_COMBO_POOLNO)->GetWindowText(cs);
    m_pCustomerPlan->SetPoolNr(static_cast<short>(atoi(cs)));
    GetDlgItem(IDC_EDIT_INFO)->GetWindowText(cs);
    m_pCustomerPlan->SetBemerkung(cs);

    m_pCustomerPlan->SetRufProtokoll(ppCustomerCallPlan::r_phonetic);

    switch (GetCheckedRadioButton(IDC_RADIO13, IDC_RADIO15))
    {
        case IDC_RADIO13:
            m_pCustomerPlan->SetNormalCall(true);
            break;
        case IDC_RADIO14:
            m_pCustomerPlan->SetDoNotCall(true);
            break;
        case IDC_RADIO15:
            m_pCustomerPlan->SetSpecialCall(true);
            break;
        default:
            break;
    }

    m_pCustomerPlan->SetCallDisabled(m_CButtonDisable.GetCheck()); //only importent by insert!

    cs = "";
    m_pCustomerPlan->SetTourID(cs);
    m_pCustomerPlan->SetSkdAnrufGenerell(m_CButtonMustCall.GetCheck());
}

//--- DeleteData -------------------------------------------------------------//

bool CCPCallPlanChangeData::DeletePlanData(const UINT iID)
{
    if (MsgBoxYesNo(IDP_LOESCHEN_JA) != IDYES)
    {
        CDialogMultiLang::OnCancel();
        return false;
    }

    switch (iID)
    {
        case IDC_RADIO10:
            return DelSingleDay();
        case IDC_RADIO11:
            return DelAllDays();
        case IDC_RADIO12:
            return DelWithoutSaturday();
        default:
        {
            ppString strTxt((long)iID);
            strTxt += ": ID notfound";
            MsgBoxOK(strTxt.c_str());
            break;
        }
    }
    return false;
}

//--- InsertData -------------------------------------------------------------//

bool CCPCallPlanChangeData::InsertPlanData(const UINT iID)
{
    switch (iID)
    {
        case IDC_RADIO10:
            return InsSingleDay();
        case IDC_RADIO11:
            return InsAllDays();
        case IDC_RADIO12:
            return InsWithoutSaturday();
        default:
        {
            ppString strTxt((long)iID);
            strTxt += ": ID notfound";
            MsgBoxOK(strTxt.c_str());
            break;
        }
    }
    return false;
}

//--- UpdatetData -------------------------------------------------------------//

bool CCPCallPlanChangeData::UpdatePlanData(const UINT iID)
{
    switch (iID)
    {
        case IDC_RADIO10:
            return UpdSingleDay();
        case IDC_RADIO11:
            return UpdAllDays();
        case IDC_RADIO12:
            return UpdWithoutSaturday();
        default:
        {
            ppString strTxt((long)iID);
            strTxt += ": ID notfound";
            MsgBoxOK(strTxt.c_str());
            break;
        }
    }
    return false;
}

//--- CheckCallTime ----------------------------------------------------------//

bool CCPCallPlanChangeData::CheckCallTime()
{
    CString Str;

    GetDlgItem(IDC_EDIT_CALLTIME)->GetWindowText(Str);
    ppTime CallTime(Str);
    if (CallTime.is_null())
    {
        MsgBoxOK(IDP_CALLTIME_REQUIRED);
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_CALLTIME));
        return false;
    }

    return true;
}

//--- Update single day ------------------------------------------------------//

bool CCPCallPlanChangeData::UpdSingleDay()
{
    BeginWaitCursor();
    m_pCustomerPlan->SetOldTime(m_constTime == m_pCustomerPlan->GetUrRufzeit() ? 0 : m_constTime);
    if (!m_pCustomerPlan->Update())
    {
        MsgBoxOK(m_pCustomerPlan->GetErrorMsg());
        EndWaitCursor();
        return false;
    }
    EndWaitCursor();
    return true;
}

//--- Update all days (saturday included) -----------//

bool CCPCallPlanChangeData::UpdAllDays()
{
    BeginWaitCursor();
    m_pCustomerPlan->SetOldTime(m_constTime == m_pCustomerPlan->GetUrRufzeit() ? 0 : m_constTime);
    if (!m_pCustomerPlan->UpdateGeneral())
    {
        MsgBoxOK(m_pCustomerPlan->GetErrorMsg());
        EndWaitCursor();
        return false;
    }
    EndWaitCursor();
    return true;
}

//--- Update all days without saturday ----------//

bool CCPCallPlanChangeData::UpdWithoutSaturday()
{
    BeginWaitCursor();
    m_pCustomerPlan->SetOldTime(m_constTime == m_pCustomerPlan->GetUrRufzeit() ? 0 : m_constTime);
    if (!m_pCustomerPlan->UpdateGeneralWithoutSaturday())
    {
        MsgBoxOK(m_pCustomerPlan->GetErrorMsg());
        EndWaitCursor();
        return false;
    }
    EndWaitCursor();
    return true;
}

//--- InsSingleDay -----------------------------------------------------------//

bool CCPCallPlanChangeData::InsSingleDay()
{
    BeginWaitCursor();
    if (!m_pCustomerPlan->Insert())
    {
        MsgBoxOK(m_pCustomerPlan->GetErrorMsg());
        EndWaitCursor();
        return false;
    }
    EndWaitCursor();
    return true;
}

//--- InsAllDays -------------------------------------------------------------//

bool CCPCallPlanChangeData::InsAllDays()
{
    BeginWaitCursor();
    if (!m_pCustomerPlan->InsertGeneral())
    {
        MsgBoxOK(m_pCustomerPlan->GetErrorMsg());
        EndWaitCursor();
        return false;
    }
    EndWaitCursor();
    return true;
}

//--- InsWithoutSaturday -----------------------------------------------------//

bool CCPCallPlanChangeData::InsWithoutSaturday()
{
    BeginWaitCursor();
    if (!m_pCustomerPlan->InsertGeneralWithoutSaturday())
    {
        MsgBoxOK(m_pCustomerPlan->GetErrorMsg());
        EndWaitCursor();
        return false;
    }
    EndWaitCursor();
    return true;
}

//--- DelSingleDay -----------------------------------------------------------//

bool CCPCallPlanChangeData::DelSingleDay()
{
    BeginWaitCursor();

    if (!m_pCustomerPlan->Delete())
    {
        MsgBoxOK(m_pCustomerPlan->GetErrorMsg());
        EndWaitCursor();
        return false;
    }
    EndWaitCursor();
    return true;
}

//--- DelAllDays -------------------------------------------------------------//

bool CCPCallPlanChangeData::DelAllDays()
{
    BeginWaitCursor();

    if (!m_pCustomerPlan->DeleteGeneral())
    {
        MsgBoxOK(m_pCustomerPlan->GetErrorMsg());
        EndWaitCursor();
        return false;
    }
    EndWaitCursor();
    return true;
}

//--- DelWithoutSaturday -----------------------------------------------------//

bool CCPCallPlanChangeData::DelWithoutSaturday()
{
    BeginWaitCursor();
    if (!m_pCustomerPlan->DeleteGeneralWithoutSaturday())
    {
        MsgBoxOK(m_pCustomerPlan->GetErrorMsg());
        EndWaitCursor();
        return false;
    }
    EndWaitCursor();
    return true;
}
