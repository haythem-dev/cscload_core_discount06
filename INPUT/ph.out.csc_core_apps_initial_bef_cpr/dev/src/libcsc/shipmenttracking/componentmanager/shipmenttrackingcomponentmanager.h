#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/itransactionfactory.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/accessorfactory.h>
#include <parameter/ibranchparametergetterptr.h>

#include <shipmenttracking/shipmenttrackingrepositoryptr.h>

class pxSession;

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingComponentManager : public persistence::ITransactionFactory,
                                         public persistence::AccessorFactory,
                                         public boost::enable_shared_from_this<ShipmentTrackingComponentManager>
{
public:
    ShipmentTrackingComponentManager();
    virtual ~ShipmentTrackingComponentManager();

    void injectTransactionHandler (nDataBase * transHandler);
    void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

    virtual libcsc::persistence::TransactionGuard   createTransaction() const;

    ShipmentTrackingRepositoryPtr                   getShipmentTrackingRepository();

private:
    // prohibit copy constructor and assignment operator:
    ShipmentTrackingComponentManager( const ShipmentTrackingComponentManager & );
    ShipmentTrackingComponentManager& operator=( const ShipmentTrackingComponentManager & );

    nDataBase *                                 m_TransactionHandler;
    parameter::IBranchParameterGetterPtr		m_BranchParameterGetter;

    mutable ShipmentTrackingRepositoryPtr       m_ShipmentTrackingRepository;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif //end GUARD_LIBCSC_SHIPMENTTRACKING_COMPONENT_MANAGER_H
