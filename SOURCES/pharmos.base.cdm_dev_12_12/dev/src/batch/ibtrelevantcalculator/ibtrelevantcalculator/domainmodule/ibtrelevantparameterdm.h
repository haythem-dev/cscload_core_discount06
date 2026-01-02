#ifndef GUARD_DOMMOD_IBTRELEVANTPARAMETER_IBTRELEVANTPARAMETERDM_H
#define GUARD_DOMMOD_IBTRELEVANTPARAMETER_IBTRELEVANTPARAMETERDM_H

//-----------------------------------------------------------------------------------------

#include "iibtrelevantparameterdm.h"
#include <libutil/accessor.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace ibtrelevantcalculator {
namespace domMod {
namespace ibtRelevantParameter {

//-----------------------------------------------------------------------------------------

class IbtRelevantParameterDM : public IIbtRelevantParameterDM
{
public:
	IbtRelevantParameterDM(const log4cplus::Logger& logger);
	~IbtRelevantParameterDM();

	virtual void												injectAccessor		( libutil::infrastructure::accessor::IAccessorPtr );
	
	virtual void                                                find				( );
	virtual basar::db::aspect::AccessorPropertyTableRef         get();
	
	virtual void												setBranchNo			( const basar::Int16 branchNo );
	virtual basar::Int16										getBranchNo			( );

private:
	IbtRelevantParameterDM( const IbtRelevantParameterDM & );
	IbtRelevantParameterDM & operator = ( const IbtRelevantParameterDM & );

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

#endif // GUARD_DOMMOD_IBTRELEVANTPARAMETER_IBTRELEVANTPARAMETERDM_H

//-----------------------------------------------------------------------------------------

