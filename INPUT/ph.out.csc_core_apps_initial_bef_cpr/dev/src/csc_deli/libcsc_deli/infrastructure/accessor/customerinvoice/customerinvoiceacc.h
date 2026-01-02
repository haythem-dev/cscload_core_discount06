#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICEACC_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICEACC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

//-------------------------------------------------------------------------------------------------//
// sqlstring builder declaration section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace customerInvoice
{
    BEGIN_QUERY_BUILDER_DECLARATION( FindCustomerInvoiceByPattern )
    END_BUILDER_DECLARATION

    BEGIN_WRITE_BUILDER_DECLARATION( InsertCustomerInvoice )
    END_BUILDER_DECLARATION

    BEGIN_WRITE_BUILDER_DECLARATION( UpdateCustomerInvoice )
    END_BUILDER_DECLARATION

    BEGIN_WRITE_BUILDER_DECLARATION( SetInvoicedFlag )
    END_BUILDER_DECLARATION

} // end namespace customerInvoice
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif //GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERINVOICEACC_H
