#include "shipmenttrackingibtordertopackagemapmaker.h"
#include "shipmenttrackingcustomerordertopackagemapmaker.h"
#include "shipmenttrackingcurrentwhslinecontext.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"
#include "shipmenttrackingarticletopositionmapper.h"
#include "shipmenttrackingpackageinformationsqlmapper.h"

#include <util/loggingutils.h>

#include <boost/make_shared.hpp>

namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingIbtOrderToPackageMapMaker::ShipmentTrackingIbtOrderToPackageMapMaker(ShipmentTrackingRequestProcessingContextPtr context) :
    ShipmentTrackingOrderToPackageMapMakerBase(context)
{
}


ShipmentTrackingIbtOrderToPackageMapMaker::~ShipmentTrackingIbtOrderToPackageMapMaker()
{
}

//----------------------------------------------------------------------------------
// Mapping Data from Outbound Database
//----------------------------------------------------------------------------------
void ShipmentTrackingIbtOrderToPackageMapMaker::addLineToPackageMapping(
    ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder,
    ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder
)
{
    METHODNAME_DEF(ShipmentTrackingIbtOrderToPackageMapMaker, addLineToPackageMapping);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    basar::Int32 customerCscOrderNo = packageInfoBuilder->getPackageInformation()->getPackageProperties()->getCscOrderNo();

    // if the TnT requesting user does not want any detials, then there is NO LineDetail!
    if (lineDetailBuilder.get() == NULL)
    {
        //NOTE: not stoting anything to: m_ArticleToPositionMapperMap and m_IbtCscPositionToPackageInfoBuilderMap
    }
    else
    {
        basar::Int32 articleNr = lineDetailBuilder->getLineDetail()->getArticleNr();

        ShipmentTrackingArticleToPositionMapperPtr articleToPositionMapper;
        ShipmentTrackingArticleToPositionMapperInt32Map::iterator previousArticleToPositionMapperIter = m_ArticleToPositionMapperMap.find(articleNr);

        if (previousArticleToPositionMapperIter != m_ArticleToPositionMapperMap.end())
        {
            articleToPositionMapper = previousArticleToPositionMapperIter->second;
        }
        else
        {
            articleToPositionMapper = boost::make_shared<ShipmentTrackingArticleToPositionMapper>();
            m_ArticleToPositionMapperMap[articleNr] = articleToPositionMapper;
        }

        basar::Int32 ibtOrderPosNr = lineDetailBuilder->getLineDetail()->getIbtOrderPosNo();
        basar::Int32 expectedDeliveryQuantity = lineDetailBuilder->getLineDetail()->getExpectedDeliveryQuantity();

        //NOTE: we store here the positions in a SQL sorted sequence and this is important, because the OrderPosNr and WHS-TotePosNo are closely related. See the comparison: "201123-KscPosNr~=TSV_Pos"
        articleToPositionMapper->addPositionWithQuantity(ibtOrderPosNr, expectedDeliveryQuantity);

        // Store the new PackageInfoBuilder for the IBT CscPosNr:
        m_IbtCscPositionToPackageInfoBuilderMap[ibtOrderPosNr] = packageInfoBuilder;
    }

    if (packageInfoBuilder->getPackageInformation()->getPackageProperties()->isNarcotic())
    {
        m_CustomerCscOrderNoNarcoticToOutboundPackageInfoBuilderMap[customerCscOrderNo] = packageInfoBuilder;
        m_CustomerCscOrderNoNarcoticToWhsPackageInfoBuilderMap[customerCscOrderNo] = ShipmentTrackingPackageInformationSQLMapperPtr();  // initialization to NULL Ptr
    }
    else
    {
        m_CustomerCscOrderNoNormalToOutboundPackageInfoBuilderMap[customerCscOrderNo] = packageInfoBuilder;
        m_CustomerCscOrderNoNormalToWhsPackageInfoBuilderMap[customerCscOrderNo] = ShipmentTrackingPackageInformationSQLMapperPtr();    // initialization to NULL Ptr
    }
}

