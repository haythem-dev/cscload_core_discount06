// StaticRun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticRun window
#ifndef _STATICRUN_
#define _STATICRUN_

class CStaticRun : public CStatic
{
// Construction
public:
    CStaticRun();
    CStaticRun(int id);

// Attributes
public:
    int m_Id;
    BOOL m_Timer;

    // Operations
public:
// Overrides
    // ClassWizard generated virtual function overrides

// Implementation
public:
    virtual ~CStaticRun();

    // Generated message map functions
protected:
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnPaint();
    afx_msg void OnDestroy();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    DECLARE_MESSAGE_MAP()
};

#endif
