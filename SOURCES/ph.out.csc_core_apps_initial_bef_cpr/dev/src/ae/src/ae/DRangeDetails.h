#pragma once


// CDRangeDetails-Dialogfeld

class CDRangeDetails : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDRangeDetails)

public:
    CDRangeDetails(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDRangeDetails();

    enum { IDD = IDD_AE_RANGE_DETAILS };
    CListCtrl m_ListCtl;
    CString m_CRangeNr;
    CString m_CRangeName;
    short m_sBranchNo;
    CString m_CMin;
    CString m_CDone;
    CString m_CSMin;
    CString m_CDiff;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};
