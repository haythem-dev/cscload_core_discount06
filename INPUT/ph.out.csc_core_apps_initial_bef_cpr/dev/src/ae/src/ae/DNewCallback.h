#pragma once
#include <callback.h>
#include<vector>
using namespace std;

class CKNDINF;

// CDNewCallback-Dialogfeld

class CDNewCallback : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDNewCallback)

public:
    CDNewCallback(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDNewCallback();

    long    m_lKritiknr;
    short   m_sBranchno;
    short   m_sAuswahl;
    short   m_sAuswahlReason;
    long    m_lIdf;
    long    m_lPosNr;
    CString m_cDivision;
    CString m_cReason;
    short   m_sLevel;
    long    m_lStartNoCallback;
    long    m_lEndNoCallback;

    enum { IDD = IDD_AE_RR_NEU };

    CDateTimeCtrl    m_DT_Zeit;
    CDateTimeCtrl    m_DT_Datum;
    CEdit            m_EditGrund;
    CButton          m_CBKundeWunsch;
    CString          m_CGrund;
    BOOL             m_bKundeWunsch;
    CString          m_CTitel;
    CString          m_CContact;
    CEdit            m_EditContact;
    CStringArray     m_ReasonMail;
    CComboBox        m_CoboxRRWish;
    CEdit            m_EditReference;

protected:
    CCALLBACKDIVISION    m_division;
    CCALLBACKTIME        m_Callbacktime;
    CCALLBACKITEMS       m_Callbackitem;

    CTM      zeit;
    short    m_rrzeit;

    void GetReasons();

    vector<short>    m_nurMailTab;
    vector<short>    m_ReasonnoTab;
    CWnd            *m_ButtonTab1[16];
    CWnd            *m_ButtonTab2[16];
    CListCtrl        m_ListCtlDivision;
    CListCtrl        m_ListCtlReason;

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButton101();
    afx_msg void OnBnClickedButton102();
    afx_msg void OnBnClickedButton103();
    afx_msg void OnBnClickedButton104();
    afx_msg void OnBnClickedButton105();
    afx_msg void OnBnClickedButton106();
    afx_msg void OnBnClickedButton107();
    afx_msg void OnBnClickedButton108();
    afx_msg void OnBnClickedButton109();
    afx_msg void OnBnClickedButton110();
    afx_msg void OnBnClickedButton111();
    afx_msg void OnBnClickedButton112();
    afx_msg void OnBnClickedButton113();
    afx_msg void OnBnClickedButton114();
    afx_msg void OnBnClickedButton115();
    afx_msg void OnBnClickedButton116();
    afx_msg void OnBnClickedButton201();
    afx_msg void OnBnClickedButton202();
    afx_msg void OnBnClickedButton203();
    afx_msg void OnBnClickedButton204();
    afx_msg void OnBnClickedButton205();
    afx_msg void OnBnClickedButton206();
    afx_msg void OnBnClickedButton207();
    afx_msg void OnBnClickedButton208();
    afx_msg void OnBnClickedButton209();
    afx_msg void OnBnClickedButton210();
    afx_msg void OnBnClickedButton211();
    afx_msg void OnBnClickedButton212();
    afx_msg void OnBnClickedButton213();
    afx_msg void OnBnClickedButton214();
    afx_msg void OnBnClickedButton215();
    afx_msg void OnBnClickedButton216();
    afx_msg void OnChangeEditGrund();
    virtual void OnOK();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    afx_msg void OnBnClickedButtonUnkritisch();
    afx_msg void OnBnClickedButtonKritisch();
    afx_msg void OnBnClickedButtonSehrKritisch();
    afx_msg void OnLvnItemchangedListDivision(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLvnItemchangedListReason(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

private:
    void sendMail(CString& rrWish);
    CString getMailSubject();
    CString getMailText(CString& rrWish);
    CString formatMailText(CKNDINF& knd, CString& username, CString& rrWish);
};
