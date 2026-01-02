//----------------------------------------------------------------------------
/*! \file		pharmostransactionacc.h
 *  \brief		accessor for pharmostransaction
 *  \author		Julian Machata
 *  \date		28.06.2012
 */
//----------------------------------------------------------------------------


#ifndef GUARD_PHARMOSTRANSACTIONACC_H
#define GUARD_PHARMOSTRANSACTIONACC_H

#include <libbasardbaspect.h>

//----------------------------------------------------------------------------
/*! \brief namespace for pharmostransaction accessor.
 */

namespace acc_pharmostransaction
{	
	// SELECTs
	BEGIN_AGGREGATE_QUERY_BUILDER_DECLARATION(SelectLastKey)
	END_BUILDER_DECLARATION		

    BEGIN_QUERY_BUILDER_DECLARATION( SelectOpenTransactions )
	END_BUILDER_DECLARATION		

	BEGIN_WRITE_BUILDER_DECLARATION(InsertPharmosTransaction)
	END_BUILDER_DECLARATION

	BEGIN_WRITE_BUILDER_DECLARATION(UpdatePharmosTransaction)
	END_BUILDER_DECLARATION

} // namespace acc_pharmostransaction

//-----------------------------------------------------------------------------

#endif // GUARD_PHARMOSTRANSACTIONACC_H

//-----------------------------------------------------------------------------

