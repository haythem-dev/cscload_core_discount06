//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCustomerProperties.h
   Author: A.Schmidt-Rehschuh
   made  : 09.04.2000

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//----------------------------------------------------------------------------//
//--- class CCPCustomerProperties (dialog) -----------------------------------//
//----------------------------------------------------------------------------//

class ppCustomerDisplay;
class CCPCustomerProperties : public CDialogMultiLang
{
public: // Konstruktion
    CCPCustomerProperties(CWnd* pParent = NULL);   // Standardkonstruktor
    ~CCPCustomerProperties();

    enum { IDD = IDD_CU_CUSTOMER_PROPERTIES };
    CButton m_CButtonCallGeneral;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnButtonCustomer();
    DECLARE_MESSAGE_MAP()

protected: //methodes
    void SetHeader();
    bool GetCustomer();
    void MakeEditable();

protected: //members
    ppCustomerDisplay* m_pCustomer;
};
