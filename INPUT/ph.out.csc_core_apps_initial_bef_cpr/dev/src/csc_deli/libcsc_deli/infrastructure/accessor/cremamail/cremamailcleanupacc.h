#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CREMAMAILCLEANUPACC_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CREMAMAILCLEANUPACC_H

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
namespace cremaMail
{
    BEGIN_WRITE_BUILDER_DECLARATION( CleanupSendMailFlagForDebtLevel )
    END_BUILDER_DECLARATION

    BEGIN_WRITE_BUILDER_DECLARATION( CleanupSendMailFlagForAmount )
    END_BUILDER_DECLARATION

} // end namespace cremaMail
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif //GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSOR_CREMAMAILCLEANUPACC_H
