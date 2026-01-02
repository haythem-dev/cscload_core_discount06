
//(c)---------- Customer service program -------------------------------------//
/*
   Source: StaticBmp.cpp
   Author: A.Schmidt-Rehschuh
   made  : 23.08.2000

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "StaticBmp.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CStaticBmp::CStaticBmp()
{
    m_bHasPicture = false;
    m_RectSize.SetRect(0,0,0,0);
}

//--- deconstructor ----------------------------------------------------------//

CStaticBmp::~CStaticBmp()
{
    if (m_bHasPicture)
    {
        m_Bitmap.DeleteObject();
        m_dcMem.DeleteDC();
    }
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CStaticBmp, CStatic)
    ON_WM_PAINT()
END_MESSAGE_MAP()


//----------------------------------------------------------------------------//
//--- public -----------------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- SetBitmap --------------------------------------------------------------//

void CStaticBmp::SetBitmap(const UINT id)
{
    if (m_bHasPicture)
    {
        // Need to DeleteObject() the bitmap which was loaded.
        m_Bitmap.DeleteObject();
        m_dcMem.DeleteDC();
    }

    m_Bitmap.LoadBitmap(id);
    m_Bitmap.GetObject(sizeof(BITMAP), &m_bmInfo);

    CClientDC dc(this);

    m_dcMem.CreateCompatibleDC(&dc);               // DC erzeugen
    m_dcMem.SelectObject(&m_Bitmap);
    GetClientRect(m_RectSize);
    m_bHasPicture = true;
}

//--- GetWndRect -------------------------------------------------------------//

const CRect& CStaticBmp::GetWndRect() const
{
    return m_RectSize;
}

//--- GetWidth ---------------------------------------------------------------//

const int CStaticBmp::GetWidth() const
{
    return m_bmInfo.bmWidth;
}

//--- GetHeight --------------------------------------------------------------//

const int CStaticBmp::GetHeight() const
{
    return m_bmInfo.bmHeight;
}

void CStaticBmp::Move(const CRect& r)
{
    MoveWindow(r);
}

//----------------------------------------------------------------------------//
//--- protected --------------------------------------------------------------//
//----------------------------------------------------------------------------//

void CStaticBmp::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    if (m_bHasPicture)
    {
       CRect Rect;
       GetClientRect(Rect);
       ClientToScreen(Rect);
       ScreenToClient(Rect);
       dc.BitBlt( Rect.left
                , Rect.top
                , m_bmInfo.bmWidth
                , m_bmInfo.bmHeight
                , &m_dcMem
                , 0, 0, SRCCOPY
                );
    }
}
