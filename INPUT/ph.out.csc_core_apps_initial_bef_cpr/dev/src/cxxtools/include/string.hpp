/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

STRING.HPP
Yet another string class.

REVISION HISTORY

22 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.
13 Nov 1995                         Peter Hoernich

*/
/*  $History: STRING.HPP $ */
/*  */
/* *****************  Version 6  ***************** */
/* User: Ck           Date: 30.01.97   Time: 9:55 */
/* Updated in $/cxxtools/inc */
/* Changed stricmp function to own methods, because UNIX have not such */
/* function. */
/*  */
/* *****************  Version 5  ***************** */
/* User: Wh           Date: 22.11.96   Time: 8:29 */
/* Updated in $/cxxtools/inc */
/* Added CompareNoCase() method. */
/*  */
/* *****************  Version 4  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:12 */
/* Updated in $/cxxtools/inc */
/* Final release. */
/* *********************************************** */

/*  Do not allow to include the file more than once                           */
#ifndef NSTRING_INC
#define NSTRING_INC

#include <assert.h>

#ifndef STRINGH_INC
    #define STRINGH_INC
    #include <string.h>
#endif
#ifndef IOSTREAMH_INC
    #define IOSTREAMH_INC
    #include <iostream>
#endif
#ifndef FSTREAMH_INC
    #define FSTREAMH_INC
    #include <fstream>
#endif

/* Forward declarations */
class  nString;
void   FreeBuffer(char *bufp);
size_t SafeStrLen(const char *stp);


/*@CS --------------------------------------------------------------------------
NAME
    nSubString - A generic substring class.

SYNOPSIS
    include "string.hpp"

DESCRIPTION
    Class nSubString represents an substring of the class nString.
    Substrings are results by operations of strings of type nString.
    You can only create a substring by using the public copy constructor.

PUBLIC CONSTRUCTOR
@DE*/
class nSubString
{
private:
    friend class nString;

    nString* dest;    // points to the string
    size_t start;     // and begin at 'start'
    size_t len;       // with 'len' characters

    nSubString (const nString& str, size_t beg, size_t length);
//  Generates a nSubString from a nString, desired start position 'beg'
//  and desired length 'length'

public:
//@DS
    nSubString(const nSubString& sub)
       : dest(sub.dest), start(sub.start), len(sub.len) {;}
//  Copy constructor

/*
PUBLIC MEMBER OPERATORS
*/
    nSubString& operator = (const nString& str);
//  Overwrites (replaces) the substring in nSubString
//  by the string in 'str'. Example : str(0,3) = "abc";

    nSubString& operator = (const nSubString& substr);
//  Overwrites (replaces) the substring in nSubString
//  by the substring in 'substr'. Example : str(0,3) = str(4, 6);

    char& operator [] (size_t pos);
//  Returns a reference to the indexed character.
//  Example: str(2,5)[3]) with 'pos' < 'nSubString::len'.
//@CE
};


/*@CS --------------------------------------------------------------------------
NAME
    nString - A generic string class.

SYNOPSIS
    include "string.hpp"

DESCRIPTION
    Class nString represents a container of a null terminated character string.
    It provides comfortable methods to create an manipulate this containing
    string.

PUBLIC CONSTRUCTORS
@DE*/
class nString
{
public:
    ~nString();

//@DS
    nString();
//  Default constructor constructs an empty string.

    nString(const char *strp);
//  Constructs the nString from a null terminated character string.

    nString(unsigned char ch, size_t repeat = 1);
//  Constructs a string which contains 'repeat'ed times 'ch'.

    nString(unsigned char *bytep, size_t length);
//  Contructs a string containing 'length' characters beginning from 'bytep'.

    nString(const nString& src);
//  Constructs the nString with data of nString src.

    nString(const nSubString& src);
//  Constructs the nString with data of nSubString src.

/*
PUBLIC DATA TYPES
*/
    enum           tPOSITION { cTRAILING, cLEADING, cBOTH };
//  Constants for positions within nString.

    enum           tCOMPARE { cIGNORE, cEXACT };
//  Constants for case sensitivity.

/*
PUBLIC MEMBER FUNCTIONS
*/
    const nString& Clear();
//  Makes the object's instance empty.

    void           Cut();
//  Cuts unused buffer space.

