#include "shipmenttrackingarticletopositionmapper.h"
#include "shipmenttrackinglinedetailsqlmapper.h"

#include <util/loggingutils.h>

namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingArticleToPositionMapper::ShipmentTrackingArticleToPositionMapper()
{
}


ShipmentTrackingArticleToPositionMapper::~ShipmentTrackingArticleToPositionMapper()
{
}

void ShipmentTrackingArticleToPositionMapper::addPositionWithQuantity(basar::Int32 posNr, basar::Int32 expectedQuantity)
{
    // storing in the 2 parallel lists:
    m_PosNrs.push_back(posNr);
    m_ExpectedQuantities.push_back(expectedQuantity);
}

basar::Int32 ShipmentTrackingArticleToPositionMapper::extractPositionForQuantity(basar::Int32 expectedQuantity, Int32ToInt32MapPtr allowedPositionsMap)
{
    METHODNAME_DEF(ShipmentTrackingArticleToPositionMapper, extractPositionForQuantity);

    // Here I implement following algorthm in a very simple way:
    // ...

    // take just the 1st with the same ExpectedDeliveryQuantity (NVL(ibtresponse.ibtconfirmedqty, (a)kdauftragpos.mengegeliefert)) == whsOriginalQuantity (dktsv.tsv_kop_omenge),
    // or, if not found => take just the first one:

    Int32List::iterator foundPosNrIt = m_PosNrs.end();
    Int32List::iterator foundExpectedQuantityIt = m_ExpectedQuantities.end();

    for (Int32List::iterator posNrIt = m_PosNrs.begin(), expectedQuantityIt = m_ExpectedQuantities.begin();
        posNrIt != m_PosNrs.end() && expectedQuantityIt != m_ExpectedQuantities.end();
        posNrIt++, expectedQuantityIt++
        )
    {
        if (allowedPositionsMap.get() != NULL &&
            allowedPositionsMap->find(*posNrIt) == allowedPositionsMap->end()
            )
        {
            // if the hit position does not belong to the allowed positions --> skip it
            continue;
        }

        // handling fallback:
        if (foundPosNrIt == m_PosNrs.end())
        {
            foundPosNrIt = posNrIt;
            foundExpectedQuantityIt = expectedQuantityIt;
        }

        // the normal algortithm - take the 1st match:
        if (*expectedQuantityIt == expectedQuantity)
        {
            foundPosNrIt = posNrIt;
            foundExpectedQuantityIt = expectedQuantityIt;
            break;
        }
    }

    if (foundPosNrIt == m_PosNrs.end())
    {
        // Don't throw, report and just continue:
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO LineDetailBuilder Position to use found for expectedQuantity: " << expectedQuantity << " filter used: " << (allowedPositionsMap.get() != NULL));

        return 0;
    }

    // extract the chosen position for further use, i.e. 
    // store the posNr value:
    basar::Int32 chosenPosNr = *foundPosNrIt;

    // remove the chosen one from the lists:
    m_PosNrs.erase(foundPosNrIt);
    m_ExpectedQuantities.erase(foundExpectedQuantityIt);

    // return the chosen posNr:
    return chosenPosNr;
}


} // end namespace shipmenttracking
} // end namespace libcsc

