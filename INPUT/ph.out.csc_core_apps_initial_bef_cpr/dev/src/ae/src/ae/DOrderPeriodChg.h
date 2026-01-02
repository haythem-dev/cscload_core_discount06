#pragma once
#include <afxstr.h>
#include "OrderPeriodData.h"
#include <orders.h>
#include <customer.h>
#include "Weekday.h"

class CDOrderPeriodChg : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDOrderPeriodChg)

public:

    enum MASKTYPE { CHANGE, INSERT };

    CDOrderPeriodChg(MASKTYPE maskType, OrderPeriodData data, CWnd* pParent = NULL);
    virtual ~CDOrderPeriodChg();

    enum { IDD = IDD_AE_ORDER_PERIOD_CHG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

private:
    OrderPeriodData data;
    MASKTYPE maskType;
    bool periodMisMatch;
    std::vector<Weekday> weekList;
    bool dateTimeChanged;

    //GUI Elements
    CStatic lblOrderPeriod;
    CStatic lblTourID;
    CStatic lblFrom;
    CStatic lblTill;
    CStatic lblIdfNo;
    CStatic lblConsTime1;
    CStatic lblConsTime2;
    CStatic lblConsTime3;
    CStatic lblCloseTime;
    CStatic lblMainTime;
    CStatic lblMonday;
    CStatic lblTuesday;
    CStatic lblWednesday;
    CStatic lblThursday;
    CStatic lblFriday;
    CStatic lblSaturday;
    CStatic lblSunday;

    CButton chkMonday;
    CButton chkTuesday;
    CButton chkWednesday;
    CButton chkThursday;
    CButton chkFriday;
    CButton chkSaturday;
    CButton chkSunday;

    CButton cgbSearch;
    CButton cgbOrderPeriod;
    CButton cgbDays;
    CButton cgbOrderTourCloseTimes;

    CEdit txtIdfNo;
    CDateTimeCtrl dtpFromTime;
    CDateTimeCtrl dtpTillTime;
    CDateTimeCtrl dtpMainTime;

    CComboBox cmbTourID;

    CButton btnCancel;
    CButton btnChangeData;

    //methods
    BOOL OnInitDialog();
    void OnDestroy();
    bool UpdateData();
    bool InsertData();
    bool CheckPeriodMisMatch();
    bool CheckOPOverLap(bool update, int weekday);
    void SetButtonStyles();
    void SetTranslations();
    void SetWeekDays(int branchNo, int idfNo, CString tourID);
    void FillWeekdaysToGUI(int branchNo, int idfNo, CString tourID);
    void InitWeekdayList();
    void GetEnteredWeekdayList(std::vector<Weekday>& curWeekDayList);
    void ResetWeekdayComboAccToEnabled();
    void ProposeOrderPeriodTimesForInsert();
    void ReadConstimeForInputData();

    //Events
    DECLARE_MESSAGE_MAP()
    afx_msg void OnIdfInputFinished();
    afx_msg void OnBtnClickedCancel();
    afx_msg void OnBtnClickedFinishInput();
    afx_msg void OnTimeChanged(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd,UINT nCtlColor);
    afx_msg void OnTourInputFinished();
    afx_msg void OnWeekdayInputFinished();
    afx_msg void OnBtnClickedDay();
};
