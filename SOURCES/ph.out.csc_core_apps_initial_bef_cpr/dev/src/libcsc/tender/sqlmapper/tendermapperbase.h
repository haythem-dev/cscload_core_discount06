#ifndef GUARD_LIBCSC_TENDER_MAPPER_BASE_H
#define GUARD_LIBCSC_TENDER_MAPPER_BASE_H

#include <tender/tenderptr.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace tender
{
class TenderMapperBase
{
public:
	TenderMapperBase( TenderPtr tender );

	void map();

protected:
	virtual ~TenderMapperBase();
    
	virtual void doMap() = 0;
    
	void setTenderNo( const basar::Int32 tenderNo );
	void setTenderState( const basar::Int16 tenderState );
	void setRemainingQuantity( const basar::Int32 & remainingQuantity );
	void setPharmacyGroupId( const basar::VarString & pharmacyGroupId );
	void setFromDate( const basar::Date & fromDate );
	void setToDate( const basar::Date & toDate );
	void setContractQuantity( const basar::Int32 contractQuantity );
	void setArticleNo( const basar::Int32 articleNo );
	void setContractNo( const basar::VarString & contractNo );
	void setBranchNo( const basar::Int16 branchNo );
	void setDiscountPercent( const basar::Decimal & discountPercent );
	void setRecallFlag( const bool recallFlag );

private:
    TenderPtr   m_Tender;
};

} // end namespace tender
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_MAPPER_BASE_H
