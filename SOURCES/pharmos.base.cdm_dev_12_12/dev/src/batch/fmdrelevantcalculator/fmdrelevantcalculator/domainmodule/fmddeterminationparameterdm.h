#ifndef GUARD_DOMMOD_FMDDETERMINATIONPARAMETER_FMDDETERMINATIONPARAMETERDM_H
#define GUARD_DOMMOD_FMDDETERMINATIONPARAMETER_FMDDETERMINATIONPARAMETERDM_H

//-----------------------------------------------------------------------------------------

#include "ifmddeterminationparameterdm.h"
#include <libutil/accessor.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace fmdrelevantcalculator {
namespace domMod {
namespace fmddeterminationparameter {

//-----------------------------------------------------------------------------------------

class FmdDeterminationParameterDM : public IFmdDeterminationParameterDM
{
public:
	FmdDeterminationParameterDM(const log4cplus::Logger& logger);
	~FmdDeterminationParameterDM();

	virtual void												injectAccessor		( libutil::infrastructure::accessor::IAccessorPtr );
	
	virtual void                                                find				( );
	virtual basar::db::aspect::AccessorPropertyTableRef         get();	

private:
	FmdDeterminationParameterDM( const FmdDeterminationParameterDM & );
	FmdDeterminationParameterDM & operator = ( const FmdDeterminationParameterDM & );

	const log4cplus::Logger&									getLogger() const;
	libutil::infrastructure::accessor::IAccessorPtr             getAccessor() const;
	
	const log4cplus::Logger&									m_Logger;
	libutil::infrastructure::accessor::IAccessorPtr             m_Accessor;
};

//-----------------------------------------------------------------------------------------

} 
} 
} 

//-----------------------------------------------------------------------------------------

#endif // GUARD_DOMMOD_FMDDETERMINATIONPARAMETER_FMDDETERMINATIONPARAMETERDM_H

//-----------------------------------------------------------------------------------------

