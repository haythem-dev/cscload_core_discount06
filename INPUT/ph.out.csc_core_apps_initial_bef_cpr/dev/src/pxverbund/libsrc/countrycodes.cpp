#include "pxcountrycodes.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxCountryCodes :: pxCountryCodes()
{
    Init();
}

pxCountryCodes :: pxCountryCodes
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
pxCountryCodes :: pxCountryCodes
(
    pxCountryCodes& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCOUNTRYCODES structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxCountryCodes :: pxCountryCodes
(
    pxSession   *session,
    tCOUNTRYCODES& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCountryCodes :: pxCountryCodes
(
    pxSession   *session,
    short   BranchNo,
    nString& InfoCode,                // Read via this type
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_   = BranchNo;
    InfoCode_   = InfoCode;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCountryCodes :: ~pxCountryCodes()
{
 //   delete subobjects;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCOUNTRYCODES structure.       */
/*----------------------------------------------------------------------------*/
tCOUNTRYCODES&
Assign
(
    tCOUNTRYCODES&     dest,
    const pxCountryCodes&  src
)
{

    dest.BranchNo           = src.BranchNo_;
    dest.InfoCode[0] = ' ';
    src.InfoCode_.GetData(dest.InfoCode);
    dest.ArticleActiv       = src.ArticleActiv_;
    dest.AuxDelivery        = src.AuxDelivery_;
    dest.SeraCode[0] = ' ';
    src.SeraCode_.GetData(dest.SeraCode);
    dest.PrintCode[0] = ' ';
    src.PrintCode_.GetData(dest.PrintCode);
    dest.XMLCode[0] = ' ';
    src.XMLCode_.GetData(dest.XMLCode);
    dest.XMLText[0] = ' ';
    src.XMLText_.GetData(dest.XMLText);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCOUNTRYCODES structure to a               */
/*  pxCountryCodes object.                                                    */
/*----------------------------------------------------------------------------*/
pxCountryCodes&
Assign
(
    pxCountryCodes&          dest,
    const tCOUNTRYCODES& src
)
{
    dest.BranchNo_           = src.BranchNo;
    dest.InfoCode_           = src.InfoCode;
    dest.ArticleActiv_       = src.ArticleActiv;
    dest.AuxDelivery_        = src.AuxDelivery;
    dest.SeraCode_           = src.SeraCode;
    dest.PrintCode_          = src.PrintCode;
    dest.XMLCode_            = src.XMLCode;
    dest.XMLText_            = src.XMLText;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCountryCodes :: Init()
{
    tCOUNTRYCODES    record;
    memset(&record, 0 , sizeof(tCOUNTRYCODES));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tCOUNTRYCODES struct*/
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxCountryCodes&
pxCountryCodes :: operator=( const pxCountryCodes& src)
{
    tCOUNTRYCODES    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCOUNTRYCODES structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxCountryCodes&
pxCountryCodes :: operator=( const tCOUNTRYCODES& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCountryCodes :: Get
(
    DBAccessMode mode
)

{
    tCOUNTRYCODES record;
    memset(&record, 0, sizeof(tCOUNTRYCODES));
    Assign(record, *this);              // resolve keys
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tCOUNTRYCODES struct
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
pxCountryCodes :: Put
(
)

{
    tCOUNTRYCODES record;
    memset(&record, 0, sizeof(tCOUNTRYCODES));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCOUNTRYCODES));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCountryCodes :: Read
(
    const void  *record
)
{

    return pxCountryCodesRead((tCOUNTRYCODES*)record);
}

int
pxCountryCodes :: ReadLock
(
    const void  *record
)
{

    return pxCountryCodesReadLock((tCOUNTRYCODES*)record);
    //return cDBXR_ISDOWN;                // not implemented
}

int
pxCountryCodes :: Update
(
    const void  *record
)
{

    return pxCountryCodesUpdate((tCOUNTRYCODES*)record);
    //return cDBXR_ISDOWN;                // not implemented
}

int
pxCountryCodes :: Insert
(
    const void  *record
)
{

    return pxCountryCodesInsert((tCOUNTRYCODES*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCountryCodes list objects being inserted in the following ascending */
/*  sequence:    ArticleNo, DatumGueltigAb, DatumGueltigBis.                  */
/*----------------------------------------------------------------------------*/
int
pxCountryCodes :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCountryCodes *that = (pxCountryCodes*)That;

    int retval = (BranchNo_ == that->BranchNo_) ? 0
                  : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )               // then ArticleNo ==
         retval = (InfoCode_ == that->InfoCode_) ? 0
                  : (InfoCode_ > that->InfoCode_ ? 1 : -1);
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxCountryCodesList :: pxCountryCodesList
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
pxCountryCodesList :: Select
(
    const short   BranchNo,
    const nString& Code,
    const short   Type,
    const int     count_                // Max number of records to read
)

{

    tCOUNTRYCODES a;
    memset(&a, 0, sizeof(tCOUNTRYCODES));     // zero out entire record buffer
    a.BranchNo  = BranchNo;
    a.InfoCode[0] = ' ';
    Code.GetData(a.InfoCode);
    a.XMLCode[0] = ' ';
    Code.GetData(a.XMLCode);
    return Select(&a, Type, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tCOUNTRYCODES struct   */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxCountryCodesList :: Select
(
          tCOUNTRYCODES *recordp,
    const short         Type,
    const int           count_
)

{
    // Set the cursor id:
    int cursorid = cCRS_DEFAULT;
    if ( Type == (short) pxCountryCodes :: CCT_XMLCODE )
       cursorid = cCRSCOUNTRYCODES_XMLCODE;
    nDBSelect(recordp, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCountryCodesList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxCountryCodes *objectp = new pxCountryCodes(Session(), *(tCOUNTRYCODES*) record); // construct new object
    InsertAscending(objectp);
    return objectp;
}

int
pxCountryCodesList :: EndBrowse
(
    const int  cursorid
)
{

    return pxCountryCodesEndBrowse(cursorid);
}


int
pxCountryCodesList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxCountryCodesGetNext((tCOUNTRYCODES*)record, cursorid);
}

int
pxCountryCodesList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxCountryCodesStartBrowse((tCOUNTRYCODES*)keys, cursorid);
}
