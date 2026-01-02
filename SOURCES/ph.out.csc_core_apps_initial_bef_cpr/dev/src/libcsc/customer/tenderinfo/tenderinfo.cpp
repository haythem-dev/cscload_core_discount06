#include <customer/tenderinfo/tenderinfo.h>

namespace libcsc {
namespace customer {

TenderInfo::TenderInfo()
{
}

TenderInfo::~TenderInfo()
{
}

basar::Int16 TenderInfo::getBranchNo() const
{
	return m_BranchNo;
}

basar::Int32 TenderInfo::getCustomerNo() const
{
	return m_CustomerNo;
}

basar::Int32 TenderInfo::getTenderNo() const
{
	return m_TenderNo;
}

const basar::VarString&	TenderInfo::getContractNo() const
{
	return m_ContractNo;
}

const basar::Date& TenderInfo::getValidFromDate() const
{
	return m_ValidFromDate;
}

const basar::Date& TenderInfo::getValidToDate() const
{
	return m_ValidToDate;
}

basar::Int32 TenderInfo::getChainNo() const
{
	return m_ChainNo;
}

basar::Int32 TenderInfo::getArticleNo() const
{
	return m_ArticleNo;
}

basar::Int32 TenderInfo::getTenderQuantity() const
{
	return m_TenderQuantity;
}

basar::Int32 TenderInfo::getFreeTenderQuantity() const
{
	return m_FreeTenderQuantity;
}

basar::Int32 TenderInfo::getDeliveredTenderQuantity() const
{
	return m_DeliveredTenderQuantity;
}

basar::Int32 TenderInfo::getReturnedTenderQuantity() const
{
	return m_ReturnedTenderQuantity;
}


} // end namespace customer
} // end namespace libcsc

