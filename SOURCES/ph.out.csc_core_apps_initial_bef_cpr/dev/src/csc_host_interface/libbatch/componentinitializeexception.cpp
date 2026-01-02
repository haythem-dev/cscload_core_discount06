//---------------------------------------------------------------------------------------------------//
// include section
//---------------------------------------------------------------------------------------------------//
#include "componentinitializeexception.h"

//---------------------------------------------------------------------------------------------------//
// class declaration section
//---------------------------------------------------------------------------------------------------//
namespace util
{
ComponentInitializeException::ComponentInitializeException( const basar::ExceptInfo & sInfo )
: BaseException( sInfo, "ComponentInitializeException" )
{
}

ComponentInitializeException::~ComponentInitializeException()
{
}

} 
