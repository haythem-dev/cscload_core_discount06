#pragma once


// CDCountDown-Dialogfeld

class CDCountDown : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCountDown)

public:
    CDCountDown(CWnd* pParent = NULL);   // Standardkonstruktor
    CDCountDown(CView* pWview);
    BOOL Create();
    void SetBitmap(const UINT id);
    virtual ~CDCountDown();

    enum { IDD = IDD_AE_TOUR_COUNTDOWN };
    CStatic m_Static_Bitmap;
    CEdit   m_Edit_Text;
    CString m_CText;
    UINT    m_id;
    long    m_lCountDown;
    BYTE    m_red;
    BYTE    m_green;
    BYTE    m_blue;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnPaint();
    afx_msg void OnDestroy();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()

private:
    CView* m_pView;
    CBitmap m_Bitmap;
    bool m_bHasPicture;
    CDC m_dcMem;
    HBITMAP m_hBmpOld;
    CRect m_Rect;
    BITMAP  m_bmInfo;
};
