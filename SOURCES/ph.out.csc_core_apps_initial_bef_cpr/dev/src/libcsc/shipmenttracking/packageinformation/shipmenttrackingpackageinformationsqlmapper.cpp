#include "shipmenttracking/tourinformation/shipmenttrackingtourinformation.h"
#include "shipmenttracking/tourinformation/shipmenttrackingtourinformationsqlmapper.h"
#include "shipmenttracking/tourinformation/shipmenttrackingtourdatasqlmapper.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"
#include "shipmenttrackingpackageinformationsqlmapper.h"
#include "shipmenttrackinglinedetailmapperbase.h"
#include "shipmenttrackingpackagepropertiessqlmapper.h"
#include "shipmenttrackingibtinformationsqlmapper.h"
#include "shipmenttrackinglinedetailsqlmapper.h"
#include "shipmenttrackingarticletopositionmapper.h"
#include "shipmenttrackingcurrentwhslinecontext.h"

#include <util/loggingutils.h>

#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <boost/make_shared.hpp>

namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingPackageInformationSQLMapper::ShipmentTrackingPackageInformationSQLMapper(
    ShipmentTrackingRequestProcessingContextPtr context,
    ShipmentTrackingTourInformationSQLMapperPtr tourInformationBuilder
) :
    ShipmentTrackingPackageInformationMapperBase(
        boost::make_shared<ShipmentTrackingPackageInformation>(
            tourInformationBuilder.get() != NULL? tourInformationBuilder->getTourInformation()->getTourData() : ShipmentTrackingTourDataPtr()
        )
    ),
    m_Context(context),
    m_TourInformationBuilder(tourInformationBuilder),
    m_PackagePropertiesMapper(context, m_PackageInformation->getPackageProperties()),
    m_IsOrderClosed(false),
    m_IsIbtPackage(false),
    m_FirstLineWhsPosNr(0),
    m_FirstLineIsContentChanged(false),
    m_FirstLineIsTourRedirected(false),
    m_PreviousLineWhsPosNr(0),
    m_PreviousLineWasContentChanged(false),
    m_PreviousLineWasTourRedirected(false)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, ShipmentTrackingPackageInformationSQLMapper);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    if (context.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "context is Null!", __FILE__, __LINE__), "");
    }
    if (tourInformationBuilder.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "tourInformationBuilder is Null!", __FILE__, __LINE__), "");
    }
}


ShipmentTrackingPackageInformationSQLMapper::~ShipmentTrackingPackageInformationSQLMapper()
{
}

void ShipmentTrackingPackageInformationSQLMapper::setResultSet(const basar::db::sql::ResultsetRef resultSet)
{
    m_PackagePropertiesMapper.setResultSet(resultSet);

    if (m_IbtInformationMapperPtr.get() != NULL)
    {
        m_IbtInformationMapperPtr->setResultSet(resultSet);
    }
}

//----------------------------------------------------------------------------------
// Mapping from Outbound database
//----------------------------------------------------------------------------------
ShipmentTrackingLineDetailSQLMapperPtr ShipmentTrackingPackageInformationSQLMapper::mapFromOutboundDataAndJoinTourInfo(
    const basar::db::sql::ResultsetRef resultSet,
    basar::Int32 cscOrderNo,
    bool isNarcotic,
    basar::Int32 iCscOrderNo
)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, mapFromOutboundDataAndJoinTourInfo);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo(fun, "resultSet is Null!", __FILE__, __LINE__), "");
    }

    setResultSet(resultSet);


    // Join Tour Info: add the new Package Info into the RESULT SET TourInformation:
    m_TourOutboundPackageInfoPositionInterator = m_TourInformationBuilder->addNextPackage(getPackageInformation());
    m_TourWarehousePackageInfoInsertionInterator = m_TourOutboundPackageInfoPositionInterator;
    m_TourWarehousePackageInfoInsertionInterator++;


    // Do fill PackageProperties from same m_ResultSet:
    m_PackagePropertiesMapper.mapFromOutboundData(cscOrderNo, isNarcotic);

    m_IsOrderClosed = m_PackagePropertiesMapper.getPackageProperties()->isOrderClosed();

    // Do fill IbtInformation from same m_ResultSet:

    if (iCscOrderNo > 0)
    {
        m_IsIbtPackage = true;

        ShipmentTrackingIbtInformationPtr ibtImformation = boost::make_shared<ShipmentTrackingIbtInformation>();
        m_IbtInformationMapperPtr = boost::make_shared<ShipmentTrackingIbtInformationSQLMapper>(m_Context, ibtImformation);
        m_IbtInformationMapperPtr->setResultSet(resultSet); //NOTE: necessary here due to late creating according to call to setResultSet()!
        m_IbtInformationMapperPtr->mapFromOutboundData(iCscOrderNo, isNarcotic);

        setIbtImformation(ibtImformation);
    }


    ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder;
    if (m_Context->Filter.DetailsDesired)
    {
        lineDetailBuilder = addNextLineDetailFromOutboundDataInner(resultSet, isNarcotic);
    }
    else
    {
        //NOTE: DO NOT query the ExpectedDeliveryQuantity if not handling LineDetails, because I optimized also the unnecessary DKTSV lines in the SQL statement away!
    }


    // Invalidate result set in Builder:
    setResultSet(basar::db::sql::ResultsetRef());

    return lineDetailBuilder;
}

