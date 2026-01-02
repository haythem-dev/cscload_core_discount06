
#ifndef GUARD_TRANSACTIONGUARD_H
#define GUARD_TRANSACTIONGUARD_H

#include <libbasardbaspect_connectionref.h>
 
namespace domMod
{
//------------------------------------------------------------------------------------------------//
/*! \brief  helper class for automatic rollback of a transaction if it has not been committed.
\n		If an initialized instance of this class is destroyed and the transaction has not  
\n		been committed a rollback is done. This is done only if the transaction was started through
\n		this instance of TransactionGuard. If a transaction was already active when beginTransaction()
\n		was called no transaction handling is done by this class.
\n This is a final class.   
\throw no-throw */
//------------------------------------------------------------------------------------------------//
class TransactionGuard
{
public:
	/*! \brief	standard ctor
	\throw	no-throw */
	TransactionGuard();
	/*! \brief	ctor that also calls init() with given ConnectionRef.
	\throw	no-throw */
	TransactionGuard( basar::db::aspect::ConnectionRef conn );
	~TransactionGuard();

	/*!	\brief	Initializes object with an ConnectionRef which can be used for transaction handling.
	\n		Without initialization with a valid ConnectionRef the methods of this class cannot be used.
	\throw	no-throw */
	void		init				( basar::db::aspect::ConnectionRef conn );

	/*!	\brief The method indicates whether a transaction is active or not.
	\throw NullReferenceException. */
	bool	isInTransaction		() const;

	/*! \brief	The method starts the transaction but only when a transaction is not already active.
	\throw NullReferenceException. */
	void		beginTransaction	();
	/*! \brief	The method realizes the transaction but only when the transaction was begun through this instance.
	\throw NullReferenceException. */
	void		commitTransaction	();
	/*! \brief	The method cancels the transaction but only when the transaction was begun through this instance.
	\throw NullReferenceException. */
	void		rollbackTransaction	();

private:
	basar::db::aspect::ConnectionRef		m_connection;
	bool						m_ownTransaction;
};

} // end namespace domMod

#endif // GUARD_TRANSACTIONGUARD_H
