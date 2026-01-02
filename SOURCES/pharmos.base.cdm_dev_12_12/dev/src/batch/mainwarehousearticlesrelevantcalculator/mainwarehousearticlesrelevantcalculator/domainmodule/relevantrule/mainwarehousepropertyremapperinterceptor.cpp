#include "mainwarehousepropertyremapperinterceptor.h"
#include "infrastructure/dataprovider/idataprovider.h"

#include "infrastructure/dataprovider/propertyremapper.h"
#include "infrastructure/dataprovider/propertyremapperptr.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

#include <boost/make_shared.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    MainwarehousePropertyRemapperInterceptor::MainwarehousePropertyRemapperInterceptor( IRelevantRulePtr rule )
        : m_RelevantRule( rule )
    {
    }

    MainwarehousePropertyRemapperInterceptor::~MainwarehousePropertyRemapperInterceptor()
    {
    }

    RuleDescription MainwarehousePropertyRemapperInterceptor::getDescription() const
    {
        return m_RelevantRule->getDescription();
    }

    infrastructure::dataType::Trilean MainwarehousePropertyRemapperInterceptor::isRelevant( infrastructure::dataProvider::IDataProviderPtr articleData ) const
    {
        using namespace infrastructure::dataProvider;

        PropertyRemapperPtr propertyRemapper = boost::make_shared< PropertyRemapper > ( articleData );
        propertyRemapper->map( properties::STORAGE_LOCATION, properties::STORAGE_LOCATION_MAINWH );
        
        return m_RelevantRule->isRelevant( propertyRemapper );
    }

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator
