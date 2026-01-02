/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxSubOrderType  methods.

REVISION HISTORY

29  November 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/
#include "pxsubordertype.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxSubOrderType :: pxSubOrderType
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
pxSubOrderType :: pxSubOrderType
(
    pxSubOrderType& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tDISCOUNTLIST structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxSubOrderType :: pxSubOrderType
(
    pxSession   *session,
    tDISCOUNTLIST& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxSubOrderType :: pxSubOrderType
(
    pxSession    *session,
    nString&      OrderType,
    nString&      SubOrderType
)
    : pxDBRecord(session)
{
    Init();
    OrderType_         = OrderType;
    SubOrderType_      = SubOrderType;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxSubOrderType :: ~pxSubOrderType()
{
}

/*----------------------------------------------------------------------------*/
/* Assign the values of the 'src' object to a tDISCOUNTLIST structure         */
/*----------------------------------------------------------------------------*/
tDISCOUNTLIST&
Assign
(
    tDISCOUNTLIST&           dest,
    const pxSubOrderType&       src
)
{
    dest.OrderType[0] = ' ';
    src.OrderType_.GetData(dest.OrderType);
    dest.SubOrderType[0] = ' ';
    src.SubOrderType_.GetData(dest.SubOrderType);
    dest.PharmacyGroupId[0] = ' ';
    src.PharmacyGroupId_.GetData(dest.PharmacyGroupId);
    dest.PaymentTerm[0] = ' ';
    src.PaymentTerm_.GetData(dest.PaymentTerm);
    dest.MonthlyDiscPct    = src.MonthlyDiscPct_;
    dest.ValutaDays        = src.ValutaDays_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDISCOUNTLIST structure to                 */
/*  a pxSubOrderType object.                                                  */
/*----------------------------------------------------------------------------*/
pxSubOrderType&
Assign
(
    pxSubOrderType&              dest,
    const tDISCOUNTLIST&    src
)
{
    dest.OrderType_                = src.OrderType;
    dest.SubOrderType_             = src.SubOrderType;
    dest.PharmacyGroupId_          = src.PharmacyGroupId;
    dest.PaymentTerm_              = src.PaymentTerm;
    dest.MonthlyDiscPct_           = src.MonthlyDiscPct;
    dest.ValutaDays_               = src.ValutaDays;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxSubOrderType :: Init()
{
    tDISCOUNTLIST    record;
    memset(&record, 0 , sizeof(tDISCOUNTLIST));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDISCOUNTLIST struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxSubOrderType&
pxSubOrderType :: operator=( const pxSubOrderType& src)
{
    tDISCOUNTLIST record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISCOUNTLIST structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxSubOrderType&
pxSubOrderType :: operator=( const tDISCOUNTLIST& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxSubOrderType :: Get
(
    DBAccessMode mode
)

{
    tDISCOUNTLIST record;
    memset(&record, 0, sizeof(tDISCOUNTLIST));
    record.OrderType[0] = ' ';
    OrderType_.GetData(record.OrderType);
    record.SubOrderType[0] = ' ';
    SubOrderType_.GetData(record.SubOrderType);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tDISCOUNTLIST struct

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxSubOrderType :: Read
(
    const void  *record
)
{
    return pxSubOrderTypeRead((tDISCOUNTLIST*)record);
}

int
pxSubOrderType :: ReadLock
(
    const void  *record
)
{
    return pxSubOrderTypeReadLock((tDISCOUNTLIST*)record);
}
