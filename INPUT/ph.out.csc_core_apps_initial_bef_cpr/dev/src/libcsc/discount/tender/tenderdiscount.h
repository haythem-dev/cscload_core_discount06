#ifndef GUARD_LIBCSC_TENDER_DISCOUNT_H
#define GUARD_LIBCSC_TENDER_DISCOUNT_H

#include <datatypes/decimal.h>
#include <datatypes/int32.h>
#include <datatypes/int16.h>
#include <datatypes/varstring.h>
#include <datatypes/date.h>
#include <datatypes/boolean.h>
#include <iostream>

namespace libcsc
{
namespace discount
{
class TenderDiscount
{
	// because of OR mapping
	friend class TenderDiscountMapperBase;

public:
	TenderDiscount();

	const libcsc::Int32 & getTenderNo() const;
	const libcsc::Decimal & getDiscountPercent() const;
    const libcsc::VarString & getPharmacyGroupId() const;
    const libcsc::VarString & getContractNo() const;
    const libcsc::Int32 & getAvailableQuantity() const;
    const libcsc::Date & getFromDate() const;
    const libcsc::Date & getToDate() const;
    const libcsc::Int32 & getContractQuantity() const;
    const libcsc::Int32 & getArticleNumber() const;
    const libcsc::Int16 & getBranchNumber() const;
	const libcsc::Bool & getRecallFlag() const;
    const libcsc::Int16 & getTenderState() const;
    const libcsc::Int16 & getDiscountCalcFrom() const;
    const libcsc::Int16 & getDiscountApplyTo() const;

	virtual std::ostream & toStream( std::ostream & strm = std::cout ) const;

private:
	libcsc::Int32					m_TenderNo;
	libcsc::Decimal					m_DiscountPercent;
    libcsc::VarString               m_PharmacyGroupId;
    libcsc::VarString               m_ContractNo;
    libcsc::Int32					m_AvailableQuantity;
    libcsc::Date 					m_FromDate;
    libcsc::Date 					m_ToDate;
    libcsc::Int32					m_ContractQuantity;
    libcsc::Int32					m_ArticleNumber;
    libcsc::Int16					m_BranchNumber;
	libcsc::Bool					m_RecallFlag;
    libcsc::Int16					m_TenderState;
    libcsc::Int16					m_DiscountCalcFrom;
    libcsc::Int16					m_DiscountApplyTo;
};

} // end namespace discount
} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::TenderDiscount & r )
{
	r.toStream( strm );
	return strm;
}

#endif // GUARD_LIBCSC_TENDER_DISCOUNT_H
