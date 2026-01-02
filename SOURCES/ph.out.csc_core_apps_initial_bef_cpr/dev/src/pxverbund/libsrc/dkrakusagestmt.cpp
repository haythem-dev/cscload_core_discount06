#include "dkrakusagestmt.hpp"

#include <string.hpp>
#include <nntypes.h>

#include "pxtcarecord.h"
#include "pxtcadef.h"

DKRAKUsageStmt::DKRAKUsageStmt()
{
	CopyToBuf( VK52->line.Program,    nString(cTCA_PROGRAM_DKRAK), mSIZEOF(tCVI522_RECORD, Program) );
	CopyToBuf( VK52->line.RecordType, nString(cTCA_MODIFY_DKRAK),  mSIZEOF(tCVI522_RECORD, RecordType) );
	VK52->line.Available  = 'N';
}

DKRAKUsageStmt::~DKRAKUsageStmt()
{
}

void DKRAKUsageStmt::SetRabateChainEnabled( bool chainEnabled )
{
	VK52->line.Chain = chainEnabled ? 'J' : 'N';
}

void DKRAKUsageStmt::SetInvoiceNo( const nString& invoiceNo )
{
	CopyToBuf( VK52->line.DocumentNo, invoiceNo, mSIZEOF(tCVI522_RECORD, DocumentNo) );
}

void DKRAKUsageStmt::SetManufacturerNo( long manufacturerNo )
{
	CopyToBuf( VK52->line.LFDNr, manufacturerNo, mSIZEOF(tCVI522_RECORD, LFDNr) );
}

void DKRAKUsageStmt::SetDocumentType( const nString& documentType )
{
	CopyToBuf( VK52->line.DocumentType,  documentType, mSIZEOF(tCVI522_RECORD, DocumentType) );
}

void DKRAKUsageStmt::SetOrderNo( long orderNo )
{
	DKRAKStatement::SetOrderNo( orderNo );
	CopyToBuf( VK52->line.SplittOrderNo, orderNo, mSIZEOF(tCVI522_RECORD, SplittOrderNo) );
}

