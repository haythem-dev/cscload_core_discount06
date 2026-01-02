#include "tenderdiscount.h"

namespace libcsc
{
namespace discount
{
TenderDiscount::TenderDiscount()
{
}

const libcsc::Int32 & TenderDiscount::getTenderNo() const
{
	return m_TenderNo;
}

const libcsc::Decimal & TenderDiscount::getDiscountPercent() const
{
	return m_DiscountPercent;
}

const libcsc::VarString & TenderDiscount::getPharmacyGroupId() const
{
    return m_PharmacyGroupId;
}
const libcsc::VarString & TenderDiscount::getContractNo() const
{
    return m_ContractNo;
}
const libcsc::Int32 & TenderDiscount::getAvailableQuantity() const
{
    return m_AvailableQuantity;
}

const libcsc::Date & TenderDiscount::getFromDate() const
{
    return m_FromDate;
}

const libcsc::Date & TenderDiscount::getToDate() const
{
    return m_ToDate;
}

const libcsc::Int32 & TenderDiscount::getContractQuantity() const
{
    return m_ContractQuantity;
}

const libcsc::Int32 & TenderDiscount::getArticleNumber() const
{
    return m_ArticleNumber;
}

const libcsc::Int16 & TenderDiscount::getBranchNumber() const
{
    return m_BranchNumber;
}

const libcsc::Bool & TenderDiscount::getRecallFlag() const
{
    return m_RecallFlag;
}

const libcsc::Int16 & TenderDiscount::getTenderState() const
{
	return m_TenderState;
}

const libcsc::Int16 & TenderDiscount::getDiscountCalcFrom() const
{
	return m_DiscountCalcFrom;
}

const libcsc::Int16 & TenderDiscount::getDiscountApplyTo() const
{
	return m_DiscountApplyTo;
}

std::ostream & TenderDiscount::toStream( std::ostream & strm /*= std::cout*/ ) const
{
	strm << "tenderNo=<" << m_TenderNo << ">";
	strm << ", discountPercent=<" << m_DiscountPercent << ">";
    strm << ", pharmacyGroupId=<" << m_PharmacyGroupId << ">";
    strm << ", contractNo=<" << m_ContractNo << ">";
    strm << ", availableQuantity=<" << m_AvailableQuantity << ">";
    strm << ", fromdate=<" << m_FromDate << ">";
    strm << ", todate=<" << m_ToDate << ">";
    strm << ", contractQuantity=<" << m_ContractQuantity << ">";
    strm << ", ArticleNumber=<" << m_ArticleNumber << ">";
    strm << ", BranchNumber=<" << m_BranchNumber << ">";
    strm << ", RecallFlag=<" << m_RecallFlag << ">";
    strm << ", TenderState=<" << m_TenderState << ">";
    strm << ", DiscountCalcFrom=<" << m_DiscountCalcFrom << ">";
    strm << ", DiscountApplyTo=<" << m_DiscountApplyTo << ">";

    return strm;	
}

} // end namespace discount
} // end namespace libcsc

