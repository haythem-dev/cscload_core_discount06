#include "stdafx.h"
#include "MainFrm.h"
#include <sstream>
#include <iomanip>
#include <time.h>
#include "allg.h"
#include <param.h>
#include "DOrderPeriodChg.h"
#include "DataTypeHelper.h"
#include "DataQueryHelper.h"
#include <vector>

IMPLEMENT_DYNAMIC(CDOrderPeriodChg, CDialog)

CDOrderPeriodChg::CDOrderPeriodChg(MASKTYPE maskType, OrderPeriodData data, CWnd* pParent) : CDialogMultiLang(CDOrderPeriodChg::IDD, pParent)
{
    this->data = data;
    this->maskType = maskType;
    this->periodMisMatch = false;
    this->dateTimeChanged = false;
}

CDOrderPeriodChg::~CDOrderPeriodChg()
{
}

void CDOrderPeriodChg::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_TXT_IDFNO, this->txtIdfNo );
    DDX_Control(pDX, IDC_DTP_FROMTIME, this->dtpFromTime );
    DDX_Control(pDX, IDC_DTP_TILLTIME, this->dtpTillTime );
    DDX_Control(pDX, IDC_DTP_MAINTIME, this->dtpMainTime );

    DDX_Control(pDX, IDC_BTN_CHANGE_DATA, this->btnChangeData );
    DDX_Control(pDX, IDC_BTN_CANCEL, this->btnCancel );

    DDX_Control(pDX, IDC_CHK_MONDAY, this->chkMonday);
    DDX_Control(pDX, IDC_CHK_TUESDAY, this->chkTuesday);
    DDX_Control(pDX, IDC_CHK_WEDNESDAY, this->chkWednesday);
    DDX_Control(pDX, IDC_CHK_THURSDAY, this->chkThursday);
    DDX_Control(pDX, IDC_CHK_FRIDAY, this->chkFriday);
    DDX_Control(pDX, IDC_CHK_SATURDAY, this->chkSaturday);
    DDX_Control(pDX, IDC_CHK_SUNDAY, this->chkSunday);

    DDX_Control(pDX, IDC_GBC_SEARCH, this->cgbSearch);
    DDX_Control(pDX, IDC_GBC_ORDERPERIODTIME, this->cgbOrderPeriod);
    DDX_Control(pDX, IDC_GBC_WEEKDAY, this->cgbDays);
    DDX_Control(pDX, IDC_GBC_ORDER_TOUR_CLOSE_TIMES, this->cgbOrderTourCloseTimes);

    DDX_Control(pDX, IDC_CMB_TOURID, this->cmbTourID );

    DDX_Control(pDX, IDC_LBL_ORDERPERIOD, this->lblOrderPeriod );
    DDX_Control(pDX, IDC_LBL_IDFNO, this->lblIdfNo );
    DDX_Control(pDX, IDC_LBL_TOURID, this->lblTourID );
    DDX_Control(pDX, IDC_LBL_FROM, this->lblFrom );
    DDX_Control(pDX, IDC_LBL_TILL, this->lblTill );
    DDX_Control(pDX, IDC_LBL_MAIN_TIME, this->lblMainTime );

    DDX_Control(pDX, IDC_LBL_CONSTIME1, this->lblConsTime1);
    DDX_Control(pDX, IDC_LBL_CONSTIME2, this->lblConsTime2);
    DDX_Control(pDX, IDC_LBL_CONSTIME3, this->lblConsTime3);

    DDX_Control(pDX, IDC_LBL_MONDAY_ACTIVE, this->lblMonday);
    DDX_Control(pDX, IDC_LBL_TUESDAY_ACTIVE, this->lblTuesday);
    DDX_Control(pDX, IDC_LBL_WEDNESDAY_ACTIVE, this->lblWednesday);
    DDX_Control(pDX, IDC_LBL_THURSDAY_ACTIVE, this->lblThursday);
    DDX_Control(pDX, IDC_LBL_FRIDAY_ACTIVE, this->lblFriday);
    DDX_Control(pDX, IDC_LBL_SATURDAY_ACTIVE, this->lblSaturday);
    DDX_Control(pDX, IDC_LBL_SUNDAY_ACTIVE, this->lblSunday);

    CDialogMultiLang::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDOrderPeriodChg, CDialogMultiLang)
    ON_EN_KILLFOCUS(IDC_TXT_IDFNO, OnIdfInputFinished)
    ON_CBN_SELENDOK(IDC_CMB_TOURID, OnTourInputFinished)
    ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnClickedCancel)
    ON_BN_CLICKED(IDC_BTN_CHANGE_DATA, OnBtnClickedFinishInput)
    ON_BN_CLICKED(IDC_CHK_MONDAY, OnBtnClickedDay)
    ON_BN_CLICKED(IDC_CHK_TUESDAY, OnBtnClickedDay)
    ON_BN_CLICKED(IDC_CHK_WEDNESDAY, OnBtnClickedDay)
    ON_BN_CLICKED(IDC_CHK_THURSDAY, OnBtnClickedDay)
    ON_BN_CLICKED(IDC_CHK_FRIDAY, OnBtnClickedDay)
    ON_BN_CLICKED(IDC_CHK_SATURDAY, OnBtnClickedDay)
    ON_BN_CLICKED(IDC_CHK_SUNDAY, OnBtnClickedDay)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTP_FROMTIME, OnTimeChanged)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTP_TILLTIME, OnTimeChanged)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTP_MAINTIME, OnTimeChanged)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


