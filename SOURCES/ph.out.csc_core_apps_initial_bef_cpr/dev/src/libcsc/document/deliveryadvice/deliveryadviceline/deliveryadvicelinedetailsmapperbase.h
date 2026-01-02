#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDETAILSMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDETAILSMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "deliveryadvicelinedetailsptr.h"


namespace libcsc {
namespace document {

class DeliveryAdviceLineDetailsMapperBase
{
public:
	DeliveryAdviceLineDetailsMapperBase(DeliveryAdviceLineDetailsPtr deliveryAdviceLineDetails);

	void			map();
protected:
	virtual ~DeliveryAdviceLineDetailsMapperBase();

	virtual void	doMap() = 0;

	void			setBranchNo( const basar::Int16 branchNo );
	void			setCustomerNo( const basar::Int32 customerNo );
	void			setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate );
	void			setPharmosOrderNo( const basar::Int32 pharmosOrderNo );
	void			setPharmosOrderPosNo( const basar::Int32 pharmosOrderPosNo );
	void			setDeliveryPosNo( const basar::Int32 deliveryPosNo );

	void			setQuantityDelivery( const basar::Int32 quantityDelivery );
	void			setBatch(const basar::VarString & batch);
	void			setExpiryDate( const basar::Date& expiryDate );
	void			setPackageId( const basar::Int32 packageId );
	void			setTrackingId( const basar::VarString & trackingId );
	void			setQuantityLack( const basar::Int32 quantityLack);
	void			setPreCalcBatchChanged(const basar::Int16 preCalcBatchChanged);
//private:
	DeliveryAdviceLineDetailsPtr m_DeliveryAdviceLineDetails;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDETAILSMAPPER_BASE_H
