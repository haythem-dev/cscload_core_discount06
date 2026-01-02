#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDISCOUNTSMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDISCOUNTSMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "deliveryadvicelinediscountptr.h"
#include "types/kindofdiscountenum.inc"


namespace libcsc {
namespace document {

class DeliveryAdviceLineDiscountMapperBase
{
public:
	DeliveryAdviceLineDiscountMapperBase(DeliveryAdviceLineDiscountPtr deliveryAdviceLineDiscount);

	void			map();
protected:
	virtual ~DeliveryAdviceLineDiscountMapperBase();

	virtual void	doMap() = 0;

	void 		setBranchNo( const basar::Int16 branchNo );
	void 		setCustomerNo( const basar::Int32 customerNo );
	void 		setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate );
	void 		setPharmosOrderNo( const basar::Int32 pharmosOrderNo );
	void 		setPharmosOrderPosNo( const basar::Int32 pharmosOrderPosNo);

	void 		setDiscountMode( const basar::Int16 discountMode );
	void 		setDiscountModeName(const basar::VarString & discountModeName);

	void 		setDiscount( const basar::Decimal discount );
	void 		setOrigin(const basar::VarString & origin );
	void 		setDeleteReason( const basar::Int16 deleteReason );
	void 		setDiscountValue( const basar::Decimal discountValue );
	void 		setDiscountType( const basar::Int16 discountType );
	void 		setHierarchy( const basar::Int16 hierarchy );
	void 		setCalculationBasis(const basar::Int16 calculationBasis);
	void 		setKindOfDiscount(const enum KindOfDiscountEnum kindOfDiscount);

//private:
	DeliveryAdviceLineDiscountPtr m_DeliveryAdviceLineDiscount;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEDISCOUNTMAPPER_BASE_H
