#include "string.hpp"
#include <ctype.h>
#include <stdio.h>
#include <sstream>

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
nString :: ~nString()
{
    FreeBuffer(datap_);
}

/*----------------------------------------------------------------------------*/
/*  Default constructor constructs an empty string object instance.           */
/*----------------------------------------------------------------------------*/
nString :: nString()
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Constructs nString object from a '\0' terminated character string.        */
/*----------------------------------------------------------------------------*/
nString :: nString
(
    const char   *stp
)
{
    size_t len;
    if ( (len = strlen(stp)) == 0 )
        Init();
    else
    {
        AllocBuffer(len);
        memcpy(datap_, stp, len);
    }
}

/*----------------------------------------------------------------------------*/
/*  Constructs a string containing 'length' characters beginning from 'bytep'.*/
/*----------------------------------------------------------------------------*/
nString :: nString
(
    unsigned char *bytep,
    size_t length
)
{
    AllocBuffer(length);
    memcpy(datap_, bytep, length);
}

/*----------------------------------------------------------------------------*/
/* Constructs a string which contains 'repeat'ed times 'ch'.                  */
/*----------------------------------------------------------------------------*/
nString :: nString
(
    unsigned char ch,
    size_t repeat
)
{
    AllocBuffer(repeat);

    for (size_t i = 0; i < repeat; i++)
        datap_[i] = ch;

    datap_[repeat] = '\0';
}

/*----------------------------------------------------------------------------*/
/*  Construct nString from another nString. We make a copy of the original    */
/*  string data to enforce value semantics (i.e. each string gets a copy of   */
/*  it's own).                                                                */
/*----------------------------------------------------------------------------*/
nString :: nString
(
    const nString& src
)
{
    src.AllocCopy(*this, src.length_, 0, 0);
}


/*----------------------------------------------------------------------------*/
/*  Assignments using the = operator.                                         */
/*----------------------------------------------------------------------------*/
nString&
nString :: operator =
(
    const nString& src                  // nString object to be copied
)
{
    AssignCopy( src.length_, src.datap_);
    return *this;
}

nString&
nString :: operator =
(
    const char   *stp                 // a C character string
)
{
    AssignCopy( strlen(stp), stp);
    return *this;
}

