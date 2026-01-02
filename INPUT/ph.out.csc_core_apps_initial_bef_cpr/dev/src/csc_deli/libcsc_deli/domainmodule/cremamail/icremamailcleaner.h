#ifndef GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_ICREMAMAILCLEANER_H
#define GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_ICREMAMAILCLEANER_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
            class AccessorPropertyTableRef;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// interface class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace cremaMail
{
    class ICremaMailCleaner
    {

    public:
        virtual ~ICremaMailCleaner() {}

        virtual void                                                        cleanup()                       = 0;
    };

} // end namespace cremaMail
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_ICREMAMAILCLEANER_H
