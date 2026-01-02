#include "tenderdiscountmapperbase.h"
#include <discount/tender/tenderdiscount.h>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace discount
{
TenderDiscountMapperBase::TenderDiscountMapperBase( TenderDiscountPtr tenderDiscount )
: m_TenderDiscount( tenderDiscount )
{
}

TenderDiscountMapperBase::~TenderDiscountMapperBase()
{
}

void TenderDiscountMapperBase::map()
{
	doMap();

	std::stringstream ss;
	ss << "TenderDiscountMapperBase::map(), m_TenderDiscount:" << *m_TenderDiscount << std::endl;
	BLOG_TRACE( LoggerPool::getLoggerTenderDiscount(), ss.str().c_str() );
}

void TenderDiscountMapperBase::setTenderNo( const basar::Int32 tenderNo )
{
	m_TenderDiscount->m_TenderNo = tenderNo;
	m_TenderDiscount->m_TenderNo.setClean();

}

void TenderDiscountMapperBase::setDiscountPercent( const basar::Decimal & discountPercent )
{
	m_TenderDiscount->m_DiscountPercent = discountPercent;
	m_TenderDiscount->m_DiscountPercent.setClean();
}

void TenderDiscountMapperBase::setPharmacyGroupId( const basar::VarString & pharmacyGrpID )
{
    m_TenderDiscount->m_PharmacyGroupId = pharmacyGrpID;
    m_TenderDiscount->m_PharmacyGroupId.setClean();
}

void TenderDiscountMapperBase::setContractNo( const basar::VarString & contractNo )
{
    m_TenderDiscount->m_ContractNo = contractNo;
    m_TenderDiscount->m_ContractNo.setClean();
}

void TenderDiscountMapperBase::setAvailableQuantity( const basar::Int32 availableQty )
{
    m_TenderDiscount->m_AvailableQuantity = availableQty;
    m_TenderDiscount->m_AvailableQuantity.setClean();
}

void TenderDiscountMapperBase::setFromDate( const basar::Date & fromdate )
{
    m_TenderDiscount->m_FromDate = fromdate;
    m_TenderDiscount->m_FromDate.setClean();
}

void TenderDiscountMapperBase::setToDate( const basar::Date & todate )
{
    m_TenderDiscount->m_ToDate = todate;
    m_TenderDiscount->m_ToDate.setClean();
}

void TenderDiscountMapperBase::setContractQuantity( const basar::Int32 contractQty )
{
    m_TenderDiscount->m_ContractQuantity = contractQty;
    m_TenderDiscount->m_ContractQuantity.setClean();
}

void TenderDiscountMapperBase::setArticleNumber( const basar::Int32 articleNo )
{
    m_TenderDiscount->m_ArticleNumber = articleNo;
    m_TenderDiscount->m_ArticleNumber.setClean();
}

void TenderDiscountMapperBase::setBranchNumber( const basar::Int16 branchNo )
{
    m_TenderDiscount->m_BranchNumber = branchNo;
    m_TenderDiscount->m_BranchNumber.setClean();
}

void TenderDiscountMapperBase::setRecallFlag( const bool recallFlag )
{
    m_TenderDiscount->m_RecallFlag = recallFlag;
    m_TenderDiscount->m_RecallFlag.setClean();
}

void TenderDiscountMapperBase::setTenderState( const basar::Int16 tenderState )
{
    m_TenderDiscount->m_TenderState = tenderState;
    m_TenderDiscount->m_TenderState.setClean();
}

void TenderDiscountMapperBase::setDiscountCalcFrom( const basar::Int16 discountCalcFrom )
{
    m_TenderDiscount->m_DiscountCalcFrom = discountCalcFrom;
    m_TenderDiscount->m_DiscountCalcFrom.setClean();
}

void TenderDiscountMapperBase::setDiscountApplyTo( const basar::Int16 discountApplyTo )
{
    m_TenderDiscount->m_DiscountApplyTo = discountApplyTo;
    m_TenderDiscount->m_DiscountApplyTo.setClean();
}


} // end namespace discount
} // end namespace libcsc

