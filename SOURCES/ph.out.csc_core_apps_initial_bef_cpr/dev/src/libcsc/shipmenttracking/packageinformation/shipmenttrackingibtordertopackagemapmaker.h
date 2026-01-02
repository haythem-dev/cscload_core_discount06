#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTORDERTOPACKAGEMAPMAKER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTORDERTOPACKAGEMAPMAKER_H

#include "shipmenttrackingibtordertopackagemapmakerptr.h"
#include "shipmenttrackingordertopackagemapmakerbase.h"
#include "shipmenttrackingarticletopositionmapperptr.h"

#include <libbasar_definitions.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingIbtOrderToPackageMapMaker : public ShipmentTrackingOrderToPackageMapMakerBase
{
public:
    ShipmentTrackingIbtOrderToPackageMapMaker(ShipmentTrackingRequestProcessingContextPtr context);
    virtual ~ShipmentTrackingIbtOrderToPackageMapMaker();

    void addLineToPackageMapping(
        ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder, 
        ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder
    );

    ShipmentTrackingPackageInformationSQLMapperPtr getAnyPackageInfoBuilderForCustomerCscOrderNo(basar::Int32 customerCscOrderNo, bool isNarcotic);

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
    void extractIbtOrderPosNrForQuantity(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext);


    //! \brief ArticleNr --> PackageInfoBuilder
    ShipmentTrackingArticleToPositionMapperInt32Map         m_ArticleToPositionMapperMap;

    //! \brief IBT-CscPosNr --> PackageInfoBuilder
    ShipmentTrackingPackageInformationSQLMapperInt32Map     m_IbtCscPositionToPackageInfoBuilderMap;

    //! \brief CustomerCscOrderNo --> Outbound Template PackageInfoBuilder - NOTE: helper for Normal IBT Local Records (KZLK=V) linked m_CustomerOrderToPackageMapMakerMap.
    ShipmentTrackingPackageInformationSQLMapperInt32Map     m_CustomerCscOrderNoNormalToOutboundPackageInfoBuilderMap;

    //! \brief CustomerCscOrderNo --> Outbound Template PackageInfoBuilder - NOTE: helper for Narcotic IBT Local Records (KZLK=V) linked m_CustomerOrderToPackageMapMakerMap.
    ShipmentTrackingPackageInformationSQLMapperInt32Map     m_CustomerCscOrderNoNarcoticToOutboundPackageInfoBuilderMap;

    //! \brief CustomerCscOrderNo --> concrete WHS Tote PackageInfoBuilder - NOTE: helper for Normal IBT Remote Records (KZLK in (L,V) AND TSV_VSW_VBFIL > 0) linked m_CustomerOrderToPackageMapMakerMap.
    ShipmentTrackingPackageInformationSQLMapperInt32Map     m_CustomerCscOrderNoNormalToWhsPackageInfoBuilderMap;

    //! \brief CustomerCscOrderNo --> concrete WHS Tote PackageInfoBuilder - NOTE: helper for Narcotic IBT Remote Records (KZLK in (L,V) AND TSV_VSW_VBFIL > 0) linked m_CustomerOrderToPackageMapMakerMap.
    ShipmentTrackingPackageInformationSQLMapperInt32Map     m_CustomerCscOrderNoNarcoticToWhsPackageInfoBuilderMap;

};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTORDERTOPACKAGEMAPMAKER_H
