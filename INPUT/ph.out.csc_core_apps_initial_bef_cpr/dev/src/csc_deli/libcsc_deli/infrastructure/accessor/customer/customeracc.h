#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERACC_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERACC_H

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
namespace customer
{
    BEGIN_QUERY_BUILDER_DECLARATION( SelectCustomerByPartnerNo )
    END_BUILDER_DECLARATION

} // end namespace customer
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif //GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERACC_H