void CDOrderPeriodChg::SetButtonStyles()
{
    this->chkMonday.SetButtonStyle(BS_AUTOCHECKBOX);
    this->chkTuesday.SetButtonStyle(BS_AUTOCHECKBOX);
    this->chkWednesday.SetButtonStyle(BS_AUTOCHECKBOX);
    this->chkThursday.SetButtonStyle(BS_AUTOCHECKBOX);
    this->chkFriday.SetButtonStyle(BS_AUTOCHECKBOX);
    this->chkSaturday.SetButtonStyle(BS_AUTOCHECKBOX);
    this->chkSunday.SetButtonStyle(BS_AUTOCHECKBOX);

    this->cgbSearch.SetButtonStyle(BS_GROUPBOX);
    this->cgbOrderPeriod.SetButtonStyle(BS_GROUPBOX);
    this->cgbDays.SetButtonStyle(BS_GROUPBOX);
    this->cgbOrderTourCloseTimes.SetButtonStyle(BS_GROUPBOX);
}


void CDOrderPeriodChg::SetTranslations()
{
    this->lblOrderPeriod.SetWindowText(CResString::ex().getStrTblText(AETXT_ORDERPERIOD));
    this->lblIdfNo.SetWindowText(CResString::ex().getStrTblText(AETXT_IDF_NUMMER));
    this->lblTourID.SetWindowText(CResString::ex().getStrTblText(AETXT_TOURID));
    this->lblFrom.SetWindowText(CResString::ex().getStrTblText(AETXT_VON));
    this->lblTill.SetWindowText(CResString::ex().getStrTblText(AETXT_BIS));
    this->lblMainTime.SetWindowText(CResString::ex().getStrTblText(AETXT_MAIN_TIME));

    this->chkMonday.SetWindowText(CResString::ex().getStrTblText(IDS_MONDAY));
    this->chkTuesday.SetWindowText(CResString::ex().getStrTblText(IDS_TUESDAY));
    this->chkWednesday.SetWindowText(CResString::ex().getStrTblText(IDS_WEDNESDAY));
    this->chkThursday.SetWindowText(CResString::ex().getStrTblText(IDS_THURSDAY));
    this->chkFriday.SetWindowText(CResString::ex().getStrTblText(IDS_FRIDAY));
    this->chkSaturday.SetWindowText(CResString::ex().getStrTblText(IDS_SATURDAY));
    this->chkSunday.SetWindowText(CResString::ex().getStrTblText(IDS_SUNDAY));

    this->cgbSearch.SetWindowText(CResString::ex().getStrTblText(AETXT_SEARCH));
    this->cgbOrderPeriod.SetWindowText(CResString::ex().getStrTblText(AETXT_ORDERPERIODTIME));
    this->cgbDays.SetWindowText(CResString::ex().getStrTblText(AETXT_WEEKDAY));
    this->cgbOrderTourCloseTimes.SetWindowText(CResString::ex().getStrTblText(AETXT_CLOSETIME));
}

void CDOrderPeriodChg::InitWeekdayList()
{
    this->weekList.push_back(Weekday(Weekday::SUNDAY, false, 0));
    this->weekList.push_back(Weekday(Weekday::MONDAY, false, 0));
    this->weekList.push_back(Weekday(Weekday::TUESDAY, false, 0));
    this->weekList.push_back(Weekday(Weekday::WEDNESDAY, false, 0));
    this->weekList.push_back(Weekday(Weekday::THURSDAY, false, 0));
    this->weekList.push_back(Weekday(Weekday::FRIDAY, false, 0));
    this->weekList.push_back(Weekday(Weekday::SATURDAY, false, 0));
}

