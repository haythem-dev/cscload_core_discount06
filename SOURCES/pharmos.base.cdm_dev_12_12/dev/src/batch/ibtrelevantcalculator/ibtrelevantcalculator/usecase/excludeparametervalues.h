#ifndef GUARD_IBTRELEVANTCALCULATOR_USECASE_EXCLUDEPARAMETERVALUES_H
#define GUARD_IBTRELEVANTCALCULATOR_USECASE_EXCLUDEPARAMETERVALUES_H

#include <libbasarproperty_propertydescription.h>
#include <libbasarcmnutil_decimal.h>
#include <vector>

namespace log4cplus
{
    class Logger;
}

namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
        }
    }
}

typedef std::vector<basar::VarString>								ExcludedSeasonGroupCollection;
typedef std::pair<basar::VarString, basar::VarString>				ExludedStorLocArea;
typedef std::vector<ExludedStorLocArea>								ExcludedStorLocAreaCollection;
typedef std::vector<basar::VarString>								ExcludedAbcCategoryCollection;

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace useCase
    {
		namespace exclrule_context
		{
			const basar::VarString EXCL_ART_WITHOUT_DEMAND		( "WITHOUT_DEMAND" );
			const basar::VarString EXCL_PSEUDO_STORLOC			( "WITHOUT_ACTIVE_BINLOCATION" );
			const basar::VarString EXCL_NARCOTICS				( "NARCOTIC" );
			const basar::VarString EXCL_CONSIGNMENT_GOODS		( "CONSIGNMENT" );
			const basar::VarString EXCL_DANGEROUS_GOODS			( "DANGEROUS" );
			const basar::VarString EXCL_EXPENSIVE_ART			( "EXPENSIVE" );
			const basar::VarString EXCL_COOL_ART				( "COOL" );
			const basar::VarString EXCL_IBT_LOCK_CENTRAL		( "CDMIBTFLAG" );
			const basar::VarString EXCL_BATCH_ART				( "BATCH" );
			const basar::VarString EXCL_BIN_LOCATION_RANGE		( "BINLOCATIONRANGE" );
			const basar::VarString EXCL_SEASON_GROUP			( "SEASONCATEGORY" );
			const basar::VarString EXCL_SPECIAL_ARTICLE_TYPE	( "SPECIALARTICLETYPE" );
			const basar::VarString EXCL_HAZARD_GOODS			( "HAZARDOUSSUBSTANCES" );
			const basar::VarString EXCL_LOCKED_ART				( "BLOCKEDARTICLE" );
			const basar::VarString EXCL_PU_LOCKED_ART			( "CENTRALPURCHASEBLOCKEDARTICLE" );
			const basar::VarString EXCL_OUTSALE					( "OUTOFTRADEARTICLE" );
			const basar::VarString EXCL_ABC_ARTICLE				( "ABC_ARTICLE_CATEGORY" );

			//TH 25 new exclusion parameter
		}

		//-------------------------------------------------------------------------------------------------//
        // class declaration
        //-------------------------------------------------------------------------------------------------//
        class ExcludeParameterValues
		{
			public:
				ExcludeParameterValues();
				virtual ~ExcludeParameterValues();

				void	addParameterRow(basar::db::aspect::AccessorPropertyTable_YIterator &);

				bool					isDemandNullExcluded()		const;
				basar::Int32			getWeeksForDemandNull()		const;
				bool					isPseudoStorLocExcluded()	const;
				bool					isNarcoticExcluded()		const;
				bool					isConsignmentExcluded()		const;
				bool					isDangerousExcluded()		const;
				bool					isExpensiveExcluded()		const;
				const basar::Decimal	getExpensivePriceBorder()	const;
				bool					isCoolExcluded()			const;
				basar::Int32			getCoolBorder()				const;
				bool					isCentralLockExcluded()		const;
				bool					isBatchExcluded()			const;
				bool					isStorLocAreaExcluded()		const;
				bool					isSeasonGroupExcluded()		const;	
				bool					isSpecialArticleExcluded()	const;	
				const basar::VarString	& getPseudoStorLoc()		const;
				bool					isAbcCategoryExcluded()		const;

				//TH new methods for exclusion parameters

				bool					isHazardGoodExcluded()		const;
				bool					isLockedArticleExcluded()	const;
				bool					isCentralPurchaseLockedArticleExcluded() const;
				bool					isOutsaleExcluded()			const;
				basar::Int32			getOutsaleBorder()			const;
	
				ExcludedSeasonGroupCollection	getExclSeasonGroups() const;
				ExcludedStorLocAreaCollection	getExclStorLocAreas() const;
				ExcludedAbcCategoryCollection	getExclAbcCategories() const;
								
			private:
                ExcludeParameterValues(const ExcludeParameterValues& );
                ExcludeParameterValues& operator= (const ExcludeParameterValues& );

				const log4cplus::Logger&			m_Logger;

				basar::Int32						m_WeeksForDemand;
				basar::Int32						m_CoolBorder;
				basar::Decimal						m_PriceExpensive;
				basar::VarString					m_PseudoStorLoc;
				bool								m_ExclNarcotics;
				bool								m_ExclConsignment;
				bool								m_ExclDangerous;
				bool								m_ExclLockByCDM;
				bool								m_ExclBatch;
				bool								m_ExclSpecialArticleType;
				bool								m_ExclHazardGoods;
				bool								m_ExclLockedArticles;
				bool								m_ExclCentrPuLockedArticles;
				basar::Int32						m_OutSaleBorder;
				ExcludedSeasonGroupCollection		m_ExclSeasonGroups;
				ExcludedStorLocAreaCollection		m_ExclStorLocAreas;
				ExcludedAbcCategoryCollection		m_ExclAbcCategories;
		};
	}
}

#endif