/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

DLISTCOL.H
Doubly-linked list of nCollectables.

REVISION HISTORY

22 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
/*  $History: DLISTCOL.HPP $ */
/*  */
/* *****************  Version 4  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:11 */
/* Updated in $/cxxtools/inc */
/* Final release. */
/* *********************************************** */

/*  Do not allow to include the file more than once                           */
#ifndef DLISTCOL_INC
   #define DLISTCOL_INC
   #include "pdlist.hpp"
   #include "collect.hpp"

/*@CS --------------------------------------------------------------------------
NAME
    nDListCollect - doubly-linked list class using nCollectables

SYNOPSIS
    include "dlistcol.hpp"
    nDListCollect *listp = new nDListCollect;

DESCRIPTION
    Class nDListCollect represents a container of collectable objects, not
    accessible by an external key. Duplicates are allowed. The ordering of
    elements is determined externally, generally by the order of insertion
    and removal.

    Class nDListCollect is implemented as a circular doubly-linked list of
    elements, which allows for efficient insertion and removal. Each element
    uses a pointer to a nCollectable data object item, so objects to be
    stored must be derived from that abstract base class. Deriving objects
    from nCollectable avoids the use of void pointers.

PUBLIC CONSTRUCTOR
@DE*/
class nDListCollect : public nPDList
{

public:
// constructors:
                nDListCollect() : nPDList() {;}
// destructor:
    virtual     ~nDListCollect()
                            { Clear();}

/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual nCollectable*   Append(nCollectable *itemp)
//  Inserts the item 'itemp' points to at the end of the list and returns
//  a pointer to it. Returns NULL if the insertion was unsuccessful.
                            { return (nCollectable*) nPDList::Append(itemp);}
    using nPDList::Append;

    virtual nCollectable*   At(size_t n) const
//  Returns a pointer to the n'th item in the collection. The index 'n' must
//  be between zero and the number of items in the collection less one, or NULL
//  is returned.
                            { return (nCollectable*) nPDList::At(n);}

    virtual void            Clear()
//  Removes all elements in the collection.
                            { nPDList::Clear();}

    virtual size_t          Entries() const
//  Returns the number of items in the collection.
                            { return nPDList::Entries();}

    virtual nCollectable*   Find(const nCollectable *itemp) const;
//  Find a collectable. A pointer to the first item that is equal to the
//  item pointed to by 'itemp' is returned, or NULL if no item is found.

    virtual nCollectable*   FindReference(const nCollectable *itemp) const;
//  Find a collectable by reference. Returns a pointer to the first item that
//  is identical to the item pointed to by 'item' (that is, that has the
//  address 'itemp', or NULL if none is found.

    virtual nCollectable*   First() const
//  Returns the first item of the collection.
                            { return (nCollectable*) nPDList::First();}

    virtual nCollectable*   InsertAt(size_t n, nCollectable *itemp)
//  Adds a new item 'itemp' to the collection at index 'n' and returns its
//  pointer. The item previously at position n is moved to n+1, etc.
//  The index 'n' must between 0 and the number of items in the collection,
//  or NULL is returned.
                            { return (nCollectable*) nPDList::InsertAt(n, itemp);}
    using nPDList::InsertAt;

    virtual nCollectable*   InsertOrdered(nCollectable *itemp,
                            const int order = cASCENDING, const long lparm = cDEFAULT);
//  Adds the new item 'itemp' to the collection respecting the item's key values,
//  thus keeping the list sorted. The order may be either 'cASCENDING' or 'cDESCENDING'.
//  Note that a suitable virtual "CompareTo" function must be supplied with the class
//  derived from nCollectable.

    virtual nCollectable*   InsertAscending(nCollectable *itemp,
                                            const long lparm = cDEFAULT)
                            {return InsertOrdered(itemp, cASCENDING, lparm);}

    virtual nCollectable*   InsertDescending(nCollectable *itemp,
                                            const long lparm = cDEFAULT)
                            {return InsertOrdered(itemp, cDESCENDING, lparm);}