BOOL CDOrderPeriodChg::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    this->SetButtonStyles();

    this->InitWeekdayList();

    this->dtpFromTime.SetFormat("HH:mm");
    this->dtpTillTime.SetFormat("HH:mm");
    this->dtpMainTime.SetFormat("HH:mm");

    time_t currentTime;
    time(&currentTime);
    CTime curTime(currentTime);

    //init with zero time instead of the standart actual time the control uses
    CTime fromTimeZero(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), 0, 0, 0);
    CTime toTimeZero(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), 0, 0, 0);
    this->dtpFromTime.SetTime(&fromTimeZero);
    this->dtpTillTime.SetTime(&toTimeZero);
    this->dtpMainTime.SetTime(&toTimeZero);

    if (maskType == CHANGE)
    {
        this->txtIdfNo.SetWindowText(data.getIdfNo());
        this->OnIdfInputFinished();

        this->cmbTourID.SelectString(0,data.getTourID());

        this->lblConsTime1.SetWindowText(data.getConsTime(0));
        this->lblConsTime2.SetWindowText(data.getConsTime(1));
        this->lblConsTime3.SetWindowText(data.getConsTime(2));

        CTime fromTime(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), atoi(data.getFromTime().Mid(0, 2)), atoi(data.getFromTime().Mid(3, 2)), 0);
        CTime tillTime(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), atoi(data.getToTime().Mid(0, 2)), atoi(data.getToTime().Mid(3, 2)), 0);

        CString mainTimeStr = data.getMainTime();
        if (data.getMainTime() == "00:00")
        {
            mainTimeStr = data.getToTime();
        }
        CTime mainTime(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), atoi(mainTimeStr.Mid(0, 2)), atoi(mainTimeStr.Mid(3, 2)), 0);

        this->dtpFromTime.SetTime(&fromTime);
        this->dtpTillTime.SetTime(&tillTime);
        this->dtpMainTime.SetTime(&mainTime);

        this->txtIdfNo.EnableWindow(FALSE);

        this->FillWeekdaysToGUI(this->data.getBranchNo(), atoi(this->data.getIdfNo()), this->data.getTourID() );
        this->SetWeekDays(this->data.getBranchNo(), atoi(this->data.getIdfNo()), this->data.getTourID() );
    }
    else
    {
        this->txtIdfNo.SetWindowText(data.getIdfNo());
        this->OnIdfInputFinished();

        this->FillWeekdaysToGUI(this->data.getBranchNo(), atoi(this->data.getIdfNo()), this->data.getTourID() );
        this->SetWeekDays(this->data.getBranchNo(), atoi(this->data.getIdfNo()), this->data.getTourID() );

        this->cmbTourID.SelectString(0,data.getTourID());
    }

    //translations
    this->btnChangeData.SetWindowText(CResString::ex().getStrTblText(maskType == CHANGE ? AETXT_UPDATE : AETXT_INSERT));

    this->btnCancel.SetWindowText(CResString::ex().getStrTblText(AETXT_CANCEL));

    this->SetTranslations();

    this->periodMisMatch=CheckPeriodMisMatch();

     return TRUE;  // return TRUE unless you set the focus to a control
                   // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDOrderPeriodChg::ProposeOrderPeriodTimesForInsert()
{
    if (this->dateTimeChanged == false)
    {
        int rc = -1;
        int count = 0;
        int weekdayCount = 0;
        CString idfNo = "";
        CString tourID = "";
        int weekday = -1;
        std::vector<Weekday> curWeekDayList;
        int toTimeValue = 0;

        /********************************GET USER INPUT******************************/
        this->txtIdfNo.GetWindowText(idfNo);
        this->cmbTourID.GetWindowText(tourID);
        GetEnteredWeekdayList(curWeekDayList);

        for (std::vector<Weekday>::iterator it = curWeekDayList.begin(); it != curWeekDayList.end(); ++it)
        {
            if ((*it).IsActive())
            {
                ++weekdayCount;
                weekday = (*it).GetWeekday();
            }
        }

        if (tourID.IsEmpty() || weekdayCount != 1)
        {
            return; //User hasnt put it the needed data, or to much data
        }

        /********************************PREPARE SQL*********************************/
        CORDERPERIOD orderPeriod;
        orderPeriod.SetCustomerno(atol(idfNo));
        orderPeriod.SetTourid(tourID);
        orderPeriod.SetWeekday(static_cast<short>(weekday));
        orderPeriod.SetBranchno(this->data.getBranchNo());

        /************************************SELECT**********************************/
        while (rc != SRV_SQLNOTFOUND)
        {
            ++count;
            orderPeriod.SetAnz_erfasst(count);

            rc = orderPeriod.SelTimesLastTour();
            if (rc != SRV_OK)
            {
                //IF the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
                if (rc == SRV_SQLNOTFOUND && orderPeriod.CloseCursor() == SRV_OK)
                {
                    orderPeriod.ClearStruct();
                }

                //no more data
                break;
            }
            toTimeValue = orderPeriod.s.TOTIME;
        }

        time_t currentTime;
        time(&currentTime);
        CTime curTime(currentTime);
        CTime fromTime(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), toTimeValue / 100, toTimeValue % 100, 0);

        int hour = 0;
        int min = 0;
        if (atoi(tourID) <= 235900)
        {
            hour = atoi(tourID.Mid(0, 2));
            min = atoi(tourID.Mid(2, 2));
        }
        else
        {
            hour = 23;
            min = 59;
        }
        CTime toTime(curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), hour, min, 0);

        this->dtpFromTime.SetTime(&fromTime);
        this->dtpTillTime.SetTime(&toTime);
    }
}

