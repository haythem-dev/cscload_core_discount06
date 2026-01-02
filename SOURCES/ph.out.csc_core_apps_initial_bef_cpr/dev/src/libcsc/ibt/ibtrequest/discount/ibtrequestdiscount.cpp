#include "ibtrequestdiscount.h"

namespace libcsc
{
namespace ibt
{
IbtRequestDiscount::IbtRequestDiscount()
{
    m_PropertyCollection.add( m_IbtRequestId );
    m_PropertyCollection.add( m_DiscountType );
    m_PropertyCollection.add( m_PharmacyGroupId );
    m_PropertyCollection.add( m_PaymentTargetNo );
    m_PropertyCollection.add( m_DiscountValuePct );
    m_PropertyCollection.add( m_DiscountValuePctMan );
	m_PropertyCollection.add( m_FixedPrice);
}

IbtRequestDiscount::~IbtRequestDiscount()
{
}

const libcsc::Int32 & IbtRequestDiscount::getIbtRequestId() const
{
    return m_IbtRequestId;
}

const IbtRequestDiscountType & IbtRequestDiscount::getDiscountType() const
{
    return m_DiscountType;
}

const libcsc::Int16 & IbtRequestDiscount::getPaymentTargetNo() const
{
    return m_PaymentTargetNo;
}

const basar::VarString & IbtRequestDiscount::getPharmacyGroupId() const
{
    return m_PharmacyGroupId;
}

const basar::Decimal & IbtRequestDiscount::getDiscountValuePct() const
{
    return m_DiscountValuePct;
}

const basar::Decimal & IbtRequestDiscount::getDiscountValuePctMan() const
{
    return m_DiscountValuePctMan;
}

const basar::Decimal & IbtRequestDiscount::getFixedPrice() const
{
	return m_FixedPrice;
}


void IbtRequestDiscount::setIbtRequestId( const basar::Int32 ibtRequestId )
{
    m_IbtRequestId = ibtRequestId;
}

void IbtRequestDiscount::setDiscountType( const IbtRequestDiscountTypeEnum discountType )
{
    m_DiscountType = discountType;
}

void IbtRequestDiscount::setPaymentTargetNo( const basar::Int16 paymentTargetNo )
{
    //if (m_PaymentTargetNo.isUnset()) // PK only set once
    //{
        m_PaymentTargetNo = paymentTargetNo;
    //}
}

void IbtRequestDiscount::setPharmacyGroupId( const basar::VarString & pharmacyGroupId )
{
    m_PharmacyGroupId = pharmacyGroupId;
}

void IbtRequestDiscount::setDiscountValuePct( const basar::Decimal & discountValuePct )
{
    m_DiscountValuePct = discountValuePct;
}

void IbtRequestDiscount::setDiscountValuePctMan( const basar::Decimal & discountValuePctMan )
{
    m_DiscountValuePctMan = discountValuePctMan;
}

void IbtRequestDiscount::setFixedPrice(const basar::Decimal & fixedprice )
{
	m_FixedPrice = fixedprice;
}

std::ostream & IbtRequestDiscount::toStream( std::ostream & strm /* = std::cout */ ) const
{
    strm << "m_IbtRequestId=<" << m_IbtRequestId << ">";
    strm << ", m_DiscountType=<" << m_DiscountType << ">";
    strm << ", m_PharmacyGroupId=<" << m_PharmacyGroupId << ">";
    strm << ", m_PaymentTargetNo=<" << m_PaymentTargetNo << ">";
    strm << ", m_DiscountValuePct=<" << m_DiscountValuePct << ">";
    strm << ", m_DiscountValuePctMan=<" << m_DiscountValuePctMan << ">";
	strm << ", m_FixedPrice=<" << m_FixedPrice << ">";
    return strm;
}

void IbtRequestDiscount::setClean()
{
    m_PropertyCollection.setClean();
}

bool IbtRequestDiscount::containsDirty() const
{
    return m_PropertyCollection.containsDirty();
}

} // namespace ibt
} // namespace libcsc
