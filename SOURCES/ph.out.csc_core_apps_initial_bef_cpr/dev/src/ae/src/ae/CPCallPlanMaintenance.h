//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCallPlanMaintenance.h
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//--- include ----------------------------------------------------------------//

#include "PageTabCtrl.h"
#include "ppCustomerDisplay.h"
#include "ppCustomerTourplanDay.h"

//--- pages (dialoge) --------------------------------------------------------//

#include "CPPACallPlanDay.h"

//----------------------------------------------------------------------------//
//--- class CCPCallPlanMaintenance (dialog) ----------------------------------//
//----------------------------------------------------------------------------//

class CPARAUFBEARB;
class CCPCallPlanMaintenance : public CDialogMultiLang
{
public: // Construction
    CCPCallPlanMaintenance(ppCustomerDisplay* Customer,
                           CWnd* pParent = NULL);
    ~CCPCallPlanMaintenance();

public:
    const bool GetAllDisabled() const;

    enum { IDD = IDD_CP_CALLPLANMAINTENANCE };
    CButton m_CButtonDeleteAll;
    CPageTabCtrl m_CTabCtrlCallPlan;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnButtonCustomer();
    afx_msg void OnButtonUpdate();
    afx_msg void OnButtonInsert();
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonPrint();
    afx_msg void OnButtonDisable();
    afx_msg void OnButtonDeleteall();
    afx_msg void OnButtonDisableall();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

private: //pages  (classes must be initialized in the constructor!)
    CCPPACallPlanDay* m_pPageCallPlanMonday;
    CCPPACallPlanDay* m_pPageCallPlanTuesday;
    CCPPACallPlanDay* m_pPageCallPlanWednesday;
    CCPPACallPlanDay* m_pPageCallPlanThursday;
    CCPPACallPlanDay* m_pPageCallPlanFriday;
    CCPPACallPlanDay* m_pPageCallPlanSaturday;
    CCPPACallPlanDay* m_pPageCallPlanSunday;

protected: //members
    CPARAUFBEARB*       m_psrvAufParameter;
    ppCustomerDisplay*  m_pCustomer;
    ppCustomerCallPlan* m_pCallPlan;
    bool                m_bIsVkMenu;

protected: //methodes
    void SetHeader();
    bool GetCustomer();
    bool PrintCallPlan(CDC* dc);
    void SetButton(const bool bEnable);
};
