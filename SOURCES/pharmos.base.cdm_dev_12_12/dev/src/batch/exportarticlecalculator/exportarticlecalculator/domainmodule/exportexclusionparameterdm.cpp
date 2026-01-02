#include "exportexclusionparameterdm.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include <libutil/misc/log_macro_definitions.h>      // libutil
#include <loggerpool/exportarticlecalculator_loggerpool.h>
#include "domainmodule/exportarticlecalculator_property_definitions.h"
#include "infrastructure/accessor/exportexclusionparameteracc_definitions.h"

#include <libutil/domainmodule.h>
#include <libutil/exception.h>

//-----------------------------------------------------------------------------------------

namespace exportarticlecalculator {
namespace domMod {
namespace exportexclusionparameter {

//-----------------------------------------------------------------------------------------
	
ExportExclusionParameterDM::ExportExclusionParameterDM(const log4cplus::Logger& logger) :
	m_Logger(logger), m_BranchNo(0), m_Country("")
{

}

ExportExclusionParameterDM::~ExportExclusionParameterDM()
{
	
}

void ExportExclusionParameterDM::injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor)
{
	m_Accessor = accessor;
}

basar::db::aspect::AccessorPropertyTable_YIterator ExportExclusionParameterDM::createSearchIterator()
{
	basar::VarString defParam;
	defParam.format("%s=%d;%s=%s;", properties::BRANCH_NO.getName().c_str(), m_BranchNo, properties::COUNTRY_CODE.getName().c_str(), m_Country.c_str() );

	return basar::db::aspect::Manager::getInstance().createAccessorYIterator(basar::cmnutil::ParameterList(defParam));
}

void ExportExclusionParameterDM::find(  )
{
	METHODNAME_DEF( IbtRelevantParameterDM, find )
    BLOG_TRACE_METHOD( m_Logger, fun );

	using exportarticlecalculator::infrastructure::accessor::exportexclusionparameter::lit::SELECT_EXPORT_EXCLUSION_PARAM_BY_COUNTRY;

	basar::db::aspect::ExecuteResultInfo executeResultInfo;
    try
    {
        executeResultInfo = m_Accessor->execute( SELECT_EXPORT_EXCLUSION_PARAM_BY_COUNTRY, createSearchIterator() );
    }
    catch( basar::Exception & e  )
    {
        libutil::exceptions::ExceptionHandler::processAccessorException( e, m_Logger, fun, SELECT_EXPORT_EXCLUSION_PARAM_BY_COUNTRY, __FILE__, __LINE__ );
        throw;
    }

    if( executeResultInfo.hasError() )
    {
        THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_EXPORT_EXCLUSION_PARAM_BY_COUNTRY, executeResultInfo )
    }
}

libutil::infrastructure::accessor::IAccessorPtr ExportExclusionParameterDM::getAccessor() const
{
    CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
    return m_Accessor;
}

basar::db::aspect::AccessorPropertyTableRef ExportExclusionParameterDM::get()
{
	METHODNAME_DEF( CustomerCollectionDM, get )
    BLOG_TRACE_METHOD( m_Logger, fun );

    return getAccessor()->getPropertyTable();
}

void ExportExclusionParameterDM::setBranchNo(const basar::Int16 branchNo)
{
	m_BranchNo = branchNo;
}

void ExportExclusionParameterDM::setCountry(const basar::VarString & country)
{
	m_Country = country;
}

const log4cplus::Logger& ExportExclusionParameterDM::getLogger() const
{
	return m_Logger;
}

basar::Int16		ExportExclusionParameterDM::getBranchNo			( )
{
	return m_BranchNo;
}

basar::VarString		ExportExclusionParameterDM::getCountry			( )
{
	return m_Country;
}

//-----------------------------------------------------------------------------------------
} 
} 
} 
