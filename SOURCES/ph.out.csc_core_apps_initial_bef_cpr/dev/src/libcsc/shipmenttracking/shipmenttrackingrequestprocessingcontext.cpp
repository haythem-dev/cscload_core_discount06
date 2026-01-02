#include "shipmenttrackingrequestprocessingcontext.h"
#include "shipmenttracking/packageinformation/shipmenttrackingtotepositiontolinebuildermapper.h"

#include <util/loggingutils.h>

#include <boost/make_shared.hpp>


namespace libcsc {
namespace shipmenttracking {

    ShipmentTrackingTotePositionToLineBuilderMapperPtr ShipmentTrackingRequestProcessingContext::getOrCreateTotePositionToLineBuilderMapperForCscOrderNo(basar::Int32 cscOrderNo)
{
    ShipmentTrackingTotePositionToLineBuilderMapperPtr totePosNoToLineBuilderMapper = getTotePositionToLineBuilderMapperForCscOrderNo(cscOrderNo);

    if (totePosNoToLineBuilderMapper.get() == NULL)
    {
        totePosNoToLineBuilderMapper = boost::make_shared<ShipmentTrackingTotePositionToLineBuilderMapper>();
        m_CscOrderNoToTotePosToLineBuilderMap[cscOrderNo] = totePosNoToLineBuilderMapper;
    }

    return totePosNoToLineBuilderMapper;
}

ShipmentTrackingTotePositionToLineBuilderMapperPtr ShipmentTrackingRequestProcessingContext::getTotePositionToLineBuilderMapperForCscOrderNo(basar::Int32 cscOrderNo)
{
    METHODNAME_DEF(ShipmentTrackingRequestProcessingContext, getTotePositionToLineBuilderMapperForCscOrderNo);

    if (cscOrderNo < 1)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "cscOrderNo < 1 !", __FILE__, __LINE__), "");
    }

    ShipmentTrackingTotePositionToLineBuilderMapperPtr totePosNoToLineBuilderMapper;

    ShipmentTrackingTotePositionToLineBuilderMapperInt32Map::iterator totePosNoToLineBuilderMapperIter = m_CscOrderNoToTotePosToLineBuilderMap.find(cscOrderNo);
    if (totePosNoToLineBuilderMapperIter != m_CscOrderNoToTotePosToLineBuilderMap.end())
    {
        totePosNoToLineBuilderMapper = totePosNoToLineBuilderMapperIter->second;
    }

    return totePosNoToLineBuilderMapper;
}



} // end namespace shipmenttracking
} // end namespace libcsc

