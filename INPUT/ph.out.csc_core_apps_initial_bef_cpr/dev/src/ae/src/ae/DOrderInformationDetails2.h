#pragma once

#include "PageTabCtrlMultiLang.h"
#include "ppDataTypes.h"
#include "TabPageMultiLang.h"


// CDOrderInformationDetails2 dialog

class CDOrderInformationDetails2 : public CTabPageMultiLang
{
    DECLARE_DYNAMIC(CDOrderInformationDetails2)

public:
    CDOrderInformationDetails2();
    virtual ~CDOrderInformationDetails2();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_AE_ORDER_INFORMATION_DETAILS2 };
#endif

    void FillList();

    int m_listpos;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual LPCTSTR GetTabTitle();
    virtual int GetID() { return IDD; }
    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
    DECLARE_MESSAGE_MAP()

    CListCtrl m_ListCtlDetails2;
};
