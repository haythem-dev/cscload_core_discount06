#include "narcoticsacc.h"
#include "narcoticsacc_definitions.h"
#include "domainmodule/csc_phadex_properties_definitions.h"
#include "loggerpool/csc_phadex_loggerpool.h"

namespace infrastructure
{
namespace accessor
{
namespace narcotics
{
BEGIN_ACCESSOR_DEFINITION( lit::NARCOTICS_TRANSFER_ACC )

BEGIN_PROPERTY_DESCRIPTION_LIST
    PROPERTY_DESCRIPTION_LIST_ADD( properties::BRANCH_NO );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::ORDER_NO );
    PROPERTY_DESCRIPTION_LIST_ADD( properties::COMPLETED_FLAG );
END_PROPERTY_DESCRIPTION_LIST

    ACCESS_METHOD( lit::SAVE_NARC_TRANSFER )
    SQL_BUILDER_CREATE( UpdateNarcTransfer )
    SQL_BUILDER_PUSH_BACK( UpdateNarcTransfer )
END_ACCESSOR_DEFINITION


BUILDER_DEFINITION( UpdateNarcTransfer )
bool UpdateNarcTransfer::isExecutable() const
{
    const bool executable = arePropertiesSet( properties::BRANCH_NO.toPropertyString() ) &&
                            arePropertiesSet( properties::CUSTOMERSUPPLIERNO.toPropertyString() ) &&
                            arePropertiesSet( properties::ORDER_NO.toPropertyString() ) &&
                            arePropertiesSet( properties::WAREHOUSE_ORDER_NO.toPropertyString() );
                            
    return executable;
}

void UpdateNarcTransfer::buildSQLString()
{
    using namespace properties;
    static const basar::VarString constSQL( "UPDATE narctransactiontransfer"
    " SET completedflag ='2', "
    " warehouseorderno = "       + WAREHOUSE_ORDER_NO.toSQLReplacementString() +
    " WHERE branchno = "         + BRANCH_NO.toSQLReplacementString() +
    " AND orderno = "            + ORDER_NO.toSQLReplacementString() +
    " AND customersupplierno = " + CUSTOMERSUPPLIERNO.toSQLReplacementString() + ";"
    );
    resolve( constSQL );
    BLOG_TRACE( csc_phadex::LoggerPool::getLoggerDomModules(), getSQLString() );
}


}
}
}
