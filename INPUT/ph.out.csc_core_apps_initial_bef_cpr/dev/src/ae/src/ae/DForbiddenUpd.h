#pragma once

#include <atltime.h>


// CDForbiddenUpd-Dialogfeld

class CDForbiddenUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDForbiddenUpd)

public:
    CDForbiddenUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDForbiddenUpd();

// Dialogfelddaten
    enum { IDD = IDD_AE_FORBIDDEN_UPD };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    DECLARE_MESSAGE_MAP()

public:
    CEdit m_edit_Word;
    CString m_CWord;
    CDateTimeCtrl m_DT_From;
    CTime m_CT_From;
    CDateTimeCtrl m_DT_To;
    CTime m_CT_To;
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnEnChangeEditWord();
    long m_lDateFrom;
    long m_lDateTo;
    int m_iFunktion;    //0 == update, 1 == insert
};
