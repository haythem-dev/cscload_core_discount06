#ifndef GUARD_LIBCSC_TENDER_DISCOUNT_MAPPER_BASE_H
#define GUARD_LIBCSC_TENDER_DISCOUNT_MAPPER_BASE_H

#include <discount/tender/tenderdiscountptr.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace discount
{
class TenderDiscountMapperBase
{
public:
	TenderDiscountMapperBase( TenderDiscountPtr tenderDiscount );

	void map();

protected:
	virtual ~TenderDiscountMapperBase();

	virtual void doMap() = 0;

	void setTenderNo( const basar::Int32 tenderNo );
	void setDiscountPercent( const basar::Decimal & discountPercent );
    void setPharmacyGroupId( const basar::VarString & pharmacyGrpID ) ;
    void setContractNo( const basar::VarString & contractNo ) ;
    void setAvailableQuantity( const basar::Int32 availableQty ) ;
    void setFromDate( const basar::Date & fromdate );
    void setToDate( const basar::Date & todate );
    void setContractQuantity( const basar::Int32 contractQty );
    void setArticleNumber( const basar::Int32 articleNo );
    void setBranchNumber( const basar::Int16 branchNo );
	void setRecallFlag( const bool recallFlag );
    void setTenderState( const basar::Int16 tenderState );
    void setDiscountCalcFrom( const basar::Int16 discountCalcFrom );
    void setDiscountApplyTo( const basar::Int16 discountApplyTo );

private:
	TenderDiscountPtr	m_TenderDiscount;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_DISCOUNT_MAPPER_BASE_H
