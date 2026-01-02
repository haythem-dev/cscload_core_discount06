#include "shipmenttrackingtotepositiontolinebuildermapper.h"

#include <util/loggingutils.h>

namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingTotePositionToLineBuilderMapper::ShipmentTrackingTotePositionToLineBuilderMapper()
{
}


ShipmentTrackingTotePositionToLineBuilderMapper::~ShipmentTrackingTotePositionToLineBuilderMapper()
{
}

void ShipmentTrackingTotePositionToLineBuilderMapper::addTotePositionLineBuildersPackageInfo(basar::Int32 totePosNr, ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder)
{
    METHODNAME_DEF(ShipmentTrackingTotePositionToLineBuilderMapper, addTotePositionLineBuildersPackageInfo);

    if (totePosNr < 1)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "totePosNr < 1 !", __FILE__, __LINE__), "");
    }
    if (packageInfoBuilder.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "packageInfoBuilder is Null!", __FILE__, __LINE__), "");
    }

    m_TotePosToPackageInfoBuilderMap[totePosNr] = packageInfoBuilder;
}

ShipmentTrackingPackageInformationSQLMapperPtr ShipmentTrackingTotePositionToLineBuilderMapper::getPackageInfoBuilderForTotePosition(basar::Int32 totePosNr)
{
    METHODNAME_DEF(ShipmentTrackingTotePositionToLineBuilderMapper, getPackageInfoBuilderForTotePosition);

    if (totePosNr < 1)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "totePosNr < 1 !", __FILE__, __LINE__), "");
    }

    ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder;

    ShipmentTrackingPackageInformationSQLMapperInt32Map::iterator packageInfoBuilderIter = m_TotePosToPackageInfoBuilderMap.find(totePosNr);
    if (packageInfoBuilderIter != m_TotePosToPackageInfoBuilderMap.end())
    {
        packageInfoBuilder = packageInfoBuilderIter->second;
    }

    return packageInfoBuilder;
}


} // end namespace shipmenttracking
} // end namespace libcsc

