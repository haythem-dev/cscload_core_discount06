#include "pxarticlecharge.hpp"
#include <boost/lexical_cast.hpp>
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArticleCharge :: pxArticleCharge
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
pxArticleCharge :: pxArticleCharge
(
    pxArticleCharge& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLECHARGE structure to construct this instance.             */
/*----------------------------------------------------------------------------*/
pxArticleCharge :: pxArticleCharge
(
    pxSession   *session,
    tARTICLECHARGE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleCharge :: pxArticleCharge
(
    pxSession*              session,
    const short             BranchNo,            // Branchnumber
    const long              ArticleNo,           // Articlenumber
    const basar::VarString& ChargenNr            // Chargennummer
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_    = BranchNo;
    ArticleNo_   = ArticleNo;
    ChargenNr_   = ChargenNr;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArticleCharge :: ~pxArticleCharge()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLECHARGE structure.      */
/*----------------------------------------------------------------------------*/
tARTICLECHARGE&
Assign
(
    tARTICLECHARGE&           dest,
    const pxArticleCharge&     src
)
{
    dest.BranchNo                  = src.BranchNo_       ;
    dest.ArticleNo                 = src.ArticleNo_      ;
    dest.ExpiryDate                = src.ExpiryDate_.getDate();
	strncpy(dest.ChargenNr, src.ChargenNr_.c_str(), mSIZEOF(tARTICLECHARGE, ChargenNr) - 1);
    dest.Stock                     = src.Stock_          ;
    dest.StateCharge               = src.StateCharge_    ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLECHARGE structure to                */
/*  a pxArticleCharge object.                                                 */
/*----------------------------------------------------------------------------*/
pxArticleCharge&
Assign
(
    pxArticleCharge&              dest,
    const tARTICLECHARGE&         src
)
{
    dest.BranchNo_                 = src.BranchNo         ;
    dest.ArticleNo_                = src.ArticleNo        ;
    dest.ExpiryDate_               = basar::Date(src.ExpiryDate);
    dest.ChargenNr_                = src.ChargenNr        ;
    dest.Stock_                    = src.Stock            ;
    dest.StateCharge_              = src.StateCharge      ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArticleCharge :: Init()
{
    tARTICLECHARGE    record;
    memset(&record, 0 , sizeof(tARTICLECHARGE));
    Assign(*this, record);
    
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTICLECHARGE struct and then imported to self.                     */
/*----------------------------------------------------------------------------*/
pxArticleCharge&
pxArticleCharge :: operator=( const pxArticleCharge& src)
{
    tARTICLECHARGE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLECHARGE structure 'src' to                */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArticleCharge&
pxArticleCharge :: operator=( const tARTICLECHARGE& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArticleCharge :: Get
(
    DBAccessMode mode
)

{
    tARTICLECHARGE record;
    memset(&record, 0, sizeof(tARTICLECHARGE));
    record.BranchNo    = BranchNo_;
    record.ArticleNo   = ArticleNo_;
	strncpy(record.ChargenNr, ChargenNr_.c_str(), mSIZEOF(tARTICLECHARGE, ChargenNr) - 1);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLECHARGE struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArticleCharge :: Put
(
)
{
    tARTICLECHARGE record;
    memset(&record, 0, sizeof(tARTICLECHARGE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTICLECHARGE));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArticleCharge :: Delete
(
)
{
    tARTICLECHARGE record;
    memset(&record, 0, sizeof(tARTICLECHARGE));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Add quantity q from quantity ordered. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxArticleCharge :: AddQuantity
(
    const long q
)
{
    long retval = 0;
    Stock_ += q;
    SetDirty();
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity ordered. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxArticleCharge :: SubQuantity
(
    const long q
)
{
    long retval;
    // avoid negative values in stock:
    retval = ( Stock_ - q < 0 ) ? Stock_ : q;
    Stock_ -= retval;
    SetDirty();
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Set quantity q from quantity on hand. Returns quantity set  .             */
/*----------------------------------------------------------------------------*/
long
pxArticleCharge :: SetQuantity
(
    const long q
)
{
    Stock_ = q;
    SetDirty();
    return q;
}

void
pxArticleCharge :: SetStateCharge
(
	const BatchStatusEnum status
)
{
	switch (status)
	{
		case BATCHSTATUS_NOT_YET_BOOKED : 
		case BATCHSTATUS_SALEABLE :
		case BATCHSTATUS_MISSING_PACKAGE_INSERT :
		case BATCHSTATUS_SOLD :
		case BATCHSTATUS_BATCH_RECALL :
		case BATCHSTATUS_TENDER :
		case BATCHSTATUS_MISSING_CERTIFICATE :
		case BATCHSTATUS_OVERSTOCK :
			StateCharge_ = boost::lexical_cast<char>(status);
			break;
		case BATCHSTATUS_BLOCKED_AUTOMAT :
			StateCharge_ = 'S';
			break;
		case BATCHSTATUS_PREWHOLE_QUARANTINE :
		default :
			StateCharge_ = 'D';
			break;
	}
}

BatchStatusEnum
pxArticleCharge :: StateCharge
(
) const
{
	if (StateCharge_ >= '0' && StateCharge_ <= '9')
		return static_cast<BatchStatusEnum>(boost::lexical_cast<int>(StateCharge_));
	if (StateCharge_ == 'S')
		return BATCHSTATUS_BLOCKED_AUTOMAT;
	return BATCHSTATUS_PREWHOLE_QUARANTINE;
}


/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArticleCharge :: Read
(
    const void  *record
)
{
    return pxArticleChargeRead((struct tARTICLECHARGE*)record);
}

int
pxArticleCharge :: ReadLock
(
    const void  *record
)
{
    return pxArticleChargeReadLock((struct tARTICLECHARGE*)record);
}

int
pxArticleCharge :: Update
(
    const void  *record
)
{
    return pxArticleChargeUpdate((struct tARTICLECHARGE*)record);
}

int
pxArticleCharge :: Delete
(
    const void  *record
)
{
    return pxArticleChargeDelete((struct tARTICLECHARGE*)record);
}

int
pxArticleCharge :: Insert
(
    const void  *record
)
{
    return pxArticleChargeInsert((struct tARTICLECHARGE*)record);
}

int
pxArticleChargeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArticleChargeEndBrowse(cursorid);
}


int
pxArticleChargeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxArticleChargeGetNext((struct tARTICLECHARGE*)record, cursorid);
}

int
pxArticleChargeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArticleChargeStartBrowse((struct tARTICLECHARGE*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArticleCharge list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxArticleCharge :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const

{
    pxArticleCharge *that = (pxArticleCharge*)That;

    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleChargeList :: pxArticleChargeList
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
pxArticleChargeList :: Select
(
    const short  BranchNo,
    const long   ArticleNo
)
{
    tARTICLECHARGE fil;
    memset(&fil, 0, sizeof(tARTICLECHARGE));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    int cursorid   = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, cDEFAULT);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArticleChargeList :: AddToList
(
    const void  *record,
    const int  /*row*/
)

{
    // construct new 'pxArticleCharge' object:
    pxArticleCharge *objectp = new pxArticleCharge(Session(), *(struct tARTICLECHARGE*) record);
    InsertAscending(objectp);
    return objectp;
}

