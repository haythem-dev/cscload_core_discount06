#include "ibtrelevantparameterdm.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include <libutil/misc/log_macro_definitions.h>      // libutil
#include <loggerpool/ibtrelevantcalculator_loggerpool.h>
#include "domainmodule/ibtrelevantcalculator_property_definitions.h"
#include "infrastructure/accessor/ibtexcludeparameteracc_definitions.h"

#include <libutil/domainmodule.h>
#include <libutil/exception.h>

//-----------------------------------------------------------------------------------------

namespace ibtrelevantcalculator {
namespace domMod {
namespace ibtRelevantParameter {

//-----------------------------------------------------------------------------------------
	
IbtRelevantParameterDM::IbtRelevantParameterDM(const log4cplus::Logger& logger) :
	m_Logger(logger), m_BranchNo(0)
{

}

IbtRelevantParameterDM::~IbtRelevantParameterDM()
{
	
}

void IbtRelevantParameterDM::injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor)
{
	m_Accessor = accessor;
}

basar::db::aspect::AccessorPropertyTable_YIterator IbtRelevantParameterDM::createSearchIterator()
{
	basar::VarString defParam;
	defParam.format("%s=%d;", properties::BRANCH_NO.getName().c_str(), m_BranchNo );

	return basar::db::aspect::Manager::getInstance().createAccessorYIterator(basar::cmnutil::ParameterList(defParam));
}

void IbtRelevantParameterDM::find(  )
{
	METHODNAME_DEF( IbtRelevantParameterDM, find )
    BLOG_TRACE_METHOD( m_Logger, fun );

    using ibtrelevantcalculator::infrastructure::accessor::ibtexcludeparameter::lit::SELECT_IBT_EXCLUDE_PARAM_BY_BRANCH;

	basar::db::aspect::ExecuteResultInfo executeResultInfo;
    try
    {
        executeResultInfo = m_Accessor->execute( SELECT_IBT_EXCLUDE_PARAM_BY_BRANCH, createSearchIterator() );
    }
    catch( basar::Exception & e  )
    {
        libutil::exceptions::ExceptionHandler::processAccessorException( e, m_Logger, fun, SELECT_IBT_EXCLUDE_PARAM_BY_BRANCH, __FILE__, __LINE__ );
        throw;
    }

    if( executeResultInfo.hasError() )
    {
        THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_IBT_EXCLUDE_PARAM_BY_BRANCH, executeResultInfo )
    }
}

libutil::infrastructure::accessor::IAccessorPtr IbtRelevantParameterDM::getAccessor() const
{
    CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
    return m_Accessor;
}

basar::db::aspect::AccessorPropertyTableRef IbtRelevantParameterDM::get()
{
	METHODNAME_DEF( CustomerCollectionDM, get )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return getAccessor()->getPropertyTable();
}

void IbtRelevantParameterDM::setBranchNo(const basar::Int16 branchNo)
{
	m_BranchNo = branchNo;
}

const log4cplus::Logger& IbtRelevantParameterDM::getLogger() const
{
	return m_Logger;
}

basar::Int16		IbtRelevantParameterDM::getBranchNo			( )
{
	return m_BranchNo;
}

//-----------------------------------------------------------------------------------------
} 
} 
} 
