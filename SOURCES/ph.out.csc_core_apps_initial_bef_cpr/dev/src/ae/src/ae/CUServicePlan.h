#pragma once

// CUServicePlan.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCUServicePlan

//--- include ----------------------------------------------------------------//

#include "ppDataTypes.h"
#include "TabPage.h"
#include "ppCustomerEmergencyServicePlan.h"
#include "Servicelistctrl.h"

//----------------------------------------------------------------------------//
//--- class CCUServicePlan (dialog) ------------------------//
//----------------------------------------------------------------------------//

class CCUServicePlan : public CTabPage
{
public: // Construction
    CCUServicePlan(const short VzNr = -1, const long KdNr = -1);
    virtual ~CCUServicePlan();
    CServiceListCtrl *m_List1;

public: //methodes (Interface description)
    void SetSaleCenterNo(const short VzNr) { m_sSaleCenterNo = VzNr; }
    void SetCustomerNo(const long KdNr) { m_lCustomerNo = KdNr; }
    void ChangeCustomer(const short VzNr, const long KdNr);
    virtual bool IsChanged();
    virtual bool UpdateServer();
    virtual bool DeleteServer();

    enum { IDD = IDD_CU_PASERVICEPLAN };

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnDestroy();
    DECLARE_MESSAGE_MAP()

protected: //members
    ppCustomerEmergencyServicePlan m_CustomerEmergency;
    bool    m_bIsActive;
    short   m_sSaleCenterNo;
    long    m_lCustomerNo;
    unsigned int m_nRows;

protected: //methodes overwrites
    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle();
    virtual void SetIsActive(const bool isActive = true) { m_bIsActive = isActive; }

    bool SetValueIntoList();
    bool GetPage(const int nKzUpDown = NEXT_PG);
    long String2longdate(const CString& cDate);
    long String2longtime(const CString& cTime);
    short YesNo2short(const CString& cYesNo);
};
