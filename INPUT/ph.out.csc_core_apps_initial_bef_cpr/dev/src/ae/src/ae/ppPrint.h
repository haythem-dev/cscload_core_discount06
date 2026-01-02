#pragma once

//ppPrint.h

#include <wingdi.h>
#include "ppTime.h"

using namespace std;

class ppPrint
{
    CDC*    m_pCdc;
    CFont*  m_pFont;
    LOGFONT m_lFont;
    int     m_iMaxRow;
    int     m_iIsPrint;
    int     m_iRandr;
    int     m_iRandl;
    int     m_iLine;
    int     m_iPercentage;
    int     m_iCx;
    int     m_iCy;
    int     m_iX;
    int     m_iY;
    bool    m_bPage;
    int     m_iPage;
    const int c_iMaxLine;
    const int c_iStartLine;
    ppString m_strLetter;

public:
    enum FontStyle
    {
        VARIABLE  = 0x00000001,
        NORMAL    = 0x00000002,
        BOLD      = 0x00000004,
        UNDERLINE = 0x00000008
    };

    ppPrint(CDC* pCdc, const ppString& strFont = "", const ppString& strDocumentName = "",
        const ppString& strLetter = "x", int iCount = 1, const int iRandr = 6,
        const int iRandl = 3, const int iLine = 3, const int iMaxLine = 67);
    ~ppPrint();

    bool StartPrint(const ppString& strDocumentName);
    bool EndPrint();
    int  PrintHeader(const ppString& strText = "", int iTime = ppPCTime::TIME | ppPCTime::DATE);
    int  Print(const ppString& strBuf, const int iLine = 1, const int iRand = 0);
    int  PrintColumn(const ppString& strComment, const int iRand = 0, const int iLine = 1);
    int  PrintColumnStatic(const ppString& strComment, const int iRandr); //variable Spalte, Text gleich lang
    bool EmptyLine(int iLine = 1);
    bool SetFont(int iType, const ppString& strFont = "" /*Times New Roman*/);
    int  SetRandr(const int iRand = 1);
    int  SetRandl(const int iRand = 1);
    int  GetRandr();
    int  GetRandl();
    int  SetLine(const int iLine = 1);
    int  GetLine();
    int  GetWidth(int iRigth = 0, int iLeft = 0);
    void SetSize(int iPercentage = 0);  // smaller = -1 bigger = +1
    void pUnsetNoPrintChar(ppString& strBuf);

private:
    CFont* pGetFont(int iType, const ppString& strFont);
    bool   pAllocateFont();
    void   pSetNewSize();
    int    pStrToChar(char* pChar, const ppString& strBuf);
    bool   pStartPage();
    bool   pEndPage();
};
