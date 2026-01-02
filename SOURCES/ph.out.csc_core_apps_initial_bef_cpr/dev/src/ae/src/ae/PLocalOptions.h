//(c)---------- Customer service program -------------------------------------//
/*
   Source: PLocalOptions.h
   Author: A.Schmidt-Rehschuh
   made  : 12.03.2001

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//----------------------------------------------------------------------------//
//--- class CPLocalOptions (dialog) ------------------------------------------//
//----------------------------------------------------------------------------//

class CPLocalOptions : public CDialogMultiLang
{
public: // Construction
    CPLocalOptions(CWnd* pParent = NULL);   // standard constructor

public: // Methodes
    const bool IsCallplanWarnOff() const;
    const bool IsProblemCallWarnOff() const;
    const bool IsActivateWnd() const;
    const int GetAutoMinutes() const;
    const int CPLocalOptions::GetAutoMMSeconds() const;
    const int GetWarnCounter() const;
    const int GetCallplanWarnMinutes() const;
    const int GetProblemCallWarnMinutes() const;

    enum { IDD = IDD_CPLOCALOPTIONS };
    CButton m_CButtonActivateWnd;
    CButton m_CButtonProblemCalls;
    CButton m_CButtonCallplan;
    CEdit m_CEditWarnMinProblemcall;
    CEdit m_CEditWarnMin;
    CEdit m_CEditWarnCount;
    CEdit m_CEditAutoMin;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditAutoMin();
    afx_msg void OnChangeEditWarnCount();
    afx_msg void OnChangeEditWarnMin();
    afx_msg void OnChangeEditWarnMinProblemcall();
    DECLARE_MESSAGE_MAP()

protected: //methodes
    void InitData();
    void ShowData();
    bool SaveData();
    bool PutRegistry(const ppString& strKeyID, const ppString& strValue);
    const char* GetRegistry(const ppString& strKeyID);
    const bool CheckEntry(CEdit& CEditCheck, CString& csValue);

protected:
    char m_szBuf[21];
    bool m_bCallplanOff;
    bool m_bProblemCallOff;
    bool m_ActivateWnd;
    UINT m_uAutoMin;
    UINT m_uWarnCount;
    UINT m_uWarnMin;
    UINT m_uWarnMinProblemCall;
};
