#include "shipmenttrackingtourinformation.h"
#include <boost/make_shared.hpp>
#include <util/loggingutils.h>
#include <exceptions/exceptionhelper.h>
#include <string>       // std::string


namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingTourInformation::ShipmentTrackingTourInformation() :
    m_TourData(boost::make_shared<ShipmentTrackingTourData>()),
    m_EtaAndDeliveryData(boost::make_shared<ShipmentTrackingEtaAndDeliveryData>()),
    m_PackageInformations(boost::make_shared<ShipmentTrackingPackageInformationCollection>())
{
}


ShipmentTrackingTourInformation::~ShipmentTrackingTourInformation()
{
}

void ShipmentTrackingTourInformation::getValidPickingDateAndBarcodeList(std::list<basar::Int32>& pickingDateList, std::list<basar::VarString>& trackingBarcodeList)
{
    // - is Tote not deleted?         --> if delted == (dktsv.tsv_status == 9) == (ToteDeletedAt is a valid DateTime) --> omit!
    // - is Tote not redirected "TO"? --> if redirected "TO" == (ToteRedirectedTour != '') == (dktsv.tsv_status == 8) --> its Barcode is not usable for tracking with this Tour, i.e. the tote's tour != (*iter).get() !!
    // - is OrderClosedAt valid? (e11date is enough)
    // - do we have Barcode?          --> == is PickingDoneAt valid?, so we can lookup in ETA and TransmedToteStatus
    // ...
    // else => no ETA and DeliveredAt querying and computing! 
    // NOTE: only if there is NO Barcode for this Tour == (*iter).get() ==> Leave the falback fill the values!

    // If the Barcode is valid, take it with PickingDate in a hash (with no doubletts!)

    for (ShipmentTrackingPackageInformationCollection::const_iterator packageIter = m_PackageInformations->begin();
        packageIter != m_PackageInformations->end();
        packageIter++
        )
    {
        ShipmentTrackingPackageInformationPtr packageInfo = *packageIter;

        if (//packageInfo->getPackageProperties()->getToteDeletedAt().isValid() ||   <--> NOTE: taking deleted too, as we have seen a case with Mihai, where the only package was deleted, but then Deliverd according to ST-CSV StateId 45!
            packageInfo->getRedirectedToTourData().get() != NULL
            )
        {
            continue;   // skip this tote, because it does not contribute to this Tour information's delivery tracking!
        }

        if (packageInfo->getPackageProperties()->getOrderClosedAt().isValid())
        {
            pickingDateList.push_back(packageInfo->getPackageProperties()->getOrderClosedAt().getDate());
        }

        // add also the IBT picking date == OrderClosedDate, because I am not sure, what PINT and Transmed finally stores in their PickingDate columns...
        // ... also, if the IBT Local (KZLK=V) DKTSV record is missing, then we have just the Picking Date of the IBT picking, which can be an another day!
        if (packageInfo->getIbtInformation().get() != NULL &&
            packageInfo->getIbtInformation()->getPackageProperties()->getOrderClosedAt().isValid()
            )
        {
            pickingDateList.push_back(packageInfo->getIbtInformation()->getPackageProperties()->getOrderClosedAt().getDate());
        }

        if (!packageInfo->getPackageProperties()->getTrackingBarcode().empty())
        {
            trackingBarcodeList.push_back(packageInfo->getPackageProperties()->getTrackingBarcode());
        }
    }

    // remove duplicates:
    pickingDateList.unique();
    trackingBarcodeList.unique();
}

} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourInformation& shipmentTrackingTourInformation)
{
    METHODNAME_DEF(ShipmentTrackingTourInformation, operator<<);
    try
    {
        os << "ST-TourInformation: {"
            << "TourData: " << shipmentTrackingTourInformation.getTourData()
            << ", EtaAndDeliveryData: " << shipmentTrackingTourInformation.getEtaAndDeliveryData()
            << ", ShipmentTrackingPackageInformations: " << shipmentTrackingTourInformation.getPackageInformationCollection()
            << "}";
        return os;
    }
    catch (basar::Exception & ex)
    {
        libcsc::exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourInformation* shipmentTrackingTourInformation)
{
    if (shipmentTrackingTourInformation != NULL)
    {
        os << *shipmentTrackingTourInformation;
    }
    else
    {
        os << "ST-TourInformation: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourInformationPtr shipmentTrackingTourInformation)
{
    os << shipmentTrackingTourInformation.get();
    return os;
}
