#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAIL_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAIL_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/boolean.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_date.h>
#include <libbasar_definitions.h>
#include <iostream>

#include "shipmenttrackinglinedetailptr.h"
#include "shipmenttrackingpackageinformationptr.h"

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingLineDetail
{
    friend class ShipmentTrackingLineDetailMapperBase;

public:
    ShipmentTrackingLineDetail(ShipmentTrackingLineDetailWeakStrToClollectionMapPtr whsToteMapKeyToOrderPositionSplitSiblingLines = ShipmentTrackingLineDetailWeakStrToClollectionMapPtr());
    virtual ~ShipmentTrackingLineDetail();

    const basar::Int32&         getOrderPosNo() const { return m_OrderPosNo; }
    const basar::Int32&         getIbtOrderPosNo() const { return m_IbtOrderPosNo; }
    const basar::Int32&         getTotePosNo() const   { return m_TotePosNo; }
    const basar::Int32&         getExpectedDeliveryQuantity() const { return m_ExpectedDeliveryQuantity; }
    const basar::Int32&         getConfirmedDeliveryQuantity() const { return m_ConfirmedDeliveryQuantity; }
    const basar::Int32&         getArticleNr() const { return m_ArticleNr; }
    const basar::VarString&     getArticleCode() const  { return m_ArticleCode; }
    const basar::VarString&     getArticleName() const  { return m_ArticleName; }
    const libcsc::Bool&         getIsNarcotic() const   { return m_IsNarcotic; }
    const basar::VarString&     getBatch() const { return m_Batch; }

    bool                        hasWarehouseData() const { return m_HasWarehouseData; }

    ShipmentTrackingPackageInformationPtr getOwnerPackageInfo() const { return m_OwnerPackageInfo.lock(); }
    const ShipmentTrackingLineDetailWeakStrToClollectionMapPtr getWhsToteMapKeyToOrderPositionSplitSiblingLines() const { return m_WhsToteMapKeyToOrderPositionSplitSiblingLines; }
    size_t getWhsSiblingToteCount() const { return m_WhsToteMapKeyToOrderPositionSplitSiblingLines->size(); }

    //! \brief Barcode + PackageId -> owner PackageInfo (Tote)
    std::string getWarehouseToteMapKey() const;

    friend std::ostream& ::operator<<(std::ostream& os, const ShipmentTrackingLineDetail& shipmentTrackingLineDetail);

private:
    libcsc::Int32           m_OrderPosNo;
    libcsc::Int32           m_IbtOrderPosNo;
    libcsc::Int32           m_TotePosNo;
    libcsc::Int32           m_ExpectedDeliveryQuantity;
    libcsc::Int32           m_ConfirmedDeliveryQuantity;
    libcsc::Int32           m_ArticleNr;
    libcsc::VarString       m_ArticleCode;
    libcsc::VarString       m_ArticleName;
    libcsc::Bool            m_IsNarcotic;
    libcsc::VarString       m_Batch;

    bool                    m_HasWarehouseData;

    ShipmentTrackingPackageInformationWeakPtr m_OwnerPackageInfo;

    /*! \brief A *SHARED* Map of WhsToteMapKey --> Order-Position Split Sibling Lines of the tote addressed by the WhsToteMapKey. 
        Each Tote has its collection of the split sibling lines, which all together - all over the whole 
        shared map "m_WhsToteMapKeyToOrderPositionSplitSiblingLines" - ressemble a single CSC Order Position/Line.
        NOTE: that this MAP is SHARED and common single data across all related splitted siblig lines and bounds them together! */
    ShipmentTrackingLineDetailWeakStrToClollectionMapPtr m_WhsToteMapKeyToOrderPositionSplitSiblingLines;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAIL_H
