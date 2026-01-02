/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

PDLIST.H
Doubly-linked list classes using void pointers.

REVISION HISTORY

22 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
/*  $History: PDLIST.HPP $ */
/*  */
/* *****************  Version 3  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:12 */
/* Updated in $/cxxtools/inc */
/* Final release. */
/* *********************************************** */

/*  Do not allow to include the file more than once                           */
#ifndef PDLIST_INC
   #define PDLIST_INC
   #include "gdlist.hpp"
/*----------------------------------------------------------------------------*/
/*  Link element class derived from generic link element class.               */
/*----------------------------------------------------------------------------*/
class nPDLink : public nGDLink
{
public:

             nPDLink (void *itemp)   { itemp_ = itemp;}
    virtual  ~nPDLink (){;}
    void     *itemp_;

};


/*@CS --------------------------------------------------------------------------
NAME
    nPDList - doubly-linked list class using void pointers

SYNOPSIS
    include "pdlist.hpp"
    nPDList *listp = new nPDList;

DESCRIPTION
    Class nPDList represents a container of collectable objects, not accessible
    by an external key. Duplicates are allowed. The ordering of elements is
    determined externally, generally by the order of insertion and removal.

    Class nPDList is implemented as a circular doubly-linked list of elements,
    which allows for efficient insertion and removal. Each element uses a void
    pointer as a link to its data object item, so objects of any type may be
    stored. On the other hand, using void pointers results in loosing any
    compiler type checking.

PUBLIC CONSTRUCTOR
@DE*/
class nPDList : private nGDList
{

public:
// constructors:
                nPDList()                  {;}
// destructor:
    virtual     ~nPDList()
                { Clear();}


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    void*       Append(void *itemp);
/*  Inserts the item 'itemp' points to at the end of the list and returns
    a pointer to it. Returns NULL if the insertion was unsuccessful.
*/
    using nGDList::Append;

    void*       At(size_t n) const
/*  Returns a pointer to the n'th item in the collection. The index 'n' must
    be between zero and the number of items in the collection less one, or NULL
    is returned.
*/
                {
                    nPDLink* ret = (nPDLink*) nGDList::At(n);
                    return (ret) ? ret->itemp_: NULL;
                }

    void        Clear();
//  Removes all elements in the collection.

    size_t      Entries() const
//  Returns the number of items in the collection.
                {return nGDList::Entries();}

    void*       First() const
//  Returns the first item of the collection.
                {return IsEmpty() ? NULL : FirstLink()->itemp_;}

    void*       InsertAt(size_t n, void *itemp);
//  Adds a new item 'itemp' to the collection at index 'n' and returns its
//  pointer. The item previously at position n is moved to n+1, etc.
//  The index 'n' must between 0 and the number of items in the collection,
//  or NULL is returned.
    using nGDList::InsertAt;

    bool        IsEmpty() const
//  Returns TRUE if the collection is empty, otherwise false.
                {return nGDList::IsEmpty();}

    void*       Last() const
//  Returns the last item of the collection.
                {return IsEmpty() ? NULL : LastLink()->itemp_;}

    void*       Prepend(void *itemp);
//  Adds the item 'itemp' points to the beginning end of the collection list
//  and returns a pointer to it. Returns NULL if the insertion was unsuccessful.
    using nGDList::Prepend;

    void*       Remove(void *itemp);
//  Removes and returns the first item from the collection with the address
//  'itemp', or returns NULL if no item with a matching address is found.
    using nGDList::Remove;

    void*       RemoveAt(size_t n);
//  Removes and returns the item at index 'n' from the collection.
//  The index 'n' must between 0 and the number of items in the collection,
//  or NULL is returned.

//@CE
protected:
    nPDLink*    FirstLink() const
                {return (nPDLink*) head.nextp;}
    nPDLink*    LastLink()  const
                {return (nPDLink*) head.prevp;}
    void*       Peel(nPDLink*);

private:
    friend class nPDListIter;
};

/*@CS --------------------------------------------------------------------------
NAME
    nPDListIter - doubly-linked list iterator class.

SYNOPSIS
    include "pdlist.hpp"
    nPDList *list = new nPDList;
    nPDListIter cursor(*list);

DESCRIPTION
    Class nPDListIter is the iterator for class nPDList, which allows sequential
    access to all the elements of a doubly-linked list. Elements are accessed in
    order, in either direction.
    Immediately after construction, the "current item" is undefined.

@DE*/
class nPDListIter : public nGDListIter
{

public:
/*@DS
PUBLIC CONSTRUCTOR
*/
    nPDListIter(nPDList& list) : nGDListIter(list) {;}
/*  Construct an iterator for the nPDList 'list'. After construction, the
    position of the iterator is undefined.

PUBLIC MEMBER OPERATORS
*/
    virtual ~nPDListIter() {;}

    void*       operator++();
//  Advances the iterator one item and returns a pointer to it. Returns NULL
//  if at the end of the collection.

    void*       operator--();
//  Backups the iterator one item and returns a pointer to it. Returns NULL
//  if at the head of the collection.

    void*       operator+=(size_t n);
//  Advances the iterator 'n' items and returns a pointer to the new current
//  item. Returns NULL if at the end of the collection.

    void*       operator-=(size_t n);
//  Moves the iterator back 'n' items and returns a pointer to the new current
//  item. Returns NULL if at the head of the collection.

    nPDList*    Container() const
//  Returns a pointer to the current container the iterator is assigned to.
                {return (nPDList*) listp;}

    void*       Current() const
//  Returns a pointer to the current data item.
                {return IsActive() ? Cursor()->itemp_ : NULL;}

    void*       InsertAfter(void *item);
//  Adds a new data item after the current iterator position and returns a
//  pointer to it. The position of the iterator is left unchanged.
    using nGDListIter::InsertAfter;

    void*       Remove();
//  Removes and returns the item at the current iterator position. Afterwards,
//  the iterator will be positioned at the previous item in the list.

    void        Reset()
//  Resets the iterator to its initial state.
                {nGDListIter::Reset();}
//@CE

protected:

    nPDLink*    Cursor() const
                {return (nPDLink*) curp;}

};

#endif
