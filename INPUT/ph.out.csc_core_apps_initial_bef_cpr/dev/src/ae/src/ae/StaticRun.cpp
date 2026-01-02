// StaticRun.cpp : implementation file
//

#include "stdafx.h"
#ifndef _STATICRUN_
    #include "StaticRun.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticRun
CStaticRun::CStaticRun()
{
    m_Timer = FALSE;
}

CStaticRun::CStaticRun(int id)
{
    m_Id = id;
}

CStaticRun::~CStaticRun()
{
}


BEGIN_MESSAGE_MAP(CStaticRun, CStatic)
    ON_WM_TIMER()
    ON_WM_PAINT()
    ON_WM_DESTROY()
    ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticRun message handlers

void CStaticRun::OnTimer(UINT nIDEvent)
{
    if (nIDEvent == 1000) {
        CString curText;
        GetWindowText(curText);
        int len = curText.GetLength();
        // only if the text exceeds a certain length we need to scroll it
        // the length to start scrolling should be a parameter to this
        // class or even better it should compute if the text does not
        // fit into the available space and then start scrolling
        // automatically
        if (len > 110)
        {
            CString left = curText.Left(1);
            curText = curText.Right(len - 1);
            curText += left;
        }
        SetWindowText((LPCTSTR)curText);
    }

    CStatic::OnTimer(nIDEvent);
}

void CStaticRun::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (!m_Timer) {
        SetTimer(1000, 90, NULL);
        m_Timer = TRUE;
    }

    // Do not call CStatic::OnPaint() for painting messages
}

void CStaticRun::OnDestroy()
{
    CStatic::OnDestroy();
    KillTimer(1000);
}

int CStaticRun::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}
