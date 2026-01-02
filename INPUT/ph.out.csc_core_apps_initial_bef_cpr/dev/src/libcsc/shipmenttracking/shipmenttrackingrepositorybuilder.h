#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORYBUILDER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORYBUILDER_H

#include "shipmenttrackingutils.h"
#include "shipmenttrackingdatafilter.h"
#include "shipmenttrackingrequestprocessingcontextptr.h"
#include "shipmenttracking/configuration/etadelayevaluationptr.h"
#include "shipmenttracking/configuration/etadelaypresentationptr.h"
#include "tourinformation/shipmenttrackingtourinformationptr.h"
#include "tourinformation/shipmenttrackingtourinformationsqlmapper.h"
#include "packageinformation/shipmenttrackingpackageinformationsqlmapper.h"
#include "packageinformation/shipmenttrackingcustomerordertopackagemapmaker.h"
#include "packageinformation/shipmenttrackingibtordertopackagemapmaker.h"
#include <persistence/iaccessorptr.h>
#include <persistence/iaccessorfactoryptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <parameter/ibranchparametergetterptr.h>
#include <libbasardbsql_resultsetref.h>



/////////////////////////////////////////////////////////////////////////////////////
// class declaration
/////////////////////////////////////////////////////////////////////////////////////

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingRepositoryBuilder
{
public:
    ShipmentTrackingRepositoryBuilder(
        ShipmentTrackingRequestProcessingContextPtr context,
        persistence::IAccessorPtr accessor
    );
    virtual ~ShipmentTrackingRepositoryBuilder();

    void    ensureEtaDelayEvaluationCacheIsFilled(const basar::VarString& dbName);
    void    ensureEtaDelayPresentationIsFilled(const basar::VarString& dbName, const basar::Int16& branchNo);
    void    ensureTransmedStatusDeliveredToCustomerIdsCacheIsFilled(const basar::VarString& dbName);


    void constructFromOutboundData();

    std::vector<std::string> constructFromOutboundDataTourIDs(const basar::Int32& TourDate);

    std::map<std::string, std::vector<int> > constructFromOutboundDataTourID_IDFS(const std::vector<std::string>& tourIDs, const basar::Int32& TourDate);

    void constructFromWarehouseData();

    void getTimesDataAndComputeDelay(
        const basar::VarString& dbNameWarehouse
    );

    ShipmentTrackingTourInformationCollectionPtr getResult();

    std::string getStatistics();

private:
    ShipmentTrackingTourInformationSQLMapperPtr getOrCreateOutboundTourInfo(const basar::db::sql::ResultsetRef resultSet);
    void processTourRedirections(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext);
    ShipmentTrackingTourInformationSQLMapperPtr getOrCreateWarehouseTourInfo(ShipmentTrackingTourDataPtr redirectedToTourData);
    
    void getOrCreateOutboundPackageInfo(const basar::db::sql::ResultsetRef resultSet);


    // -----
    // DATA:

    //! \brief Request Processing Context info, like User's choice, server file config data, etc.
    ShipmentTrackingRequestProcessingContextPtr             m_Context;

    // Server Config from file:
    persistence::IAccessorPtr               m_Accessor;

    int                                     m_CntReportedTotes;
    int                                     m_CntProcessedOutboundRows;
    int                                     m_CntProcessedWhsRows;
    int                                     m_CntPostProcessedWhsRows;

    // -----

    EtaDelayEvaluationCollection            m_EtaDelayEvaluationCache;
    EtaDelayPresentationPtr                 m_etaDelayPresentation;

    EtaDelayPresentationMap                 m_EtaDelayPresentationCache;

    // -----
    // Repository Builder TnT Data being constructed:

    //! \brief TourInfo Builder map
    ShipmentTrackingTourInformationSQLMapperMap             m_TourInformationBuilderMap;
    
    //! \brief The RESULT SET!
    ShipmentTrackingTourInformationCollectionPtr            m_TourInformationCollection;

    //! \brief CscOderNo+isNarcotic+IbtCscOrderNo --> ShipmentTrackingPackageInformationSQLMapper. Simultaneously this is the "PckageInfo Template" map.
    ShipmentTrackingPackageInformationSQLMapperStrMap       m_OutboundPackageInformationBuilderMap;

    //! \brief Helper for locally picked packages
    ShipmentTrackingCustomerOrderToPackageMapMakerInt32Map  m_CustomerOrderToPackageMapMakerMap;

    //! \brief Helper for IBT picked packages
    ShipmentTrackingIbtOrderToPackageMapMakerInt32Map       m_IbtOrderToPackageMapMakerMap;

    Int32HashSetMap                                         m_CscOrderNosForWhsQuery;
    Int32HashSetMap                                         m_PickingDatesForWhsQuery;


    //! \brief Barcode+ToteNo --> ShipmentTrackingPackageInformationSQLMapper.
    ShipmentTrackingPackageInformationSQLMapperStrMap       m_WarhousePackageInformationBuilderMap;

    //! \brief TourInfo-MapKey + PackageInfo-MapKey --> ShipmentTrackingPackageInformationSQLMapper.
    ShipmentTrackingPackageInformationSQLMapperStrMap       m_TourToWhsPackageInformationBuilderMap;
};


} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORYBUILDER_H
