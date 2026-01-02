/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

Class nSubString:
Implementation.


*/
/*  $History: STRINGSB.CPP $ */
/*  */
/* *****************  Version 4  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:05 */
/* Updated in $/cxxtools/src */
/* Final release. */
/* *********************************************** */
#include "string.hpp"
#include <stdexcept>

/*----------------------------------------------------------------------------*/
/*               Implementation of Class nSubstring                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  Constructor for nSubstring from String                                    */
/*----------------------------------------------------------------------------*/
nSubString :: nSubString
(
    const nString& str,
    size_t beg,
    size_t length
)
:   dest((nString*)&str),
    start(beg),
    len(length)
{
    if (!str.IsEmpty() || beg != 0 || length != 0)
    {
       //assert(str.CheckIndex(beg));
       if (!str.IsEmpty() && beg != 0 && !str.CheckIndex(beg))
       {
          // nMessage ueberlisten
          char cstr[17];
          sprintf(cstr, "%ld", static_cast<long>(beg));
          throw std::out_of_range(cstr);
//          THROW(nBoundsErr(nMessage("Index %s out of range [0-%u]",
//                                   cstr, (*dest).length_-1).String()));
       }

       if (length != 0)
       {
          //assert(str.CheckIndex(beg+length-1) && str.CheckIndex(length - 1));
          if (!str.CheckIndex(beg+length-1))
          {
             char cstr[17];
             sprintf(cstr, "%ld", static_cast<long>(beg+length-1));
             throw std::out_of_range(cstr);
//             THROW(nBoundsErr(nMessage("Index %s out of range [0-%u]", cstr,
//                               (*dest).length_ == 0 ? 0 : (*dest).length_-1).String()));
          }

          if (!str.CheckIndex(length-1))
          {
             char cstr[17];
             sprintf(cstr, "%ld", static_cast<long>(length));
             throw std::out_of_range(cstr);
//             THROW(nBoundsErr(nMessage("Length %s out of range [0-%u]", cstr,
//                               (*dest).length_ == 0 ? 0 : (*dest).length_-1).String()));
          }

       }
    }
}

/*----------------------------------------------------------------------------*/
/*  A substring is overwritten (replaced) by a string.                        */
/*  A new array of char is allocated without to forget the old string and it  */
/*  length. The first part of the new string is copy from the old one into    */
/*  the new one (0-'start'). Next part is 'str'. The last part is after the   */
/*  substring to the end ('oldlength'-('start'+'len')).                       */
/*----------------------------------------------------------------------------*/
nSubString&
nSubString :: operator =
(
    const nString& str
)
{
    if (!(*dest).IsEmpty())
    {
       char *olddatap = dest->datap_;
       size_t oldlength = dest->length_;

       (*dest).AllocBuffer(oldlength + str.length_ - len);
       (*dest).length_ = 0;
       (*dest).ConcatInPlace(start, olddatap);
       (*dest).ConcatInPlace(str.length_, str.datap_);
       (*dest).ConcatInPlace(oldlength -start-len, &olddatap[start + len]);
       FreeBuffer(olddatap);
    }
    return *this;
}


/*----------------------------------------------------------------------------*/
/*  A substring is overwritten (replaced) by another string.                  */
/*  See for more information in description of preceding function             */
/*----------------------------------------------------------------------------*/
nSubString&
nSubString :: operator =
(
    const nSubString& substr
)
{
    return operator = (nString(substr));
}

/*----------------------------------------------------------------------------*/
/*  Returns a reference to the indexed character.                             */
/*----------------------------------------------------------------------------*/
char&
nSubString :: operator []
(
    size_t pos
)
{
    //assert(0 <= pos && pos < len);
    if (pos >= len)
    {
       // nMessage ueberlisten
       char strpos[17];
       sprintf(strpos, "%ld", (long)pos);
       throw std::out_of_range(strpos);
//       THROW(nBoundsErr(nMessage("Index %s out of range [0-%u]",
//                                strpos, len-1).String()));
    }

    return (*dest)[start+pos];
}



/*----------------------------------------------------------------------------*/
/*                Implementation of that part of Class nString                */
/*           which cooperates with indices or with Class nSubString.          */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  Constructor for nString with data from nSubString.                        */
/*----------------------------------------------------------------------------*/
nString :: nString
(
    const nSubString& src
)
{
    AllocBuffer(src.len);
    memcpy(datap_, &(src.dest->datap_[src.start]), src.len);
}

/*----------------------------------------------------------------------------*/
/*  Returns a substring by pointer on nString. 'pos' is the first character   */
/*  of the substring and the substring has 'length' characters.               */
/*----------------------------------------------------------------------------*/
nSubString
nString :: operator ()
(
    size_t pos,
    size_t length
)
{
    return nSubString(*this, pos, length);
}

/*----------------------------------------------------------------------------*/
/*  Returns a reference to the indexed character.                             */
/*----------------------------------------------------------------------------*/
char&
nString :: operator []
(
    size_t pos
)
{
    //assert(CheckIndex(pos));
    if (!CheckIndex(pos))
    {
       // nMessage ueberlisten
       char strpos[17];
       sprintf(strpos, "%ld", (long)pos);
       throw std::out_of_range(strpos);
//       THROW(nBoundsErr(nMessage("Index %s out of range [0-%u]",
//                                strpos, length_-1).String()));
    }
    return datap_[pos];
}

/*----------------------------------------------------------------------------*/
/*  Beginning from position 'start' searches for 'substr' with 'substrlength' */
/*  characters. Ignores case for 'com == nString::cIGNORE. Respects case for  */
/*  'com == nString::cEXACT'. Returns the position when found,                */
/*  else a position greater then 'this->Length()'.                            */
/*----------------------------------------------------------------------------*/
size_t
nString :: FindSubString
(
    const nString& substr,
    size_t substrlength,
    size_t start,
    tCOMPARE com
)
const
{
    size_t pos = start;
    bool found = false;

    // meaningless 'substrlength' ?
    if (substrlength == 0 || substrlength > substr.length_)
       pos = length_ + 1;

    while (!found && pos <= length_)
    {
       // Are both first chars equal ?
       if ((com == cEXACT && datap_[pos] == substr.datap_[0]) ||
           (com == cIGNORE && tolower(datap_[pos]) == tolower(substr.datap_[0]))
          )
       {
          bool sub = true;

          // Compare rest of substring with string.
          for (size_t len = 1; sub && len < substrlength; len++)
          {
             if ((com == cEXACT && datap_[pos+len] != substr.datap_[len]) ||
                 (com == cIGNORE &&
                  tolower(datap_[pos+len]) != tolower(substr.datap_[len]))
                )
                sub = false;  // neq
          }
          if (sub)
             found = true;
          else
             ++pos;
       }
       else
          ++pos;
    }

    return pos;
}

