#ifndef DKRAKUSAGESTMT_H_
#define DKRAKUSAGESTMT_H_

#include "dkrakstatement.hpp"

// forward declaration
class nString;

class DKRAKUsageStmt: public DKRAKStatement
{
public:
	DKRAKUsageStmt();
	~DKRAKUsageStmt();

	void SetRabateChainEnabled( bool chainEnabled );
	void SetInvoiceNo( const nString& invoiceNo );
	void SetManufacturerNo( long manufacturerNo );
	void SetDocumentType( const nString& documentType );

	// overwritten method from base class to set additional information
	void SetOrderNo( long orderNo );
};

#endif /* DKRAKUSAGESTMT_HPP_ */
