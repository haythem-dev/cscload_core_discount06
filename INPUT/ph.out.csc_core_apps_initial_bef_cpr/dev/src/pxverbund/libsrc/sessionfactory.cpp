#include "sessionfactory.h"
#include "invalidsessionexception.h"

#include <persistence/connection.h>
#include <pxsess.hpp>
#include <boost/make_shared.hpp>

SessionFactory::SessionFactory( libcsc::persistence::ConnectionPtr connection )
    : m_Connection( connection )
{
}

SessionFactory::SessionFactory( basar::db::sql::ConnectionRef connection )
    : m_Connection( boost::make_shared< libcsc::persistence::Connection >( connection ) )
{
}

SessionFactory::~SessionFactory()
{
}

PxSessionPtr SessionFactory::create( const pxSessionInitialization& sessionInitialization )
{
    PxSessionPtr session = boost::make_shared< pxSession >( sessionInitialization );
    session->injectDBConnection( m_Connection );

	if( ! session->IsGoodState() )
	{
		basar::VarString reason = session->ErrorMsg();
		basar::ExceptInfo info( "SessionFactory::create", reason, __FILE__, __LINE__ );
		throw InvalidSessionException( info ); 
	}

    return session;
}
