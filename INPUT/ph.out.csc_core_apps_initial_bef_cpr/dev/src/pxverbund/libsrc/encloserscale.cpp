/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxEncloserScale methods.

REVISION HISTORY

12 Dec 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxencloserscale.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxEncloserScale :: pxEncloserScale
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxEncloserScale :: pxEncloserScale
(
    pxEncloserScale& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tENCLOSERSCALE structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxEncloserScale :: pxEncloserScale
(
    pxSession   *session,
    tENCLOSERSCALE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxEncloserScale :: pxEncloserScale
(
    pxSession *session,
   const pxEncloserScale *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
       (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxEncloserScale :: pxEncloserScale
(
    pxSession    *session,
    short        BranchNo,            // Branchnumber
    long         CustomerNo,          // Customernumber
    short        TimeDiff,            // TimeDiff
    short        MaxPositions         // MaxPositions

)
    : pxDBRecord(session)
{
    Init();
    BranchNo_     = BranchNo;
    CustomerNo_   = CustomerNo;
    TimeDiff_     = TimeDiff;
    MaxPositions_ = MaxPositions;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxEncloserScale :: ~pxEncloserScale()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tENCLOSERSCALE structure.      */
/*----------------------------------------------------------------------------*/
tENCLOSERSCALE&
Assign
(
    tENCLOSERSCALE&           dest,
    const pxEncloserScale&       src
)
{
    dest.BranchNo                 = src.BranchNo_              ;
    dest.CustomerNo               = src.CustomerNo_            ;
    dest.TimeDiff                 = src.TimeDiff_              ;
    dest.MaxPositions             = src.MaxPositions_          ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tENCLOSERSCALE structure to                */
/*  a pxEncloserScale object.                                                 */
/*----------------------------------------------------------------------------*/
pxEncloserScale&
Assign
(
    pxEncloserScale&              dest,
    const tENCLOSERSCALE&    src
)
{
    dest.BranchNo_                 = src.BranchNo              ;
    dest.CustomerNo_               = src.CustomerNo            ;
    dest.TimeDiff_                 = src.TimeDiff              ;
    dest.MaxPositions_             = src.MaxPositions          ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxEncloserScale :: Init()
{
    tENCLOSERSCALE    record;
    memset(&record, 0 , sizeof(tENCLOSERSCALE));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tENCLOSERSCALE struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxEncloserScale&
pxEncloserScale :: operator=( const pxEncloserScale& src)
{
    tENCLOSERSCALE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tENCLOSERSCALE structure 'src' to                   */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxEncloserScale&
pxEncloserScale :: operator=( const tENCLOSERSCALE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxEncloserScale list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                       */
/*----------------------------------------------------------------------------*/
int
pxEncloserScale :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxEncloserScale *that = (pxEncloserScale*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > BranchNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (CustomerNo_ == that->CustomerNo_) ? 0
              : (CustomerNo_ > CustomerNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (TimeDiff_ == that->TimeDiff_) ? 0
              : (TimeDiff_ > TimeDiff_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxEncloserScaleList :: pxEncloserScaleList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxEncloserScaleList :: Select
(
    const int     count_
)
{
    tENCLOSERSCALE fil;
    memset(&fil, 0, sizeof(tENCLOSERSCALE));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxEncloserScaleList :: Select
(
    const short   BranchNo,
    const long    CustomerNo,
    const int     count_
)
{
    tENCLOSERSCALE fil;
    memset(&fil, 0, sizeof(tENCLOSERSCALE));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxEncloserScaleList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxEncloserScale' object:
    pxEncloserScale *objectp = new pxEncloserScale(Session(), *(tENCLOSERSCALE*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/* FindNearest returns a pxEncloserScale pointer to the corresponding entry   */
/* which timeDiff(in seconds) is lower but at nearest to TimeSlot .           */
/* If no entry found, so a NULLP will be returned               .             */
/*----------------------------------------------------------------------------*/
pxEncloserScale*
pxEncloserScaleList :: FindNearest
(
    const long       TimeSlot              // Count of seconds
)
{
    pxEncloserScaleListIter   iter( *this );  // define iterator
    pxEncloserScale          *entryp;         // pointer to listentry
    pxEncloserScale          *bestp = NULL;   // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxEncloserScale*) ++iter) != NULL ) // browse list
    {
       if ( (entryp->TimeDiff()*60 ) <  TimeSlot)
       {
          if ( !bestp )
          {
             bestp = entryp;
             continue;
          }
          bestp = entryp;
       }
    }
    return   bestp;                        // return entrypointer
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxEncloserScale :: Get
(
    DBAccessMode mode
)

{
    tENCLOSERSCALE record;
    memset(&record, 0, sizeof(tENCLOSERSCALE));
    record.BranchNo       = BranchNo_;
    record.CustomerNo     = CustomerNo_;
    record.TimeDiff       = TimeDiff_;
    record.MaxPositions   = MaxPositions_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLEQUOTA struct
   /* else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_AQUOT_ENTRY_NOTFOUND, BranchNo_, CustomerNo_, ArticleNo_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxEncloserScale :: Put
(
)
{
    tENCLOSERSCALE record;
    memset(&record, 0, sizeof(tENCLOSERSCALE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tENCLOSERSCALE));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxEncloserScale :: Delete
(
)
{
    tENCLOSERSCALE record;
    memset(&record, 0, sizeof(tENCLOSERSCALE));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxEncloserScale :: Read
(
    const void  *record
)
{
    return pxEncloserScaleRead((tENCLOSERSCALE*)record);
}

int
pxEncloserScale :: ReadLock
(
    const void  *record
)
{
    return pxEncloserScaleReadLock((tENCLOSERSCALE*)record);
}

int
pxEncloserScale :: Update
(
    const void  *record
)
{
    return pxEncloserScaleUpdate((tENCLOSERSCALE*)record);
}

int
pxEncloserScale :: Delete
(
    const void  *record
)
{
    return pxEncloserScaleDelete((tENCLOSERSCALE*)record);
}

int
pxEncloserScale :: Insert
(
    const void  *record
)
{
    return pxEncloserScaleInsert((tENCLOSERSCALE*)record);
}

int
pxEncloserScaleList :: EndBrowse
(
    const int  cursorid
)
{
    return pxEncloserScaleEndBrowse(cursorid);
}


int
pxEncloserScaleList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxEncloserScaleGetNext((tENCLOSERSCALE*)record, cursorid);
}

int
pxEncloserScaleList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxEncloserScaleStartBrowse((tENCLOSERSCALE*)keys, cursorid);
}
