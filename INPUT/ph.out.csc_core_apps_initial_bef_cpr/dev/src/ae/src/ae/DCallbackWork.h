#pragma once

// DCallbackWork.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDCallbackWork dialog

class CDCallbackWork : public CDialogMultiLang
{
// Construction
public:
    CDCallbackWork(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_CALLBACK_WORK };
    CButton m_CBUpd;
    CButton m_CBNew;
    CButton m_CBDel;
    CComboBox m_ComboTag;
    CEdit   m_EditVon;
    CEdit   m_EditBis;
    CString m_CBis;
    CString m_CVon;
    CString m_CTag;
    CString m_CPartner;
    long    m_lPartnerNo;           // Partnernumer
    short   m_lVon;                 // Beginnzeit
    bool    m_new;                  // Kennz. ob insert oder update
    CString m_Tag;                  // Wochentag

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void SetTag();

    afx_msg void OnChangeEditBis();
    afx_msg void OnChangeEditVon();
    afx_msg void OnButtonDel();
    afx_msg void OnButtonNew();
    afx_msg void OnButtonUpd();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};
