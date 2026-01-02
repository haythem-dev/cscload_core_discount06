#include "customerinvoiceconnectedfactory.h"

#include "icustomerinvoicegetter.h"

#include "domainmodule/customerinvoice/icustomerinvoice.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"

#include <boost/make_shared.hpp>

namespace libcsc_deli
{
namespace componentManager
{
    CustomerInvoiceConnectedFactory::CustomerInvoiceConnectedFactory()
    {
    }

    CustomerInvoiceConnectedFactory::~CustomerInvoiceConnectedFactory()
    {
    }

    void CustomerInvoiceConnectedFactory::injectCustomerInvoiceGetter( ICustomerInvoiceGetterPtr customerInvoiceGetter )
    {
        m_CustomerInvoiceGetter = customerInvoiceGetter;
    }

    domMod::customerInvoice::ICustomerInvoicePtr CustomerInvoiceConnectedFactory::getCustomerInvoice() const
    {
        CHECK_INSTANCE_EXCEPTION( m_CustomerInvoiceGetter.get() );
        return m_CustomerInvoiceGetter->getCustomerInvoice();
    }

    domMod::customerInvoice::ICustomerInvoicePtr CustomerInvoiceConnectedFactory::create( basar::db::aspect::AccessorPropertyTable_YIterator yit ) const
    {
        domMod::customerInvoice::ICustomerInvoicePtr customerInvoice = getCustomerInvoice();

        customerInvoice->resetSearchYit();
        basar::db::aspect::AccessorPropertyTable_YIterator searchYit = customerInvoice->getSearchYit();
        searchYit.match( yit ); // branchno, customerno, doctype, docno and date

        customerInvoice->findByPattern( searchYit ); // search DB for entry for this customer invoice data
        return customerInvoice;
    }

} // end namespace componentManager
} // end namespace libcsc_deli
