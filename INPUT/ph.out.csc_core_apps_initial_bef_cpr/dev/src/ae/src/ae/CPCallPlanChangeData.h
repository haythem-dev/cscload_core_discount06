//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCallPlanChangeData.h
   Author: A.Schmidt-Rehschuh/v.d.Grün
   made  : 19.04.2000

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//--- include ----------------------------------------------------------------//

#include "ppCustomerCallPlan.h"
#include "ppCustomerCallPlanTour.h"

//----------------------------------------------------------------------------//
//--- class CCPCallPlanChangeData (dialog) ----------------------------------//
//----------------------------------------------------------------------------//

class CCPCallPlanChangeData : public CDialogMultiLang
{
public: // Construction
    CCPCallPlanChangeData(ppCustomerCallPlan* pCustomerPlan,
                          const ppDayType::t_day eDay,
                          CWnd* pParent = NULL);   // standard constructor
    ~CCPCallPlanChangeData();

public: //set-methodes
    void SetIsInsert(const bool isInsert = true);
    void SetIsDelete(const bool isDelete = true);
    void SetIsDisable(const bool isDisable = true);
    void SetStockRunningTimeExpress(const short iShortTime);
    void SetStockRunningTime(const short iNormalTime);

    enum { IDD = IDD_CP_CALLPLANCHANGEDATA };
    CButton m_CButtonMustCall;
    CButton m_CButtonDisable;
    CEdit   m_CEditCalltime;
    CComboBox m_CComboBoxPoolno;
    CComboBox m_CComboBoxPriority;
    CString m_csTime;
    CString m_CInfo;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    afx_msg void OnRadio4();
    afx_msg void OnChangeEditCalltime();
    afx_msg void OnKillfocusEditCalltime();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

protected: //members
    ppCustomerCallPlan*     m_pCustomerPlan;
    ppCustomerCallPlanTour* m_pCustomerTour;
    bool                    m_bIsInsert;
    bool                    m_bIsDelete;
    bool                    m_bIsDisabled;
    const long              m_constTime;
    ppDayType::t_day        m_eDay;
    short                   m_iShortTime;
    short                   m_iNormalTime;

protected: //methodes
    void InitializeCombos();
    void SetHeader();
    void MakeEditable();
    void GetDataFromScreen();
    bool CheckCallTime();
    bool DeletePlanData(const UINT iID);
    bool InsertPlanData(const UINT iID);
    bool UpdatePlanData(const UINT iID);

    bool UpdSingleDay();
    bool UpdAllDays();
    bool UpdWithoutSaturday();
    bool InsSingleDay();
    bool InsAllDays();
    bool InsWithoutSaturday();
    bool DelSingleDay();
    bool DelAllDays();
    bool DelWithoutSaturday();
    void MakeInsertable();
};