void CDOrderPeriodChg::OnTourInputFinished()
{
    CString tourID = "";
    this->cmbTourID.GetWindowText(tourID);

    if (!tourID.IsEmpty())
    {
        this->FillWeekdaysToGUI(this->data.getBranchNo(), atoi(this->data.getIdfNo()), tourID);
    }

    //Some days are maybe not allowed anymore
    this->ResetWeekdayComboAccToEnabled();
    this->InitWeekdayList();

    this->SetWeekDays(this->data.getBranchNo(), atoi(this->data.getIdfNo()), tourID);

    this->lblConsTime1.SetWindowText("");
    this->lblConsTime2.SetWindowText("");
    this->lblConsTime3.SetWindowText("");

    this->ReadConstimeForInputData();
}

void CDOrderPeriodChg::ResetWeekdayComboAccToEnabled()
{
    if (this->chkSunday.IsWindowEnabled())
    {
        this->chkSunday.SetCheck(0);
    }

    if (this->chkMonday.IsWindowEnabled())
    {
        this->chkMonday.SetCheck(0);
    }

    if (this->chkTuesday.IsWindowEnabled())
    {
        this->chkTuesday.SetCheck(0);
    }

    if (this->chkWednesday.IsWindowEnabled())
    {
        this->chkWednesday.SetCheck(0);
    }

    if (this->chkThursday.IsWindowEnabled())
    {
        this->chkThursday.SetCheck(0);
    }

    if (this->chkFriday.IsWindowEnabled())
    {
        this->chkFriday.SetCheck(0);
    }

    if (this->chkSaturday.IsWindowEnabled())
    {
        this->chkSaturday.SetCheck(0);
    }
}

void CDOrderPeriodChg::GetEnteredWeekdayList(std::vector<Weekday>& curWeekDayList)
{
    curWeekDayList.push_back( Weekday(Weekday::SUNDAY, this->chkSunday.GetCheck() == 1 ? true : false, 0 ) );
    curWeekDayList.push_back( Weekday(Weekday::MONDAY, this->chkMonday.GetCheck() == 1 ? true : false, 0 ) );
    curWeekDayList.push_back( Weekday(Weekday::TUESDAY, this->chkTuesday.GetCheck() == 1 ? true : false, 0 ) );
    curWeekDayList.push_back( Weekday(Weekday::WEDNESDAY, this->chkWednesday.GetCheck() == 1 ? true : false, 0 ) );
    curWeekDayList.push_back( Weekday(Weekday::THURSDAY, this->chkThursday.GetCheck() == 1 ? true : false, 0 ) );
    curWeekDayList.push_back( Weekday(Weekday::FRIDAY, this->chkFriday.GetCheck() == 1 ? true : false, 0 ) );
    curWeekDayList.push_back( Weekday(Weekday::SATURDAY, this->chkSaturday.GetCheck() == 1 ? true : false, 0 ) );
}

void CDOrderPeriodChg::SetWeekDays(int branchNo, int idfNo, CString tourID)
{
    int rc = -1;
    int count = 0;
    CORDERPERIOD orderPeriod;

    if (idfNo <= 0 || tourID.IsEmpty())
    {
        return;
    }

    //select tourids
    orderPeriod.SetBranchno(static_cast<short>(branchNo));
    orderPeriod.SetCustomerno(idfNo);
    orderPeriod.SetTourid(tourID);

    while (rc != SRV_SQLNOTFOUND)
    {
        ++count;
        orderPeriod.SetAnz_erfasst(count);

        rc = orderPeriod.SelOPWeekdays();
        if (rc != SRV_OK)
        {
            //IF the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
            if (rc == SRV_SQLNOTFOUND && orderPeriod.CloseCursor() == SRV_OK)
            {
                orderPeriod.ClearStruct();
            }

            //no more data
            break;
        }

        switch (orderPeriod.s.WEEKDAY)
        {
        case 1:
            this->weekList.at(Weekday::MONDAY) = Weekday(Weekday::MONDAY, true, orderPeriod.s.ID);
            this->chkMonday.SetCheck(true);
            break;
        case 2:
            this->weekList.at(Weekday::TUESDAY) = Weekday(Weekday::TUESDAY, true, orderPeriod.s.ID);
            this->chkTuesday.SetCheck(true);
            break;
        case 3:
            this->weekList.at(Weekday::WEDNESDAY) = Weekday(Weekday::WEDNESDAY, true, orderPeriod.s.ID);
            this->chkWednesday.SetCheck(true);
            break;
        case 4:
            this->weekList.at(Weekday::THURSDAY) = Weekday(Weekday::THURSDAY, true, orderPeriod.s.ID);
            this->chkThursday.SetCheck(true);
            break;
        case 5:
            this->weekList.at(Weekday::FRIDAY) = Weekday(Weekday::FRIDAY, true, orderPeriod.s.ID);
            this->chkFriday.SetCheck(true);
            break;
        case 6:
            this->weekList.at(Weekday::SATURDAY) = Weekday(Weekday::SATURDAY, true, orderPeriod.s.ID);
            this->chkSaturday.SetCheck(true);
            break;
        case 0:
            this->weekList.at(Weekday::SUNDAY) = Weekday(Weekday::SUNDAY, true, orderPeriod.s.ID);
            this->chkSunday.SetCheck(true);
            break;
        default:
            AfxMessageBox(CResString::ex().getStrTblText(AETXT_INVALID_WEEKDAY));
            return;
        }
    }
}

