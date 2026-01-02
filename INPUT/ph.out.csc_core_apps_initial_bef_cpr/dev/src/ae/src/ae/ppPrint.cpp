/*---------------------------------------------------------------------------*/
/* ppPrint.cpp: classmethodes for printing                                   */
/*---------------------------------------------------------------------------*/

#include "stdafx.h"
#include "ppPrint.h"

//----- Class ppPrint --------------------------------------------------------/
//----- Constructor ( initialize objekt ) ------------------------------------/

    ppPrint::ppPrint( CDC *pCdc, const ppString& strFont, const ppString& strDocumentName,
                      const ppString& strLetter, int /*iCount*/, const int iRandr,
                      const int iRandl, const int iLine, const int iMaxLine )
                      :c_iMaxLine( iMaxLine ), c_iStartLine( iLine )
    {
        m_iPage       = 1;
        m_pFont       = NULL;
        m_pCdc        = pCdc;
        m_iLine       = iLine;
        m_iRandr      = iRandr;
        m_iRandl      = iRandl;
        m_strLetter   = strLetter;
        m_iPercentage = 0;
        m_bPage       = false;

        if (!(pCdc->GetCurrentFont()->GetLogFont(&m_lFont)))
        {
            AfxMessageBox( "error in getlogfont!" );
        }

        TEXTMETRIC tMetr;
        pCdc->GetTextMetrics(&tMetr);
        m_lFont.lfWidth  = 0;
        m_lFont.lfHeight = tMetr.tmHeight * -1;

        SetFont(NORMAL, strFont);

        DOCINFO sDocument;
        sDocument.cbSize      = sizeof(DOCINFO);
        sDocument.lpszDocName = strDocumentName.c_str();
        sDocument.lpszOutput  = NULL;
        sDocument.fwType = NULL;

        m_iIsPrint = m_pCdc->StartDoc(&sDocument);

        if (!m_iIsPrint)
        {
            AfxMessageBox( "Doc not started" );
        }
        else
        {
            pStartPage();
        }
    }

//----- Deconstructor ( delete objekt ) --------------------------------------/

    ppPrint::~ppPrint()
    {
        if (m_pFont)
            delete m_pFont;
    }

//----- Function:StartPrint --------------------------------------------------/

    bool ppPrint::StartPrint(const ppString& strDocumentName)
    {
        if (!m_iIsPrint)
        {
            m_bPage = false;
            m_iPage = 1;
            DOCINFO sDocument;
            sDocument.cbSize      = sizeof( DOCINFO );
            sDocument.lpszDocName = strDocumentName.c_str();
            sDocument.lpszOutput  = NULL;
            sDocument.fwType = NULL;
            m_iIsPrint = m_pCdc->StartDoc( &sDocument );
        }

        pStartPage();
        return m_iIsPrint ? true : false;
    }

//----- Function:EndPrint ----------------------------------------------------/

    bool ppPrint::EndPrint()
    {
        pEndPage();
        m_pCdc->EndDoc();
        return true;
    }

//----- Function:PrintHeader -------------------------------------------------/

    int ppPrint::PrintHeader(const ppString& strText, int iTime)
    {
        ppPCTime t;
        int iLine = GetLine();
        ppString strTime = t.GetCurrentDateTime(iTime);

        int iC1 = PrintColumn(strText, 0);
        SetLine(iLine);
        int iC2 = PrintColumn(strTime, GetWidth() - strTime.length());
        return SetLine(iC1 >= iC2 ? GetLine() - (iC1 - iC2) + 2 : GetLine() + 2);
    }


//----- Function:EndPrint ----------------------------------------------------/

    int ppPrint::Print(const ppString& strBuf, const int iLine, const int iRand)
    {
        if (m_pCdc->TextOut(m_iCx * (iRand + m_iRandr), m_iCy * m_iLine, strBuf.c_str(), strBuf.length()))
        {
            if ((m_iLine += iLine) >= c_iMaxLine - 2)
            {
                pStartPage();
            }
            return 1;
        }

        return 0;
    }

