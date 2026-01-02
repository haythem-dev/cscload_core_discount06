#pragma once


// CDConnect-Dialogfeld

class CDConnect : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDConnect)

public:
    CDConnect(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDConnect();

    enum { IDD = IDD_HP_CONNECT };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonBack();
    virtual BOOL DestroyWindow();
    DECLARE_MESSAGE_MAP()
};
