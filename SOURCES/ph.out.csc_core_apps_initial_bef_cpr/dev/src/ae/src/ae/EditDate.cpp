// EditDate.cpp : implementation file
//

#include "stdafx.h"
#include "EditDate.h"
#include "ppDataTypes.h"

/////////////////////////////////////////////////////////////////////////////
// CEditDate

CEditDate::CEditDate(long datum)
{
    m_lDatum = datum;
    if (m_lDatum != 0)
        m_csDatum.Format("%.2ld.%.2ld.%.4ld",
            datum % 100L,
            (datum % 10000L) / 100L,
            (datum / 10000L));
}

CEditDate::~CEditDate()
{
}


BEGIN_MESSAGE_MAP(CEditDate, CEdit)
    ON_WM_CHAR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDate message handlers

void CEditDate::OnChar(UINT c,UINT /*l*/,UINT /*f*/)
{
    if (c < '0' || c > '9')
        return;
    int startalt, stopalt;
    GetSel(startalt, stopalt);
    CString buffer;
    buffer.Format("%c", c);
    ReplaceSel(buffer);
    GetWindowText(m_csDatum);
    CheckDatum();
    int start, stop;
    GetSel(start, stop);
    SetWindowText(m_csDatum);
    if (start == 2 || start == 5)
        ++start;
    SetSel(start, start, FALSE);
}

CString CEditDate::GetDateChar()
{
    CheckDatum();
    CheckCentury();
    SetWindowText(m_csDatum);
    SetSel(11, 11, FALSE);
    return m_csDatum;
}

long CEditDate::GetDateLong()
{
    CheckDatum();
    if (!CheckCentury())
        return -1L;
    m_lDatum = (atol(m_csDatum.Right(4)) * 10000) +
                (atol(m_csDatum.Mid(3,2)) * 100) +
                (atol(m_csDatum.Left(2)));
    SetWindowText(m_csDatum);
    SetSel(11, 11, FALSE);
    return m_lDatum;
}

void CEditDate::SetDateChar(CString s)
{
    m_csDatum = s;
    CheckDatum();
    SetWindowText(m_csDatum);
}

void CEditDate::SetDateLong(long l)
{
    m_csDatum.Format("%.2ld.%.2ld.%.4ld",
                    l % 100L,
                    (l % 10000L) / 100L,
                    (l / 10000L));
    SetWindowText(m_csDatum);
}

bool CEditDate::CheckCentury()
{
    CString buffer = m_csDatum;
    CTime t = CTime::GetCurrentTime();;
    int jahr = t.GetYear();
    if (m_csDatum.GetLength() == 6)
    {
        m_csDatum.Format("%s%d", buffer.GetString(), jahr);
        return true;
    }
    else if (m_csDatum.GetLength() == 8)
    {
        m_csDatum.Format("%6.6s%d%2.2s", buffer.GetString(), jahr/100, buffer.Right(2).GetString());
        return true;
    }
    else if (m_csDatum.GetLength() == 10)
    {
        return true;
    }
    else
        return false;
}

void CEditDate::CheckDatum()
{
    CString buffer;
    ppString str = m_csDatum;
    str.remove('.');
    m_csDatum = str;
    int len = m_csDatum.GetLength();
    for (;;)    // dient nur zum vorzeitigen weitermachen bei Ende string
    {
        // Tag
        buffer = m_csDatum.Left(2);
        if (atoi(buffer) > 31)
        {
            m_csDatum = '0' + m_csDatum;
            ++len;
        }
        if (len > 1)
            m_csDatum = m_csDatum.Left(2) + '.' + m_csDatum.Right(len - 2);
        ++len;
        // Monat
        if (len < 4)
            break;
        buffer = m_csDatum.Left(5);
        buffer = buffer.Right(buffer.GetLength() == 5 ? 2 : 1);
        if (atoi(buffer) > 12)
        {
            m_csDatum = m_csDatum.Left(3) + '0' + m_csDatum.Right(len - 3);
            ++len;
        }
        if (len > 4)
            m_csDatum = m_csDatum.Left(5) + '.' + m_csDatum.Right(len - 5);
        ++len;
        if (len < 7)
            break;
        // Jahr
        if (len > 10)
            m_csDatum = m_csDatum.Left(10);
        break;
    }
}
