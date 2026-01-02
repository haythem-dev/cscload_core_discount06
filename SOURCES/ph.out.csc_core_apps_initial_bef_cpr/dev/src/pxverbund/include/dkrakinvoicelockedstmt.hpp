#ifndef DKRAKINVOICELOCKEDSTMT_HPP_
#define DKRAKINVOICELOCKEDSTMT_HPP_

#include "dkrakstatement.hpp"

class DKRAKInvoiceLockedStmt: public DKRAKStatement
{
public:
	DKRAKInvoiceLockedStmt();
	~DKRAKInvoiceLockedStmt();

	void SetManufacturerNo( long manufacturerNo );
	void SetInvoiceNo( const nString& invoiceNo );
	void SetRabateChainEnabled( bool chainEnabled );
	void SetDocumentType( const nString& documentType );
	void SetLockCount( long lockCount );
	void SetAvailability( bool available );

	// overwritten method from base class to set additional information
	void SetOrderNo( long orderNo );
};

#endif /* DKRAKINVOICELOCKEDSTMT_HPP_ */
