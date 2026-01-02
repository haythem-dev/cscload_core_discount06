#include "pxcsterm.hpp"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxCustTerms :: pxCustTerms
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
pxCustTerms :: pxCustTerms
(
    pxCustTerms& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKUNDEKONDI structure to construct this instance.                     */
/*----------------------------------------------------------------------------*/
pxCustTerms :: pxCustTerms
(
    pxSession   *session,
    tKUNDEKONDI&     src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustTerms :: pxCustTerms
(
    pxSession   *session,
    short   VZNr,                // Read via this type
    long    KdNr,                // Read via this type
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    VertriebszentrumNr_ = VZNr;
    KundenNr_ = KdNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustTerms :: ~pxCustTerms()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKUNDEKONDI structure.         */
/*----------------------------------------------------------------------------*/
tKUNDEKONDI&
Assign
(
    tKUNDEKONDI&       dest,
    const pxCustTerms& src
)
{

    dest.IDFNr               = src.IDFNr_;
    dest.VertriebszentrumNr  = src.VertriebszentrumNr_;
    dest.KundenNr            = src.KundenNr_;
    dest.BuendelRundungProz  = src.BuendelRundungProz_;
    dest.TagAutoValuta       = src.TagAutoValuta_;
    dest.ValutaTageMax       = src.ValutaTageMax_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKUNDEKONDI structure to a pxCustTerms object.   */
/*----------------------------------------------------------------------------*/
pxCustTerms&
Assign
(
    pxCustTerms&    dest,
    const tKUNDEKONDI&  src
)
{

    dest.IDFNr_              = src.IDFNr;
    dest.VertriebszentrumNr_ = src.VertriebszentrumNr;
    dest.KundenNr_           = src.KundenNr;
    dest.BuendelRundungProz_ = src.BuendelRundungProz;
    dest.TagAutoValuta_      = src.TagAutoValuta;
    dest.ValutaTageMax_      = src.ValutaTageMax;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustTerms :: Init()
{
    tKUNDEKONDI    record;
    memset(&record, 0 , sizeof(tKUNDEKONDI));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tKUNDEKONDI struct  */
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxCustTerms&
pxCustTerms :: operator=( const pxCustTerms& src)
{
    tKUNDEKONDI    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKUNDEKONDI structure 'src' to this instance.    */
/*----------------------------------------------------------------------------*/
pxCustTerms&
pxCustTerms :: operator=( const tKUNDEKONDI& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustTerms :: Get
(
    DBAccessMode mode
)

{
    tKUNDEKONDI record;
    memset(&record, 0, sizeof(tKUNDEKONDI));
    record.VertriebszentrumNr = VertriebszentrumNr_;
    record.KundenNr = KundenNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tKUNDEKONDI struct
    else
       DBCondition(nMessage(CMsgStream(), CMSG_CST_NOTERMS, KundenNr_),
                   retval);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustTerms :: Read
(
    const void  *record
)
{

    return pxKundeKondiRead((tKUNDEKONDI*)record);
}

/*----------------------------------------------------------------------------*/
/*  Container construction.                                                   */
/*----------------------------------------------------------------------------*/
pxCustTermsList :: pxCustTermsList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using single string value arguments.                 */
/*----------------------------------------------------------------------------*/
size_t
pxCustTermsList :: Select
(
    const int     count_                // Max number of records to read
)

{

    tKUNDEKONDI k;
    memset(&k, 0, sizeof(tKUNDEKONDI));     // zero out entire record buffer
    return Select(&k, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tKUNDEKONDI structure. */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxCustTermsList :: Select
(
          tKUNDEKONDI   *kundep,
    const int     count_
)

{
    int cursorid = cCRS_DEFAULT;
    nDBSelect(kundep, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustTermsList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxCustTerms *objectp = new pxCustTerms(Session(), *(tKUNDEKONDI*) record); // construct new object
    Append(objectp);
    return objectp;
}

int
pxCustTermsList :: EndBrowse
(
    const int  cursorid
)
{

    return pxKundeKondiEndBrowse(cursorid);
}


int
pxCustTermsList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxKundeKondiGetNext((tKUNDEKONDI*)record, cursorid);
}

int
pxCustTermsList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxKundeKondiStartBrowse((tKUNDEKONDI*)keys, cursorid);
}
