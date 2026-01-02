#include "StdAfx.h"
#include "LetterMan.h"


CLetterMan::CLetterMan()
{
    m_kb[0] = '\0';
    m_kb[1] = '\0';
}

CLetterMan::~CLetterMan()
{
}

char* CLetterMan::Next()
{
    if (m_kb[0] == '\0')
    {
        m_kb[0] = AeGetApp()->Letter_A();
        return m_kb;
    }

    ++m_kb[0];
    if (m_kb[0] > AeGetApp()->Letter_Z())
    {
        m_kb[0] = AeGetApp()->Letter_A();
    }

    return m_kb;
}

char* CLetterMan::Current()
{
    if (m_kb[0] == '\0')
    {
        throw - 2;
    }
    return m_kb;
}

void CLetterMan::Reset()
{
    m_kb[0] = '\0';
}

void CLetterMan::SetSeed(char seed)
{
    if ((seed < AeGetApp()->Letter_A()) || (seed > AeGetApp()->Letter_Z()))
    {
        throw - 1;
    }
    m_kb[0] = seed;
}

/*static*/
bool CLetterMan::InRange(WORD key, int listItemCount)
{
    return (key >= AeGetApp()->Letter_A()) && (key < AeGetApp()->Letter_A() + listItemCount);
}


/*static*/
bool CLetterMan::InAZRange(WORD key)
{
    return (key >= AeGetApp()->Letter_A()) && (key <= AeGetApp()->Letter_Z());
}
