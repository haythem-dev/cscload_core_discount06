#ifndef GUARD_LIBCSC_IBT_I_IBTREQUESTDISCOUNT_H
#define GUARD_LIBCSC_IBT_I_IBTREQUESTDISCOUNT_H

#include <libbasar_definitions.h>
#include <datatypes/int16.h>
#include <base/istreamable.h>
#include <ibt/ibtrequest/discount/ibtrequestdiscounttypeenum.h>

namespace libcsc
{
namespace ibt
{
class IIbtRequestDiscount : public base::IStreamable
{
public:
	virtual ~IIbtRequestDiscount() {};

	virtual const IbtRequestDiscountType & getDiscountType() const = 0;
	virtual const libcsc::Int16 & getPaymentTargetNo() const = 0;
	virtual const basar::VarString & getPharmacyGroupId() const = 0;
	virtual const basar::Decimal & getDiscountValuePct() const = 0;
	virtual const basar::Decimal & getDiscountValuePctMan() const = 0;
	virtual const basar::Decimal & getFixedPrice() const = 0;

	virtual void setDiscountType( const IbtRequestDiscountTypeEnum discountType ) = 0;
	virtual void setPaymentTargetNo( const basar::Int16 paymentTargetNo ) = 0;
	virtual void setPharmacyGroupId( const basar::VarString & pharmacyGroupId ) = 0;
	virtual void setDiscountValuePct( const basar::Decimal & discountValuePct ) = 0;
	virtual void setDiscountValuePctMan( const basar::Decimal & discountValuePctMan ) = 0;
	virtual void setFixedPrice(const basar::Decimal & fixedprice) = 0;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUESTDISCOUNT_H
