#pragma once

#include "PageTabCtrlMultiLang.h"
#include "ppDataTypes.h"
#include "TabPageMultiLang.h"


// CDOrderInformationDetails3 dialog

class CDOrderInformationDetails3 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderInformationDetails3)

public:
    CDOrderInformationDetails3();
    virtual ~CDOrderInformationDetails3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDER_INFORMATION_DETAILS3 };
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

    CListCtrl m_ListCtlDetails3;
};
