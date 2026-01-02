/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxTenderCustomer methods.

REVISION HISTORY

24 Oct 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxtendercustomer.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTenderCustomer :: pxTenderCustomer
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
pxTenderCustomer :: pxTenderCustomer
(
    pxTenderCustomer& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTENDERCUSTOMER structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxTenderCustomer :: pxTenderCustomer
(
    pxSession   *session,
    tTENDERCUSTOMER& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderCustomer :: pxTenderCustomer
(
    pxSession *session,
   const pxTenderCustomer *src
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
pxTenderCustomer :: pxTenderCustomer
(
    pxSession    *session,
    long         TenderNo,            // TenderNumber
    short        BranchNo,            // Branchnumber
    long         CustomerNo           // Customernumber

)
    : pxDBRecord(session)
{
    Init();
    TenderNo_    = TenderNo;
    BranchNo_    = BranchNo;
    CustomerNo_  = CustomerNo;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTenderCustomer :: ~pxTenderCustomer()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTENDERCUSTOMER structure.         */
/*----------------------------------------------------------------------------*/
tTENDERCUSTOMER&
Assign
(
    tTENDERCUSTOMER&           dest,
    const pxTenderCustomer&       src
)
{
    dest.TenderNo                 = src.TenderNo_              ;
    dest.BranchNo                 = src.BranchNo_              ;
    dest.CustomerNo               = src.CustomerNo_            ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTENDERCUSTOMER structure to                   */
/*  a pxTenderCustomer object.                                                    */
/*----------------------------------------------------------------------------*/
pxTenderCustomer&
Assign
(
    pxTenderCustomer&              dest,
    const tTENDERCUSTOMER&    src
)
{
    dest.TenderNo_                 = src.TenderNo              ;
    dest.BranchNo_                 = src.BranchNo              ;
    dest.CustomerNo_               = src.CustomerNo            ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTenderCustomer :: Init()
{
    tTENDERCUSTOMER    record;
    memset(&record, 0 , sizeof(tTENDERCUSTOMER));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTENDERCUSTOMER struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxTenderCustomer&
pxTenderCustomer :: operator=( const pxTenderCustomer& src)
{
    tTENDERCUSTOMER record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTENDERCUSTOMER structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxTenderCustomer&
pxTenderCustomer :: operator=( const tTENDERCUSTOMER& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxTenderCustomer list objects being inserted in the                */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo                                                      */
/*----------------------------------------------------------------------------*/
int
pxTenderCustomer :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxTenderCustomer *that = (pxTenderCustomer*)That;
    int retval = (TenderNo_ == that->TenderNo_) ? 0
                : (TenderNo_ > TenderNo_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderCustomerList :: pxTenderCustomerList
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
pxTenderCustomerList :: Select
(
    const int     count_
)
{
    tTENDERCUSTOMER fil;
    memset(&fil, 0, sizeof(tTENDERCUSTOMER));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxTenderCustomerList :: Select
(
    const long    TenderNo,
    const short   BranchNo,
    const long    CustomerNo,
    const int     count_
)
{
    tTENDERCUSTOMER fil;
    memset(&fil, 0, sizeof(tTENDERCUSTOMER));  // zero out entire record buffer
    fil.TenderNo   = TenderNo;
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
pxTenderCustomerList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxTenderCustomer' object:
    pxTenderCustomer *objectp = new pxTenderCustomer(Session(), *(tTENDERCUSTOMER*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxTenderCustomer :: Get
(
    DBAccessMode mode
)

{
    tTENDERCUSTOMER record;
    memset(&record, 0, sizeof(tTENDERCUSTOMER));
    record.TenderNo   = TenderNo_;
    record.BranchNo   = BranchNo_;
    record.CustomerNo = CustomerNo_;
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
pxTenderCustomer :: Put
(
)
{
    tTENDERCUSTOMER record;
    memset(&record, 0, sizeof(tTENDERCUSTOMER));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTENDERCUSTOMER));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxTenderCustomer :: Delete
(
)
{
    tTENDERCUSTOMER record;
    memset(&record, 0, sizeof(tTENDERCUSTOMER));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxTenderCustomer :: Read
(
    const void  *record
)
{
    return pxTenderCustomerRead((tTENDERCUSTOMER*)record);
}

int
pxTenderCustomer :: ReadLock
(
    const void  *record
)
{
    return pxTenderCustomerReadLock((tTENDERCUSTOMER*)record);
}

int
pxTenderCustomer :: Update
(
    const void  *record
)
{
    return pxTenderCustomerUpdate((tTENDERCUSTOMER*)record);
}

int
pxTenderCustomer :: Delete
(
    const void  *record
)
{
    return pxTenderCustomerDelete((tTENDERCUSTOMER*)record);
}

int
pxTenderCustomer :: Insert
(
    const void  *record
)
{
    return pxTenderCustomerInsert((tTENDERCUSTOMER*)record);
}

int
pxTenderCustomerList :: EndBrowse
(
    const int  cursorid
)
{
    return pxTenderCustomerEndBrowse(cursorid);
}


int
pxTenderCustomerList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxTenderCustomerGetNext((tTENDERCUSTOMER*)record, cursorid);
}

int
pxTenderCustomerList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxTenderCustomerStartBrowse((tTENDERCUSTOMER*)keys, cursorid);
}
