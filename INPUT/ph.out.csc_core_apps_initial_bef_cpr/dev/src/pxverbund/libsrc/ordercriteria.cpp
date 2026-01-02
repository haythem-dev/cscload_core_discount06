/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOrderCriteria methods.

REVISION HISTORY

16 Oct 2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxordercriteria.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"


/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderCriteria :: pxOrderCriteria
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
pxOrderCriteria :: pxOrderCriteria
(
    pxOrderCriteria& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tORDERCRITERIA structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxOrderCriteria :: pxOrderCriteria
(
    pxSession   *session,
    tORDERCRITERIA& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxOrderCriteria :: pxOrderCriteria
(
    pxSession    *session,
    short       BranchNo,               // Read via this type and
    long        ArticleNo               // this type
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_   = BranchNo;
    ArticleNo_  = ArticleNo;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderCriteria :: ~pxOrderCriteria()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tORDERCRITERIA structure.           */
/*----------------------------------------------------------------------------*/
tORDERCRITERIA&
Assign
(
    tORDERCRITERIA&           dest,
    const pxOrderCriteria&       src
)
{
    dest.BranchNo                  = src.BranchNo_               ;
    dest.ArticleNo                 = src.ArticleNo_              ;
    dest.ManufacturerNo            = src.ManufacturerNo_         ;
    dest.CustomerNo                = src.CustomerNo_             ;
    dest.MinOrderQty               = src.MinOrderQty_            ;
    dest.MinOrderValue             = src.MinOrderValue_          ;
    dest.AddOnChargeArtNo          = src.AddOnChargeArtNo_       ;
    dest.AddOnChargePct            = src.AddOnChargePct_         ;

    // strings
    dest.PharmacyGroupId[0] = ' ';
    src.PharmacyGroupId_.GetData(dest.PharmacyGroupId);
    dest.OrderType[0] = ' ';
    src.OrderType_.GetData(dest.OrderType);
    dest.LimitAction[0] = ' ';
    src.LimitAction_.GetData(dest.LimitAction);
    dest.ActionRestriction[0] = ' ';
    src.ActionRestriction_.GetData(dest.ActionRestriction);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tORDERCRITERIA structure to                     */
/*  a pxOrderCriteria object.                                                      */
/*----------------------------------------------------------------------------*/
pxOrderCriteria&
Assign
(
    pxOrderCriteria&              dest,
    const tORDERCRITERIA&    src
)
{
    dest.BranchNo_                 = src.BranchNo                ;
    dest.ArticleNo_                = src.ArticleNo               ;
    dest.ManufacturerNo_           = src.ManufacturerNo          ;
    dest.PharmacyGroupId_          = src.PharmacyGroupId         ;
    dest.CustomerNo_               = src.CustomerNo              ;
    dest.OrderType_                = src.OrderType               ;
    dest.MinOrderQty_              = src.MinOrderQty             ;
    dest.MinOrderValue_            = src.MinOrderValue           ;
    dest.LimitAction_              = src.LimitAction             ;
    dest.ActionRestriction_        = src.ActionRestriction       ;
    dest.AddOnChargeArtNo_         = src.AddOnChargeArtNo        ;
    dest.AddOnChargePct_           = src.AddOnChargePct          ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderCriteria :: Init()
{
    tORDERCRITERIA    record;
    memset(&record, 0 , sizeof(tORDERCRITERIA));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tORDERCRITERIA struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxOrderCriteria&
pxOrderCriteria :: operator=( const pxOrderCriteria& src)
{
    tORDERCRITERIA record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tORDERCRITERIA structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxOrderCriteria&
pxOrderCriteria :: operator=( const tORDERCRITERIA& src)
{
    return Assign(*this, src);
}


/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderCriteria :: Get
(
    DBAccessMode mode
)

{
    tORDERCRITERIA record;
    memset(&record, 0, sizeof(tORDERCRITERIA));
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tORDERCRITERIA struct
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
pxOrderCriteria :: Read
(
    const void  *record
)
{
    return pxOrderCriteriaRead((tORDERCRITERIA*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderCriteria list objects being inserted in the                  */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxOrderCriteria :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderCriteria *that = (pxOrderCriteria*)That;
    int retval = (ArticleNo_ == that->ArticleNo_) ? 0
                : (ArticleNo_ > ArticleNo_ ? 1 : -1);

    if ( retval == 0 )
       retval = (MinOrderQty_ == that->MinOrderQty_) ? 0
                : (MinOrderQty_ > that->MinOrderQty_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderCriteriaList :: pxOrderCriteriaList
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
pxOrderCriteriaList :: Select
(
    const int     count_
)
{
    tORDERCRITERIA fil;
    memset(&fil, 0, sizeof(tORDERCRITERIA));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxOrderCriteriaList :: Select
(
    const short   BranchNo,
    const long    ArticleNo,
    const int     count_
)
{
    tORDERCRITERIA fil;
    memset(&fil, 0, sizeof(tORDERCRITERIA));  // zero out entire record buffer
    fil.BranchNo  = BranchNo;
    fil.ArticleNo = ArticleNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo,ArticleNo, OrderType and         */
/*  PharmacyGroupId                                                           */
/*----------------------------------------------------------------------------*/
size_t
pxOrderCriteriaList :: Select
(
    const short   BranchNo,
    const long    ArticleNo,
    const nString& OrderType,
    const nString& PharmacyGroupId,
    const int     count_
)
{
    tORDERCRITERIA fil;
    memset(&fil, 0, sizeof(tORDERCRITERIA));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    fil.PharmacyGroupId[0] = ' ';
    PharmacyGroupId.GetData(fil.PharmacyGroupId);
    fil.OrderType[0] = ' ';
    OrderType.GetData(fil.OrderType);
    int cursorid  = cCRORDERTYPCSTPHARMGRP;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via BranchNo,OrderType and LimitAction        */
/*  PharmacyGroupId                                                           */
/*----------------------------------------------------------------------------*/
size_t
pxOrderCriteriaList :: SelectAddOnChargeArtNo
(
    const short   BranchNo,
    const long    CustomerNo,
    const nString& OrderType,
    const nString& LimitAction,
    const int     count_
)
{
    tORDERCRITERIA fil;
    memset(&fil, 0, sizeof(tORDERCRITERIA));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.OrderType[0] = ' ';
    OrderType.GetData(fil.OrderType);
    fil.LimitAction[0] = ' ';
    LimitAction.GetData(fil.LimitAction);
    int cursorid  = cCRORDERTYPLIMITACTION;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Find return entryp depend on customerno                                   */
/*----------------------------------------------------------------------------*/
pxOrderCriteria*
pxOrderCriteriaList :: Find
(
    const long CustomerNo
)
{
    pxOrderCriteria *curp = NULL;             // ptr to current entry
    pxOrderCriteriaListIter  cursor(*this);  // define an iterator
    while ( (curp = (pxOrderCriteria*) ++cursor) != NULL )
    {
       if (curp->CustomerNo() == CustomerNo )
       {
          break;
       }
    }
    return curp;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderCriteriaList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxOrderCriteria' object:
    pxOrderCriteria *objectp = new pxOrderCriteria(Session(), *(tORDERCRITERIA*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxOrderCriteriaList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOrderCriteriaEndBrowse(cursorid);
}


int
pxOrderCriteriaList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxOrderCriteriaGetNext((tORDERCRITERIA*)record, cursorid);
}

int
pxOrderCriteriaList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOrderCriteriaStartBrowse((tORDERCRITERIA*)keys, cursorid);
}

