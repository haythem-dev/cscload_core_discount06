#pragma once


// CDUmsHercode-Dialogfeld

class CDUmsHercode : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDUmsHercode)

public:
    CDUmsHercode(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDUmsHercode();

    enum { IDD = IDD_AE_ANZ_UMS_HERCODE };
    CListCtrl m_ListCtl;
    long m_lAufnr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};
