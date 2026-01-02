#include "cscexceptionbase.h"

namespace libcsc
{
namespace exceptions
{
CSCExceptionBase::CSCExceptionBase( const basar::ExceptInfo & sInfo, const basar::VarString & exceptionType )
: basar::Exception( sInfo, exceptionType )
{
}

CSCExceptionBase::~CSCExceptionBase()
{
}

const basar::VarString & CSCExceptionBase::reason() const
{
	return m_InfoStruct.reason;
}

} // end namespace exceptions
} // end namespace libcsc
