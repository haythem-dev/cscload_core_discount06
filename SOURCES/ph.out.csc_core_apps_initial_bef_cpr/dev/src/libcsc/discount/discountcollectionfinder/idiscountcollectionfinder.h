//-------------------------------------------------------------------------------------------------//
/*! \file
*   \brief 
*   \author b.bischof@phoenixgroup.eu
*   \date   01.11.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_IDISCOUNT_COLLECTION_FINDER_H
#define GUARD_LIBCSC_IDISCOUNT_COLLECTION_FINDER_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h>
#include "exceptions/invalidparameterexception.h"

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
class pxOrder;

namespace libcsc
{
    namespace discount
    {
        //typedef DiscountBaseValueList::const_iterator DiscountBaseValueList_ConstIterator;
        //typedef DiscountBaseValueList::const_iterator DiscountBaseValueList_ConstIterator;
    }
}

//-------------------------------------------------------------------------------------------------//
// interface declaration section
//-------------------------------------------------------------------------------------------------//
namespace libcsc
{
    namespace discount
    {
        class IDiscountCollectionFinder
        {
            public:
                virtual ~IDiscountCollectionFinder(){}
				virtual const DiscountBaseValueList& find( pxOrder* order, long articleNo, int qty, double* pharmacyPurchasePrice = 0 ) = 0;
                virtual const DiscountBaseValueList& get() const = 0;
                virtual void clear() = 0;
        };
    }
}

#endif
