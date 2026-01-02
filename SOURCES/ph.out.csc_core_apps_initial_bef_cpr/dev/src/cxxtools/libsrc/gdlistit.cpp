/*FIL
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Generic doubly-linked list iterator routines.

REVISION HISTORY

22 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
extern "C" {
#include <assert.h>
#include <stdlib.h>
}
#include "gdlist.hpp"


/*----------------------------------------------------------------------------*/
/*  Prefix operators:                                                         */
/*----------------------------------------------------------------------------*/
nGDLink*
nGDListIter :: operator++()
{
    Advance();
    return IsActive() ? curp : NULL;
}

nGDLink*
nGDListIter :: operator--()
{
    Backup();
    return IsActive() ? curp : NULL;
}

nGDLink*
nGDListIter::operator+=(size_t n)
{
    while (n--)
      ++(*this);
    return Current();
}

nGDLink*
nGDListIter::operator-=(size_t n)
{
    while (n--)
      --(*this);
    return Current();
}

/*----------------------------------------------------------------------------*/
/*  Insert a link after current iterator position.                            */
/*----------------------------------------------------------------------------*/
void
nGDListIter::InsertAfter(nGDLink* link)
{
    assert( link != NULL );
    listp->Link(curp, link);
}

/*----------------------------------------------------------------------------*/
/*  Remove the link at current iterator position.                             */
/*----------------------------------------------------------------------------*/
nGDLink*
nGDListIter::Remove()
{
    if ( IsActive() )                   // Ensure iterator points at active link
    {
       Backup();                        // Backup the iterator to the prev. link,
                                        // then remove link at old position
       return listp->Remove(curp->nextp);
    }
    return NULL;
}
