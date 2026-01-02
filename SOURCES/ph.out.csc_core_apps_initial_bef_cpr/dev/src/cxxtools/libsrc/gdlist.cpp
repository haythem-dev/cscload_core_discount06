/*FIL
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Routines to implement generic doubly-linked lists.

REVISION HISTORY

22 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
/*  $History: GDLIST.CPP $ */
/*  */
/* *****************  Version 3  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:05 */
/* Updated in $/cxxtools/src */
/* Final release. */
/* *********************************************** */

#include <assert.h>
#include "gdlist.hpp"

/*----------------------------------------------------------------------------*/
/*  Find a link via index "i".                                                */
/*----------------------------------------------------------------------------*/
nGDLink*
nGDList :: At(size_t i ) const
{
    if ( i >= Entries() )               // Ensure index is in range
       return NULL;

    register nGDLink* curp = head.nextp;
    while (i--)
    {
      curp = curp->nextp;
    }
    return curp;
}


/*----------------------------------------------------------------------------*/
/*  Clear the list. The routine walks the list, setting the "next" and "prev" */
/*  pointers point to self. This allows other routines to detect whether an   */
/*  attempt is made to insert a link more than once.                          */
/*----------------------------------------------------------------------------*/
void
nGDList :: Clear()
{
    register nGDLink* current = head.nextp;
    while (current != &head)
    {
      current = current->Clear();
    }
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Put link at position "i". The link formerly at position "i" becomes       */
/*  link "i+1".                                                               */
/*----------------------------------------------------------------------------*/
void
nGDList :: InsertAt(size_t i, nGDLink *newp )
{
    assert( i <= Entries() );           // ensure index is in range
    nGDLink* prevp = i ? At(i-1) : &head;
    Link(prevp, newp);

}

/*----------------------------------------------------------------------------*/
/*  Remove and return the link with address 'curp'.                           */
/*----------------------------------------------------------------------------*/
nGDLink*
nGDList :: Remove(nGDLink *curp )
{
    if ( curp )
    {
       (curp->prevp)->nextp = curp->nextp; // next link into prior element
       (curp->nextp)->prevp = curp->prevp; // next element now links to prior
       curp->nextp = curp->prevp = curp;   // mark remove condition
       --count;                            // count -1
    }
    return curp;
}

/*----------------------------------------------------------------------------*/
/*  Remove and return the link at position "i".                               */
/*----------------------------------------------------------------------------*/
nGDLink*
nGDList :: RemoveAt(size_t i)
{
    assert( i < Entries() );           // ensure index is in range
    if ( i >= Entries() )              // Ensure index is in range
       return NULL;
    return Remove(At(i));
}

/*----------------------------------------------------------------------------*/
/*  Initialize the list.                                                      */
/*----------------------------------------------------------------------------*/
void
nGDList :: Init()
{
    head.nextp = head.prevp = &head;
    count  = 0;
}

/*----------------------------------------------------------------------------*/
/*  Link elements.                                                            */
/*----------------------------------------------------------------------------*/
void
nGDList :: Link(nGDLink *prevp, nGDLink *newp )
{
    newp->nextp = prevp->nextp;         // link newp with next node
    newp->prevp = prevp;                // link newp with prior node
    (newp->nextp)->prevp = newp;        // next node´s prior link points at newp
    prevp->nextp = newp;                // prior node now links to newp
    ++count;                            // count linked elements
}

