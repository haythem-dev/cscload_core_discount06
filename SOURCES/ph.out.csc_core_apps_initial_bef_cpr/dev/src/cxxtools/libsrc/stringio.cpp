/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

Class nString:
I/O functions.


*/
/*  $History: STRINGIO.CPP $ */
/*  */
/* *****************  Version 4  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:05 */
/* Updated in $/cxxtools/src */
/* Final release. */
/* *********************************************** */
#include "string.hpp"
#include <ctype.h>
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/*  The string is reading into pieces of buflen (15) characters.              */
/*  When a buffer is filled, it grows and the string is copied into           */
/*  the new buffer. At least the new 'length_' is calculated.                 */
/*  The delimter is not extracted and not stored.                             */
/*----------------------------------------------------------------------------*/
std::istream&
nString :: ReadToDelimiter
(
	std::istream& strm,
    const nString& delim
)
{
    size_t aktpos    = 0;
    bool ready      = false;
    const size_t buflen = 15;

    // Get memory for first part of string.
    AllocBuffer(buflen);

    // Reading until EOF or delimiter detected.
    while (!ready && !strm.bad() && !strm.fail())
    {
       char ch = ' ';
       bool delimfound = false;

       // Fill the buffer with characters.
       while (aktpos < bufsize_ &&
              ((delimfound = (delim.FindChar(ch = (char) strm.get()) < delim.length_)) == false)
                  && !strm.eof() && !strm.bad() && !strm.fail())
          datap_[aktpos++] = ch;

       if (!strm.bad() && !strm.fail())
       {
          // Ready because reading EOF or delimiters ?
          if (strm.eof() || delimfound)
          {
             ready = true;
             strm.putback(ch);
          }
          else
          {
             // String is greater than buffer. A new one.
             ConcatInPlace(buflen, "");
          }
       }
    }

    if (strm.bad() || strm.fail())
    {
       Clear();
    }
    else
    {
       // EOS
       datap_[aktpos] = '\0';

       // new length_ of string
       length_ = aktpos;
    }

    return strm;
}

/*----------------------------------------------------------------------------*/
/*  Reads a whole line from istream. EOL is not extracted and not stored.     */
/*  Leading whitespaces are extracted but not stored if skipwhite==true.      */
/*----------------------------------------------------------------------------*/
std::istream&
nString :: ReadLine
(
	std::istream& strm,
    const bool skipwhite
)
{
    if (skipwhite)
       strm >> std::ws;

    if (strm.eof() || strm.bad() || strm.fail())
    {
       // Exist no line.
       Clear();

       return strm;
    }
    else
       return ReadToDelimiter(strm, "\n");
}

/*----------------------------------------------------------------------------*/
/*  Reads a token from istream. Token is separated by whitespaces.            */
/*  The whitespace after the token is not extracted and not stored.           */
/*----------------------------------------------------------------------------*/
std::istream&
nString :: ReadToken
(
	std::istream& strm,
    const nString& extrachars
)
{
    nString allchars = "\x20\x09\x0a\x0b\x0c\x0d" + extrachars;

    char ch = ' ';

    while (!strm.eof() && !strm.bad() && !strm.fail() &&
           allchars.FindChar(ch = (char) strm.get()) < allchars.length_);

    if (strm.eof() || strm.bad() || strm.fail())
    {
       // Exist no token.
       Clear();

       return strm;
    }
    else
    {
       strm.putback(ch);

       return ReadToDelimiter(strm, allchars);
    }
}
