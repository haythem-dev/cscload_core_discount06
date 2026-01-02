#include "shipmenttrackinghandler.h"

#include <util/loggingutils.h>

#include <shipmenttracking/componentmanager/shipmenttrackingcomponentmanager.h>
#include <shipmenttracking/shipmenttrackingrepository.h>
#include <shipmenttracking/tourinformation/shipmenttrackingtourinformation.h>
#include <shipmenttracking/packageinformation/shipmenttrackingpackageinformation.h>
#include <shipmenttracking/packageinformation/shipmenttrackinglinedetail.h>

#include "cscservicehelper.h"

#include <types/messagecodeenum.inc>
#include <pxxmit.hpp>


namespace csc {
namespace service {

ShipmentTrackingHandler::ShipmentTrackingHandler()
{
    METHODNAME_DEF(ShipmentTrackingHandler, ShipmentTrackingHandler);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);
}


ShipmentTrackingHandler::~ShipmentTrackingHandler()
{
    METHODNAME_DEF(ShipmentTrackingHandler, ~ShipmentTrackingHandler);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);
}

/////////////////////////////////////////////////////////////////////////////////////
// PUBLIC Methods
/////////////////////////////////////////////////////////////////////////////////////

void ShipmentTrackingHandler::getShipmentTracking(
    warehouse::shipmenttracking::ShipmentTrackingResponse& _return,
    const warehouse::shipmenttracking::ShipmentTrackingRequest & request)
{
    METHODNAME_DEF(ShipmentTrackingHandler, getShipmentTracking);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    std::string exceptionMessage;
    try
    {
        // Check branch and customer:
        csc::base::ReturnStruct branchAndCustomerCheckResult = Helper::checkBranchAndCustomer(getSession(), request.BranchNo, request.CustomerNo);
        if (branchAndCustomerCheckResult.ErrorCode != nError().ErrorNumber())
        {
            _return.__set_RetValue(branchAndCustomerCheckResult);
            return;
        }

        // Prepare:
        if (request.__isset.DataFilter)
        {
            convertDataFilter(m_Filter, request.DataFilter);
        }

        // Do Process:
        // LibCSC query DB and fill the shipmentTrackingTourInformationCollection - The Busines Logic:
        libcsc::shipmenttracking::ShipmentTrackingTourInformationCollectionPtr shipmentTrackingTourInformationCollection =
            getSession()->getShipmentTrackingComponentManager()->getShipmentTrackingRepository()->findShipmentTracking(
                request.BranchNo,
                request.CustomerNo,
                m_Filter
            );

        // Map busines logic result to the Thrift _return object:
        // Create the result collection:
        warehouse::shipmenttracking::ShipmentTrackingTourInformationList shipmentTrackingTourInformationList;

        // Fill / map the result collection:
        if (shipmentTrackingTourInformationCollection.get() != NULL &&
            shipmentTrackingTourInformationCollection->size() > 0
            )
        {
            convertTourInformationCollection(shipmentTrackingTourInformationList, *shipmentTrackingTourInformationCollection);
        }

        // Return all:
        _return.__set_TourInformationList(shipmentTrackingTourInformationList);
        _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
    }
    catch (basar::Exception const& ex)
    {
        exceptionMessage = (ex.getStackTrace().size() > 0) ? ex.stackTrace() : ex.what();
    }
    catch (...)
    {
        exceptionMessage = "unknown exception.";
    }

    if (!exceptionMessage.empty())
    {
        std::stringstream ss;
        ss << "ShipmentTrackingHandler::getShipmentTracking(" << request.BranchNo << ", " << request.CustomerNo << ", " << m_Filter << "):" << std::endl << exceptionMessage;
        exceptionMessage = ss.str();

        BLOG_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), exceptionMessage);

        nError error;
        error.ExternalError(getSession()->CMsgStream(), CMSG_MISC_EXCEPTION, exceptionMessage.c_str());

        _return.__set_RetValue(Helper::getReturnStructFromError(error));
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// PRIVATE Methods
/////////////////////////////////////////////////////////////////////////////////////

