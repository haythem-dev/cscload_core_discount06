#pragma once

// CUCustomerTimes.h : Header-Datei
//


//--- include ----------------------------------------------------------------//

#include "ppDataTypes.h"
#include "PageTabCtrl.h"

//--- pages (dialoge) --------------------------------------------------------//

//#include "PACustomerTimeCompound.h"
#include "CUServicePlan.h"
#include "CUVacation.h"
//#include "PACustomerTimeOpenClose.h"
//#include "PACustomerTimeVacation.h"

//----------------------------------------------------------------------------//
//--- class CCUCustomerTime (dialog) -----------------------------------------//
//----------------------------------------------------------------------------//

class CCUCustomerTimes : public CDialogMultiLang
{
public: // Construction
    CCUCustomerTimes(const short VZ = -1,
                     const long Knd = -1,
                     CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_CU_PSCUSTOMERTIMES };
    CPageTabCtrl m_CTabCtrlCustomerTime;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonSave();
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnButtonDelete();
    afx_msg void OnButtonChange();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

private: //pages  (classes must be initialized in the constructor!)
    CCUServicePlan  m_PageCustomerTimeEmergencyService;
    CCUVacation     m_PageCustomerTimeVacation;

protected: //members
    short           m_sSaleCenterNo;
    long            m_lCustomerNo;
    bool            m_bIsVkMenu;

protected: //methodes
    void SetHeader();
    bool AreChanged();
};
