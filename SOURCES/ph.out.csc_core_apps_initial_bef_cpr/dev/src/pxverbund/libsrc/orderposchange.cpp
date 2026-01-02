/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOrderPosChange  methods.

REVISION HISTORY

20 Aug 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxorderposchange.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderPosChange :: pxOrderPosChange
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
pxOrderPosChange :: pxOrderPosChange
(
    pxOrderPosChange& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGPOSCHANGE structure to construct this instance.              */
/*----------------------------------------------------------------------------*/
pxOrderPosChange :: pxOrderPosChange
(
    pxSession   *session,
    tKDAUFTRAGPOSCHANGE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderPosChange :: pxOrderPosChange
(
    pxSession    *session,
    const long   KdAuftragNr,         // customer ordernumber
    const long   PosNr                // Positionnumber
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
pxOrderPosChange :: ~pxOrderPosChange()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGPOSCHANGE structure.    */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGPOSCHANGE&
Assign
(
    tKDAUFTRAGPOSCHANGE&           dest,
    const pxOrderPosChange&     src
)
{
    dest.KdAuftragNr            = src.KdAuftragNr_     ;
    dest.PosNr                  = src.PosNr_           ;
    dest.MengeBestellt          = src.MengeBestellt_   ;
    dest.MengeBestaetigt        = src.MengeBestaetigt_ ;
    dest.Menge_Alt              = src.MengeAlt_        ;
    dest.SWChecked              = src.SWChecked_       ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGPOSCHANGE structure to            */
/*  a pxOrderPosChange object.                                                 */
/*----------------------------------------------------------------------------*/
pxOrderPosChange&
Assign
(
    pxOrderPosChange&              dest,
    const tKDAUFTRAGPOSCHANGE&         src
)
{
    dest.KdAuftragNr_            = src.KdAuftragNr     ;
    dest.PosNr_                  = src.PosNr           ;
    dest.MengeBestellt_          = src.MengeBestellt   ;
    dest.MengeBestaetigt_        = src.MengeBestaetigt ;
    dest.MengeAlt_               = src.Menge_Alt       ;
    dest.SWChecked_              = src.SWChecked       ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderPosChange :: Init()
{
    tKDAUFTRAGPOSCHANGE    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGPOSCHANGE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGPOSCHANGE struct and then imported to self.                        */
/*----------------------------------------------------------------------------*/
pxOrderPosChange&
pxOrderPosChange :: operator=( const pxOrderPosChange& src)
{
    tKDAUFTRAGPOSCHANGE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPOSCHANGE structure 'src' to              */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxOrderPosChange&
pxOrderPosChange :: operator=( const tKDAUFTRAGPOSCHANGE& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderPosChange :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGPOSCHANGE record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSCHANGE));
    record.KdAuftragNr    = KdAuftragNr_ ;
    record.PosNr          = PosNr_       ;

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGPOSCHANGE struct
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
pxOrderPosChange :: Put
(
)
{
    tKDAUFTRAGPOSCHANGE record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSCHANGE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGPOSCHANGE));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxOrderPosChange :: Delete
(
)
{
    tKDAUFTRAGPOSCHANGE record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSCHANGE));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderPosChange :: Read
(
    const void  *record
)
{
    return pxOrderPosChangeRead((tKDAUFTRAGPOSCHANGE*)record);
}

int
pxOrderPosChange :: ReadLock
(
    const void  *record
)
{
    return pxOrderPosChangeReadLock((tKDAUFTRAGPOSCHANGE*)record);
}

int
pxOrderPosChange :: Update
(
    const void  *record
)
{
    return pxOrderPosChangeUpdate((tKDAUFTRAGPOSCHANGE*)record);
}

int
pxOrderPosChange :: Delete
(
    const void  *record
)
{
    return pxOrderPosChangeDelete((tKDAUFTRAGPOSCHANGE*)record);
}

int
pxOrderPosChange :: Insert
(
    const void  *record
)
{
    return pxOrderPosChangeInsert((tKDAUFTRAGPOSCHANGE*)record);
}

int
pxOrderPosChangeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOrderPosChangeEndBrowse(cursorid);
}


int
pxOrderPosChangeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxOrderPosChangeGetNext((tKDAUFTRAGPOSCHANGE*)record, cursorid);
}

int
pxOrderPosChangeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOrderPosChangeStartBrowse((tKDAUFTRAGPOSCHANGE*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderPosChange list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxOrderPosChange :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxOrderPosChange *that = (pxOrderPosChange*)That;

    int retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);

    if (retval == 0 )
       retval = (PosNr_ == that->PosNr_) ? 0
                : (PosNr_ > that->PosNr_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderPosChangeList :: pxOrderPosChangeList
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
pxOrderPosChangeList :: Select
(
    const long   KdAuftragNr,
    const long   PosNr,
    const int    count_
)
{
    tKDAUFTRAGPOSCHANGE fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGPOSCHANGE));  // zero out entire record buffer
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
pxOrderPosChangeList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxOrderPosChange' object:
    pxOrderPosChange *objectp = new pxOrderPosChange(Session(), *(tKDAUFTRAGPOSCHANGE*) record);
    InsertAscending(objectp);
    return objectp;
}
