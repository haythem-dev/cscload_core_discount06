//---------------------------------------------------------------------------//
/*! \file accessorexecutionexception_h.h
 *  \brief exception indicating execution problem with an accessor
 *  \author Bischof Bjoern
 *  \date 20.08.2009
 *  \version 00.00.00.01 first version
 */ //-----------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// include section
//---------------------------------------------------------------------------//
#include "accessorexecutionexception.h"

namespace util
{

AccessorExecutionException::AccessorExecutionException( const basar::ExceptInfo & sInfo )
: BasarException( sInfo, "MissingDatasetException" )
{
}
AccessorExecutionException::~AccessorExecutionException()
{
}

} // end namespace util
