//---------------------------------------------------------------------------//
/*! \file accessorexecutionexception_h.h
 *  \brief exception indicating execution problem with an accessor
 *  \author Bischof Bjoern
 *  \date 20.08.2009
 *  \version 00.00.00.01 first version
 */ //-----------------------------------------------------------------------//

#ifndef GUARD_ACCESSOREXECUTION_EXCEPTION_H
#define GUARD_ACCESSOREXECUTION_EXCEPTION_H

//---------------------------------------------------------------------------//
// include section
//---------------------------------------------------------------------------//
#include <vector>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_exceptions.h>


namespace util
{
class AccessorExecutionException : public basar::Exception
{
public:
	/*! \brief constructor */
	AccessorExecutionException( const basar::ExceptInfo & sInfo );
	/*! \brief destructor */
	~AccessorExecutionException();

private:
	//!< forbidden
	AccessorExecutionException();					
};

} // end namespace util



#endif // GUARD_ACCESSOREXECUTION_EXCEPTION_H

