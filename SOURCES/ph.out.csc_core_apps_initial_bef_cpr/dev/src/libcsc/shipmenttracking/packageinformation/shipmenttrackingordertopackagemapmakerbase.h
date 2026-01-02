#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGORDERTOPACKAGEMAPMAKERBASE_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGORDERTOPACKAGEMAPMAKERBASE_H

#include "shipmenttrackingordertopackagemapmakerbaseptr.h"
#include "shipmenttrackingcurrentwhslinecontextptr.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontextptr.h"
#include "shipmenttrackingpackageinformationsqlmapperptr.h"
#include "shipmenttrackinglinedetailsqlmapperptr.h"

#include <libbasar_definitions.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingOrderToPackageMapMakerBase
{
public:
    virtual ~ShipmentTrackingOrderToPackageMapMakerBase();

    void extractAndUpdateNextLineDetail(
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    );

protected:
    ShipmentTrackingOrderToPackageMapMakerBase(ShipmentTrackingRequestProcessingContextPtr context);

    virtual ShipmentTrackingPackageInformationSQLMapperPtr getOutboundPackageInfoBuilderTemplate(
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    ) = 0;
    
    virtual void registerNewWhsPackageInfoBuilder(
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    ) = 0;

    virtual void extractOneOutboundArticleLineAndRemoveFromTourIfEmpty(
        ShipmentTrackingPackageInformationSQLMapperPtr outboundPackageInfoBuilderTemplate,
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    ) = 0;


    //! \brief Request Processing Context info, like User's choice, server file config data, etc.
    ShipmentTrackingRequestProcessingContextPtr             m_Context;

private:

    //! \brief Try to get a registered lineDetaBuilder from another tote for a case, current CscOrderPos is splitted to more than one tote
    void tryToGetAndRegisterToteSplittedLineDataBuilder(
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    );

};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGORDERTOPACKAGEMAPMAKERBASE_H
