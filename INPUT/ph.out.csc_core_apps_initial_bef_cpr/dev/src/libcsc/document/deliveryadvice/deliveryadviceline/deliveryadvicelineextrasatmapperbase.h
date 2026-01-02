#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEEXTRASATMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEEXTRASATMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "deliveryadvicelineextrasatptr.h"


namespace libcsc {
namespace document {

class DeliveryAdviceLineExtrasATMapperBase
{
public:
	DeliveryAdviceLineExtrasATMapperBase(DeliveryAdviceLineExtrasATPtr deliveryAdviceLineExtrasAT);

	void			map();
protected:
	virtual ~DeliveryAdviceLineExtrasATMapperBase();

	virtual void	doMap() = 0;

	void			setBranchNo( const basar::Int16 branchNo );
	void			setCustomerNo( const basar::Int32 customerNo );
	void			setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate );
	void			setPharmosOrderNo( const basar::Int32 pharmosOrderNo );
	void			setPharmosOrderPosNo( const basar::Int32 pharmosOrderPosNo );
	void			setDeliveryPosNo( const basar::Int32 deliveryPosNo );

	void			setIsNarcotic( const bool isNarcotic );
	void			setIsRX(const bool isRX);
	void			setIsPsychotropic( const bool isPychotropic );
	void			setIsVeterinary( const bool isVeterinary );
	void			setIsHazardous( const bool isHazardous );
	void			setIsReportable( const bool isReportable);
	void			setIsShortExpiry(const bool isShortExpiry);
//private:
	DeliveryAdviceLineExtrasATPtr m_DeliveryAdviceLineExtrasAT;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEEXTRASATMAPPER_BASE_H
