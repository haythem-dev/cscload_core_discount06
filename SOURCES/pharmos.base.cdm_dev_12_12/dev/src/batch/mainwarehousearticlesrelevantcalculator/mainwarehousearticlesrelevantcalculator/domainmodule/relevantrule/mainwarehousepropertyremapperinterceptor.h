#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_MAINWAREHOUSEPROPERTYREMAPPERINTERCEPTOR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_MAINWAREHOUSEPROPERTYREMAPPERINTERCEPTOR_H

#include "irelevantrule.h"
#include "irelevantruleptr.h"

#include "infrastructure/dataprovider/idataproviderptr.h"

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    class MainwarehousePropertyRemapperInterceptor : public IRelevantRule
    {
    public:
        MainwarehousePropertyRemapperInterceptor( IRelevantRulePtr );
        ~MainwarehousePropertyRemapperInterceptor();

        // from IRelevantRule interface
        RuleDescription                                 getDescription() const;
        infrastructure::dataType::Trilean               isRelevant( infrastructure::dataProvider::IDataProviderPtr ) const;

    private:
        // forbidden
        MainwarehousePropertyRemapperInterceptor();

    private:
        IRelevantRulePtr                                m_RelevantRule;
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_MAINWAREHOUSEPROPERTYREMAPPERINTERCEPTOR_H
