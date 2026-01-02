#include "tender.h"

namespace libcsc
{
namespace tender
{
Tender::Tender()
{
}

const libcsc::Int32 & Tender::getTenderNo() const
{
	return m_TenderNo;
}

const libcsc::Int16 & Tender::getTenderState() const
{
	return m_TenderState;
}

const libcsc::Int32 & Tender::getRemainingQuantity() const
{
	return m_RemainingQuantity;
}

const libcsc::VarString & Tender::getPharmacyGroupId() const
{
	return m_PharmacyGroupId;
}

const libcsc::Date & Tender::getFromDate() const
{
	return m_FromDate;
}

const libcsc::Date & Tender::getToDate() const
{
	return m_ToDate;
}

const libcsc::Int32 & Tender::getContractQuantity() const
{
	return m_ContractQuantity;
}

const libcsc::Int32 & Tender::getArticleNo() const
{
	return m_ArticleNo;
}

const libcsc::VarString & Tender::getContractNo() const
{
	return m_ContractNo;
}

const libcsc::Int16 & Tender::getBranchNo() const
{
	return m_BranchNo;
}

const libcsc::Decimal & Tender::getDiscountPercent() const
{
	return m_DiscountPercent;
}

const libcsc::Bool & Tender::getRecallFlag() const
{
	return m_RecallFlag;
}

std::ostream & Tender::toStream( std::ostream & strm /*= std::cout*/ ) const
{
    strm << "tenderNo=<" << m_TenderNo << ">";
    strm << ", tenderState=<" << m_TenderState << ">";
    strm << ", remainingQuantity=<" << m_RemainingQuantity << ">";
    strm << ", pharmacyGroupId=<" << m_PharmacyGroupId << ">";
    strm << ", fromDate=<" << m_FromDate << ">";
    strm << ", toDate=<" << m_ToDate << ">";
    strm << ", contractQuantity=<" << m_ContractQuantity << ">";
    strm << ", articleNo=<" << m_ArticleNo << ">";
    strm << ", contractNo=<" << m_ContractNo << ">";
    strm << ", branchNo=<" << m_BranchNo << ">";
    strm << ", discountPercent=<" << m_DiscountPercent << ">";
    strm << ", recallFlag=<" << m_RecallFlag << ">";
    return strm;	
}

} // end namespace tender
} // end namespace libcsc

