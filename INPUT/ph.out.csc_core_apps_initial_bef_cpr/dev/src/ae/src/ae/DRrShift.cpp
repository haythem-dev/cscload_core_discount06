// DRrShift.cpp : implementation file
//

#include "stdafx.h"
#include "DRrShift.h"

#define MAXIMUM_ZEIT_SHIFT  1440

/////////////////////////////////////////////////////////////////////////////
// CDRrShift dialog


CDRrShift::CDRrShift(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDRrShift::IDD, pParent)
{
    m_CShiftTime = _T("");
}


void CDRrShift::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_SHIFT_TIME, m_EditShiftTime);
    DDX_Text(pDX, IDC_EDIT_SHIFT_TIME, m_CShiftTime);
}


BEGIN_MESSAGE_MAP(CDRrShift, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_SHIFT_TIME, OnChangeEditShiftTime)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRrShift message handlers

void CDRrShift::OnChangeEditShiftTime()
{
    AllgWertKontr(&m_EditShiftTime, MAXIMUM_ZEIT_SHIFT);
}
