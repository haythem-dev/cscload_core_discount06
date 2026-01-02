#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATIONSQLMAPPER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATIONSQLMAPPER_H

#include "shipmenttrackingpackageinformationsqlmapperptr.h"
#include "shipmenttrackingpackageinformationmapperbase.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontextptr.h"
#include "shipmenttracking/tourinformation/shipmenttrackingtourinformationsqlmapperptr.h"
#include "shipmenttrackingpackagepropertiessqlmapper.h"
#include "shipmenttrackingibtinformationsqlmapper.h"
#include "shipmenttrackinglinedetailsqlmapper.h"
#include "shipmenttrackingarticletopositionmapperptr.h"
#include "shipmenttrackingcurrentwhslinecontextptr.h"

#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingPackageInformationSQLMapper : public ShipmentTrackingPackageInformationMapperBase
{
public:
    ShipmentTrackingPackageInformationSQLMapper(
        ShipmentTrackingRequestProcessingContextPtr context,
        ShipmentTrackingTourInformationSQLMapperPtr tourInformationBuilder
    );
    virtual ~ShipmentTrackingPackageInformationSQLMapper();

    ShipmentTrackingLineDetailSQLMapperPtr mapFromOutboundDataAndJoinTourInfo(
        const basar::db::sql::ResultsetRef resultSet,
        basar::Int32 cscOrderNo,
        bool isNarcotic,
        basar::Int32 iCscOrderNo
    );

    ShipmentTrackingLineDetailSQLMapperPtr addNextLineDetailFromOutboundData(
        const basar::db::sql::ResultsetRef resultSet,
        bool isNarcotic
    );

    /*! \brief Create a partially shallow, partially deep copy:
               -> Deep copy 1 level: -> just the contained PackageProperties
               -> Shallow copy:      -> DO NOT TAKE Lines and IBT Info at all in this step. Lines will be moved 1 by 1 from Outbound Tote (PackageId == 0) to the here newly created WHS-Tote
                                     -> just link to the same TourData (same for IbtInfo) 
        NOTE: this method results in a subset of createCloneWithTighlyConnectedDataButWithoutLines()
        NOTE: this method is used for cloning the Outbound-PackageInfo into WHS-PackageInfo for early reading IBT Local Info (DKTSV.KZLK=V)
    */
    ShipmentTrackingPackageInformationSQLMapperPtr createCloneWithTighlyConnectedDataButWithoutLinesAndIbt();

    //! \brief Add IBT Clone From Outbound Data. This method is implemed separately due to early handling of IBT Local Info (DKTSV.KZLK=V)
    void addIbtCloneFromOutboundData(const ShipmentTrackingPackageInformationSQLMapper& originalPackageInfoBuilder);

    /*! \brief Create a partially shallow, partially deep copy:
               -> Deep copy 1 level: -> just the contained PackageProperties and same for IbtInfo as for this PackageInfo
               -> Shallow copy:      -> DO NOT TAKE Lines at all in this step. They will be moved 1 by 1 from Outbound Tote (PackageId == 0) to the here newly created WHS-Tote
                                     -> just link to the same TourData (same for IbtInfo) 
        NOTE: this method results in a superset of createCloneWithTighlyConnectedDataButWithoutLinesAndIbt()
        NOTE: this is the very normal cloning of Outbound-PackageInfo into WHS-PackageInfo while reading content lines
    */
    ShipmentTrackingPackageInformationSQLMapperPtr createCloneWithTighlyConnectedDataButWithoutLinesAndRemoveFromTourIfEmpty();

    void removePackageFromTourInformationIfEmtpty();

    //! \brief Make destination redirected Clone From Warehouse Data
    void updateCloneFromTourRedirectionSource(const ShipmentTrackingPackageInformationSQLMapper& originalPackageInfoBuilder);

    ShipmentTrackingLineDetailSQLMapperPtr extractOneOutboundArticleLineAndRemoveFromTourIfEmpty(basar::Int32 articleNr, basar::Int32 whsOriginalQuantity);
    ShipmentTrackingLineDetailSQLMapperPtr extractOneOutboundArticleLineForIbtPosNrAndRemoveFromTourIfEmpty(basar::Int32 ibtOrderPosNr);

    // ---------
    // Warehouse connecting and filling nethods:

    ShipmentTrackingLineDetailSQLMapperPtr getToteLineDetailBuilderForTotePosNr(basar::Int32 totePosNr);
    bool isFirstTotePositionNrOrHasNoLinesYet(basar::Int32 totePosNr) { return m_FirstLineWhsPosNr == 0 || m_FirstLineWhsPosNr == totePosNr; }

    //! \brief Add New Warehouse LineDetailBuilder from a fresh and for WHS yet unused outbound line 
    void addNewWarehouseLineDetailBuilder(
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    );

    //! \brief Reuse lineDetaBuilder from another tote in this WHS Tote for a case, that current CscOrderPos is splitted to more than one tote
    void resuseToteSplittedWarehouseLineDetailBuilder(
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    );

    /*! \brief totePosNr == dktsv.tsv_pos -> it is important for the reading of properties just along with the first line
               NOTE: lineDetailBuilder can be null, if (m_Context->Filter.DetailsDesired == false) */
    void mapFromWarehouseData(
        ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
    );

    //! \brief final update of TotalConfirmedDeliveryQuantities from WHS collected line details. This may only becalled from the end of: ShipmentTrackingRepositoryBuilder::constructFromWarehouseData()
    void UpdateTotalConfirmedDeliveryQuantities();

private:
    // prohibit copy constructor and assignment operator:
    ShipmentTrackingPackageInformationSQLMapper(const ShipmentTrackingPackageInformationSQLMapper&);
    ShipmentTrackingPackageInformationSQLMapper & operator=(const ShipmentTrackingPackageInformationSQLMapper&);

    void setResultSet(const basar::db::sql::ResultsetRef resultSet);

    ShipmentTrackingLineDetailSQLMapperPtr addNextLineDetailFromOutboundDataInner(
        const basar::db::sql::ResultsetRef resultSet,
        bool isNarcotic
    );

    //! \brief Inner Helper
    void storeLineInArticleToPositionMapperMap(
        ShipmentTrackingLineDetailSQLMapperPtr lineDetailBuilder,
        ShipmentTrackingLineDetailPtr lineDetail
    );

    // -----
    // Data:
    //! \brief Request Processing Context info, like User's choice, server file config data, etc.
    ShipmentTrackingRequestProcessingContextPtr             m_Context;

    //! \brief Relation to the originally during CSC Order planned tour:
    ShipmentTrackingTourInformationSQLMapperPtr     m_TourInformationBuilder;

    //! \brief This iterator serves as a handle for removing the "Outbound Package" from the RESULT SET TourInfo, if all the data was taken by Warehouse Package(s)
    ShipmentTrackingPackageInformationCollection::iterator  m_TourOutboundPackageInfoPositionInterator;

    //! \brief This iterator serves as a handle for the insertion point for new "Warehouse Packages" the RESULT SET TourInfo, which correspond to the primerly created Oubtound Package.
    ShipmentTrackingPackageInformationCollection::iterator  m_TourWarehousePackageInfoInsertionInterator;

    //! \brief tightly connected (contains)
    ShipmentTrackingPackagePropertiesSQLMapper      m_PackagePropertiesMapper;

    //! \brief tightly connected (contains)
    ShipmentTrackingIbtInformationSQLMapperPtr      m_IbtInformationMapperPtr;


    // -----
    // Outbound to Warehouse DB data Mappign helpers:
    bool                    m_IsOrderClosed;
    bool                    m_IsIbtPackage;

    //! \brief Cascade of ArticleNr --> CscPosition/expectedDeliveryQuantity --> ShipmentTrackingLineDetailSQLMapper
    ShipmentTrackingArticleToPositionMapperInt32Map m_ArticleToPositionMapperMap;

    //! \brief Customer-CscOrderPosNr --> ShipmentTrackingPackageInformationSQLMapper
    ShipmentTrackingLineDetailSQLMapperInt32Map     m_CustomerOrderPositionToLineDetailBuilderMap;

    //! \brief IBT-CscOrderPosNr --> ShipmentTrackingPackageInformationSQLMapper
    ShipmentTrackingLineDetailSQLMapperInt32Map     m_IbtOrderPositionToLineDetailBuilderMap;

    // ----------------------
    // Warehouse data mapping

    basar::Int32                                    m_FirstLineWhsPosNr;
    bool                                            m_FirstLineIsContentChanged;
    bool                                            m_FirstLineIsTourRedirected;

    basar::Int32                                    m_PreviousLineWhsPosNr;
    bool                                            m_PreviousLineWasContentChanged;
    bool                                            m_PreviousLineWasTourRedirected;

    //! \brief Cascade of TotePosition --> ShipmentTrackingLineDetailSQLMapper for direct updates from next WHS LineDetail info
    ShipmentTrackingLineDetailSQLMapperInt32Map     m_TotePositionToLineDetailBuilderMap;
};


} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATIONSQLMAPPER_H