void CDOrderPeriodChg::FillWeekdaysToGUI(int branchNo, int idfNo, CString tourID)
{
    int rc = -1;
    int count = 0;
    CORDERPERIOD orderPeriod;

    this->lblMonday.SetWindowText(CResString::ex().getStrTblText(AETXT_INAKTIV));
    this->lblTuesday.SetWindowText(CResString::ex().getStrTblText(AETXT_INAKTIV));
    this->lblWednesday.SetWindowText(CResString::ex().getStrTblText(AETXT_INAKTIV));
    this->lblThursday.SetWindowText(CResString::ex().getStrTblText(AETXT_INAKTIV));
    this->lblFriday.SetWindowText(CResString::ex().getStrTblText(AETXT_INAKTIV));
    this->lblSaturday.SetWindowText(CResString::ex().getStrTblText(AETXT_INAKTIV));
    this->lblSunday.SetWindowText(CResString::ex().getStrTblText(AETXT_INAKTIV));

    if (idfNo <= 0 || tourID.IsEmpty())
    {
        return;
    }

    //select tourids
    orderPeriod.SetBranchno(static_cast<short>(branchNo));
    orderPeriod.SetCustomerno(idfNo);
    orderPeriod.SetTourid(tourID);

    while (rc != SRV_SQLNOTFOUND)
    {
        ++count;
        orderPeriod.SetAnz_erfasst(count);

        rc = orderPeriod.SelWeekdays4Tour();
        if (rc != SRV_OK)
        {
            //IF the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
            if (rc == SRV_SQLNOTFOUND && orderPeriod.CloseCursor() == SRV_OK)
            {
                orderPeriod.ClearStruct();
            }

            //no more data
            break;
        }

        switch (orderPeriod.s.WEEKDAY)
        {
        case 1:
            this->lblMonday.SetWindowText(CResString::ex().getStrTblText(AETXT_AKTIV));
            break;
        case 2:
            this->lblTuesday.SetWindowText(CResString::ex().getStrTblText(AETXT_AKTIV));
            break;
        case 3:
            this->lblWednesday.SetWindowText(CResString::ex().getStrTblText(AETXT_AKTIV));
            break;
        case 4:
            this->lblThursday.SetWindowText(CResString::ex().getStrTblText(AETXT_AKTIV));
            break;
        case 5:
            this->lblFriday.SetWindowText(CResString::ex().getStrTblText(AETXT_AKTIV));
            break;
        case 6:
            this->lblSaturday.SetWindowText(CResString::ex().getStrTblText(AETXT_AKTIV));
            break;
        case 0:
            this->lblSunday.SetWindowText(CResString::ex().getStrTblText(AETXT_AKTIV));
            break;
        default:
            AfxMessageBox(CResString::ex().getStrTblText(AETXT_INVALID_WEEKDAY));
            return;

        }
    }
}

void CDOrderPeriodChg::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDOrderPeriodChg::OnIdfInputFinished()
{
    CString idfNo = "";
    int weekDay = -1;//Not used atm

    this->txtIdfNo.GetWindowText(idfNo);

    std::string tmp = idfNo;
    if (tmp.empty())
    {
        return;
    }
    else if (!DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_IDF_NOT_VALID));
        return;
    }

    this->cmbTourID.ResetContent();

    std::vector<std::pair<CString,bool> > tourIDList;
    int rc = DataQueryHelper::getTourIDsForIDF(atol(idfNo), this->data.getBranchNo(), weekDay, tourIDList);
    if (rc == -1)
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_NOTOURFORIDF));
        return;
    }
    for (std::vector<std::pair<CString, bool> >::iterator it = tourIDList.begin(); it != tourIDList.end(); ++it)
    {
        this->cmbTourID.AddString((*it).first);
    }
}

void CDOrderPeriodChg::OnBtnClickedCancel()
{
    CDialogMultiLang::OnCancel();
}

void CDOrderPeriodChg::OnBtnClickedFinishInput()
{
    if (maskType == CHANGE)
    {
        if (this->UpdateData())
        {
            AfxMessageBox(CResString::ex().getStrTblText(AETXT_OP_UPDATE_SUCCESS));
            EndDialog(0);
        }
        else
        {
            AfxMessageBox(CResString::ex().getStrTblText(AETXT_OP_UPDATE_ERROR));
        }
    }
    else
    {
        if (this->InsertData())
        {
            AfxMessageBox(CResString::ex().getStrTblText(AETXT_OP_INSERT_SUCCESS));
            EndDialog(0);
        }
        else
        {
            AfxMessageBox(CResString::ex().getStrTblText(AETXT_OP_INSERT_ERROR));
        }
    }
}

void CDOrderPeriodChg::OnTimeChanged(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
    this->dateTimeChanged = true;
    this->periodMisMatch = this->CheckPeriodMisMatch();

    //move cursor from hours to minutes
    keybd_event(VK_RIGHT, 0, 0, 0);
    keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
}

