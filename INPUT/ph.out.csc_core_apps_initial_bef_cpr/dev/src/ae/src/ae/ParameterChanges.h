#pragma once
#include <parameter_change_logging.h>
#include <parameter_change_log_defs.h>

// CParameterChanges dialog

class CParameterChanges : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CParameterChanges)

public:
    CParameterChanges( CWnd* pParent = NULL );

    virtual ~CParameterChanges();

    BOOL OnInitDialog();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PARAMETER_CHANGES };
#endif

protected:
    virtual void DoDataExchange( CDataExchange* pDX );

    afx_msg void OnBnClickedButtonSearch();
    afx_msg void OnBnClickedButtonReset();
    afx_msg void OnDtnDatetimechangeDatetimepickerFromDate(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDtnDatetimechangeDatetimepickerToDate(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

private:
    void initDateTimePickers();
    void initParametersComboBox();
    void initResultsListControl();
    void initBranchNumberComboBox();

    void setDefaultDateForToDate();
    void setDefaultDateForFromDate();
    void setRangeForDateTimePickers();
    void setDateToParameterChangeLogging(CPARAMETER_CHANGE_LOGGING& parameterChangeLogging);
    void setParameterToParameterChangeLogging(CPARAMETER_CHANGE_LOGGING& parameterChangeLogging);
    void setBranchNumberToParameterChangeLogging(CPARAMETER_CHANGE_LOGGING& parameterChangeLogging);

    void getDatesFromDateTimePickers( long& fromDate, long& toDate );

    void warningDateFromBiggerThanDateTo();

    void createColumnsInResultsListControl();
    void insertColumnsInResultsListControl();

    void insertDataInListControl(CStringArray& rawInListControl);
    void obtainDataForListControl(CStringArray& rawInListControl, CPARAMETER_CHANGE_LOGGING& parameterChangeLogging);

    short m_dateFromBiggerThanDateToWarningCounter;
    CString m_Regionliste;
    CComboBox m_comboBoxParameter;
    CListCtrl m_listControlResults;
    CComboBox m_comboBoxBranchNumber;
    CDateTimeCtrl m_dateTimePickerToDate;
    CDateTimeCtrl m_dateTimePickerFromDate;
};
