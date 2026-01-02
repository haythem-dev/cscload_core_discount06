#include "dkrakprioritystmt.hpp"

#include <string.hpp>
#include <date.hpp>
#include <nntypes.h>

#include "pxtcarecord.h"
#include "pxtcadef.h"

DKRAKPriorityStmt::DKRAKPriorityStmt()
{
	CopyToBuf( VK52->line.Program,    nString(cTCA_PROGRAM_DKRAK), mSIZEOF(tCVI522_RECORD, Program)    );
	CopyToBuf( VK52->line.RecordType, nString(cTCA_MODIFY_DKRAK),  mSIZEOF(tCVI522_RECORD, RecordType) );
}

DKRAKPriorityStmt::~DKRAKPriorityStmt()
{
}

void DKRAKPriorityStmt::SetInvoiceNo( const nString& invoiceNo )
{
	CopyToBuf( VK52->line.DocumentNo, invoiceNo, mSIZEOF(tCVI522_RECORD, DocumentNo) );
}

void DKRAKPriorityStmt::SetManufacturerNo( long manufacturerNo )
{
	CopyToBuf( VK52->line.LFDNr, manufacturerNo, mSIZEOF(tCVI522_RECORD, LFDNr) );
}

void DKRAKPriorityStmt::SetPriorityEnabled( bool priorityEnabled )
{
	VK52->line.Priority = priorityEnabled ? 'J' : 'N';
}

void DKRAKPriorityStmt::SetRabateChainEnabled( bool chainEnabled )
{
	VK52->line.Chain = chainEnabled ? 'J' : 'N';
}

void DKRAKPriorityStmt::SetDocumentType( const nString& documentType )
{
	CopyToBuf( VK52->line.DocumentType, documentType, mSIZEOF(tCVI522_RECORD, DocumentType) );
}

void DKRAKPriorityStmt::SetOrderNo( long orderNo )
{
	DKRAKStatement::SetOrderNo( orderNo );
	CopyToBuf( VK52->line.SplittOrderNo, orderNo, mSIZEOF(tCVI522_RECORD, SplittOrderNo) );
}
