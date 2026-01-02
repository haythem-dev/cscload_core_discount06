/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOrderCalcMode  methods.

REVISION HISTORY

06 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxordercalcmode.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderCalcMode :: pxOrderCalcMode
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
pxOrderCalcMode :: pxOrderCalcMode
(
    pxOrderCalcMode& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGRECHART structure to construct this instance.             */
/*----------------------------------------------------------------------------*/
pxOrderCalcMode :: pxOrderCalcMode
(
    pxSession   *session,
    tKDAUFTRAGRECHART& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderCalcMode :: pxOrderCalcMode
(
    pxSession    *session,
    const long   KdAuftragNr         // customer ordernumber
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_      = KdAuftragNr;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderCalcMode :: ~pxOrderCalcMode()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGRECHART structure. */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGRECHART&
Assign
(
    tKDAUFTRAGRECHART&           dest,
    const pxOrderCalcMode&     src
)
{
    dest.Print                  = src.Print_                  ;
    dest.Deduction_Aep           = src.DeductionAep_           ;
    dest.Deduction_Avp           = src.DeductionAvp_           ;
    dest.WithColumnNr           = src.WithColumnNr_           ;
    dest.ByEmail                = src.ByEmail_                ;
    dest.KdAuftragNr            = src.KdAuftragNr_            ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGRECHART structure to           */
/*  a pxOrderCalcMode object.                                                    */
/*----------------------------------------------------------------------------*/
pxOrderCalcMode&
Assign
(
    pxOrderCalcMode&              dest,
    const tKDAUFTRAGRECHART&         src
)
{
    dest.Print_                  = src.Print                  ;
    dest.DeductionAep_           = src.Deduction_Aep           ;
    dest.DeductionAvp_           = src.Deduction_Avp           ;
    dest.WithColumnNr_           = src.WithColumnNr           ;
    dest.ByEmail_                = src.ByEmail                ;
    dest.KdAuftragNr_            = src.KdAuftragNr            ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderCalcMode :: Init()
{
    tKDAUFTRAGRECHART    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGRECHART));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGRECHART struct and then imported to self.                        */
/*----------------------------------------------------------------------------*/
pxOrderCalcMode&
pxOrderCalcMode :: operator=( const pxOrderCalcMode& src)
{
    tKDAUFTRAGRECHART record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGRECHART structure 'src' to           */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxOrderCalcMode&
pxOrderCalcMode :: operator=( const tKDAUFTRAGRECHART& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderCalcMode :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGRECHART record;
    memset(&record, 0, sizeof(tKDAUFTRAGRECHART));
    record.KdAuftragNr    = KdAuftragNr_ ;

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGRECHART struct
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
pxOrderCalcMode :: Put
(
)
{
    tKDAUFTRAGRECHART record;
    memset(&record, 0, sizeof(tKDAUFTRAGRECHART));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGRECHART));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxOrderCalcMode :: Delete
(
)
{
    tKDAUFTRAGRECHART record;
    memset(&record, 0, sizeof(tKDAUFTRAGRECHART));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderCalcMode :: Read
(
    const void  *record
)
{
    return pxOrderCalcModeRead((tKDAUFTRAGRECHART*)record);
}

int
pxOrderCalcMode :: ReadLock
(
    const void  *record
)
{
    return pxOrderCalcModeReadLock((tKDAUFTRAGRECHART*)record);
}

int
pxOrderCalcMode :: Update
(
    const void  *record
)
{
    return pxOrderCalcModeUpdate((tKDAUFTRAGRECHART*)record);
}

int
pxOrderCalcMode :: Delete
(
    const void  *record
)
{
    return pxOrderCalcModeDelete((tKDAUFTRAGRECHART*)record);
}

int
pxOrderCalcMode :: Insert
(
    const void  *record
)
{
    return pxOrderCalcModeInsert((tKDAUFTRAGRECHART*)record);
}

int
pxOrderCalcModeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOrderCalcModeEndBrowse(cursorid);
}


int
pxOrderCalcModeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxOrderCalcModeGetNext((tKDAUFTRAGRECHART*)record, cursorid);
}

int
pxOrderCalcModeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOrderCalcModeStartBrowse((tKDAUFTRAGRECHART*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderCalcMode list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxOrderCalcMode :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderCalcMode *that = (pxOrderCalcMode*)That;

    int retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderCalcModeList :: pxOrderCalcModeList
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
pxOrderCalcModeList :: Select
(
    const long   KdAuftragNr,
    const int    count_
)
{
    tKDAUFTRAGRECHART fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGRECHART));  // zero out entire record buffer
    fil.KdAuftragNr  = KdAuftragNr;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderCalcModeList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxOrderCalcMode' object:
    pxOrderCalcMode *objectp = new pxOrderCalcMode(Session(), *(tKDAUFTRAGRECHART*) record);
    InsertAscending(objectp);
    return objectp;
}
