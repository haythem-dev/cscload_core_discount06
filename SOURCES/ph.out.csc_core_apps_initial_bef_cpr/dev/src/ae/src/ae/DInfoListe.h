// DInfoListe.h : header file
//
#ifndef _STATICRUN_
    #include "StaticRun.h"
#endif


class CKOPLIST;

/////////////////////////////////////////////////////////////////////////////
// CDInfoListe dialog

class CDInfoListe : public CDialogMultiLang
{
// Construction
public:
    CDInfoListe(CWnd* pParent = NULL); // standard constructor
    BOOL m_bAufnahme;
    long m_ArtNr;
    CString m_Name;
    BOOL m_Timer;

    enum { IDD = IDD_ARTIKTAB };
    CStaticRun m_StaticInfo;
    CListCtrl m_List1;
    CEdit m_PZN;
    CEdit m_DISPO;
    CEdit m_BEMERK;
    CEdit m_INPUT;
    CButton m_COPY;
    CEdit m_SUCH;
    CEdit m_TEXT1;
    CEdit m_HERSTINFO;
    CButton m_CHK_HERST_BLOCKED;
    CButton m_CHK_HERST_QUALIFIED;
    CButton m_ZURUECK;
    CButton m_WEITER;
    CString m_such;
    CString m_text1;
    CString m_input;
    CString m_bemerk;
    CString m_dispo;
    CString m_pzn;
    CString m_CInfo;
    CString m_ArtCode;
    CEdit m_edit_ArtCode;

protected:
    void MarkListPos(int pos);
    void AddPosToList(char* kb,
                      CString Name,
                      CString AltName,
                      CString Dispo,
                      CString Bemerk,
                      long PZN);
    void ReadFromList(int pos);
    void PosWechseln();
    void ShowHerstInfo(BOOL fShow);

    virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support
    LRESULT OnHookFkt(WPARAM wParam, LPARAM lpMsg);

    afx_msg void OnWeiter();
    afx_msg void OnZurueck();
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    virtual void OnOK();
    afx_msg void OnCopy();
    afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT nIDEvent);

    DECLARE_MESSAGE_MAP()

private:
    void FillList(CKOPLIST& koplist);

    bool declare_switch;
    int seite;
    bool m_bIsVkMenu;
};
