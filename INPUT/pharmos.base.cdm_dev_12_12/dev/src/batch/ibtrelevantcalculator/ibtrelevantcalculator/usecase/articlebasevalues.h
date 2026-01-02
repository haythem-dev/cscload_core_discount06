#ifndef GUARD_IBTRELEVANTCALCULATOR_USECASE_ARTICLEBASEVALUES_H
#define GUARD_IBTRELEVANTCALCULATOR_USECASE_ARTICLEBASEVALUES_H

#include <libbasardbsql_resultsetref.h>

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace useCase
    {
		//-------------------------------------------------------------------------------------------------//
        // class declaration
        //-------------------------------------------------------------------------------------------------//
        class ArticleBaseValues
		{
			public:
				ArticleBaseValues();
				virtual ~ArticleBaseValues();

				void				fillFromDbResult(const basar::db::sql::ResultsetRef);
				
				basar::Int32		getArticleNo() const;
				basar::Int16		getisFixedRegional() const;
				
				bool				isNarcotic() const;
				bool				isPrivateGood() const;
				bool				isDangerous() const;
				bool				isConsignment() const;
				bool				isPseudoStorLoc(const basar::VarString & pseudoStorLoc) const;
				bool				isExpensive(const basar::Decimal priceBorder) const;
				bool				isCentralExcl() const;
				bool				isBatch() const;
				bool				isSpecialArticle() const;
				bool				isHazardArticle() const;
				bool				isLockedArticle() const;
				bool				isCentralPurchaseLockedArticle() const;
				bool				isOutsaleExcl(basar::Int32 outsaleBorder) const;
				bool				isCoolExcl(basar::Int32 coolBorder) const;
				bool				isStorLocExcl(basar::VarString storLocExclFrom, basar::VarString storLocExclTo ) const;
				bool				isSeasonGroup(basar::VarString seasonGrp) const;
				bool				isNoDemand(const basar::Int32 demand) const;
				bool				isAbcExcl(basar::VarString abcCategory) const;

				//TH check for tourismus- exclusion
				
				const basar::Int32		getOutsaleDate()const;
				const basar::VarString	getStorLoc()	const;
				const basar::Decimal	getPrice()		const;

			private:
                ArticleBaseValues(const ArticleBaseValues& );
                ArticleBaseValues& operator= (const ArticleBaseValues& );

				const log4cplus::Logger&			m_Logger;
				basar::db::sql::ResultsetRef		m_ArticleValues;
		};
	}
}

#endif