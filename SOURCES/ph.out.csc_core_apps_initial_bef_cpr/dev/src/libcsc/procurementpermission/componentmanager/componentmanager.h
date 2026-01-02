/*
 * componentmanager.h
 *
 *  Created on: 09.02.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_PROCUREMENTPERMISSION_COMPONENTMANAGER_H
#define GUARD_LIBCSC_PROCUREMENTPERMISSION_COMPONENTMANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include "procurementpermission/repository/irepositoryptr.h"

namespace libcsc {
namespace procurementpermission {

class pxSession;

class ComponentManager : public boost::enable_shared_from_this<ComponentManager>
{
public:
    ComponentManager();
    ~ComponentManager();

    void injectConnection(persistence::ConnectionPtr connection);
    repo::IRepositoryPtr getRepository();

private:
    ComponentManager(ComponentManager const& );
    ComponentManager& operator=(ComponentManager const &);

    persistence::IAccessorPtr createAccessor();
    repo::IRepositoryPtr createRepository();

    persistence::ConnectionPtr m_Connection;
};

} // end namespace procurementpermission
} // end namespace libcsc

#endif // GUARD_LIBCSC_PROCUREMENTPERMISSION_COMPONENTMANAGER_H
