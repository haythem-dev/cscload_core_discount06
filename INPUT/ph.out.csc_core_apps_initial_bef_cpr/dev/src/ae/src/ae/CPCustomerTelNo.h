//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCustomerTelNo.h
   Author: A.Schmidt-Rehschuh
   made  : 09.04.2000

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//----------------------------------------------------------------------------//
//--- class CCPCustomerTelNo (dialog) ----------------------------------------//
//----------------------------------------------------------------------------//

class ppCustomerDisplay;
class CCPCustomerTelNo : public CDialogMultiLang
{
public: // Construction
    CCPCustomerTelNo(CWnd* pParent = NULL);   // standard constructor
    ~CCPCustomerTelNo();

    enum { IDD = IDD_CP_CUSTOMER_TELNO };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnButtonRestore();
    afx_msg void OnButtonCustomer();
    DECLARE_MESSAGE_MAP()

protected: //methodes
    void SetHeader();
    bool GetCustomer();

protected: //members
    ppCustomerDisplay* m_pCustomer;
};