void ShipmentTrackingHandler::convertDataFilter(
    libcsc::shipmenttracking::ShipmentTrackingDataFilter& libcscFilter,
    const warehouse::shipmenttracking::ShipmentTrackingDataFilter& thriftFilter
) const
{
    METHODNAME_DEF(ShipmentTrackingHandler, convertDataFilter);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    if (thriftFilter.__isset.ToteDeliveryDate)
    {
        libcscFilter.ToteDeliveryDate = Helper::getBasarDateFromCscDate(thriftFilter.ToteDeliveryDate);
    }
    else if (thriftFilter.__isset.PickingDate)
    {
        libcscFilter.PickingDate = Helper::getBasarDateFromCscDate(thriftFilter.PickingDate);
    }

    if (thriftFilter.__isset.DetailsDesired)
    {
        libcscFilter.DetailsDesired = thriftFilter.DetailsDesired;
    }

    if (thriftFilter.__isset.SpecificTourID)
    {
        libcscFilter.SpecificTourID = thriftFilter.SpecificTourID;

        // trim sapces on the beginning and on the end
        libcscFilter.SpecificTourID.trim(basar::VarString::FIRST_END);
    }

    if (thriftFilter.__isset.SendPharmosOrderNumbers)
    {
        libcscFilter.SendPharmosOrderNumbers = thriftFilter.SendPharmosOrderNumbers;
    }

    if (thriftFilter.__isset.SendPickingOrderNumbers)
    {
        libcscFilter.SendPickingOrderNumbers = thriftFilter.SendPickingOrderNumbers;
    }

    if (thriftFilter.__isset.SendPackagePosNos)
    {
        libcscFilter.SendPackagePosNos = thriftFilter.SendPackagePosNos;
    }
}

void ShipmentTrackingHandler::convertTourInformationCollection(
    warehouse::shipmenttracking::ShipmentTrackingTourInformationList& thriftList,
    const libcsc::shipmenttracking::ShipmentTrackingTourInformationCollection& libcscColl
)
{
    METHODNAME_DEF(ShipmentTrackingHandler, convertTourInformationCollection);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    int posNr = 1;
    for (libcsc::shipmenttracking::ShipmentTrackingTourInformationCollection::const_iterator libcscIter = libcscColl.begin();
        libcscIter != libcscColl.end();
        libcscIter++, posNr++
        )
    {
        libcsc::shipmenttracking::ShipmentTrackingTourInformationPtr libcscTourInformation = *libcscIter;

        warehouse::shipmenttracking::ShipmentTrackingTourInformation thriftTourInformation;
        
        // TourData:
        warehouse::shipmenttracking::ShipmentTrackingTourData thriftTourData;
        bool planedTimeIsValid = convertTourData(thriftTourData, libcscTourInformation->getTourData());
        thriftTourInformation.__set_TourData(thriftTourData);

        // EtaAndDeliveryData:
        warehouse::shipmenttracking::ShipmentTrackingEtaAndDeliveryData thriftEtaAndDeliveryData;
        convertEtaAndDeliveryData(planedTimeIsValid, thriftEtaAndDeliveryData, libcscTourInformation->getEtaAndDeliveryData());
        thriftTourInformation.__set_EtaAndDeliveryData(thriftEtaAndDeliveryData);

        // PackageInformationCollection:
        if (libcscTourInformation->getPackageInformationCollection().get() != NULL &&
            libcscTourInformation->getPackageInformationCollection()->size() > 0
            )
        {
            warehouse::shipmenttracking::ShipmentTrackingPackageInformationList thriftPackageInfoList;

            convertTourPackageInformationCollection(thriftPackageInfoList, *libcscTourInformation->getPackageInformationCollection(), posNr);

            thriftTourInformation.__set_PackageInformationList(thriftPackageInfoList);
        }

        // Store whole collected TourInformation:
        thriftList.push_back(thriftTourInformation);
    }
}

