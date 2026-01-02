//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Bjoern Bischof
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_CICSPHARMOSTRANSACTIONDMPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_CICSPHARMOSTRANSACTIONDMPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
    namespace pharmosTransaction
    {
        namespace preparation
        {
	        class CICSPharmosTransactionDM;
            typedef boost::shared_ptr< CICSPharmosTransactionDM > CICSPharmosTransactionDMPtr;    

        }
    }
}

#endif

