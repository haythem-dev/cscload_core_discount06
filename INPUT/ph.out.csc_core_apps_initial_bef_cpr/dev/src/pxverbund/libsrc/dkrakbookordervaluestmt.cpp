#include "dkrakbookordervaluestmt.hpp"

#include <string.hpp>
#include <date.hpp>
#include <nntypes.h>

#include "pxtcarecord.h"
#include "pxtcadef.h"

DKRAKBookOrderValueStmt::DKRAKBookOrderValueStmt()
{
	CopyToBuf( VK52->line.RecordType,  nString(cTCA_UNBOOK_DKRAK),  mSIZEOF(tCVI522_RECORD, RecordType) );
}

DKRAKBookOrderValueStmt::~DKRAKBookOrderValueStmt()
{
}

void DKRAKBookOrderValueStmt::SetDateTo(const nDate& date)
{
	CopyToBuf( VK52->line.DateTo, date.GetYYYYMMDD() - cTCA_CENTURY_DEF, mSIZEOF(tCVI522_RECORD, DateTo) );
}

void DKRAKBookOrderValueStmt::SetRabateChainEnabled( bool chainEnabled )
{
	VK52->line.Chain = chainEnabled ? 'J' : 'N';
}

void DKRAKBookOrderValueStmt::SetSplittOrderNo( long orderNo )
{
	CopyToBuf( VK52->line.SplittOrderNo, orderNo, mSIZEOF(tCVI522_RECORD, SplittOrderNo) );
}

void DKRAKBookOrderValueStmt::SetOrderValueGross( const nMoney& orderValue )
{
	CopyToBuf( VK52->line.MOUM, orderValue, mSIZEOF(tCVI522_RECORD, MOUM)); // brutto
}

void DKRAKBookOrderValueStmt::SetOrderValueNet( const nMoney& orderValue )
{
	CopyToBuf( VK52->line.ERUM, orderValue, mSIZEOF(tCVI522_RECORD, ERUM)); // netto
}
