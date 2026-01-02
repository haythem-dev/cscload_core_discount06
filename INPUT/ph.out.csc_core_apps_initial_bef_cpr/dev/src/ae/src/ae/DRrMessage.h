#pragma once

// DRrMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDRrMessage dialog

class CDRrMessage : public CDialogMultiLang
{
// Construction
public:
    CDRrMessage(CWnd* pParent = NULL);   // standard constructor
    CDRrMessage(CView* pWview);
    BOOL Create();

// Dialog Data
    enum { IDD = IDD_AE_RR_MESSAGE };


// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    // Generated message map functions
    virtual void OnCancel();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

private:
    CView* m_pView;
};
