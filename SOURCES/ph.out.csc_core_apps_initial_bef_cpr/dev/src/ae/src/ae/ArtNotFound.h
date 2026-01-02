#pragma once


// CArtNotFound dialog

class CArtNotFound : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CArtNotFound)

public:
    CArtNotFound(CWnd* pParent = NULL);   // standard constructor
    virtual ~CArtNotFound();

    enum { IDD = IDD_AE_ART_NOT_FOUND };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonGoogle();
    afx_msg void OnButtonInfo();
    CString m_cFehltext;
    CString m_cBezeichnung;
    bool m_bNoShort;
    long m_lArtNo;
    bool m_bAufnahme;
};