//----------------------------------------------------------------------------------
// Mapping Data from Warehouse Database
//----------------------------------------------------------------------------------
ShipmentTrackingPackageInformationSQLMapperPtr ShipmentTrackingIbtOrderToPackageMapMaker::getAnyPackageInfoBuilderForCustomerCscOrderNo(basar::Int32 customerCscOrderNo, bool isNarcotic)
{
    METHODNAME_DEF(ShipmentTrackingIbtOrderToPackageMapMaker, getAnyPackageInfoBuilderForCustomerCscOrderNo);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << customerCscOrderNo << ", " << isNarcotic);

    ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder;

    if (isNarcotic)
    {
        ShipmentTrackingPackageInformationSQLMapperInt32Map::iterator packageInfoBuilderIter = m_CustomerCscOrderNoNarcoticToOutboundPackageInfoBuilderMap.find(customerCscOrderNo);

        if (packageInfoBuilderIter != m_CustomerCscOrderNoNarcoticToOutboundPackageInfoBuilderMap.end())
        {
            packageInfoBuilder = packageInfoBuilderIter->second;
        }
    }
    else
    {
        ShipmentTrackingPackageInformationSQLMapperInt32Map::iterator packageInfoBuilderIter = m_CustomerCscOrderNoNormalToOutboundPackageInfoBuilderMap.find(customerCscOrderNo);

        if (packageInfoBuilderIter != m_CustomerCscOrderNoNormalToOutboundPackageInfoBuilderMap.end())
        {
            packageInfoBuilder = packageInfoBuilderIter->second;
        }
    }

    return packageInfoBuilder;
}

