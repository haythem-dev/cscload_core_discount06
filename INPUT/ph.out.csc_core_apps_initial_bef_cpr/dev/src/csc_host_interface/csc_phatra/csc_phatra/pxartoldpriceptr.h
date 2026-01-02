
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTOLDPRICEPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTOLDPRICEPTR_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
class pxArtOldPrice;
namespace domMod
{
    namespace pharmosTransaction
    {
		namespace processing
        {
			typedef boost::shared_ptr< ::pxArtOldPrice > pxArtOldPricePtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTOLDPRICEPTR_H