//----------------------------------------------------------------------------------
// Mapping from Outbound database -> Add Next Line Detail From Outbound Data
//----------------------------------------------------------------------------------
ShipmentTrackingLineDetailSQLMapperPtr ShipmentTrackingPackageInformationSQLMapper::addNextLineDetailFromOutboundData(
    const basar::db::sql::ResultsetRef resultSet,
    bool isNarcotic
)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, addNextLineDetailFromOutboundData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder;
    if (!m_Context->Filter.DetailsDesired)
    {
        return lineDetailBuilder;
    }

    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo(fun, "resultSet is Null!", __FILE__, __LINE__), "");
    }

    setResultSet(resultSet);

    // do the inner Add Next Line Detail processing:
    lineDetailBuilder = addNextLineDetailFromOutboundDataInner(resultSet, isNarcotic);

    // Invalidate result set in Builder:
    setResultSet(basar::db::sql::ResultsetRef());

    return lineDetailBuilder;
}

//----------------------------------------------------------------------------------
// Mapping from Outbound database -> Inner Impl: Add Next Line Detail From Outbound Data
//----------------------------------------------------------------------------------
ShipmentTrackingLineDetailSQLMapperPtr ShipmentTrackingPackageInformationSQLMapper::addNextLineDetailFromOutboundDataInner(
    const basar::db::sql::ResultsetRef resultSet,
    bool isNarcotic
)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, addNextLineDetailFromOutboundDataInner);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // Do fill LineDetail from same m_ResultSet:
    ShipmentTrackingLineDetailPtr lineDetail = boost::make_shared<ShipmentTrackingLineDetail>();
    ShipmentTrackingLineDetailSQLMapperPtr lineDetailMapper = boost::make_shared<ShipmentTrackingLineDetailSQLMapper>(lineDetail);
    lineDetailMapper->mapFromOutboundDataAndAddLineDetail(resultSet, *this, isNarcotic);

    // Update the Outbound --> Warehouse Builder connection structure:
    storeLineInArticleToPositionMapperMap(lineDetailMapper, lineDetail);
    
    // Count quantities:
    int expectedDeliveryQuantity = lineDetail->getExpectedDeliveryQuantity();
    m_PackagePropertiesMapper.addTotalExpectedDeliveryQuantity(expectedDeliveryQuantity);

    return lineDetailMapper;
}

//----------------------------------------------------------------------------------
// Inner Helper
//----------------------------------------------------------------------------------
void ShipmentTrackingPackageInformationSQLMapper::storeLineInArticleToPositionMapperMap(
    ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder,
    ShipmentTrackingLineDetailPtr lineDetail
)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, storeLineInArticleToPositionMapperMap);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    if (!m_IsOrderClosed)   // <-- if this order is not closed yet, then there is no connecting with Warehouse (DKTSV) data => so no need to store this mapping below
    {
        return; // <-- quit completely in this case!
    }

    basar::Int32 customerOrderPosNr = lineDetail->getOrderPosNo();

    if (!m_IsIbtPackage)     // <-- if this is an IBT package, then the ShipmentTrackingIbtOrderToPackageMapMaker is managing the tote line mapping between Outbound ((a)KdAuftragPos) and Warehouse (DKTSV)
    {
        basar::Int32 articleNr = lineDetail->getArticleNr();

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

        //NOTE: we store here the positions in a SQL sorted sequence and this is important, because the OrderPosNr and WHS-TotePosNo are closely related. See the comparison: "201123-KscPosNr~=TSV_Pos"
        articleToPositionMapper->addPositionWithQuantity(customerOrderPosNr, lineDetail->getExpectedDeliveryQuantity());
    }

    // Store the new PackageInfoBuilder for the Local CscPosNr:
    m_CustomerOrderPositionToLineDetailBuilderMap[customerOrderPosNr] = lineDetailBuilder;

    basar::Int32 ibtOrderPosNr = lineDetail->getIbtOrderPosNo();
    if (ibtOrderPosNr > 0)
    {
        m_IbtOrderPositionToLineDetailBuilderMap[ibtOrderPosNr] = lineDetailBuilder;
    }

}

