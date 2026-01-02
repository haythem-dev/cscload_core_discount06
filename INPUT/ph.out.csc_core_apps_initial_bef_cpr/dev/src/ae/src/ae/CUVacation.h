#pragma once

// CUVacation.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CCUVacation

//--- include ----------------------------------------------------------------//

#include "ppDataTypes.h"
#include "TabPage.h"
#include "ppCustomerVacation.h"
#include "Vacationlistctrl.h"

//----------------------------------------------------------------------------//
//--- class CCUVacation (dialog) ------------------------//
//----------------------------------------------------------------------------//

class ppMGridCtrlStage;

class CCUVacation : public CTabPage
{
public: // Construction
    CCUVacation(const short VzNr = -1, const long KdNr = -1);
    virtual ~CCUVacation();
    CVacationListCtrl *m_List1;

public: //methodes (Interface description)
    void SetSaleCenterNo(const short VzNr) { m_sSaleCenterNo = VzNr; }
    void SetCustomerNo(const long KdNr) { m_lCustomerNo = KdNr; }
    void ChangeCustomer(const short VzNr, const long KdNr) ;
    virtual bool IsChanged();
    virtual bool UpdateServer();
    virtual bool DeleteServer();

// Dialog Data
    enum { IDD = IDD_CU_PAVACATION };


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
    afx_msg void OnDestroy();
    DECLARE_MESSAGE_MAP()

protected: //members
    ppCustomerVacation  m_CustomerVacation;
    bool                m_bIsActive;
    short               m_sSaleCenterNo;
    long                m_lCustomerNo;
    unsigned int        m_nRows;

protected: //methodes overwrites
    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle();
    virtual void SetIsActive(const bool isActive = true) { m_bIsActive = isActive; }

protected:
    bool SetValueIntoList();
    bool GetPage(const int nKzUpDown = NEXT_PG);
    long String2longdate(const CString& cDate);
};
