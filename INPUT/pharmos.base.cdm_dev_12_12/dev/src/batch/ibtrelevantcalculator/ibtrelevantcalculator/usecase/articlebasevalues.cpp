//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "articlebasevalues.h"
#include "loggerpool/ibtrelevantcalculator_loggerpool.h"
#include <libutil/misc/metaclassmacro_definitions.h> // libutil
#include <libbasarcmnutil_logging.h>
#include "domainmodule/ibtrelevantcalculator_property_definitions.h"

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace useCase
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ArticleBaseValues::ArticleBaseValues()
		: m_Logger( ibtrelevantcalculator::LoggerPool::getLoggerUseCases() )
        {
            METHODNAME_DEF( ArticleBaseValues, ArticleBaseValues )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ArticleBaseValues::~ArticleBaseValues()
        {
            METHODNAME_DEF( ArticleBaseValues, ~ArticleBaseValues )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void ArticleBaseValues::fillFromDbResult(const basar::db::sql::ResultsetRef dbResult)
		{
			m_ArticleValues = dbResult;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        basar::Int32 ArticleBaseValues::getArticleNo() const
		{
			return m_ArticleValues.getInt32(properties::ARTICLE_NO.getName());
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		basar::Int16 ArticleBaseValues::getisFixedRegional() const
		{
			return m_ArticleValues.getInt16(properties::FIXREGIONAL.getName());
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isNarcotic() const
		{
			return m_ArticleValues.getString(properties::NARCOTIC_FLAG.getName()) == basar::VarString("1");
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isPrivateGood() const
		{
			return m_ArticleValues.getString(properties::PRIVATE_GOODS_TYPE.getName()) != basar::VarString("N");
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isDangerous() const
		{
			return basar::VarString(m_ArticleValues.getString(properties::UN_NO.getName())).empty() == false;
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isConsignment() const
		{
			return m_ArticleValues.getInt32(properties::CONSIGNMENT_PARTNER_NO.getName()) != 0;
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isPseudoStorLoc(const basar::VarString & pseudoStorLoc) const
		{
			return pseudoStorLoc == basar::VarString(m_ArticleValues.getString(properties::STORAGE_LOCATION.getName()));
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isAbcExcl(basar::VarString abcCategory) const
		{
			return abcCategory == basar::VarString(m_ArticleValues.getString(properties::ABC_CATEGORY.getName()));
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isSpecialArticle() const
		{
			return basar::VarString(m_ArticleValues.getString(properties::SPECIAL_ARTICLE_TYPE.getName())).empty() == false;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isHazardArticle() const
		{
			return	m_ArticleValues.getInt16(properties::HAZARDOUS_SUBSTANCE_OLD.getName()) > 0 || 
					m_ArticleValues.getInt16(properties::HAZARDOUS_SUBSTANCE_NEW.getName()) > 0;
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isLockedArticle() const
		{
			return m_ArticleValues.getString(properties::ARTICLE_LOCKED_FLAG.getName()) == basar::VarString("1");
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isCentralPurchaseLockedArticle() const
		{
			return m_ArticleValues.getString(properties::CENTR_PU_ART_LOCKED_FLAG.getName()) == basar::VarString("1");
		}
				
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isOutsaleExcl(basar::Int32 outsaleBorder) const
		{
			basar::cmnutil::Date dt = basar::cmnutil::Date::getCurrent();
			dt.addDays( -30 * outsaleBorder );

			return	m_ArticleValues.getInt32(properties::OUTSALE_DATE.getName()) > 0 &&
					dt.getDate() >= m_ArticleValues.getInt32(properties::OUTSALE_DATE.getName());
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const basar::Int32		ArticleBaseValues::getOutsaleDate()	const
		{
			return m_ArticleValues.getInt32(properties::OUTSALE_DATE.getName());
		}				
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isExpensive(const basar::Decimal priceBorder) const
		{
			return priceBorder <= m_ArticleValues.getDecimal(properties::PURCHASING_PRICE.getName());
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isCentralExcl() const
		{
			return m_ArticleValues.getInt16(properties::IBT_EXCLUDE_FLAG.getName()) == 1;
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isBatch() const
		{
			return m_ArticleValues.getString(properties::BATCH_FLAG.getName()) == basar::VarString("1");
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isCoolExcl(basar::Int32 coolBorder) const
		{
			basar::Int32 articleCoolMode = basar::VarString(m_ArticleValues.getString(properties::COOL_ARTICLE_MODE.getName())).stoi();

			if (coolBorder > 4 || coolBorder < 0)
				BLOG_WARN(m_Logger, "invalid cool border set at exclusion!");

			if (0 == articleCoolMode || 0 == coolBorder) // no cool article at all / no exclusion at all
				return false; 
			
			if (4 == articleCoolMode) // 4=Kühlkette
				return true; // cold chain article always excluded as coolBorder != 0

			if (4 == coolBorder) // 4=Kühlkette
				return false; // only cold chain excluded, but no cold chain article
							
			if (coolBorder >= articleCoolMode) // 1=8; 2=20; 3=25 Grad
				return true;
			else
				return false;			
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isStorLocExcl(basar::VarString storLocExclFrom, basar::VarString storLocExclTo ) const
		{
			basar::VarString storLoc = m_ArticleValues.getString(properties::STORAGE_LOCATION.getName());

			return storLoc >= storLocExclFrom && storLoc <= storLocExclTo;
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isSeasonGroup(basar::VarString seasonGrp) const
		{
			return	m_ArticleValues.getString(properties::SEASON_GROUP_1.getName()) == seasonGrp ||
					m_ArticleValues.getString(properties::SEASON_GROUP_2.getName()) == seasonGrp ||
					m_ArticleValues.getString(properties::SEASON_GROUP_3.getName()) == seasonGrp;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool	ArticleBaseValues::isNoDemand(const basar::Int32 demand) const
		{
			return 0 == demand;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const basar::VarString	ArticleBaseValues::getStorLoc()	const
		{
			return m_ArticleValues.getString(properties::STORAGE_LOCATION.getName());
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const basar::Decimal 	ArticleBaseValues::getPrice()		const
		{
			return m_ArticleValues.getDecimal(properties::PURCHASING_PRICE.getName());
		}
	}
}