void CDOrderPeriodChg::ReadConstimeForInputData()
{
    //check if all values are set
    CString idfNo = "";
    CString tourID = "";
    int fetchCountTime = 0;
    CORDERPERIOD orderPeriodTime;
    int rc;
    bool foundConsTime = false;

    this->txtIdfNo.GetWindowText(idfNo);
    this->cmbTourID.GetWindowText(tourID);

    std::string tmp = idfNo;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        return;
    }

    tmp = tourID;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        return;
    }

    //get const times for this data
    fetchCountTime = 1;
    for (int j = 0; j < 3; j++)
    {
        orderPeriodTime.SetTourid(tourID);
        orderPeriodTime.SetBranchno(this->data.getBranchNo());
        orderPeriodTime.SetCustomerno(atol(idfNo));
        orderPeriodTime.SetAnz_erfasst(fetchCountTime);

        rc = orderPeriodTime.SelConsTime();
        if (rc != SRV_OK)
        {
            //IF the end is reached, the cursor needs to be closed, so that upon a page up event, the sql is running again.
            if (rc == SRV_SQLNOTFOUND && orderPeriodTime.CloseCursor() == SRV_OK)
            {
                orderPeriodTime.ClearStruct();
            }

            //no more data
            break;
        }

        if (orderPeriodTime.s.CONSTIME == 0)
        {
            continue;
        }

        this->data.addConsTime(DataTypeHelper::toString(orderPeriodTime.s.CONSTIME).c_str());
        foundConsTime = true;

        switch (j)
        {
        case 0:
            this->lblConsTime1.SetWindowText(DataTypeHelper::toString(orderPeriodTime.s.CONSTIME).c_str());
            break;
        case 1:
            this->lblConsTime2.SetWindowText(DataTypeHelper::toString(orderPeriodTime.s.CONSTIME).c_str());
            break;
        case 2:
            this->lblConsTime3.SetWindowText(DataTypeHelper::toString(orderPeriodTime.s.CONSTIME).c_str());
            break;
        }
        ++fetchCountTime;
    }

    if (!foundConsTime)
    {
        CPARAUFBEARB paraufbearb;
        paraufbearb.s.FILIALNR = AeGetApp()->VzNr();
        paraufbearb.Server(AafilSelaufbearb);
        int wareHouseProcessingTime = paraufbearb.s.DURCHLAUFNORMAL;

        int tourIDAsInt = atol(tourID);
        tourIDAsInt = tourIDAsInt / 100;  //Bahnhof entfernen
        tourIDAsInt = tourIDAsInt * 100;
        long lStdConsTime = 0;
        if (tourIDAsInt < 240000)
        {
            AllgAddTimeSpan(tourIDAsInt, wareHouseProcessingTime * (-60), &lStdConsTime);
            lStdConsTime = lStdConsTime / 100;
            std::string test = DataTypeHelper::padString(DataTypeHelper::toString(lStdConsTime).c_str(), 4, '0');
            test.insert(2, ":");
            this->lblConsTime1.SetWindowText(test.c_str());
            this->data.addConsTime(test.c_str());
        }
    }

    this->periodMisMatch = this->CheckPeriodMisMatch();
}

bool CDOrderPeriodChg::InsertData()
{
    bool retValue = false;
    CString fromTime = "";
    CString toTime = "";
    CString mainTime = "";
    CString idfNo = "";
    CString tourID = "";
    int weekDay = 0;
    std::vector<Weekday> curWeekDayList;

    /********************************GET USER INPUT******************************/
    this->dtpFromTime.GetWindowText(fromTime);
    this->dtpTillTime.GetWindowText(toTime);
    this->dtpMainTime.GetWindowText(mainTime);
    this->txtIdfNo.GetWindowText(idfNo);
    this->cmbTourID.GetWindowText(tourID);

    fromTime.Remove(':');
    toTime.Remove(':');
    mainTime.Remove(':');

    GetEnteredWeekdayList(curWeekDayList);

    /****************************USER INPUT CHECK********************************/
    std::string tmp = fromTime;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_FROMTIME_ERROR));
        return false;
    }

    tmp = toTime;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_ENDTIME_ERROR));
        return false;
    }

    tmp = mainTime;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_MAINTIME_ERROR));
        return false;
    }

    tmp = idfNo;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_IDF_NOT_VALID));
        return false;
    }

    tmp = tourID;
    if (tmp.empty())
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_TOUR_ERROR));
        return false;
    }

    if (weekDay == -1)
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_WEEKDAY_ERROR));
        return false;
    }

    /************************LOGICAL USER INPUT DATA CHECK********************************/
    if (mainTime > toTime)
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_MAINTIME_ERROR));
        return false;
    }

    this->periodMisMatch=CheckPeriodMisMatch();

    if (this->periodMisMatch)
    {
        if (AfxMessageBox(CResString::ex().getStrTblText(AETXT_WARN_ORDERPERIOD), MB_YESNO) == IDNO)
        {
            return false;
        }
    }

    for (std::vector<Weekday>::iterator it = curWeekDayList.begin(); it != curWeekDayList.end(); ++it)
    {
        if ((*it).IsActive() && this->CheckOPOverLap(false, (*it).GetWeekday()))
        {
            AfxMessageBox(CResString::ex().getStrTblText(AETXT_OPOVERLAP));
            return false;
        }
    }

    for (std::vector<Weekday>::iterator it = curWeekDayList.begin(); it != curWeekDayList.end(); ++it)
    {
        if ((*it).IsActive())
        {
            weekDay = (*it).GetWeekday();

            CORDERPERIOD orderPeriod;
            /********************************PREPARE SQL*********************************/
            orderPeriod.SetFromtime(atol(fromTime));
            orderPeriod.SetTotime(atol(toTime));
            orderPeriod.SetMaintime(atol(mainTime));
            orderPeriod.SetCustomerno(atol(idfNo));
            orderPeriod.SetTourid(tourID);
            orderPeriod.SetWeekday(static_cast<short>(weekDay));
            orderPeriod.SetBranchno(this->data.getBranchNo());

            /************************************INSERT**********************************/
            if (!orderPeriod.InsertOPAndOPT())
            {
                retValue = true;
            }
        }
    }

    return retValue;
}