    virtual bool            IsEmpty() const
//  Returns TRUE if the collection is empty, otherwise false.
                            { return nPDList::IsEmpty();}

    virtual nCollectable*   Last() const
//  Returns the last item of the collection.
                            { return (nCollectable*) nPDList::Last();}

    virtual nCollectable*   Prepend(nCollectable *itemp)
//  Adds the item 'itemp' points to the beginning end of the collection list
//  and returns a pointer to it. Returns NULL if the insertion was unsuccessful.
                            { return (nCollectable*) nPDList::Prepend(itemp);}
    using nPDList::Prepend;

    virtual nCollectable*   Remove(nCollectable *itemp)
//  Removes and returns the first item from the collection with the address
//  'itemp', or returns NULL if no item with a matching address is found.
                            { return (nCollectable*) nPDList::Remove(itemp);}
    using nPDList::Remove;

    virtual nCollectable*   RemoveAt(size_t n)
//  Removes and returns the item at index 'n' from the collection.
//  The index 'n' must between 0 and the number of items in the collection,
//  or NULL is returned.
                            { return (nCollectable*) nPDList::RemoveAt(n);}

    virtual size_t          Sort(const int  order = cASCENDING,
                                 const long lparm = cDEFAULT);
//  Sorts the list.

//@CE

private:
    friend class nDListCollectIter;
};

/*@CS --------------------------------------------------------------------------
NAME
    nDListCollectIter - doubly-linked list iterator class.

SYNOPSIS
    include "dlistcol.hpp"
    nDListCollect *list = new nDListCollect;
    nDListCollectIter cursor(*list);

DESCRIPTION
    Class nDListCollectIter is the iterator for class nDListCollect, which
    allows sequential access to all the elements of a doubly-linked list.
    Elements are accessed in order, in either direction.
    Immediately after construction, the "current item" is undefined.

@DE*/
class nDListCollectIter : public nPDListIter
{

public:
    virtual ~nDListCollectIter() {;}
/*@DS
PUBLIC CONSTRUCTOR
*/
    nDListCollectIter(nDListCollect& list) : nPDListIter(list) {;}
//  Construct an iterator for the nDListCollect 'list'. After construction, the
//  position of the iterator is undefined.

// PUBLIC MEMBER OPERATORS
    virtual nCollectable*   operator++()
//  Advances the iterator one item and returns a pointer to it. Returns NULL
//  if at the end of the collection.
                            { return (nCollectable*) nPDListIter::operator++();}

    virtual nCollectable*   operator--()
//  Backups the iterator one item and returns a pointer to it. Returns NULL
//  if at the head of the collection.
                            { return (nCollectable*) nPDListIter::operator--();}

    virtual nCollectable*   operator+=(size_t n)
//  Advances the iterator 'n' items and returns a pointer to the new current
//  item. Returns NULL if at the end of the collection.
                            { return (nCollectable*) nPDListIter::operator+=(n);}

    virtual nCollectable*   operator-=(size_t n)
//  Moves the iterator back 'n' items and returns a pointer to the new current
//  item. Returns NULL if at the head of the collection.
                            { return (nCollectable*) nPDListIter::operator-=(n);}

    nDListCollect*  Container() const
//  Returns a pointer to the current container the iterator is assigned to.
                            { return (nDListCollect*) nPDListIter::Container();}

    virtual nCollectable*   Current() const
//  Returns a pointer to the current data item.
                            { return (nCollectable*) nPDListIter::Current();}

    virtual nCollectable*   InsertAfter(nCollectable *item)
//  Adds a new data item after the current iterator position and returns a
//  pointer to it. The position of the iterator is left unchanged.
                            { return (nCollectable*) nPDListIter::InsertAfter(item);}
    using nPDListIter::InsertAfter;

    virtual nCollectable*   Remove()
//  Removes and returns the item at the current iterator position. Afterwards,
//  the iterator will be positioned at the previous item in the list.
                            { return (nCollectable*) nPDListIter::Remove();}

    virtual void            Reset()
//  Resets the iterator to its initial state.
                            { nPDListIter::Reset();}
//@CE

};

#endif
