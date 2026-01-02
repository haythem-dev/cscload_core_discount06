#pragma once


// CDUserInfo-Dialogfeld

class CDUserInfo : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDUserInfo)

public:
    CDUserInfo(CWnd* pParent = NULL);   // Standardkonstruktor
    CDUserInfo(CView* pWview);
    BOOL Create();
    virtual ~CDUserInfo();

    enum { IDD = IDD_AE_USER_INFO };

    CStatic m_Static_Bitmap;
    CString m_cUserInfo;
    short m_sPrio;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnPaint();
    afx_msg void OnDestroy();
    afx_msg void OnButtonRead();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );

    DECLARE_MESSAGE_MAP()

private:
    CView* m_pView;
    CBitmap m_Bitmap;
    bool m_bHasPicture;
    CDC m_dcMem;
    HBITMAP m_hBmpOld;
    CRect m_Rect;
    BITMAP  m_bmInfo;

protected: //methodes
    void RepositionWindow();
    void SetBitmap(const UINT id);
};
