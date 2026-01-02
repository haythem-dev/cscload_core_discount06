/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOrderPosCalcMode  methods.

REVISION HISTORY

06 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxorderposcalcmode.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderPosCalcMode :: pxOrderPosCalcMode
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
pxOrderPosCalcMode :: pxOrderPosCalcMode
(
    pxOrderPosCalcMode& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRPOSRECHART structure to construct this instance.             */
/*----------------------------------------------------------------------------*/
pxOrderPosCalcMode :: pxOrderPosCalcMode
(
    pxSession   *session,
    tKDAUFTRPOSRECHART& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderPosCalcMode :: pxOrderPosCalcMode
(
    pxSession    *session,
    const long   KdAuftragNr,         // customer ordernumber
    const long   PosNr                // posnumber
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_      = KdAuftragNr;
    PosNr_            = PosNr;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderPosCalcMode :: ~pxOrderPosCalcMode()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRPOSRECHART structure. */
/*----------------------------------------------------------------------------*/
tKDAUFTRPOSRECHART&
Assign
(
    tKDAUFTRPOSRECHART&           dest,
    const pxOrderPosCalcMode&     src
)
{
    dest.KdAuftragNr            = src.KdAuftragNr_            ;
    dest.PosNr                  = src.PosNr_                  ;
    dest.SurchargePct           = src.SurchargePct_           ;
    dest.DeductionPct           = src.DeductionPct_           ;
    dest.Surcharge_Calc         = src.SurchargeCalc_          ;
    dest.CalcAvp                = src.CalcAvp_                ;
    dest.Surcharge_Calc_Dis     = src.SurchargeCalcDis_          ;
    dest.CalcAvp_Dis            = src.CalcAvpDis_                ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRPOSRECHART structure to           */
/*  a pxOrderPosCalcMode object.                                                    */
/*----------------------------------------------------------------------------*/
pxOrderPosCalcMode&
Assign
(
    pxOrderPosCalcMode&              dest,
    const tKDAUFTRPOSRECHART&         src
)
{
    dest.KdAuftragNr_            = src.KdAuftragNr            ;
    dest.PosNr_                  = src.PosNr                  ;
    dest.SurchargePct_           = src.SurchargePct           ;
    dest.DeductionPct_           = src.DeductionPct           ;
    dest.SurchargeCalc_          = src.Surcharge_Calc         ;
    dest.CalcAvp_                = src.CalcAvp                ;
    dest.SurchargeCalcDis_       = src.Surcharge_Calc_Dis         ;
    dest.CalcAvpDis_             = src.CalcAvp_Dis                ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderPosCalcMode :: Init()
{
    tKDAUFTRPOSRECHART    record;
    memset(&record, 0 , sizeof(tKDAUFTRPOSRECHART));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRPOSRECHART struct and then imported to self.                        */
/*----------------------------------------------------------------------------*/
pxOrderPosCalcMode&
pxOrderPosCalcMode :: operator=( const pxOrderPosCalcMode& src)
{
    tKDAUFTRPOSRECHART record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRPOSRECHART structure 'src' to           */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxOrderPosCalcMode&
pxOrderPosCalcMode :: operator=( const tKDAUFTRPOSRECHART& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderPosCalcMode :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRPOSRECHART record;
    memset(&record, 0, sizeof(tKDAUFTRPOSRECHART));
    record.KdAuftragNr    = KdAuftragNr_ ;
    record.PosNr          = PosNr_ ;

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRPOSRECHART struct
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
pxOrderPosCalcMode :: Put
(
)
{
    tKDAUFTRPOSRECHART record;
    memset(&record, 0, sizeof(tKDAUFTRPOSRECHART));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRPOSRECHART));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxOrderPosCalcMode :: Delete
(
)
{
    tKDAUFTRPOSRECHART record;
    memset(&record, 0, sizeof(tKDAUFTRPOSRECHART));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderPosCalcMode :: Read
(
    const void  *record
)
{
    return pxOrderPosCalcModeRead((tKDAUFTRPOSRECHART*)record);
}

int
pxOrderPosCalcMode :: ReadLock
(
    const void  *record
)
{
    return pxOrderPosCalcModeReadLock((tKDAUFTRPOSRECHART*)record);
}

int
pxOrderPosCalcMode :: Update
(
    const void  *record
)
{
    return pxOrderPosCalcModeUpdate((tKDAUFTRPOSRECHART*)record);
}

int
pxOrderPosCalcMode :: Delete
(
    const void  *record
)
{
    return pxOrderPosCalcModeDelete((tKDAUFTRPOSRECHART*)record);
}

int
pxOrderPosCalcMode :: Insert
(
    const void  *record
)
{
    return pxOrderPosCalcModeInsert((tKDAUFTRPOSRECHART*)record);
}

int
pxOrderPosCalcModeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOrderPosCalcModeEndBrowse(cursorid);
}


int
pxOrderPosCalcModeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxOrderPosCalcModeGetNext((tKDAUFTRPOSRECHART*)record, cursorid);
}

int
pxOrderPosCalcModeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOrderPosCalcModeStartBrowse((tKDAUFTRPOSRECHART*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderPosCalcMode list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxOrderPosCalcMode :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderPosCalcMode *that = (pxOrderPosCalcMode*)That;

    int retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderPosCalcModeList :: pxOrderPosCalcModeList
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
pxOrderPosCalcModeList :: Select
(
    const long   KdAuftragNr,
    const long   PosNr,
    const int    count_
)
{
    tKDAUFTRPOSRECHART fil;
    memset(&fil, 0, sizeof(tKDAUFTRPOSRECHART));  // zero out entire record buffer
    fil.KdAuftragNr  = KdAuftragNr;
    fil.PosNr        = PosNr;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderPosCalcModeList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxOrderPosCalcMode' object:
    pxOrderPosCalcMode *objectp = new pxOrderPosCalcMode(Session(), *(tKDAUFTRPOSRECHART*) record);
    InsertAscending(objectp);
    return objectp;
}
