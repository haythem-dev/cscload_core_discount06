/*FIL
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1994-1995 by NORDAT NetWork GmbH
                              All rights reserved

GDLIST.H
Generic doubly-linked list classes.

REVISION HISTORY

20 Oct 1994 V1.00 REV 00 written by Wolfgang Hoppe.
02 May 1995 V1.01 REV 00 WH

*/
/*  $History: GDLIST.HPP $ */
/*  */
/* *****************  Version 3  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:11 */
/* Updated in $/cxxtools/inc */
/* Final release. */
/* *********************************************** */

/*  Do not allow to include the file more than once                           */
#ifndef GDLIST_INC
#define GDLIST_INC

#include <stddef.h>

/*----------------------------------------------------------------------------*/
/*  Generic link element class.                                               */
/*----------------------------------------------------------------------------*/
class nGDLink
{
public:
                nGDLink ()              { prevp = nextp = this; }
    virtual     ~nGDLink ()             {;}
    nGDLink*    Clear()
                {
                    nGDLink* retval = nextp;
                    prevp =  nextp = this; // Link to self (not in list)
                    return retval;
                }

    nGDLink*    Next() const
                {return nextp;}
    nGDLink*    Prev() const
                {return prevp;}
    nGDLink     *nextp;                 // pointer to next link
    nGDLink     *prevp;                 // pointer to previous link

};

/*----------------------------------------------------------------------------*/
/*  Generic doubly-linked list class.                                         */
/*----------------------------------------------------------------------------*/
class nGDList
{

public:
// constructor:
                nGDList()               { Init(); }
// destructor:
    virtual     ~nGDList()              {Clear();}
// member functions:
    void        Append (nGDLink *newp)  {Link(head.prevp, newp);}
    nGDLink*    At     (size_t) const;
    void        Clear();
    size_t      Entries() const         {return count;}
    nGDLink*    First() const           {return IsEmpty() ? NULL : head.nextp;}
    void        InsertAt(size_t, nGDLink* );
    bool        IsEmpty() const         {return count ==0;}
    nGDLink*    Last() const            {return IsEmpty() ? NULL : head.prevp;}
    void        Prepend(nGDLink *newp)  {Link(&head, newp);}
    nGDLink*    Remove(nGDLink*);
    nGDLink*    RemoveAt(size_t);
    nGDLink*    RemoveFirst()           {return IsEmpty() ? NULL : Remove(head.nextp);}
    nGDLink*    RemoveLast()            {return IsEmpty() ? NULL : Remove(head.prevp);}

protected:
    nGDLink     head;                   // linked list head object
    int         count;                  // element count

    void        Init();
    void        Link(nGDLink *, nGDLink *);
    nGDLink*    HeadLink()  { return &head; };
private:
    friend class nGDListIter;
};

/*----------------------------------------------------------------------------*/
/*  Generic doubly-linked list iterator class.                                */
/*----------------------------------------------------------------------------*/
class nGDListIter
{

public:

                nGDListIter(nGDList& list)
                                        {
                                            listp = &list;
                                            curp = &(listp->head);
                                        }

    virtual     ~nGDListIter()          {;}
    nGDLink*    operator++();           // Advance and return
    nGDLink*    operator--();           // Backup and return
    nGDLink*    operator+=(size_t n);   // Advance n links and return
    nGDLink*    operator-=(size_t n);   // Backup  n links and return

    nGDList*    Container() const       {return listp;}
    nGDLink*    Current() const         {return IsActive() ? curp : NULL;}
    void        InsertAfter(nGDLink*);  // Insert link after current position
    nGDLink*    Remove();               // Remove current link
    void        Reset()                 {curp = &listp->head;}
    void        ToFirst()               {curp = listp->head.nextp;}
    void        ToLast()                {curp = listp->head.prevp;}

protected:
    void        Advance()               {curp = curp->nextp;}
    void        Backup()                {curp = curp->prevp;}
    bool        IsActive() const        {return curp != &(listp->head);}

    nGDList     *listp;                 // ptr to list object
    nGDLink     *curp;                  // ptr to current link

};

#endif                                  // for ifndef GDLIST_INC
