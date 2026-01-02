#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_DEBTLIMITDISCONNECTEDFACTORY_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_DEBTLIMITDISCONNECTEDFACTORY_H

#include "idebtlimitdisconnectedfactory.h"

#include "domainmodule/debtlimit/debtlimitdmptr.h"

#include <libutil/accessor.h>
#include <libutil/dbconnection.h>

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
    class DebtLimitDisconnectedFactory : public IDebtLimitDisconnectedFactory
    {
    public:
        DebtLimitDisconnectedFactory();
        ~DebtLimitDisconnectedFactory();

        void                                            injectDBConnection( libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr );

        // from IDebtLimitConnectedFactory interface
        domMod::debtLimit::IDebtLimitPtr                create( basar::db::aspect::AccessorPropertyTable_YIterator ) const;

    private:
        basar::db::aspect::ConnectionRef                getDBConnection()      const;

        libutil::infrastructure::accessor::IAccessorPtr getDebtLimitAccessor() const;
        domMod::debtLimit::DebtLimitDMPtr               getDebtLimitDM()       const;

    private:
        // forbidden
        DebtLimitDisconnectedFactory( const DebtLimitDisconnectedFactory& );
        DebtLimitDisconnectedFactory& operator = ( const DebtLimitDisconnectedFactory& );

        libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr m_DBConnectionDataGetter;
    };

} // end namespace componentManager
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_COMPONENTMANAGER_DEBTLIMITDISCONNECTEDFACTORY_H
