#ifndef GUARD_ARTICLEACCOUNTINFO_HPP
#define GUARD_ARTICLEACCOUNTINFO_HPP

#include "types/pickingtypeenum.inc"
#include "types/bookingtypeenum.inc"
#include "types/reservationtypeenum.inc"

struct ArticleAccountInfo
{
	short						BranchNo;
	long						ArticleNo;
	long						PurchaseOrderNo;
	long						PositionNo;
	long						CustomerSupplierNo;
	enum BookingTypeEnum		StockTransaction;
	enum PickingTypeEnum		CommiType;
	enum ReservationTypeEnum	MoveType;
	basar::VarString			BelegArt;

	ArticleAccountInfo()
	{
		BranchNo			= 0;
		ArticleNo			= 0;
		PurchaseOrderNo 	= 0;
		PositionNo			= 0;
		CustomerSupplierNo	= 0;
		StockTransaction	= StockDebitAndDemand;	// 0
		CommiType			= ShipNormal;			// 0
		MoveType			= RESTYPE_UNKNOWN;
		BelegArt			= "";
	}
};

#endif // GUARD_ARTICLEACCOUNTINFO_HPP