//----------------------------------------------------------------------------------
// Extract and Update Next Line Detail -> getOutboundPackageInfoBuilderTemplate
//----------------------------------------------------------------------------------
ShipmentTrackingPackageInformationSQLMapperPtr ShipmentTrackingIbtOrderToPackageMapMaker::getOutboundPackageInfoBuilderTemplate(
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingIbtOrderToPackageMapMaker, getOutboundPackageInfoBuilderTemplate);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    ShipmentTrackingPackageInformationSQLMapperPtr outboundPackageInfoBuilderTemplate;

    // ---------------------------
    // Handling Packages with LineDetails:
    if (m_Context->Filter.DetailsDesired)
    {
        // Extract Line -> need to extract one fresh and for WHS yet unused outbound line and fill it with WHS data for the first time...
        extractIbtOrderPosNrForQuantity(currentWhsLineContext);
        if (currentWhsLineContext->getIbtOrderPosNr() < 0)
        {
            // Don't throw, error is already reported. Just continue:
            return ShipmentTrackingPackageInformationSQLMapperPtr();
        }

        ShipmentTrackingPackageInformationSQLMapperInt32Map::iterator outboundPackageInfoBuilderTemplateIter = m_IbtCscPositionToPackageInfoBuilderMap.find(currentWhsLineContext->getIbtOrderPosNr());
        if (outboundPackageInfoBuilderTemplateIter == m_IbtCscPositionToPackageInfoBuilderMap.end())
        {
            // Don't throw, report and just continue:
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO ToteOutboundTemplate found in m_IbtCscPositionToPackageInfoBuilderMap for DetailsDesired ibtOrderPosNr: " << currentWhsLineContext);
            return outboundPackageInfoBuilderTemplate;
        }

        outboundPackageInfoBuilderTemplate = outboundPackageInfoBuilderTemplateIter->second;
    }
    // ---------------------------
    // Handling No-Details && currentWhsLineContext == IBT Remote tote && currentWhsLineContext->getWhsPackageInfoBuilder() is IBT Local Package
    else if (currentWhsLineContext->getWhsPackageInfoBuilder().get() != NULL)
    {
        //NOTE: the currentWhsLineContext->getWhsPackageInfoBuilder() is IBT Local Package

        registerNewWhsPackageInfoBuilder(currentWhsLineContext);
        
        basar::Int32 customerCscOrderNo = currentWhsLineContext->getWhsPackageInfoBuilder()->getPackageInformation()->getPackageProperties()->getCscOrderNo();
        if (currentWhsLineContext->isNarcotic())
        {
            ShipmentTrackingPackageInformationSQLMapperInt32Map::iterator outboundPackageInfoBuilderTemplateIter = m_CustomerCscOrderNoNarcoticToOutboundPackageInfoBuilderMap.find(customerCscOrderNo);
            if (outboundPackageInfoBuilderTemplateIter != m_CustomerCscOrderNoNarcoticToOutboundPackageInfoBuilderMap.end())
            {
                outboundPackageInfoBuilderTemplate = outboundPackageInfoBuilderTemplateIter->second;
            }
        }
        else
        {
            ShipmentTrackingPackageInformationSQLMapperInt32Map::iterator outboundPackageInfoBuilderTemplateIter = m_CustomerCscOrderNoNormalToOutboundPackageInfoBuilderMap.find(customerCscOrderNo);
            if (outboundPackageInfoBuilderTemplateIter != m_CustomerCscOrderNoNormalToOutboundPackageInfoBuilderMap.end())
            {
                outboundPackageInfoBuilderTemplate = outboundPackageInfoBuilderTemplateIter->second;
            }
        }

        if (outboundPackageInfoBuilderTemplate.get() == NULL)
        {
            // Don't throw, report and just continue:
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO ToteOutboundTemplate found in m_IbtCscPositionToPackageInfoBuilderMap for IBT Remote & Local: " << currentWhsLineContext);
            return outboundPackageInfoBuilderTemplate;
        }
    }
    // ---------------------------
    // Handling No-Details && currentWhsLineContext == IBT Remote tote && currentWhsLineContext->getWhsPackageInfoBuilder() is NULL ==> IBT Local Package is missing!
    else
    {
        // if here, then we have a IBT Remote tote in currentWhsLineContext, and there was NO IBT Local tote for this Tote!
        // So, find first free, or take defaut -> the first one available outboundPackageInfoBuilderTemplate:

        if (currentWhsLineContext->isNarcotic())
        {
            for (ShipmentTrackingPackageInformationSQLMapperInt32Map::const_iterator 
                outboundPackageInfoBuilderTemplateIter = m_CustomerCscOrderNoNarcoticToOutboundPackageInfoBuilderMap.begin(),
                whsPackageInfoBuilderTemplateIter = m_CustomerCscOrderNoNarcoticToWhsPackageInfoBuilderMap.begin()
                ;
                outboundPackageInfoBuilderTemplateIter != m_CustomerCscOrderNoNarcoticToOutboundPackageInfoBuilderMap.end() &&
                whsPackageInfoBuilderTemplateIter != m_CustomerCscOrderNoNarcoticToWhsPackageInfoBuilderMap.end()
                ;
                outboundPackageInfoBuilderTemplateIter++,
                whsPackageInfoBuilderTemplateIter++
                )
            {
                if (outboundPackageInfoBuilderTemplate.get() == NULL)
                {
                    // store the fallback default:
                    outboundPackageInfoBuilderTemplate = outboundPackageInfoBuilderTemplateIter->second;
                }

                if (whsPackageInfoBuilderTemplateIter->second.get() == NULL)
                {
                    // take first free one:
                    outboundPackageInfoBuilderTemplate = outboundPackageInfoBuilderTemplateIter->second;
                    break;
                }
            }
        }
        else
        {
            for (ShipmentTrackingPackageInformationSQLMapperInt32Map::const_iterator
                outboundPackageInfoBuilderTemplateIter = m_CustomerCscOrderNoNormalToOutboundPackageInfoBuilderMap.begin(),
                whsPackageInfoBuilderTemplateIter = m_CustomerCscOrderNoNormalToWhsPackageInfoBuilderMap.begin()
                ;
                outboundPackageInfoBuilderTemplateIter != m_CustomerCscOrderNoNormalToOutboundPackageInfoBuilderMap.end() &&
                whsPackageInfoBuilderTemplateIter != m_CustomerCscOrderNoNormalToWhsPackageInfoBuilderMap.end()
                ;
                outboundPackageInfoBuilderTemplateIter++,
                whsPackageInfoBuilderTemplateIter++
                )
            {
                if (outboundPackageInfoBuilderTemplate.get() == NULL)
                {
                    // store the fallback default:
                    outboundPackageInfoBuilderTemplate = outboundPackageInfoBuilderTemplateIter->second;
                }

                if (whsPackageInfoBuilderTemplateIter->second.get() == NULL)
                {
                    // take first free one:
                    outboundPackageInfoBuilderTemplate = outboundPackageInfoBuilderTemplateIter->second;
                    break;
                }
            }
        }

        if (outboundPackageInfoBuilderTemplate.get() == NULL)
        {
            // Don't throw, report and just continue:
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO ToteOutboundTemplate found in m_IbtCscPositionToPackageInfoBuilderMap for IBT Remote only: " << currentWhsLineContext);
            return outboundPackageInfoBuilderTemplate;
        }
    }

    // -------
    // Add IBT, if missing yet
    if (currentWhsLineContext->getWhsPackageInfoBuilder().get() != NULL &&
        currentWhsLineContext->getWhsPackageInfoBuilder()->getPackageInformation()->getIbtInformation().get() == NULL
        )
    {
        // We must now copy an appropriate IBT Info for the IBT Local Package KZLK = V;
        currentWhsLineContext->getWhsPackageInfoBuilder()->addIbtCloneFromOutboundData(*outboundPackageInfoBuilderTemplate.get());

        if (!m_Context->Filter.DetailsDesired)
        {
            outboundPackageInfoBuilderTemplate->removePackageFromTourInformationIfEmtpty();
        }
    }

    return outboundPackageInfoBuilderTemplate;
}

