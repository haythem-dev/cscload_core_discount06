/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOrderPosPromo  methods.

REVISION HISTORY

20 Aug 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxorderpospromo.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderPosPromo :: pxOrderPosPromo
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
pxOrderPosPromo :: pxOrderPosPromo
(
    pxOrderPosPromo& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGPOSPROMO structure to construct this instance.              */
/*----------------------------------------------------------------------------*/
pxOrderPosPromo :: pxOrderPosPromo
(
    pxSession   *session,
    tKDAUFTRAGPOSPROMO& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderPosPromo :: pxOrderPosPromo
(
    pxSession    *session,
    const long   KdAuftragNr,         // customer ordernumber
    const long   PosNr                // Positionnumber
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_      = KdAuftragNr;
    PosNr_            = PosNr;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderPosPromo :: ~pxOrderPosPromo()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGPOSPROMO structure.  */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGPOSPROMO&
Assign
(
    tKDAUFTRAGPOSPROMO&           dest,
    const pxOrderPosPromo&     src
)
{
    dest.KdAuftragNr            = src.KdAuftragNr_     ;
    dest.PosNr                  = src.PosNr_           ;
    dest.PharmacyGroupId[0] = ' ';
    src.PharmacyGroupId_.GetData(dest.PharmacyGroupId);
    dest.DiscountGrpNo          = src.DiscountGrpNo_   ;
    dest.BaseQty                = src.BaseQty_         ;
    dest.Base_Value             = src.BaseValue_       ;
    dest.CustomerNo             = src.CustomerNo_      ;
    dest.Promotion_No           = src.PromotionNo_     ;
    dest.InternalDiscount       = src.InternalDiscount_  ;
    dest.DiscountValuePct       = src.DiscountValuePct_  ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGPOSPROMO structure to            */
/*  a pxOrderPosPromo object.                                                 */
/*----------------------------------------------------------------------------*/
pxOrderPosPromo&
Assign
(
    pxOrderPosPromo&              dest,
    const tKDAUFTRAGPOSPROMO&         src
)
{
    dest.KdAuftragNr_           = src.KdAuftragNr     ;
    dest.PosNr_                 = src.PosNr           ;
    dest.PharmacyGroupId_       = src.PharmacyGroupId ;
    dest.DiscountGrpNo_         = src.DiscountGrpNo   ;
    dest.BaseQty_               = src.BaseQty         ;
    dest.BaseValue_             = src.Base_Value      ;
    dest.CustomerNo_            = src.CustomerNo      ;
    dest.PromotionNo_           = src.Promotion_No    ;
    dest.InternalDiscount_      = src.InternalDiscount    ;
    dest.DiscountValuePct_      = src.DiscountValuePct    ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderPosPromo :: Init()
{
    tKDAUFTRAGPOSPROMO    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGPOSPROMO));
    Assign(*this, record);
    DiscountValuePct_ = 0.0;
    InternalDiscount_ = '0';

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGPOSPROMO struct and then imported to self.                        */
/*----------------------------------------------------------------------------*/
pxOrderPosPromo&
pxOrderPosPromo :: operator=( const pxOrderPosPromo& src)
{
    tKDAUFTRAGPOSPROMO record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPOSPROMO structure 'src' to              */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxOrderPosPromo&
pxOrderPosPromo :: operator=( const tKDAUFTRAGPOSPROMO& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderPosPromo :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGPOSPROMO record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSPROMO));
    record.KdAuftragNr    = KdAuftragNr_ ;
    record.PosNr          = PosNr_       ;

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGPOSPROMO struct
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
pxOrderPosPromo :: Put
(
)
{
    tKDAUFTRAGPOSPROMO record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSPROMO));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGPOSPROMO));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxOrderPosPromo :: Delete
(
)
{
    tKDAUFTRAGPOSPROMO record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSPROMO));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderPosPromo :: Read
(
    const void  *record
)
{
    return pxOrderPosPromoRead((tKDAUFTRAGPOSPROMO*)record);
}

int
pxOrderPosPromo :: ReadLock
(
    const void  *record
)
{
    return pxOrderPosPromoReadLock((tKDAUFTRAGPOSPROMO*)record);
}

int
pxOrderPosPromo :: Update
(
    const void  *record
)
{
    return pxOrderPosPromoUpdate((tKDAUFTRAGPOSPROMO*)record);
}

int
pxOrderPosPromo :: Delete
(
    const void  *record
)
{
    return pxOrderPosPromoDelete((tKDAUFTRAGPOSPROMO*)record);
}

int
pxOrderPosPromo :: Insert
(
    const void  *record
)
{
    return pxOrderPosPromoInsert((tKDAUFTRAGPOSPROMO*)record);
}

int
pxOrderPosPromoList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOrderPosPromoEndBrowse(cursorid);
}


int
pxOrderPosPromoList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxOrderPosPromoGetNext((tKDAUFTRAGPOSPROMO*)record, cursorid);
}

int
pxOrderPosPromoList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOrderPosPromoStartBrowse((tKDAUFTRAGPOSPROMO*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderPosPromo list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxOrderPosPromo :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderPosPromo *that = (pxOrderPosPromo*)That;

    int retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);

    if (retval == 0 )
       retval = (PosNr_ == that->PosNr_) ? 0
                : (PosNr_ > that->PosNr_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderPosPromoList :: pxOrderPosPromoList
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
pxOrderPosPromoList :: Select
(
    const long   KdAuftragNr,
    const long   PosNr,
    const int    count_
)
{
    tKDAUFTRAGPOSPROMO fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGPOSPROMO));  // zero out entire record buffer
    fil.KdAuftragNr  = KdAuftragNr;
    fil.PosNr        = PosNr;
    int cursorid    = cCRS_DEFAULT;
    if ( PosNr == 0)
        cursorid    = cCRSPOSRAB_KDAUFTRAGNR;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderPosPromoList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxOrderPosPromo' object:
    pxOrderPosPromo *objectp = new pxOrderPosPromo(Session(), *(tKDAUFTRAGPOSPROMO*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/* Find returns a pxPosPromo pointer to the corresponding entry depend on     */
/* given Params. If entry is not found within the list , so NULLP will        */
/* be returned                                                                */
/*----------------------------------------------------------------------------*/
pxOrderPosPromo*
pxOrderPosPromoList :: Find
(
    const short PromotionNo
)
{
    pxOrderPosPromoListIter   iter( *this );        // define iterator
    pxOrderPosPromo         *entryp = NULL;         // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxOrderPosPromo*) ++iter) != NULL ) // browse list
    {
       if ( entryp->PromotionNo() == PromotionNo )
       {
          break;
       }
    }
    return   entryp;                               // return entrypointer
}
/*----------------------------------------------------------------------------*/
/* GetDiscountValuePct                                                        */
/*----------------------------------------------------------------------------*/
double
pxOrderPosPromoList :: GetDiscountValuePct
(
)
{
    double  retval = 0.0;
    pxOrderPosPromoListIter   iter( *this );        // define iterator
    pxOrderPosPromo         *entryp = NULL;         // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxOrderPosPromo*) ++iter) != NULL ) // browse list
    {
       retval = retval + entryp->DiscountValuePct();
    }
    return   retval;                               // return entrypointer
}
