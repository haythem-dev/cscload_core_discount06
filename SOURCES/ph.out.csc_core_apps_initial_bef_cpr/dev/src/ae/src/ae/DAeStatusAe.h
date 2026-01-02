#pragma once

// DAeStatusAe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAeStatusAe dialog
#include <vector>
using namespace std;

class CDAeStatusAe : public CDialogMultiLang
{
// Construction
public:
    CDAeStatusAe(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_STATUS_AE };
    CButton m_CBRr;
    CButton m_CBKc;
    CComboBox m_CComboMinuten;
    CListCtrl m_ListCtl_Zur;
    CListCtrl m_ListCtl;
    CString m_CStringComboBox;
    CString m_cTasks;
    CString m_Sort1;
    CString m_Sort2;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
    void AusgabeDaten();
    void ShowDiffToTime();  // (anrufplan)anzeige idfnr u. zeitdiff in minuten
    void AusgabeListBox(CListCtrl *list, CString Status);
    void Alarm(int bAlarm = TRUE);
    int  m_bAlarmTimer;
    int  m_bAlarm;
    void SortList(int sortfield);
    void LookforRr();   // Überprüfen, ob neue, nicht bearbeitete Rückrufe vorhanden sind
    void LookforKc();   // Überprüfen, ob neue, nicht bearbeitete Kommidefekte vorhanden sind

    vector<long> m_pl; // pointer to class list
    vector <long>::iterator m_it;

    vector<long> m_plold; // pointer to class list
    vector <long>::iterator m_itold;

    CCALLBACKTODO m_callback;
    CCALLBACKTODONEW m_callbacknew;

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnCheckAlarm();
    afx_msg void OnCheckSort();
    afx_msg void OnButtonRr();
    afx_msg void OnButtonKc();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLvnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()
};
