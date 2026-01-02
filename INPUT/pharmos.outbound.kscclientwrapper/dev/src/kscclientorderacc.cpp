//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientorderacc.cpp
 *  \brief  Accessor for KSC order.
 *  \author Klaus Hinz
 *  \date   21.01.2008
 */
//-------------------------------------------------------------------------------------------------//

#include "kscclientorderacc.h"
#include <libbasardbaspect.h>
#include <libbasarproperty_propertydescriptionlistref.h>

namespace acc_kscclientorder
{
  using basar::db::aspect::SQLStringBuilder;

  // at least 1 SQL builder necessary for instantiating the accessor
  BUILDER_DEFINITION(DummyBuilder)
    DONT_CHECK_PROPERTIES(DummyBuilder)
    SQL_PATTERN(DummyBuilder, "");

  BEGIN_ACCESSOR_DEFINITION("AccKSCClientOrder")
    PROPERTY_DESCRIPTION_LIST(
        "int16 branchno; \
         int32 customerno; \
         string ordertype; \
         string subordertype; \
         string pickingtype; \
         string bookingtype; \
         date deliverydate; \
         string orderheadline1; \
         string orderheadline2; \
         string orderheadline3; \
         string ordernote; \
         int16 callback; \
         string reference; \
         int16 originbranchno; \
         int32 batchtyp; \
         int32 deferredpaymentdate; \
		 string edideliverynote; \
		 int32 edideliverydate; \
		 int32 batchschreiben; \
		 ")
  END_ACCESSOR_DEFINITION
}