bool CDOrderPeriodChg::UpdateData()
{
    bool retValue = false;
    bool activeWeekDays = false;
    CString fromTime = "";
    CString toTime = "";
    CString mainTime = "";
    CString tourID = "";
    int weekDay = 0;
    std::vector<Weekday> curWeekDayList;

    /********************************GET USER INPUT******************************/
    this->dtpFromTime.GetWindowText(fromTime);
    this->dtpTillTime.GetWindowText(toTime);
    this->dtpMainTime.GetWindowText(mainTime);
    this->cmbTourID.GetWindowText(tourID);

    fromTime.Remove(':');
    toTime.Remove(':');
    mainTime.Remove(':');

    GetEnteredWeekdayList(curWeekDayList);

    /****************************USER INPUT CHECK********************************/
    std::string tmp = fromTime;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_FROMTIME_ERROR));
        return false;
    }

    tmp = toTime;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_ENDTIME_ERROR));
        return false;
    }

    tmp = mainTime;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_MAINTIME_ERROR));
        return false;
    }

    tmp = tourID;
    if (tmp.empty())
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_TOUR_ERROR));
        return false;
    }

    if (weekDay == -1)
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_WEEKDAY_ERROR));
        return false;
    }

    /************************LOGICAL USER INPUT DATA CHECK********************************/
    if (mainTime > toTime)
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_MAINTIME_ERROR));
        return false;
    }

    this->periodMisMatch = CheckPeriodMisMatch();

    if (this->periodMisMatch)
    {
        if (AfxMessageBox(CResString::ex().getStrTblText(AETXT_WARN_ORDERPERIOD), MB_YESNO) == IDNO)
        {
            return false;
        }
    }

    for (std::vector<Weekday>::iterator it = curWeekDayList.begin(); it != curWeekDayList.end(); ++it)
    {
        if ((*it).IsActive() && this->CheckOPOverLap(true, (*it).GetWeekday()))
        {
            AfxMessageBox(CResString::ex().getStrTblText(AETXT_OPOVERLAP));
            return false;
        }
        else if ((*it).IsActive())
        {
            activeWeekDays = true;
        }
    }

    if (!activeWeekDays)
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_WEEKDAYS_NOT_ACTIVE));
        return false;
    }

    std::vector<Weekday>::iterator beginCur = curWeekDayList.begin();
    std::vector<Weekday>::iterator endCur = curWeekDayList.end();
    std::vector<Weekday>::iterator beginOld = this->weekList.begin();

    while (beginCur != endCur)
    {
        CORDERPERIOD orderPeriod;
        orderPeriod.SetFromtime(atol(fromTime));
        orderPeriod.SetTotime(atol(toTime));
        orderPeriod.SetMaintime(atol(mainTime));
        orderPeriod.SetOrder_period_id(this->data.getOrderPeriodTimeID());
        orderPeriod.SetTourid(tourID);
        orderPeriod.SetBranchno(this->data.getBranchNo());
        orderPeriod.SetId( (*beginOld).GetID() );
        orderPeriod.SetWeekday(static_cast<short>((*beginCur).GetWeekday()));
        orderPeriod.SetCustomerno(atol(this->data.getIdfNo()));

        if (*beginCur != *beginOld)
        {
            //insert
            if (beginCur->IsActive() && !beginOld->IsActive())
            {
                if (!orderPeriod.InsertOPAndOPT())
                {
                    retValue = true;
                }
            }
            //update
            else if (beginCur->IsActive() && beginOld->IsActive())
            {
                if (!orderPeriod.UpdateTime())
                {
                    retValue = true;
                }
            }
            //delete -> not wanted atm
            else if (!beginCur->IsActive() && beginOld->IsActive())
            {
                retValue = true;
            }
        }
        else
        {
            if (beginOld->IsActive() &&
                (tourID != this->data.getTourID() ||
                 fromTime != this->data.getFromTime() ||
                 toTime != this->data.getToTime() ||
                 mainTime != this->data.getMainTime() ) )
            {
                if (!orderPeriod.UpdateTime())
                {
                    retValue = true;
                }
            }
            else
            {
                retValue = true;
            }
        }
        ++beginCur;
        ++beginOld;
    }

    return retValue;
}


