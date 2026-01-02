#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVEREXPORTERPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVEREXPORTERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace turnover
        {
            class ICustomerTurnoverExporter;
            typedef boost::shared_ptr< ICustomerTurnoverExporter > ICustomerTurnoverExporterPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVEREXPORTERPTR_H
