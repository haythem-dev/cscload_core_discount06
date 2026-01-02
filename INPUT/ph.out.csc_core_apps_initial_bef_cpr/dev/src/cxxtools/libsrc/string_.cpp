/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

Class nString:
Internal methods.

REVISION HISTORY

22 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
/*  $History: STRING_.CPP $ */
/*  */
/* *****************  Version 4  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:05 */
/* Updated in $/cxxtools/src */
/* Final release. */
/* *********************************************** */
#include "string.hpp"
#include <ctype.h>
#include <stdio.h>

// static class data
static char nStringNil_ = '\0';


/*----------------------------------------------------------------------------*/
/*                       Private Member Functions                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  Initialize an object's instance.                                          */
/*----------------------------------------------------------------------------*/
void
nString :: Init
(
)
{
    length_  = bufsize_ = 0;
    datap_ = (char *)&nStringNil_;
}


/*----------------------------------------------------------------------------*/
/*  Buffer allocation. Allocates one extra char for \0 termination.           */
/*  Assumes (optimistically) that data length will equal allocation length.   */
/*----------------------------------------------------------------------------*/
void
nString :: AllocBuffer
(
    size_t len
)
{
    if (len == 0)                       // then no buffer required
    {
       Init();                          // initialize this object
    }
    else
    {
       datap_ = new char[len+1];      // may throw an exception
       assert(datap_ != 0);
       datap_[len] = '\0';
       length_ = bufsize_ = len;
    }
}


/*----------------------------------------------------------------------------*/
/*  Clone the data attached to this string object allocating 'ExtraLen'       */
/*  characters. Places results in uninitialized string 'dest'. Copies part    */
/*  or all of the original data to start of new string.                       */
/*----------------------------------------------------------------------------*/
void
nString :: AllocCopy
(
    nString& dest,
    size_t CopyLen,
    size_t CopyIndex,
    size_t ExtraLen
)
const
{

    size_t NewLen = CopyLen + ExtraLen;
    if (NewLen == 0)
    {
       dest.Init();
    }
    else
    {
       dest.AllocBuffer(NewLen);
       memcpy(dest.datap_, &datap_[CopyIndex], CopyLen);
    }
}


/*----------------------------------------------------------------------------*/
/*  Master routine for assignment operations.                                 */
/*  If the buffer currently allocated isn't is big enough, we free it and     */
/*  allocate a new one.                                                       */
/*----------------------------------------------------------------------------*/
void
nString :: AssignCopy
(
    size_t len,
    const char *datap
)
{
    if (len > bufsize_)   // then does not fit, alloc new buffer
    {
       FreeBuffer(datap_);
       Init();
       AllocBuffer(len);
    }

    if (len != 0)
       memcpy(datap_, datap, len);
    length_ = len;
    datap_[len] = '\0';
}


/*----------------------------------------------------------------------------*/
/*  Master concatenation routine, concatenates two sources. Assumes that      */
/*  'this' is a new nString object.                                           */
/*----------------------------------------------------------------------------*/
void
nString :: ConcatCopy
(
    size_t len1,
    const char *datap1,
    size_t len2,
    const char *datap2
)
{
    size_t newlen = len1 + len2;

    AllocBuffer(newlen);
    memcpy(datap_, datap1, len1);
    memcpy(&datap_[len1], datap2, len2);
}


/*----------------------------------------------------------------------------*/
/*  Concatenate in place main routine for += operators. If the buffer is too  */
/*  small, or we have a width mis-match, we just allocate a new buffer. This  */
/*  is slow, but sure.                                                        */
/*----------------------------------------------------------------------------*/
void
nString :: ConcatInPlace
(
    size_t len,
    const char *datap
)
{
    if ( length_ + len > bufsize_ )           // then must grow the buffer
    {
       char *olddatap_ = datap_;
       ConcatCopy(length_, olddatap_, len, datap);
       FreeBuffer(olddatap_);
    }
    else                         // fast concatenation when buffer big enough
    {
       memcpy(&datap_[length_], datap, len);
       length_ += len;
    }

    datap_[length_] = '\0';
}


/*----------------------------------------------------------------------------*/
/*  Reduces buffer length to specified size. Makes for that a new buffer and  */
/*  releases the old buffer. Characters may go loss!                          */
/*----------------------------------------------------------------------------*/
void
nString :: ReduceBufferTo
(
    const size_t& NewLength
)
{
    char *olddatap_ = datap_;
    AllocBuffer(NewLength);
    // datap_, length_, bufsize_ have the new values
    if (length_ != 0)
    {
       memcpy(datap_, olddatap_, length_);
    }
    // Completed
    FreeBuffer(olddatap_);
}



/*----------------------------------------------------------------------------*/
/*                  Friend Function for Buffer Deletion                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  Safe buffer deletion. Does not free any storage if buffer pointer         */
/*  points at 'nStringNil_' or equals NULL.                                   */
/*----------------------------------------------------------------------------*/
void FreeBuffer
(
    char *bufp
)
{
    if ( bufp != NULL && bufp != (char *)&nStringNil_ )
       delete [] bufp;
}



/*----------------------------------------------------------------------------*/
/*          Pubic Member Functions for Releasing Unused Space                 */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* The buffer containing the chars is deallocated.                            */
/*----------------------------------------------------------------------------*/
const nString&
nString :: Clear
(
)
{
   FreeBuffer(datap_);
   Init();

   return *this;
}


/*----------------------------------------------------------------------------*/
/*  Looks for unused buffer space.                                            */
/*  Cuts the buffer after the first '\0'.                                     */
/*----------------------------------------------------------------------------*/
void
nString :: Cut
(
)
{
    size_t index_;

    for (index_ = 0; index_ < bufsize_; index_++)
    {
       if ('\0' == datap_[index_] )
       {
          ReduceBufferTo(index_);
          break;
       }
    }
}

