#pragma once

#include "PageTabCtrlMultiLang.h"
#include "ppDataTypes.h"
#include "TabPageMultiLang.h"


// CDOrderInformationDetails1 dialog

class CDOrderInformationDetails1 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderInformationDetails1)

public:
    CDOrderInformationDetails1();
    virtual ~CDOrderInformationDetails1();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDER_INFORMATION_DETAILS1 };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual LPCTSTR GetTabTitle();
    virtual int GetID() { return IDD; }

    DECLARE_MESSAGE_MAP()

public:
    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();

    void FillList();

    CListCtrl m_ListCtlDetails1;
    int m_listpos;
};
