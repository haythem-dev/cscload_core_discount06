/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Implementation of class pxCommType methods.

REVISION HISTORY

8 Aug 1995 V1.00 REV 00 written by Dietmar Schloetel.
*/

#include "pxcomtyp.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal  constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxCommType :: pxCommType
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
pxCommType :: pxCommType
(
    pxCommType& src
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
pxCommType :: pxCommType
(
    pxSession *session,
    const pxCommType  *srcp
)
    : pxDBRecord(session)
{
    Init();
    if (srcp != NULL)
       (*this) = *srcp;
}

/*----------------------------------------------------------------------------*/
/*  Use tKOMMIARTEN structure to construct this instance.                        */
/*----------------------------------------------------------------------------*/
pxCommType :: pxCommType
(
    pxSession *session,
    tKOMMIARTEN& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

pxCommType :: pxCommType
(
    pxSession *session,
    char KoArt,          // Read via character input
    short BranchNo,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KoArt_ = KoArt;
    BranchNo_ = BranchNo;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCommType :: ~pxCommType()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKOMMIARTEN structure.         */
/*----------------------------------------------------------------------------*/
tKOMMIARTEN&
Assign
(
    tKOMMIARTEN&     dest,
    const pxCommType& src
)
{

    dest.KoArt = src.KoArt_ ;
    dest.Bezeichnung[0] = ' ';
    src.Bezeichnung_.GetData(dest.Bezeichnung);
    dest.KoMethode = src.KoMethode_ ;
    dest.BranchNo  = src.BranchNo_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKOMMIARTEN structure to a pxCommType      */
/*                                                              object.       */
/*----------------------------------------------------------------------------*/
pxCommType&
Assign
(
    pxCommType&    dest,
    const tKOMMIARTEN&  src
)
{

    dest.KoArt_  = src.KoArt;
    dest.Bezeichnung_   = src.Bezeichnung;
    dest.Bezeichnung_.Strip();
    dest.KoMethode_ = static_cast<enum PickingTypeEnum>(src.KoMethode);
    dest.BranchNo_ = src.BranchNo;
    return dest;
}
/*----------------------------------------------------------------------------*/
/*  Compare the value of KoArt_   with the given char   */
/*----------------------------------------------------------------------------*/
int
pxCommType :: Compare
(
    const char    src
)
{
    return (KoArt_ == src) ? 0 : (KoArt_ > src) ? 1 : -1;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCommType :: Init()
{
    tKOMMIARTEN    record;
    memset(&record, 0 , sizeof(tKOMMIARTEN));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tKOMMIARTEN       */
/*  struct and then imported to self.                                         */
/*----------------------------------------------------------------------------*/
pxCommType&
pxCommType :: operator=( const pxCommType& src)
{
    tKOMMIARTEN    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKOMMIARTEN structure to this instance.        */
/*----------------------------------------------------------------------------*/
pxCommType&
pxCommType :: operator=( const tKOMMIARTEN& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCommType :: Get
(
    DBAccessMode mode
)

{
    tKOMMIARTEN record;
    memset(&record, 0, sizeof(tKOMMIARTEN));
    record.KoArt = KoArt_;
    record.BranchNo = BranchNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tKOMMIARTEN struct
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCommType :: Put
(
)

{
    tKOMMIARTEN record;
    memset(&record, 0, sizeof(tKOMMIARTEN));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKOMMIARTEN));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCommType :: Read
(
    const void  *record
)
{
    return pxKommiArtRead((tKOMMIARTEN*)record);
}
int
pxCommType :: ReadLock
(
    const void  *record
)
{
    return pxKommiArtReadLock((tKOMMIARTEN*)record);
}

int
pxCommType :: Update
(
    const void  *record
)
{
    return pxKommiArtUpdate((tKOMMIARTEN*)record);
}

int
pxCommType :: Insert
(
    const void  *record
)
{
    return pxKommiArtInsert((tKOMMIARTEN*)record);
}

/*----------------------------------------------------------------------------*/
/*  List constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCommTypeList :: pxCommTypeList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using single string value arguments.                 */
/*----------------------------------------------------------------------------*/
size_t
pxCommTypeList :: Select
(
    const short   BranchNo,
    const int     count_                // Max number of records to read
)

{

    tKOMMIARTEN record;
    memset(&record, 0, sizeof(tKOMMIARTEN));
    record.BranchNo = BranchNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Find an Entry in the List                                                 */
/*----------------------------------------------------------------------------*/
pxCommType*
pxCommTypeList :: Find
(
    const char   commiart,
    const short BranchNo
)
{
    pxCommType *ob;
    pxCommTypeListIter iterator(*this);

    while ( (ob =  (pxCommType*) ++iterator) != NULL )
    {
       if (ob->Compare(commiart) == 0 && ob->BranchNo() == BranchNo)
          break;                       // found
    }
    return ob;

}

/*----------------------------------------------------------------------------*/
/*  Find the BranchNo within this list                                        */
/*----------------------------------------------------------------------------*/
short
pxCommTypeList :: Find
(
    const short    BranchNo
)
{
    short branchno = 0;
    pxCommTypeListIter cursor(*this);
    pxCommType   *temp;
    while ( (temp = (pxCommType*) ++cursor) != NULL )
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
pxCommTypeList :: AddToList
(
    const void  *record,
    const int  /*row*/
)
{
    pxCommType *objectp = new pxCommType(Session(),*(tKOMMIARTEN*) record); // construct new object
    Append(objectp);
    return objectp;
}

int
pxCommTypeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxKommiArtEndBrowse(cursorid);
}


int
pxCommTypeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxKommiArtGetNext((tKOMMIARTEN*)record, cursorid);
}

int
pxCommTypeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxKommiArtStartBrowse((tKOMMIARTEN*)keys, cursorid);
}
