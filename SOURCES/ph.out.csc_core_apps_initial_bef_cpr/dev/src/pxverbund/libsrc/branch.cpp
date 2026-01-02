#include "pxbranch.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include <logger/loggerpool.h>
#include <sstream>
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxBranch :: pxBranch
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
pxBranch :: pxBranch
(
    pxBranch& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tFILIALE structure to construct this instance.                        */
/*----------------------------------------------------------------------------*/
pxBranch :: pxBranch
(
    pxSession   *session,
    tFILIALE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxBranch :: pxBranch
(
    pxSession   *session,
    short      FilialNr,                 // Read via this type
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    std::stringstream ss;
    ss << "pxBranch::pxBranch(): FilialNr<" << FilialNr << ">";
    BLOG_TRACE( libcsc::LoggerPool::getLoggerSession(), ss.str().c_str() );

    Init();
    FilialNr_ = FilialNr;
    Store_ = FilialNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxBranch :: ~pxBranch()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tFILIALE structure.            */
/*----------------------------------------------------------------------------*/
tFILIALE&
Assign
(
    tFILIALE&    dest,
    const pxBranch&  src
)
{
    // Copy native data types:
    dest.FilialNr        = src.FilialNr_;
    dest.BGANr           = src.BGANr_;
    dest.BGANr_EK        = src.BGANr_EK_;

    // nStrings:
    dest.Bezeichnung[0]  = ' ';
    src.Bezeichnung_.GetData(dest.Bezeichnung);
    dest.Strasse[0]      = ' ';
    src.Strasse_.GetData(dest.Strasse);
    dest.Ort[0]          = ' ';
    src.Ort_.GetData(dest.Ort);
    dest.Postleitzahl[0] = ' ';
    src.Postleitzahl_.GetData(dest.Postleitzahl);
    dest.Vorwahl[0]      = ' ';
    src.Vorwahl_.GetData(dest.Vorwahl);
    dest.TelNrOVw[0]     = ' ';
    src.TelNrOVw_.GetData(dest.TelNrOVw);
    dest.FaxNrOVw[0]     = ' ';
    src.FaxNrOVw_.GetData(dest.FaxNrOVw);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tFILIALE structure to a pxBranch object.   */
/*----------------------------------------------------------------------------*/
pxBranch&
Assign
(
    pxBranch&        dest,
    const tFILIALE&  src
)
{
    // Copy native data types:
    dest.FilialNr_      = src.FilialNr;
    dest.BGANr_         = src.BGANr;
    dest.BGANr_EK_      = src.BGANr_EK;

    // Strings:
    dest.Bezeichnung_    = src .Bezeichnung;
    dest.Strasse_        = src.Strasse;
    dest.Ort_            = src.Ort;
    dest.Postleitzahl_   = src.Postleitzahl;
    dest.Vorwahl_        = src.Vorwahl;
    dest.TelNrOVw_       = src.TelNrOVw;
    dest.FaxNrOVw_       = src.FaxNrOVw;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxBranch :: Init()
{
    Store_ = -1;

    tFILIALE    record;
    memset(&record, 0 , sizeof(tFILIALE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tFILIALE struct and then imported to self.                                */
/*----------------------------------------------------------------------------*/
pxBranch&
pxBranch :: operator=( const pxBranch& src)
{
    tFILIALE record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tFILIALE structure 'src' to this instance.       */
/*----------------------------------------------------------------------------*/
pxBranch&
pxBranch :: operator=( const tFILIALE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxBranch :: Get
(
    DBAccessMode mode
)

{
    tFILIALE record;
    memset(&record, 0, sizeof(tFILIALE));
    record.FilialNr = FilialNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tFILIALE struct
    //TODO: (MJ) fixed, tested but commented back out (after clarifications), due to the estimated high effort of retesting all dependent programs and modules...
    //else
    //    DBCondition(nMessage(CMsgStream(), CMSG_SESS_NOBRANCH, FilialNr_), CMSG_SESS_NOBRANCH);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxBranch :: Put
(
)
{
    tFILIALE record;
    memset(&record, 0, sizeof(tFILIALE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tFILIALE));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxBranch :: Read
(
    const void  *record
)
{
    return pxFilialeRead((tFILIALE*)record);
}

int
pxBranch :: ReadLock
(
    const void  *record
)
{
    return pxFilialeReadLock((tFILIALE*)record);
}

int
pxBranch :: Update
(
    const void  *record
)
{
    return pxFilialeUpdate((tFILIALE*)record);
}

int
pxBranch :: Insert
(
    const void  *record
)
{
    return pxFilialeInsert((tFILIALE*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxBranch list     */
/*  objects being inserted in the following ascending sequence: FilialNr.     */
/*----------------------------------------------------------------------------*/
int
pxBranch :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const
{
    pxBranch *that = (pxBranch*)That;
    int retval = (FilialNr_ == that->FilialNr_) ? 0
                : (FilialNr_ > that->FilialNr_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxBranchList :: pxBranchList
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
pxBranchList :: Select
(
    const int     count_
)
{
    tFILIALE fil;
    memset(&fil, 0, sizeof(tFILIALE));     // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxBranchList :: AddToList
(
    const void  *record,
    const int  /*row*/
)
{
    // construct new 'pxBranch' object:
    pxBranch *objectp = new pxBranch(Session(), *(tFILIALE*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxBranchList :: EndBrowse
(
    const int  cursorid
)
{
    return pxFilialeEndBrowse(cursorid);
}


int
pxBranchList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxFilialeGetNext((tFILIALE*)record, cursorid);
}

int
pxBranchList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxFilialeStartBrowse((tFILIALE*)keys, cursorid);
}
