#include "shipmenttrackingcustomerordertopackagemapmaker.h"
#include "shipmenttrackingibtordertopackagemapmaker.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"
#include "shipmenttrackingcurrentwhslinecontext.h"
#include "shipmenttrackingpackageinformationsqlmapper.h"
#include "shipmenttrackinglinedetailsqlmapper.h"

#include <util/loggingutils.h>

namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingCustomerOrderToPackageMapMaker::ShipmentTrackingCustomerOrderToPackageMapMaker(ShipmentTrackingRequestProcessingContextPtr context) :
    ShipmentTrackingOrderToPackageMapMakerBase(context)
{
}


ShipmentTrackingCustomerOrderToPackageMapMaker::~ShipmentTrackingCustomerOrderToPackageMapMaker()
{
}

//----------------------------------------------------------------------------------
// Mapping Data from Outbound Database
//----------------------------------------------------------------------------------
void ShipmentTrackingCustomerOrderToPackageMapMaker::linkNewIbtOrderToPackageMapMaker(
    basar::Int32 ibtCscOrderNo,
    ShipmentTrackingIbtOrderToPackageMapMakerPtr ibtOrderToPackageMapMaker
)
{
    m_IbtOrderToPackageMapMakerMap[ibtCscOrderNo] = ibtOrderToPackageMapMaker;
}

//----------------------------------------------------------------------------------
// Add Line to Package Mapping
//----------------------------------------------------------------------------------
void ShipmentTrackingCustomerOrderToPackageMapMaker::addLineToPackageMapping(
    ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder,
    ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder
)
{
    METHODNAME_DEF(ShipmentTrackingCustomerOrderToPackageMapMaker, addLineToPackageMapping);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // if the TnT requesting user does not want any detials, then there is NO LineDetail!
    basar::Int32 articleNr = 0;

    if (lineDetailBuilder.get() != NULL)
    {
        articleNr = lineDetailBuilder->getLineDetail()->getArticleNr();
    }
    else if (packageInfoBuilder->getPackageInformation()->getPackageProperties()->isNarcotic())
    {
        articleNr = 1;
    }

    m_LocalPackageInfoBuilderMap[articleNr] = packageInfoBuilder;
}


//----------------------------------------------------------------------------------
// Mapping Data from Warehouse Database
//----------------------------------------------------------------------------------
ShipmentTrackingPackageInformationSQLMapperPtr ShipmentTrackingCustomerOrderToPackageMapMaker::createIbtLocalWhsPackageInfo(basar::Int32 customerCscOrderNo, bool isNarcotic)
{
    METHODNAME_DEF(ShipmentTrackingCustomerOrderToPackageMapMaker, createIbtLocalWhsPackageInfo);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << customerCscOrderNo << ", " << isNarcotic);

    ShipmentTrackingPackageInformationSQLMapperPtr whsPackageInfoBuilder;

    if (m_IbtOrderToPackageMapMakerMap.size() < 1)
    {
        // Don't throw, report and just continue:
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO m_IbtOrderToPackageMapMakerMap found! customerCscOrderNo: " << customerCscOrderNo);
        return whsPackageInfoBuilder;
    }

    // it does not matter which outboundPackageInfoBuilder we take. This Customer-CscOrderNo is tour purified, and we copy it without Lines and IbtInfo!
    for (ShipmentTrackingIbtOrderToPackageMapMakerInt32Map::const_iterator ibtOrderToPackageMapMakerIter = m_IbtOrderToPackageMapMakerMap.begin();
        ibtOrderToPackageMapMakerIter != m_IbtOrderToPackageMapMakerMap.end();
        ibtOrderToPackageMapMakerIter++
        )
    {
        ShipmentTrackingPackageInformationSQLMapperPtr outboundPackageInfoBuilderTemplate = ibtOrderToPackageMapMakerIter->second->getAnyPackageInfoBuilderForCustomerCscOrderNo(customerCscOrderNo, isNarcotic);

        // ... just take first found match:
        if (outboundPackageInfoBuilderTemplate.get() != NULL)
        {
            whsPackageInfoBuilder = outboundPackageInfoBuilderTemplate->createCloneWithTighlyConnectedDataButWithoutLinesAndIbt();
            //NOTE: !! DO NOT do: outboundPackageInfoBuilderTemplate->removePackageFromTourInformationIfEmtpty();

            return whsPackageInfoBuilder;
        }
    }

    // ERROR: Don't throw, report and just continue:
    LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO IBT Local packageInfoBuilder found for customerCscOrderNo: " << customerCscOrderNo << ", " << isNarcotic);

    return whsPackageInfoBuilder;
}

