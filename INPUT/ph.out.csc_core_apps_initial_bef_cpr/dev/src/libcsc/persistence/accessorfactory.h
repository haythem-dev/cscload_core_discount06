#ifndef GUARD_LIBCSC_PERSISTENCE_ACCESSOR_FACTORY_H
#define GUARD_LIBCSC_PERSISTENCE_ACCESSOR_FACTORY_H

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_preparedstatementref.h>
#include <persistence/isqlparameterbinderptr.h>
#include <persistence/iaccessorfactory.h>
#include <persistence/iaccessorptr.h>
#include <persistence/connectionptr.h>

namespace libcsc
{
namespace persistence
{
class AccessorFactory : public IAccessorFactory
{
public:
    AccessorFactory();
    virtual ~AccessorFactory();

    void injectConnection(persistence::ConnectionPtr connection);

    virtual bool                                    EnsureDBConnectionWithDirtyRead();
    virtual persistence::IAccessorPtr               createAccessor() const;

private:
    // prohibit copy constructor and assignment operator:
    AccessorFactory(const AccessorFactory &);
    AccessorFactory& operator=(const AccessorFactory &);

    persistence::ConnectionPtr                  m_Connection;
    bool                                        m_DirtyReadSet;
};

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_ACCESSOR_FACTORY_H
