#ifndef GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_REPOSITORY_H
#define GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <libbasarcmnutil_bstring.h>
#include "transmissionresponseptr.h"

namespace libcsc {
namespace msv3 {

class TransmissionResponseRepository
{
public:
    TransmissionResponseRepository();
    virtual ~TransmissionResponseRepository();

	virtual void injectFindAccessor(persistence::IAccessorPtr accessor);
	virtual void injectFindByInternalHashAccessor(persistence::IAccessorPtr accessor);
	virtual void injectInsertAccessor(persistence::IAccessorPtr accessor);
    virtual void injectUpdateAccessor(persistence::IAccessorPtr accessor);

	virtual TransmissionResponsePtr createEmptyTransmissionResponse() const;
	virtual TransmissionResponsePtr findTransmissionResponse(const basar::VarString& transmissionUuid) const;
	virtual TransmissionResponsePtr findByInternalHash(const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::VarString& internalHash, const basar::DateTime& checkFrom) const;
	virtual void saveTransmissionResponse(TransmissionResponsePtr transmissionResponse) const;

protected:

private:
    TransmissionResponseRepository& operator=(const TransmissionResponseRepository&);

	persistence::IAccessorPtr m_FindAccessor;
	persistence::IAccessorPtr m_FindByInternalHashAccessor;
	persistence::IAccessorPtr m_InsertAccessor;
    persistence::IAccessorPtr m_UpdateAccessor;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_TRANSMISSIONRESPONSE_REPOSITORY_H
