#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKS_MAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKS_MAPPER_BASE_H

#include <libbasar_definitions.h>
#include "types/orderremarktypeenum.inc"
#include "deliveryadviceremarksptr.h"


namespace libcsc {
namespace document {

class DeliveryAdviceRemarksMapperBase
{
public:
	DeliveryAdviceRemarksMapperBase(DeliveryAdviceRemarksPtr deliveryAdviceRemarks);

	void			map();
protected:
	virtual ~DeliveryAdviceRemarksMapperBase();

	virtual void	doMap() = 0;

	void	setBranchNo( const basar::Int16 branchNo ) ;
	void	setCustomerNo( const basar::Int32 customerNo );
	void	setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate );
	void	setCSCOrderNo( const basar::Int32 & CSCOrderNo );
	void	setCSCOrderPosNo( const basar::Int32 CSCOrderPosNo );

	void	setRemarkType( const ::OrderRemarkTypeEnum remarkType );
	void	setSerialNo( const basar::Int16 serialNo );

	void	setRemarkText( const basar::VarString & remarkText );

//private:
	DeliveryAdviceRemarksPtr m_DeliveryAdviceRemarks;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REMARKS_MAPPER_BASE_H
