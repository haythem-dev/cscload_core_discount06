#pragma once

// DCheckNachl.h : header file
//
#include <nachlief.h>

/////////////////////////////////////////////////////////////////////////////
// CDCheckNachl dialog

class CDCheckNachl : public CDialogMultiLang
{
// Construction
public:
    CDCheckNachl(CWnd* pParent = NULL);   // standard constructor
    long m_lArtikelnr;
    long m_lIdf;
    long m_lMenge;
    CNACHLIEF m_nachl;
    CString m_cAArt;

    enum { IDD = IDD_AE_CHECK_NACHL };
    CListCtrl m_ListCtl;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnButtonNewPos();
    virtual void OnCancel();
    DECLARE_MESSAGE_MAP()
};
