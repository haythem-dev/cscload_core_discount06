
//(c)---------- Customer service program -------------------------------------//
/*
   Source: NMDText.cpp
   Author: A.Schmidt-Rehschuh
   made  : 30.04.2002

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "NMDText.h"

//----------------------------------------------------------------------------//
//---public-methodes ---------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- SetText ----------------------------------------------------------------//

void CNMDText::SetText(const ppString& strText)
{
    m_strText = strText;
    SetText();
}

//--- StartMessage -----------------------------------------------------------//

void CNMDText::StartMessage()
{
    m_bIsStart = true;
}

//--- EndMessage -------------------------------------------------------------//

void CNMDText::EndMessage()
{
    m_bIsStart = false;
    ShowButton();
}

//--- AddMessage -------------------------------------------------------------//

bool CNMDText::AddMessage(const ppString& strMessage)
{
    if (m_bIsStart)
    {
        m_strMessage = strMessage;
        AddMessage();
    }

    return m_bIsStart;
}

//--- ClearMessage -----------------------------------------------------------//

void CNMDText::ClearMessage()
{
    CleanEdit();
}

//----------------------------------------------------------------------------//
//--- class CNMDProgress (not modal dialog) ----------------------------------//
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CNMDText::CNMDText(const ppString& strText)
{
    m_bIsStart = false;
    m_bIsInit = false;
    m_strText = strText;
}

//--- DoDataExchange ---------------------------------------------------------//

void CNMDText::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDOK, m_CButtonOK);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_CEditMsg);
}

//--- Create -----------------------------------------------------------------//

BOOL CNMDText::Create()
{
    if (CDialogMultiLang::Create(CNMDText::IDD))
    {
        GetDlgItem(IDOK)->ShowWindow(FALSE);
        return TRUE;
    }
    return FALSE;
}

//--- DestroyWindow ----------------------------------------------------------//

BOOL CNMDText::DestroyWindow()
{
    return CDialogMultiLang::DestroyWindow();
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CNMDText, CDialogMultiLang)
    ON_WM_SIZE()
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CNMDProgress message handlers (ClassWizard) ----------------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CNMDText::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_bIsInit = true;
    SetText();
    SetEditSize();
    return TRUE;
}

//--- (ClassWizard)OnSize ----------------------------------------------------//

void CNMDText::OnSize(UINT nType, int cx, int cy)
{
    CDialogMultiLang::OnSize(nType, cx, cy);
    SetEditSize();
}

//--- (ClassWizard)OnOK ------------------------------------------------------//

void CNMDText::OnOK()
{
    DestroyWindow();
}

//--- (ClassWizard)OnCancel --------------------------------------------------//

void CNMDText::OnCancel()
{
}

//----------------------------------------------------------------------------//
//---protected-methodes ------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- SetText ----------------------------------------------------------------//

void CNMDText::SetText()
{
    SetWindowText(m_strText);
}

//--- SetEditSize ------------------------------------------------------------//

void CNMDText::SetEditSize()
{
    if (!m_bIsInit)
        return;

    const int ciRand = 5;
    CRect rSize;
    GetClientRect(rSize);

    CRect rOld;

    m_CButtonOK.GetClientRect(rOld);
    m_CButtonOK.ClientToScreen(rOld);
    ScreenToClient(rOld);
    int iHeight = rOld.bottom - rOld.top;
    int iWidth  = rOld.right - rOld.left;
    int iLenght = rSize.right - rSize.left;
    int iRight  = rSize.left + iWidth;

    CRect recButton;
    recButton.top     = (rSize.bottom - ciRand - iHeight );
    recButton.left    = (iRight - iWidth) + 5;
    recButton.bottom  = (rSize.bottom - ciRand);
    recButton.right   = iRight + 5;
    m_CButtonOK.MoveWindow(recButton);

    rSize.bottom = rSize.bottom - iHeight - ciRand - 10;
    rSize.right = iLenght - 10;
    rSize.left = 5;
    rSize.top = 5;
    m_CEditMsg.MoveWindow(rSize);
}

//--- ShowButton ------------------------------------------------------------//

void CNMDText::ShowButton()
{
    GetDlgItem(IDOK)->ShowWindow(TRUE);
}

//--- AddMessage ------------------------------------------------------------//

void CNMDText::AddMessage()
{
    CString csTxt;
    m_CEditMsg.GetWindowText(csTxt);

    ppString strNew = m_strMessage;
    strNew.exchange(NEW_LINE,LINE_FEED);
    csTxt += strNew;
    m_CEditMsg.SetWindowText(csTxt);
    m_CEditMsg.LineScroll(m_CEditMsg.GetLineCount() );
    m_CEditMsg.RedrawWindow();
}

//--- CleanMessage -----------------------------------------------------------//

void CNMDText::CleanEdit()
{
    m_CEditMsg.Clear();
}