//----------------------------------------------------------------------------------
// Helper: Prepare for read from Warehouse database -> making a partially shallow, partially deep copy
//----------------------------------------------------------------------------------
ShipmentTrackingPackageInformationSQLMapperPtr ShipmentTrackingPackageInformationSQLMapper::createCloneWithTighlyConnectedDataButWithoutLinesAndIbt()
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, createCloneWithTighlyConnectedDataButWithoutLinesAndIbt);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // Create a partially shallow, partially deep copy. 
    // -> Deep copy 1 level:-> just the contained PackageProperties and same for IbtInfo as for this PackageInfo
    // -> Shallow copy : -> DO NOT TAKE Lines at all in this step. They will be moved 1 by 1 from Outbound Tote(PackageId == 0) to the here newly created WHS - Tote
    //     -> just link to the same TourData(same for IbtInfo)


    // Link to the same Tour as the original:
    ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilderCloneForWhs = boost::make_shared<ShipmentTrackingPackageInformationSQLMapper>(m_Context, m_TourInformationBuilder);

    // Clone PackageProperties:
    packageInfoBuilderCloneForWhs->m_PackagePropertiesMapper.fillCloneFromOutboundData(this->m_PackagePropertiesMapper);

    packageInfoBuilderCloneForWhs->m_TourWarehousePackageInfoInsertionInterator = this->m_TourWarehousePackageInfoInsertionInterator;
    packageInfoBuilderCloneForWhs->m_IsOrderClosed = this->m_IsOrderClosed;
    packageInfoBuilderCloneForWhs->m_IsIbtPackage = this->m_IsIbtPackage;

    //NOTE: DO NOT TAKE Lines at all in this step. They will be moved 1 by 1 from Outbound Tote(PackageId == 0) to the here newly created WHS - Tote

    //NOTE: Outbound Tote has no "Tote Redirections"!

    // Connect the new WHS package to own TourInfo where he belongs
    m_TourInformationBuilder->insertPackageToList(m_TourWarehousePackageInfoInsertionInterator, packageInfoBuilderCloneForWhs->getPackageInformation());

    return packageInfoBuilderCloneForWhs;
}

//----------------------------------------------------------------------------------
// Fill Clone From Outbound Data. This is the rest of the "deep clone" part.
//----------------------------------------------------------------------------------
void ShipmentTrackingPackageInformationSQLMapper::addIbtCloneFromOutboundData(const ShipmentTrackingPackageInformationSQLMapper& originalPackageInfoBuilder)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, addIbtCloneFromOutboundData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // Do fill IbtInformation from same m_ResultSet:
    m_IsIbtPackage = originalPackageInfoBuilder.m_IsIbtPackage;

    if (originalPackageInfoBuilder.m_IbtInformationMapperPtr.get() != NULL)
    {
        ShipmentTrackingIbtInformationPtr ibtImformation = boost::make_shared<ShipmentTrackingIbtInformation>();
        m_IbtInformationMapperPtr = boost::make_shared<ShipmentTrackingIbtInformationSQLMapper>(m_Context, ibtImformation);
        m_IbtInformationMapperPtr->fillCloneFromOutboundData(*originalPackageInfoBuilder.m_IbtInformationMapperPtr.get());

        setIbtImformation(ibtImformation);
    }
}

//----------------------------------------------------------------------------------
// Helper: Prepare for read from Warehouse database -> making a partially shallow, partially deep copy
//----------------------------------------------------------------------------------
ShipmentTrackingPackageInformationSQLMapperPtr ShipmentTrackingPackageInformationSQLMapper::createCloneWithTighlyConnectedDataButWithoutLinesAndRemoveFromTourIfEmpty()
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, createCloneWithTighlyConnectedDataButWithoutLinesAndRemoveFromTourIfEmpty);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // Create a partially shallow, partially deep copy. 
    // -> Deep copy 1 level:-> just the contained PackageProperties and same for IbtInfo as for this PackageInfo
    // -> Shallow copy : -> DO NOT TAKE Lines at all in this step. They will be moved 1 by 1 from Outbound Tote(PackageId == 0) to the here newly created WHS - Tote
    //     -> just link to the same TourData(same for IbtInfo)


    // Link to the same Tour as the original:
    ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilderClone = createCloneWithTighlyConnectedDataButWithoutLinesAndIbt();

    // clone IBT info
    packageInfoBuilderClone->addIbtCloneFromOutboundData(*this);

    removePackageFromTourInformationIfEmtpty();

    return packageInfoBuilderClone;
}

