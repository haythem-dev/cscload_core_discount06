#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_REQUESTPROCESSINGCONTEXT_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_REQUESTPROCESSINGCONTEXT_H

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasar_definitions.h>

#include "shipmenttrackingdatafilter.h"
#include "shipmenttrackingrequestprocessingcontextptr.h"
#include "shipmenttracking/packageinformation/shipmenttrackingtotepositiontolinebuildermapperptr.h"
#include <boost/shared_ptr.hpp>
#include <list>


namespace libcsc {
namespace shipmenttracking {

//! \brief Request Processing Context info, like User's choice, server file config data, etc.
class ShipmentTrackingRequestProcessingContext
{
private:
    // prohibit user default constructor:
    ShipmentTrackingDataFilter m_DummyFilter;
    std::vector<std::string> m_DefaultTourList;

public:

    ShipmentTrackingRequestProcessingContext(
        const basar::Int16& branchNo,
        const basar::Int32& customerNo,
        ShipmentTrackingDataFilter& filter,
        const basar::VarString& dbNameOutbound,
        const basar::VarString& dbNameWarehouse
    ) :
        m_DummyFilter(),
        BranchNo(branchNo),
        CustomerNo(customerNo),
        Filter(filter),
        DbNameOutbound(dbNameOutbound),
        DbNameWarehouse(dbNameWarehouse),
        VerboseTracing(false),
        m_TransmedStatusDeliveredToCustomerIdsCache("")
    {}


    const basar::Int16                 BranchNo;
    const basar::Int32                 CustomerNo;
    const ShipmentTrackingDataFilter&   Filter;

    const basar::VarString DbNameOutbound;
    const basar::VarString DbNameWarehouse;

    // DB Config helper:
    bool                                    VerboseTracing;


    void setTransmedStatusDeliveredToCustomerIdsCache(const basar::VarString& transmedStatusDeliveredToCustomerIdsCache) { m_TransmedStatusDeliveredToCustomerIdsCache = transmedStatusDeliveredToCustomerIdsCache; }
    const basar::VarString& getTransmedStatusDeliveredToCustomerIdsCache() { return m_TransmedStatusDeliveredToCustomerIdsCache; }

    ShipmentTrackingTotePositionToLineBuilderMapperPtr getOrCreateTotePositionToLineBuilderMapperForCscOrderNo(basar::Int32 cscOrderNo);
    ShipmentTrackingTotePositionToLineBuilderMapperPtr getTotePositionToLineBuilderMapperForCscOrderNo(basar::Int32 cscOrderNo);

private:
    // prohibit user default constructor:
    ShipmentTrackingRequestProcessingContext() :
        m_DummyFilter(),
        BranchNo(-1),
        CustomerNo(-1),
        Filter(m_DummyFilter),
        DbNameOutbound("noDB"),
        DbNameWarehouse("noDB"),
        VerboseTracing(false),
        m_TransmedStatusDeliveredToCustomerIdsCache("")
    {
    
    }

    // prohibit copy constructor and assignment operator:
    ShipmentTrackingRequestProcessingContext(const ShipmentTrackingRequestProcessingContext&);
    ShipmentTrackingRequestProcessingContext& operator=(const ShipmentTrackingRequestProcessingContext&);

    basar::VarString                        m_TransmedStatusDeliveredToCustomerIdsCache;

    //! \brief CscOrderNo --> TotePositionToLineBuilderMapper map
    ShipmentTrackingTotePositionToLineBuilderMapperInt32Map m_CscOrderNoToTotePosToLineBuilderMap;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_REQUESTPROCESSINGCONTEXT_H
