//-------------------------------------------------------------------------------------------------//
/*! \file
*   \brief 
*   \author b.bischof@phoenixgroup.eu
*   \date 19.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PRICING_IORDERTYPEGETTER_H
#define GUARD_CSC_PRICING_IORDERTYPEGETTER_H

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
        class IOrderTypeGetter
        {
            public:
                virtual ~IOrderTypeGetter(){}
                /* The following methods must be implemented as non-const methods, b/c for implementation a cascade of methods ia called  - all non const.*/
                virtual bool isNormal() /*const */= 0;
                virtual bool isTenderInvoice() /*const */= 0;
        };
    } // namespace pricing
} // namespace csc

#endif
