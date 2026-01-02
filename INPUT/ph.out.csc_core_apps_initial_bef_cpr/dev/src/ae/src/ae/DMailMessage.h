#pragma once

// DMailMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDMailMessage dialog

class CDMailMessage : public CDialogMultiLang
{
// Construction
public:
    CDMailMessage(CWnd* pParent = NULL);   // standard constructor
    CDMailMessage(CView* pWview);
    BOOL Create();
    long m_lNewsno;
    int m_iFilialnr;
    long m_lUid;

    enum { IDD = IDD_AE_MAIL_MESSAGE };
    CStatic m_Static_Bitmap;
    CEdit m_Edit_Text;
    CString m_CText;
    CString m_CDatum;
    CString m_CZeit;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void GetText();
    void SetBitmap(const UINT id);

    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnPaint();
    afx_msg void OnDestroy();
    afx_msg void OnButtonDruck();
    afx_msg void OnBnClickedButtonRead();
    DECLARE_MESSAGE_MAP()

private:
    CView* m_pView;
    CBitmap m_Bitmap;
    bool m_bHasPicture;
    CDC m_dcMem;
    HBITMAP m_hBmpOld;
    CRect m_Rect;
    BITMAP m_bmInfo;
};
