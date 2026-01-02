#pragma once

// DCallbackUpd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDCallbackUpd dialog
#include "DDruckAuftrag.h"
#include "CallbackStatusManager.h"

class CDCallbackUpd : public CDialogMultiLang
{
    // Construction
public:
    CDCallbackUpd(CWnd* pParent = NULL);   // standard constructor
    long m_lKritiknr;
    long m_lRRNr;
    long m_lIdf;
    short m_sVzNr;
    CString m_Titel;
    bool m_bAuftr;
    bool m_bCall;
    CStatic m_Static_Bitmap;
    long m_lRemarkno;
    CString m_RemarkHead;
    CString m_RemarkText;
    CString m_RemarkTextFree;
    CCALLBACKREMARKS m_remarks;
    void NewFax();

    enum { IDD = IDD_AE_RR_BEARB };
    CEdit   m_EditText;
    CString m_CText;
    CString m_CGrund;
    CString m_CApotheke;
    CString m_CIdf;
    CString m_CInhaber;
    CString m_COrt;
    CString m_CPlz;
    CString m_CTel;
    CString m_CKw;
    CString m_CWertig;
    CString m_CFaxNr;
    CString m_CUser;
    CString m_CStrasse;
    CString m_CEmail;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    CCALLBACKITEMS m_RRItem;
    CCallbackStatusManager m_CallbackStatusManager;

    afx_msg void OnChangeEditText();
    afx_msg void OnButtonRr();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    afx_msg void OnButtonShift();
    afx_msg void OnButtonDruck();
    afx_msg void OnButtonAuftrag();
    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnBnClickedButtonMakeCall();
    afx_msg void OnCbnSelchangeComboCBRemarks();
    afx_msg void OnBnClickedButtonFax();
    afx_msg void OnBnClickedButtonMail();
    DECLARE_MESSAGE_MAP()

    void Zeilendruck(CAeOutputs& aeOutputs, CString text);
    void SetBitmap(const UINT id);
    int WriteAttachment();

    CBitmap     m_Bitmap;
    bool        m_bHasPicture;
    CDC         m_dcMem;
    CRect       m_Rect;
    BITMAP      m_bmInfo;
    char        filenameattach[81];
    CButton     m_CB_MakeCall;
    CComboBox   m_Cobox_CBRemarks;
    CComboBox   m_ComboStatus;
    CEdit       m_EditStatus;
    CEdit       m_EditReference;
};
