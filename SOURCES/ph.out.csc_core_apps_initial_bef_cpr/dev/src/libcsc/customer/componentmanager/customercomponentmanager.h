#ifndef GUARD_LIBCSC_CUSTOMER_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_CUSTOMER_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <parameter/ibranchparametergetterptr.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <customer/icustomerrepositoryptr.h>

namespace libcsc {
namespace customer {

class CustomerComponentManager : public boost::enable_shared_from_this<CustomerComponentManager>
{
public:
    CustomerComponentManager();
    virtual ~CustomerComponentManager();

    void injectConnection( persistence::ConnectionPtr connection );
    void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

    ICustomerRepositoryPtr getCustomerRepository();

private:
    CustomerComponentManager( const CustomerComponentManager & );
    CustomerComponentManager & operator=( const CustomerComponentManager & );

    ICustomerRepositoryPtr createCustomerRepository();

    persistence::IAccessorPtr createAccessor();

    persistence::ConnectionPtr m_Connection;
    parameter::IBranchParameterGetterPtr m_BranchParameterGetter;
};

} // end namespace customer
} // end namespace libcsc

#endif //end GUARD_LIBCSC_CUSTOMER_COMPONENT_MANAGER_H
