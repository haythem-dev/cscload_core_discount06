#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_UNDERDELIVERYQUOTA_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_UNDERDELIVERYQUOTA_H

#include "irelevantrule.h"

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
	namespace domMod
	{
		namespace relevantRule
		{
			class UnderDeliveryQuota : public IRelevantRule
			{
			public:
				UnderDeliveryQuota(basar::Int32 underDeliveryQuotaCount);
				~UnderDeliveryQuota();

				// from IRelevantRule interface
				RuleDescription                                 getDescription() const;
				infrastructure::dataType::Trilean               isRelevant(infrastructure::dataProvider::IDataProviderPtr) const;
			private:
				// forbidden
				UnderDeliveryQuota();

			private:
				basar::Int32                                    m_UnderDeliveryQuotaCount;
			};

		} // end namespace relevantRule
	} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_UNDERDELIVERYQUOTA_H
