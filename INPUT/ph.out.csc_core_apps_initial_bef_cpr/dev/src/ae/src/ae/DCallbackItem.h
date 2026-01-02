#pragma once

// DCallbackItem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDCallbackItem dialog
#include <vector>
using namespace std;

class CDCallbackItem : public CDialogMultiLang
{
// Construction
public:
    CDCallbackItem(CWnd* pParent = NULL);   // standard constructor
    long m_lKritiknr;
    long m_lIdf;
    long m_lPosNr;
    short m_sVz;

    enum { IDD = IDD_AE_RR_ERFASS };
    CDateTimeCtrl m_DT_Zeit;
    CDateTimeCtrl m_DT_Datum;
    CEdit m_EditWotag;
    CEdit m_EditMax;
    CEdit m_EditZeitCalc;
    CEdit m_EditDatumCalc;
    CEdit m_EditTitel;
    CComboBox m_ComboPartner;
    CListCtrl m_ListCtl;
    CEdit m_EditGrund;
    CButton m_CBKundeWunsch;
    CString m_CGrund;
    BOOL  m_bKundeWunsch;
    CString m_CTitel;
    CString m_CDatumCalc;
    CString m_CZeitCalc;
    CString m_CWotag;
    CString m_CMax;
    CEdit   m_EditReference;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CCALLBACKTIME m_Callbacktime;
    CCALLBACKITEMS m_Callbackitem;
    CStringArray m_saDay;
    CCALLBACKPARTNER partner;
    CTM zeit;
    short m_rrzeit;
    struct partners     // Partnereinträge
    {
        long No;
        ppString Name;
        short rr_time;
    };

    vector<partners> pl; // pointer to class list
    vector <partners>::iterator it;

    BOOL GetOfficeTimes();      // List-Box mit Eintraegen versorgen
    void ComputeNextGoodTime(); // errechnen nächstmögliche Rückrufzeit
    // Generated message map functions
    afx_msg void OnChangeEditGrund();
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnSelchangeComboPartner();
    afx_msg void OnDatetimechangeDatetimepickerRrDatum(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

private:
    void GetSelectedPartner(long& callbackpartno, short& callbacktime);
    void ComputeTime(long lDate, long lTime);
};
