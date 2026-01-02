#include "tendermapperbase.h"
#include <tender/tender.h>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace tender
{
TenderMapperBase::TenderMapperBase( TenderPtr tenderDiscount )
: m_Tender( tenderDiscount )
{
}

TenderMapperBase::~TenderMapperBase()
{
}

void TenderMapperBase::map()
{
    doMap();

    std::stringstream ss;
    ss << "TenderMapperBase::map(), m_Tender:" << *m_Tender << std::endl;
    BLOG_TRACE( LoggerPool::getLoggerTenderDiscount(), ss.str().c_str() );
}

void TenderMapperBase::setTenderNo( const basar::Int32 tenderNo )
{
	m_Tender->m_TenderNo = tenderNo;
	m_Tender->m_TenderNo.setClean();
}

void TenderMapperBase::setTenderState( const basar::Int16 tenderState )
{
	m_Tender->m_TenderState = tenderState;
	m_Tender->m_TenderState.setClean();
}

void TenderMapperBase::setRemainingQuantity( const basar::Int32 & remainingQuantity )
{
	m_Tender->m_RemainingQuantity = remainingQuantity;
	m_Tender->m_RemainingQuantity.setClean();
}

void TenderMapperBase::setPharmacyGroupId( const basar::VarString & pharmacyGroupId )
{
    m_Tender->m_PharmacyGroupId = pharmacyGroupId;
    m_Tender->m_PharmacyGroupId.setClean();
}

void TenderMapperBase::setFromDate( const basar::Date & fromDate )
{
	m_Tender->m_FromDate = fromDate;
	m_Tender->m_FromDate.setClean();
}

void TenderMapperBase::setToDate( const basar::Date & toDate )
{
	m_Tender->m_ToDate = toDate;
	m_Tender->m_ToDate.setClean();
}

void TenderMapperBase::setContractQuantity( const basar::Int32 contractQuantity )
{
	m_Tender->m_ContractQuantity = contractQuantity;
	m_Tender->m_ContractQuantity.setClean();
}

void TenderMapperBase::setArticleNo( const basar::Int32 articleNo )
{
	m_Tender->m_ArticleNo = articleNo;
	m_Tender->m_ArticleNo.setClean();
}

void TenderMapperBase::setContractNo( const basar::VarString & contractNo )
{
	m_Tender->m_ContractNo = contractNo;
	m_Tender->m_ContractNo.setClean();
}

void TenderMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_Tender->m_BranchNo = branchNo;
	m_Tender->m_BranchNo.setClean();
}

void TenderMapperBase::setDiscountPercent( const basar::Decimal & discountPercent )
{
	m_Tender->m_DiscountPercent = discountPercent;
	m_Tender->m_DiscountPercent.setClean();
}

void TenderMapperBase::setRecallFlag( const bool recallFlag )
{
	m_Tender->m_RecallFlag = recallFlag;
	m_Tender->m_RecallFlag.setClean();
}

} // end namespace tender
} // end namespace libcsc