//----------------------------------------------------------------------------------
// Helper: Prepare for read from Warehouse database -> making a partially shallow, partially deep copy
//----------------------------------------------------------------------------------
void ShipmentTrackingPackageInformationSQLMapper::removePackageFromTourInformationIfEmtpty()
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, removePackageFromTourInformationIfEmtpty);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // ----------------------------
    // Check if there are no more lines, and if no => remove this empty Outbound PackageInfo trom TourInfo (result structure)! -> this is the case if (m_Context->Filter.DetailsDesired == false)
    if (m_CustomerOrderPositionToLineDetailBuilderMap.size() < 1)
    {
        m_TourOutboundPackageInfoPositionInterator = m_TourInformationBuilder->removePackageFromList(m_TourOutboundPackageInfoPositionInterator);
    }
}

//----------------------------------------------------------------------------------
// Make destination redirected Clone From Warehouse Data
//----------------------------------------------------------------------------------
void ShipmentTrackingPackageInformationSQLMapper::updateCloneFromTourRedirectionSource(const ShipmentTrackingPackageInformationSQLMapper& originalPackageInfoBuilder)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, updateCloneFromTourRedirectionSource);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // --------------
    // Sahre all data except TourData:

    m_PackagePropertiesMapper.m_PackageProperties = originalPackageInfoBuilder.m_PackagePropertiesMapper.m_PackageProperties;
    setPackageProperties(originalPackageInfoBuilder.m_PackagePropertiesMapper.m_PackageProperties);

    if (originalPackageInfoBuilder.m_IbtInformationMapperPtr.get() != NULL)
    {
        m_IbtInformationMapperPtr = originalPackageInfoBuilder.m_IbtInformationMapperPtr;
        setIbtImformation(originalPackageInfoBuilder.m_IbtInformationMapperPtr->getIbtInformation());
    }

    setLineDetailCollection(originalPackageInfoBuilder.m_PackageInformation->getLineDetailCollection());

    // and finally set the RedirectedFromTourData:
    setRedirectedFromTourData(originalPackageInfoBuilder.m_PackageInformation->getTourData());

    // Flags, Maps, etc:
    m_IsOrderClosed = originalPackageInfoBuilder.m_IsOrderClosed;
    m_IsIbtPackage = originalPackageInfoBuilder.m_IsIbtPackage;

    // Unwanted: m_ArticleToPositionMapperMap, m_CustomerOrderPositionToLineDetailBuilderMap, m_IbtOrderPositionToLineDetailBuilderMap
    // Unnecessary: m_FirstLineWhsPosNr, m_FirstLineIsContentChanged, m_FirstLineIsTourRedirected, m_PreviousLineWhsPosNr, m_PreviousLineWasContentChanged, m_PreviousLineWasTourRedirected

    // Wanted:
    m_TotePositionToLineDetailBuilderMap = originalPackageInfoBuilder.m_TotePositionToLineDetailBuilderMap;

    // ---------------
    // Join Tour Info: add the new Package Info into the RESULT SET TourInformation:
    m_TourInformationBuilder->addNextPackage(getPackageInformation());
    //NOTE: don't store any Tour insertion point, it is unnecessary neither: m_TourWarehousePackageInfoInsertionInterator, nor: m_TourOutboundPackageInfoPositionInterator (the 2nd one would be completely wrong!)
}

