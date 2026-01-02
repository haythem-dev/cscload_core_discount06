#pragma once

#include "PageTabCtrlMultiLang.h"
#include "ppDataTypes.h"
#include "TabPageMultiLang.h"


// CDOrderInformationDetails4 dialog

class CDOrderInformationDetails4 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderInformationDetails4)

public:
    CDOrderInformationDetails4();
    virtual ~CDOrderInformationDetails4();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDER_INFORMATION_DETAILS4 };
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

    CListCtrl m_ListCtlDetails4;
    int m_listpos;
};
