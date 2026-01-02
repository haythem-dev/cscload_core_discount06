//-------------------------------------------------------------------------------------------------//
/*! \file	pricelist2pharmacygroupacc.h
*   \brief	Accessor for the mapping pricelist to pharmacy group.
*   \author NTT DATA
*   \date	13.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_PRICELIST2PHARMACYGROUPACC_H
#define GUARD_PRICELIST2PHARMACYGROUPACC_H

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
			namespace pricelist2pharmacygroup
			{
				namespace lit
				{
					const basar::VarString PriceList2PharmacyGroupAcc("PriceList2PharmacyGroupAcc");
					const basar::VarString SelectPharmacyGroupByPriceListId("SelectPharmacyGroupByPriceListId");
				}

				BEGIN_QUERY_BUILDER_DECLARATION(SelectPharmacyGroupByPriceListId)
				END_BUILDER_DECLARATION
			} // end namespace pricelist2pharmaycygroup
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace importpricelist

#endif // GUARD_PRICELIST2PHARMACYGROUPACC_H

