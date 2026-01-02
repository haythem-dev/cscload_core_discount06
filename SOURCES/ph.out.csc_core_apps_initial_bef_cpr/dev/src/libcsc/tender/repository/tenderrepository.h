#ifndef GUARD_LIBCSC_TENDER_REPOSITORY_H
#define GUARD_LIBCSC_TENDER_REPOSITORY_H

#include <tender/repository/itenderrepository.h>
//#include <tender/tendercollectionptr.h>
#include <tender/tenderptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <parameter/ibranchparametergetterptr.h>

namespace libcsc
{
namespace tender
{
class TenderRepository : public ITenderRepository
{
public:
	TenderRepository();
	virtual ~TenderRepository();

	void injectAccessor( persistence::IAccessorPtr accessor );
	void injectBranchParameterGetter(libcsc::parameter::IBranchParameterGetterPtr);
	virtual void switchTenderState( const basar::Int32 tenderNo );

private:
	TenderPtr findTender( const basar::Int32 tenderNo ) const;
	TenderPtr findSuccessorTender( const TenderPtr origTender, const basar::Int32 tenderState ) const;
	void activateTender( const TenderPtr tender, const basar::Int32 tenderState );

	mutable persistence::IAccessorPtr				m_Accessor;
	libcsc::parameter::IBranchParameterGetterPtr	m_BranchParameterGetter;
};

} // end namespace tender
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_REPOSITORY_H
