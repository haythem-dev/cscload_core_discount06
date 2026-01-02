/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxPosParking  methods.

REVISION HISTORY

04 April 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxposparking.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxPosParking :: pxPosParking
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
pxPosParking :: pxPosParking
(
    pxPosParking& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tPOSITIONPARKING structure to construct this instance.                */
/*----------------------------------------------------------------------------*/
pxPosParking :: pxPosParking
(
    pxSession   *session,
    tPOSITIONPARKING& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPosParking :: pxPosParking
(
    pxSession    *session,
    short       BranchNo,               // BranchNumber
    long        CustomerNo,             // Customernumber
    long        ArticleNo,              // Articlenumber
    long        OrderNoOrg,             // Original Ordernumber
    long        OrderQty                // Quantity ordered
)
    : pxDBRecord(session)
{
    Init();
    nDate now;
    BranchNo_   = BranchNo;
    CustomerNo_ = CustomerNo;
    ArticleNo_  = ArticleNo;
    OrderNoOrg_ = OrderNoOrg;
    OrderQty_   = OrderQty;
    Date_       = now;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxPosParking :: ~pxPosParking()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tPOSITIONPARKING structure.    */
/*----------------------------------------------------------------------------*/
tPOSITIONPARKING&
Assign
(
    tPOSITIONPARKING&       dest,
    const pxPosParking&     src
)
{
    dest.Date       = src.Date_.GetYYYYMMDD();
    dest.BranchNo   = src.BranchNo_;
    dest.ArticleNo  = src.ArticleNo_;
    dest.CustomerNo = src.CustomerNo_;
    dest.OrderNoOrg = src.OrderNoOrg_;
    dest.OrderQty   = src.OrderQty_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tPOSITIONPARKING structure to              */
/*  a pxPosParking object.                                                    */
/*----------------------------------------------------------------------------*/
pxPosParking&
Assign
(
    pxPosParking&              dest,
    const tPOSITIONPARKING&    src
)
{
    dest.Date_       = nDate(src.Date);
    dest.BranchNo_   = src.BranchNo;
    dest.ArticleNo_  = src.ArticleNo;
    dest.CustomerNo_ = src.CustomerNo;
    dest.OrderNoOrg_ = src.OrderNoOrg;
    dest.OrderQty_   = src.OrderQty;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxPosParking :: Init()
{
    tPOSITIONPARKING    record;
    memset(&record, 0 , sizeof(tPOSITIONPARKING));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tPOSITIONPARKING struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxPosParking&
pxPosParking :: operator=( const pxPosParking& src)
{
    tPOSITIONPARKING record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tPOSITIONPARKING structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxPosParking&
pxPosParking :: operator=( const tPOSITIONPARKING& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxPosParking :: Get
(
    DBAccessMode mode
)

{
    tPOSITIONPARKING record;
    memset(&record, 0, sizeof(tPOSITIONPARKING));
    record.Date       = Date_.GetYYYYMMDD();
    record.BranchNo   = BranchNo_;
    record.ArticleNo  = ArticleNo_;
    record.CustomerNo = CustomerNo_;
    record.OrderNoOrg = OrderNoOrg_;
    record.OrderQty   = OrderQty_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tPOSITIONPARKING struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxPosParking :: Put
(
)
{
    tPOSITIONPARKING record;
    memset(&record, 0, sizeof(tPOSITIONPARKING));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tPOSITIONPARKING));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxPosParking :: Delete
(
)
{
    tPOSITIONPARKING record;
    memset(&record, 0, sizeof(tPOSITIONPARKING));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxPosParking :: Read
(
    const void  *record
)
{
    return pxPosParkingRead((tPOSITIONPARKING*)record);
}

int
pxPosParking :: ReadLock
(
    const void  *record
)
{
    return pxPosParkingReadLock((tPOSITIONPARKING*)record);
}

int
pxPosParking :: Update
(
    const void  *record
)
{
    return pxPosParkingUpdate((tPOSITIONPARKING*)record);
}

int
pxPosParking :: Delete
(
    const void  *record
)
{
    return pxPosParkingDelete((tPOSITIONPARKING*)record);
}

int
pxPosParking :: Insert
(
    const void  *record
)
{
    return pxPosParkingInsert((tPOSITIONPARKING*)record);
}

int
pxPosParkingList :: EndBrowse
(
    const int  cursorid
)
{
    return pxPosParkingEndBrowse(cursorid);
}


int
pxPosParkingList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxPosParkingGetNext((tPOSITIONPARKING*)record, cursorid);
}

int
pxPosParkingList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxPosParkingStartBrowse((tPOSITIONPARKING*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxPosParking list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxPosParking :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxPosParking *that = (pxPosParking*)That;
    int retval = (Date_ == that->Date_) ? 0
                : (Date_ > that->Date_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPosParkingList :: pxPosParkingList
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
pxPosParkingList :: Select
(
    const int     count_
)
{
    tPOSITIONPARKING fil;
    memset(&fil, 0, sizeof(tPOSITIONPARKING));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo, CustomerNo,ArticleNo            */
/*----------------------------------------------------------------------------*/
size_t
pxPosParkingList :: Select
(
    const short    BranchNo,
    const long     CustomerNo,
    const long     ArticleNo,
    const int      count_
)
{
    tPOSITIONPARKING fil;
    memset(&fil, 0, sizeof(tPOSITIONPARKING));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    fil.CustomerNo = CustomerNo;
    int cursorid  = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo, CustomerNo,ArticleNo,Date,      */
/*  OrderNo                                                                   */
/*----------------------------------------------------------------------------*/
size_t
pxPosParkingList :: Select
(
    const short    BranchNo,
    const long     CustomerNo,
    const long     ArticleNo,
    const nDate&    Date,
    const long     OrderNo,
    const int      count_
)
{
    tPOSITIONPARKING fil;
    memset(&fil, 0, sizeof(tPOSITIONPARKING));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    fil.CustomerNo = CustomerNo;
    fil.Date       = Date.GetYYYYMMDD(); // store key
    fil.OrderNoOrg = OrderNo;
    int cursorid  = cCRSPOSPARKING_ORDERTODAY;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxPosParkingList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxPosParking' object:
    pxPosParking *objectp = new pxPosParking(Session(), *(tPOSITIONPARKING*) record);
    InsertAscending(objectp);
    return objectp;
}