//----------------------------------------------------------------------------------
// Extract One Outbound Article Line from the Outbound Tote Template
//----------------------------------------------------------------------------------
ShipmentTrackingLineDetailSQLMapperPtr ShipmentTrackingPackageInformationSQLMapper::extractOneOutboundArticleLineAndRemoveFromTourIfEmpty(basar::Int32 articleNr, basar::Int32 whsOriginalQuantity)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, extractOneOutboundArticleLineAndRemoveFromTourIfEmpty);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << articleNr << ", " << whsOriginalQuantity << ", " << m_PackageInformation->getOutboundMapKey());

    // --------------------------------------
    // get the right ArticleToPositionMapper:
    ShipmentTrackingArticleToPositionMapperInt32Map::iterator articleToPositionMapperIter = m_ArticleToPositionMapperMap.find(articleNr);
    if (articleToPositionMapperIter == m_ArticleToPositionMapperMap.end())
    {
        // Don't throw, report and just continue:
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO LineDetail found for articleNr: " << articleNr << ", m_CustomerOrderPositionToLineDetailBuilderMap.size: " << m_CustomerOrderPositionToLineDetailBuilderMap.size() << ", m_IbtOrderPositionToLineDetailBuilderMap.size: " << m_IbtOrderPositionToLineDetailBuilderMap.size());

        return ShipmentTrackingLineDetailSQLMapperPtr();
    }

    // ----------------------------------
    // extract the respective orderPosNr:
    // i.e. find first contained particle with ExpectedDeliveryQuantity == whsOriQuantity 
    // and remove it from the lineDetailMapMaker
    basar::Int32 orderPosNr = articleToPositionMapperIter->second->extractPositionForQuantity(whsOriginalQuantity);

    // and if the lineDetailMapMaker is empty remove it
    if (articleToPositionMapperIter->second->getSize() < 1)
    {
        m_ArticleToPositionMapperMap.erase(articleToPositionMapperIter);
    }

    ShipmentTrackingLineDetailSQLMapperInt32Map::iterator lineDetailBuilderIter = m_CustomerOrderPositionToLineDetailBuilderMap.find(orderPosNr);
    if (lineDetailBuilderIter == m_CustomerOrderPositionToLineDetailBuilderMap.end())
    {
        // Don't throw, report and just continue:
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO LineDetailBuilder found for orderPosNr: " << orderPosNr << ", m_CustomerOrderPositionToLineDetailBuilderMap.size: " << m_CustomerOrderPositionToLineDetailBuilderMap.size() << ", m_IbtOrderPositionToLineDetailBuilderMap.size: " << m_IbtOrderPositionToLineDetailBuilderMap.size());

        return ShipmentTrackingLineDetailSQLMapperPtr();
    }

    // ----------------------------
    // extract the respective line:
    ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder = lineDetailBuilderIter->second;

    // Remove line from the Outbound result structure -> just to be moved (added) to the Warehouse result structure:
    lineDetailBuilder->removeLineDetailFromOutboundCollection(*this);

    // remove it from Outbound map:
    m_CustomerOrderPositionToLineDetailBuilderMap.erase(lineDetailBuilderIter);

    // ----------------------------
    // Check if there are no more lines, and if no => remove this empty Outbound PackageInfo trom TourInfo (result structure)!
    if (m_CustomerOrderPositionToLineDetailBuilderMap.size() < 1)
    {
        m_TourOutboundPackageInfoPositionInterator = m_TourInformationBuilder->removePackageFromList(m_TourOutboundPackageInfoPositionInterator);
    }

    return lineDetailBuilder;
}

//----------------------------------------------------------------------------------
// Extract One Outbound Article Line from the Outbound Tote Template
//----------------------------------------------------------------------------------
ShipmentTrackingLineDetailSQLMapperPtr ShipmentTrackingPackageInformationSQLMapper::extractOneOutboundArticleLineForIbtPosNrAndRemoveFromTourIfEmpty(basar::Int32 ibtOrderPosNr)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, extractOneOutboundArticleLineForIbtPosNrAndRemoveFromTourIfEmpty);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << ibtOrderPosNr << ", " << m_PackageInformation->getOutboundMapKey());

    ShipmentTrackingLineDetailSQLMapperInt32Map::iterator lineDetailBuilderIter = m_IbtOrderPositionToLineDetailBuilderMap.find(ibtOrderPosNr);
    if (lineDetailBuilderIter == m_IbtOrderPositionToLineDetailBuilderMap.end())
    {
        // Don't throw, report and just continue:
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO LineDetailBuilder found in m_IbtOrderPositionToLineDetailBuilderMap for ibtOrderPosNr: " << ibtOrderPosNr << ", m_CustomerOrderPositionToLineDetailBuilderMap.size: " << m_CustomerOrderPositionToLineDetailBuilderMap.size() << ", m_IbtOrderPositionToLineDetailBuilderMap.size: " << m_IbtOrderPositionToLineDetailBuilderMap.size());

        return ShipmentTrackingLineDetailSQLMapperPtr();
    }

    // ----------------------------
    // extract the respective line:
    ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder = lineDetailBuilderIter->second;
    
    // Remove line from the Outbound result structure -> just to be moved (added) to the Warehouse result structure:
    lineDetailBuilder->removeLineDetailFromOutboundCollection(*this);

    // remove it from Outbound map:
    m_IbtOrderPositionToLineDetailBuilderMap.erase(lineDetailBuilderIter);

    // get and remove it also from m_CustomerOrderPositionToLineDetailBuilderMap
    basar::Int32 customerOrderPosNr = lineDetailBuilder->getLineDetail()->getOrderPosNo();

    lineDetailBuilderIter = m_CustomerOrderPositionToLineDetailBuilderMap.find(customerOrderPosNr);
    if (lineDetailBuilderIter == m_CustomerOrderPositionToLineDetailBuilderMap.end())
    {
        // Don't throw, report and just continue:
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO LineDetailBuilder found in m_CustomerOrderPositionToLineDetailBuilderMap for customerOrderPosNr: " << customerOrderPosNr << ", m_CustomerOrderPositionToLineDetailBuilderMap.size: " << m_CustomerOrderPositionToLineDetailBuilderMap.size() << ", m_IbtOrderPositionToLineDetailBuilderMap.size: " << m_IbtOrderPositionToLineDetailBuilderMap.size());

        return lineDetailBuilder;
    }

    // remove it from Outbound map:
    m_CustomerOrderPositionToLineDetailBuilderMap.erase(lineDetailBuilderIter);

    // ----------------------------
    // Check if there are no more lines, and if no => remove this empty Outbound PackageInfo trom TourInfo (result structure)!
    if (m_CustomerOrderPositionToLineDetailBuilderMap.size() < 1)
    {
        m_TourOutboundPackageInfoPositionInterator = m_TourInformationBuilder->removePackageFromList(m_TourOutboundPackageInfoPositionInterator);
    }

    return lineDetailBuilder;
}

