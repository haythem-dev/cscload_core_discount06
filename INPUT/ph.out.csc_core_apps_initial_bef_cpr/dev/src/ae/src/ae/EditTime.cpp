// EditTime.cpp : implementation file
//

#include "stdafx.h"
#include "EditTime.h"
#include "ppDataTypes.h"

/////////////////////////////////////////////////////////////////////////////
// CEditTime


CEditTime::CEditTime(long ltime)
{
    m_lTime = ltime;
    ppTime p(m_lTime, ppTime::display_hhmm, true);
    m_csTime = (const char*)p;
    m_lTime = (const long)p;

}

CEditTime::~CEditTime()
{
}


BEGIN_MESSAGE_MAP(CEditTime, CEdit)
    ON_WM_CHAR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTime message handlers

void CEditTime::OnChar(UINT c,UINT /*l*/,UINT /*f*/)
{
    if (c < '0' || c > '9')
        return;
    int start = 0;
    int stop = 0;
    int startalt = 0;
    int stopalt = 0;
    int vor = 0;
    int nach = 0;

    GetSel(startalt, stopalt);
    CString buffer;
    buffer.Format("%c", c);
    ReplaceSel(buffer);
    GetWindowText(m_csTime);
    GetSel(start, stop);
    if (start == startalt)
        ++start;

    vor = m_csTime.GetLength();
    ppTime p(m_csTime, ppTime::display_hhmm, true);
    if (p.GetState() == ppTime::is_false)
    {
        AfxMessageBox( "Fehler in Eingabe");
    }

    m_csTime = (const char*)p;
    m_lTime = (const long)p;
    nach = m_csTime.GetLength();
    SetWindowText(m_csTime);
    if (nach > vor)
        ++start;
    if (start < nach)
    {
        if (m_csTime.GetAt(start) == ':')
            ++start;
    }
    SetSel(start, start, FALSE);
}

CString CEditTime::GetTimeChar()
{
    return m_csTime;
}

long CEditTime::GetTimeLong()
{
    return m_lTime;
}

void CEditTime::SetTimeChar(CString s)
{
    ppTime p(s, ppTime::display_hhmm, true);
    m_csTime = (const char*)p;
    m_lTime = (const long)p;
    SetWindowText(m_csTime);
}

void CEditTime::SetTimeLong(long l)
{
    ppTime p(l, ppTime::display_hhmm, true);
    m_csTime = (const char*)p;
    m_lTime = (const long)p;
    SetWindowText(m_csTime);
}
