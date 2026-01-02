//----------------------------------------------------------------------------
/*! \file	  customeracc.h
 *  \brief  string builder declaration for customer accessor
 *  \author	Frank Naumann
 *  \date   23.03.2010
 */
//----------------------------------------------------------------------------

#ifndef GUARD_CUSTOMERACC_H
#define GUARD_CUSTOMERACC_H

//----------------------------------------------------------------------------

#include <libbasardbaspect_macros.h>

//----------------------------------------------------------------------------
/*! \brief namespace for customer-accessor.
 */
namespace acc_customer {

/*! \brief class for selecting customer by customerno. final class.
 */
BEGIN_QUERY_BUILDER_DECLARATION(SelectCustomer)
END_BUILDER_DECLARATION

/*! \brief class for inserting customer. final class.
 */
BEGIN_WRITE_BUILDER_DECLARATION(InsertCustomer)
END_BUILDER_DECLARATION

/*! \brief class for updating customer. final class.
 */
BEGIN_WRITE_BUILDER_DECLARATION(UpdateCustomer)
END_BUILDER_DECLARATION

} // namespace acc_customer

//----------------------------------------------------------------------------

#endif	// GUARD_CUSTOMERACC_H

//----------------------------------------------------------------------------
