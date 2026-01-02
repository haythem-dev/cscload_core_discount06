#pragma once

// DParAufArt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDParAufArt dialog

class CDParAufArt : public CDialogMultiLang
{
// Construction
public:
    CDParAufArt(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PAR_AART };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void ReadDataInListBox();
    void AddPosToList(CString AArt, CString AText, CString AGlobal, CString AStandard);

    virtual void OnOK();
    virtual void OnCancel();
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDel();
    afx_msg void OnButtonNeu();
    afx_msg void OnButtonUpd();
    DECLARE_MESSAGE_MAP()
};
