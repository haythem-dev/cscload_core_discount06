#ifndef GUARD_LIBCSC_MSV3_ORDERRESPONSE_REPOSITORY_H
#define GUARD_LIBCSC_MSV3_ORDERRESPONSE_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <libbasarcmnutil_bstring.h>
#include "orderresponseptr.h"

namespace libcsc {
namespace msv3 {

class OrderResponseRepository
{
public:
    OrderResponseRepository();
    virtual ~OrderResponseRepository();

    virtual void injectFindAccessor(persistence::IAccessorPtr accessor);
    virtual void injectInsertAccessor(persistence::IAccessorPtr accessor);
    virtual void injectUpdateAccessor(persistence::IAccessorPtr accessor);

	virtual OrderResponsePtr createEmptyOrderResponse() const;
	virtual OrderResponsePtr findOrderResponse(const basar::VarString& orderUuid) const;
	virtual void saveOrderResponse(OrderResponsePtr orderResponse) const;

protected:

private:
    OrderResponseRepository& operator=(const OrderResponseRepository&);

    persistence::IAccessorPtr m_FindAccessor;
    persistence::IAccessorPtr m_InsertAccessor;
    persistence::IAccessorPtr m_UpdateAccessor;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_ORDERRESPONSE_REPOSITORY_H
