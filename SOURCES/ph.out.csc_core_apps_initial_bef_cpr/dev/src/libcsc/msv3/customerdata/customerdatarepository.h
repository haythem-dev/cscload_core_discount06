#ifndef GUARD_LIBCSC_MSV3_CUSTOMERDATA_REPOSITORY_H
#define GUARD_LIBCSC_MSV3_CUSTOMERDATA_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasarcmnutil_bstring.h>
#include "customerdataptr.h"

namespace libcsc {
namespace msv3 {

class CustomerDataRepository
{
public:
    CustomerDataRepository();
    virtual ~CustomerDataRepository();
    
    virtual void injectFindAccessor(persistence::IAccessorPtr accessor);    

	virtual CustomerDataPtr findCustomerData(const basar::Int16& branchno, const basar::Int32& customerno) const;	

protected:

private:
    CustomerDataRepository& operator=(const CustomerDataRepository&);
	
    persistence::IAccessorPtr m_FindAccessor;    
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_CUSTOMERDATA_REPOSITORY_H
