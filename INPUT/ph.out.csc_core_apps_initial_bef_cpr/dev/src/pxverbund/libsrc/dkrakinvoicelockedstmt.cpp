#include "dkrakinvoicelockedstmt.hpp"

#include <string.hpp>
#include <date.hpp>
#include <nntypes.h>

#include "pxtcarecord.h"
#include "pxtcadef.h"

DKRAKInvoiceLockedStmt::DKRAKInvoiceLockedStmt()
{
	CopyToBuf( VK52->line.RecordType, nString(cTCA_VERIFYCODE_DKRAK), mSIZEOF(tCVI522_RECORD, RecordType) );
}

DKRAKInvoiceLockedStmt::~DKRAKInvoiceLockedStmt()
{
}

void DKRAKInvoiceLockedStmt::SetInvoiceNo( const nString& invoiceNo )
{
	CopyToBuf( VK52->line.DocumentNo, invoiceNo, mSIZEOF(tCVI522_RECORD, DocumentNo) );
}

void DKRAKInvoiceLockedStmt::SetManufacturerNo( long manufacturerNo )
{
	CopyToBuf( VK52->line.LFDNr, manufacturerNo, mSIZEOF(tCVI522_RECORD, LFDNr) );
}

void DKRAKInvoiceLockedStmt::SetRabateChainEnabled( bool chainEnabled )
{
	VK52->line.Chain = chainEnabled ? 'J' : 'N';
}

void DKRAKInvoiceLockedStmt::SetDocumentType( const nString& documentType )
{
	CopyToBuf( VK52->line.DocumentType, documentType, mSIZEOF(tCVI522_RECORD, DocumentType) );
}

void DKRAKInvoiceLockedStmt::SetLockCount( long lockCount )
{
	CopyToBuf( VK52->line.LockCount, lockCount, mSIZEOF(tCVI522_RECORD, LockCount) );
}

void DKRAKInvoiceLockedStmt::SetAvailability( bool available )
{
	VK52->line.NVH = available ? 'J' : 'N';
}

void DKRAKInvoiceLockedStmt::SetOrderNo( long orderNo )
{
	DKRAKStatement::SetOrderNo( orderNo );
	CopyToBuf( VK52->line.SplittOrderNo, orderNo, mSIZEOF(tCVI522_RECORD, SplittOrderNo) );
}