//----------------------------------------------------------------------------------
// Get Tote-LineDetailBuilder for TotePosNr
//----------------------------------------------------------------------------------
ShipmentTrackingLineDetailSQLMapperPtr ShipmentTrackingPackageInformationSQLMapper::getToteLineDetailBuilderForTotePosNr(basar::Int32 totePosNr)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, getToteLineDetailBuilderForTotePosNr);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << totePosNr);

    ShipmentTrackingLineDetailSQLMapperInt32Map::iterator toteLineDetailBuilderIterator = m_TotePositionToLineDetailBuilderMap.find(totePosNr);

    ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder;
    if (toteLineDetailBuilderIterator != m_TotePositionToLineDetailBuilderMap.end())
    {
        lineDetailBuilder = toteLineDetailBuilderIterator->second;
    }

    return lineDetailBuilder;
}


//----------------------------------------------------------------------------------
// Add New Warehouse LineDetailBuilder from a fresh and for WHS yet unused outbound line 
//----------------------------------------------------------------------------------
void ShipmentTrackingPackageInformationSQLMapper::addNewWarehouseLineDetailBuilder(
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, addNewWarehouseLineDetailBuilder);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    if (currentWhsLineContext.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "currentWhsLineContext is Null!", __FILE__, __LINE__), "");
    }

    ShipmentTrackingLineDetailSQLMapperPtr toteLineDetailBuilder = currentWhsLineContext->getLineDetailBuilder();
    if (toteLineDetailBuilder.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "toteLineDetailBuilder is Null!", __FILE__, __LINE__), "");
    }

    m_TotePositionToLineDetailBuilderMap[currentWhsLineContext->getTotePosNr()] = toteLineDetailBuilder;
    toteLineDetailBuilder->addExtractedOutboundLineToWarehouseTote(*this);
}

//----------------------------------------------------------------------------------
// Reuse lineDetaBuilder from another tote in this WHS Tote for a case, that current CscOrderPos is splitted to more than one tote
//----------------------------------------------------------------------------------
void ShipmentTrackingPackageInformationSQLMapper::resuseToteSplittedWarehouseLineDetailBuilder(
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, resuseToteSplittedWarehouseLineDetailBuilder);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    if (currentWhsLineContext.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "currentWhsLineContext is Null!", __FILE__, __LINE__), "");
    }

    ShipmentTrackingLineDetailSQLMapperPtr toteLineDetailBuilder = currentWhsLineContext->getLineDetailBuilder();
    if (toteLineDetailBuilder.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "toteLineDetailBuilder is Null!", __FILE__, __LINE__), "");
    }

    m_TotePositionToLineDetailBuilderMap[currentWhsLineContext->getTotePosNr()] = toteLineDetailBuilder;
    toteLineDetailBuilder->createNewLineDetailCloneFromOutboundDataAndAttachToPackageInfo(*this);
}

