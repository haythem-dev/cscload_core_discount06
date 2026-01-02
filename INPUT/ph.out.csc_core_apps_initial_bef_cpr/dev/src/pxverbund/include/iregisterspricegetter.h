//-------------------------------------------------------------------------------------------------//
/*! \file
*   \brief 
*   \author b.bischof@phoenixgroup.eu
*   \date 08.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PRICING_IREGISTERPRICEGETTER_H
#define GUARD_CSC_PRICING_IREGISTERPRICEGETTER_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
//#include <libutil/viewconn.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
class nMoney;

//-------------------------------------------------------------------------------------------------//
// interface declaration section
//-------------------------------------------------------------------------------------------------//
namespace csc
{
    namespace pricing
    {
        class IRegisterPriceGetter
        {
            public:
                virtual ~IRegisterPriceGetter(){}
				virtual const nMoney& getMaxWholesalePrice() const = 0;
				virtual const nMoney& getReferencePrice() const = 0;
        };
    } // namespace pricing
} // namespace csc

#endif
