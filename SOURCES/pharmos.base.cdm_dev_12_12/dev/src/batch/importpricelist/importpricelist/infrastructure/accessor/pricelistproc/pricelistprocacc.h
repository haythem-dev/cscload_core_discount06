//-------------------------------------------------------------------------------------------------//
/*! \file	pricelistprocacc.h
*   \brief	Accessor for the price list processing data.
*   \author NTT DATA
*   \date	14.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_PRICELISTPROCACC_H
#define GUARD_PRICELISTPROCACC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

//-------------------------------------------------------------------------------------------------//
// sqlstring builder declaration section
//-------------------------------------------------------------------------------------------------//
namespace importpricelist
{
	namespace infrastructure
	{
		namespace accessor
		{
			namespace pricelistproc
			{
				namespace lit
				{
					const basar::VarString PriceListProcAcc("PriceListProcAcc");
					const basar::VarString SelectPriceListProcByFileName("SelectPriceListProcByFileName");
					const basar::VarString SelectPriceListProcByKey("SelectPriceListProcByKey");
					const basar::VarString SelectMaxDates("SelectMaxDates");
					const basar::VarString SelectMaxSeqNo("SelectMaxSeqNo");
					const basar::VarString InsertPriceListProc("InsertPriceListProc");
					const basar::VarString UpdatePriceListProc("UpdatePriceListProc");
					const basar::VarString UpdateStatusAndInfoMsg("UpdateStatusAndInfoMsg");
					const basar::VarString UpdateStatusToFailed("UpdateStatusToFailed");
					const basar::VarString DeletePriceListProcByFileName("DeletePriceListProcByFileName");
					const basar::VarString DeletePriceListProcByKey("DeletePriceListProcByKey");
				}

				BEGIN_QUERY_BUILDER_DECLARATION(SelectPriceListProcByFileName)
				END_BUILDER_DECLARATION

				BEGIN_QUERY_BUILDER_DECLARATION(SelectPriceListProcByKey)
				END_BUILDER_DECLARATION

				BEGIN_QUERY_BUILDER_DECLARATION(SelectMaxDates)
				END_BUILDER_DECLARATION

				BEGIN_QUERY_BUILDER_DECLARATION(SelectMaxSeqNo)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(InsertPriceListProc)
				END_BUILDER_DECLARATION
				
				BEGIN_WRITE_BUILDER_DECLARATION(UpdatePriceListProc)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(UpdateStatusAndInfoMsg)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(UpdateStatusToFailed)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(DeletePriceListProcByFileName)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(DeletePriceListProcByKey)
				END_BUILDER_DECLARATION
			} // end namespace pricelistproc
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace importpricelist

#endif // GUARD_PRICELISTPROCACC_H

