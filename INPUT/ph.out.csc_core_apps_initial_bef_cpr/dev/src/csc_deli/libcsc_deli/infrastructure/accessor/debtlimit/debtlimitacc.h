#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_DEBTLIMITACC_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_DEBTLIMITACC_H

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
namespace debtLimit
{
    BEGIN_QUERY_BUILDER_DECLARATION( SelectDebtLimit )
    END_BUILDER_DECLARATION

    BEGIN_WRITE_BUILDER_DECLARATION( InsertDebtLimit )
    END_BUILDER_DECLARATION

    BEGIN_WRITE_BUILDER_DECLARATION( UpdateDebtLimit )
    END_BUILDER_DECLARATION

    BEGIN_WRITE_BUILDER_DECLARATION( DeleteDebtLimit )
    END_BUILDER_DECLARATION

} // end namespace debtLimit
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif //GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_DEBTLIMITACC_H
