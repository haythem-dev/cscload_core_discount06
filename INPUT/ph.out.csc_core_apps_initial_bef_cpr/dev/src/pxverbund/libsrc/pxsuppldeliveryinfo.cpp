
#include "pxsuppldeliveryinfo.hpp"
#include "tsuppldeliveryinfo.h"
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"		// CMSG_ART_NOTFOUND,                  // 33001 article %d not found

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxSupplDeliveryInfo :: pxSupplDeliveryInfo
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
pxSupplDeliveryInfo :: pxSupplDeliveryInfo
(
    const pxSupplDeliveryInfo& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tSUPPLDELIVERYINFO structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxSupplDeliveryInfo :: pxSupplDeliveryInfo
(
    pxSession   *session,
    tSUPPLDELIVERYINFO& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxSupplDeliveryInfo :: pxSupplDeliveryInfo
(
    pxSession    *session,
    long        ArticleNo,              // Articlenumber
    DBAccessMode mode

)
    : pxDBRecord(session)
{
    Init();
    ArticleNo_  = ArticleNo;
    Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxSupplDeliveryInfo :: ~pxSupplDeliveryInfo()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tSUPPLDELIVERYINFO structure.         */
/*----------------------------------------------------------------------------*/
tSUPPLDELIVERYINFO&
Assign
(
    tSUPPLDELIVERYINFO&           dest,
    const pxSupplDeliveryInfo&     src
)
{
	dest.Id						= src.Id_;
	dest.ArticleNo				= src.ArticleNo_;
	dest.AvailabilityInfo[0]	= ' ';
	strncpy(dest.AvailabilityInfo, src.AvailabilityInfo_.c_str(), 254);
	dest.PredictedAvailDate		= src.PredictedAvailDate_.getDate();
	dest.AvailableDate			= src.AvailableDate_.getDate();
	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tSUPPLDELIVERYINFO structure to                   */
/*  a pxSupplDeliveryInfo object.                                                    */
/*----------------------------------------------------------------------------*/
pxSupplDeliveryInfo&
Assign
(
    pxSupplDeliveryInfo&              dest,
    const tSUPPLDELIVERYINFO&         src
)
{
	dest.Id_					= src.Id;
	dest.ArticleNo_				= src.ArticleNo;
	dest.AvailabilityInfo_		= src.AvailabilityInfo;
	dest.PredictedAvailDate_	= src.PredictedAvailDate;
	dest.AvailableDate_			= src.AvailableDate;
	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxSupplDeliveryInfo :: Init()
{
    tSUPPLDELIVERYINFO    record;
    memset(&record, 0 , sizeof(tSUPPLDELIVERYINFO));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tSUPPLDELIVERYINFO struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxSupplDeliveryInfo&
pxSupplDeliveryInfo :: operator=( const pxSupplDeliveryInfo& src)
{
    tSUPPLDELIVERYINFO record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tSUPPLDELIVERYINFO structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxSupplDeliveryInfo&
pxSupplDeliveryInfo :: operator=( const tSUPPLDELIVERYINFO& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxSupplDeliveryInfo :: Get
(
    DBAccessMode mode
)

{
    tSUPPLDELIVERYINFO record;
    memset(&record, 0, sizeof(tSUPPLDELIVERYINFO));
    record.ArticleNo = ArticleNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tSUPPLDELIVERYINFO struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxSupplDeliveryInfo :: Read
(
    const void  *record
)
{
	return pxSupplDeliveryInfoRead((tSUPPLDELIVERYINFO*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxSupplDeliveryInfo list objects being inserted in the            */
/*  following ascending sequence:                                             */
/*  ArticleNo_                                                                */
/*----------------------------------------------------------------------------*/
int
pxSupplDeliveryInfo :: CompareTo
(
    const nCollectable* That,
          void*         /*p*/,
    const long          /*lparm*/
)   const
{
    pxSupplDeliveryInfo *that = (pxSupplDeliveryInfo*)That;
    int retval = (ArticleNo_ == that->ArticleNo_) ? 0
                : (ArticleNo_ > that->ArticleNo_ ? 1 : -1);

    return retval;
}

