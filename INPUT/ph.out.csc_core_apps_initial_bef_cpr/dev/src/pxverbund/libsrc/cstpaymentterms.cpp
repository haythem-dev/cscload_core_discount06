#include "pxcstpaymentterms.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCstPaymentTerms :: pxCstPaymentTerms
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
pxCstPaymentTerms :: pxCstPaymentTerms
(
    pxCstPaymentTerms& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCSTPAYMENTTERMS structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxCstPaymentTerms :: pxCstPaymentTerms
(
    pxSession   *session,
    tCSTPAYMENTTERMS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstPaymentTerms :: pxCstPaymentTerms
(
    pxSession *session,
   const pxCstPaymentTerms *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
       (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  read one table entry to construct this instance                           */
/*----------------------------------------------------------------------------*/
pxCstPaymentTerms :: pxCstPaymentTerms
(
    pxSession *session,
    const short    BranchNo,            // Branchno
    const long     CustomerNo,          // Customer number
    const PriceTypeEnum PriceType,      // Pricetype
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_     = BranchNo;
    CustomerNo_   = CustomerNo;
    PreisTyp_     = PriceType;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCstPaymentTerms :: ~pxCstPaymentTerms()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCSTPAYMENTTERMS structure.           */
/*----------------------------------------------------------------------------*/
tCSTPAYMENTTERMS&
Assign
(
    tCSTPAYMENTTERMS&           dest,
    const pxCstPaymentTerms&       src
)
{
    dest.BranchNo               = src.BranchNo_      ;
    dest.CustomerNo             = src.CustomerNo_    ;
    dest.Preis_Typ              = static_cast<short>(src.PreisTyp_);
    dest.PaymentTarget          = src.PaymentTarget_ ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCSTPAYMENTTERMS structure to                     */
/*  a pxCstPaymentTerms object.                                                      */
/*----------------------------------------------------------------------------*/
pxCstPaymentTerms&
Assign
(
    pxCstPaymentTerms&              dest,
    const tCSTPAYMENTTERMS&    src
)
{
    dest.BranchNo_               = src.BranchNo      ;
    dest.CustomerNo_             = src.CustomerNo    ;
    dest.PreisTyp_               = static_cast<PriceTypeEnum>(src.Preis_Typ);
    dest.PaymentTarget_          = src.PaymentTarget ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCstPaymentTerms :: Init()
{
    tCSTPAYMENTTERMS    record;
    memset(&record, 0 , sizeof(tCSTPAYMENTTERMS));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCSTPAYMENTTERMS struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxCstPaymentTerms&
pxCstPaymentTerms :: operator=( const pxCstPaymentTerms& src)
{
    tCSTPAYMENTTERMS record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCSTPAYMENTTERMS structure 'src' to                     */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCstPaymentTerms&
pxCstPaymentTerms :: operator=( const tCSTPAYMENTTERMS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCstPaymentTerms list objects being inserted in the                     */
/*  following ascending sequence:                                             */
/*----------------------------------------------------------------------------*/
int
pxCstPaymentTerms :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxCstPaymentTerms *that = (pxCstPaymentTerms*)That;
    int retval = (PreisTyp_ == that->PreisTyp_) ? 0
                : (PreisTyp_ > that->PreisTyp_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCstPaymentTerms :: Get
(
    DBAccessMode mode
)

{
    tCSTPAYMENTTERMS record;
    memset(&record, 0, sizeof(tCSTPAYMENTTERMS));
    record.BranchNo   = BranchNo_;
    record.CustomerNo = CustomerNo_;
    record.Preis_Typ  = static_cast<short>(PreisTyp_);
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
pxCstPaymentTerms :: Put
(
)
{
    tCSTPAYMENTTERMS record;
    memset(&record, 0, sizeof(tCSTPAYMENTTERMS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCSTPAYMENTTERMS));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCstPaymentTerms :: Delete
(
)
{
    tCSTPAYMENTTERMS record;
    memset(&record, 0, sizeof(tCSTPAYMENTTERMS));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCstPaymentTerms :: Read
(
    const void  *record
)
{
    return pxCstPaymentTermsRead((tCSTPAYMENTTERMS*)record);
}

int
pxCstPaymentTerms :: ReadLock
(
    const void  *record
)
{
    return pxCstPaymentTermsReadLock((tCSTPAYMENTTERMS*)record);
}

int
pxCstPaymentTerms :: Update
(
    const void  *record
)
{
    return pxCstPaymentTermsUpdate((tCSTPAYMENTTERMS*)record);
}

int
pxCstPaymentTerms :: Delete
(
    const void  *record
)
{
    return pxCstPaymentTermsDelete((tCSTPAYMENTTERMS*)record);
}

int
pxCstPaymentTerms :: Insert
(
    const void  *record
)
{
    return pxCstPaymentTermsInsert((tCSTPAYMENTTERMS*)record);
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstPaymentTermsList :: pxCstPaymentTermsList
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
pxCstPaymentTermsList :: Select
(
    const int     count_
)
{
    tCSTPAYMENTTERMS fil;
    memset(&fil, 0, sizeof(tCSTPAYMENTTERMS));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via Promotion Number                          */
/*----------------------------------------------------------------------------*/
size_t
pxCstPaymentTermsList :: Select
(
    const short    BranchNo,
    const long     CustomerNo,
    const int      count_
)
{
    tCSTPAYMENTTERMS fil;
    memset(&fil, 0, sizeof(tCSTPAYMENTTERMS));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/* Find returns a pxCstPaymentTerms pointer to the corresponding entry        */
/* depend on given PriceType. If entry is not found within the list, so NULLP */
/* will be returned                                                           */
/*----------------------------------------------------------------------------*/
pxCstPaymentTerms*
pxCstPaymentTermsList :: Find
(
    const PriceTypeEnum PriceType
)
{
    pxCstPaymentTermsListIter   iter( *this );        // define iterator
    pxCstPaymentTerms           *entryp = NULL;       // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxCstPaymentTerms*) ++iter) != NULL ) // browse list
    {
       if ( (entryp->PreisTyp() == PriceType ) )
          break;
    }
    return   entryp;                               // return entrypointer
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCstPaymentTermsList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCstPaymentTerms' object:
    pxCstPaymentTerms *objectp = new pxCstPaymentTerms(Session(), *(tCSTPAYMENTTERMS*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCstPaymentTermsList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCstPaymentTermsEndBrowse(cursorid);
}


int
pxCstPaymentTermsList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxCstPaymentTermsGetNext((tCSTPAYMENTTERMS*)record, cursorid);
}

int
pxCstPaymentTermsList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCstPaymentTermsStartBrowse((tCSTPAYMENTTERMS*)keys, cursorid);
}
