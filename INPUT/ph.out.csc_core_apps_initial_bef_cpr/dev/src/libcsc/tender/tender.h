#ifndef GUARD_LIBCSC_TENDER_H
#define GUARD_LIBCSC_TENDER_H

#include <datatypes/int32.h>
#include <datatypes/int16.h>
#include <datatypes/varstring.h>
#include <datatypes/date.h>
#include <datatypes/decimal.h>
#include <datatypes/boolean.h>
#include <iostream>


namespace libcsc
{
namespace tender
{
class Tender
{
    // because of OR mapping
    friend class TenderMapperBase;

public:
    Tender();

    const libcsc::Int32 & getTenderNo() const;
    const libcsc::Int16 & getTenderState() const;
    const libcsc::Int32 & getRemainingQuantity() const;
    const libcsc::VarString & getPharmacyGroupId() const;
    const libcsc::Date & getFromDate() const;
    const libcsc::Date & getToDate() const;
    const libcsc::Int32 & getContractQuantity() const;
    const libcsc::Int32 & getArticleNo() const;
    const libcsc::VarString & getContractNo() const;
    const libcsc::Int16 & getBranchNo() const;
	const libcsc::Decimal & getDiscountPercent() const;
	const libcsc::Bool & getRecallFlag() const;

    std::ostream & toStream( std::ostream & strm = std::cout ) const;

private:
    libcsc::Int32		m_TenderNo;
    libcsc::Int16		m_TenderState;
    libcsc::Int32		m_RemainingQuantity;
    libcsc::VarString	m_PharmacyGroupId;
    libcsc::Date		m_FromDate;
    libcsc::Date		m_ToDate;
    libcsc::Int32		m_ContractQuantity;
    libcsc::Int32		m_ArticleNo;
    libcsc::VarString	m_ContractNo;
    libcsc::Int16		m_BranchNo;
	libcsc::Decimal		m_DiscountPercent;
	libcsc::Bool		m_RecallFlag;
};

} // end namespace tender
} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::tender::Tender & r )
{
    r.toStream( strm );
    return strm;
}

#endif // GUARD_LIBCSC_TENDER_H
