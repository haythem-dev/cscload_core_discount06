#include "ibtrelevantbranchparameterdm.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include <libutil/misc/log_macro_definitions.h>      // libutil
#include <loggerpool/ibtrelevantcalculator_loggerpool.h>
#include "domainmodule/ibtrelevantcalculator_property_definitions.h"
#include "infrastructure/accessor/ibtbrancharticlerelevanceacc_definitions.h"

#include <libutil/domainmodule.h>
#include <libutil/exception.h>

//-----------------------------------------------------------------------------------------

namespace ibtrelevantcalculator {
namespace domMod {
namespace ibtRelevantBranchParameter {

//-----------------------------------------------------------------------------------------
	
IbtRelevantBranchParameterDM::IbtRelevantBranchParameterDM(const log4cplus::Logger& logger) :
	m_Logger(logger), m_BranchNo(0)
{
	METHODNAME_DEF( IbtRelevantBranchParameterDM, IbtRelevantBranchParameterDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

IbtRelevantBranchParameterDM::~IbtRelevantBranchParameterDM()
{
	METHODNAME_DEF( IbtRelevantBranchParameterDM, ~IbtRelevantBranchParameterDM )
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void IbtRelevantBranchParameterDM::injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor)
{
	METHODNAME_DEF( IbtRelevantBranchParameterDM, injectAccessor )
    BLOG_TRACE_METHOD( m_Logger, fun );
	
	m_Accessor = accessor;
}

basar::db::aspect::AccessorPropertyTable_YIterator IbtRelevantBranchParameterDM::createSearchIterator()
{
	METHODNAME_DEF( IbtRelevantBranchParameterDM, createSearchIterator )
    BLOG_TRACE_METHOD( m_Logger, fun );
	
	basar::VarString defParam;
	defParam.format("%s=%d;", properties::BRANCH_NO.getName().c_str(), m_BranchNo );

	return basar::db::aspect::Manager::getInstance().createAccessorYIterator(basar::cmnutil::ParameterList(defParam));
}

void IbtRelevantBranchParameterDM::find(  )
{
	METHODNAME_DEF( IbtRelevantBranchParameterDM, find )
    BLOG_TRACE_METHOD( m_Logger, fun );

    using ibtrelevantcalculator::infrastructure::accessor::ibtbrancharticlerelevanceparam::lit::SELECT_IBT_BRANCH_ARTICLE_RELEVANCE_PARAM;

	basar::db::aspect::ExecuteResultInfo executeResultInfo;
    try
    {
        executeResultInfo = m_Accessor->execute( SELECT_IBT_BRANCH_ARTICLE_RELEVANCE_PARAM, createSearchIterator() );
    }
    catch( basar::Exception & e  )
    {
        libutil::exceptions::ExceptionHandler::processAccessorException( e, m_Logger, fun, SELECT_IBT_BRANCH_ARTICLE_RELEVANCE_PARAM, __FILE__, __LINE__ );
        throw;
    }

    if( executeResultInfo.hasError() )
    {
        THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_IBT_BRANCH_ARTICLE_RELEVANCE_PARAM, executeResultInfo )
    }
}

libutil::infrastructure::accessor::IAccessorPtr IbtRelevantBranchParameterDM::getAccessor() const
{
	METHODNAME_DEF( IbtRelevantBranchParameterDM, getAccessor )
    BLOG_TRACE_METHOD( m_Logger, fun );
	
    CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
    return m_Accessor;
}

basar::db::aspect::AccessorPropertyTableRef IbtRelevantBranchParameterDM::get()
{
	METHODNAME_DEF( IbtRelevantBranchParameterDM, get )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return getAccessor()->getPropertyTable();
}

void IbtRelevantBranchParameterDM::setBranchNo(const basar::Int16 branchNo)
{
	METHODNAME_DEF( IbtRelevantBranchParameterDM, setBranchNo )
    BLOG_TRACE_METHOD( m_Logger, fun );
	m_BranchNo = branchNo;
}

const log4cplus::Logger& IbtRelevantBranchParameterDM::getLogger() const
{
	return m_Logger;
}

basar::Int16 IbtRelevantBranchParameterDM::getBranchNo			( )
{
	METHODNAME_DEF( IbtRelevantBranchParameterDM, getBranchNo )
    BLOG_TRACE_METHOD( m_Logger, fun );
	
	return m_BranchNo;
}

//-----------------------------------------------------------------------------------------
} 
} 
} 
