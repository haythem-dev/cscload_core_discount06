#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_CUSTOMERINVOICECONNECTEDFACTORY_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_CUSTOMERINVOICECONNECTEDFACTORY_H

#include "icustomerinvoiceconnectedfactory.h"

#include "icustomerinvoicegetterptr.h"
#include <libutil/accessor.h>
#include <libutil/dbconnection.h>

//------------------------------------------------------------------------------//
// Forward declarations
//------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
        }
    }
}

namespace libcsc_deli
{
namespace componentManager
{
    class CustomerInvoiceConnectedFactory : public ICustomerInvoiceConnectedFactory
    {
    public:
        CustomerInvoiceConnectedFactory();
        ~CustomerInvoiceConnectedFactory();

        void                                            injectCustomerInvoiceGetter( ICustomerInvoiceGetterPtr );

        // from interface
        domMod::customerInvoice::ICustomerInvoicePtr    create( basar::db::aspect::AccessorPropertyTable_YIterator ) const;

    private:
        // forbidden
        CustomerInvoiceConnectedFactory( const CustomerInvoiceConnectedFactory& );
        CustomerInvoiceConnectedFactory& operator = ( const CustomerInvoiceConnectedFactory& );

        domMod::customerInvoice::ICustomerInvoicePtr    getCustomerInvoice()         const;

    private:
        ICustomerInvoiceGetterPtr                       m_CustomerInvoiceGetter;
    };

} // end namespace componentManager
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_COMPONENTMANAGER_CUSTOMERINVOICECONNECTEDFACTORY_H
