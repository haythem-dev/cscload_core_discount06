
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDPROCESSHELPERPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDPROCESSHELPERPTR_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
    namespace pharmosTransaction
    {
		namespace processing
        {
            class RecordProcessHelper;
            typedef boost::shared_ptr< RecordProcessHelper > RecordProcessHelperPtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDPROCESSHELPERPTR_H

