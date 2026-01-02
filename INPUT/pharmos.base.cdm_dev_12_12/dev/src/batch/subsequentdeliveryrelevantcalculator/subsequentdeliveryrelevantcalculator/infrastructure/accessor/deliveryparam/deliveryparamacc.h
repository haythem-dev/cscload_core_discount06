//-------------------------------------------------------------------------------------------------//
/*! \file	deliveryparamacc.h
*   \brief	Accessor for the pricing data.
*   \author NTT DATA
*   \date	18.10.2022
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_DELIVERYPARAMACC_H
#define GUARD_DELIVERYPARAMACC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

//-------------------------------------------------------------------------------------------------//
// sqlstring builder declaration section
//-------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
	namespace infrastructure
	{
		namespace accessor
		{
			namespace deliveryparam
			{
				namespace lit
				{
					const basar::VarString DeliveryParamAcc("DeliveryParamAcc");
					const basar::VarString SelectDeliveryParams("SelectDeliveryParams");
				}

				BEGIN_QUERY_BUILDER_DECLARATION(SelectDeliveryParams)
				END_BUILDER_DECLARATION
			} // end namespace deliveryparam
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace subsequentdeliveryrelevantcalculator

#endif // GUARD_DELIVERYPARAMACC_H

