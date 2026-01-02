//(c)---------- Customer service program -------------------------------------//
/*
   Source: NMDProgress.h
   Author: A.Schmidt-Rehschuh
   made  : 11.07.2000

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//----------------------------------------------------------------------------//
//--- class CNMDProgress (not modal dialog) ----------------------------------//
//----------------------------------------------------------------------------//

class CNMDProgress : public CDialogMultiLang
{
public: // Construction
    CNMDProgress(const UINT nLower = 0, const UINT nUpper = 100);   // standard constructor

public: // methodes
    void SetMaxCount(const UINT nMax);
    void SetTimer(const UINT nSec);
    void SetRange(const UINT nLower, const UINT nUpper);
    void SetProgress(const int iPos = 0);
    void SetText(const CString& csText);

// Dialog Data
    enum { IDD = IDD_NMDPROGRESS };
    CProgressCtrl m_CProgressCtrl;

public:
    virtual BOOL DestroyWindow();
    virtual BOOL Create();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
    virtual void OnCancel();
    DECLARE_MESSAGE_MAP()

protected: //members
    int m_iLower;
    int m_iUpper;
    int m_iTimer;
    int m_iCount;
    int m_iMax;
    CString m_csText;
};
