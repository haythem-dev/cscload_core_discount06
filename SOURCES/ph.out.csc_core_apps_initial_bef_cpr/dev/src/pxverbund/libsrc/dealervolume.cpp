/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxDealerVolume methods.

REVISION HISTORY

17 August 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxdealervolume.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxDealerVolume :: pxDealerVolume
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
pxDealerVolume :: pxDealerVolume
(
    pxDealerVolume& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tDEALERVOLUME structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxDealerVolume :: pxDealerVolume
(
    pxSession   *session,
    tDEALERVOLUME& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDealerVolume :: pxDealerVolume
(
    pxSession *session,
   const pxDealerVolume *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
       (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDealerVolume :: pxDealerVolume
(
    pxSession    *session,
    short        BranchNo,            // Branchnumber
    long         Uid,                 // UserId
    nDate&        date,                // DateInVoice
    long         InVoiceNo            // Invoice number
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_     = BranchNo;
    Uid_          = Uid;
    DateInVoice_  = date;
    InVoiceNo_    = InVoiceNo;
    VolumeState_  = '0';
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxDealerVolume :: ~pxDealerVolume()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDEALERVOLUME structure.         */
/*----------------------------------------------------------------------------*/
tDEALERVOLUME&
Assign
(
    tDEALERVOLUME&           dest,
    const pxDealerVolume&       src
)
{
    dest.BranchNo                 = src.BranchNo_              ;
    dest.Uid                      = src.Uid_                   ;
    dest.InVoiceNo                = src.InVoiceNo_             ;
    dest.OrderNoVSE               = src.OrderNoVSE_            ;
    dest.OrderNoKSC               = src.OrderNoKSC_            ;
    dest.DateInVoice              = src.DateInVoice_.GetYYYYMMDD();
    dest.TimeInVoice              = src.TimeInVoice_.GetHHMMSS();
    dest.InVoiceVolume            = src.InVoiceVolume_;
    dest.Volume1                  = src.Volume1_;
    dest.Volume2                  = src.Volume2_;
    dest.Volume3                  = src.Volume3_;
    dest.Volume4                  = src.Volume4_;
    dest.CustomerNo               = src.CustomerNo_;
    dest.VolumeState              = src.VolumeState_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDEALERVOLUME structure to                   */
/*  a pxDealerVolume object.                                                    */
/*----------------------------------------------------------------------------*/
pxDealerVolume&
Assign
(
    pxDealerVolume&              dest,
    const tDEALERVOLUME&    src
)
{
    dest.BranchNo_                = src.BranchNo               ;
    dest.Uid_                     = src.Uid                    ;
    dest.InVoiceNo_               = src.InVoiceNo              ;
    dest.OrderNoVSE_              = src.OrderNoVSE             ;
    dest.OrderNoKSC_              = src.OrderNoKSC             ;
    dest.DateInVoice_             = nDate(src.DateInVoice)     ;
    dest.TimeInVoice_             = src.TimeInVoice            ;
    dest.InVoiceVolume_           = src.InVoiceVolume          ;
    dest.Volume1_                 = src.Volume1                ;
    dest.Volume2_                 = src.Volume2                ;
    dest.Volume3_                 = src.Volume3                ;
    dest.Volume4_                 = src.Volume4                ;
    dest.CustomerNo_              = src.CustomerNo             ;
    dest.VolumeState_             = src.VolumeState            ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxDealerVolume :: Init()
{
    tDEALERVOLUME    record;
    memset(&record, 0 , sizeof(tDEALERVOLUME));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDEALERVOLUME struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxDealerVolume&
pxDealerVolume :: operator=( const pxDealerVolume& src)
{
    tDEALERVOLUME record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDEALERVOLUME structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxDealerVolume&
pxDealerVolume :: operator=( const tDEALERVOLUME& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxDealerVolume list objects being inserted in the                */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo                                                      */
/*----------------------------------------------------------------------------*/
int
pxDealerVolume :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxDealerVolume *that = (pxDealerVolume*)That;
    int retval = (Uid_ == that->Uid_) ? 0
                : (Uid_ > Uid_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDealerVolumeList :: pxDealerVolumeList
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
pxDealerVolumeList :: Select
(
    const int     count_
)
{
    tDEALERVOLUME fil;
    memset(&fil, 0, sizeof(tDEALERVOLUME));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via ArticleNo                       */
/*----------------------------------------------------------------------------*/
size_t
pxDealerVolumeList :: Select
(
    const short   BranchNo,
    const long    Uid,
    const int     count_
)
{
    tDEALERVOLUME fil;
    memset(&fil, 0, sizeof(tDEALERVOLUME));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.Uid        = Uid;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxDealerVolumeList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxDealerVolume' object:
    pxDealerVolume *objectp = new pxDealerVolume(Session(), *(tDEALERVOLUME*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxDealerVolume :: Get
(
    DBAccessMode mode
)

{
    tDEALERVOLUME record;
    memset(&record, 0, sizeof(tDEALERVOLUME));
    record.BranchNo     = BranchNo_;
    record.Uid          = Uid_;
    record.DateInVoice  = DateInVoice_.GetYYYYMMDD();
    record.InVoiceNo    = InVoiceNo_;
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
pxDealerVolume :: Put
(
)
{
    tDEALERVOLUME record;
    memset(&record, 0, sizeof(tDEALERVOLUME));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tDEALERVOLUME));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxDealerVolume :: Delete
(
)
{
    tDEALERVOLUME record;
    memset(&record, 0, sizeof(tDEALERVOLUME));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxDealerVolume :: Read
(
    const void  *record
)
{
    return pxDealerVolumeRead((tDEALERVOLUME*)record);
}

int
pxDealerVolume :: ReadLock
(
    const void  *record
)
{
    return pxDealerVolumeReadLock((tDEALERVOLUME*)record);
}

int
pxDealerVolume :: Update
(
    const void  *record
)
{
    return pxDealerVolumeUpdate((tDEALERVOLUME*)record);
}

int
pxDealerVolume :: Delete
(
    const void  *record
)
{
    return pxDealerVolumeDelete((tDEALERVOLUME*)record);
}

int
pxDealerVolume :: Insert
(
    const void  *record
)
{
    return pxDealerVolumeInsert((tDEALERVOLUME*)record);
}

int
pxDealerVolumeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxDealerVolumeEndBrowse(cursorid);
}


int
pxDealerVolumeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxDealerVolumeGetNext((tDEALERVOLUME*)record, cursorid);
}

int
pxDealerVolumeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxDealerVolumeStartBrowse((tDEALERVOLUME*)keys, cursorid);
}
