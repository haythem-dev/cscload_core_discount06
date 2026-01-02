/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1999 by NORDAT Network GmbH
                              All rights reserved

Article bit map class pxArtFlagsFiliale.

REVISION HISTORY

22 Mar 1999 V1.00 REV 00 written by Dietmar Schlötel.
*/
#include "pxartflf.hpp"
#include "pxdefs.hpp"

static const int cArtFlagFEntries = 5;

/*----------------------------------------------------------------------------*/
/*  Export article flags into longs.                                          */
/*----------------------------------------------------------------------------*/
void
pxArtFFlags :: Export
(
    long&  l1,
    long&  l2,
    long&  l3,
    long&  l4,
    long&  l5
)   const
{

    unsigned long LongArray[cArtFlagFEntries];
    nBitMap::Export(LongArray, (size_t)cArtFlagFEntries, (size_t)cFlagBytesPerLong);
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
pxArtFFlags :: Import
(
    const long  l1,
    const long  l2,
    const long  l3,
    const long  l4,
    const long  l5
)
{

    unsigned long LongArray[cArtFlagFEntries];
    LongArray[0] = (unsigned long) l1;
    LongArray[1] = (unsigned long) l2;
    LongArray[2] = (unsigned long) l3;
    LongArray[3] = (unsigned long) l4;
    LongArray[4] = (unsigned long) l5;
    nBitMap::Import(LongArray, (size_t)cArtFlagFEntries, (size_t)cFlagBytesPerLong);
}