    int            Compare(const nString& str) const
                   {return strcmp(datap_, str.datap_);}
//  Compares the strings contained in two nStrings.
    int            CompareNoCase(const nString& str) const
                   {//return stricmp(datap_, str.datap_);}
                        nString tmp1(*this), tmp2(str);
                        tmp1.ToLower();
                        tmp2.ToLower();
                        return tmp1.Compare(tmp2);
                    }
//  ditto, ignore case

    int            Compare(const char *stp) const
                   {return strcmp(datap_, stp);}
//  Compares the string in nString with the string 'stp' points to.
    int            CompareNoCase(const char *stp) const
                   {//return strcmp(datap_, stp);}
                        nString tmp1(*this), tmp2(stp);
                        tmp1.ToLower();
                        tmp2.ToLower();
                        return tmp1.Compare(tmp2);
                    }
//  ditto, ignore case.

    char*        GetData(char *dest, size_t  size) const;
    char*        GetData(char *dest, int  size) const;
//  Copies 'size' characters from '*datap_' to '*dest' and returns 'dest'.
//  Safe Method. Characters will cut if 'size' is less than 'length_'.
//  Copies 'length' characters if 'size' is greater.
//  Appends the null terminator in every case.

    char*        GetData(char *dest) const
                   {return GetData(dest, length_);}
//  Copies 'length_' characters from *datap_ to *dest. Dangerous Method.

    bool           IsAllDigit();
//  Tests whether all characters in the string are digits

    bool           IsEmpty() const {return length_ == 0;}
//  Tests for empty string.

    size_t         Length() const {return length_;}
//  Returns the actuell length of the contained string.

    void           ToLower();
//  Changes the contained string to lower case.

    void           ToUpper();
//  Changes the contained string to upper case.

    const nString& Strip(tPOSITION kindofstrip = cBOTH, char ch = ' ');
//  Delete 'ch' at begin and/or end of the string.

    const nString& Replace(char a, char b, size_t start=0);
//  Replaces each occurence of character 'a' with character 'b', beginning at
//  index 'start'. 'start' defaults to 0. Returns a reference to self.

    const nString& Trim(size_t len,
                       tPOSITION kindofposition = cTRAILING,
                       char ch = ' ');
//  Trims (expands or cuts) nString to length of len.
//  If this is shorter than 'len', 'ch' is inserted at the end (cTRAILING).
//  If this is longer than 'len', this is cut at the end (cTRAILING).
//  'cBOTH' is ignored.

    const nString& Compress(char ch = ' ');
//  Delete all occurences of 'ch'.

    size_t         FindChar(char ch, size_t start = 0) const;
//  Returns first position (beginning from position 'start') of 'ch' when found.
//  Returns else a Position greater than string length.

    size_t         FindSubString(const nString& substr, size_t substrlength,
                                 size_t start, tCOMPARE com) const;
//  Beginning from position 'start' searches for 'substr' with 'substrlength'
//  characters. Ignores case for 'com == nString::cIGNORE'. Respects case for
//  'com == nString::cEXACT'. Returns the position when found, else a position
//  greater then 'this->Length()'.

    size_t         FindSubString(const nString& substr, size_t start = 0,
                                  tCOMPARE com = cEXACT) const
                   {return FindSubString(substr, substr.length_, start, com);}
//  Beginning from position 'start' searches for 'substr'.
//  Ignores case for 'com == nString::cIGNORE'. Respects case for
//  'com == nString::cEXACT'. Returns the position when found,
//  else a position greater then 'this->Length()'.


/*
STREAM READING FUNCTIONS
*/

	std::istream&       ReadToken(std::istream& strm, const nString& extrachars);
//  Reads a token from istream. Token is separated by whitespaces
//  (given by isspace: x20, x09 to x0d) and the 'extrachars'.
//  The whitespace/extrachar after the token is not extracted and not stored.

	std::istream&       ReadToken(std::istream& strm) {return ReadToken(strm, "");}
//  Reads a token from istream. Token is separated by whitespaces
//  (given by isspace: x20, x09 to x0d).
//  The whitespace after the token is not extracted and not stored.

	std::istream&       ReadToDelimiter(std::istream& strm, const nString& delim);
//  Read the istream to delimeter.
//  The delimeter is not extracted and not stored.

	std::istream&       ReadLine(std::istream& strm, const bool skipwhite = false);
//  Reads a whole line from istream. EOL is not extracted and not stored.
//  Leading whitespaces are extracted but not stored if skipwhite==true.