//----------------------------------------------------------------------------------
// Mapping from Warehouse database
//----------------------------------------------------------------------------------
void ShipmentTrackingPackageInformationSQLMapper::mapFromWarehouseData(
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, mapFromWarehouseData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // totePosNr == dktsv.tsv_pos -> it is important for the reading of properties just along with the first line
    // NOTE : lineDetailBuilder can be null, if (m_Context->Filter.DetailsDesired == false)

    if (currentWhsLineContext.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "currentWhsLineContext is Null!", __FILE__, __LINE__), "");
    }

    setResultSet(currentWhsLineContext->getResultSet());


    // logic of the following flag can only be based on proper SQL sorting !
    bool readingFirstDataLineOfPosOrItsBatchSplit =        // <- flag indicating if we are reading 2nd or later Batch split detail of the first line.
        m_FirstLineIsContentChanged == currentWhsLineContext->isContentChanged() &&
        m_FirstLineIsTourRedirected == currentWhsLineContext->isTourRedirected();

    // "readingPosBatchSplit" is a flag indicating if we are reading 2nd or later Batch split detail of the line.
    //NOTE: logic of the following flag can only be based on proper SQL sorting!
    bool readingPosBatchSplit = false;            

    // -------------------
    // Tote PosNr handling
    if (currentWhsLineContext->getTotePosNr() != 0)
    {
        if (m_FirstLineWhsPosNr == 0)
        {
            readingFirstDataLineOfPosOrItsBatchSplit = true;     // <- must be reset here, because its value was "random" until now
            readingPosBatchSplit = false;

            m_FirstLineWhsPosNr = currentWhsLineContext->getTotePosNr();
            m_FirstLineIsContentChanged = currentWhsLineContext->isContentChanged();
            m_FirstLineIsTourRedirected = currentWhsLineContext->isTourRedirected();
        }
        else
        {
            // it makes sense to compute it only here:
            readingPosBatchSplit =
                //currentWhsLineContext->getTotePosNr() != 0 &&
                m_PreviousLineWhsPosNr == currentWhsLineContext->getTotePosNr() &&
                m_PreviousLineWasContentChanged == currentWhsLineContext->isContentChanged() &&
                m_PreviousLineWasTourRedirected == currentWhsLineContext->isTourRedirected();
        }
    }

    // -----------------
    // read the tote properties and Redirection TourData
    if (currentWhsLineContext->getTotePosNr() == 0 ||                       // always read status information!
        currentWhsLineContext->getTotePosNr() == m_FirstLineWhsPosNr        //NOTE: read all records of the first line. For all other lines are the package and tour informations the same => so skip them!
       )
    {
        if (!readingPosBatchSplit)              // BUT: skip also all Batch split duplications of the first line in all state combinations --> NOTE: DO NOT SKIP OTHER STATES OF THE FIRST LINE -> it is necessary for redirection, content change, and original PickingDate!
        {
            if (m_PackagePropertiesMapper.m_PackageProperties->getCscOrderNo() == currentWhsLineContext->getCscOrderNo())
            {
                // Do fill PackageProperties from same m_ResultSet:
                m_PackagePropertiesMapper.mapFromWarehouseData(currentWhsLineContext);

                if (currentWhsLineContext->isTourRedirected())
                {
                    // handle changed Tour info:
                    if (m_PackageInformation->getRedirectedToTourData().get() == NULL)
                    {
                        // Do fill TourData from same resultSet:
                        ShipmentTrackingTourDataPtr redirectedToTourData = boost::make_shared<ShipmentTrackingTourData>();
                        ShipmentTrackingTourDataSQLMapper redirectedToTourDataMapper(redirectedToTourData, currentWhsLineContext->getResultSet());
                        redirectedToTourDataMapper.mapFromWarehouseData(m_PackagePropertiesMapper.m_PackageProperties->getOrderClosedAt().getDate(), currentWhsLineContext);

                        setRedirectedToTourData(redirectedToTourData);
                    }
                }
            }
            else if (m_IbtInformationMapperPtr.get() != NULL)
            {
                // Do fill IbtInformation from same m_ResultSet:
                m_IsIbtPackage = true;

                m_IbtInformationMapperPtr->mapFromWarehouseData(currentWhsLineContext);

                if (!m_PackagePropertiesMapper.m_PackageProperties->hasWarehouseData())
                {
                    m_PackagePropertiesMapper.mapFromWarehouseData(currentWhsLineContext, true);
                }

                if (currentWhsLineContext->isDeleted())
                {
                    // mark also as deleted -> There is just one value for Normal local, IBT Remote or Local case. Tote can be deleted just once!
                    m_PackagePropertiesMapper.mapFromWarehouseData(currentWhsLineContext);
                }
            }
        }
    }

    // -----------------
    // Handle Line info
    if (m_Context->Filter.DetailsDesired &&
        currentWhsLineContext->getTotePosNr() != 0 &&
        readingFirstDataLineOfPosOrItsBatchSplit
        )
    {
        if (currentWhsLineContext->getLineDetailBuilder().get() == NULL)
        {
            // Don't throw, report and just continue:
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! lineDetailBuilder is Null! In: " << m_PackageInformation->getOutboundMapKey() << " " << m_PackageInformation->getWarehouseMapKey() << ", " << currentWhsLineContext);
        }
        else
        {
            if (!readingPosBatchSplit)
            {
                m_PackagePropertiesMapper.addTotalExpectedDeliveryQuantity(currentWhsLineContext->getLineDetailBuilder()->getLineDetail()->getExpectedDeliveryQuantity());
            }

            currentWhsLineContext->getLineDetailBuilder()->mapFromWarehouseData(currentWhsLineContext, *this);
        }
    }
    //else --> DO NOT query the ConfirmedDeliveryQuantity if not handling LineDetails (m_Context->Filter.DetailsDesired), because I optimized also the unnecessary DKTSV lines in the SQL statement away!

    // -------
    // Finish:
    if (currentWhsLineContext->getTotePosNr() != 0)
    {
        m_PreviousLineWhsPosNr = currentWhsLineContext->getTotePosNr();
        m_PreviousLineWasContentChanged = currentWhsLineContext->isContentChanged();
        m_PreviousLineWasTourRedirected = currentWhsLineContext->isTourRedirected();
    }

    // Invalidate result set in Builder:
    setResultSet(basar::db::sql::ResultsetRef());
}

