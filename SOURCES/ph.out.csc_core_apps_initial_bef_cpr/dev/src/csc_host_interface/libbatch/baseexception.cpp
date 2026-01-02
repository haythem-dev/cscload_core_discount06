// following include directive must be the first include !
#include "baseexception.h"

namespace util
{

BaseException::BaseException( const basar::ExceptInfo & sInfo, const basar::VarString & exceptionType )
: BasarException( sInfo, exceptionType )
{
}

BaseException::~BaseException()
{
}

const basar::VarString& BaseException::reason() const
{
	return m_InfoStruct.reason;
}

}
