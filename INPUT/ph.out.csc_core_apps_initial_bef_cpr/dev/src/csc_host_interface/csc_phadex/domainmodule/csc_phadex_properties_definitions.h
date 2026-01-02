#ifndef GUARD_CSC_PHADEX_PROPERTIES_DEFINITIONS_H
#define GUARD_CSC_PHADEX_PROPERTIES_DEFINITIONS_H

#include <libbasarproperty_definitions.h>
#include <libbasarproperty_propertydescription.h>

namespace properties
{
    //phadextransaction
    CONST_PROPERTY_DESCRIPTION( DATABASE_NAME, "databasename", basar::STRING )
    CONST_PROPERTY_DESCRIPTION( BRANCH_NO, "branchno", basar::INT16 )
    CONST_PROPERTY_DESCRIPTION( CREATION_DATETIME, "creationdatetime", basar::DATETIME )
    CONST_PROPERTY_DESCRIPTION( DATA, "data", basar::STRING )
    CONST_PROPERTY_DESCRIPTION( PROCESS_DATETIME, "processdatetime", basar::DATETIME )
    CONST_PROPERTY_DESCRIPTION( PROCESSED_FLAG, "processedflag", basar::INT16 )
    CONST_PROPERTY_DESCRIPTION( RECORD_NO, "recordno", basar::INT32 )
    CONST_PROPERTY_DESCRIPTION( RECORD_TYPE, "recordtype", basar::INT16 )
    CONST_PROPERTY_DESCRIPTION( TRANSFER_DATETIME, "transferdatetime", basar::DATETIME )

    //DRKSC
    CONST_PROPERTY_DESCRIPTION( RRDS_RRN, "rrds_rrn", basar::INT32 )
    CONST_PROPERTY_DESCRIPTION( KSC_FIL, "ksc_fil", basar::INT16 )
    CONST_PROPERTY_DESCRIPTION( KSC_SA, "ksc_sa", basar::INT16 )
    CONST_PROPERTY_DESCRIPTION( KSC_DATUM, "ksc_datum", basar::INT32 )
    CONST_PROPERTY_DESCRIPTION( KSC_ZEIT, "ksc_zeit", basar::INT32 )
    CONST_PROPERTY_DESCRIPTION( KSC_STATUS, "ksc_status", basar::STRING)
    CONST_PROPERTY_DESCRIPTION( KSC_DATA, "ksc_data", basar::STRING )
	CONST_PROPERTY_DESCRIPTION( LIMIT, "limit", basar::INT32 )

    //narctransactiontransfer
    CONST_PROPERTY_DESCRIPTION( COMPLETED_FLAG, "completedflag", basar::INT16 )
    CONST_PROPERTY_DESCRIPTION( ORDER_NO, "orderno", basar::INT32 )
	CONST_PROPERTY_DESCRIPTION( WAREHOUSE_ORDER_NO, "warehouseorderno", basar::INT32)
    CONST_PROPERTY_DESCRIPTION( CUSTOMERSUPPLIERNO, "customersupplierno", basar::INT32)

} // end namespace properties

#endif // GUARD_CSC_PHADEX_PROPERTIES_DEFINITIONS_H
