#pragma once


// CDAufWerte-Dialogfeld

class CDAufWerte : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDAufWerte)

public:
    CDAufWerte(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDAufWerte();

    enum { IDD = IDD_AE_AUFWERTE };
    CListCtrl m_List1;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
};
