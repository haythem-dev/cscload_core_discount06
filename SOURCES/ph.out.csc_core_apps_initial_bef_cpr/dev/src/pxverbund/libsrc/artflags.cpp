/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Article bit map classes pxArtClass and pxArtFlags.

REVISION HISTORY

20 Apr 1996 V1.00 REV 00 written by Wolfgang Hoppe.
*/
#include "pxartcls.hpp"
#include "pxartflg.hpp"
#include "pxdefs.hpp"

static const int cArtFlagEntries  = 5;
static const int cArtClassEntries = 2;

/*----------------------------------------------------------------------------*/
/*  Export article class bit map into longs.                                  */
/*----------------------------------------------------------------------------*/
void
pxArtClass :: Export
(
    long&  class1,
    long&  class2
)   const
{

    unsigned long LongArray[cArtClassEntries];
    nBitMap::Export(LongArray, (size_t)cArtClassEntries, (size_t)cFlagBytesPerLong);
    class1 = (long) LongArray[0];
    class2 = (long) LongArray[1];
}

/*----------------------------------------------------------------------------*/
/*  Import article class bit map from longs.                                  */
/*----------------------------------------------------------------------------*/
void
pxArtClass :: Import
(
    const long  class1,
    const long  class2
)
{

    unsigned long LongArray[cArtClassEntries];
    LongArray[0] = (unsigned long) class1;
    LongArray[1] = (unsigned long) class2;
    nBitMap::Import(LongArray, (size_t)cArtClassEntries, (size_t)cFlagBytesPerLong);
}

/*----------------------------------------------------------------------------*/
/*  Test if article may be sold to a specific customer. 'cust' is a bit map   */
/*  containing article classes allowed to be sold to that customer.           */
/*----------------------------------------------------------------------------*/
bool
pxArtClass :: IsAuthorized
(
    const pxArtClass& cust              // customer's article class flags
)   const
{

    unsigned long self = 0;
    unsigned long src  = 0;
    nBitMap::Export(&self, (size_t)1);
    cust.nBitMap::Export(&src, (size_t)1);
    return ( (src & self) == self );
}

/*----------------------------------------------------------------------------*/
/*  Export article flags into longs.                                          */
/*----------------------------------------------------------------------------*/
void
pxArtFlags :: Export
(
    long&  l1,
    long&  l2,
    long&  l3,
    long&  l4,
    long&  l5
)   const
{

    unsigned long LongArray[cArtFlagEntries];
    nBitMap::Export(LongArray, (size_t)cArtFlagEntries, (size_t)cFlagBytesPerLong);
    l1 = (long) LongArray[0];
    l2 = (long) LongArray[1];
    l3 = (long) LongArray[2];
    l4 = (long) LongArray[3];
    l5 = (long) LongArray[4];
}

/*----------------------------------------------------------------------------*/
/*  Import article class bit map from longs.                                  */
/*----------------------------------------------------------------------------*/
void
pxArtFlags :: Import
(
    const long  l1,
    const long  l2,
    const long  l3,
    const long  l4,
    const long  l5
)
{

    unsigned long LongArray[cArtFlagEntries];
    LongArray[0] = (unsigned long) l1;
    LongArray[1] = (unsigned long) l2;
    LongArray[2] = (unsigned long) l3;
    LongArray[3] = (unsigned long) l4;
    LongArray[4] = (unsigned long) l5;
    nBitMap::Import(LongArray, (size_t)cArtFlagEntries, (size_t)cFlagBytesPerLong);
}
