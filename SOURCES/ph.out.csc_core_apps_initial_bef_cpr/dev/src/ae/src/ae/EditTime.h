#pragma once

// EditTime.h : header file
//
// spezielles Edit-Feld zur Eingabe des Datums

/////////////////////////////////////////////////////////////////////////////
// CEditTime window

class CEditTime : public CEdit
{
// Construction
public:
    CEditTime(long ltime = 0);
    virtual ~CEditTime();

// Attributes
public:
    long m_lTime;
    CString m_csTime;

// Operations
public:
    CString GetTimeChar();
    long GetTimeLong();
    void SetTimeChar(CString);
    void SetTimeLong(long);

protected:
    afx_msg void OnChar(UINT c,UINT l,UINT f);
    DECLARE_MESSAGE_MAP()
};
