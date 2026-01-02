#include "pxartoldprice.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxArtOldPrice :: pxArtOldPrice()
{
    Init();
}

pxArtOldPrice :: pxArtOldPrice
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
pxArtOldPrice :: pxArtOldPrice
(
    pxArtOldPrice& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLEOLDPRICE structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxArtOldPrice :: pxArtOldPrice
(
    pxSession   *session,
    tARTICLEOLDPRICE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtOldPrice :: pxArtOldPrice
(
    pxSession   *session,
    short   BranchNo,
    long    ArticleNo                // Read via this type
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
pxArtOldPrice :: ~pxArtOldPrice()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLEOLDPRICE structure.    */
/*----------------------------------------------------------------------------*/
tARTICLEOLDPRICE&
Assign
(
    tARTICLEOLDPRICE&     dest,
    const pxArtOldPrice&  src
)
{

    dest.BranchNo           = src.BranchNo_;
    dest.ArticleNo          = src.ArticleNo_;
    dest.PreisEKApo         = src.PreisEKApo_;
    dest.PreisEKGrosso      = src.PreisEKGrosso_;
    dest.PreisEKGrossoNA    = src.PreisEKGrossoNA_;
    dest.PreisVKApo         = src.PreisVKApo_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLEOLDPRICE structure to a            */
/*  pxArtOldPrice object.                                                     */
/*----------------------------------------------------------------------------*/
pxArtOldPrice&
Assign
(
    pxArtOldPrice&          dest,
    const tARTICLEOLDPRICE& src
)
{
    dest.BranchNo_           = src.BranchNo;
    dest.ArticleNo_          = src.ArticleNo;
    dest.PreisEKApo_         = src.PreisEKApo;
    dest.PreisEKGrosso_      = src.PreisEKGrosso;
    dest.PreisEKGrossoNA_    = src.PreisEKGrossoNA;
    dest.PreisVKApo_         = src.PreisVKApo;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtOldPrice :: Init()
{
    tARTICLEOLDPRICE    record;
    memset(&record, 0 , sizeof(tARTICLEOLDPRICE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tARTICLEOLDPRICE struct*/
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxArtOldPrice&
pxArtOldPrice :: operator=( const pxArtOldPrice& src)
{
    tARTICLEOLDPRICE    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLEOLDPRICE structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxArtOldPrice&
pxArtOldPrice :: operator=( const tARTICLEOLDPRICE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtOldPrice :: Get
(
    DBAccessMode mode
)

{
    tARTICLEOLDPRICE record;
    memset(&record, 0, sizeof(tARTICLEOLDPRICE));
    Assign(record, *this);              // resolve keys
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tARTICLEOLDPRICE struct
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
pxArtOldPrice :: Put
(
)

{
    tARTICLEOLDPRICE record;
    memset(&record, 0, sizeof(tARTICLEOLDPRICE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTICLEOLDPRICE));
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArtOldPrice :: Delete
(
)
{
    tARTICLEOLDPRICE record;
    memset(&record, 0, sizeof(tARTICLEOLDPRICE));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtOldPrice :: Read
(
    const void  *record
)
{

    return pxArtOldPriceRead((tARTICLEOLDPRICE*)record);
}

int
pxArtOldPrice :: ReadLock
(
    const void  *record
)
{

    return pxArtOldPriceReadLock((tARTICLEOLDPRICE*)record);
    //return cDBXR_ISDOWN;                // not implemented
}

int
pxArtOldPrice :: Update
(
    const void  *record
)
{

    return pxArtOldPriceUpdate((tARTICLEOLDPRICE*)record);
    //return cDBXR_ISDOWN;                // not implemented
}

int
pxArtOldPrice :: Insert
(
    const void  *record
)
{

    return pxArtOldPriceInsert((tARTICLEOLDPRICE*)record);
}

int
pxArtOldPrice :: Delete
(
    const void  *record
)
{
    return  pxArtOldPriceDelete((tARTICLEOLDPRICE*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtOldPrice list objects being inserted in the following ascending */
/*  sequence:    ArticleNo, DatumGueltigAb, DatumGueltigBis.                  */
/*----------------------------------------------------------------------------*/
int
pxArtOldPrice :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxArtOldPrice *that = (pxArtOldPrice*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                  : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )               // then ArticleNo ==
         retval = (ArticleNo_ == that->ArticleNo_) ? 0
                  : (ArticleNo_ > that->ArticleNo_ ? 1 : -1);
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxArtOldPriceList :: pxArtOldPriceList
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
pxArtOldPriceList :: Select
(
    const short   BranchNo,
    const long    ArticleNo,
    const int     count_                // Max number of records to read
)

{

    tARTICLEOLDPRICE a;
    memset(&a, 0, sizeof(tARTICLEOLDPRICE));     // zero out entire record buffer
    a.BranchNo  = BranchNo;
    a.ArticleNo = ArticleNo;
    return Select(&a, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tARTICLEOLDPRICE struct*/
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxArtOldPriceList :: Select
(
          tARTICLEOLDPRICE *recordp,
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
pxArtOldPriceList :: AddToList
(
    const void  *record,
    const int  /* row */
)

{
    pxArtOldPrice *objectp = new pxArtOldPrice(Session(), *(tARTICLEOLDPRICE*) record); // construct new object
    InsertAscending(objectp);
    return objectp;
}

int
pxArtOldPriceList :: EndBrowse
(
    const int  cursorid
)
{

    return pxArtOldPriceEndBrowse(cursorid);
}


int
pxArtOldPriceList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxArtOldPriceGetNext((tARTICLEOLDPRICE*)record, cursorid);
}

int
pxArtOldPriceList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxArtOldPriceStartBrowse((tARTICLEOLDPRICE*)keys, cursorid);
}
