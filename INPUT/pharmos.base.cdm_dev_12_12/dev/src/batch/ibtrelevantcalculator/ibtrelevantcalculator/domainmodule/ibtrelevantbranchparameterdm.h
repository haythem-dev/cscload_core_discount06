#ifndef GUARD_DOMMOD_IBTRELEVANTBRANCHPARAMETER_IBTRELEVANTBRANCHPARAMETERDM_H
#define GUARD_DOMMOD_IBTRELEVANTBRANCHPARAMETER_IBTRELEVANTBRANCHPARAMETERDM_H

//-----------------------------------------------------------------------------------------

#include "iibtrelevantbranchparameterdm.h"
#include <libutil/accessor.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace ibtrelevantcalculator {
namespace domMod {
namespace ibtRelevantBranchParameter {

//-----------------------------------------------------------------------------------------

class IbtRelevantBranchParameterDM : public IIbtRelevantBranchParameterDM
{
public:
	IbtRelevantBranchParameterDM(const log4cplus::Logger& logger);
	~IbtRelevantBranchParameterDM();

	virtual void												injectAccessor		( libutil::infrastructure::accessor::IAccessorPtr );
	
	virtual void                                                find				( );
	virtual basar::db::aspect::AccessorPropertyTableRef         get();
	
	virtual void												setBranchNo			( const basar::Int16 branchNo );
	virtual basar::Int16										getBranchNo			( );

private:
	IbtRelevantBranchParameterDM( const IbtRelevantBranchParameterDM & );
	IbtRelevantBranchParameterDM & operator = ( const IbtRelevantBranchParameterDM & );

	const log4cplus::Logger&									getLogger() const;
	libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
	basar::db::aspect::AccessorPropertyTable_YIterator			createSearchIterator();

	const log4cplus::Logger&									m_Logger;
	basar::Int16												m_BranchNo;
	libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
};

//-----------------------------------------------------------------------------------------

} 
} 
} 

//-----------------------------------------------------------------------------------------

#endif // GUARD_DOMMOD_IBTRELEVANTBRANCHPARAMETER_IBTRELEVANTBRANCHPARAMETERDM_H

//-----------------------------------------------------------------------------------------

