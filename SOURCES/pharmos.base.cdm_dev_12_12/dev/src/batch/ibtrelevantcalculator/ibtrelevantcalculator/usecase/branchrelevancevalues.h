#ifndef GUARD_IBTRELEVANTCALCULATOR_USECASE_BRANCHRELEVANCEVALUES_H
#define GUARD_IBTRELEVANTCALCULATOR_USECASE_BRANCHRELEVANCEVALUES_H

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
/*
typedef std::vector<basar::VarString>								ExcludedSeasonGroupCollection;
typedef std::pair<basar::VarString, basar::VarString>				ExludedStorLocArea;
typedef std::vector<ExludedStorLocArea>								ExcludedStorLocAreaCollection;
typedef std::vector<basar::VarString>								ExcludedAbcCategoryCollection;
*/
//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace useCase
    {
	/*	namespace branchrule_context
		{
			const basar::Int16 FIXREGIONALASSIGNMENTFLAG1		( "considerfixregionalassignmentflag" );
		}
*/
		//-------------------------------------------------------------------------------------------------//
        // class declaration
        //-------------------------------------------------------------------------------------------------//
        class BranchRelevanceValues
		{
			public:
				BranchRelevanceValues();
				virtual ~BranchRelevanceValues();

				void	GetBranchParameterValue(basar::db::aspect::AccessorPropertyTable_YIterator &, basar::Int16 brno);

				basar::Int16	getBranchValueYesNo()		const;
								
			private:
                BranchRelevanceValues(const BranchRelevanceValues& );
                BranchRelevanceValues& operator= (const BranchRelevanceValues& );

				const log4cplus::Logger&			m_Logger;

				basar::Int16						m_BrRelevance;
		};
	}
}

#endif