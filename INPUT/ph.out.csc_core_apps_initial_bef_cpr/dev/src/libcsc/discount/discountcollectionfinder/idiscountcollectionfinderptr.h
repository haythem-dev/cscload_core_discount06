//-------------------------------------------------------------------------------------------------//
/*! \file
*   \brief
*   \author b.bischof@phoenixgroup.eu
*   \date   01.11.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_IDISCOUNT_COLLECTION_FINDER_PTR_H
#define GUARD_LIBCSC_IDISCOUNT_COLLECTION_FINDER_PTR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//-------------------------------------------------------------------------------------------------//
// interface declaration section
//-------------------------------------------------------------------------------------------------//
namespace libcsc
{
    namespace discount
    {
        class IDiscountCollectionFinder;
        typedef boost::shared_ptr< libcsc::discount::IDiscountCollectionFinder > IDiscountCollectionFinderPtr;
    }
}

#endif
