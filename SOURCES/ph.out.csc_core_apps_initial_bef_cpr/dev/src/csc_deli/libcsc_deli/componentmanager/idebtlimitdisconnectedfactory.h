#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_IDEBTLIMITDISCONNECTEDFACTORY_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_IDEBTLIMITDISCONNECTEDFACTORY_H

#include "domainmodule/debtlimit/idebtlimitptr.h"

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

    class IDebtLimitDisconnectedFactory
    {
    public:
        virtual ~IDebtLimitDisconnectedFactory() {}

        virtual domMod::debtLimit::IDebtLimitPtr create( basar::db::aspect::AccessorPropertyTable_YIterator ) const = 0;
    };

} // end namespace componentManager
} // end namespace libcsc_deli

#endif //GUARD_LIBCSC_DELI_COMPONENTMANAGER_IDEBTLIMITDISCONNECTEDFACTORY_H
