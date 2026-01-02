#include <shipmenttracking/shipmenttrackingrepositorybuilder.h>
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"
#include "shipmenttracking/configuration/etadelayevaluationptr.h"
#include "shipmenttracking/configuration/etadelayevaluation.h"
#include "shipmenttracking/configuration/etadelayevaluationsqlmapper.h"
#include "shipmenttracking/configuration/etadelaypresentationptr.h"
#include "shipmenttracking/configuration/etadelaypresentation.h"
#include "shipmenttracking/configuration/etadelaypresentationsqlmapper.h"
#include "shipmenttracking/configuration/transmedstatusiddeliveredtocustomersqlfetcher.h"
#include "shipmenttracking/shipmenttrackingrepositorysqlbuilder.h"
#include "tourinformation/shipmenttrackingtourinformation.h"
#include "tourinformation/shipmenttrackingtourinformationmapperbase.h"
#include "tourinformation/shipmenttrackingtourinformationsqlmapper.h"
#include "tourinformation/shipmenttrackingetaanddeliverydatasqlmapper.h"
#include "shipmenttracking/packageinformation/shipmenttrackingcurrentwhslinecontext.h"
#include "shipmenttracking/packageinformation/shipmenttrackingpackageinformationsqlmapper.h"
#include "shipmenttracking/packageinformation/shipmenttrackingpackagepropertiessqlmapper.h"
#include "shipmenttracking/packageinformation/shipmenttrackinglinedetailsqlmapper.h"

#include <exceptions/sqlduplicateexception.h>

#include <persistence/iaccessor.h>
#include <persistence/iaccessorfactory.h>
#include <persistence/itransactionfactory.h>
#include <parameter/branchparametergetter.h>
#include <boost/make_shared.hpp>

#include <libbasarcmnutil.h>
#include <util/loggingutils.h>
#include <exceptions/exceptionhelper.h>


namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingRepositoryBuilder::ShipmentTrackingRepositoryBuilder(
    ShipmentTrackingRequestProcessingContextPtr context,
    persistence::IAccessorPtr accessor
) :
    m_Context(context),
    m_Accessor(accessor),
    m_CntReportedTotes(0),
    m_CntProcessedOutboundRows(0),
    m_CntProcessedWhsRows(0),
    m_CntPostProcessedWhsRows(0),
    m_TourInformationCollection(boost::make_shared<ShipmentTrackingTourInformationCollection>())
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, ShipmentTrackingRepositoryBuilder);

    if (context.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "context is Null!", __FILE__, __LINE__), "");
    }
    if (accessor.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "accessor is Null!", __FILE__, __LINE__), "");
    }

    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);
}

ShipmentTrackingRepositoryBuilder::~ShipmentTrackingRepositoryBuilder()
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, ~ShipmentTrackingRepositoryBuilder);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);
}

/////////////////////////////////////////////////////////////////////////////////////
// BUILD CONFIG Methods
/////////////////////////////////////////////////////////////////////////////////////
void ShipmentTrackingRepositoryBuilder::ensureEtaDelayEvaluationCacheIsFilled(const basar::VarString& dbNameWarehouse)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, ensureEtaDelayEvaluationCacheIsFilled);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << " Cache size:" << m_EtaDelayEvaluationCache.size());

    if (m_EtaDelayEvaluationCache.size() > 0)
    {
        return;
    }

    try
    {
        basar::db::sql::ResultsetRef resultset = m_Accessor->select(
            EtaDelayEvaluationSQLMapper::getSelectSQL(dbNameWarehouse)
        );

        int cntr = 0;
        while (resultset.next())
        {
            cntr++;
            EtaDelayEvaluationPtr etaDelayEvaluation = boost::make_shared<EtaDelayEvaluation>();
            EtaDelayEvaluationSQLMapper mapper(etaDelayEvaluation, resultset);
            mapper.map();

            m_EtaDelayEvaluationCache.push_back(etaDelayEvaluation);
            //LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << dbNameWarehouse << ") built and cached " << cntr << ".: " << etaDelayEvaluation);
        }

        if (cntr == 0)
        {
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << dbNameWarehouse << ") NO EtaDelayEvaluation data found in DB. Using fallback!");
        }
    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

void ShipmentTrackingRepositoryBuilder::ensureEtaDelayPresentationIsFilled(const basar::VarString& dbNameWarehouse, const basar::Int16& branchNo)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, ensureEtaDelayPresentationIsFilled);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    try
    {
        EtaDelayPresentationMap::const_iterator it = m_EtaDelayPresentationCache.find(branchNo);
        if (it != m_EtaDelayPresentationCache.end())
        {
            //LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << dbNameWarehouse << ", branchNo: " << branchNo << ") found: " << it->second);
            m_etaDelayPresentation = it->second;
        }

        basar::db::sql::ResultsetRef resultset = m_Accessor->select(
            EtaDelayPresentationSQLMapper::getSelectSQL(dbNameWarehouse, branchNo)
        );

        EtaDelayPresentationPtr etaDelayPresentation = boost::make_shared<EtaDelayPresentation>();
        if (resultset.next())
        {
            EtaDelayPresentationSQLMapper mapper(etaDelayPresentation, resultset);
            mapper.map();
        }
        else
        {
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << dbNameWarehouse << ", branchNo: " << branchNo << ") is missing in DB. Using fallback!");

            EtaDelayPresentationSQLMapper mapper(etaDelayPresentation, resultset);
            mapper.setFallback(branchNo);
        }

        m_EtaDelayPresentationCache[branchNo] = etaDelayPresentation;

        //LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << dbNameWarehouse << ", branchNo: " << branchNo << ") built and cached: " << etaDelayPresentation);

        m_etaDelayPresentation = etaDelayPresentation;
    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

