#pragma once


// CDSeperateGrp-Dialogfeld

class CDSeperateGrp : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSeperateGrp)

public:
    CDSeperateGrp(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSeperateGrp();

    enum { IDD = IDD_AE_SEPERAT_GRP };
    CListCtrl m_ListCtl;
    CStringArray m_Gruppen;
    CSEPORDERGRP m_SepOrder;

    void FillList();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonInsert();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};
