#pragma once


// CDReserve-Dialogfeld

class CDReserve : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDReserve)

public:
    CDReserve(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDReserve();

    enum { IDD = IDD_AE_RESERVE };
    CEdit m_edit_PZN;
    CString m_CPZN;
    CEdit m_edit_EKG;
    CString m_CEKG;
    CEdit m_edit_Max;
    CString m_CMax;
    CEdit m_edit_Prozent;
    CString m_CProzent;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonIns();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnBnClickedButtonUpd();
    afx_msg void OnBnClickedButtonPzn();
    afx_msg void OnEnChangeEditPzn();
    afx_msg void OnEnChangeEditEkg();
    afx_msg void OnEnChangeEditPct();
    DECLARE_MESSAGE_MAP()

protected:
    CARTIKELRESERVE m_Reserve;

public:
    CString m_CBestand;
    CEdit m_edit_Bestand;
    CString m_CBestandAct;
    CButton m_CB_Bst;
    BOOL m_bBst;
    int m_Funktion; //0 = prozentual
                    //1 = absolut
};