bool ShipmentTrackingHandler::convertTourData(
    warehouse::shipmenttracking::ShipmentTrackingTourData& thriftTourData,
    const libcsc::shipmenttracking::ShipmentTrackingTourDataPtr libcscTourData
)
{
    METHODNAME_DEF(ShipmentTrackingHandler, convertTourData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    thriftTourData.__set_TourId(libcscTourData->getTourId());

    bool planedTimeIsValid = libcscTourData->getPlannedTimeOfArrival().isValid();
    if (planedTimeIsValid)
    {
        thriftTourData.__set_PlannedTimeOfArrival(
            Helper::getCscDateTimeFromCscDateTime(libcscTourData->getPlannedTimeOfArrival())
        );
    }

    return planedTimeIsValid;
}

void ShipmentTrackingHandler::convertEtaAndDeliveryData(
    bool planedTimeIsValid,
    warehouse::shipmenttracking::ShipmentTrackingEtaAndDeliveryData& thriftEtaAndDeliveryData,
    const libcsc::shipmenttracking::ShipmentTrackingEtaAndDeliveryDataPtr libcscEtaAndDeliveryData
)
{
    METHODNAME_DEF(ShipmentTrackingHandler, convertEtaAndDeliveryData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    bool deliveredAtIsValid = libcscEtaAndDeliveryData->getDeliveredAt().isValid();
    if (deliveredAtIsValid)
    {
        thriftEtaAndDeliveryData.__set_DeliveredAt(
            Helper::getCscDateTimeFromCscDateTime(libcscEtaAndDeliveryData->getDeliveredAt())
        );
    }

    bool etaIsValid = libcscEtaAndDeliveryData->getEstimatedTimeOfArrival().isValid();
    if (etaIsValid)
    {
        thriftEtaAndDeliveryData.__set_EstimatedTimeOfArrival(
            Helper::getCscDateTimeFromCscDateTime(libcscEtaAndDeliveryData->getEstimatedTimeOfArrival())
        );
        thriftEtaAndDeliveryData.__set_EstimatedTimeOfArrivalMin(
            Helper::getCscDateTimeFromCscDateTime(libcscEtaAndDeliveryData->getEstimatedTimeOfArrivalMin())
        );
        thriftEtaAndDeliveryData.__set_EstimatedTimeOfArrivalMax(
            Helper::getCscDateTimeFromCscDateTime(libcscEtaAndDeliveryData->getEstimatedTimeOfArrivalMax())
        );
    }

    if (planedTimeIsValid &&
        (deliveredAtIsValid || etaIsValid)
        )
    {
        thriftEtaAndDeliveryData.__set_DelayInMinutes(libcscEtaAndDeliveryData->getDelayInMinutes());
    }

    if (!libcscEtaAndDeliveryData->getDelayInfo().empty() &&
        // Efficient way to check if std::string has only spaces:
        // https://stackoverflow.com/questions/6444842/efficient-way-to-check-if-stdstring-has-only-spaces/36535031
        libcscEtaAndDeliveryData->getDelayInfo().find_first_not_of(' ') != std::string::npos
        )
    {
        thriftEtaAndDeliveryData.__set_DelayInfo(libcscEtaAndDeliveryData->getDelayInfo());
    }
}

void ShipmentTrackingHandler::convertTourPackageInformationCollection(
    warehouse::shipmenttracking::ShipmentTrackingPackageInformationList& thriftList,
    const libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollection& libcscColl,
    int packageInformationPositionNumber
)
{
    METHODNAME_DEF(ShipmentTrackingHandler, convertTourPackageInformationCollection);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << packageInformationPositionNumber);

    int posNr = 1;
    for (libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollection::const_iterator libcscIter = libcscColl.begin();
        libcscIter != libcscColl.end();
        libcscIter++, posNr++
        )
    {
        libcsc::shipmenttracking::ShipmentTrackingPackageInformationPtr libcscPackageInformation = *libcscIter;

        warehouse::shipmenttracking::ShipmentTrackingPackageInformation thriftPackageInformation;

        // PackageProperties:
        warehouse::shipmenttracking::ShipmentTrackingPackageProperties thriftPackageProperties;
        convertPackageProperties(
            thriftPackageProperties, 
            libcscPackageInformation->getPackageProperties(),
            libcscPackageInformation->getRedirectedFromTourData().get() != NULL ? libcscPackageInformation->getRedirectedFromTourData()->getTourId() : "",
            libcscPackageInformation->getRedirectedToTourData().get() != NULL ? libcscPackageInformation->getRedirectedToTourData()->getTourId() : ""
        );
        thriftPackageInformation.__set_PackageProperties(thriftPackageProperties);

        // IbtInformation:
        warehouse::shipmenttracking::ShipmentTrackingIbtInformationList thriftIbtInformationList;
        convertIbtInformation(thriftIbtInformationList, libcscPackageInformation->getIbtInformation());
        if (thriftIbtInformationList.size() > 0)
        {
            thriftPackageInformation.__set_IbtInformationList(thriftIbtInformationList);
        }

        // LineDetails List:
        if (m_Filter.DetailsDesired &&
            libcscPackageInformation->getLineDetailCollection().get() != NULL &&
            libcscPackageInformation->getLineDetailCollection()->size() > 0
            )
        {
            warehouse::shipmenttracking::ShipmentTrackingLineDetailList thriftLineDetailList;

            convertTourLineDetailCollection(thriftLineDetailList, *libcscPackageInformation->getLineDetailCollection(), posNr);

            thriftPackageInformation.__set_LineDetails(thriftLineDetailList);
        }

        thriftList.push_back(thriftPackageInformation);
    }
}

void ShipmentTrackingHandler::convertPackageProperties(
    warehouse::shipmenttracking::ShipmentTrackingPackageProperties& thriftPackageProperties,
    const libcsc::shipmenttracking::ShipmentTrackingPackagePropertiesPtr libcscPackageProperties,
    const basar::VarString& redirectedFromTourId,
    const basar::VarString& redirectedToTourId
)
{
    METHODNAME_DEF(ShipmentTrackingHandler, convertPackageProperties);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    thriftPackageProperties.__set_PackageId(libcscPackageProperties->getPackageId());
    thriftPackageProperties.__set_CscOrderNo(libcscPackageProperties->getCscOrderNo());

    if (libcscPackageProperties->getPharmosOrderNo() > 0)
    {
        thriftPackageProperties.__set_PharmosOrderNo(libcscPackageProperties->getPharmosOrderNo());
    }

    if (libcscPackageProperties->getDeliveryAdviceNo() > 0)
    {
        thriftPackageProperties.__set_DeliveryAdviceNo(libcscPackageProperties->getDeliveryAdviceNo());
    }

    if (libcscPackageProperties->getPickingOrderNo() > 0)
    {
        thriftPackageProperties.__set_PickingOrderNo(libcscPackageProperties->getPickingOrderNo());
    }

    if (libcscPackageProperties->getPickingOrderPageNo() > 0)
    {
        thriftPackageProperties.__set_PickingOrderPageNo(libcscPackageProperties->getPickingOrderPageNo());
    }

    if (libcscPackageProperties->getOrderClosedAt().isValid() && libcscPackageProperties->getOrderClosedAt().getYear() > 2010 && libcscPackageProperties->getOrderClosedAt().getYear() < 2090)
    {
        thriftPackageProperties.__set_OrderClosedOn(
            Helper::getCscDateFromIntDate(libcscPackageProperties->getOrderClosedAt().getDate())
        );
        thriftPackageProperties.__set_OrderClosedAt(
            Helper::getCscDateTimeFromCscDateTime(libcscPackageProperties->getOrderClosedAt())
        );
    }

    if (libcscPackageProperties->getPickingDoneAt().isValid() && libcscPackageProperties->getPickingDoneAt().getYear() > 2010 && libcscPackageProperties->getPickingDoneAt().getYear() < 2090)
    {
        thriftPackageProperties.__set_PickingDoneAt(
            Helper::getCscDateTimeFromCscDateTime(libcscPackageProperties->getPickingDoneAt())
        );
    }

    if (!libcscPackageProperties->getTrackingBarcode().empty() &&
        // Efficient way to check if std::string has only spaces:
        // https://stackoverflow.com/questions/6444842/efficient-way-to-check-if-stdstring-has-only-spaces/36535031
        libcscPackageProperties->getTrackingBarcode().find_first_not_of(' ') != std::string::npos
        )
    {
        thriftPackageProperties.__set_TrackingBarcode(libcscPackageProperties->getTrackingBarcode());
    }

    if (libcscPackageProperties->isToteContentChanged())
    {
        thriftPackageProperties.__set_ToteContentChanged(libcscPackageProperties->isToteContentChanged());
    }

    if (redirectedFromTourId.find_first_not_of(' ') != std::string::npos)
    {
        thriftPackageProperties.__set_RedirectedFromTourId(redirectedFromTourId);
    }

    if (redirectedToTourId.find_first_not_of(' ') != std::string::npos)
    {
        thriftPackageProperties.__set_RedirectedToTourId(redirectedToTourId);
    }

    if (libcscPackageProperties->getToteDeletedAt().isValid() && libcscPackageProperties->getToteDeletedAt().getYear() > 2010 && libcscPackageProperties->getToteDeletedAt().getYear() < 2090)
    {
        thriftPackageProperties.__set_ToteDeletedAt(
            Helper::getCscDateTimeFromCscDateTime(libcscPackageProperties->getToteDeletedAt())
        );
    }

    if (libcscPackageProperties->getPackageType().find_first_not_of(' ') != std::string::npos)
    {
        thriftPackageProperties.__set_PackageType(libcscPackageProperties->getPackageType());
    }
}

void ShipmentTrackingHandler::convertIbtInformation(
    warehouse::shipmenttracking::ShipmentTrackingIbtInformationList& thriftIbtInformationList,
    const libcsc::shipmenttracking::ShipmentTrackingIbtInformationPtr libcscIbtInformation
)
{
    METHODNAME_DEF(ShipmentTrackingHandler, convertIbtInformation);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    if (libcscIbtInformation.get() == NULL)
    {
        return; // stop the recursion and ----> quit!
    }

    warehouse::shipmenttracking::ShipmentTrackingIbtInformation thriftIbtInformation;

    thriftIbtInformation.__set_BranchNo(libcscIbtInformation->getBranchNo());
    thriftIbtInformation.__set_CustomerNo(libcscIbtInformation->getCustomerNo());

    // PackageProperties:
    warehouse::shipmenttracking::ShipmentTrackingPackageProperties thriftPackageProperties;
    convertPackageProperties(
        thriftPackageProperties, 
        libcscIbtInformation->getPackageProperties(),
        "", //NOTE: there is no FromTourData yet. If then just the ToTourData
        libcscIbtInformation->getRedirectedToTourData().get() != NULL ? libcscIbtInformation->getRedirectedToTourData()->getTourId() : ""
        );
    thriftIbtInformation.__set_PackageProperties(thriftPackageProperties);

    // TourData:
    warehouse::shipmenttracking::ShipmentTrackingTourData thriftTourData;
    convertTourData(thriftTourData, libcscIbtInformation->getTourData());
    thriftIbtInformation.__set_TourData(thriftTourData);

    //NOTE: #1: IBT EtaAndDeliveryData is neither needed, nor provided yet by any system, but possible in future.
    
    //NOTE: #2: If there was an IBT chaining, this is the place, where you have to recurse the IBT chain and linearise it into the: thriftIbtInformationList like this:
    //convertIbtInformation(thriftIbtInformationList, libcscIbtInformation->getIbtInformation());

    // store the data 1st after filling it!
    thriftIbtInformationList.push_back(thriftIbtInformation);
}

void ShipmentTrackingHandler::convertTourLineDetailCollection(
    warehouse::shipmenttracking::ShipmentTrackingLineDetailList& thriftList,
    const libcsc::shipmenttracking::ShipmentTrackingLineDetailCollection& libcscColl,
    int lineDetailPositionNumber
)
{
    METHODNAME_DEF(ShipmentTrackingHandler, convertTourLineDetailCollection);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << lineDetailPositionNumber);

    int posNr = 1;
    for (libcsc::shipmenttracking::ShipmentTrackingLineDetailCollection::const_iterator libcscIter = libcscColl.begin();
        libcscIter != libcscColl.end();
        libcscIter++, posNr++
        )
    {
        libcsc::shipmenttracking::ShipmentTrackingLineDetailPtr libcscLineDetail = *libcscIter;

        warehouse::shipmenttracking::ShipmentTrackingLineDetail thriftLineDetail;

        thriftLineDetail.__set_OrderPosNo(libcscLineDetail->getOrderPosNo());
        thriftLineDetail.__set_ExpectedDeliveryQuantity(libcscLineDetail->getExpectedDeliveryQuantity());

        // only deliver the Quantity After Picking, if different to ordered and confirmed ExpectedDeliveryQuantity:
        if (libcscLineDetail->hasWarehouseData() &&
            libcscLineDetail->getExpectedDeliveryQuantity() != libcscLineDetail->getConfirmedDeliveryQuantity()
            )
        {
            thriftLineDetail.__set_ConfirmedDeliveryQuantity(libcscLineDetail->getConfirmedDeliveryQuantity());
        }

        thriftLineDetail.__set_ArticleCode(libcscLineDetail->getArticleCode());
        thriftLineDetail.__set_ArticleName(libcscLineDetail->getArticleName());
        thriftLineDetail.__set_IsNarcotic(libcscLineDetail->getIsNarcotic());

        // check if Batch is set and if it is not only a dummy batch '.' sign:
        basar::VarString tmpBatch = libcscLineDetail->getBatch();
        tmpBatch.trim(basar::cmnutil::BString::FIRST_END);

        if (!tmpBatch.empty() &&
            tmpBatch.find_first_not_of('.') != std::string::npos
            )
        {
            thriftLineDetail.__set_Batch(tmpBatch);
        }

        if (m_Filter.SendPackagePosNos)
        {
            thriftLineDetail.__set_PackagePosNo(libcscLineDetail->getTotePosNo());
        }

        if (libcscLineDetail->getWhsSiblingToteCount() > 1)
        {
            std::string ownersWhsMapKey = libcscLineDetail->getWarehouseToteMapKey();
            libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakStrToClollectionMapPtr whsToteMapKeyToOrderPositionSplitSiblingLines = libcscLineDetail->getWhsToteMapKeyToOrderPositionSplitSiblingLines();

            std::vector<std::string> otherTotesMapKeys;

            for (libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakStrToClollectionMap::iterator it1 = whsToteMapKeyToOrderPositionSplitSiblingLines->begin();
                it1 != whsToteMapKeyToOrderPositionSplitSiblingLines->end();
                it1++
                )
            {
                if (it1->first == ownersWhsMapKey)
                {
                    continue; // --> skip own Tote!
                }

                otherTotesMapKeys.push_back(it1->first);
            }

            thriftLineDetail.__set_SiblingsSplitInTotes(otherTotesMapKeys);
        }

        thriftList.push_back(thriftLineDetail);
    }
}


} // namespace service
} // namespace csc
