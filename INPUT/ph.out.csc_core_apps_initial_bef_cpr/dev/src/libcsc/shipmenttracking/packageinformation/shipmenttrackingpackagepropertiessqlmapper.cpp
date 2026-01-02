#include "shipmenttrackingpackagepropertiessqlmapper.h"
#include "shipmenttrackingpackageproperties.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"
#include "shipmenttrackingcurrentwhslinecontext.h"

#include <libbasarcmnutil_timespan.h>
#include <util/loggingutils.h>

#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <boost/make_shared.hpp>

namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingPackagePropertiesSQLMapper::ShipmentTrackingPackagePropertiesSQLMapper(
    ShipmentTrackingRequestProcessingContextPtr context,
    ShipmentTrackingPackagePropertiesPtr packageProperties, 
    const basar::VarString& fieldPrefix
) :
    ShipmentTrackingPackagePropertiesMapperBase(packageProperties),
    m_Context(context),
    m_FieldPrefix(fieldPrefix)
{
}


ShipmentTrackingPackagePropertiesSQLMapper::~ShipmentTrackingPackagePropertiesSQLMapper()
{
}

//----------------------------------------------------------------------------------
// Mapping Shipment Tracking Package Properties from Outbound Database
//----------------------------------------------------------------------------------
void ShipmentTrackingPackagePropertiesSQLMapper::mapFromOutboundData(basar::Int32 cscOrderNo, bool isNarcotic)
{
    if (m_ResultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingPackagePropertiesSQLMapper::mapFromOutboundData()", "m_ResultSet is Null!", __FILE__, __LINE__), "");
    }

    setCscOrderNo           (cscOrderNo);                                   // <- (a)kdauftrag.kdauftragnr as cscOrderNo      (old: N/A)

    if (m_Context->Filter.SendPharmosOrderNumbers)
    {
        setPharmosOrderNo   (m_ResultSet.getInt32(m_FieldPrefix + "pharmosorderno"));       // <- (a)kdauftrag.kdauftragnrfiliale as pharmosOrderNo (old wrong: dktsv.tsv_kauf)
    }
    else
    {
        setPharmosOrderNo   (0);
    }

    setDeliveryAdviceNo     (m_ResultSet.getInt32(m_FieldPrefix + "deliveryadviceno"));     // <- (a)kdauftrag.rechnungnr as deliveryAdviceNo (old: N/A)

    int e11date = m_ResultSet.getInt32(m_FieldPrefix + "e11date");          // integer formatted date (YYYYMMDD)
    int e11time = m_ResultSet.getInt32(m_FieldPrefix + "e11time");          // integer formatted time (hhmmssttt)
    setOrderClosedAt        (basar::DateTime(e11date, e11time));                            // <- (a)kdauftragereignis as e11 where e11.ereignisart=11 -> e11.datum + e11.zeit

    setIsNarcotic           (isNarcotic);
    if (isNarcotic)
    {
        setPackageType      ("Narcotics");
    }
}

//----------------------------------------------------------------------------------
// Fill Clone From Outbound Data
//----------------------------------------------------------------------------------
void ShipmentTrackingPackagePropertiesSQLMapper::fillCloneFromOutboundData(const ShipmentTrackingPackagePropertiesSQLMapper& originalPackagePropertiesBuilder)
{
    const ShipmentTrackingPackagePropertiesPtr& oriPackageProps = originalPackagePropertiesBuilder.getPackageProperties();

    setCscOrderNo           (oriPackageProps->getCscOrderNo());             // <- (a)kdauftrag.kdauftragnr as cscOrderNo      (old: N/A)

    if (m_Context->Filter.SendPharmosOrderNumbers)
    {
        setPharmosOrderNo   (oriPackageProps->getPharmosOrderNo());         // <- (a)kdauftrag.kdauftragnrfiliale as pharmosOrderNo (old wrong: dktsv.tsv_kauf)
    }
    else
    {
        setPharmosOrderNo   (0);
    }

    setDeliveryAdviceNo     (oriPackageProps->getDeliveryAdviceNo());       // <- (a)kdauftrag.rechnungnr as deliveryAdviceNo (old: N/A)

    setOrderClosedAt        (oriPackageProps->getOrderClosedAt());          // <- (a)kdauftragereignis as e11 where e11.ereignisart=11 -> e11.datum + e11.zeit

    setIsNarcotic           (oriPackageProps->isNarcotic());
    setPackageType          (oriPackageProps->getPackageType());
}

