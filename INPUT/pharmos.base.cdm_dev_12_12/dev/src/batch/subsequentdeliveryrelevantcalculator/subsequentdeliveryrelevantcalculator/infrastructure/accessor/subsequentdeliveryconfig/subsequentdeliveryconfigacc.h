//-------------------------------------------------------------------------------------------------//
/*! \file	subsequentdeliveryconfigacc.h
*   \brief	Accessor for subsequentdeliveryconfig - result of calculation.
*   \author NTT DATA
*   \date	18.10.2022
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_SUBSEQUENTDELIVERYCONFIGACC_H
#define GUARD_SUBSEQUENTDELIVERYCONFIGACC_H

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
			namespace subsequentdeliveryconfig
			{
				namespace lit
				{
					const basar::VarString SubsequentDeliveryConfigAcc("SubsequentDeliveryConfigAcc");
					const basar::VarString InitSubsequentDeliveryConfig("InitSubsequentDeliveryConfig");
					const basar::VarString InsertSubsequentDeliveryConfig("InsertSubsequentDeliveryConfig");
					const basar::VarString UpdateSubsequentDeliveryConfig("UpdateSubsequentDeliveryConfig");
					const basar::VarString ResetSubsequentDeliveryConfig("ResetSubsequentDeliveryConfig");
					const basar::VarString DeleteSubsequentDeliveryConfigForNotExistingArticles("DeleteSubsequentDeliveryConfigForNotExistingArticles");
					const basar::VarString DeleteSubsequentDeliveryConfigForBlockedArticles("DeleteSubsequentDeliveryConfigForBlockedArticles");
				}

				BEGIN_WRITE_BUILDER_DECLARATION(InitSubsequentDeliveryConfig)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(InsertSubsequentDeliveryConfig)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(UpdateSubsequentDeliveryConfig)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(ResetSubsequentDeliveryConfig)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(DeleteSubsequentDeliveryConfigForNotExistingArticles)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(DeleteSubsequentDeliveryConfigForBlockedArticles)
				END_BUILDER_DECLARATION
			} // end namespace subsequentdeliveryconfig
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace subsequentdeliveryrelevantcalculator

#endif // GUARD_SUBSEQUENTDELIVERYCONFIGACC_H

