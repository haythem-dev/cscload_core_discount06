#pragma once

// DAeAnzFrText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAeAnzFrText dialog

class CDAeAnzFrText : public CDialogMultiLang
{
// Construction
public:
    CDAeAnzFrText(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_ANZ_FREITEXT };
    CString m_CAePreis;
    CString m_CBemerk;
    CString m_CDarr;
    CString m_CEinh;
    CString m_CGrPreis;
    CString m_CMenge;
    CString m_CName;
    CString m_CRabDM;
    CString m_CRabProz;
    long m_auftragnr;
    long m_posnr;
    long m_datum;
    CComboBox m_ComboTax;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};
