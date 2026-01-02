#include "fmddeterminationparameterdm.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include <libutil/misc/log_macro_definitions.h>      // libutil
#include <loggerpool/fmdrelevantcalculator_loggerpool.h>
#include "domainmodule/fmdrelevantcalculator_property_definitions.h"
#include "infrastructure/accessor/fmddeterminationparameteracc_definitions.h"

#include <libutil/domainmodule.h>
#include <libutil/exception.h>

//-----------------------------------------------------------------------------------------

namespace fmdrelevantcalculator {
namespace domMod {
namespace fmddeterminationparameter {

//-----------------------------------------------------------------------------------------
	
FmdDeterminationParameterDM::FmdDeterminationParameterDM(const log4cplus::Logger& logger) :
	m_Logger(logger)
{

}

FmdDeterminationParameterDM::~FmdDeterminationParameterDM()
{
	
}

void FmdDeterminationParameterDM::injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor)
{
	m_Accessor = accessor;
}

void FmdDeterminationParameterDM::find(  )
{
	METHODNAME_DEF( IbtRelevantParameterDM, find )
    BLOG_TRACE_METHOD( m_Logger, fun );

	using fmdrelevantcalculator::infrastructure::accessor::fmddeterminationparameter::lit::SELECT_FMD_DETERMINATION_PARAM;

	basar::db::aspect::ExecuteResultInfo executeResultInfo;
    try
    {
		executeResultInfo = m_Accessor->execute(SELECT_FMD_DETERMINATION_PARAM );
    }
    catch( basar::Exception & e  )
    {
        libutil::exceptions::ExceptionHandler::processAccessorException( e, m_Logger, fun, SELECT_FMD_DETERMINATION_PARAM, __FILE__, __LINE__ );
        throw;
    }

    if( executeResultInfo.hasError() )
    {
        THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_FMD_DETERMINATION_PARAM, executeResultInfo )
    }
}

libutil::infrastructure::accessor::IAccessorPtr FmdDeterminationParameterDM::getAccessor() const
{
    CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
    return m_Accessor;
}

basar::db::aspect::AccessorPropertyTableRef FmdDeterminationParameterDM::get()
{
	METHODNAME_DEF( CustomerCollectionDM, get )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return getAccessor()->getPropertyTable();
}

const log4cplus::Logger& FmdDeterminationParameterDM::getLogger() const
{
	return m_Logger;
}

//-----------------------------------------------------------------------------------------
} 
} 
} 
