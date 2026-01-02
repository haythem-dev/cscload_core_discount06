#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERORDERCOLLECTIONACC_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERORDERCOLLECTIONACC_H

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
namespace customerOrder
{
    BEGIN_QUERY_BUILDER_DECLARATION( FindCustomerOrderCollection )
    END_BUILDER_DECLARATION

} // end namespace customerOrder
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif //GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CUSTOMERORDERCOLLECTIONACC_H
