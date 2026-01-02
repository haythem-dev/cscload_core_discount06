#ifndef GUARD_PXVERBUND_INVALIDSESSIONEXCEPTION_H
#define GUARD_PXVERBUND_INVALIDSESSIONEXCEPTION_H

#include <exceptions/cscexceptionbase.h>

class InvalidSessionException : public libcsc::exceptions::CSCExceptionBase
{
	public:
		InvalidSessionException( const basar::ExceptInfo & sInfo );
		virtual ~InvalidSessionException();

	private:
		InvalidSessionException();
};

#endif //GUARD_PXVERBUND_INVALIDSESSIONEXCEPTION_H

