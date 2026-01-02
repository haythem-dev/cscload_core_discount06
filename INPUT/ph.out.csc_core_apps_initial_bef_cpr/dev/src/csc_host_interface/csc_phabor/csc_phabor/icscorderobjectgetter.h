//-------------------------------------------------------------------------------------------------//
/*! \file ICSCOrderObjectGetter.h
 *  \brief
 *  \author Julian Machata
 *  \date 29.06.2012
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_UTIL_ICSCBATCHORDEROBJECT_GETTER_H
#define GUARD_UTIL_ICSCBATCHORDEROBJECT_GETTER_H

#include <libbasardbaspect_accessorpropertytable.h>
#include "pvhx04_includes.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTableRef;
        }
    }
}

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace util
{
    class ICSCOrderObjectGetter
    {
        public:
            virtual ~ICSCOrderObjectGetter(){};

            virtual pxCustBase*         getPxCustomer()         = 0;
            virtual pxCustOrderInfo*    getPxCustomerInfo()     = 0;
            virtual pxParameter*        getPxOrderParameter()   = 0;
            virtual pxOrder*            getPxOrder()            = 0;

            virtual void setPxCustomer( pxCustBase* customer )              = 0;
            virtual void setPxCustomerInfo( pxCustOrderInfo* customerInfo ) = 0;
            virtual void setPxOrderParameter( pxParameter* parameter )      = 0;
            virtual void setPxOrder( pxOrder* order )                       = 0;

            virtual pxVerbund::IPXVBOrderTransmitPtr    getPxOrderTransmit()    = 0;
            virtual pxVerbund::IPXVBSessionPtr          getPxVbSession()        = 0;
    };

}
}
} // end namespace util

//----------------------------------------------------------------------------
#endif //GUARD_UTIL_ICSCBATCHORDEROBJECT_GETTER_H
