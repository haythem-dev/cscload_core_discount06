#include "pxarticlelppr.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxArticleLppr :: pxArticleLppr()
{
    Init();
}

pxArticleLppr :: pxArticleLppr
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
pxArticleLppr :: pxArticleLppr
(
    pxArticleLppr& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLELPPR structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxArticleLppr :: pxArticleLppr
(
    pxSession   *session,
    tARTICLELPPR& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleLppr :: pxArticleLppr
(
    pxSession   *session,
    long    ArticleNo,                // Read via this type
    char    Type
)
    : pxDBRecord(session)
{
    Init();
    ArticleNo_         = ArticleNo;
    ReimbursementType_ = Type;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArticleLppr :: ~pxArticleLppr()
{
 //   delete subobjects;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLELPPR structure.        */
/*----------------------------------------------------------------------------*/
tARTICLELPPR&
Assign
(
    tARTICLELPPR&     dest,
    const pxArticleLppr&  src
)
{

    dest.ArticleNo          = src.ArticleNo_;
    dest.Reimbursement_Type  = src.ReimbursementType_;
    dest.ReimbursementPrice = src.ReimbursementPrice_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLELPPR structure to a                */
/*  pxArticleLppr object.                                                     */
/*----------------------------------------------------------------------------*/
pxArticleLppr&
Assign
(
    pxArticleLppr&          dest,
    const tARTICLELPPR& src
)
{
    dest.ArticleNo_          = src.ArticleNo;
    dest.ReimbursementType_  = src.Reimbursement_Type;
    dest.ReimbursementPrice_ = src.ReimbursementPrice;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArticleLppr :: Init()
{
    tARTICLELPPR    record;
    memset(&record, 0 , sizeof(tARTICLELPPR));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tARTICLELPPR struct*/
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxArticleLppr&
pxArticleLppr :: operator=( const pxArticleLppr& src)
{
    tARTICLELPPR    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLELPPR structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxArticleLppr&
pxArticleLppr :: operator=( const tARTICLELPPR& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArticleLppr :: Get
(
    DBAccessMode mode
)

{
    tARTICLELPPR record;
    memset(&record, 0, sizeof(tARTICLELPPR));
    Assign(record, *this);              // resolve keys
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tARTICLELPPR struct
   /* else if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(), CMSG_ART_NOBASEPRICES,
                   ArtikelNr_),retval);
    */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArticleLppr :: Put
(
)

{
    tARTICLELPPR record;
    memset(&record, 0, sizeof(tARTICLELPPR));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTICLELPPR));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArticleLppr :: Read
(
    const void  *record
)
{

    return pxArticleLpprRead((tARTICLELPPR*)record);
}

int
pxArticleLppr :: ReadLock
(
    const void  *record
)
{

    return pxArticleLpprReadLock((tARTICLELPPR*)record);
    //return cDBXR_ISDOWN;                // not implemented
}

int
pxArticleLppr :: Update
(
    const void  *record
)
{

    return pxArticleLpprUpdate((tARTICLELPPR*)record);
    //return cDBXR_ISDOWN;                // not implemented
}

int
pxArticleLppr :: Insert
(
    const void  *record
)
{

    return pxArticleLpprInsert((tARTICLELPPR*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArticleLppr list objects being inserted in the following ascending */
/*  sequence:    ArticleNo, DatumGueltigAb, DatumGueltigBis.                  */
/*----------------------------------------------------------------------------*/
int
pxArticleLppr :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxArticleLppr *that = (pxArticleLppr*)That;

    int retval = (ArticleNo_ == that->ArticleNo_) ? 0
               : (ArticleNo_ > that->ArticleNo_ ? 1 : -1);
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxArticleLpprList :: pxArticleLpprList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using ArticleNo and current date.                    */
/*----------------------------------------------------------------------------*/
size_t
pxArticleLpprList :: Select
(
    const long    ArticleNo,
    const char    Type,
    const int     count_                // Max number of records to read
)

{

    tARTICLELPPR a;
    memset(&a, 0, sizeof(tARTICLELPPR));     // zero out entire record buffer
    a.ArticleNo = ArticleNo;
    a.Reimbursement_Type = Type;
    return Select(&a, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tARTICLELPPR struct*/
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxArticleLpprList :: Select
(
          tARTICLELPPR *recordp,
    const int           count_
)

{
    // Set the cursor id:
    int cursorid = cCRS_DEFAULT;
    nDBSelect(recordp, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArticleLpprList :: AddToList
(
    const void  *record,
    const int  /* row */
)

{
    pxArticleLppr *objectp = new pxArticleLppr(Session(), *(tARTICLELPPR*) record); // construct new object
    InsertAscending(objectp);
    return objectp;
}

int
pxArticleLpprList :: EndBrowse
(
    const int  cursorid
)
{

    return pxArticleLpprEndBrowse(cursorid);
}


int
pxArticleLpprList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxArticleLpprGetNext((tARTICLELPPR*)record, cursorid);
}

int
pxArticleLpprList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxArticleLpprStartBrowse((tARTICLELPPR*)keys, cursorid);
}
