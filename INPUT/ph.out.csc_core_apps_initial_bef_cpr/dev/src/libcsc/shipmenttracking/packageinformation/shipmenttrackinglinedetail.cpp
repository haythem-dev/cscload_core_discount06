#include "shipmenttrackinglinedetail.h"
#include "shipmenttrackingpackageinformation.h"

#include <util/loggingutils.h>
#include <exceptions/exceptionhelper.h>

#include <boost/make_shared.hpp>

namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingLineDetail::ShipmentTrackingLineDetail(ShipmentTrackingLineDetailWeakStrToClollectionMapPtr whsToteMapKeyToOrderPositionSplitSiblingLines) :
    m_HasWarehouseData(false),
    m_WhsToteMapKeyToOrderPositionSplitSiblingLines(whsToteMapKeyToOrderPositionSplitSiblingLines)
{
    m_IbtOrderPosNo = 0;
    m_IbtOrderPosNo.setClean();

    m_TotePosNo = 0;
    m_TotePosNo.setClean();

    m_ConfirmedDeliveryQuantity = 0;
    m_ConfirmedDeliveryQuantity.setClean();

    m_Batch = "";
    m_Batch.setClean();

    if (m_WhsToteMapKeyToOrderPositionSplitSiblingLines.get() == NULL)
    {
        m_WhsToteMapKeyToOrderPositionSplitSiblingLines = boost::make_shared<ShipmentTrackingLineDetailWeakStrToClollectionMap>();
    }
}

ShipmentTrackingLineDetail::~ShipmentTrackingLineDetail()
{
}

std::string ShipmentTrackingLineDetail::getWarehouseToteMapKey() const 
{
    ShipmentTrackingPackageInformationPtr ownerTote = getOwnerPackageInfo(); 
    return ownerTote.get() != NULL ? ownerTote->getWarehouseMapKey() : ""; 
}

} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetail& shipmentTrackingLineDetail)
{
    METHODNAME_DEF(ShipmentTrackingLineDetail, operator<<);
    try
    {
        os << "ST-LineDetail: {"
            << "OrderPosNo: " << shipmentTrackingLineDetail.getOrderPosNo()
            << ", IbtOrderPosNo: " << shipmentTrackingLineDetail.getIbtOrderPosNo()
            << ", TotePosNo: " << shipmentTrackingLineDetail.getTotePosNo()
            << ", ExpectedDeliveryQuantity: " << shipmentTrackingLineDetail.getExpectedDeliveryQuantity()
            << ", ConfirmedDeliveryQuantity: " << shipmentTrackingLineDetail.getConfirmedDeliveryQuantity()
            << ", ArticleNr: " << shipmentTrackingLineDetail.getArticleNr()
            << ", ArticleCode: " << shipmentTrackingLineDetail.getArticleCode()
            << ", ArticleName: " << shipmentTrackingLineDetail.getArticleName()
            << ", IsNarcotic: " << shipmentTrackingLineDetail.getIsNarcotic()
            << ", Batch: " << shipmentTrackingLineDetail.getBatch()
            << ", HasWarehouseData: " << shipmentTrackingLineDetail.hasWarehouseData()
            ;

        if (shipmentTrackingLineDetail.m_WhsToteMapKeyToOrderPositionSplitSiblingLines.get() != NULL &&
            shipmentTrackingLineDetail.m_WhsToteMapKeyToOrderPositionSplitSiblingLines->size() > 1
            )
        {
            os << ", WhsToteMapKeyToOrderPositionSplitSiblingLines: " << shipmentTrackingLineDetail.getWhsToteMapKeyToOrderPositionSplitSiblingLines();
        }

        os << "}";
        return os;
    }
    catch (basar::Exception & ex)
    {
        libcsc::exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetail* shipmentTrackingLineDetail)
{
    if (shipmentTrackingLineDetail != NULL)
    {
        os << *shipmentTrackingLineDetail;
    }
    else
    {
        os << "ST-LineDetail: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailPtr shipmentTrackingLineDetail)
{
    os << shipmentTrackingLineDetail.get();
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakPtr shipmentTrackingLineDetail)
{
    libcsc::shipmenttracking::ShipmentTrackingLineDetailPtr sh = shipmentTrackingLineDetail.lock();
    os << sh.get();
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailCollection& shipmentTrackingLineDetails)
{
    os << "[";


    int ii = 0;
    for (libcsc::shipmenttracking::ShipmentTrackingLineDetailCollection::const_iterator it = shipmentTrackingLineDetails.begin();
        it != shipmentTrackingLineDetails.end();
        it++, ii++
        )
    {
        if (ii > 0)
        {
            os << ", ";
        }

        os << *it;
    }
    os << "]";

    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailCollection* shipmentTrackingLineDetails)
{
    if (shipmentTrackingLineDetails != NULL)
    {
        os << *shipmentTrackingLineDetails;
    }
    else
    {
        os << "ST-LineDetailCollection: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailCollectionPtr shipmentTrackingLineDetails)
{
    os << shipmentTrackingLineDetails.get();
    return os;
}

//----------------------------------------------------------------------------------
// Handling Weak Pointer Collection
//----------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakCollection& shipmentTrackingLineDetails)
{
    os << "[";


    //int ii = 0;
    //for (libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakCollection::const_iterator it = shipmentTrackingLineDetails.begin();
    //    it != shipmentTrackingLineDetails.end();
    //    it++, ii++
    //    )
    //{
    //    if (ii > 0)
    //    {
    //        os << ", ";
    //    }

    //    os << *it; // weak pointer std::ostream& operator<< is used here
    //}
    os << "Weak cnt: " << shipmentTrackingLineDetails.size();
    os << "]";

    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakCollection* shipmentTrackingLineDetails)
{
    if (shipmentTrackingLineDetails != NULL)
    {
        os << *shipmentTrackingLineDetails;
    }
    else
    {
        os << "ST-LineDetailWeakCollection: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakCollectionPtr shipmentTrackingLineDetails)
{
    os << shipmentTrackingLineDetails.get();
    return os;
}

//----------------------------------------------------------------------------------
// Handling Weak Pointer Collection Map
//----------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakStrToClollectionMap& shipmentTrackingLineDetails)
{
    os << "{{"; // satrt of the map and of its first element -> a key + value pair


    int ii = 0;
    for (libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakStrToClollectionMap::const_iterator it = shipmentTrackingLineDetails.begin();
        it != shipmentTrackingLineDetails.end();
        it++, ii++
        )
    {
        if (ii > 0)
        {
            os << "}, {"; // separation of one map element, where a key points to a Collection: ShipmentTrackingLineDetailWeakCollectionPtr
        }

        os << it->first; 
        os << " --> "; // separator of the map  key and the map value: ShipmentTrackingLineDetailWeakCollectionPtr
        os << it->second; // the std::ostream& operator<< of the ShipmentTrackingLineDetailWeakCollectionPtr is used here
    }
    os << "}}";

    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakStrToClollectionMap* shipmentTrackingLineDetails)
{
    if (shipmentTrackingLineDetails != NULL)
    {
        os << *shipmentTrackingLineDetails;
    }
    else
    {
        os << "ST-LineDetailWeakStrToClollectionMap: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakStrToClollectionMapPtr shipmentTrackingLineDetails)
{
    os << shipmentTrackingLineDetails.get();
    return os;
}
