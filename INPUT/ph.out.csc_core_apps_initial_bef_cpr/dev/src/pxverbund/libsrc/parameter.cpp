/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxParameter  methods.

REVISION HISTORY

13 March 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxparameter.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxParameter :: pxParameter
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
pxParameter :: pxParameter
(
    pxParameter& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tPARAMETER structure to construct this instance.                      */
/*----------------------------------------------------------------------------*/
pxParameter :: pxParameter
(
    pxSession   *session,
    tPARAMETER& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Construct this object                                                     */
/*----------------------------------------------------------------------------*/
pxParameter :: pxParameter
(
    pxSession      *session,
    const short   FilialNr,
    const nString& ProgrammName,
    const nString& Zweck,
    const nString& ParameterName
)
    : pxDBRecord(session)
{
    Init();
    FilialNr_      = FilialNr;
    ProgrammName_  = ProgrammName;
    Zweck_         = Zweck;
    ParameterName_ = ParameterName;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxParameter :: ~pxParameter()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tPARAMETER structure.      */
/*----------------------------------------------------------------------------*/
tPARAMETER&
Assign
(
    tPARAMETER&           dest,
    const pxParameter&       src
)
{
    dest.FilialNr                  = src.FilialNr_                           ;
    dest.ProgrammName[0] = ' ';
    dest.Zweck[0] = '0';
    dest.ParameterName[0] = '0';
    dest.AusPraegung[0]   = '0';
    src.ProgrammName_.GetData(dest.ProgrammName);
    src.Zweck_.GetData(dest.Zweck);
    src.ParameterName_.GetData(dest.ParameterName);
    src.AusPraegung_.GetData(dest.AusPraegung);
    dest.Wert                      = src.Wert_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tPARAMETER structure to                    */
/*  a pxParameter object.                                                     */
/*----------------------------------------------------------------------------*/
pxParameter&
Assign
(
    pxParameter&              dest,
    const tPARAMETER&    src
)
{
    dest.FilialNr_                 = src.FilialNr                            ;
    dest.ProgrammName_             = src.ProgrammName                        ;
    dest.Zweck_                    = src.Zweck                               ;
    dest.ParameterName_            = src.ParameterName                       ;
    dest.AusPraegung_              = src.AusPraegung                         ;
    dest.Wert_                     = src.Wert                                ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxParameter :: Init()
{
    tPARAMETER    record;
    memset(&record, 0 , sizeof(tPARAMETER));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tPARAMETER struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxParameter&
pxParameter :: operator=( const pxParameter& src)
{
    tPARAMETER record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tPARAMETER structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxParameter&
pxParameter :: operator=( const tPARAMETER& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxParameter :: Get
(
    DBAccessMode mode
)

{
    tPARAMETER record;
    memset(&record, 0, sizeof(tPARAMETER));
    record.FilialNr       = FilialNr_;
    record.ProgrammName[0] = '0';
    record.Zweck[0] = '0';
    record.ParameterName[0] = ' ';
    ProgrammName_.GetData(record.ProgrammName) ;
    Zweck_.GetData(record.Zweck);
    ParameterName_.GetData(record.ParameterName);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tPARAMETER struct
    //else if ( retval > cDBXR_NORMAL )
    //   ExternalCondition(CMsgStream(),
    //                     CMSG_AD_DELPOS_NOTFOUND, KdAuftragNr_,PosNr_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxParameter :: Put
(
)
{
    tPARAMETER record;
    memset(&record, 0, sizeof(tPARAMETER));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tPARAMETER));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxParameter :: Delete
(
)
{
    tPARAMETER record;
    memset(&record, 0, sizeof(tPARAMETER));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxParameter :: Read
(
    const void  *record
)
{
    return pxParameterRead((tPARAMETER*)record);
}

int
pxParameter :: ReadLock
(
    const void  *record
)
{
    return pxParameterReadLock((tPARAMETER*)record);
}

int
pxParameter :: Update
(
    const void  *record
)
{
    return pxParameterUpdate((tPARAMETER*)record);
}

int
pxParameter :: Delete
(
    const void  *record
)
{
    return pxParameterDelete((tPARAMETER*)record);
}

int
pxParameter :: Insert
(
    const void  *record
)
{
    return pxParameterInsert((tPARAMETER*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxParameter list objects being inserted in the                  */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxParameter :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxParameter *that = (pxParameter*)That;
    int retval = (ProgrammName_ == that->ProgrammName_) ? 0
                : (ProgrammName_ > that->ProgrammName_ ? 1 : -1);
    if ( retval == 0 )
       retval = (Wert_ == that->Wert_) ? 0
                : (Wert_ > that->Wert_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxParameterList :: pxParameterList
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
pxParameterList :: Select
(
    const int     count_
)
{
    tPARAMETER fil;
    memset(&fil, 0, sizeof(tPARAMETER));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxParameterList :: Select
(
    const short    FilialNr,
    const nString&  ProgrammName,
    const nString&  Zweck,
    const nString&  ParameterName,
        const long     Wert,
    const int     count_

)
{
    tPARAMETER fil;
    memset(&fil, 0, sizeof(tPARAMETER));  // zero out entire record buffer
    fil.FilialNr      = FilialNr;
    fil.ProgrammName[0]  = ' ';
    fil.Zweck[0]         = ' ';
    fil.ParameterName[0] = ' ';
    ProgrammName.GetData(fil.ProgrammName);
    Zweck.GetData(fil.Zweck);
    ParameterName.GetData(fil.ParameterName);
        fil.Wert             = Wert;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxParameterList :: Select
(
    const short    FilialNr,
    const nString&  ProgrammName,
    const nString&  Zweck,
    const nString&  ParameterName,
    const int     count_

)
{
    tPARAMETER fil;
    memset(&fil, 0, sizeof(tPARAMETER));  // zero out entire record buffer
    fil.FilialNr      = FilialNr;
    fil.ProgrammName[0]  = ' ';
    fil.Zweck[0]         = ' ';
    fil.ParameterName[0] = ' ';
    ProgrammName.GetData(fil.ProgrammName);
    Zweck.GetData(fil.Zweck);
    ParameterName.GetData(fil.ParameterName);
    int cursorid = cCRSPARAMETER_MINT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Find: returns a pxParameter pointer depend on ArtikelNr                   */
/*----------------------------------------------------------------------------*/
pxParameter*
pxParameterList :: Find
(
    const nString&  AusPraegung
)
{
    pxParameter* paramp = NULL;
    pxParameterListIter cursor(*this);

    while ( (paramp = (pxParameter*) ++cursor) != NULL )
    {
       nString art =  paramp->AusPraegung();
       art.Trim(AusPraegung.Length());
       if ( art == AusPraegung )
       {
          break;
       }
    }
    return paramp;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxParameterList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxParameter' object:
    pxParameter *objectp = new pxParameter(Session(), *(tPARAMETER*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxParameterList :: EndBrowse
(
    const int  cursorid
)
{
    return pxParameterEndBrowse(cursorid);
}


int
pxParameterList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxParameterGetNext((tPARAMETER*)record, cursorid);
}

int
pxParameterList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxParameterStartBrowse((tPARAMETER*)keys, cursorid);
}

