#ifndef GUARD_PXVERBUND_LOCK_PXLOCKACCESSOR_ERRORHANDLER_H
#define GUARD_PXVERBUND_LOCK_PXLOCKACCESSOR_ERRORHANDLER_H

#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql.h>
#include <liblockmanager/infrastructure/accessor/ilockaccessorerrorhandler.h>

namespace lock {

class PxLockAccessorErrorHandler : public libLockManager::accessor::ILockAccessorErrorHandler
{
public:
	PxLockAccessorErrorHandler();
	virtual ~PxLockAccessorErrorHandler();

	// from ILockAccessorErrorHandler interface
	void handleError(const basar::VarString sql, const basar::db::sql::ExecuteReturnInfo info, const basar::VarString context);

private:
	// don't allow copying of this class
	PxLockAccessorErrorHandler( const PxLockAccessorErrorHandler& );
	PxLockAccessorErrorHandler& operator = ( const PxLockAccessorErrorHandler& );
};


} // end namespace lock

#endif // GUARD_PXVERBUND_LOCK_PXLOCKACCESSOR_ERRORHANDLER_H
