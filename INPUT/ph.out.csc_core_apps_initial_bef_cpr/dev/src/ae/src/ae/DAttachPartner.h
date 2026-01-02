#pragma once

// DAttachPartner.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAttachPartner dialog
#include <vector>
using namespace std;

class CDAttachPartner : public CDialogMultiLang
{
// Construction
public:
    CDAttachPartner(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_CALLBACK_TERM };
    CButton m_CB_Vz;
    CListCtrl m_List1;
    CListCtrl m_List2;
    long m_lStartNoCallback;
    long m_lEndNoCallback;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    long m_lUid;        // Eigene Benutzer-ID
    struct partners     // Partnereinträge
    {
        long No;
        short Vz;
        ppString Name;
    };

    vector<partners> pl; // pointer to class list
    vector <partners>::iterator it;

    // Generated message map functions
    afx_msg void OnButtonDef();
    afx_msg void OnButtonUndef();
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnDestroy();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnCheckVz();
    DECLARE_MESSAGE_MAP()

    void FillList();
};
