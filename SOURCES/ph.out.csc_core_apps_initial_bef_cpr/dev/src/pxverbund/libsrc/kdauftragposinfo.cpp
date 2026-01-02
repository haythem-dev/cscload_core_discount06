#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxkdauftragposinfo.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxKdauftragposInfo :: pxKdauftragposInfo
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Read constructor                                                          */
/*----------------------------------------------------------------------------*/
pxKdauftragposInfo :: pxKdauftragposInfo
(
    pxSession   *session,
    long		KdAuftragNrL,                // Read via this type
    long		PosNr,
	const nString&	Computer,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_ = KdAuftragNrL;
    PosNr_       = PosNr;
	DBName_      = Computer;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxKdauftragposInfo :: pxKdauftragposInfo
(
    pxKdauftragposInfo& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxKdauftragposInfo :: ~pxKdauftragposInfo()
{
// delete subobjects
}


/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGPOS structure.            */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGPOS&
Assign
(
    tKDAUFTRAGPOS&         dest,
    const pxKdauftragposInfo&  src
)
{
    dest.KdAuftragNr           = src.KdAuftragNr_;
    dest.PosNr                 = src.PosNr_;
    dest.IBTTourWeekDay        = src.IBTTourWeekDay_;
    strcpy(dest.TourIdIBT    ,    " ");
    src.TourIdIBT_.GetData(dest.TourIdIBT);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGPOS structure to a pxArtremote object.*/
/*----------------------------------------------------------------------------*/
pxKdauftragposInfo&
Assign
(
    pxKdauftragposInfo&        dest,
    const tKDAUFTRAGPOS&   src
)
{
	dest.KdAuftragNr_           = src.KdAuftragNr;
    dest.PosNr_                 = src.PosNr;
    dest.TourIdIBT_             = src.TourIdIBT;
    dest.IBTTourWeekDay_        = src.IBTTourWeekDay;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxKdauftragposInfo :: Init()
{
    tKDAUFTRAGPOS    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGPOS));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tKDAUFTRAGPOS struct*/
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxKdauftragposInfo&
pxKdauftragposInfo :: operator=( const pxKdauftragposInfo& src)
{
    tKDAUFTRAGPOS    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPOS structure 'src' to this instance.       */
/*----------------------------------------------------------------------------*/
pxKdauftragposInfo&
pxKdauftragposInfo :: operator=( const tKDAUFTRAGPOS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxKdauftragposInfo :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGPOS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOS));
    record.KdAuftragNr = KdAuftragNr_;
    record.PosNr       = PosNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tKDAUFTRAGPOS struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(), CMSG_ITM_NOTFOUND, KdAuftragNr_, PosNr_, DBName_());
	return retval;
}

/*----------------------------------------------------------------------------*/
/*  Get a record from the data source.                                        */
/*----------------------------------------------------------------------------*/

int
pxKdauftragposInfo :: Read
(
    const void *record
)
{
   if (!(DBName_.IsEmpty()))
   {
      return pxPositionInfoRead((tKDAUFTRAGPOS*)record, DBName_());
   }
   else
   {
      return ExternalCondition(CMsgStream(), CMSG_ITM_NOTFOUND, KdAuftragNr_, PosNr_, DBName_());
   }
}
