#pragma once

// TabPageMultilang.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabPageMultiLang dialog


class CTabPageMultiLang : public CPropertyPageMultiLang
{
    //DECLARE_DYNCREATE(CTabPage)

// Construction
public:
    CTabPageMultiLang(int nIDP =0);
    ~CTabPageMultiLang();

// Attrbiutes
public:
    bool m_bModified;
    bool m_bEnabled;
    CString m_csTitle;
    bool m_bIsChanged; 
    bool m_bIsActive;

    int IDD;

    void SetTabTitle(CString cs);
    virtual int GetID() { return IDD; }
    virtual LPCTSTR GetTabTitle() { return m_csTitle; }
    virtual bool IsChanged() { return m_bIsChanged; }
    virtual bool IsModified() { return m_bModified; }
    virtual void SetIsChanged(const bool bIsChanged = true) { m_bIsChanged = bIsChanged; }
    virtual void SetData() {};
    virtual void SetIsActive(const bool bIsActive = true) { m_bIsActive = bIsActive; }
    virtual bool UpdateServer() { return true; }
    virtual bool InsertServer() { return true; }
    virtual bool DeleteServer() { return true; }
    virtual bool OtherServer() { return true; }
    virtual void OnButtonHistory() {}
    virtual void Initialize() {} 
    virtual const int GetCountItem() const { return 0; }

    virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
};
