#include "invalidsessionexception.h"

InvalidSessionException::InvalidSessionException( const basar::ExceptInfo & sInfo )
	: CSCExceptionBase( sInfo, "InvalidSessionException" )
{
}

InvalidSessionException::~InvalidSessionException()
{
}