void ShipmentTrackingRepositoryBuilder::ensureTransmedStatusDeliveredToCustomerIdsCacheIsFilled(const basar::VarString& dbNameWarehouse)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, ensureTransmedStatusDeliveredToCustomerIdsCacheIsFilled);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << " Cache size:" << m_Context->getTransmedStatusDeliveredToCustomerIdsCache().length());

    if (m_Context->getTransmedStatusDeliveredToCustomerIdsCache().length() > 0)
    {
        return;
    }

    try
    {
        basar::db::sql::ResultsetRef resultset = m_Accessor->select(
            TransmedStatusIdDeliveredToCustomerSqlFetcher::getSelectSQL(dbNameWarehouse)
        );

        int cntr = 0;
        std::stringstream sTransmedStatusDeliveredToCustomerIds;
        while (resultset.next())
        {
            TransmedStatusIdDeliveredToCustomerSqlFetcher fetcher(resultset);
            basar::Int16 transmedStatusIdDeliveredToCustomer = fetcher.fetch();

            if (transmedStatusIdDeliveredToCustomer == 7127)
            {
                // Backdoor - config for elevated Verbose CSC TnT tracing:
                m_Context->VerboseTracing = true;
                continue;
            }

            cntr++;
            if (cntr > 1)
            {
                sTransmedStatusDeliveredToCustomerIds << ", ";
            }

            sTransmedStatusDeliveredToCustomerIds << transmedStatusIdDeliveredToCustomer;
        }

        if (cntr == 0)
        {
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << dbNameWarehouse << ") NO EtaDelayEvaluation data found in DB!");
            sTransmedStatusDeliveredToCustomerIds << "null";
        }

        m_Context->setTransmedStatusDeliveredToCustomerIdsCache(sTransmedStatusDeliveredToCustomerIds.str());
        //LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << dbNameWarehouse << ") built and cached " << cntr << ".: " << m_Context->getTransmedStatusDeliveredToCustomerIdsCache());
    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// BUILD TnT DATA Methods
/////////////////////////////////////////////////////////////////////////////////////
void ShipmentTrackingRepositoryBuilder::constructFromOutboundData()
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, constructFromOutboundData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << m_Context->DbNameOutbound << ")");

    try
    {
        basar::db::sql::ResultsetRef resultSet = m_Accessor->select(
            ShipmentTrackingRepositorySqlBuilder::getOutboundDataSelectSQL(*m_Context.get())
        );

        //m_CntProcessedOutboundRows = 0;
        while (resultSet.next())
        {
            m_CntProcessedOutboundRows++;

            //ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder =
            getOrCreateOutboundPackageInfo(resultSet);
        }

        if (m_CntProcessedOutboundRows == 0)
        {
            LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "NO ShipmentTrackingTourInformation data found in DB.");
        }
    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// BUILD TourIds Methods
/////////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> ShipmentTrackingRepositoryBuilder::constructFromOutboundDataTourIDs(const basar::Int32& TourDate)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, constructFromOutboundData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << m_Context->DbNameOutbound << ")");

    std::vector<std::string> tourIDVector;

    try
    {
        basar::db::sql::ResultsetRef resultSet = m_Accessor->select(ShipmentTrackingRepositorySqlBuilder::getOutboundDataSelectSQLTourIDs(*m_Context.get(), TourDate));

        m_CntProcessedOutboundRows = 0;
        while (resultSet.next())
        {
            m_CntProcessedOutboundRows++;

            std::string touridString = resultSet.getString("tourid");
            tourIDVector.push_back(touridString);
        }

        if (m_CntProcessedOutboundRows == 0)
        {
            LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "NO ShipmentTrackingTourInformation data found in DB.");
        }

        return tourIDVector;
    }
    catch (basar::Exception& ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// BUILD IDFs for TourIds Methods
/////////////////////////////////////////////////////////////////////////////////////
std::map<std::string, std::vector<int> > ShipmentTrackingRepositoryBuilder::constructFromOutboundDataTourID_IDFS(const std::vector<std::string>& tourIDs, const basar::Int32& TourDate)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, constructFromOutboundData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << m_Context->DbNameOutbound << ")");

    std::map<std::string, std::vector<int> > theTourIDFMap;

    try
    {
        basar::db::sql::ResultsetRef resultSet = m_Accessor->select(
            ShipmentTrackingRepositorySqlBuilder::getOutboundDataSelectSQLTourID_IDFS(*m_Context.get(), tourIDs, TourDate));


        //Loop over vector to get all IDFs for a tourID
        std::map<std::string, std::vector<int> >::iterator it;
        while (resultSet.next())
        {
            
            std::string tourid = resultSet.getString("tourid");
            int idf = resultSet.getInt32("idfnr");

            //TourId exists in vector
            if ( theTourIDFMap.find(tourid) != theTourIDFMap.end() )
            {
                //IDF map of TourIDF needs to be expanded 
                it = theTourIDFMap.find(tourid);
                it->second.push_back(idf);
            }
            else
            {
                //TourId needs to be into the map with new IDF vector
                std::vector<int> localidfvector;
                localidfvector.push_back(idf);
                theTourIDFMap.insert( std::pair<std::string, std::vector<int> >(tourid, localidfvector) );
            }
        }

        if (m_CntProcessedOutboundRows == 0)
        {
            LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "NO ShipmentTrackingTourInformation data found in DB.");
        }
    }
    catch (basar::Exception& ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }

    return theTourIDFMap;
}

