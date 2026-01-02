#ifndef GUARD_PXVERBUND_LOCK_PXLOCKACCESSORDECORATOR_H
#define GUARD_PXVERBUND_LOCK_PXLOCKACCESSORDECORATOR_H

#include <liblockmanager/infrastructure/accessor/ilockaccessor.h>
#include <liblockmanager/infrastructure/accessor/ilockaccessorptr.h>

#include <libbasarcmnutil_bstring.h>

// FIXME: Please remove when pxdb/ ESQL code isn't existing anymore
// This class manages and switches connections automatically.
// Normally this isn't needed because Basar DB connections handle this
// internally. But as long as ESQLC with DADE are still in use which
// don't handle several connections automatically, this class is still needed.

namespace lock
{
	class PxLockAccessorDecorator : public libLockManager::accessor::ILockAccessor
	{
	public:
		PxLockAccessorDecorator( libLockManager::accessor::ILockAccessorPtr,
			const basar::VarString internalConnName,
			const basar::VarString lockConnName );
		virtual ~PxLockAccessorDecorator();

	// from ILockAccessor interface
	public:
		bool                                        findByKey ( const libLockManager::IKey&       );
		void                                        save      ( const libLockManager::ILockEntry& );
		void                                        erase     ( const libLockManager::IKey&       );
		void                                        forceErase( const libLockManager::IKey&       );

		void                                        eraseStaleLocks();
		void                                        injectErrorHandler(libLockManager::accessor::ILockAccessorErrorHandlerPtr);

	private:
		// don't allow copying of this class
		PxLockAccessorDecorator( const PxLockAccessorDecorator& );
		PxLockAccessorDecorator& operator = ( const PxLockAccessorDecorator& );

		void                                        setInternalConnection();
		void                                        setLockConnection();

		libLockManager::accessor::ILockAccessorPtr  m_Accessor;
		basar::VarString                            m_internalConnectionName;
		basar::VarString                            m_lockConnectionName;
	};

} // end namespace lock

#endif // GUARD_PXVERBUND_LOCK_PXLOCKACCESSORDECORATOR_H
