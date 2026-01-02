#pragma once

#include <atltime.h>


// CDTourSperr-Dialogfeld

class CDTourSperr : public CDialogMultiLang, CPageBrowser
{
    DECLARE_DYNAMIC(CDTourSperr)

public:
    CDTourSperr(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDTourSperr();

// Dialogfelddaten
    enum { IDD = IDD_AE_TOURSPERRE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedCheckZuVz();
    afx_msg void OnEnChangeEditVz();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonMarkAll();
    afx_msg void OnBnClickedButtonSperr();
    afx_msg void OnBnClickedButtonEntsperr();
    afx_msg void OnLvnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);

    CEdit m_edit_Ab;
    CString m_cAb;
    CButton m_CB_ZuVz;
    CListCtrl m_ListCtl;
    CDateTimeCtrl m_DT_Zeit;
    CComboBox m_Combo_Fili;
    virtual BOOL OnInitDialog();
    CTime m_CT_Zeit;
    CImageList m_ImageSmall;
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);    // List-Box mit Eintraegen versorgen
    void Update();          // List-Box abarbeiten
    void SelectEintrag();
    void SetMarked(int pos);    //Markieren Tour für Update
    void DelMarked(int pos);    //Entfernen Markierung

private:
    CTOURSPERRE m_TourSperre;
};
