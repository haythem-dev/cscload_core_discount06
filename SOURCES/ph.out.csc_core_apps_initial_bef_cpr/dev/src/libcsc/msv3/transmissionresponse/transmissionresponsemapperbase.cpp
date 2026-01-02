#include "transmissionresponsemapperbase.h"
#include "transmissionresponse.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace msv3 {

TransmissionResponseMapperBase::TransmissionResponseMapperBase(TransmissionResponsePtr transmissionResponse) :
	m_TransmissionResponse(transmissionResponse)
{
}

TransmissionResponseMapperBase::~TransmissionResponseMapperBase()
{
}

void TransmissionResponseMapperBase::map()
{
	doMap();
}

void TransmissionResponseMapperBase::mapSerial(const basar::Int32& id)
{
	doMapSerial(id);
}

void TransmissionResponseMapperBase::setTransmissionId(const basar::Int32& transmissionId)
{
	m_TransmissionResponse->m_Id = transmissionId;
	m_TransmissionResponse->m_Id.setClean();
}

void TransmissionResponseMapperBase::setBranchNo(const basar::Int16& branchNo)
{
    m_TransmissionResponse->m_BranchNo = branchNo;
    m_TransmissionResponse->m_BranchNo.setClean();
}

void TransmissionResponseMapperBase::setCustomerNo(const basar::Int32& customerNo)
{
    m_TransmissionResponse->m_CustomerNo = customerNo;
    m_TransmissionResponse->m_CustomerNo.setClean();
}

void TransmissionResponseMapperBase::setTransmissionGuid(const basar::VarString& transmissionGuid)
{
	m_TransmissionResponse->m_TransmissionGuid = transmissionGuid;
    m_TransmissionResponse->m_TransmissionGuid.setClean();
}

void TransmissionResponseMapperBase::setTransmissionSupportId(const basar::Int32& transmissionSupportId)
{
	m_TransmissionResponse->m_TransmissionSupportId = transmissionSupportId;
    m_TransmissionResponse->m_TransmissionSupportId.setClean();
}

void TransmissionResponseMapperBase::setIsOffer(const basar::Int16& isOffer)
{
	m_TransmissionResponse->m_IsOffer = libcsc::Bool(isOffer != 0);
    m_TransmissionResponse->m_IsOffer.setClean();
}

void TransmissionResponseMapperBase::setResponseAsXml(const basar::VarString& xmlResponse)
{
	m_TransmissionResponse->m_ResponseAsXml = xmlResponse;
    m_TransmissionResponse->m_ResponseAsXml.setClean();
}

void TransmissionResponseMapperBase::setCreationDate(const basar::Int32& creationDate)
{
	m_TransmissionResponse->m_CreationDate = creationDate;
	m_TransmissionResponse->m_CreationDate.setClean();
}

void TransmissionResponseMapperBase::setCreationTime(const basar::Int32& creationTime)
{
	m_TransmissionResponse->m_CreationTime = creationTime;
	m_TransmissionResponse->m_CreationTime.setClean();
}

void TransmissionResponseMapperBase::setInternalHash(const basar::VarString& internalHash)
{
	m_TransmissionResponse->m_InternalHash = internalHash;
	m_TransmissionResponse->m_InternalHash.setClean();
}


void TransmissionResponseMapperBase::setClean()
{
	m_TransmissionResponse->m_Id.setClean();
    m_TransmissionResponse->m_BranchNo.setClean();
    m_TransmissionResponse->m_CustomerNo.setClean();
    m_TransmissionResponse->m_TransmissionGuid.setClean();
    m_TransmissionResponse->m_TransmissionSupportId.setClean();
    m_TransmissionResponse->m_IsOffer.setClean();
    m_TransmissionResponse->m_ResponseAsXml.setClean();
    m_TransmissionResponse->m_CreationDate.setClean();
	m_TransmissionResponse->m_CreationTime.setClean();
	m_TransmissionResponse->m_InternalHash.setClean();
}


} // end namespace msv3
} // end namespace libcsc