//----------------------------------------------------------------------------------
// registerNewWhsPackageInfoBuilder
//----------------------------------------------------------------------------------
void ShipmentTrackingIbtOrderToPackageMapMaker::registerNewWhsPackageInfoBuilder(
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingIbtOrderToPackageMapMaker, registerNewWhsPackageInfoBuilder);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    basar::Int32 customerCscOrderNo = currentWhsLineContext->getWhsPackageInfoBuilder()->getPackageInformation()->getPackageProperties()->getCscOrderNo();
    if (currentWhsLineContext->isNarcotic())
    {
        ShipmentTrackingPackageInformationSQLMapperInt32Map::const_iterator whsPackageInfoBuilderTemplateIter = m_CustomerCscOrderNoNarcoticToWhsPackageInfoBuilderMap.find(customerCscOrderNo);
        if (whsPackageInfoBuilderTemplateIter == m_CustomerCscOrderNoNarcoticToWhsPackageInfoBuilderMap.end())
        {
            // Don't throw, report and just continue:
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO Tote WHS Template found in m_CustomerCscOrderNoNarcoticToWhsPackageInfoBuilderMap for customerCscOrderNo: " << customerCscOrderNo << " and: " << currentWhsLineContext);
        }
        else if (whsPackageInfoBuilderTemplateIter->second.get() == NULL)
        {
            m_CustomerCscOrderNoNarcoticToWhsPackageInfoBuilderMap[customerCscOrderNo] = currentWhsLineContext->getWhsPackageInfoBuilder();
        }
    }
    else
    {
        ShipmentTrackingPackageInformationSQLMapperInt32Map::const_iterator whsPackageInfoBuilderTemplateIter = m_CustomerCscOrderNoNormalToWhsPackageInfoBuilderMap.find(customerCscOrderNo);
        if (whsPackageInfoBuilderTemplateIter == m_CustomerCscOrderNoNormalToWhsPackageInfoBuilderMap.end())
        {
            // Don't throw, report and just continue:
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO Tote WHS Template found in m_CustomerCscOrderNoNormalToWhsPackageInfoBuilderMap for customerCscOrderNo: " << customerCscOrderNo << " and: " << currentWhsLineContext);
        }
        else if (whsPackageInfoBuilderTemplateIter->second.get() == NULL)
        {
            m_CustomerCscOrderNoNormalToWhsPackageInfoBuilderMap[customerCscOrderNo] = currentWhsLineContext->getWhsPackageInfoBuilder();
        }
    }
}

//----------------------------------------------------------------------------------
// Extract and Update Next Line Detail -> extractIbtOrderPosNrForQuantity
//----------------------------------------------------------------------------------
void ShipmentTrackingIbtOrderToPackageMapMaker::extractIbtOrderPosNrForQuantity(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext)
{
    METHODNAME_DEF(ShipmentTrackingIbtOrderToPackageMapMaker, extractIbtOrderPosNrForQuantity);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // get the right ArticleToPositionMapper:
    ShipmentTrackingArticleToPositionMapperInt32Map::iterator articleToPositionMapperIter = m_ArticleToPositionMapperMap.find(currentWhsLineContext->getArticleNr());
    if (articleToPositionMapperIter == m_ArticleToPositionMapperMap.end())
    {
        // Don't throw, report and just continue:
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO LineDetail found in m_ArticleToPositionMapperMap for articleNr: " << currentWhsLineContext);
        currentWhsLineContext->setIbtOrderPosNr(-1);
        return;
    }

    // ----------------------------------
    // extract the respective orderPosNr:
    // i.e. find first contained particle with ExpectedDeliveryQuantity == whsOriQuantity 
    // and remove it from the lineDetailMapMaker
    currentWhsLineContext->setIbtOrderPosNr(
        articleToPositionMapperIter->second->extractPositionForQuantity(
            currentWhsLineContext->getWhsOriginalQuantity()
        )
    );

    // and if the lineDetailMapMaker is empty remove it
    if (articleToPositionMapperIter->second->getSize() < 1)
    {
        m_ArticleToPositionMapperMap.erase(articleToPositionMapperIter);
    }
}


//----------------------------------------------------------------------------------
// Extract and Update Next Line Detail -> extractOneOutboundArticleLineAndRemoveFromTourIfEmpty
//----------------------------------------------------------------------------------
void ShipmentTrackingIbtOrderToPackageMapMaker::extractOneOutboundArticleLineAndRemoveFromTourIfEmpty(
    ShipmentTrackingPackageInformationSQLMapperPtr outboundPackageInfoBuilderTemplate,
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingIbtOrderToPackageMapMaker, extractOneOutboundArticleLineAndRemoveFromTourIfEmpty);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    currentWhsLineContext->setLineDetailBuilder(
        outboundPackageInfoBuilderTemplate->extractOneOutboundArticleLineForIbtPosNrAndRemoveFromTourIfEmpty(
            currentWhsLineContext->getIbtOrderPosNr()
        )
    );
}


} // end namespace shipmenttracking
} // end namespace libcsc

