#ifndef GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_H
#define GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_H

#include <ibt/ibtrequest/discount/iibtrequestdiscount.h>
#include <datatypes/decimal.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <datatypes/propertycollection.h>

namespace libcsc
{
namespace ibt
{
class IbtRequestDiscount : public IIbtRequestDiscount
{
    // because of OR mapping
    friend class IbtRequestDiscountMapperBase;

public:
    IbtRequestDiscount();
    virtual ~IbtRequestDiscount();

	const libcsc::Int32 & getIbtRequestId() const;
	virtual const IbtRequestDiscountType & getDiscountType() const;
	virtual const libcsc::Int16 & getPaymentTargetNo() const;
	virtual const basar::VarString & getPharmacyGroupId() const;
	virtual const basar::Decimal & getDiscountValuePct() const;
	virtual const basar::Decimal & getDiscountValuePctMan() const;
	virtual const basar::Decimal & getFixedPrice() const;

	void setIbtRequestId( const basar::Int32 ibtRequestId );
	virtual void setDiscountType( const IbtRequestDiscountTypeEnum discountType );
	virtual void setPaymentTargetNo( const basar::Int16 paymentTargetNo );
	virtual void setPharmacyGroupId( const basar::VarString & pharmacyGroupId );
	virtual void setDiscountValuePct( const basar::Decimal & discountValuePct );
	virtual void setDiscountValuePctMan( const basar::Decimal & discountValuePctMan );
	virtual void setFixedPrice(const basar::Decimal & fixedprice);

	virtual std::ostream & toStream( std::ostream & strm /* = std::cout */ ) const;

	void setClean();
	bool containsDirty() const;

private:
    IbtRequestDiscount( const IbtRequestDiscount & );
    IbtRequestDiscount & operator=( const IbtRequestDiscount & );

    libcsc::Int32 m_IbtRequestId;
    IbtRequestDiscountType m_DiscountType;
    libcsc::VarString m_PharmacyGroupId;
    libcsc::Int16 m_PaymentTargetNo;
    libcsc::Decimal m_DiscountValuePct;
    libcsc::Decimal m_DiscountValuePctMan;
	libcsc::Decimal m_FixedPrice;
	libcsc::PropertyCollection	m_PropertyCollection;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_H
