#ifndef GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_H
#define GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <datatypes/boolean.h>

namespace libcsc {
namespace msv3 {

class TransmissionResponse
{
	// because of OR mapping
	friend class TransmissionResponseMapperBase;

public:
	TransmissionResponse();
	virtual ~TransmissionResponse();

	virtual const libcsc::Int32&		getId() const;
	virtual const libcsc::Int16&		getBranchNo() const;
	virtual const libcsc::Int32&		getCustomerNo() const;
	virtual const libcsc::VarString&	getTransmissionGuid() const;
	virtual const libcsc::Int32&		getTransmissionSupportId() const;
	virtual const libcsc::Bool&			getIsOffer() const;
	virtual const libcsc::VarString&	getResponseAsXml() const;
	virtual const libcsc::Int32&		getCreationDate() const;
	virtual const libcsc::Int32&		getCreationTime() const;
	virtual const libcsc::VarString&	getInternalHash() const;

	virtual void						setId(const libcsc::Int32& id);
	virtual void						setBranchNo(const libcsc::Int16& branchNo);
	virtual void						setCustomerNo(const libcsc::Int32& customerNo);
	virtual void						setTransmissionGuid(const libcsc::VarString& transmissionGuid);
	virtual void						setTransmissionSupportId(const libcsc::Int32& transmissionSupportId);
	virtual void						setIsOffer(const libcsc::Bool& isOffer);
	virtual void						setResponseAsXml(const libcsc::VarString& xmlResponse);
	virtual void						setCreationDate(const libcsc::Int32& creationDate);
	virtual void						setCreationTime(const libcsc::Int32& creationTime);
	virtual void						setInternalHash(const libcsc::VarString& internalHash);

	virtual bool						isClean();
	virtual bool						isDirty();

protected:

private:
	libcsc::Int32						m_Id;
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::VarString					m_TransmissionGuid;
	libcsc::Int32						m_TransmissionSupportId;
	libcsc::Bool						m_IsOffer;
	libcsc::VarString					m_ResponseAsXml;
	libcsc::Int32						m_CreationDate;
	libcsc::Int32						m_CreationTime;
	libcsc::VarString					m_InternalHash;
};

} // namespace msv3
} // namespace libcsc

#endif // GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_H