//----- Function:PrintColumn ---------------------------------------------------/

    int ppPrint::PrintColumnStatic(const ppString& strComment, const int iRandr)
    {
        int iMaxByte = GetWidth(iRandr);
        ppString strText = strComment;
        int iStrLen = strComment.length();

        pUnsetNoPrintChar(strText);

        if (iStrLen <= iMaxByte)
        {
            Print(strText, 0, iRandr);
            return iRandr;
        }
        else
        {
            EmptyLine(1);
            Print(strText, 0, 0);
            return 0;
        }
    }

//----- Function:PrintColumn (mit jeweils fester Spalten vorgabe---------------------------//

    int ppPrint::PrintColumn(const ppString& strComment, const int iRandr, const int iLine)
    {
        int iMaxByte = GetWidth(iRandr);
        int iStrLen = strComment.length();
        ppString strText = strComment;
        int iLen;
        int i = 0;
        int iCountLine = 0;
        int iSumLen = 0;
        int iEmpty = 0;
        ppString::iterator irStr;

        pUnsetNoPrintChar(strText);

        if (iStrLen <= iMaxByte)
            return Print(strText, iLine, iRandr);

        while (iSumLen < iStrLen)
        {
            ppString* p_str = new ppString(strText.begin() + iSumLen, strText.end());
            iLen = p_str->length() > static_cast<unsigned int>(iMaxByte) ? iMaxByte - 1 : p_str->length() - 1;
            if (!iLen)
                break;
            else if (iLen < iMaxByte - 1)
                i = iLen;
            else
            {
                for (i = iLen; i > 0 && p_str->at(i) != ' '; i--)
                {
                    //do nothing
                }

                p_str->erase(p_str->begin() + i, p_str->end());
            }
            // erase blanc at the beginnig if there are
            for (iEmpty = 0; iEmpty < i && p_str->at(iEmpty) == ' '; iEmpty++)
            {
                //do nothing
            }

            p_str->erase(p_str->begin(), p_str->begin() + iEmpty);

            Print(*p_str, iLine, iRandr);
            delete p_str;
            ++iCountLine;
            iSumLen += i + 1;
        }

        return iCountLine;
    }

//----- Function:EndPrint ----------------------------------------------------/

    bool ppPrint::EmptyLine(int iLine)
    {
        m_iLine += iLine;
        return true;
    }

//----- Function:SetRandr ----------------------------------------------------/

    int ppPrint::SetRandr(const int iRand)
    {
        m_iRandr = iRand;
        return m_iRandr;
    }

//----- Function:SetRandl ----------------------------------------------------/

    int ppPrint::SetRandl(const int iRand)
    {
        m_iRandl = iRand;
        return m_iRandl;
    }

//----- Function:GetRandr ----------------------------------------------------/

    int ppPrint::GetRandr()
    {
        return m_iRandr;
    }

//----- Function:GetRandl ----------------------------------------------------/

    int ppPrint::GetRandl()
    {
        return m_iRandl;
    }

//----- Function:SetLine -----------------------------------------------------/

    int ppPrint::SetLine(const int iLine)
    {
        m_iLine = iLine;
        return m_iLine;
    }

//----- Function:GetLine -----------------------------------------------------/

    int ppPrint::GetLine()
    {
        return m_iLine;
    }

//----- Function:GetWidth ----------------------------------------------------/

    int ppPrint::GetWidth(int iRight, int iLeft)
    {
        int iRandr = (iRight == 0) ? m_iRandr : m_iRandr + iRight;
        int iRandl = (iLeft == 0) ? m_iRandl : m_iRandl + iLeft;

        int iWidth = (m_pCdc->GetDeviceCaps(HORZRES) - ((iRandr + iRandl) * m_iCx)) / m_iCx;
        return iWidth;
    }

//----- Function:SetFont -----------------------------------------------------//

    bool ppPrint::SetFont(int iType, const ppString& strFont)
    {
        CFont* pFont = pGetFont(iType, strFont);

        if (!pFont)
        {
            return false;
        }
        //int iCsytem = m_pCdc->SetMapMode( MM_TEXT );
        m_pCdc->SelectObject(pFont);
        pSetNewSize();

        return true;
    }

