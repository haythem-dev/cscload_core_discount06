#ifndef GUARD_LIBCSC_PERSISTENCE_I_ACCESSOR_FACTORY_H
#define GUARD_LIBCSC_PERSISTENCE_I_ACCESSOR_FACTORY_H

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_preparedstatementref.h>
#include <persistence/isqlparameterbinderptr.h>
#include <persistence/iaccessorptr.h>

namespace libcsc
{
namespace persistence
{
class IAccessorFactory
{
public:
    virtual ~IAccessorFactory() {}

    virtual bool                                    EnsureDBConnectionWithDirtyRead() = 0;
    virtual persistence::IAccessorPtr               createAccessor() const = 0;
};

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_I_ACCESSOR_FACTORY_H