//----------------------------------------------------------------------------------
// Extract and Update Next Line Detail -> getOutboundPackageInfoBuilderTemplate
//----------------------------------------------------------------------------------
ShipmentTrackingPackageInformationSQLMapperPtr ShipmentTrackingCustomerOrderToPackageMapMaker::getOutboundPackageInfoBuilderTemplate(
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingCustomerOrderToPackageMapMaker, getOutboundPackageInfoBuilderTemplate);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    basar::Int32 articleNo = currentWhsLineContext->getArticleNr();
    ShipmentTrackingPackageInformationSQLMapperInt32Map::iterator outboundPackageInfoBuilderTemplateIter = m_LocalPackageInfoBuilderMap.find(articleNo);
    if (outboundPackageInfoBuilderTemplateIter == m_LocalPackageInfoBuilderMap.end())
    {
        if (!m_Context->Filter.DetailsDesired)
        {
            articleNo = articleNo == 1? 0   // make 0 from 1 ==> Redirecting in a bad case, where Outbound says NOT NARCOTIC, but WHS Says: YES Narcotic!
                : articleNo == 0? 1         // make 1 from 0 ==> Redirecting in a bad case, where Outbound says YES NARCOTIC, but WHS Says: NOT Narcotic!
                    : articleNo;            // HUH?! ==> just let this fail again....

            outboundPackageInfoBuilderTemplateIter = m_LocalPackageInfoBuilderMap.find(articleNo);
        }

        if (outboundPackageInfoBuilderTemplateIter == m_LocalPackageInfoBuilderMap.end())
        {
            // Don't throw, report and just continue:
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO ToteOutboundTemplate found in m_LocalPackageInfoBuilderMap for articleNr: " << currentWhsLineContext);
            return ShipmentTrackingPackageInformationSQLMapperPtr();
        }
        else
        {
            LOG4CPLUS_WARN(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected But Redirected! NO ToteOutboundTemplate found in m_LocalPackageInfoBuilderMap for articleNr: " << currentWhsLineContext);
        }
    }

    ShipmentTrackingPackageInformationSQLMapperPtr outboundPackageInfoBuilderTemplate = outboundPackageInfoBuilderTemplateIter->second;

    return outboundPackageInfoBuilderTemplate;
}

//----------------------------------------------------------------------------------
// registerNewWhsPackageInfoBuilder
//----------------------------------------------------------------------------------
void ShipmentTrackingCustomerOrderToPackageMapMaker::registerNewWhsPackageInfoBuilder(
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingCustomerOrderToPackageMapMaker, registerNewWhsPackageInfoBuilder);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << currentWhsLineContext->getCscOrderNo());
}

//----------------------------------------------------------------------------------
// Extract and Update Next Line Detail -> extractOneOutboundArticleLineAndRemoveFromTourIfEmpty
//----------------------------------------------------------------------------------
void ShipmentTrackingCustomerOrderToPackageMapMaker::extractOneOutboundArticleLineAndRemoveFromTourIfEmpty(
    ShipmentTrackingPackageInformationSQLMapperPtr outboundPackageInfoBuilderTemplate,
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingCustomerOrderToPackageMapMaker, extractOneOutboundArticleLineAndRemoveFromTourIfEmpty);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    currentWhsLineContext->setLineDetailBuilder(
        outboundPackageInfoBuilderTemplate->extractOneOutboundArticleLineAndRemoveFromTourIfEmpty(
            currentWhsLineContext->getArticleNr(),
            currentWhsLineContext->getWhsOriginalQuantity()
        )
    );
}



} // end namespace shipmenttracking
} // end namespace libcsc

