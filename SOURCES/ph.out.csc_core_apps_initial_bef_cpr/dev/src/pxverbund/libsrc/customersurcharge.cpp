/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxCustomerSurcharge methods.

REVISION HISTORY

16 Dec 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxcustomersurcharge.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustomerSurcharge :: pxCustomerSurcharge
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
pxCustomerSurcharge :: pxCustomerSurcharge
(
    pxCustomerSurcharge& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERSURCHARGE structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxCustomerSurcharge :: pxCustomerSurcharge
(
    pxSession   *session,
    tCUSTOMERSURCHARGE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerSurcharge :: pxCustomerSurcharge
(
    pxSession *session,
   const pxCustomerSurcharge *src
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
pxCustomerSurcharge :: pxCustomerSurcharge
(
    pxSession    *session,
    short       BranchNo,           
    long        CustomerNo,         
    long        ManufacturerNo      

)
    : pxDBRecord(session)
{
    Init();
    BranchNo_     = BranchNo;
    CustomerNo_  = CustomerNo;
    ManufacturerNo_   = ManufacturerNo;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustomerSurcharge :: ~pxCustomerSurcharge()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCUSTOMERSURCHARGE structure.  */
/*----------------------------------------------------------------------------*/
tCUSTOMERSURCHARGE&
Assign
(
    tCUSTOMERSURCHARGE&           dest,
    const pxCustomerSurcharge&       src
)
{
    dest.BranchNo			= src.BranchNo_         ;
    dest.CustomerNo         = src.CustomerNo_       ;
    dest.ManufacturerNo     = src.ManufacturerNo_	;
    dest.SurchargePct       = src.SurchargePct_     ;
 
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCUSTOMERSURCHARGE structure to            */
/*  a pxCustomerSurcharge object.                                             */
/*----------------------------------------------------------------------------*/
pxCustomerSurcharge&
Assign
(
    pxCustomerSurcharge&              dest,
    const tCUSTOMERSURCHARGE&    src
)
{
    dest.BranchNo_			= src.BranchNo		    ;
    dest.CustomerNo_         = src.CustomerNo       ;
    dest.ManufacturerNo_     = src.ManufacturerNo	;
    dest.SurchargePct_       = src.SurchargePct     ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustomerSurcharge :: Init()
{
    tCUSTOMERSURCHARGE    record;
    memset(&record, 0 , sizeof(tCUSTOMERSURCHARGE));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCUSTOMERSURCHARGE struct and then imported to self.                      */
/*----------------------------------------------------------------------------*/
pxCustomerSurcharge&
pxCustomerSurcharge :: operator=( const pxCustomerSurcharge& src)
{
    tCUSTOMERSURCHARGE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCUSTOMERSURCHARGE structure 'src' to            */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustomerSurcharge&
pxCustomerSurcharge :: operator=( const tCUSTOMERSURCHARGE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCustomerSurcharge list objects being inserted in the            */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                       */
/*----------------------------------------------------------------------------*/
//int
//pxCustomerSurcharge :: CompareTo
//(
//    const nCollectable   *That,
//          void           *p,
//    const long           lparm
//)   const
//
//{
//    pxCustomerSurcharge *that = (pxCustomerSurcharge*)That;
//    int retval = (BranchNo_ == that->BranchNo_) ? 0
//                : (BranchNo_ > BranchNo_ ? 1 : -1);
//    if ( retval == 0 )
//       retval = (PromotionNo_ == that->PromotionNo_) ? 0
//              : (PromotionNo_ > PromotionNo_ ? 1 : -1);
//    if ( retval == 0 )
//       retval = (ArticleNo_ == that->ArticleNo_) ? 0
//              : (ArticleNo_ > ArticleNo_ ? 1 : -1);
//
//    return retval;
//}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerSurchargeList :: pxCustomerSurchargeList
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
pxCustomerSurchargeList :: Select
(
    const int     count_
)
{
    tCUSTOMERSURCHARGE fil;
    memset(&fil, 0, sizeof(tCUSTOMERSURCHARGE));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxCustomerSurchargeList :: Select
(
    const short 	BranchNo,
    const long 	CustomerNo,
    const long 	ManufacturerNo,
    const int     	count_
)
{
    tCUSTOMERSURCHARGE fil;
    memset(&fil, 0, sizeof(tCUSTOMERSURCHARGE));  // zero out entire record buffer
    fil.BranchNo     	= BranchNo;
    fil.CustomerNo   	= CustomerNo;
    fil.ManufacturerNo  = ManufacturerNo;
    int cursorid = cCRSCUSTOMERSURCHARGE_BR_CST_MAN;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustomerSurchargeList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCustomerSurcharge' object:
    pxCustomerSurcharge *objectp = new pxCustomerSurcharge(Session(), *(tCUSTOMERSURCHARGE*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustomerSurcharge :: Get
(
    DBAccessMode mode
)

{
    tCUSTOMERSURCHARGE record;
    memset(&record, 0, sizeof(tCUSTOMERSURCHARGE));
    record.BranchNo       	= BranchNo_;
    record.CustomerNo      	= CustomerNo_;
    record.ManufacturerNo  	= ManufacturerNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tCUSTOMERSURCHARGE struct
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
pxCustomerSurcharge :: Put
(
)
{
    tCUSTOMERSURCHARGE record;
    memset(&record, 0, sizeof(tCUSTOMERSURCHARGE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCUSTOMERSURCHARGE));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCustomerSurcharge :: Delete
(
)
{
    tCUSTOMERSURCHARGE record;
    memset(&record, 0, sizeof(tCUSTOMERSURCHARGE));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustomerSurcharge :: Read
(
    const void  *record
)
{
    return pxCustomerSurchargeRead((tCUSTOMERSURCHARGE*)record);
}

int
pxCustomerSurcharge :: ReadLock
(
    const void  *record
)
{
    return pxCustomerSurchargeReadLock((tCUSTOMERSURCHARGE*)record);
}

//int
//pxCustomerSurcharge :: Update
//(
//    const void  *record
//)
//{
//    return pxCustomerSurchargeUpdate((tCUSTOMERSURCHARGE*)record);
//}
//
//int
//pxCustomerSurcharge :: Delete
//(
//    const void  *record
//)
//{
//    return pxCustomerSurchargeDelete((tCUSTOMERSURCHARGE*)record);
//}
//
//int
//pxCustomerSurcharge :: Insert
//(
//    const void  *record
//)
//{
//    return pxCustomerSurchargeInsert((tCUSTOMERSURCHARGE*)record);
//}

int
pxCustomerSurchargeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCustomerSurchargeEndBrowse(cursorid);
}


int
pxCustomerSurchargeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxCustomerSurchargeGetNext((tCUSTOMERSURCHARGE*)record, cursorid);
}

int
pxCustomerSurchargeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCustomerSurchargeStartBrowse((tCUSTOMERSURCHARGE*)keys, cursorid);
}
