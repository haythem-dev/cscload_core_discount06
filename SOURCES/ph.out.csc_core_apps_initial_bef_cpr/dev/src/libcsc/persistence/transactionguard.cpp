#include "transactionguard.h"

namespace libcsc
{
namespace persistence
{
TransactionGuard::TransactionGuard( nDataBase * transactionHandler ) 
: m_TransactionHandler( transactionHandler ), 
  m_OwnTransaction( false )
{
}

TransactionGuard::~TransactionGuard()
{
	if( !m_OwnTransaction )
	{
		return;
	}

	if( isInTransaction() )
	{
		rollback();
	}
}

void TransactionGuard::begin()
{
	if( !isInTransaction() )
	{
		m_OwnTransaction = true;
		m_TransactionHandler->nDBBeginTransaction(cDBTransDataBase);
	}
}

void TransactionGuard::commit()
{
	if( m_OwnTransaction )
	{
		m_TransactionHandler->nDBCommit(cDBTransDataBase);
	}
}

void TransactionGuard::rollback()
{
	if( m_OwnTransaction ) 
	{
		m_TransactionHandler->nDBRollBack();
	}
}

bool TransactionGuard::isInTransaction() const
{
	return m_TransactionHandler->nDBInTransaction();
}

} // end namespace persistence
} // end namespace libcsc
