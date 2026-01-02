#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICECONNECTEDFACTORY_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICECONNECTEDFACTORY_H

#include "domainmodule/customerinvoice/icustomerinvoiceptr.h"

//------------------------------------------------------------------------------//
// Forward declarations
//------------------------------------------------------------------------------//
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

namespace libcsc_deli
{
namespace componentManager
{

    class ICustomerInvoiceConnectedFactory
    {
    public:
        virtual ~ICustomerInvoiceConnectedFactory() {}

        virtual domMod::customerInvoice::ICustomerInvoicePtr create( basar::db::aspect::AccessorPropertyTable_YIterator ) const = 0;
    };

} // end namespace componentManager
} // end namespace libcsc_deli

#endif //GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICECONNECTEDFACTORY_H
