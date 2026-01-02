#include "pxbranch.hpp"
#include "pxxmit.hpp"
#include "pxoeparm.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstot.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxitem.hpp"
#include "pxsessioninitialization.h"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
pxOrderTransmit::pxOrderTransmit( const pxSessionInitialization& sessioninit )
	: pxSession( sessioninit )
{
	Init();	
}

/*----------------------------------------------------------------------------*/
/*  Construction with specific ini-file                                       */
/*----------------------------------------------------------------------------*/
pxOrderTransmit::pxOrderTransmit(const basar::VarString& IniFileName)
    : pxSession(IniFileName, 0)
{
    Init();                             
	OpenDBConnection();    
}

/*----------------------------------------------------------------------------*/
/*  Construction without specific ini-file                                    */
/*----------------------------------------------------------------------------*/
pxOrderTransmit :: pxOrderTransmit
(
    const short    		 branchNo,
	const basar::VarString& countryCode,
	const basar::VarString& dataSource,
	const ::pxDeviceType deviceType,
	const basar::VarString& deviceName,
	const basar::VarString& messageFileName
)
    : pxSession( branchNo,
	             countryCode,
	             dataSource,
	             deviceType,
	             deviceName,
	             messageFileName)
{
    Init();                             	// Initialize data members
	OpenDBConnection();    
}

/*----------------------------------------------------------------------------*/
/*  Destruction.                                                              */
/*----------------------------------------------------------------------------*/
pxOrderTransmit :: ~pxOrderTransmit()
{
}

/*----------------------------------------------------------------------------*/
/*  Initialize data members.                                                  */
/*----------------------------------------------------------------------------*/
void
pxOrderTransmit :: Init
(
)
{
    Customer_         = NULL;
    ActiveOrders_     = NULL;
    DeferredOrders_   = NULL;
    Order_            = NULL;
    Item_             = NULL;
    CustInfo_         = NULL;
	TransmissionType_ = tFileTransfer;
    CallBack_         = false;
    isOCPOrder        = false;
    TotalTransPos_    = 0;
    ClearError();
    WrongIDFNr_.Clear();
    SetDeliveryDate(0);
}

/*----------------------------------------------------------------------------*/
/*  Free storage, reset data members to initial values.                       */
/*----------------------------------------------------------------------------*/
void
pxOrderTransmit :: Reset
(
)
{
    if (ActiveOrders_)
       delete ActiveOrders_;
    if (DeferredOrders_)
       delete DeferredOrders_;
    if (Customer_)
       delete Customer_;
    WrongIDFNr_.Clear();
    pxGlobalNoDatabaseWrite = false;
    Init();
}

/*----------------------------------------------------------------------------*/

void
pxOrderTransmit :: SetDoubleOrder
(
)
{
	Order_->SetSendOrderDouble();
}

/*----------------------------------------------------------------------------*/

void
pxOrderTransmit :: SetNotCloseOrder
(
)
{
	Order_->SetHoldOrder();
}

/*----------------------------------------------------------------------------*/
/*  Perform error checking after trying to create a new order item.           */
/*  Returns pointer to new item or NULL in case of a fatal error.             */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrderTransmit :: ItemPtr
(
)
{
    if ( Order_ )                       // ensure order is open
    {
       Error() = (Order_->Error());     // copy error object contents
    }
    else                                // cannot enter an item, no order open
    {
       ExternalError(CMsgStream(), CMSG_XMIT_ITEM_REJECT);
       Item_ = NULL;                    // There is no item current
    }
    return Item_;                       // return current item ptr
}

/*----------------------------------------------------------------------------*/
/*  Sets the WrongIDFNr_                                                      */
/*----------------------------------------------------------------------------*/
void pxOrderTransmit :: SetWrongIDFNr
(
 const nString& idfnr
)
{
    WrongIDFNr_ = idfnr;
    WrongIDFNr_.Trim(7, nString::cLEADING, '0');
}

/*----------------------------------------------------------------------------*/
/*  CheckOrderOverDrive: This methode calls an pxOrder function to check      */
/*  the state of an order with odertype OV(Swiss special).                    */
/*----------------------------------------------------------------------------*/
int
pxOrderTransmit :: CheckOrderOverdrive
(
)
{

    if ( Order_ )                       // ensure order is open
    {
       Order_->CheckOverdriveState();
       Error() = (Order_->Error());     // copy order error object contents
    }
    return ErrorState();
}

bool
pxOrderTransmit	:: IsSplitOrderOnTens
(
)
{
	return Order_->Param()->IsSplitOrderOnTens();
}

long
pxOrderTransmit	:: AnzPosZu
(
)
{
	return Order_->Param()->AnzPosZu();
}

bool
pxOrderTransmit	:: IsOrderSplit
(
)
{
	return ( Order_->Param()->IsCustomerOrderSplit() &&
			 Customer_->Flags().IsAuftragSplit());
}

bool
pxOrderTransmit	:: IsOrderConsolidation
(
)
{
	if( !Order_->isMSV3Order() )
	{
		return ( Order_->Param()->IsOrderConsolidation() &&
			Customer_->Flags().IsAuftragZusammen() &&
			Order_->OrderType().IsOrderCons()      &&
			Order_->CommType().IsShipNormal()      &&
			Order_->StockTrans().IsDefaultTransaction() );
	}
	else
	{
		return IsOrderConsolidationMSV3();
	}
}

bool
pxOrderTransmit	:: IsOrderConsolidationMSV3
(
)
{
	return ( Customer_->Flags().IsAuftragZusammen() &&
		Order_->OrderType().IsOrderCons()      &&
		Order_->CommType().IsShipNormal()      &&
		Order_->StockTrans().IsDefaultTransaction() );
}
