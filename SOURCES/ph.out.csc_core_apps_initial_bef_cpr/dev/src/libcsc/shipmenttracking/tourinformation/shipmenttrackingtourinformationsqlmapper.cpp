#include "shipmenttrackingtourdatasqlmapper.h"
#include "shipmenttrackingtourinformationsqlmapper.h"
#include "shipmenttrackingtourinformation.h"
#include <libbasarcmnutil_timespan.h>
#include <persistence/iaccessor.h>
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <boost/make_shared.hpp>

namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingTourInformationSQLMapper::ShipmentTrackingTourInformationSQLMapper(ShipmentTrackingTourInformationPtr shipmentTrackingTourInformation) :
    ShipmentTrackingTourInformationMapperBase(shipmentTrackingTourInformation)
{
}


ShipmentTrackingTourInformationSQLMapper::~ShipmentTrackingTourInformationSQLMapper()
{
}

//----------------------------------------------------------------------------------
// Mapping Shipment Tracking Tour Information from Outbound database
//----------------------------------------------------------------------------------
void ShipmentTrackingTourInformationSQLMapper::mapShipmentTrackingTourInformationFromOutboundData(const basar::db::sql::ResultsetRef resultSet)
{
    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingTourInformationSQLMapper::mapShipmentTrackingTourInformation()", "resultSet is Null!", __FILE__, __LINE__), "");
    }

    // Do fill TourData from same resultSet:
    ShipmentTrackingTourDataSQLMapper tourDataMapper(m_TourInformation->getTourData(), resultSet);
    tourDataMapper.mapFromOutboundData();
}

//----------------------------------------------------------------------------------
// Mapping Shipment Tracking Tour Information from Warehouse database
//----------------------------------------------------------------------------------
void ShipmentTrackingTourInformationSQLMapper::mapShipmentTrackingTourInformationFromWarehouseData(ShipmentTrackingTourDataPtr redirectedToTourData)
{
    // Do fill TourData from same resultSet:
    replaceTourInformation(redirectedToTourData);
}


} // end namespace shipmenttracking
} // end namespace libcsc
