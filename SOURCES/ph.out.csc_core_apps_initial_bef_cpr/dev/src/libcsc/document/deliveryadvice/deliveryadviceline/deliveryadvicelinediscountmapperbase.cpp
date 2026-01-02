#include "deliveryadvicelinediscountmapperbase.h"
#include "deliveryadvicelinediscount.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DeliveryAdviceLineDiscountMapperBase::DeliveryAdviceLineDiscountMapperBase( DeliveryAdviceLineDiscountPtr deliveryAdviceLineDiscount ) :
	m_DeliveryAdviceLineDiscount( deliveryAdviceLineDiscount )
{
}

DeliveryAdviceLineDiscountMapperBase::~DeliveryAdviceLineDiscountMapperBase()
{
}

void DeliveryAdviceLineDiscountMapperBase::map()
{
	doMap();
}

void 	DeliveryAdviceLineDiscountMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_DeliveryAdviceLineDiscount->m_BranchNo = branchNo;
	m_DeliveryAdviceLineDiscount->m_BranchNo.setClean();
}

void 	DeliveryAdviceLineDiscountMapperBase::setCustomerNo( const basar::Int32 customerNo )
{
	m_DeliveryAdviceLineDiscount->m_CustomerNo = customerNo;
	m_DeliveryAdviceLineDiscount->m_CustomerNo.setClean();

}

void 	DeliveryAdviceLineDiscountMapperBase::setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate )
{
	m_DeliveryAdviceLineDiscount->m_DeliveryAdviceDate = deliveryAdviceDate;
	m_DeliveryAdviceLineDiscount->m_DeliveryAdviceDate.setClean();

}

void 	DeliveryAdviceLineDiscountMapperBase::setPharmosOrderNo( const basar::Int32 pharmosOrderNo )
{
	m_DeliveryAdviceLineDiscount->m_PharmosOrderNo = pharmosOrderNo;
	m_DeliveryAdviceLineDiscount->m_PharmosOrderNo.setClean();

}

void 	DeliveryAdviceLineDiscountMapperBase::setPharmosOrderPosNo( const basar::Int32 pharmosOrderPosNo )
{
	m_DeliveryAdviceLineDiscount->m_PharmosOrderPosNo = pharmosOrderPosNo;
	m_DeliveryAdviceLineDiscount->m_PharmosOrderPosNo.setClean();

}

	
void 	DeliveryAdviceLineDiscountMapperBase::setDiscountMode( const basar::Int16 discountMode )
{
	m_DeliveryAdviceLineDiscount->m_DiscountMode = discountMode;
	m_DeliveryAdviceLineDiscount->m_DiscountMode.setClean();

}


void 	DeliveryAdviceLineDiscountMapperBase::setDiscountModeName(const basar::VarString & discountModeName)
{
	m_DeliveryAdviceLineDiscount->m_DiscountModeName = discountModeName;
	m_DeliveryAdviceLineDiscount->m_DiscountModeName.setClean();

}

	
void 	DeliveryAdviceLineDiscountMapperBase::setDiscount( const basar::Decimal discount )
{
	m_DeliveryAdviceLineDiscount->m_Discount = discount;
	m_DeliveryAdviceLineDiscount->m_Discount.setClean();

}

void 	DeliveryAdviceLineDiscountMapperBase::setOrigin(const basar::VarString & origin )
{
	m_DeliveryAdviceLineDiscount->m_Origin = origin;
	m_DeliveryAdviceLineDiscount->m_Origin.setClean();

}

void 	DeliveryAdviceLineDiscountMapperBase::setDeleteReason( const basar::Int16 deleteReason )
{
	m_DeliveryAdviceLineDiscount->m_DeleteReason = deleteReason;
	m_DeliveryAdviceLineDiscount->m_DeleteReason.setClean();
}

void 	DeliveryAdviceLineDiscountMapperBase::setDiscountValue( const basar::Decimal discountValue )
{
	m_DeliveryAdviceLineDiscount->m_DiscountValue = discountValue;
	m_DeliveryAdviceLineDiscount->m_DiscountValue.setClean();
}

void 	DeliveryAdviceLineDiscountMapperBase::setDiscountType( const basar::Int16 discountType )
{
	m_DeliveryAdviceLineDiscount->m_DiscountType = discountType;
	m_DeliveryAdviceLineDiscount->m_DiscountType.setClean();
}

void 	DeliveryAdviceLineDiscountMapperBase::setHierarchy( const basar::Int16 hierarchy )
{
	m_DeliveryAdviceLineDiscount->m_Hierarchy = hierarchy;
	m_DeliveryAdviceLineDiscount->m_Hierarchy.setClean();
}

void 	DeliveryAdviceLineDiscountMapperBase::setCalculationBasis(const basar::Int16 calculationBasis)
{
	m_DeliveryAdviceLineDiscount->m_CalculationBasis = calculationBasis;
	m_DeliveryAdviceLineDiscount->m_CalculationBasis.setClean();
}

void 	DeliveryAdviceLineDiscountMapperBase::setKindOfDiscount(const enum KindOfDiscountEnum kindOfDiscount)
{
	m_DeliveryAdviceLineDiscount->m_KindOfDiscount = kindOfDiscount;
}

} // end namespace document
} // end namespace libcsc
