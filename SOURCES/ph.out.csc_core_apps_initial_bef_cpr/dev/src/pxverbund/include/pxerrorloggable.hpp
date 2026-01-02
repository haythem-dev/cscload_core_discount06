#ifndef GUARD_PXERRORLOGGABLE_HPP
#define GUARD_PXERRORLOGGABLE_HPP

#include "error.hpp"

class pxErrorLoggable : public nError
{
public:
	pxErrorLoggable();
	virtual ~pxErrorLoggable();
	
	virtual void WriteLog(const nString& message, nErrorState state, int msgid);

//	pxErrorLoggable& operator=(const pxErrorLoggable&);
//	pxErrorLoggable& operator=(const nError&);
};

#endif // GUARD_PXERRORLOGGABLE_HPP
