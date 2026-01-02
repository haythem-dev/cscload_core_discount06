#include "dkrakreleasestmt.hpp"

#include <string.hpp>
#include <date.hpp>
#include <nntypes.h>

#include "pxtcarecord.h"
#include "pxtcadef.h"

DKRAKReleaseStmt::DKRAKReleaseStmt()
{
	CopyToBuf( VK52->line.RecordType, nString(cTCA_RELEASE_DKRAK),  mSIZEOF(tCVI522_RECORD, RecordType) );
}

DKRAKReleaseStmt::~DKRAKReleaseStmt()
{
}

void DKRAKReleaseStmt::SetDateTo(const nDate& date)
{
	CopyToBuf( VK52->line.DateTo, date.GetYYYYMMDD() - cTCA_CENTURY_DEF, mSIZEOF(tCVI522_RECORD, DateTo) );
}
