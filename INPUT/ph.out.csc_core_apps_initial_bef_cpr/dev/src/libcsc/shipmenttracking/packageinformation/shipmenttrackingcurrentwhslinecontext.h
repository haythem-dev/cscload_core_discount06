#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_CURRENTWHSLINECONTEXT_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_CURRENTWHSLINECONTEXT_H

#include "shipmenttrackingcurrentwhslinecontextptr.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontextptr.h"
#include "shipmenttracking/packageinformation/shipmenttrackingpackageinformationsqlmapperptr.h"
#include "shipmenttracking/packageinformation/shipmenttrackinglinedetailsqlmapperptr.h"

#include <libbasar_definitions.h>
//#include <libbasarcmnutil_bstring.h>
//#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_datetime.h>
#include <persistence/iaccessorptr.h>
#include <libbasardbsql_resultsetref.h>



namespace libcsc {
namespace shipmenttracking {

//! \brief Request Processing Context info, like User's choice, server file config data, etc.
class ShipmentTrackingCurrentWhsLineContext
{
public:

    //! \brief Factory method
    static ShipmentTrackingCurrentWhsLineContextPtr create(
        ShipmentTrackingRequestProcessingContextPtr context,
        const basar::db::sql::ResultsetRef resultSet,
        int resultSetRowPosition
    );


    const ShipmentTrackingRequestProcessingContextPtr geRequestProcessingContext()                  const { return m_Context; }
    const basar::db::sql::ResultsetRef& getResultSet()                                              const { return m_ResultSet; }

    int                         getResultSetRowPosition()   const { return m_ResultSetRowPosition; }

    void setWhsPackageInfoBuilder(ShipmentTrackingPackageInformationSQLMapperPtr whsPackageInfoBuilder)   { m_WhsPackageInfoBuilder = whsPackageInfoBuilder; }
    const ShipmentTrackingPackageInformationSQLMapperPtr getWhsPackageInfoBuilder()                 const { return m_WhsPackageInfoBuilder; }

    void setLineDetailBuilder(ShipmentTrackingLineDetailSQLMapperPtr LineDetailBuilder)                   { m_LineDetailBuilder = LineDetailBuilder; }
    const ShipmentTrackingLineDetailSQLMapperPtr getLineDetailBuilder()                             const { return m_LineDetailBuilder; }

    const basar::VarString&     getTrackingBarcode()        const { return m_TrackingBarcode; }
    const basar::Int32&         getPackageId()              const { return m_PackageId; }
    const basar::Int32&         getCscOrderNo()             const { return m_CscOrderNo; }
    const basar::Int32&         getPickingOrderNo()         const { return m_PickingOrderNo; }
    const basar::Int16&         getPickingOrderPageNo()     const { return m_PickingOrderPageNo; }
    const basar::VarString&     getKzlk()                   const { return m_Kzlk; }
    const basar::VarString&     getToteState()              const { return m_ToteState; }
    const basar::VarString&     getTourId()                 const { return m_TourId; }
    const basar::VarString&     getRedirectedFromTourId()   const { return m_RedirectedFromTourId; }
    const basar::Int32&         getDeliveryDurationInMin()  const { return m_DeliveryDurationInMin; }
    const basar::DateTime&      getInsertDateTime()         const { return m_InsertDateTime; }

    const std::string&          getWhsPackageInfoKey()      const { return m_WhsPackageInfoKey; }
    bool                        isIbtLocal()                const { return m_IsIbtLocal; }
    bool                        isContentChanged()          const { return m_IsContentChanged; }
    bool                        isTourRedirected()          const { return m_IsTourRedirected; }
    bool                        isDeleted()                 const { return m_IsDeleted; }

    const basar::Int32&         getTotePosNr()              const { return m_TotePosNr; }
    const basar::Int32&         getArticleNr()              const { return m_ArticleNr; }
    const basar::Int32&         getWhsOriginalQuantity()    const { return m_WhsOriginalQuantity; }
    bool                        isContainer()               const { return m_IsContainer; }
    bool                        isNarcotic()                const { return m_IsNarcotic; }
    
    void setIsFirstTotePositionLine(bool isFirstTotePositionLine)   { m_IsFirstTotePositionLine = isFirstTotePositionLine; }
    bool                        isFirstTotePositionLine()   const { return m_IsFirstTotePositionLine; }

    void setIbtOrderPosNr(basar::Int32 ibtOrderPosNr)       { m_IbtOrderPosNr = ibtOrderPosNr; }
    const basar::Int32&         getIbtOrderPosNr()          const { return m_IbtOrderPosNr; }

private:
    // prohibit user default constructor:
    ShipmentTrackingCurrentWhsLineContext() :
        m_ResultSetRowPosition(0),
        m_PackageId(0),
        m_CscOrderNo(0),
        m_PickingOrderNo(0),
        m_PickingOrderPageNo(0),
        m_DeliveryDurationInMin(0),
        m_IsIbtLocal(false),
        m_IsContentChanged(false),
        m_IsTourRedirected(false),
        m_IsDeleted(false),
        m_TotePosNr(0),
        m_ArticleNr(0),
        m_WhsOriginalQuantity(0),
        m_IsContainer(false),
        m_IsNarcotic(false),
        m_IsFirstTotePositionLine(false),
        m_IbtOrderPosNr(0)
    {}

    ShipmentTrackingCurrentWhsLineContext(
        ShipmentTrackingRequestProcessingContextPtr context,
        const basar::db::sql::ResultsetRef resultSet,
        int resultSetRowPosition
    );

    void initialize();

    // -----
    // DATA:

    ShipmentTrackingRequestProcessingContextPtr     m_Context;
    basar::db::sql::ResultsetRef                    m_ResultSet;

    int                     m_ResultSetRowPosition;

    ShipmentTrackingPackageInformationSQLMapperPtr  m_WhsPackageInfoBuilder;
    ShipmentTrackingLineDetailSQLMapperPtr m_LineDetailBuilder;

    // WHS PackageInfo data:
    basar::VarString        m_TrackingBarcode;
    basar::Int32            m_PackageId;
    basar::Int32            m_CscOrderNo;
    basar::Int32            m_PickingOrderNo;
    basar::Int16            m_PickingOrderPageNo;
    basar::VarString        m_Kzlk;
    basar::VarString        m_ToteState;
    basar::VarString        m_TourId;
    basar::VarString        m_RedirectedFromTourId;
    basar::Int32            m_DeliveryDurationInMin;
    basar::DateTime         m_InsertDateTime;

    std::string             m_WhsPackageInfoKey;
    bool                    m_IsIbtLocal;
    bool                    m_IsContentChanged;
    bool                    m_IsTourRedirected;
    bool                    m_IsDeleted;

    // WHS LineDetail data:
    basar::Int32            m_TotePosNr;
    basar::Int32            m_ArticleNr;
    basar::Int32            m_WhsOriginalQuantity;
    bool                    m_IsContainer;
    bool                    m_IsNarcotic;
    bool                    m_IsFirstTotePositionLine;
    basar::Int32            m_IbtOrderPosNr;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_CURRENTWHSLINECONTEXT_H
