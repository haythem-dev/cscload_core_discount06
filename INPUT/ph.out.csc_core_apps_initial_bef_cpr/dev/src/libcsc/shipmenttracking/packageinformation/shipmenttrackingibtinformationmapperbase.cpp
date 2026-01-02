#include "shipmenttrackingibtinformationmapperbase.h"
#include "shipmenttrackingibtinformation.h"


namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingIbtInformationMapperBase::ShipmentTrackingIbtInformationMapperBase(ShipmentTrackingIbtInformationPtr shipmentTrackingIbtInformation)
    : m_IbtInformation(shipmentTrackingIbtInformation)
{
}


ShipmentTrackingIbtInformationMapperBase::~ShipmentTrackingIbtInformationMapperBase()
{
}

void ShipmentTrackingIbtInformationMapperBase::setBranchNo(const basar::Int16 branchNo)
{
    m_IbtInformation->m_BranchNo = branchNo;
    m_IbtInformation->m_BranchNo.setClean();
}

void ShipmentTrackingIbtInformationMapperBase::setCustomerNo(const basar::Int32 customerNo)
{
    m_IbtInformation->m_CustomerNo = customerNo;
    m_IbtInformation->m_CustomerNo.setClean();
}

ShipmentTrackingTourDataPtr ShipmentTrackingIbtInformationMapperBase::getIbtInfoTourDataForWrite() const
{
    return m_IbtInformation->m_TourData;
}

void ShipmentTrackingIbtInformationMapperBase::setTourData(ShipmentTrackingTourDataPtr tourData)
{
    m_IbtInformation->m_TourData = tourData;
}

void ShipmentTrackingIbtInformationMapperBase::setRedirectedToTourData(const ShipmentTrackingTourDataPtr redirectedToTourData)
{
    m_IbtInformation->m_RedirectedToTourData = redirectedToTourData;
}


} // end namespace shipmenttracking
} // end namespace libcsc

