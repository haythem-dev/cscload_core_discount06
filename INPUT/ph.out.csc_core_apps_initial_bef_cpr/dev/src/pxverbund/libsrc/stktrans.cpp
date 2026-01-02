/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Implementation of class pxStockTrans methods.

REVISION HISTORY

8 Aug 1995 V1.00 REV 00 written by Dietmar Schloetel.
*/

#include "pxstktra.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"


/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxStockTrans :: pxStockTrans()
{
    Init();
}

pxStockTrans :: pxStockTrans
(
    pxSession *session
)
    :pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxStockTrans :: pxStockTrans
(
    pxStockTrans& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  "Copy" constructor using a pointer to the source rather than a reference. */
/*  NULL pointer safe.                                                        */
/*----------------------------------------------------------------------------*/
pxStockTrans :: pxStockTrans
(
    pxSession *session,
    const pxStockTrans *srcp
)
    : pxDBRecord(session)
{
    Init();
    if (srcp != NULL)
        (*this) = *srcp;
}

/*----------------------------------------------------------------------------*/
/*  Use tBUCHUNGSART structure to construct this instance.                    */
/*----------------------------------------------------------------------------*/
pxStockTrans :: pxStockTrans
(
    pxSession *session,
    tBUCHUNGSART& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

pxStockTrans :: pxStockTrans
(
    pxSession *session,
    short BranchNo,
    char BuchArts,         // Read via character input
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_ = BranchNo;
    BuchArt_ = BuchArts;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxStockTrans :: ~pxStockTrans()
{
//  delete subobjects;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tBUCHUNGSART structure.        */
/*----------------------------------------------------------------------------*/
tBUCHUNGSART&
Assign
(
    tBUCHUNGSART&     dest,
    const pxStockTrans& src
)
{
    dest.BuchArt = src.BuchArt_ ;
    dest.Bezeichnung[0] = ' ';
    src.Bezeichnung_.GetData(dest.Bezeichnung);
    dest.BuchMethode = src.BuchMethode_ ;
    dest.BranchNo    = src.BranchNo_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tBUCHUNGSART structure to a pxStockTrans   */
/*                                                              object.       */
/*----------------------------------------------------------------------------*/
pxStockTrans&
Assign
(
    pxStockTrans&    dest,
    const tBUCHUNGSART&  src
)
{
    dest.BuchArt_  = src.BuchArt;
    dest.Bezeichnung_ = src.Bezeichnung;
    dest.BuchMethode_ = static_cast<enum BookingTypeEnum>(src.BuchMethode);
    dest.BranchNo_    = src.BranchNo;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Compare the value of Buchart_ with the given string                       */
/*----------------------------------------------------------------------------*/
int
pxStockTrans :: Compare
(
    const char src
)
{
    return (BuchArt_ == src) ? 0 : (BuchArt_ > src) ? 1 : -1;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxStockTrans :: Init()
{
    tBUCHUNGSART record;
    memset(&record, 0 , sizeof(tBUCHUNGSART));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tBUCHUNGSART       */
/*  struct and then imported to self.                                         */
/*----------------------------------------------------------------------------*/
pxStockTrans&
pxStockTrans :: operator=( const pxStockTrans& src)
{
    tBUCHUNGSART record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tBUCHUNGSART structure to this instance.        */
/*----------------------------------------------------------------------------*/
pxStockTrans&
pxStockTrans :: operator=( const tBUCHUNGSART& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxStockTrans :: Get
(
    DBAccessMode mode
)
{
    tBUCHUNGSART record;
    memset(&record, 0, sizeof(tBUCHUNGSART));
    record.BuchArt = BuchArt_;
    record.BranchNo = BranchNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;                 // import the data from tBUCHUNGSART struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxStockTrans :: Put
(
)
{
    tBUCHUNGSART record;
    memset(&record, 0, sizeof(tBUCHUNGSART));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tBUCHUNGSART));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxStockTrans :: Read
(
    const void *record
)
{
    return pxBuchArtRead((tBUCHUNGSART*)record);
}

int
pxStockTrans :: ReadLock
(
    const void  *record
)
{
    return pxBuchArtReadLock((tBUCHUNGSART*)record);
}

int
pxStockTrans :: Update
(
    const void *record
)
{
    return pxBuchArtUpdate((tBUCHUNGSART*)record);
}

int
pxStockTrans :: Insert
(
    const void *record
)
{
    return pxBuchArtInsert((tBUCHUNGSART*)record);
}

/*----------------------------------------------------------------------------*/
/*  List constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxStockTransList :: pxStockTransList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Select all table rows.                                                    */
/*----------------------------------------------------------------------------*/
size_t
pxStockTransList :: Select
(
    const short BranchNo,
    const int   count_                // Max number of records to read
)
{
    tBUCHUNGSART record;
    memset(&record, 0, sizeof(tBUCHUNGSART));
    record.BranchNo = BranchNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Find an Entry in the List                                                 */
/*----------------------------------------------------------------------------*/
pxStockTrans*
pxStockTransList :: Find
(
    const char  buchart,
    const short BranchNo
)
{
    pxStockTrans *ob;
    pxStockTransListIter iterator(*this);

    while ( (ob = (pxStockTrans*) ++iterator) != NULL )
    {
        if (ob->Compare(buchart) == 0 && ob->BranchNo() == BranchNo)
            break;                           // found
    }
    return ob;
}

/*----------------------------------------------------------------------------*/
/*  Find the BranchNo within this list                                        */
/*----------------------------------------------------------------------------*/
short
pxStockTransList :: Find
(
    const short BranchNo
)
{
    short branchno = 0;
    pxStockTransListIter cursor(*this);
    pxStockTrans *temp;
    while ( (temp = (pxStockTrans*) ++cursor) != NULL )
    {
        if ( temp->BranchNo_ == BranchNo )
        {
            branchno = temp->BranchNo_;
            break;
        }
    }

    return branchno;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxStockTransList :: AddToList
(
    const void  *record,
    const int  /*row*/
)
{
    pxStockTrans *objectp = new pxStockTrans(Session(),*(tBUCHUNGSART*)record); // construct new object
    Append(objectp);
    return objectp;
}

int
pxStockTransList :: EndBrowse
(
    const int cursorid
)
{
    return pxBuchArtEndBrowse(cursorid);
}

int
pxStockTransList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxBuchArtGetNext((tBUCHUNGSART*)record, cursorid);
}

int
pxStockTransList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxBuchArtStartBrowse((tBUCHUNGSART*)keys, cursorid);
}
