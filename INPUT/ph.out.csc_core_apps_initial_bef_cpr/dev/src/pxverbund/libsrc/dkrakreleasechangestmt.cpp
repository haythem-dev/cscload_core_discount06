#include "dkrakreleasechangestmt.hpp"

#include <string.hpp>
#include <date.hpp>
#include <nntypes.h>

#include "pxtcarecord.h"
#include "pxtcadef.h"

DKRAKReleaseChangeStmt::DKRAKReleaseChangeStmt()
{
	CopyToBuf( VK52->line.RecordType, nString(cTCA_CHANGE_DKRAK), mSIZEOF(tCVI522_RECORD, RecordType) );
}

DKRAKReleaseChangeStmt::~DKRAKReleaseChangeStmt()
{
}

void DKRAKReleaseChangeStmt::SetDateTo(const nDate& date)
{
	CopyToBuf( VK52->line.DateTo, date.GetYYYYMMDD() - cTCA_CENTURY_DEF, mSIZEOF(tCVI522_RECORD, DateTo) );
}

void DKRAKReleaseChangeStmt::SetRabateChainEnabled( bool chainEnabled )
{
	VK52->line.Chain = chainEnabled ? 'J' : 'N';
}
