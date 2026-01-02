#include <shipmenttracking/shipmenttrackingrepository.h>
#include <shipmenttracking/shipmenttrackingrepositorybuilder.h>
#include "tourinformation/shipmenttrackingtourinformation.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"

#include <exceptions/sqlduplicateexception.h>

#include <persistence/iaccessor.h>
#include <persistence/iaccessorfactory.h>
#include <persistence/itransactionfactory.h>
#include <util/loggingutils.h>
#include <exceptions/exceptionhelper.h>
#include <parameter/branchparametergetter.h>
#include <boost/make_shared.hpp>


namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingRepository::ShipmentTrackingRepository()
{
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingRepository::ShipmentTrackingRepository()");
}

ShipmentTrackingRepository::~ShipmentTrackingRepository()
{
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingRepository::~ShipmentTrackingRepository()");
}

void ShipmentTrackingRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
{
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingRepository::injectTransactionFactory()");

    m_TransactionFactory = transactionFactory;
}

void ShipmentTrackingRepository::injectAccessorFactory(persistence::IAccessorFactoryPtr accessorFactory)
{
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingRepository::injectAccessorFactory()");

    m_AccessorFactory = accessorFactory;
}

void ShipmentTrackingRepository::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
{
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), "ShipmentTrackingRepository::injectBranchParameterGetter()");

    m_BranchParameterGetter = parameterGetter;
}


