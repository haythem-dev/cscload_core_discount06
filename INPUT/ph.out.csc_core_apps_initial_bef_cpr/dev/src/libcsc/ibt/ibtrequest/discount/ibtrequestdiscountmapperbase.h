#ifndef GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_MAPPERBASE_H
#define GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_MAPPERBASE_H

#include <libbasar_definitions.h>
#include <ibt/ibtrequest/discount/ibtrequestdiscountptr.h>
#include <ibt/ibtrequest/discount/ibtrequestdiscounttypeenum.h>

namespace libcsc 
{
namespace ibt
{
class IbtRequestDiscountMapperBase
{
public:
    IbtRequestDiscountMapperBase( IbtRequestDiscountPtr ibtRequestDiscount );

    void map();

protected:
    virtual ~IbtRequestDiscountMapperBase();

    virtual void doMap() = 0;

	void setIbtRequestId( const basar::Int32 ibtRequestId );
	void setDiscountType( const IbtRequestDiscountTypeEnum discountType );
	void setPharmacyGroupId( const basar::VarString & pharmacyGroupId );
	void setPaymentTargetNo( const basar::Int16 paymentTargetNo );
	void setDiscountValuePct( const basar::Decimal & discountValuePct );
	void setDiscountValuePctMan( const basar::Decimal & discountValuePctMan );
	void setFixedPrice(const basar::Decimal & fixedprice);

private:
    IbtRequestDiscountPtr	m_IbtRequestDiscount;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_MAPPERBASE_H
