#ifndef GUARD_LIBCSC_CREMA_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_CREMA_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <crema/repository/irepositoryptr.h>

namespace libcsc {
namespace crema {

class CremaComponentManager : public boost::enable_shared_from_this<CremaComponentManager>
{
public:
    CremaComponentManager();
    virtual ~CremaComponentManager();

    void injectConnection( persistence::ConnectionPtr connection );

    repo::IRepositoryPtr getRepository();

private:
    CremaComponentManager( const CremaComponentManager& );
    CremaComponentManager& operator=( const CremaComponentManager& );

    repo::IRepositoryPtr createRepository();

    persistence::IAccessorPtr createAccessor();

    persistence::ConnectionPtr  m_Connection;
};

} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_COMPONENT_MANAGER_H
