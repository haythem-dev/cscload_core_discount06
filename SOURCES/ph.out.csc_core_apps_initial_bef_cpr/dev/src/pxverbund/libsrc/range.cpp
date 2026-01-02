/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxRange methods.

REVISION HISTORY

08 Feb 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxrange.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"


/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxRange :: pxRange
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
pxRange :: pxRange
(
    pxRange& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tDISCOUNTGRP structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxRange :: pxRange
(
    pxSession   *session,
    tDISCOUNTGRP& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxRange :: pxRange
(
    pxSession    *session,
    short       BranchNo,               // Read via this type and
    long        DiscountGrpNo           // this type
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_         = BranchNo;
    DiscountGrpNo_    = DiscountGrpNo;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxRange :: pxRange
(
    pxSession    *session,
    short       BranchNo,               // Read via this type and
    short       DiscountGrpType,        // Read via this type and
    long        CustomerNo              // this type
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_         = BranchNo;
    DiscountGrpType_  = DiscountGrpType;
    CustomerNo_       = CustomerNo;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxRange :: ~pxRange()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDISCOUNTGRP structure.        */
/*----------------------------------------------------------------------------*/
tDISCOUNTGRP&
Assign
(
    tDISCOUNTGRP&           dest,
    const pxRange&       src
)
{
    dest.BranchNo                  = src.BranchNo_               ;
    dest.DiscountGrpNo             = src.DiscountGrpNo_          ;
    dest.Description[0] = ' ';
    src.Description_.GetData(dest.Description);
    dest.DiscountGrpType           = src.DiscountGrpType_        ;
    dest.CustomerNo                = src.CustomerNo_             ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDISCOUNTGRP structure to                  */
/*  a pxRange object.                                                    */
/*----------------------------------------------------------------------------*/
pxRange&
Assign
(
    pxRange&              dest,
    const tDISCOUNTGRP&    src
)
{
    dest.BranchNo_                 = src.BranchNo                ;
    dest.DiscountGrpNo_            = src.DiscountGrpNo           ;
    dest.Description_              = src.Description             ;
    dest.DiscountGrpType_          = src.DiscountGrpType         ;
    dest.CustomerNo_               = src.CustomerNo              ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxRange :: Init()
{
    tDISCOUNTGRP    record;
    memset(&record, 0 , sizeof(tDISCOUNTGRP));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDISCOUNTGRP struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxRange&
pxRange :: operator=( const pxRange& src)
{
    tDISCOUNTGRP record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISCOUNTGRP structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxRange&
pxRange :: operator=( const tDISCOUNTGRP& src)
{
    return Assign(*this, src);
}


/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxRange :: Get
(
    DBAccessMode mode
)

{
    tDISCOUNTGRP record;
    memset(&record, 0, sizeof(tDISCOUNTGRP));
    record.BranchNo          = BranchNo_;
    record.DiscountGrpNo     = DiscountGrpNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tDISCOUNTGRP struct
   /* else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_AD_DELPOS_NOTFOUND, KdAuftragNr_,PosNr_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxRange :: Read
(
    const void  *record
)
{
    return pxRangeRead((tDISCOUNTGRP*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRange list objects being inserted in the                  */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxRange :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxRange *that = (pxRange*)That;
    int retval = (DiscountGrpNo_ == that->DiscountGrpNo_) ? 0
                : (DiscountGrpNo_ > DiscountGrpNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRangeList :: pxRangeList
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
pxRangeList :: Select
(
    const int     count_
)
{
    tDISCOUNTGRP fil;
    memset(&fil, 0, sizeof(tDISCOUNTGRP));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxRangeList :: Select
(
    const short   BranchNo,
    const long    DiscountGrpNo,
    const int     count_
)
{
    tDISCOUNTGRP fil;
    memset(&fil, 0, sizeof(tDISCOUNTGRP));  // zero out entire record buffer
    fil.BranchNo      = BranchNo;
    fil.DiscountGrpNo = DiscountGrpNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo, DiscountGrpType, Customerno     */
/*----------------------------------------------------------------------------*/
size_t
pxRangeList :: Select
(
    const short   BranchNo,
    const short   DiscountGrpType,
    const long    CustomerNo,
    const int     count_
)
{
    tDISCOUNTGRP fil;
    memset(&fil, 0, sizeof(tDISCOUNTGRP));  // zero out entire record buffer
    fil.BranchNo        = BranchNo;
    fil.DiscountGrpType = DiscountGrpType;
    fil.CustomerNo      = CustomerNo;
    int cursorid = cCRSDISCOUNTGRPTYPE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxRangeList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxRange' object:
    pxRange *objectp = new pxRange(Session(), *(tDISCOUNTGRP*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxRangeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxRangeEndBrowse(cursorid);
}


int
pxRangeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxRangeGetNext((tDISCOUNTGRP*)record, cursorid);
}

int
pxRangeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxRangeStartBrowse((tDISCOUNTGRP*)keys, cursorid);
}

