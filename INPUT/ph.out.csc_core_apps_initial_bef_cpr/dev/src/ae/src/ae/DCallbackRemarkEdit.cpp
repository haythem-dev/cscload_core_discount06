// DCallbackRemarkEdit.cpp : implementation file
//

#include "stdafx.h"
#include "DCallbackRemarkEdit.h"


// CDCallbackRemarkEdit dialog

IMPLEMENT_DYNAMIC(CDCallbackRemarkEdit, CDialog)

CDCallbackRemarkEdit::CDCallbackRemarkEdit(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCallbackRemarkEdit::IDD, pParent)
    , m_CBHead(_T(""))
    , m_CBText(_T(""))
    , m_CBTextFree(_T(""))
{
    m_lRemarkNo = 0;
}

CDCallbackRemarkEdit::~CDCallbackRemarkEdit()
{
}

void CDCallbackRemarkEdit::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_HEADER, m_CBHead);
    DDX_Text(pDX, IDC_EDIT_TEXT, m_CBText);
    DDX_Text(pDX, IDC_EDIT_TEXT_FREE, m_CBTextFree);
}


BEGIN_MESSAGE_MAP(CDCallbackRemarkEdit, CDialogMultiLang)
END_MESSAGE_MAP()


// CDCallbackRemarkEdit message handlers
void CDCallbackRemarkEdit::OnOK()
{
    UpdateData();
    CDialogMultiLang::OnOK();
}
