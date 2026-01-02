#include "pxartreservation.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtReservation :: pxArtReservation
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
pxArtReservation :: pxArtReservation
(
    pxArtReservation& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLERESERVATION structure to construct this instance.             */
/*----------------------------------------------------------------------------*/
pxArtReservation :: pxArtReservation
(
    pxSession   *session,
    tARTICLERESERVATION& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtReservation :: pxArtReservation
(
    pxSession*          session,
    const short        BranchNo,            // Branchnumber
    const long         ArticleNo            // Articlenumber
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_    = BranchNo;
    ArticleNo_   = ArticleNo;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtReservation :: ~pxArtReservation()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLERESERVATION structure. */
/*----------------------------------------------------------------------------*/
tARTICLERESERVATION&
Assign
(
    tARTICLERESERVATION&        dest,
    const pxArtReservation&     src
)
{
    dest.BranchNo                  = src.BranchNo_       ;
    strncpy(dest.PharmacyGroupId, src.PharmacyGroupId_.c_str(), mSIZEOF(tARTICLERESERVATION, PharmacyGroupId) - 1);
    dest.ArticleNo                 = src.ArticleNo_      ;
    dest.ReservType                = static_cast<short>(src.ReservType_);
    dest.MaxQty                    = src.MaxQty_         ;
    dest.ReservedQty               = src.ReservedQty_    ;
    dest.ReservePct                = src.ReservePct_     ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLERESERVATION structure to           */
/*  a pxArtReservation object.                                                */
/*----------------------------------------------------------------------------*/
pxArtReservation&
Assign
(
    pxArtReservation&              dest,
    const tARTICLERESERVATION&     src
)
{
    dest.BranchNo_                 = src.BranchNo         ;
    dest.PharmacyGroupId_          = src.PharmacyGroupId  ;
    dest.ArticleNo_                = src.ArticleNo        ;
    dest.ReservType_               = static_cast<ReservationTypeEnum>(src.ReservType);
    dest.MaxQty_                   = src.MaxQty           ;
    dest.ReservedQty_              = src.ReservedQty      ;
    dest.ReservePct_               = src.ReservePct       ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtReservation :: Init()
{
    tARTICLERESERVATION    record;
    memset(&record, 0 , sizeof(tARTICLERESERVATION));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTICLERESERVATION struct and then imported to self.                     */
/*----------------------------------------------------------------------------*/
pxArtReservation&
pxArtReservation :: operator=( const pxArtReservation& src)
{
    tARTICLERESERVATION record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLERESERVATION structure 'src' to           */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArtReservation&
pxArtReservation :: operator=( const tARTICLERESERVATION& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtReservation :: Get
(
    DBAccessMode mode
)
{
    tARTICLERESERVATION record;
    memset(&record, 0, sizeof(tARTICLERESERVATION));
    record.BranchNo    = BranchNo_;
    record.ArticleNo   = ArticleNo_;
    record.ReservType  = static_cast<short>(ReservType_);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLERESERVATION struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArtReservation :: Put
(
)
{
    tARTICLERESERVATION record;
    memset(&record, 0, sizeof(tARTICLERESERVATION));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTICLERESERVATION));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArtReservation :: Delete
(
)
{
    tARTICLERESERVATION record;
    memset(&record, 0, sizeof(tARTICLERESERVATION));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/

void pxArtReservation::SetReservType(const ReservationTypeEnum rt)
{
    ReservType_ = rt;
}

/*----------------------------------------------------------------------------*/

void pxArtReservation::SetPharmacyGroupId( const basar::VarString& PharmacyGroupId )
{
    PharmacyGroupId_ = PharmacyGroupId.c_str();
}

/*----------------------------------------------------------------------------*/

void pxArtReservation::SetReservePct( const short pct )
{
	ReservePct_ = pct;
}

/*----------------------------------------------------------------------------*/

void pxArtReservation::SetMaxQty( const long maxqty )
{
	MaxQty_ = maxqty;
}

/*----------------------------------------------------------------------------*/
/*  Add quantity q from quantity ordered. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxArtReservation :: AddReservedQuantity
(
    const long q
)
{
	long ReservedQtyOld = ReservedQty_;
	ReservedQty_ += q;
	if (IsReserveForPharmGroup() && (ReservedQty_ > MaxQty_))
	{
		ReservedQty_ = MaxQty_;
	}
	SetDirty();
	return (ReservedQty_ - ReservedQtyOld);
}

/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity ordered. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxArtReservation :: SubReservedQuantity
(
    const long q                      // quantity to be subtracted
)
{
    long retval;
    // avoid negative values in stock:
    retval = ( ReservedQty_ - q < 0 ) ? ReservedQty_ : q;
    ReservedQty_ -= retval;
    SetDirty();
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Set quantity q from quantity on hand. Returns quantity set  .             */
/*----------------------------------------------------------------------------*/
long
pxArtReservation :: SetReservedQuantity
(
    const long q
)
{
    ReservedQty_ = q;
    SetDirty();
    return q;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtReservation :: Read
(
    const void  *record
)
{
    return pxArtReservationRead((tARTICLERESERVATION*)record);
}

int
pxArtReservation :: ReadLock
(
    const void  *record
)
{
    return pxArtReservationReadLock((tARTICLERESERVATION*)record);
}

int
pxArtReservation :: Update
(
    const void  *record
)
{
    return pxArtReservationUpdate((tARTICLERESERVATION*)record);
}

int
pxArtReservation :: Delete
(
    const void  *record
)
{
    return pxArtReservationDelete((tARTICLERESERVATION*)record);
}

int
pxArtReservation :: Insert
(
    const void  *record
)
{
    return pxArtReservationInsert((tARTICLERESERVATION*)record);
}

int
pxArtReservationList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArtReservationEndBrowse(cursorid);
}


int
pxArtReservationList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxArtReservationGetNext((tARTICLERESERVATION*)record, cursorid);
}

int
pxArtReservationList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArtReservationStartBrowse((tARTICLERESERVATION*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtReservation list objects being inserted in the               */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxArtReservation :: CompareTo
(
    const nCollectable*   That,
          void*          /*p*/,
    const long           /*lparm*/
)   const

{
    pxArtReservation *that = (pxArtReservation*)That;

    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtReservationList :: pxArtReservationList
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
pxArtReservationList :: Select
(
    const short  BranchNo,
    const long   ArticleNo
)
{
    tARTICLERESERVATION fil;
    memset(&fil, 0, sizeof(tARTICLERESERVATION));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    int cursorid    = cCRSARTICLERESERVATION_AllReservations;
	nDBSelect(&fil, cursorid, cDEFAULT);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtReservationList :: AddToList
(
    const void  *record,
    const int  /*row*/
)
{
    pxArtReservation *objectp = new pxArtReservation(Session(), *(tARTICLERESERVATION*) record);
    InsertAscending(objectp);
    return objectp;
}

pxArtReservation* pxArtReservationList::FindReservationType(const ReservationTypeEnum reservType)
{
	pxArtReservation*           articleReservation;
	pxArtReservationListIter    iter(*this);

	while (NULL != (articleReservation = (pxArtReservation*)++iter))
	{
		if (reservType == articleReservation->GetReservType())
			return articleReservation;
	}
	return articleReservation;
}