//----------------------------------------------------------------------------------
// Update Total Confirmed Delivery Quantities
//----------------------------------------------------------------------------------
typedef std::map<void*, bool> PointerHashSetMap;

void ShipmentTrackingPackageInformationSQLMapper::UpdateTotalConfirmedDeliveryQuantities()
{
    METHODNAME_DEF(ShipmentTrackingPackageInformationSQLMapper, UpdateTotalConfirmedDeliveryQuantities);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);


    std::string ownWhsMapKey = getPackageInformation()->getWarehouseMapKey();
    PointerHashSetMap whsToteMapKeyToOrderPositionSplitSiblingLinesPointerMap;

    // count Total Confirmed Delivery Quantities:
    const ShipmentTrackingLineDetailCollectionPtr lineDetailCollectionPtr = m_PackageInformation->getLineDetailCollection();
    for (ShipmentTrackingLineDetailCollection::iterator lineDetailIter = lineDetailCollectionPtr->begin();
        lineDetailIter != lineDetailCollectionPtr->end();
        lineDetailIter++
        )
    {
        int confirmedDeliveryQuantity = (*lineDetailIter)->getConfirmedDeliveryQuantity();
        m_PackagePropertiesMapper.addTotalConfirmedDeliveryQuantity(confirmedDeliveryQuantity);

        // ------------------------------------------------
        // process CscOrderPos split to more than one tote:
        if ((*lineDetailIter)->getWhsSiblingToteCount() < 2)
        {
            continue; // --> skip further processing
        }

        ShipmentTrackingLineDetailWeakStrToClollectionMapPtr whsToteMapKeyToOrderPositionSplitSiblingLines = (*lineDetailIter)->getWhsToteMapKeyToOrderPositionSplitSiblingLines();

        if (whsToteMapKeyToOrderPositionSplitSiblingLinesPointerMap.find(whsToteMapKeyToOrderPositionSplitSiblingLines.get()) != whsToteMapKeyToOrderPositionSplitSiblingLinesPointerMap.end())
        {
            continue; // --> already processed => skip further processing
        }

        // prohibit reprocessing on next batch
        whsToteMapKeyToOrderPositionSplitSiblingLinesPointerMap[whsToteMapKeyToOrderPositionSplitSiblingLines.get()] = true;

        for (ShipmentTrackingLineDetailWeakStrToClollectionMap::iterator it1 = whsToteMapKeyToOrderPositionSplitSiblingLines->begin();
            it1 != whsToteMapKeyToOrderPositionSplitSiblingLines->end();
            it1++
            )
        {
            if (it1->first == ownWhsMapKey)
            {
                continue; // --> skip own Tote!
            }

            ShipmentTrackingLineDetailWeakCollectionPtr lineDetailWeakCollection = it1->second;

            for (ShipmentTrackingLineDetailWeakCollection::iterator it2 = lineDetailWeakCollection->begin();
                it2 != lineDetailWeakCollection->end();
                it2++
                )
            {
                ShipmentTrackingLineDetailPtr otherTotesSiblingLine = (*it2).lock();

                if (otherTotesSiblingLine.get() != NULL)
                {
                    confirmedDeliveryQuantity = otherTotesSiblingLine->getConfirmedDeliveryQuantity();
                    m_PackagePropertiesMapper.addTotalRelatedConfirmedDeliveryQuantity(confirmedDeliveryQuantity);
                }
            }
        }
    }
}


} // end namespace shipmenttracking
} // end namespace libcsc
