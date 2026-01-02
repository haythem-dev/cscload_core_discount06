#pragma once

#include "PageTabCtrlMultiLang.h"
#include "ppDataTypes.h"
#include "TabPageMultiLang.h"


// CDOrderInformationDetails5 dialog

class CDOrderInformationDetails5 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderInformationDetails5)

public:
    CDOrderInformationDetails5();
    virtual ~CDOrderInformationDetails5();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDER_INFORMATION_DETAILS5 };
#endif

    void FillList();

    int m_listpos;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    virtual BOOL OnSetActive();
    virtual LPCTSTR GetTabTitle();
    virtual int GetID() { return IDD; }
    DECLARE_MESSAGE_MAP()

    CListCtrl m_ListCtlDetails5;
};
