
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTBASE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTBASE_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
class pxArtBase;
namespace domMod
{
    namespace pharmosTransaction
    {
		namespace processing
        {
			typedef boost::shared_ptr< ::pxArtBase > pxArtBasePtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTBASE_H

