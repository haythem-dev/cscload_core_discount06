#include "debtlimitdisconnectedfactory.h"

#include "domainmodule/debtlimit/debtlimitdm.h"
#include "domainmodule/debtlimit/debtlimitdmptr.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"

#include "infrastructure/accessor/debtlimit/debtlimitacc.h"
#include "infrastructure/accessor/debtlimit/debtlimitacc_definitions.h"

#include "loggerpool/libcsc_deli_loggerpool.h"
#include <boost/make_shared.hpp>

namespace libcsc_deli
{
namespace componentManager
{
    DebtLimitDisconnectedFactory::DebtLimitDisconnectedFactory()
    {
    }

    DebtLimitDisconnectedFactory::~DebtLimitDisconnectedFactory()
    {
    }

    libutil::infrastructure::accessor::IAccessorPtr DebtLimitDisconnectedFactory::getDebtLimitAccessor() const
    {
        infrastructure::accessor::debtLimit::SelectDebtLimit();

        using libutil::infrastructure::accessor::AccessorProxy;
        return boost::make_shared< AccessorProxy >( infrastructure::accessor::debtLimit::lit::DEBTLIMIT_ACC, getDBConnection() );
    }

    domMod::debtLimit::DebtLimitDMPtr DebtLimitDisconnectedFactory::getDebtLimitDM() const
    {
        domMod::debtLimit::DebtLimitDMPtr dm = boost::make_shared< domMod::debtLimit::DebtLimitDM >();
        dm->injectDebtLimitAccessor( getDebtLimitAccessor() );

        return dm;
    }

    void DebtLimitDisconnectedFactory::injectDBConnection( libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr dbConnDataGetter )
    {
        m_DBConnectionDataGetter = dbConnDataGetter;
    }

    basar::db::aspect::ConnectionRef DebtLimitDisconnectedFactory::getDBConnection() const
    {
        CHECK_INSTANCE_EXCEPTION( m_DBConnectionDataGetter.get() );
        return m_DBConnectionDataGetter->getCurrentConnection();
    }

    domMod::debtLimit::IDebtLimitPtr DebtLimitDisconnectedFactory::create( basar::db::aspect::AccessorPropertyTable_YIterator yit ) const
    {
        domMod::debtLimit::DebtLimitDMPtr debtLimit = getDebtLimitDM();
        debtLimit->set( yit );

        return debtLimit;
    }

} // end namespace componentManager
} // end namespace libcsc_deli
