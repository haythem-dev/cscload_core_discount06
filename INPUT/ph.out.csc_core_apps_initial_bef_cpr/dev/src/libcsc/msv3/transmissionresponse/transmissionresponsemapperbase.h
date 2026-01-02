#ifndef GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSEMAPPER_BASE_H
#define GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSEMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "transmissionresponseptr.h"

namespace libcsc {
namespace msv3 {

class TransmissionResponseMapperBase
{
public:
	TransmissionResponseMapperBase(TransmissionResponsePtr transmissionResponse);

	void			map();
	void			mapSerial(const basar::Int32& id);

protected:
	virtual ~TransmissionResponseMapperBase();

	virtual void	doMap() = 0;
	virtual void	doMapSerial(const basar::Int32& id) = 0;

	void			setTransmissionId(const basar::Int32& transmissionId);
	void			setBranchNo(const basar::Int16& branchNo);
	void			setCustomerNo(const basar::Int32& customerNo);
	void			setTransmissionGuid(const basar::VarString& transmissionGuid);
	void			setTransmissionSupportId(const basar::Int32& transmissionSupportId);
	void			setIsOffer(const basar::Int16& isOffer);
	void			setResponseAsXml(const basar::VarString& xmlResponse);
	void			setCreationDate(const basar::Int32& creationDate);
	void			setCreationTime(const basar::Int32& creationTime);
	void			setInternalHash(const basar::VarString& internalHash);

	virtual void	setClean();


private:
	TransmissionResponsePtr m_TransmissionResponse;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSEMAPPER_BASE_H
