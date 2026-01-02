#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAILSQLMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAILSQLMAPPER_H

#include "shipmenttrackinglinedetailsqlmapperptr.h"
#include "shipmenttrackinglinedetailmapperbase.h"
#include "shipmenttrackingpackageinformationsqlmapperptr.h"
#include "shipmenttrackingbatchtototelinemapperptr.h"
#include "shipmenttrackingcurrentwhslinecontextptr.h"

#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingLineDetailSQLMapper : public ShipmentTrackingLineDetailMapperBase
{
public:
    ShipmentTrackingLineDetailSQLMapper(ShipmentTrackingLineDetailPtr lineDetail);
    virtual ~ShipmentTrackingLineDetailSQLMapper();

    void mapFromOutboundDataAndAddLineDetail(const basar::db::sql::ResultsetRef resultSet, ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder, bool isNarcotic);

    void removeLineDetailFromOutboundCollection(ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder);

    void addExtractedOutboundLineToWarehouseTote(ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder);

    void createNewLineDetailCloneFromOutboundDataAndAttachToPackageInfo(ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder);

    void mapFromWarehouseData(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext, ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder);

private:
    // prohibit copy constructor and assignment operator:
    ShipmentTrackingLineDetailSQLMapper(const ShipmentTrackingLineDetailSQLMapper&);
    ShipmentTrackingLineDetailSQLMapper & operator=(const ShipmentTrackingLineDetailSQLMapper&);

    void fillCloneFromOutboundData(const ShipmentTrackingLineDetail& originalLineDetail);

    ShipmentTrackingLineDetailCollection::iterator addCurrentLineDetailToOwnerPackage(ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder);

    // -----
    // Data:

    ShipmentTrackingLineDetailCollection::iterator m_OutboundPackageLineColectionIterator;

    //! \brief Batch --> BatchToToteLineMapper map
    ShipmentTrackingBatchToToteLineMapperStrMap    m_WhsBatchToBatchToToteLineMapperMap;
};


} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAILSQLMAPPER_H