//----------------------------------------------------------------------------------
// Mapping Shipment Tracking Package Properties from Warehouse Database
//----------------------------------------------------------------------------------
void ShipmentTrackingPackagePropertiesSQLMapper::mapFromWarehouseData(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext, bool updateCustomerPartFromIbtForMissingLocalIbt)
{
    METHODNAME_DEF(ShipmentTrackingPackagePropertiesSQLMapper, mapFromWarehouseData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << updateCustomerPartFromIbtForMissingLocalIbt);

    // ----------------------------------
    // Updating is done always:
    basar::DateTime insertDateTime = currentWhsLineContext->getInsertDateTime(); // <- dktsv.insertdatetime

    if (currentWhsLineContext->getToteState() == "1")       // content changed and deleted are mutually exclusive DKTSV instruction rows
    {
        // <- dktsv.tsv_status == 1 -> means "Gutschrift", i.e. some tote articles have less quantity, than confirmed in CSC Oder! One value for Normal local, IBT Remote or Local case. Picking is done just once!
        setContentChangedAt     (insertDateTime);    // <- dktsv.tsv_status == 1
    }
    else if (currentWhsLineContext->getToteState() == "9")  // content changed and deleted are mutually exclusive DKTSV instruction rows
    {
        setToteDeletedAt        (insertDateTime);   // <- dktsv.tsv_status == 9 -> Sometimes a tote gets deleted during picking. E.g. because tote is defect. Mostly, but not always the content of a deleted tote is loaded to an another tote. 
                                            //    There is just one value for Normal local, IBT Remote or Local case. Tote can be deleted just once!
    }
    
    if (!updateCustomerPartFromIbtForMissingLocalIbt &&
        currentWhsLineContext->isTourRedirected() && // redirected can be combined with "Content Changed" or with "Deleted"
        (!getPackageProperties()->getTourRedirectedAt().isValid() || getPackageProperties()->getTourRedirectedAt() > insertDateTime)
        )
    {
        setTourRedirectedAt     (insertDateTime);    // <- dktsv.tsv_status == 8
    }

    if (getPackageProperties()->hasWarehouseData())
    {
        if (!updateCustomerPartFromIbtForMissingLocalIbt)
        {
            // then just update Tote State info:
            if (getPackageProperties()->getPickingDoneAt() > insertDateTime)
            {
                // update if possible
                setPickingDoneAt(insertDateTime);   // <- dktsv.insertdatetime
            }
        }

        return;     // --> and quit!
    }

    // ----------------------------------
    // common Package Properties reading:
    setPackageId                (currentWhsLineContext->getPackageId());            // <- dktsv.tsv_wannennr == ToteNo

    setTrackingBarcode          (currentWhsLineContext->getTrackingBarcode());      // <- dktsv.tsv_vsw_tm_barcode

    if (!updateCustomerPartFromIbtForMissingLocalIbt)
    {
        setRedirectedFromTourId (currentWhsLineContext->getRedirectedFromTourId()); // <- dktsv.tsv_vsw_rtour
        setPickingDoneAt        (insertDateTime);                                   // <- dktsv.insertdatetime
    }

    bool isContainer =          currentWhsLineContext->isContainer();               // <- bitand(artikelzentral.etartklasse1, 512) = 512 / dktsv.tsv_vsw_btm 'J'/'N'
    setIsContainer              (isContainer);
    if (isContainer)
    {
        setPackageType          ("Container");
    }

    if (m_Context->Filter.SendPickingOrderNumbers)
    {
        setPickingOrderNo       (currentWhsLineContext->getPickingOrderNo());       // <- dktsv.tsv_vsw_la    == WarehouseOrderNo
        short pickingOrderPageNo = currentWhsLineContext->getPickingOrderPageNo();  // <- dktsv.tsv_vsw_seite == WarehouseOrderPageNo
        setPickingOrderPageNo   (pickingOrderPageNo);

        if (!isContainer &&
            (pickingOrderPageNo >= 70 && pickingOrderPageNo < 900) &&
            !getPackageProperties()->isNarcotic()
            )
        {
            setIsAdditionalTote (true);
            setPackageType      ("AdditionalTote");
        }
    }
    else
    {
        setPickingOrderNo       (0);
        setPickingOrderPageNo   (0);
    }

    setHasWarehouseData(true);
}


} // end namespace shipmenttracking
} // end namespace libcsc
