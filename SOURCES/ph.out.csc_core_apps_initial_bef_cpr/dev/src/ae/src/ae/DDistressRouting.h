#pragma once


// CDDistressRouting-Dialogfeld

class CDDistressRouting : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDDistressRouting)

public:
    CDDistressRouting(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDDistressRouting();

// Dialogfelddaten
    enum { IDD = IDD_AE_DISTRESS_ROUTING };
    CListCtrl m_ListCtl1;
    CListCtrl m_ListCtl2;
    CComboBox m_combo_DestBranch;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonRemove();
    afx_msg void OnCbnSelchangeComboDestBranch();
    afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLvnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

private:
    CDISTRESSROUTING m_Distress;
    short m_sDestBranch;
    int m_iCountlist1;
    int m_iCountlist2;
    int m_iCol1;
    int m_iOrder1;
    int m_iCol2;
    int m_iOrder2;
    CImageList m_ImageSmall;
};
