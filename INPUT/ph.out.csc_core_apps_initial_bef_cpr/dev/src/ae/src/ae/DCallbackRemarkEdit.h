#pragma once


// CDCallbackRemarkEdit dialog

class CDCallbackRemarkEdit : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCallbackRemarkEdit)

public:
    CDCallbackRemarkEdit(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDCallbackRemarkEdit();

// Dialog Data
    enum { IDD = IDD_AE_DCALLBACKREMARKS_EDIT };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()
public:
    CString m_CBHead;
    CString m_CBText;
    CString m_CBTextFree;
    long m_lRemarkNo;
};
