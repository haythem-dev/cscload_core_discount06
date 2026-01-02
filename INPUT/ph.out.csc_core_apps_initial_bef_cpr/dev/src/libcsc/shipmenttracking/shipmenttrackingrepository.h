#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORY_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORY_H

#include "shipmenttrackingdatafilter.h"
#include "shipmenttrackingrepositoryptr.h"
#include "tourinformation/shipmenttrackingtourinformationptr.h"
#include <persistence/iaccessorptr.h>
#include <persistence/iaccessorfactoryptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <parameter/ibranchparametergetterptr.h>
#include <list>


/////////////////////////////////////////////////////////////////////////////////////
// forward declarations
/////////////////////////////////////////////////////////////////////////////////////
namespace basar {
    namespace db {
        namespace sql {
            class ResultsetRef;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// class declaration
/////////////////////////////////////////////////////////////////////////////////////

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingRepository
{
public:
    ShipmentTrackingRepository();
    virtual ~ShipmentTrackingRepository();

    void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
    void injectAccessorFactory(persistence::IAccessorFactoryPtr accessorFactory);
    void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

    ShipmentTrackingTourInformationCollectionPtr findShipmentTracking(
        const basar::Int16& branchNo,
        const basar::Int32& customerNo,
        ShipmentTrackingDataFilter& filter
        );

    std::vector<std::string> findTourIDs(
        const basar::Int16& branchNo,
        const basar::Int32& date,
        ShipmentTrackingDataFilter& filter
    );

    std::map<std::string, std::vector<int> > findIDFsforTourIDs(
        const basar::Int16& branchNo,
        const basar::Int32& date,
        ShipmentTrackingDataFilter& filter,
        const std::vector<std::string>& tourIDList
    );

private:

    // General Factories:
    persistence::ITransactionFactoryPtr     m_TransactionFactory;
    persistence::IAccessorFactoryPtr        m_AccessorFactory;
    parameter::IBranchParameterGetterPtr    m_BranchParameterGetter;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_REPOSITORY_H
