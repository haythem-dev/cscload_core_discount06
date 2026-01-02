#include "dkrakcanceldeldeliveryorderstmt.hpp"

#include <string.hpp>
#include <date.hpp>
#include <nntypes.h>

#include "pxtcarecord.h"
#include "pxtcadef.h"

DKRAKCancelDelelayedDeliveryOrderStmt::DKRAKCancelDelelayedDeliveryOrderStmt()
{
	CopyToBuf( VK52->line.RecordType,   nString(cTCA_CANCEL_VAORDER_DKRAK),  mSIZEOF(tCVI522_RECORD, RecordType) );
}

DKRAKCancelDelelayedDeliveryOrderStmt::~DKRAKCancelDelelayedDeliveryOrderStmt()
{
}

void DKRAKCancelDelelayedDeliveryOrderStmt::SetDateTo(const nDate& date)
{
	CopyToBuf( VK52->line.DateTo, date.GetYYYYMMDD() - cTCA_CENTURY_DEF, mSIZEOF(tCVI522_RECORD, DateTo) );
}

void DKRAKCancelDelelayedDeliveryOrderStmt::SetRabateChainEnabled( bool chainEnabled )
{
	VK52->line.Chain = chainEnabled ? 'J' : 'N';
}
