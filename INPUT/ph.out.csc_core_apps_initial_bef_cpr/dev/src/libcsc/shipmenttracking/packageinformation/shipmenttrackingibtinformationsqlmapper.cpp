#include "shipmenttrackingibtinformationsqlmapper.h"
#include "shipmenttrackingpackagepropertiessqlmapper.h"
#include "shipmenttracking/tourinformation/shipmenttrackingtourdatasqlmapper.h"
#include "shipmenttrackingcurrentwhslinecontext.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"
#include "shipmenttrackingibtinformation.h"
#include <libbasarcmnutil_timespan.h>
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <boost/make_shared.hpp>

namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingIbtInformationSQLMapper::ShipmentTrackingIbtInformationSQLMapper(
    ShipmentTrackingRequestProcessingContextPtr context,
    ShipmentTrackingIbtInformationPtr shipmentTrackingIbtInformation
) :
    ShipmentTrackingIbtInformationMapperBase(shipmentTrackingIbtInformation),
    m_PackagePropertiesMapper(context, m_IbtInformation->getPackageProperties(), "i")
{
}


ShipmentTrackingIbtInformationSQLMapper::~ShipmentTrackingIbtInformationSQLMapper()
{
}

void ShipmentTrackingIbtInformationSQLMapper::setResultSet(const basar::db::sql::ResultsetRef resultSet)
{
    m_ResultSet = resultSet; 
    m_PackagePropertiesMapper.setResultSet(m_ResultSet);
}

//----------------------------------------------------------------------------------
// Mapping Shipment Tracking IBT Info from Outbound Database
//----------------------------------------------------------------------------------
void ShipmentTrackingIbtInformationSQLMapper::mapFromOutboundData(basar::Int32 cscOrderNo, bool isNarcotic)
{
    if (m_ResultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingIbtInformationSQLMapper::mapFromOutboundData()", "m_ResultSet is Null!", __FILE__, __LINE__), "");
    }

    setBranchNo             (m_ResultSet.getInt16("ibtbranchno"));      // <- IBT: (a)kdauftrag.filialnr
    setCustomerNo           (m_ResultSet.getInt32("ibtcustomerno"));    // <- IBT: (a)kdauftrag.idfnr

    // Do fill PackageProperties from same m_ResultSet:
    m_PackagePropertiesMapper.mapFromOutboundData(cscOrderNo, isNarcotic);

    // Do fill TourData from same m_ResultSet:
    ShipmentTrackingTourDataSQLMapper tourDataMapper(m_IbtInformation->getTourData(), m_ResultSet, "i");
    tourDataMapper.mapFromOutboundData();
}

//----------------------------------------------------------------------------------
// Fill Clone From Outbound Data
//----------------------------------------------------------------------------------
void ShipmentTrackingIbtInformationSQLMapper::fillCloneFromOutboundData(const ShipmentTrackingIbtInformationSQLMapper& originalIbtInfoBuilder)
{
    setBranchNo             (originalIbtInfoBuilder.m_IbtInformation->getBranchNo());      // <- IBT: (a)kdauftrag.filialnr
    setCustomerNo           (originalIbtInfoBuilder.m_IbtInformation->getCustomerNo());    // <- IBT: (a)kdauftrag.idfnr

    // Do fill PackageProperties from same m_ResultSet:
    m_PackagePropertiesMapper.fillCloneFromOutboundData(originalIbtInfoBuilder.m_PackagePropertiesMapper);

    // Link to the same TourData as the original:
    setTourData(originalIbtInfoBuilder.getIbtInfoTourDataForWrite());
}

//----------------------------------------------------------------------------------
// Mapping Shipment Tracking IBT Info from Warehouse Database
//----------------------------------------------------------------------------------
void ShipmentTrackingIbtInformationSQLMapper::mapFromWarehouseData(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext)
{
    // Do fill PackageProperties from same m_ResultSet:
    m_PackagePropertiesMapper.mapFromWarehouseData(currentWhsLineContext);

    if (currentWhsLineContext->isTourRedirected() &&
        m_IbtInformation->getRedirectedToTourData().get() == NULL
        )
    {
        // handle changed Tour info:

        // Do fill TourData from same resultSet:
        ShipmentTrackingTourDataPtr redirectedToTourData = boost::make_shared<ShipmentTrackingTourData>();
        ShipmentTrackingTourDataSQLMapper redirectedToTourDataMapper(redirectedToTourData, m_ResultSet);
        redirectedToTourDataMapper.mapFromWarehouseData(m_IbtInformation->getPackageProperties()->getOrderClosedAt().getDate(), currentWhsLineContext);

        setRedirectedToTourData(redirectedToTourData);
    }
}

} // end namespace shipmenttracking
} // end namespace libcsc