nString&
nString :: operator =
(
    const long&   src                  // a long
)
{
    char buffer[(sizeof(long)) * 3];
    sprintf(buffer, "%ld", src);
    AssignCopy( strlen(buffer), buffer);
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Concatenation using the + operators.                                      */
/*  To keep things simple, all "operator+" functions are friends and a new    */
/*  object instance is created and returned.                                  */
/*----------------------------------------------------------------------------*/
nString
operator +
(
    const nString& s1,                  // Concatenate two string objects
    const nString& s2
)
{
    nString retval;                     // result
    retval.ConcatCopy(s1.length_, s1.datap_, s2.length_, s2.datap_);
    return retval;
}

nString
operator +
(
    const nString& s,
    const char   *stp                 // a C character string
)
{
    nString retval;                     // result
    retval.ConcatCopy(s.length_, s.datap_, SafeStrLen(stp), stp);
    return retval;
}

nString
operator +
(
    const char   *stp,                // a C character string
    const nString& s
)
{
    nString retval;                     // result
    retval.ConcatCopy(SafeStrLen(stp), stp, s.length_, s.datap_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Concatenate in place using the += operators.                              */
/*----------------------------------------------------------------------------*/
nString&
nString :: operator +=
(
    const nString& string               // append string object to self
)
{
    ConcatInPlace(string.length_, string.datap_);
    return *this;
}

nString&
nString :: operator +=
(
    const char   *stp                 // append C string to self
)
{
    ConcatInPlace(SafeStrLen(stp), stp);
    return *this;
}

nString&
nString :: operator +=
(
    const char   ch                   // append this character
)
{
    ConcatInPlace(1, &ch);
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  operator << : Write string data to output stream.                         */
/*----------------------------------------------------------------------------*/
std::ostream& operator <<
(
	std::ostream&   os,                  // the output stream
    const nString& s                    // the object instance
)
{
    size_t len = s.Length();
    std::streamsize wid = os.width();
    wid = (static_cast<std::streamsize>(len) < wid) ? wid - len : 0;
    os.width(wid);                   // set width
    long flags = os.flags();
    if (wid && !(flags & std::ios::left))
        os << "";                     // let the ostream fill
    os.write(s(), len);
    if (wid && (flags & std::ios::left))
        os << "";                     // let the ostream fill
    return os;
}

/*----------------------------------------------------------------------------*/
/*  Moves string data into a user supplied buffer and returns buffer pointer. */
/*  If the caller's buffer size is less than the length of self, the data is  */
/*  shortened to avoid buffer overrides.                                      */
/*----------------------------------------------------------------------------*/
char*
nString :: GetData
(
    char   *dest,
    size_t size
)
const
{
//  Sanity check:
    if ( size <= 0 || !(length_ > 0) )
        return NULL;
//  Allow to copy at most 'length_' characters
    if (size > length_)
        size = length_;

    memcpy(dest, datap_, size);                 // Do copy
    dest[size] = '\0';
    return dest;
}

char*
nString :: GetData
(
    char *dest,
    int size
)
const
{
    return GetData(dest, (size_t) size);
}

/*----------------------------------------------------------------------------*/
/*  Replace each occurence of character 'a' with character 'b', beginning at  */
/*  index 'start'.                                                            */
/*----------------------------------------------------------------------------*/
const nString&
nString :: Replace
(
    char     a,
    char     b,
    size_t   start
)
{
    for (register size_t i = start; i < length_; i++)
    {
        if (datap_[i] == a)
            datap_[i] = b;
    }
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Change self to lower case.                                                */
/*----------------------------------------------------------------------------*/
void
nString :: ToLower
(
)
{
    register size_t n = length_;
    register char *p = datap_;
    for ( ;n--; p++)
    {
        *p = static_cast<char>(tolower((unsigned char)*p));
    }

}

/*----------------------------------------------------------------------------*/
/*  Change self to upper case.                                                */
/*----------------------------------------------------------------------------*/
void
nString :: ToUpper
(
)
{
    register size_t n = length_;
    register char *p = datap_;
    for ( ;n--; p++)
    {
        *p = static_cast<char>(toupper((unsigned char)*p));
    }

}


/*----------------------------------------------------------------------------*/
/*  Searches for 'ch' starting at position 'start'.                            */
/*  Returns the position. If the position is greater than length_             */
/*  the character wasn't found.                                               */
/*----------------------------------------------------------------------------*/
size_t
nString :: FindChar
(
    char   ch,
    size_t start
)
const
{
    size_t position = start;

    if (position < length_)
    {
        bool found = false;

        while (!found && position < length_)
        {
            if (datap_[position] == ch)
                found = true;
            else
                ++position;
        }
    }

    return position;
}


/*----------------------------------------------------------------------------*/
/* The character 'ch' is deleted the beginning and at the end of the string.  */
/* The deletion controlls 'kindofstrip'.                                      */
/*----------------------------------------------------------------------------*/
const nString&
nString :: Strip
(
    tPOSITION kindofstrip,
    char ch
)
{
    switch (kindofstrip)
    {
        case cBOTH :
        case cTRAILING :
        {
            // Overwrite 'c' with EOS.
            while (length_ > 0 && datap_[length_ - 1] == ch)
                datap_[--length_] = '\0';

            // if 'cBoth' go to next case.
            if (kindofstrip != cBOTH)
                break;
        }

        case cLEADING :
        {
            if (*datap_ != '\0' && *datap_ == ch)
            {
                size_t to = 0, from = 0;

                // 'start' to first character neq 'ch'
                while (datap_[from] == ch)
                    ++from;

                // copy characters to the beginning
                while (datap_[from] != '\0')
                    datap_[to++] = datap_[from++];

                // set new stringlength
                length_ = to;

                // overwrite rest of buffer
                while (to <= from)
                    datap_[to++] = '\0';
            }
            break;
        }

        default : ; // nothing ?
    }

    return *this;
}

/*----------------------------------------------------------------------------*/
/*  If the string contains 'ch' it will be deleted at all positions.          */
/*----------------------------------------------------------------------------*/
const nString&
nString :: Compress
(
    char ch
)
{
    // First strip the string.
    Strip(cBOTH, ch);

    size_t to = FindChar(ch);

    if (to < length_)
    {
        size_t from = to;

        // copy backwards.
        while (datap_[from] != '\0')
        {
            // overread 'ch'
            while (datap_[from] == ch)
                ++from;

            datap_[to++] = datap_[from++];
        }

        // new length_
        length_ = to;

        // overwrite rest of buffer
        while (to <= from)
            datap_[to++] = '\0';
    }

    return *this;
}


/*----------------------------------------------------------------------------*/
/*  Trim (expand or cut) nString to length of len.                            */
/*  If this is shorter than 'len', 'ch' is inserted at the end (cTRAILING).   */
/*  If this is longer than 'len', this is cut at the end (cTRAILING).         */
/*  ('cBOTH' is ignored).                                                     */
/*----------------------------------------------------------------------------*/
const nString&
nString :: Trim
(
    size_t len,
    tPOSITION kop,
    char ch
)
{
    if (len != length_ && kop != cBOTH)
    {
        char *olddatap = datap_;
        size_t oldlength = length_, pos;

        AllocBuffer(len);

        pos = 0;
        while (pos < length_)
            datap_[pos++] = ch;

        if (kop == cTRAILING)
        {
            pos = 0;
            while (pos < length_ && pos < oldlength)
            {
                datap_[pos] = olddatap[pos];
                ++pos;
            }
        }
        else /*if (kop == cLEADING) */
        {
            pos = length_;
            while (pos > 0 && oldlength >= 1)
            {
                datap_[pos-1] = olddatap[oldlength-1];
                --pos;
                --oldlength;
            }
        }

        // Release memory olddatap points to it
        FreeBuffer(olddatap);
    }

    return *this;
}


/*----------------------------------------------------------------------------*/
/*  Tests, if nString contains only digits.                                   */
/*  The test is negative, if nString is empty.                                */
/*----------------------------------------------------------------------------*/
bool
nString :: IsAllDigit
(
)
{
    bool decision = true;

    if (length_ > 0)
    {
        for (size_t step = 0; step < length_; step++)  // is string empty?
        {
            if (!isdigit(datap_[step]))                 // is character nondigit?
            {
                decision = false;
                break;
            }
        }
    }
    else
    {
        decision = false;
    }
    return decision;
}
