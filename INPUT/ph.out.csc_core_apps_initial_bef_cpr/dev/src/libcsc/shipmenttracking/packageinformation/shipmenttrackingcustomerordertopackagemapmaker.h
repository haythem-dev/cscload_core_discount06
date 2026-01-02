#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGCUSTOMERORDERTOPACKAGEMAPMAKER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGCUSTOMERORDERTOPACKAGEMAPMAKER_H

#include "shipmenttrackingcustomerordertopackagemapmakerptr.h"
#include "shipmenttrackingordertopackagemapmakerbase.h"
#include "shipmenttrackingibtordertopackagemapmakerptr.h"
#include "shipmenttrackingpackageinformationsqlmapperptr.h"
#include "shipmenttrackinglinedetailsqlmapperptr.h"

#include <libbasar_definitions.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingCustomerOrderToPackageMapMaker : public ShipmentTrackingOrderToPackageMapMakerBase
{
public:
    ShipmentTrackingCustomerOrderToPackageMapMaker(ShipmentTrackingRequestProcessingContextPtr context);
    virtual ~ShipmentTrackingCustomerOrderToPackageMapMaker();

    void linkNewIbtOrderToPackageMapMaker(
        basar::Int32 ibtCscOrderNo,
        ShipmentTrackingIbtOrderToPackageMapMakerPtr ibtOrderToPackageMapMaker
    );

    void addLineToPackageMapping(
        ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder, 
        ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder
    );

    ShipmentTrackingPackageInformationSQLMapperPtr createIbtLocalWhsPackageInfo(basar::Int32 customerCscOrderNo, bool isNarcotic);

protected:

    virtual ShipmentTrackingPackageInformationSQLMapperPtr getOutboundPackageInfoBuilderTemplate(
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    );

    virtual void registerNewWhsPackageInfoBuilder(
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    );

    virtual void extractOneOutboundArticleLineAndRemoveFromTourIfEmpty(
        ShipmentTrackingPackageInformationSQLMapperPtr outboundPackageInfoBuilderTemplate,
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    );

private:

    //! \brief NOTE: unidirectional link: ibtCscOrderNo --> IbtOrderToPackageMapMaker
    ShipmentTrackingIbtOrderToPackageMapMakerInt32Map  m_IbtOrderToPackageMapMakerMap;

    //! \brief ArticleNr --> ShipmentTrackingPackageInformationSQLMapper
    ShipmentTrackingPackageInformationSQLMapperInt32Map  m_LocalPackageInfoBuilderMap;
};


} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGCUSTOMERORDERTOPACKAGEMAPMAKER_H
