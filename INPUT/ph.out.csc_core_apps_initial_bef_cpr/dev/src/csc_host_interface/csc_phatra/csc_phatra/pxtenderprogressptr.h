
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXTENDERPROGRESSPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXTENDERPROGRESSPTR_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
class pxTenderProgress;
namespace domMod
{
    namespace pharmosTransaction
    {
		namespace processing
        {
			typedef boost::shared_ptr< ::pxTenderProgress > pxTenderProgressPtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXTENDERPROGRESSPTR_H
