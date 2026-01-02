
#include "transactionguard.h"

namespace domMod
{

TransactionGuard::TransactionGuard()
: m_ownTransaction( false )
{
}

TransactionGuard::TransactionGuard( 
	basar::db::aspect::ConnectionRef conn 
		)
: m_ownTransaction( false )
{
	init( conn );
}

TransactionGuard::~TransactionGuard()
{
	if( !m_ownTransaction )
	{
		return;
	}

	if( m_connection.isNull() ) 
	{
		// throw exception?
		return;
	}

	if( isInTransaction() ) 
	{
		m_connection.rollbackTransaction();
	}
}

void TransactionGuard::init( 
	basar::db::aspect::ConnectionRef conn 
		)
{
	m_connection = conn;
}

bool TransactionGuard::isInTransaction() const
{
	return m_connection.isInTransaction();
}

void TransactionGuard::beginTransaction()
{
	if( !isInTransaction() )
	{
		m_ownTransaction = true;
		m_connection.beginTransaction();
	}
}

void TransactionGuard::commitTransaction()
{
	if( m_ownTransaction ) 
	{
		m_connection.commitTransaction();
	}
}

void TransactionGuard::rollbackTransaction()
{
	if( m_ownTransaction ) 
	{
		m_connection.rollbackTransaction();
	}
}

} // end namespace domMod
