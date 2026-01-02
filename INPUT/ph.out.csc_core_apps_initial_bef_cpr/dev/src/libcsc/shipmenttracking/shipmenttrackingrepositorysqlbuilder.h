#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORYSQLBUILDER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORYSQLBUILDER_H

#include "shipmenttrackingutils.h"
#include "shipmenttrackingdatafilter.h"
#include "shipmenttrackingrequestprocessingcontextptr.h"


/////////////////////////////////////////////////////////////////////////////////////
// class declaration
/////////////////////////////////////////////////////////////////////////////////////

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingRepositorySqlBuilder
{
public:

    static const basar::VarString getOutboundDataSelectSQL(
        const ShipmentTrackingRequestProcessingContext& context
    );

    static const basar::VarString getOutboundDataSelectSQLTourIDs(
        const ShipmentTrackingRequestProcessingContext& context,
        const basar::Int32& TourDate
    );

    static const basar::VarString getOutboundDataSelectSQLTourID_IDFS(
        const ShipmentTrackingRequestProcessingContext& context,
        const std::vector<std::string>& tourIDs,
        const basar::Int32& TourDate
    );

    static const basar::VarString getWarehouseDataSelectSQL(
        const ShipmentTrackingRequestProcessingContext& context,
        const Int32HashSetMap& pickingDateMap,
        const Int32HashSetMap& cscOrderNoMap
    );

private:
    // Prohibit defaul user construction:
    ShipmentTrackingRepositorySqlBuilder();
    virtual ~ShipmentTrackingRepositorySqlBuilder();

    //! \brief The SELECT for the current day or future delivery date, starting from the table KdAuftrag
    static void getOutboundDataSelectForCurrentDayTables(
        const ShipmentTrackingRequestProcessingContext& context,
        std::stringstream& sSql
    );

    //! \brief The SELECT for the Archive, starting from the table AKdAuftrag
    static void getOutboundDataSelectForArchiveTables(
        const ShipmentTrackingRequestProcessingContext& context,
        std::stringstream& sSql
    );

};


} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORYSQLBUILDER_H
