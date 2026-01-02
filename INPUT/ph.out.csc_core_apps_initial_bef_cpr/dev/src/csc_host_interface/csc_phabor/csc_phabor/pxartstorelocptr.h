
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTSTORELOCPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTSTORELOCPTR_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
class pxArtStoreLoc;

namespace domMod
{
    namespace pharmosTransaction
    {
		namespace processing
        {
            
			typedef boost::shared_ptr< ::pxArtStoreLoc > pxArtStoreLocPtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTSTORELOCPTR_H