//----- Function:SetSize -----------------------------------------------------/

    void ppPrint::SetSize(int iPercentage)
    {
        m_iPercentage = iPercentage;
        pSetNewSize();
    }

//----- Private --------------------------------------------------------------/

//----- Function:GetFont -----------------------------------------------------/

    CFont* ppPrint::pGetFont(int iType, const ppString& strFont)
    {
        if (!pAllocateFont())
            return NULL;

        if (!strFont.empty())
            pStrToChar(m_lFont.lfFaceName, strFont);

        if (iType & BOLD && iType & UNDERLINE)
        {
            m_lFont.lfWeight = FW_BOLD;
            m_lFont.lfUnderline = true;
        }
        else if (iType & UNDERLINE)
        {
            m_lFont.lfWeight = FW_NORMAL;
            m_lFont.lfUnderline = true;
        }
        else if (iType & BOLD)
        {
            m_lFont.lfWeight = FW_BOLD;
            m_lFont.lfUnderline = false;
        }
        else if (iType & NORMAL)
        {
            m_lFont.lfWeight = FW_NORMAL;
            m_lFont.lfUnderline = false;
        }
        else if (iType & VARIABLE)
        {
            m_lFont.lfWeight = FW_NORMAL;
            m_lFont.lfUnderline = false;
        }
        else
            return NULL;

        if (!m_pFont->CreateFontIndirect(&m_lFont))
            return NULL;

        return m_pFont;
    }

//----- Function:pCheckFont --------------------------------------------------/

    bool ppPrint::pAllocateFont()
    {
        if (m_pFont)
            delete m_pFont;

        CFont* pFont = new CFont();
        m_pFont = pFont;

        return true;
    }

//----- Function:UnsetNoPrintChar --------------------------------------------/

    void ppPrint::pUnsetNoPrintChar(ppString& strBuf)
    {
        int iLen = strBuf.length();

        for (int i = 0; i < iLen; i++)
        {
            char ch = strBuf.at(i);
            if (ch == '\0')
                break;
            if (ch == 10 || ch == 13)
                strBuf.at(i) = ' ';
        }
    }

//----- Function:SetNewSize --------------------------------------------------/

    void ppPrint::pSetNewSize()
    {
        CSize cSize;

        cSize = m_pCdc->GetTextExtent(m_strLetter.c_str(), m_strLetter.length());
        m_iCx = (cSize.cx == 0) ? 60 : cSize.cx;
        m_iCy = (cSize.cy == 0) ? 100 : cSize.cy;

        m_iCx = (m_iCx * (100 + m_iPercentage)) / 100;
        m_iCy = (m_iCy * (100 + m_iPercentage)) / 100;
        m_iMaxRow = m_pCdc->GetDeviceCaps(VERTRES) / m_iCy;
    }

//----- Function:strtochar ---------------------------------------------------/

    int ppPrint::pStrToChar(char* pChar, const ppString& strBuf)
    {
        int iLen = strBuf.length();

        int i = 0;
        for (; i < iLen; i++)
        {
           pChar[i] = strBuf.at(i);
        }
        pChar[i] = '\0';
        return i;
    }

//----- Function:pEndPage ----------------------------------------------------/

    bool ppPrint::pEndPage()
    {
        if (m_iIsPrint && m_bPage)
        {
            ppString strBuf;
            strBuf.itos(m_iPage++);
            strBuf = "Page " + strBuf;
            int iRand = (GetWidth(GetRandr(), GetRandl()) / 2) - (strBuf.length() / 2) + GetRandl();
            m_pCdc->TextOut(m_iCx * iRand, m_iCy * c_iMaxLine, strBuf.c_str(), strBuf.length());

            m_bPage = false;
            m_pCdc->EndPage();
            return true;
        }
        return false;
    }

//----- Function:pStartPage --------------------------------------------------/

    bool ppPrint::pStartPage()
    {
        pEndPage();
        if (m_iIsPrint && !m_bPage)
        {
            m_iLine = c_iStartLine;
            m_bPage = true;
            m_pCdc->StartPage();
            return true;
        }
        return false;
    }
