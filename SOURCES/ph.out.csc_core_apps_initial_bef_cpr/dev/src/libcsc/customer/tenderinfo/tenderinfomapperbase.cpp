#include <customer/tenderinfo/tenderinfomapperbase.h>
#include <customer/tenderinfo/tenderinfo.h>

namespace libcsc {
namespace customer {

TenderInfoMapperBase::TenderInfoMapperBase(TenderInfoPtr tenderInfo)
: m_TenderInfo(tenderInfo)
{
}

TenderInfoMapperBase::~TenderInfoMapperBase()
{
}

void TenderInfoMapperBase::map()
{
    doMap();
}

void TenderInfoMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_TenderInfo->m_BranchNo = branchNo;
	m_TenderInfo->m_BranchNo.setClean();
}

void TenderInfoMapperBase::setCustomerNo(const basar::Int32 customerNo)
{
	m_TenderInfo->m_CustomerNo = customerNo;
	m_TenderInfo->m_CustomerNo.setClean();
}

void TenderInfoMapperBase::setTenderNo(const basar::Int32 tenderNo)
{
	m_TenderInfo->m_TenderNo = tenderNo;
	m_TenderInfo->m_TenderNo.setClean();
}

void TenderInfoMapperBase::setContractNo(const basar::VarString& contractNo)
{
	m_TenderInfo->m_ContractNo = contractNo;
	m_TenderInfo->m_ContractNo.setClean();
}

void TenderInfoMapperBase::setValidFromDate(const basar::Date& validFromDate)
{
	m_TenderInfo->m_ValidFromDate = validFromDate;
	m_TenderInfo->m_ValidFromDate.setClean();
}

void TenderInfoMapperBase::setValidToDate(const basar::Date& validToDate)
{
	m_TenderInfo->m_ValidToDate = validToDate;
	m_TenderInfo->m_ValidToDate.setClean();
}

void TenderInfoMapperBase::setChainNo(const basar::Int32 chainNo)
{
	m_TenderInfo->m_ChainNo = chainNo;
	m_TenderInfo->m_ChainNo.setClean();
}

void TenderInfoMapperBase::setArticleNo(const basar::Int32 articleNo)
{
	m_TenderInfo->m_ArticleNo = articleNo;
	m_TenderInfo->m_ArticleNo.setClean();
}

void TenderInfoMapperBase::setTenderQuantity(const basar::Int32 tenderQuantity)
{
	m_TenderInfo->m_TenderQuantity = tenderQuantity;
	m_TenderInfo->m_TenderQuantity.setClean();
}

void TenderInfoMapperBase::setFreeTenderQuantity(const basar::Int32 freeTenderQuantity)
{
	m_TenderInfo->m_FreeTenderQuantity = freeTenderQuantity;
	m_TenderInfo->m_FreeTenderQuantity.setClean();
}

void TenderInfoMapperBase::setDeliveredTenderQuantity(const basar::Int32 deliveredTenderQuantity)
{
	m_TenderInfo->m_DeliveredTenderQuantity = deliveredTenderQuantity;
	m_TenderInfo->m_DeliveredTenderQuantity.setClean();
}

void TenderInfoMapperBase::setReturnedTenderQuantity(const basar::Int32 returnedTenderQuantity)
{
	m_TenderInfo->m_ReturnedTenderQuantity = returnedTenderQuantity;
	m_TenderInfo->m_ReturnedTenderQuantity.setClean();
}


} // end namespace customer
} // end namespace libcsc

