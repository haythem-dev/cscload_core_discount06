/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Routines to implement doubly-linked lists using void pointers.

REVISION HISTORY

22 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
/*  $History: PDLIST.CPP $ */
/*  */
/* *****************  Version 4  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:05 */
/* Updated in $/cxxtools/src */
/* Final release. */
/* *********************************************** */
#include "pdlist.hpp"

/*----------------------------------------------------------------------------*/
/*  Append an element to the end of the list.                                 */
/*----------------------------------------------------------------------------*/
void*
nPDList::Append(void *itemp)
{
    nGDList::Link(LastLink(), new nPDLink(itemp));
    return itemp;
}

/*----------------------------------------------------------------------------*/
/*  Clear the entire list.                                                    */
/*----------------------------------------------------------------------------*/
void
nPDList::Clear()
{
    nPDLink    *temp;
    nPDLink    *headl = (nPDLink*) HeadLink();
    nPDLink    *link = FirstLink();     // begin at first link
    while ( link != headl )
    {
       temp = (nPDLink*) link->Next();  // keep pointer to next link
       delete link;                     // before deleting it
       link = temp;
    }
    nGDList::Init();
}

/*----------------------------------------------------------------------------*/
/*  Insert a new element at position 'n'.                                     */
/*----------------------------------------------------------------------------*/
void*
nPDList::InsertAt(size_t n, void *itemp)
{
    nGDList::InsertAt(n, new nPDLink(itemp));
    return itemp;
}

/*----------------------------------------------------------------------------*/
/*  Insert a new element at the head of the list.                             */
/*----------------------------------------------------------------------------*/
void*
nPDList::Prepend(void *itemp)
{
    nGDList::Link(&head, new nPDLink(itemp));
    return itemp;
}

/*----------------------------------------------------------------------------*/
/*  Remove the element 'itemp' points at from the list. Returns a pointer     */
/*  to the data item or NULL if 'itemp' could not be found in the list.       */
/*----------------------------------------------------------------------------*/
void*
nPDList::Remove(void *itemp)
{
    nPDLink    *headl = (nPDLink*) HeadLink();
    nPDLink    *link = FirstLink();
    while ( link != headl )
    {
       if ( itemp == link->itemp_ )
       {
          return Peel((nPDLink*)nGDList::Remove(link));
       }
       link = (nPDLink*) link->Next();
    }
    return NULL;
}

/*----------------------------------------------------------------------------*/
/*  Remove element at position 'n'. Returns NULL if 'n' is invalid, otherwise */
/*  NULL is returned.                                                         */
/*----------------------------------------------------------------------------*/
void*
nPDList::RemoveAt(size_t n)
{
    return Peel((nPDLink*)nGDList::RemoveAt(n));
}

/*----------------------------------------------------------------------------*/
/*  Delete a link and return a pointer to its item.                           */
/*----------------------------------------------------------------------------*/
void*
nPDList::Peel(nPDLink* link)
{
    if ( link )
    {
       void  *retval = link->itemp_;
       delete link;
       return retval;
    }
    return NULL;
}

/*----------------------------------------------------------------------------*/
/*  Iterator methods.                                                         */
/*----------------------------------------------------------------------------*/
void*
nPDListIter::operator++()               // Advance iterator to next item
{
    Advance();
    return Current();
}

void*
nPDListIter::operator--()               // backup to previous item
{
    Backup();
    return Current();
}

void*
nPDListIter::operator+=(size_t n)       // advance n items
{
    while (n--)
       ++(*this);
    return Current();
}

void*
nPDListIter::operator-=(size_t n)       // backup n items
{
    while (n--)
       --(*this);
    return Current();
}

void*
nPDListIter::InsertAfter(void * itemp)  // insert new after current position
{
    nGDListIter::InsertAfter(new nPDLink(itemp));
    return itemp;
}

void*
nPDListIter::Remove()                   // Remove item at current position
{
    return Container()->Peel( (nPDLink*) nGDListIter::Remove() );
}
