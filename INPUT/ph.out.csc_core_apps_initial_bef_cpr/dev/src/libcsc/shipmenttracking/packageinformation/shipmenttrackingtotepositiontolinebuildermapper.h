#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOTEPOSITIONTOLINEBUILDERMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOTEPOSITIONTOLINEBUILDERMAPPER_H

#include "shipmenttracking/shipmenttrackingutils.h"
#include "shipmenttrackingtotepositiontolinebuildermapperptr.h"
#include "shipmenttrackingpackageinformationsqlmapperptr.h"

#include <libbasar_definitions.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTotePositionToLineBuilderMapper
{
public:
    ShipmentTrackingTotePositionToLineBuilderMapper();
    virtual ~ShipmentTrackingTotePositionToLineBuilderMapper();

    void addTotePositionLineBuildersPackageInfo(basar::Int32 totePosNr, ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder);

    ShipmentTrackingPackageInformationSQLMapperPtr getPackageInfoBuilderForTotePosition(basar::Int32 totePosNr);

private:
    
    //! \brief parallel simple sequential list of sorted Csc Positions belonging to the article represented by object of this class.
    ShipmentTrackingPackageInformationSQLMapperInt32Map m_TotePosToPackageInfoBuilderMap;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOTEPOSITIONTOLINEBUILDERMAPPER_H
