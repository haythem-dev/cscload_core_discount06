#pragma once

// DMailNew.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMailNew dialog
#include <vector>
using namespace std;

class CDMailNew : public CDialogMultiLang
{
// Construction
public:
    CDMailNew(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_NEW_MAIL };
    CButton m_CBTip;
    CEdit m_Edit_Zeit;
    CEdit m_Edit_Text;
    CEdit m_Edit_Datum;
    CComboBox m_Combo_Group;
    CString m_CDatum;
    CString m_CText;
    CString m_CZeit;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CTM zeit;
    long m_lDatum;
    long m_lZeit;
    struct gruppe       // Gruppeneinträge
    {
        long No;
        ppString Name;
    };

    vector<gruppe> m_pl; // pointer to class list
    vector <gruppe>::iterator m_it;

    // Generated message map functions
    afx_msg void OnChangeEditDatum();
    afx_msg void OnChangeEditText();
    afx_msg void OnChangeEditZeit();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};
