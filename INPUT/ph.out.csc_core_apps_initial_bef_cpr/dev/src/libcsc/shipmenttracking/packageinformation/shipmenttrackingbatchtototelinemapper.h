#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGBATCHTOTOTELINEMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGBATCHTOTOTELINEMAPPER_H

#include "shipmenttrackingbatchtototelinemapperptr.h"
#include "shipmenttrackinglinedetailptr.h"

#include <libbasar_definitions.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingBatchToToteLineMapper
{
public:
    ShipmentTrackingBatchToToteLineMapper();
    virtual ~ShipmentTrackingBatchToToteLineMapper();

    void addLineDetailForWhsMapKey(std::string whsMapKey, ShipmentTrackingLineDetailPtr lineDetail);

    ShipmentTrackingLineDetailPtr getLineDetailForWhsMapKey(std::string whsMapKey);

private:
    
    //! \brief WhsToteMapKey --> LineDetail map for one WHS batch of this splitted CscOrderPos 
    ShipmentTrackingLineDetailStrMap m_WhsToteMapKeyToLineDetailMap;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGBATCHTOTOTELINEMAPPER_H
