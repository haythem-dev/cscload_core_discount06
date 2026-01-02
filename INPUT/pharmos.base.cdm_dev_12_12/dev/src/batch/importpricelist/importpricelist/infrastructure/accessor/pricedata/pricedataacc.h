//-------------------------------------------------------------------------------------------------//
/*! \file	pricedataacc.h
*   \brief	Accessor for the pricing data.
*   \author NTT DATA
*   \date	25.08.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_PRICEDATAACC_H
#define GUARD_PRICEDATAACC_H

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
			namespace pricedata
			{
				namespace lit
				{
					const basar::VarString PriceDataAcc("PriceDataAcc");
					const basar::VarString SelectPriceDataByPharmacyGroup("SelectPriceDataByPharmacyGroup");
					const basar::VarString SelectPriceDataByArticlePharmacyGroup("SelectPriceDataByArticlePharmacyGroup");
					const basar::VarString SelectArticlesWithValidPrices("SelectArticlesWithValidPrices");
					const basar::VarString SelectPriceDataNotInZArtikel("SelectPriceDataNotInZArtikel");
					const basar::VarString InsertPriceData("InsertPriceData");
					const basar::VarString UpdatePriceDataDateToByPharmacyGroup("UpdatePriceDataDateToByPharmacyGroup");
					const basar::VarString DeletePriceDataByPharmacyGroup("DeletePriceDataByPharmacyGroup");
					const basar::VarString UpdatePriceDataDateToByPharmacyGroupArticle("UpdatePriceDataDateToByPharmacyGroupArticle");
					const basar::VarString DeletePriceDataByPharmacyGroupArticle("DeletePriceDataByPharmacyGroupArticle");
				}

				BEGIN_QUERY_BUILDER_DECLARATION(SelectPriceDataByPharmacyGroup)
				END_BUILDER_DECLARATION

				BEGIN_QUERY_BUILDER_DECLARATION(SelectPriceDataByArticlePharmacyGroup)
				END_BUILDER_DECLARATION

				BEGIN_QUERY_BUILDER_DECLARATION(SelectArticlesWithValidPrices)
				END_BUILDER_DECLARATION

				BEGIN_QUERY_BUILDER_DECLARATION(SelectPriceDataNotInZArtikel)
				END_BUILDER_DECLARATION
				
				BEGIN_WRITE_BUILDER_DECLARATION(InsertPriceData)
				END_BUILDER_DECLARATION
				
				BEGIN_WRITE_BUILDER_DECLARATION(UpdatePriceDataDateToByPharmacyGroup)
				END_BUILDER_DECLARATION
				
				BEGIN_WRITE_BUILDER_DECLARATION(DeletePriceDataByPharmacyGroup)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(UpdatePriceDataDateToByPharmacyGroupArticle)
				END_BUILDER_DECLARATION

				BEGIN_WRITE_BUILDER_DECLARATION(DeletePriceDataByPharmacyGroupArticle)
				END_BUILDER_DECLARATION
			} // end namespace pricedata
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace importpricelist

#endif // GUARD_PRICEDATAACC_H