bool CDOrderPeriodChg::CheckOPOverLap(bool update, int weekDay)
{
    CORDERPERIOD orderPeriodOverLap;
    bool retValue = false;
    CString fromTime = "";
    CString toTime = "";
    CString tourID = "";
    int maxValue = update ? 1 : 0;

    /********************************GET USER INPUT******************************/
    this->dtpFromTime.GetWindowText(fromTime);
    this->dtpTillTime.GetWindowText(toTime);
    this->cmbTourID.GetWindowText(tourID);

    fromTime.Remove(':');
    toTime.Remove(':');

    /****************************USER INPUT CHECK********************************/
    std::string tmp = fromTime;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_FROMTIME_ERROR));
        return false;
    }

    tmp = toTime;
    if (!tmp.empty() && !DataTypeHelper::isNumber(tmp))
    {
        AfxMessageBox(CResString::ex().getStrTblText(AETXT_ENDTIME_ERROR));
        return false;
    }

    /****************************Set Data to Struct********************************/
    orderPeriodOverLap.SetCustomerno(atol(this->data.getIdfNo()));
    orderPeriodOverLap.SetTourid(tourID);
    orderPeriodOverLap.SetBranchno(this->data.getBranchNo());
    orderPeriodOverLap.SetFromtime(atol(fromTime));
    orderPeriodOverLap.SetTotime(atol(toTime));
    orderPeriodOverLap.SetWeekday(static_cast<short>(weekDay));

    if (orderPeriodOverLap.CheckOPOverLap() == 0)
    {
        if (orderPeriodOverLap.GetAnz_erfasst() > maxValue)
        {
            retValue = true;
        }
    }
    if (orderPeriodOverLap.CloseCursor() == 0)
    {
        orderPeriodOverLap.ClearStruct();
    }

    return retValue;
}

bool CDOrderPeriodChg::CheckPeriodMisMatch()
{
    try
    {
        int highestTime = 0;
        CString tmp = "";

        this->lblConsTime1.GetWindowText(tmp);
        int consTime1 = atol(tmp);

        this->lblConsTime2.GetWindowText(tmp);
        int consTime2 = atol(tmp);

        this->lblConsTime3.GetWindowText(tmp);
        int consTime3 = atol(tmp);

        this->dtpTillTime.GetWindowText(tmp);
        tmp.Remove(':');
        int orderPeriodEndTime = atol(tmp);

        if (consTime1 > consTime2 && consTime1 > consTime3)
        {
            highestTime = consTime1;
        }
        else if (consTime2 > consTime1 && consTime2 > consTime3)
        {
            highestTime = consTime2;
        }
        else
        {
            highestTime = consTime3;
        }

        if (highestTime > 0 && orderPeriodEndTime >= highestTime)
        {
            return true;
        }
        return false;
    }
    catch(...)
    {
        return false;
    }
}

HBRUSH CDOrderPeriodChg::OnCtlColor(CDC* pDC, CWnd* pWnd,UINT nCtlColor)
{
   HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

   // Add the following code
   if (this->periodMisMatch && (pWnd->GetDlgCtrlID() == IDC_LBL_CONSTIME1 ||
       pWnd->GetDlgCtrlID() == IDC_LBL_CONSTIME2 ||
       pWnd->GetDlgCtrlID() == IDC_LBL_CONSTIME3 ))
   {
      pDC->SetTextColor(RGB(255,0,0));
   }

   if (pWnd->GetDlgCtrlID() == IDC_LBL_MONDAY_ACTIVE ||
       pWnd->GetDlgCtrlID() == IDC_LBL_TUESDAY_ACTIVE ||
       pWnd->GetDlgCtrlID() == IDC_LBL_WEDNESDAY_ACTIVE ||
       pWnd->GetDlgCtrlID() == IDC_LBL_THURSDAY_ACTIVE ||
       pWnd->GetDlgCtrlID() == IDC_LBL_FRIDAY_ACTIVE ||
       pWnd->GetDlgCtrlID() == IDC_LBL_SATURDAY_ACTIVE ||
       pWnd->GetDlgCtrlID() == IDC_LBL_SUNDAY_ACTIVE )
   {
       CStatic* label = (CStatic*)GetDlgItem(pWnd->GetDlgCtrlID());
       CString strText;
       label->GetWindowText(strText);
       if (strText == CResString::ex().getStrTblText(AETXT_AKTIV))
       {
           pDC->SetTextColor(RGB(0, 255, 0));
       }
       else
       {
           pDC->SetTextColor(RGB(255, 0, 0));
       }
   }

   return hbr;
}

void CDOrderPeriodChg::OnBtnClickedDay()
{
    this->ProposeOrderPeriodTimesForInsert();

    this->ReadConstimeForInputData();
}
