//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientitemacc.cpp
 *  \brief  Accessor for KSC items.
 *  \author Stefan Will
 *  \date   04.02.2008
 */
//-------------------------------------------------------------------------------------------------//

#include "kscclientitemacc.h"
#include <libbasardbaspect.h>
#include <libbasarproperty_propertydescriptionlistref.h>

namespace acc_kscclientitem
{
  using basar::db::aspect::SQLStringBuilder;

  // at least 1 SQL builder necessary for instantiating the accessor
  BUILDER_DEFINITION(DummyBuilder)
    DONT_CHECK_PROPERTIES(DummyBuilder)
    SQL_PATTERN(DummyBuilder, "");

  // kes 05.09.13: new items for ABBA-UW: discountpct, kindofdiscount
  // (dk)07.02.14: new item for ABBA-UW: rebateinkind (=Naturalrabatt), same as nonchargedqty
					//  Int32 rebateinkind        = Natural-Rabatt
					//	Decimal discountpct       = Freier Rabatt
					//	Int16 kindofdiscount      = Rabatt-Typ


  BEGIN_ACCESSOR_DEFINITION("AccKSCClientItem")
    PROPERTY_DESCRIPTION_LIST(
        "int32 articleno; \
         string ean; \
         string articlecode; \
         int32 orderqty; \
         int16 interbranchtransfer; \
         int16 subsequentdelivery; \
         int16 articlerequirementpurchase; \
         int16 partialdelivery; \
         int16 sequenceno; \
         string itemnote; \
         int32 idforigin; \
		 int32 ordernoorigin; \
		 int32 posnoorigin; \
		 int32 nonchargedqty; \
		 decimal discountpct; \
		 int16 kindofdiscount; \
		 int32 rebateinkind; \
		 string batch; \
		 ")
  END_ACCESSOR_DEFINITION
}
