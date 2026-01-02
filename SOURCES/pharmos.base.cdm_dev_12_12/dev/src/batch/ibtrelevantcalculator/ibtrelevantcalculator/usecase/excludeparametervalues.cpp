//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "excludeparametervalues.h"
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
	ExcludeParameterValues::ExcludeParameterValues()
	:	m_Logger( ibtrelevantcalculator::LoggerPool::getLoggerUseCases() ),
		m_WeeksForDemand(0),
		m_CoolBorder(0),
		m_PriceExpensive(basar::Decimal(0)),
		m_PseudoStorLoc(""),
		m_ExclNarcotics(false),
		m_ExclConsignment(false),
		m_ExclDangerous(false),
		m_ExclLockByCDM(false),
		m_ExclBatch(false),
		m_ExclSpecialArticleType(false),
		m_ExclHazardGoods(false),
		m_ExclLockedArticles(false),
		m_ExclCentrPuLockedArticles(false),
		m_OutSaleBorder(0)
	{
		METHODNAME_DEF( ExcludeParameterValues, ExcludeParameterValues )
		BLOG_TRACE_METHOD( m_Logger, fun );
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ExcludeParameterValues::~ExcludeParameterValues()
	{
		METHODNAME_DEF( ExcludeParameterValues, ~ExcludeParameterValues )
		BLOG_TRACE_METHOD( m_Logger, fun );
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void	ExcludeParameterValues::addParameterRow(basar::db::aspect::AccessorPropertyTable_YIterator & yitParam)
	{
		if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_ART_WITHOUT_DEMAND)
		{
			m_WeeksForDemand = yitParam.getInt32(properties::COMPARE_VALUE_INT.getName());

			std::stringstream ss;
			ss << "exclusion of articles without demand in the past " << m_WeeksForDemand << " weeks.";
			BLOG_INFO(m_Logger, ss.str());
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_PSEUDO_STORLOC)
		{
			m_PseudoStorLoc = yitParam.getString(properties::PSEUDO_STORAGE_LOCATION.getName());
			BLOG_INFO(m_Logger, "Exclusion of articles with pseudo storage location.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_NARCOTICS)
		{
			m_ExclNarcotics = true;
			BLOG_INFO(m_Logger, "Exclusion of narcotic articles.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_CONSIGNMENT_GOODS)
		{
			m_ExclConsignment = true;
			BLOG_INFO(m_Logger, "Exclusion of consignment articles.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_DANGEROUS_GOODS)
		{
			m_ExclDangerous = true;
			BLOG_INFO(m_Logger, "Exclusion of dangerous articles.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_EXPENSIVE_ART)
		{
			m_PriceExpensive = yitParam.getDecimal(properties::COMPARE_VALUE_DEC.getName());

			std::stringstream ss;
			ss << "exclusion of expensive articles = purchasing price >= " << m_PriceExpensive.toString(2);
			BLOG_INFO(m_Logger, ss.str());
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_COOL_ART)
		{
			m_CoolBorder = yitParam.getInt32(properties::COMPARE_VALUE_INT.getName());
			
			std::stringstream ss;
			ss << "exclusion of cool articles; border = " << m_CoolBorder;
			BLOG_INFO(m_Logger, ss.str());
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_IBT_LOCK_CENTRAL)
		{
			m_ExclLockByCDM = true;
			BLOG_INFO(m_Logger, "Exclusion of centrally blocked articles.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_BATCH_ART)
		{
			m_ExclBatch = true;
			BLOG_INFO(m_Logger, "Exclusion of batch articles.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_BIN_LOCATION_RANGE)
		{
			m_ExclStorLocAreas.push_back(std::make_pair(yitParam.getString(properties::INTERVAL_START.getName()), yitParam.getString(properties::INTERVAL_END.getName())));
			
			std::stringstream ss;
			ss << "exclusion of articles in storage location area " << yitParam.getString(properties::INTERVAL_START.getName()) << " - " << yitParam.getString(properties::INTERVAL_END.getName());
			BLOG_INFO( m_Logger, ss.str() );
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_SEASON_GROUP)
		{
			m_ExclSeasonGroups.push_back(yitParam.getString(properties::COMPARE_VALUE_STR.getName()));

			std::stringstream ss;
			ss << "exclusion of articles with season group " << yitParam.getString(properties::COMPARE_VALUE_STR.getName());
			BLOG_INFO( m_Logger, ss.str() );
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_ABC_ARTICLE)
		{
			m_ExclAbcCategories.push_back(yitParam.getString(properties::COMPARE_VALUE_STR.getName()));

			std::stringstream ss;
			ss << "exclusion of articles with ABC category " << yitParam.getString(properties::COMPARE_VALUE_STR.getName());
			BLOG_INFO( m_Logger, ss.str() );
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_SPECIAL_ARTICLE_TYPE)
		{
			m_ExclSpecialArticleType = true;
			BLOG_INFO(m_Logger, "Exclusion of special articles.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_HAZARD_GOODS)
		{
			m_ExclHazardGoods = true;
			BLOG_INFO(m_Logger, "Exclusion of hazardous articles.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_LOCKED_ART)
		{
			m_ExclLockedArticles = true;
			BLOG_INFO(m_Logger, "Exclusion of locked articles.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_PU_LOCKED_ART)
		{
			m_ExclCentrPuLockedArticles = true;
			BLOG_INFO(m_Logger, "Exclusion of central purchase locked articles.");
		}
		else if (yitParam.getString(properties::CONTEXT_NAME.getName()) == exclrule_context::EXCL_OUTSALE)
		{
			m_OutSaleBorder = yitParam.getInt32(properties::COMPARE_VALUE_INT.getName());
			
			std::stringstream ss;
			ss << "exclusion of articles with outsale date more than < " << m_OutSaleBorder << " > month in the past.";
			BLOG_INFO(m_Logger, ss.str());
		}
		//TH detect (25) new exclusion parameters
		else
		{
			BLOG_WARN (m_Logger, "unknown context name detected.");
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isDemandNullExcluded()		const
	{
		return m_WeeksForDemand > 0;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	basar::Int32	ExcludeParameterValues::getWeeksForDemandNull()		const
	{
		return m_WeeksForDemand;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isPseudoStorLocExcluded()	const
	{
		return !m_PseudoStorLoc.empty();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const basar::VarString & ExcludeParameterValues::getPseudoStorLoc() const
	{
		return m_PseudoStorLoc;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isNarcoticExcluded()		const
	{
		return m_ExclNarcotics;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isConsignmentExcluded()		const
	{
		return m_ExclConsignment;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isDangerousExcluded()		const
	{
		return m_ExclDangerous;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isSpecialArticleExcluded()		const
	{
		return m_ExclSpecialArticleType;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isHazardGoodExcluded()		const
	{
		return m_ExclHazardGoods;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isLockedArticleExcluded()		const
	{
		return m_ExclLockedArticles;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isCentralPurchaseLockedArticleExcluded()		const
	{
		return m_ExclCentrPuLockedArticles;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isOutsaleExcluded()		const
	{
		return m_OutSaleBorder > 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	basar::Int32 ExcludeParameterValues::getOutsaleBorder()	const
	{
		return m_OutSaleBorder;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isExpensiveExcluded()		const
	{
		return m_PriceExpensive > basar::Decimal(0);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const basar::Decimal ExcludeParameterValues::getExpensivePriceBorder()	const
	{
		return m_PriceExpensive;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isCoolExcluded()			const
	{
		return m_CoolBorder > 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	basar::Int32	ExcludeParameterValues::getCoolBorder()				const
	{
		return m_CoolBorder;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isCentralLockExcluded()		const
	{
		return m_ExclLockByCDM;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isBatchExcluded()			const
	{
		return m_ExclBatch;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isStorLocAreaExcluded()		const
	{
		return !m_ExclStorLocAreas.empty();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isSeasonGroupExcluded()		const
	{
		return !m_ExclSeasonGroups.empty();
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool	ExcludeParameterValues::isAbcCategoryExcluded()		const
	{
		return !m_ExclAbcCategories.empty();
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ExcludedSeasonGroupCollection	ExcludeParameterValues::getExclSeasonGroups() const
	{
		return m_ExclSeasonGroups;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ExcludedStorLocAreaCollection	ExcludeParameterValues::getExclStorLocAreas() const
	{
		return m_ExclStorLocAreas;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ExcludedAbcCategoryCollection	ExcludeParameterValues::getExclAbcCategories() const
	{
		return m_ExclAbcCategories;
	}

	}
}