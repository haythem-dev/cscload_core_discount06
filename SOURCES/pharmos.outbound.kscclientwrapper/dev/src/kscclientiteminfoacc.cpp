//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientiteminfoacc.cpp
 *  \brief  Accessor for infos about KSC items.
 *  \author Stefan Will
 *  \date   08.02.2008
 */
//-------------------------------------------------------------------------------------------------//

#include "kscclientiteminfoacc.h"
#include <libbasardbaspect.h>
#include <libbasarproperty_propertydescriptionlistref.h>

namespace acc_kscclientiteminfo
{
  using basar::db::aspect::SQLStringBuilder;

  // at least 1 SQL builder necessary for instantiating the accessor
  BUILDER_DEFINITION(DummyBuilder)
    DONT_CHECK_PROPERTIES(DummyBuilder)
    SQL_PATTERN(DummyBuilder, "");

  BEGIN_ACCESSOR_DEFINITION("AccKSCClientItemInfo")
    PROPERTY_DESCRIPTION_LIST(
        "int32 articleno; \
         string ean; \
         string articlecode; \
         int32 qtylack; \
         int32 lackreason; \
         int32 auxqty; \
         string articleunit; \
         string articlename; \
         string handout; \
         int16 auxbranchno; \
         string codeblocage; \
         int32 restdeliveryqty; \
         int32 deliveryqty; \
         string lackreasonctycode; \
         decimal pharmpurchprice; \
         decimal custpurchprice; \
         decimal pharmsellprice; \
         decimal taxrate; \
         date expirydate; \
         decimal lpprprice; \
         string seracode; \
         string xmlcode; \
         string xmltext; \
         string articleunitorg; \
         string articlenameorg; \
         string handoutorg; \
         decimal pharmpurchpriceorg; \
         decimal custpurchpriceorg; \
         decimal pharmsellpriceorg; \
         decimal taxrateorg; \
         decimal lpprpriceorg; \
         int32 articlenoorg; \
         string codeblocageorg; \
         string seracodeorg; \
         string xmlcodeorg; \
         string xmltextorg;")
  END_ACCESSOR_DEFINITION
}
