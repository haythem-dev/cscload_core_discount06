//-------------------------------------------------------------------------------------------------//
/*! \file
*   \brief
*   \author b.bischof@phoenixgroup.eu
*   \date   03.11.2021
*/
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_DISCOUNT_COLLECTION_FINDER_H
#define GUARD_LIBCSC_DISCOUNT_COLLECTION_FINDER_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "idiscountcollectionfinder.h"
#include <discount/basevalues/discountbasevalue/idiscountbasevaluerepositoryptr.h>
#include <discount/calculator/commands/idiscountfilter.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
class pxOrder;

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace libcsc
{
    namespace discount
    {
        class DiscountCollectionFinder : public IDiscountCollectionFinder
        {
            //--------------------------------------------------------------------------------------------------//
            // object declaration section
            //--------------------------------------------------------------------------------------------------//
            public:
                DiscountCollectionFinder();
                ~DiscountCollectionFinder();

                void injectDiscountBaseValueRepository( IDiscountBaseValueRepositoryPtr );
                void injectFilters(const DiscountFilterList& filters);
                
                virtual const DiscountBaseValueList& find( pxOrder* order, long articleNo, int qty, double* pharmacyPurchasePrice = 0 );
                virtual const DiscountBaseValueList& get() const;
                virtual void clear();

            private:
                /////////////////////////////////////////////////////////////////////////
                // private member methods
                /////////////////////////////////////////////////////////////////////////
                DiscountCollectionFinder(const DiscountCollectionFinder& );
                DiscountCollectionFinder& operator= (const DiscountCollectionFinder& );

                /////////////////////////////////////////////////////////////////////////
                // private member variables
                /////////////////////////////////////////////////////////////////////////
                IDiscountBaseValueRepositoryPtr m_DiscountBaseValueRepository;
                DiscountFilterList              m_Filters;
                DiscountBaseValueList           m_DiscountWorkingList;

        };
    } // discount
} // libcsc

#endif
