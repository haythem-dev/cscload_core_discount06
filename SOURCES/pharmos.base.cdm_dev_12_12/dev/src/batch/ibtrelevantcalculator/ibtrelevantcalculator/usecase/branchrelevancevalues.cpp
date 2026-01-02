//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "branchrelevancevalues.h"
#include "loggerpool/ibtrelevantcalculator_loggerpool.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include <libbasarcmnutil_logging.h>
#include "domainmodule/ibtrelevantcalculator_property_definitions.h"

#include <libbasardbaspect_accessorpropertytable_yiterator.h>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace useCase
    {
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	BranchRelevanceValues::BranchRelevanceValues()
	:	m_Logger( ibtrelevantcalculator::LoggerPool::getLoggerUseCases() ),
		m_BrRelevance(0)
	{
		METHODNAME_DEF( BranchRelevanceValues, BranchRelevanceValues )
		BLOG_TRACE_METHOD( m_Logger, fun );
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	BranchRelevanceValues::~BranchRelevanceValues()
	{
		METHODNAME_DEF( BranchRelevanceValues, ~BranchRelevanceValues )
		BLOG_TRACE_METHOD( m_Logger, fun );
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void	BranchRelevanceValues::GetBranchParameterValue(basar::db::aspect::AccessorPropertyTable_YIterator & yitParam, basar::Int16 brno )
	{
		METHODNAME_DEF( BranchRelevanceValues, GetBranchParameterValue )
		BLOG_TRACE_METHOD( m_Logger, fun );
		
		//if (yitParam.getInt16(properties::FIXREGIONALASSIGNMENTFLAG.getName()) == branchrule_context::FIXREGIONALASSIGNMENTFLAG1)
		//{
			m_BrRelevance = yitParam.getInt16(properties::FIXREGIONALASSIGNMENTFLAG.getName());

			std::stringstream ss;
			ss << "Fix Regional " << m_BrRelevance << " for BranchNo." << brno;
			BLOG_INFO(m_Logger, ss.str());
		//}
		//else
		//{
			//BLOG_WARN (m_Logger, "unknown Fix Regional context name detected.");
		//}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	basar::Int16	BranchRelevanceValues::getBranchValueYesNo()		const
	{
		METHODNAME_DEF( BranchRelevanceValues, getBranchValueYesNo )
		BLOG_TRACE_METHOD( m_Logger, fun );

		return m_BrRelevance;
	}


	}
}