/////////////////////////////////////////////////////////////////////////////////////
// getOrCreateOutboundTourInfo(resultSet)
/////////////////////////////////////////////////////////////////////////////////////
ShipmentTrackingTourInformationSQLMapperPtr ShipmentTrackingRepositoryBuilder::getOrCreateOutboundTourInfo(const basar::db::sql::ResultsetRef resultSet)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, getOrCreateOutboundTourInfo);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    try
    {
        // Construct TourInfo:
        ShipmentTrackingTourInformationPtr tourInformation = boost::make_shared<ShipmentTrackingTourInformation>();
        ShipmentTrackingTourInformationSQLMapperPtr tourInfoBuilder = boost::make_shared<ShipmentTrackingTourInformationSQLMapper>(tourInformation);
        tourInfoBuilder->mapShipmentTrackingTourInformationFromOutboundData(resultSet);

        std::string tourInfoKey = tourInformation->getMapKey();

        // Try get tour:
        ShipmentTrackingTourInformationSQLMapperMap::iterator previousTourInfoIter = m_TourInformationBuilderMap.find(tourInfoKey);

        if (previousTourInfoIter != m_TourInformationBuilderMap.end())
        {
            return previousTourInfoIter->second;
        }

        // Add the new Tour Info to RESULT SET:
        m_TourInformationCollection->push_back(tourInformation);

        // Store builder in map:
        m_TourInformationBuilderMap.insert(std::make_pair(tourInfoKey, tourInfoBuilder));

        return tourInfoBuilder;
    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// getOrCreateOutboundPackageInfo(tourInformationBuilder, resultSet)
/////////////////////////////////////////////////////////////////////////////////////
void ShipmentTrackingRepositoryBuilder::getOrCreateOutboundPackageInfo(const basar::db::sql::ResultsetRef resultSet)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, getOrCreateOutboundPackageInfo);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    try
    {
        // From Outbound point of view, this is the separation to "totes":
        basar::Int32  cscOrderNo = resultSet.getInt32("cscorderno");        // <- (a)kdauftrag.kdauftragnr as cscOrderNo
        bool          isNarcotic = resultSet.getInt32("isNarcotic") == 1;   // <- bitand(artikelzentral.etartklasse1, 512) = 512 / dktsv.tsv_vsw_btm 'J'/'N'
        basar::Int32 iCscOrderNo = resultSet.getInt32("icscorderno");       // <- (a)kdauftrag.kdauftragnr as cscOrderNo


        std::stringstream outbPackageInfoKeyStrm;
        outbPackageInfoKeyStrm << cscOrderNo << "-" << isNarcotic << "-" << iCscOrderNo;
        std::string packageInfoKey = outbPackageInfoKeyStrm.str();
        bool basicKeyInMap = false;

        // --------------------
        // Try get PackageInfo:
        ShipmentTrackingPackageInformationSQLMapperStrMap::iterator previousPackageInfoIter = m_OutboundPackageInformationBuilderMap.find(packageInfoKey);

        // Handle different possition tours of an Order which is not closed:
        ShipmentTrackingTourInformationSQLMapperPtr tourInformationBuilder;
        ShipmentTrackingPackageInformationSQLMapperPtr packageInfoBuilder;
        bool isOrderClosed = false;
        if (previousPackageInfoIter != m_OutboundPackageInformationBuilderMap.end())
        {
            basicKeyInMap = true;
            isOrderClosed = previousPackageInfoIter->second->getPackageInformation()->getPackageProperties()->isOrderClosed();
            if (isOrderClosed)
            {
                // if order closed -> CscOrderNo is tour-purified => no necessity to recompute the tour, so just tak the found PackageInfoBuilder:
                packageInfoBuilder = previousPackageInfoIter->second;
            }
            else
            {
                // if order is not closed yet, compute tour for each line:
                tourInformationBuilder = getOrCreateOutboundTourInfo(resultSet);

                // if order is not closed yet, we compute tour for each line separately.
                // So the packageInfoKey must contain also the tour key!
                // => extend the lookup packageInfoKey and look again if we have a package match:
                outbPackageInfoKeyStrm << "-" << tourInformationBuilder->getTourInformation()->getMapKey();
                packageInfoKey = outbPackageInfoKeyStrm.str();

                // retry to find a PackageInfo:
                previousPackageInfoIter = m_OutboundPackageInformationBuilderMap.find(packageInfoKey);
                if (previousPackageInfoIter != m_OutboundPackageInformationBuilderMap.end())
                {
                    packageInfoBuilder = previousPackageInfoIter->second;
                }
                // else create a new PackageInfo
            }
        }


        // ----------------------
        // Update:
        ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder;
        bool isIbtOrderClosed = false;
        if (packageInfoBuilder.get() != NULL)
        {
            if (iCscOrderNo > 0) // very simple NULL reference protection
            {
                isIbtOrderClosed = packageInfoBuilder->getPackageInformation()->getIbtInformation()->getPackageProperties()->isOrderClosed();
            }

            if (m_Context->Filter.DetailsDesired)
            {
                // add next detail:
                lineDetailBuilder = packageInfoBuilder->addNextLineDetailFromOutboundData(resultSet, isNarcotic);
            }
            //else --> nothing to do here... => continue to the finish of this method
        }
        else
        {
            // ----------------------
            // Construct PackageInfo:
            if (tourInformationBuilder.get() == NULL)
            {
                // we land here only on a very first DB data row of each Customer-CscOrderNo.
                // Else for orders, which are not closed yet, we got the tourInformationBuilder through an up above lookup
                tourInformationBuilder = getOrCreateOutboundTourInfo(resultSet);
            }

            packageInfoBuilder = boost::make_shared<ShipmentTrackingPackageInformationSQLMapper>(m_Context, tourInformationBuilder);
            lineDetailBuilder = packageInfoBuilder->mapFromOutboundDataAndJoinTourInfo(resultSet, cscOrderNo, isNarcotic, iCscOrderNo);

            // Invalidate result set in Builder:

            // -------------------
            // Store all new info:

            // Store the new Package Info builder in map:
            //NOTE: here the packageInfoKey can be either without or already Tour-MapKey decoration
            m_OutboundPackageInformationBuilderMap.insert(std::make_pair(packageInfoKey, packageInfoBuilder));

            isOrderClosed = basicKeyInMap ?
                false : // <-- if we are here, and the: (basicKeyInMap == true) => then the current order can not be closed
                packageInfoBuilder->getPackageInformation()->getPackageProperties()->isOrderClosed(); // <-- else we must get it explicitely

            if (!basicKeyInMap &&   // <-- i.e. if we didn't decorated the packageInfoKey with Tour-MapKey yet
                !isOrderClosed      // <-- AND the current order is NOT closed:
                )
            {
                // then decorate it with Tour-MapKey and store it:

                //NOTE: if order is not closed yet, we compute tour for each line:
                outbPackageInfoKeyStrm << "-" << tourInformationBuilder->getTourInformation()->getMapKey();
                packageInfoKey = outbPackageInfoKeyStrm.str();

                m_OutboundPackageInformationBuilderMap.insert(std::make_pair(packageInfoKey, packageInfoBuilder));
            }

            // Collect PickingDates and CscOrderNo to select Warehouse data in a 2nd step:

            // ------------------
            // store CscOrderNo-s and Picking Dates for later WHS mapping, if orders are closed:
            if (isOrderClosed)
            {
                m_CscOrderNosForWhsQuery[cscOrderNo] = true;

                const basar::DateTime& orderClosedAt = packageInfoBuilder->getPackageInformation()->getPackageProperties()->getOrderClosedAt();
                m_PickingDatesForWhsQuery[orderClosedAt.getDate()] = true;
            }

            // IBT -> store CscOrderNo & Picking Date:
            //NOTE: IBT Order can be closed, while the Local Order is still not closed
            if (iCscOrderNo > 0 &&
                packageInfoBuilder->getPackageInformation()->getIbtInformation()->getPackageProperties()->isOrderClosed()
                )
            {
                isIbtOrderClosed = true;

                m_CscOrderNosForWhsQuery[iCscOrderNo] = true;
                const basar::DateTime& iOrderClosedAt = packageInfoBuilder->getPackageInformation()->getIbtInformation()->getPackageProperties()->getOrderClosedAt();
                m_PickingDatesForWhsQuery[iOrderClosedAt.getDate()] = true;
            }
        }

        // -----------------------------------------------------
        // Store the Customer- and IBT-OrderToPackageMapMakerPtr
        ShipmentTrackingCustomerOrderToPackageMapMakerPtr customerOrderToPackageMapMaker;
        if (isOrderClosed)
        {
            //NOTE: only store this Mapper info, if the Local Order is closed. Else, the Order is not tour purified!

            ShipmentTrackingCustomerOrderToPackageMapMakerInt32Map::iterator customerOrderToPackageMapMakerIter = m_CustomerOrderToPackageMapMakerMap.find(cscOrderNo);
            if (customerOrderToPackageMapMakerIter != m_CustomerOrderToPackageMapMakerMap.end())
            {
                customerOrderToPackageMapMaker = customerOrderToPackageMapMakerIter->second;
            }
            else
            {
                customerOrderToPackageMapMaker = boost::make_shared<ShipmentTrackingCustomerOrderToPackageMapMaker>(m_Context);
                m_CustomerOrderToPackageMapMakerMap[cscOrderNo] = customerOrderToPackageMapMaker;
            }

            if (iCscOrderNo == 0)
            {
                // only store this info, if we are handling a Locally Picked Line!
                customerOrderToPackageMapMaker->addLineToPackageMapping(packageInfoBuilder, lineDetailBuilder);
            }
        }

        if (isIbtOrderClosed)
        {
            //NOTE: only store this Mapper info, if the IBT Order is closed. Else, the Order is not tour purified!

            ShipmentTrackingIbtOrderToPackageMapMakerPtr ibtOrderToPackageMapMaker;
            ShipmentTrackingIbtOrderToPackageMapMakerInt32Map::iterator ibtOrderToPackageMapMakerIter = m_IbtOrderToPackageMapMakerMap.find(iCscOrderNo);
            if (ibtOrderToPackageMapMakerIter != m_IbtOrderToPackageMapMakerMap.end())
            {
                ibtOrderToPackageMapMaker = ibtOrderToPackageMapMakerIter->second;
            }
            else
            {
                ibtOrderToPackageMapMaker = boost::make_shared<ShipmentTrackingIbtOrderToPackageMapMaker>(m_Context);
                m_IbtOrderToPackageMapMakerMap[iCscOrderNo] = ibtOrderToPackageMapMaker;
            }

            if (customerOrderToPackageMapMaker.get() != NULL)
            {
                customerOrderToPackageMapMaker->linkNewIbtOrderToPackageMapMaker(iCscOrderNo, ibtOrderToPackageMapMaker);
            }

            ibtOrderToPackageMapMaker->addLineToPackageMapping(packageInfoBuilder, lineDetailBuilder);
        }
    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// constructFromWarehouseData(dbNameWarehouse, filter)
/////////////////////////////////////////////////////////////////////////////////////
void ShipmentTrackingRepositoryBuilder::constructFromWarehouseData()
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, constructFromWarehouseData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << m_Context->DbNameWarehouse << ")");

    try
    {
        if (m_PickingDatesForWhsQuery.size() == 0 || m_CscOrderNosForWhsQuery.size() == 0)
        {
            LOG4CPLUS_DEBUG(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "NO PickingDates: " << m_PickingDatesForWhsQuery.size() << " or CscOrderNo-s: " << m_CscOrderNosForWhsQuery.size() << " available to select data from Warehouse DB.");
            return;
        }

        basar::db::sql::ResultsetRef resultSet = m_Accessor->select(
            ShipmentTrackingRepositorySqlBuilder::getWarehouseDataSelectSQL(
                *m_Context.get(),
                m_PickingDatesForWhsQuery,
                m_CscOrderNosForWhsQuery
            )
        );

        ShipmentTrackingCurrentWhsLineContextCollection postponedIbtLinesWithoutIbtLocalInfo;

        //m_CntProcessedWhsRows = 0;
        while (resultSet.next())
        {
            m_CntProcessedWhsRows++;

            ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext = ShipmentTrackingCurrentWhsLineContext::create(m_Context, resultSet, m_CntProcessedWhsRows);


            ShipmentTrackingCustomerOrderToPackageMapMakerInt32Map::iterator customerOrderToPackageMapMakerIter = m_CustomerOrderToPackageMapMakerMap.find(currentWhsLineContext->getCscOrderNo());

            // ----------------------------------------------
            // Try to get an already created WHS PackageInfo:
            ShipmentTrackingPackageInformationSQLMapperStrMap::iterator previousWhsPackageInfoIter = m_WarhousePackageInformationBuilderMap.find(currentWhsLineContext->getWhsPackageInfoKey());
            if (previousWhsPackageInfoIter != m_WarhousePackageInformationBuilderMap.end())
            {
                currentWhsLineContext->setWhsPackageInfoBuilder(previousWhsPackageInfoIter->second);
            }

            // -----------------------
            // Process: KZLK=V record:
            if (currentWhsLineContext->isIbtLocal())
            {
                // processing for the KZLK=V record
                if (currentWhsLineContext->getWhsPackageInfoBuilder().get() == NULL)
                {
                    // Try to create it:
                    if (customerOrderToPackageMapMakerIter == m_CustomerOrderToPackageMapMakerMap.end())
                    {
                        // Don't throw, report and just continue:
                        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO m_CustomerOrderToPackageMapMakerMap found searching for cscOrderNo: " << currentWhsLineContext);
                        continue;
                    }

                    currentWhsLineContext->setWhsPackageInfoBuilder(
                        customerOrderToPackageMapMakerIter->second->createIbtLocalWhsPackageInfo(
                            currentWhsLineContext->getCscOrderNo(),
                            currentWhsLineContext->isNarcotic()
                        )
                    );

                    currentWhsLineContext->setIsFirstTotePositionLine(true);
                }

                if (currentWhsLineContext->getWhsPackageInfoBuilder().get() != NULL)
                {
                    currentWhsLineContext->getWhsPackageInfoBuilder()->mapFromWarehouseData(currentWhsLineContext);
                }
                else
                {
                    continue; // --> error is already reported
                }
            }
            else if (currentWhsLineContext->isDeleted())
            {
                if (currentWhsLineContext->getWhsPackageInfoBuilder().get() == NULL)
                {
                    // Don't throw, report and just continue:
                    LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! Tote deleted and no WhsPackageInfoBuilder available! " << currentWhsLineContext);
                    continue;
                }
                else
                {
                    //LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Processing Tote Deleted DKTSV instruction: " << currentWhsLineContext);
                    currentWhsLineContext->getWhsPackageInfoBuilder()->mapFromWarehouseData(currentWhsLineContext);
                }
            }
            else
            {
                // -----------------------
                // find the orderToPackageMapMaker for content data mapping:
                ShipmentTrackingOrderToPackageMapMakerBasePtr orderToPackageMapMaker;

                if (customerOrderToPackageMapMakerIter != m_CustomerOrderToPackageMapMakerMap.end())
                {
                    orderToPackageMapMaker = customerOrderToPackageMapMakerIter->second;
                }
                else if (!m_Context->Filter.DetailsDesired &&                       // if we are not precessing details AND
                    currentWhsLineContext->getWhsPackageInfoBuilder().get() == NULL // if we don't have a WhsPackageInfoBuilder from a previously processed IBT Local (Dktsv.KZLK=V) yet, then:
                    )
                {
                    // ... then postpone the processing of this line after all other lines is done,
                    // so that all IBT Local totes (Dktsv.KZLK=V) are matched with theit IBT remote totes
                    postponedIbtLinesWithoutIbtLocalInfo.push_back(currentWhsLineContext);
                    continue;
                }
                else
                {
                    ShipmentTrackingIbtOrderToPackageMapMakerInt32Map::iterator ibtOrderToPackageMapMakerIter = m_IbtOrderToPackageMapMakerMap.find(currentWhsLineContext->getCscOrderNo());
                    if (ibtOrderToPackageMapMakerIter == m_IbtOrderToPackageMapMakerMap.end())
                    {
                        // Don't throw, report and just continue:
                        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO: m_CustomerOrderToPackageMapMakerMap AND NO: m_IbtOrderToPackageMapMakerMap found searching for cscOrderNo: " << currentWhsLineContext);
                        continue;
                    }
                    orderToPackageMapMaker = ibtOrderToPackageMapMakerIter->second;
                }

                // ---------------------------------------------
                // if whsPackageInfo is NULL, it will be created. If it exists, it will be updated:
                orderToPackageMapMaker->extractAndUpdateNextLineDetail(currentWhsLineContext);
            }

            // ---------------------------------------------
            // Finish -> do tote redirects if the updaters returned a non NULL Ptr in whsPackageInfoBuilder:
            processTourRedirections(currentWhsLineContext);
        } // while (resultSet.next())


        // ---------------------------------------------
        // DO Postprocessing of the Remote IBT lines, which do not have WhsPackageInfoBuilder from a previously processed IBT Local (Dktsv.KZLK=V) yet
        //m_CntPostProcessedWhsRows = 0;
        for (ShipmentTrackingCurrentWhsLineContextCollection::const_iterator currentWhsLineContextIter = postponedIbtLinesWithoutIbtLocalInfo.begin();
            currentWhsLineContextIter != postponedIbtLinesWithoutIbtLocalInfo.end();
            currentWhsLineContextIter++, m_CntPostProcessedWhsRows++
            )
        {
            ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext = *currentWhsLineContextIter;

            ShipmentTrackingIbtOrderToPackageMapMakerInt32Map::iterator ibtOrderToPackageMapMakerIter = m_IbtOrderToPackageMapMakerMap.find(currentWhsLineContext->getCscOrderNo());
            if (ibtOrderToPackageMapMakerIter == m_IbtOrderToPackageMapMakerMap.end())
            {
                // Don't throw, report and just continue:
                LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! NO: m_CustomerOrderToPackageMapMakerMap AND NO: m_IbtOrderToPackageMapMakerMap found searching in postprocessing for cscOrderNo: " << currentWhsLineContext);
                continue;
            }

            ShipmentTrackingOrderToPackageMapMakerBasePtr orderToPackageMapMaker = ibtOrderToPackageMapMakerIter->second;

            // if whsPackageInfo is NULL, it will be created. If it exists, it will be updated:
            orderToPackageMapMaker->extractAndUpdateNextLineDetail(currentWhsLineContext);

            // Finish -> do tote redirects if the updaters returned a non NULL Ptr in whsPackageInfoBuilder:
            processTourRedirections(currentWhsLineContext);
        }


        // ---------------------------------------------
        // FINISH:
        // Count Total Confirmed Delivery Quantities:
        for (ShipmentTrackingPackageInformationSQLMapperStrMap::iterator whsPackageInfoBuiderIter = m_WarhousePackageInformationBuilderMap.begin();
            whsPackageInfoBuiderIter != m_WarhousePackageInformationBuilderMap.end();
            whsPackageInfoBuiderIter++
            )
        {
            whsPackageInfoBuiderIter->second->UpdateTotalConfirmedDeliveryQuantities();
        }

    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// processTourRedirections(currentWhsLineContext)
/////////////////////////////////////////////////////////////////////////////////////
void ShipmentTrackingRepositoryBuilder::processTourRedirections(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, processTourRedirections);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // Finish -> do tote redirects if the updaters returned a non NULL Ptr in whsPackageInfoBuilder:

    if (!currentWhsLineContext->isFirstTotePositionLine())
    {
        // if here, then the WHS package was already created -> no need to update in ShipmentTrackingRepositoryBuilder
        return;
    }
    // handle new Tote:

    // remember the new "whsPackageInfoBuilder"
    m_WarhousePackageInformationBuilderMap[currentWhsLineContext->getWhsPackageInfoKey()] = currentWhsLineContext->getWhsPackageInfoBuilder();

    std::string tourWhsPackageMapKey =
        currentWhsLineContext->getWhsPackageInfoBuilder()->getPackageInformation()->getTourData()->getMapKey() +
        "-" +
        currentWhsLineContext->getWhsPackageInfoBuilder()->getPackageInformation()->getWarehouseMapKey()
        ;

    m_TourToWhsPackageInformationBuilderMap[tourWhsPackageMapKey] = currentWhsLineContext->getWhsPackageInfoBuilder();

    ShipmentTrackingTourDataPtr redirectedToTourData = currentWhsLineContext->getWhsPackageInfoBuilder()->getPackageInformation()->getRedirectedToTourData();
    if (redirectedToTourData.get() == NULL)
    {
        return;
    }
    //else: handle redirects:

    std::string redirectedToTourWhsPackageMapKey =
        redirectedToTourData->getMapKey() +
        "-" +
        currentWhsLineContext->getWhsPackageInfoBuilder()->getPackageInformation()->getWarehouseMapKey()
        ;
    ShipmentTrackingPackageInformationSQLMapperStrMap::iterator redirectedWhsPackageInfoBuilderIter = m_TourToWhsPackageInformationBuilderMap.find(redirectedToTourWhsPackageMapKey);

    if (redirectedWhsPackageInfoBuilderIter != m_TourToWhsPackageInformationBuilderMap.end())
    {
        // nothing to do, already created a redirect
    }
    else
    {
        ShipmentTrackingTourInformationSQLMapperPtr redirectedToTourInfoBuilder = getOrCreateWarehouseTourInfo(redirectedToTourData);

        ShipmentTrackingPackageInformationSQLMapperPtr redirectedWhsPackageInfoBuilder = boost::make_shared<ShipmentTrackingPackageInformationSQLMapper>(m_Context, redirectedToTourInfoBuilder);
        redirectedWhsPackageInfoBuilder->updateCloneFromTourRedirectionSource(*currentWhsLineContext->getWhsPackageInfoBuilder().get());

        //NOTE: DO NOT STORE the new "redirectedWhsPackageInfoBuilder" to m_WarhousePackageInformationBuilderMap !!
        m_TourToWhsPackageInformationBuilderMap[redirectedToTourWhsPackageMapKey] = redirectedWhsPackageInfoBuilder;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// getOrCreateOutboundTourInfo(resultSet)
/////////////////////////////////////////////////////////////////////////////////////
ShipmentTrackingTourInformationSQLMapperPtr ShipmentTrackingRepositoryBuilder::getOrCreateWarehouseTourInfo(ShipmentTrackingTourDataPtr redirectedToTourData)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, getOrCreateWarehouseTourInfo);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    try
    {
        std::string tourInfoKey = redirectedToTourData->getMapKey();

        // Try get tour:
        ShipmentTrackingTourInformationSQLMapperMap::iterator previousTourInfoIter = m_TourInformationBuilderMap.find(tourInfoKey);

        if (previousTourInfoIter != m_TourInformationBuilderMap.end())
        {
            return previousTourInfoIter->second;
        }

        // Construct TourInfo:
        ShipmentTrackingTourInformationPtr tourInformation = boost::make_shared<ShipmentTrackingTourInformation>();
        ShipmentTrackingTourInformationSQLMapperPtr tourInfoBuilder = boost::make_shared<ShipmentTrackingTourInformationSQLMapper>(tourInformation);
        tourInfoBuilder->mapShipmentTrackingTourInformationFromWarehouseData(redirectedToTourData);


        // Add the new Tour Info to RESULT SET:
        m_TourInformationCollection->push_back(tourInformation);

        // Store builder in map:
        m_TourInformationBuilderMap.insert(std::make_pair(tourInfoKey, tourInfoBuilder));

        return tourInfoBuilder;
    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// getTimesDataAndComputeDelay(dbNameWarehouse)
/////////////////////////////////////////////////////////////////////////////////////
ShipmentTrackingTourInformation* tntSTTourInfoTracingHelper(ShipmentTrackingTourInformationPtr tourInfo, bool doTraceIt)
{
    return doTraceIt ? tourInfo.get() : NULL;
}

void ShipmentTrackingRepositoryBuilder::getTimesDataAndComputeDelay(const basar::VarString& dbNameWarehouse)
{
    METHODNAME_DEF(ShipmentTrackingRepositoryBuilder, getTimesDataAndComputeDelay);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "(" << dbNameWarehouse << ")");

    try
    {
        int posNr = 1;
        for (ShipmentTrackingTourInformationCollection::const_iterator tourIter = m_TourInformationCollection->begin();
            tourIter != m_TourInformationCollection->end();
            tourIter++, posNr++
            )
        {
            // sanity check:
            if (NULL == *tourIter ||
                NULL == (*tourIter).get() ||
                NULL == (*tourIter)->getPackageInformationCollection().get() ||
                NULL == (*tourIter)->getPackageInformationCollection()->front().get()
                )
            {
                LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Tour Info or Package Info is NULL. Skipping TnT record! " << posNr << ".: " << tntSTTourInfoTracingHelper(*tourIter, m_Context->VerboseTracing));
                continue;
            }

            m_CntReportedTotes += static_cast<int>((*tourIter)->getPackageInformationCollection()->size());

            // Collect PickingDates and Barcodes valid for this tour:
            std::list<basar::Int32> pickingDateList;
            std::list<basar::VarString> trackingBarcodeList;

            (*tourIter)->getValidPickingDateAndBarcodeList(pickingDateList, trackingBarcodeList);

            // After collecting all the Barcodes and PickingDates -> Query the ETA and DeliveredAt!
            ShipmentTrackingEtaAndDeliveryDataSQLMapper etaSqlMapper((*tourIter)->getEtaAndDeliveryData());

            if (pickingDateList.size() > 0 && trackingBarcodeList.size() > 0)
            {
                basar::db::sql::ResultsetRef resultset = m_Accessor->select(
                    etaSqlMapper.getSelectSQL(
                        dbNameWarehouse,
                        pickingDateList,
                        trackingBarcodeList,
                        m_Context->getTransmedStatusDeliveredToCustomerIdsCache()
                    )
                );

                if (resultset.next())
                {
                    etaSqlMapper.setResultSet(resultset);
                    etaSqlMapper.mapTimesAndComputeDelay((*tourIter)->getTourData()->getPlannedTimeOfArrival(), m_etaDelayPresentation, m_EtaDelayEvaluationCache);

                    // Finally: Enforced check, if every field of the tour object tree is set now:
                    LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "ETA / Delivery times read and computed: " << posNr << ".: " << tntSTTourInfoTracingHelper(*tourIter, m_Context->VerboseTracing));
                }
                else
                {
                    etaSqlMapper.setTimesAndDelayFallback(m_EtaDelayEvaluationCache);

                    // Finally: Enforced check, if every field of the tour object tree is set now:
                    LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "NO ETA / Delivery time results from DB. Using fallback! " << posNr << ".: " << tntSTTourInfoTracingHelper(*tourIter, m_Context->VerboseTracing));
                }
            }
            else
            {
                etaSqlMapper.setTimesAndDelayFallback(m_EtaDelayEvaluationCache);

                // Finally: Enforced check, if every field of the tour object tree is set now:
                LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "no ETA / Delivery times searched. There is no PickingDate and Barcode yet. " << posNr << ".: " << tntSTTourInfoTracingHelper(*tourIter, m_Context->VerboseTracing));
            }
        }
    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// getResult()
