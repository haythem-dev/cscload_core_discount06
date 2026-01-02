#include "dkraklockstmt.hpp"

#include <string.hpp>
#include <date.hpp>
#include <nntypes.h>

#include "pxtcarecord.h"
#include "pxtcadef.h"

DKRAKLockStmt::DKRAKLockStmt()
{
	CopyToBuf( VK52->line.Program,    nString(cTCA_PROGRAM_DKRAK),  mSIZEOF(tCVI522_RECORD, Program)    );
	CopyToBuf( VK52->line.RecordType, nString(cTCA_LOCKCODE_DKRAK), mSIZEOF(tCVI522_RECORD, RecordType) );
}

DKRAKLockStmt::~DKRAKLockStmt()
{
}

void DKRAKLockStmt::SetDateTo( const nDate& date )
{
	CopyToBuf( VK52->line.DateTo, date.GetYYYYMMDD() - cTCA_CENTURY_DEF, mSIZEOF(tCVI522_RECORD, DateTo) );
}

void DKRAKLockStmt::SetOrderNo( long orderNo )
{
	DKRAKStatement::SetOrderNo( orderNo );
	CopyToBuf( VK52->line.SplittOrderNo, orderNo, mSIZEOF(tCVI522_RECORD, SplittOrderNo) );
}

void DKRAKLockStmt::SetRabateChainEnabled( bool chainEnabled )
{
	VK52->line.Chain = chainEnabled ? 'J' : 'N';
}
