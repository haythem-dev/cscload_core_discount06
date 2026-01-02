#include "shipmenttrackingbatchtototelinemapper.h"
#include "shipmenttrackinglinedetail.h"

#include <util/loggingutils.h>

namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingBatchToToteLineMapper::ShipmentTrackingBatchToToteLineMapper()
{
}


ShipmentTrackingBatchToToteLineMapper::~ShipmentTrackingBatchToToteLineMapper()
{
}

void ShipmentTrackingBatchToToteLineMapper::addLineDetailForWhsMapKey(std::string whsMapKey, ShipmentTrackingLineDetailPtr lineDetail)
{
    METHODNAME_DEF(ShipmentTrackingBatchToToteLineMapper, addLineDetailForWhsMapKey);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << whsMapKey);

    if (whsMapKey.size() < 1)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "whsMapKey is empty!", __FILE__, __LINE__), "");
    }
    if (lineDetail.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "lineDetail is Null!", __FILE__, __LINE__), "");
    }

    m_WhsToteMapKeyToLineDetailMap[whsMapKey] = lineDetail;
}

ShipmentTrackingLineDetailPtr ShipmentTrackingBatchToToteLineMapper::getLineDetailForWhsMapKey(std::string whsMapKey)
{
    METHODNAME_DEF(ShipmentTrackingBatchToToteLineMapper, getLineDetailForWhsMapKey);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << whsMapKey);

    if (whsMapKey.size() < 1)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "whsMapKey is empty!", __FILE__, __LINE__), "");
    }

    ShipmentTrackingLineDetailPtr lineDetail;

    ShipmentTrackingLineDetailStrMap::iterator lineDetailIter = m_WhsToteMapKeyToLineDetailMap.find(whsMapKey);
    if (lineDetailIter != m_WhsToteMapKeyToLineDetailMap.end())
    {
        lineDetail = lineDetailIter->second;
    }

    return lineDetail;
}


} // end namespace shipmenttracking
} // end namespace libcsc

