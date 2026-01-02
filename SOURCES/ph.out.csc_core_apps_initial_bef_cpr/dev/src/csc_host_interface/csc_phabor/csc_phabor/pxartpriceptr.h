
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTPRICEPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTPRICEPTR_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
class pxArtPrice;
namespace domMod
{
    namespace pharmosTransaction
    {
		namespace processing
        {
			typedef boost::shared_ptr< ::pxArtPrice > pxArtPricePtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_PXARTPRICEPTR_H
