#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGARTICLETOPOSITIONMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGARTICLETOPOSITIONMAPPER_H

#include "shipmenttracking/shipmenttrackingutils.h"
#include "shipmenttrackingarticletopositionmapperptr.h"

#include <libbasar_definitions.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingArticleToPositionMapper
{
public:
    ShipmentTrackingArticleToPositionMapper();
    virtual ~ShipmentTrackingArticleToPositionMapper();

    void addPositionWithQuantity(basar::Int32 posNr, basar::Int32 expectedQuantity);

    basar::Int32 extractPositionForQuantity(basar::Int32 expectedQuantity, Int32ToInt32MapPtr allowedPositionsMap = Int32ToInt32MapPtr());

    size_t getSize() { return m_PosNrs.size(); }

private:
    
    //! \brief Parallel simple sequential list of sorted Csc Positions belonging to the article represented by object of this class.
    Int32List m_PosNrs;

    //! \brief parallel simple sequential list of Expected Quantities corresponding to the Csc Positions and belonging to the article represented by object of this class.
    Int32List m_ExpectedQuantities;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGARTICLETOPOSITIONMAPPER_H
