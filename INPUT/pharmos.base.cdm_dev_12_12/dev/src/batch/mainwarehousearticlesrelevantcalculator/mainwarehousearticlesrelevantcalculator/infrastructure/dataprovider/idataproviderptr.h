#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_IDATAPROVIDERPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_IDATAPROVIDERPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace dataProvider
{
    class IDataProvider;
    typedef boost::shared_ptr< IDataProvider > IDataProviderPtr;

} // end namespace dataProvider
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_IDATAPROVIDERPTR_H