/////////////////////////////////////////////////////////////////////////////////////

bool compareTourMapKeys(const ShipmentTrackingTourInformationPtr& first, const ShipmentTrackingTourInformationPtr& second)
{
    if (first.get() == NULL && second.get() == NULL)
    {
        return true;
    }

    if (first.get() == NULL)
    {
        return true;
    }

    if (second.get() == NULL)
    {
        return false;
    }

    return first->getMapKey().compare(second->getMapKey()) <= 0;
}

ShipmentTrackingTourInformationCollectionPtr ShipmentTrackingRepositoryBuilder::getResult()
{
    m_TourInformationCollection->sort(compareTourMapKeys);

    return m_TourInformationCollection;
}

/////////////////////////////////////////////////////////////////////////////////////
// Get Statistics:
/////////////////////////////////////////////////////////////////////////////////////
std::string ShipmentTrackingRepositoryBuilder::getStatistics()
{
    std::stringstream str;
    str << "PickingDates: " << m_PickingDatesForWhsQuery.size()
        << ", CscOrderNo-s: " << m_CscOrderNosForWhsQuery.size()
        << ", Customer-CscOrderNo-s: " << m_CustomerOrderToPackageMapMakerMap.size()
        << ", IBT-CscOrderNo-s: " << m_IbtOrderToPackageMapMakerMap.size()
        << ", Tours: " << m_TourInformationCollection->size()
        << ", WHS-Totes: " << m_WarhousePackageInformationBuilderMap.size()
        << ", Reported Totes: " << m_CntReportedTotes
        << ", Outbound DB Rows: " << m_CntProcessedOutboundRows
        << ", WHS DB Rows: " << m_CntProcessedWhsRows
        << ", Post Processed WHS DB Rows: " << m_CntPostProcessedWhsRows
        ;

    return str.str();
}

} // end namespace shipmenttracking
} // end namespace libcsc