/////////////////////////////////////////////////////////////////////////////////////
// PUBLIC Methods
/////////////////////////////////////////////////////////////////////////////////////
ShipmentTrackingTourInformationCollectionPtr ShipmentTrackingRepository::findShipmentTracking(
    const basar::Int16& branchNo,
    const basar::Int32& customerNo,
    ShipmentTrackingDataFilter& filter
)
{
    METHODNAME_DEF(ShipmentTrackingRepository, findShipmentTracking);

    // ------------------------------
    // Check all the params if valid:
    std::stringstream str;
    str << fun << "(" << branchNo << ", " << customerNo << ", " << filter;
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), str.str());

    basar::VarString dbNameOutbound = m_BranchParameterGetter->getDatabaseName(branchNo);
    if (dbNameOutbound.empty())
    {
        LOG4CPLUS_FATAL(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Name for Outbound DB not found!");
        ShipmentTrackingTourInformationCollectionPtr errCaseRetEmptyColl = boost::make_shared<ShipmentTrackingTourInformationCollection>();
        return errCaseRetEmptyColl;
    }

    basar::VarString dbNameWarehouse = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);
    if (dbNameWarehouse.empty())
    {
        LOG4CPLUS_FATAL(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Name for Warehouse DB not found!");
        ShipmentTrackingTourInformationCollectionPtr errCaseRetEmptyColl = boost::make_shared<ShipmentTrackingTourInformationCollection>();
        return errCaseRetEmptyColl;
    }

    if (customerNo < 1)
    {
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Invalid customerNo parameter: " << customerNo);
        ShipmentTrackingTourInformationCollectionPtr errCaseRetEmptyColl = boost::make_shared<ShipmentTrackingTourInformationCollection>();
        return errCaseRetEmptyColl;
    }

    LOG4CPLUS_INFO(libcsc::LoggerPool::getLoggerShipmentTracking(), str.str() << " Start:...");

    //NOTE: in Shipment Trackig (Track and Trace) we always set the Dirty Read!
    // See the Analysis of the: Requirement 9339:TnT auf Dirty Read in pxverbund/libcsc und zurück auf Ode21 von Ode-PA
    // http://tfs:8080/tfs/DefaultCollection/Pharmos/_workitems/edit/9339
    m_AccessorFactory->EnsureDBConnectionWithDirtyRead();


    // --------------------------------------
    // Create BUILDER and play Director role:
    try
    {
        ShipmentTrackingRequestProcessingContext* contextRawCppPointer = new ShipmentTrackingRequestProcessingContext(
            branchNo,
            customerNo,
            filter,
            dbNameOutbound,
            dbNameWarehouse
        );

        ShipmentTrackingRequestProcessingContextPtr contextPtr(contextRawCppPointer);

        persistence::IAccessorPtr accessor = m_AccessorFactory->createAccessor();
        ShipmentTrackingRepositoryBuilder tntBuilder(contextPtr, accessor);


        // Read Config:
        tntBuilder.ensureEtaDelayEvaluationCacheIsFilled(dbNameWarehouse);

        tntBuilder.ensureEtaDelayPresentationIsFilled(dbNameWarehouse, branchNo);

        tntBuilder.ensureTransmedStatusDeliveredToCustomerIdsCacheIsFilled(dbNameWarehouse);

        // Build TnT Data:

        tntBuilder.constructFromOutboundData();

        tntBuilder.constructFromWarehouseData();

        tntBuilder.getTimesDataAndComputeDelay(dbNameWarehouse);

        // Finish: get the result and return it to caller:
        ShipmentTrackingTourInformationCollectionPtr tourInformationCollection = tntBuilder.getResult();

        LOG4CPLUS_INFO(libcsc::LoggerPool::getLoggerShipmentTracking(), str.str() << " DONE: " << tntBuilder.getStatistics());

        return tourInformationCollection;
    }
    catch (basar::Exception & ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

std::vector<std::string> ShipmentTrackingRepository::findTourIDs(
    const basar::Int16& branchNo,
    const basar::Int32& date,
    ShipmentTrackingDataFilter& filter
)
{
    METHODNAME_DEF(ShipmentTrackingRepository, findTourIDs);

    // ------------------------------
    // Check all the params if valid:
    std::stringstream str;
    str << fun << "(" << branchNo << ", " << date;
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), str.str());

    LOG4CPLUS_INFO(libcsc::LoggerPool::getLoggerShipmentTracking(), str.str() << " Start:...");

    basar::VarString dbNameOutbound = m_BranchParameterGetter->getDatabaseName(branchNo);
    basar::VarString dbNameWarehouse = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);

    m_AccessorFactory->EnsureDBConnectionWithDirtyRead();

    // --------------------------------------
    // Create BUILDER and play Director role:
    try
    {
        ShipmentTrackingRequestProcessingContext* contextRawCppPointer = new ShipmentTrackingRequestProcessingContext(
            branchNo,
            0,
            filter,
            dbNameOutbound,
            dbNameWarehouse
        );

        ShipmentTrackingRequestProcessingContextPtr contextPtr(contextRawCppPointer);

        persistence::IAccessorPtr accessor = m_AccessorFactory->createAccessor();
        ShipmentTrackingRepositoryBuilder tntBuilder(contextPtr, accessor);

        // Build TnT Data:
        std::vector<std::string> returnVector = tntBuilder.constructFromOutboundDataTourIDs(date);

        LOG4CPLUS_INFO(libcsc::LoggerPool::getLoggerShipmentTracking(), str.str() << " DONE: " << tntBuilder.getStatistics());

        return returnVector;
    }
    catch (basar::Exception& ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

std::map<std::string, std::vector<int> > ShipmentTrackingRepository::findIDFsforTourIDs(
    const basar::Int16& branchNo,
    const basar::Int32& date,
    ShipmentTrackingDataFilter& filter,
    const std::vector<std::string>& tourIDList
)
{
    METHODNAME_DEF(ShipmentTrackingRepository, findIDFsforTourIDs);
    std::vector<std::vector<int> > tourIDIDFS;

    // ------------------------------
    // Check all the params if valid:
    std::stringstream str;
    str << fun << "(" << branchNo << ", " << date << ", " << tourIDList.size();
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), str.str());

    basar::VarString dbNameOutbound = m_BranchParameterGetter->getDatabaseName(branchNo);
    if (dbNameOutbound.empty())
    {
        LOG4CPLUS_FATAL(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Name for Outbound DB not found!");
        //ShipmentTrackingTourInformationCollectionPtr errCaseRetEmptyColl = boost::make_shared<ShipmentTrackingTourInformationCollection>();
        //return errCaseRetEmptyColl;
    }

    basar::VarString dbNameWarehouse = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);
    if (dbNameWarehouse.empty())
    {
        LOG4CPLUS_FATAL(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Name for Warehouse DB not found!");
        //ShipmentTrackingTourInformationCollectionPtr errCaseRetEmptyColl = boost::make_shared<ShipmentTrackingTourInformationCollection>();
        //return errCaseRetEmptyColl;
    }

    if (branchNo < 1)
    {
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Invalid branchNo parameter: " << branchNo);
        //ShipmentTrackingTourInformationCollectionPtr errCaseRetEmptyColl = boost::make_shared<ShipmentTrackingTourInformationCollection>();
        //return errCaseRetEmptyColl;
    }

    LOG4CPLUS_INFO(libcsc::LoggerPool::getLoggerShipmentTracking(), str.str() << " Start:...");

    //NOTE: in Shipment Trackig (Track and Trace) we always set the Dirty Read!
    // See the Analysis of the: Requirement 9339:TnT auf Dirty Read in pxverbund/libcsc und zurück auf Ode21 von Ode-PA
    // http://tfs:8080/tfs/DefaultCollection/Pharmos/_workitems/edit/9339
    m_AccessorFactory->EnsureDBConnectionWithDirtyRead();

    // --------------------------------------
    // Create BUILDER and play Director role:
    try
    {
        ShipmentTrackingRequestProcessingContext* contextRawCppPointer = new ShipmentTrackingRequestProcessingContext(
            branchNo,
            0,
            filter,
            dbNameOutbound,
            dbNameWarehouse
        );

        ShipmentTrackingRequestProcessingContextPtr contextPtr(contextRawCppPointer);

        persistence::IAccessorPtr accessor = m_AccessorFactory->createAccessor();
        ShipmentTrackingRepositoryBuilder tntBuilder(contextPtr, accessor);

        // Build TnT Data:
        return tntBuilder.constructFromOutboundDataTourID_IDFS(tourIDList, date);
    }
    catch (basar::Exception& ex)
    {
        exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

} // end namespace shipmenttracking
} // end namespace libcsc
