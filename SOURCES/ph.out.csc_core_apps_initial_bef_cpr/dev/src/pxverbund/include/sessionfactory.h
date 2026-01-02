#ifndef GUARD_PP_SESSIONFACTORY_H
#define GUARD_PP_SESSIONFACTORY_H

/*
    This factory creates a new shared_ptr containing pxSession
    from pxSessionInitialization. In contrast to calling pxSession( pxSessionInitialization )
    directly it is not needed to include pxSession header which depends on further headers
    from pxdb, cxxtools and therelike
*/

#include "pxsessionptr.h"
#include <persistence/connectionptr.h>
#include <libbasardbsql_connectionref.h>

class pxSessionInitialization;

class SessionFactory
{
public:
    explicit SessionFactory( libcsc::persistence::ConnectionPtr );
    explicit SessionFactory( basar::db::sql::ConnectionRef      );
    ~SessionFactory();

    PxSessionPtr                  create( const pxSessionInitialization& );

private:
    // forbidden
    SessionFactory();
    SessionFactory( const SessionFactory& );
    SessionFactory& operator = ( const SessionFactory& );

private:
    libcsc::persistence::ConnectionPtr m_Connection;
};

#endif // GUARD_PP_SESSIONFACTORY_H
