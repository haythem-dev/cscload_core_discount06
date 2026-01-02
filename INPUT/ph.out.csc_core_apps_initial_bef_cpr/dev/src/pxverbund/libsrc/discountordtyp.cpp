/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxDiscountOrdTyp methods.

REVISION HISTORY

09 Feb 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxdiscountordtyp.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"


/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxDiscountOrdTyp :: pxDiscountOrdTyp
(
    pxSession *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDiscountOrdTyp :: pxDiscountOrdTyp
(
    pxDiscountOrdTyp& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tDISCOUNTORDERTYP structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxDiscountOrdTyp :: pxDiscountOrdTyp
(
    pxSession *session,
    tDISCOUNTORDERTYP& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxDiscountOrdTyp :: pxDiscountOrdTyp
(
    pxSession   *session,
    short       DiscountType,               // Read via this type and
    nString&    KdAuftragArt                // this type
)
    : pxDBRecord(session)
{
    Init();
    DiscountType_ = DiscountType;
    KdAuftragArt_ = KdAuftragArt;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxDiscountOrdTyp :: ~pxDiscountOrdTyp()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDISCOUNTORDERTYP structure.   */
/*----------------------------------------------------------------------------*/
tDISCOUNTORDERTYP&
Assign
(
    tDISCOUNTORDERTYP&           dest,
    const pxDiscountOrdTyp&      src
)
{
    dest.DiscountType    = src.DiscountType_;
    dest.KdAuftragArt[0] = ' ';
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDISCOUNTORDERTYP structure to             */
/*  a pxDiscountOrdTyp object.                                                */
/*----------------------------------------------------------------------------*/
pxDiscountOrdTyp&
Assign
(
    pxDiscountOrdTyp&           dest,
    const tDISCOUNTORDERTYP&    src
)
{
    dest.DiscountType_ = src.DiscountType;
    dest.KdAuftragArt_ = src.KdAuftragArt;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxDiscountOrdTyp :: Init()
{
    tDISCOUNTORDERTYP record;
    memset(&record, 0, sizeof(tDISCOUNTORDERTYP));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDISCOUNTORDERTYP struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxDiscountOrdTyp&
pxDiscountOrdTyp :: operator=( const pxDiscountOrdTyp& src)
{
    tDISCOUNTORDERTYP record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISCOUNTORDERTYP structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxDiscountOrdTyp&
pxDiscountOrdTyp :: operator=( const tDISCOUNTORDERTYP& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxDiscountOrdTyp :: Get
(
    DBAccessMode mode
)
{
    tDISCOUNTORDERTYP record;
    memset(&record, 0, sizeof(tDISCOUNTORDERTYP));
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;        // import the data from tDISCOUNTORDERTYP struct
   /* else if ( retval > cDBXR_NORMAL )
        ExternalCondition(CMsgStream(), CMSG_AD_DELPOS_NOTFOUND, KdAuftragNr_, PosNr_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxDiscountOrdTyp :: Read
(
    const void *record
)
{
    return pxDiscountOrdTypRead((tDISCOUNTORDERTYP*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxDiscountOrdTyp list objects being inserted in the               */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxDiscountOrdTyp :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxDiscountOrdTyp *that = (pxDiscountOrdTyp*)That;
    int retval = (DiscountType_ == that->DiscountType_) ? 0
               : (DiscountType_ > DiscountType_ ? 1 : -1);
    if ( retval == 0 )
        retval = (KdAuftragArt_ == that->KdAuftragArt_) ? 0
               : (KdAuftragArt_ > that->KdAuftragArt_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDiscountOrdTypList :: pxDiscountOrdTypList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxDiscountOrdTypList :: Select
(
    const int count_
)
{
    tDISCOUNTORDERTYP fil;
    memset(&fil, 0, sizeof(tDISCOUNTORDERTYP));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Find : returns the corresponding Discounttyp given by KdAuftragArt        */
/*----------------------------------------------------------------------------*/
short
pxDiscountOrdTypList :: Find
(
    const nString& KdAuftragArt
)
{
    short discounttyp = 0;
    pxDiscountOrdTypListIter cursor(*this);   // define an iterator
    pxDiscountOrdTyp* entriep;
    while ( (entriep = (pxDiscountOrdTyp*) ++cursor) != NULL )
    {
        if ( entriep->KdAuftragArt() == KdAuftragArt )
        {
            discounttyp = entriep->DiscountType();
            break;
        }
    }
    return discounttyp;
}

/*----------------------------------------------------------------------------*/
/*  Find : returns the corresponding Discounttyp given by KdAuftragArt and    */
/*  DiscountType                                                              */
/*----------------------------------------------------------------------------*/
short
pxDiscountOrdTypList :: Find
(
    const nString& KdAuftragArt,
    const short    DiscountType
)
{
    short discounttyp = 0;
    pxDiscountOrdTypListIter cursor(*this);   // define an iterator
    pxDiscountOrdTyp* entriep;
    while ( (entriep = (pxDiscountOrdTyp*) ++cursor) != NULL )
    {
        if ( entriep->KdAuftragArt() == KdAuftragArt && entriep->DiscountType() == DiscountType )
        {
            discounttyp = entriep->DiscountType();
            break;
        }
    }
    return discounttyp;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxDiscountOrdTypList :: AddToList
(
    const void *record,
    const int  /* row */
)
{
    // construct new 'pxDiscountOrdTyp' object:
    pxDiscountOrdTyp *objectp = new pxDiscountOrdTyp(Session(), *(tDISCOUNTORDERTYP*)record);
    InsertAscending(objectp);
    return objectp;
}

int
pxDiscountOrdTypList :: EndBrowse
(
    const int cursorid
)
{
    return pxDiscountOrdTypEndBrowse(cursorid);
}

int
pxDiscountOrdTypList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxDiscountOrdTypGetNext((tDISCOUNTORDERTYP*)record, cursorid);
}

int
pxDiscountOrdTypList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxDiscountOrdTypStartBrowse((tDISCOUNTORDERTYP*)keys, cursorid);
}
