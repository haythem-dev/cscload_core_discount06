/*FIL
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Routines to implement doubly-linked lists of nCollectables.

REVISION HISTORY

22 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
/*  $History: DLISTCOL.CPP $ */
/*  */
/* *****************  Version 4  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:05 */
/* Updated in $/cxxtools/src */
/* Final release. */
/* *********************************************** */
#include "dlistcol.hpp"

/*----------------------------------------------------------------------------*/
/*  Find a collectable. A pointer to the first item that is equal to the      */
/*  item pointed to by 'item' is returned, or NULL if no item is found.       */
/*----------------------------------------------------------------------------*/
nCollectable*
nDListCollect::Find
(
    const nCollectable *item
)   const
{
    nCollectable* current;
    nDListCollectIter it(*((nDListCollect*)this)); // to iterate the list
    while ( ((current = ++it) != NULL) && !current->IsEqual(item) )
       ;
    return current;
}

/*----------------------------------------------------------------------------*/
/*  Find a collectable by reference. Returns a pointer to the first item that */
/*  is identical to the item pointed to by 'item' (that is, that has the      */
/*  address 'item'), or NULL if none is found.                                */
/*----------------------------------------------------------------------------*/
nCollectable*
nDListCollect::FindReference
(
    const nCollectable *item
)   const
{
    nCollectable* current;
    nDListCollectIter it(*((nDListCollect*)this)); // to iterate the list
    while ( ((current = ++it) != NULL) && (current != item) )
       ;
    return current;
}

/*----------------------------------------------------------------------------*/
/*  Insert a Collectable in ordered sequence.                                 */
/*----------------------------------------------------------------------------*/
nCollectable*
nDListCollect::InsertOrdered
(
    nCollectable *item,
    const int  order,
    const long lparm
)
{
    nCollectable* current;
    nDListCollectIter it(*this);        // to iterate the list
    while ( (current = ++it) != NULL )
    {
       int CmpResult = current->CompareTo(item, this, lparm);
       if ( (order == cASCENDING && CmpResult > 0) ||
            (order == cDESCENDING && CmpResult <= 0) )
       {
          --it;                         // then insert item here
          return it.InsertAfter(item);
       }
    }
    return Append(item);                // at the end of the list
}

/*----------------------------------------------------------------------------*/
/*  Sort the list.                                                            */
/*----------------------------------------------------------------------------*/
size_t
nDListCollect::Sort
(
    const int  order,
    const long lparm
)
{
    if ( Entries() )                       // ensure entries are there
    {
       nCollectable **buffer = new nCollectable*[Entries()];
       int i;
       for (i = 0; Entries(); i++)
       {
          buffer[i] = RemoveAt(0);
       }

       for ( int x = 0; x < i; x++ )
       {
          InsertOrdered(buffer[x], order, lparm);
       }
       delete[] buffer;
    }
    return Entries();
}
