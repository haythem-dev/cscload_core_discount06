
//(c)---------- Customer service program -------------------------------------//
/*
   Source: NMDProgress.cpp
   Author: A.Schmidt-Rehschuh
   made  : 12.07.2000

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "NMDProgress.h"

//----------------------------------------------------------------------------//
//---public-methodes ---------------------------------------------------------//
//----------------------------------------------------------------------------//

void CNMDProgress::SetText(const CString& csText)
{
    m_csText = csText;
}

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CNMDProgress::CNMDProgress(const UINT nLower, const UINT nUpper)
{
    m_iTimer = -1;
    m_iCount = 1;
    m_iMax   = 0;
    m_csText = "";
    SetRange(nLower, nUpper);
}

//--- DoDataExchange ---------------------------------------------------------//

void CNMDProgress::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PROGRESS, m_CProgressCtrl);
}

//--- Create -----------------------------------------------------------------//

BOOL CNMDProgress::Create()
{
    return CDialogMultiLang::Create(CNMDProgress::IDD);
}

//--- DestroyWindow ----------------------------------------------------------//

BOOL CNMDProgress::DestroyWindow()
{
    if (m_iTimer > -1)
        KillTimer(m_iTimer);
    return CDialogMultiLang::DestroyWindow();
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CNMDProgress, CDialogMultiLang)
    ON_WM_TIMER()
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CNMDProgress message handlers (ClassWizard) ----------------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CNMDProgress::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    if (!m_csText.IsEmpty() )
       GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(m_csText);

    m_CProgressCtrl.SetRange(static_cast<short>(m_iLower), static_cast<short>(m_iUpper));
    return TRUE;
}

//--- (ClassWizard)OnTimer ---------------------------------------------------//

void CNMDProgress::OnTimer(UINT nIDEvent)
{
    SetProgress();
    CDialogMultiLang::OnTimer(nIDEvent);
}

//--- (ClassWizard)OnCancel --------------------------------------------------//

void CNMDProgress::OnCancel()
{
    return; //no esc allowed!
}

//----------------------------------------------------------------------------//
//--- public methodes --------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- SetMax -----------------------------------------------------------------//

void CNMDProgress::SetMaxCount(const UINT nMax)
{
    m_iMax = nMax;
}

//--- SetTimer ---------------------------------------------------------------//

void CNMDProgress::SetTimer(const UINT nSec)
{
    m_iTimer = CDialogMultiLang::SetTimer( CNMDProgress::IDD, nSec * 1000, NULL );
}

//--- SetRange ---------------------------------------------------------------//

void CNMDProgress::SetRange(const UINT nLower, const UINT nUpper)
{
    m_iLower = nLower;
    m_iUpper = nUpper;
    m_iMax   = m_iMax == 0 ? nUpper : m_iMax;
}

//--- SetPos -----------------------------------------------------------------//

void CNMDProgress::SetProgress(const int iPos)
{
    m_CProgressCtrl.SetPos(iPos > 0 ? iPos * 100 / m_iMax : m_iCount * 100 / m_iMax);
    if (m_iCount++ > m_iUpper)
        m_iCount = 0;
}
