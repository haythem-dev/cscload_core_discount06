//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPPACallPlanDay.h
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//--- include ----------------------------------------------------------------//

#include "TabPage.h"
#include "ppDataTypes.h"
#include "ppCustomerCallPlan.h"

//----------------------------------------------------------------------------//
//--- class CCPCallPlanMaintenance (dialog) ----------------------------------//
//----------------------------------------------------------------------------//

class CCPCallPlanMaintenance;
class CPARAUFBEARB;
class CCPPACallPlanDay : public CTabPage, CPageBrowser
{
public: // Construction
    CCPPACallPlanDay(CCPCallPlanMaintenance* pWnd,
                     const ppCustomerDisplay* pCustomer,
                     const CPARAUFBEARB* psrvAufParameter,
                     const ppDayType::t_day d);

public: //operation
    void ClearListCtrl();

// Dialog Data
    enum { IDD = IDD_CP_PACALLPLANDAY };
    CListCtrl m_ListCtl;


// Overrides
    // ClassWizard generate virtual function overrides
public:
    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnKeydownListCallplanday(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickListCallplanday(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

protected: //members
    const CPARAUFBEARB*      m_psrvAufParameter;
    CCPCallPlanMaintenance*  m_pParent;
    const ppCustomerDisplay* m_pCustomer;
    ppCustomerCallPlan       m_CustomerPlan;
    bool                     m_bIsActive;
    short                    m_sSaleCenterNo;
    long                     m_lCustomerNo;
    unsigned int             m_nColumnsCount;
    unsigned int             m_iPos;

protected: //methodes overwrites
    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle();
    virtual bool UpdateServer();
    virtual bool InsertServer();
    virtual bool DeleteServer();
    virtual bool OtherServer();
    virtual void Initialize();
    virtual const int GetCountItem() const;

protected:
    bool SetListHeader();
    bool SetValueIntoList(const char& chSelector = AeGetApp()->Letter_A());
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);
    bool IsCustomerChanged();
    bool GetPosition(const bool bWithMsg=true);
    void MakeEditable();
    void UpdateIntoList();
    void SetButton();
    void SetFirstListPos();

protected:
    const ppString c_strTitle;
    ppDayType::t_day m_eDay;
};
