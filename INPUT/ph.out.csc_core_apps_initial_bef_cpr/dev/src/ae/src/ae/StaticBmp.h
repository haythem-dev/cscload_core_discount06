//(c)---------- Customer service program -------------------------------------//
/*
   Source: StaticBmp.h
   Author: A.Schmidt-Rehschuh
   made  : 23.08.2000

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//----------------------------------------------------------------------------//
//--- class CStaticBmp (Control) ---------------------------------------------//
//----------------------------------------------------------------------------//

class CStaticBmp : public CStatic
{
public: // Construction
    CStaticBmp();

public: // Operations
    virtual void CStaticBmp::SetBitmap(const UINT id);
    virtual const CRect& CStaticBmp::GetWndRect() const;
    virtual const int GetWidth() const;
    virtual const int GetHeight() const;
    virtual void Move(const CRect& r);

public: // Implementation
    virtual ~CStaticBmp();

protected: // Generated message map functions
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()

protected: //members
    bool    m_bHasPicture;
    CBitmap m_Bitmap;
    CDC     m_dcMem;
    CRect   m_RectSize;
    BITMAP  m_bmInfo;
};