	std::istream&       ReadFile(std::istream& strm)
                            {return ReadToDelimiter(strm, "");};
//  Reads the whole istream.

/*
CLASS AND FRIEND OPERATORS
*/

//  overloaded assignment operators:
           nString& operator = (const nString& src);
           nString& operator = (const char *stp);
           nString& operator = (const long& src);

//  string concatenation operators:
    friend nString operator + (const nString& s1, const nString& s2);
    friend nString operator + (const nString& s, const char *stp);
    friend nString operator + (const char *stp, const nString& s);
           nString& operator += (const nString& string);
           nString& operator += (const char *stp);
           nString& operator += (const char ch);


//  type casts:
                   operator char*() const { return (char*) datap_;}
//  Converts to a pointer to char
                   operator const char*() const { return (char*) datap_;}
//  Converts to a pointer to const char

//  Type conversions:
    char*        operator ()() const { return (char*) datap_;}
//  Returns a pointer to char
    nSubString     operator () (size_t pos, size_t length = 1);
//  Returns a nSubstring with 'lenght' characters from 'pos'.
    char&        operator [] (size_t pos);
//  Returns a reference to the indexed character.
//  Indexing [0 to Length()-1].


//@CE


protected:
/*
implementation helpers
*/
    void           Init();
    void           AllocCopy(nString& dest, size_t CopyLen, size_t CopyIndex, size_t ExtraLen) const;
    void           AllocBuffer(size_t len);
    void           AssignCopy(size_t len, const char *datap);
    void           ConcatCopy(size_t len1, const char *datap1, size_t len2, const char *datap2);
    void           ConcatInPlace(size_t len, const char *datap);
    void           ReduceBufferTo(const size_t& NewLenght);
    friend void    FreeBuffer(char *bufp);
    friend size_t  SafeStrLen(const char *stp)
                   {
                       assert(stp != NULL);
                       return (stp == NULL) ? 0 : strlen(stp);
                   }

    bool           CheckIndex(size_t pos) const
                   {
                       return (pos < length_);
                   }
/*
protected data structures
*/
    char           *datap_;             // pointer to string
    size_t         length_;             // string length
    size_t         bufsize_;            // buffer size

/*
friend classes
*/
    friend class   nSubString;
};

std::ostream&        operator <<  (std::ostream& str, const nString& s);

inline bool    operator ==  (const nString& s1, const nString& s2)
                             { return s1.Compare(s2) == 0; }
inline bool    operator ==  (const nString& s1, const char*  s2)
                             { return s1.Compare(s2) == 0; }
inline bool    operator ==  (const char*  s1, const nString& s2)
                             { return s2.Compare(s1) == 0; }

inline bool    operator !=  (const nString& s1, const nString& s2)
                             { return s1.Compare(s2) != 0; }
inline bool    operator !=  (const nString& s1, const char*  s2)
                              { return s1.Compare(s2) != 0; }
inline bool    operator !=  (const char*  s1, const nString& s2)
                             { return s2.Compare(s1) != 0; }

inline bool    operator <   (const nString& s1, const nString& s2)
                             { return s1.Compare(s2) < 0; }
inline bool    operator <   (const nString& s1, const char*  s2)
                             { return s1.Compare(s2) < 0; }
inline bool    operator <   (const char*  s1, const nString& s2)
                             { return s2.Compare(s1) > 0; }

inline bool    operator >   (const nString& s1, const nString& s2)
                             { return s1.Compare(s2) > 0; }
inline bool    operator >   (const nString& s1, const char*  s2)
                             { return s1.Compare(s2) > 0; }
inline bool    operator >   (const char*  s1, const nString& s2)
                             { return s2.Compare(s1) < 0; }

inline bool    operator <=  (const nString& s1, const nString& s2)
                             { return s1.Compare(s2) <= 0; }
inline bool    operator <=  (const nString& s1, const char*  s2)
                             { return s1.Compare(s2) <= 0; }
inline bool    operator <=  (const char*  s1, const nString& s2)
                             { return s2.Compare(s1) >= 0; }

inline bool    operator >=  (const nString& s1, const nString& s2)
                             { return s1.Compare(s2) >= 0; }
inline bool    operator >=  (const nString& s1, const char*  s2)
                             { return s1.Compare(s2) >= 0; }
inline bool    operator >=  (const char*  s1, const nString& s2)
                             { return s2.Compare(s1) <= 0; }

#endif
