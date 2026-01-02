#ifndef DKRAKPRIORITYSTMT_HPP_
#define DKRAKPRIORITYSTMT_HPP_

#include "dkrakstatement.hpp"

// forward declaration
class nString;

class DKRAKPriorityStmt: public DKRAKStatement
{
public:
	DKRAKPriorityStmt();
	~DKRAKPriorityStmt();

	void SetManufacturerNo( long manufacturerNo );
	void SetInvoiceNo( const nString& invoiceNo );
	void SetRabateChainEnabled( bool chainEnabled );
	void SetPriorityEnabled( bool priorityEnabled );
	void SetDocumentType( const nString& documentType );

	// overwritten method from base class to set additional information
	void SetOrderNo( long orderNo );
};

#endif /* DKRAKPRIORITYSTMT_HPP_ */
