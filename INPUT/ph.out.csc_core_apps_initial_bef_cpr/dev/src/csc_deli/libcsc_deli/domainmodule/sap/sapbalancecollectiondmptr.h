#ifndef GUARD_LIBCSC_DELI_DOMMOD_SAP_SAPBALANCECOLLECTIONDMPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_SAP_SAPBALANCECOLLECTIONDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace sap
        {
            class SAPBalanceCollectionDM;
            typedef boost::shared_ptr< SAPBalanceCollectionDM > SAPBalanceCollectionDMPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_SAP_SAPBALANCECOLLECTIONDMPTR_H
