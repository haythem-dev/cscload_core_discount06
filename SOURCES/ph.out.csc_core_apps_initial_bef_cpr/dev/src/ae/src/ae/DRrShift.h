#pragma once

// DRrShift.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDRrShift dialog

class CDRrShift : public CDialogMultiLang
{
// Construction
public:
    CDRrShift(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_RR_SHIFT };
    CEdit m_EditShiftTime;
    CString m_CShiftTime;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnChangeEditShiftTime();
    DECLARE_MESSAGE_MAP()
};
