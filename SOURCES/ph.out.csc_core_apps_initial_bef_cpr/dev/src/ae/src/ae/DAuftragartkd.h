#pragma once

// DAuftragartKd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAuftragartKd dialog

class CDAuftragartKd : public CDialogMultiLang
{
// Construction
public:
    CDAuftragartKd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    enum { IDD = IDD_AE_AUFTRAGARTKD };
    CEdit m_Edit_Valutamonauto;
    CEdit m_Edit_Valutamon;
    CEdit m_Edit_Idf;
    CEdit m_Edit_Aart;
    CButton m_CBEfg;
    CButton m_CBDel;
    BOOL m_bStockReservation;
    BOOL m_bBANR;
    BOOL m_bMonatrab;
    BOOL m_bNatra;
    BOOL m_bNetto;
    BOOL m_bValutasperre;
    BOOL m_bVerbund;
    CString m_CAart;
    CString m_CIdf;
    CString m_CValutamon;
    CString m_CValutamonauto;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnButtonDel();
    afx_msg void OnButtonEfg();
    afx_msg void OnChangeEditAart();
    afx_msg void OnChangeEditIdf();
    afx_msg void OnChangeEditValutamon();
    afx_msg void OnChangeEditValutamonauto();
    afx_msg void OnChangeEditSockReservation();
    virtual void OnCancel();
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonKndwahl();
    DECLARE_MESSAGE_MAP()
};
