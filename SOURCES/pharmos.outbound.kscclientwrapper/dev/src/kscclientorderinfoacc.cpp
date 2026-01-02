//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientorderinfoacc.cpp
 *  \brief  Accessor for infos about a KSC order.
 *  \author Stefan Will
 *  \date   08.02.2008
 */
//-------------------------------------------------------------------------------------------------//

#include "kscclientorderinfoacc.h"
#include <libbasardbaspect.h>
#include <libbasarproperty_propertydescriptionlistref.h>

namespace acc_kscclientorderinfo
{
  using basar::db::aspect::SQLStringBuilder;

  // at least 1 SQL builder necessary for instantiating the accessor
  BUILDER_DEFINITION(DummyBuilder)
    DONT_CHECK_PROPERTIES(DummyBuilder)
    SQL_PATTERN(DummyBuilder, "");

  BEGIN_ACCESSOR_DEFINITION("AccKSCClientOrderInfo")
    PROPERTY_DESCRIPTION_LIST(
        "int32 orderno; \
         string tourid; \
         date tourdate; \
         decimal valueoforder; \
         int32 linesoforder; \
         int32 lacklines; \
         int32 textlines; \
         string pharmacyname; \
         int16 deliverybranchno;")
  END_ACCESSOR_DEFINITION
}
