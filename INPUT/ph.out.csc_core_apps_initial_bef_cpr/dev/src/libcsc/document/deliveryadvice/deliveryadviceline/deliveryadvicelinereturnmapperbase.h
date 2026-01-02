#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINERETURNMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINERETURNMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "deliveryadvicelinereturnptr.h"


namespace libcsc {
namespace document {

class DeliveryAdviceLineReturnMapperBase
{
public:
	DeliveryAdviceLineReturnMapperBase(DeliveryAdviceLineReturnPtr deliveryAdviceLineReturn);

	void			map();
protected:
	virtual ~DeliveryAdviceLineReturnMapperBase();

	virtual void	doMap() = 0;

	void			setBranchNo( const basar::Int16 branchNo );
	void			setCustomerNo( const basar::Int32 customerNo );
	void			setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate );
	void			setDeliveryAdviceNo( const basar::VarString& deliveryAdviceNo);
	void			setDeliveryAdvicePosNo( const basar::Int32 deliveryAdvicePosNo);

	void			setBlockedForreturns( const basar::Int16 blockedForreturns);
	void			setQuantityReturned(const basar::Int32  quantityReturned);
	void			setQuantityReturnedRebateInKind( const basar::Int32 quantityReturnedRebateInKind);
	void			setQuantityReturnRejected( const basar::Int32 quantityReturnRejected);

//private:
	DeliveryAdviceLineReturnPtr m_DeliveryAdviceLineReturn;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINERETURNMAPPER_BASE_H
