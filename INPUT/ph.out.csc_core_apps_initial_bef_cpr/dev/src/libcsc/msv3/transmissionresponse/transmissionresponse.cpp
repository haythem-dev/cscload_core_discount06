#include "transmissionresponse.h"

namespace libcsc {
namespace msv3 {

TransmissionResponse::TransmissionResponse()
{
}

TransmissionResponse::~TransmissionResponse()
{
}

const Int32& TransmissionResponse::getId() const
{
	return m_Id;
}

const Int16& TransmissionResponse::getBranchNo() const
{
	return m_BranchNo;
}

const Int32& TransmissionResponse::getCustomerNo() const
{
	return m_CustomerNo;
}

const VarString& TransmissionResponse::getTransmissionGuid() const
{
	return m_TransmissionGuid;
}

const Int32& TransmissionResponse::getTransmissionSupportId() const
{
	return m_TransmissionSupportId;
}

const Bool& TransmissionResponse::getIsOffer() const
{
	return m_IsOffer;
}

const VarString& TransmissionResponse::getResponseAsXml() const
{
	return m_ResponseAsXml;
}

const Int32& TransmissionResponse::getCreationDate() const
{
	return m_CreationDate;
}

const libcsc::Int32& TransmissionResponse::getCreationTime() const
{
	return m_CreationTime;
}

const libcsc::VarString& TransmissionResponse::getInternalHash() const
{
	return m_InternalHash;
}


void TransmissionResponse::setId(const Int32& id)
{
	m_Id = id;
}

void TransmissionResponse::setBranchNo(const Int16& branchNo)
{
	m_BranchNo = branchNo;
}

void TransmissionResponse::setCustomerNo(const Int32& customerNo)
{
	m_CustomerNo = customerNo;
}

void TransmissionResponse::setTransmissionGuid(const VarString& transmissionGuid)
{
	m_TransmissionGuid = transmissionGuid;
}

void TransmissionResponse::setTransmissionSupportId(const Int32& transmissionSupportId)
{
	m_TransmissionSupportId = transmissionSupportId;
}

void TransmissionResponse::setIsOffer(const Bool& isOffer)
{
	m_IsOffer = isOffer;
}

void TransmissionResponse::setResponseAsXml(const VarString& xmlResponse)
{
	m_ResponseAsXml = xmlResponse;
}

void TransmissionResponse::setCreationDate(const Int32& creationDate)
{
	m_CreationDate = creationDate;
}

void TransmissionResponse::setCreationTime(const libcsc::Int32& creationTime)
{
	m_CreationTime = creationTime;
}

void TransmissionResponse::setInternalHash(const libcsc::VarString& internalHash)
{
	m_InternalHash = internalHash;
}


bool TransmissionResponse::isClean()
{
	return m_Id.isClean() && m_TransmissionGuid.isClean();
}

bool TransmissionResponse::isDirty()
{
	return m_TransmissionGuid.isDirty();
}


} // namespace msv3
} // namespace libcsc
